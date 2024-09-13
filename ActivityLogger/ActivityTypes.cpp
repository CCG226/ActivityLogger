#include "pch.h"
#include "ActivityTypes.h"
#if __has_include("ActivityTypes.g.cpp")
#include "ActivityTypes.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::ActivityLogger::implementation
{
    int32_t ActivityTypes::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ActivityTypes::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ActivityTypes::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
