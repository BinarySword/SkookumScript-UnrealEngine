//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Typed name and typed data classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSTYPED_HPP
#define __SSTYPED_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ANamed.hpp>
#include <AgogCore/APSorted.hpp>
#include <AgogCore/ARefCount.hpp>
#include "SkookumScript/SSClassDescBase.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClassUnaryBase;
class SSInstance;
class SSExpressionBase;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Typed Name
// Subclasses SSTypedData
// See Also   SSQualifier
// Author(s)  Conan Reis
struct SSTypedName : public ANamed
  {
  public:
	SS_NEW_OPERATORS(SSTypedName);
  // Public Data Members

    // Used as a hint to parser/compiler so that correct data member usage can be assured.
    // $Revisit - CReis In theory this hint should not be needed during run-time if not
    // debugging or parsing - i.e. if only SS_COMPILED_IN is defined.  Currently only used
    // if SS_CODE_IN, SS_CODE_OUT or SS_COMPILED_OUT is defined.]
    ARefPtr<SSClassDescBase> m_type_p;

  // Common Methods

    explicit SSTypedName(const ASymbol & name = ASymbol::get_null(), const SSClassDescBase * type_p = nullptr);
    SSTypedName(const SSTypedName & source);
    ~SSTypedName();

  // Comparison Methods

    bool operator==(const SSTypedName & typed) const  { return (m_name == typed.m_name) && (m_type_p->compare(*typed.m_type_p) == AEquate_equal); }
    bool operator<(const SSTypedName & typed) const   { return (m_name < typed.m_name) || ((m_name == typed.m_name) && (m_type_p->compare(*typed.m_type_p) == AEquate_less)); }

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      SSTypedName(const void ** binary_pp);
      void assign_binary(const void ** binary_pp);
    #endif

    #if (SKOOKUM & SS_COMPILED_OUT)
      void     as_binary(void ** binary_pp) const;
      uint32_t as_binary_length() const                 { return 4u + m_type_p->as_binary_ref_typed_length(); }
    #endif

  };  // SSTypedName

typedef APSortedLogical<SSTypedName, ASymbol> tSSTypedNames;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Typed Name Data reference
// See Also   SSData
// Author(s)  Conan Reis
struct SSTypedData : public SSTypedName
  {
  public:
	SS_NEW_OPERATORS(SSTypedData);
  // Public Data Members

    SSInstance * m_data_p;

  // Common Methods

    explicit SSTypedData(const ASymbol & name = ASymbol::get_null(), const SSClassDescBase * type_p = nullptr, SSInstance * instance_p = nullptr);
    SSTypedData(const SSTypedData & source);

    void set_data(SSInstance * data_p);

  // Class Methods

    static void empty_table(APSortedLogical<SSTypedData, ASymbol> * table_p);

  };  // SSTypedData


typedef APSortedLogical<SSTypedData, ASymbol> tSSTypedDatas;


//=======================================================================================
// Inline Functions
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSTyped.inl"
#endif


#endif  // __SSTYPED_HPP

