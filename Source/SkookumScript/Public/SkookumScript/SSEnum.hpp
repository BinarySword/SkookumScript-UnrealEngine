//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2010 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Enumeration class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSENUM_HPP
#define __SSENUM_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Macros / Defines
//=======================================================================================

//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSClassDescBase;
class SSInvokedMethod;
class SSInstance;
struct SSTypedData;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Atomic Enumeration class
// Author(s)  Conan Reis
class SSEnum
  {
  public:
  
  // Class Methods

    static SSTypedData * get_class_data_with_enum(SSClass * enum_class_p, SSEnumType enum_value);

    static void register_bindings();

    static SSInstance * as_instance(SSEnumType value, SSClass * pEnumClass);

  protected:

  // Internal Class Methods

    // SkookumScript Atomic Methods

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_string(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSEnum


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSEnum.inl"
#endif


#endif  // __SSENUM_HPP

