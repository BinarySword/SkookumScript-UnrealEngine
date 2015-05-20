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


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSColor.hpp"


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSColor::ms_class_p = nullptr;


//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied color
// 
// # Author(s): Markus Breyer
SSInstance * SSColor::as_instance(const FLinearColor & col)
  {
  #ifdef SS_COLOR_STORE_DIRECT

    // Store FLinearColor directly in SSInstance
    return SSInstance::pool_new(ms_class_p, col);

  #else

    // Allocate an FLinearColor and store a pointer to it in SSInstance
    return SSInstance::pool_new(ms_class_p, new ("Skookum.FLinearColor") FLinearColor(col));

  #endif
  }

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied color
// 
// # Author(s): Markus Breyer
SSInstance * SSColor::as_instance(const FColor & col)
  {
  return as_instance(FLinearColor(col));
  }

//---------------------------------------------------------------------------------------
void SSColor::register_bindings()
  {
  ms_class_p = SSBrain::get_class("Color");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'Color' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor,      SSColor::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy, SSColor::mthd_ctor_copy);
  ms_class_p->register_method_func("!rgba",            SSColor::mthd_ctor_rgba);
  ms_class_p->register_method_func("!rgb",             SSColor::mthd_ctor_rgb);
  ms_class_p->register_method_func(ASymbolX_dtor,      SSColor::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,     SSColor::mthd_String);

  ms_class_p->register_method_func(ASymbol_assign,           SSColor::mthd_op_assign);
  ms_class_p->register_method_func(ASymbolX_equalQ,          SSColor::mthd_op_equals);
  ms_class_p->register_method_func(ASymbolX_not_equalQ,      SSColor::mthd_op_not_equal);
  ms_class_p->register_method_func(ASymbol_add,              SSColor::mthd_op_add);
  ms_class_p->register_method_func(ASymbol_add_assign,       SSColor::mthd_op_add_assign);
  ms_class_p->register_method_func(ASymbol_subtract,         SSColor::mthd_op_subtract);
  ms_class_p->register_method_func(ASymbol_subtract_assign,  SSColor::mthd_op_subtract_assign);
  ms_class_p->register_method_func(ASymbol_multiply,         SSColor::mthd_op_multiply);
  ms_class_p->register_method_func(ASymbol_multiply_assign,  SSColor::mthd_op_multiply_assign);
  ms_class_p->register_method_func(ASymbol_divide,           SSColor::mthd_op_divide);
  ms_class_p->register_method_func(ASymbol_divide_assign,    SSColor::mthd_op_divide_assign);

  ms_class_p->register_method_func("r",                SSColor::mthd_r);
  ms_class_p->register_method_func("g",                SSColor::mthd_g);
  ms_class_p->register_method_func("b",                SSColor::mthd_b);
  ms_class_p->register_method_func("a",                SSColor::mthd_a);
  ms_class_p->register_method_func("rgba_set",         SSColor::mthd_rgba_set);
  ms_class_p->register_method_func("r_set",            SSColor::mthd_r_set);
  ms_class_p->register_method_func("g_set",            SSColor::mthd_g_set);
  ms_class_p->register_method_func("b_set",            SSColor::mthd_b_set);
  ms_class_p->register_method_func("a_set",            SSColor::mthd_a_set);

  }


