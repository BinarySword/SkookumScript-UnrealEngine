//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FVector4 - Engine\Source\Runtime\Core\Public\Math\Vector4.h
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSVector4.hpp"


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSVector4::ms_class_p = nullptr;


//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied vector
// 
// # Author(s): Markus Breyer
SSInstance * SSVector4::as_instance(const FVector4 & vec)
  {
  #ifdef SS_VECTOR4_STORE_DIRECT

    // Store FVector4 directly in SSInstance
    return SSInstance::pool_new(ms_class_p, vec);

  #else

    // Allocate an FVector4 and store a pointer to it in SSInstance
    return SSInstance::pool_new(ms_class_p, new ("Skookum.FVector4") FVector4(vec));

  #endif
  }

//---------------------------------------------------------------------------------------
void SSVector4::register_bindings()
  {
  ms_class_p = SSBrain::get_class("Vector4");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'Vector4' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor, SSVector4::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy, SSVector4::mthd_ctor_copy);
  ms_class_p->register_method_func("!xyzw",            SSVector4::mthd_ctor_xyzw);
  ms_class_p->register_method_func("!xyz",             SSVector4::mthd_ctor_xyz);
  ms_class_p->register_method_func("!xy",              SSVector4::mthd_ctor_xy);
  ms_class_p->register_method_func(ASymbolX_dtor,      SSVector4::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,     SSVector4::mthd_String);

  ms_class_p->register_method_func(ASymbol_assign,           SSVector4::mthd_op_assign);
  ms_class_p->register_method_func(ASymbolX_equalQ,          SSVector4::mthd_op_equals);
  ms_class_p->register_method_func(ASymbolX_not_equalQ,      SSVector4::mthd_op_not_equal);
  ms_class_p->register_method_func(ASymbol_add,              SSVector4::mthd_op_add);
  ms_class_p->register_method_func(ASymbol_add_assign,       SSVector4::mthd_op_add_assign);
  ms_class_p->register_method_func(ASymbol_subtract,         SSVector4::mthd_op_subtract);
  ms_class_p->register_method_func(ASymbol_subtract_assign,  SSVector4::mthd_op_subtract_assign);
  ms_class_p->register_method_func(ASymbol_multiply,         SSVector4::mthd_op_multiply);
  ms_class_p->register_method_func(ASymbol_multiply_assign,  SSVector4::mthd_op_multiply_assign);
  ms_class_p->register_method_func(ASymbol_divide,           SSVector4::mthd_op_divide);
  ms_class_p->register_method_func(ASymbol_divide_assign,    SSVector4::mthd_op_divide_assign);

  ms_class_p->register_method_func("x",                SSVector4::mthd_x);
  ms_class_p->register_method_func("y",                SSVector4::mthd_y);
  ms_class_p->register_method_func("z",                SSVector4::mthd_z);
  ms_class_p->register_method_func("w",                SSVector4::mthd_w);
  ms_class_p->register_method_func("xyzw_set",         SSVector4::mthd_xyzw_set);
  ms_class_p->register_method_func("x_set",            SSVector4::mthd_x_set);
  ms_class_p->register_method_func("y_set",            SSVector4::mthd_y_set);
  ms_class_p->register_method_func("z_set",            SSVector4::mthd_z_set);
  ms_class_p->register_method_func("w_set",            SSVector4::mthd_w_set);
  ms_class_p->register_method_func("zero?",            SSVector4::mthd_zeroQ);
  ms_class_p->register_method_func("zero",             SSVector4::mthd_zero);

  //ms_vector_class_p->register_method_func("distance",         SSVector4::mthd_distance);
  //ms_vector_class_p->register_method_func("distance_squared", SSVector4::mthd_distance_squared);
  ms_class_p->register_method_func("dot",              SSVector4::mthd_dot);
  //ms_vector_class_p->register_method_func("length",           SSVector4::mthd_length);
  //ms_vector_class_p->register_method_func("length_squared",   SSVector4::mthd_length_squared);
  //ms_vector_class_p->register_method_func(ASymbolX_nearQ,     SSVector4::mthd_nearQ);

  //ms_vector_class_p->register_method_func("angle",            SSVector4::mthd_angle);
  //ms_vector_class_p->register_method_func("normalize",        SSVector4::mthd_normalize);
  }


