//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Base classes for executed/called/invoked objects declaration file
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSINVOKEDBASE_HPP
#define __SSINVOKEDBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <new>  // For placement new
#include <AgogCore/APArray.hpp>
#include <AgogCore/AList.hpp>
#include "SkookumScript/SSInstance.hpp"
#include "SkookumScript/SSSymbol.hpp"
#include "SkookumScript/SSDebug.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declaration
class SSClass;
class SSExpressionBase;
class SSIdentifier;
class SSInvokableBase;
class SSInvokeBase;
class SSInvokedMethod;
class SSList;
enum eSSMember;

class SSInvokedCoroutine;  // For circular reference


// Used when specifying an argument by index - a simple integer could be used, but these
// give a bit more context
enum eSSArgNum
  {
  SSArg_1 = 0,
  SSArg_2,
  SSArg_3,
  SSArg_4,
  SSArg_5,
  SSArg_6,
  SSArg_7,
  SSArg_8,
  SSArg_9,
  SSArg_10,
  SSArg_11,
  SSArg_12,
  SSArg_13,
  SSArg_14,
  SSArg_15,
  SSArg_16,
  SSArg_17,
  SSArg_18,
  SSArg_19,
  SSArg_20,
  };

// Used with abort commands
enum eSSNotify
  {
  SSNotify_ignore   = 0x0,  // Caller is not notified
  SSNotify_fail     = 0x1,  // Caller notified that this sub-expression did not successfully complete
  SSNotify_success  = 0x3   // Caller notified that this sub-expression successfully completed
  };

// Used with abort commands - also see eSSNotify 
enum eSSNotifyChild
  {
  SSNotifyChild_detach  = 0x0,  // Child/sub calls ignore the fact that their caller is being aborted
  SSNotifyChild_abort   = 0x1   // Abort child/sub calls
  };


