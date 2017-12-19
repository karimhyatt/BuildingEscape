// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "Gameframework/Actor.h"
#include "Math/TransformNonVectorized.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString actorName = GetOwner()->GetName();
	FVector loc = GetOwner()->GetTransform().GetTranslation();
	FString position = loc.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *actorName, *position);

}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

