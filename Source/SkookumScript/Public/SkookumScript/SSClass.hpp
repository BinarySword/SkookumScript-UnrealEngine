//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structures for class descriptors and class objects
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSCLASS_HPP
#define __SSCLASS_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSClassDescBase.hpp"
#include "SkookumScript/SSDataInstance.hpp"
#include "SkookumScript/SSMethod.hpp"
#include "SkookumScript/SSCoroutine.hpp"  // Needs: tSSCoroutineFunc and tSSCoroutineMthd


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
struct SSApplyExpressionBase; 
class  SSBrain;
class  SSClassDescBase;
class  SSInvokedMethod;
class  SSObjectId;
struct SSTypedData;


// Short-hand for arrays
// $Revisit - CReis These arrays will eventually become non-sorted virtual method tables
typedef APSorted<SSClassUnaryBase, SSClassUnaryBase, SSClassUnaryBase> tSSSortedTypes;
typedef APSortedLogical<SSClass, ASymbol>         tSSClasses;
typedef APSortedLogical<SSMethodBase, ASymbol>    tSSMethodTable;
typedef APSortedLogical<SSCoroutineBase, ASymbol> tSSCoroutines;
typedef APSortedLogical<SSTypedName, ASymbol>     tSSTypedNames;
typedef APSortedLogical<SSTypedData, ASymbol>     tSSTypedDatas;


//---------------------------------------------------------------------------------------
// Used when binding a member to a class:
//   SSClass::register_coroutine_func(), SSClass::register_coroutine_mthd(),
//   SSClass::register_method_func(), SSClass::register_method_mthd()
//   
// Enum flags are preferred over bool since it is more descriptive at the point of call.
enum eSSBindFlag
  {
  // Descriptive enumerations - use when passing as a full argument:
  // [Listed before flag enumerations to ensure that they are used as descriptors in the
  // debugger when this enum type has the associated value.]
  
    // Instance member with rebinding disallowed.
    SSBindFlag_instance_no_rebind   = 0x0,  // [Placed as first enum with 0 to ensure that it appears as description in debugger when value is 0.]

    // Class member with rebinding disallowed.
    SSBindFlag_class_no_rebind      = 1 << 0,

    // Instance member with rebinding allowed
    SSBindFlag_instance_rebind      = 1 << 1,

    // Bind as a class member rather than an instance member
    SSBindFlag_class_rebind         = (1 << 0) | (1 << 1),

    // Default binding - instance member and disallow previously bound member to be rebound
    SSBindFlag_default              = SSBindFlag_instance_no_rebind,


  // Flag enumerations - use when dealing with the individual flags:

    // No binding flags set
    SSBindFlag__none        = 0x0,

    // Bind as a class member rather than an instance member
    SSBindFlag__class       = 1 << 0,

    // Bind as an instance member rather than a class member.  [Just used as hint since flag not set.]
    SSBindFlag__instance    = 0x0,

    // Allow previously bound member to be rebound
    SSBindFlag__rebind      = 1 << 1,

    // Disallow previously bound member to be rebound - assert if attempt is made to bind
    // a member that has already been bound.  [Just used as hint since flag not set.]
    SSBindFlag__no_rebind   = 0x0,
  };

