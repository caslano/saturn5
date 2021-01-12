/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_09272006_0725)
#define BOOST_FUSION_IS_VIEW_IMPL_09272006_0725

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply : mpl::false_ {};
        };
    }
}}

#endif

/* is_view_impl.hpp
2Bks10rHT7/2AREH9PscfKxR12NI2E4+0Fxdj/mZWXJt2s9x+XjPIEt+v/ZhH94ALyVCF4v9xWWMXVcUF+pst1+OAZu65HVi/xzfx3aytR/pz9tkFJIr967+cZWrbb7RRg9aE18fd97mvOccX1N3vljOd/FtsQdZYV89rzyOH97z3/I0f6+U80t8mXZPZuJErB/setZQZk+ORTzGNtQ/7zlxTbV9cbnYucT3Dft1B3xJ1vHI
*/