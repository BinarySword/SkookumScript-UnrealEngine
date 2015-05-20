//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Instance of a class with data members
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSDATAINSTANCE_HPP
#define __SSDATAINSTANCE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/APSorted.hpp>
#include "SkookumScript/SSInstance.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================


//---------------------------------------------------------------------------------------
// Notes      Class instance objects with one or more data members
// Subclasses SSDataInstance(SSActor), SSMetaClass
// Author(s)  Conan Reis
class SSDataInstance : public SSInstance
  {
  public:
  
  friend class AObjBlock<SSDataInstance>;

  // Common Methods

    SS_NEW_OPERATORS(SSDataInstance);
    SSDataInstance(SSClass * class_p);
    virtual ~SSDataInstance();


  // Methods

    void add_data_members();
    void data_empty()          { SSData::empty_table(&m_data); }

    virtual SSData * get_data_by_instance(const SSInstance & obj) const;

    // Overriding from SSInstance

    virtual void pool_delete() override;

    // Overriding from SSObjectBase

    virtual SSInstance * get_data_by_name(const ASymbol & name) const override;
    virtual void         set_data_by_name(const ASymbol & name, SSInstance * obj_p);

    
  // Class Methods

    static SSDataInstance * pool_new(SSClass * class_p);
    static AObjReusePool<SSDataInstance> & get_pool();


  protected:

  // Internal Methods

    // Default constructor only may be called by pool_new()
    SSDataInstance() {}

  // Data Members

    // Array of class instance data members - accessed by symbol name.
    // $Revisit - CReis It may be possible to rewrite this so that a direct index can be
    // used rather than a binary search of the symbols
    tSSDataTable m_data;

  };  // SSDataInstance


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         class_p - Class type for this instance
// # Author(s): Conan Reis
inline SSDataInstance::SSDataInstance(
  SSClass * class_p // = nullptr
  ) :
  SSInstance(class_p)
  {
  add_data_members();
  }


#endif  // __SSDATAINSTANCE_HPP

