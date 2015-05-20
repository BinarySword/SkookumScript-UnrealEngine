//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Method parameters & body classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

//=======================================================================================
// SSMethodFunc Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         name - identifier name for the method
// Arg         scope_p - class scope to use
// Arg         params_p - parameters object to take over contents of
// Arg         atomic_f - C++ static / class member function to call when the method is
//             invoked / called - nullptr if supplied at a later time.  (Default nullptr)
// # See:      Transfer constructor of SSParameters.
// # Author(s): Conan Reis
A_INLINE SSMethodFunc::SSMethodFunc(
  const ASymbol & name,
  SSClass *       scope_p,
  SSParameters *  params_p,
  tSSMethodFunc   atomic_f // = nullptr
  ) :
  SSMethodBase(name, scope_p, params_p),
  m_atomic_f(atomic_f)
  {
  }


//=======================================================================================
// SSMethodMthd Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         name - identifier name for the method
// Arg         scope_p - class scope to use
// Arg         params_p - parameters object to take over contents of
// Arg         atomic_m - C++ method to call when the method is invoked / called - nullptr
//             if supplied at a later time.  (Default nullptr)
// # See:      Transfer constructor of SSParameters.
// # Author(s): Conan Reis
A_INLINE SSMethodMthd::SSMethodMthd(
  const ASymbol & name,
  SSClass *       scope_p,
  SSParameters *  params_p,
  tSSMethodMthd   atomic_m // = nullptr
  ) :
  SSMethodBase(name, scope_p, params_p),
  m_atomic_m(atomic_m)
  {
  }

//=======================================================================================
// SSMethod Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Overwrite the expression, written as a hack to allow external Skookum commands
//			   to keep their code after it has run
// Arg         expr_p - pointer to code (can be nullptr)
// # Notes:    Function so we can set the expression to nullptr so that it doesn't get
//             deleted by the method destructor intended only to be used as a hack to get
//             the external Skookum calls to work correctly
// # Author(s): Richard Orth
A_INLINE void SSMethod::replace_expression(SSExpressionBase * expr_p)
  {
  m_expr_p = expr_p;
  }

