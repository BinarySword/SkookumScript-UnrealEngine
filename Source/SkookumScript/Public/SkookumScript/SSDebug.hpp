//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Debugging and error handling classes
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSDEBUG_HPP
#define __SSDEBUG_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AFreePtr.hpp>
#include <AgogCore/AFunctionBase.hpp>
#include <AgogCore/AIdPtr.hpp>
#include <AgogCore/AList.hpp>
#include <AgogCore/APSorted.hpp>
#include "SkookumScript/SSMemberInfo.hpp"
#include "SkookumScript/SkookumRemoteBase.hpp"
#include "SkookumScript/SSParser.hpp"


//=======================================================================================
// Global Macros / Defines
//=======================================================================================

#if (SKOOKUM & SS_DEBUG)

  #define SS_DPRINTF(_msg, ...)                                     ADebug::print_format(_msg, __VA_ARGS__)

  #define SS_ASSERTX(_boolean_exp, _ex_desc)                        A_VERIFY(_boolean_exp, _ex_desc, AErrId_generic, SSDebug)
  #define SS_ASSERT(_boolean_exp, _ex_desc, _ExClass)               A_VERIFY(_boolean_exp, _ex_desc, AErrId_generic, _ExClass)
  #define SS_ASSERT_INVOKED(_boolean_exp, _ex_desc)                 A_VERIFY(_boolean_exp, (SSDebugInfoSetter(), _ex_desc), AErrId_generic, SSDebug)
  #define SS_ASSERT_INFO(_boolean_exp, _ex_desc, _info)             A_VERIFY(_boolean_exp, (SSDebugInfoSetter(_info), _ex_desc), AErrId_generic, SSDebug)
  #define SS_ASSERT_MEMORY(_ex_desc, _ExClass)                      A_VERIFY_MEMORY(_ex_desc, _ExClass)
  #define SS_ASSERT_ID(_boolean_exp, _ex_desc, _err_id, _ExClass)   A_VERIFY(_boolean_exp, _ex_desc, _err_id, _ExClass)
  #define SS_ERRORX(_ex_desc)                                       A_ERROR(_ex_desc, AErrId_generic, SSDebug)
  #define SS_ERROR(_ex_desc, _ExClass)                              A_ERROR(_ex_desc, AErrId_generic, _ExClass)
  #define SS_ERROR_INVOKED(_ex_desc)                                A_ERROR((SSDebugInfoSetter(), _ex_desc), AErrId_generic, SSDebug)
  #define SS_ERROR_INFO(_ex_desc, _info)                            A_ERROR((SSDebugInfoSetter(_info), _ex_desc), AErrId_generic, SSDebug)
  #define SS_ERROR_ID(_ex_desc, _err_id, _ExClass)                  A_ERROR(_ex_desc, _err_id, _ExClass)

  // Store current call so rest of engine can know if in the middle of a script call or not.
  #define SSDEBUG_STORE_CALL(_scope_p)                              SSInvokedContextBase * _old_call_p = SSDebug::ms_current_call_p; SSDebug::ms_current_call_p = _scope_p;
  #define SSDEBUG_RESTORE_CALL()                                    SSDebug::ms_current_call_p = _old_call_p;

  // Setting debug info for invoked method/coroutine.  Called internally so there is no info.
  #define SSDEBUG_ICALL_SET_INTERNAL(_icontext_p)                   _icontext_p->m_source_idx = 0u; _icontext_p->m_debug_info = uint16_t(SSDebugInfo::Flag__default);

  // Setting debug info for invoked method/coroutine.  Copy from previously stored global expression values.  Done via globals rather than passing expression as an argument so the arguments are consistent across build targets.
  #define SSDEBUG_ICALL_SET_GEXPR(_icontext_p)                      _icontext_p->m_source_idx = SSInvokedContextBase::ms_last_expr_p->m_source_idx; _icontext_p->m_debug_info = SSInvokedContextBase::ms_last_expr_p->m_debug_info;

  #define SSDEBUG_ICALL_SET_EXPR(_icontext_p, _expr_p)              _icontext_p->m_source_idx = _expr_p->m_source_idx; _icontext_p->m_debug_info = _expr_p->m_debug_info;

  // Store expression debug info for invoked methods/coroutines.  Done via globals rather than passing expression as an argument so the arguments are consistent across build targets.
  #define SSMEMORY_ARGS(_Class, _debug_bytes)                       #_Class, sizeof(_Class) - (_debug_bytes), _debug_bytes

#else  // SS_DEBUG not defined

  // Note, using (void(0)) avoids warning that ; is used without an expression.

  #define SS_DPRINTF(_msg, ...)                                     (void(0))

  #define SS_ASSERTX(_boolean_exp, _ex_desc)                        (void(0))
  #define SS_ASSERT(_boolean_exp, _ex_desc, _ExClass)               (void(0))
  #define SS_ASSERT_INVOKED(_boolean_exp, _ex_desc, _info)          (void(0))
  #define SS_ASSERT_INFO(_boolean_exp, _ex_desc, _info)             (void(0))
  #define SS_ASSERT_MEMORY(_ex_desc, _ExClass)                      (void(0))
  #define SS_ASSERT_ID(_boolean_exp, _ex_desc, _err_id, _ExClass)   (void(0))
  #define SS_ERRORX(_ex_desc)                                       (void(0))
  #define SS_ERROR(_ex_desc, _ExClass)                              (void(0))
  #define SS_ERROR_INVOKED(_ex_desc)                                (void(0))
  #define SS_ERROR_INFO(_ex_desc, _info)                            (void(0))
  #define SS_ERROR_ID(_ex_desc, _err_id, _ExClass)                  (void(0))

  #define SSDEBUG_STORE_CALL(_scope_p)                              (void(0))
  #define SSDEBUG_RESTORE_CALL()                                    (void(0))

  #define SSDEBUG_ICALL_SET_INTERNAL(_icontext_p)                   (void(0))
  #define SSDEBUG_ICALL_SET_GEXPR(_icontext_p)                      (void(0))
  #define SSDEBUG_ICALL_SET_EXPR(_icontext_p, _expr_p)              (void(0))

  #define SSMEMORY_ARGS(_Class, _debug_bytes)                       #_Class, sizeof(_Class), _debug_bytes

