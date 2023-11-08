// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "PA_System.generated.h"

UCLASS()
class CRUSHDEPTH_API APA_System : public AActor
{
	GENERATED_BODY()

	TArray<AActor*> speakers;
	
public:	
	// Sets default values for this actor's properties
	APA_System();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TMap<FString, USoundBase*> sounds = {
		{"computer_malfunction", nullptr},
		{"engine_failure", nullptr},
		{"initiate_dive", nullptr},
		{"initiate_surface", nullptr},
		{"oxygen_failure", nullptr},
		{"power_system", nullptr},
		{"presure_destabilisation", nullptr},
		{"surfaced", nullptr}
	};

	UFUNCTION(BlueprintCallable, Category="PA System")
	void PlayAnnouncement(FString name);

};
