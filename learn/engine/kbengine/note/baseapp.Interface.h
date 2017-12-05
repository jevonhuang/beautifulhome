//NETWORK_INTERFACE_DECLARE_BEGIN(BaseappInterface)
namespace BaseappInterface
{	
	extern Network::MessageHandlers messageHandlers;
	
	// 客户端请求导入协议。
	//BASEAPP_MESSAGE_DECLARE_ARGS0(importClientMessages, NETWORK_FIXED_MESSAGE)
	class importClientMessagesBaseappMessagehandler0 : public Network::MessageHandler			
	{																			
	public:
		virtual void handle(Network::Channel* pChannel, KBEngine::MemoryStream& s);
	};	
	
	extern const importClientMessagesBaseappMessagehandler0& importClientMessages;	
	
	class importClientMessagesArgs0 : public Network::MessageArgs					
	{																
	public:															
		importClientMessagesArgs0():Network::MessageArgs(){}						
		~importClientMessagesArgs0(){}											
																	
		static void staticAddToBundle(Network::Bundle& s)			
		{															
		}															
		static void staticAddToStream(MemoryStream& s)				
		{															
		}															
		virtual int32 dataSize(void)								
		{															
			return 0;												
		}															
		virtual void addToStream(MemoryStream& s)					
		{															
		}															
		virtual void createFromStream(MemoryStream& s)				
		{															
		}															
	};																
		
	// 客户端entitydef导出。
	//BASEAPP_MESSAGE_DECLARE_ARGS0(importClientEntityDef, NETWORK_FIXED_MESSAGE)
	class importClientEntityDefBaseappMessagehandler0 : public Network::MessageHandler			
	{																			
	public:
		virtual void handle(Network::Channel* pChannel, KBEngine::MemoryStream& s);
	};	
	
	extern const importClientEntityDefBaseappMessagehandler0& importClientEntityDef;	

	class importClientEntityDefArgs0 : public Network::MessageArgs					
	{																
	public:															
		importClientEntityDefArgs0():Network::MessageArgs(){}						
		~importClientEntityDefArgs0(){}											
																	
		static void staticAddToBundle(Network::Bundle& s)			
		{															
		}															
		static void staticAddToStream(MemoryStream& s)				
		{															
		}															
		virtual int32 dataSize(void)								
		{															
			return 0;												
		}															
		virtual void addToStream(MemoryStream& s)					
		{															
		}															
		virtual void createFromStream(MemoryStream& s)				
		{															
		}															
	};
	
	// 某app主动请求断线。
	//BASEAPP_MESSAGE_DECLARE_ARGS0(reqClose, NETWORK_FIXED_MESSAGE)
	class reqCloseBaseappMessagehandler0 : public Network::MessageHandler			
	{																			
	public:
		virtual void handle(Network::Channel* pChannel, KBEngine::MemoryStream& s);
	};
	
	extern const reqCloseBaseappMessagehandler0& reqClose;		

	class reqCloseArgs0 : public Network::MessageArgs					
	{																
	public:															
		reqCloseArgs0():Network::MessageArgs(){}						
		~reqCloseArgs0(){}											
																	
		static void staticAddToBundle(Network::Bundle& s)			
		{															
		}															
		static void staticAddToStream(MemoryStream& s)				
		{															
		}															
		virtual int32 dataSize(void)								
		{															
			return 0;												
		}															
		virtual void addToStream(MemoryStream& s)					
		{															
		}															
		virtual void createFromStream(MemoryStream& s)				
		{															
		}															
	};
	
	// 某app主动请求look。
	// BASEAPP_MESSAGE_DECLARE_ARGS0(lookApp, NETWORK_FIXED_MESSAGE)
	class lookAppBaseappMessagehandler0 : public Network::MessageHandler			
	{																			
	public:
		virtual void handle(Network::Channel* pChannel, KBEngine::MemoryStream& s);
	};	

	extern const lookAppBaseappMessagehandler0& lookApp;	
	
	class lookAppArgs0 : public Network::MessageArgs					
	{																
	public:															
		lookAppArgs0():Network::MessageArgs(){}						
		~lookAppArgs0(){}											
																	
		static void staticAddToBundle(Network::Bundle& s)			
		{															
		}															
		static void staticAddToStream(MemoryStream& s)				
		{															
		}															
		virtual int32 dataSize(void)								
		{															
			return 0;												
		}															
		virtual void addToStream(MemoryStream& s)					
		{															
		}															
		virtual void createFromStream(MemoryStream& s)				
		{															
		}															
	};	
	
	// 某个app请求查看该app负载状态。
	// BASEAPP_MESSAGE_DECLARE_ARGS0(queryLoad, NETWORK_FIXED_MESSAGE)
	class queryLoadBaseappMessagehandler0 : public Network::MessageHandler			
	{																			
	public:
		virtual void handle(Network::Channel* pChannel, KBEngine::MemoryStream& s);
	};	

	extern const queryLoadBaseappMessagehandler0& queryLoad;	
	
	class queryLoadArgs0 : public Network::MessageArgs					
	{																
	public:															
		queryLoadArgs0():Network::MessageArgs(){}						
		~queryLoadArgs0(){}											
																	
		static void staticAddToBundle(Network::Bundle& s)			
		{															
		}															
		static void staticAddToStream(MemoryStream& s)				
		{															
		}															
		virtual int32 dataSize(void)								
		{															
			return 0;												
		}															
		virtual void addToStream(MemoryStream& s)					
		{															
		}															
		virtual void createFromStream(MemoryStream& s)				
		{															
		}															
	};	
		
	// console远程执行python语句。
	// BASEAPP_MESSAGE_DECLARE_STREAM(onExecScriptCommand, NETWORK_VARIABLE_MESSAGE)
	class onExecScriptCommandBaseappMessagehandler_stream : public Network::MessageHandler			
	{																			
	public:
		virtual void handle(Network::Channel* pChannel, KBEngine::MemoryStream& s);
	};	

	extern const onExecScriptCommandBaseappMessagehandler_stream& onExecScriptCommand;	
	
	class onExecScriptCommandArgs_stream : public Network::MessageArgs			
	{																
	public:															
		onExecScriptCommandArgs_stream():Network::MessageArgs(){}				
		~onExecScriptCommandArgs_stream(){}										
																	
		virtual int32 dataSize(void)								
		{															
			return NETWORK_VARIABLE_MESSAGE;						
		}															
		virtual MessageArgs::MESSAGE_ARGS_TYPE type(void)			
		{															
			return MESSAGE_ARGS_TYPE_VARIABLE;						
		}															
		virtual void addToStream(MemoryStream& s)					
		{															
		}															
		virtual void createFromStream(MemoryStream& s)				
		{															
		}															
	};		
	
//NETWORK_INTERFACE_DECLARE_END()
}