#endif  // (SKOOKUM & SS_DEBUG)


#if defined(SSDEBUG_COMMON)
  // Store expression debug info for next invoked method/coroutine.  Done via globals rather than passing expression as an argument so the arguments are consistent across build targets.
  #define SSDEBUG_ICALL_STORE_GEXPR(_expr_p)                        SSInvokedContextBase::ms_last_expr_p = _expr_p;
#else
  #define SSDEBUG_ICALL_STORE_GEXPR(_expr_p)                        (void(0))
#endif


//---------------------------------------------------------------------------------------
// Debug hooks for notifying when scripts start/stop various tasks so that things like
// tracing, profiling, breakpoints, etc. can be added.
#if defined(SSDEBUG_HOOKS)  // Normally defined in SkookumScript.hpp

  // Called whenever a method is about to be invoked - see SSDebug::append_hook()
  #define SSDEBUG_HOOK_METHOD(_imethod_p)                           SSDebug::hook_method(_imethod_p)

  // Called whenever a coroutine is about to be invoked - see SSDebug::append_hook()
  #define SSDEBUG_HOOK_COROUTINE(_icoro_p)                           SSDebug::hook_coroutine(_icoro_p)

  // Called whenever the Skookum scripting system is about to be entered to execute some script code - see SSDebug::append_hook()
  #define SSDEBUG_HOOK_SCRIPT_ENTRY(_origin_id)                     SSDebug::hook_script_origin_push(_origin_id)

  // Called whenever the Skookum scripting system is about to be exited after having executed some script code - see SSDebug::append_hook()
  #define SSDEBUG_HOOK_SCRIPT_EXIT()                                SSDebug::hook_script_origin_pop()

#else  // SSDEBUG_HOOKS not defined

  // Note, using (void(0)) avoids warning that ; is used without an expression.

  #define SSDEBUG_HOOK_METHOD(_imethod_p)                           (void(0))
  #define SSDEBUG_HOOK_COROUTINE(_icoro_p)                          (void(0))
  #define SSDEBUG_HOOK_SCRIPT_ENTRY(_origin_id)                     (void(0))
  #define SSDEBUG_HOOK_SCRIPT_EXIT()                                (void(0))

#endif  // SSDEBUG_HOOKS


#if (SKOOKUM & SS_DEBUG)

  // Called whenever expression is about to be invoked and it has a debug action (like a
  // breakpoint) - see SSDebug::hook_expression()
  #define SSDEBUG_HOOK_EXPR(_expr_p, _scope_p, _caller_p) \
    if ((SSDebug::ms_expr_hook_flag | (_expr_p)->m_debug_info) & SSDebugInfo::Flag_debug_enabled) \
      { SSDebug::hook_expression((SSExpressionBase *)(_expr_p), (_scope_p), (_caller_p)); } \
    (void(0))

#elif defined(SSDEBUG_HOOKS)

  #define SSDEBUG_HOOK_EXPR(_expr_p, _scope_p, _caller_p) \
    if (SSDebug::ms_expr_hook_flag) \
      { SSDebug::hook_expression((SSExpressionBase *)(_expr_p), (_scope_p), (_caller_p)); } \
    (void(0))

#else  // Neither (SKOOKUM & SS_DEBUG) nor SSDEBUG_HOOKS defined

  #define SSDEBUG_HOOK_EXPR(_expr_p, _scope_p, _caller_p) \
    (void(0))

#endif


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSExpressionBase;
class SSInstance;
class SSInvokedBase;
class SSInvokedContextBase;
class SSInvokedMethod;
class SSInvokedCoroutine;
class SSObjectBase;
class SSQualifier;


//---------------------------------------------------------------------------------------
// Used when generating information for callstacks/local variables/etc.
enum eSSInvokeInfo
  {
  SSInvokeInfo_none           = 0x0,     // No extra info
  SSInvokeInfo_indent         = 1 << 0,  // Indent lines when building multi-line string
  SSInvokeInfo_skip_this      = 1 << 1,  // Skip the most recent/current call when string

  SSInvokeInfo_scope          = 1 << 2,  // Include the identifier scope
  SSInvokeInfo_args           = 1 << 3,  // Include argument values
  SSInvokeInfo_this           = 1 << 4,  // Include this/receiver value

  // Locals only info
  SSInvokeInfo_temporaries    = 1 << 5,  // Include instance data members
  SSInvokeInfo_instance_data  = 1 << 6,  // Include instance data members
  SSInvokeInfo_class_data     = 1 << 7,  // Include class data members

  SSInvokeInfo__locals_def    = SSInvokeInfo_scope | SSInvokeInfo_temporaries | SSInvokeInfo_args | SSInvokeInfo_this | SSInvokeInfo_instance_data | SSInvokeInfo_class_data,

  // Callstack only info
  SSInvokeInfo_ignore_absent  = 1 << 8,  // If no call stack available do not print any info
  SSInvokeInfo_index          = 1 << 9,  // Include caller source character index
  SSInvokeInfo_updater        = 1 << 10, // Include the updater for invoked coroutines
  SSInvokeInfo_depth          = 1 << 11, // Include the call depth
  // Update count for coroutines?
  // Pending count?
  // Expressions?
  
  SSInvokeInfo__callstack_def = SSInvokeInfo_scope | SSInvokeInfo_args | SSInvokeInfo_this | SSInvokeInfo_index | SSInvokeInfo_updater
  };


