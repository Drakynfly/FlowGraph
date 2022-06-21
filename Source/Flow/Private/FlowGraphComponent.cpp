// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#include "FlowGraphComponent.h"

#include "FlowAsset.h"
#include "FlowSubsystem.h"

#include "Engine/ViewportStatsSubsystem.h"

UFlowGraphComponent::UFlowGraphComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RootFlow(nullptr)
	, bAutoStartRootFlow(true)
	, RootFlowMode(EFlowNetMode::Authority)
	, bAllowMultipleInstances(true)
{
}

void UFlowGraphComponent::PostRegister(const bool LoadedFromInstance)
{
	Super::PostRegister(LoadedFromInstance);

	if (RootFlow)
	{
		if (LoadedFromInstance)
		{
			LoadRootFlow();
		}
		else if (bAutoStartRootFlow)
		{
			StartRootFlow();
		}
	}
}

void UFlowGraphComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UFlowSubsystem* FlowSubsystem = GetFlowSubsystem())
	{
		FlowSubsystem->FinishRootFlow(this, EFlowFinishPolicy::Keep);
	}

	Super::EndPlay(EndPlayReason);
}

void UFlowGraphComponent::StartRootFlow()
{
	if (RootFlow && IsFlowNetMode(RootFlowMode))
	{
		if (UFlowSubsystem* FlowSubsystem = GetFlowSubsystem())
		{
			VerifyIdentityTags();

			FlowSubsystem->StartRootFlow(this, RootFlow, bAllowMultipleInstances);
		}
	}
}

void UFlowGraphComponent::FinishRootFlow(const EFlowFinishPolicy FinishPolicy)
{
	if (UFlowSubsystem* FlowSubsystem = GetFlowSubsystem())
	{
		FlowSubsystem->FinishRootFlow(this, FinishPolicy);
	}
}

void UFlowGraphComponent::SaveRootFlow(TArray<FFlowAssetSaveData>& SavedFlowInstances)
{
	if (UFlowAsset* FlowAssetInstance = GetRootFlowInstance())
	{
		const FFlowAssetSaveData AssetRecord = FlowAssetInstance->SaveInstance(SavedFlowInstances);
		SavedAssetInstanceName = AssetRecord.InstanceName;
		return;
	}

	SavedAssetInstanceName = FString();
}

void UFlowGraphComponent::LoadRootFlow()
{
	if (RootFlow && !SavedAssetInstanceName.IsEmpty() && GetFlowSubsystem())
	{
		VerifyIdentityTags();

		GetFlowSubsystem()->LoadRootFlow(this, RootFlow, SavedAssetInstanceName);
		SavedAssetInstanceName = FString();
	}
}

void UFlowGraphComponent::OnSave_Implementation()
{
}

void UFlowGraphComponent::OnLoad_Implementation()
{
}