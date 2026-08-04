// Patrizio Ternali All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_RotateToFaceTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotateToFaceTargetDelegate);

/**
 * 
 */
UCLASS()
class WARRIOR_API UAbilityTask_RotateToFaceTarget : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UAbilityTask_RotateToFaceTarget();
	
	UPROPERTY(BLueprintAssignable)
	FRotateToFaceTargetDelegate OnCompleted;
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|AbilityTasks", 
		meta=(
			DisplayName = "Rotate to Face Target Actor", 
			HidePin = "OwningAbility", 
			DefaultToSelf = "OwningAbility", 
			BlueprintInternalUseOnly = "true"
		)
	)
	static UAbilityTask_RotateToFaceTarget* CreateRotateToFaceTarget(
		UGameplayAbility* OwningAbility,
		AActor* InTargetActor,
		float InRotationInterpSpeed = 18.f,
		float InAnglePrecision = 5.f
	);
	
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	
private:
	bool HasReachedAnglePrecision(AActor* QueryActor, AActor* TargetActor) const;
	void FinishRotation();
	
	UPROPERTY()
	TObjectPtr<AActor> TargetActor = nullptr;
	
	float RotationInterpSpeed = 18.f;
	float AnglePrecision = 5.f;
};
