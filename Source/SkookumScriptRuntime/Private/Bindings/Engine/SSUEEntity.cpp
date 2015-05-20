//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// Based on:
//   UObject *
// 
// Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../../SkookumScriptRuntimePrivatePCH.h"
#include "SSUEEntity.hpp"
#include "SSUEEntityClass.hpp"
#include "../SSUEBindings.hpp"


namespace SSUEEntity
  {

  //---------------------------------------------------------------------------------------
  // Convert to String
  static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {    
    if (result_pp) // Do nothing if result not desired
      {
      UObject * this_p = scope_p->this_as<UObject>();
      AString obj_name = this_p ? FStringToAString(this_p->GetName()) : "null";
      AString class_name = scope_p->get_this()->get_class()->as_code();
      AString uclass_name = this_p ? FStringToAString(this_p->GetClass()->GetName()) : "null";

      AString str(nullptr, 9u + obj_name.get_length() + class_name.get_length() + uclass_name.get_length(), 0u);
      str.append('"');
      str.append(obj_name);
      str.append("\" <", 3u);
      str.append(class_name);
      str.append("> (", 3u);
      str.append(uclass_name);
      str.append(')');
      *result_pp = SSString::as_instance(str);
      }
    }

  //---------------------------------------------------------------------------------------
  // Get name of this Entity
  static void mthd_name(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {    
    if (result_pp) // Do nothing if result not desired
      {
      UObject * this_p = scope_p->this_as<UObject>();
      AString obj_name = this_p ? FStringToAString(this_p->GetName()) : "null";
      *result_pp = SSString::as_instance(obj_name);
      }
    }

  //---------------------------------------------------------------------------------------
  // Get Unreal Engine class of this Entity
  static void mthd_entity_class(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      UObject * this_p = scope_p->this_as<UObject>();
      *result_pp = this_p ? SSUEEntityClass::as_instance(this_p->GetClass()) : SSBrain::ms_nil_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // =(Entity operand) Boolean
  static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      *result_pp = SSBoolean::pool_new(scope_p->this_as<UObject>() == scope_p->get_arg<UObject>(SSArg_1));
      }
    }

  //---------------------------------------------------------------------------------------
  // ~=(Entity operand) Boolean
  static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      *result_pp = SSBoolean::pool_new(scope_p->this_as<UObject>() != scope_p->get_arg<UObject>(SSArg_1));
      }
    }

  //---------------------------------------------------------------------------------------
  // Get Unreal Engine class of this class
  static void mthdc_static_class(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      // Determine class
      SSClass * class_p = &((SSMetaClass *)scope_p->get_topmost_scope())->get_class_info();
      UClass ** uclass_pp = SSUE::g_class_map_s2u.Find(class_p);
      SS_ASSERTX(uclass_pp, a_cstr_format("The UE4 equivalent of class type '%s' is not known to SkookumScript.", class_p->get_name_cstr_dbg()));
      *result_pp = uclass_pp ? SSUEEntityClass::as_instance(*uclass_pp) : SSBrain::ms_nil_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // Entity@load(String name) ThisClass_
  static void mthdc_load(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      // Determine class of object to load
      SSClass * class_p = &((SSMetaClass *)scope_p->get_topmost_scope())->get_class_info();
      UClass ** uclass_pp = SSUE::g_class_map_s2u.Find(class_p);
      SS_ASSERTX(uclass_pp, a_cstr_format("Cannot load entity '%s' as the UE4 equivalent of class type '%s' is not known to SkookumScript.", scope_p->get_arg<AString>(SSArg_1)->as_cstr(), class_p->get_name_cstr_dbg()));

      // Load object
      UObject * obj_p = nullptr;
      if (uclass_pp)
        {
        obj_p = StaticLoadObject(*uclass_pp, SSUE::get_world(), *AStringToFString(*scope_p->get_arg<AString>(SSArg_1)));
        }

      *result_pp = obj_p ? SSUE::get_object_instance(obj_p, *uclass_pp, class_p) : SSBrain::ms_nil_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // Entity@default() ThisClass_
  static void mthdc_default(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      // Determine class of object to get
      SSClass * class_p = &((SSMetaClass *)scope_p->get_topmost_scope())->get_class_info();
      UClass ** uclass_pp = SSUE::g_class_map_s2u.Find(class_p);
      SS_ASSERTX(uclass_pp, a_cstr_format("Cannot get default instance of class '%s' as the UE4 equivalent of this class is not known to SkookumScript.", class_p->get_name_cstr_dbg()));

      // Get default object
      UObject * obj_p = nullptr;
      if (uclass_pp)
        {
        obj_p = GetMutableDefault<UObject>(*uclass_pp);
        }

      *result_pp = obj_p ? SSUE::get_object_instance(obj_p, *uclass_pp, class_p) : SSBrain::ms_nil_p;
      }
    }

  //---------------------------------------------------------------------------------------
  // Entity@null() ThisClass_
  static void mthdc_null(SSInvokedMethod * scope_p, SSInstance ** result_pp)
    {
    if (result_pp) // Do nothing if result not desired
      {
      // Determine class of object to get
      SSClass * class_p = &((SSMetaClass *)scope_p->get_topmost_scope())->get_class_info();

      // Get null object of that class
      *result_pp = SSInstance::pool_new(class_p, static_cast<UObject * const &>(nullptr));
      }
    }

  //---------------------------------------------------------------------------------------
  // Entity@()
  static bool coro_wait_until_destroyed(SSInvokedCoroutine * scope_p)
    {
    UObject * this_p = scope_p->this_as<UObject>(); // We store the UObject as a weak pointer so it becomes null when the object is destroyed
    return !this_p || !this_p->IsValidLowLevel();
    }

  static const SSClass::MethodInitializerFunc methods_i2[] =
    {
      { "String", mthd_String },
      { "name", mthd_name },
      { "entity_class", mthd_entity_class },
      { "equal?", mthd_op_equals },
      { "not_equal?", mthd_op_not_equal },
    };

  static const SSClass::MethodInitializerFunc methods_c2[] =
    {
      { "static_class", mthdc_static_class },
      { "load", mthdc_load },
      { "default", mthdc_default },
      { "null", mthdc_null },
    };

  void register_bindings2()
    {
    g_class_p->register_method_func_bulk(methods_i2, A_COUNT_OF(methods_i2), SSBindFlag_instance_no_rebind);
    g_class_p->register_method_func_bulk(methods_c2, A_COUNT_OF(methods_c2), SSBindFlag_class_no_rebind);
    g_class_p->register_coroutine_func("_wait_until_destroyed", coro_wait_until_destroyed, SSBindFlag_instance_no_rebind);
    }

  } // SSUEEntity
