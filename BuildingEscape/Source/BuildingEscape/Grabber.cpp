// Software development company copyright.


#include "Grabber.h"
#include "Engine.h"

#define		OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Player see loc:%s - rot:%s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);
	/// true ��� ����� ����������������� ������������ ����, GetOwner(������������ ����� ����)
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	//if (GetWorld()->LineTraceSingleByChannel(OUT Hit,
	//	PlayerViewPointLocation,
	//	LineTraceEnd,
	//	ECollisionChannel::ECC_PhysicsBody,
	//	TraceParameters)) 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Player hit whith %s"), *Hit.GetActor()->GetName());
	//}
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	)) {
		UE_LOG(LogTemp, Warning, TEXT("Player hit whith %s"), *Hit.GetActor()->GetName());
	}

	

	// ...
}

