// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
	: IncreaseRate(.01)
	, MaxSpeed(1500)
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
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

		// Update the velocity, accounting for the bounce increase
		NewVelocity *= (1 + IncreaseRate);
		// Trap the bug that makes the ball sometimes slow down
		if (Velocity.SizeSquared() > NewVelocity.SizeSquared())
		{
			UE_LOG(LogTemp, Display, TEXT("Encountered the slowdown bug"));
			NewVelocity *= Velocity.Size() / NewVelocity.Size();
		}
		Velocity = NewVelocity;

		// Cap the velocity below maxspeed
		if (Velocity.Size() >= MaxSpeed)
		{
			Velocity = Velocity * MaxSpeed / Velocity.Size();
		}
	}

	// Damage the thing that is hit if it can take damage.
	if (AActor* Target = HitResult.Actor.Get())
	{
		if (Target->CanBeDamaged())
		{
			Target->TakeDamage(1, FDamageEvent(), GetWorld()->GetFirstPlayerController(), this);
		}
	}
	
}

