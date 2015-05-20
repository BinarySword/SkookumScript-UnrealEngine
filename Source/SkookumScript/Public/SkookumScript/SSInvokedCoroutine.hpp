//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Class wrapper for executed/called/invoked coroutines declaration file
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================

#ifndef __SSINVOKEDCOROUTINE_HPP
#define __SSINVOKEDCOROUTINE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSInvokedBase.hpp"


//=======================================================================================
// Global Macros / Defines
//=======================================================================================

// Default value indicating that invoked coroutine is not in its actors update list.
const uint32_t SSInvokedCoroutine_not_listed = ADef_uint32;

//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSCoroutineBase;
class SSCoroutineCall;


//---------------------------------------------------------------------------------------
// Notes      Wrapper for executed/called/invoked coroutines
// Author(s)  Conan Reis
class SSInvokedCoroutine : public SSInvokedContextBase
  {
  // For fast access.
  friend class SSInstance;
  friend class SSMind;
  friend class SSCoroutineCall;

  public:

  // Nested Structures

    enum eFlag
      {
      Flag_none             = 0,
      Flag_tracked_updating = 1 << 0,
      Flag_tracked_pending  = 1 << 1,
      Flag_tracked_mask     = Flag_tracked_updating | Flag_tracked_pending,

      Flag_suspended        = 1 << 2,

      Flag__default = Flag_none
      };

  // Public Data Members

    // Number of times this coroutine has been updated.  This will always be 0u on the
    // first update.  m_update_count * m_update_interval will give an approximate
    // elapsed time of how long this coroutine has been invoked.
    uint32_t m_update_count;

    // Specifies how many seconds should elapse between each update of this coroutine.
    // Since the update interval is stored in this invoked coroutine rather than the
    // coroutine itself, the same coroutine can have different update rates and a specific
    // invoked coroutine can change its update interval from one update to the next.
    f32 m_update_interval;

    // Simulation time (in seconds) when this coroutine should next be updated.  The next
    // update time is incremented prior to the update, so it may be modified freely
    // within the update without concern that it will be additionally modified.
    // The simulation time should only be updated when the game is being simulated - i.e.
    // it should not change when the game is paused or when in the game's front end.
    // Also note that since the simulation time is being represented by a f32, there
    // will be rounding errors after the simulation has been running straight for more
    // than 3 days.  This could instead be represented by an integer using milliseconds,
    // but most people find it more intuitive and less error prone to think in terms of
    // seconds rather than milliseconds or hundredths of seconds.
    f64 m_update_next;

  // Common Methods

    SS_NEW_OPERATORS(SSInvokedCoroutine);

    SSInvokedCoroutine();
    SSInvokedCoroutine(const SSCoroutineBase & coroutine, f32 update_interval = SSCall_interval_always, SSInvokedBase * caller_p = nullptr, SSObjectBase * scope_p = nullptr);

  // Comparison Methods

    bool operator==(const SSInvokedCoroutine & icoroutine) const;
    bool operator<(const SSInvokedCoroutine & icoroutine) const;

  // Converter Methods

    operator const ASymbol & () const;

  // Accessor Methods
    
    const ASymbol &         get_name() const;
    const SSCoroutineBase & get_coroutine() const;
    virtual SSMind *        get_updater() const;
    void                    reset(f32 update_interval, SSInvokedBase * caller_p, SSInstance * scope_p, SSMind * updater_p = nullptr, const APCompactArray<SSIdentifier> * rargs_p = nullptr);
    void                    set_coroutine(const SSCoroutineBase & coroutine);

    // Overriding from SSInvokedBase

    virtual SSInstance *      as_instance() const;
    virtual void              abort_invoke(eSSNotify notify_caller = SSNotify_fail, eSSNotifyChild notify_child = SSNotifyChild_abort);
    virtual void              pending_return(bool completed = true);
    virtual void              pending_schedule(bool completed = true);
    virtual eSSMember         get_invoke_type() const;
    virtual SSInvokableBase * get_invokable() const;

    #if (SKOOKUM & SS_DEBUG)
      virtual bool is_in_use() const                        { return is_valid_id() && ((m_flags & Flag_tracked_mask) != 0u); }
    #endif

    #if defined(SS_AS_STRINGS)
      virtual AString as_string_debug() const;
    #endif

  // Methods
    
    bool is_suspended() const								{ return (m_flags & Flag_suspended) != 0u; }
    void suspend();
    void resume();
    bool on_update();

  // Class Methods

    static SSInstance *         as_instance(SSInvokedCoroutine * icoroutine_p);
    static void                 pool_delete(SSInvokedCoroutine * icoroutine_p);
    static SSInvokedCoroutine * pool_new(SSCoroutineBase * coroutine_p);
    static SSInvokedCoroutine * pool_new(const SSCoroutineCall & cocall, f32 update_interval, SSInvokedBase * caller_p, SSInstance * scope_p, SSMind * updater_p = nullptr);
    static AObjReusePool<SSInvokedCoroutine> & get_pool();

  // SkookumScript Atomic Methods

    static void register_bindings();

    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  protected:

  // Internal Methods

    void stop_tracking();


  // Data Members

    // The coroutine that is invoked/running
    const SSCoroutineBase * m_coroutine_p;

    // Variable identifiers to bind any return argument results to or nullptr if no return
    // arguments used.
    const APCompactArray<SSIdentifier> * m_return_args_p;

    // The mind that is updating/tracking this invoked coroutine.  It may be the same as
    // m_scope_p or it may not.
    // $Revisit - CReis This *could* be a simple hard pointer SSMind *, but being paranoid
    // at the moment.
    mutable AIdPtr<SSMind> m_mind_p;

    // See SSInvokedCoroutine::eFlag
    uint32_t m_flags;

    // Future: priority - to resolve conflicting coroutines

  };  // SSInvokedCoroutine


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specialization - SSInvokedCoroutine stored indirectly as smart pointer in
// SSUserData rather than whole structure
template<> inline SSInvokedCoroutine *  SSUserDataBase::as<SSInvokedCoroutine>() const           { return static_cast<SSInvokedCoroutine *>(as_stored<AIdPtr<SSInvokedBase>>()->get_obj()); }
template<> inline void                  SSUserDataBase::set(SSInvokedCoroutine * const & value)  { *as_stored<AIdPtr<SSInvokedBase>>() = value; }

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInvokedCoroutine.inl"
#endif


#endif  // __SSINVOKEDCOROUTINE_HPP
