//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2001 Agog Labs Inc.,
// All rights reserved.
//
// Classes for expressions that can be evaluated/invoked
// # Author(s): Conan Reis
// # Notes:        
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScript/SSSymbol.hpp"
#include "SkookumScript/SSInvokedBase.hpp"


//=======================================================================================
// SSExpressionBase Inline Methods
//=======================================================================================

#if (SKOOKUM & SS_COMPILED_OUT)

//---------------------------------------------------------------------------------------
// Returns length of binary version of itself plus it's type information in
//             bytes.
// # Returns:  length of binary version of itself plus type information in bytes
// # See:      as_binary_typed(), from_binary_typed_new(), as_binary(), as_binary_length()
// # Notes:    Used in combination with as_binary_typed()
//
//             Binary composition:
//               1 byte  - expression type
//              [2 bytes - *SSDebug binary* expression source character position]
//               n bytes - expression binary
// # Author(s): Conan Reis
A_INLINE uint32_t SSExpressionBase::as_binary_typed_length() const
  {
  //#if (SKOOKUM & SS_DEBUG)
    return 3u + as_binary_length();
  //#else
  //  return 1u + as_binary_length();
  //#endif
  }

//---------------------------------------------------------------------------------------
// Use this class method instead of the instance method when the expression
//             being converted may be nullptr.  Returns length of binary version of itself
//             plus it's type information in bytes.
// # Returns:  length of binary version of itself plus type information in bytes
// # See:      as_binary_typed(), from_binary_typed_new(), as_binary(), as_binary_length()
// # Notes:    Used in combination with as_binary_typed()
//
//             Binary composition:
//               1 byte  - expression type
//              [2 bytes - *SSDebug binary* expression source character position]
//              [n bytes - expression binary - if not a default expression (i.e. not nullptr)]
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE uint32_t SSExpressionBase::as_binary_typed_length(SSExpressionBase * expr_p)
  {
  //#if (SKOOKUM & SS_DEBUG)
    return expr_p ? (3u + expr_p->as_binary_length()) : 1u;
  //#else
  //  return expr_p ? (1u + expr_p->as_binary_length()) : 1u;
  //#endif
  }

//---------------------------------------------------------------------------------------
// Fills memory pointed to by binary_pp with the information needed to
//             recreate an expression (without knowing what type of expression it is) and
//             increments the memory address to just past the last byte written.
// Arg         binary_pp - Pointer to address to fill and increment.  Its size *must* be
//             large enough to fit all the binary data.  Use the get_binary_length()
//             method to determine the size needed prior to passing binary_pp to this
//             method.
// # Examples: 
// # See:      as_binary_typed_length(), from_binary_typed_new(), as_binary(),
//             as_binary_length(), as_binary_typed()
// # Notes:    Used in combination with as_binary_length_typed() and from_binary_new()
//
//             Binary composition:
//               1 byte  - expression type
//               n bytes - expression binary
//
// # Modifiers: static
// # Author(s): Conan Reis
A_INLINE void SSExpressionBase::as_binary_typed(
  SSExpressionBase * expr_p,
  void **            binary_pp
  )
  {
  if (expr_p)
    {
    expr_p->as_binary_typed(binary_pp);
    }
  else
    {
    // 1 byte - inferred this (default)
    **(uint8_t **)binary_pp = static_cast<uint8_t>(SSExprType__default);
    (*(uint8_t **)binary_pp)++;
    }
  }

#endif // (SKOOKUM & SS_COMPILED_OUT)


#if (SKOOKUM & SS_CODE_IN)

//---------------------------------------------------------------------------------------
// #Description
//   Returns this expression (or any *last* sub-expression) that would have no *direct*
//   side-effect (i.e. when a part of its functionality is useless even when it has a
//   sub-expression that has a side effect) when its result is not used (i.e. not used as
//   an argument/receiver or returned as the last expression in a code block).
//   
//   If an expression is returned to determine whether it had no effects or if it has sub
//   expressions with effects call get_side_effect() on it.
//
//   Non-last sub-expressions - especially for code blocks - are automatically tested for
//   side effects immediately *after* they are parsed.
//
// #Modifiers virtual - override for custom behaviour
// #See Also  get_side_effect()
// #Author(s) Conan Reis
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // #Returns nullptr or expression that has no side effects and not used as a result.
  A_INLINE const SSExpressionBase *
