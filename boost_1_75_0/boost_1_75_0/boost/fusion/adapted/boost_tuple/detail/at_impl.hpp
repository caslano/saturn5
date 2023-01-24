/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_09262006_1920)
#define BOOST_FUSION_AT_IMPL_09262006_1920

#include <boost/fusion/support/config.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template <>
        struct at_impl<boost_tuple_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename
                    tuples::element<N::value, Sequence>::type 
                element;
    
                typedef typename 
                    mpl::if_<
                        is_const<Sequence>
                      , typename tuples::access_traits<element>::const_type
                      , typename tuples::access_traits<element>::non_const_type
                    >::type 
                type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return tuples::get<N::value>(seq);
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
SjlpumNczVZEQdG61GXrfgqShJ9Y0H8NR4sZ9Pj6ew1pL9G+0V/3ZfoNKIU3DeZ2eoNJGq/hz7f482X+fJY/H+NPhT89/DmPP+8eTDZxChsWuUwyFbIRVGz4eZZ9K5NAECz+dTWyRNSd8/kYKl2B89QRtnJbpEQlxZo8PqPh5+JqGO6wpisiW6gIQGBY+xRMLJXHWQr18a3xFsZIiD/G+KeYO53qmuUdwe/6fM/jiCfHLt0xEmwheOR6MtiTePgIoRA2Hk/xwBGwpylMKrlY/PiCJfccC5NKxyAezPgcDmcnY/pbuuE6qZzWSGw2tU332rgrBnSfWQ7lnEFJ0EcweAYtpwxYoFLHVltlyd3EWG0QYzWVj9U7qYDlNMSXG4ZoM4Ec35N0LJO9XF35SrzFUYNuxPP7URhnn7MtCXoWytameYhCUYQgj2zFyjEevX3Q7RUewUXgOswkk453FfTVcvrI8PogC+dlzuoHLg0hP9Aif/24pvGIf7OIpm5GwpvYO1nug8mTKP7yWCieUVVoCi5U/+jNgwtMwQVq1UsnKTjPFJynLoY6uJR/A4zKbcJpCmxpUnC8paBJxG6jWilYLcL/5nXjjftqDCM6IYbLniO4LVhQhTDHk6twkOPh8nEE61hQyRq7imRPJc9AjaHdIuOW7EpnCnn+nBoDPLvAxCwVH/SwmPzXErNQEsEs7DfkA4HKVrhOGEC5LCcJ
*/