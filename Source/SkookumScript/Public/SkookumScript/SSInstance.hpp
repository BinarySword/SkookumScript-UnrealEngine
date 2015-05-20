//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structure for simplest type of object in language - instance of a
//             class without data members
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSINSTANCE_HPP
#define __SSINSTANCE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ARefCount.hpp>
#include <AgogCore/AString.hpp>
#include "SkookumScript/SSObjectBase.hpp"
#include "SkookumScript/SSUserData.hpp"

//=======================================================================================
// Global Macros / Defines
//=======================================================================================

//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSBrain;
class SSClass;
class SSList;
class SSCoroutineCall;
class SSExpressionBase;
class SSMethodCall;
class SSInvokedBase;
class SSInvokedCoroutine;
class SSInvokedMethod;


//---------------------------------------------------------------------------------------
// Flags used when converting an SSInstance to a code string
enum eSSCodeFlag
  {
  // If set and a new line character is encountered then replace with escaped new line
  // and also split string literal into multiple lines for better readability:
  //   This:
  //     "First line
  //      Second line"
  //      
  //   if true becomes:
  //     "First line\n" +
  //     "Second line"
  //     
  //   if false becomes:
  //     "First line\nSecond line"
  SSCodeFlag_break_lines   = 1 << 0,

  // Append the class type after the code string. Only used when a String() method is
  // called and ignored for simple types where the type is obvious.
  SSCodeFlag_include_type  = 1 << 1,

  SSCodeFlag__none    = 0,
  SSCodeFlag__default = SSCodeFlag__none
  };