SSExpressionBase::find_expr_last_no_side_effect() const
  {
  return nullptr;
  }

//---------------------------------------------------------------------------------------
// #Description
//   Indicates whether this expression (or any sub-expression) has any potential side
//   effects when used as a stand alone statement - i.e. not used as an argument/receiver
//   or returned as the last expression in a code block.
//
// #Modifiers virtual - override for custom behaviour
// #See Also  find_expr_last_no_side_effect()
// #Author(s) Conan Reis
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // #Returns See eSSSideEffect
  A_INLINE eSSSideEffect
SSExpressionBase::get_side_effect() const
  {
  return SSSideEffect_present;
  }

#endif  // (SKOOKUM & SS_CODE_IN)


//---------------------------------------------------------------------------------------
// Gets the mind that is updating/owning this expression.
// # Modifiers: virtual - override for custom behaviour
// # Author(s): Conan Reis
A_INLINE SSMind * SSExpressionBase::get_updater(const SSInvokedExpression & iexpr) const
  {
  SSInvokedBase * caller_p = iexpr.m_caller_p;

  return caller_p ? caller_p->get_updater() : nullptr;
  }

//---------------------------------------------------------------------------------------
// Evaluate an expression immediately (i.e. within one frame) and get result.
// # Returns:  Result of invocation
// Arg         scope_p - scope for data/method/etc. look-ups.  It should always be an
//             object derived from SSInvokedContextBase.
// Arg         caller_p - object that called/invoked this expression and that may await
//             a result.  If it is nullptr, then there is no object that needs to be
//             returned to and notified when this invocation is complete.
// # See:      invoke(), invoke_now_proc()
// # Author(s): Conan Reis
A_INLINE SSInstance * SSExpressionBase::invoke_now(
  SSObjectBase *  scope_p,
  SSInvokedBase * caller_p // = nullptr
  ) const
  {
  SSInstance * result_p;

  invoke(scope_p, caller_p, &result_p);

  return result_p;
  }

//---------------------------------------------------------------------------------------
// Evaluate an expression immediately (i.e. within one frame) as a procedure
//             (don't care about result - only side effects are desired).
// Arg         scope_p - scope for data/method/etc. look-ups.  It should always be an
//             object derived from SSInvokedContextBase.
// Arg         caller_p - object that called/invoked this expression and that may await
//             a result.  If it is nullptr, then there is no object that needs to be
//             returned to and notified when this invocation is complete.
// # See:      invoke()
// # Author(s): Conan Reis
A_INLINE void SSExpressionBase::invoke_now_proc(
  SSObjectBase *  scope_p,
  SSInvokedBase * caller_p // = nullptr
  ) const
  {
  invoke(scope_p, caller_p);
  }

//---------------------------------------------------------------------------------------
// Iterate through sub-expressions/re-entrant calls
// # Returns:  true if the invoke cascade has completed its evaluation and there is a
//             resulting instance, false if there is a result pending.
// Arg         iexpr_p - the invoked expression wrapped around this expression
// Arg         result_pp - pointer to a pointer to store the instance resulting from the
//             invocation of this expression.  If it is nullptr, then the result does not
//             need to be returned and only side-effects are desired.  (Default nullptr)
// # Notes:    Called by invoke() and SSInvokedExpression::pending_return()
// # Author(s): Conan Reis
A_INLINE bool SSExpressionBase::invoke_iterate(
  SSInvokedExpression * iexpr_p,
  SSInstance **         result_pp // = nullptr
  ) const
  {
  // This default invoked_iterate() is currently used by the expressions: SSInvokeSync,
  // SSConcurrentSync and SSDivert.
  SSInvokedBase * caller_p = iexpr_p->get_caller();

  // If this is not the initial call, return to caller if one is waiting
  if (caller_p && caller_p->pending_count())
    {
    caller_p->pending_unregister(iexpr_p);
    }

  // $Revisit - CReis Should probably free iexpr before pending_unregister() above calls
  // pending_return().  Fix code here and mimic throughout codebase where pending_unregister()
  // is also called.
  SSInvokedExpression::pool_delete(iexpr_p);

  return true;
  }


