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


#ifndef __SSBRAIN_HPP
#define __SSBRAIN_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/APSorted.hpp>
#include <AgogCore/ASymbol.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class AFunctionBase;
class SSObjectBase;
class SSInstance;

#ifdef A_PLAT_PC
  template<class _ElementType, class _KeyType = _ElementType, class _CompareClass = ACompareAddress<_KeyType> > class APArrayFree;
#else
  #include <AgogCore/APArray.hpp>
#endif

// Shorthand
typedef APSortedLogical<SSClass, ASymbol> tSSClasses;


//---------------------------------------------------------------------------------------
// Notes      The "Brain" class - holds class hierarchy and other misc. objects that do
//            not have an obvious home elsewhere.
// See Also   SSClass (and other classes)
// Author(s)  Conan Reis
class SSBrain
  {
  public:
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Nested Structures

    // AEx<SSBrain> exception id values
    enum
      {
      ErrId_superclass_mismatch = AErrId_last,  // Tried to create same Class with different superclasses
      ErrId_no_superclass                       // Requested superclass does not exist
      };

    // Header for compiled binary code
    struct BinHeader
      {
      // Compiled binary code id
      uint32_t m_id;

      // Folder checksum from source scripts
      uint32_t m_checksum_folders;

      // File checksum from source scripts
      uint32_t m_checksum_files;
      };


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Public Class Data Members (for quick access)

    // Common Classes

      static SSClass * ms_boolean_class_p;
      static SSClass * ms_char_class_p;
      static SSClass * ms_class_class_p;  // In practice, the metaclass "<Object>" is used instead of "Class"
      static SSClass * ms_closure_class_p;
      static SSClass * ms_integer_class_p;
      static SSClass * ms_invoked_base_class_p;
      static SSClass * ms_invoked_context_base_class_p;
      static SSClass * ms_invoked_method_class_p;
      static SSClass * ms_invoked_coroutine_class_p;
      static SSClass * ms_list_class_p;
      static SSClass * ms_none_class_p;
      static SSClass * ms_object_class_p;
      static SSClass * ms_real_class_p;
      static SSClass * ms_string_class_p;
      static SSClass * ms_symbol_class_p;
      static SSClass * ms_mind_class_p;
      static SSClass * ms_master_class_p;
      static SSClass * ms_actor_class_p;

    // Generic/Reflective Classes

      static SSClass * ms_auto_class_p;  // Auto_
      static SSClass * ms_this_class_p;  // ThisClass_
      static SSClass * ms_item_class_p;  // ItemClass_

    // Global Instances

      static SSInstance * ms_nil_p;  // The single instance of the None object

    // File management members

      // Checksums for tracking changes on the source folders and files that define the
      // class hierarchy.  Used for quick dependency checking when determining whether the
      // compiled code binary is up-to-date with the source scripts.
      static uint32_t ms_checksum_folders;
      static uint32_t ms_checksum_files;


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // Conversion Methods

    #if (SKOOKUM & SS_COMPILED_OUT)

      static void     as_binary(void ** binary_pp);
      static uint32_t as_binary_length();

    #endif // (SKOOKUM & SS_COMPILED_OUT)


    #if (SKOOKUM & SS_COMPILED_IN)

      static void      assign_binary(const void ** binary_pp);
      static void      assign_binary_class_hier(const void ** binary_pp, SSClass * superclass_p);
      static eAEquate  is_binary_valid(const void * binary_p);
      static eAEquate  is_binary_id_valid(uint32_t bin_id);

    #endif // (SKOOKUM & SS_COMPILED_IN)

  // Class Methods

    static SSClass * create_class(const ASymbol & class_name, SSClass * superclass_p = ms_object_class_p, uint32_t flags = ADef_uint32, bool append_super_members = false);
    static SSClass * create_class(const ASymbol & class_name, const ASymbol & superclass_name, uint32_t flags = ADef_uint32, bool append_super_members = false);
    static SSClass * get_class(const ASymbol & class_name);
    static SSClass * get_class(const char * class_name_p);
    static bool      is_class_present(const ASymbol & class_name);

    static const tSSClasses & get_classes()  { return ms_classes; }


    // Initialization

    static void register_bind_atomics_func(void (*bind_atomics_f)());
    static void initialize_pre_load(uint32_t ensure_class_count);
    static void initialize_after_classes_known(const ASymbol & startup_class_name);
    static void initialize_post_load();
    static void initialize_classes();
    static void deinitialize_classes();
    static void deinitialize();

    #if (SKOOKUM & SS_DEBUG)

      static void ensure_atomics_registered(SSClass ** ignore_classes_pp = nullptr, uint32_t ignore_count = 0u);

    #endif // (SKOOKUM & SS_DEBUG)

  protected:

  // Internal Class Methods

    static APArrayFree<AFunctionBase> * get_bind_funcs();


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Class Data Members

    static tSSClasses ms_classes;

  };  // SSBrain


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSBrain.inl"
#endif


#endif  // __SSBRAIN_HPP

