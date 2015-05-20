
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structures for class descriptors and class objects
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================


//=======================================================================================
// SSClassDescBase Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Increments the reference/usage count of this class [if such a mechanism is
//             used for this class type].
// # Modifiers: virtual
// # Author(s): Conan Reis
A_INLINE void SSClassDescBase::reference() const
  {
  // By default, do nothing.
  }

//---------------------------------------------------------------------------------------
// Decrements the reference/usage count of this class [if such a mechanism is
//             used for this class type].
// # Modifiers: virtual
// # Author(s): Conan Reis
A_INLINE void SSClassDescBase::dereference()
  {
  // By default, do nothing.
  }

//---------------------------------------------------------------------------------------
// Same as dereference() in that it decrements the reference count to this
//             object, but it does not call on_no_references() if the reference count
//             becomes 0.
// # Modifiers: virtual
// # Author(s): Conan Reis
A_INLINE void SSClassDescBase::dereference_delay() const
  {
  // By default, do nothing.
  }

//---------------------------------------------------------------------------------------
// Returns true if it is an `Actor` class or a subclass of `Actor` (SSActorClass) or
// false if not.
// 
// Returns:   true if it is an actor class instance (SSActorClass)
// Notes:     Same as calling is_class(*SSBrain::ms_actor_class_p), but faster.
// Modifiers: virtual
// Author(s): Conan Reis
A_INLINE bool SSClassDescBase::is_builtin_actor_class() const
  {
  return false;
  }

//---------------------------------------------------------------------------------------
//  Determines if this type is a generic/reflective class.
//  [Generic classes are: ThisClass_ and ItemClass_.  The Auto_ class is replaced during
//  parse as its type is determined via its surrounding context.]
//
// #Examples
//   "ThisClass_" with "String" as a scope type becomes "String"
//
// #Modifiers virtual
// #See Also  as_finalized_generic()
// #Author(s) Conan Reis
A_INLINE bool SSClassDescBase::is_generic() const
  {
  return false;
  }

//---------------------------------------------------------------------------------------
// Returns true if it is a metaclass - i.e. using class scope.
// # Returns:  true if it is a metaclass
// # Modifiers: virtual
// # Author(s): Conan Reis
A_INLINE bool SSClassDescBase::is_metaclass() const
  {
  return false;
  }


