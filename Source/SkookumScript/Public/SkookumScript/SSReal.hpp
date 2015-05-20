//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Real (floating point) class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSREAL_HPP
#define __SSREAL_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Atomic Real (floating point) class
// Author(s)  Conan Reis
class SSReal
  {
  public:
  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(SSRealType value);

  protected:

  // Internal Class Methods

    // SkookumScript Atomic Methods

    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_Integer(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_betweenQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_clamp(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_max(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_min(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_negate(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_negated(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_increment(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_decrement(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_subtract(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_subtract_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_multiply(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_multiply_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_divide(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_divide_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_greater(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_greater_or_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_less(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_less_or_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    // Scalar Math


      //static void mthd_as_int_floor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_as_int_ceil(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_as_int_trunc(SSInvokedMethod * scope_p, SSInstance ** result_pp);

      //static void mthd_abs(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_cube(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_reciprocal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_sqr(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_sqrt(SSInvokedMethod * scope_p, SSInstance ** result_pp);

      //static void mthd_sin(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_cos(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_tan(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_asin(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      //static void mthd_acos(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSReal


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSReal.inl"
#endif


#endif  // __SSREAL_HPP

