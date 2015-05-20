// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "ISkookumScriptRuntime.h"
#include "Engine.h"
#include "CoreUObject.h"
#include "ModuleManager.h"

#include <AgogCore/AgogCore.hpp>
#include <AgogCore/AString.hpp>
#include <AgogCore/ASymbol.hpp>
#include <AgogCore/ADatum.hpp>
#include <AgogCore/ADeferFunc.hpp>
#include <AgogCore/ABinaryParse.hpp>
#include <AgogCore/AIdPtr.hpp>
#include <AgogCore/AObjReusePool.hpp>
#include <AgogCore/AMath.hpp>
#include <SkookumScript/SSClass.hpp>
#include <SkookumScript/SSBrain.hpp>
#include <SkookumScript/SSBoolean.hpp>
#include <SkookumScript/SSString.hpp>
#include <SkookumScript/SSReal.hpp>
#include <SkookumScript/SSList.hpp>
#include <SkookumScript/SSSymbol.hpp>
#include <SkookumScript/SSUserData.hpp>
#include <SkookumScript/SSInstance.hpp>
#include <SkookumScript/SSInvokedMethod.hpp>
#include <SkookumScript/SSInvokedCoroutine.hpp>
#include <SkookumScript/SSClosure.hpp>
#include <SkookumScript/SSMind.hpp>
#include <SkookumScript/SSParser.hpp>
#include <SkookumScript/SSDebug.hpp>

#include "Bindings/SSUESymbol.hpp"
#include "Bindings/SSUEUtils.hpp"

#if WITH_EDITOR
  #include "UnrealEd.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogSkookum, Log, All);

