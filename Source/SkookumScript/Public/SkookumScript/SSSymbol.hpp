//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Manages Symbols for SkookumScript
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSSYMBOL_HPP
#define __SSSYMBOL_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/ASymbolTable.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Macros / Defines
//=======================================================================================

//---------------------------------------------------------------------------------------
// These Macros will expand to create constants of type ASymbol in the form:
//   ASYM(Object) -> ASymbol_Object  // Representing the symbol 'Object'
//
// Extra care should be taken when using them during global initialization time.
//
// Eventually, in release builds, these could be just be numerical ids and AString objects
// will be dropped all together.
//
// Try to keep them in alphabetical order so that they are easy to scan at a glance.
//
#define SS_SYMBOLS \
  ASYM(Actor) \
  ASYM(Auto_) \
  ASYM(Boolean) \
  ASYM(Char) \
  ASYM(Class) \
  ASYM(Closure) \
  ASYM(Debug) \
  ASYM(Data) \
  ASYM(DataC) \
  ASYM(Filter) \
  ASYM(Integer) \
  ASYM(InvokedBase) \
  ASYM(InvokedContextBase) \
  ASYM(InvokedMethod) \
  ASYM(InvokedCoroutine) \
  ASYM(ItemClass_) \
  ASYM(List) \
  ASYM(Master) \
  ASYM(Mind) \
  ASYM(None) \
  ASYM(Object) \
  ASYM(Random) \
  ASYM(Real) \
  ASYM(String) \
  ASYM(Symbol) \
  ASYM(ThisClass_) \
  ASYM(TriggerInVehicle) \
  ASYM(TriggerOnBike) \
  ASYM(TriggerOnFoot) \
  ASYM(_Class) \
  ASYM(_Focus) \
  ASYM(_Named) \
  ASYM(_Player) \
  ASYM(_This) \
  ASYM(_anon) \
  ASYM(_closure) \
  ASYM(_pulse) \
  ASYM(_wait) \
  ASYM(_wait_until) \
  ASYM(_user_) \
  ASYM(add) \
  ASYM(add_assign) \
  ASYM(and) \
  ASYM(append) \
  ASYM(append_items) \
  ASYM(append_list) \
  ASYM(as_new) \
  ASYM(as_code) \
  ASYM(assign) \
  ASYM(at) \
  ASYM(at_set) \
  ASYM(branch) \
  ASYM(case) \
  ASYM(closure) \
  ASYM(coin_toss) \
  ASYM(crop) \
  ASYM(decrement) \
  ASYM(divert) \
  ASYM(divide) \
  ASYM(divide_assign) \
  ASYM(down_slope) \
  ASYM(down_slope_int) \
  ASYM(else) \
  ASYM(empty) \
  ASYM(exit) \
  ASYM(false) \
  ASYM(find_named) \
  ASYM(first) \
  ASYM(if) \
  ASYM(increment) \
  ASYM(insert) \
  ASYM(insert_items) \
  ASYM(insert_list) \
  ASYM(invoke_script_) \
  ASYM(items_set) \
  ASYM(last) \
  ASYM(length) \
  ASYM(length_after) \
  ASYM(loop) \
  ASYM(multiply) \
  ASYM(multiply_assign) \
  ASYM(name) \
  ASYM(nand) \
  ASYM(negated) \
  ASYM(nil) \
  ASYM(nor) \
  ASYM(normal) \
  ASYM(normal_int) \
  ASYM(nose) \
  ASYM(nose_int) \
  ASYM(not) \
  ASYM(nxor) \
  ASYM(or) \
  ASYM(origin_actor_update) \
  ASYM(origin_class_ctors) \
  ASYM(origin_default_ctor) \
  ASYM(origin_embedded1) \
  ASYM(origin_embedded2) \
  ASYM(origin_embedded3) \
  ASYM(origin_embedded4) \
  ASYM(origin_embedded5) \
  ASYM(origin_parser_interpreted) \
  ASYM(pop_at) \
  ASYM(pop_first) \
  ASYM(pop_last) \
  ASYM(pop_range) \
  ASYM(pop_range_last) \
  ASYM(race) \
  ASYM(range) \
  ASYM(remove_at) \
  ASYM(remove_first) \
  ASYM(remove_last) \
  ASYM(remove_range) \
  ASYM(remove_range_last) \
  ASYM(reuse) \
  ASYM(reverse) \
  ASYM(rotate_down) \
  ASYM(rotate_up) \
  ASYM(seed) \
  ASYM(seed_set) \
  ASYM(subtract) \
  ASYM(subtract_assign) \
  ASYM(swap) \
  ASYM(sync) \
  ASYM(this) \
  ASYM(this_class) \
  ASYM(this_code) \
  ASYM(thorn) \
  ASYM(thorn_int) \
  ASYM(triangle) \
  ASYM(triangle_int) \
  ASYM(triangle_symm) \
  ASYM(true) \
  ASYM(uniform) \
  ASYM(uniform_int) \
  ASYM(uniform_symm) \
  ASYM(unless) \
  ASYM(up_slope) \
  ASYM(up_slope_int) \
  ASYM(when) \
  ASYM(xor) \


