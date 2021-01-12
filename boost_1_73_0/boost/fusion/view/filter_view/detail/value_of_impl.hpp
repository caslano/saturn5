/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_05062005_0857)
#define FUSION_VALUE_OF_IMPL_05062005_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<filter_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
YefTcTBGW7p8JPMKHLe/ipMwwenzBqfHWdof5dgce1JJAh9o3IDbxQrD31zjtU3BV5YEUek3eGq11GZFXiK194EtVQ3XjaXFWgKbwl+GJwnyBjt370r642Q+XBtOsyS0G3DrWrcIfz/guV8kTwJsGheEr+4lfHIDiY+xeg9Lreteu2PK8I+Q+LCIczR21zBUttT7k2X+09CBYyqMNL7dZiHbOgm8vHfP8XDWNtEMNENm7fkU
*/