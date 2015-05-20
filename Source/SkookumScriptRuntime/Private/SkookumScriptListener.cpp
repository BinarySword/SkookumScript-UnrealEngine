//=======================================================================================
// SkookumScript C++ library.
// Copyright (c) 2014 Agog Labs Inc.,
// All rights reserved.
//
// SkookumScript (SS) Unreal Engine (UE) Bindings
// 
// Based on: UObject
// 
// #Author(s):  Markus Breyer
//=======================================================================================


//=======================================================================================
// Includes
//=======================================================================================

#include "SkookumScriptRuntimePrivatePCH.h"
#include "../Classes/SkookumScriptListener.h"
#include "SkookumScriptListenerManager.hpp"

#include "Bindings/VectorMath/SSVector3.hpp"
#include "Bindings/Engine/SSUEName.hpp"
#include "SSUEActor.generated.hpp"
#include "SSUEDamageType.generated.hpp"
#include "SSUEController.generated.hpp"
#include "SSUEPrimitiveComponent.generated.hpp"

//=======================================================================================
// FSkookumScriptListenerAutoPtr
//======================================================================================

FSkookumScriptListenerAutoPtr::~FSkookumScriptListenerAutoPtr()
  {
  USkookumScriptListener * listener_p = Get();
  SS_ASSERTX(listener_p, "USkookumScriptListeners are entirely under Sk control and cannot just go away.");
  SkookumScriptListenerManager::get_singleton()->free_listener(listener_p);
  }

//=======================================================================================
// Class Data
//=======================================================================================

//=======================================================================================
// Method Definitions
//=======================================================================================

//---------------------------------------------------------------------------------------

USkookumScriptListener::USkookumScriptListener(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
  , m_unregister_callback_p(nullptr)
  , m_num_arguments(0)
  {
  }

//---------------------------------------------------------------------------------------

void USkookumScriptListener::initialize(UObject * obj_p, SSInvokedCoroutine * coro_p, tUnregisterCallback callback_p)
  {
  SS_ASSERTX(!coro_p->is_suspended(), "Coroutine must not be suspended yet when delegate object is initialized.");

  m_obj_p = obj_p;
  m_coro_p = coro_p;
  m_unregister_callback_p = callback_p;
  m_num_arguments = 0;
  }

//---------------------------------------------------------------------------------------

void USkookumScriptListener::deinitialize()
  {
  // Kill any events that are still around
  while (has_event())
    {
    free_event(pop_event(), true);
    }

  // Forget the coroutine we keep track of
  m_coro_p.null();

  // Unregister from delegate list if any
  if (m_unregister_callback_p && m_obj_p.IsValid())
    {
    (*m_unregister_callback_p)(m_obj_p.Get(), this);
    }
  }

//---------------------------------------------------------------------------------------

USkookumScriptListener::EventInfo * USkookumScriptListener::alloc_event()
  {
  EventInfo * event_p = SkookumScriptListenerManager::get_singleton()->alloc_event();
  #if (SKOOKUM & SS_DEBUG)
    ::memset(event_p->m_argument_p, 0, sizeof(event_p->m_argument_p));
  #endif
  return event_p;
  }

//---------------------------------------------------------------------------------------

void USkookumScriptListener::free_event(EventInfo * event_p, bool free_arguments)
  {
  SkookumScriptListenerManager::get_singleton()->free_event(event_p, free_arguments ? m_num_arguments : 0);
  }

//---------------------------------------------------------------------------------------

inline void USkookumScriptListener::push_event_and_resume(EventInfo * event_p, uint32_t num_arguments)
  {
  #if (SKOOKUM & SS_DEBUG)
    for (uint32_t i = 0; i < num_arguments; ++i) SS_ASSERTX(event_p->m_argument_p[i], "All event arguments must be set.");
    for (uint32_t i = num_arguments; i < A_COUNT_OF(event_p->m_argument_p); ++i) SS_ASSERTX(!event_p->m_argument_p[i], "Unused event arguments must be left alone.");
    SS_ASSERTX(m_num_arguments == 0 || m_num_arguments == num_arguments, "All events must have same argument count.");
  #endif
  m_num_arguments = num_arguments;
  m_event_queue.append(event_p);
  if (m_coro_p.is_valid()) m_coro_p->resume();
  }

//=======================================================================================
// Various event handlers
//======================================================================================

//---------------------------------------------------------------------------------------

void USkookumScriptListener::OnActorOverlap(AActor * other_actor_p)
  {
  EventInfo * event_p = alloc_event();
  event_p->m_argument_p[SSArg_1] = SSUEActor::as_instance(other_actor_p);
  push_event_and_resume(event_p, 1);
  }

//---------------------------------------------------------------------------------------

void USkookumScriptListener::OnTakeAnyDamage(float damage, const UDamageType * damage_type_p, AController * instigated_by_p, AActor * damage_causer_p)
  {
  EventInfo * event_p = alloc_event();
  event_p->m_argument_p[SSArg_1] = SSReal::as_instance(damage);
  event_p->m_argument_p[SSArg_2] = SSUEDamageType::as_instance(const_cast<UDamageType*>(damage_type_p));
  event_p->m_argument_p[SSArg_3] = SSUEController::as_instance(instigated_by_p);
  event_p->m_argument_p[SSArg_4] = SSUEActor::as_instance(damage_causer_p);
  push_event_and_resume(event_p, 4);
  }

//---------------------------------------------------------------------------------------

void USkookumScriptListener::OnTakePointDamage(float damage, AController * instigated_by_p, FVector hit_location, UPrimitiveComponent * hit_component_p, FName bone_name, FVector shot_from_direction, const UDamageType * damage_type_p, AActor * damage_causer_p)
  {
  EventInfo * event_p = alloc_event();
  event_p->m_argument_p[SSArg_1] = SSReal::as_instance(damage);
  event_p->m_argument_p[SSArg_2] = SSUEController::as_instance(instigated_by_p);
  event_p->m_argument_p[SSArg_3] = SSVector3::as_instance(hit_location);
  event_p->m_argument_p[SSArg_4] = SSUEPrimitiveComponent::as_instance(hit_component_p);
  event_p->m_argument_p[SSArg_5] = SSUEName::as_instance(bone_name);
  event_p->m_argument_p[SSArg_6] = SSVector3::as_instance(shot_from_direction);
  event_p->m_argument_p[SSArg_7] = SSUEDamageType::as_instance(const_cast<UDamageType*>(damage_type_p));
  event_p->m_argument_p[SSArg_8] = SSUEActor::as_instance(damage_causer_p);
  push_event_and_resume(event_p, 8);
  }

//---------------------------------------------------------------------------------------

void USkookumScriptListener::OnDestroyed()
  {
  push_event_and_resume(alloc_event(), 0);
  }
