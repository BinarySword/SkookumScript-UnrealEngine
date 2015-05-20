//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   FName
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSUEName.hpp"


//=======================================================================================
// Class Data
//=======================================================================================

SSClass * SSUEName::ms_class_p = nullptr;


//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------
// Returns a script class instance wrapper for the supplied name
// 
// # Author(s): Markus Breyer
SSInstance * SSUEName::as_instance(const FName & name)
  {
  // Store FName directly in SSInstance
  return SSInstance::pool_new(ms_class_p, name);
  }

//---------------------------------------------------------------------------------------
void SSUEName::register_bindings()
  {
  ms_class_p = SSBrain::get_class("Name");

  SS_ASSERTX(ms_class_p, "Tried to register bindings for class 'Name' but it is unknown!");

  ms_class_p->register_method_func(ASymbolX_ctor,      SSUEName::mthd_ctor);
  ms_class_p->register_method_func(ASymbolX_ctor_copy, SSUEName::mthd_ctor_copy);
  ms_class_p->register_method_func(ASymbolX_dtor,      SSUEName::mthd_dtor);

  ms_class_p->register_method_func(ASymbol_String,     SSUEName::mthd_String);

  ms_class_p->register_method_func(ASymbol_assign,     SSUEName::mthd_op_assign);


  // Hook up extra String methods

  SSClass * string_class_p = SSBrain::get_class("String");

  string_class_p->register_method_func("Name",          SSUEName::mthd_String_to_Name);
  
  }


//---------------------------------------------------------------------------------------
// # Skookum:   Name@!() Name
// # Author(s): Markus Breyer
void SSUEName::mthd_ctor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  const AString & str = *scope_p->get_arg<AString>(SSArg_1);
  scope_p->this_set(FName(str.as_cstr()));
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Name@!copy(Name name) Name
// # Author(s): Markus Breyer
void SSUEName::mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Results are ignored for constructors
  scope_p->this_set(*scope_p->get_arg<FName>(SSArg_1));
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Name@!!()
// # Author(s): Markus Breyer
void SSUEName::mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Name@String() String
// # Author(s): Markus Breyer
void SSUEName::mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const FName & name = *scope_p->this_as<FName>();
    *result_pp = SSString::as_instance(AString(name.GetPlainANSIString()));
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   Name@:=(Name name) Name
// # Author(s): Markus Breyer
void SSUEName::mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  SSInstance * this_p = scope_p->get_this();

  this_p->set(*scope_p->get_arg<FName>(SSArg_1));

  // Return this if result desired
  if (result_pp)
    {
    this_p->reference();
    *result_pp = this_p;
    }
  }

//---------------------------------------------------------------------------------------
// # Skookum:   String@Name() Name
// # Author(s): Markus Breyer
void SSUEName::mthd_String_to_Name(SSInvokedMethod * scope_p, SSInstance ** result_pp)
  {
  // Do nothing if result not desired
  if (result_pp)
    {
    const AString & str = *scope_p->this_as<AString>();
    *result_pp = SSUEName::as_instance(FName(str.as_cstr()));
    }
  }

