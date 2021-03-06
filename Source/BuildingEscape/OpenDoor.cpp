// Copyright 2017 Pantheon Productions. All Rights Reserved

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

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
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is not set to a reference"))
	}

}

void UOpenDoor::OpenDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	if (!Owner) { return; }
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


float UOpenDoor::GetTotalMassOfActors()
{

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("PressurePlate is not set to a reference"))
		return 0;
	}

	float totalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> overlappingActors;



	PressurePlate->GetOverlappingActors(overlappingActors);
	// Iterate through them adding total masses
	for (const auto* actor : overlappingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return totalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll Triggervolume very framne

	if (GetTotalMassOfActors() > 30.f) // TODO: Make into a parameter
	{
		OpenDoor();
		LastTimeDoorOpen = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastTimeDoorOpen > CloseDoorDelay)
		CloseDoor();


}

