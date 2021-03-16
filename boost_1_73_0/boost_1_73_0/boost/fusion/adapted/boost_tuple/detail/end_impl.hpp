/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09272006_0721)
#define BOOST_FUSION_END_IMPL_09272006_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace tuples
{
    struct null_type;
}}
    
namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef 
                    boost_tuple_iterator<
                        typename mpl::if_<
                            is_const<Sequence>
                          , tuples::null_type const
                          , tuples::null_type
                        >::type
                    > 
                type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
51U58gYkH+6XRmqtrsEyn7L8QGjo0C0ZaagTjXzEd9bVUuVgRIXJDC7bQmei+lzHW/jqjnCDZgBtRaFGqjCsR9Y+qzNyj7E6Ww7sPmGCom0E9rw82hTDrDR2dk400lYPslROyd8zDmatKlaL00pnF5eHaCqspLQ8kbeiG8IcdVPnn4siWWuH/HURJgZG7LOMDu2i6n8q7W6/eEP4HZ6qLuJcm8kytSPNjPelGfTklHYpF9JBe3eQDfosFo8h+tw=
*/