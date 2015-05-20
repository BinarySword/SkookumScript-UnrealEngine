//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FQuat - Engine\Source\Runtime\Core\Public\Math\Rotation.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSRotation.hpp"
#include "SSRotationAngles.hpp"


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSRotation::ms_class_p = nullptr;


//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied rotation
// 
// # Author(s): Markus Breyer
SSInstance * SSRotation::as_instance(const FQuat & rot)
  {
#ifdef SS_ROTATION_STORE_DIRECT

  // Store FQuat directly in SSInstance
  return SSInstance::pool_new(ms_class_p, rot);

#else

  // Allocate an FQuat and store a pointer to it in SSInstance
  return SSInstance::pool_new(ms_class_p, new ("Skookum.FQuat") FQuat(rot));

#endif
  }

//---------------------------------------------------------------------------------------
void SSRotation::register_bindings()
  {
  ms_class_p = SSBrain::get_class("Rotation");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'Rotation' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor,       SSRotation::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy,  SSRotation::mthd_ctor_copy);
  ms_class_p->register_method_func(ASymbolX_dtor,       SSRotation::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,      SSRotation::mthd_String);
  ms_class_p->register_method_func("RotationAngles",    SSRotation::mthd_RotationAngles);

  ms_class_p->register_method_func(ASymbol_assign,      SSRotation::mthd_op_assign);

  ms_class_p->register_method_func("zero?",             SSRotation::mthd_zeroQ);
  ms_class_p->register_method_func("zero",              SSRotation::mthd_zero);

  }


//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@!() Rotation
// # Author(s): Markus Breyer
void SSRotation::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_ROTATION_STORE_DIRECT
  scope_p->this_set(FQuat::Identity);
#else
  scope_p->this_set(new ("Skookum.FQuat") FQuat(FQuat::Identity));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@!copy(Rotation rot) Rotation
// # Author(s): Markus Breyer
void SSRotation::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_ROTATION_STORE_DIRECT
  scope_p->this_set(*scope_p->get_arg<FQuat>(SSArg_1));
#else
  scope_p->this_set(new ("Skookum.FQuat") FQuat(*scope_p->get_arg<FQuat>(SSArg_1)));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@!!()
// # Author(s): Markus Breyer
void SSRotation::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
#ifdef SS_ROTATION_STORE_INDIRECT
  delete scope_p->this_as<FQuat>();
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@String() String
// # Author(s): Markus Breyer
void SSRotation::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FQuat & rotation = *scope_p->this_as<FQuat>();
    FRotator rotator(rotation);
    AString str(128u, "(yaw=%g, pitch=%g, roll=%g)", double(rotator.Yaw), double(rotator.Pitch), double(rotator.Roll));

    *result_pp = SSString::as_instance(str);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@RotationAngles() String
// # Author(s): Markus Breyer
void SSRotation::mthd_RotationAngles(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FQuat & rotation = *scope_p->this_as<FQuat>();
    *result_pp = SSRotationAngles::as_instance(FRotator(rotation));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@:=(Rotation rot) Rotation
// # Author(s): Markus Breyer
void SSRotation::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*scope_p->get_arg<FQuat>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@zero() Rotation
// # Author(s): Markus Breyer
void SSRotation::mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(FQuat::Identity);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Rotation@zero?() Boolean
// # Author(s): Markus Breyer
void SSRotation::mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FQuat & rotation = *scope_p->this_as<FQuat>();
    *result_pp = SSBoolean::pool_new(rotation.Equals(FQuat::Identity));
    }
  }

