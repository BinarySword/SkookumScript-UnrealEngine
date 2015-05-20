//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structures for abstract class descriptors
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSCLASSDESCBASE_HPP
#define __SSCLASSDESCBASE_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AMemory.hpp>
#include "SkookumScript/SkookumScript.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Pre-declarations
class  AString;
class  ASymbol;
class  SSCoroutineBase;
class  SSMetaClass;
class  SSMethodBase;
class  SSClassUnaryBase;
struct SSTypedName;


//---------------------------------------------------------------------------------------
enum eSSClassType
  {
  SSClassType_class           = 0,  // SSClass
  SSClassType_metaclass       = 1,  // SSMetaClass
  SSClassType_typed_class     = 2,  // SSTypedClass
  SSClassType_invokable_class = 3,  // SSInvokableClass
  SSClassType_class_union     = 4   // SSClassUnion
  };


//---------------------------------------------------------------------------------------
// Notes      SkookumScript Class Abstract Base also known as a class descriptor
//            - "class-desc" from the language syntax:
//
//              class-desc     = class-unary | class-union
//              class-unary    = class-instance | meta-class
//              class-instance = class | list-class
//              class          = class-name
//              list-class     = List ['{' ws [class-desc ws] '}']
//              meta-class     = '<' class-name '>'
//              class-union    = '<' class-unary {'|' class-unary}1+ '>'
//
// Subclasses SSClassUnaryBase(SSClass(SSActorClass), SSTypedClass, SSMetaClass),
//            SSClassUnion
// Author(s)  Conan Reis
class SSClassDescBase 
  {
  friend class SSBrain;  // Accesses protected elements

  public:

  // Nested Structures

    // Enumerated constants
    enum
      {
      Binary_ref_size = 9
      };

    // AEx<SSMetaClass> exception id values
    enum eErrId
      {
      ErrId_nonexistent_data = AErrId_last,  // No such data member exists
      ErrId_nonexistent_method,              // No such method exists
      };

  // Common Methods

    SSClassDescBase() {}
    virtual ~SSClassDescBase() {}

  // Converter Methods

    #if (SKOOKUM & SS_COMPILED_OUT)
      virtual void as_binary_ref(void ** binary_pp) const = 0;
      void         as_binary_ref_typed(void ** binary_pp) const;
      virtual uint32_t as_binary_ref_typed_length() const  { return 5u; }
    #endif


    #if (SKOOKUM & SS_COMPILED_IN)
      static SSClassDescBase * from_binary_ref(eSSClassType type, const void ** binary_pp);
      static SSClassDescBase * from_binary_ref_typed(const void ** binary_pp);
    #endif


    #if defined(SS_AS_STRINGS)
      virtual AString as_code() const = 0;
      virtual AString get_scope_desc() const;
    #endif


  // Comparison Methods

    eAEquate         compare(const SSClassDescBase & type) const;
    static bool      equals(const SSClassDescBase & lhs, const SSClassDescBase & rhs)     { return lhs.compare(rhs) == AEquate_equal; }
    static ptrdiff_t comparison(const SSClassDescBase & lhs, const SSClassDescBase & rhs) { return ptrdiff_t(lhs.compare(rhs)); }

  // Methods

      virtual void reference() const;
      virtual void dereference();
      virtual void dereference_delay() const;

      // Type Info Methods

        virtual SSClassDescBase *        as_finalized_generic(const SSClassDescBase & scope_type) const = 0;
        virtual const SSClassUnaryBase * as_unary_class() const = 0;
        virtual SSClassUnaryBase *       as_unary_class() = 0;
        virtual SSClassUnaryBase *       find_common_type(const SSClassDescBase & cls) const = 0;
        virtual bool                     is_builtin_actor_class() const;
        virtual bool                     is_actor_instance() const       { return is_builtin_actor_class() && !is_metaclass(); }
        virtual bool                     is_generic() const;
        virtual bool                     is_metaclass() const; 
        virtual bool                     is_class_type(const SSClassDescBase * type_p) const = 0;
        virtual eSSClassType             get_class_type() const = 0;
        virtual SSClassDescBase *        get_item_type() const           { return nullptr; }
        virtual SSClass *                get_key_class() const = 0;
        virtual const ASymbol &          get_key_class_name() const = 0;
        virtual SSMetaClass &            get_metaclass() const = 0;
        SSClassDescBase *                qualify(SSClass * qual_scope_p) const;

      // Data Member Methods

        virtual SSClassDescBase * get_data_type(const ASymbol & data_name, eSSScope * scope_p = nullptr) const = 0;

      // Method Member Methods

        virtual SSMethodBase * get_method(const ASymbol & method_name) const = 0;
        virtual SSMethodBase * get_method_inherited(const ASymbol & method_name) const = 0;
        virtual bool           is_method_inherited_valid(const ASymbol & method_name) const = 0;
        virtual bool           is_method_registered(const ASymbol & method_name) const;

      // Coroutine Member Methods

        virtual SSCoroutineBase * get_coroutine_inherited(const ASymbol & coroutine_name) const = 0;

      // Class Methods

        static void enable_compound_refs(bool use_refs = true)    { ms_compounds_use_ref = use_refs; }

  protected:

      // Class Data Members

      // If set then compound types - SSTypedClass and SSClassUnion - use an index reference
      // rather than a fully described binary.
      static bool ms_compounds_use_ref;

  };  // SSClassDescBase


//---------------------------------------------------------------------------------------
// Notes      This class represents class descriptors that are a single/unary class
//            rather than a union of classes.
//
//              class-unary    = class-instance | meta-class
//              class-instance = class | list-class
//              class          = class-name
//              list-class     = List ['{' ws [class-desc ws] '}']
//              meta-class     = '<' class-name '>'
//
// Subclasses SSClass(SSActorClass), SSTypedClass, SSInvokableClass, SSMetaClass
// Author(s)  Conan Reis
class SSClassUnaryBase : public SSClassDescBase
  {
  public:

  // Nested Structures

    enum ePath
      {
      Path_class      = 0,  // 00 this/current class [always "set"]
      Path_superclass = 1,  // 01
      Path_subclass   = 2,  // 10
      Path_super_sub  = 3   // 11 [CReis Sounds like a sandwich doesn't it?]
      };

  // Methods

    // Type-checking Methods

      virtual const SSClassUnaryBase * as_unary_class() const  { return this; }
      virtual SSClassUnaryBase *       as_unary_class()        { return this; }

    // Method Member Methods

      virtual void append_method(SSMethodBase * method_p) = 0;
      virtual bool is_method_valid(const ASymbol & method_name) const = 0;

    // Coroutine Member Methods

      virtual void append_coroutine(SSCoroutineBase * coroutine_p) = 0;
      virtual bool is_coroutine_valid(const ASymbol & coroutine_name) const = 0;
      virtual bool is_coroutine_registered(const ASymbol & coroutine_name) const = 0;

    // Data Member Methods

      virtual SSTypedName * append_data_member(const ASymbol & name, SSClassDescBase * type_p) = 0;

  };


//=======================================================================================
// Inline Methods
//=======================================================================================

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSClassDescBase.inl"
#endif


#endif  // __SSCLASSDESCBASE_HPP

