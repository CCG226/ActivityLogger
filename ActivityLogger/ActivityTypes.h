#pragma once

#include "ActivityTypes.g.h"

namespace winrt::ActivityLogger::implementation
{
    struct ActivityTypes : ActivityTypesT<ActivityTypes>
    {
        ActivityTypes() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::ActivityLogger::factory_implementation
{
    struct ActivityTypes : ActivityTypesT<ActivityTypes, implementation::ActivityTypes>
    {
    };
}
