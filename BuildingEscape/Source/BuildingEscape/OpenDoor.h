// Software development company copyright.

#pragma once

//#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	float GetTotalMassOfActorsOnPlate();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.0f;

	UPROPERTY(BlueprintAssignable);
	FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable);
	FDoorEvent OnClose;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate = nullptr;

	AActor* Owner = nullptr;

};
	//UPROPERTY(VisibleAnywhere)
