//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FRotator - Engine\Source\Runtime\Core\Public\Math\RotationAngles.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSRotationAngles.hpp"
#include "SSRotation.hpp"


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSRotationAngles::ms_class_p = nullptr;


//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied vector
// 
// # Author(s): Markus Breyer
SSInstance * SSRotationAngles::as_instance(const FRotator & angles)
  {
#ifdef SS_ROTATION_ANGLES_STORE_DIRECT

  // Store FRotator directly in SSInstance
  return SSInstance::pool_new(ms_class_p, angles);

#else

  // Allocate an FRotator and store a pointer to it in SSInstance
  return SSInstance::pool_new(ms_class_p, new ("Skookum.FRotator") FRotator(angles));

#endif
  }

//---------------------------------------------------------------------------------------
void SSRotationAngles::register_bindings()
  {
  ms_class_p = SSBrain::get_class("RotationAngles");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'RotationAngles' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor,        SSRotationAngles::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy,   SSRotationAngles::mthd_ctor_copy);
  ms_class_p->register_method_func("!yaw_pitch_roll",    SSRotationAngles::mthd_ctor_yaw_pitch_roll);
  ms_class_p->register_method_func(ASymbolX_dtor,        SSRotationAngles::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,       SSRotationAngles::mthd_String);
  ms_class_p->register_method_func("Rotation",           SSRotationAngles::mthd_Rotation);

  ms_class_p->register_method_func(ASymbol_assign,       SSRotationAngles::mthd_op_assign);

  ms_class_p->register_method_func("yaw",                SSRotationAngles::mthd_yaw);
  ms_class_p->register_method_func("pitch",              SSRotationAngles::mthd_pitch);
  ms_class_p->register_method_func("roll",               SSRotationAngles::mthd_roll);
  ms_class_p->register_method_func("yaw_pitch_roll_set", SSRotationAngles::mthd_yaw_pitch_roll_set);
  ms_class_p->register_method_func("yaw_set",            SSRotationAngles::mthd_yaw_set);
  ms_class_p->register_method_func("pitch_set",          SSRotationAngles::mthd_pitch_set);
  ms_class_p->register_method_func("roll_set",           SSRotationAngles::mthd_roll_set);
  ms_class_p->register_method_func("zero?",              SSRotationAngles::mthd_zeroQ);
  ms_class_p->register_method_func("zero",               SSRotationAngles::mthd_zero);

  }


//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@!() RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_ROTATION_ANGLES_STORE_DIRECT
  scope_p->this_set(FRotator::ZeroRotator);
#else
  scope_p->this_set(new ("Skookum.FRotator") FRotator(0.0f, 0.0f, 0.0f));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@!copy(RotationAngles angles) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_ROTATION_ANGLES_STORE_DIRECT
  scope_p->this_set(*scope_p->get_arg<FRotator>(SSArg_1));
#else
  scope_p->this_set(new ("Skookum.FRotator") FRotator(*scope_p->get_arg<FRotator>(SSArg_1)));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@!yaw_pitch_roll(Real yaw, Real pitch, Real roll) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_ctor_yaw_pitch_roll(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_ROTATION_ANGLES_STORE_DIRECT
  scope_p->this_set(FRotator(
    *scope_p->get_arg<SSRealType>(SSArg_2),
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_3)));
#else
  scope_p->this_set(new ("Skookum.FRotator") FRotator(
    *scope_p->get_arg<SSRealType>(SSArg_2),
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_3)));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@!!()
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
#ifdef SS_ROTATION_ANGLES_STORE_INDIRECT
  delete scope_p->this_as<FRotator>();
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@String() String
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FRotator & rot = *scope_p->this_as<FRotator>();
    AString str(128u, "(yaw=%g, pitch=%g, roll=%g)", double(rot.Yaw), double(rot.Pitch), double(rot.Roll));

    *result_pp = SSString::as_instance(str);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@Rotation() Rotation
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_Rotation(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FRotator & rot = *scope_p->this_as<FRotator>();
    *result_pp = SSRotation::as_instance(rot.Quaternion());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@:=(RotationAngles angles) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*scope_p->get_arg<FRotator>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@yaw() Real
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_yaw(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FRotator>()->Yaw);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@pitch() Real
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_pitch(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FRotator>()->Pitch);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@roll() Real
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_roll(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FRotator>()->Roll);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@yaw_pitch_roll_set(Real yaw, Real pitch, Real roll) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_yaw_pitch_roll_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FRotator *    rot_p = this_p->as<FRotator>();

  rot_p->Yaw   = *scope_p->get_arg<SSRealType>(SSArg_1);
  rot_p->Pitch = *scope_p->get_arg<SSRealType>(SSArg_2);
  rot_p->Roll  = *scope_p->get_arg<SSRealType>(SSArg_3);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@yaw_set(Real yaw) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_yaw_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FRotator>()->Yaw = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@pitch_set(Real pitch) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_pitch_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FRotator>()->Pitch = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@roll_set(Real roll) RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_roll_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FRotator>()->Roll = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@zero() RotationAngles
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  FRotator * rot_p = this_p->as<FRotator>();
  rot_p->Yaw   = 0.0f;
  rot_p->Pitch = 0.0f;
  rot_p->Roll  = 0.0f;

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   RotationAngles@zero?() Boolean
// # Author(s): Markus Breyer
void SSRotationAngles::mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(scope_p->this_as<FRotator>()->IsZero());
    }
  }

