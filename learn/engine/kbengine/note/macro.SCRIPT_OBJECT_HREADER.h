//SCRIPT_OBJECT_HREADER(ScriptObject, ScriptObject) ==> #define SCRIPT_HREADER_BASE(CLASS, SUPERCLASS)												

/* 当前脚本模块的类别 */																
static PyTypeObject _scriptType;														
typedef ScriptObject ThisClass;																
																						
static PyObject* _tp_repr(PyObject* self)												
{																						
	return static_cast<ScriptObject*>(self)->tp_repr();										
}																						
																						
static PyObject* _tp_str(PyObject* self)												
{																						
	return static_cast<ScriptObject*>(self)->tp_str();											
}																						
																						
/** 脚本模块对象从python中创建
*/																						
static PyObject* _tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)			
{																						
	return ScriptObject::tp_new(type, args, kwds);												
}																						
																						
/** python 请求获取本模块的属性或者方法
*/																						
static PyObject* _tp_getattro(PyObject* self, PyObject* name)							
{																						
	return static_cast<ScriptObject*>(self)->onScriptGetAttribute(name);						
}																						
																						
/** python 请求设置本模块的属性或者方法
*/																						
static int _tp_setattro(PyObject* self, PyObject* name, PyObject* value)				
{																						
	return (value != NULL) ?															
			static_cast<ScriptObject*>(self)->onScriptSetAttribute(name, value):				
			static_cast<ScriptObject*>(self)->onScriptDelAttribute(name);						
}																						
																						
/** python 请求初始化本模块对象
*/																						
static int _tp_init(PyObject* self, PyObject *args, PyObject* kwds)						
{																						
	return static_cast<ScriptObject*>(self)->onScriptInit(self, args, kwds);					
}																						
																						
public:																						
/* 最终将要被安装到脚本模块中的方法和成员存放列表*/										
static PyMethodDef* _ScriptObject_lpScriptmethods;											
static PyMemberDef* _ScriptObject_lpScriptmembers;											
static PyGetSetDef* _ScriptObject_lpgetseters;												
/* 本模块所要暴漏给脚本的方法和成员， 最终会被导入到上面的2个指针列表中 */				
static PyMethodDef _ScriptObject_scriptMethods[];											
static PyMemberDef _ScriptObject_scriptMembers[];											
static PyGetSetDef _ScriptObject_scriptGetSeters[];										
																						
static bool _ScriptObject_py_installed;													
																						
/** getset的只读属性
*/																						
static int __py_readonly_descr(PyObject* self, PyObject* value, void* closure)			
{																						
	PyErr_Format(PyExc_TypeError,														
	"Sorry, this attribute %s.%s is read-only", (self != NULL ? self->ob_type->tp_name
	: "ScriptObject"), (closure != NULL ? (char*)closure : "unknown"));							
	PyErr_PrintEx(0);																	
	return 0;																			
}																						
																						
/** getset的只写属性
*/																						
static int __py_writeonly_descr(PyObject* self, PyObject* value, void* closure)			
{																						
	PyErr_Format(PyExc_TypeError,														
	"Sorry, this attribute %s.%s is write-only", (self != NULL ? self->ob_type->tp_name
	: "ScriptObject"), (closure != NULL ? (char*)(closure) : "unknown"));						
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
		PyMethodDef* pmf = &_ScriptObject_scriptMethods[nlen];								
		if(!pmf->ml_doc && !pmf->ml_flags && !pmf->ml_meth && !pmf->ml_name)			
			break;																		
		nlen++;																			
	}																					
																						
	if(strcmp("ScriptObject", "ScriptObject") == 0)												
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
		PyMemberDef* pmd = &_ScriptObject_scriptMembers[nlen];								
		if(!pmd->doc && !pmd->flags && !pmd->type && !pmd->name && !pmd->offset)		
			break;																		
		nlen++;																			
	}																					
																						
	if(strcmp("ScriptObject", "ScriptObject") == 0)												
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
		PyGetSetDef* pgs = &_ScriptObject_scriptGetSeters[nlen];							
		if(!pgs->doc && !pgs->get && !pgs->set && !pgs->name && !pgs->closure)			
			break;																		
		nlen++;																			
	}																					
																						
	if(strcmp("ScriptObject", "ScriptObject") == 0)												
		return nlen;																	
	return ScriptObject::calcTotalGetSetCount() + nlen;									
}																						
																						
