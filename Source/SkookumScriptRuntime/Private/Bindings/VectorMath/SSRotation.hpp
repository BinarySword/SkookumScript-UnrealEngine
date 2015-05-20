//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FQuat
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __ROTATION_HPP
#define __ROTATION_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "UnrealMath.h"          // Vector math functions.


//=======================================================================================
// Global Defines / Macros
//=======================================================================================

#if defined(A_BITS64) && !defined(SS_ROTATION_STORE_INDIRECT)
// 64-bits - SSInstance has enough space to store FQuat directly.
#define SS_ROTATION_STORE_DIRECT
#else
// 32-bits - SSInstance does not have enough space to store FVecor directly so must
// allocate an FQuat and store a pointer to it.
#define SS_ROTATION_STORE_INDIRECT
#endif

//---------------------------------------------------------------------------------------
// Storage specializations
#ifdef SS_ROTATION_STORE_INDIRECT

// Stored indirectly as pointer in SSUserData rather than whole structure
template<> inline FQuat * SSUserDataBase::as<FQuat>() const          { return *as_stored<FQuat*>(); }
template<> inline void    SSUserDataBase::set(FQuat * const & value) { *as_stored<FQuat*>() = value; }

#else

// Stored directly by value 
template<> inline FQuat * SSUserDataBase::as<FQuat>() const        { return as_stored<FQuat>(); }
template<> inline void    SSUserDataBase::set(FQuat const & value) { *as_stored<FQuat>() = value; }

#endif


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
class SSRotation
  {
  public:

    // Public Class Data

    static SSClass * ms_class_p;

    // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FQuat & vec);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_RotationAngles(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSRotation


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __ROTATION_HPP

