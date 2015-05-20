//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Runtime Hooks for Unreal - Input/Output Init/Update/Deinit Manager
// 
// #Author(s):  Conan Reis
//=======================================================================================


#ifndef __SSUERUNTIME_HPP
#define __SSUERUNTIME_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <SkookumScript/SkookumRuntimeBase.hpp>
#include "../SkookumScriptListenerManager.hpp"

#include "Platform.h"  // Set up base types, etc for the platform


//=======================================================================================
// Global Structures
//=======================================================================================

//---------------------------------------------------------------------------------------
// SkookumScript Runtime Hooks for Unreal
// - Input/Output Init/Update/Deinit Manager
class SSUERuntime : public SkookumRuntimeBase
  {
  public:

    static SSUERuntime * get_singleton() { return static_cast<SSUERuntime *>(SkookumRuntimeBase::ms_default_p); }

  // Methods

    SSUERuntime() : m_compiled_file_b(false), m_listener_manager(256, 256) { ms_default_p = this; }
    ~SSUERuntime() {}

    // Script Loading / Binding

      const FString & get_compiled_path() const;

      bool load_compiled_scripts(bool ensure_atomics = true, SSClass ** ignore_classes_pp = nullptr, uint32_t ignore_count = 0u);

    // Overridden from SkookumRuntimeBase

      // Binary Serialization / Loading Overrides

        virtual bool             is_binary_hierarchy_existing() override;
        virtual SSBinaryHandle * get_binary_hierarchy() override;
        virtual SSBinaryHandle * get_binary_class_group(const SSClass & cls) override;
        virtual void             release_binary(SSBinaryHandle * handle_p) override;

        // Only needed for debugging - not needed in user/final/release build
        #if (SKOOKUM & SS_DEBUG) && defined(A_SYMBOL_STR_DB)
  
          virtual SSBinaryHandle * get_binary_symbol_table() override;
        #endif

      // Flow Methods

        virtual void on_init() override;
        virtual void on_bind_routines() override;
        virtual void on_deinit() override;

      // Accessors

        SkookumScriptListenerManager * get_listener_manager() { return &m_listener_manager; }

  protected:

    // Internal class methods

      static void deinit();

    // Data Members

      mutable bool        m_compiled_file_b;
      mutable FString     m_compiled_path;

      SkookumScriptListenerManager m_listener_manager;

  };  // SSUERuntime


//=======================================================================================
// Inline Methods
//=======================================================================================


#endif  // __SSUERUNTIME_HPP

