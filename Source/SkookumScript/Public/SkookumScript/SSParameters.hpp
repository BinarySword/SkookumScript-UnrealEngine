//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Formal Parameter List/Interface Class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSPARAMETERS_HPP
#define __SSPARAMETERS_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/APSorted.hpp>
#include <AgogCore/APCompactArray.hpp>
#include <AgogCore/ARefCount.hpp>
#include "SkookumScript/SSMemberInfo.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declaration
struct SSApplyExpressionBase;
class  SSClassDescBase;
class  SSParameterBase;
class  SSParser;
struct SSTypedName;

typedef APCompactArrayLogical<SSParameterBase, ASymbol> tSSParamList;
typedef APCompactArrayLogical<SSTypedName, ASymbol>     tSSParamReturnList;


//---------------------------------------------------------------------------------------
// Notes      Formal Parameter/Interface List - used by SSInvokableBase [SSMethodBase
//            (SSMethod, SSMethodFunc, SSMethodMthd), SSCoroutineBase (SSCoroutine,
//            SSCoroutineMthd, SSCoroutineFunc)]
// Author(s)  Conan Reis
class SSParameters : public ARefCountMix<SSParameters>
  {
  friend class SSParser;  // For quick access during construction with parsing

  public:

  // Nested Structures

    enum eStrFlag
      {
      StrFlag_return      = 1 << 0,  // Include return type
      StrFlag_names_only  = 1 << 1,  // Only output parameter names - no type info or default

      StrFlag__default           = StrFlag_return,
      StrFlag__default_no_return = 0x0,
      StrFlag__simple            = StrFlag_return | StrFlag_names_only
      };

    // Used to differentiate between the 2 parameter types
    enum eType
      {
      Type_send,   // Send parameter prior to ;
      Type_return  // Return parameter following ;
      };

  // Public Class Data

    // $Revisit - CReis Temp count of parameter lists with defaults
    static uint32_t ms_param_count;

  // Common Methods

    SS_NEW_OPERATORS(SSParameters);
    SSParameters();
    ~SSParameters();


  // Comparison Methods

    bool operator==(const SSParameters & params) const;
    bool operator<(const SSParameters & params) const;
    bool is_valid_arg_to(const SSParameters & params) const;


  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_OUT)
      void     as_binary(void ** binary_pp) const;
      uint32_t as_binary_length() const;
    #endif


    #ifdef SS_AS_STRINGS
      AString as_code(uint32_t str_flags = StrFlag__default) const;
    #endif

  // Methods

    // Debugging Methods
    #if (SKOOKUM & SS_DEBUG)
      SSExpressionBase * find_expr_by_pos(uint32_t source_idx, eSSExprFind type = SSExprFind_all) const;
      eAIterateResult    iterate_expressions(SSApplyExpressionBase * apply_expr_p, const SSInvokableBase * invokable_p = nullptr);
    #endif

    SSParameters &             assign(SSParameters * parms_p);
    uint                        get_arg_count_min() const;
    uint                        get_arg_count_min_after_arg1() const;
    const tSSParamList &       get_param_list() const                 { return m_params; }
    const tSSParamReturnList & get_param_return_list() const          { return m_return_params; }
    SSClassDescBase *          get_result_class() const;
    bool                       is_defaulted() const;
    bool                       is_result_params() const               { return m_return_params.is_filled(); }
    bool                       is_sharable() const;
    void                       set_result_type(const SSClassDescBase & rclass);
    void                       track_memory(AMemoryStats * mem_stats_p) const;

    // Type-checking Methods

      bool           is_generic() const;
      bool           is_last_closure() const;
      SSParameters * as_finalized_generic(const SSClassDescBase & scope_type) const;

  // Class Methods

    static SSParameters * get_or_create(SSParameters * params_p);
    static SSParameters * get_or_create(SSClassDescBase * result_type_p, SSParameterBase * param_p = nullptr);

    #if (SKOOKUM & SS_COMPILED_IN)
      static SSParameters * get_or_create(const void ** binary_pp);
    #endif

    static void shared_empty()               { ms_shared_params.free_all(); }  
    static void shared_ensure_references();
    static void shared_track_memory(AMemoryStats * mem_stats_p);


  protected:

  // Internal Methods

    SSParameters(SSClassDescBase * result_type_p, SSParameterBase * param_p);
    explicit SSParameters(SSParameters * params_p);

    #if (SKOOKUM & SS_COMPILED_IN)
      SSParameters(const void ** binary_pp);
    #endif

  // Data Members

    // Send Parameters (incoming/outgoing) Dynamically allocated unary and group parameters
    tSSParamList m_params;

	// Optional Return Parameters (outgoing only)
    tSSParamReturnList m_return_params;

    // Return type (outgoing only)
    // $Revisit - CReis In theory this hint should not be needed during run-time if not
    // debugging or parsing - i.e. if only SS_COMPILED_IN is defined.  Currently only used
    // if SS_CODE_IN, SS_CODE_OUT or SS_COMPILED_OUT is defined.]
    ARefPtr<SSClassDescBase> m_result_type_p;


  // Class Data Members

    static APSortedLogical<SSParameters> ms_shared_params;

  };  // SSParameters


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSParameters.inl"
#endif


#endif  // __SSPARAMETERS_HPP