/** 将所有父类以及当前模块的暴露成员和方法安装到最终要导入脚本的列表中 
*/																						
static void setupScriptMethodAndAttribute(PyMethodDef* lppmf, PyMemberDef* lppmd, PyGetSetDef* lppgs)																		
{																						
	int i = 0;																			
	PyMethodDef* pmf = NULL;															
	PyMemberDef* pmd = NULL;															
	PyGetSetDef* pgs = NULL;															
																						
	while(true){																		
		pmf = &_ScriptObject_scriptMethods[i];												
		if(!pmf->ml_doc && !pmf->ml_flags && !pmf->ml_meth && !pmf->ml_name)			
			break;																		
		i++;																			
		*(lppmf++) = *pmf;																
	}																					
																						
	i = 0;																				
	while(true){																		
		pmd = &_ScriptObject_scriptMembers[i];												
		if(!pmd->doc && !pmd->flags && !pmd->type && !pmd->name && !pmd->offset)		
			break;																		
		i++;																			
		*(lppmd++) = *pmd;																
	}																					
																						
	i = 0;																				
	while(true){																		
		pgs = &_ScriptObject_scriptGetSeters[i];											
		if(!pgs->doc && !pgs->get && !pgs->set && !pgs->name && !pgs->closure)			
			break;																		
		i++;																			
		*(lppgs++) = *pgs;																
	}																					
																						
	if(strcmp("ScriptObject", "ScriptObject") == 0){												
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
static void installScript(PyObject* mod, const char* name = "ScriptObject")						
{																						
	int nMethodCount			= ScriptObject::calcTotalMethodCount();						
	int nMemberCount			= ScriptObject::calcTotalMemberCount();						
	int nGetSetCount			= ScriptObject::calcTotalGetSetCount();						
																						
	_ScriptObject_lpScriptmethods	= new PyMethodDef[nMethodCount + 2];					
	_ScriptObject_lpScriptmembers	= new PyMemberDef[nMemberCount + 2];					
	_ScriptObject_lpgetseters		= new PyGetSetDef[nGetSetCount + 2];					
																						
	setupScriptMethodAndAttribute(_ScriptObject_lpScriptmethods,							
								  _ScriptObject_lpScriptmembers,							
								  _ScriptObject_lpgetseters);								
																						
	_scriptType.tp_methods		= _ScriptObject_lpScriptmethods;							
	_scriptType.tp_members		= _ScriptObject_lpScriptmembers;							
	_scriptType.tp_getset		= _ScriptObject_lpgetseters;								
																						
																						
	ScriptObject::onInstallScript(mod);														
	if (PyType_Ready(&_scriptType) < 0){												
		ERROR_MSG("PyType_Ready(ScriptObject) is error!");								
		PyErr_Print();																	
		return;																			
	}																					
																						
	if(mod)																				
	{																					
		Py_INCREF(&_scriptType);														
		if(PyModule_AddObject(mod, name, (PyObject *)&_scriptType) < 0)					
		{																				
			ERROR_MSG(fmt::format("PyModule_AddObject({}) is error!", name));			
		}																				
	}																					
																						
	SCRIPT_ERROR_CHECK();																
	_ScriptObject_py_installed = true;														
																						
	ScriptObject::scriptObjectTypes[name] = &_scriptType;								
}																						
																						
/** 卸载当前脚本模块 
*/																						
static void uninstallScript(void)														
{																						
	SAFE_RELEASE_ARRAY(_ScriptObject_lpScriptmethods);										
	SAFE_RELEASE_ARRAY(_ScriptObject_lpScriptmembers);										
	SAFE_RELEASE_ARRAY(_ScriptObject_lpgetseters);											
	CLASS::onUninstallScript();															
																						
	if(_ScriptObject_py_installed)															
		Py_DECREF(&_scriptType);														
}																						

static void _tp_dealloc(PyObject* self)													
{																						
	ScriptObject::_scriptType.tp_free(self);													
}	