//---------------------------------------------------------------------------------------
// Ids that cannot be represented as C++ identifiers.
// They take the form of:
//   ASYMX(strat_default, "$default") -> ASymbolX_strat_default
//
// Extra care should be taken when using them during global initialization time.
//
// Try to keep them in alphabetical order so that they are easy to scan at a glance.
//
#define SS_SYMBOLS_NAMED \
  ASYMX(ctor,                "!") \
  ASYMX(ctor_copy,           "!copy") \
  ASYMX(ctor_seed,           "!seed") \
  ASYMX(dtor,                "!!") \
  ASYMX(equalQ,              "equal?") \
  ASYMX(greaterQ,            "greater?") \
  ASYMX(greater_or_equalQ,   "greater_or_equal?") \
  ASYMX(lessQ,               "less?") \
  ASYMX(less_or_equalQ,      "less_or_equal?") \
  ASYMX(not_equalQ,          "not_equal?") \
  ASYMX(op_increment,        "++") \
  ASYMX(op_decrement,        "--") \
  ASYMX(op_negated,          "-expr") \
  ASYMX(op_assign,           ":=") \
  ASYMX(op_add,              "+") \
  ASYMX(op_add_assign,       "+=") \
  ASYMX(op_subtract,         "-") \
  ASYMX(op_subtract_assign,  "-=") \
  ASYMX(op_multiply,         "*") \
  ASYMX(op_multiply_assign,  "*=") \
  ASYMX(op_divide,           "/") \
  ASYMX(op_divide_assign,    "/=") \
  ASYMX(op_equals,           "=") \
  ASYMX(op_not_equal,        "~=") \
  ASYMX(op_greater,          ">") \
  ASYMX(op_greater_or_equal, ">=") \
  ASYMX(op_less,             "<") \
  ASYMX(op_less_or_equal,    "<=") \
  ASYMX(unnamed,             "?unnamed?") \


//---------------------------------------------------------------------------------------
// Declare ASymbol constants
#define ASYM(_id)         ASYMBOL_DECLARE(ASymbol, _id)
#define ASYMX(_id, _str)  ASYMBOL_DECLARE(ASymbolX, _id)
  SS_SYMBOLS
  SS_SYMBOLS_NAMED
#undef ASYMX
#undef ASYM


//---------------------------------------------------------------------------------------
// Common Symbol ids
enum eASymbolId
  {
  ASymbolID_null          = ASymbol_id_null,

  // Class Names
  ASymbolId_Actor         = 0x85b479fd,
  ASymbolId_Boolean       = 0x4538b1f4,
  ASymbolId_Class         = 0x2c8a369b,
  ASymbolId_Closure       = 0x87bab44d,
  ASymbolId_Integer       = 0x95b29297,
  ASymbolId_InvokedMethod = 0x1387e23f,
  ASymbolId_None          = 0xdfa2aff1,
  ASymbolId_Object        = 0xaf01aeda,
  ASymbolId_Real          = 0x36be666b,
  ASymbolId_String        = 0x9912b79f,
  ASymbolId_Symbol        = 0xeb6433cf,

  // Reserved Words
  ASymbolId_branch        = 0xbb861b1f,
  ASymbolId_case          = 0x78089904,
  ASymbolId_divert        = 0xfcaca109,
  ASymbolId_else          = 0x55bb558b,
  ASymbolId_exit          = 0x9409840e,
  ASymbolId_false         = 0x2bcd6830,
  ASymbolId_fork          = 0xbbeb587a,
  ASymbolId_if            = 0x5137067c,
  ASymbolId_loop          = 0xa15f1dee,
  ASymbolId_nil           = 0x4d33c2a5,
  ASymbolId_race          = 0xda6fbbaf,
  ASymbolId_rush          = 0xf533deef,
  ASymbolId_skip          = 0xf876557d,
  ASymbolId_sync          = 0x2c2bf57a,
  ASymbolId_this          = 0xfeee8227,
  ASymbolId_this_class    = 0x3f064bae,
  ASymbolId_this_code     = 0x37c2fcbe,
  ASymbolId_true          = 0xfdfc4c8d,
  ASymbolId_unless        = 0x3eddbf3e,
  ASymbolId_when          = 0x23e80e1c,

  // Boolean word operators
  ASymbolId_and           = 0x07f59b6d,
  ASymbolId_nand          = 0x02091d53,
  ASymbolId_nor           = 0xe1665840,
  ASymbolId_not           = 0x0805fd75,
  ASymbolId_nxor          = 0xfc3101bc,
  ASymbolId_or            = 0x1db77587,
  ASymbolId_xor           = 0xf9cd8782,

  // C++ Reserved Words to watch for
  ASymbolId_break         = 0x0c7c50da,
  ASymbolId_continue      = 0x13e32adf,
  ASymbolId_default       = 0xe35e00df,
  ASymbolId_do            = 0x9d45c095,
  ASymbolId_for           = 0xef7509f8,
  ASymbolId_return        = 0xa79e3f0f,
  ASymbolId_switch        = 0x6fe94b18,
  ASymbolId_while         = 0xc0d455fd
  };



//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declaration
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
// Notes      Simple container for the symbol table
//
// Author(s)  Conan Reis
class SSSymbol
  {
  public:

  // Class Methods

    static SSInstance * as_instance(const ASymbol & sym);

    static void register_bindings();


  protected:

  // Internal Class Methods

  // SkookumScript Atomic Methods

    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_destructor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_greater(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_greater_or_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_less(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_less_or_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_Symbol(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_id(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_id_str(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_nullQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSSymbol


#endif  // __SSSYMBOL_HPP
