//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FRotator
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSROTATIONANGLES_HPP
#define __SSROTATIONANGLES_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "UnrealMath.h"          // Vector math functions.


//=======================================================================================
// Global Defines / Macros
//=======================================================================================

#if defined(A_BITS64) && !defined(SS_ROTATION_ANGLES_STORE_INDIRECT)
// 64-bits - SSInstance has enough space to store FVecor directly.
#define SS_ROTATION_ANGLES_STORE_DIRECT
#else
// 32-bits - SSInstance does not have enough space to store FVecor directly so must
// allocate an FRotator and store a pointer to it.
#define SS_ROTATION_ANGLES_STORE_INDIRECT
#endif

//---------------------------------------------------------------------------------------
// Storage specializations
#ifdef SS_ROTATION_ANGLES_STORE_INDIRECT

// Stored indirectly as pointer in SSUserData rather than whole structure
template<> inline FRotator *  SSUserDataBase::as<FRotator>() const          { return *as_stored<FRotator*>(); }
template<> inline void        SSUserDataBase::set(FRotator * const & value) { *as_stored<FRotator*>() = value; }

#else

// Stored directly by value 
template<> inline FRotator *  SSUserDataBase::as<FRotator>() const        { return as_stored<FRotator>(); }
template<> inline void        SSUserDataBase::set(FRotator const & value) { *as_stored<FRotator>() = value; }

#endif


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
class SSRotationAngles
  {
  public:

    // Public Class Data

    static SSClass * ms_class_p;

    // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const FRotator & vec);

    static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_yaw_pitch_roll(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_Rotation(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_yaw(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pitch(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_roll(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_yaw_pitch_roll_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_yaw_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pitch_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_roll_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSRotationAngles


//=======================================================================================
// Inline Functions
//=======================================================================================


#endif // __SSROTATIONANGLES_HPP