//---------------------------------------------------------------------------------------
// Debug/logging print "decoration" type.  Used by SSDebug:print() and SSConsole::log_append()
enum eSSDPrintType
  {
  SSDPrintType_standard,  // Skookum (white)
  SSDPrintType_title,     // Title / link (yellow)
  SSDPrintType_note,      // Notable action (green)
  SSDPrintType_system,    // C++ (electric blue)
  SSDPrintType_error,     // (red)
  SSDPrintType_warning,   // (orange)
  SSDPrintType_result,    // (light yellow)
  SSDPrintType_trace,     // (lavender)

  // Or-ed in flag that indicates that print comes from remote IDE - italics or slightly
  // different background.  If not present then locale is considered to be embedded/runtime.
  SSDPrintType_flag_remote   = 1 << 7,

  SSDPrintType_non_flag_mask = 0x7F

  // $Note - CReis Currently assuming this will fit in 1 byte.
  };


//---------------------------------------------------------------------------------------
// Type of script code/classes to include for memory statistics
enum eSSCodeSerialize
  {
  SSCodeSerialize_static,        // Only always loaded code
  SSCodeSerialize_static_demand  // Always loaded code + demand loaded code
  };


//---------------------------------------------------------------------------------------
struct SSPrintInfo
  {
  // Public Data Members

    AString  m_str;
    uint32_t m_type;  // See eSSDPrintType

  // Common Methods

    SSPrintInfo(const AString & str, uint type = SSDPrintType_system)
      : m_str(str), m_type(type)
      {}

  };

typedef AFunctionArgBase<const SSPrintInfo &> tSSPrintFunc;


const uint16_t SSExpr_char_pos_invalid = UINT16_MAX - 1u;

//---------------------------------------------------------------------------------------
struct SSDebugInfo
  {
  // Nested Structures

    // Describes how the bits of SSExpressionBase::m_debug_info are utilized.
    enum eFlag
      {
      // Debug index (11 bits) - Index into debug action table (0-2047).  Flag_debug_idx__none indicates no debug action set.
      Flag_debug_idx__mask   = (1 << 11) - 1,
      Flag_debug_idx__none   = Flag_debug_idx__mask,

      // Code Origin (4 bits) - Indicates the location where the code for this expression came from
      Flag_origin_internal   = 0x0,      // Code was hooked up internally in C++ or was generated
      Flag_origin_source     = 1 << 12,  // Code came from a standard source file (* default args may need more info)
      Flag_origin_alias,                 // Code came from an alias - origin info specifies alias
      Flag_origin_custom1,               // Code came from a custom location #1 such as a tool
      Flag_origin_custom2,               // Code came from a custom location #2 such as a tool
      Flag_origin_custom3,               // Code came from a custom location #3 such as a tool
      Flag_origin_custom4,               // Code came from a custom location #4 such as a tool
      Flag_origin_custom5,               // Code came from a custom location #5 such as a tool
      Flag_origin_custom6,               // Code came from a custom location #6 such as a tool
      Flag_origin_custom7,               // Code came from a custom location #7 such as a tool
      Flag_origin_custom8,               // Code came from a custom location #8 such as a tool
      Flag_origin_custom9,               // Code came from a custom location #9 such as a tool
      Flag_origin_custom10,              // Code came from a custom location #10 such as a tool
      Flag_origin_custom11,              // Code came from a custom location #11 such as a tool
      Flag_origin_custom12,              // Code came from a custom location #12 such as a tool
      Flag_origin_custom13,              // Code came from a custom location #13 such as a tool
      Flag_origin__mask      = ((1 << 15) - 1) - Flag_debug_idx__mask,

      // Debug enable (1 bit)  - Indicates a debug action to take when this expression is about to be evaluated
      Flag_debug_disabled    = 0x0,      // No special action to take
      Flag_debug_enabled     = 1 << 15,  // Examine debug index to determine action

      Flag__default        = Flag_debug_idx__none | Flag_origin_internal | Flag_debug_disabled,
      Flag__default_source = Flag_debug_idx__none | Flag_origin_source | Flag_debug_disabled
      };

  // Public Data

    // Source string character index position where this expression starts in the original
    // parsed code file/string.  m_debug_flags describes the source code origin.
    uint16_t m_source_idx; 

    // Debug flags & misc. info - such as breakpoint set flag - see eFlag
    uint16_t m_debug_flags;

    // Used for top level commands during creation of callstack
    static const SSExpressionBase * ms_expr_default_p;
    static const SSExpressionBase * ms_expr_p;

  // Methods

    void set_info(uint16_t source_idx, uint16_t debug_flags)  { m_source_idx = source_idx; m_debug_flags = debug_flags; }
    void set_internal()                                       { m_source_idx = 0u; m_debug_flags = Flag__default; }

    bool is_origin_source() const                             { return (m_debug_flags & Flag_origin__mask) == Flag_origin_source; }
    bool is_origin_internal() const                           { return (m_debug_flags & Flag_origin__mask) == Flag_origin_internal; }
    bool is_valid_origin_source() const                       { return ((m_debug_flags & Flag_origin__mask) == Flag_origin_source) && (m_source_idx != SSExpr_char_pos_invalid); }

  // Class Methods

    static SSExpressionBase * get_expr_default();
  };

// Dummy structure used to calculate size used by SSDebugInfo with respect to alignment
// and pointer/virtual table use, etc.
struct SSDebugInfoPtrDummyStruct
  {
  void * m_ptr_p;
  SSDebugInfo m_info;
  };

// Actual amount of bytes used by SSDebugInfo in structures like SSExpressionBase for use
// in methods like track_memory()
const size_t SSDebugInfo_size_used = sizeof(SSDebugInfoPtrDummyStruct) - sizeof(void *);


//---------------------------------------------------------------------------------------
// Used to provide extra debug info in SS_ASSERT_INFO() when the currently executing
// expression is known.
struct SSDebugInfoSetter
  {
  // Methods
    SSDebugInfoSetter();
    SSDebugInfoSetter(const SSExpressionBase & expr);
    SSDebugInfoSetter(SSInvokedBase * caller_p);
    ~SSDebugInfoSetter();
  };


