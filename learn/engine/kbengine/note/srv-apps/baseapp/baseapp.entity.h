class Entity : public script::ScriptObject
{
	/** 当前脚本模块的类别
	*/		
	static PyTypeObject _scriptType;														
	typedef Entity ThisClass;																
																							
	static PyObject* _tp_repr(PyObject* self)												
	{																						
		return static_cast<Entity*>(self)->tp_repr();										
	}																						
																							
	static PyObject* _tp_str(PyObject* self)												
	{																						
		return static_cast<Entity*>(self)->tp_str();											
	}																						
																							
	/** 脚本模块对象从python中创建
	*/																						
	static PyObject* _tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)			
	{																						
		return Entity::tp_new(type, args, kwds);												
	}																						
																							
	/** python 请求获取本模块的属性或者方法
	*/																						
	static PyObject* _tp_getattro(PyObject* self, PyObject* name)							
	{																						
		return static_cast<Entity*>(self)->onScriptGetAttribute(name);						
	}																						
																							
	/** python 请求设置本模块的属性或者方法
	*/																						
	static int _tp_setattro(PyObject* self, PyObject* name, PyObject* value)				
	{																						
		return (value != NULL) ?															
				static_cast<Entity*>(self)->onScriptSetAttribute(name, value):				
				static_cast<Entity*>(self)->onScriptDelAttribute(name);						
	}																						
																							
	/** python 请求初始化本模块对象
	*/																						
	static int _tp_init(PyObject* self, PyObject *args, PyObject* kwds)						
	{																						
		return static_cast<Entity*>(self)->onScriptInit(self, args, kwds);					
	}																						
																							
public:																						
	/* 最终将要被安装到脚本模块中的方法和成员存放列表*/											
	static PyMethodDef* _Entity_lpScriptmethods;											
	static PyMemberDef* _Entity_lpScriptmembers;											
	static PyGetSetDef* _Entity_lpgetseters;												
	/* 本模块所要暴漏给脚本的方法和成员， 最终会被导入到上面的2个指针列表中 */					
	static PyMethodDef _Entity_scriptMethods[];											
	static PyMemberDef _Entity_scriptMembers[];											
	static PyGetSetDef _Entity_scriptGetSeters[];										
																							
	static bool _Entity_py_installed;													
																							
	/** getset的只读属性
	*/																						
	static int __py_readonly_descr(PyObject* self, PyObject* value, void* closure)			
	{																						
		PyErr_Format(PyExc_TypeError,														
		"Sorry, this attribute %s.%s is read-only", (self != NULL ? self->ob_type->tp_name
		: ”Entity“), (closure != NULL ? (char*)closure : "unknown"));							
		PyErr_PrintEx(0);																	
		return 0;																			
	}																						
																							
	/** getset的只写属性
	*/																						
	static int __py_writeonly_descr(PyObject* self, PyObject* value, void* closure)			
	{																						
		PyErr_Format(PyExc_TypeError,														
		"Sorry, this attribute %s.%s is write-only", (self != NULL ? self->ob_type->tp_name
		: "Entity"), (closure != NULL ? (char*)(closure) : "unknown"));						
		PyErr_PrintEx(0);																	
		return 0;																			
	}																						
																							
	/** 这个接口可以获得当前模块的脚本类别 
	*/																						
	static PyTypeObject* getScriptType(void)												
	{																						
		return &_scriptType;																
	}	
	
	static PyTypeObject* getBaseScriptType(void)											
	{																						
		if(strcmp("ScriptObject", "ScriptObject") == 0)										
			return 0;																		
		return ScriptObject::getScriptType();													
	}																						
																							
	static long calcDictOffset(void)														
	{																						
		if(strcmp("ScriptObject", "ScriptObject") == 0)										
			return 0;																		
		return 0;																			
	}																						
																							
	/** 计算所有继承模块的暴露方法个数 
	*/																						
	static int calcTotalMethodCount(void)													
	{																						
		int nlen = 0;																		
		while(true)																			
		{																					
			PyMethodDef* pmf = &_Entity_scriptMethods[nlen];								
			if(!pmf->ml_doc && !pmf->ml_flags && !pmf->ml_meth && !pmf->ml_name)			
				break;																		
			nlen++;																			
		}																					
																							
		if(strcmp("Entity", "ScriptObject") == 0)												
			return nlen;																	
		return ScriptObject::calcTotalMethodCount() + nlen;									
	}																						
																							
	/** 计算所有继承模块的暴露成员个数 
	*/																						
	static int calcTotalMemberCount(void)													
	{																						
		int nlen = 0;																		
		while(true)																			
		{																					
			PyMemberDef* pmd = &_Entity_scriptMembers[nlen];								
			if(!pmd->doc && !pmd->flags && !pmd->type && !pmd->name && !pmd->offset)		
				break;																		
			nlen++;																			
		}																					
																							
		if(strcmp("Entity", "ScriptObject") == 0)												
			return nlen;																	
		return ScriptObject::calcTotalMemberCount() + nlen;									
	}																						
																							
	/** 计算所有继承模块的暴露getset个数 
	*/																						
	static int calcTotalGetSetCount(void)													
	{																						
		int nlen = 0;																		
		while(true)																			
		{																					
			PyGetSetDef* pgs = &_Entity_scriptGetSeters[nlen];							
			if(!pgs->doc && !pgs->get && !pgs->set && !pgs->name && !pgs->closure)			
				break;																		
			nlen++;																			
		}																					
																							
		if(strcmp("Entity", "ScriptObject") == 0)												
			return nlen;																	
		return ScriptObject::calcTotalGetSetCount() + nlen;									
	}																						
																							
	/** 将所有父类以及当前模块的暴露成员和方法安装到最终要导入脚本的列表中 
	*/																						
	static void setupScriptMethodAndAttribute(PyMethodDef* lppmf, PyMemberDef* lppmd,		
	PyGetSetDef* lppgs)																		
	{																						
		int i = 0;																			
		PyMethodDef* pmf = NULL;															
		PyMemberDef* pmd = NULL;															
		PyGetSetDef* pgs = NULL;															
																							
		while(true){																		
			pmf = &_Entity_scriptMethods[i];												
			if(!pmf->ml_doc && !pmf->ml_flags && !pmf->ml_meth && !pmf->ml_name)			
				break;																		
			i++;																			
			*(lppmf++) = *pmf;																
		}																					
																							
		i = 0;																				
		while(true){																		
			pmd = &_Entity_scriptMembers[i];												
			if(!pmd->doc && !pmd->flags && !pmd->type && !pmd->name && !pmd->offset)		
				break;																		
			i++;																			
			*(lppmd++) = *pmd;																
		}																					
																							
		i = 0;																				
		while(true){																		
			pgs = &_Entity_scriptGetSeters[i];											
			if(!pgs->doc && !pgs->get && !pgs->set && !pgs->name && !pgs->closure)			
				break;																		
			i++;																			
			*(lppgs++) = *pgs;																
		}																					
																							
		if(strcmp("Entity", "ScriptObject") == 0){												
			*(lppmf) = *pmf;																
			*(lppmd) = *pmd;																
			*(lppgs) = *pgs;																
			return;																			
		}																					
																							
		ScriptObject::setupScriptMethodAndAttribute(lppmf, lppmd, lppgs);						
	}																						
																							
	/** 安装当前脚本模块 
		@param mod: 所要导入的主模块
	*/																						
	static void installScript(PyObject* mod, const char* name = ”Entity“)						
	{																						
		int nMethodCount			= Entity::calcTotalMethodCount();						
		int nMemberCount			= Entity::calcTotalMemberCount();						
		int nGetSetCount			= Entity::calcTotalGetSetCount();						
																							
		_Entity_lpScriptmethods	= new PyMethodDef[nMethodCount + 2];					
		_Entity_lpScriptmembers	= new PyMemberDef[nMemberCount + 2];					
		_Entity_lpgetseters		= new PyGetSetDef[nGetSetCount + 2];					
																							
		setupScriptMethodAndAttribute(_Entity_lpScriptmethods,							
									  _Entity_lpScriptmembers,							
									  _Entity_lpgetseters);								
																							
		_scriptType.tp_methods		= _Entity_lpScriptmethods;							
		_scriptType.tp_members		= _Entity_lpScriptmembers;							
		_scriptType.tp_getset		= _Entity_lpgetseters;								
																							
																							
		Entity::onInstallScript(mod);														
		if (PyType_Ready(&_scriptType) < 0){												
			ERROR_MSG("PyType_Ready("Entity") error!");									
			PyErr_Print();																	
			return;																			
		}																					
																							
		if(mod)																				
		{																					
			Py_INCREF(&_scriptType);														
			if(PyModule_AddObject(mod, name, (PyObject *)&_scriptType) < 0)					
			{																				
				ERROR_MSG(fmt::format("PyModule_AddObject({}) error!", name));				
			}																				
		}																					
																							
		SCRIPT_ERROR_CHECK();																
		_Entity_py_installed = true;														
																							
		ScriptObject::scriptObjectTypes[name] = &_scriptType;								
	}																						
																							
	/** 卸载当前脚本模块 
	*/																						
	static void uninstallScript(void)														
	{																						
		SAFE_RELEASE_ARRAY(_Entity_lpScriptmethods);										
		SAFE_RELEASE_ARRAY(_Entity_lpScriptmembers);										
		SAFE_RELEASE_ARRAY(_Entity_lpgetseters);											
		Entity::onUninstallScript();															
																							
		if(_Entity_py_installed)															
			Py_DECREF(&_scriptType);														
	}																						
	
	
	/** python创建的对象则对象从python中释放
	*/																						
	static void _tp_dealloc(PyObject* self)													
	{																						
		static_cast<Entity*>(self)->~Entity();												
		Entity::_scriptType.tp_free(self);													
	}																						
	
public:																										
	typedef KBEUnordered_map< std::string, std::vector<PyObjectPtr> > ENTITY_EVENTS;						
protected:																									
	ENTITY_ID													id_;										
	ScriptDefModule*											pScriptModule_;								
	const ScriptDefModule::PROPERTYDESCRIPTION_MAP*				pPropertyDescrs_;							
	SPACE_ID													spaceID_;									
	ScriptTimers												scriptTimers_;								
	PY_CALLBACKMGR												pyCallbackMgr_;								
	bool														isDestroyed_;								
	uint32														flags_;										
	ENTITY_EVENTS												events_;									
