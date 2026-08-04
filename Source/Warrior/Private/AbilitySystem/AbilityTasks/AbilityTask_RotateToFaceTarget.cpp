// Patrizio Ternali All Rights Reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_RotateToFaceTarget.h"

#include "Kismet/KismetMathLibrary.h"

UAbilityTask_RotateToFaceTarget::UAbilityTask_RotateToFaceTarget()
{
	bTickingTask = true;
}

UAbilityTask_RotateToFaceTarget* UAbilityTask_RotateToFaceTarget::CreateRotateToFaceTarget(
	UGameplayAbility* OwningAbility, AActor* InTargetActor, float InRotationInterpSpeed, float InAnglePrecision)
{
	UAbilityTask_RotateToFaceTarget* Task = NewAbilityTask<UAbilityTask_RotateToFaceTarget>(OwningAbility);
	
	Task->TargetActor = InTargetActor;
	Task->RotationInterpSpeed = InRotationInterpSpeed;
	Task->AnglePrecision = InAnglePrecision;
	
	return Task;
}

void UAbilityTask_RotateToFaceTarget::Activate()
{
	AActor* AvatarActor = GetAvatarActor();
	
	if (!AvatarActor || !TargetActor)
	{
		FinishRotation();
		return;
	}
	
	if (HasReachedAnglePrecision(AvatarActor, TargetActor))
	{
		FinishRotation();
	}
}

void UAbilityTask_RotateToFaceTarget::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	AActor* AvatarActor = GetAvatarActor();
	
	if (!AvatarActor || !TargetActor)
	{
		FinishRotation();
		return;
	}
	
	if (HasReachedAnglePrecision(AvatarActor, TargetActor))
	{
		FinishRotation();
		return;
	}
	
	const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(AvatarActor->GetActorLocation(), TargetActor->GetActorLocation());
	const FRotator DesiredRot(0.f, LookAtRot.Yaw, 0.f);
	const FRotator NewRot = FMath::RInterpTo(AvatarActor->GetActorRotation(), DesiredRot, DeltaTime, RotationInterpSpeed);
	
	AvatarActor->SetActorRotation(NewRot);
}

bool UAbilityTask_RotateToFaceTarget::HasReachedAnglePrecision(AActor* QueryActor, AActor* TargetActor) const
{
	const FVector OwnerForward = QueryActor->GetActorForwardVector();
	const FVector OwnerToTargetNormalized = (TargetActor->GetActorLocation() - QueryActor->GetActorLocation()).GetSafeNormal();
	
	const float DotResult = FVector::DotProduct(OwnerForward, OwnerToTargetNormalized);
	const float AngleDiff = UKismetMathLibrary::DegAcos(DotResult);
	
	return AngleDiff <= AnglePrecision;
}

void UAbilityTask_RotateToFaceTarget::FinishRotation()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast();
	}
	
	EndTask();
}
