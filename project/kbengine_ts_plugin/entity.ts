module Kbe
{
	export class Entity 
	{
		id: number;
		className: string;

		position: Vector3 = new Vector3(0, 0, 0);
		direction: Vector3 = new Vector3(0, 0, 0);
		entityLastLocalPos = new Vector3(0.0, 0.0, 0.0);
		entityLastLocalDir = new Vector3(0.0, 0.0, 0.0);

		inWorld: boolean = false;
		inited: boolean = false;
		isControlled: boolean = false;
		isOnGround: boolean = false;

		cell: EntityCall;
		base: EntityCall;

		__init__()
		{
		}

		CallPropertysSetMethods()
		{
			let module: ScriptModule = MODULE_DEFS[this.className];

			for(let name in module.propertys)
			{
				let property: Property = module.propertys[name];
				let setmethod = module.GetScriptSetMethod(name);

				if(setmethod !== undefined)
				{
					if(property.IsBase())
					{
						if(this.inited && !this.inWorld)
						{
							let oldval = this[name];
							setmethod.call(this, oldval)
						}
					}
					else
					{
						if(this.inWorld)
						{
							if(property.IsOwnerOnly() || !this.IsPlayer())
								continue;

							let oldval = this[name];
							setmethod.call(this, oldval)
						}
					}
				}
			}
		}

		GetPropertyValue(name: string)
		{
			let value = this[name];
			if(value == undefined)
			{		
				if (this.inited)		
					Logger.Warning("Entity::GetPropertyValue: property(%s) not found(undefined).", name);
			}

			return value;
		}

		SetPropertyValue(name: string, value: any)
		{
			this[name] = value;
		}

		OnDestroy()
		{
		}

		OnControlled(isControlled: boolean)
		{
			Logger.Debug("Entity::OnControlled:entity(%id) controlled state(%s) change.", this.id, isControlled);
		}

		IsPlayer(): boolean
		{
			return App.app.entity_id === this.id;
		}

		BaseCall(methodName: string, ...args: any[])
		{
			if(this.base === undefined)
			{
				Logger.Error("Entity::BaseCall: entity(%d) base is undefined.", this.id);
			}

			let method: Method = MODULE_DEFS[this.className].baseMethods[methodName];
			if(method === undefined)
			{
				Logger.Error("Entity::BaseCall: entity(%d) method(%s) not found.", this.id, methodName);
			}

			if(args.length !== method.args.length)
			{
				Logger.Error("Entity::BaseCall: args(%d != %d) size is error!", args.length, method.args.length);  
				return;
			}

			this.base.NewCall();
			//this.base.bundle.WriteUint16(0);
			this.base.bundle.WriteUint16(method.methodUtype);

			try
			{
				for(let i = 0; i < args.length; i++)
				{
					if(method.args[i].IsSameType(args[i]))
					{
						method.args[i].AddToStream(this.base.bundle, args[i])
					}
					else
					{
						throw(new Error("Entity::baseCall: arg[" + i + "] is error!"));
					}
				}
			}
			catch(e)
			{
				Logger.Error(e.toString());
				Logger.Error("Entity::baseCall: args is error!");
				this.base.bundle = undefined;
			}

			this.base.SendCall();
		}

		CellCall(methodName: string, ...args: any[])
		{
			if(this.cell === undefined)
			{
				Logger.Error("Entity::CellCall: entity(%d) cell is undefined.", this.id);
			}

			let method: Method = MODULE_DEFS[this.className].cellMethods[methodName];
			if(method === undefined)
			{
				Logger.Error("Entity::CellCall: entity(%d) method(%s) not found.", this.id, methodName);
			}

			if(args.length !== method.args.length)
			{
				Logger.Error("Entity::CellCall: args(%d != %d) size is error!", args.length, method.args.length);  
				return;
			}

			this.cell.NewCall();
			this.cell.bundle.WriteUint16(0);
			this.cell.bundle.WriteUint16(method.methodUtype);

			try
			{
				for(let i = 0; i < args.length; i++)
				{
					if(method.args[i].IsSameType(args[i]))
					{
						method.args[i].AddToStream(this.cell.bundle, args[i])
					}
					else
					{
						throw(new Error("Entity::baseCall: arg[" + i + "] is error!"));
					}
				}
			}
			catch(e)
			{
				Logger.Error(e.tostring());
				Logger.Error("Entity::baseCall: args is error!");
				this.cell.bundle = undefined;
			}

			this.cell.SendCall();
		}

		EnterWorld()
		{
			this.OnEnterWorld();
		}

		OnEnterWorld()
		{
			Logger.Debug("Entity::OnEnterWorld------------------->>>id:%s.", this.id);
		}

		LeaveWorld()
		{
			this.OnLeaveWorld();
		}

		OnLeaveWorld()
		{
			Logger.Debug("Entity::OnLeaveWorld------------------->>>id:%s.", this.id);
		}

		EnterSpace()
		{
			this.OnEnterSpace();
		}

		OnEnterSpace()
		{
			Logger.Debug("Entity::OnEnterSpace------------------->>>id:%s.", this.id);
		}

		LeaveSpace()
		{
			this.OnLeaveSpace();
		}

		OnLeaveSpace()
		{
			Logger.Debug("Entity::OnLeaveSpace------------------->>>id:%s.", this.id);
		}

		OnUpdateVolatileData()
		{
			Logger.Warning("Entity::OnUpdateVolatileData------------------->>>id:%s.y:%s", this.id, this.position.y);
		}

		set_position(oldVal: Vector3)
		{
			if(this.IsPlayer())
			{
				App.app.entityServerPos.x = this.position.x;
				App.app.entityServerPos.y = this.position.y;
				App.app.entityServerPos.z = this.position.z;
			}

			if(this.inWorld)
			   Event.Fire("set_position", this);
		}

		set_direction(oldVal: Vector3)
		{
			if(this.inWorld)
			   Event.Fire("set_direction", this);
		}

		SetPositionFromServer(postion: Vector3)
		{
		}

		SetDirectionFromServer(direction: Vector3)
		{
		}

		Destroy()
		{
			this.OnDestroy();
		}
	}	
}


