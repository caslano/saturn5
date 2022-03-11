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