//---------------------------------------------------------------------------------------
// SkookumScript MetaClass - i.e. a class treated as an instance using class scope (only
// class methods/data can be used).  It is a wrapper around a `SSClass` object so that a
// class can be treated as an first-order instance object.
//
//   ```
//   meta-class = '<' class-name '>'
//   ```
// $Revisit - CReis Might be good idea to have it be derived from `SSMind` instead of
// `SSInstanceUnreffed`. This would allow instances to use their class as a default
// updater mind rather than the single "master mind".
// 
// Author(s)  Conan Reis
class SSMetaClass : public SSClassUnaryBase, public SSInstanceUnreffed
  {
  friend class SSClass;       // Accesses protected elements
  friend class SSClassUnion;  // Accesses protected elements

  public:

  // Unhide Inherited Methods

    // Methods in this class with the same name as methods in its superclasses are 'hidden'
    // (even if they do not have the same parameters), this makes them visible again.
    // These using directives must precede the new methods in this class.
    using SSInstanceUnreffed::method_call;


  // Common Methods

    SS_NEW_OPERATORS(SSMetaClass);

    explicit SSMetaClass(SSClass * class_info_p = nullptr);

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void as_binary_ref(void ** binary_pp) const;
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
      virtual AString get_scope_desc() const;
    #endif


  // Comparison Methods

    eAEquate compare(const SSMetaClass & mclass) const;

  // Methods

    SSClass & get_class_info() const  { return *m_class_info_p; }

    // Overriding from SSClassUnaryBase & SSClassDescBase

      virtual SSClassDescBase *  as_finalized_generic(const SSClassDescBase & scope_type) const;
      SSClassUnaryBase *         find_common_class(const SSClass & cls) const;
      virtual SSClassUnaryBase * find_common_type(const SSClassDescBase & cls) const;
      virtual eSSClassType       get_class_type() const;
      virtual SSClassDescBase *  get_data_type(const ASymbol & data_name, eSSScope * scope_p = nullptr) const;
      virtual SSClass *          get_key_class() const;
      virtual const ASymbol &    get_key_class_name() const;
      virtual SSMetaClass &      get_metaclass() const;
      virtual bool               is_generic() const;
      virtual bool               is_metaclass() const; 
      virtual bool               is_class_type(const SSClassDescBase * type_p) const;

      // Method Member Methods

        virtual void           append_method(SSMethodBase * method_p);
        virtual SSMethodBase * get_method(const ASymbol & method_name) const;
        virtual SSMethodBase * get_method_inherited(const ASymbol & method_name) const;
        virtual bool           is_method_inherited_valid(const ASymbol & method_name) const;
        virtual bool           is_method_valid(const ASymbol & method_name) const;

      // Coroutine Member Methods

        virtual void              append_coroutine(SSCoroutineBase * coroutine_p);
        virtual SSCoroutineBase * get_coroutine_inherited(const ASymbol & coroutine_name) const  { return nullptr; }
        virtual bool              is_coroutine_registered(const ASymbol & coroutine_name) const  { return false; }
        virtual bool              is_coroutine_valid(const ASymbol & coroutine_name) const       { return false; }

      // Data Member Methods

        virtual SSTypedName * append_data_member(const ASymbol & name, SSClassDescBase * type_p);

    // Overriding from SSInstance

      virtual void method_invoke(const SSMethodCall & mcall, SSObjectBase * scope_p, SSInvokedBase * caller_p, SSInstance ** result_pp);
      virtual void method_call(const ASymbol & method_name, SSInstance ** args_pp, uint32_t arg_count, SSInstance ** result_pp = nullptr, SSInvokedBase * caller_p = nullptr);

      #if defined(SS_AS_STRINGS)
        virtual AString as_string_debug() const;
      #endif


    // Overriding from SSObjectBase

      virtual SSInstance * get_data_by_name(const ASymbol & name) const;
      virtual void         set_data_by_name(const ASymbol & name, SSInstance * obj_p);
      virtual uint32_t     get_obj_type() const       { return SSObjectType_meta_class; } 


  protected:

  // Data Members

    // The class that this instance represents/is wrapped around
    // $Revisit - CReis [Optimization] Consider using m_class_p from SSInstance instead since it will
    // always point to "Class" and not add any useful info.
    SSClass * m_class_info_p;

    // $Revisit - CReis [Optimization] m_ref_count and m_user_data inherited from SSInstance are not used.
    // A SSInstanceBase class could be created that does not have these data members.

  };  // SSMetaClass

//---------------------------------------------------------------------------------------
// Specialization - also ensures that `SSInvokedBase::get_arg<SSMetaClass>(--)` etc. work properly
// 
// See: SSInstance::as<SSClass>
template<> inline SSMetaClass * SSInstance::as<SSMetaClass>() const { return static_cast<SSMetaClass *>(const_cast<SSInstance *>(this)); }