//---------------------------------------------------------------------------------------
// SkookumScript user/reusable instance object / class instance - simplest object without
// any data members and with reference counting and user data
// 
// Subclasses: SSBoolean, SSClosure, SSDataInstance(SSActor), SSInstanceUnreffed(SSMetaClass)
// Author(s):  Conan Reis
class SSInstance : public SSObjectBase, public ARefCountMix<SSInstance>
  {
  // Accesses protected elements
  friend class SSBrain;
  friend class SSClosure;

  public:

  // Methods

    SS_NEW_OPERATORS(SSInstance);

    SSInstance();
    virtual ~SSInstance();

    virtual bool is_metaclass() const;
    SSClass *    get_class() const;
    SSClass *    get_key_class() const;

    virtual void pool_delete();

    virtual void as_code_append(AString * str_p, uint32_t code_flags = SSCodeFlag__none, SSInvokedBase * caller_p = nullptr) const;
    AString      as_code(uint32_t code_flags = SSCodeFlag__none, SSInvokedBase * caller_p = nullptr) const  { AString str; as_code_append(&str, code_flags, caller_p); return str; }

    #if defined(SS_AS_STRINGS)
      virtual AString         as_string_debug() const;
      virtual const ASymbol & get_name_debug() const                             { return ASymbol::ms_null; }
    #endif

    template <typename _UserType>       _UserType * as() const                   { return m_user_data.as<_UserType>(); }
    template <typename _UserType> void              set(_UserType const & value) { return m_user_data.set(value); }

    // Method Invocation

      void         call_default_constructor();
      void         call_destructor();
      virtual void method_invoke(const SSMethodCall & mcall, SSObjectBase * scope_p, SSInvokedBase * caller_p, SSInstance ** result_pp);

  //---------------------------------------------------------------------------------------
  // Evaluates the method with 0 or more arguments and returns immediately
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
  //   This is a convenience method to use instead of method_invoke() - if more arguments
  //   or control is desired, then use method_invoke()
  //   
  // See:
  //   method_call(), method_query(), method_invoke(), call_destructor(),
  //   call_default_constructor()
  virtual void method_call(
    const ASymbol & method_name,
    SSInstance **   args_pp,
    uint32_t        arg_count,
    SSInstance **   result_pp = nullptr,
    SSInvokedBase * caller_p = nullptr
    );

  //---------------------------------------------------------------------------------------
  // Evaluates the method with 0/1 arguments and returns immediately
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
  //   This is a convenience method to use instead of `method_call(name, args_pp, --)`
  //   - if more arguments or control is desired, then use it instead
  //   
  // See:
  //   method_call(), method_query(), method_invoke(), call_destructor(),
  //   call_default_constructor()
  void method_call(
    const ASymbol & method_name,
    SSInstance *    arg_p = nullptr,
    SSInstance **   result_pp = nullptr,
    SSInvokedBase * caller_p = nullptr
    );

  //---------------------------------------------------------------------------------------
  // Evaluates the method with 0/1 arguments and returns a Boolean `true` or
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
  //   This is a convenience method to use instead of `method_call(name, args_pp, --)`
  //   - if more arguments or control is desired, then use it instead
  // 
  // See: method_query(), method_invoke(), call_destructor(), call_default_constructor()
  bool method_query(
    const ASymbol & method_name,
    SSInstance *    arg_p    = nullptr,
    SSInvokedBase * caller_p = nullptr
    );

    // Coroutine Invocation

      void                 coroutine_schedule(const SSCoroutineCall & cocall, f32 update_interval = SSCall_interval_always, SSInvokedBase * caller_p = nullptr, SSMind * updater_p = nullptr);
      SSInvokedCoroutine * coroutine_call(const ASymbol & coroutine_name, SSInstance ** args_pp, uint32_t arg_count, bool immediate = true, f32 update_interval = SSCall_interval_always, SSInvokedBase * caller_p = nullptr, SSMind * updater_p = nullptr);
      SSInvokedCoroutine * coroutine_call(const ASymbol & coroutine_name, SSInstance * arg_p = nullptr, bool immediate = true, f32 update_interval = SSCall_interval_always, SSInvokedBase * caller_p = nullptr, SSMind * updater_p = nullptr);

    // Overriding from SSObjectBase

      virtual SSInstance *  as_instance() const                             { return const_cast<SSInstance *>(this); }
      virtual SSInstance *  get_data_by_name(const ASymbol & name) const;
      virtual uint32_t      get_obj_type() const                            { return SSObjectType_instance; } 
      virtual SSInstance *  get_topmost_scope() const;
      virtual void          set_data_by_name(const ASymbol & name, SSInstance * obj_p);

    // Overriding from ARefCountMix<>

      virtual void on_no_references();


  // Class Methods

    template<typename _UserType>
    static SSInstance * pool_new(SSClass * class_p, const _UserType & user_data);
    static SSInstance * pool_new(SSClass * class_p);
    static AObjReusePool<SSInstance> & get_pool();

  protected:

  // User data type definition

    typedef SSUserData<2> UserData;

  // Internal Methods

    friend class AObjBlock<SSInstance>;  // So it can be accessed only by pool_new()

    SSInstance(SSClass * class_p);
    SSInstance(SSClass * class_p, const UserData & user_data);

    // Bindings - for the class 'Object'

      static void register_bindings();

      static void mthd_as_string(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_sameQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);

      static void mthdc_as_string(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_class_ofQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_class_actorQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_subclass_ofQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_superclass_ofQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_print(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_println(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthdc_data_untyped_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);

      bool coro_wait(SSInvokedCoroutine * scope_p);
      bool coro_wait_until(SSInvokedCoroutine * scope_p);

  // Data Members

    // Class this is an instance of - stores methods and other info shared by instances
    SSClass * m_class_p;

    // $Note - CReis Could allow a redirection pointer - to allow direct hook-ins to already
    // existing data structures.  This would make a wasted 4 bytes for each type.

    // $Note - CReis [Memory]
    // The address of m_user_data can be used with a placement new of a data structure
    // up to pointer size * 2 bytes.
    // This includes most smart pointers like AIdxPtr<> and AIdPtr<>
    UserData  m_user_data;


  };  // SSInstance


//---------------------------------------------------------------------------------------
// Specialization - also ensures that `SSInvokedBase::get_arg<SSClass>(--)` etc. work properly
// 
// See: SSInstance::as<SSMetaClass>()
template<> inline SSClass * SSInstance::as<SSClass>() const  { return m_class_p; }


// Used to set an effectively *infinite* reference count so that the instance never gets
// "garbage collected" - in combination with overriding on_no_referenced() just to make sure.
const uint32_t SSInstanceUnreffed_infinite_ref_count = 1000000u;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript instance object / class instance - that ignores reference
//            counting and has user data no data members.
//            
//            Mainly used as a hack for nil so that it does not need to be reference
//            counted - though it has the unnecessary overhead of the user data and
//            reference count variables.  [Mechanism to ignore reference counting is a bit
//            hacky though it saves splitting apart SSInstance into 2 or more classes and
//            rewriting all the code that references it.]
// Subclasses SSMetaClass
// Author(s)  Conan Reis
class SSInstanceUnreffed : public SSInstance
  {
  public:

  // Methods

    SS_NEW_OPERATORS(SSInstanceUnreffed);
    SSInstanceUnreffed();
    SSInstanceUnreffed(SSClass * class_p);

    // Overriding from SSInstance (overriding from ARefCountMix<>)

      virtual void on_no_references();

  };


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Retrieves an instance object from the dynamic pool and initializes it for use.
// This method should be used instead of 'new' because it prevents unnecessary
// allocations by reusing previously allocated objects.
// # Returns:  a dynamic SSInstance
// # See:      pool_delete() 
// # Notes:    To 'deallocate' an object that was retrieved with this method, use
//             'pool_delete()' rather than 'delete'.
// # Modifiers: static
// # Author(s): Markus Breyer
template <typename _UserType>
inline SSInstance * SSInstance::pool_new(SSClass * class_p, const _UserType & user_data)
  {
  SSInstance * instance_p = pool_new(class_p);
  
  instance_p->set(user_data);

  return instance_p;
  }



#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInstance.inl"
#endif


#endif  // __SSINSTANCE_HPP

