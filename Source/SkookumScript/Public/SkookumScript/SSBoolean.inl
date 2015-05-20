//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Boolean (true/false) class - allows short circuit
//             evaluation.
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AObjReusePool.hpp>
#include "SkookumScript/SSBrain.hpp"


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Modifiers: protected
// # Author(s): Conan Reis
A_INLINE SSBoolean::SSBoolean() :
  SSInstance(SSBrain::ms_boolean_class_p)
  {
  // $Note - CReis If this is called while initializing the Boolean pool before the classes
  // (SSBrain::ms_boolean_class_p in particular) have been set in SSBrain::initialize_pre_load()
  // then SSBoolean::init_pool() must be called after SSBrain::initialize_pre_load().
  }

//---------------------------------------------------------------------------------------
// Retrieves a Boolean instance object from the dynamic pool and initializes
//             it for use.  This method should be used instead of 'new' because it
//             prevents unnecessary allocations by reusing previously allocated objects.
// # Returns:  a dynamic SSBoolean
// Arg         bool_value - Should be a bool or 0 or 1
// # See:      pool_delete() 
// # Notes:    To 'deallocate' an object that was retrieved with this method, use
//             'pool_delete()' rather than 'delete'.
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSBoolean * SSBoolean::pool_new(SSBooleanType bool_value)
  {
  SSBoolean * bool_p = get_pool().pop();

  bool_p->set(bool_value);
  bool_p->m_ref_count = 1u;
  bool_p->m_ptr_id    = ++ms_ptr_id_prev;

  return bool_p;
  }
  
//---------------------------------------------------------------------------------------
// Evaluates if the SSBoolean is true
// # Returns:  bool
// # See:      is_false() 
// # Notes:    
// # Modifiers: 
// # Author(s): Richard Orth
A_INLINE bool SSBoolean::is_true()
  {
  return !!*as<SSBooleanType>();
  }

//---------------------------------------------------------------------------------------
// Evaluates if the SSBoolean is false
// # Returns:  bool
// # See:      is_true() 
// # Notes:    
// # Modifiers: 
// # Author(s): Richard Orth
A_INLINE bool SSBoolean::is_false()
  {
  return !*as<SSBooleanType>();
  }
