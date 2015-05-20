//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Coroutine parameters & body classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================


//=======================================================================================
// SSCoroutineMthd Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         name - identifier name for the coroutine 
// Arg         scope_p - class scope to use
// Arg         params_p - parameters object to take over contents of
// Arg         update_m - Atomic method to call when the coroutine is invoked / updating
//             - nullptr if supplied at a later time.  (Default nullptr)
// # See:      Transfer constructor of SSParameters.
// # Author(s): Conan Reis
A_INLINE SSCoroutineMthd::SSCoroutineMthd(
  const ASymbol & name,
  SSClass *       scope_p,
  SSParameters *  params_p,
  tSSCoroutineMthd update_m // = nullptr
  ) :
  SSCoroutineBase(name, scope_p, params_p),
  m_update_m(update_m)
  {
  }

//---------------------------------------------------------------------------------------
// Sets the update method for this coroutine
// Arg         update_m - Atomic method to call when the coroutine is invoked / updating
// # Author(s): Conan Reis
A_INLINE void SSCoroutineMthd::set_update(tSSCoroutineMthd update_m)
  {
  m_update_m = update_m;
  }


//=======================================================================================
// SSCoroutineFunc Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         name - identifier name for the coroutine 
// Arg         scope_p - class scope to use
// Arg         params_p - parameters object to take over contents of
// Arg         update_f - Atomic method to call when the coroutine is invoked / updating
//             - nullptr if supplied at a later time.  (Default nullptr)
// # See:      Transfer constructor of SSParameters.
// # Author(s): Conan Reis
A_INLINE SSCoroutineFunc::SSCoroutineFunc(
  const ASymbol & name,
  SSClass *       scope_p,
  SSParameters *  params_p,
  tSSCoroutineFunc update_f // = nullptr
  ) :
  SSCoroutineBase(name, scope_p, params_p),
  m_update_f(update_f)
  {
  }

//---------------------------------------------------------------------------------------
// Sets the update method for this coroutine
// Arg         update_f - Atomic method to call when the coroutine is invoked / updating
// # Author(s): Conan Reis
A_INLINE void SSCoroutineFunc::set_update(tSSCoroutineFunc update_f)
  {
  m_update_f = update_f;
  }

