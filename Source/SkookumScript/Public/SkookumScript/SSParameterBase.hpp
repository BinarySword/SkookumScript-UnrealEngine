//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Parameter Abstract Base Class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSPARAMETERBASE_HPP
#define __SSPARAMETERBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ANamed.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSExpressionBase;

// SSParameterBase enumerated constants
enum
  {
  // Number of bits used by the eSSParameter when in binary form.  If changed,
  // SSGroupParam_max_class_count defined in SkookumScript/SSGroupParam.h should also change.
  SSParam_type_bits = 2,
  // Bit mask for type info when in binary form
  SSParam_type_mask = 3
  };

// Possible parameter types
enum eSSParameter
  {
  SSParameter_unary                = 0,    // Unary parameter without a default expression
  SSParameter_unary_default        = 1,    // Unary parameter with a default expression using method's scope when evaluated (->)
  //SSParameter_unary_default_caller = 2,  // $Note - CReis Future - Unary parameter with a default expression using the caller's scope when evaluated (=>)
  SSParameter_group                = 3     // Variable length parameter that is grouped into a single List argument
  };

//---------------------------------------------------------------------------------------
// Notes      Parameter Abstract Base Class
// Subclasses SSUnaryParam, SSGroupParam
// Author(s)  Conan Reis
class SSParameterBase : public ANamed
  {
  public:

  // Common Methods

    explicit SSParameterBase(const ASymbol & name = ASymbol::get_null());
    virtual ~SSParameterBase();

  // Comparison Methods
  
    virtual bool compare_equal(const SSParameterBase & param) const = 0;
    virtual bool compare_less(const SSParameterBase & param) const = 0;

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_OUT)

      virtual void     as_binary(void ** binary_pp) const = 0;
      virtual uint32_t as_binary_length() const = 0;

      // Also see from_binary_new()

    #endif // (SKOOKUM & SS_COMPILED_OUT)


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const = 0;
    #endif


  // Methods

    virtual SSExpressionBase * get_default_expr() const  { return nullptr; }
    virtual eSSParameter       get_kind() const = 0;
    virtual bool               is_defaultable() const = 0;
    virtual void               track_memory(AMemoryStats * mem_stats_p) const = 0;

    // Type-checking Methods

      virtual SSParameterBase * as_finalized_generic(const SSClassDescBase & scope_type) const = 0;
      virtual SSClassDescBase * get_expected_type() const = 0;
      virtual bool              is_generic() const = 0;

  // Class Methods

    #if (SKOOKUM & SS_COMPILED_IN)
      static SSParameterBase * from_binary_new(const void ** binary_pp);
    #endif

  };  // SSParameterBase


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
//  Constructor
// # Returns:   itself
// Arg          name - name of the parameter (Default ASymbol::ms_null)
// # Author(s):  Conan Reis
inline SSParameterBase::SSParameterBase(
  const ASymbol & name // = ASymbol::ms_null
  ) :
  ANamed(name)
  {
  }


#endif  // __SSPARAMETERBASE_HPP

