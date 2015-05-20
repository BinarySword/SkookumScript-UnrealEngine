//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Typed name and typed data classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSInstance.hpp"


//=======================================================================================
// SSTypedName Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Default constructor
// # Returns:  itself
// Arg         name - name of the object (Default ASymbol::ms_null)
// Arg         type_p - class type to use.  The instance stored by this member must be of
//             this class or a subclass.
// # Notes:    A SSTypedName may be coerced to or from a ASymbol if only the name is needed.
// # Author(s): Conan Reis
A_INLINE SSTypedName::SSTypedName(
  const ASymbol &         name,  // = ASymbol::ms_null
  const SSClassDescBase * type_p // = nullptr
  ) :
  ANamed(name),
  m_type_p(const_cast<SSClassDescBase *>(type_p))
  {
  }

//---------------------------------------------------------------------------------------
// Copy constructor
// # Returns:  itself
// Arg         source - Typed name to copy
// # Notes:    May be coerced to or from a ASymbol if only the name is needed.
// # Author(s): Conan Reis
A_INLINE SSTypedName::SSTypedName(const SSTypedName & source) :
  ANamed(source),
  m_type_p(source.m_type_p)
  {
  }

//---------------------------------------------------------------------------------------
// Destructor
// # Author(s): Conan Reis
A_INLINE SSTypedName::~SSTypedName()
  {
  // Defined here to ensure compiler knows about SSClass details
  }


//=======================================================================================
// SSTypedData Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Default constructor
// # Returns:  itself
// Arg         name - name of the object (Default ASymbol::ms_null)
// Arg         type_p - class type to use.  The instance stored by this member must be of
//             this class or a subclass.
// Arg         instance_p - pointer to class instance to reference.  [Note that it does
//             not automatically have its reference count incremented.]
// # Notes:    A SSTypedData may be coerced to or from a ASymbol if only the name is needed.
// # Author(s): Conan Reis
A_INLINE SSTypedData::SSTypedData(
  const ASymbol &         name,      // = ASymbol::ms_null
  const SSClassDescBase * type_p,    // = nullptr
  SSInstance *            instance_p // = nullptr
  ) :
  SSTypedName(name, type_p),
  m_data_p(instance_p)
  {
  }

//---------------------------------------------------------------------------------------
// Copy constructor
// # Returns:  itself
// Arg         source - Typed name to copy
// # Author(s): Conan Reis
A_INLINE SSTypedData::SSTypedData(const SSTypedData & source) :
  SSTypedName(source),
  m_data_p(source.m_data_p)
  {
  }

 //---------------------------------------------------------------------------------------
// Data setter
// # Author(s): Conan Reis
A_INLINE void SSTypedData::set_data(SSInstance * data_p)
  {
  if (data_p) data_p->reference();
  if (m_data_p) m_data_p->dereference();
  m_data_p = data_p;
  }
