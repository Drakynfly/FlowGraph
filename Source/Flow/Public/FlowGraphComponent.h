// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

#include "FlowComponent.h"
#include "GameplayTagContainer.h"

#include "FlowSave.h"
#include "FlowTypes.h"
#include "FlowGraphComponent.generated.h"

/**
* Base component of Flow System - extends flow component to add ability to begin a flow graph instance
*/
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class FLOW_API UFlowGraphComponent : public UFlowComponent
{
	GENERATED_BODY()

	friend class UFlowSubsystem;

	UFlowGraphComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PostRegister(bool LoadedFromInstance) override;

protected:
	virtual void OnSave_Implementation() override;
	virtual void OnLoad_Implementation() override;

//////////////////////////////////////////////////////////////////////////
// Root Flow

public:
	// Asset that might instantiated as "Root Flow"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root Flow")
	UFlowAsset* RootFlow;

	// If true, component will start Root Flow on Begin Play
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root Flow")
	bool bAutoStartRootFlow;

	// Networking mode for creating this Root Flow
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root Flow")
	EFlowNetMode RootFlowMode;

	// If false, another Root Flow instance won't be created from this component, if this Flow Asset is already instantiated
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root Flow")
	bool bAllowMultipleInstances;

	UPROPERTY(SaveGame)
	FString SavedAssetInstanceName;

	// This will instantiate Flow Asset assigned on this component.
	// Created Flow Asset instance will be a "root flow", as additional Flow Assets can be instantiated via Sub Graph node
	UFUNCTION(BlueprintCallable, Category = "Root Flow")
	void StartRootFlow();

	// This will destroy instantiated Flow Asset - created from asset assigned on this component.
	UFUNCTION(BlueprintCallable, Category = "Root Flow")
	void FinishRootFlow(const EFlowFinishPolicy FinishPolicy);

//////////////////////////////////////////////////////////////////////////
// SaveGame

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	virtual void SaveRootFlow(TArray<FFlowAssetSaveData>& SavedFlowInstances);

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	virtual void LoadRootFlow();
};