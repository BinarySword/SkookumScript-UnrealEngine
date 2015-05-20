//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript Base Object inline file
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include <AgogCore/AObjReusePool.hpp>
#include "SkookumScript/SSBrain.hpp"


//=======================================================================================
// Inline Methods
//=======================================================================================

// The methods for simple data type retrieval are inlined in the SkookumScript/SSInstance.inl file.

//---------------------------------------------------------------------------------------
// Retrieves a SSData object from the dynamic pool and initializes it with the
//             nil object for use.  This method should be used instead of 'new' because it
//             prevents unnecessary allocations by reusing previously allocated objects.
// # Returns:  a dynamic SSData
// # See:      pool_delete() 
// # Notes:    To 'deallocate' an object that was retrieved with this method, use
//             'pool_delete()' rather than 'delete'.
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSData * SSData::pool_new(
  const ASymbol & name
  )
  {
  SSData * data_p  = get_pool().pop();
  data_p->m_name   = name;
  data_p->m_data_p = SSBrain::ms_nil_p;

  return data_p;
  }

//---------------------------------------------------------------------------------------
// Retrieves a SSData object from the dynamic pool and initializes it with the
//             supplied object for use.  This method should be used instead of 'new' 
//             because it prevents unnecessary allocations by reusing previously allocated
//             objects.
// # Returns:  a dynamic SSData
// # See:      pool_delete() 
// # Notes:    To 'deallocate' an object that was retrieved with this method, use
//             'pool_delete()' rather than 'delete'.
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE SSData * SSData::pool_new(
  const ASymbol & name,
  SSInstance *    instance_p
  )
  {
  SSData * data_p  = get_pool().pop();
  data_p->m_name   = name;
  data_p->m_data_p = instance_p;

  return data_p;
  }

//---------------------------------------------------------------------------------------
// Puts a SSData object back on the dynamic pool for future reuse.
//             This method should be used instead of 'delete' because it prevents
//             unnecessary deallocations by reusing previously allocated objects.
// # See:      pool_new() 
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE void SSData::pool_delete(SSData * data_p)
  {
  get_pool().append(data_p);
  }

