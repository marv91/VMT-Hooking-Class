# VMT Hooking Class

usage:

Define the new function. Use the call convention of the original function.

```C++
typedef void(__thiscall *funcA_t)(void*);
funcA_t oFuncA;

void hkFuncA() {
	cout << "hijacked funcA was called\n";
	oFuncA(g_pClass);
}
```

Create a new VMTHook using the create factory on a given class pointer (pClass). Hook a virtual function using the HookFunction method.

```C++
unique_ptr<VMTHook> ClassVMT(VMTHook::Create<MyClass>(pClass));
oFuncA = ClassVMT->HookFunction<funcA_t>(0, &hkFuncA);

pClass->FuncA();
```