//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@!() Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_VECTOR4_STORE_DIRECT
    scope_p->this_set(FVector4(0.0f, 0.0f, 0.0f, 0.0f));
  #else
    scope_p->this_set(new ("Skookum.FVector4") FVector4(0.0f, 0.0f, 0.0f, 0.0f));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@!copy(Vector4 vec) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_VECTOR4_STORE_DIRECT
    scope_p->this_set(*scope_p->get_arg<FVector4>(SSArg_1));
  #else
    scope_p->this_set(new ("Skookum.FVector4") FVector4(*scope_p->get_arg<FVector4>(SSArg_1)));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@!xyzw(Real x, Real y, Real z, Real w) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_ctor_xyzw(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_VECTOR4_STORE_DIRECT
  scope_p->this_as<FVector4>()->Set(
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_2),
    *scope_p->get_arg<SSRealType>(SSArg_3),
    *scope_p->get_arg<SSRealType>(SSArg_4));
#else
  scope_p->set_this(new ("Skookum.FVector4") FVector4(
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_2),
    *scope_p->get_arg<SSRealType>(SSArg_3),
    *scope_p->get_arg<SSRealType>(SSArg_4)));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@!xyz(Real x, Real y, Real z) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_ctor_xyz(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_VECTOR4_STORE_DIRECT
    scope_p->this_as<FVector4>()->Set(
      *scope_p->get_arg<SSRealType>(SSArg_1),
      *scope_p->get_arg<SSRealType>(SSArg_2),
      *scope_p->get_arg<SSRealType>(SSArg_3),
      0.0f);
  #else
    scope_p->set_this(new ("Skookum.FVector4") FVector4(
      *scope_p->get_arg<SSRealType>(SSArg_1),
      *scope_p->get_arg<SSRealType>(SSArg_2),
      *scope_p->get_arg<SSRealType>(SSArg_3),
      0.0f));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@!xy(Real x, Real y) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_ctor_xy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_VECTOR4_STORE_DIRECT
    scope_p->this_as<FVector4>()->Set(
      *scope_p->get_arg<SSRealType>(SSArg_1),
      *scope_p->get_arg<SSRealType>(SSArg_2),
      0.0f, 0.0f);
  #else
    scope_p->set_this<Fvector>(new ("Skookum.FVector4") FVector4(
      *scope_p->get_arg<SSRealType>(SSArg_1),
      *scope_p->get_arg<SSRealType>(SSArg_2),
      0.0f, 0.0f));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@!!()
// # Author(s): Markus Breyer
void SSVector4::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  #ifdef SS_VECTOR4_STORE_INDIRECT
    delete scope_p->this_as<FVector4>();
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@String() String
// # Author(s): Markus Breyer
void SSVector4::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector4 * vector_p = scope_p->this_as<FVector4>();
    AString   str(128u, "(%g, %g, %g, %g)", double(vector_p->X), double(vector_p->Y), double(vector_p->Z), double(vector_p->W));

    *result_pp = SSString::as_instance(str);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@:=(Vector4 vec) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*scope_p->get_arg<FVector4>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@=(Vector4 vec) Boolean
// # Author(s): Markus Breyer
void SSVector4::mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(*scope_p->this_as<FVector4>() == *scope_p->get_arg<FVector4>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@~=(Vector4 vec) Boolean
// # Author(s): Markus Breyer
void SSVector4::mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(*scope_p->this_as<FVector4>() != *scope_p->get_arg<FVector4>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@+(Vector4 vec) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = as_instance(*scope_p->this_as<FVector4>() + *scope_p->get_arg<FVector4>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@+=(Vector4 vec) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FVector4>() += *scope_p->get_arg<FVector4>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@-(Vector4 vec) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_subtract(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = as_instance(*scope_p->this_as<FVector4>() - *scope_p->get_arg<FVector4>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@-=(Vector4 vec) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_subtract_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*this_p->as<FVector4>() - *scope_p->get_arg<FVector4>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@*(Real num) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_multiply(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FVector4 vector(*scope_p->this_as<FVector4>());

    vector *= *scope_p->get_arg<SSRealType>(SSArg_1);

    *result_pp = as_instance(vector);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@*=(Real num) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_multiply_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FVector4>() *= *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@/(Real num) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_divide(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = as_instance(*scope_p->this_as<FVector4>() / *scope_p->get_arg<SSRealType>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@/=(Real num) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_op_divide_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*this_p->as<FVector4>() / *scope_p->get_arg<SSRealType>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@x() Real
// # Author(s): Markus Breyer
void SSVector4::mthd_x(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector4>()->X);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@y() Real
// # Author(s): Markus Breyer
void SSVector4::mthd_y(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector4>()->Y);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@z() Real
// # Author(s): Markus Breyer
void SSVector4::mthd_z(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector4>()->Z);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@w() Real
// # Author(s): Markus Breyer
void SSVector4::mthd_w(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector4>()->W);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@xyzw_set(Real x, Real y, Real z, Real w) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_xyzw_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FVector4 *    vec_p  = this_p->as<FVector4>();

  vec_p->X = *scope_p->get_arg<SSRealType>(SSArg_1);
  vec_p->Y = *scope_p->get_arg<SSRealType>(SSArg_2);
  vec_p->Z = *scope_p->get_arg<SSRealType>(SSArg_3);
  vec_p->W = *scope_p->get_arg<SSRealType>(SSArg_4);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@x_set(Real x) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_x_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FVector4>()->X = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@y_set(Real y) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_y_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FVector4>()->Y = *scope_p->get_arg<SSRealType>(SSArg_1);


  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@z_set(Real z) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_z_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FVector4>()->Z = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@w_set(Real w) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_w_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FVector4>()->W = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@zero() Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_zero(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FVector4 *    vec_p  = this_p->as<FVector4>();

  vec_p->X = 0.0f;
  vec_p->Y = 0.0f;
  vec_p->Z = 0.0f;

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@zero?() Boolean
// # Author(s): Markus Breyer
void SSVector4::mthd_zeroQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FVector4 & vector = *scope_p->this_as<FVector4>();
    *result_pp = SSBoolean::pool_new(vector.X == 0.0f && vector.Y == 0.0f && vector.Z == 0.0f && vector.W == 0.0f);
    }
  }

/*
//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@distance(Vector4 vec) Real
// # Author(s): Markus Breyer
void SSVector4::mthd_distance(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(FVector4::Dist(
      *scope_p->this_as<FVector4>(),
      *scope_p->get_arg<FVector4>(SSArg_1)));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@distance_squared(Vector4 vec) Real
// # Author(s): Markus Breyer
void SSVector4::mthd_distance_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(FVector4::DistSquared(
      *scope_p->this_as<FVector4>(),
      *scope_p->get_arg<FVector4>(SSArg_1)));
    }
  }
*/

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@dot(Vector4 vec) Real
// # Author(s): Markus Breyer
void SSVector4::mthd_dot(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(Dot4(
      *scope_p->this_as<FVector4>(),
      *scope_p->get_arg<FVector4>(SSArg_1)));
    }
  }

/*
//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@length() Real
// # Author(s): Markus Breyer
void SSVector4::mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector4>()->Size());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@length_squared() Real
// # Author(s): Markus Breyer
void SSVector4::mthd_length_squared(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FVector4>()->SizeSquared());
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@near?(Vector4 vector, Real epsilon_sq -> 0.0025) Boolean
// # Author(s): Markus Breyer
void SSVector4::mthd_nearQ(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(
      FVector4::DistSquared(*scope_p->this_as<FVector4>(), *scope_p->get_arg<FVector4>(SSArg_1))
        <= *scope_p->get_arg<SSRealType>(SSArg_2));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@angle(Vector4 vec) Real
// # Author(s): Markus Breyer
void SSVector4::mthd_angle(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(qAngleBetween(
      *scope_p->this_as<FVector4>(),
      *scope_p->get_arg<FVector4>(SSArg_1)));
    }
  }
 
//---------------------------------------------------------------------------------------
// # Skookum:   Vector4@normalize(Real length -> 1.0) Vector4
// # Author(s): Markus Breyer
void SSVector4::mthd_normalize(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FVector4 *    vec_p  = this_p->as<FVector4>();

  *vec_p = qNormalize(*vec_p, *scope_p->get_arg<SSRealType>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }
*/
