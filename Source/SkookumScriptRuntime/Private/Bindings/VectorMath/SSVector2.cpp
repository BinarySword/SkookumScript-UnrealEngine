//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FVector2D - Engine\Source\Runtime\Core\Public\Math\Vector2.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSVector2.hpp"


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSVector2::ms_class_p = nullptr;


//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied vector
// 
// # Author(s): Markus Breyer
SSInstance * SSVector2::as_instance(const FVector2D & vec)
  {
  // Store FVector2D directly in SSInstance
  return SSInstance::pool_new(ms_class_p, vec);
  }

//---------------------------------------------------------------------------------------
void SSVector2::register_bindings()
  {
  ms_class_p = SSBrain::get_class("Vector2");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'Vector2' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor,      SSVector2::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy, SSVector2::mthd_ctor_copy);
  ms_class_p->register_method_func("!xy",              SSVector2::mthd_ctor_xy);
  ms_class_p->register_method_func(ASymbolX_dtor,      SSVector2::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,     SSVector2::mthd_String);

  ms_class_p->register_method_func(ASymbol_assign,           SSVector2::mthd_op_assign);
  ms_class_p->register_method_func(ASymbolX_equalQ,          SSVector2::mthd_op_equals);
  ms_class_p->register_method_func(ASymbolX_not_equalQ,      SSVector2::mthd_op_not_equal);
  ms_class_p->register_method_func(ASymbol_add,              SSVector2::mthd_op_add);
  ms_class_p->register_method_func(ASymbol_add_assign,       SSVector2::mthd_op_add_assign);
  ms_class_p->register_method_func(ASymbol_subtract,         SSVector2::mthd_op_subtract);
  ms_class_p->register_method_func(ASymbol_subtract_assign,  SSVector2::mthd_op_subtract_assign);
  ms_class_p->register_method_func(ASymbol_multiply,         SSVector2::mthd_op_multiply);
  ms_class_p->register_method_func(ASymbol_multiply_assign,  SSVector2::mthd_op_multiply_assign);
  ms_class_p->register_method_func(ASymbol_divide,           SSVector2::mthd_op_divide);
  ms_class_p->register_method_func(ASymbol_divide_assign,    SSVector2::mthd_op_divide_assign);

  ms_class_p->register_method_func("x",                SSVector2::mthd_x);
  ms_class_p->register_method_func("y",                SSVector2::mthd_y);
  ms_class_p->register_method_func("xy_set",           SSVector2::mthd_xy_set);
  ms_class_p->register_method_func("x_set",            SSVector2::mthd_x_set);
  ms_class_p->register_method_func("y_set",            SSVector2::mthd_y_set);
  ms_class_p->register_method_func("zero?",            SSVector2::mthd_zeroQ);
  ms_class_p->register_method_func("zero",             SSVector2::mthd_zero);

  ms_class_p->register_method_func("cross",            SSVector2::mthd_cross);
  ms_class_p->register_method_func("distance",         SSVector2::mthd_distance);
  ms_class_p->register_method_func("distance_squared", SSVector2::mthd_distance_squared);
  ms_class_p->register_method_func("dot",              SSVector2::mthd_dot);
  ms_class_p->register_method_func("length",           SSVector2::mthd_length);
  ms_class_p->register_method_func("length_squared",   SSVector2::mthd_length_squared);
  ms_class_p->register_method_func(ASymbolX_nearQ,     SSVector2::mthd_nearQ);

  //ms_vector_class_p->register_method_func("angle",            SSVector2::mthd_angle);
  //ms_vector_class_p->register_method_func("normalize",        SSVector2::mthd_normalize);
  }


