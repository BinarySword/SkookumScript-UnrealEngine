//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic String Class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSSTRING_HPP
#define __SSSTRING_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AString.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class AString;
class SSInvokedMethod;
class SSInstance;


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Atomic String
// Author(s)  Conan Reis
class SSString
  {
  public:
  // Class Methods

    static void register_bindings();

    static SSInstance * as_instance(const AString & str);
    static void         to_escape_string(const AString & str, AString * esc_str_p, bool break_newlines = false);
    static AString      to_escape_string(const AString & str, bool break_newlines = false)  { AString estr; to_escape_string(str, &estr, break_newlines); return estr; }

	// Helpful Instance->String macros are also in SkookumScript/SSInstance.hpp

  protected:

  // Internal Class Methods

    // SkookumScript Atomic Methods

    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_destructor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_append(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_append_char(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_crc32(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_as_integer(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_as_real(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_string(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_symbol(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_compare_insensitive(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_count(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_count_char(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_crop(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_empty(SSInvokedMethod * scope_p, SSInstance ** result_pp);
	static void mthd_emptyQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_enumerate(SSInvokedMethod * scope_p, SSInstance ** result_pp);
	static void mthd_filledQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_findQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_find_char(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_find_reverseQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_find_char_reverse(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_at(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_first(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_last(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_range(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_get_end(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_get_token(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_insert(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_insert_char(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_line_indent(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_lowercase(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_equals(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_not_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_greater(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_greater_or_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_less(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_less_or_equal(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_remove(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_remove_all(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_remove_char_all(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_remove_range(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_remove_end(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_replace(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_replace_range(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_replace_all(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_replace_char_all(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_reverse(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_set_count(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    //static void mthd_tokenize(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_uppercase(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  };  // SSString


//=======================================================================================
// Inline Methods
//=======================================================================================



#endif  // __SSSTRING_HPP

