//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Qualifier class - full qualification consisting of member name and owner class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSQUALIFIER_HPP
#define __SSQUALIFIER_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ANamed.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

class SSClass;  // Pre-declaration


//---------------------------------------------------------------------------------------
// Notes      Qualifier class - full qualification consisting of member name and owner class
// Subclasses SSInvokableBase(SSMethodBase, SSCoroutineBase),
//            SSInvokeBase(SSMethodCall, SSCoroutineCall)
// See Also   SSTypedName
// Author(s)  Conan Reis
class SSQualifier : public ANamed
  {
  friend class SSQualifierCompareName;

  public:
	  SS_NEW_OPERATORS(SSQualifier);
  // Common Methods

    explicit SSQualifier(const ASymbol & name = ASymbol::get_null(), SSClass * scope_p = nullptr);
    SSQualifier(const SSQualifier & source) : ANamed(source), m_scope_p(source.m_scope_p) {}

    SSQualifier & operator=(const SSQualifier & source) { m_name = source.m_name; m_scope_p = source.m_scope_p; return *this; }

  // Comparison Methods

    bool operator==(const SSQualifier & qual) const;
    bool operator<(const SSQualifier & qual) const;
    bool equal_ids(const SSQualifier & qual) const;
    bool equal_ids_scope_name(const SSQualifier & qual) const;
    bool less_ids_scope_name(const SSQualifier & qual) const;
    bool less_ids_name_scope(const SSQualifier & qual) const;

  // Methods

    SSClass * get_scope() const;
    void      set_scope(const SSClass * scope_p);
    void      invalidate()                           { m_name.set_null(); m_scope_p = nullptr; }

    // Data Methods - only valid if qualifier represents data member

      SSClassDescBase * get_data_type() const;

  // Class Methods

  protected:

  // Data Members

    // $Revisit - CReis Should probably be SSClassUnaryBase so it could be either
    // SSClass/SSActorClass or SSMetaClass
    SSClass * m_scope_p;

  };  // SSQualifier


//---------------------------------------------------------------------------------------
// This is passed as a second argument to various template classes such as APArray and
// APSorted to provide a mechanism for logical sorting of elements.
//
// Does a logical comparison of the name and then the scope.
class SSQualifierCompareName
  {
  public:
  // Class Methods

    // Returns true if elements are equal
    static bool equals(const SSQualifier & lhs, const SSQualifier & rhs)     { return (lhs.m_name == rhs.m_name) && (lhs.m_scope_p == rhs.m_scope_p); }

    // Returns 0 if equal, < 0 if lhs is less than rhs, and > 0 if lhs is greater than rhs
    static ptrdiff_t comparison(const SSQualifier & lhs, const SSQualifier & rhs);
  };


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSQualifier.inl"
#endif


#endif  // __SSQUALIFIER_HPP

