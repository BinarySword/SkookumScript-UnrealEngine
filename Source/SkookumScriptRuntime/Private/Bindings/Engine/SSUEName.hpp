//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2015 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FName
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSUENAME_HPP
#define __SSUENAME_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "NameTypes.h"

//=======================================================================================
// Global Defines / Macros
//=======================================================================================

// Stored directly by value 
template<> inline FName *  SSUserDataBase::as<FName>() const        { return as_stored<FName>(); }
template<> inline void     SSUserDataBase::set(FName const & value) { *as_stored<FName>() = value; }

//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;
  
  
//---------------------------------------------------------------------------------------
class SSUEName
  {
  public:

  // Public Class Data

    static SSClass * ms_class_p;

  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FName & name);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    // Class Methods of String

    static void mthd_String_to_Name(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSUEName


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __SSUENAME_HPP

