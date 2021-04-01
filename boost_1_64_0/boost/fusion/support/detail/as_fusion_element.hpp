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
Xc2+eivyGNTJ0MagPNCsRMNRv8bb3sHkIk+xFLxT5QlVreqGlWk7J37v2qde1e9Rua6V8pWbPAjyy+6+7Zn+7pZzbZEv0HSkwDAeF9TiSqOnuwrk2K79LtEVmZJMSkai3UYY9C7gZbIjoJ8+jbos8Wh3HlFrb7fXfUOdqtzUuO6hIu+S/xLN3/eiCH/F5uUvr2OiatQ0I1+Um5OUwrHrV8ANS9lL1ZHdWIZ1CNji3Xc1qhLhUeCfBYqj9uqBovN/wQ96vU/0QLxVmnDznXyaCI5iowLsdQak4dTM+ZsaHA0Bv2BXs+G4CSzzqzt6fI7zFpOdBSf0jn5aUKsmNBCN+bxn7BbDqp6KasHNdpFctnE7yhTpHBwyA3rB5GIleJbnsNguByRXMYFdG3q+hilkAkdWGxpQLCgUm6fVrYKM2Em2wAcLJ+HQOL2KByOaCTTE3XGfyiFK8xNDljoAbLArGa6vcHNNwgeMwZZHfWL9KVtEU1Dns4zzsRixxsNEbjFJzRDu/3ftw2wVK/HO847Jw4rGaDn6ieSiyo7syrp6ClkvPNI8642Di1DuaQ==
*/