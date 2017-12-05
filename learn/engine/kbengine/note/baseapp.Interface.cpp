//NETWORK_INTERFACE_DECLARE_BEGIN(BaseappInterface)
namespace BaseappInterface
{
	Network::MessageHandlers messageHandlers;
	
	// 客户端请求导入协议。
	//BASEAPP_MESSAGE_EXPOSED(importClientMessages)
	bool pBaseappimportClientMessages_exposed = messageHandlers.pushExposedMessage("Baseapp::importClientMessages");	
	//BASEAPP_MESSAGE_DECLARE_ARGS0(importClientMessages, NETWORK_FIXED_MESSAGE)
	void importClientMessagesBaseappMessagehandler0::handle(Network::Channel* pChannel, KBEngine::MemoryStream& s)
	{
			KBEngine::Baseapp::getSingleton().importClientMessages(pChannel);
	}	
	importClientMessagesBaseappMessagehandler0* pimportClientMessages = static_cast<importClientMessagesBaseappMessagehandler0>(messageHandlers.add("Baseapp::importClientMessages", new importClientMessagesArgs0, 0, new importClientMessagesBaseappMessagehandler0)
	const importClientMessagesBaseappMessagehandler0& importClientMessages = *pimportClientMessages

	// 客户端entitydef导出。
	//BASEAPP_MESSAGE_EXPOSED(importClientEntityDef)
	bool pBaseappimportClientEntityDef_exposed = messageHandlers.pushExposedMessage("Baseapp::importClientEntityDef");	
	//BASEAPP_MESSAGE_DECLARE_ARGS0(importClientEntityDef, NETWORK_FIXED_MESSAGE)
	void importClientEntityDefBaseappMessagehandler0::handle(Network::Channel* pChannel, KBEngine::MemoryStream& s)
	{
			KBEngine::Baseapp::getSingleton().importClientEntityDef(pChannel);
	}	
	importClientEntityDefBaseappMessagehandler0* pimportClientEntityDef = static_cast<importClientEntityDefBaseappMessagehandler0>(messageHandlers.add("Baseapp::importClientEntityDef", new importClientEntityDefArgs0, 0, new importClientEntityDefBaseappMessagehandler0)
	const importClientEntityDefBaseappMessagehandler0& importClientEntityDef = *pimportClientEntityDef	
	
	// 某app主动请求断线。
	//BASEAPP_MESSAGE_DECLARE_ARGS0(reqClose, NETWORK_FIXED_MESSAGE)
	void reqCloseBaseappMessagehandler0::handle(Network::Channel* pChannel, KBEngine::MemoryStream& s)
	{
			KBEngine::Baseapp::getSingleton().reqClose(pChannel);
	}	
	reqCloseBaseappMessagehandler0* preqClose = static_cast<reqCloseBaseappMessagehandler0>(messageHandlers.add("Baseapp::reqClose", new reqCloseArgs0, 0, new reqCloseBaseappMessagehandler0)
	const reqCloseBaseappMessagehandler0& reqClose = *preqClose		
	
	// 某app主动请求look。
	//BASEAPP_MESSAGE_DECLARE_ARGS0(lookApp, NETWORK_FIXED_MESSAGE)
	void lookAppBaseappMessagehandler0::handle(Network::Channel* pChannel, KBEngine::MemoryStream& s)
	{
			KBEngine::Baseapp::getSingleton().lookApp(pChannel);
	}		
	lookAppBaseappMessagehandler0* lookApp = static_cast<lookAppBaseappMessagehandler0>(messageHandlers.add("Baseapp::lookApp", new lookAppArgs0, 0, new lookAppBaseappMessagehandler0)
	const lookAppBaseappMessagehandler0& lookApp = *plookApp			

	// 某个app请求查看该app负载状态。
	// BASEAPP_MESSAGE_DECLARE_ARGS0(queryLoad, NETWORK_FIXED_MESSAGE)
	void queryLoadBaseappMessagehandler0::handle(Network::Channel* pChannel, KBEngine::MemoryStream& s)
	{
			KBEngine::Baseapp::getSingleton().queryLoad(pChannel);
	}		
	queryLoadBaseappMessagehandler0* queryLoad = static_cast<queryLoadBaseappMessagehandler0>(messageHandlers.add("Baseapp::queryLoad", new queryLoadArgs0, 0, new queryLoadBaseappMessagehandler0)
	const queryLoadBaseappMessagehandler0& queryLoad = *pqueryLoad	

	// console远程执行python语句。
	// BASEAPP_MESSAGE_DECLARE_ARGS0(onExecScriptCommand, NETWORK_FIXED_MESSAGE)
	void onExecScriptCommandBaseappMessagehandler_stream::handle(Network::Channel* pChannel, KBEngine::MemoryStream& s)
	{
			KBEngine::Baseapp::getSingleton().onExecScriptCommand(pChannel, s);
	}		
	onExecScriptCommandBaseappMessagehandler_stream* onExecScriptCommand = static_cast<onExecScriptCommandBaseappMessagehandler_stream>(messageHandlers.add("Baseapp::onExecScriptCommand", new onExecScriptCommandArgs_stream, -1, new onExecScriptCommandBaseappMessagehandler_stream)
	const onExecScriptCommandBaseappMessagehandler_stream& onExecScriptCommand = *ponExecScriptCommand	
	
//NETWORK_INTERFACE_DECLARE_END()	
}