//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Integer (signed 32-bit integer) class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSINTEGER_HPP
#define __SSINTEGER_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClassDescBase;
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Atomic Integer (signed 32-bit integer) class
// Author(s)  Conan Reis
class SSInteger
  {
  public:
  
  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(SSIntegerType value);


    // SkookumScript Atomic Methods

      static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_Boolean(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_Integer(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_Real(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

      static void mthd_abs(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_betweenQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_and(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_not(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_or(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_shift_down(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_shift_up(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_xor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_bit_setQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_clamp(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_max(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_min(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_mod(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_negate(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_pow2Q(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_sign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
      static void mthd_swap(SSInvokedMethod * scope_p, SSInstance ** result_pp);

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

  };  // SSInteger


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSInteger.inl"
#endif


#endif  // __SSINTEGER_HPP

