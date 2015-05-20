//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Classes for expressions that can be evaluated/invoked
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSEXPRESSIONBASE_HPP
#define __SSEXPRESSIONBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ASymbol.hpp>
#include <AgogCore/APCompactArray.hpp>
#include <AgogCore/ARefCount.hpp>
#include "SkookumScript/SSDebug.hpp"


//=======================================================================================
// Global Macros / Defines
//=======================================================================================

// Store character position for debugging
#if (SKOOKUM & SS_DEBUG)
  #define SSDEBUG_SET_CHAR_POS(_expr_p, _pos)  (_expr_p)->m_source_idx = ((_pos) < UINT16_MAX) ? uint16_t(_pos) : UINT16_MAX
#else
  #define SSDEBUG_SET_CHAR_POS(_expr_p, _pos)  (void(0))
#endif


//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
// This is used to differentiate between different types of expressions when it is only
// known that an instance is of type SSExpressionBase, but not the specific subclass.
// It is returned by the method SSExpressionBase::get_type()
//
// *** NOTE *** These values are put directly into the compiled code binary using
// SSExpression::as_binary_typed() - and related methods - as a single byte (giving 255
// possible types) [SSUnaryParam and SSGroupParam actually squeeze it into 6 bits (63
// possible types) when reading/writing to binary - they will have to be modified if the
// number of types increases beyond 63], so changing these values requires changing the
// version number of the compiled code binary SSBrain_bin_code_id_version found in
// SSBrain.cpp.
enum eSSExprType
  {
  SSExprType__default                 =  0,  // Use default argument / receiver / clause (valid only as an argument, a receiver of an invocation, or as a default / else clause)
  SSExprType_identifier               =  1,  // SSIdentifier  temp
  SSExprType_identifier_member        =  2,  // SSIdentifierMember  m_value
  SSExprType_identifier_class_member  =  3,  // SSIdentifierClassMember  ms_random
  SSExprType_object_id                =  4,  // SSObjectId  MyClass@'some_name'
  SSExprType_literal                  =  5,  // SSLiteral (Boolean, Character, Integer, Real, String, Symbol, Class, nil, this, this_class, this_code)
  SSExprType_literal_list             =  6,  // SSLiteralList {elem1, elem2}
  SSExprType_closure_method           =  7,  // SSLiteralClosure(Method)  ^[do_this() do_that()]
  SSExprType_closure_coroutine        =  8,  // SSLiteralClosure(Coroutine)  ^[_do_this() _do_that()]
  SSExprType_bind                     =  9,  // SSBind - variable bind expression.  Could be a member variable, a parameter variable, or a temporary variable.
  SSExprType_cast                     = 10,  // SSCast - expr<>Class
  SSExprType_conversion               = 11,  // SSConversion - expr>>Class
  SSExprType_code                     = 12,  // SSCode - code block (generally nested)
  SSExprType_conditional              = 13,  // SSConditional - if bool1 [clause1] bool2 [clause2] else [else_clause]
  SSExprType_case                     = 14,  // SSCase - case compare test1 [clause1] test2 [clause2] else [else_clause]
  SSExprType_when                     = 15,  // SSWhen - clause when test
  SSExprType_unless                   = 16,  // SSUnless - clause unless test
  SSExprType_loop                     = 17,  // SSLoop - loop [ if loop_test() [exit] loop_code() ]
  SSExprType_loop_exit                = 18,  // SSLoopExit - (valid only in the scope of the loop it references)
  SSExprType_invoke                   = 19,  // SSInvocation - receiver.call()
  SSExprType_invoke_sync              = 20,  // SSInvokeSync - receiver%call()
  SSExprType_invoke_race              = 21,  // SSInvokeRace - receiver%>call()
  SSExprType_invoke_cascade           = 22,  // SSInvokeCascade - receiver :call1() :call2() :call3()
  SSExprType_invoke_closure_method    = 23,  // SSInvokeClosureMethod - closure_expr()
  SSExprType_invoke_closure_coroutine = 24,  // SSInvokeClosureCoroutine - closure_expr()
  SSExprType_instantiate              = 25,  // SSInstantiate - Instantiates / allocates / creates an object and initializes its data members to nil - called just prior to a constructor
  SSExprType_copy_invoke              = 26,  // SSCopyInvoke - Instantiates object via !copy() and calls initial method on it - expr!method() -> ExprType!copy(expr).method() or ExprType!copy(expr).[method() self()]
  SSExprType_concurrent_sync          = 27,  // SSConcurrentSync - convergent concurrent threaded expressions - sync [ _expr1() _expr2() _expr3() ]
  SSExprType_concurrent_race          = 28,  // SSConcurrentRace - concurrent racing expressions - race [ _expr1() _expr2() _expr3() ]
  SSExprType_concurrent_branch        = 29,  // SSConcurrentBranch - branched concurrent expression - branch [ _expr() ]
  SSExprType_divert                   = 30   // SSDivert - diverted expression - divert [ _expr() ]
  };

