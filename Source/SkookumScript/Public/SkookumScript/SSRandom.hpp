//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Random Number Generator class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSRANDOM_HPP
#define __SSRANDOM_HPP


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
// Notes      SkookumScript Atomic Random Number Generator class.  It is high speed and
//            seed driven (allowing the reproduction of generated sequences).
// Author(s)  Conan Reis
class SSRandom
  {
  public:
 
  // Class Methods

    static void register_bindings();

  protected:

  // Internal Class Methods

    // SkookumScript Atomic Methods

    static void mthd_constructor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_seed(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_seed(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_seed_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_coin_toss(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_uniform_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_triangle_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_normal_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_up_slope_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_down_slope_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_thorn_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_nose_int(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_uniform(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_uniform_symm(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_triangle(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_triangle_symm(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_normal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_up_slope(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_down_slope(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_thorn(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_nose(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSRandom


//=======================================================================================
// Inline Methods
//=======================================================================================



#endif  // __SSRANDOM_HPP

