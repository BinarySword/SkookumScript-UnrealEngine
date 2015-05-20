//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Data structure for actor class descriptors and actor class objects
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


#ifndef __SSACTORCLASS_HPP
#define __SSACTORCLASS_HPP


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSClass.hpp"
#include "SkookumScript/SSActor.hpp"


//=======================================================================================
// Global Structures
//=======================================================================================

// Some shorthand for sorted arrays
typedef APSortedLogical<SSActor, ASymbol>  tSSActors;


//---------------------------------------------------------------------------------------
// Notes      Class structure for all SkookumScript classes derived from and including
//            'Actor'.
// Subclasses 
// See Also   
// UsesLibs   AgogCore/AgogCore.lib
// InLibs     SkookumLib.lib
// # Examples:  
// Author(s)  Conan Reis
class SSActorClass : public SSClass
  {
  // Accesses protected elements
  friend class SSParser;
  friend class SSCompiler;

  public:

  // Common Methods

    SS_NEW_OPERATORS(SSActorClass);

    explicit SSActorClass(const ASymbol & name = ASymbol::get_null(), SSClass * superclass_p = nullptr, uint32_t flags = Flag__default_actor);
    virtual ~SSActorClass();

  // Methods

    //virtual void clear_members();
    //virtual void clear_members_compact();
    virtual bool is_builtin_actor_class() const;
    virtual void track_memory(AMemoryStats * mem_stats_p, bool skip_demand_loaded) const;

    // Serialization Methods

      virtual SSInstance * object_id_lookup(SSObjectId * obj_id_p) const;

      #if (SKOOKUM & SS_CODE_IN)
        //virtual SSClass * object_id_validate(SSObjectId * obj_id_p) const;
      #endif

      virtual bool demand_unload();

      //#if (SKOOKUM & SS_COMPILED_OUT)
      //  virtual void     as_binary(void ** binary_pp) const;
      //  virtual uint32_t as_binary_length() const;
      //#endif


      //#if (SKOOKUM & SS_COMPILED_IN)
      //  virtual void assign_binary(const void ** binary_pp, bool append_super_members = true);
      //#endif

    // Instance Methods

      void                 append_instance(const SSActor & actor);
      SSActor *            find_instance(const ASymbol & name) const    { return m_instances.get(name); }
      SSActor *            get_first_instance() const                   { return m_instances.get_first(); }
      const tSSActors &    get_instances() const                        { return m_instances; }
      void                 remove_instance(const SSActor & actor, eATerm term = ATerm_long);
      void                 instances_enable_behavior(bool activate = true, bool construct = false) const;
      virtual SSInstance * new_instance();

  // Class Methods

  protected:

  // Data Members

    // Instances of this class (including derived class instances) for quick class based
    // look-ups.
    // $Revisit - CReis This might be better as something that doesn't need a large
    // contiguous chunk of memory.  Could also not store derived instances and only do a
    // sub-class look-up if needed - this would potentially slow things down.
    tSSActors m_instances;

  };  // SSActorClass


//=======================================================================================
// Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Storage specialization - SSActorClass stored indirectly as pointer in SSUserData rather than whole structure
template<> inline SSActorClass * SSUserDataBase::as<SSActorClass>() const                { return *as_stored<SSActorClass*>(); }
template<> inline void           SSUserDataBase::set(SSActorClass const * const & value) { *as_stored<const SSActorClass*>() = value; }
template<> inline void           SSUserDataBase::set(SSActorClass       * const & value) { *as_stored<SSActorClass*>() = value; }

#ifndef A_INL_IN_CPP
  #include "SkookumScript/SSActorClass.inl"
#endif


#endif  // __SSACTORCLASS_HPP

