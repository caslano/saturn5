/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AS_FUSION_ELEMENT_05052005_0338)
#define FUSION_AS_FUSION_ELEMENT_05052005_0338

#include <boost/fusion/support/config.hpp>
#include <boost/ref.hpp>

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct as_fusion_element
    {
        typedef T type;
    };

    template <typename T>
    struct as_fusion_element<reference_wrapper<T> >
    {
        typedef T& type;
    };

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
    template <typename T>
    struct as_fusion_element<std::reference_wrapper<T> >
    {
        typedef T& type;
    };
#endif

    template <typename T, int N>
    struct as_fusion_element<T[N]>
    {
        typedef const T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

    template <typename T, int N>
    struct as_fusion_element<const volatile T[N]>
    {
        typedef const volatile T(&type)[N];
    };

}}}

#endif

/* as_fusion_element.hpp
dn558c4t6vvcwiNJwlhJTns5GqxVH3zydVTV0FZHqbU5Lup+lHDxQ1w+HCaXdle5tOtSaU+8KJZ20DjXs4qhYcqMbzGLSDgwnI3fdozfMYLwgeFhFcFbYK30Si5vpW8Mp916bLQZ1+Wx/hESeWIWJwxwyHbhjsPdHB5hU942Qx+7u1kq0bjN3OxiMAhh23zy0JuqPfFsS9K1F9QfGmQTsBNj1Nd2MBvogI3qzfTMsNZV48VW1JpqvNjiXk2NFzvYRFl3NBzOFsbqvRNtgyCiJ6LXaAmyIhIlevwEEb3XtbFEL5EgeggeEr1E3yBElFWCRFndLsIqq2x/3jvvnPfPzDf33Lnz3e/O3H/m8bPN77KlTxVqevMpMfO32vi6nckpw6lf0oKTb76zWeV7EvBj5817LuC1aIViOfmY7DreLu/EAuzP4IWM5nEWr7ofyx2yn1PfC++8dPJrLw5p+7YkGtT/asT9cILVYafkX3VRzRevBLx7jTheHuSEg0kxFTT1eh9XgZ8p8aRvgkcl9C9hrwiI5WlHAG91qQwKcOOddWDGctqm+LIA75NnoC+szVsv3AY2PZ6qepCIfbL5L7O2SDr3OMyN7O28sH5W89bINvfXyZ0AFT3FmEWntuGuf2VEOzzkfAB/ldVQZQtiHJB2PcSzI/PmxJbdR2/pmnHfCjO2VGpiWFjUz3QMKVBrueVjO1ItA9wrtU77UGJT
*/