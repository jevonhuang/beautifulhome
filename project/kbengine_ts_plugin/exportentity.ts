module Kbe
{
	var EntityScripts = {};
	export function RegisterScript(scriptName: string, script: any)
	{
		EntityScripts[scriptName] = script;
	}

	export function GetEntityScript(name: string)
	{
		let script =  EntityScripts[name];
		if(script === undefined)
		{
			Logger.Error("ExportEntity::GetEntityScript(%s) is undefined.", name);
		}

		return script;
	}	
	
	export function RegisterInterface(accepter:any, giver:any)
	{
		for (let key in giver)
			if (!accepter[key])
				accepter[key] = giver[key]
	}
}


