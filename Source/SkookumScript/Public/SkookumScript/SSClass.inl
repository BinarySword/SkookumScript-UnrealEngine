
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

#include <AgogCore/ABinaryParse.hpp>
#include "SkookumScript/SSBrain.hpp"
#include "SkookumScript/SSSymbol.hpp"


//=======================================================================================
// SSMetaClass Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Standard sort by name id.
// # Returns:  AEquate_less, AEquate_equal, AEquate_greater
// Arg         mclass - metaclass to compare
// # See:      SSClass::compare() - hierarchy sort
// # Author(s): Conan Reis
A_INLINE eAEquate SSMetaClass::compare(const SSMetaClass & mclass) const
  {
  return m_class_info_p->compare_ids(*mclass.m_class_info_p);
  }

//---------------------------------------------------------------------------------------
// Returns class type
// # Returns:  class type
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE eSSClassType SSMetaClass::get_class_type() const
  {
  return SSClassType_metaclass;
  }

//---------------------------------------------------------------------------------------
// Returns key/main class
// # Returns:  key/main class
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE SSClass * SSMetaClass::get_key_class() const
  {
  return m_class_info_p;
  }

//---------------------------------------------------------------------------------------
// Get the name of the wrapped class
// # Returns:  name of the wrapped class
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE const ASymbol & SSMetaClass::get_key_class_name() const
  {
  return m_class_info_p->m_name;
  }

//---------------------------------------------------------------------------------------
// Returns a MetaClass version of itself - i.e. the class as an instance.
// # Returns:  MetaClass version of itself
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMetaClass & SSMetaClass::get_metaclass() const
  {
  return *const_cast<SSMetaClass *>(this);
  }

//---------------------------------------------------------------------------------------
// Gets the named method.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSMetaClass::get_method(const ASymbol & method_name) const
  {
  return m_class_info_p->get_class_method(method_name);
  }

//---------------------------------------------------------------------------------------
// Gets the named method from this class or a superclass.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSMetaClass::get_method_inherited(const ASymbol & method_name) const
  {
  return m_class_info_p->get_class_method_inherited(method_name);
  }

//---------------------------------------------------------------------------------------
// Appends (or replaces existing) class scope method with the given name and
//             parameters.  The method will use this class as its class scope.
// Arg         method_p - method to append / replace
// # See:      Transfer constructor of SSParameters.
// # Notes:    Used when parsing / reading in compiled binary code
//             The parser ensures that there are no methods with duplicate names - this
//             method does not.
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE void SSMetaClass::append_method(SSMethodBase * method_p)
  {
  m_class_info_p->append_class_method(method_p);
  }

//---------------------------------------------------------------------------------------
// Returns true if it is a metaclass - i.e. using class scope.
// # Returns:  true if it is a metaclass
// # Modifiers: virtual - overridden from SSClassDescBase & SSInstance
// # Author(s): Conan Reis
A_INLINE bool SSMetaClass::is_metaclass() const
  {
  return true;
  }

//---------------------------------------------------------------------------------------
// Determines if class method has been previously registered in this class
//             (without searching through inherited methods).
// # Returns:  true if method has been previously registered, false if not
// Arg         method_name - name of method
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE bool SSMetaClass::is_method_valid(const ASymbol & method_name) const
  {
  return m_class_info_p->is_class_method_valid(method_name);
  }

//---------------------------------------------------------------------------------------
// Determines if the class method is available
// # Returns:  true if method is available, false if not.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE bool SSMetaClass::is_method_inherited_valid(const ASymbol & method_name) const
  {
  return m_class_info_p->is_class_method_inherited_valid(method_name);
  }

//---------------------------------------------------------------------------------------
// Appends (or replaces existing) coroutine with the given name and parameters
//             using this class as its class scope.
// Arg         method_p - method to append / replace
// # See:      Transfer constructor of SSParameters.
// # Notes:    Used when parsing / reading in compiled binary code
//             The parser ensures that there are no methods with duplicate names - this
//             method does not.
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE void SSMetaClass::append_coroutine(SSCoroutineBase * coroutine_p)
  {


  A_ERRORX("Class coroutines not yet implemented!")


  //m_class_p->append_class_coroutine(coroutine_p);
  }

