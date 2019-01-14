module Kbe
{
	export class NetworkInterface
	{
		private socket: WebSocket = undefined;
		private onOpenCB: Function = undefined;

		get IsGood(): boolean
		{
			return this.socket != undefined && this.socket.readyState === WebSocket.OPEN;
		}

		ConnectTo(addr: string, callbackFunc?: (event:Event)=>any)
		{
			try
			{
				this.socket = new WebSocket(addr);
			}
			catch(e)
			{
				Logger.Error("NetworkInterface::Connect:Init socket error:" + e);
				Event.Fire("onConnectionState", false);
				return;
			}

			this.socket.binaryType = "arraybuffer";

			this.socket.onerror = this.onerror;
			this.socket.onclose = this.onclose;
			this.socket.onmessage = this.onmessage;
			this.socket.onopen = this.onopen;
			if(callbackFunc)
			{
				this.onOpenCB = callbackFunc;
			}
		}

		Close()
		{
			try
			{
				Logger.Info("networkinterface::Close on good:" + this.IsGood)
				if(this.socket != undefined)
				{
					this.socket.close();
					this.socket.onclose = undefined;
					this.socket = undefined;
				}
			}
			catch(e)
			{
				Logger.Error("networkinterface::Close error:%s.", e);
			}
		}

		Send(buffer: ArrayBuffer)
		{
			if(!this.IsGood)
			{
				Logger.Error("networkinterface::Send:socket is unavailable.");
				return;
			}

			try
			{
				Logger.Debug("networkinterface::Send buffer length:[%d].", buffer.byteLength);
				this.socket.send(buffer);
			}
			catch(e)
			{
				Logger.Error("networkinterface::Send error:%s.", e);
			}
		}

		private onopen = (event: MessageEvent) =>
		{
			Logger.Debug("networkinterface::onopen:success!");
			if(this.onOpenCB)
			{
				this.onOpenCB(event);
				this.onOpenCB = undefined;
			}
		}
		
		private onerror = (event: MessageEvent) =>
		{
			Logger.Debug("networkinterface::onerror:...!");
			Event.Fire("onNetworkError", event);
		}

		private onmessage = (event: MessageEvent) =>
		{
			let data: ArrayBuffer = event.data;
			//Logger.Debug("networkinterface::onmessage:...!" + data.byteLength);
			let stream: MemoryStream = new MemoryStream(data);
			stream.wpos = data.byteLength;

			while(stream.rpos < stream.wpos)
			{
				let msgID = stream.ReadUint16();
				//Logger.Debug("networkinterface::onmessage:...!msgID:" + msgID);

				let handler: Message = Message.clientMassges[msgID];
				if(!handler)
				{
					Logger.Error("networkinterface::onmessage:message(%d) has not found.", msgID);
				}
				else
				{
					let msgLen = handler.length;
					if(msgLen === -1)
					{
						msgLen = stream.ReadUint16();
						if(msgLen === 65535)
						{
							msgLen = stream.ReadUint32();
						}
					}

					let wpos = stream.wpos;
					let rpos = stream.rpos + msgLen;
					stream.wpos = rpos;
					handler.HandleMessage(stream);
					stream.wpos = wpos;
					stream.rpos = rpos;
				}
			}
		}

		private onclose = () =>
		{
			Logger.Debug("networkinterface::onclose:...!");
			Event.Fire("onDisconnected");
		}
	}	
}