//=======================================================================================
// SSLoop Inline Methods
//=======================================================================================

#if (SKOOKUM & SS_COMPILED_IN)

//---------------------------------------------------------------------------------------
// Constructor from binary info
// # Returns:  itself
// Arg         binary_pp - Pointer to address to read binary serialization info from and
//             to increment - previously filled using as_binary() or a similar mechanism.
// # See:      as_binary()
// # Notes:    Binary composition:
//               4 bytes - loop name id
//               n bytes - expression typed binary
//
//             Little error checking is done on the binary info as it assumed that it
//             previously validated upon input.
// # Author(s): Conan Reis
A_INLINE SSLoop::SSLoop(const void ** binary_pp) :
  m_name(ASymbol::create_from_binary(binary_pp))
  {
  m_expr_p = from_binary_typed_new(binary_pp);
  }

#endif // (SKOOKUM & SS_COMPILED_IN)



//=======================================================================================
// SSLoopExit Inline Methods
//=======================================================================================

#if (SKOOKUM & SS_COMPILED_IN)

//---------------------------------------------------------------------------------------
// Constructor from binary info
// # Returns:  itself
// Arg         binary_pp - Pointer to address to read binary serialization info from and
//             to increment - previously filled using as_binary() or a similar mechanism.
// # See:      as_binary()
// # Notes:    Binary composition:
//               4 bytes - loop name id
//
//             Little error checking is done on the binary info as it assumed that it was
//             previously validated upon input.
// # Author(s): Conan Reis
A_INLINE SSLoopExit::SSLoopExit(const void ** binary_pp) :
  m_name(ASymbol::create_from_binary(binary_pp))
  {
  }

#endif // (SKOOKUM & SS_COMPILED_IN)


//=======================================================================================
// SSConversion Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         type_p - desired class type
// Arg         m_expr_p - expression to convert if not of desired class type.
// # Author(s): Conan Reis
A_INLINE SSConversion::SSConversion(
  SSClass *          type_p,
  SSExpressionBase * expr_p
  ) :
  m_type_p(type_p),
  m_expr_p(expr_p)
  {
  }


#if (SKOOKUM & SS_COMPILED_IN)

//---------------------------------------------------------------------------------------
// Constructor from binary info
// # Returns:  itself
// Arg         binary_pp - Pointer to address to read binary serialization info from and
//             to increment - previously filled using as_binary() or a similar mechanism.
// # See:      assign_binary(), as_binary()
// # Notes:    Little error checking is done on the binary info as it assumed that it was
//             previously validated upon input.
// # Author(s): Conan Reis
A_INLINE SSConversion::SSConversion(const void ** binary_pp) :
  m_type_p(nullptr),
  m_expr_p(nullptr)
  {
  assign_binary(binary_pp);
  }

#endif // (SKOOKUM & SS_COMPILED_IN)


//=======================================================================================
// SSCast Inline Methods
//=======================================================================================

//---------------------------------------------------------------------------------------
// Constructor
// # Returns:  itself
// Arg         type_p - class type to override with
// Arg         m_expr_p - expression whose type is to be overridden.
// # Author(s): Conan Reis
A_INLINE SSCast::SSCast(
  SSClassDescBase *  type_p,
  SSExpressionBase * expr_p
  ) :
  m_type_p(type_p),
  m_expr_p(expr_p)
  {
  }


#if (SKOOKUM & SS_COMPILED_IN)

//---------------------------------------------------------------------------------------
// Constructor from binary info
// # Returns:  itself
// Arg         binary_pp - Pointer to address to read binary serialization info from and
//             to increment - previously filled using as_binary() or a similar mechanism.
// # See:      assign_binary(), as_binary()
// # Notes:    Little error checking is done on the binary info as it assumed that it was
//             previously validated upon input.
// # Author(s): Conan Reis
A_INLINE SSCast::SSCast(const void ** binary_pp) :
  m_type_p(nullptr),
  m_expr_p(nullptr)
  {
  assign_binary(binary_pp);
  }

#endif // (SKOOKUM & SS_COMPILED_IN)
