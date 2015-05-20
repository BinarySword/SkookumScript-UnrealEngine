//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structure for storing user data
//
// # Author(s): Markus Breyer
// # Notes:        
//=======================================================================================

#ifndef __SSUSERDATA_HPP
#define __SSUSERDATA_HPP

//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ARefCount.hpp>
#include <AgogCore/AString.hpp>
#include <AgogCore/ADebug.hpp>

//=======================================================================================
//
//=======================================================================================

// Base class for accessing user data stored inside a class instance
struct SSUserDataBase
  {
  // Gets an object stored by value in this data structure cast to the desired type
  // Each specialization _must_ be explicitly template-specialized to make sure it's properly stored
  template <typename _UserType> _UserType * as() const  { static_assert(sizeof(_UserType) == 0, "as() _must_ be specialized for each type that is stored to make sure each type is stored correctly!"); return nullptr; }

  // Handy helper for POD types that are stored by value in this object
  template <typename _UserType> _UserType * as_stored() const { return (_UserType *)this; }

  // Sets user data of this object
  // Each specialization _must_ be explicitly template-specialized to make sure it's properly stored
  template <typename _UserType> void set(_UserType const & value)  { static_assert(sizeof(_UserType) == 0, "set() _must_ be specialized for each type that is stored to make sure each type is stored correctly!"); }

  };

// Class for storing user data
template <int _SizeInPtrs>
struct SSUserData : private SSUserDataBase
  {
  template <typename _UserType> _UserType * as() const;
  template <typename _UserType> void        set(const _UserType & value) { SSUserDataBase::set(value); }

  // placeholder union to reserve appropriate space
  union
    {
    SSIntegerType   m_integer;
    SSRealType      m_real;
    SSEnumType      m_enum;
    uintptr_t       m_uintptr;
    void *          m_ptr[_SizeInPtrs];
    }               m_data;
  };

//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// A few common specializations of SSUserDataBase::as()

template<> inline SSIntegerType * SSUserDataBase::as<SSIntegerType>() const { return as_stored<SSIntegerType>(); }
template<> inline SSRealType    * SSUserDataBase::as<SSRealType   >() const { return as_stored<SSRealType   >(); }
template<> inline SSCharType    * SSUserDataBase::as<SSCharType   >() const { return as_stored<SSCharType   >(); }
template<> inline SSBooleanType * SSUserDataBase::as<SSBooleanType>() const { return as_stored<SSBooleanType>(); }
template<> inline SSEnumType    * SSUserDataBase::as<SSEnumType   >() const { return as_stored<SSEnumType   >(); }
template<> inline AString       * SSUserDataBase::as<AString      >() const { return as_stored<AString      >(); }
template<> inline ASymbol       * SSUserDataBase::as<ASymbol      >() const { return as_stored<ASymbol      >(); }

//---------------------------------------------------------------------------------------
// A few common specializations of SSUserDataBase::set()

template<> inline void SSUserDataBase::set(const SSIntegerType & value) { *as_stored<SSIntegerType>() = value; }
template<> inline void SSUserDataBase::set(const SSRealType    & value) { *as_stored<SSRealType   >() = value; }
template<> inline void SSUserDataBase::set(const SSCharType    & value) { *as_stored<SSCharType   >() = value; }
template<> inline void SSUserDataBase::set(const SSBooleanType & value) { *as_stored<SSBooleanType>() = value; }
template<> inline void SSUserDataBase::set(const SSEnumType    & value) { *as_stored<SSEnumType   >() = value; }
template<> inline void SSUserDataBase::set(const AString       & value) { *as_stored<AString      >() = value; }
template<> inline void SSUserDataBase::set(const ASymbol       & value) { *as_stored<ASymbol      >() = value; }

//---------------------------------------------------------------------------------------
// Gets an object stored in this data structure cast to the desired type
// relies on SSUserDataBase::as() and its specializations to actually know how to do this
// 
template <int _SizeInPtrs>
template <typename _UserType>
inline _UserType * SSUserData<_SizeInPtrs>::as() const
  {
  _UserType * data_p = SSUserDataBase::as<_UserType>();
  A_ASSERTX((void*)data_p != (void*)this || sizeof(_UserType) <= sizeof(*this), "_UserType does not fit into this instance of SSUserData.");
  return data_p;
  }

#endif  // __SSUSERDATA_HPP

