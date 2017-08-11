// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerInput.h"
#include <string>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "AirBlueprintLib.generated.h"

UENUM(BlueprintType)
enum class LogDebugLevel : uint8 {
    Informational UMETA(DisplayName="Informational"),
    Success UMETA(DisplayName = "Success"),
    Failure UMETA(DisplayName = "Failure"),
    Unimportant  UMETA(DisplayName = "Unimportant")
};

/**
 * 
 */
UCLASS()
class UAirBlueprintLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static void LogMessageString(const std::string &prefix, const std::string &suffix, LogDebugLevel level, float persist_sec = 60);
    static void LogMessage(const FString &prefix, const FString &suffix, LogDebugLevel level, float persist_sec = 60);
    static float GetWorldToMetersScale(const AActor* context);

    template<typename T>
    static T* GetActorComponent(AActor* actor, FString name);
    template<typename T>
    static T* FindActor(const UObject* context, FString name);
    template<typename T>
    static void FindAllActor(const UObject* context, TArray<AActor*>& foundActors);
    static bool HasObstacle(const AActor* actor, const FVector& start, const FVector& end, const AActor* ignore_actor = nullptr, ECollisionChannel collison_channel = ECC_Visibility);
    static bool GetObstacle(const AActor* actor, const FVector& start, const FVector& end, FHitResult& hit, const AActor* ignore_actor = nullptr, ECollisionChannel collison_channel = ECC_Visibility);
    static bool GetLastObstaclePosition(const AActor* actor, const FVector& start, const FVector& end, FHitResult& hit, const AActor* ignore_actor = nullptr, ECollisionChannel collison_channel = ECC_Visibility);
    static void FollowActor(AActor* follower, const AActor* followee, const FVector& offset, bool fixed_z = false, float fixed_z_val = 2.0f);

    template<class UserClass>
    static FInputActionBinding& BindActionToKey(const FName action_name, const FKey in_key, UserClass* actor,
        typename FInputActionHandlerSignature::TUObjectMethodDelegate< UserClass >::FMethodPtr func,
        bool shift_key = false, bool control_key = false, bool alt_key = false, bool command_key = false);

    template<class UserClass>
    static FInputAxisBinding& BindAxisToKey(const FName axis_name, const FKey in_key, AActor* actor, UserClass* obj,
        typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr func);
    template<class UserClass>
    static FInputAxisBinding& BindAxisToKey(const FInputAxisKeyMapping& axis, AActor* actor, UserClass* obj,
        typename FInputAxisHandlerSignature::TUObjectMethodDelegate<UserClass>::FMethodPtr func);

    static int RemoveAxisBinding(const FInputAxisKeyMapping& axis, FInputAxisBinding* axis_binding, AActor* actor);

    static void EnableInput(AActor* actor);

    static bool getLogMessagesHidden()
    {
        return log_messages_hidden;
    }
    static void setLogMessagesHidden(bool is_hidden)
    {
        log_messages_hidden = is_hidden;
    }

private:
    static bool log_messages_hidden;
};

