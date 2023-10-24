// Fill out your copyright notice in the Description page of Project Settings.


#include "GS_Core.h"


float AGS_Core::GetSubmarineHealth() {
    return CurrentSubmarineHealth;
};

void AGS_Core::SetSubmarineHealth(float NewHealth) {
    CurrentSubmarineHealth = std::max(0.f, std::min(NewHealth, SubmarineStartHealth));
};

void AGS_Core::SubtractSubmarineHealth(float Amount) {
    SetSubmarineHealth(CurrentSubmarineHealth - Amount);
};