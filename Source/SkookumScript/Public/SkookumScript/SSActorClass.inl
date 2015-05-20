//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structure for actor class descriptors and actor class objects
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSDebug.hpp"


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
//  Constructor
// # Returns:   itself
// Arg          name - Name of the class.  It should follow the form of "ClassName"
//              uppercase {alphanumeric}
// Arg          superclass_p - pointer to superclass of this class.  Only "Object" should
//              have no superclass.
// # Author(s):  Conan Reis
A_INLINE SSActorClass::SSActorClass(
  const ASymbol & name,         // = ASymbol::ms_null
  SSClass *       superclass_p, // = nullptr
  uint32_t        flags         // = Flag__default_actor
  ) :
  SSClass(name, superclass_p, flags)
  {
  }

//---------------------------------------------------------------------------------------
// Appends an actor instance of this class to the instance list of this class
// Arg         actor - actor instance to append
// # Examples: called in SSActor::SSActor()
// # Author(s): Conan Reis
A_INLINE void SSActorClass::append_instance(const SSActor & actor)
  {
  //A_DPRINT(A_SOURCE_STR " SSActorClass::append_instance('%s')\n", actor.get_name_cstr_dbg());

  if (actor.get_name() != ASymbol::get_null())
    {
    //if (m_instances.find(actor.get_name()))
    //  {
    //  A_DPRINT(A_SOURCE_STR " SSActorClass::append_instance('%s') - dupe found!\n", actor.get_name_cstr_dbg());
    //  }

    m_instances.append(actor);

    if (m_superclass_p->is_builtin_actor_class())
      {
      static_cast<SSActorClass *>(m_superclass_p)->append_instance(actor);
      }
    }
  }

//---------------------------------------------------------------------------------------
// Removes an actor instance of this class from the instance list of this class.
// 
// # Params:
//   actor: actor instance to remove
//   term: if ATerm_short then it is only a temporary removal for something like a rename
//   
// # Examples: called in SSActor::~SSActor() and SSActor:rename()
// # Author(s): Conan Reis
A_INLINE void SSActorClass::remove_instance(
  const SSActor & actor,
  eATerm          term // = ATerm_long
  )
  {
  //A_DPRINT(A_SOURCE_STR " SSActorClass::remove_instance('%s')\n", actor.get_name_cstr_dbg());

  if (actor.get_name() != ASymbol::get_null())
    {
    m_instances.remove_elem(actor);

    if (m_superclass_p->is_builtin_actor_class())
      {
      static_cast<SSActorClass *>(m_superclass_p)->remove_instance(actor);
      }

    if ((term == ATerm_long) && m_instances.is_empty())
      {
      m_instances.compact();

      // If there was a deferred unload and there are no more instances, do the unload now
      if (m_flags & Flag_demand_unload)
        {
        demand_unload();
        }
      }
    }
  }

