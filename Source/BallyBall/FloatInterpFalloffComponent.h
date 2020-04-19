// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatInterpFalloffComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLYBALL_API UFloatInterpFalloffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatInterpFalloffComponent();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Boost the target intensity by the given amount
	UFUNCTION(BlueprintCallable)
	void BoostTargetIntensity(float Amount);

	// The actual current intensity
	UPROPERTY(BlueprintReadOnly)
	float Intensity;

	// The rate of change of the intensity 
	UPROPERTY(EditAnywhere)
	float IntensitySpeed;

	// The rate of intensity falloff
	UPROPERTY(EditAnywhere)
	float TargetIntensityFalloffSpeed;

	// The current target intensity.
	UPROPERTY(EditAnywhere)
	float TargetIntensity;

	// The maximum allowed target
	UPROPERTY(EditAnywhere)
	float MaxTarget;

	// Whether the maximum target should be used
	UPROPERTY(EditAnywhere)
	bool bUseMaxTarget;

};
