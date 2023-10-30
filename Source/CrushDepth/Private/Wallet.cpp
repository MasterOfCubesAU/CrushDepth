// Fill out your copyright notice in the Description page of Project Settings.


#include "Wallet.h"

UWallet::UWallet()
{
	this->Balance = 0;
}

float UWallet::GetBalance()
{
	return this->Balance;
}

void UWallet::SetBalance(float Amount)
{
	this->Balance = std::max(0.f, Amount);
}

void UWallet::SubtractBalance(float Amount)
{
	this->Balance = std::max(0.f, this->Balance - Amount);
}

void UWallet::AddBalance(float Amount)
{
	this->Balance = std::max(0.f, this->Balance + Amount);
}
