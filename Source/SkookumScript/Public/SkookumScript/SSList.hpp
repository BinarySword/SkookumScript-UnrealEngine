//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Atomic List (dynamic array of typed objects) class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSLIST_HPP
#define __SSLIST_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/APArray.hpp>
#include "SkookumScript/SSInvokedBase.hpp"
#include "SkookumScript/SSUserData.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSInvokedMethod;
class SSInvokedBase;

//---------------------------------------------------------------------------------------
// Storage specialization - SSInvokedContextBase stored indirectly as pointer in SSUserData rather than whole structure
template<> inline SSList *  SSUserDataBase::as<SSList>() const          { return *as_stored<SSList*>(); }
template<> inline void      SSUserDataBase::set(SSList * const & value) { *as_stored<SSList*>() = value; }

//---------------------------------------------------------------------------------------
// Notes      SkookumScript Atomic List (dynamic array of typed objects) class
// See Also   SSInstance (this class is stored as a pointer in SSInstance::m_user_data)
// Author(s)  Conan Reis
class SSList
  {
  friend class SSLiteralList;  // Accesses protected items

  public:
	  SS_NEW_OPERATORS(SSList);

  // Methods

    explicit SSList(uint32_t ensure_size = 0u) : m_items(nullptr, 0u, ensure_size) {}
    ~SSList();

    SSInstance ** get_array() const   { return m_items.get_array(); }
    uint32_t      get_count() const   { return m_items.get_length(); }

    APArray<SSInstance> & get_instances() const   { return const_cast<SSList *>(this)->m_items; }

    void append(SSInstance & instance, bool reference_b = true);
	void remove(SSInstance & instance, bool dereference_b = true);
    void append_elems_as_strings(AString * str_p, SSInvokedBase * caller_p = nullptr) const;

  // Class Methods

    static SSInstance * as_instance(SSList * list_p = nullptr);
    static void         register_bindings();

  protected:

  // Internal Class Methods

    // SkookumScript Atomic Methods

    static void mthd_constructor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_ctor_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_destructor(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_String(SSInvokedMethod * scope_p, SSInstance ** result_pp);

    static void mthd_op_add(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_add_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_op_assign(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_append(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_append_absent_same(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_append_absent_list_same(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_append_items(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_append_list(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_copy(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_as_new(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_at(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_at_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_crop(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_empty(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_emptyQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_filledQ(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_length(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_length_after(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_first(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_last(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_match_list_same(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_range(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_insert(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_insert_items(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_insert_list(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_not_same_items(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pop_at(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pop_first(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pop_last(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pop_range(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_pop_range_last(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_at(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_same(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_first(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_last(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_list_same(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_range(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_remove_range_last(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_reverse(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_rotate_down(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_rotate_up(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_same_items(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_items_set(SSInvokedMethod * scope_p, SSInstance ** result_pp);
    static void mthd_swap(SSInvokedMethod * scope_p, SSInstance ** result_pp);

  // Data Members

    // Ordered array of items/elements.
    APArray<SSInstance> m_items;

  };  // SSList


//=======================================================================================
// Inline Methods
//=======================================================================================



#endif  // __SSLIST_HPP

