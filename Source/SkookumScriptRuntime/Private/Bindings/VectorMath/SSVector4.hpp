//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FVector4 - Engine\Source\Runtime\Core\Public\Math\Vector.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSVECTOR4_HPP
#define __SSVECTOR4_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "UnrealMath.h"          // Vector math functions.


//=======================================================================================
// Global Defines / Macros
//=======================================================================================

#if defined(A_BITS64) && !defined(SS_VECTOR4_STORE_INDIRECT)
  // 64-bits - SSInstance has enough space to store FVector4 directly.
  #define SS_VECTOR4_STORE_DIRECT
#else
  // 32-bits - SSInstance does not have enough space to store FVecor directly so must
  // allocate an FVector4 and store a pointer to it.
  #define SS_VECTOR4_STORE_INDIRECT
#endif

//---------------------------------------------------------------------------------------
// Storage specializations
#ifdef SS_VECTOR4_STORE_INDIRECT

  // Stored indirectly as pointer in SSUserData rather than whole structure
  template<> inline FVector4 * SSUserDataBase::as<FVector4>() const          { return *as_stored<FVector4*>(); }
  template<> inline void      SSUserDataBase::set(FVector4 * const & value) { *as_stored<FVector4*>() = value; }

#else

  // Stored directly by value 
  template<> inline FVector4 * SSUserDataBase::as<FVector4>() const        { return as_stored<FVector4>(); }
  template<> inline void      SSUserDataBase::set(FVector4 const & value) { *as_stored<FVector4>() = value; }

#endif


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;
  
  
//---------------------------------------------------------------------------------------
class SSVector4
  {
  public:

  // Public Class Data

    static SSClass * ms_class_p;

  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FVector4 & vec);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_xyzw(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_xyz(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_xy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_subtract(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_subtract_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_multiply(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_multiply_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_divide(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_divide_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_x(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_y(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_z(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_w(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_xyzw_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_x_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_y_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_z_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_w_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    //static void mthd_distance(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_distance_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dot(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_length_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_nearQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    //static void mthd_angle(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_normalize(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSVector4


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __SSVECTOR4_HPP

