//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Member Identifier class
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSMEMBERINFO_HPP
#define __SSMEMBERINFO_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSQualifier.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class SSClassUnaryBase;
class SSExpressionBase;
class SSInvokableBase;
class SSInvokedBase;
class SSObjectBase;
struct SSOverlay;


//---------------------------------------------------------------------------------------
// Used to find expressions by source index position
enum eSSExprFind
  {
  SSExprFind_all,           // Find all expressions
  SSExprFind_interesting,   // Find all interesting expressions (expressions that do some sort of work)
  SSExprFind_invoke         // Find all expressions that call methods/coroutines
  };


//---------------------------------------------------------------------------------------
struct SSMemberInfo
  {
  // Nested Structures

    enum ePathFlag
      {
      PathFlag_scope        = 1 << 0,
      PathFlag_extension    = 1 << 1,
      PathFlag_translate    = 1 << 2, // Convert invalid file characters like ? to -Q

      PathFlag__none        = 0x0,
      PathFlag__file        = PathFlag_extension | PathFlag_translate,
      PathFlag__scope_ext   = PathFlag_scope | PathFlag_extension,
      };

    // Used when converting this structure to and from a binary stream
    enum eByteFlag
      {
      ByteFlag_class_member  = 1 << 7,

      ByteFlag__type_mask   = 0x7f
      };

  // Public Data

    SSQualifier m_member_id;
    eSSMember   m_type;
    bool        m_class_scope;  // true = class member,  false = instance member


  // Methods

    //SS_NEW_OPERATORS(SSMemberInfo);

    SSMemberInfo()                                                                : m_type(SSMember__invalid), m_class_scope(false) {}
    SSMemberInfo(const SSQualifier & member_id, eSSMember type, bool class_scope) : m_member_id(member_id), m_type(type), m_class_scope(class_scope)  {}
    SSMemberInfo(const SSMemberInfo & info)                                       : m_member_id(info.m_member_id), m_type(info.m_type), m_class_scope(info.m_class_scope)  {}

    SSMemberInfo & operator=(const SSMemberInfo & info)                           { m_member_id = info.m_member_id; m_type = info.m_type; m_class_scope = info.m_class_scope; return *this; }

    // Comparison Methods

      bool operator==(const SSMemberInfo & info) const;
      bool operator!=(const SSMemberInfo & info) const    { return !operator==(info); }
      bool operator<(const SSMemberInfo & info) const;

    // Accessor & Conversion Methods

	  SSInvokableBase *  as_invokable() const;
      SSClass          * get_class() const                { return m_member_id.get_scope(); }
      SSClassUnaryBase * get_class_scope() const;
      bool               is_valid() const                 { return m_type != SSMember__invalid; }
      void               invalidate()                     { m_type = SSMember__invalid; m_member_id.invalidate(); }
      void               set_class(SSClass * scope_p)     { return m_member_id.set_scope(scope_p); }

      operator const SSQualifier & () const               { return m_member_id; }

      #if defined(SS_AS_STRINGS)
        AString as_file_title(ePathFlag flags = PathFlag_scope) const;
      #endif

      #if (SKOOKUM & SS_DEBUG)
        SSExpressionBase * find_expr_by_pos(uint32_t pos, eSSExprFind type = SSExprFind_all) const;
        SSExpressionBase * find_expr_on_pos(uint32_t pos, eSSExprFind type = SSExprFind_all) const;
        SSExpressionBase * find_expr_span(uint32_t source_idx, uint32_t * idx_begin_p = nullptr, uint32_t * idx_end_p = nullptr, eSSExprFind type = SSExprFind_all) const;
	    SSExpressionBase * get_body_expr() const;
        void               get_expr_span(const SSExpressionBase & expr, uint32_t * idx_begin_p, uint32_t * idx_end_p) const;
        void               set_context(SSObjectBase * scope_p, SSInvokedBase * caller_p);
      #endif

    // Binary Stream Methods

      SSMemberInfo(const void ** binary_pp);

      #if (SKOOKUM & SS_COMPILED_OUT)
        virtual void     as_binary(void ** binary_pp) const;
        virtual uint32_t as_binary_length() const               { return 4u + 4u + 1u; }
      #endif

  };  // SSMemberInfo


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSMemberInfo.inl"
#endif


#endif  // __SSMEMBERINFO_HPP