//---------------------------------------------------------------------------------------
// Indicates whether a given expression (and its sub expressions) has side effects or not.
// [Can be used in the place of bool to give more obvious context.]
enum eSSSideEffect
  {
  // Has no side-effects
  SSSideEffect_none      = 0,  // [implicitly coercible to false]
  // Has primary call, clause, elements, etc. effects
  SSSideEffect_present   = 1,  // [implicitly coercible to true]
  // Has secondary/incidental receiver, test expression, etc. effects though no primary
  // effects.  [Probably a mistake]
  SSSideEffect_secondary = 2 
  };


// Pre-declarations
class SSInstance;
class SSObjectBase;
class SSInvokedBase;
class SSInvokedExpression;
class SSParser;
class SSClassDescBase;
class SSClass;


//---------------------------------------------------------------------------------------
// Abstract base structure for applying some operation / iterating through expression
// structures - used in SSClass, SSExpressionBase, SSInvokableBase, their subclasses and
// any other structures that contain expressions.
// 
// [There may be a more sophisticated methodology for a callback with context though an
// abstract base base class is simple and effective.]
// 
// #See Also
//   SSClass::iterate_expressions(), SSClass::iterate_expressions_recurse(),
//   SSExpressionBase::iterate_expressions()
//   
// #Author(s) Conan Reis
struct SSApplyExpressionBase
  {
  // Called with each expression being iterated over.
  // Return true to stop/abort the iteration and false to continue iterating.
  // expr_p is the expression being iterated over and invokable_p is
  // the method/coroutine where the expression originates or nullptr if that info isn't
  // available.
  virtual eAIterateResult apply_expr(SSExpressionBase * expr_p, const SSInvokableBase * invokable_p) = 0;
  };


