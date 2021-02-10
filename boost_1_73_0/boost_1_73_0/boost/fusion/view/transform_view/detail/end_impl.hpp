/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_1028)
#define FUSION_END_IMPL_07162005_1028

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<last_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct end_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last1_type last1_type;
                typedef typename Sequence::last2_type last2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<last1_type, last2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last1(), s.last2(), s.f);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
rnmvLrbxy+84m0nrSmYjTtWgv+yiSvvzZ10X3cnSG7ntTtL0knsw/GdcBHKAda94crIMF5S402La44j7Cd79In64/YgCFcYR/6ia44FNqWT4TM85lj+LTkdsi47oeqQQdDwR8Vo7Oo1gdG+9GltSWdzra+jqNU+f8lNQPB/O6rXjFKkhuqIEC+Ns5aLXC3SFVoZ/n0+WnQwu4PlKlWj1y7olyrEuubr5oS4XrjRP92fyW/tua++u4RfcG1iUya+Ces0/u2ss3cNT/su7nh1s05OQEDiXiPxgVss29OIXbGHCcQM28DBMKw1afQVaB5jms5ZlubA5AM3EjhS8gBVXS0KdCyHGTn8syl2DPb6O39xrC205Wou3y2VDKFfWvbSczMgCwmvbajsojFE6qzrkKj12LNNSFLe5Xiwvy+RTKBD9NLy8QHbz4/H+yc8LQafhoQK9tK1mVpj2j6k7aNjGGa8xjzpxiouJg/kKk5wjywKFy/2YGpaKh1Nu2S66BrWoVheYVHBwNMv8GmfmNoa+sTsgvnNS1MDP/dmprD3Nyn88FTlspS5m5bmpMUd/cK0gf6gppGbrFfmEWIC0sei3KIROHsn1aQl2UVwgkueytY4yXe97YDWkZoLgHO65BVwc+cIoaYl+t6Xei/Fi
*/