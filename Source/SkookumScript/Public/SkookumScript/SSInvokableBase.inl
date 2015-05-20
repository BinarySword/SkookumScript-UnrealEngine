//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Invokable parameters & body class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Default constructor - no name, class or parameters
// # Returns:  itself
// # Author(s): Conan Reis
A_INLINE SSInvokableBase::SSInvokableBase()
  {
  }

//---------------------------------------------------------------------------------------
// Constructor without parameters
// # Returns:  itself
// Arg         name - name of the object
// Arg         scope_p - class scope to use
// Arg         params - parameters object to take over contents of
// # See:      Transfer constructor of SSParameters.
// # Author(s): Conan Reis
A_INLINE SSInvokableBase::SSInvokableBase(
  const ASymbol & name,
  SSClass *       scope_p
  ) :
  SSQualifier(name, scope_p)
  {
  }

//---------------------------------------------------------------------------------------
// Constructor with name, class and parameters
// # Returns:  itself
// Arg         name - name of the object
// Arg         scope_p - class scope to use
// Arg         params_p - parameters use - see SSParameters::get_or_create()
// # Author(s): Conan Reis
A_INLINE SSInvokableBase::SSInvokableBase(
  const ASymbol & name,
  SSClass *       scope_p,
  SSParameters *  params_p
  ) :
  SSQualifier(name, scope_p),
  m_params_p(params_p)
  {
  }

//---------------------------------------------------------------------------------------
// #Description
//   Constructor with name, class and return type and optional parameter
//
// #Author(s) Conan Reis
A_INLINE SSInvokableBase::SSInvokableBase(
  // Name of invokable
  const ASymbol & name,
  // Result class type for parameter interface
  SSClassDescBase * result_type_p,
  // Optional single unary parameter - No parameter if nullptr.
  SSParameterBase * param_p
  ) :
  SSQualifier(name),
  m_params_p(SSParameters::get_or_create(result_type_p, param_p))
  {}