public:																										
																											
	bool initing() const{ return hasFlags(ENTITY_FLAGS_INITING); }											
																											
	void onInitializeScript()
	{
	}
	
	void initializeScript()																					
	{																										
		removeFlags(ENTITY_FLAGS_INITING);																	
		SCOPED_PROFILE(SCRIPTCALL_PROFILE);																	
																											
		const ScriptDefModule::COMPONENTDESCRIPTION_MAP* pComponentDescrs =									
			&pScriptModule_->getComponentDescrs();															
																											
		ScriptDefModule::COMPONENTDESCRIPTION_MAP::const_iterator iter1 = pComponentDescrs->begin();		
		for (; iter1 != pComponentDescrs->end(); ++iter1)													
		{																									
			PyObject* pComponentProperty = PyObject_GetAttrString(this, iter1->first.c_str());				
			if(pComponentProperty)																			
			{																								
				if(PyObject_TypeCheck(pComponentProperty, EntityComponent::getScriptType()))				
				{																							
					EntityComponent* pEntityComponent = static_cast<EntityComponent*>(pComponentProperty);	
					pEntityComponent->initializeScript();													
				}																							
				else																						
				{																							
					PyErr_Format(PyExc_AssertionError, "%s.%s is not property of EntityComponent!",			
						scriptName(), iter1->first.c_str());												
					PyErr_PrintEx(0);																		
				}																							
																											
				Py_DECREF(pComponentProperty);																
			}																								
			else																							
			{																								
				PyErr_Clear();																				
			}																								
		}																									
																											
		if(PyObject_HasAttrString(this, "__init__"))														
		{																									
			PyObject* pyResult = PyObject_CallMethod(this, const_cast<char*>("__init__"),					
											const_cast<char*>(""));											
			if(pyResult != NULL)																			
				Py_DECREF(pyResult);																		
			else																							
				SCRIPT_ERROR_CHECK();																		
		}																									
																											
		iter1 = pComponentDescrs->begin();																	
		for (; iter1 != pComponentDescrs->end(); ++iter1)													
		{																									
			PyObject* pComponentProperty = PyObject_GetAttrString(this, iter1->first.c_str());				
			if(pComponentProperty)																			
			{																								
				if(PyObject_TypeCheck(pComponentProperty, EntityComponent::getScriptType()))				
				{																							
					EntityComponent* pEntityComponent = static_cast<EntityComponent*>(pComponentProperty);	
					pEntityComponent->updateOwner(id(), this);												
					pEntityComponent->onAttached();															
				}																							
				else																						
				{																							
					PyErr_Format(PyExc_AssertionError, "%s.%s is not property of EntityComponent!",			
						scriptName(), iter1->first.c_str());												
					PyErr_PrintEx(0);																		
				}																							
																											
				Py_DECREF(pComponentProperty);																
			}																								
			else																							
			{																								
				PyErr_Clear();																				
			}																								
		}																									
																											
		onInitializeScript();																				
	}																										
																											
	void initializeEntity(PyObject* dictData, bool persistentData = false)									
	{																										
		createNamespace(dictData, persistentData);															
		initializeScript();																					
	}																										
																											
	bool _reload(bool fullReload)
	{
		return true;		
	}
	
	bool reload(bool fullReload)																			
	{																										
		if(fullReload)																						
		{																									
			pScriptModule_ = EntityDef::findScriptModule(scriptName());										
			KBE_ASSERT(pScriptModule_);																		
			pPropertyDescrs_ = &pScriptModule_->getPropertyDescrs();										
		}																									
																											
		if(PyObject_SetAttrString(this, "__class__", (PyObject*)pScriptModule_->getScriptType()) == -1)		
		{																									
			WARNING_MSG(fmt::format("Entity::reload: "														
				"{} {} could not change __class__ to new class!n",											
				pScriptModule_->getName(), id_));															
			PyErr_Print();																					
			return false;																					
		}																									
																											
		initProperty(true);																					
		return _reload(fullReload);																			
	}																										
																											
	void createNamespace(PyObject* dictData, bool persistentData = false)									
	{																										
		if(dictData == NULL)																				
			return;																							
																											
		if(!PyDict_Check(dictData)){																		
			ERROR_MSG(fmt::format("Entity::createNamespace: create Entity[{}:{}] "							
				"args is not a dict.n",																	
				scriptName(), id_));																		
			return;																							
		}																									
																											
		EntityDef::context().currComponentType = g_componentType;											
		EntityDef::context().currEntityID = id();															
																											
		Py_ssize_t pos = 0;																					
		PyObject *key, *value;																				
		PyObject* cellDataDict = PyObject_GetAttrString(this, "cellData");									
																											
		if(cellDataDict == NULL)																			
		{																									
			PyErr_Clear();																					
			EntityComponent::convertDictDataToEntityComponent(id(), this, pScriptModule_, dictData, persistentData); 
		}																									
																											
		while(PyDict_Next(dictData, &pos, &key, &value))													
		{																									
			DEBUG_CREATE_ENTITY_NAMESPACE																	
			if(PyObject_HasAttr(this, key) > 0)																
			{																								
				wchar_t* PyUnicode_AsWideCharStringRet0 = PyUnicode_AsWideCharString(key, NULL);			
				char* ccattr = strutil::wchar2char(PyUnicode_AsWideCharStringRet0);							
				PyMem_Free(PyUnicode_AsWideCharStringRet0);													
																											
				PropertyDescription* pCompPropertyDescription =												
					pScriptModule_->findComponentPropertyDescription(ccattr);								
																											
				if (pCompPropertyDescription)																
				{																							
					if(PyDict_Check(value) /* createDictDataFromPersistentStream 流程导致非字典 */)			
					{																						
						EntityComponent* pEntityComponent = (EntityComponent*)PyObject_GetAttr(this, key);	
						pEntityComponent->updateFromDict(this, value);										
						Py_DECREF(pEntityComponent);														
					}																						
					else																					
					{																						
						PyObject_SetAttr(this, key, value);													
					}																						
				}																							
				else																						
				{																							
					PyObject_SetAttr(this, key, value);														
				}																							
																											
				free(ccattr);																				
				continue;																					
			}																								
																											
			if(cellDataDict != NULL && PyDict_Contains(cellDataDict, key) > 0)								
			{																								
				PyObject* pyVal = PyDict_GetItem(cellDataDict, key);										
				if (PyDict_Check(pyVal))																	
				{																							
					if (0 != PyDict_Update(pyVal, value) /* EntityComponent required */)					
					{																						
						SCRIPT_ERROR_CHECK();																
						KBE_ASSERT(false);																	
					}																						
				}																							
				else																						
				{																							
					PyDict_SetItem(cellDataDict, key, value);												
				}																							
			}																								
			else																							
			{																								
				wchar_t* PyUnicode_AsWideCharStringRet0 = PyUnicode_AsWideCharString(key, NULL);			
				char* ccattr = strutil::wchar2char(PyUnicode_AsWideCharStringRet0);							
				PyMem_Free(PyUnicode_AsWideCharStringRet0);													
																											
				PropertyDescription* pCompPropertyDescription =												
					pScriptModule_->findComponentPropertyDescription(ccattr);								
																											
				free(ccattr);																				
																											
				if (pCompPropertyDescription)																
				{																							
					/* 一般在base上可能放在cellData中是字典，而没有cell的实体需要pass这个设置 */				
					if(PyDict_Check(value))																	
						continue;																			
				}																							
																											
				PyObject_SetAttr(this, key, value);															
			}																								
		}																									
																											
		SCRIPT_ERROR_CHECK();																				
																											
		Py_XDECREF(cellDataDict);																			
	}																										
																											
	void addCellDataToStream(COMPONENT_TYPE sendTo, uint32 flags, MemoryStream* mstream, bool useAliasID = false)				
	{
		addPositionAndDirectionToStream(*s, useAliasID);

		if (!cellDataDict_)
			return;

		if(sendTo != CLIENT_TYPE)
			EntityDef::context().currComponentType = CELLAPP_TYPE;
		else
			EntityDef::context().currComponentType = CLIENT_TYPE;

		ScriptDefModule::PROPERTYDESCRIPTION_MAP& propertyDescrs = pScriptModule_->getCellPropertyDescriptions();
		ScriptDefModule::PROPERTYDESCRIPTION_MAP::const_iterator iter = propertyDescrs.begin();

		for(; iter != propertyDescrs.end(); ++iter)
		{
			PropertyDescription* propertyDescription = iter->second;
			if(flags == 0 || (flags & propertyDescription->getFlags()) > 0)
			{
				PyObject* pyVal = PyDict_GetItemString(cellDataDict_, propertyDescription->getName());


				if (propertyDescription->getDataType()->type() == DATA_TYPE_ENTITY_COMPONENT)
				{
					// 由于存在一种情况， 组件def中没有内容， 但有cell脚本，此时baseapp上无法判断他是否有cell属性，所以写celldata时没有数据写入
					EntityComponentType* pEntityComponentType = (EntityComponentType*)propertyDescription->getDataType();
					if (pEntityComponentType->pScriptDefModule()->getCellPropertyDescriptions().size() == 0)
						continue;

					if (useAliasID && pScriptModule_->usePropertyDescrAlias())
					{
						(*s) << (uint8)0;
						(*s) << propertyDescription->aliasIDAsUint8();
					}
					else
					{
						(*s) << (ENTITY_PROPERTY_UID)0;
						(*s) << propertyDescription->getUType();
					}

					pEntityComponentType->addCellDataToStream(s, flags, pyVal, this->id(), propertyDescription, sendTo, true);
				}
				else
				{
					if (useAliasID && pScriptModule_->usePropertyDescrAlias())
					{
						(*s) << (uint8)0;
						(*s) << propertyDescription->aliasIDAsUint8();
					}
					else
					{
						(*s) << (ENTITY_PROPERTY_UID)0;
						(*s) << propertyDescription->getUType();
					}

					if (!propertyDescription->isSameType(pyVal))
					{
						ERROR_MSG(fmt::format("{}::addCellDataToStream: {}({}) not is ({})!n", this->scriptName(),
							propertyDescription->getName(), (pyVal ? pyVal->ob_type->tp_name : "unknown"), propertyDescription->getDataType()->getName()));

						PyObject* pydefval = propertyDescription->parseDefaultStr("");
						propertyDescription->addToStream(s, pydefval);
						Py_DECREF(pydefval);
					}
					else
					{
						propertyDescription->addToStream(s, pyVal);
					}
				}

				if (PyErr_Occurred())
				{	
					PyErr_PrintEx(0);
					DEBUG_MSG(fmt::format("{}::addCellDataToStream: {} error!n", this->scriptName(),
						propertyDescription->getName()));
				}
			}
		}
	}	
	
	PyObject* createCellDataFromStream(MemoryStream* mstream)												
	{																										
		EntityDef::context().currComponentType = CELLAPP_TYPE;												
		EntityDef::context().currEntityID = id();															
																											
		PyObject* cellData = PyDict_New();																	
		ENTITY_PROPERTY_UID uid;																			
		Vector3 pos, dir;																					
		STREAM_TO_POS_DIR(*mstream, pos, dir);																
		ADD_POSDIR_TO_PYDICT(cellData, pos, dir);															
																											
		ScriptDefModule::PROPERTYDESCRIPTION_UIDMAP& propertyDescrs =										
								pScriptModule_->getCellPropertyDescriptions_uidmap();						
																											
		size_t count = propertyDescrs.size();																
																											
		{																									
			ScriptDefModule::PROPERTYDESCRIPTION_UIDMAP::iterator iter = propertyDescrs.begin();			
			for(; iter != propertyDescrs.end(); ++iter)														
			{																								
				/* 由于存在一种情况， 组件def中没有内容， 但有cell脚本，此时baseapp上无法判断他是否有cell属性，所以写celldata时没有数据写入 */ 
				if (iter->second->getDataType()->type() == DATA_TYPE_ENTITY_COMPONENT)						
				{																							
					EntityComponentType* pEntityComponentType = (EntityComponentType*)iter->second->getDataType();	
					if (pEntityComponentType->pScriptDefModule()->getCellPropertyDescriptions().size() == 0)
					{																						
						--count;																			
						continue;																			
					}																						
				}																							
			}																								
		}																									
																											
		while(mstream->length() > 0 && count-- > 0)															
		{																									
			(*mstream) >> uid /* 父属性 */ >> uid;															
			ScriptDefModule::PROPERTYDESCRIPTION_UIDMAP::iterator iter = propertyDescrs.find(uid);			
			if(iter == propertyDescrs.end())																
			{																								
				ERROR_MSG(fmt::format("{}::createCellDataFromStream: not found uid({})! entityID={}n", scriptName(), uid, id()));	
				break;																						
			}																								
																											
			PyObject* pyobj = NULL;																			
			if (iter->second->getDataType()->type() == DATA_TYPE_ENTITY_COMPONENT)							
			{																								
				pyobj = ((EntityComponentType*)iter->second->getDataType())->createCellDataFromStream(mstream);
			}																								
			else																							
			{																								
				pyobj = iter->second->createFromStream(mstream);											
			}																								
																											
			if(pyobj == NULL)																				
			{																								
				SCRIPT_ERROR_CHECK();																		
				pyobj = iter->second->parseDefaultStr("");													
				PyDict_SetItemString(cellData, iter->second->getName(), pyobj);								
				Py_DECREF(pyobj);																			
			}																								
			else																							
			{																								
				PyDict_SetItemString(cellData, iter->second->getName(), pyobj);								
				Py_DECREF(pyobj);																			
			}																								
		}																									
																											
		return cellData;																					
	}																										
																											
	void addCellDataToStreamByDetailLevel(int8 detailLevel, MemoryStream* mstream, bool useAliasID = false)	
	{																										
		EntityDef::context().currComponentType = CELLAPP_TYPE;												
		EntityDef::context().currEntityID = id();															
																											
		PyObject* cellData = PyObject_GetAttrString(this, "__dict__");										
																											
		ScriptDefModule::PROPERTYDESCRIPTION_MAP& propertyDescrs =											
				pScriptModule_->getCellPropertyDescriptionsByDetailLevel(detailLevel);						
		ScriptDefModule::PROPERTYDESCRIPTION_MAP::const_iterator iter = propertyDescrs.begin();				
		for(; iter != propertyDescrs.end(); ++iter)															
		{																									
			PropertyDescription* propertyDescription = iter->second;										
			PyObject* pyVal = PyDict_GetItemString(cellData, propertyDescription->getName());				
																											
			if(useAliasID && pScriptModule_->usePropertyDescrAlias())										
			{																								
				(*mstream) << propertyDescription->aliasIDAsUint8();										
			}																								
			else																							
			{																								
				(*mstream) << propertyDescription->getUType();												
			}																								
																											
			propertyDescription->getDataType()->addToStream(mstream, pyVal);								
		}																									
																											
		Py_XDECREF(cellData);																				
		SCRIPT_ERROR_CHECK();																				
	}																										
																											
	void addClientDataToStream(MemoryStream* s, bool otherClient = false)									
	{																										
		EntityDef::context().currComponentType = CLIENT_TYPE;												
		EntityDef::context().currEntityID = id();															
																											
		PyObject* pydict = PyObject_GetAttrString(this, "__dict__");										
																											
		ScriptDefModule::PROPERTYDESCRIPTION_MAP& propertyDescrs =											
				pScriptModule()->getClientPropertyDescriptions();											
		ScriptDefModule::PROPERTYDESCRIPTION_MAP::iterator iter = propertyDescrs.begin();					
		for(; iter != propertyDescrs.end(); ++iter)															
		{																									
			PropertyDescription* propertyDescription = iter->second;										
			if(otherClient)																					
			{																								
				if((propertyDescription->getFlags() & ENTITY_BROADCAST_OTHER_CLIENT_FLAGS) <= 0)			
					continue;																				
			}																								
																											
			PyObject *key = PyUnicode_FromString(propertyDescription->getName());							
																											
			if(PyDict_Contains(pydict, key) > 0)															
			{																								
				if(pScriptModule()->usePropertyDescrAlias())												
				{																							
					(*s) << (uint8)0;																		
	    			(*s) << propertyDescription->aliasIDAsUint8();											
				}																							
				else																						
				{																							
					(*s) << (ENTITY_PROPERTY_UID)0;															
	    			(*s) << propertyDescription->getUType();												
				}																							
																											
	    		propertyDescription->getDataType()->addToStream(s, PyDict_GetItem(pydict, key));			
			}																								
																											
			Py_DECREF(key);																					
		}																									
																											
		Py_XDECREF(pydict);																					
	}																										
																											
	void addPositionAndDirectionToStream(MemoryStream& s, bool useAliasID = false);							
	{																										
		ENTITY_PROPERTY_UID posuid = ENTITY_BASE_PROPERTY_UTYPE_POSITION_XYZ;								
		ENTITY_PROPERTY_UID diruid = ENTITY_BASE_PROPERTY_UTYPE_DIRECTION_ROLL_PITCH_YAW;					
																											
		Network::FixedMessages::MSGInfo* msgInfo =															
					Network::FixedMessages::getSingleton().isFixed("Property::position");					
																											
		if(msgInfo != NULL)																					
		{																									
			posuid = msgInfo->msgid;																		
			msgInfo = NULL;																					
		}																									
																											
		msgInfo = Network::FixedMessages::getSingleton().isFixed("Property::direction");					
		if(msgInfo != NULL)																					
		{																									
			diruid = msgInfo->msgid;																		
			msgInfo = NULL;																					
		}																									
																											
		PyObject* pyPos = NULL;																				
		PyObject* pyDir = NULL;																				
																											
																											
		if(g_componentType == BASEAPP_TYPE)																	
		{																									
			PyObject* cellDataDict = PyObject_GetAttrString(this, "cellData");								
			if(cellDataDict == NULL)																		
			{																								
				PyErr_Clear();																				
				return;																						
			}																								
			else																							
			{																								
				pyPos = PyDict_GetItemString(cellDataDict, "position");										
				pyDir = PyDict_GetItemString(cellDataDict, "direction");									
			}																								
																											
			Py_XDECREF(cellDataDict);																		
			if(pyPos == NULL && pyDir == NULL)																
			{																								
				PyErr_Clear();																				
				return;																						
			}																								
		}																									
		else																								
		{																									
			pyPos = PyObject_GetAttrString(this, "position");												
			pyDir = PyObject_GetAttrString(this, "direction");												
		}																									
																											
																											
		Vector3 pos, dir;																					
		script::ScriptVector3::convertPyObjectToVector3(pos, pyPos);										
		script::ScriptVector3::convertPyObjectToVector3(dir, pyDir);										
																											
		if(pScriptModule()->usePropertyDescrAlias() && useAliasID)											
		{																									
			ADD_POS_DIR_TO_STREAM_ALIASID(s, pos, dir)														
		}																									
		else																								
		{																									
			ADD_POS_DIR_TO_STREAM(s, pos, dir)																
		}																									
																											
		if(g_componentType != BASEAPP_TYPE)																	
		{																									
			Py_XDECREF(pyPos);																				
			Py_XDECREF(pyDir);																				
		}																									
	}
	
	static PyObject* __py_reduce_ex__(PyObject* self, PyObject* protocol)									
	{																										
		Entity* entity = static_cast<Entity*>(self);															
		DEBUG_REDUCE_EX(entity);																			
		PyObject* args = PyTuple_New(2);																	
		PyObject* unpickleMethod = script::Pickler::getUnpickleFunc("EntityCall");							
		PyTuple_SET_ITEM(args, 0, unpickleMethod);															
		PyObject* args1 = PyTuple_New(4);																	
		PyTuple_SET_ITEM(args1, 0, PyLong_FromUnsignedLong(entity->id()));									
		PyTuple_SET_ITEM(args1, 1, PyLong_FromUnsignedLongLong(g_componentID));								
		PyTuple_SET_ITEM(args1, 2, PyLong_FromUnsignedLong(entity->pScriptModule()->getUType()));			
		if(g_componentType == BASEAPP_TYPE)																	
			PyTuple_SET_ITEM(args1, 3, PyLong_FromUnsignedLong(ENTITYCALL_TYPE_BASE));						
		else																								
			PyTuple_SET_ITEM(args1, 3, PyLong_FromUnsignedLong(ENTITYCALL_TYPE_CELL));						
		PyTuple_SET_ITEM(args, 1, args1);																	
																											
		if(unpickleMethod == NULL){																			
			Py_DECREF(args);																				
			return NULL;																					
		}																									
		SCRIPT_ERROR_CHECK();																				
		return args;																						
	}																										
																											
	inline ScriptTimers& scriptTimers()
	{ 
		return scriptTimers_; 
	}	
	
	void onTimer(ScriptID timerID, int useraAgs);															
	{
		SCOPED_PROFILE(ONTIMER_PROFILE);
		
		CALL_ENTITY_AND_COMPONENTS_METHOD(this, SCRIPT_OBJECT_CALL_ARGS2(pyTempObj, const_cast<char*>("onTimer"),
			const_cast<char*>("Ii"), timerID, useraAgs, GETERR));
	}	
	
	PY_CALLBACKMGR& callbackMgr()
	{ 
		return pyCallbackMgr_; 
	}													
																											
	static PyObject* __pyget_pyGetID(Entity *self, void *closure)											
	{																										
		return PyLong_FromLong(self->id());																	
	}																										
																											
	INLINE ENTITY_ID id() const																				
	{																										
		return id_;																							
	}																										
																											
	INLINE void id(ENTITY_ID v)																				
	{																										
		id_ = v; 																							
	}																										
																											
	INLINE bool hasFlags(uint32 v) const																	
	{																										
		return (flags_ & v) > 0;																			
	}																										
																											
	INLINE uint32 flags() const																				
	{																										
		return flags_;																						
	}																										
																											
	INLINE void flags(uint32 v)																				
	{																										
		flags_ = v; 																						
	}																										
																											
	INLINE uint32 addFlags(uint32 v)																		
	{																										
		flags_ |= v;																						
		return flags_;																						
	}																										
																											
	INLINE uint32 removeFlags(uint32 v)																		
	{																										
		flags_ &= ~v; 																						
		return flags_;																						
	}																										
																											
	INLINE SPACE_ID spaceID() const																			
	{																										
		return spaceID_;																					
	}																										
	INLINE void spaceID(SPACE_ID id)																		
	{																										
		spaceID_ = id;																						
	}																										
	static PyObject* __pyget_pyGetSpaceID(Entity *self, void *closure)										
	{																										
		return PyLong_FromLong(self->spaceID());															
	}																										
																											
	INLINE ScriptDefModule* pScriptModule(void) const														
	{																										
		return pScriptModule_; 																				
	}																										
																											
	int onScriptDelAttribute(PyObject* attr)																
	{																										
		char* ccattr = PyUnicode_AsUTF8AndSize(attr, NULL);													
		DEBUG_OP_ATTRIBUTE("del", attr)																		
																											
		if(pPropertyDescrs_)																				
		{																									
			ScriptDefModule::PROPERTYDESCRIPTION_MAP::const_iterator iter = pPropertyDescrs_->find(ccattr);	
			if(iter != pPropertyDescrs_->end())																
			{																								
				char err[255];																				
				kbe_snprintf(err, 255, "property[%s] defined in %s.def, del failed!", ccattr, scriptName());
				PyErr_SetString(PyExc_TypeError, err);														
				PyErr_PrintEx(0);																			
				return 0;																					
			}																								
		}																									
																											
		if(pScriptModule_->findMethodDescription(ccattr, g_componentType) != NULL)							
		{																									
			char err[255];																					
			kbe_snprintf(err, 255, "method[%s] defined in %s.def, del failed!", ccattr, scriptName());		
			PyErr_SetString(PyExc_TypeError, err);															
			PyErr_PrintEx(0);																				
			return 0;																						
		}																									
																											
		return ScriptObject::onScriptDelAttribute(attr);													
	}																										
																											
	int onScriptSetAttribute(PyObject* attr, PyObject* value)												
	{																										
		DEBUG_OP_ATTRIBUTE("set", attr)																		
		char* ccattr = PyUnicode_AsUTF8AndSize(attr, NULL);													
																											
		if(pPropertyDescrs_)																				
		{																									
			ScriptDefModule::PROPERTYDESCRIPTION_MAP::const_iterator iter = pPropertyDescrs_->find(ccattr);	
			if(iter != pPropertyDescrs_->end())																
			{																								
				PropertyDescription* propertyDescription = iter->second;									
				DataType* dataType = propertyDescription->getDataType();									
																											
				if(!hasFlags(ENTITY_FLAGS_DESTROYING) && isDestroyed_)										
				{																							
					PyErr_Format(PyExc_AssertionError, "can't set %s.%s to %s. entity is destroyed!",		
													scriptName(), ccattr, value->ob_type->tp_name);			
					PyErr_PrintEx(0);																		
					return 0;																				
				}																							
																											
				if(!dataType->isSameType(value))															
				{																							
					PyErr_Format(PyExc_ValueError, "can't set %s.%s to %s.",								
													scriptName(), ccattr, value->ob_type->tp_name);			
					PyErr_PrintEx(0);																		
					return 0;																				
				}																							
				else																						
				{																							
					Py_ssize_t ob_refcnt = value->ob_refcnt;												
					PyObject* pySetObj = propertyDescription->onSetValue(this, value);						
																											
					/* 如果def属性数据有改变， 那么可能需要广播 */												
					if(pySetObj != NULL)																	
					{																						
						onDefDataChanged(NULL, propertyDescription, pySetObj);								
						if(pySetObj == value && pySetObj->ob_refcnt - ob_refcnt > 1)						
							Py_DECREF(pySetObj);															
					}																						
																											
					return pySetObj == NULL ? -1 : 0;														
				}																							
			}																								
		}																									
																											
		return ScriptObject::onScriptSetAttribute(attr, value);												
	}																										
																											
	PyObject * onScriptGetAttribute(PyObject* attr)														
	{
		DEBUG_OP_ATTRIBUTE("get", attr)
			
		char* ccattr = PyUnicode_AsUTF8AndSize(attr, NULL);
		
		// 如果访问了def持久化类容器属性
		// 由于没有很好的监测容器类属性内部的变化，这里使用一个折中的办法进行标脏
		PropertyDescription* pPropertyDescription = const_cast<ScriptDefModule*>(pScriptModule())->findPersistentPropertyDescription(ccattr);
		if(pPropertyDescription && (pPropertyDescription->getFlags() & ENTITY_BASE_DATA_FLAGS) > 0)
		{
			setDirty();
		}
		else if (strcmp(ccattr, "cellData") == 0)
		{
			setDirty();
		}
		
		return ScriptObject::onScriptGetAttribute(attr);
	}
															
	PyObject* pyAddTimer(float interval, float repeat, int32 userArg)	
	{																										
		EntityScriptTimerHandler* pHandler = new EntityScriptTimerHandler(this);							
		ScriptTimers * pTimers = &scriptTimers_;															
		int id = ScriptTimersUtil::addTimer(&pTimers,														
				interval, repeat,																			
				userArg, pHandler);																			
																											
		if (id == 0)																						
		{																									
			PyErr_SetString(PyExc_ValueError, "Unable to add timer");										
			PyErr_PrintEx(0);																				
			delete pHandler;																				
																											
			return NULL;																					
		}																									
																											
		return PyLong_FromLong(id);																			
	}	
	
	static PyObject* __py_pyAddTimer(PyObject* self, PyObject* args, PyObject* kwds)												
	{																																
		float arg1;																						
		float arg2;																						
		int32 arg3;																						
																																	
		const uint8 argsSize = 3;																									
		uint16 currargsSize = (uint16)PyTuple_Size(args);																			
		ThisClass* pobj = static_cast<ThisClass*>(self);																			
																																	
		if(currargsSize == argsSize)																								
		{																															
			if(!PyArg_ParseTuple(args, "f|f|i", &arg1, &arg2, &arg3))																		
			{																														
				PyErr_Format(PyExc_TypeError, "%s: args(%s, %s, %s) error!\n", __FUNCTION__, "float", "float", "int32");	
				PyErr_PrintEx(0);																									
				S_Return;																											
			}																														
		}																															
		else																														
		{																															
			PyErr_Format(PyExc_AssertionError, "%s: args require %d args(%s, %s, %s), gived %d! is script[%s].\n",					
				__FUNCTION__, argsSize, "float", "float", "int32", currargsSize, pobj->scriptName());						
																																	
			PyErr_PrintEx(0);																																																											
			S_Return;																												
		}																															
																																	
		return pobj->pyAddTimer(arg1, arg2, arg3);																					
	}																																
															
	PyObject* pyDelTimer(PY_METHOD_ARG_ScriptID)
	{																										
		if(!ScriptTimersUtil::delTimer(&scriptTimers_, timerID))											
		{																									
			return PyLong_FromLong(-1);																		
		}																									
																											
		return PyLong_FromLong(timerID);																	
	}	
	
	static PyObject* __py_pyDelTimer(PyObject* self, PyObject* args, PyObject* kwds)												
	{																																
		PY_METHOD_ARG_ScriptID arg1;																								
																																	
		const uint8 argsSize = 1;																									
		uint16 currargsSize = (uint16)PyTuple_Size(args);																			
		ThisClass* pobj = static_cast<ThisClass*>(self);																			
																																	
		if(currargsSize == argsSize)																								
		{																															
			if(!PyArg_ParseTuple(args, PY_METHOD_ARG_ScriptID_PYARGTYPE, &arg1))																						
			{																														
				PyErr_Format(PyExc_TypeError, "%s: args(%s) error!n", __FUNCTION__, "ScriptID");									
				PyErr_PrintEx(0);																									
				S_Return;																											
			}																														
		}																															
		else																														
		{																															
			PyErr_Format(PyExc_AssertionError, "%s: args require %d args(%s), gived %d! is script[%s].\n",							
				__FUNCTION__, argsSize, "ScriptID", currargsSize, pobj->scriptName());												
																																	
			PyErr_PrintEx(0);																										
																																	
			S_Return;																												
		}																															
																																	
		return pobj->pyDelTimer(arg1);																								
	}				

				
	static PyObject* __py_pyWriteToDB(PyObject* self, PyObject* args)										
	{																										
		uint16 currargsSize = (uint16)PyTuple_Size(args);													
		Entity* pobj = static_cast<Entity*>(self);															
																											
		if((g_componentType == CELLAPP_TYPE && currargsSize > 2) ||											
			(g_componentType == BASEAPP_TYPE && currargsSize > 3))											
		{																									
			PyErr_Format(PyExc_AssertionError,																
							"%s::writeToDB: args max require %d args, gived %d!n",							
				pobj->scriptName(), 1, currargsSize);														
																											
			PyErr_PrintEx(0);																				
			S_Return;																						
		}																									
																											
		int extra = 0;																						
		std::string strextra;																				
		PyObject* pycallback = NULL;																		
																											
		if(g_componentType == CELLAPP_TYPE)																	
		{																									
			PyObject* baseMB = PyObject_GetAttrString(self, "base");										
			if(baseMB == NULL || baseMB == Py_None)															
			{																								
				PyErr_Clear();																				
				PyErr_SetString(PyExc_AssertionError,														
				"This method can only be called on a real entity that has a base entity. ");				
				PyErr_PrintEx(0);																			
			}																								
		}																									
		else if(g_componentType == BASEAPP_TYPE)															
		{																									
			extra = -1;	/* shouldAutoLoad -1默认不改变设置 */												
		}																									
																											
		if(currargsSize == 1)																				
		{																									
			if(g_componentType == BASEAPP_TYPE)																
			{																								
				if(PyArg_ParseTuple(args, "O", &pycallback) == -1)											
				{																							
					PyErr_Format(PyExc_AssertionError, "%s::writeToDB: args error!", pobj->scriptName());	
					PyErr_PrintEx(0);																		
					pycallback = NULL;																		
					S_Return;																				
				}																							
																											
				if(!PyCallable_Check(pycallback))															
				{																							
					if(pycallback != Py_None)																
					{																						
						PyErr_Format(PyExc_TypeError, "%s::writeToDB: args1 not is callback!", pobj->scriptName());
						PyErr_PrintEx(0);																	
						S_Return;																			
					}																						
					else																					
					{																						
						pycallback = NULL;																	
					}																						
				}																							
			}																								
			else																							
			{																								
				if(PyArg_ParseTuple(args, "i", &extra) == -1)												
				{																							
					PyErr_Format(PyExc_AssertionError, "%s::writeToDB: args error!", pobj->scriptName());	
					PyErr_PrintEx(0);																		
					pycallback = NULL;																		
					S_Return;																				
				}																							
			}																								
		}																									
		else if(currargsSize == 2)																			
		{																									
			if(g_componentType == BASEAPP_TYPE)																
			{																								
				if(PyArg_ParseTuple(args, "O|i", &pycallback, &extra) == -1)								
				{																							
					PyErr_Format(PyExc_AssertionError, "%s::writeToDB: args error!", pobj->scriptName());	
					PyErr_PrintEx(0);																		
					pycallback = NULL;																		
					S_Return;																				
				}																							
																											
				if(!PyCallable_Check(pycallback))															
				{																							
					if(pycallback != Py_None)																
					{																						
						PyErr_Format(PyExc_TypeError, "%s::writeToDB: args1 not is callback!", pobj->scriptName());	
						PyErr_PrintEx(0);																	
						S_Return;																			
					}																						
					else																					
					{																						
						pycallback = NULL;																	
					}																						
				}																							
			}																								
			else																							
			{																								
				PyObject* pystr_extra = NULL;																
				if(PyArg_ParseTuple(args, "i|O", &extra, &pystr_extra) == -1)								
				{																							
					PyErr_Format(PyExc_AssertionError, "%s::writeToDB: args error!", pobj->scriptName());	
					PyErr_PrintEx(0);																		
					pycallback = NULL;																		
					S_Return;																				
				}																							
																											
				if(pystr_extra)																				
				{																							
					wchar_t* PyUnicode_AsWideCharStringRet0 = PyUnicode_AsWideCharString(pystr_extra, NULL);
					char* ccattr = strutil::wchar2char(PyUnicode_AsWideCharStringRet0);						
					strextra = ccattr;																		
					PyMem_Free(PyUnicode_AsWideCharStringRet0);												
					free(ccattr);																			
				}																							
																											
				if(!g_kbeSrvConfig.dbInterface(strextra))													
				{																							
					PyErr_Format(PyExc_TypeError, "%s::writeToDB: args2, "									
													"incorrect dbInterfaceName(%s)!",						
													pobj->scriptName(), strextra.c_str());					
					PyErr_PrintEx(0);																		
					S_Return;																				
				}																							
			}																								
		}																									
		else if(currargsSize == 3)																			
		{																									
			if(g_componentType == BASEAPP_TYPE)																
			{																								
				PyObject* pystr_extra = NULL;																
				if(PyArg_ParseTuple(args, "O|i|O", &pycallback, &extra, &pystr_extra) == -1)				
				{																							
					PyErr_Format(PyExc_AssertionError, "%s::writeToDB: args error!", pobj->scriptName());	
					PyErr_PrintEx(0);																		
					pycallback = NULL;																		
					S_Return;																				
				}																							
																											
				if(!PyCallable_Check(pycallback))															
				{																							
					if(pycallback != Py_None)																
					{																						
						PyErr_Format(PyExc_TypeError, "%s::writeToDB: args1 not is callback!", pobj->scriptName());	
						PyErr_PrintEx(0);																	
						S_Return;																			
					}																						
					else																					
					{																						
						pycallback = NULL;																	
					}																						
				}																							
																											
				if(pystr_extra)																				
				{																							
					wchar_t* PyUnicode_AsWideCharStringRet0 = PyUnicode_AsWideCharString(pystr_extra, NULL);
					char* ccattr = strutil::wchar2char(PyUnicode_AsWideCharStringRet0);						
					strextra = ccattr;																		
					PyMem_Free(PyUnicode_AsWideCharStringRet0);												
					free(ccattr);																			
				}																							
																											
				if(!g_kbeSrvConfig.dbInterface(strextra))													
				{																							
					PyErr_Format(PyExc_TypeError, "%s::writeToDB: args3, "									
										"incorrect dbInterfaceName(%s)!",									
											pobj->scriptName(), strextra.c_str());							
					PyErr_PrintEx(0);																		
					S_Return;																				
				}																							
			}																								
			else																							
			{																								
				KBE_ASSERT(false);																			
			}																								
		}																									
																											
		pobj->writeToDB(pycallback, (void*)&extra, (void*)strextra.c_str());								
		S_Return;																							
	}																										
																											
	void writeToDB(void* data, void* extra1, void* extra2)												
	{
		PyObject* pyCallback = NULL;
		int8 shouldAutoLoad = dbid() <= 0 ? 0 : -1;

		// data 是有可能会NULL的， 比如定时存档是不需要回调函数的
		if(data != NULL)
			pyCallback = static_cast<PyObject*>(data);

		if(extra1 != NULL && (*static_cast<int*>(extra1)) != -1)
			shouldAutoLoad = (*static_cast<int*>(extra1)) > 0 ? 1 : 0;

		if (extra2)
		{
			if (strlen(static_cast<char*>(extra2)) > 0)
			{
				DBInterfaceInfo* pDBInterfaceInfo = g_kbeSrvConfig.dbInterface(static_cast<char*>(extra2));
				if (pDBInterfaceInfo->isPure)
				{
					ERROR_MSG(fmt::format("Entity::writeToDB: dbInterface({}) is a pure database does not support Entity! "
						"kbengine[_defs].xml->dbmgr->databaseInterfaces->*->pure\n",
						static_cast<char*>(extra2)));

					return;
				}

				int dbInterfaceIndex = pDBInterfaceInfo->index;
				if (dbInterfaceIndex >= 0)
				{
					dbInterfaceIndex_ = dbInterfaceIndex;
				}
				else
				{
					ERROR_MSG(fmt::format("Entity::writeToDB: not found dbInterface({})!\n",
						static_cast<char*>(extra2)));

					return;
				}
			}
		}

		if(isArchiveing_)
		{
			// __py_pyWriteToDB没有增加引用
			//if(pyCallback != NULL)
			//	Py_DECREF(pyCallback);

			WARNING_MSG(fmt::format("{}::writeToDB(): is archiveing! entityid={}, dbid={}.\n", 
				this->scriptName(), this->id(), this->dbid()));

			return;
		}

		isArchiveing_ = true;

		if(isDestroyed())
		{	
			// __py_pyWriteToDB没有增加引用
			//if(pyCallback != NULL)
			//	Py_DECREF(pyCallback);

			ERROR_MSG(fmt::format("{}::writeToDB(): is destroyed! entityid={}, dbid={}.\n", 
				this->scriptName(), this->id(), this->dbid()));

			return;
		}

		CALLBACK_ID callbackID = 0;
		if(pyCallback != NULL)
		{
			callbackID = callbackMgr().save(pyCallback);
		}

		// creatingCell_ 此时可能正在创建cell
		// 不过我们在此假设在cell未创建完成的时候base这个接口被调用
		// 写入数据库的是该entity的初始值， 并不影响
		if(this->cellEntityCall() == NULL) 
		{
			onCellWriteToDBCompleted(callbackID, shouldAutoLoad, -1);
		}
		else
		{
			Network::Bundle* pBundle = Network::Bundle::createPoolObject(OBJECTPOOL_POINT);
			(*pBundle).newMessage(CellappInterface::reqWriteToDBFromBaseapp);
			(*pBundle) << this->id();
			(*pBundle) << callbackID;
			(*pBundle) << shouldAutoLoad;
			sendToCellapp(pBundle);
		}
	}																											
	void destroy(bool callScript = true)																	
	{																										
		if(hasFlags(ENTITY_FLAGS_DESTROYING))																
			return;																							
																											
		if(!isDestroyed_)																					
		{																									
			isDestroyed_ = true;																			
			addFlags(ENTITY_FLAGS_DESTROYING);																
			EntityComponent::onEntityDestroy(this, pScriptModule_, callScript, true);						
			onDestroy(callScript);																			
			scriptTimers_.cancelAll();																		
			removeFlags(ENTITY_FLAGS_DESTROYING);															
			EntityComponent::onEntityDestroy(this, pScriptModule_, callScript, false);						
			events_.clear();																				
			Py_DECREF(this);																				
		}																									
	}																										
	INLINE bool isDestroyed() const																			
	{																										
		return isDestroyed_;																				
	}																										
	DECLARE_PY_GET_MOTHOD(pyGetIsDestroyed);																
																											
	void destroyEntity();																					
	static PyObject* __py_pyDestroyEntity(PyObject* self, PyObject* args, PyObject * kwargs);				
																											
	DECLARE_PY_GET_MOTHOD(pyGetClassName);																	
																											
	void initProperty(bool isReload = false);																
																											
	static PyObject* __py_pyGetDatachangeEventPtr(PyObject* self, PyObject* args)							
	{																										
		Entity* pobj = static_cast<Entity*>(self);															
		static EntityComponent::OnDataChangedEvent dataChangedEvent;										
			dataChangedEvent = std::tr1::bind(&Entity::onDefDataChanged, pobj,								
			std::tr1::placeholders::_1, std::tr1::placeholders::_2, std::tr1::placeholders::_3);			
		return PyLong_FromVoidPtr((void*)&dataChangedEvent);												
	}																										
																											
	ENTITY_EVENTS& events() { return events_; }																
																											
	bool registerEvent(const std::string& evnName, PyObject* pyCallback)									
	{																										
		ENTITY_DESTROYED_CHECK(return false, "registerEvent", this);										
																											
		if (!PyCallable_Check(pyCallback))																	
		{																									
			PyErr_Format(PyExc_TypeError, "{}::registerEvent: '%.200s' object is not callable! eventName=%s, entityID={}",
				scriptName(), (pyCallback ? pyCallback->ob_type->tp_name : "NULL"), evnName.c_str(), id());		
			PyErr_PrintEx(0);																				
			return false;																					
		}																									
																											
		std::vector<PyObjectPtr>& evnVecs = events_[evnName];												
		std::vector<PyObjectPtr>::iterator iter = evnVecs.begin();											
		for(; iter != evnVecs.end(); ++iter)																
		{																									
			if((*iter).get() == pyCallback)																	
			{																								
				PyErr_Format(PyExc_TypeError, "{}::registerEvent: This callable('%.200s') has been registered! eventName=%s, entityID={}",
					scriptName(), (pyCallback ? pyCallback->ob_type->tp_name : "NULL"), evnName.c_str(), id());	
				PyErr_PrintEx(0);																			
				return false;																				
			}																								
		}																									
																											
		events_[evnName].push_back(pyCallback);																
        return true;                                                                                        
	}																										
																											
	void fireEvent(const std::string& evnName, PyObject* pyArgs = NULL)										
	{																										
		ENTITY_DESTROYED_CHECK(return, "fireEvent", this);													
																											
		std::vector<PyObjectPtr>& evnVecs = events_[evnName];												
		std::vector<PyObjectPtr>::iterator iter = evnVecs.begin();											
		for(; iter != evnVecs.end(); ++iter)																
		{																									
			PyObject* pyResult = NULL;																		
			if (pyArgs == NULL)																				
			{																								
				pyResult = PyObject_CallObject((*iter).get(), NULL);										
			}																								
			else																							
			{																								
				pyResult = PyObject_CallObject((*iter).get(), pyArgs);										
			}																								
																											
			if(pyResult == NULL)																			
			{																								
				SCRIPT_ERROR_CHECK();																		
			}																								
			else																							
			{																								
				Py_DECREF(pyResult);																		
			}																								
		}																									
	}																										
																											
	bool deregisterEvent(const std::string& evnName, PyObject* pyCallback)									
	{																										
		std::vector<PyObjectPtr>& evnVecs = events_[evnName];												
		std::vector<PyObjectPtr>::iterator iter = evnVecs.begin();											
		for(; iter != evnVecs.end(); ++iter)																
		{																									
			if((*iter).get() == pyCallback)																	
			{																								
				evnVecs.erase(iter);																		
				return true;																				
			}																								
		}																									
																											
		return false;																						
	}																										
																											
    static PyObject* __py_pyRegisterEvent(PyObject* self, PyObject* args)									
	{																										
		uint16 currargsSize = (uint16)PyTuple_Size(args);													
		Entity* pobj = static_cast<Entity*>(self);															
																											
		if(currargsSize != 2)																				
		{																									
			PyErr_Format(PyExc_AssertionError,																
							"%s::registerEvent: args require %d args, gived %d!n",							
							pobj->scriptName(), 1, currargsSize);											
																											
			PyErr_PrintEx(0);																				
			Py_RETURN_FALSE;																				
		}																									
																											
		const char* eventName = NULL;																		
		PyObject* pycallback = NULL;																		
		if(PyArg_ParseTuple(args, "sO", &eventName, &pycallback) == -1)										
		{																									
			PyErr_Format(PyExc_AssertionError, "%s::registerEvent:: args error!", pobj->scriptName());		
			PyErr_PrintEx(0);																				
			pycallback = NULL;																				
			Py_RETURN_FALSE;																				
		}																									
																											
		if(!eventName)																						
		{																									
			PyErr_Format(PyExc_AssertionError, "%s::registerEvent:: eventName error!", pobj->scriptName());	
			PyErr_PrintEx(0);																				
			pycallback = NULL;																				
			Py_RETURN_FALSE;																				
		}																									
																											
		return PyBool_FromLong(pobj->registerEvent(eventName, pycallback));									
	}																										
																											
    static PyObject* __py_pyDeregisterEvent(PyObject* self, PyObject* args)									
	{																										
		uint16 currargsSize = (uint16)PyTuple_Size(args);													
		Entity* pobj = static_cast<Entity*>(self);															
																											
		if(currargsSize != 2)																				
		{																									
			PyErr_Format(PyExc_AssertionError,																
							"%s::deregisterEvent: args require %d args, gived %d!n",						
							pobj->scriptName(), 1, currargsSize);											
																											
			PyErr_PrintEx(0);																				
			Py_RETURN_FALSE;																				
		}																									
																											
		const char* eventName = NULL;																		
		PyObject* pycallback = NULL;																		
		if(PyArg_ParseTuple(args, "sO", &eventName, &pycallback) == -1)										
		{																									
			PyErr_Format(PyExc_AssertionError, "%s::deregisterEvent:: args error!", pobj->scriptName());	
			PyErr_PrintEx(0);																				
			pycallback = NULL;																				
			Py_RETURN_FALSE;																				
		}																									
																											
		if(!eventName)																						
		{																									
			PyErr_Format(PyExc_AssertionError, "%s::deregisterEvent:: eventName error!", pobj->scriptName());
			PyErr_PrintEx(0);																				
			pycallback = NULL;																				
			Py_RETURN_FALSE;																				
		}																									
																											
		return PyBool_FromLong(pobj->deregisterEvent(eventName, pycallback));								
	}																										
																											
    static PyObject* __py_pyFireEvent(PyObject* self, PyObject* args)										
	{																										
		uint16 currargsSize = (uint16)PyTuple_Size(args);													
		Entity* pobj = static_cast<Entity*>(self);															
																											
		if(currargsSize == 0)																				
		{																									
			PyErr_Format(PyExc_AssertionError,																
							"%s::fireEvent: args require %d args, gived %d!n",								
							pobj->scriptName(), 1, currargsSize);											
																											
			PyErr_PrintEx(0);																				
			Py_RETURN_FALSE;																				
		}																									
																											
		char* eventName = NULL;																				
		if(currargsSize == 1)																				
		{																									
			if(PyArg_ParseTuple(args, "s", &eventName) == -1)												
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::fireEvent:: args error! entityID={}", pobj->scriptName(), pobj->id());		
				PyErr_PrintEx(0);																			
				Py_RETURN_FALSE;																			
			}																								
																											
			if(!eventName)																					
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::fireEvent:: eventName error!", pobj->scriptName());	
				PyErr_PrintEx(0);																			
				Py_RETURN_FALSE;																			
			}																								
																											
			pobj->fireEvent(eventName);																		
		}																									
		else if(currargsSize == 2)																			
		{																									
			PyObject* pyobj = NULL;																			
			if (PyArg_ParseTuple(args, "sO", &eventName, &pyobj) == -1)										
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::fireEvent:: args error! entityID={}", pobj->scriptName(), pobj->id());		
				PyErr_PrintEx(0);																			
				Py_RETURN_FALSE;																			
			}																								
																											
			if(!eventName)																					
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::fireEvent:: eventName error!", pobj->scriptName());	
				PyErr_PrintEx(0);																			
				Py_RETURN_FALSE;																			
			}																								
																											
			PyObject* pyargs = PyTuple_New(1);																
			Py_INCREF(pyobj);																				
			PyTuple_SET_ITEM(pyargs, 0, pyobj);																
			pobj->fireEvent(eventName, pyargs);																
			Py_DECREF(pyargs);																				
		}																									
		else																								
		{																									
			PyObject* pyEvnName = PyTuple_GET_ITEM(args, 0);												
																											
			if(!PyUnicode_Check(pyEvnName))																	
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::fireEvent:: eventName error!", pobj->scriptName());	
				PyErr_PrintEx(0);																			
				Py_RETURN_FALSE;																			
			}																								
																											
			wchar_t* PyUnicode_AsWideCharStringRet0 = PyUnicode_AsWideCharString(pyEvnName, NULL);			
			eventName = strutil::wchar2char(PyUnicode_AsWideCharStringRet0);								
			PyMem_Free(PyUnicode_AsWideCharStringRet0);														
																											
			PyObject* pyargs = PyTuple_GetSlice(args, 1, currargsSize);										
			pobj->fireEvent(eventName, pyargs);																
			Py_DECREF(pyargs);																				
			free(eventName);																				
		}																									
																											
		Py_RETURN_TRUE;																						
	}																										
																											
	PyObject* pyGetComponent(const std::string& componentName, bool all)									
	{																										
		std::vector<EntityComponent*> founds =																
			EntityComponent::getComponents(componentName, this, pScriptModule_);							
																											
		if (!all)																							
		{																									
			if(founds.size() > 0)																			
				return founds[0];																			
																											
			Py_RETURN_NONE;																					
		}																									
		else																								
		{																									
			PyObject* pyObj = PyTuple_New(founds.size());													
																											
			for (int i = 0; i < (int)founds.size(); ++i)													
			{																								
				PyTuple_SetItem(pyObj, i, founds[i]);														
			}																								
																											
			return pyObj;																					
		}																									
																											
        return NULL;																						
	}																										
																											
    static PyObject* __py_pyGetComponent(PyObject* self, PyObject* args)									
	{																										
		uint16 currargsSize = (uint16)PyTuple_Size(args);													
		Entity* pobj = static_cast<Entity*>(self);															
																											
		if(currargsSize == 0 || currargsSize > 2)															
		{																									
			PyErr_Format(PyExc_AssertionError,																
							"%s::getComponent: args require 1-2 args, gived %d!n",							
							pobj->scriptName(), currargsSize);												
																											
			PyErr_PrintEx(0);																				
			Py_RETURN_NONE;																					
		}																									
																											
		char* componentName = NULL;																			
		if(currargsSize == 1)																				
		{																									
			if(PyArg_ParseTuple(args, "s", &componentName) == -1)											
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::getComponent:: args error!", pobj->scriptName());	
				PyErr_PrintEx(0);																			
				Py_RETURN_NONE;																				
			}																								
																											
			if(!componentName)																				
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::getComponent:: componentName error!", pobj->scriptName());
				PyErr_PrintEx(0);																			
				Py_RETURN_NONE;																				
			}																								
																											
			return pobj->pyGetComponent(componentName, false);												
		}																									
		else if(currargsSize == 2)																			
		{																									
			PyObject* pyobj = NULL;																			
			if (PyArg_ParseTuple(args, "sO", &componentName, &pyobj) == -1)									
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::getComponent:: args error!", pobj->scriptName());	
				PyErr_PrintEx(0);																			
				Py_RETURN_NONE;																				
			}																								
																											
			if(!componentName)																				
			{																								
				PyErr_Format(PyExc_AssertionError, "%s::getComponent:: componentName error!", pobj->scriptName());
				PyErr_PrintEx(0);																			
				Py_RETURN_NONE;																				
			}																								
																											
			return pobj->pyGetComponent(componentName, (pyobj == Py_True));									
		}																									
																											
		Py_RETURN_NONE;																						
	}																										

