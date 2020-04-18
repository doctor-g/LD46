// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called every frame
//
// See https://stackoverflow.com/a/45160605/176007 for bounce computation
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult HitResult;
	AddActorWorldOffset(Velocity * DeltaTime, true, &HitResult);
	if (HitResult.bBlockingHit)
	{
		float DotProduct = FVector::DotProduct(Velocity, HitResult.Normal);
		FVector NewVelocity;
		NewVelocity.X = Velocity.X - 2 * DotProduct * HitResult.Normal.X;
		NewVelocity.Y = Velocity.Y - 2 * DotProduct * HitResult.Normal.Y;

		// Move along the new velocity scaled by how much "time" we went into the blocking hit,
		// this time without sweeping.
		AddActorWorldOffset(NewVelocity * DeltaTime * (1-HitResult.Time), false);

		Velocity = NewVelocity;
	}
}

