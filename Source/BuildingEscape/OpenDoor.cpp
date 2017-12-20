// Copyright 2017 Pantheon Productions. All Rights Reserved

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

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

	ActorThatOpensTheDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();

}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll Triggervolume very framne

	// If the ActorThatOpensDoor is in the volume then we open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpensTheDoor))
	{
		OpenDoor();
		LastTimeDoorOpen = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastTimeDoorOpen > CloseDoorDelay)
		CloseDoor();


}

