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
		FVector newVelocity;
		newVelocity.X = Velocity.X - 2 * DotProduct * HitResult.Normal.X;
		newVelocity.Y = Velocity.Y - 2 * DotProduct * HitResult.Normal.Y;
		Velocity = newVelocity;
	}
}