//---------------------------------------------------------------------------------------
// Adds an class data member with the specified name to this class.
// Arg         name - name of class data member.  It must be unique - no superclass nor
//             subclass may have it and there should be no instance data member with the
//             same name either.
// Arg         type_p - class type of data member
// # See:      append_class_data()
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE SSTypedName * SSMetaClass::append_data_member(
  const ASymbol &   name,
  SSClassDescBase * type_p
  )
  {
  return m_class_info_p->append_class_data(name, type_p);
  }


//=======================================================================================
// SSClass Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Standard sort by name id.
// # Returns:  AEquate_less, AEquate_equal, AEquate_greater
// Arg         ssclass - class to compare
// # See:      compare() - hierarchy sort
// # Author(s): Conan Reis
A_INLINE eAEquate SSClass::compare_ids(const SSClass & ssclass) const
  {
  return m_name.compare(ssclass.m_name);
  }

//---------------------------------------------------------------------------------------
// Comparison function
// # Returns:  AEquate_equal, AEquate_less, or AEquate_greater
// Arg         sslcass - other class to compare against
// # Notes:    This method really only makes sense if the classes being compared are
//             ancestor/descendant or descendant/ancestor
// # Author(s): Conan Reis
A_INLINE eAEquate SSClass::compare(const SSClass & ssclass) const
  {
  if (this == &ssclass)
    {
    return AEquate_equal;
    }

  if (is_subclass(ssclass))
    {
    return AEquate_less;
    }

  return AEquate_greater;
  }

//---------------------------------------------------------------------------------------
// Sets whether the class should indicate that it has been loaded or not
// # Author(s): Conan Reis
A_INLINE void SSClass::set_flag_load(
  bool loaded // = true
  )
  {
  if (loaded)
    {
    m_flags = (m_flags & ~Flag_demand_unload) | Flag_loaded;
    }
  else
    {
    m_flags &= ~(Flag_loaded | Flag_demand_unload);
    }
  }


#if (SKOOKUM & SS_CODE_IN)

//---------------------------------------------------------------------------------------
// Gets existing object id validation list or creates one if set to use a validation list.
//
// #Notes
//   To get existing object id validation list without creating one if it doesn't already
//   exist use get_object_id_valid_list().
//
// #See Also  get_object_id_valid_list()
// #Author(s) Conan Reis
A_INLINE ASymbolTable * SSClass::get_object_id_valid_list_merge()
  {
  #if defined(A_SYMBOLTABLE_CLASSES)
    if ((m_object_ids_p == nullptr) && (m_flags & Flag_object_id_parse_list))
      {
      m_object_ids_p = SS_NEW(ASymbolTable)(true);
      }
  #endif

  return m_object_ids_p;
  }

#endif  // (SKOOKUM & SS_CODE_IN)


//---------------------------------------------------------------------------------------
// Appends the specified subclass to this class
// Arg         subclass_p - pointer to subclass to append
// # Author(s): Conan Reis
A_INLINE void SSClass::append_subclass(SSClass * subclass_p)
  {
  m_subclasses.append_absent(*subclass_p);

  // CReis Append data and method tables if they exist.  This isn't implemented since this
  // is currently only called before any members have been added.
  }

//---------------------------------------------------------------------------------------
// Determines the closest superclass that this class and cls share.
// # Returns:  closest superclass that this class and cls share.
// # Author(s): Conan Reis
A_INLINE SSClass * SSClass::find_common_class(const SSClass & cls) const
  {
  SSClass * class_p = const_cast<SSClass *>(&cls);

  do
    {
    if (is_class(*class_p))
      {
      return class_p;
      }

    class_p = class_p->get_superclass();
    }
  while (class_p);

  // Should never get here since the "Object" class is a superclass of all classes.
  return nullptr;
  }

//---------------------------------------------------------------------------------------
//  Determines if this class is equal to or a subclass of (derived from) the
//              supplied class 'cls'.
// # Returns:   true if same class or subclass of 'cls', false if not
// Arg          cls - class to determine if this class is the same class or a subclass of
// # Examples:  bool correct_class = some_class.is_class(test_class);
// # Author(s):  Conan Reis
A_INLINE bool SSClass::is_class(const SSClass & cls) const
  {
  return (&cls == this) || (m_superclass_p && m_superclass_p->is_class(cls));
  }