//---------------------------------------------------------------------------------------
// Notes      Member Expression identifying information
// Author(s)  Conan Reis
class SSMemberExpression : public SSMemberInfo
  {
  public:

    // Common Methods

      SSMemberExpression()                                : m_expr_p(nullptr), m_source_idx(0u) {}
      SSMemberExpression(const SSMemberInfo & member_info, SSExpressionBase * expr_p = nullptr);
      SSMemberExpression(const SSMemberExpression & info) : SSMemberInfo(info), m_expr_p(info.m_expr_p), m_source_idx(info.m_source_idx) {}

    // Comparison Methods

      bool operator==(const SSMemberExpression & expr_info) const;
      bool operator<(const SSMemberExpression & expr_info) const;

    // Accessor methods

      virtual SSExpressionBase * get_expr() const;

      uint32_t get_source_idx();
      bool     is_origin_source() const;

      #if (SKOOKUM & SS_DEBUG)
        using SSMemberInfo::set_context;
        void set_context(SSObjectBase * scope_p, SSInvokedBase * caller_p, SSExpressionBase * expr_p);
      #endif

    // Binary Stream Methods

      SSMemberExpression(const void ** binary_pp);

      #if (SKOOKUM & SS_COMPILED_OUT)
        virtual void     as_binary(void ** binary_pp) const;
        virtual uint32_t as_binary_length() const             { return SSMemberInfo::as_binary_length() + 2u; }
      #endif

  //protected: // Public for now

    // Data Members

      // Cached info - may go stale - use get_expr() instead of using directly
      mutable SSExpressionBase * m_expr_p;

      // Expression character index position - cached from m_expr_p and only valid if
      // SS_DEBUG flag is set in the SKOOKUM define.
      mutable uint32_t m_source_idx;

      // $Revisit - CReis Might need this if different source origins are used
      //SSDebugInfo::eFlag m_code_origin;

  };


#if (SKOOKUM & SS_DEBUG)

//---------------------------------------------------------------------------------------
// Invoked object descriptor - SSInvokedContext(SSInvokedMethod or SSInvokedCoroutine) or
// SSInvokedExpression/SSExpression "leaf".
class SSInvokedInfo
  : public SSMemberInfo,
  AListNode<SSInvokedInfo>  // Stored in the m_calls of its caller
  {
  public:

  // Nested Structures

    enum eFlag
      {
      Flag_expression   = 1 << 0,  // Represents a "leaf" expression.
      };


  // Common Methods

    operator const uint32_t & () const                  { return m_unique_id; }
    bool operator==(const SSInvokedInfo & iinfo) const  { return m_unique_id == iinfo.m_unique_id; }
    bool operator<(const SSInvokedInfo & iinfo) const   { return m_unique_id < iinfo.m_unique_id; }

  protected:

  // Data Members

    uint32_t m_flags;

    // Unique instance id for this invoked object "thread"
    uint32_t m_unique_id;

    // Expression index position of calling expression if this represents an invoked
    // context (method/coroutine) or the current/leaf expression index if it is a invoked
    // expression.
    uint32_t m_expr_idx;

    // String representation of arguments in name->value form.
    // Symbols translated as needed and escape characters converted to backslash equivalents.
    AString m_args_str;

    // Call Hierarchy
      
      SSInvokedInfo *      m_caller_p;  // Invoked context that called this
      AList<SSInvokedInfo> m_calls;     // List of any invoked objects called by this invoked object

    // Scope/receiver/this Info
    
      uint32_t  m_scope_id;       // Unique object id of scope
      uint32_t  m_scope_addr;     // Scope memory address
      SSClass * m_scope_class_p;  // Scope class
      AString   m_scope_str;      // String representation of scope (translated & breaks converted)

    // Updater info

      ASymbol   m_updater_name;
      SSClass * m_updater_class_p;

    // Invoked Coroutine Info

      uint32_t m_update_count;
      f32      m_update_interval;
      f64      m_update_next;

  };  // SSInvokedInfo


//---------------------------------------------------------------------------------------
// Since Skookum runs scripts concurrently a "call tree" is a more correct and useful
// representation than a "call stack".  Each actor object may have zero to many call tree
// "leaves" that it is updating and there can be many call trees distributed amongst all
// the actors in the runtime.
class SSCallTree
  {
  public:

  // Common Methods

  protected:

  // Data Members

    // Leaf point of current call stack being examined
    SSInvokedInfo * m_current_path_p;

    // Leaf point of current break stack
    SSInvokedInfo * m_break_path_p;

    // Ancestor/originating root of entire call tree
    SSInvokedInfo * m_call_root_p;

  };  // SSCallTree


