/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/repetitive_view/repetitive_view_fwd.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_tag;

    template <typename Sequence, typename Pos>
    struct repetitive_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<repetitive_view_tag>
        {
            template<typename View>
            struct apply
            {
                typedef typename View::sequence_type sequence_type;

                typedef repetitive_view_iterator<sequence_type,
                    typename result_of::end<sequence_type>::type > type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(View const& v)
                {
                    return type(v.seq,end(v.seq));
                }
            };
        };

    }

}}

#endif


/* end_impl.hpp
Kp4cCzcIat4FRe1yDUsck+c+mDsYP3Pzwh2lUYCorCDK1u1EnLm+KbMHvblBUrDptV5CvDi/XPYWsxt24aUsn1kKF7l56PL8x3ec4qPxRpEy1iw6X9zRfWMek5ZUTJ0PhbFp0Exv2ZNbWOfBgsaH4ZVTKSlSNhP8Len3UVhY3N4KFP1caIgUaMqWOEII/Q6h39I2v0f+Yx1q6ui7js4N7BJ6TygHnJu4LT/kTfcFlY/fcpjtaaECK278wjBMEi76rmKS84NaqwtZCIt4Lr/6a1to45PkA1bFbSPJfDL4cFj/SMytHL0TgBp8z1IWLEhre1yy+Yy0MNYIOneg7NX1lgBTZeNG7MFlokQZVYvCZXV0kGKifG1blnbwC3KiPAdIY6h41m41CK7ID4EWRzYf6tOOze1tbBAOuRsnMhdeaqE0cm8KOOdauL0/KuzY9Y9wz1/iVBv90GnfNB63sl3IPsXEry+Od9fr2p1fKtsV4P3rQEdHzhwUKjgu0Ogc+yXKevngyACLbq7h8HMn9oFGOSLdDGvWEFHqv3i3XJTKndvZcpe4wAjqptivZQ==
*/