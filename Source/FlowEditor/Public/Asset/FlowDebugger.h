// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

/**
** Minimalistic form of breakpoint debugger
** See BehaviorTreeDebugger for a more complex example
 */
class FLOWEDITOR_API FFlowDebugger
{
public:
	FFlowDebugger();
	~FFlowDebugger();

	static void PausePlaySession();
	static bool IsPlaySessionPaused();
};