//---------------------------------------------------------------------------------------
// Notes      Invoked Object Abstract Base Class
// Subclasses SSInvokedExpression, SSInvokedContextBase
// Author(s)  Conan Reis
class SSInvokedBase : public SSObjectBase, public AListNode<SSInvokedBase>
  {
  public:

  // Public Data Members

    // Path for data look-ups (the owner)
    AIdPtr<SSObjectBase> m_scope_p;

    // Object that invoked / called this invokable and expects to be returned to on the
    // completion of this invokable.  Essentially the call-stack *parent* of this object.
    // nullptr if there is nothing to return to.
    // $Revisit - CReis Now that invoked objects have a list of sub-calls, each sub-called
    // could be notified if its caller went out of scope and thus set this to nullptr - in
    // which case this would not need to be a smart pointer.  Though SSConcurrentBranch
    // might complicate things.
    AIdPtr<SSInvokedBase> m_caller_p;
    
    // Invoked objects that this invoked object has called/created.  Essentially the
    // call-stack *children* of this object.
    // [Needed for SSConcurrentRace, abort_subcalls() & detach_subcalls().]
    AList<SSInvokedBase> m_calls;


  // Common Methods

    SSInvokedBase(SSInvokedBase * caller_p = nullptr, SSObjectBase * scope_p = nullptr);
    ~SSInvokedBase();


  // Methods

    SSInvokedBase * get_caller() const                    { return m_caller_p; }
    SSObjectBase *  get_scope() const                     { return m_scope_p; }
    void            set_caller(SSInvokedBase * caller_p)  { m_caller_p = caller_p; }

    virtual SSInvokedContextBase *   get_caller_context() const;
    virtual const SSExpressionBase * get_expr() const     { return nullptr; }
    virtual SSMind *                 get_updater() const;
    uint32_t                         get_context_depth() const;
    bool                             is_caller(SSInvokedBase * caller_p) const;

    #if (SKOOKUM & SS_DEBUG)

      virtual SSExpressionBase * get_caller_expr() const = 0;
      virtual SSDebugInfo        get_debug_info() const = 0;
      virtual bool               is_in_use() const        { return is_valid_id(); }

      AString list_callstack_debug(uint32_t stack_flags = SSInvokeInfo__callstack_def) const;

    #endif

    // Pending Methods

      virtual void abort_invoke(eSSNotify notify_caller = SSNotify_fail, eSSNotifyChild notify_child = SSNotifyChild_abort) = 0;
      void         abort_subcalls(eSSNotify notify_caller = SSNotify_success);
      void         detach(eSSNotify notify_caller = SSNotify_success);
      void         detach_subcalls(eSSNotify notify_caller = SSNotify_success);
      uint32_t     pending_count() const                  { return m_pending_count; }
      void         pending_increment()                    { m_pending_count++; }
      void         pending_increment(uint32_t increment)      { m_pending_count += increment; }
      void         pending_set(uint32_t pending)              { m_pending_count = pending; }
      void         pending_clear()                        { m_pending_count = 0u; }  // Used by concurrent branch
      void         pending_deferred(SSInvokedBase * deferred_p);
      void         pending_unregister(SSInvokedBase * pending_p, bool completed = true);
      virtual void pending_return(bool completed = true) = 0;
    
    // Overriding from SSObjectBase

      virtual SSInstance *           get_data_by_name(const ASymbol & name) const;
      virtual uint32_t               get_obj_type() const { return SSObjectType_invoked_obj; } 
      virtual SSInvokedContextBase * get_scope_context() const;
      virtual SSInstance *           get_topmost_scope() const;
      virtual void                   set_data_by_name(const ASymbol & name, SSInstance * obj_p);

    // SkookumScript Atomic Methods

      static void register_bindings();
    
      static void mthd_abort(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_abort_subcalls(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_detach(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_detach_subcalls(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_data_by_name(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_pending_increment(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_pending_count(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_pending_decrement(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_data_by_name_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_validQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  protected:

    // Internal Methods

      void abort_common(eSSNotify notify_caller, eSSNotifyChild notify_child);

  // Data Members

    // Number of expressions / tasks currently executing concurrently that the invoked
    // object is waiting for a return value from.
    uint32_t m_pending_count;

  };  // SSInvokedBase


//---------------------------------------------------------------------------------------
// Notes      Invoked Object to wrap around expressions that may not evaluate immediately
//            - i.e. they take more than one frame to complete their invocation.  This
//            currently includes the expressions SSCode, SSLoop, SSConcurrentRace and
//            SSInvokeCascade.
// Author(s)  Conan Reis
class SSInvokedExpression : public SSInvokedBase
  {
  public:

  // Public Data

    // Index position in multi-part expression
    uint32_t m_index;

    // Optional extra data - when wrapped around a SSInvokeCascade object, it is the
    // receiver instance object (SSInstance *).
    uintptr_t m_data;

  // Common Methods

    SS_NEW_OPERATORS(SSInvokedExpression);

    SSInvokedExpression(const SSExpressionBase & expr, SSInvokedBase * caller_p = nullptr, SSObjectBase * scope_p = nullptr) : SSInvokedBase(caller_p, scope_p), m_index(0u), m_expr_p(&expr) {}

  // Methods

    // Overriding from SSInvokedBase

    virtual void abort_invoke(eSSNotify notify_caller = SSNotify_fail, eSSNotifyChild notify_child = SSNotifyChild_abort);
    virtual void pending_return(bool completed = true);
    
    virtual const SSExpressionBase * get_expr() const       { return m_expr_p; }
    virtual SSMind *                 get_updater() const override;

    #if (SKOOKUM & SS_DEBUG)

      virtual SSExpressionBase * get_caller_expr() const;
      virtual SSDebugInfo        get_debug_info() const;

    #endif

  // Class Methods

    static void                  pool_delete(SSInvokedExpression * iexpr_p);
    static SSInvokedExpression * pool_new(const SSExpressionBase & expr, SSInvokedBase * caller_p, SSObjectBase * scope_p);
    static AObjReusePool<SSInvokedExpression> & get_pool();

  protected:

  // Internal Methods

    friend class AObjBlock<SSInvokedExpression>;  // So constructor can only be accessed by pool_new()

    SSInvokedExpression() {}  // Intentionally uninitialized for pool

  // Data Members

    // The expression that is being invoked
    const SSExpressionBase * m_expr_p;

  };  // SSInvokedExpression


//---------------------------------------------------------------------------------------
// Notes      Invoked Object with Context (temporary variables) Abstract Base Class
//            The 'm_scope_p' member will always be an object derived from SSInstanceBase
// Subclasses SSInvokedMethod, SSInvokedCoroutine
// Author(s)  Conan Reis
class SSInvokedContextBase : public SSInvokedBase
  {
  public:

    // Public Data

    #if (SKOOKUM & SS_DEBUG)

      // Copied from the expression that invoked this method/coroutine - see SSExpressionBase.

      // Debug:  Source character index position where this expression starts in the 
      // originally parsed code file/string.  m_debug_info describes the source code origin.
      uint16_t m_source_idx; 

      // Debug: Debug flags & misc. info - such as breakpoint set flag - see SSDebug::eInfo
      uint16_t m_debug_info;

    #endif

    #if defined(SSDEBUG_HOOKS)
      // Last expression about to invoke a method/coroutine - passed globally (yuck!) to
      // avoid different parameters for debug/non-debug.
      static const SSExpressionBase * ms_last_expr_p;
    #endif


  // Common Methods

    
    SSInvokedContextBase(SSInvokedBase * caller_p = nullptr, SSObjectBase * scope_p = nullptr) : SSInvokedBase(caller_p, scope_p) {}

  // Methods

    SSInstance *              get_this();
    virtual eSSMember         get_invoke_type() const = 0;
    virtual SSInvokableBase * get_invokable() const = 0;

    template <typename _UserType>
      _UserType * this_as() const;

    template <typename _UserType>
      void this_set(const _UserType & value);

#if (SKOOKUM & SS_DEBUG)
      virtual SSExpressionBase * get_caller_expr() const;
      virtual SSDebugInfo        get_debug_info() const;
    #endif

    #if defined(SS_AS_STRINGS)
      AString         as_invoke_string(uint32_t flags = SSInvokeInfo_scope) const;
      virtual AString as_string_debug() const = 0;
    #endif


    // Data Context Methods (for manipulating the 'temporary variable stack')

      // See eSSArgNum earlier in the file

      SSInstance *   get_arg(uint32_t pos) const                           { return m_data.get_at(pos)->m_data_p; }
      SSInstance *   get_arg_by_name(const ASymbol & name) const           { return m_data.get(name)->m_data_p; }

      template <typename _UserType>
      _UserType *    get_arg(uint32_t pos) const;

      void           set_arg(uint32_t pos, SSInstance * obj_p);
      void           set_arg_and_ref(uint32_t pos, SSInstance * obj_p);

      template <typename _UserType>
      void           set_arg(uint32_t pos, _UserType value);

      const tSSDataIdxTable & get_data() const                             { return m_data; }

      template <typename _UserType, typename... _ParamClasses>
        _UserType * append_user_data(_ParamClasses&... args);

      template <typename _UserType>
        _UserType * get_user_data() const;
    
      void data_append_args_exprs(const APArrayBase<SSExpressionBase> & args, const SSInvokableBase & invokable_params, SSObjectBase * arg_scope_p);
      void data_append_args(SSInstance ** arguments_pp, uint32_t arg_count, const SSInvokableBase & invokable_params);
      void data_append_arg(const ASymbol & param_name, SSInstance * arg_p) { m_data.append(*SSData::pool_new(param_name, arg_p)); }
      void data_append_vars(const AVCompactArrayBase<ASymbol> & var_names);
      void data_bind_return_args(const APArrayBase<SSIdentifier> & return_args, const SSInvokableBase & invokable_params);
      void data_remove_vars(const AVCompactArrayBase<ASymbol> & var_names, SSInstance * delay_collect_p);
      void data_remove_vars(uint32_t count, SSInstance * delay_collect_p);
      void data_append_var(const ASymbol & var_name);
      void data_empty()                                                    { SSData::empty_table(&m_data); }
      void data_empty_compact()                                            { SSData::empty_table(&m_data); m_data.empty_compact(); }
      void data_compact()                                                  { m_data.compact(); }

    // Overriding from SSObjectBase -> SSInvokedBase

      virtual SSInvokedContextBase * get_caller_context() const;
      virtual SSInvokedContextBase * get_scope_context() const;
      virtual SSInstance *           get_data_by_name(const ASymbol & name) const;
      virtual void                   set_data_by_name(const ASymbol & name, SSInstance * obj_p);

  protected:

  // Data Members

    // Array of arguments and temporary variables - accessed directly by index or found
    // by symbol name.
    // $Revisit - CReis [Index Look-up] To save data wrangling when more code accesses data
    // by index, the instances could be stored directly without a name.  If a named
    // look-up is needed then the parameter descriptor could be referenced.
    tSSDataIdxTable m_data;

  };  // SSInvokedContextBase

//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specialization - SSInvokedBase stored indirectly as pointer in SSUserData rather than whole structure
template<> inline SSInvokedBase * SSUserDataBase::as<SSInvokedBase>() const { return as_stored<AIdPtr<SSInvokedBase>>()->get_obj(); }

//---------------------------------------------------------------------------------------
// Storage specialization - SSInvokedContextBase stored indirectly as pointer in SSUserData rather than whole structure
template<> inline SSInvokedContextBase * SSUserDataBase::as<SSInvokedContextBase>() const { return static_cast<SSInvokedContextBase *>(as_stored<AIdPtr<SSInvokedBase>>()->get_obj()); }

//---------------------------------------------------------------------------------------
// Gets the receiver scope object / "this" of this invoked object and and returns it as
// desired type.
// 
// Does any casting etc. that is necessary from SSInstance to the type requested.
// 
// # Examples:
//   // Get the pointer back from an AString
//   AString * str_p = obj_p->this_as<AString>()
//    
// # Author(s): Conan Reis
template <typename _UserType>
inline _UserType * SSInvokedContextBase::this_as() const
  {
  const SSInstance * instance_p = static_cast<const SSInstance *>(m_scope_p.get_obj());
  return instance_p->as<_UserType>();
  }

//---------------------------------------------------------------------------------------
// Sets user data of this object
//
template <typename _UserType>
inline void SSInvokedContextBase::this_set(const _UserType & value)
  {
  SSInstance * instance_p = static_cast<SSInstance *>(m_scope_p.get_obj());
  instance_p->set(value);
  }

//---------------------------------------------------------------------------------------
// Get argument at specified index and return it as desired type.
// 
// Does any casting etc. that is necessary from SSInstance to the type requested.
// 
// # Params:
//   idx: index position of parameter to retrieve
//
// # Examples:
//   // Get the pointer back from an AString
//   AString * str_p = scope_p->get_arg<AString>(SSArg_1)
// 
// # Author(s): Conan Reis
template <typename _UserType>
inline _UserType * SSInvokedContextBase::get_arg(uint32_t idx) const
  {
  return m_data.get_at(idx)->m_data_p->as<_UserType>();
  }

//---------------------------------------------------------------------------------------
// Store user data structure for later retrieval with `get_user_data<>()`. The structure
// can be no more than 2 uintptr_t in size (32-bit: 8 bytes, 64-bit: 16 bytes)
// 
// This is useful for coroutines that need access to persistent info on successive calls
// to their bound C++ routines - for polling etc.
// 
// # Params:
//   ...args: Whatever arguments 0+ are needed for a _UserType constructor.
// 
// # Examples:
//   // Store a smart pointer to a SSActor object.
//   scope_p->append_user_data<AIdPtr<SSActor> >(actor_p);
//   
//   // Or store a float
//   scope_p->append_user_data<float>(num);
//
// 
//   // Get the pointer back when you need it
//   SSActor * actor_p = scope_p->get_user_data<AIdPtr<SSActor> >()
//   
//   // Or get a float back
//   float * num_p = scope_p->get_user_data<float>();
// 
// # Notes:
//   ***This mechanism assumes that the user data is stored at the *end* of this invoked
//   object's data table - so only *one* user data object may be stored in this manner.***
//   
//   The user data has an appropriate constructor called when it is initially stored and
//   its destructor is called on it when this invoked object has finished its invocation.
//   The user data structure is stored in the user data of a SSInstance object that comes
//   from a preallocated pool so it should not need to allocate additional memory.
//   [Though the dynamic pointer array in the data table `m_data` may need to increase.]
// 
// # See:       get_user_data<>()
// # Author(s): Conan Reis
template <typename _UserType, typename... _ParamClasses>
_UserType * SSInvokedContextBase::append_user_data(_ParamClasses&... args)
  {
  class _SSUserInstance : public SSInstance
    {
    public:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    _SSUserInstance(_ParamClasses... args) : SSInstance(SSBrain::ms_object_class_p)
      {
      //A_DPRINT("_SSUserInstance::ctor() - called.\n");
      m_ref_count = 1u;
      // Call _UserType constructor on the user data area of this instance
      A_ASSERTX(as<_UserType>() == reinterpret_cast<_UserType *>(&m_user_data), "This only works for types that are stored by value.");
      new (as<_UserType>()) _UserType(args...);
      }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    virtual void on_no_references() override
      {
      //A_DPRINT("_SSUserInstance::on_no_references() - called.\n");
      // Call destructor for _UserType
      as<_UserType>()->~_UserType();
      // Change virtual table for this instance back to SSInstance
      new (this) SSInstance();
      // Put it back on the pool for reuse
      pool_delete();
      }
    };

  // Get new SSInstance from the pool, change its virtual table to _SSUserInstance and
  // call its constructor which in turn calls the _UserType constructor.
  _SSUserInstance * user_obj_p = new (SSInstance::get_pool().pop()) _SSUserInstance(args...);

  // Add it to the end of this invoked object's data table.
  data_append_arg(ASymbol__user_, user_obj_p);

  return user_obj_p->as<_UserType>();
  }

//---------------------------------------------------------------------------------------
// Get pointer to user data that was previously stored with `append_user_data<>()`.
// 
// This is useful for coroutines that need access to persistent info on successive calls
// to their bound C++ routines - for polling etc.
// 
// # Examples:
//   // Get the pointer back from smart pointer to a SSActor object
//   actor_p = scope_p->get_user_data<AIdPtr<SSActor> >()
//   
//   // Or get a float back
//   float * num_p = scope_p->get_user_data<float>();
// 
// # Notes:
//   The user data structure is stored in an SSInstance user data that is added to the
//   end of this invoked object's data table.
// 
// # See:       append_user_data<>()
// # Author(s): Conan Reis
template <typename _UserType>
inline _UserType * SSInvokedContextBase::get_user_data() const
  {
  return m_data.get_last()->m_data_p->as<_UserType>();
  }

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInvokedBase.inl"
#endif

#endif  // __SSINVOKEDBASE_HPP
