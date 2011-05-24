#define _NEED_STDIO
#include <PluginInc.h>
#include <PluginManager.h>
#include <XComCreator.h>

void Test();

#if defined(_MSC_VER) && defined(UNICODE)
#define main wmain
#endif

int main()
{
    CPluginManager loader;

    if (loader.LoadPluginManager(L"../Plugins"))
    {
        loader.GetPluginLoader()->LoadPluginFiles(L"../Plugins",
            L"Win32DllTempl.plugin" PLNEXT);
        loader.GetPluginLoader()->InitializePlugins();

        Test();

        loader.Unload();
    }

    return 0;
}


#include <Ix_Example.h>

void MyFunc2(const Cx_Ptr& obj)
{
    long value = 0;

    // Cx_Interface与Cx_Ptr互转，转为特定接口
    Cx_Interface<Ix_Example> pIFExample(obj);
    if (pIFExample)
    {
        pIFExample->Foo(value);
        printf("value: %d\n", value);
    }
}

void Test()
{
    long value = 0;

    // 使用类ID和接口创建对象
    Cx_Interface<Ix_Example> pIFExample(CLSID_Example);
    if (pIFExample)
    {
        pIFExample->Foo(value);    // 调用接口函数
        printf("value: %d\n", value);
    }

    // 转换为其他接口
    Cx_Interface<Ix_Example2> pIFExample2(pIFExample);
    if (pIFExample2.IsNotNull())
    {
        pIFExample2->Foo2(value);
    }

    // 转为无接口类型的Cx_Ptr，可避免函数定义时必须包含其他接口文件
    MyFunc2(Cx_Ptr(pIFExample2));
}
