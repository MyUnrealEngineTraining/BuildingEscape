// Software development company copyright.


#include "OpenDoor.h"

#define		OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (Owner == nullptr) {
	UE_LOG(LogTemp, Error, TEXT("Owner component not found, in the ActorComponent OpenDoor"));
		return;
	}
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("PressurePlate not found in %s"), *Owner->GetName());
		return;
	}

	// ...
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if(GetTotalMassOfActorsOnPlate() > TriggerMass)	
	{
		OnOpen.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Total mass = %f"), GetTotalMassOfActorsOnPlate());
	} else {
		OnClose.Broadcast();
	}

	// ...
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PressurePlate == nullptr) return TotalMass;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// Iterate through them adding their mass
	for (const auto& actor: OverlappingActors) {
		//UE_LOG(LogTemp, Warning, TEXT("Found %s"), *MyInput->GetName());        
		float mass = actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s: mass = %f"), *actor->GetName(), mass);
		TotalMass += mass;
		//UE_LOG(LogTemp, Warning, TEXT("Found %f"), TotalMass);
	}

	return TotalMass;
}

