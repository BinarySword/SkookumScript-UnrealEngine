//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Base Object declaration file
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================

#ifndef __SSOBJECTBASE_HPP
#define __SSOBJECTBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AIdPtr.hpp>
#include <AgogCore/ANamed.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
struct SSData;
class  SSInstance;
class  SSInvokedContextBase;

template<class _ObjectType> class AObjBlock;
template<class _ObjectType> class AObjReusePool;

#ifdef A_PLAT_PC
  template<class _ElementType, class _KeyType = _ElementType> class APArrayLogical;
  template<class _ElementType, class _KeyType = _ElementType> class APSortedLogical;
#else
  #include <AgogCore/APArray.hpp>
  #include <AgogCore/APSorted.hpp>
#endif

typedef APSortedLogical<SSData, ASymbol> tSSDataTable;
typedef APArrayLogical<SSData, ASymbol>  tSSDataIdxTable;


//---------------------------------------------------------------------------------------
// Used by SSObjectBase::get_obj_type() which returns uint32_t rather than eSSObjectType so
// that the types can be easily extended when custom types are derived.
enum eSSObjectType
  {
  // SSInstance, SSInstanceUnreffed(used by nil)
  SSObjectType_instance,

  // SSBoolean
  SSObjectType_boolean,

  // SSActor
  SSObjectType_actor,

  // SSMind
  SSObjectType_mind,

  // SSClosure
  SSObjectType_closure,

  // SSMetaClass
  SSObjectType_meta_class,

  // SSInvokedBase(SSInvokedExpression, SSInvokedContextBase(SSInvokedMethod,
  // SSInvokedCoroutine)) - Could split into invoked_expr, invoked_method, invoked_coroutine
  SSObjectType_invoked_obj,

  // Custom object types should be => SSObjectType__custom_start
  SSObjectType__custom_start
  };


//---------------------------------------------------------------------------------------
// SkookumScript Data member (data member, class data member, argument, temporary variable)
struct SSData : public ANamed
  {
  SS_NEW_OPERATORS(SSData);


  friend class AObjBlock<SSData>;

  // Public Data Members

    SSInstance * m_data_p;

  // Class Methods

    static SSData *                pool_new(const ASymbol & name);
    static SSData *                pool_new(const ASymbol & name, SSInstance * instance_p);
    static void                    pool_delete(SSData * data_p);
    static AObjReusePool<SSData> & get_pool();

    static void empty_table(tSSDataTable * table_p);
    static void empty_table(tSSDataIdxTable * table_p);

  protected:

  // Internal Methods

    SSData() {} // Fully initialized by pool_new

  };  // SSData


//---------------------------------------------------------------------------------------
// Root object abstract base class for all Skookum "instances".
//
// #Notes
//   AIdPtr<SSObjectBase> can be used as a smart pointer for this class and any of its
//   subclasses.
//
// #Subclasses
//   SSInstance(SSBoolean, SSClosure, SSDataInstance(SSActor),
//   SSInstanceUnreffed(SSMetaClass)), SSInvokedBase(SSInvokedExpression,
//   SSInvokedContextBase(SSInvokedMethod, SSInvokedCoroutine))
//
// #Author(s) Conan Reis
class SSObjectBase
  {
  public:

    // Public Data Members

      // Pointer id of the object that must match the id in any AIdPtr<SSObjectBase> for it
	  // to be valid.
      uint32_t m_ptr_id;

    // Methods
     
      virtual ~SSObjectBase() {}

      void renew_id()                                  { m_ptr_id = ++ms_ptr_id_prev; }
      bool is_valid_id() const                         { return m_ptr_id && (m_ptr_id <= ms_ptr_id_prev); }

      virtual uint32_t get_obj_type() const = 0;
      virtual bool     is_mind() const                 { return false; }

    // Data methods

      virtual SSInstance *           as_instance() const;
      virtual SSInstance *           get_data_by_name(const ASymbol & name) const = 0;
      virtual void                   set_data_by_name(const ASymbol & name, SSInstance * obj_p) = 0;
      virtual SSInvokedContextBase * get_scope_context() const;
      virtual SSInstance *           get_topmost_scope() const = 0;

    // Class Data

      static uint32_t ms_ptr_id_prev;

  };  // SSObjectBase


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSObjectBase.inl"
#endif


#endif  // __SSOBJECTBASE_HPP