public:
	Entity(ENTITY_ID id, const ScriptDefModule* pScriptModule,
		PyTypeObject* pyType = getScriptType(), bool isInitialised = true);
	~Entity();

	/** 
		是否存储数据库 
	*/
	INLINE bool hasDB() const;
	INLINE void hasDB(bool has);

	/** 
		数据库关联ID
	*/
	INLINE DBID dbid() const;
	INLINE void dbid(uint16 dbInterfaceIndex, DBID id);

	PyObject* pyGetDBID()
	{
		if (!hasFlags(ENTITY_FLAGS_DESTROYING) && isDestroyed())
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d is destroyed!\n",		
				scriptName(), id());		
			PyErr_PrintEx(0);
			return 0;																					
		}

		return PyLong_FromUnsignedLongLong(this->dbid()); 
	}
	
	static PyObject* __pyget_pyGetDBID(PyObject *self, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pyGetDBID();								
	}
	
	/**
	数据库关联名称
	*/
	INLINE uint16 dbInterfaceIndex() const
	{
		return dbInterfaceIndex_;
	}
	
	PyObject* pyGetDBInterfaceName()
	{
		if (!hasFlags(ENTITY_FLAGS_DESTROYING) && isDestroyed())
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d is destroyed!\n",
				scriptName(), id());
			PyErr_PrintEx(0);
			return 0;
		}

		if (dbid() == 0)
			return PyUnicode_FromString("");

		return PyUnicode_FromString(g_kbeSrvConfig.dbInterfaceIndex2dbInterfaceName(dbInterfaceIndex()));
	}
	
	static PyObject* __pyget_pyGetDBInterfaceName(PyObject *self, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pyGetDBInterfaceName();								
	}	

	/** 
		销毁cell部分的实体 
	*/
	bool destroyCellEntity(void)
	{
		if(isDestroyed())	
		{
			return false;																					
		}

		if(cellEntityCall_  == NULL || cellEntityCall_->getChannel() == NULL)
		{
			isArchiveing_ = false;
			return false;
		}

		Network::Bundle* pBundle = Network::Bundle::createPoolObject(OBJECTPOOL_POINT);
		(*pBundle).newMessage(CellappInterface::onDestroyCellEntityFromBaseapp);
		(*pBundle) << id_;
		sendToCellapp(pBundle);
		return true;
	}
	
	PyObject* pyDestroyCellEntity(void)
	{
		if(cellEntityCall_ == NULL) 
		{
			PyErr_Format(PyExc_AssertionError, "%s::destroyCellEntity: id:%i no cell! creatingCell=%s\n", 
				this->scriptName(), this->id(),
				creatingCell_ ? "true" : "false");
			PyErr_PrintEx(0);
			return 0;
		}
		else
			destroyCellEntity();

		S_Return;
	}
	
	static PyObject* __py_pyDestroyCellEntity(PyObject* self, PyObject* args, PyObject* kwds)												
	{																																
		return static_cast<ThisClass*>(self)->pyDestroyCellEntity();																			
	}		
	/** 
		脚本获取entityCall 
	*/
	PyObject* pyGetCellEntityCall()		
	{
		PyObject* pEntity = owner();

		if (!pEntity)
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d is destroyed!\n",
				scriptName(), ownerID_);
			PyErr_PrintEx(0);
			return 0;
		}

		PyObject* entityCall = PyObject_GetAttrString(pEntity, "cell");
		if (!entityCall || entityCall == Py_None)
		{
			PyErr_Format(PyExc_AttributeError, "'%s: %d' object has no attribute 'cell'\n",
				pEntity->ob_type->tp_name, ownerID_);

			return NULL;
		}

		PyObject* pyObj = PyObject_GetAttrString(entityCall, pPropertyDescription_->getName());
		Py_DECREF(entityCall);
		return pyObj;
	}	
	static PyObject* __pyget_pyGetCellEntityCall(PyObject *self, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pyGetCellEntityCall();								
	}	
	
	EntityCall* cellEntityCall(void) const;

	void cellEntityCall(EntityCall* entityCall);
	
	/** 
		脚本获取entityCall 
	*/
	PyObject* pyGetClientEntityCall()
	{
		PyObject* pEntity = owner();

		if (!pEntity)
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d is destroyed!\n",
				scriptName(), ownerID_);
			PyErr_PrintEx(0);
			return 0;
		}

		PyObject* entityCall = PyObject_GetAttrString(pEntity, "client");
		if (!entityCall || entityCall == Py_None)
		{
			PyErr_Format(PyExc_AttributeError, "'%s: %d' object has no attribute 'client'\n",
				pEntity->ob_type->tp_name, ownerID_);

			return NULL;
		}

		PyObject* pyObj = PyObject_GetAttrString(entityCall, pPropertyDescription_->getName());
		Py_DECREF(entityCall);
		return pyObj;
	}
	
	static PyObject* __pyget_pyGetClientEntityCall(PyObject *self, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pyGetClientEntityCall();								
	}	
	
	EntityCall* clientEntityCall() const;

	void clientEntityCall(EntityCall* entityCall);

	/**
		是否创建过space
	*/
	INLINE bool isCreatedSpace();

	/** 
		cellData部分 
	*/
	bool installCellDataAttr(PyObject* dictData = NULL, bool installpy = true);

	void createCellData(void);

	void destroyCellData(void);

	void addPersistentsDataToStream(uint32 flags, MemoryStream* s);

	PyObject* createCellDataDict(uint32 flags);

	INLINE PyObject* getCellData(void) const;
	
	INLINE bool creatingCell(void) const;

	/**
		请求cell部分将entity的celldata更新一份过来
	*/
	void reqBackupCellData();
	
	/** 
		写备份信息到流
	*/
	void writeBackupData(MemoryStream* s);
	void onBackup();

	/** 
		写存档信息到流
	*/
	void writeArchiveData(MemoryStream* s);

	/** 
		将要保存到数据库之前的通知 
	*/
	void onWriteToDB();
	void onCellWriteToDBCompleted(CALLBACK_ID callbackID, int8 shouldAutoLoad, int dbInterfaceIndex);
	void onWriteToDBCallback(ENTITY_ID eid, DBID entityDBID, uint16 dbInterfaceIndex,
		CALLBACK_ID callbackID, int8 shouldAutoLoad, bool success);

	/** 网络接口
		entity第一次写数据库由dbmgr返回的dbid
	*/
	void onGetDBID(Network::Channel* pChannel, DBID dbid);

	/** 
		创建cell失败回调 
	*/
	void onCreateCellFailure(void);

	/** 
		创建cell成功回调 
	*/
	void onGetCell(Network::Channel* pChannel, COMPONENT_ID componentID);

	/** 
		丢失cell了的通知 
	*/
	void onLoseCell(Network::Channel* pChannel, MemoryStream& s);

	/** 
		当cellapp意外终止后， baseapp如果能找到合适的cellapp则将其恢复后
		会调用此方法
	*/
	void onRestore();

	/** 
		备份cell数据
	*/
	void onBackupCellData(Network::Channel* pChannel, MemoryStream& s);

	/** 
		客户端丢失 
	*/
	void onClientDeath();

	/** 网络接口
		远程呼叫本entity的方法 
	*/
	void onRemoteMethodCall(Network::Channel* pChannel, MemoryStream& s);

	/** 
		销毁这个entity 
	*/
	void onDestroy(bool callScript);

	/**
		销毁base内部通知
	*/
	void onDestroyEntity(bool deleteFromDB, bool writeToDB);

	/** 
		为一个baseEntity在指定的cell上创建一个cellEntity 
	*/
	PyObject* createCellEntity(PyObject *)
	{
		if(isDestroyed())
		{
			PyErr_Format(PyExc_AssertionError, "%s::createCellEntity: %d is destroyed!\n",
				scriptName(), id());
			PyErr_PrintEx(0);
			return 0;
		}

		if(Baseapp::getSingleton().findEntity(id()) == NULL)
		{
			PyErr_Format(PyExc_AssertionError, "%s::createCellEntity: %d not found!\n", 
				scriptName(), id());

			PyErr_PrintEx(0);
			return 0;
		}

		if(creatingCell_ || this->cellEntityCall())
		{
			PyErr_Format(PyExc_AssertionError, "%s::createCellEntity: %d has a cell!\n", 
				scriptName(), id());

			PyErr_PrintEx(0);
			return 0;
		}

		if(!PyObject_TypeCheck(pyobj, EntityCall::getScriptType()))
		{
			PyErr_Format(PyExc_TypeError, "create %s arg1 is not cellEntityCall!", 
				this->scriptName());

			PyErr_PrintEx(0);
			return 0;
		}
		
		EntityCallAbstract* cellEntityCall = static_cast<EntityCallAbstract*>(pyobj);
		if(cellEntityCall->type() != ENTITYCALL_TYPE_CELL)
		{
			PyErr_Format(PyExc_TypeError, "create %s args1 not is a direct cellEntityCall!", 
				this->scriptName());

			PyErr_PrintEx(0);
			return 0;
		}
		
		creatingCell_ = true;
		Baseapp::getSingleton().createCellEntity(cellEntityCall, this);
		S_Return;
	}
	
	static PyObject* __py_createCellEntity(PyObject* self, PyObject* args, PyObject* kwds)												
	{																																
		PyObject * arg1;																								
																																	
		const uint8 argsSize = 1;																									
		uint16 currargsSize = (uint16)PyTuple_Size(args);																			
		ThisClass* pobj = static_cast<ThisClass*>(self);																			
																																	
		if(currargsSize == argsSize)																								
		{																															
			if(!PyArg_ParseTuple(args, "0", &arg1))																						
			{																														
				PyErr_Format(PyExc_TypeError, "%s: args(%s) error!\n", __FUNCTION__, #ARG_TYPE1);									
				PyErr_PrintEx(0);																									
				S_Return;																											
			}																														
		}																															
		else																														
		{																															
			PyErr_Format(PyExc_AssertionError, "%s: args require %d args(%s), gived %d! is script[%s].\n",							
				__FUNCTION__, argsSize, "PyObject_ptr", currargsSize, pobj->scriptName());												
																																	
			PyErr_PrintEx(0);																																																										
			S_Return;																												
		}																															
																																	
		return pobj->createCellEntity(arg1);																								
	}																																
																																	
	
	/** 
		为一个baseEntity在指定的cell上还原一个cellEntity 
	*/
	void restoreCell(EntityCallAbstract* cellEntityCall);
	INLINE bool inRestore();

	/** 
		创建一个cellEntity在一个新的space上 
	*/
	PyObject* createCellEntityInNewSpace(PyObject*)
	{
		if(isDestroyed())
		{
			PyErr_Format(PyExc_AssertionError, "%s::createCellEntityInNewSpace: %d is destroyed!\n",
				scriptName(), id());
			PyErr_PrintEx(0);
			return 0;
		}	

		if(createdSpace_ || this->cellEntityCall() != NULL)
		{
			PyErr_Format(PyExc_AssertionError, "%s::createCellEntityInNewSpace: %d in space!\n", 
				scriptName(), id());

			PyErr_PrintEx(0);
			return 0;
		}

		createdSpace_ = true;
		Baseapp::getSingleton().createCellEntityInNewSpace(this, args);
		S_Return;
	}	
	static PyObject* __py_createCellEntityInNewSpace(PyObject* self, PyObject* args, PyObject* kwds)												
	{																																
		PyObject* arg1;																								
																																	
		const uint8 argsSize = 1;																									
		uint16 currargsSize = (uint16)PyTuple_Size(args);																			
		ThisClass* pobj = static_cast<ThisClass*>(self);																			
																																	
		if(currargsSize == argsSize)																								
		{																															
			if(!PyArg_ParseTuple(args, "0", &arg1))																						
			{																														
				PyErr_Format(PyExc_TypeError, "%s: args(%s) error!\n", __FUNCTION__, "PyObject*");									
				PyErr_PrintEx(0);																									
				S_Return;																											
			}																														
		}																															
		else																														
		{																															
			PyErr_Format(PyExc_AssertionError, "%s: args require %d args(%s), gived %d! is script[%s].\n",							
				__FUNCTION__, argsSize, "PyObject*", currargsSize, pobj->scriptName());												
																																	
			PyErr_PrintEx(0);																																																										
			S_Return;																												
		}																															
																																	
		return pobj->createCellEntityInNewSpace(arg1);																								
	}
	
	/** 网络接口
		客户端直接发送消息给cell实体
	*/
	void forwardEntityMessageToCellappFromClient(Network::Channel* pChannel, MemoryStream& s);
	
	/**
		发送消息到cellapp上
	*/
	void sendToCellapp(Network::Bundle* pBundle);
	void sendToCellapp(Network::Channel* pChannel, Network::Bundle* pBundle);

	/** 
		传送
	*/																				
	PyObject* pyTeleport(PyObject*)
	{
		if(isDestroyed())
		{
			PyErr_Format(PyExc_AssertionError, "%s::teleport: %d is destroyed!\n",
				scriptName(), id());
			PyErr_PrintEx(0);
			return 0;
		}	

		if(this->cellEntityCall() == NULL)
		{
			PyErr_Format(PyExc_AssertionError, "%s::teleport: %d no has cell!\n", 
				scriptName(), id());

			PyErr_PrintEx(0);
			return 0;
		}

		if(baseEntityMB == NULL)
		{
			PyErr_Format(PyExc_Exception, "%s::teleport: %d baseEntityMB is NULL!\n", 
				scriptName(), id());

			PyErr_PrintEx(0);
			return 0;
		}

		bool isEntityCall = PyObject_TypeCheck(baseEntityMB, EntityCall::getScriptType());
		bool isEntity = !isEntityCall && (PyObject_TypeCheck(baseEntityMB, Entity::getScriptType())
			|| PyObject_TypeCheck(baseEntityMB, Proxy::getScriptType()));

		if(!isEntityCall && !isEntity)
		{
			PyErr_Format(PyExc_AssertionError, "%s::teleport: %d invalid baseEntityMB!\n", 
				scriptName(), id());

			PyErr_PrintEx(0);
			return 0;
		}

		ENTITY_ID eid = 0;

		// 如果不是entityCall则是本地base
		if(isEntityCall)
		{
			EntityCall* mb = static_cast<EntityCall*>(baseEntityMB);

			if(mb->type() != ENTITYCALL_TYPE_BASE && mb->type() != ENTITYCALL_TYPE_CELL_VIA_BASE)
			{
				PyErr_Format(PyExc_AssertionError, "%s::teleport: %d baseEntityMB is not baseEntityCall!\n", 
					scriptName(), id());

				PyErr_PrintEx(0);
				return 0;
			}

			eid = mb->id();

			Network::Bundle* pBundle = Network::Bundle::createPoolObject(OBJECTPOOL_POINT);
			(*pBundle).newMessage(BaseappInterface::reqTeleportOther);
			(*pBundle) << eid;

			BaseappInterface::reqTeleportOtherArgs3::staticAddToBundle((*pBundle), this->id(), 
				this->cellEntityCall()->componentID(), g_componentID);

			mb->sendCall(pBundle);
		}
		else
		{
			Entity* pEntity = static_cast<Entity*>(baseEntityMB);
			if(!pEntity->isDestroyed())
			{
				pEntity->reqTeleportOther(NULL, this->id(), 
					this->cellEntityCall()->componentID(), g_componentID);
			}
			else
			{
				PyErr_Format(PyExc_AssertionError, "%s::teleport: %d baseEntity is destroyed!\n", 
					scriptName(), id());

				PyErr_PrintEx(0);
				return 0;
			}
		}

		S_Return;
	}	
	
	static PyObject* __py_pyTeleport(PyObject* self, PyObject* args, PyObject* kwds)												
	{																																
		PyObject* arg1;																								
																																	
		const uint8 argsSize = 1;																									
		uint16 currargsSize = (uint16)PyTuple_Size(args);																			
		ThisClass* pobj = static_cast<ThisClass*>(self);																			
																																	
		if(currargsSize == argsSize)																								
		{																															
			if(!PyArg_ParseTuple(args, "0", &arg1))																						
			{																														
				PyErr_Format(PyExc_TypeError, "%s: args(%s) error!\n", __FUNCTION__, "PyObject*");									
				PyErr_PrintEx(0);																									
				S_Return;																											
			}																														
		}																															
		else																														
		{																															
			PyErr_Format(PyExc_AssertionError, "%s: args require %d args(%s), gived %d! is script[%s].\n",							
				__FUNCTION__, argsSize, "PyObject*", currargsSize, pobj->scriptName());												
																																	
			PyErr_PrintEx(0);																																																											
			S_Return;																												
		}																															
																																	
		return pobj->pyTeleport(arg1);																								
	}																																

	
	/**
		传送回调
	*/
	void onTeleportCB(Network::Channel* pChannel, SPACE_ID spaceID, bool fromCellTeleport);  
	void onTeleportFailure();  
	void onTeleportSuccess(SPACE_ID spaceID);

	/** 网络接口
		某个entity请求teleport到这个entity的space上。
	*/
	void reqTeleportOther(Network::Channel* pChannel, ENTITY_ID reqTeleportEntityID, 
		COMPONENT_ID reqTeleportEntityCellAppID, COMPONENT_ID reqTeleportEntityBaseAppID);

	/** 网络接口
		entity请求迁移到另一个cellapp上的过程开始和结束。
	*/
	void onMigrationCellappStart(Network::Channel* pChannel, COMPONENT_ID sourceCellAppID, COMPONENT_ID targetCellAppID);
	void onMigrationCellappEnd(Network::Channel* pChannel, COMPONENT_ID sourceCellAppID, COMPONENT_ID targetCellAppID);
	void onMigrationCellappOver(COMPONENT_ID targetCellAppID);
	
	/**
		设置获取是否自动存档
	*/
	INLINE int8 shouldAutoArchive() const;
	INLINE void shouldAutoArchive(int8 v);
	
	PyObject* pyGetShouldAutoArchive()
	{
		return PyLong_FromLong(shouldAutoArchive_);
	}	
	static PyObject* __pyget_pyGetShouldAutoArchive(PyObject *self, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pyGetShouldAutoArchive();								
	}	
	
	int pySetShouldAutoArchive(PyObject *value)	
	{
		if(isDestroyed())	
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d is destroyed!\n",		
				scriptName(), id());		
			PyErr_PrintEx(0);
			return 0;																				
		}

		if(!PyLong_Check(value))
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d set shouldAutoBackup value is not int!\n",		
				scriptName(), id());		
			PyErr_PrintEx(0);
			return 0;	
		}

		shouldAutoBackup_ = (int8)PyLong_AsLong(value);
		return 0;
	}	
	static int __pyset_pySetShouldAutoArchive(PyObject *self, PyObject *value, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pySetShouldAutoArchive(value);							
	}	
	
	/**
		设置获取是否自动备份
	*/
	INLINE int8 shouldAutoBackup() const;
	INLINE void shouldAutoBackup(int8 v);

	PyObject* pyGetShouldAutoBackup()
	{
		return PyLong_FromLong(shouldAutoArchive_);
	}	
	static PyObject* __pyget_pyGetShouldAutoArchive(PyObject *self, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pyGetShouldAutoBackup();								
	}
	
	int pySetShouldAutoArchive(PyObject *value)	
	{
		if(isDestroyed())	
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d is destroyed!\n",		
				scriptName(), id());		
			PyErr_PrintEx(0);
			return 0;																				
		}

		if(!PyLong_Check(value))
		{
			PyErr_Format(PyExc_AssertionError, "%s: %d set shouldAutoArchive value is not int!\n",		
				scriptName(), id());		
			PyErr_PrintEx(0);
			return 0;	
		}

		shouldAutoArchive_ = (int8)PyLong_AsLong(value);
		return 0;
	}	
	static int __pyset_pySetShouldAutoBackup(PyObject *self, PyObject *value, void *closure)					
	{																				
		return static_cast<ThisClass*>(self)->pySetShouldAutoBackup(value);							
	}
	
	/**
		cellapp宕了
	*/
	void onCellAppDeath();

	/** 
		转发消息完成 
	*/
	void onBufferedForwardToCellappMessagesOver();
	void onBufferedForwardToClientMessagesOver();
	
	INLINE BaseMessagesForwardClientHandler* pBufferedSendToClientMessages();
	
	/** 
		设置实体持久化数据是否已脏，脏了会自动存档 
	*/
	INLINE void setDirty(bool dirty = true);
	INLINE bool isDirty() const;
	
