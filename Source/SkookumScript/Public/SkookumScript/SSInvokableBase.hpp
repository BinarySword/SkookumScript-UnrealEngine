//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Invokable parameters & body class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSINVOKABLEBASE_HPP
#define __SSINVOKABLEBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSQualifier.hpp"
#include "SkookumScript/SSParameters.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declaration
struct SSApplyExpressionBase;
class  SSExpressionBase;

//---------------------------------------------------------------------------------------
// Notes      SkookumScript InvokableBase
// Subclasses SSMethodBase (SSMethod, SSMethodFunc, SSMethodMthd), SSCoroutineBase (SSCoroutine,
//            SSCoroutineMthd, SSCoroutineFunc)
// Author(s)  Conan Reis
class SSInvokableBase : public SSQualifier
  {
  public:

  // Common Methods

    SSInvokableBase();
    SSInvokableBase(const ASymbol & name, SSClass * scope_p);
    SSInvokableBase(const ASymbol & name, SSClass * scope_p, SSParameters * params_p);
    SSInvokableBase(const ASymbol & name, SSClassDescBase * result_type_p, SSParameterBase * param_p);
    virtual ~SSInvokableBase();

  // Methods

    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const = 0;
      virtual AString as_code_params() const = 0;
    #endif

    // Debugging Methods
    #if (SKOOKUM & SS_DEBUG)
      SSExpressionBase * find_expr_by_pos(uint32_t pos, eSSExprFind type = SSExprFind_all) const;
      SSExpressionBase * find_expr_on_pos(uint32_t pos, eSSExprFind type = SSExprFind_all) const;
      SSExpressionBase * find_expr_span(uint32_t source_idx, uint32_t * idx_begin_p = nullptr, uint32_t * idx_end_p = nullptr, eSSExprFind type = SSExprFind_all) const;
      void               get_expr_span(const SSExpressionBase & expr, uint32_t * idx_begin_p, uint32_t * idx_end_p) const;
      eSSMember          get_member_type() const;
      eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p);
    #endif

    AString                    as_string_name(bool qualified = true) const;
    SSInvokableBase &          assign(const SSInvokableBase & invokable)  { SSQualifier::operator=(invokable); m_params_p = invokable.m_params_p; return *this; }
    virtual SSExpressionBase * get_custom_expr() const;
    const SSParameters &       get_params() const                         { return *m_params_p; }
    SSParameters &             get_params()                               { return *m_params_p; }
    void                       set_params(SSParameters * params_p)        { m_params_p = params_p; }
    virtual eSSInvokable       get_invoke_type() const = 0;
    virtual bool               is_bound() const = 0;
    virtual bool               is_class_member() const = 0;
    virtual bool               is_placeholder();
    //virtual SSInvokableBase * evaluate(SSObjectBase * scope_p, SSInvokedBase * caller_p) = 0;
    //virtual SSInvokableBase * give_result(SSInstance * result_p, SSInvokableBase * sub_expr_p, SSInvokedBase * caller_p) = 0;

  protected:

  // Data Members

    ARefPtr<SSParameters> m_params_p;

    // Future: ADebug / content creation data structure for parameter descriptions

  };  // SSInvokableBase


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInvokableBase.inl"
#endif


#endif  // __SSINVOKABLEBASE_HPP

