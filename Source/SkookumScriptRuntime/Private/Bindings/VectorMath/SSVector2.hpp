//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FVector2D - Engine\Source\Runtime\Core\Public\Math\Vector.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSVECTOR2_HPP
#define __SSVECTOR2_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "UnrealMath.h"          // Vector math functions.


//=======================================================================================
// Global Defines / Macros
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specializations

// Stored directly by value 
template<> inline FVector2D * SSUserDataBase::as<FVector2D>() const        { return as_stored<FVector2D>(); }
template<> inline void        SSUserDataBase::set(FVector2D const & value) { *as_stored<FVector2D>() = value; }


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;
  
  
//---------------------------------------------------------------------------------------
class SSVector2
  {
  public:

  // Public Class Data

    static SSClass * ms_class_p;

  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FVector2D & vec);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
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
    static void mthd_xy_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_x_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_y_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_cross(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_distance(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_distance_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dot(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_length_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_nearQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    //static void mthd_angle(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_normalize(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSVector2


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __SSVECTOR2_HPP

