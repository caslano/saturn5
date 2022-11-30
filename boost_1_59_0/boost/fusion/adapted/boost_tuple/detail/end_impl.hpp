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
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
*/