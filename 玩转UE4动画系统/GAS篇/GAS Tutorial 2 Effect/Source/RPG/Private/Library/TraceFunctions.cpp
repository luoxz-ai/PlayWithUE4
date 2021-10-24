﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/TraceFunctions.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UTraceFunctions::TraceForTarget(const AActor* Actor,const float Distance,const EDrawDebugTrace::Type DrawDebugTraceType,bool& Detected,ARPGCharacterBase*& Target)
{
	Detected = false;
	if(Actor != nullptr)
	{
		const FVector Location = Actor->GetActorLocation();
		const FVector Forward = Actor->GetActorForwardVector();
		const FVector Start = Location;
		const FVector End = Start + Forward*Distance;
		const FRotator Orientation = UKismetMathLibrary::MakeRotFromX(Forward);
		TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
		ObjectTypes.Add(static_cast<EObjectTypeQuery>(ECollisionChannel::ECC_Pawn));
		FHitResult Result;
		const TArray<AActor*> ActorsToIgnore;
		UKismetSystemLibrary::BoxTraceSingleForObjects(Actor,Start,End,FVector(0.0,50.0,90.0),Orientation,ObjectTypes,false,ActorsToIgnore,DrawDebugTraceType,Result,true);
		Target = Cast<ARPGCharacterBase>(Result.GetActor());
		Detected = Result.bBlockingHit&&Target!=nullptr;
	}
}
