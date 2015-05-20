//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structure for simplest type of object in language - instance of a
//             class without data members
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AObjReusePool.hpp>


//=======================================================================================
// SSInstance Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Default constructor - does not initialize all data members for speed.
// 
// # Notes:
//   Should probably use `new_pool()` instead.
//   ***Don't call this unless data members are manually initialized***
//   Used by get_pool().
//   
// # Author(s): Conan Reis
A_INLINE SSInstance::SSInstance()
  {
  }

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         class_p - Class type for this instance
// # Author(s): Conan Reis
A_INLINE SSInstance::SSInstance(
  SSClass * class_p // = nullptr
  ) :
  m_class_p(class_p)
  {
  m_ptr_id = ++ms_ptr_id_prev;
  }

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         class_p - Class type for this instance
// Arg         user_data - 32 bits of user info
// # Author(s): Conan Reis
A_INLINE SSInstance::SSInstance(
  SSClass * class_p,
  const UserData & user_data
  ) :
  m_class_p(class_p),
  m_user_data(user_data)
  {
  m_ptr_id = ++ms_ptr_id_prev;
  }

//---------------------------------------------------------------------------------------
// Destructor
// # Modifiers: virtual - overridden from SSObjectBase
// # Author(s): Conan Reis
A_INLINE SSInstance::~SSInstance()
  {
  m_ptr_id = AIdPtr_null;
  }

//---------------------------------------------------------------------------------------
// Returns the class of the instance
// # Returns:  class of the instance (may be a SSClass or a SSActorClass)
// # Author(s): Conan Reis
A_INLINE SSClass * SSInstance::get_class() const
  {
  return m_class_p;
  }

//---------------------------------------------------------------------------------------
// Returns the 'this' using this object as the scope.
// # Returns:  itself
// # See:      get_data_by_name(), set_data_by_name()
// # Modifiers: virtual from SSObjectBase
// # Author(s): Conan Reis
A_INLINE SSInstance * SSInstance::get_topmost_scope() const
  {
  return const_cast<SSInstance *>(this);
  }

//---------------------------------------------------------------------------------------
// Returns true if class type, false if not
// # Modifiers: virtual
// # Author(s): Conan Reis
A_INLINE bool SSInstance::is_metaclass() const
  {
  return false;
  }

//---------------------------------------------------------------------------------------
// Cleans up the instance.  Calls its destructor (if it has one) and adds it
//             to the reuse pool.
// # Modifiers: virtual - overridden from ARefCountMix<>
// # Author(s): Conan Reis
A_INLINE void SSInstance::on_no_references()
  {
  // Call its destructor - if it has one
  call_destructor();
  pool_delete();
  }

//---------------------------------------------------------------------------------------
//  Frees up an instance and puts it into the dynamic pool ready for its next
//              use.  This should be used instead of 'delete' because it prevents
//              unnecessary deallocations by saving previously allocated objects.
// Arg          str_ref_p - pointer to instance to free up and put into the dynamic pool.
// # Examples:  called by dereference()
// # See:       pool_new(), dereference()
// # Notes:     To 'allocate' an object use 'pool_new()' rather than 'new'.
// # Modifiers:  virtual
// # Author(s):  Conan Reis
A_INLINE void SSInstance::pool_delete()
  {
  //A_DPRINT("SSInstance::pool_delete('%s', 0x%p) - id: %u\n", m_class_p->get_name_cstr(), m_user_data, m_ptr_id);

  m_ptr_id = AIdPtr_null;

  get_pool().append(this);
  }

//---------------------------------------------------------------------------------------
A_INLINE void SSInstance::method_call(
  const ASymbol & method_name,
  SSInstance *    arg_p,     // = nullptr
  SSInstance **   result_pp, // = nullptr
  SSInvokedBase * caller_p   // = nullptr
  )
  {
  method_call(method_name, &arg_p, arg_p ? 1u : 0u, result_pp, caller_p);
  }

