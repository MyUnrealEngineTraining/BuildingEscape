// Software development company copyright.

#pragma once

//#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UPROPERTY(VisibleAnywhere)
	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.f;
	float LastDoorOpenTime;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.0f;
	

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	//c
	AActor* ActorThatOpens;
	AActor* Owner;

};
