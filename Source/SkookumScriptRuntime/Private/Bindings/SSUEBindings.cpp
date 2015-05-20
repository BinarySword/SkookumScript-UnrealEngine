//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// # Author(s):  Conan Reis
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "../SkookumScriptRuntimePrivatePCH.h"
#include "../Classes/SkookumScriptComponent.h"
#include "SSUEBindings.hpp"

#include "VectorMath/SSVector2.hpp"
#include "VectorMath/SSVector3.hpp"
#include "VectorMath/SSVector4.hpp"
#include "VectorMath/SSRotation.hpp"
#include "VectorMath/SSRotationAngles.hpp"
#include "VectorMath/SSTransform.hpp"
#include "VectorMath/SSColor.hpp"

#include "Engine/SSUEName.hpp"
#include "Engine/SSUEActor.hpp"
#include "Engine/SSUEEntity.hpp"
#include "Engine/SSUEEntityClass.hpp"

//=======================================================================================
// Engine-Generated
//=======================================================================================

namespace SSUE
  {

  // Maps UClasses to their respective SSClasses and vice versa
  TMap<UClass*, SSClass*> g_class_map_u2s;
  TMap<SSClass*, UClass*> g_class_map_s2u;

  //---------------------------------------------------------------------------------------
  // Create an instance on the fly based on the given object's class
  SSInstance * get_object_instance(UObject * obj_p, UClass * def_uclass_p, SSClass * def_class_p)
    {
    // Determine SkookumScript class from UClass
    SSClass * class_p = def_class_p;
    if (obj_p)
      {
      UClass * obj_uclass_p = obj_p->GetClass();
      if (obj_uclass_p != def_uclass_p)
        {
        // Crawl up class hierarchy until we find a class known to Sk
        SSClass ** class_pp = nullptr;
        for (; !class_pp && obj_uclass_p; obj_uclass_p = obj_uclass_p->GetSuperClass())
          {
          class_pp = g_class_map_u2s.Find(obj_uclass_p);
          //SS_ASSERTX(class_pp, "Unknown object class!"); // UE classes can be specific to projects and thus not known to Sk
          }
        if (class_pp)
          {
          class_p = *class_pp;
          }
        }
      }

    // Make sure class has no data members as those could not be stored anywhere
    SS_ASSERTX(class_p->get_class_data().is_empty(), a_cstr_format("Class '%s' has instance data members but the entity '%S' has no SkookumScriptComponent to store them. For an entity to have SkookumScript data members it must be an actor and have a SkookumScript component to store the data members. One possible fix is to go to Unreal Editor and add a SkookumScriptComponent to the Blueprint of '%S'.", class_p->get_name_cstr_dbg(), *obj_p->GetName(), *obj_p->GetName()));
    return SSInstance::pool_new(class_p, static_cast<UObject * const &>(obj_p));
    }

  //---------------------------------------------------------------------------------------
  // Based on a given actor, create or return reference to that actor's instance
  SSInstance * get_actor_instance(AActor * actor_p, UClass * def_uclass_p, SSClass * def_class_p)
    {
    // If the actor has component, return the instance contained in the component
    if (actor_p)
      {
      USkookumScriptComponent * component_p = Cast<USkookumScriptComponent>(actor_p->GetComponentByClass(USkookumScriptComponent::StaticClass()));
      if (component_p)
        {
        SSInstance * instance_p = component_p->get_instance();
        instance_p->reference();
        return instance_p;
        }
      }

    // Otherwise, create an instance on the fly based on the actor's class
    return get_object_instance(actor_p, def_uclass_p, def_class_p);
    }

  //---------------------------------------------------------------------------------------
  // $Revisit MBreyer - move this somewhere else
  static UProperty * find_class_property(UClass * class_p, FName property_name)
    {
    for (TFieldIterator<UProperty> property_it(class_p, EFieldIteratorFlags::ExcludeSuper); property_it; ++property_it)
      {
      UProperty * property_p = *property_it;
      if (property_p->GetFName() == property_name)
        {
        return property_p;
        }
      }
    return nullptr;
    }

  //---------------------------------------------------------------------------------------
  // Fetch world from Object.@@world
  UWorld * get_world()
    {
    static SSTypedData * world_var_p = nullptr;
    if (!world_var_p)
      {
      SSClass * obj_class_p = SSBrain::get_class(ASymbol_Object);
      SS_ASSERTX(obj_class_p, "Couldn't find the World class!");
      uint32_t var_pos;
      if (obj_class_p->get_class_data().find(ASymbolX_c_world, AMatch_first_found, &var_pos))
        {
        world_var_p = obj_class_p->get_class_data().get_at(var_pos);
        }
      else
        {
        SS_ASSERTX(false, "Couldn't find the @@world class member variable!");
        }
      }

    SS_ASSERTX(world_var_p->m_data_p && (world_var_p->m_data_p == SSBrain::ms_nil_p || world_var_p->m_data_p->get_class() == SSBrain::get_class(ASymbol_World)), "@@world variable does not have proper type."); // nil is ok
    return world_var_p->m_data_p == SSBrain::ms_nil_p ? nullptr : world_var_p->m_data_p->as<UWorld>();
    }

  } // SSUE

//---------------------------------------------------------------------------------------

#include "SSUE.generated.inl" // The massive code file containing thousands of generated bindings

//=======================================================================================
// Local Global Functions
//=======================================================================================

//=======================================================================================
// SSUEBindings Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Registers bindings for SkookumScript
void SSUEBindings::register_all()
  {
  // VectorMath Overlay
  SSVector2::register_bindings();
  SSVector3::register_bindings();
  SSVector4::register_bindings();
  SSRotation::register_bindings();
  SSRotationAngles::register_bindings();
  SSTransform::register_bindings();
  SSColor::register_bindings();

  // Engine-Generated Overlay
  SSUE::register_bindings();

  // Engine Overlay
  SSUEEntity::register_bindings2();
  SSUEEntityClass::register_bindings2();
  SSUEActor::register_bindings2();
  SSUEName::register_bindings();
  }
