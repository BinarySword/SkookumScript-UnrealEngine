//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FTransform - Engine\Source\Runtime\Core\Public\Math\Transform.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSTRANSFORM_HPP
#define __SSTRANSFORM_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "SkookumScript/SSInstance.hpp"
#include "SkookumScript/SSInvokedBase.hpp"
#include "UnrealMath.h"          // Vector math functions.

//=======================================================================================
// Global Defines / Macros
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specialization - SSInvokedContextBase stored indirectly as pointer in SSUserData rather than whole structure
template<> inline FTransform *  SSUserDataBase::as<FTransform>() const          { return *as_stored<FTransform*>(); }
template<> inline void          SSUserDataBase::set(FTransform * const & value) { *as_stored<FTransform*>() = value; }

//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;
  
//---------------------------------------------------------------------------------------
class SSTransform
  {
  public:

  // Public Class Data

    static SSClass * ms_class_p;

  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FTransform & vec);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_position(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_position_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_rotation(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_rotation_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_scale(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_scale_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_identity(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSTransform


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __SSTRANSFORM_HPP

