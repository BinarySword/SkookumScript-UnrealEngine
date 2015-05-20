//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Class wrapper for info used to make a method call/invocation - i.e. coroutine
//             identifier (name/index) and passed argument info.
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSCOROUTINECALL_HPP
#define __SSCOROUTINECALL_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSInvocation.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
// Notes      Info used to make a coroutine call/invocation - i.e. coroutine identifier
//            (name/index) and passed argument info.
// Author(s)  Conan Reis
class SSCoroutineCall : public SSInvokeBase
  {
  friend class SSParser;

  public:
	  SS_NEW_OPERATORS(SSCoroutineCall);
  // Common Methods

    SSCoroutineCall(const ASymbol & coroutine_name = ASymbol::get_null(), SSClass * scope_p = nullptr);
    SSCoroutineCall(SSInvokeBase * call_p);

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)

      SSCoroutineCall(const void ** binary_pp);

    #endif // (SKOOKUM & SS_COMPILED_IN)


  // Methods

    // Overriding from SSInvokeBase

    virtual eSSInvokeType   get_invoke_type() const;
    virtual SSInvokedBase * invoke_call(SSInstance * receiver_p, SSObjectBase * scope_p, SSInvokedBase * caller_p, SSInstance ** result_pp) const;
    virtual void            track_memory(AMemoryStats * mem_stats_p) const;

  };  // SSCoroutineCall


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSCoroutineCall.inl"
#endif


#endif  // __SSCOROUTINECALL_HPP