//---------------------------------------------------------------------------------------
//  Determines if this class is a subclass of (derived from) the supplied
//              class 'superclass'.
// # Returns:   true if subclass of 'superclass', false if not
// Arg          superclass - class to determine if this class is a subclass of
// # Examples:  bool correct_class = some_class.is_subclass(test_class);
// # Author(s):  Conan Reis
A_INLINE bool SSClass::is_subclass(const SSClass & superclass) const
  {
  SSClass * super_p = m_superclass_p;

  return (super_p == &superclass) || (super_p && super_p->is_subclass(superclass));
  // Or this: return (m_superclass_p == &superclass) || (m_superclass_p && m_superclass_p->is_subclass(superclass));
  // Or this: return (m_superclass_p && m_superclass_p->is_class(superclass));
  }

//---------------------------------------------------------------------------------------
//  Determines if this class is a superclass of (parent of) the supplied
//              class 'subclass'.
// # Returns:   true if superclass of 'subclass', false if not
// Arg          subclass - class to determine if this class is a superclass of
// # Examples:  bool correct_class = some_class.is_superclass(test_class);
// # Author(s):  Conan Reis
A_INLINE bool SSClass::is_superclass(const SSClass & subclass) const
  {
  SSClass * sub_super_p = subclass.m_superclass_p;

  return (sub_super_p == this) || (sub_super_p && is_superclass(*sub_super_p));
  // Or this: return (subclass.m_superclass_p == this) || (subclass.m_superclass_p && is_superclass(subclass.m_superclass_p));
  // Or this: return subclass.is_subclass(*this);
  }

//---------------------------------------------------------------------------------------
// Determines if this class is a valid scope qualifier by the specified
//             receiver scope - i.e. receiver ThisClass@member
// # Returns:  true if valid scope qualifier, false if not
// Arg         recv_type_p - class type of receiver
// # See:      SSClassDescBase::qualify()
// # Author(s): Conan Reis
A_INLINE bool SSClass::is_scope_qualifier(SSClassDescBase * recv_type_p) const
  {
  return (recv_type_p == nullptr)
    || ((recv_type_p->get_class_type() == SSClassType_metaclass)
      ? static_cast<SSMetaClass *>(recv_type_p)->m_class_info_p->is_class(*this)
      : recv_type_p->is_class_type(this));
  }

//---------------------------------------------------------------------------------------
//  Gets the qualified (or unqualified) method.
// # Returns:   A pointer to the requested method or nullptr if it does not exist.
// Arg          method_qual - name and optional highest level scope of method.  Note
//              that a SSQualifier may be coerced from a ASymbol if the topmost scoped
//              method is desired.
// # Author(s):  Conan Reis
A_INLINE SSMethodBase * SSClass::get_instance_method_scoped_inherited(const SSQualifier & method_qual) const
  {
  // $Revisit - CReis [Index Look-up] This look-up should eventually be replaced with an index into a method table.
  SSClass * scope_p = method_qual.get_scope();

  return (scope_p ?
    scope_p->get_instance_method_inherited(method_qual.get_name()) :
    get_instance_method_inherited(method_qual.get_name()));
  }

//---------------------------------------------------------------------------------------
//  Gets the named coroutine.
// # Returns:   A pointer to the requested coroutine or nullptr if it does not exist.
// Arg          coroutine_name - name of coroutine.
// # See:       get_coroutine(coroutine_qual), get_coroutine(coroutine_call)
// # Author(s):  Conan Reis
A_INLINE SSCoroutineBase * SSClass::get_coroutine_inherited(const ASymbol & coroutine_name) const
  {
  SSCoroutineBase * coroutine_p = m_coroutines.get(coroutine_name);

  return (coroutine_p == nullptr)
    ? (m_superclass_p
      ? m_superclass_p->get_coroutine_inherited(coroutine_name)
      : nullptr)
    : coroutine_p;
  }

