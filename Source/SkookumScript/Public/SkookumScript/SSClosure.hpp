//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2012 Agog Labs Inc.,
// All rights reserved.
//
// Class Wrapper for a method/coroutine and the receiver object (this) that it
//             acts on.
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSCLOSURE_HPP
#define __SSCLOSURE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSLiteralClosure.hpp"


//=======================================================================================
// Defines
//=======================================================================================

#define SSCLOSURE_INFO      (reinterpret_cast<SSClosureInfoBase *>(m_user_data.m_data.m_ptr[0])) // $Revisit - MBreyer HACK
#define SSCLOSURE_RECV      (reinterpret_cast<SSInstance *>(m_user_data.m_data.m_ptr[1])) // $Revisit - MBreyer HACK
#define SSCLOSURE_CAPTURES  ((SSInstance **)(ptrdiff_t(this) + sizeof(SSClosure)))


//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
// #Description
//   Wrapper for a method/coroutine, the receiver object (this) that it acts on and any
//   captured variables from its source scope (where its literal was defined).
//   $Note - CReis [Hack for less memory+speed] It has different memory behaviour 
//   depending on its capture count:
//     0  used as a "swap-in memory replacement" for SSInstance - it occupies the same
//        space with just a different virtual table.
//     1+ uses its own memory rather than hijacking an SSInstance and includes references
//        to captured variables.
class SSClosure : public SSInstance
  {
  public:
  // Common Methods

    SS_NEW_OPERATORS(SSClosure);

  // Methods

    SSInstance *        get_receiver() const             { return SSCLOSURE_RECV; }
    SSClosureInfoBase * get_info() const                 { return SSCLOSURE_INFO; }
    uint32_t            get_captured_count() const       { return SSCLOSURE_INFO->get_captured().get_count(); }
    SSInstance **       get_captured_array() const       { return SSCLOSURE_CAPTURES; }

    static SSClosure * pool_new(SSClosureInfoBase * closure_info_p, SSInstance * receiver_p);
    virtual void       pool_delete();

    virtual AString as_string_debug() const;

    virtual uint32_t     get_obj_type() const  { return SSObjectType_closure; } 
    virtual SSInstance * get_data_by_name(const ASymbol & name) const;
    virtual void         set_data_by_name(const ASymbol & name, SSInstance * obj_p);
    virtual SSInstance * get_topmost_scope() const;
    virtual void         on_no_references();

  //---------------------------------------------------------------------------------------
  // Evaluates the closure as a method with 0 or more arguments and returns immediately
  // 
  // Params:
  //   method_name: name of method to call
  //   args_pp:
  //     Optional pointers to object instances to use as arguments - each one present
  //     should have its reference count incremented and each defaulted/skipped argument
  //     should be a `nullptr` element. If `arg_count` is 0 this is ignored
  //   arg_count:
  //     number of arguments to use in `args_pp`. If it is 0 then no arguments are passed
  //     and `args_pp` is ignored.
  //   caller_p:
  //     object that called/invoked this expression and that may await a result.  If it is
  //     nullptr, then there is no object that needs to be notified when this invocation is
  //     complete.
  //   result_pp:
  //     Pointer to a pointer to store the instance resulting from the invocation of this
  //     expression.  If it is nullptr, then the result does not need to be returned and
  //     only side-effects are desired.
  //     
  // Notes:
  //   Essentially the same as calling `some_closure(---)` in script.
  //   
  // See:
  //   method_call(), method_query(), method_invoke(), call_destructor(),
  //   call_default_constructor()
  void closure_method_call(
    SSInstance **   args_pp,
    uint32_t        arg_count,
    SSInstance **   result_pp = nullptr,
    SSInvokedBase * caller_p = nullptr
    );

  //---------------------------------------------------------------------------------------
  // Evaluates the closure as a method and returns immediately
  // 
  // Params:
  //   method_name: name of method to call
  //   arg_p:
  //     Optional pointer to object instance to use as an argument.  If it is present it
  //     should have its reference count incremented.  If it is nullptr, then no arguments
  //     are passed.
  //   caller_p:
  //     object that called/invoked this expression and that may await a result.  If it is
  //     nullptr, then there is no object that needs to be notified when this invocation is
  //     complete.
  //   result_pp:
  //     Pointer to a pointer to store the instance resulting from the invocation of this
  //     expression.  If it is nullptr, then the result does not need to be returned and
  //     only side-effects are desired.
  //     
  // Notes:
  //   Essentially the same as calling `some_closure(---)` in script.
  //   This is a convenience method to use instead of `closure_method_call(name, args_pp, --)`
  //   - if more arguments or control is desired, then use it instead
  //   
  // See:
  //   method_call(), method_query(), method_invoke(), call_destructor(),
  //   call_default_constructor()
  inline void SSClosure::closure_method_call(
    SSInstance *    arg_p     = nullptr,
    SSInstance **   result_pp = nullptr,
    SSInvokedBase * caller_p  = nullptr
    )
    {
    closure_method_call(&arg_p, arg_p ? 1u : 0u, result_pp, caller_p);
    }

  //---------------------------------------------------------------------------------------
  // Evaluates the closure as a method with 0/1 arguments and returns a Boolean `true` or
  // `false` result immediately.
  // 
  // Returns: the result of the method call as `true` or `false`.
  // 
  // Params:
  //   method_name: name of method to call
  //   arg_p:
  //     Optional argument to be passed to method.  If it is nullptr, then no arguments are
  //     passed.
  //   caller_p:
  //     Object that called/invoked this expression and that may await a result.  If it is
  //     `nullptr`, then there is no object that needs to be notified when this invocation
  //     is complete.
  // 
  // Notes:
  //   Essentially the same as calling `!result?: some_closure(---)` in script.
  //   This is a convenience method to use instead of `closure_method_call(name, args_pp, --)`
  //   - if more arguments or control is desired, then use it instead
  // 
  // See: method_query(), method_invoke(), call_destructor(), call_default_constructor()
  bool closure_method_query(
    SSInstance *    arg_p    = nullptr,
    SSInvokedBase * caller_p = nullptr
    );


  // Class Methods

    // SkookumScript Atomic Methods

      static void register_bindings();

      //static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_dtor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  protected:

  // Internal Methods

    SSClosure(SSClosureInfoBase * literal_p, SSInstance * receiver_p);

  // Data Members

    // Inherited from SSInstance

      // Store link to closure literal.  If the code that the closure literal is nested in
      // is unloaded *bad things will happen*.  Use get_literal() and get_captured_count()
      // to access it.
      // $Vital - CReis Probably need to ref count closure literal for at least 2 reasons:
      //   1) Dynamic code origin may be unloaded
      //   2) Closure written in workspace window, editor, etc. may have no permanent
      //   store of the code.
      //m_user_data.m_data.m_ptr[0]  - used as SSClosureInfoBase * m_closure_info_p [ref counted]
       
      // Reference counted pointer to the receiver/this for the closure.  Use
      // get_receiver() to access it.
      //m_user_data.m_data.m_ptr[1]  - used as SSInstance * m_receiver_p

      // $Note - CReis [Bit of a hack to save memory] When captured variables present then
      // extra memory past m_user_data is array of reference counted pointers to
      // SSInstance * for each captured variable.  Use get_captured_array() to access them.

  };  // SSClosure

//---------------------------------------------------------------------------------------
// Specialization - also ensures that `SSInvokedBase::get_arg<SSClosure>(--)`,
// `scope_p->this_as<SSClosure>()` etc. work properly
// 
// See: SSInstance::as<SSClass>
template<> inline SSClosure * SSInstance::as<SSClosure>() const { return static_cast<SSClosure *>(const_cast<SSInstance *>(this)); }


//=======================================================================================
// Inline Methods
//=======================================================================================



#endif  // __SSCLOSURE_HPP

