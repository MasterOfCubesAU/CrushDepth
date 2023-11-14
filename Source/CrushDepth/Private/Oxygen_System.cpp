// Fill out your copyright notice in the Description page of Project Settings.


#include "Oxygen_System.h"

UOxygen_System::UOxygen_System()
{
	GConfig->GetFloat(TEXT("Player"), TEXT("OxygenDepletionRate"), this->DepletionRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	GConfig->GetFloat(TEXT("Player"), TEXT("PlayerStartOxygen"), this->MaxOxygen, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	this->CurrentOxygen = this->MaxOxygen;
}

float UOxygen_System::GetCurrentOxygen() {
	return this->CurrentOxygen;
}
// Please do not use this function to "deplete" oxygen. Use UOxygen_System::ConsumeOxygen() instead.
void UOxygen_System::SetCurrentOxygen(float Amount) {
	this->CurrentOxygen = std::max(0.f, std::min(Amount, this->MaxOxygen));
	if (this->CurrentOxygen == 0.f)
	{
		this->OnOxygenFinish();
	}
}

float UOxygen_System::GetMaxOxygen() {
	return this->MaxOxygen;
}
void UOxygen_System::SetMaxOxygen(float Amount) {
	this->DepletionRate = std::max(0.f, Amount);
}

float UOxygen_System::GetDepletionRate() { return this->DepletionRate; }
void UOxygen_System::SetDepletionRate(float Amount) {
	this->DepletionRate = std::max(0.f, Amount);
}

void UOxygen_System::ConsumeOxygen()
{
	this->SetCurrentOxygen(this->CurrentOxygen - this->DepletionRate);
}
