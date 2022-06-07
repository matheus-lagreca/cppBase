// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeHitBoxData.h"

TArray<FMEleeHitSphereDefinition> UMeleeHitBoxData::GetMeleeHitSpheres(TArray<int> indexes)
{
	TArray<FMEleeHitSphereDefinition> hitSphereSubset;

	for (int i = 0; i< indexes.Num(); i++)
	{
		int currentIndex = indexes[i];

		if (MeleeHitSpheres.Num() > currentIndex && currentIndex >= 0)
		{
			hitSphereSubset.Add(MeleeHitSpheres[currentIndex]);
		}
	}
	return hitSphereSubset;
}
