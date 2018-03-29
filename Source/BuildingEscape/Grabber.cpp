// Copyright 2017 Pantheon Productions. All Rights Reserved

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

#define OUT

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

	FindPhsyicsHandleComponent();
	SetupInputComponent();


}

void UGrabber::FindPhsyicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does have a PhysicsHandle"), *GetOwner()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a PhysicsHandle"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does have an InputController"), *GetOwner()->GetName())

			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have an InputController"), *GetOwner()->GetName())
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"))
		/// Line trace and see whether we reach actors with physics body collision channel set

		/// If we hit anything, attach a physics handle
		GetFirstPhysicsBodyInReach();
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
	/// Release physics Handle

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physiscs handle is attached, move the object we're holding


}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	FVector LineEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

	/// Set up Query Parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA Ray-Cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);


	/// See WHat we Hit
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Obejct hit: %s"), *(ActorHit->GetName()))
	}


	return FHitResult();
}
