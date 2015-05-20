//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Method parameters & body classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSMETHOD_HPP
#define __SSMETHOD_HPP


//=======================================================================================
// Includes
//=======================================================================================

class ASymbol;

#include "SkookumScript/SSInvokableBase.hpp"
#include "SkookumScript/SSInstance.hpp"       // Used by tSSMethodMthd to determine size of method pointer


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declration
class SSInvokedMethod;

//---------------------------------------------------------------------------------------
// Notes      Method parameters & body abstract class
// Subclasses SSMethod, SSMethodFunc, SSMethodMthd
// Author(s)  Conan Reis
class SSMethodBase : public SSInvokableBase
  {
  public:
  // Common Methods

    SSMethodBase(const ASymbol & name, SSClass * scope_p) : SSInvokableBase(name, scope_p) {}
    SSMethodBase(const ASymbol & name, SSClass * scope_p, SSParameters * params_p) : SSInvokableBase(name, scope_p, params_p) {}
    SSMethodBase(const ASymbol & name, SSParameterBase * param_p, SSClassDescBase * result_type_p) : SSInvokableBase(name, result_type_p, param_p) {}

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSMethodBase(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
      virtual void assign_binary(const void ** binary_pp);
    #endif

    #if (SKOOKUM & SS_COMPILED_OUT)

      bool             is_operator() const;
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;

    #endif // (SKOOKUM & SS_COMPILED_OUT)

    #if defined(SS_AS_STRINGS)
      virtual AString as_code_params() const;
    #endif

  // Methods

    SSMethodBase & assign(const SSMethodBase & method)      { SSInvokableBase::assign(method); return *this; }

    virtual void invoke(SSInvokedMethod * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const = 0;
    virtual bool is_class_member() const;
    virtual void track_memory(AMemoryStats * mem_stats_p) const = 0;

  };  // SSMethodBase


//---------------------------------------------------------------------------------------
// Notes      Custom/Compound Method Class
// Author(s)  Conan Reis
class SSMethod : public SSMethodBase
  {
  friend class SSParser;

  public:
  // Common Methods

    SS_NEW_OPERATORS(SSMethod);
    SSMethod(const ASymbol & name, SSClass * scope_p) : SSMethodBase(name, scope_p), m_expr_p(nullptr) {}
    SSMethod(const ASymbol & name, SSClass * scope_p, SSParameters * params_p, SSExpressionBase * expr_p = nullptr) : SSMethodBase(name, scope_p, params_p), m_expr_p(expr_p) {}
    virtual ~SSMethod();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSMethod(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
      void assign_binary(const void ** binary_pp);
    #endif


    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


    // Debugging Methods
    #if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * get_custom_expr() const;
    #endif


  // Methods

    SSMethod & assign_take(SSMethod * method_p);
	void       set_expression(SSExpressionBase * expr_p);
	void       replace_expression(SSExpressionBase * expr_p);

    // Overridden from SSMethodBase

      virtual void    invoke(SSInvokedMethod * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
      SSInvokedBase * invoke_deferred(SSInvokedMethod * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
      virtual void    track_memory(AMemoryStats * mem_stats_p) const;

    // Overridden from SSInvokableBase

      virtual eSSInvokable get_invoke_type() const;
      virtual bool         is_bound() const;

  protected:

  // Data Members

    // Optimized code block containing the statements to execute when this coroutine is
    // invoked.  It is either a SSCode, SSLiteral(nil), or some other expression.
    SSExpressionBase * m_expr_p;

  };  // SSMethod


//---------------------------------------------------------------------------------------
// Typedef for pointer to C++ method function - which must be a static or global function.
// It is associated with a Skookum method and called whenever the method is invoked.
// 
// # Params:
//   scope_p:
//     Calling scope and working data for the invoked code - this is the path for
//     accessing run-time information, passed arguments, data members, the call stack,
//     etc. - see `SSInvokedMethod` for a description of its methods and data members.
//   result_pp:
//     pointer to a pointer to store the instance resulting from the invocation of this
//     expression.  If it is `nullptr`, then the result does not need to be returned and
//     only side-effects are desired.  (Default `nullptr`)
//     
// # See: tSSMethodMthd, tSSCoroutineFunc, tSSCoroutineMthd
typedef void (* tSSMethodFunc)(SSInvokedMethod * scope_p, SSInstance ** result_pp);


//---------------------------------------------------------------------------------------
// SkookumScript method wrapper for atomic/C++ function Class
class SSMethodFunc : public SSMethodBase
  {
  public:
	  SS_NEW_OPERATORS(SSMethodFunc);

  // Public Data Members

    tSSMethodFunc m_atomic_f;

  // Common Methods

    SSMethodFunc(const ASymbol & name, SSClass * scope_p, SSParameters * params_p, tSSMethodFunc atomic_f = nullptr);
    SSMethodFunc(const ASymbol & name, SSClass * scope_p, tSSMethodFunc atomic_f = nullptr) : SSMethodBase(name, scope_p), m_atomic_f(atomic_f) {}
    SSMethodFunc(const ASymbol & name, SSClassDescBase * result_type_p, SSParameterBase * param_p, tSSMethodFunc atomic_f = nullptr) : SSMethodBase(name, param_p, result_type_p), m_atomic_f(atomic_f) {}


  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSMethodFunc(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    void set_function(tSSMethodFunc atomic_f) { m_atomic_f = atomic_f; }

    // Overridden from SSMethodBase

      virtual void invoke(SSInvokedMethod * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
      virtual void track_memory(AMemoryStats * mem_stats_p) const;

    // Overridden from SSInvokableBase

      virtual eSSInvokable get_invoke_type() const;
      virtual bool         is_bound() const;
      virtual bool         is_placeholder();


  // Atomic Methods

    static void mthd_placeholder(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSMethodFunc


//---------------------------------------------------------------------------------------
// Typedef for pointer to C++ method function - which must be an instance method from a
// class derived from `SSInstance`.
// It is associated with a Skookum method and called whenever the method is invoked.
// 
// # Params:
//   scope_p:
//     Calling scope and working data for the invoked code - this is the path for
//     accessing run-time information, passed arguments, data members, the call stack,
//     etc. - see `SSInvokedMethod` for a description of its methods and data members.
//   result_pp:
//     pointer to a pointer to store the instance resulting from the invocation of this
//     expression.  If it is `nullptr`, then the result does not need to be returned and
//     only side-effects are desired.  (Default `nullptr`)
// 
// # Notes:
//   *** Pointer to member methods can be of different sizes depending on the class that
//   is used and for different compilers! ***
//     
// # See: tSSMethodFunc, tSSCoroutineFunc, tSSCoroutineMthd
typedef void (SSInstance::* tSSMethodMthd)(SSInvokedMethod * scope_p, SSInstance ** result_pp);


//---------------------------------------------------------------------------------------
// SkookumScript method wrapper for atomic/C++ instance method Class
class SSMethodMthd : public SSMethodBase
  {
  public:
	  SS_NEW_OPERATORS(SSMethodMthd);

  // Public Data Members

    // $Vital - CReis This sometimes gives the warning C4121: alignment of a member was sensitive to packing
    // Investigate it and fix it or remove warning if it is not useful.
    // *** Pointer to member methods can be of different sizes depending on the class
    // that is used and for different compilers!  On the PC this is 12 bytes ***
    tSSMethodMthd m_atomic_m;

  // Common Methods

    SSMethodMthd(const ASymbol & name, SSClass * scope_p, SSParameters * params_p, tSSMethodMthd atomic_m = nullptr);
    SSMethodMthd(const ASymbol & name, SSClassDescBase * result_type_p, SSParameterBase * param_p, tSSMethodMthd atomic_m = nullptr) : SSMethodBase(name, param_p, result_type_p), m_atomic_m(atomic_m) {}
    SSMethodMthd(const ASymbol & name, SSClassDescBase * result_type_p, tSSMethodMthd atomic_m = nullptr) : SSMethodBase(name, nullptr, result_type_p), m_atomic_m(atomic_m) {}


  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSMethodMthd(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    void set_function(tSSMethodMthd atomic_m) { m_atomic_m = atomic_m; }

    // Overridden from SSMethodBase

      virtual void invoke(SSInvokedMethod * scope_p, SSInvokedBase * caller_p = nullptr, SSInstance ** result_pp = nullptr) const;
      virtual void track_memory(AMemoryStats * mem_stats_p) const;

    // Overridden from SSInvokableBase

      virtual eSSInvokable get_invoke_type() const;
      virtual bool         is_bound() const;

  };  // SSMethodMthd


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSMethod.inl"
#endif


#endif  // __SSMETHOD_HPP

