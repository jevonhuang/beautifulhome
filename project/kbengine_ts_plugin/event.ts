module Kbe
{
	class EventInfo
	{
		m_object: object;
		m_cbFunction: Function;

		constructor(p_object: object, cbFunction: Function)
		{
			this.m_object = p_object;
			this.m_cbFunction = cbFunction;
		}
	}


	export class Event
	{
		private static _events: {} = {};

		static Register(eventName: string, p_object: object|null, cbFunction: Function): void
		{
			let eventList: Array<EventInfo> = this._events[eventName];  // 或者let eventList: EventInfo[] = [];
			if(eventList === undefined)
			{
				eventList = [];
				this._events[eventName] = eventList;
			}
			eventList.push(new EventInfo(p_object, cbFunction));
		}

		static Deregister(eventName: string, p_object: object|null, cbFunction: Function): void
		{
			let eventList: Array<EventInfo> = this._events[eventName];
			if(eventList === undefined)
			{
				Logger.Error("Event::Deregister:cant find event by name(%s).", eventName);
				return;
			}

			let hasFound: boolean = false;
			for (let item of eventList)
			{
				// 注意，严格模式下，arguments,call等被禁用，不可访问这些成员
				//Logger.Warning("Event::Deregister:let key of eventList.:" +item.m_cbFunction.toString());

				if(p_object === item.m_object && item.m_cbFunction === cbFunction)
				{
					let index: number = eventList.indexOf(item);
					eventList.splice(index, 1);
					Logger.Warning("Event::Deregister:item.m_cbFunction === cbFunction...delete index:%d", index);
					hasFound = true;
					break;
				}
			}
			if(!hasFound)
			{
				Logger.Error("Event::Deregister:cant find event by Function(event name:%s).", eventName);
			}
		}

		static Fire(eventName: string, ...params: any[]): void
		{
			let eventList: Array<EventInfo> = this._events[eventName];
			if(eventList === undefined)
			{
				Logger.Debug("Event::Fire:cant find event by name(%s).", eventName);
				return;
			}

			for(let item of eventList)
			{
				try
				{
					// 注意，传入参数和注册函数参数类型数量可以不一致，作为事件函数的参数类型检查没有作用
					item.m_cbFunction.apply(item.m_object, params);
				}
				catch(e)
				{
					Logger.Error("Event::Fire(%s):%s", eventName, e);
				}
			}
		}

		static DeregisterObject(p_object: object): void
		{
			if(p_object === null)
			{
				Logger.Error("Event::DeregisterObject:object cannot be null.");
				return;
			}

			let deleteCount: number = 0;
			for(let key in this._events)
			{
				let eventList: Array<EventInfo> = this._events[key];
				for(let item of eventList)
				{
					if(item.m_object === p_object)
					{
						let index: number = eventList.indexOf(item);
						eventList.splice(index, 1);
						deleteCount += 1;
					}
				}
			}

			Logger.Debug("KBEEvent::DeregisterObject %s:delete count:%d.", p_object.toString(), deleteCount);
		}
	}	
}
