// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_Core.h"

AGS_Core::AGS_Core() {
    this->CurrentSubmarineHealth = this->SubmarineStartHealth;
    UE_LOG(LogTemp, Warning, TEXT("Current Submarine Health: %f"), this->CurrentSubmarineHealth)
}

float AGS_Core::GetSubmarineHealth() {
    return this->CurrentSubmarineHealth;
};

void AGS_Core::SetSubmarineHealth(float NewHealth) {
    this->CurrentSubmarineHealth = std::max(0.f, std::min(NewHealth, SubmarineStartHealth));
};

void AGS_Core::SubtractSubmarineHealth(float Amount) {
    this->SetSubmarineHealth(this->CurrentSubmarineHealth - Amount);
};