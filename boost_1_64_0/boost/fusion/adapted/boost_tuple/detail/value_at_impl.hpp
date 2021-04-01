/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_09262006_1926)
#define BOOST_FUSION_VALUE_AT_IMPL_09262006_1926

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply : tuples::element<N::value, Sequence> {};
        };
    }
}}

#endif

/* value_at_impl.hpp
N6JMISjUAEtklgXUp9mwDL/UrCHBrjzHPnTZq6/H+t+F/yUjtdp0CTj3WSiUMPyBtwDN23PBKHlyU+wRJDj84ty3unbU5LePPKc4ZBpnELkMJvs0ue6z2fFaZlao/p+DyZO4xpbNcGtFNwJJ/o1voLdNaOn9nODCw9dLTCAyk0EyRuUvDSOC3m0hN8xoOCHqFwPis2u5zZyWevh01RQc0GSg5/nCd9ciW2dsmKz5v6cxzix0n9DI578/DMJKSLqu3TIQYeMGeMpxUaKE1Cs1KVZWAPNUcYqp70t2n3brlOuOcNkpe47fHLbUvD/JLtHqgB+/XPGiwSy4B5pUZuwGryYL+dX9A1VAwv7t9lHlLp1x6Wd0cXBbn3fLKMnb5leEXo6LHcEsZTO00dQTTLm2w2BtgdZ0qd3oQJUSwPu3cb5q7kAYXeUUt2BMBjTWSD1Pr4UZvOPv53T9j0ixgiQ1yzxeWUdfMfavXKzE+Lq5CfxPIhOqrOSox382qoeptZlmsF3A9+fVDd/3vl6Jcj8wy2M7Qei4lZsgCfQzdqD52B3SBUpgSmWTxvJeIQ==
*/