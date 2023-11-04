// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_Core.h"

AGS_Core::AGS_Core() {
    GConfig->GetFloat(TEXT("Submarine"), TEXT("SubmarineStartHealth"), this->SubmarineStartHealth, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
    GConfig->GetFloat(TEXT("Submarine"), TEXT("SubmarineAscentRate"), this->AscentRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
    GConfig->GetFloat(TEXT("Submarine"), TEXT("SubmarineDescentRate"), this->DescentRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
    this->CurrentSubmarineHealth = this->SubmarineStartHealth;
    this->CurrentSubmarineDepth = 0.f;
    this->CurrentBestAttempt = CurrentSubmarineDepth;
    this->CurrentSubmarineState = SubmarineStates::Surfaced;
    GConfig->GetFloat(TEXT("Player"), TEXT("MoneyGenerationRate"), this->MoneyRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
    // Seed random
    srand(time(0));
}

// Health

float AGS_Core::GetSubmarineHealth() {
    return this->CurrentSubmarineHealth;
};

void AGS_Core::SetSubmarineHealth(float NewHealth) {
    this->CurrentSubmarineHealth = std::max(0.f, std::min(NewHealth, this->SubmarineStartHealth));
};

void AGS_Core::SubtractSubmarineHealth(float Amount) {
    this->SetSubmarineHealth(this->CurrentSubmarineHealth - Amount);
};

// Submarine Depth

float AGS_Core::GetSubmarineDepth() {
    return this->CurrentSubmarineDepth;
};

float AGS_Core::GetCurrentBestAttempt() {
    return this->CurrentBestAttempt;
};

// Submarine States

SubmarineStates AGS_Core::GetSubmarineState() {
    return this->CurrentSubmarineState;
}

bool AGS_Core::ToggleDive() {
    switch (this->CurrentSubmarineState)
    {
    case SubmarineStates::Surfaced:
        this->StartDescent();
        return true;
    case SubmarineStates::Ascending:
        return false;
    case SubmarineStates::Descending:
        this->StartAscent();
        return true;
    default:
        return false;
    }
  
}

void AGS_Core::StartDescent() {
    this->CurrentSubmarineState = SubmarineStates::Descending;
    GetWorld()->GetTimerManager().SetTimer(
        DiveTimer,
        this,
        &AGS_Core::DoDive,
        1.0f,
        true);
}

void AGS_Core::DoDive() {
    float DiveRate;
    this->CurrentSubmarineState == SubmarineStates::Descending ? DiveRate = this->DescentRate :  DiveRate = -this->AscentRate;

    int MaxRand = std::abs(DiveRate) * 1.5;
    this->CurrentSubmarineDepth = std::max(0.f, this->CurrentSubmarineDepth + DiveRate + (DiveRate > 0 ? 1 : -1) * (std::rand() % MaxRand) );
    if (this->CurrentSubmarineDepth == 0.f)
    {
        this->CurrentSubmarineState = SubmarineStates::Surfaced;
        GetWorld()->GetTimerManager().ClearTimer(DiveTimer);
    }
    // Update best attempt
    if (this->CurrentSubmarineDepth > this->CurrentBestAttempt)
    {
        this->CurrentBestAttempt = this->CurrentSubmarineDepth;
    }
    // Update player money
    // Don't distribute money if less than midpoint of current best attempt.
    if (this->CurrentSubmarineState != SubmarineStates::Descending || this->CurrentSubmarineDepth <= this->CurrentBestAttempt / 2.f)
    {
        return;
    }
    
    // Iterate through all players and add money
    for (FConstPlayerControllerIterator iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
    {
        APlayerController* Player = Cast<APlayerController>(*iterator);
        
        float BaseMoneyRate = this->MoneyRate;
        float AmountToAdd = this->CurrentSubmarineDepth >= this->CurrentBestAttempt / 2.f && this->CurrentSubmarineDepth < this->CurrentBestAttempt ? BaseMoneyRate / 2.0 : BaseMoneyRate;

        // Update Money
        ((ACD_PlayerState*)Player->PlayerState)->wallet->AddBalance(AmountToAdd);
    }
    
}

void AGS_Core::StartAscent() {
    this->CurrentSubmarineState = SubmarineStates::Ascending;
}

void AGS_Core::SetAscentRate(float NewRate) {
    this->AscentRate = NewRate;
}

float AGS_Core::GetAscentRate() {
    return AscentRate;
}

void AGS_Core::SetDescentRate(float NewRate) {
    this->DescentRate = NewRate;
}

float AGS_Core::GetDescentRate() {
    return DescentRate;
}

void AGS_Core::OnGameOver() {
    // Save Best Attempt to file
    float BestAttempt = this->GetBestAttempt();
    if (this->CurrentBestAttempt > BestAttempt)
    {
        GConfig->SetFloat(TEXT("Stats"), TEXT("BestAttempt"), this->CurrentBestAttempt, FPaths::ProjectConfigDir() / TEXT("SaveData.ini"));
        GConfig->Flush(false, FPaths::ProjectConfigDir() / TEXT("SaveData.ini"));
    }
}

float AGS_Core::GetBestAttempt() {
    float BestAttempt = 0;
    GConfig->GetFloat(TEXT("Stats"), TEXT("BestAttempt"), BestAttempt, FPaths::ProjectConfigDir() / TEXT("SaveData.ini"));
    return BestAttempt;
}

float AGS_Core::GetMoneyRate() {
    return MoneyRate;
}

void AGS_Core::SetMoneyRate(float NewRate) {
    this->MoneyRate = NewRate;
}

int32 AGS_Core::GetUpgradeTier(FString UpgradeType) {
    return UpgradeTiers[UpgradeType];
}

void AGS_Core::SetUpgradeTier(FString UpgradeType, int32 Tier) {
    UpgradeTiers[UpgradeType] = Tier;
}