//---------------------------------------------------------------------------------------
// Evaluates the coroutine call.
// # Returns:  nullptr if the coroutine completed immediately or an invoked coroutine if the
//             coroutine has a deferred completion.
// Arg         coroutine_name - name of the coroutine to call if it exists for this object.
//             If the specified coroutine does not exist for this object it will assert if
//             (SKOOKUM & SS_DEBUG) is set.
// Arg         arg_p - pointer to an object to use as an argument to the coroutine.
//             If it is nullptr then no argument is passed.
// Arg         immediate - if true the coroutine is invoked immediately (it may not be fully
//             evaluated, but it will be *started* immediately), if false the coroutine is
//             scheduled for invocation on the next update.
// Arg         update_interval - Specifies how often the coroutine should be updated in
//             seconds.  (Default SSCall_interval_always)
// Arg         caller_p - object that called/invoked this expression and that may await
//             a result - call its pending_deferred() method with the result of this method
//             as necessary.  If it is nullptr, then there is no object that needs to be
//             notified when this invocation is complete.
// Arg         updater_p - mind that will update invoked coroutine as needed - generally
//             same updater as the caller.  If nullptr the caller's updater is used and if
//             the caller is nullptr scope_p is used.
// # See:      coroutine_schedule()
// # Author(s): Conan Reis
A_INLINE SSInvokedCoroutine * SSInstance::coroutine_call(
  const ASymbol & coroutine_name,
  SSInstance *    arg_p,           // = nullptr
  bool            immediate,       // = true
  f32             update_interval, // = SSCall_interval_always
  SSInvokedBase * caller_p,        // = nullptr
  SSMind *        updater_p        // = nullptr
  )
  {
  return coroutine_call(
    coroutine_name, &arg_p, arg_p ? 1u : 0u, immediate, update_interval, caller_p, updater_p);
  }

//---------------------------------------------------------------------------------------
// Retrieves an instance object from the dynamic pool and initializes it for
//             use.  This method should be used instead of 'new' because it prevents
//             unnecessary allocations by reusing previously allocated objects.
// # Returns:  a dynamic SSInstance
// # See:      pool_delete() 
// # Notes:    To 'deallocate' an object that was retrieved with this method, use
//             'pool_delete()' rather than 'delete'.
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSInstance * SSInstance::pool_new(SSClass * class_p)
  {
  SSInstance * instance_p = get_pool().pop();

  instance_p->m_class_p   = class_p;
  instance_p->m_ref_count = 1u;
  instance_p->m_ptr_id    = ++ms_ptr_id_prev;

  //A_DPRINT("SSInstance::pool_new('%s') - id: %u\n", class_p->get_name_cstr(), instance_p->m_ptr_id);

  return instance_p;
  }


//=======================================================================================
// SSInstanceUnreffed Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Default constructor - does not initialize all data members for speed
// # Notes:    ***Don't call this unless data members are manually initialized***
//             Used by get_pool().
// # Returns:  itself
// # Author(s): Conan Reis
A_INLINE SSInstanceUnreffed::SSInstanceUnreffed()
  {
  // Set ref count to essentially infinite - and on_no_references() modifiied just in case.
  m_ref_count = SSInstanceUnreffed_infinite_ref_count;
  }

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         class_p - Class type for this instance
// # Author(s): Conan Reis
A_INLINE SSInstanceUnreffed::SSInstanceUnreffed(
  SSClass * class_p // = nullptr
  ) :
  SSInstance(class_p)
  {
  // Set ref count to essentially infinite - and on_no_references() modifiied just in case.
  m_ref_count = SSInstanceUnreffed_infinite_ref_count;
  }

//---------------------------------------------------------------------------------------
// Would cleans up the instance though just resets reference count to a high
//             number since it ignores referencing/dereferencing.
// # Modifiers: virtual - overridden from SSInstance (which overrode ARefCountMix)
// # Author(s): Conan Reis
A_INLINE void SSInstanceUnreffed::on_no_references()
  {
  // Wow a million decrements!  Just reset it.
  m_ref_count = SSInstanceUnreffed_infinite_ref_count;
  }
