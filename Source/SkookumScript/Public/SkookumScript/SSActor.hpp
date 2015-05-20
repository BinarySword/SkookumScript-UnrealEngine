//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Actor class - i.e. named simulation objects with a list of all instances stored in
// their classes
// 
// Author(s): Conan Reis
//=======================================================================================


#ifndef __SSACTOR_HPP
#define __SSACTOR_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSDataInstance.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSActorClass;

//---------------------------------------------------------------------------------------
// Named simulation object with a list of all instances stored in their classes (SSActorClass).
// 
// $Revisit - CReis Some actors may not need data members so there could be a version of
// `SSActor` that derives from `SSInstance` rather than `SSDataInstance`.
class SSActor :
  public ANamed,         // Adds name
  public SSDataInstance  // Adds instance info and data members.
  {
  public:

  // Common Methods

    SS_NEW_OPERATORS(SSActor);

    SSActor(const ASymbol & name = ASymbol::get_null(), SSActorClass * class_p = nullptr, bool add_to_instance_list = true);
    virtual ~SSActor();

  // Accessor Methods


  // Methods

    AString        as_string() const;
    SSActorClass * get_class_actor() const                         { return reinterpret_cast<SSActorClass *>(m_class_p); }
    void           rename(const ASymbol & name);

    // Overriding from SSInstance -> SSDataInstance

      virtual void pool_delete() override;

    // Overriding from SSInstance

       #if defined(SS_AS_STRINGS)
         virtual AString         as_string_debug() const override  { return as_string(); }
         virtual const ASymbol & get_name_debug() const override   { return m_name; }
       #endif

    // Overriding from SSObjectBase

      virtual uint32_t get_obj_type() const override               { return SSObjectType_actor; } 

 // Class Methods

    static AString generate_unique_name_str(const AString & name_root, uint32_t * create_idx_p = nullptr);
    static ASymbol generate_unique_name_sym(const AString & name_root, uint32_t * create_idx_p = nullptr);


 // SkookumScript Atomics

      static void register_bindings();

    // Atomic Methods

      static void mthd_ctor_named(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_name(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_string(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    // Atomic Class Methods

      static void mthdc_find_named(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_generate_name_str(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_generate_name_sym(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_named(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_instances_first(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_instances_length(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_instances(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSActor


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSActor.inl"
#endif


#endif  // __SSACTOR_HPP
