// Patrizio Ternali All Rights Reserved


#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());
	
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;	
	}
	
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	
	// Numero float espresso in gradi che va da -180 a 180
	// 0 -> Il personaggio si sta muovendo esattamente nella direzione in cui sta guardando
	// 90 -> Il personaggio guarda avanti ma si sta muovendo verso destra
	// -90 -> Il personaggio guarda avanti ma si sta muovendo verso sinistra
	// 180 o -180 -> Il personaggio sta camminando all'indietro.
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
