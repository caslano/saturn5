/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_0115)
#define FUSION_BEGIN_IMPL_07162005_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::concat_type concat_type;
                typedef typename Sequence::category category;
                typedef result_of::equal_to<first_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, first_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::true_)
                {
                    return s.concat();
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::false_)
                {
                    return type(s.first(), s.concat());
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, equal_to());
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
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
*/