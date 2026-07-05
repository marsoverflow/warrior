// Patrizio Ternali All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"

#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "WarriorDebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/WarriorWidgetBase.h"

AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* AWarriorEnemyCharacter::GetPawnUIComponent()
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AWarriorEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AWarriorEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWarriorWidgetBase* HealthWidget = Cast<UWarriorWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitEnemyStartUpData();
}

void AWarriorEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartupData.IsNull()) { return; }
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartupData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartupData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
				}
			}
		)
	);
}