//---------------------------------------------------------------------------------------
// Notes      SkookumScript ExpressionBase
// Subclasses See eSSExprType above.
// Author(s)  Conan Reis
class SSExpressionBase
  {
  public:

  // Debug Data Members - public for quick access

    #if (SKOOKUM & SS_DEBUG)

      // Debug:  Character index position where this expression starts in the originally
      // parsed code file/string.  m_debug_info describes the source code origin.
      uint16_t m_source_idx; 

      // Debug: Debug flags & misc. info - such as breakpoint set flag - see SSDebug::eInfo
      uint16_t m_debug_info;

      // Debug: Any time a new expression is constructed, it's 'm_debug_info' will be set
      // to this value.  It can be changed when creating expressions that have varying
      // starting debug information like different origin locations
      // - such as SSDebugInfo::Flag_origin_internal (default), SSDebugInfo::Flag_origin_source, or
      // SSDebugInfo::Flag_origincustom.
      static uint16_t ms_new_expr_debug_info;

    #endif


  // Common Methods

    virtual ~SSExpressionBase();

  // Converter Methods

    virtual SSExpressionBase * as_copy() const;

    #if (SKOOKUM & SS_COMPILED_OUT)

      virtual void     as_binary(void ** binary_pp) const = 0;
      virtual uint32_t as_binary_length() const = 0;
      void             as_binary_typed(void ** binary_pp) const;
      uint32_t         as_binary_typed_length() const;

      static void      as_binary_typed(SSExpressionBase * expr_p, void ** binary_pp);
      static uint32_t  as_binary_typed_length(SSExpressionBase * expr_p);

    #endif // (SKOOKUM & SS_COMPILED_OUT)


    #if (SKOOKUM & SS_COMPILED_IN)

      static SSExpressionBase * from_binary_new(eSSExprType expr_type, const void ** binary_pp);
      static SSExpressionBase * from_binary_typed_new(const void ** binary_pp);

    #endif // (SKOOKUM & SS_COMPILED_IN)


    #if (SKOOKUM & SS_CODE_IN)

      virtual const SSExpressionBase * find_expr_last_no_side_effect() const;
      virtual eSSSideEffect            get_side_effect() const;

    #endif // (SKOOKUM & SS_CODE_IN)


    #if defined(SS_AS_STRINGS)

      virtual AString as_code() const = 0;
      AString         as_code_block() const;

    #endif // defined(SS_AS_STRINGS)


  // Methods

    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const = 0;
    SSInstance *            invoke_now(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr) const;
    void                    invoke_now_proc(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr) const;
    virtual void            null_receiver(SSExpressionBase * receiver_p);
    virtual void            track_memory(AMemoryStats * mem_stats_p) const = 0;

    // Type-checking Methods

      virtual eSSExprType get_type() const = 0;
      virtual bool        is_loop(const ASymbol & loop_name) const  { return false; }
      virtual bool        is_immediate(uint32_t * durational_idx_p = nullptr) const;
      virtual bool        is_nil() const                            { return (this == nullptr); }

    // Called by SSInvokedExpression

      virtual SSMind * get_updater(const SSInvokedExpression & iexpr) const;
      virtual bool     invoke_iterate(SSInvokedExpression * iexpr_p, SSInstance ** result_pp = nullptr) const;
      virtual void     invoke_exit(SSInvokedExpression * iexpr_p, SSInvokedExpression * sub_exit_p = nullptr) const  {}


    #if (SKOOKUM & SS_DEBUG)

      // Debugging Methods

      SSExpressionBase() : m_source_idx(SSExpr_char_pos_invalid), m_debug_info(ms_new_expr_debug_info) {}

      SSExpressionBase *         find_expr_on_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      SSExpressionBase *         find_expr_by_pos_first() const   { return find_expr_by_pos(0u); }
      SSExpressionBase *         find_expr_by_pos_last() const;
      SSExpressionBase *         find_expr_span(uint32_t source_idx, uint32_t * idx_begin_p = nullptr, uint32_t * idx_end_p = nullptr, eSSExprFind type = SSExprFind_all) const;
      void                       get_expr_span(const SSExpressionBase & expr, uint32_t * idx_begin_p = nullptr, uint32_t * idx_end_p = nullptr) const;
      virtual SSDebugInfo        get_debug_info(const SSInvokedExpression & iexpr) const;
      bool                       is_valid_origin_source() const   { return ((m_debug_info & SSDebugInfo::Flag_origin__mask) == SSDebugInfo::Flag_origin_source) && (m_source_idx != SSExpr_char_pos_invalid); }

      virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);

      static void set_new_expr_debug_info(uint16_t debug_info)    { ms_new_expr_debug_info = debug_info; }

    #endif

  };  // SSExpressionBase


