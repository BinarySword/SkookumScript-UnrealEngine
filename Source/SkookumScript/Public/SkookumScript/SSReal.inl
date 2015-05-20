//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Real (floating point) class
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
A_INLINE SSInstance * SSReal::as_instance(SSRealType value)
  {
  return SSInstance::pool_new(SSBrain::ms_real_class_p, value);
  }


