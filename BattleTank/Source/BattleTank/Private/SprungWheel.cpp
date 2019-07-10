// Copyright MetalMuffin Entertainment 2018


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Defaults
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass Mesh"));
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel Mesh"));
	ConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint Component"));

	//Attachments
	SetRootComponent(Mass);
	Mass->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ConstraintComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

