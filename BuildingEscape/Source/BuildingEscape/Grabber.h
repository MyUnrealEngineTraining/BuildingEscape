// Software development company copyright.

#pragma once

#include "coreminimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "components/actorcomponent.h"
#include "grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{

	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game starts
	virtual void BeginPlay() override;


protected:



private:

	float Reach = 150.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* MyInputComponent = nullptr;

	// Ray-cast , Pressed action
	void Grab();

	// Grab released action
	void UnGrab();
		

	//	Find (assumed) attached phisics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	const FVector GetReachLineEnd();

	const FVector GetReachLineStart();

};





	//UPROPERTY(EditAnywhere);

