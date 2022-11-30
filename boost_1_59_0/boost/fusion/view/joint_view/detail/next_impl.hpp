/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_0136)
#define FUSION_NEXT_IMPL_07162005_0136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<joint_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::concat_type concat_type;
                typedef typename Iterator::category category;
                typedef typename result_of::next<first_type>::type next_type;
                typedef result_of::equal_to<next_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, next_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::false_)
                {
                    return type(fusion::next(i.first), i.concat);
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return call(i, equal_to());
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
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
*/