//---------------------------------------------------------------------------------------
// Notes      Debug Breakpoint
// Author(s)  Conan Reis
class SSBreakPoint : public SSMemberExpression
  {
  public:

  // Nested Structures

    // Hit type
    enum eHit
      {
      Hit_always,
      Hit_equal,
      Hit_greater_equal,
      Hit_less_equal,
      Hit_multiple
      };

    enum eConstrain
      {
      Constrain_ignored,
      Constrain_populate
      };

    enum eBinaryFlag
      {
      BinaryFlag__none        = 0x0,
      BinaryFlag_class_scope  = 1 << 0,
      BinaryFlag_enabled      = 1 << 1
      };

    enum eUpdate
      {
      Update_enable,
      Update_disable,
      Update_remove
      };


  // Common Methods

    SS_NEW_OPERATORS(SSBreakPoint);

    SSBreakPoint(const SSMemberInfo & member_info, SSExpressionBase * break_expr_p = nullptr);
    SSBreakPoint(const SSMemberExpression & info, uint32_t table_idx, bool enabled = true);
    ~SSBreakPoint();

    // Accessor methods

      virtual SSExpressionBase * get_expr() const;

  // Methods

    void enable(bool set_break = true);
    void enable_set()                         { enable(); }
    void enable_clear()                       { enable(false); }
    void enable_toggle()                      { enable(!m_enabled); }
    bool is_enabled() const                   { return m_enabled; }
    void remove();

  //protected: // Public for now

    // Internal Methods

      void reaquire_expr(bool force = false) const;
      void release_expr();

    // Data Members

      // Index position in SSDebug::ms_breakpoint_table - SSDebugInfo::Flag_debug_idx__none
      // reserved for expressions without a breakpoint.
      uint32_t m_table_idx;

      // Indicates whether breakpoint is active or not
      bool m_enabled;


      // Future conditions:
      //
      //   // Only perform break action when all other conditions met and m_hit_count is:
      //   //  Hit_always        - any value
      //   //  Hit_equal         - equal to m_hit_count_test
      //   //  Hit_greater_equal - greater than or equal to m_hit_count_test
      //   //  Hit_greater_equal - less than or equal to m_hit_count_test
      //   //  Hit_multiple      - a multiple of m_hit_count_test
      //   eHit m_hit_type;
      //   uint m_hit_count_test;
      // 
      //   // Increment when all other conditions met
      //   uint m_hit_count;
      // 
      //   // Only perform break action when this context is in the call stack
      //   AIdPtr<SSInvokedContextBase> m_invoked_caller_p;
      // 
      //   // Only perform break action when being updated by a class (or subclass if m_updater_subclass_check is set) of this type.
      //   SSClass * m_updater_class_p;
      //   bool      m_updater_subclass_check;
      // 
      //   // Only perform break action when scope/receiver is an actor with the specified name
      //   ASymbol m_scope_actor_name;
      //
      //   // Test to determine if break action should occur once other conditions met [May want to keep original code]
      //   SSExpressionBase * m_test_expr_p;
      // 
      //   // Other Conditions:
      //   //
      //   //  Frame/update count
      //   //  Time-based
      //   //  Updater mind
      //   //  Scope/receiver class
      //   //  Scope/receiver instance
      //   //  Method call
      //   //  Coroutine call
      //   //  Method caller
      //   //  Coroutine caller
      //   //  Invoked Coroutine invoke count

  };  // SSBreakPoint


typedef APSortedLogical<SSBreakPoint, SSMemberExpression> tSSBreakPoints;

#endif  // (SKOOKUM & SS_DEBUG)