//---------------------------------------------------------------------------------------
//  Gets the qualified (or unqualified) coroutine.
// # Returns:   A pointer to the requested coroutine or nullptr if it does not exist.
// Arg          coroutine_qual - name and optional highest level scope of coroutine.  Note
//              that a SSQualifier may be coerced from a ASymbol if the topmost scoped
//              coroutine is desired.
// # Author(s):  Conan Reis
A_INLINE SSCoroutineBase * SSClass::get_coroutine_scoped_inherited(const SSQualifier & coroutine_qual) const
  {
  SSClass * scope_p = coroutine_qual.get_scope();

  return ((scope_p) && (scope_p != this)) ?
    scope_p->get_coroutine_inherited(coroutine_qual.get_name()) :
    get_coroutine_inherited(coroutine_qual.get_name());
  }

//---------------------------------------------------------------------------------------
// Determines if coroutine is registered - i.e. it exists and it is not a
//             placeholder.
// # Returns:  true if coroutine is registered
// Arg         coroutine_name - name of coroutine to check
// # Author(s): Conan Reis
A_INLINE bool SSClass::is_coroutine_registered(const ASymbol & coroutine_name) const
  {
  SSCoroutineBase * coro_p = m_coroutines.get(coroutine_name);

  return !((coro_p == nullptr) || coro_p->is_placeholder());
  }

//---------------------------------------------------------------------------------------
// Instantiates / creates a new instance of this class and adds any data
//             members and initializes them to nil
// # Returns:  an instance of this class
// # Notes:    This will not work for the 'Boolean' class.
// # Modifiers: virtual - override for custom behaviour
// # Author(s): Conan Reis
A_INLINE SSInstance * SSClass::new_instance()
  {
  if (m_data.get_length())
    {
    return SSDataInstance::pool_new(this);
    }
  else
    {
    return SSInstance::pool_new(this);
    }
  }

//---------------------------------------------------------------------------------------
// Returns class type
// # Returns:  class type
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE eSSClassType SSClass::get_class_type() const
  {
  return SSClassType_class;
  }

//---------------------------------------------------------------------------------------
// Returns key/main class
// # Returns:  key/main class
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE SSClass * SSClass::get_key_class() const
  {
  return const_cast<SSClass *>(this);
  }

//---------------------------------------------------------------------------------------
// Get the name of the class
// # Returns:  name of the class
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE const ASymbol & SSClass::get_key_class_name() const
  {
  return m_name;
  }

//---------------------------------------------------------------------------------------
// Returns component item class (as with a List) or nullptr if does not have component items.
//
// #Modifiers virtual
// #See Also  SSTypedClass
// #Author(s) Conan Reis
A_INLINE SSClassDescBase * SSClass::get_item_type() const
  {
  return (this == SSBrain::ms_list_class_p)
    ? SSBrain::ms_object_class_p
    : nullptr;
  }

//---------------------------------------------------------------------------------------
// Gets the named method.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSClass::get_method(const ASymbol & method_name) const
  {
  SSMethodBase * method_p = get_instance_method(method_name);

  return method_p
    ? method_p
    : get_class_method(method_name);
  }

//---------------------------------------------------------------------------------------
// Gets the named instance method from this class or a superclass.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # See:      get_instance_method_scoped_inherited(method_qual), get_class_method_inherited()
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSClass::get_instance_method_inherited(const ASymbol & method_name) const
  {
  // $Revisit - CReis [Index Look-up] This look-up should eventually be replaced with an index into a method table.
  SSMethodBase * method_p = m_methods.get(method_name);

  return ((method_p == nullptr) && m_superclass_p)
    ? m_superclass_p->get_instance_method_inherited(method_name)
    : method_p;
  }

//---------------------------------------------------------------------------------------
// Gets the named class method from this class or a superclass
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # See:      get_instance_method_scoped_inherited(method_qual), get_instance_method_inherited(method_name)
// # Notes:    Any returned class method must have a metaclass as a receiver.
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSClass::get_class_method_inherited(const ASymbol & method_name) const
  {
  SSMethodBase * method_p = m_class_methods.get(method_name);

  // Note that instance methods of "Object" are also valid for any class instance.

  return method_p
    ? method_p
    : (m_superclass_p
      ? m_superclass_p->get_class_method_inherited(method_name)
      : SSBrain::ms_object_class_p->m_methods.get(method_name));
  }

