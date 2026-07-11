// Patrizio Ternali All Rights Reserved


#include "AnimInstances/WarriorBaseAnimInstance.h"

#include "WarriorFunctionLibrary.h"

bool UWarriorBaseAnimInstance::DoesActorHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarriorFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	
	return false;
}
