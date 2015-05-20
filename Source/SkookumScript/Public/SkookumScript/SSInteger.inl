//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Integer (signed 32-bit integer) class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSBrain.hpp"
#include "SkookumScript/SSInstance.hpp"


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSInstance * SSInteger::as_instance(SSIntegerType value)
  {
  return SSInstance::pool_new(SSBrain::ms_integer_class_p, value);
  }