//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@!() Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  scope_p->this_set(FVector2D::ZeroVector);
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@!copy(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  scope_p->this_set(*scope_p->get_arg<FVector2D>(SSArg_1));
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@!xy(Real x, Real y) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_ctor_xy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  scope_p->this_as<FVector2D>()->Set(
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_2));
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@!!()
// # Author(s): Markus Breyer
void SSVector2::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@String() String
// # Author(s): Markus Breyer
void SSVector2::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector2D * vector_p = scope_p->this_as<FVector2D>();
    AString   str(128u, "(%g, %g)", double(vector_p->X), double(vector_p->Y));

    *result_pp = SSString::as_instance(str);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@:=(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*scope_p->get_arg<FVector2D>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@=(Vector2 vec) Boolean
// # Author(s): Markus Breyer
void SSVector2::mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(*scope_p->this_as<FVector2D>() == *scope_p->get_arg<FVector2D>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@~=(Vector2 vec) Boolean
// # Author(s): Markus Breyer
void SSVector2::mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(*scope_p->this_as<FVector2D>() != *scope_p->get_arg<FVector2D>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@+(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector2D vector(*scope_p->this_as<FVector2D>());

    vector += *scope_p->get_arg<FVector2D>(SSArg_1);

    *result_pp = as_instance(vector);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@+=(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FVector2D>() += *scope_p->get_arg<FVector2D>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@-(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_subtract(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector2D vector(*scope_p->this_as<FVector2D>());

    vector -= *scope_p->get_arg<FVector2D>(SSArg_1);

    *result_pp = as_instance(vector);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@-=(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_subtract_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FVector2D>() -= *scope_p->get_arg<FVector2D>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@*(Real num) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_multiply(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector2D vector(*scope_p->this_as<FVector2D>());

    vector *= *scope_p->get_arg<SSRealType>(SSArg_1);

    *result_pp = as_instance(vector);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@*=(Real num) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_multiply_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FVector2D>() *= *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@/(Real num) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_divide(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector2D vector(*scope_p->this_as<FVector2D>());

    vector /= *scope_p->get_arg<SSRealType>(SSArg_1);

    *result_pp = as_instance(vector);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@/=(Real num) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_op_divide_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FVector2D>() /= *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@x() Real
// # Author(s): Markus Breyer
void SSVector2::mthd_x(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector2D>()->X);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@y() Real
// # Author(s): Markus Breyer
void SSVector2::mthd_y(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector2D>()->Y);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@xy_set(Real x, Real y) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_xy_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FVector2D *   vec_p = this_p->as<FVector2D>();

  vec_p->X = *scope_p->get_arg<SSRealType>(SSArg_1);
  vec_p->Y = *scope_p->get_arg<SSRealType>(SSArg_2);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@x_set(Real x) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_x_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FVector2D>()->X = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@y_set(Real y) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_y_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FVector2D>()->Y = *scope_p->get_arg<SSRealType>(SSArg_1);


  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@zero() Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FVector2D *  vec_p  = this_p->as<FVector2D>();

  vec_p->X = 0.0f;
  vec_p->Y = 0.0f;

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@zero?() Boolean
// # Author(s): Markus Breyer
void SSVector2::mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(scope_p->this_as<FVector2D>()->IsZero());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@cross(Vector2 vec) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_cross(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(FVector2D::CrossProduct(
      *scope_p->this_as<FVector2D>(),
      *scope_p->get_arg<FVector2D>(SSArg_1)));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@distance(Vector2 vec) Real
// # Author(s): Markus Breyer
void SSVector2::mthd_distance(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(FVector2D::Distance(
      *scope_p->this_as<FVector2D>(),
      *scope_p->get_arg<FVector2D>(SSArg_1)));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@distance_squared(Vector2 vec) Real
// # Author(s): Markus Breyer
void SSVector2::mthd_distance_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(FVector2D::DistSquared(
      *scope_p->this_as<FVector2D>(),
      *scope_p->get_arg<FVector2D>(SSArg_1)));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@dot(Vector2 vec) Real
// # Author(s): Markus Breyer
void SSVector2::mthd_dot(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(FVector2D::DotProduct(
      *scope_p->this_as<FVector2D>(),
      *scope_p->get_arg<FVector2D>(SSArg_1)));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@length() Real
// # Author(s): Markus Breyer
void SSVector2::mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector2D>()->Size());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@length_squared() Real
// # Author(s): Markus Breyer
void SSVector2::mthd_length_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector2D>()->SizeSquared());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@near?(Vector2 vector, Real epsilon_sq -> 0.0025) Boolean
// # Author(s): Markus Breyer
void SSVector2::mthd_nearQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(
      FVector2D::DistSquared(*scope_p->this_as<FVector2D>(), *scope_p->get_arg<FVector2D>(SSArg_1))
        <= *scope_p->get_arg<SSRealType>(SSArg_2));
    }
  }

/*
//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@angle(Vector2 vec) Real
// # Author(s): Markus Breyer
void SSVector2::mthd_angle(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(qAngleBetween(
      *scope_p->this_as<FVector2D>(),
      *scope_p->get_arg<FVector2D>(SSArg_1)));
    }
  }
 
//---------------------------------------------------------------------------------------
// # Skookum:   Vector2@normalize(Real length -> 1.0) Vector2
// # Author(s): Markus Breyer
void SSVector2::mthd_normalize(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FVector2D *    vec_p  = this_p->as<FVector2D>();

  *vec_p = qNormalize(*vec_p, *scope_p->get_arg<SSRealType>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }
*/
