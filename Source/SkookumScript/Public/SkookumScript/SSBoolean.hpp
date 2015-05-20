//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic Boolean (true/false) class - allows short circuit
//             evaluation.
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSBOOLEAN_HPP
#define __SSBOOLEAN_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSInstance.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

class SSInvokedMethod;  // Pre-declaration

//---------------------------------------------------------------------------------------
// Notes      SkookumScript Atomic Boolean (true/false) - allows short circuit evaluation.
//            Has same data as SSInstance - only differs in that it has a different
//            virtual method table.
// Author(s)  Conan Reis
class SSBoolean : public SSInstance
  {
  public:

    SS_NEW_OPERATORS(SSBoolean);

  // Methods

    bool is_true();
    bool is_false();

    // Overridden from SSInstance

      virtual void method_invoke(const SSMethodCall & mcall, SSObjectBase * scope_p, SSInvokedBase * caller_p, SSInstance ** result_pp);
      virtual void on_no_references();
      virtual void pool_delete();

    // Overridden from SSObjectBase

      virtual uint32_t get_obj_type() const  { return SSObjectType_boolean; } 

  // Class Methods

    static SSBoolean *                pool_new(SSBooleanType bool_value);
    static AObjReusePool<SSBoolean> & get_pool();
    static void                       init_pool(SSClass * bool_class_p);

    static void register_bindings();

  protected:


  // Internal Methods

    friend class AObjBlock<SSBoolean>;  // So it can be accessed only by pool_new()

    SSBoolean();

  // Internal Class Methods

    // SkookumScript Atomic Methods

    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_Integer(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_string(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_not(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_nxor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_xor(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    // Defined internally in method_invoke() to allow short circuit evaluation
    //static void mthd_op_and(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_op_or(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_op_nand(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_op_nor(SSInvokedMethod * scope_p, SSInstance ** result_pp);


  // Data Members

  // Class Data Members

  };  // SSBoolean


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSBoolean.inl"
#endif


#endif  // __SSBOOLEAN_HPP