typedef void (* tSSMethodHook)(SSInvokedMethod * imethod_p);
typedef void (* tSSCoroutineHook)(SSInvokedCoroutine * icoro_p);
typedef void (* tSSScriptSystemHook)(const ASymbol & origin_id);


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Debug
// Author(s)  Conan Reis
class SSDebug
  {
  public:

  // Public Nested Structures

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Runtime Debug State
    enum eState
      {
      State__flag_suspended      = 1 << 0,
      State__flag_member_info    = 1 << 1,
      State__flag_expr_info      = 1 << 2,

      State_running              = 0x0,
      State_suspended            = State__flag_suspended,
      State_suspended_member     = State__flag_suspended | State__flag_member_info,
      State_suspended_expr       = State__flag_suspended | State__flag_member_info | State__flag_expr_info
      };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Stepwise Debugging Type/Flags
    enum eStep
      {
      // Used to indicate not stepping
      Step__none = 0x0,

      // Stop at next expression regardless of the context
      Step_next  = 1,

      // Stop on the next expression that has the same invoked context (method/coroutine)
      // unless it is stale in which case ignore it.
      Step_into  = 2,

      // Stop on the expression with the same invoked context (method/coroutine) unless it
      // is stale in which case ignore it after the current expression has completed.
      Step_over  = 3,

      // Stop on the next expression after the current invoked context (method/coroutine)
      // has completed (it should be on the same thread).
      Step_out   = 4
      };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Debugging Flags - used by SSDebug::ms_flags
    enum eFlag
      {
      Flag_hook_expression    = 1 << 0,
      Flag_stepping           = 1 << 1,

      Flag__none                  = 0x0,
      Flag__test_expression_mask  = Flag_hook_expression | Flag_stepping,
      Flag__default               = Flag__none
      };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Debugging preferences flags - used by SSDebug::ms_pref_flags
    enum ePrefFlag
      {
      // Automatically print out callstack when a Skookum expression break occurs
      PrefFlag_break_print_callstack    = 1 << 0,

      // Automatically print out local variables when a Skookum expression break occurs
      PrefFlag_break_print_locals       = 1 << 1,

      PrefFlag__none              = 0x0,
      PrefFlag__break_print_mask  = PrefFlag_break_print_callstack | PrefFlag_break_print_locals,
      PrefFlag__default           = PrefFlag_break_print_callstack | PrefFlag_break_print_locals
      };


    #if defined(SSDEBUG_HOOKS)

      //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      // Hook group used to describe a set of script execution callbacks to enable/disable
      // all at once.
      struct Hook : public
        ANamed,
        AListNode<Hook, tSSMethodHook>,
        AListNode<Hook, tSSCoroutineHook>,
        AListNode<Hook, tSSScriptSystemHook>
        {
        friend class SSDebug;

        // Nested Structures
       
          // Used by SSDebug::Hook::m_flags
          enum eFlag
            {
            Flag_enabled                = 1 << 0,

            Flag_only_updater_class     = 1 << 4,
            Flag_only_scope_name        = 1 << 6,
            Flag_only_invoked_caller    = 1 << 7,

            Flag__none = 0x0,
            Flag__condition_mask = Flag_only_updater_class | Flag_only_scope_name | Flag_only_invoked_caller
            };

        // Data Members

          // Short name of hook - used for UI
          AString m_hook_name;

          // More detailed description of hook - used for UI
          AString m_hook_desc;

          // Callback/hook for methods - ignored if nullptr
          tSSMethodHook m_hook_method_f;

          // Callback/hook for coroutines - ignored if nullptr
          tSSCoroutineHook m_hook_coroutine_f;

          // Callback/hook for entering the Skookum system prior to executing scripts.
          // [Either both m_hook_script_entry_f and m_hook_script_exit_f must be set to a
          // valid function or both must be set to nullptr - in which case they are ignored.]
          tSSScriptSystemHook m_hook_script_entry_f;

          // Callback/hook for exiting the Skookum system after executing scripts.
          // [Either both m_hook_script_entry_f and m_hook_script_exit_f must be set to a
          // valid function or both must be set to nullptr - in which case they are ignored.]
          tSSScriptSystemHook m_hook_script_exit_f;

          // Conditions / Constraints for method/coroutine hooks

            // Only run hooks when being updated by a class (or subclass if
            // m_updater_subclass_check is set) of this type.
            SSClass * m_updater_class_p;
            bool      m_updater_subclass_check;  // $Revisit - CReis Could store this in m_flags

            // Only run hooks when scope/receiver is an actor with the specified name
            ASymbol m_scope_actor_name;

            // Only run hooks when this context is in the call stack
            AIdPtr<SSInvokedContextBase> m_invoked_caller_p;

            // [Conditions that could be added in the future]
            // 
            // Note - all these conditions (and more) can be tested in the hook/ functions
            // themselves - it just might not be as efficient as "built-in" tests.
            // 
            //   Frame/update count
            //   Time-based
            //   Updater mind
            //   Scope/receiver class
            //   Scope/receiver instance
            //   Method call
            //   Coroutine call
            //   Method caller
            //   Coroutine caller
            //   Invoked Coroutine invoke count

        // Methods

          Hook(const AString & hook_name);
          Hook(const Hook & hook);

          Hook & operator=(const Hook & hook);

          AString       get_name_str() const        { return m_hook_name; }
          const char *  get_name_cstr() const       { return m_hook_name.as_cstr(); }
          AString       get_name_str_dbg() const    { return m_hook_name; }
          const char *  get_name_cstr_dbg() const   { return m_hook_name.as_cstr(); }
          void          set_name(const AString & name);

          bool is_enabled() const                   { return (m_flags & Flag_enabled) !=0; }
          bool is_conditions_met(SSInvokedContextBase * icontext_p) const;

        protected:

          // Internal methods

            void update_flags();

          // Protected Data Members

            // Current hook state - see SSDebug::Hook::eFlag
            uint32_t m_flags;

        };  // SSDebug::Hook

      #endif // SSDEBUG_HOOKS


  // Public Class Data Members - for quick access

    // Number of spaces to indent - used in situations like when converting in-memory
    // structures to code scripts like most `as_string_debug()` methods.
    // This is independent of tab stop size.
    static uint32_t ms_indent_size;

    // Tab stop size in non-proportional space characters. Used wherever tab `\t`
    // characters are displayed in text - used to determine visual columns a section of
    // code uses when creating debug / error messages like
    // `SSParser::get_result_context_string()`.
    // This is independent of indent size.
    static uint32_t ms_tab_stops;

    #if (SKOOKUM & SS_DEBUG)
      // Currently executing method or coroutine - tracked here for debugging purposes.
      // Enables rest of engine to know if in the middle of a script call or not.
      // Also see ms_next_expr & ms_next_invokable_p.
      static AIdPtr<SSInvokedContextBase> ms_current_call_p;
    #endif

    #if defined(SSDEBUG_COMMON)
      // If set to SSDebugInfo::Flag_debug_enabled then all expressions have their execution
      // trapped/tested otherwise only expressions with breakpoints are tested.
      static uint32_t ms_expr_hook_flag;
    #endif


  // Common Methods

      static void initialize_pre_load();
      static void enable_engine_present(bool engine_present_b = true)           { ms_engine_present_b = engine_present_b; }
      static bool is_engine_present()                                           { return ms_engine_present_b; }
      static void register_bindings();
      static void deinitialize();

    // Debug Output

      static void    info();
      static void    callstack(SSInvokedBase * invoked_p = nullptr, uint32_t stack_flags = SSInvokeInfo__callstack_def);
      static void    callstack_string(AString * str_p, SSInvokedBase * invoked_p = nullptr, uint32_t stack_flags = SSInvokeInfo__callstack_def);
      static AString context_string(const AString & description, SSObjectBase * call_scope_p, SSObjectBase * alt_scope_p = nullptr, uint32_t stack_flags = SSInvokeInfo__callstack_def);
      static void    locals_string(AString * str_p, SSInvokedBase * invoked_p = nullptr, uint32_t flags = SSInvokeInfo__locals_def);
      static void    print(const AString & str, eSSLocale locale = SSLocale_all, uint32_t type = SSDPrintType_system);
      static bool    print_ide(const AString & str, eSSLocale locale = SSLocale_all, uint32_t type = SSDPrintType_system);
      static void    print_ide_all(const AString & str)                { print_ide(str); }
      static void    print_agog(const AString & str, eSSLocale locale = SSLocale_all, uint32_t type = SSDPrintType_system);
      static void    print_script_context(const AString & msg, const SSInvokableBase * invokable_p = nullptr, SSExpressionBase * expr_p = nullptr, uint32_t type = SSDPrintType_system);
      static void    print_error(const AString & err_msg, eAErrLevel level = AErrLevel_error);
      static void    set_print_func(tSSPrintFunc * log_func_p);
      static void    register_print_with_agog();
      static void    suppress_prints(bool suppress)                             { ms_suppress_prints = suppress; }

      #if (SKOOKUM & SS_CODE_IN)
        static void  print_parse_error(SSParser::eResult result, const AString & path = AString::ms_empty, const AString * code_p = nullptr, uint32_t result_pos = 0u, uint32_t result_start = ADef_uint32, uint32_t start_pos = 0u);
        static void  print_parse_error(const SSParser::Args & args, const AString & path = AString::ms_empty, const AString * code_p = nullptr, uint32_t start_pos = 0u)  { print_parse_error(args.m_result, path, code_p, args.m_end_pos, args.m_start_pos, start_pos); }
      #endif

      #if (SKOOKUM & SS_DEBUG)
        static void context_append(AString * str_p);
      #endif

    // Debug Memory

      static void     print_memory(eSSCodeSerialize type = SSCodeSerialize_static_demand);
      static uint32_t print_memory_runtime();
      static uint32_t print_memory_code(eSSCodeSerialize type = SSCodeSerialize_static_demand, SSClass * from_class_p = nullptr, eAHierarchy iterate = AHierarchy__all);
      static void     set_print_memory_ext_func(AFunctionBase * mem_func_p)         { ms_print_mem_ext_p = mem_func_p; }


    // Debugging

      #if defined(SSDEBUG_COMMON)
        static void set_flag(eFlag debug_flag, bool enable = true);
      #endif

      #if (SKOOKUM & SS_DEBUG)
        static eState               get_execution_state()                       { return ms_exec_state; }
        static SSMemberExpression & get_next_expression()                       { return ms_next_expr; }
        static SSInvokedBase *      get_next_invokable();
        static uint32_t             get_preferences()                           { return ms_pref_flags; }

        static void break_expression(SSObjectBase * scope_p, SSInvokedBase * caller_p, SSExpressionBase * expr_p);
        static void break_invokable(SSInvokedBase * invoked_p);
        static void enable_preference(ePrefFlag preference, bool enable = true);
        static void invalidate_next_expression();
        static bool is_active_member(const SSMemberInfo & member)               { return member.is_valid() && ms_next_expr.is_valid() && (member == ms_next_expr); }
        static bool is_preference(ePrefFlag preference)                         { return (ms_pref_flags & preference) != 0u; }
        static void set_execution_state(eState state)                           { ms_exec_state = state; }
        static void set_next_expression(const SSMemberExpression & expr_info);
        static void set_next_expression(SSObjectBase * scope_p, SSInvokedBase * caller_p, SSExpressionBase * expr_p);
        static void set_preferences(uint32_t pref_flags)                        { ms_pref_flags = pref_flags; }
        static void step(eStep step_type);
      #endif  // (SKOOKUM & SS_DEBUG)

    // Breakpoints

      #if (SKOOKUM & SS_DEBUG)

        static SSBreakPoint * breakpoint_append(const SSMemberExpression & bp_info, uint32_t table_idx, bool enabled = true);
        static SSBreakPoint * breakpoint_append_absent(const SSMemberInfo & member_info, uint source_idx, bool * appended_p = nullptr);
        static SSBreakPoint * breakpoint_append_absent(const SSMemberInfo & member_info, SSExpressionBase * break_expr_p, bool * appended_p = nullptr);
        static uint32_t       breakpoint_get_count()                            { return ms_breakpoints.get_length(); }
        static bool           breakpoint_remove(const SSBreakPoint & bp);
        static bool           breakpoint_remove_by_expr(const SSExpressionBase & expr);
        static void           breakpoint_enable_all();
        static void           breakpoint_disable_all();
        static void           breakpoint_remove_all();
        static void           breakpoint_list_all();

        static bool breakpoint_is_on_class(const SSClass & ssclass);
        static bool breakpoint_is_on_member(const SSMemberInfo & member_info);
        static bool breakpoint_is_on_expr(const SSExpressionBase & expr);

        static void                   breakpoint_get_all_by_member(tSSBreakPoints * bps_p, const SSMemberInfo & member_info);
        static const tSSBreakPoints & breakpoint_get_all_by_member(const SSMemberInfo & member_info);
        static SSBreakPoint *         breakpoint_get_by_expr(const SSExpressionBase & expr);
        static SSBreakPoint *         breakpoint_get_at_idx(uint32_t table_idx) { return (table_idx < SSDebugInfo::Flag_debug_idx__none) ? ms_breakpoint_table.get_at(table_idx) : nullptr; }

        static const APSortedLogicalFree<SSBreakPoint, SSMemberExpression> & breakpoints_get_all()  { return ms_breakpoints; }

      #endif  // (SKOOKUM & SS_DEBUG)


    // Breakpoints - Scripted

      static void set_scripted_break(void (*scripted_break_f)(const AString & message, SSInvokedMethod * scope_p))    { ms_scripted_break_f = scripted_break_f; }

    // Execution Hooks

      #if defined(SSDEBUG_COMMON)
        static void set_hook_expr(void (*expr_dbg_f)(SSExpressionBase * expr_p, SSObjectBase * scope_p, SSInvokedBase * caller_p) = nullptr);
        static void hook_expression(SSExpressionBase * expr_p, SSObjectBase * scope_p, SSInvokedBase * next_caller_p);
      #endif
          
      #if defined(SSDEBUG_HOOKS)

        static void            append_hook(const Hook & hook, bool auto_enable = true);
        static const Hook *    copy_hook(const ASymbol & hook_name, const AString & new_name);
        static void            enable_hook(const ASymbol & hook_name, bool enable = true);
        static void            enable_hook(Hook * hook_p, bool enable);
        static void            hook_condition_scope_actor(const ASymbol & hook_name, const ASymbol & actor_name);
        static void            hook_condition_invoked_caller(const ASymbol & hook_name, SSInvokedContextBase * caller_p);
        static void            hook_condition_updater_class(const ASymbol & hook_name, SSClass * class_p, bool subclass_check);
        static void            remove_hook(const ASymbol & hook_name);
        static bool            is_hook_enabled(const ASymbol & hook_name);
        static const Hook *    get_hook(const ASymbol & hook_name)            { return ms_hooks.get(hook_name); }
        static const ASymbol & get_hook_script_origin()                       { return ms_hook_script_origin_stack[ms_hook_script_origin_idx]; }

        static const APSortedLogicalFree<Hook, ASymbol> & get_hooks()         { return ms_hooks; }

        // Example/built-in Hooks

          static void hook_examples();
          static void hook_trace_method(SSInvokedMethod * imethod_p);
          static void hook_trace_coroutine(SSInvokedCoroutine * icoro_p);
          static void hook_trace_script_entry(const ASymbol & origin_id);
          static void hook_trace_script_exit(const ASymbol & origin_id);

        // Called by system - do not call manually.  [Public by necessity - see SSDEBUG_HOOK_*() macros.]

          static void hook_method(SSInvokedMethod * imethod_p);
          static void hook_coroutine(SSInvokedCoroutine * icoro_p);
          static void hook_script_origin_push(const ASymbol & origin_id);
          static void hook_script_origin_pop();

      #endif // SSDEBUG_HOOKS

  protected:

  // Internal Class Methods

    static void breakpoint_hit_embedded_def(SSExpressionBase * expr_p, SSObjectBase * scope_p, SSInvokedBase * caller_p);

  // SkookumScript Atomic Methods

    static void mthdc_break(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_callstack(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_callstack_str(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_copy_hook(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_enable_hook(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_engine_presentQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_hook_names(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_hook_condition_scope_actor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_hook_condition_invoked_caller(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_hook_condition_updater_class(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_hook_enabledQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_print(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_println(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthdc_sym_to_str(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  // Class Data Members

    // If true, the engine/game is present/hooked-in and if false it is not present.
    // This value is tested by Debug@is_engine_present()
    static bool ms_engine_present_b;

    // Printing

      static bool                    ms_suppress_prints;
      static tSSPrintFunc *          ms_log_func_p;
      static AFreePtr<AFunctionBase> ms_print_mem_ext_p;

    #if (SKOOKUM & SS_DEBUG)

    // Preferences

      // See ePrefFlag
      static uint32_t ms_pref_flags;

    // Execution Info

      // Runtime Execution Debug state
      static eState ms_exec_state;
      
      // Next member expression to execute - generally the expression that the runtime
      // is suspended/broken on.  Also see ms_current_call_p
      static SSMemberExpression ms_next_expr;

      // Current invokable that is sacrosanct to step-wise debugging - ms_current_call_p can change or be lost
      static AIdPtr<SSInvokedBase> ms_next_invokable_p;

      // See eStep
      static eStep ms_step_type;

      static AIdPtr<SSInvokedContextBase> ms_step_icontext_p;
      static AIdPtr<SSInvokedBase>        ms_step_caller_p;
      static SSExpressionBase *           ms_step_expr_p;

    // Breakpoints
    
      // Breakpoints stored by index position - may be sparse with nullptr at unused indexes.
      // Index position is cached in breakpoint objects and used as a breakpoint "id".
      static APArray<SSBreakPoint> ms_breakpoint_table;

      // Breakpoints sorted by member expression info
      static APSortedLogicalFree<SSBreakPoint, SSMemberExpression> ms_breakpoints;

    #endif  // (SKOOKUM & SS_DEBUG)

      static void (* ms_scripted_break_f)(const AString & message, SSInvokedMethod * scope_p);

    // Execution Hooks
    #if defined(SSDEBUG_HOOKS)
      static ASymbol  ms_hook_script_origin_stack[8u];  // Shouldn't need to be too deep
      static uint32_t ms_hook_script_origin_idx;

      // Expression Debugger Function pointer
      static void (* ms_hook_expr_f)(SSExpressionBase * expr_p, SSObjectBase * scope_p, SSInvokedBase * caller_p);

      static APSortedLogicalFree<Hook, ASymbol> ms_hooks;
      static AList<Hook, tSSMethodHook>         ms_hook_methods;
      static AList<Hook, tSSCoroutineHook>      ms_hook_coroutines;
      static AList<Hook, tSSScriptSystemHook>   ms_hook_origins;
    #endif

    #if defined(SSDEBUG_COMMON)
      // Debugging flags - see SSDebug::eFlag
      static uint32_t ms_flags;
    #endif

  };  // SSDebug


#if (SKOOKUM & SS_DEBUG)

//=======================================================================================
// SSBreakPoint Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// # Author(s): Conan Reis
inline void SSBreakPoint::remove()
  {
  SSDebug::breakpoint_remove(*this);
  }

//---------------------------------------------------------------------------------------
// # Author(s): Conan Reis
inline SSBreakPoint::~SSBreakPoint()
  {
  }

#endif  // (SKOOKUM & SS_DEBUG)


//=======================================================================================
// SSDebug Inline Methods
//=======================================================================================

#if defined(SSDEBUG_COMMON)

//---------------------------------------------------------------------------------------
// Sets debug flag - see SSDebug::eFlag
// # Modifiers: static
// # Author(s): Conan Reis
inline void SSDebug::set_flag(
  eFlag debug_flag,
  bool  enable // = true
  )
  {
  ms_flags = enable ? (ms_flags | debug_flag) : (ms_flags & ~debug_flag);

  // Test all expressions?
  ms_expr_hook_flag = ((ms_flags & Flag__test_expression_mask) != 0u)
    ? SSDebugInfo::Flag_debug_enabled
    : SSDebugInfo::Flag_debug_disabled;
  }

//---------------------------------------------------------------------------------------
// Sets the expression debugger hook function.  It is called within each
//             expression's invoke() method just prior to actually invoking the
//             expression.
// Arg         expr_dbg_f - expression debugger function to set
// # See:      breakpoint_hit_embedded_def() - explains the arguments
// # Notes:    In addition to any custom tests, an expression's debug data can be tested
//             for interesting values.  For example ExpressionBase::m_debug_info can be
//             tested to see if its SSDebugInfo::Flag_debug_enabled flag is set.
// # Author(s): Conan Reis
inline void SSDebug::set_hook_expr(
  void (*expr_dbg_f)(SSExpressionBase * expr_p, SSObjectBase * scope_p, SSInvokedBase * caller_p) // = nullptr
  )
  {
  ms_hook_expr_f = expr_dbg_f;
  set_flag(Flag_hook_expression, expr_dbg_f != nullptr);
  }

#endif  // SSDEBUG_COMMON


#endif  // __SSDEBUG_HPP


