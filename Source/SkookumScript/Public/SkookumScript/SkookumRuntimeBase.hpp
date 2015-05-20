//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// The "Brain" class - holds class hierarchy and other misc. objects that do
//             not have an obvious home elsewhere.
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SKOOKUMRUNTIMEBASE_HPP
#define __SKOOKUMRUNTIMEBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ASymbol.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

enum eSSLoadStatus
  {
  SSLoadStatus_ok,
  SSLoadStatus_stale,
  SSLoadStatus_runtime_old,
  SSLoadStatus_not_found,
  SSLoadStatus_debug_info_not_found
  };

//---------------------------------------------------------------------------------------
// Stores binary info memory pointer - used with the SkookumRuntimeBase get_binary*() and
// release_binary() methods.
// If needed, subclass this class for subclasses of SkookumRuntimeBase to add user /
// platform / project specific handle / pointer to manage the memory - for example a file
// handle.
struct SSBinaryHandle
  {
  // Public Data

    // Pointer to memory this handle represents
    void * m_binary_p;

    // Size of memory in bytes
    // [Could be 64-bit though Skookum binary files should not need to be over 4GB.]
    uint32_t m_size;

  // Public Methods

    // Ensures proper destructor call if subclassed
    virtual ~SSBinaryHandle() {}
  };

//---------------------------------------------------------------------------------------
// Abstract base object for platform/OS specific / IO-based functions needed by Skookum
// for debugging and other tasks.  Derive a subclass and instantiate it prior to using
// Skookum.  Each method should be overridden as needed.  
// 
// Other areas that have external function hooks:
//   - Agog::dprint()
//   - A_BREAK
//   - memory allocate/deallocate, etc.
//   - SkookumRemoteBase socket functionality + spawn remote IDE
//   - SSDebug execution hooks
class SkookumRuntimeBase
  {
  public:

  // Class Data Members

    static SkookumRuntimeBase * ms_default_p;

  // Methods

    SkookumRuntimeBase();
    ~SkookumRuntimeBase();

    // Binary Serialization / Loading Overrides

      virtual bool             is_binary_hierarchy_existing() = 0;
      virtual SSBinaryHandle * get_binary_hierarchy() = 0;
      virtual SSBinaryHandle * get_binary_class_group(const SSClass & cls) = 0;

      // Only needed for debugging - not needed in user/final/release build
      #if (SKOOKUM & SS_DEBUG) && defined(A_SYMBOL_STR_DB)
  
        virtual SSBinaryHandle * get_binary_symbol_table() = 0;
      #endif

      virtual void release_binary(SSBinaryHandle * handle_p) = 0;

    // Script Loading / Binding

      eSSLoadStatus load_compiled_hierarchy();
      virtual void  load_compiled_class_group(SSClass * class_p);
      void          load_compiled_class_group_all();
      virtual void  on_bind_routines();

    // Flow Methods

      virtual void on_init()           {}
      virtual void on_deinit()         {}

      // Update methods (in order of preference)
      // - just use *one* of these (the most convenient version) once an update

        static void update(uint64_t sim_ticks, f64 sim_time, f32 sim_delta);
        static void update(uint64_t sim_ticks);
        static void update(float sim_delta);

  protected:

    // Internal class methods

      static void bind_routines();
  };


#endif  // __SKOOKUMRUNTIMEBASE_HPP

