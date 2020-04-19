// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatInterpFalloffComponent.h"

// Sets default values for this component's properties
UFloatInterpFalloffComponent::UFloatInterpFalloffComponent()
	: IntensitySpeed(2)
	, TargetIntensityFalloffSpeed(4)
	, MaxTarget(1)
	, bUseMaxTarget(true)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}



// Called every frame
void UFloatInterpFalloffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Move the intensity toward the target
	Intensity = FMath::FInterpTo(Intensity, Intensity < TargetIntensity ? TargetIntensity : 0, DeltaTime, IntensitySpeed);

	// Reduce the target
	TargetIntensity = FMath::FInterpTo(TargetIntensity, 0, DeltaTime, TargetIntensityFalloffSpeed);	
}

void UFloatInterpFalloffComponent::BoostTargetIntensity(float Amount)
{
	TargetIntensity += Amount;
	if (bUseMaxTarget)
	{
		TargetIntensity = FMath::Max(TargetIntensity, MaxTarget);
	}
}

