// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityObject.h"
#include "Delivery1UtilityObject.generated.h"

/**
 * DeliveryOne Tools
 */

UCLASS(Blueprintable)
class TOOLSCLASS_API UDelivery1UtilityObject : public UEditorUtilityObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Delivery1")
	virtual void RunBase();

private:
	void LogAssetDependencies();
	
};
