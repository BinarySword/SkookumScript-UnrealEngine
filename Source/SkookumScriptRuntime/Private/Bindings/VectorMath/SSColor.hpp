//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FLinearColor
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSCOLOR_HPP
#define __SSCOLOR_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "UnrealMath.h"          // Vector math functions.


//=======================================================================================
// Global Defines / Macros
//=======================================================================================

#if defined(A_BITS64) && !defined(SS_COLOR_STORE_INDIRECT)
  // 64-bits - SSInstance has enough space to store FLinearColor directly.
  #define SS_COLOR_STORE_DIRECT
#else
  // 32-bits - SSInstance does not have enough space to store FLinearColor directly so must
  // allocate an FLinearColor and store a pointer to it.
  #define SS_COLOR_STORE_INDIRECT
#endif

//---------------------------------------------------------------------------------------
// Storage specializations
#ifdef SS_COLOR_STORE_INDIRECT

  // Stored indirectly as pointer in SSUserData rather than whole structure
  template<> inline FLinearColor *  SSUserDataBase::as<FLinearColor>() const          { return *as_stored<FLinearColor*>(); }
  template<> inline void            SSUserDataBase::set(FLinearColor * const & value) { *as_stored<FLinearColor*>() = value; }

#else

  // Stored directly by value 
  template<> inline FLinearColor *  SSUserDataBase::as<FLinearColor>() const        { return as_stored<FLinearColor>(); }
  template<> inline void            SSUserDataBase::set(FLinearColor const & value) { *as_stored<FLinearColor>() = value; }

#endif


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;
  
  
//---------------------------------------------------------------------------------------
class SSColor
  {
  public:

  // Public Class Data

    static SSClass * ms_class_p;

  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FLinearColor & col);
    static SSInstance * as_instance(const FColor & col);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_rgba(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_rgb(SSInvokedMethod * scope_p, SSInstance ** result_pp);
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

    static void mthd_r(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_g(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_b(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_a(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_rgba_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_r_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_g_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_b_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_a_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSColor


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __SSCOLOR_HPP

