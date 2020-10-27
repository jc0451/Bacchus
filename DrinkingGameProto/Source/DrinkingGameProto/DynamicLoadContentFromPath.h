// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DynamicLoadContentFromPath.generated.h"

/**
 * 
 */
UCLASS()
class DRINKINGGAMEPROTO_API UDynamicLoadContentFromPath : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

		UFUNCTION(BlueprintCallable, Category = "Sweet")
		static TArray<UObject*> DynamicLoadContentFromPath(FString PathFromContentFolder = "Images", UClass* AssetClass = nullptr, bool LoadFromSubfolders = false);
};

		
