// Patrizio Ternali All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UEnemyUIComponent;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
	
public:
	AWarriorEnemyCharacter();
	
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
	virtual UPawnUIComponent* GetPawnUIComponent() override;
	
protected:
	// Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	// End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UEnemyUIComponent* EnemyUIComponent;
	
private:
	void InitEnemyStartUpData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
