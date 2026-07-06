// Patrizio Ternali All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WarriorHeroController.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AWarriorHeroController();
	
	// Begin IGenericTeamAgentInterface interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	// End IGenericTeamAgentInterface interface
	
protected:
	FGenericTeamId HeroTeamId;
};
