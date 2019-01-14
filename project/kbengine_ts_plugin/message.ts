module Kbe
{
	export class Message
	{
		static messages = {};
		static clientMassges = {};

		id: number;
		name: string;
		length: number;
		argsType: number;
		args: Array<DATATYPE_BASE> = new Array<DATATYPE_BASE>();
		handler: Function = undefined;

		static BindFixedMessage()
		{
			Message.messages["Loginapp_importClientMessages"] = new Message(5, "importClientMessages", 0, 0, new Array(), null);
			Message.messages["Baseapp_importClientMessages"] = new Message(207, "importClientMessages", 0, 0, new Array(), null);

			Message.messages["Client_onImportClientMessages"] = new Message(518, "Client_onImportClientMessages", -1, -1, new Array(), App.app.Client_onImportClientMessages);
			Message.clientMassges[Message.messages["Client_onImportClientMessages"].id] = Message.messages["Client_onImportClientMessages"];
		}

		constructor(id: number, name: string, length: number, argstype: number, args: Array<number>, handler: Function)
		{
			this.id = id;
			this.name = name;
			this.length = length;
			this.argsType = argstype;

			for(let argType of args)
			{
				this.args.push(idToDatatype[argType]);
			}

			this.handler = handler;
		}

		private CreateFromStream(stream: MemoryStream)
		{
			if(this.args.length <= 0)
				return stream;

			let result = [];
			for(let item of this.args)
			{
				result.push(item.CreateFromStream(stream));
			}

			return result;
		}

		HandleMessage(stream: MemoryStream): void
		{
			Logger.Debug("Message::handleMessage:name(%s), this.args.length(%d), this.argsType(%d).", this.name, this.args.length, this.argsType);

			if(this.handler === undefined)
			{
				Logger.Error("Message::handleMessage: interface(" + this.name + "/" + this.id + ") no implement!");
				return;
			}

			if(this.args.length === 0)
			{
				if(this.argsType < 0)
				{
					this.handler.call(App.app, stream);
				}
				else
				{
					this.handler.call(App.app);
				}
			}
			else
			{
				this.handler.apply(App.app, this.CreateFromStream(stream));
			}
		}
	}	
}