//---------------------------------------------------------------------------------------
// Gets the named method from this class or a superclass.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSClass::get_method_inherited(const ASymbol & method_name) const
  {
  SSMethodBase * method_p = get_instance_method_inherited(method_name);

  return method_p
    ? method_p
    : get_class_method_inherited(method_name);
  }

//---------------------------------------------------------------------------------------
// Returns a MetaClass version of itself - i.e. the class as an instance.
// # Returns:  MetaClass version of itself
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMetaClass & SSClass::get_metaclass() const
  {
  return const_cast<SSMetaClass &>(m_metaclass);
  }

//---------------------------------------------------------------------------------------
// Determines if method is registered - i.e. it exists and it is not a
//             placeholder.
// # Returns:  true if method is registered
// Arg         method_name - name of method to check
// # Author(s): Conan Reis
A_INLINE bool SSClass::is_method_registered(const ASymbol & method_name) const
  {
  // Note that only instance methods are checked - SSMetaClass checks class methods
  SSMethodBase * method_p = get_instance_method(method_name);

  return !((method_p == nullptr) || method_p->is_placeholder());
  }

//---------------------------------------------------------------------------------------
// Determines if the method is available
// # Returns:  true if method is available, false if not.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE bool SSClass::is_method_valid(const ASymbol & method_name) const
  {
  return (get_instance_method(method_name)
    || (get_class_method(method_name) != nullptr));
  }

//---------------------------------------------------------------------------------------
// Determines if the method is available
// # Returns:  true if method is available, false if not.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE bool SSClass::is_method_inherited_valid(const ASymbol & method_name) const
  {
  return ((get_instance_method_inherited(method_name) != nullptr)
    || (get_class_method_inherited(method_name) != nullptr));
  }

//---------------------------------------------------------------------------------------
// Appends (or replaces existing) instance method with the given name and
//             parameters.  The method will use this class as its class scope.
// Arg         method_p - method to append / replace
// # See:      Transfer constructor of SSParameters.
// # Notes:    Used when parsing / reading in compiled binary code
//             The parser ensures that there are no methods with duplicate names - this
//             method does not.
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE void SSClass::append_method(SSMethodBase * method_p)
  {
  // Note that only instance methods are checked.
  append_instance_method(method_p);
  }

//---------------------------------------------------------------------------------------
// Adds an instance data member with the specified name to this class.
//             When an instance of this class or a instance of a subclass is constructed
//             it will have a data member with this name.
// Arg         name - name of instance data member.  It must be unique - no superclass
//             nor subclass may have it and there should be no class data member with the
//             same name either.
// Arg         type_p - class type of data member
// # See:      append_class_data()
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE SSTypedName * SSClass::append_data_member(
  const ASymbol &   name,
  SSClassDescBase * type_p
  )
  {
  return append_instance_data(name, type_p);
  }


//=======================================================================================
// SSClassUnion Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Copy Constructor
// Arg         class_union - other union class to copy
// # Author(s): Conan Reis
A_INLINE SSClassUnion::SSClassUnion(const SSClassUnion & class_union) :
  m_common_class_p(class_union.m_common_class_p),
  m_union(class_union.m_union)
  {
  if (m_common_class_p)
    {
    m_common_class_p->reference();
    }

  m_union.apply_method(&SSClassUnaryBase::reference);
  }

//---------------------------------------------------------------------------------------
// Destructor
// # Modifiers: virtual - overridden from ARefCountMix<>
// # Author(s): Conan Reis
A_INLINE SSClassUnion::~SSClassUnion()
  {
  if (m_common_class_p)
    {
    m_common_class_p->dereference_delay();
    }

  m_union.apply_method(&SSClassUnaryBase::dereference_delay);
  }

//---------------------------------------------------------------------------------------
// Assignment
// Arg         class_union - other union class to copy
// # Author(s): Conan Reis
A_INLINE SSClassUnion & SSClassUnion::operator=(const SSClassUnion & class_union)
  {
  set_common_class(class_union.m_common_class_p);

  class_union.m_union.apply_method(&SSClassUnaryBase::reference);
  m_union.apply_method(&SSClassUnaryBase::dereference_delay);
  m_union = class_union.m_union;

  return *this;
  }

