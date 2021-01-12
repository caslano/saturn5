/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_AT_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct single_view_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template<>
        struct at_impl<single_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<N, mpl::int_<0> >));
                typedef typename Sequence::value_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type 
                call(Sequence& seq)
                {
                    return seq.val;
                }
            };
        };
    }

}}

#endif

/* at_impl.hpp
5QyGAAbvO3ged3Q41vGbhxW95+Hgd3dwK3DfFAS7n4N1j0r0QF/2wx0sjPojj8im/ayqKIxLj/MYhzNtW8jfXItC+gT9E6pD6HBsq3ZPlwHJJq0azlhefGRoX//A22Ke1K2a5E1s87I7nP27cE41DsvXd+GO9n/IqYu5vy+Q8p1Z2L4BFtq8sDYVKljh9ylNOPs5PVC8ljh9NF0ZfXrJxcb2WH8OYSx/973rjP6/nmb/AOsa
*/