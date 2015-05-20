//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Literal expression for closures & anonymous/lambda code/functions
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSLITERALCLOSURE_HPP
#define __SSLITERALCLOSURE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AVCompactSorted.hpp"
#include "SkookumScript/SSExpressionBase.hpp"
#include "SkookumScript/SSMethod.hpp"
#include "SkookumScript/SSCoroutine.hpp"


//=======================================================================================
// Defines
//=======================================================================================


//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
// Notes      Shared info for closure literals and closure objects/invokables which
//            ensures that common data is available even if original expression is
//            unloaded from memory (via being a demand load class, IDE console workspace
//            command, etc.)
// Subclasses SSClosureMethodInfo, SSClosureCoroutineInfo           
// See Also   Other *Closure* classes
// Author(s)  Conan Reis
class SSClosureInfoBase : public ARefCountMix<SSClosureInfoBase>
  {
  friend class SSLiteralClosure;
  friend class SSParser;

  public:

  // Common Methods

    SSClosureInfoBase() {}
    SSClosureInfoBase(SSClosureInfoBase * info_p);
    virtual ~SSClosureInfoBase();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSClosureInfoBase(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      void     as_binary(void ** binary_pp) const;
      uint32_t as_binary_length() const;
    #endif


  // Debugging Methods

    #if defined(SS_AS_STRINGS)
      uint32_t get_captured_name_lengths() const;
    #endif


  // Methods

    const AVCompactSortedLogical<ASymbol> & get_captured() const  { return m_captured; }

    virtual SSExpressionBase * get_closure_expr() const = 0;
    virtual SSParameters &     get_closure_params() const = 0;
    virtual SSInvokableBase *  get_invokable() const = 0;
    virtual bool               is_method() const                  { return true; }
    virtual void               track_memory(AMemoryStats * mem_stats_p) const = 0;
    //virtual SSInvokedBase *   invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;

  protected:

  // Data Members

    // Captured local variables.
    // $Revisit - CReis - What about scoped variables?
    AVCompactSortedLogical<ASymbol> m_captured;

    // Location where code literal was defined (which is useful for debugging) is stored
    // in SSMethod/SSCoroutine qualifier.  It is set on load - there is no need to
    // serialize it.

  };  // SSClosureInfoBase


//---------------------------------------------------------------------------------------
// Notes      Shared info for closure literals and closure objects/invokables for methods
// See Also   SSClosure*
// Author(s)  Conan Reis
class SSClosureInfoMethod : public SSClosureInfoBase, public SSMethod
  {
  friend class SSParser;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSClosureInfoMethod);

    SSClosureInfoMethod();
    SSClosureInfoMethod(SSClosureInfoMethod * closure_p);
    virtual ~SSClosureInfoMethod();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSClosureInfoMethod(const void ** binary_pp);
    #endif


  // Methods

    virtual SSExpressionBase * get_closure_expr() const   { return m_expr_p; }
    virtual SSParameters &     get_closure_params() const { return *m_params_p; }
    virtual SSInvokableBase *  get_invokable() const      { return const_cast<SSClosureInfoMethod *>(this); }
    virtual void               track_memory(AMemoryStats * mem_stats_p) const;

  protected:

  // Data Members

    // SSQualifier::m_scope_p - indicates class where literal was defined or nullptr if
    //   from outside class hierarchy like workspace window, tool, etc.

    // ANamed::m_name - method name or some sort of location identifier if m_scope_p=nullptr

  };  // SSClosureInfoMethod


//---------------------------------------------------------------------------------------
// Notes      Shared info for closure literals and closure objects/invokables for coroutines
// See Also   SSClosure*
// Author(s)  Conan Reis
class SSClosureInfoCoroutine : public SSClosureInfoBase, public SSCoroutine
  {
  friend class SSParser;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSClosureInfoCoroutine);

    SSClosureInfoCoroutine();
    SSClosureInfoCoroutine(SSClosureInfoMethod * closure_p);
    virtual ~SSClosureInfoCoroutine();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSClosureInfoCoroutine(const void ** binary_pp);
    #endif


  // Methods

    virtual SSExpressionBase * get_closure_expr() const   { return m_expr_p; }
    virtual SSParameters &     get_closure_params() const { return *m_params_p; }
    virtual SSInvokableBase *  get_invokable() const      { return const_cast<SSClosureInfoCoroutine *>(this); }
    //virtual SSInvokedBase *    invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual bool               is_method() const          { return false; }
    virtual void               track_memory(AMemoryStats * mem_stats_p) const;

  protected:

  // Data Members

   // SSQualifier::m_scope_p - indicates class where literal was defined or nullptr if
    //   from outside class hierarchy like workspace window, tool, etc.

    // ANamed::m_name - method name or some sort of location identifier if m_scope_p=nullptr

  };  // SSClosureInfoCoroutine


//---------------------------------------------------------------------------------------
// Notes      Literal for closures & anonymous/lambda code/functions.
// See Also   SSClosure*
// Author(s)  Conan Reis
class SSLiteralClosure : public SSExpressionBase
  {
  friend class SSParser;

  public:

  // Common Methods

    SSLiteralClosure(SSExpressionBase * recv_p = nullptr);
    SSLiteralClosure(SSLiteralClosure * closure_method_p, eSSExprType type);
    virtual ~SSLiteralClosure();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSLiteralClosure(const void ** binary_pp, eSSExprType type);
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


  // Debugging Methods

    #if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * find_expr_by_pos(uint pos, eSSExprFind type = SSExprFind_all) const;
      virtual eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif


  // Methods

    SSClosureInfoBase *     get_closure_info() const  { return m_info_p; }
    virtual eSSExprType     get_type() const          { return m_info_p->is_method() ? SSExprType_closure_method : SSExprType_closure_coroutine; }
    virtual SSInvokedBase * invoke(SSObjectBase * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

  protected:

  // Data Members

    // Specified receiver object or nullptr if local this is captured.
    SSExpressionBase * m_receiver_p;

    // Reference counted closure info shared by this literal expression and any closure
    // objects/invokables.
    ARefPtr<SSClosureInfoBase> m_info_p;

  };  // SSLiteralClosure


//=======================================================================================
// Inline Methods
//=======================================================================================


#endif  // __SSLITERALCLOSURE_HPP

