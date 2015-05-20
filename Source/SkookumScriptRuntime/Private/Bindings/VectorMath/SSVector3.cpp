//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FVector - Engine\Source\Runtime\Core\Public\Math\Vector3.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSVector3.hpp"
#include "SSRotation.hpp"
#include "SSTransform.hpp"


namespace SSVector3
  {

  //=======================================================================================
  // Data
  //=======================================================================================

  SSClass * g_class_p = nullptr;
  ASymbol   g_class_name;

  //=======================================================================================
  // Methods
  //=======================================================================================

  //---------------------------------------------------------------------------------------
  // Returns a script class instance wrapper for the supplied vector
  SSInstance * as_instance(const FVector & vec)
    {
    #ifdef SS_VECTOR3_STORE_DIRECT

      // Store FVector directly in SSInstance
      return SSInstance::pool_new(g_class_p, vec);

    #else

      // Allocate an FVector and store a pointer to it in SSInstance
      return SSInstance::pool_new(g_class_p, new ("Skookum.FVector") FVector(vec));

    #endif
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@!() Vector3
  // # Author(s): Markus Breyer
  static void mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Results are ignored for constructors
    #ifdef SS_VECTOR3_STORE_DIRECT
      scope_p->this_set(FVector::ZeroVector);
    #else
      scope_p->this_set(new ("Skookum.FVector") FVector(0.0f, 0.0f, 0.0f));
    #endif
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@!copy(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Results are ignored for constructors
    #ifdef SS_VECTOR3_STORE_DIRECT
      scope_p->this_set(*scope_p->get_arg<FVector>(SSArg_1));
    #else
      scope_p->this_set(new ("Skookum.FVector") FVector(*scope_p->get_arg<FVector>(SSArg_1)));
    #endif
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@!xyz(Real x, Real y, Real z) Vector3
  // # Author(s): Markus Breyer
  static void mthd_ctor_xyz(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Results are ignored for constructors
    #ifdef SS_VECTOR3_STORE_DIRECT
      scope_p->this_as<FVector>()->Set(
        *scope_p->get_arg<SSRealType>(SSArg_1),
        *scope_p->get_arg<SSRealType>(SSArg_2),
        *scope_p->get_arg<SSRealType>(SSArg_3));
    #else
      scope_p->this_set(new ("Skookum.FVector") FVector(
        *scope_p->get_arg<SSRealType>(SSArg_1),
        *scope_p->get_arg<SSRealType>(SSArg_2),
        *scope_p->get_arg<SSRealType>(SSArg_3)));
    #endif
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@!xy(Real x, Real y) Vector3
  // # Author(s): Markus Breyer
  static void mthd_ctor_xy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Results are ignored for constructors
    #ifdef SS_VECTOR3_STORE_DIRECT
      scope_p->this_as<FVector>()->Set(
        *scope_p->get_arg<SSRealType>(SSArg_1),
        *scope_p->get_arg<SSRealType>(SSArg_2),
        0.0f);
    #else
      scope_p->set_this<FVector>(new ("Skookum.FVector") FVector(
        *scope_p->get_arg<SSRealType>(SSArg_1),
        *scope_p->get_arg<SSRealType>(SSArg_2),
        0.0f));
    #endif
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@!!()
  // # Author(s): Markus Breyer
  static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    #ifdef SS_VECTOR3_STORE_INDIRECT
      delete scope_p->this_as<FVector>();
    #endif
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@String() String
  // # Author(s): Markus Breyer
  static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      FVector * vector_p = scope_p->this_as<FVector>();
      AString   str(128u, "(%g, %g, %g)", double(vector_p->X), double(vector_p->Y), double(vector_p->Z));

      *result_pp = SSString::as_instance(str);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@:=(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    this_p->set(*scope_p->get_arg<FVector>(SSArg_1));

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@=(Vector3 vec) Boolean
  // # Author(s): Markus Breyer
  static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSBoolean::pool_new(*scope_p->this_as<FVector>() == *scope_p->get_arg<FVector>(SSArg_1));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@~=(Vector3 vec) Boolean
  // # Author(s): Markus Breyer
  static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSBoolean::pool_new(*scope_p->this_as<FVector>() != *scope_p->get_arg<FVector>(SSArg_1));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@+(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      FVector vector(*scope_p->this_as<FVector>());

      vector += *scope_p->get_arg<FVector>(SSArg_1);

      *result_pp = as_instance(vector);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@+=(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    *this_p->as<FVector>() += *scope_p->get_arg<FVector>(SSArg_1);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@-(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_subtract(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      FVector vector(*scope_p->this_as<FVector>());

      vector -= *scope_p->get_arg<FVector>(SSArg_1);

      *result_pp = as_instance(vector);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@-=(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_subtract_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    *this_p->as<FVector>() -= *scope_p->get_arg<FVector>(SSArg_1);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@*(Real num) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_multiply(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      FVector vector(*scope_p->this_as<FVector>());

      vector *= *scope_p->get_arg<SSRealType>(SSArg_1);

      *result_pp = as_instance(vector);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@*=(Real num) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_multiply_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    *this_p->as<FVector>() *= *scope_p->get_arg<SSRealType>(SSArg_1);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@/(Real num) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_divide(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      FVector vector(*scope_p->this_as<FVector>());

      vector /= *scope_p->get_arg<SSRealType>(SSArg_1);

      *result_pp = as_instance(vector);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@/=(Real num) Vector3
  // # Author(s): Markus Breyer
  static void mthd_op_divide_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    *this_p->as<FVector>() /= *scope_p->get_arg<SSRealType>(SSArg_1);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@rotate_by(Rotation rot) Vector3
  // # Author(s): Markus Breyer
  static void mthd_rotate_by(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      const FVector & vec = *scope_p->this_as<FVector>();
      const FQuat & rot = *scope_p->get_arg<FQuat>(SSArg_1);

      *result_pp = as_instance(rot.RotateVector(vec));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@unrotate_by(Rotation rot) Vector3
  // # Author(s): Markus Breyer
  static void mthd_unrotate_by(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      const FVector & vec = *scope_p->this_as<FVector>();
      const FQuat rot = *scope_p->get_arg<FQuat>(SSArg_1);

      *result_pp = as_instance(rot.Inverse().RotateVector(vec));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@transform_by(Transform xform) Vector3
  // # Author(s): Markus Breyer
  static void mthd_transform_by(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      const FVector & vec = *scope_p->this_as<FVector>();
      const FTransform & xform = *scope_p->get_arg<FTransform>(SSArg_1);

      *result_pp = as_instance(xform.TransformPosition(vec));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@untransform_by(Transform xform) Vector3
  // # Author(s): Markus Breyer
  static void mthd_untransform_by(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      const FVector & vec = *scope_p->this_as<FVector>();
      const FTransform & xform = *scope_p->get_arg<FTransform>(SSArg_1);

      *result_pp = as_instance(xform.InverseTransformPosition(vec));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@x() Real
  // # Author(s): Markus Breyer
  static void mthd_x(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(scope_p->this_as<FVector>()->X);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@y() Real
  // # Author(s): Markus Breyer
  static void mthd_y(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(scope_p->this_as<FVector>()->Y);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@z() Real
  // # Author(s): Markus Breyer
  static void mthd_z(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(scope_p->this_as<FVector>()->Z);
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@xyz_set(Real x, Real y, Real z) Vector3
  // # Author(s): Markus Breyer
  static void mthd_xyz_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();
    FVector *    vec_p  = this_p->as<FVector>();

    vec_p->X = *scope_p->get_arg<SSRealType>(SSArg_1);
    vec_p->Y = *scope_p->get_arg<SSRealType>(SSArg_2);
    vec_p->Z = *scope_p->get_arg<SSRealType>(SSArg_3);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@x_set(Real x) Vector3
  // # Author(s): Markus Breyer
  static void mthd_x_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    this_p->as<FVector>()->X = *scope_p->get_arg<SSRealType>(SSArg_1);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@y_set(Real y) Vector3
  // # Author(s): Markus Breyer
  static void mthd_y_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    this_p->as<FVector>()->Y = *scope_p->get_arg<SSRealType>(SSArg_1);


    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@z_set(Real z) Vector3
  // # Author(s): Markus Breyer
  static void mthd_z_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    this_p->as<FVector>()->Z = *scope_p->get_arg<SSRealType>(SSArg_1);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@zero() Vector3
  // # Author(s): Markus Breyer
  static void mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();

    this_p->as<FVector>()->Set(0.0f, 0.0f, 0.0f);

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@zero?() Boolean
  // # Author(s): Markus Breyer
  static void mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSBoolean::pool_new(scope_p->this_as<FVector>()->IsZero());
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@cross(Vector3 vec) Vector3
  // # Author(s): Markus Breyer
  static void mthd_cross(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = as_instance(FVector::CrossProduct(
        *scope_p->this_as<FVector>(),
        *scope_p->get_arg<FVector>(SSArg_1)));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@distance(Vector3 vec) Real
  // # Author(s): Markus Breyer
  static void mthd_distance(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(FVector::Dist(
        *scope_p->this_as<FVector>(),
        *scope_p->get_arg<FVector>(SSArg_1)));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@distance_squared(Vector3 vec) Real
  // # Author(s): Markus Breyer
  static void mthd_distance_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(FVector::DistSquared(
        *scope_p->this_as<FVector>(),
        *scope_p->get_arg<FVector>(SSArg_1)));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@dot(Vector3 vec) Real
  // # Author(s): Markus Breyer
  static void mthd_dot(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(FVector::DotProduct(
        *scope_p->this_as<FVector>(),
        *scope_p->get_arg<FVector>(SSArg_1)));
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@length() Real
  // # Author(s): Markus Breyer
  static void mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(scope_p->this_as<FVector>()->Size());
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@length_squared() Real
  // # Author(s): Markus Breyer
  static void mthd_length_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(scope_p->this_as<FVector>()->SizeSquared());
      }
    }

  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@near?(Vector3 vector, Real epsilon_sq -> 0.0025) Boolean
  // # Author(s): Markus Breyer
  static void mthd_nearQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSBoolean::pool_new(
        FVector::DistSquared(*scope_p->this_as<FVector>(), *scope_p->get_arg<FVector>(SSArg_1))
          <= *scope_p->get_arg<SSRealType>(SSArg_2));
      }
    }

  /*
  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@angle(Vector3 vec) Real
  // # Author(s): Markus Breyer
  static void mthd_angle(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    // Do nothing if result not desired
    if (result_pp)
      {
      *result_pp = SSReal::as_instance(qAngleBetween(
        *scope_p->this_as<FVector>(),
        *scope_p->get_arg<FVector>(SSArg_1)));
      }
    }
 
  //---------------------------------------------------------------------------------------
  // # Skookum:   Vector3@normalize(Real length -> 1.0) Vector3
  // # Author(s): Markus Breyer
  static void mthd_normalize(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    SSInstance * this_p = scope_p->get_this();
    FVector *    vec_p  = this_p->as<FVector>();

    *vec_p = qNormalize(*vec_p, *scope_p->get_arg<SSRealType>(SSArg_1));

    // Return this if result desired
    if (result_pp)
      {
      this_p->reference();
      *result_pp = this_p;
      }
    }
  */

  static const SSClass::MethodInitializerFunc methods_i[] = 
    {
      { "!",                mthd_ctor },
      { "!copy",            mthd_ctor_copy },
      { "!xyz",             mthd_ctor_xyz },
      { "!xy",              mthd_ctor_xy },
      { "!!",               mthd_dtor },

      { "String",           mthd_String },

      { "assign",           mthd_op_assign },
      { "equal?",           mthd_op_equals },
      { "not_equal?",       mthd_op_not_equal },
      { "add",              mthd_op_add },
      { "add_assign",       mthd_op_add_assign },
      { "subtract",         mthd_op_subtract },
      { "subtract_assign",  mthd_op_subtract_assign },
      { "multiply",         mthd_op_multiply },
      { "multiply_assign",  mthd_op_multiply_assign },
      { "divide",           mthd_op_divide },
      { "divide_assign",    mthd_op_divide_assign },

      { "rotate_by",        mthd_rotate_by },
      { "unrotate_by",      mthd_unrotate_by },
      { "transform_by",     mthd_transform_by },
      { "untransform_by",   mthd_untransform_by },

      { "x",                mthd_x },
      { "y",                mthd_y },
      { "z",                mthd_z },
      { "xyz_set",          mthd_xyz_set },
      { "x_set",            mthd_x_set },
      { "y_set",            mthd_y_set },
      { "z_set",            mthd_z_set },
      { "zero?",            mthd_zeroQ },
      { "zero",             mthd_zero },

      { "cross",            mthd_cross },
      { "distance",         mthd_distance },
      { "distance_squared", mthd_distance_squared },
      { "dot",              mthd_dot },
      { "length",           mthd_length },
      { "length_squared",   mthd_length_squared },
      { "near?",            mthd_nearQ },
      //{ "angle",            mthd_angle },
      //{ "normalize",        mthd_normalize },
    };

  //---------------------------------------------------------------------------------------
  void register_bindings()
    {
    g_class_name = ASymbol::create_existing("Vector3");
    g_class_p = SSBrain::get_class(g_class_name);

    SS_ASSERTX(g_class_p, "Tried to register bindings for class 'Vector3' but it is unknown!");

    g_class_p->register_method_func_bulk(methods_i, A_COUNT_OF(methods_i), SSBindFlag_instance_no_rebind);
    }

  } // SSVector3