//---------------------------------------------------------------------------------------
// # Skookum:   Color@!() Color
// # Author(s): Markus Breyer
void SSColor::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_COLOR_STORE_DIRECT
    scope_p->this_set(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
  #else
    scope_p->this_set(new ("Skookum.FLinearColor") FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@!copy(Color col) Color
// # Author(s): Markus Breyer
void SSColor::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_COLOR_STORE_DIRECT
    scope_p->this_set(*scope_p->get_arg<FLinearColor>(SSArg_1));
  #else
    scope_p->this_set(new ("Skookum.FLinearColor") FLinearColor(*scope_p->get_arg<FLinearColor>(SSArg_1)));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@!rgba(Real r, Real g, Real b, Real a) Color
// # Author(s): Markus Breyer
void SSColor::mthd_ctor_rgba(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
#ifdef SS_COLOR_STORE_DIRECT
  scope_p->this_set(FLinearColor(
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_2),
    *scope_p->get_arg<SSRealType>(SSArg_3),
    *scope_p->get_arg<SSRealType>(SSArg_4)));
#else
  scope_p->this_set(new ("Skookum.FLinearColor") FLinearColor(
    *scope_p->get_arg<SSRealType>(SSArg_1),
    *scope_p->get_arg<SSRealType>(SSArg_2),
    *scope_p->get_arg<SSRealType>(SSArg_3),
    *scope_p->get_arg<SSRealType>(SSArg_4)));
#endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@!rgb(Real r, Real g, Real b) Color
// # Author(s): Markus Breyer
void SSColor::mthd_ctor_rgb(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  #ifdef SS_COLOR_STORE_DIRECT
    scope_p->this_set(FLinearColor(
      *scope_p->get_arg<SSRealType>(SSArg_1),
      *scope_p->get_arg<SSRealType>(SSArg_2),
      *scope_p->get_arg<SSRealType>(SSArg_3),
      1.0f));
  #else
    scope_p->this_set(new ("Skookum.FLinearColor") FLinearColor(
      *scope_p->get_arg<SSRealType>(SSArg_1),
      *scope_p->get_arg<SSRealType>(SSArg_2),
      *scope_p->get_arg<SSRealType>(SSArg_3),
      1.0f));
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@!!()
// # Author(s): Markus Breyer
void SSColor::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  #ifdef SS_COLOR_STORE_INDIRECT
    delete scope_p->this_as<FLinearColor>();
  #endif
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@String() String
// # Author(s): Markus Breyer
void SSColor::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FLinearColor * vector_p = scope_p->this_as<FLinearColor>();
    AString   str(128u, "(R=%g, G=%g, B=%g, A=%g)", double(vector_p->R), double(vector_p->G), double(vector_p->B), double(vector_p->A));

    *result_pp = SSString::as_instance(str);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@:=(Color col) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*scope_p->get_arg<FLinearColor>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@=(Color col) Boolean
// # Author(s): Markus Breyer
void SSColor::mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(*scope_p->this_as<FLinearColor>() == *scope_p->get_arg<FLinearColor>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@~=(Color col) Boolean
// # Author(s): Markus Breyer
void SSColor::mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSBoolean::pool_new(*scope_p->this_as<FLinearColor>() != *scope_p->get_arg<FLinearColor>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@+(Color col) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = as_instance(*scope_p->this_as<FLinearColor>() + *scope_p->get_arg<FLinearColor>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@+=(Color col) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FLinearColor>() += *scope_p->get_arg<FLinearColor>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@-(Color col) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_subtract(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = as_instance(*scope_p->this_as<FLinearColor>() - *scope_p->get_arg<FLinearColor>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@-=(Color col) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_subtract_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FLinearColor>() -= *scope_p->get_arg<FLinearColor>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@*(Real num) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_multiply(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    FLinearColor vector(*scope_p->this_as<FLinearColor>());

    vector *= *scope_p->get_arg<SSRealType>(SSArg_1);

    *result_pp = as_instance(vector);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@*=(Real num) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_multiply_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FLinearColor>() *= *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@/(Real num) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_divide(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = as_instance(*scope_p->this_as<FLinearColor>() / *scope_p->get_arg<SSRealType>(SSArg_1));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@/=(Real num) Color
// # Author(s): Markus Breyer
void SSColor::mthd_op_divide_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  *this_p->as<FLinearColor>() /= *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@r() Real
// # Author(s): Markus Breyer
void SSColor::mthd_r(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FLinearColor>()->R);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@g() Real
// # Author(s): Markus Breyer
void SSColor::mthd_g(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FLinearColor>()->G);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@b() Real
// # Author(s): Markus Breyer
void SSColor::mthd_b(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FLinearColor>()->B);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@a() Real
// # Author(s): Markus Breyer
void SSColor::mthd_a(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    *result_pp = SSReal::as_instance(scope_p->this_as<FLinearColor>()->A);
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@rgba_set(Real r, Real g, Real b, Real a) Color
// # Author(s): Markus Breyer
void SSColor::mthd_rgba_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();
  FLinearColor *    vec_p  = this_p->as<FLinearColor>();

  vec_p->R = *scope_p->get_arg<SSRealType>(SSArg_1);
  vec_p->G = *scope_p->get_arg<SSRealType>(SSArg_2);
  vec_p->B = *scope_p->get_arg<SSRealType>(SSArg_3);
  vec_p->A = *scope_p->get_arg<SSRealType>(SSArg_4);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@r_set(Real r) Color
// # Author(s): Markus Breyer
void SSColor::mthd_r_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FLinearColor>()->R = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@g_set(Real g) Color
// # Author(s): Markus Breyer
void SSColor::mthd_g_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FLinearColor>()->G = *scope_p->get_arg<SSRealType>(SSArg_1);


  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@b_set(Real b) Color
// # Author(s): Markus Breyer
void SSColor::mthd_b_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FLinearColor>()->B = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Color@a_set(Real a) Color
// # Author(s): Markus Breyer
void SSColor::mthd_a_set(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->as<FLinearColor>()->A = *scope_p->get_arg<SSRealType>(SSArg_1);

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }
