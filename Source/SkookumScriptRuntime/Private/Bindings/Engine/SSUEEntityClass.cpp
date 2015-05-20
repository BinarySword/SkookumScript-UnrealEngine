//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   UClass *
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSUEEntityClass.hpp"
#include "../SSUEBindings.hpp"


namespace SSUEEntityClass
  {

  //=======================================================================================
  // Methods
  //=======================================================================================

  //---------------------------------------------------------------------------------------
  // # Skookum:   UClass@String() String
  // # Author(s): Markus Breyer
  static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      UClass * uclass_p = scope_p->this_as<UClass>();
      AString uclass_name = FStringToAString(uclass_p->GetName());

      AString str(nullptr, 3u + uclass_name.get_length(), 0u);
      str.append('(');
      str.append(uclass_name);
      str.append(')');
      *result_pp = SSString::as_instance(str);
      }
    }

  static const SSClass::MethodInitializerFunc methods_i2[] =
    {
      { "String", mthd_String },
    };

  //---------------------------------------------------------------------------------------
  void register_bindings2()
    {
    g_class_p->register_method_func_bulk(methods_i2, A_COUNT_OF(methods_i2), SSBindFlag_instance_no_rebind);
    }

  } // SSUEEntityClass