protected:
	/** 
		定义属性数据被改变了 
	*/
	void onDefDataChanged(EntityComponent* pEntityComponent, const PropertyDescription* propertyDescription, PyObject* pyData);

	/**
		从db擦除在线log
	*/
	void eraseEntityLog();

protected:
	// 这个entity的客户端entityCall cellapp entityCall
	EntityCall*								clientEntityCall_;
	EntityCall*								cellEntityCall_;

	// entity创建后，在cell部分未创建时，将一些cell属性数据保存在这里
	PyObject*								cellDataDict_;

	// 是否是存储到数据库中的entity
	bool									hasDB_;
	DBID									DBID_;

	// 是否正在获取celldata中
	bool									isGetingCellData_;

	// 是否正在存档中
	bool									isArchiveing_;

	// 是否进行自动存档 <= 0为false, 1为true, KBE_NEXT_ONLY为执行一次后自动为false
	int8									shouldAutoArchive_;
	
	// 是否进行自动备份 <= 0为false, 1为true, KBE_NEXT_ONLY为执行一次后自动为false
	int8									shouldAutoBackup_;

	// 是否正在创建cell中
	bool									creatingCell_;

	// 是否已经创建了一个space
	bool									createdSpace_;

	// 是否正在恢复
	bool									inRestore_;
	
	// 如果此时实体还没有被设置为ENTITY_FLAGS_TELEPORT_START,  说明onMigrationCellappArrived包优先于
	// onMigrationCellappStart到达(某些压力所致的情况下会导致实体跨进程跳转时（由cell1跳转到cell2），
	// 跳转前所产生的包会比cell2的enterSpace包慢到达)，因此发生这种情况时需要将cell2的包先缓存
	// 等cell1的包到达后执行完毕再执行cell2的包
	BaseMessagesForwardClientHandler*		pBufferedSendToClientMessages_;
	
	// 需要持久化的数据是否变脏，如果没有变脏不需要持久化
	bool									isDirty_;

	// 如果这个实体已经写到数据库，那么这个属性就是对应的数据库接口的索引
	uint16									dbInterfaceIndex_;
};
