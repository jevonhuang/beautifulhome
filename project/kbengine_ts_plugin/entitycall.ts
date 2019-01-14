module Kbe
{
	export abstract class EntityCall
	{
		protected networkInterface: NetworkInterface;
		bundle:Bundle;
		id:number = 0;

		constructor(networkInterface: NetworkInterface)
		{
			this.networkInterface = networkInterface;
		}

		SendCall(bundle?: Bundle)
		{
			Logger.Assert(this.bundle !== undefined);

			if(bundle === undefined)
				bundle = this.bundle;
			bundle.Send(this.networkInterface);
			
			if(bundle === this.bundle)
				this.bundle = undefined;
		}

		protected abstract BuildBundle();

		NewCall()
		{
			if(this.bundle === undefined)
				this.bundle = new Bundle();
				
			this.BuildBundle();

			this.bundle.WriteUint32(this.id);
		}
	}

	export class CellEntityCall extends EntityCall
	{
		BuildBundle()
		{
			Logger.Assert(this.bundle !== undefined);
			this.bundle.NewMessage(Message.messages["Baseapp_onRemoteCallCellMethodFromClient"])
		}
	}

	export class BaseEntityCall extends EntityCall
	{
		BuildBundle()
		{
			Logger.Assert(this.bundle !== undefined);
			this.bundle.NewMessage(Message.messages["Entity_onRemoteMethodCall"])
		}
	}
	
}
