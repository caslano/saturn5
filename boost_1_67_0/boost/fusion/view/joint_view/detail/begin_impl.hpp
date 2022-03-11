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