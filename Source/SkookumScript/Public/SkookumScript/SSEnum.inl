//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2010 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Enumeration class
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
A_INLINE SSInstance * SSEnum::as_instance(SSEnumType value, SSClass * pEnumClass)
  {
  return SSInstance::pool_new(pEnumClass, value);
  }