//---------------------------------------------------------------------------------------
// Notes      SkookumScript loop expression
// Subclasses 
// See Also   SSLoopExit
// # Examples:    loop
//              [
//              ? loop_test() [exit].
//              loop_code()
//              ]
// Author(s)  Conan Reis
class SSLoop : public SSExpressionBase
  {
  friend class SSParser;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSLoop);

    SSLoop(SSExpressionBase * expr_p = nullptr, const ASymbol & name = ASymbol::get_null() ) : m_expr_p(expr_p), m_name(name) {}
    virtual ~SSLoop();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSLoop(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual bool is_loop(const ASymbol & loop_name) const  { return loop_name.is_null() || (loop_name == m_name); }

    // Overridden from SSExpressionBase

    virtual eSSExprType     get_type() const;
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual bool            is_immediate(uint32_t * durational_idx_p = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

    // Called by SSInvokedExpression

    virtual bool invoke_iterate(SSInvokedExpression * iexpr_p, SSInstance ** result_pp = nullptr) const;
    virtual void invoke_exit(SSInvokedExpression * iexpr_p, SSInvokedExpression * sub_exit_p = nullptr) const;

    // Debugging Methods
    #if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif

  protected:

  // Data Members

    // Optional loop name - so that a nested 'exit' can refer to it explicitly.
    ASymbol m_name;

    // Expression to loop
    SSExpressionBase * m_expr_p;

  // Class Data Members

  };  // SSLoop


//---------------------------------------------------------------------------------------
// Notes      SkookumScript loop exit expression
// Subclasses 
// See Also   
// # Examples:    loop
//              [
//              ? loop_test() [exit].
//              loop_code()
//              ]
// Author(s)  Conan Reis
class SSLoopExit : public SSExpressionBase
  {
  friend class SSParser;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSLoopExit);

    SSLoopExit(const ASymbol & name = ASymbol::get_null()) : m_name(name) {}
    virtual ~SSLoopExit();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSLoopExit(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    // Overridden from SSExpressionBase

    virtual eSSExprType     get_type() const;
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

  protected:

  // Data Members

    // Optional loop name - so that a nested 'exit' can refer to it explicitly.
    ASymbol m_name;

  };  // SSLoopExit


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Conversion to Class Type Primitive Expression
// See Also   SSCast
// # Examples:    expr>>Class
// Author(s)  Conan Reis
class SSConversion : public SSExpressionBase
  {
  friend class SSParser;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSConversion);

    SSConversion(SSClass * type_p, SSExpressionBase * expr_p);
    virtual ~SSConversion();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSConversion(const void ** binary_pp);
      void assign_binary(const void ** binary_pp);
    #endif

    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif

    #if (SKOOKUM & SS_CODE_IN)
      virtual const SSExpressionBase * find_expr_last_no_side_effect() const  { return this; }
      virtual eSSSideEffect            get_side_effect() const;
    #endif

    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    // Overridden from SSExpressionBase

      virtual eSSExprType     get_type() const;
      virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
      virtual void            null_receiver(SSExpressionBase * receiver_p);
      virtual void            track_memory(AMemoryStats * mem_stats_p) const;

      // Debugging Methods
      #if (SKOOKUM & SS_DEBUG)
        virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
        virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
      #endif

  protected:

  // Data Members

    // Desired class type
    SSClass * m_type_p;

    // Expression to convert
    SSExpressionBase * m_expr_p;

  };  // SSConversion


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Class Cast Primitive Expression
// See Also   SSCast
// # Examples:    expr<>Class
// Author(s)  Conan Reis
class SSCast : public SSExpressionBase
  {
  friend class SSParser;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSCast);

    SSCast(SSClassDescBase * type_p, SSExpressionBase * expr_p);
    virtual ~SSCast();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSCast(const void ** binary_pp);
      void assign_binary(const void ** binary_pp);
    #endif

    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif

    #if (SKOOKUM & SS_CODE_IN)
      virtual const SSExpressionBase * find_expr_last_no_side_effect() const  { return this; }
      virtual eSSSideEffect            get_side_effect() const;
    #endif

    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif

  // Methods

    // Overridden from SSExpressionBase

      virtual eSSExprType     get_type() const;
      virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
      virtual void            null_receiver(SSExpressionBase * receiver_p);
      virtual void            track_memory(AMemoryStats * mem_stats_p) const;

      // Debugging Methods
      #if (SKOOKUM & SS_DEBUG)
        virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
        virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
      #endif

  protected:

  // Data Members

    // Desired class type
    // $Revisit - CReis In theory this hint should not be needed during run-time (just
    // m_expr_p would be needed) if not debugging or parsing - i.e. if only SS_COMPILED_IN
    // is defined.  Currently only used if SS_CODE_IN, SS_CODE_OUT or SS_COMPILED_OUT is
    // defined.]
    ARefPtr<SSClassDescBase> m_type_p;

    // Expression to convert
    SSExpressionBase * m_expr_p;

  };  // SSCast


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSExpressionBase.inl"
#endif


#endif  // __SSEXPRESSIONBASE_HPP

