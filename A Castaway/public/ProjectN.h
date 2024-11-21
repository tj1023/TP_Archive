// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

// 스크립트의 갯수 (SUB_LEN + 2)
#define SCRIPT_LEN 26

DECLARE_LOG_CATEGORY_EXTERN(ProjectN, Log, All);

#define NLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define NLOG_S(Verbosity) UE_LOG(ProjectN, Verbosity, TEXT("%s"), *NLOG_CALLINFO)
#define NLOG(Verbosity, Format, ...) UE_LOG(ProjectN, Verbosity, TEXT("%s %s"), *NLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define NCHECK(Expr, ...) { if (!(Expr)) { NLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; } }