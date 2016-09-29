// Copyright Daniel Goldaraz 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	AActor* owner = GetOwner();
	initialDoorRotation = owner->GetActorRotation().Yaw;
	isDoorOpen = false;

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	isDoorOpen = true;
	// Find the owner
	AActor* owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, openAngle, 0.0f);
	owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	isDoorOpen = false;
	// Find the owner
	AActor* owner = GetOwner();
	FRotator newRotation = FRotator(0.0f, initialDoorRotation, 0.0f);
	owner->SetActorRotation(newRotation);
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume every frame
	//If the actor that opens is in the volume, then open the door
	if (pressurePlate)
	{
		if (pressurePlate->IsOverlappingActor(actorThatOpens))
		{
			OpenDoor();
		}
		else if(isDoorOpen)
		{
			CloseDoor();
		}
	}
	
}

