//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Invocation classes: SSInvokeBase, SSInvocation, SSInvokeSync, SSInvokeRace,
// SSInvokeCascade, SSInstantiate and SSCopyInvoke
// 
// #Author(s):  Conan Reis
//=======================================================================================


#ifndef __SSINVOCATION_HPP
#define __SSINVOCATION_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSExpressionBase.hpp"
#include "SkookumScript/SSQualifier.hpp"
#include "AgogCore/APCompactArray.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSMethodCall;
class SSIdentifier;

//---------------------------------------------------------------------------------------
// Notes      SkookumScript invocation / call selector / descriptor
// Subclasses SSMethodCall, SSCoroutineCall
// Author(s)  Conan Reis
class SSInvokeBase : public SSQualifier

  {
  friend class SSParser;

  public:
	  SS_NEW_OPERATORS(SSInvokeBase);
  // Common Methods
    SSInvokeBase(const ASymbol & call_name = ASymbol::get_null(), SSClass * scope_p = nullptr);
    SSInvokeBase(SSInvokeBase * call_p);
    virtual ~SSInvokeBase();

  // Converter Methods

    // Binary

    #if (SKOOKUM & SS_COMPILED_OUT)

      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
      void             as_binary_typed(void ** binary_pp) const;
      uint32_t         as_binary_typed_length() const;
      //void             assign_binary(const void ** binary_pp);

    #endif // (SKOOKUM & SS_COMPILED_OUT)


    #if (SKOOKUM & SS_COMPILED_IN)
      void                  assign_binary(const void ** binary_pp);
      static SSInvokeBase * from_binary_typed_new(const void ** binary_pp);
    #endif


    // AString Methods
    #if defined(SS_AS_STRINGS)

      virtual AString as_code() const;
      AString         as_string_name() const;

    #endif


    // Debugging Methods
    #if (SKOOKUM & SS_DEBUG)
      SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif


  // Methods

    virtual eSSInvokeType                    get_invoke_type() const = 0;
    const APCompactArray<SSExpressionBase> & get_args() const           { return m_arguments; }
    const APCompactArray<SSIdentifier> &     get_return_args() const    { return m_return_args; }
    virtual SSInvokedBase *                  invoke_call(SSInstance * receiver_p, SSObjectBase * scope_p, SSInvokedBase * caller_p, SSInstance ** result_pp) const = 0;
    virtual void                             track_memory(AMemoryStats * mem_stats_p) const = 0;

  protected:
    
  // Data Members

    // $Note - CReis Future: An index into the invokable (method, coroutine) table
    // in this call's invoker's class.  This would replace the 'm_name' data member.
    //uint32_t m_call_index;

    // Array of dynamic expressions to be invoked and have their instance results passed
    // to the method/coroutine.
    //   - Arguments fill the parameters based on the order of their index position
    //   - Arguments that are nullptr indicate that they should be filled with the
    //     corresponding default argument from the parameter list
    //
    // $Revisit - CReis Future: Each default expression could be put directly in place [the
    // same data structure as the parameter list could be used, but a mechanism so that
    // they are not deleted more than once must be determined].  This future plan for
    // argument lists requires that the available invokables (and their parameter lists)
    // are in memory and that it is possible to determine the class scope of the
    // invokable call.  [See SSInvokedContextBase::data_append_args()]
    APCompactArray<SSExpressionBase> m_arguments;

    // Return argument bindings
    //   - Argument identifiers fill the return parameters based on the order of their index position
    //   - Argument identifiers that are nullptr indicate that they are skipped/ignored.
    // $Revisit - [Memory] CReis since few closures use return args it would save memory
    // to have this class without them and a separate SSInvokeRArgsBase with them.
    APCompactArray<SSIdentifier> m_return_args;
  };  // SSInvokeBase


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Invocation.
//            This class is similar to the SSInvokeCascade class except that it has
//            only one 'command' to give to the receiver and similar to SSInstantiate
//            except that its receiver can be any expression and not just a new instance.
// See Also   SSInvokeSync, SSInvokeRace, SSInvokeCascade, SSInstantiate
// # Examples:    receiver.call()
// Author(s)  Conan Reis
class SSInvocation : public SSExpressionBase
  {
  friend class SSParser;

  public:
  // Common Methods

    SS_NEW_OPERATORS(SSInvocation);

    SSInvocation(SSInvokeBase * call_p, SSExpressionBase * receiver_p = nullptr);
    virtual ~SSInvocation();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSInvocation(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSExprType     get_type() const      { return SSExprType_invoke; }
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual bool            is_immediate(uint32_t * durational_idx_p = nullptr) const;
    virtual void            null_receiver(SSExpressionBase * receiver_p);
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

  // Debugging Methods

    #if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif

  protected:
    
  // Data Members

    // The object that results from the evaluation of this expression is the
    // target/subject/receiver of subroutine 'm_call_p'.  If 'm_receiver_p' is nullptr
    // then 'this' - i.e. the topmost scope - is inferred.
    SSExpressionBase * m_receiver_p;

    // Subroutine to call - SSCoroutineCall or SSMethodCall
    SSInvokeBase * m_call_p;

  };  // SSInvocation


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Apply Invocation.
//            This class is similar to the SSInvocation class except that the command is
//            applied only to valid receiver objects based on a runtime test of the
//            receiver class type.
//
//            There are 3 receiver categories:
//              nil (class None)
//                - the invocation is ignored
//              list object (class List)
//                - the invocation is applied to each element concurrently (for durational
//                  calls).  If the list is empty the invocation is ignored.
//              some other object type (anything other than None and List)
//                - the invocation is called normally
// See Also   SSInvocation, SSInvokeRace, SSInvokeCascade, SSInstantiate
// # Examples:    receiver%call()
//            receiver_or_nil%call()
//            list%call()
//            {1, 2, 3}%add_assign(1)  // becomes {2, 3, 4}
// Author(s)  Conan Reis
class SSInvokeSync : public SSInvocation
  {
  friend class SSParser;

  public:

  // Common Methods

	SS_NEW_OPERATORS(SSInvokeSync);

    SSInvokeSync(SSInvokeBase * call_p, SSExpressionBase * receiver_p = nullptr) : SSInvocation(call_p, receiver_p) {}
    virtual ~SSInvokeSync()  {}

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSInvokeSync(const void ** binary_pp) : SSInvocation(binary_pp) {}
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSExprType     get_type() const      { return SSExprType_invoke_sync; }
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

  };  // SSInvokeSync


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Race Invocation.
//            This class is similar to the SSInvocation class except that the command is
//            applied only to valid receiver objects based on a runtime test of the
//            receiver class type.
//
//            There are 3 receiver categories:
//              nil (class None)
//                - the invocation is ignored
//              list object (class List)
//                - the invocation is applied to each element concurrently (for durational
//                  calls).  If the list is empty the invocation is ignored.
//              some other object type (anything other than None and List)
//                - the invocation is called normally
//
//            This class is very similar to SSConcurrentRace and changes to this class might
//            need to be reflected there and vice-versa.
// See Also   SSInvocation, SSInvokeCascade, SSInstantiate, SSConcurrentRace
// # Examples:    receiver%>call()
//            receiver_or_nil%>call()
//            list%>call()
//            {1, 2, 3}%>add_assign(1)               // becomes {2, 3, 4}
//            {guy1, guy2, guy3}%>_path_to_pos(pos)  // After first guy gets to pos other guys stop
// Author(s)  Conan Reis
class SSInvokeRace : public SSInvocation
  {
  friend class SSParser;

  public:

  // Common Methods

	SS_NEW_OPERATORS(SSInvokeRace);

    SSInvokeRace(SSInvokeBase * call_p, SSExpressionBase * receiver_p = nullptr) : SSInvocation(call_p, receiver_p) {}
    virtual ~SSInvokeRace()  {}

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSInvokeRace(const void ** binary_pp) : SSInvocation(binary_pp) {}
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSExprType     get_type() const      { return SSExprType_invoke_race; }
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual bool            invoke_iterate(SSInvokedExpression * iexpr_p, SSInstance ** result_pp = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

  };  // SSInvokeRace


//---------------------------------------------------------------------------------------
// Notes      SkookumScript invocation cascade - i.e. different subroutines called
//            serially (one after another) that act upon the same receiver.
//            This class is similar to the SSInvocation class except that it has more
//            than one 'command' to give to the receiver.
// See Also   SSInvocation, SSInvokeSync, SSInvokeRace, SSInstantiate
// # Examples:    receiver
//              :call1()
//              :call2()
//              :call3()
// Author(s)  Conan Reis
class SSInvokeCascade : public SSExpressionBase
  {
  friend class SSParser;
  friend class SSInvokedExpression;

  public:
  // Common Methods

    SS_NEW_OPERATORS(SSInvokeCascade);

    SSInvokeCascade(SSExpressionBase * receiver_p = nullptr) : m_receiver_p(receiver_p) {}
    virtual ~SSInvokeCascade();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSInvokeCascade(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSExprType     get_type() const;
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual bool            is_immediate(uint32_t * durational_idx_p = nullptr) const;
    virtual void            null_receiver(SSExpressionBase * receiver_p);
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

  // Class Methods

    static void clean_up(SSInvokedExpression * iexpr_p);
    
  // Data Members

    // The object that results from the evaluation of this expression is the target for
    // subroutines 'm_invoke_calls'.  If 'm_receiver_p' is nullptr then 'this' - i.e. the topmost
    // scope - is inferred.
    SSExpressionBase * m_receiver_p;

    // Subroutines to call - SSCoroutineCall or SSMethodCall
    APArrayFree<SSInvokeBase> m_invoke_calls;

  };  // SSInvokeCascade


//---------------------------------------------------------------------------------------
// SkookumScript Instantiation expression.
// Instantiates / allocates / creates an object (instance of a class) initializes its
// data members to nil and calls its constructor.
// 
// #Examples
//   Class!()
// 
// #See Also   SSCopyInvoke, SSInvocation, SSInvokeSync, SSInvokeRace, SSInvokeCascade
// #Author(s)  Conan Reis
class SSInstantiate : public SSExpressionBase
  {
  friend class SSParser;

  public:
  // Common Methods

    SS_NEW_OPERATORS(SSInstantiate);

    SSInstantiate(SSClass * class_p, SSMethodCall * ctor_p) : m_class_p(class_p), m_ctor_p(ctor_p) {}
    virtual ~SSInstantiate();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSInstantiate(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSExprType     get_type() const;
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

    // Debugging Methods

    #if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif

  protected:

  // Data Members

    // Instance of class to create
    SSClass * m_class_p;

    // Constructor method call
    SSMethodCall * m_ctor_p;

  };  // SSInstantiate


//---------------------------------------------------------------------------------------
// SkookumScript Copy Instantiation & method call expression.
// Instantiates object via !copy() and calls initial method on it.
// 
// * Could derive from SSInstantiate though every method would need to be rewritten anyway.
// 
// #Examples
//   expr!method()
//   
//   // Equivalent to:
//     ExprType!copy(expr).method()
//     ExprType!copy(expr).[method() self()]
// 
// #See Also   SSInstantiation, SSInvocation, SSInvokeSync, SSInvokeRace, SSInvokeCascade
// #Author(s)  Conan Reis
class SSCopyInvoke : public SSExpressionBase
  {
  friend class SSParser;

  public:
  // Common Methods

    SS_NEW_OPERATORS(SSCopyInvoke);

    SSCopyInvoke(SSClass * class_p, SSMethodCall * ctor_p, SSMethodCall * method_p) :
      m_class_p(class_p), m_ctor_p(ctor_p), m_method_p(method_p) {}
    virtual ~SSCopyInvoke();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSCopyInvoke(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSExprType     get_type() const;
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

    // Debugging Methods

    #if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif

  protected:

  // Data Members

    // Instance of class to create
    SSClass * m_class_p;

    // Constructor method call
    SSMethodCall * m_ctor_p;

    // Initial method call
    SSMethodCall * m_method_p;

  };  // SSInstantiate


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInvocation.inl"
#endif


#endif  // __SSINVOCATION_HPP

