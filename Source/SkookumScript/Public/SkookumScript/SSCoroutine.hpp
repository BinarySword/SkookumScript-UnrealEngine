//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Coroutine parameters & body classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSCOROUTINE_HPP
#define __SSCOROUTINE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSInvokableBase.hpp"
#include "SkookumScript/SSInstance.hpp"         // Used by tSSCoroutineMthd to determine size of method pointer


//=======================================================================================
// Global Structures
//=======================================================================================

class SSInvokedCoroutine;  // Pre-declaration


//---------------------------------------------------------------------------------------
// Notes      Method parameters & body abstract class
// Subclasses SSCoroutine, SSCoroutineMthd, SSCoroutineFunc
// Author(s)  Conan Reis
class SSCoroutineBase : public SSInvokableBase
  {
  public:

  // Common Methods

    SSCoroutineBase(const ASymbol & name, SSClass * scope_p) : SSInvokableBase(name, scope_p) {}
    SSCoroutineBase(const ASymbol & name, SSClass * scope_p, SSParameters * params_p) : SSInvokableBase(name, scope_p, params_p) {}

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSCoroutineBase(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
      virtual void assign_binary(const void ** binary_pp);
    #endif

    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
    #endif

    #if defined(SS_AS_STRINGS)
      virtual AString as_code_params() const;
    #endif

  // Methods

    virtual bool is_class_member() const  { return false; }
    virtual bool on_update(SSInvokedCoroutine * data_p) const = 0;
    virtual void track_memory(AMemoryStats * mem_stats_p) const = 0;


  // Data Members

    // Future: Specification and description of data used by this coroutine
    // Future: Description of coroutine for tools/debugging
    // Future: Bit field/list of incompatible/conflicting coroutines that this coroutine cannot run concurrently with (i.e. to movement related coroutines would likely conflict)

  };  // SSCoroutineBase


//---------------------------------------------------------------------------------------
// Notes      Custom/Compound Coroutine Class
// Author(s)  Conan Reis
class SSCoroutine : public SSCoroutineBase
  {
  friend class SSParser;

  public:
	  SS_NEW_OPERATORS(SSCoroutine);
  // Common Methods

    SSCoroutine(const ASymbol & name, SSClass * scope_p) : SSCoroutineBase(name, scope_p), m_expr_p(nullptr) {}
    SSCoroutine(const ASymbol & name, SSClass * scope_p, SSParameters * params_p, SSExpressionBase * body_p = nullptr) : SSCoroutineBase(name, scope_p, params_p), m_expr_p(body_p) {}
    virtual ~SSCoroutine();

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSCoroutine(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
      virtual void assign_binary(const void ** binary_pp);
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

    SSCoroutine & assign_take(SSCoroutine * coroutine_p);
    virtual bool  on_update(SSInvokedCoroutine * data_p) const;
    void          set_expression(SSExpressionBase * expr_p);

    // Overridden from SSMethodBase

      virtual void    track_memory(AMemoryStats * mem_stats_p) const;

    // Overridden from SSInvokableBase

      virtual eSSInvokable get_invoke_type() const;
      virtual bool         is_bound() const;

  protected:

  // Data Members

    // Optimized code block containing the statements to execute when this coroutine is
    // invoked.  It is either a SSCode, SSLiteral(nil), or some other expression.
    SSExpressionBase * m_expr_p;

  };  // SSCoroutine

//---------------------------------------------------------------------------------------
// Typedef for pointer to C++ coroutine method - which must be a member of a class
// derived from SkookumScript/SSInstance.
// It is associated with a Skookum coroutine and called every `on_update()` when in an
// Actor's list of invoked coroutines.
// 
// # Returns:
//   Boolean indicating whether the coroutine has completed.  `false` if the invoked
//   coroutine should be called again in the next update, `true` if the coroutine has
//   completed and it should be removed from the Actor's invoked coroutines list.
//   
// # Params:
//   scope_p:
//     Calling scope and working data for the invoked coroutine - this is the access point
//     for run-time information, passed arguments, data members, the call stack, etc.
//     - see `SSInvokedCoroutine` for a description of its methods and data members.
//     
// # See: Coroutine::on_update(), tSSCoroutineFunc, tSSMethodFunc, tSSMethodMthd
typedef bool (SSInstance::* tSSCoroutineMthd)(SSInvokedCoroutine * scope_p);

// Macro for casting to tSSCoroutineMthd
#define SSCOROUTINE_MTHD(_mthd) static_cast<tSSCoroutineMthd>(_mthd)
//#define SSCOROUTINE_MTHD(_mthd) reinterpret_cast<tSSCoroutineMthd>(_mthd)


//---------------------------------------------------------------------------------------
// Notes      Atomic Coroutine (C++) Method Class
// Author(s)  Conan Reis
class SSCoroutineMthd : public SSCoroutineBase
  {
  public:
	  SS_NEW_OPERATORS(SSCoroutineMthd);

  // Public Data Members

    //uint32_t _align32;  // $Note - CReis [Memory] Alignment of pointer to member is finicky if the owner class is not yet declared.

    // AMethod to call when this coroutine is running/being updated
    tSSCoroutineMthd m_update_m;


  // Common Methods

    SSCoroutineMthd(const ASymbol & name, SSClass * scope_p, SSParameters * params_p, tSSCoroutineMthd update_m = nullptr);

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSCoroutineMthd(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSInvokable get_invoke_type() const;
    virtual bool         is_bound() const;
    virtual bool         on_update(SSInvokedCoroutine * data_p) const;
    void                 set_update(tSSCoroutineMthd update_m);
    virtual void         track_memory(AMemoryStats * mem_stats_p) const;

  };  // SSCoroutineMthd


//---------------------------------------------------------------------------------------
// Typedef for pointer to C++ coroutine function - which must be a static or global
// function.
// It is associated with a Skookum coroutine and called every `on_update()` when in an
// Actor's list of invoked coroutines.
// 
// # Returns:
//   Boolean indicating whether the coroutine has completed.  `false` if the invoked
//   coroutine should be called again in the next update, `true` if the coroutine has
//   completed and it should be removed from the Actor's invoked coroutines list.
//   
// # Params:
//   scope_p:
//     Calling scope and working data for the invoked coroutine - this is the access point
//     for run-time information, passed arguments, data members, the call stack, etc.
//     - see `SSInvokedCoroutine` for a description of its methods and data members.
//     
// # See: Coroutine::on_update(), tSSCoroutineMthd, tSSMethodFunc, tSSMethodMthd
typedef bool (* tSSCoroutineFunc)(SSInvokedCoroutine * scope_p);


//---------------------------------------------------------------------------------------
// Notes      Atomic Coroutine Function Class
// Author(s)  Conan Reis
class SSCoroutineFunc : public SSCoroutineBase
  {
  public:
	  SS_NEW_OPERATORS(SSCoroutineFunc);

  // Public Data Members

    // AMethod to call when this coroutine is running/being updated
    tSSCoroutineFunc m_update_f;


  // Common Methods

    SSCoroutineFunc(const ASymbol & name, SSClass * scope_p, SSParameters * params_p, tSSCoroutineFunc update_f = nullptr);

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSCoroutineFunc(const ASymbol & name, SSClass * scope_p, const void ** binary_pp);
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Methods

    virtual eSSInvokable get_invoke_type() const;
    virtual bool         is_bound() const;
    virtual bool         is_placeholder();
    virtual bool         on_update(SSInvokedCoroutine * data_p) const;
    void                 set_update(tSSCoroutineFunc update_f);
    virtual void         track_memory(AMemoryStats * mem_stats_p) const;

  // Atomic Methods

    static bool coro_placeholder(SSInvokedCoroutine * scope_p);

  };  // SSCoroutineFunc


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSCoroutine.inl"
#endif


#endif  // __SSCOROUTINE_HPP