// Converters from data structures to compiled binary code
#if (SKOOKUM & SS_COMPILED_OUT)

//---------------------------------------------------------------------------------------
// Binary reference length in bytes.
// # Modifiers: virtual
// # Author(s): Conan Reis
A_INLINE uint32_t SSClassUnion::as_binary_ref_typed_length() const
  {
  return ms_compounds_use_ref ? Binary_ref_size : (1u + as_binary_length());
  }

#endif // (SKOOKUM & SS_COMPILED_OUT)


// Converters from compiled binary code to data structures
#if (SKOOKUM & SS_COMPILED_IN)

//---------------------------------------------------------------------------------------
// Returns pointer to class based on the binary reference info or nullptr if not
//             found
// # Returns:  pointer to class or nullptr
// Arg         binary_pp - Pointer to address to read binary serialization info from and
//             to increment - previously filled using as_binary_ref() or a similar
//             mechanism.
// # See:      as_binary_ref_typed(), as_binary_ref_typed_length(), from_binary_ref_typed()
// # Notes:    Binary composition:
//               4 bytes - class union index
//
//             Little error checking is done on the binary info as it assumed that it
//             previously validated upon input.
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSClassUnion * SSClassUnion::from_binary_ref(const void ** binary_pp)
  {
  if (ms_compounds_use_ref)
    {
    // $Note - CReis This method assumes that the order and number of shared class unions
    // is the same now as when the reference was saved.
    return ms_shared_unions.get_at(A_BYTE_STREAM_UI32_INC(binary_pp));
    }
  else
    {
    return get_or_create(SSClassUnion(binary_pp));
    }
  }

#endif // (SKOOKUM & SS_COMPILED_IN)


//---------------------------------------------------------------------------------------
// Clears class union
// # Author(s): Conan Reis
A_INLINE void SSClassUnion::clear()
  {
  m_union.apply_method(&SSClassUnaryBase::dereference_delay);
  m_union.empty();

  if (m_common_class_p)
    {
    m_common_class_p->dereference_delay();
    }

  m_common_class_p = nullptr;
  }

//---------------------------------------------------------------------------------------
// Returns a matching class union from the shared global list of class unions.
//             If a matching class union does not already exist, it creates one.
// # Returns:  global class union
// Arg         class_union - class union to find match for
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSClassUnion * SSClassUnion::get_or_create(const SSClassUnion & class_union)
  {
  uint32_t       find_pos;
  SSClassUnion * union_p = ms_shared_unions.get(class_union, AMatch_first_found, &find_pos);

  if (union_p == nullptr)
    {
    union_p = SS_NEW(SSClassUnion)(class_union);
    ms_shared_unions.insert(*union_p, find_pos);
    }

  return union_p;
  }

//---------------------------------------------------------------------------------------
// Returns class type
// # Returns:  class type
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE eSSClassType SSClassUnion::get_class_type() const
  {
  return SSClassType_class_union;
  }

//---------------------------------------------------------------------------------------
// Returns class type of data member
// # Returns:  class type of data member
// Arg         data_name - name of data member
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSClassDescBase * SSClassUnion::get_data_type(
  const ASymbol & data_name,
  eSSScope *      scope_p // = nullptr
  ) const
  {
  // Without a cast to a specific class use nearest shared superclass.
  return m_common_class_p->get_data_type(data_name, scope_p);
  }

//---------------------------------------------------------------------------------------
// Returns key/main class
// # Returns:  key/main class
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE SSClass * SSClassUnion::get_key_class() const
  {
  return m_common_class_p->get_key_class();
  }

//---------------------------------------------------------------------------------------
// Get the name of the wrapped class
// # Returns:  name of the wrapped class
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE const ASymbol & SSClassUnion::get_key_class_name() const
  {
  return m_common_class_p->get_key_class_name();
  }

//---------------------------------------------------------------------------------------
// Returns a MetaClass version of itself - i.e. the class as an instance.
// # Returns:  MetaClass version of itself
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMetaClass & SSClassUnion::get_metaclass() const
  {
  // Without a cast to a specific class use nearest shared superclass.
  return m_common_class_p->get_metaclass();
  }

