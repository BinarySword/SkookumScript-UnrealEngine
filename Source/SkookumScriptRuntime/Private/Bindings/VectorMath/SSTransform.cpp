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


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSTransform.hpp"
#include "SSVector3.hpp"
#include "SSRotation.hpp"

#include "UnrealMath.h"   // Transform math functions.


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSTransform::ms_class_p = nullptr;

//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied transform
// 
// # Author(s): Markus Breyer
SSInstance * SSTransform::as_instance(const FTransform & transform)
  {
  // $Revisit - CReis Could rewrite this as `SSInstance::from<FTransform>(transform)`
  // Could store class as SSClass * SSClass::get<FTransform>()
  // Allocate an FTransform and store a pointer to it in SSInstance
  return SSInstance::pool_new(ms_class_p, new ("Skookum.FTransform") FTransform(transform));
  }

//---------------------------------------------------------------------------------------
void SSTransform::register_bindings()
  {
  ms_class_p = SSBrain::get_class("Transform");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'Transform' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor,       SSTransform::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy,  SSTransform::mthd_ctor_copy);
  ms_class_p->register_method_func(ASymbolX_dtor,       SSTransform::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,      SSTransform::mthd_String);

  ms_class_p->register_method_func(ASymbol_assign,      SSTransform::mthd_op_assign);

  ms_class_p->register_method_func("position",          SSTransform::mthd_position);
  ms_class_p->register_method_func("position_set",      SSTransform::mthd_position_set);
  ms_class_p->register_method_func("rotation",          SSTransform::mthd_rotation);
  ms_class_p->register_method_func("rotation_set",      SSTransform::mthd_rotation_set);
  ms_class_p->register_method_func("scale",             SSTransform::mthd_scale);
  ms_class_p->register_method_func("scale_set",         SSTransform::mthd_scale_set);

  ms_class_p->register_method_func("identity",          SSTransform::mthd_identity);

  }


//---------------------------------------------------------------------------------------
// # Skookum:   Transform@!() Transform
// # Author(s): Markus Breyer
void SSTransform::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  scope_p->this_set(new ("Skookum.FTransform") FTransform());
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@!copy(Vector vec) Vector
// # Author(s): Markus Breyer
void SSTransform::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  scope_p->this_set(new ("Skookum.FTransform") FTransform(*scope_p->get_arg<FTransform>(SSArg_1)));
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@!!()
// # Author(s): Markus Breyer
void SSTransform::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  delete scope_p->this_as<FTransform>();
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@String() String
// # Author(s): Markus Breyer
void SSTransform::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FTransform *  transform_p = scope_p->this_as<FTransform>();
    const FVector &     location = transform_p->GetLocation();
    const FRotator      rotator(transform_p->GetRotation());
    const FVector &     scale = transform_p->GetScale3D();
    AString             str(128u, "t=(%g, %g, %g) yaw=%g pitch=%g roll=%g s=(%g, %g, %g)", 
                          double(location.X), double(location.Y), double(location.Z),
                          double(rotator.Yaw), double(rotator.Pitch), double(rotator.Roll),
                          double(scale.X), double(scale.Y), double(scale.Z));

    *result_pp = SSString::as_instance(str);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@:=(Transform xform) Transform
// # Author(s): Markus Breyer
void SSTransform::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FTransform>() = *scope_p->get_arg<FTransform>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@position() Vector
// # Author(s): Markus Breyer
void SSTransform::mthd_position(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSVector3::as_instance(scope_p->this_as<FTransform>()->GetLocation());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@position_set(Vector pos) Transform
// # Author(s): Markus Breyer
void SSTransform::mthd_position_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FTransform>()->SetLocation(*scope_p->get_arg<FVector>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@rotation() Rotation
// # Author(s): Markus Breyer
void SSTransform::mthd_rotation(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSRotation::as_instance(scope_p->this_as<FTransform>()->GetRotation());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@rotation_set(Rotation rot) Transform
// # Author(s): Markus Breyer
void SSTransform::mthd_rotation_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FTransform>()->SetRotation(*scope_p->get_arg<FQuat>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@scale() Vector
// # Author(s): Markus Breyer
void SSTransform::mthd_scale(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSVector3::as_instance(scope_p->this_as<FTransform>()->GetScale3D());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@scale_set(Vector scale) Transform
// # Author(s): Markus Breyer
void SSTransform::mthd_scale_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FTransform>()->SetScale3D(*scope_p->get_arg<FVector>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Transform@identity() Transform
// # Author(s): Markus Breyer
void SSTransform::mthd_identity(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FTransform>()->SetIdentity();

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

