// Patrizio Ternali All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "WarriorBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	
	// 'const' qui è importante anche se c'è BlueprintPure.
	// Perché essendo BlueprintThreadSafe garantisce la sola lettura in un ipotetico accesso multi-thread
	// che farebbe crashare istantaneamente il gioco
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	bool DoesActorHaveTag(FGameplayTag TagToCheck) const;
};