//---------------------------------------------------------------------------------------
// SkookumScript Class - i.e. an instance of a class using class instance scope (both
// instance methods/data and class methods/data can be used).
//
//   class = class-name
//
// Subclasses: SSActorClass
// Author(s):  Conan Reis
class SSClass : public SSClassUnaryBase, public ANamed
  {
  // Accesses protected elements
  friend class SSBrain;
  friend class SSClassUnion;
  friend class SSCompiler;
  friend class SSContextClassBase;
  friend class SSInvokableClass;
  friend class SSMetaClass;
  friend class SSParser;
  friend class SSTypedClass;

  public:

  // Nested Structures

    // AEx<SSClass> exception id values
    enum
      {
      ErrId_nonexistent_method_regd = AErrId_last,  // No such method has been registered
      ErrId_duplicate_coroutine,                    // Coroutine with same name already registered
      ErrId_nonexistent_coroutine,                  // No such coroutine exists
      };

    enum eSubclass
      {
      Subclass_recurse,  // Apply recursively to subclasses
      Subclass_defer     // Do not apply to subclasses - defer it at a later time as a bulk operation
      };

    // Class flags - stored in m_flags
    enum eFlag
      {
      Flag_none             = 0,
      Flag_loaded           = 1 << 0,  // Class has all members loaded
      Flag_demand_load      = 1 << 1,  // Class only loads members when asked to do so
      Flag_demand_load_lock = 1 << 2,  // Once loaded do not allow it to be unloaded
      Flag_demand_unload    = 1 << 3,  // Deferred unload - unload when next possible to do so

      // Object id flags - look-up/validate for this class - i.e. Class@'name'
        Flag_object_id_lookup = 1 << 4,

        // Validation flags - use masks below
          Flag_object_id_parse_any   = 1 << 5,
          Flag_object_id_parse_list  = 1 << 6,
          Flag_object_id_parse_defer = 1 << 7,

        // Object id validation setting (masks):
          // Accept none during compile [used to temporarily disable object ids]
          Flag__id_valid_none  = Flag_none,
          // Accept any during compile
          Flag__id_valid_any   = Flag_object_id_parse_any,
          // Validate using list during compile (include list as compile dependency)
          Flag__id_valid_parse = Flag_object_id_parse_list,
          // Validate using list during compile if it exists (parse) - otherwise accept any during compile and validate using list in separate pass/run (defer)
          Flag__id_valid_exist = Flag_object_id_parse_any | Flag_object_id_parse_list,
          // Accept any during compile and validate using list in separate pass/run
          Flag__id_valid_defer = Flag_object_id_parse_any | Flag_object_id_parse_list | Flag_object_id_parse_defer,

          Flag__id_valid_mask = Flag_object_id_parse_any | Flag_object_id_parse_list | Flag_object_id_parse_defer,

        Flag__id_mask = Flag_object_id_lookup | Flag__id_valid_mask,

      // Defaults and masks
        Flag__default         = Flag_none,
        Flag__default_actor   = Flag__default | Flag_object_id_lookup | Flag_object_id_parse_any,
        Flag__demand_loaded   = Flag_loaded | Flag_demand_load,
        Flag__mask_binary     = Flag_demand_load | Flag__id_mask
      };

  // Public Types

    struct MethodInitializerFunc
      {
      const char *    m_method_name_p;
      tSSMethodFunc   m_atomic_f;
      };

    struct MethodInitializerFuncId
      {
      uint32_t        m_method_name_id;
      tSSMethodFunc   m_atomic_f;
      };
    
    struct MethodInitializerMthd
      {
      const char *    m_method_name_p;
      tSSMethodMthd   m_atomic_m;
      };

    struct MethodInitializerMthdId
      {
      uint32_t        m_method_name_id;
      tSSMethodMthd   m_atomic_m;
      };
    
    struct CoroutineInitializerFunc
      {
      const char *      m_coroutine_name_p;
      tSSCoroutineFunc  m_atomic_f;
      };

    struct CoroutineInitializerFuncId
      {
      uint32_t          m_coroutine_name_id;
      tSSCoroutineFunc  m_atomic_f;
      };

    struct CoroutineInitializerMthd
      {
      const char *      m_coroutine_name_p;
      tSSCoroutineMthd  m_atomic_m;
      };

    struct CoroutineInitializerMthdId
      {
      uint32_t          m_coroutine_name_id;
      tSSCoroutineMthd  m_atomic_m;
      };

    // Public Class Data

    #if (SKOOKUM & SS_DEBUG)
      // Reparse Member Info - placed here rather than in SSCompiler to ensure that it is
      // available for as many build configurations as possible.

      static bool ms_use_reparse_info;

      static APSorted<SSMethodBase, SSQualifier, SSQualifierCompareName>    ms_reparse_methods;
      static APSorted<SSMethodBase, SSQualifier, SSQualifierCompareName>    ms_reparse_class_methods;
      static APSorted<SSCoroutineBase, SSQualifier, SSQualifierCompareName> ms_reparse_coroutines;
      //static APSorted<SSTypedData, SSQualifier, SSQualifierCompareName>     ms_reparse_class_data;
    #endif

  // Common Methods

    SS_NEW_OPERATORS(SSClass);

    explicit SSClass(const ASymbol & name, SSClass * superclass_p = nullptr, uint32_t flags = Flag__default);
    ~SSClass();

  // Converter Methods

    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif


  // Comparison Methods

    eAEquate compare(const SSClass & ssclass) const;      // Hierarchy sort
    eAEquate compare_ids(const SSClass & ssclass) const;  // Standard sort

  // Serialization Methods

    void         enable_demand_load(bool demand_load = true)            { if (demand_load) { m_flags |= Flag_demand_load; } else { m_flags &= ~Flag_demand_load; } }
    virtual bool demand_unload();
    SSClass *    get_demand_loaded_root() const;
    bool         is_demand_loaded() const                               { return (m_flags & Flag_demand_load) || (m_superclass_p && m_superclass_p->is_demand_loaded()); }
    bool         is_demand_loaded_root() const                          { return (m_flags & Flag_demand_load) != 0; }
    bool         is_loaded() const                                      { return (m_flags & Flag_loaded) != 0u; }
    bool         is_load_locked() const                                 { return (m_flags & Flag_demand_load_lock) != 0u; }
    bool         is_unload_deferred() const                             { return (m_flags & Flag_demand_unload) != 0u; }
    void         lock_load(bool lock = true)                            { if (lock) { m_flags |= Flag_demand_load_lock; } else { m_flags &= ~Flag_demand_load_lock; } }
    void         set_flag_load(bool loaded = true);
    void         set_loaded()                                           { set_flag_load(); }

    void                 enable_object_id_lookup(bool enable = true);
    bool                 is_object_id_lookup() const                    { return (m_flags & Flag_object_id_lookup) != 0u; }
    void                 set_object_id_lookup_func(SSInstance * (* object_id_lookup_f)(SSObjectId * obj_id_p));
    virtual SSInstance * object_id_lookup(SSObjectId * obj_id_p) const;

    #if (SKOOKUM & SS_CODE_IN)
      void              clear_object_id_valid_list();
      uint32_t          get_object_id_validate() const                  { return m_flags & Flag__id_valid_mask; }
      ASymbolTable *    get_object_id_valid_list() const                { return m_object_ids_p; }
      ASymbolTable *    get_object_id_valid_list_merge();
      void              set_object_id_validate(uint32_t validate_mask = Flag__id_valid_any);
      virtual SSClass * object_id_validate(SSObjectId * obj_id_p, bool validate_deferred = true) const;

      #if (SKOOKUM & SS_DEBUG)
        uint32_t        object_id_validate_recurse(bool validate_deferred, uint32_t * obj_id_count_p = nullptr);
      #endif
    #endif

    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void     as_binary(void ** binary_pp) const;
      virtual uint32_t as_binary_length() const;
      void             as_binary_recurse(void ** binary_pp, bool skip_demand_loaded) const;
      uint32_t         as_binary_recurse_length(bool skip_demand_loaded) const;
      void             as_binary_group(void ** binary_pp, bool skip_demand_loaded) const;
      uint32_t         as_binary_group_length(bool skip_demand_loaded) const;
      void             as_binary_placeholder_recurse(void ** binary_pp) const;
      static uint32_t  as_binary_placeholder_recurse_length_all();
      virtual void     as_binary_ref(void ** binary_pp) const;
    #endif


    #if (SKOOKUM & SS_COMPILED_IN)
      virtual void     assign_binary(const void ** binary_pp, bool append_super_members = true);
      static SSClass * from_binary_ref(const void ** binary_pp);
      static void      from_binary_group(const void ** binary_pp);
    #endif

    #if (SKOOKUM & SS_DEBUG)
      void         ensure_loaded_debug();
      virtual void reparse_prep();

      uint32_t        count_expressions_recurse(eAHierarchy hierarchy = AHierarchy__all);
      eAIterateResult iterate_expressions(SSApplyExpressionBase * apply_expr_p);
      eAIterateResult iterate_expressions_recurse(SSApplyExpressionBase * apply_expr_p, eAHierarchy hierarchy = AHierarchy__all);
    #endif

  // Methods

    virtual SSMetaClass & get_metaclass() const;

    uint32_t     get_flags() const                                      { return m_flags; }

    virtual void clear_members();
    virtual void clear_members_compact();

    virtual void track_memory(AMemoryStats * mem_stats_p, bool skip_demand_loaded) const;
    virtual void track_memory(AMemoryStats * mem_stats_p) const         { track_memory(mem_stats_p, true); }
    void         track_memory_recursive(AMemoryStats * mem_stats_p, bool skip_demand_loaded) const;


    // Hierarchy Methods

      void                       append_subclass(SSClass * subclass_p);
      SSClass *                  find_common_class(const SSClass & cls) const;
      virtual SSClassUnaryBase * find_common_type(const SSClassDescBase & cls) const;
      uint32_t                   get_class_recurse_count(bool skip_demand_loaded) const;
      tSSClasses &               get_subclasses()                       { return m_subclasses; }
      const tSSClasses &         get_subclasses() const                 { return m_subclasses; }
      void                       get_subclasses_all(tSSClasses * classes_p) const;
      SSClass *                  get_superclass() const                 { return m_superclass_p; }
      void                       get_superclasses_all(tSSClasses * classes_p) const;
      uint32_t                   get_superclass_depth() const;
      SSClass *                  get_class_depth_at(uint32_t depth) const;
      bool                       is_class(const SSClass & cls) const;
      bool                       is_subclass(const SSClass & superclass) const;
      bool                       is_superclass(const SSClass & subclass) const;
      bool                       is_scope_qualifier(SSClassDescBase * recv_type_p) const;
      eAIterateResult            iterate_recurse(AFunctionArgRtnBase<SSClass *, eAIterateResult> * apply_class_p, eAHierarchy hierarchy = AHierarchy__all);
      void                       iterate_recurse(AFunctionArgBase<SSClass *> * apply_class_p, eAHierarchy hierarchy = AHierarchy__all);
      SSClass *                  next_class(SSClass * root_p) const;
      SSClass *                  next_sibling() const;


    // Method Methods

      // Instance & Class Methods

        virtual void           append_method(SSMethodBase * method_p);
        virtual SSMethodBase * get_method(const ASymbol & method_name) const;
        virtual SSMethodBase * get_method_inherited(const ASymbol & method_name) const;
        SSMethodBase *         get_method_inherited_receiver(const ASymbol & method_name, SSInstance ** receiver_pp, SSInvokedBase * caller_p) const;
        virtual bool           is_method_valid(const ASymbol & method_name) const;
        virtual bool           is_method_inherited_valid(const ASymbol & method_name) const;
        void                   register_method_func(const ASymbol & method_name, tSSMethodFunc atomic_f, eSSBindFlag flags = SSBindFlag_default);
        void                   register_method_func(const char * method_name_p, tSSMethodFunc atomic_f, eSSBindFlag flags = SSBindFlag_default);
        void                   register_method_mthd(const ASymbol & method_name, tSSMethodMthd atomic_m, eSSBindFlag flags = SSBindFlag_default);
        void                   register_method_mthd(const char * method_name_p, tSSMethodMthd atomic_m, eSSBindFlag flags = SSBindFlag_default);
        void                   register_method_func_bulk(const MethodInitializerFunc   * bindings_p, uint32_t count, eSSBindFlag flags);
        void                   register_method_func_bulk(const MethodInitializerFuncId * bindings_p, uint32_t count, eSSBindFlag flags);
        void                   register_method_mthd_bulk(const MethodInitializerMthd   * bindings_p, uint32_t count, eSSBindFlag flags);
        void                   register_method_mthd_bulk(const MethodInitializerMthdId * bindings_p, uint32_t count, eSSBindFlag flags);

      // Instance Methods

        void                   append_instance_method(SSMethodBase * method_p);
        SSMethodBase *         get_instance_destructor_inherited() const                     { return m_destructor_p; }
        SSMethodBase *         get_instance_method(const ASymbol & method_name) const        { return m_methods.get(method_name); }
        SSMethodBase *         get_instance_method_inherited(const ASymbol & method_name) const;
        SSMethodBase *         get_instance_method_overridden(const ASymbol & method_name) const;
        SSMethodBase *         get_instance_method_scoped_inherited(const SSQualifier & method_qual) const;
        const tSSMethodTable & get_instance_methods() const                                  { return m_methods; }
        bool                   is_instance_method_valid(const ASymbol & method_name) const   { return (m_methods.get(method_name) != nullptr); }
        virtual SSInstance *   new_instance();

      // Class Methods

        void                   append_class_method(SSMethodBase * method_p);
        SSMethodBase *         get_class_method(const ASymbol & method_name) const                  { return m_class_methods.get(method_name); }
        SSMethodBase *         get_class_method_inherited(const ASymbol & method_name) const;
        SSMethodBase *         get_class_method_overridden(const ASymbol & method_name) const;
        const tSSMethodTable & get_class_methods() const                                            { return m_class_methods; }
        void                   invoke_class_ctor();
        void                   invoke_class_ctor_recurse();
        void                   invoke_class_dtor_recurse();
        bool                   is_class_method_valid(const ASymbol & method_name) const             { return (m_class_methods.get(method_name) != nullptr); }
        bool                   is_class_method_inherited_valid(const ASymbol & method_name) const   { return (get_class_method_inherited(method_name) != nullptr); }

    // Coroutine Methods

      virtual void         append_coroutine(SSCoroutineBase * coroutine_p);
      SSCoroutineBase *    get_coroutine(const ASymbol & coroutine_name) const       { return m_coroutines.get(coroutine_name); }
      SSCoroutineBase *    get_coroutine_inherited(const ASymbol & coroutine_name) const;
      SSCoroutineBase *    get_coroutine_overridden(const ASymbol & coroutine_name) const;
      SSCoroutineBase *    get_coroutine_scoped_inherited(const SSQualifier & coroutine_qual) const;
      virtual bool         is_coroutine_registered(const ASymbol & coroutine_name) const;
      virtual bool         is_coroutine_valid(const ASymbol & coroutine_name) const  { return m_coroutines.find(coroutine_name); }
      void                 register_coroutine_func(const ASymbol & coroutine_name, tSSCoroutineFunc update_f, eSSBindFlag flags = SSBindFlag_default);
      void                 register_coroutine_func(const char * coroutine_name_p, tSSCoroutineFunc update_f, eSSBindFlag flags = SSBindFlag_default);
      void                 register_coroutine_mthd(const ASymbol & coroutine_name, tSSCoroutineMthd update_m, eSSBindFlag flags = SSBindFlag_default);
      void                 register_coroutine_mthd(const char * coroutine_name_p, tSSCoroutineMthd update_m, eSSBindFlag flags = SSBindFlag_default);
      void                 register_coroutine_func_bulk(const CoroutineInitializerFunc   * bindings_p, uint32_t count, eSSBindFlag flags);
      void                 register_coroutine_func_bulk(const CoroutineInitializerFuncId * bindings_p, uint32_t count, eSSBindFlag flags);
      void                 register_coroutine_mthd_bulk(const CoroutineInitializerMthd   * bindings_p, uint32_t count, eSSBindFlag flags);
      void                 register_coroutine_mthd_bulk(const CoroutineInitializerMthdId * bindings_p, uint32_t count, eSSBindFlag flags);
      bool                 remove_coroutine(const ASymbol & coroutine_name)          { return m_coroutines.free(coroutine_name); }
      const tSSCoroutines & get_coroutines() const                                   { return m_coroutines; }

    // Data Methods

      virtual SSTypedName *     append_data_member(const ASymbol & name, SSClassDescBase * type_p);
      virtual SSClassDescBase * get_data_type(const ASymbol & data_name, eSSScope * scope_p = nullptr) const;

      // Instance Methods

        SSTypedName *         append_instance_data(const ASymbol & name, SSClassDescBase * type_p, eSubclass subclasses = Subclass_recurse);
        const tSSTypedNames & get_instance_data() const        { return m_data; }
        const tSSTypedNames & get_instance_data_table() const  { return m_data_table; }
        void                  remove_instance_data_all();

        #if (SKOOKUM & SS_COMPILED_IN)
          SSClass * find_instance_data_scope(const ASymbol & name, ePath check_path = Path_super_sub);
        #endif

      // Class Methods

        SSTypedName *         append_class_data(const ASymbol & name, SSClassDescBase * type_p, eSubclass subclasses = Subclass_recurse);
        void                  fill_class_data_names(APSortedLogical<ASymbol> * target_p);
        const tSSTypedDatas & get_class_data() const        { return m_class_data; }
        const tSSTypedDatas & get_class_data_table() const  { return m_class_data_table; }
        void                  remove_class_data_all();

        #if (SKOOKUM & SS_COMPILED_IN)
          SSClass * find_class_data_scope(const ASymbol & name, ePath check_path = Path_super_sub);
        #endif

    // Overriding from SSClassDescBase

      virtual SSClassDescBase * as_finalized_generic(const SSClassDescBase & scope_type) const;
      virtual eSSClassType      get_class_type() const;
      virtual SSClassDescBase * get_item_type() const;
      virtual const ASymbol &   get_key_class_name() const;
      virtual bool              is_class_type(const SSClassDescBase * type_p) const;
      virtual bool              is_generic() const;
      virtual bool              is_method_registered(const ASymbol & method_name) const;

    // Overriding from SSClassUnaryBase

      virtual SSClass * get_key_class() const;

  protected:

  // Internal Methods

    void         recurse_instance_data(const SSTypedName * typed_p);
    void         recurse_remove_instance_data_all(const tSSTypedNames & data);
    void         recurse_remove_class_data_all(const tSSTypedDatas & data);
    void         recurse_class_data(const SSTypedData * data_p);
    virtual void recurse_class_ctor(SSInvokedMethod * imethod_p);
    void         recurse_class_dtor();
    void         demand_unload_recurse();
    void         set_destructor(SSMethodBase * destructor_p);

  // Internal Class Methods

    // SkookumScript Atomic Methods

      #if (SKOOKUM & SS_DEBUG)
        virtual void find_unregistered_atomics(APArray<SSInvokableBase> * atomics_p);
      #endif


  // Data Members

    // Class Flags - see eFlags
    uint32_t m_flags;

    // Parent of this class [Single inheritance only - at least in first pass]
    SSClass * m_superclass_p;

    // Child classes of this class
    tSSClasses m_subclasses;

    // Used to lookup named instance objects via object id expressions.  See object_id_lookup()
    SSInstance * (* m_object_id_lookup_f)(SSObjectId * obj_id_p);

    // Used to validate object ids for this class.
    // $Revisit - CReis Since there are few classes that use object ids it might be an idea
    // to store only the symbol tables for classes that actually use them rather than
    // taking up 4/8 bytes for every class whether they use object ids or not.
    ASymbolTable * m_object_ids_p;

    // $Revisit - CReis [Index Look-up] Rewrite the data and method tables so that a direct
    // index can be used rather than a binary search of the symbols.

    // Instance Member Info

      // Data Members (name and class type) for instances of this class - added via this
      // class directly.  Each data member name must be unique - no superclass nor subclass
      // may have it and there should be no class data member with the same name either
      // - this is enforced by the compiler.
      // m_data_table references this and inherited members for constructing instances of
      // this class.
      tSSTypedNames m_data;

      // Data Members (name and class type) for instances of this class including data
      // members inherited from all its superclasses for quick construction / instantiation.
      tSSTypedNames m_data_table;

      // Methods of this class - added via this class directly.
      tSSMethodTable m_methods;

      // Shortcut to instance destructor
      SSMethodBase * m_destructor_p;

      // List of available coroutines
      tSSCoroutines m_coroutines;

      // Coroutines of this class and all its superclasses for quick look-ups
      //tSSCoroutines m_coroutine_table;

    // Class Member Info

      // Class Data Members (name, class type and data) for this class - added via this
      // class directly.  Each class data member name must be unique - no superclass nor
      // subclass/ may have it and there should be no instance data member with the same
      // name either - this is enforced by the compiler.
      // m_class_data_table is used for class data look-ups.
      tSSTypedDatas m_class_data;

      // Class Data Members (name and class type) for this class including data members
      // inherited from all its superclasses for quick look-ups.
      // $Note - CReis [Optimization] Currently this does not include indirect data members from "Class".
      tSSTypedDatas m_class_data_table;

      // Class Methods of this class - added via this class directly.
      tSSMethodTable m_class_methods;

      // Class Methods of this class including data members inherited from all its
      // superclasses for quick look-ups.
      //tSSMethodTable m_class_method_table;

    // Wrappers - for quick access and no need to allocate memory

      // Metaclass wrapper for this class
      SSMetaClass m_metaclass;

  };  // SSClass


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Union between 2 or more classes - i.e. instance classes and
//            meta classes (SSClassUnaryBase -> SSClass & SSMetaClass).  Used as a type
//            descriptor to denote an instance that could be one of several different
//            types.  The class type "None" (nil) in particular is often paired with
//            other types.
//
//              class-union    = '<' class-unary {'|' class-unary}1+ '>'
//              class-unary    = class-instance | meta-class
//              class-instance = class | list-class
//              class          = class-name
//              list-class     = List ['{' ws [class-desc ws] '}']
//              meta-class     = '<' class-name '>'
//
// ToDo
//   - merge superclasses with subclasses (and same classes)
//   - disallow "unions" that merge down to one class - use MetaClass instead
//   - sort list of unioned classes alphabetically
//   - have global sorted list of already created unions
//   - derive from ARefCount and have all references to a SSDescBase increment and decrement
//     - potentially make a SSClassDescRef that does this automatically
//
// Author(s)  Conan Reis
class SSClassUnion : public SSClassDescBase, public ARefCountMix<SSClassUnion>
  {
  // Accesses protected elements
  friend class SSBrain;       
  friend class SSClass;
  friend class SSTypedClass;
  friend class SSInvokableClass;
  friend class SSMetaClass;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSClassUnion);

    SSClassUnion()                                                : m_common_class_p(nullptr) {}
    explicit SSClassUnion(const SSClassUnaryBase & initial_class) : m_common_class_p(const_cast<SSClassUnaryBase *>(&initial_class)) { initial_class.reference(); initial_class.reference(); m_union.append(initial_class); }
    explicit SSClassUnion(const SSClassDescBase & initial_class)  : m_common_class_p(nullptr) { merge_class(initial_class); }
    SSClassUnion(const SSClassUnion & class_union);
    virtual ~SSClassUnion();
    
    SSClassUnion & operator=(const SSClassUnion & class_union);

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_OUT)
      void         as_binary(void ** binary_pp) const;
      uint32_t     as_binary_length() const;
      virtual void as_binary_ref(void ** binary_pp) const;
      virtual uint32_t as_binary_ref_typed_length() const;
    #endif


    #if (SKOOKUM & SS_COMPILED_IN)
      SSClassUnion(const void ** binary_pp)                       : m_common_class_p(nullptr) { assign_binary(binary_pp); }
      void                  assign_binary(const void ** binary_pp);
      static SSClassUnion * from_binary_ref(const void ** binary_pp);
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const;
    #endif

  // Comparison Methods

    eAEquate compare(const SSClassUnion & class_union) const;
    bool     operator==(const SSClassUnion & class_union) const  { return compare(class_union) == AEquate_equal; }
    bool     operator<(const SSClassUnion & class_union) const   { return compare(class_union) == AEquate_less; }
    bool     operator>(const SSClassUnion & class_union) const   { return compare(class_union) == AEquate_greater; }
    bool     operator!=(const SSClassUnion & class_union) const  { return compare(class_union) != AEquate_equal; }
    bool     operator<=(const SSClassUnion & class_union) const  { return compare(class_union) != AEquate_greater; }
    bool     operator>=(const SSClassUnion & class_union) const  { return compare(class_union) != AEquate_less; }

  // Methods

    // Type-checking Methods

      virtual const SSClassUnaryBase * as_unary_class() const         { return m_common_class_p; }
      virtual SSClassUnaryBase *       as_unary_class()               { return m_common_class_p; }
      SSClassUnaryBase *               get_common_class() const       { return m_common_class_p; }
      void                             set_common_class(SSClassUnaryBase * class_p);
      virtual bool                     is_builtin_actor_class() const;
      bool                             is_class_maybe(const SSClassDescBase * type_p) const;
      bool                             is_valid_param_for(const SSClassDescBase * arg_type_p) const;
      virtual bool                     is_metaclass() const; 
      bool                             is_trivial() const             { return (m_union.get_length() <= 1u); }
      void                             merge_class(const SSClassUnaryBase & new_class);
      void                             merge_class(const SSClassDescBase & new_class);

    // Overriding from SSClassUnaryBase, SSClassDescBase, ARefCountMix<>

      virtual void reference() const;
      virtual void dereference();
      virtual void dereference_delay() const;
      void         on_no_references();

      virtual SSClassDescBase *  as_finalized_generic(const SSClassDescBase & scope_type) const;
      virtual SSClassUnaryBase * find_common_type(const SSClassDescBase & cls) const;
      virtual eSSClassType       get_class_type() const;
      virtual SSClassDescBase *  get_data_type(const ASymbol & data_name, eSSScope * scope_p = nullptr) const;
      virtual SSClassDescBase *  get_item_type() const;
      virtual SSClass *          get_key_class() const;
      virtual const ASymbol &    get_key_class_name() const;
      virtual SSMetaClass &      get_metaclass() const;
      virtual bool               is_class_type(const SSClassDescBase * type_p) const;
      virtual bool               is_generic() const;

      // Method Member Methods

        virtual SSMethodBase * get_method(const ASymbol & method_name) const;
        virtual SSMethodBase * get_method_inherited(const ASymbol & method_name) const;
        virtual bool           is_method_inherited_valid(const ASymbol & method_name) const;

      // Coroutine Member Methods

        virtual SSCoroutineBase * get_coroutine_inherited(const ASymbol & coroutine_name) const;

  // Class Methods

    static SSClassUnion *    get_or_create(const SSClassUnion & class_union);
    static SSClassDescBase * get_merge(const SSClassDescBase & class1, const SSClassDescBase & class2);
    static SSClassDescBase * get_merge(const APArrayBase<SSClassDescBase> & classes, bool object_on_empty_b = true);
    static SSClassDescBase * get_reduced(const SSClassUnion & class_union, const SSClassUnaryBase & class_to_remove);
    static void              shared_empty()               { ms_shared_unions.free_all(); }  
    static void              shared_ensure_references();
    static void              shared_track_memory(AMemoryStats * mem_stats_p);

  protected:

  // Internal Methods

    void clear();

  // Data Members

    // [Cached] Most specific superclass common to all classes in this union.
    SSClassUnaryBase * m_common_class_p;

    // Sorted list of classes in this union - there will always be more than one and they
    // will never be direct descendants of one another - i.e. none of the classes are
    // super-classes or sub-classes to any of the other classes in the union.
    tSSSortedTypes m_union;

  // Class Data Members

    // Class union objects that are shared amongst various data-structures
    static APSortedLogicalFree<SSClassUnion> ms_shared_unions;

  };  // SSClassUnion


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specialization - SSMetaClass stored indirectly as pointer in SSUserData rather than whole structure
template<> inline SSMetaClass * SSUserDataBase::as<SSMetaClass>() const                { return *as_stored<SSMetaClass*>(); }
template<> inline void          SSUserDataBase::set(SSMetaClass const * const & value) { *as_stored<const SSMetaClass*>() = value; }
template<> inline void          SSUserDataBase::set(SSMetaClass       * const & value) { *as_stored<SSMetaClass*>() = value; }


#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSClass.inl"
#endif


#endif  // __SSCLASS_HPP

