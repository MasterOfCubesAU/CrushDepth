// Fill out your copyright notice in the Description page of Project Settings.


#include "PA_System.h"


// Sets default values
APA_System::APA_System()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APA_System::BeginPlay()
{
	Super::BeginPlay();
	if (this->sound || true)
	{
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("PA_Loudspeaker"), this->speakers);
		UE_LOG(LogTemp, Warning, TEXT("Found %d speakers"), this->speakers.Num());
		this->PlayAnnouncement(TEXT("A"));
	}
	
}

// Called every frame
void APA_System::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APA_System::PlayAnnouncement(FString name)
{
	//FString file_path = FString::Printf(TEXT("/Game/Assets/Sounds/PA/%s"), *name);
	//USoundWave* sound = StaticLoadObject<USoundWave>(FName(*file_path));
	for (AActor* speaker : this->speakers)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), this->sound, speaker->GetActorLocation());
	}
}