//---------------------------------------------------------------------------------------
// Gets the named method.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSClassUnion::get_method(const ASymbol & method_name) const
  {
  // Without a cast to a specific class use nearest shared superclass.
  return m_common_class_p->get_method(method_name);
  }

//---------------------------------------------------------------------------------------
// Gets the named method from this class or a superclass.
// # Returns:  A pointer to the requested method or nullptr if it does not exist.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE SSMethodBase * SSClassUnion::get_method_inherited(const ASymbol & method_name) const
  {
  // Without a cast to a specific class use nearest shared superclass.
  return m_common_class_p->get_method_inherited(method_name);
  }

//---------------------------------------------------------------------------------------
//  Gets the named coroutine.
// # Returns:   A pointer to the requested coroutine or nullptr if it does not exist.
// Arg          coroutine_name - name of coroutine.
// # See:       get_coroutine(coroutine_qual), get_coroutine(coroutine_call)
// # Author(s):  Conan Reis
A_INLINE SSCoroutineBase * SSClassUnion::get_coroutine_inherited(const ASymbol & coroutine_name) const
  {
  return m_common_class_p->get_coroutine_inherited(coroutine_name);
  }

//---------------------------------------------------------------------------------------
// Returns true if it is an "Actor" class or a subclass of "Actor"
//             (SSActorClass) or false if not.
// # Returns:  true if it is an actor class instance (SSActorClass)
// # Notes:    Same as calling is_class(*SSBrain::ms_actor_class_p), but faster.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE bool SSClassUnion::is_builtin_actor_class() const
  {
  return m_common_class_p->is_builtin_actor_class();
  }

//---------------------------------------------------------------------------------------
// Returns true if it is a metaclass - i.e. using class scope.
// # Returns:  true if it is a metaclass
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE bool SSClassUnion::is_metaclass() const
  {
  return m_common_class_p->is_metaclass();
  }

//---------------------------------------------------------------------------------------
// Determines if the method is available
// # Returns:  true if method is available, false if not.
// Arg         method_name - name of method.
// # Modifiers: virtual - overridden from SSClassUnaryBase
// # Author(s): Conan Reis
A_INLINE bool SSClassUnion::is_method_inherited_valid(const ASymbol & method_name) const
  {
  // Without a cast to a specific class use nearest shared superclass.
  return m_common_class_p->is_method_inherited_valid(method_name);
  }

//---------------------------------------------------------------------------------------
// Decrements the reference count to this object and if the reference count
//             becomes 0 call on_no_references()
// # See:      reference(), dereference_delay(), on_no_references()
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE void SSClassUnion::dereference()
  {
  ARefCountMix<SSClassUnion>::dereference();
  }

//---------------------------------------------------------------------------------------
// Same as dereference() in that it decrements the reference count to this
//             object, but it does not call on_no_references() if the reference count
//             becomes 0.
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE void SSClassUnion::dereference_delay() const
  {
  ARefCountMix<SSClassUnion>::dereference_delay();
  }

//---------------------------------------------------------------------------------------
// Increments the reference count to this object.
// # See:      dereference(), dereference_delay()
// # Modifiers: virtual - overridden from SSClassDescBase
// # Author(s): Conan Reis
A_INLINE void SSClassUnion::reference() const
  {
  ARefCountMix<SSClassUnion>::reference();
  }

//---------------------------------------------------------------------------------------
// Called when the number of references to this object reaches zero - by
//             default it deletes this object and removes it from the list of available
//             class unions.
// # See:      dereference(), ensure_reference()
// # Notes:    called by dereference() and ensure_reference()
// # Author(s): Conan Reis
A_INLINE void SSClassUnion::on_no_references()
  {
  ms_shared_unions.free(*this);
  }

//---------------------------------------------------------------------------------------
// # Author(s): Conan Reis
A_INLINE void SSClassUnion::set_common_class(SSClassUnaryBase * class_p)
  {
  if (class_p)
    {
    class_p->reference();
    }

  if (m_common_class_p)
    {
    m_common_class_p->dereference_delay();
    }

  m_common_class_p = class_p;
  }

