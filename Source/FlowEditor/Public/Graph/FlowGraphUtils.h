// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

class FFlowAssetEditor;

class FLOWEDITOR_API FFlowGraphUtils
{
public:
	FFlowGraphUtils() {}

	static TSharedPtr<FFlowAssetEditor> GetFlowAssetEditor(const UObject* ObjectToFocusOn);
};
