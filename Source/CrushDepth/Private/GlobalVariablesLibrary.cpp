// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalVariablesLibrary.h"

// ====================================================
// =============== SUBMARINE VARIABLES ================
// ====================================================
float UGlobalVariablesLibrary::GetSubmarineStartHealth() {
	float SubmarineStartHealth;
	GConfig->GetFloat(TEXT("Submarine"), TEXT("SubmarineStartHealth"), SubmarineStartHealth, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return SubmarineStartHealth;
}

void UGlobalVariablesLibrary::SetSubmarineStartHealth(float SubmarineStartHealth) {
	GConfig->SetFloat(TEXT("Submarine"), TEXT("SubmarineStartHealth"), SubmarineStartHealth, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

float UGlobalVariablesLibrary::GetCurrentSubmarineHealth() {
	float CurrentSubmarineHealth;
	GConfig->GetFloat(TEXT("Submarine"), TEXT("CurrentSubmarineHealth"), CurrentSubmarineHealth, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return CurrentSubmarineHealth;
}

void UGlobalVariablesLibrary::SetCurrentSubmarineHealth(float CurrentSubmarineHealth) {
	GConfig->SetFloat(TEXT("Submarine"), TEXT("CurrentSubmarineHealth"), CurrentSubmarineHealth, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

float UGlobalVariablesLibrary::GetSubmarineDescentRate() {
	float SubmarineDescentRate;
	GConfig->GetFloat(TEXT("Submarine"), TEXT("SubmarineDescentRate"), SubmarineDescentRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return SubmarineDescentRate;
}

void UGlobalVariablesLibrary::SetSubmarineDescentRate(float SubmarineDescentRate) {
	GConfig->SetFloat(TEXT("Submarine"), TEXT("SubmarineDescentRate"), SubmarineDescentRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

// ====================================================
// ================= PLAYER VARIABLES =================
// ====================================================
float UGlobalVariablesLibrary::GetPlayerMoney() {
	float Money;
	GConfig->GetFloat(TEXT("Player"), TEXT("Money"), Money, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return Money;
}

void UGlobalVariablesLibrary::SetPlayerMoney(float Money) {
	GConfig->SetFloat(TEXT("Player"), TEXT("Money"), Money, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

float UGlobalVariablesLibrary::GetPlayerSpeed() {
	float Speed;
	GConfig->GetFloat(TEXT("Player"), TEXT("PlayerSpeed"), Speed, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return Speed;
}

void UGlobalVariablesLibrary::SetPlayerSpeed(float Speed) {
	GConfig->SetFloat(TEXT("Player"), TEXT("Speed"), Speed, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

float UGlobalVariablesLibrary::GetMoneyGenerationRate() {
	float MoneyGenerationRate;
	GConfig->GetFloat(TEXT("Player"), TEXT("MoneyGenerationRate"), MoneyGenerationRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return MoneyGenerationRate;
}

void UGlobalVariablesLibrary::SetMoneyGenerationRate(float MoneyGenerationRate) {
	GConfig->SetFloat(TEXT("Player"), TEXT("MoneyGenerationRate"), MoneyGenerationRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

// ====================================================
// ================= PLAYER VARIABLES =================
// ====================================================
float UGlobalVariablesLibrary::GetTaskSpawnRate() {
	float TaskSpawnRate;
	GConfig->GetFloat(TEXT("Environment"), TEXT("TaskSpawnRate"), TaskSpawnRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return TaskSpawnRate;
}

void UGlobalVariablesLibrary::SetTaskSpawnRate(float TaskSpawnRate) {
	GConfig->SetFloat(TEXT("Environment"), TEXT("TaskSpawnRate"), TaskSpawnRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

float UGlobalVariablesLibrary::GetMaxOxygen() {
	float MaxOxygen;
	GConfig->GetFloat(TEXT("Environment"), TEXT("MaxOxygen"), MaxOxygen, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return MaxOxygen;
}

void UGlobalVariablesLibrary::SetMaxOxygen(float MaxOxygen) {
	GConfig->SetFloat(TEXT("Environment"), TEXT("MaxOxygen"), MaxOxygen, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}

float UGlobalVariablesLibrary::GetOxygenDepletionRate() {
	float OxygenDepletionRate;
	GConfig->GetFloat(TEXT("Environment"), TEXT("OxygenDepletionRate"), OxygenDepletionRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return OxygenDepletionRate;
}

void UGlobalVariablesLibrary::SetOxygenDepletionRate(float OxygenDepletionRate) {
	GConfig->SetFloat(TEXT("Environment"), TEXT("OxygenDepletionRate"), OxygenDepletionRate, FPaths::ProjectConfigDir() / TEXT("GlobalVariables.ini"));
	return;
}