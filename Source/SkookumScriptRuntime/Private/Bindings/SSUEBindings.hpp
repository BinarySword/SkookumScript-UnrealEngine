//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Unreal Engine Bindings
// 
// # Author(s):  Conan Reis
//=======================================================================================


#ifndef __SSUEBINDINGS_HPP
#define __SSUEBINDINGS_HPP


//=======================================================================================
// Includes
//=======================================================================================

//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
namespace SSUE
  {

  extern TMap<UClass*, SSClass*> g_class_map_u2s; // Maps UClasses to their respective SSClasses
  extern TMap<SSClass*, UClass*> g_class_map_s2u; // Maps SSClasses to their respective UClasses

  UWorld *      get_world(); // Get tha world

  SSInstance *  get_object_instance(UObject * obj_p, UClass * def_uclass_p = nullptr, SSClass * def_class_p = nullptr); // Create an instance on the fly based on the given object's class
  SSInstance *  get_actor_instance(AActor * actor_p, UClass * def_uclass_p = nullptr, SSClass * def_class_p = nullptr); // Based on a given actor, create or return reference to that actor's instance
  }

//---------------------------------------------------------------------------------------
class SSUEBindings
  {
  public:
  // Class Methods

    static void register_all();

  };  // SSUEBindings


//=======================================================================================
// Inline Methods
//=======================================================================================


#endif  // __SSUEBINDINGS_HPP

