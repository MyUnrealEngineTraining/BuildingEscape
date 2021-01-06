// Software development company copyright.


#include "Grabber.h"

#define		OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
	if (!PhysicsHandle) return;
	if (PhysicsHandle->GrabbedComponent == nullptr) {
		return;
	} else {
		// move the object that we are holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}

	

}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Missing UPhysicsHandleComponent in %s"), *GetOwner()->GetName());
		return;
	} else {

	}
}

void UGrabber::SetupInputComponent()
{
	MyInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (MyInputComponent) {
		MyInputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		MyInputComponent->BindAction("Grab", IE_Released, this, &UGrabber::UnGrab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing InputComponent in %s"), *GetOwner()->GetName());
		return;
	}
}


void UGrabber::Grab()
{
	/// LINE TRACE and if we reach any actors with physics body collision channels set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();	// gets the mesh in our case
	if (ComponentToGrab == nullptr) return;
	auto ActorHit = HitResult.GetActor();
	/// if we hit something, then attach a phisycs handle
	if (ActorHit) {
		//  attach physics handle
		if (PhysicsHandle == nullptr) return;
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::UnGrab()
{
	if (PhysicsHandle == nullptr) return;
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{	
	//	DrawDebugLine(
	//		GetWorld(),
	//		PlayerViewPointLocation,
	//		GetReachLineEnd(),
	//		FColor(255, 0, 0),
	//		false,
	//		0.0f,
	//		0.0f,
	//		10.0f
	//	);
	/// Create struct for request ( true для более детализированного столкновения луча, GetOwner(игнорировать самих себя))
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	)) {
		UE_LOG(LogTemp, Warning, TEXT("Player hit whith %s"), *Hit.GetActor()->GetName());
	}
	//if (GetWorld()->LineTraceSingleByChannel(OUT Hit,
	//	PlayerViewPointLocation,
	//	GetReachLineEnd(),
	//	ECollisionChannel::ECC_PhysicsBody,
	//	TraceParameters)) 
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Player hit whith %s"), *Hit.GetActor()->GetName());
	//}
	return Hit;
}

const FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return  PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

const FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return  PlayerViewPointLocation;
}

//UE_LOG(LogTemp, Warning, TEXT("Found %s"), *MyInput->GetName());
