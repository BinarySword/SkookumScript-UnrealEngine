//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Class wrapper for executed/called/invoked methods declaration file
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSINVOKEDMETHOD_HPP
#define __SSINVOKEDMETHOD_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSInvokedBase.hpp"


//=======================================================================================
// Defines
//=======================================================================================

//=======================================================================================
// Global Structures
//=======================================================================================

class SSMethodBase;  // Pre-declaration

//---------------------------------------------------------------------------------------
// Notes      Wrapper for executed/called/invoked methods
// Author(s)  Conan Reis
class SSInvokedMethod : public SSInvokedContextBase
  {
  public:
  // Common Methods

    SS_NEW_OPERATORS(SSInvokedMethod);

    SSInvokedMethod(SSInvokedBase * caller_p = nullptr, SSObjectBase * scope_p = nullptr, SSMethodBase * method_p = nullptr) : SSInvokedContextBase(caller_p, scope_p), m_method_p(method_p) {}

  // Methods

	void set_method(SSMethodBase * method_p)                        { m_method_p = method_p; }
    //SSInstance * get_this();

    // Overriding from SSInvokedBase

      virtual void abort_invoke(eSSNotify notify_caller = SSNotify_fail, eSSNotifyChild notify_child = SSNotifyChild_abort);
      virtual void pending_return(bool completed = true);

      virtual eSSMember         get_invoke_type() const;
      virtual SSInvokableBase * get_invokable() const;

      #if defined(SS_AS_STRINGS)
        virtual AString  as_string_debug() const;
      #endif

    // Inherited from SSObjectBase -> SSInvokedContextBase

      virtual SSInstance * as_instance() const;

  // Class Methods

    static AObjReusePool<SSInvokedMethod> & get_pool();
    static void                             pool_delete(SSInvokedMethod * imethod_p);
    static SSInvokedMethod *                pool_new(SSInvokedBase * caller_p, SSObjectBase * scope_p, SSMethodBase * method_p);

    // SkookumScript Atomic Methods

      static void register_bindings();

      static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  protected:

  // Data Members

    // Atomic or custom code object that is being invoked - see pool_new()
    SSMethodBase * m_method_p;

    // Future:  Used with dynamic scoping first-order code blocks.
    //uint32_t m_scope_id;

  };  // SSInvokedMethod


//---------------------------------------------------------------------------------------
// Method/coroutine hybrid - essentially a coroutine that can return a result.
//             Simple modification to invoked method to allow it to handle durational code
//             to a limited extent.
//             Used primarily for quick and dirty string -> executing code in script
//             consoles.
// Also See    SSParser::invoke_script()
// # Author(s): Conan Reis
class SSInvokedDeferrableMethod : public SSInvokedMethod
  {
  public:

    SSInvokedDeferrableMethod(SSObjectBase * scope_p = nullptr, SSMethodBase * method_p = nullptr) : SSInvokedMethod(nullptr, scope_p, method_p) {}

    void            invoke(SSInstance ** result_pp = nullptr);
    SSInvokedBase * invoke_deferred(SSInstance ** result_pp = nullptr);
    SSInstance *    invoke_now();

    // Overriding from SSInvokedBase

      virtual void abort_invoke(eSSNotify notify_caller = SSNotify_fail, eSSNotifyChild notify_child = SSNotifyChild_abort);
      virtual void pending_return(bool completed = true);
  };


//---------------------------------------------------------------------------------------
// Simple modification to invoked method to allow it to handle External Code
//             that may or may not actually be a coroutine
// # Author(s): Richard Orth
class SSIExternalMethodCallWrapper : public SSInvokedDeferrableMethod
  {
  public:

  // Common Methods

    SS_NEW_OPERATORS(SSIExternalMethodCallWrapper);

    SSIExternalMethodCallWrapper(SSObjectBase * scope_p = nullptr, SSMethodBase * method_p = nullptr) : SSInvokedDeferrableMethod(scope_p, method_p), m_finished_p(nullptr) {}
	~SSIExternalMethodCallWrapper();

  // Overriding from SSInvokedBase

    virtual void abort_invoke(eSSNotify notify_caller = SSNotify_fail, eSSNotifyChild notify_child = SSNotifyChild_abort);
    virtual void pending_return(bool completed = true);

  // Methods

    void clear_finished_check();

  // Data Members

    bool * m_finished_p;

  };  // SSIExternalMethodCallWrapper


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specialization - SSInvokedMethod stored indirectly as pointer in SSUserData rather than whole structure
template<> inline SSInvokedMethod *  SSUserDataBase::as<SSInvokedMethod>() const          { return static_cast<SSInvokedMethod *>(as_stored<AIdPtr<SSInvokedBase>>()->get_obj()); }
template<> inline void               SSUserDataBase::set(SSInvokedMethod * const & value) { *as_stored<AIdPtr<SSInvokedBase>>() = value; }


#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInvokedMethod.inl"
#endif


#endif  // __SSINVOKEDMETHOD_HPP

