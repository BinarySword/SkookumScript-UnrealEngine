//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FVector - Engine\Source\Runtime\Core\Public\Math\Vector.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


#ifndef __SSVECTOR3_HPP
#define __SSVECTOR3_HPP
#pragma once


//=======================================================================================
// Includes
//=======================================================================================

#include "AgogCore/AgogCore.hpp"
#include "UnrealMath.h"          // Vector math functions.


//=======================================================================================
// Global Defines / Macros
//=======================================================================================

#if defined(A_BITS64) && !defined(SS_VECTOR3_STORE_INDIRECT)
  // 64-bits - SSInstance has enough space to store FVecor directly.
  #define SS_VECTOR3_STORE_DIRECT
#else
  // 32-bits - SSInstance does not have enough space to store FVecor directly so must
  // allocate an FVector and store a pointer to it.
  #define SS_VECTOR3_STORE_INDIRECT
#endif

//---------------------------------------------------------------------------------------
// Storage specializations
#ifdef SS_VECTOR3_STORE_INDIRECT

  // Stored indirectly as pointer in SSUserData rather than whole structure
  template<> inline FVector * SSUserDataBase::as<FVector>() const          { return *as_stored<FVector*>(); }
  template<> inline void      SSUserDataBase::set(FVector * const & value) { *as_stored<FVector*>() = value; }

#else

  // Stored directly by value 
  template<> inline FVector * SSUserDataBase::as<FVector>() const        { return as_stored<FVector>(); }
  template<> inline void      SSUserDataBase::set(FVector const & value) { *as_stored<FVector>() = value; }

#endif

//=======================================================================================
// Global Data/Methods
//=======================================================================================

// Pre-declarations
class SSClass;
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
namespace SSVector3
  {

  // Data

    extern ASymbol    g_class_name;
    extern SSClass *  g_class_p;

  // Methods

    void register_bindings();

    SSInstance * as_instance(const FVector & vec);

  };  // SSVector3


#endif // __SSVECTOR3_HPP

