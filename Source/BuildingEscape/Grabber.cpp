// Copyright 2017 Pantheon Productions. All Rights Reserved

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

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

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber Reporting for Duty!"));




}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ViewpointVector;
	FRotator ViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewpointVector, OUT ViewpointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Viewpoint: %s"), *ViewpointVector.ToString());
	

	FVector LineEnd = ViewpointVector + ViewpointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		ViewpointVector,
		LineEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);


}

