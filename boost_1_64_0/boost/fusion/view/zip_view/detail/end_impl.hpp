/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_20060123_2208)
#define FUSION_END_IMPL_20060123_2208

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/min.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion {

    struct zip_view_tag;

    namespace detail
    {
        template<typename SeqRef, typename M>
        struct get_endpoint
        {
            typedef typename remove_reference<SeqRef>::type Seq;
            typedef typename result_of::begin<Seq>::type begin;
            typedef typename result_of::advance<begin, M>::type type;            
        };

        template<typename M>
        struct endpoints
        {
            template<typename T>
            struct result;

            template<typename M1, typename SeqRef>
            struct result<endpoints<M1>(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               get_endpoint<SeqRef, M> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<endpoints(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::advance<M>(fusion::begin(seq));
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<endpoints(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::advance<M>(fusion::begin(seq));
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct end_impl;

        template<>
        struct end_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Sequence::sequences, detail::endpoints<typename Sequence::size> >::type,
                    typename Sequence::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::endpoints<typename Sequence::size>()));
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
BfNhVq1Fv2Voqvnmn72N40uGolUC489tx7Ulx6MFgfE7sTDx7U40HZgvs7yPud+odzBPZv221vmFliT2i7/aoSnlIvY7nPTjGFoamIafJc1jCM1d7Nf4UJm3aIoF5vt9u77vO5oNGL+7D3YsSUJTg/E8TzaOq4MWAubGrHNwgxJoejBbZhmhZSPQYsEcme0bMVlJmYGVYFaje8/VlBkY72+NoqOGcgFTMmvwq9lDtAwwJ2YD0lKGUmZg/E74rI55SpktNM/6edcJhc8KGF/z1rX+1SkXMN7fmH4l5qDpwFTMJozRGSgXMDWzsMatHqAlgtkwa3dRZaJcwOyZuZ9v+hUtGcyV2dZPZ7LR0kXdkg7aMmhZYM7MlrnnHUXLFXUzjj3qhlYgeqjie/gNmnqReZ3S/8Y0yhOM52K9Sl34mizqbOb3SqQ8wfj8AltEDEGLE3Wz7Pp3RDOA8Rk9a9GNZmsE470PebiwM+UJVpJZ68c7DJSZqMtW3GtGmYn9Og4O1lFmoi6o5fs7aKrF5vu59wrvghYExuvmLT14gXIRNuXzlgFoscI6fDjpQLmAeTO7VrR+Y+pd1D2rNNMXLR2Mz29zrJ6ev2wwF2bN77XyQssDK8FsbcnIK9T7EvM69/nZd9ECwPjvdTMyfo5CCwTj5/y4xSkfTQvmxs/5LPUwWpSoCx3V4jlaApgNM98nz9egJYq6DQ0HjUFbKc7ZKOXkB8pT1LnmlOlHeYIpmTkkng1AyxJ1V6b23IGWC8bnkOb+bg+aYql5XUKEx1E0NZgDs3ZNblPvAWB8Dj2TdE/RQsDsmPnsOj4NTSfqHK6dLI0WC8bPWa3z2kg0gzjn0Gm7yqEliTqHza2KoaWKujP6rzXRMsD4/DJ31w1GyxZ1ZZyvJ6O9BuPvmy2H/McCrUDULbiygu6SfZL53CNuOnWmrMF4XZutOePQAsH4HD50nfaNshZ1X4cnD0HTgymZ5byZfIOyBuNzOLe4wWjKGsyd2WxjhxNoJlG36NHOg2hpYI7Mwm+5WlPW4iyZB/otpazBfJit0nT5iaZYZj6jF2N7GNBUYHy/Hi2VejQNmB2zGjNrHKc8weyZXR44QUN5irqp/r3KounAXJm92z/tEeUJ5sZszKYhlLUBjM/PZv/G2WhGMCdm22ulXUFLFnVBHToFUdZgfEb6b/ocyhOsHLNvE5XN0WyWm+/XR39nG2UGxvfrWuzFWcoMjO932zV9EeUCxvf7srB0APUu1lytHbaaehdn2RHZYhL1DubBzGS9ORMtA8yRzyjnshP1DmbLLPmfRwPQcsH8mTUOjDuFpl5h/h6n1/odRgsB4/s92zfuPfUOxp/pvZXmV0TTg/nzugn3HdASwVyYGZcaP6KZwIoz613Sjc5yBIz/BnFvtc9/KBew8vz3OlWCO5pipfmd18e/P4imAqvBLDpxfCT1B8Zf69o49e9B/YHx/Y41u/AKbbao034p/D6WJPZrdsUzjOYH5sbvRLi9HVqe6MHZcnQx6m+V+WvIjeueR9ACwDTM7EKvjKP+wHien/ObTqf+xJrNqoX0RzOAKZk5pk0cjWYU+/V3Hk/3Og3MjllLy/57aX5iv649I5yodzDee/jkyfnU+2rz56jizMPl0dRgDsza1PZ4RLmAufD+JuvWooWAWbFcFt2w/oWmBSvDf/OvvJzmN1zU5Xr++ICWIOq2JgTsQ0sG4/3F9U9OpszEOXeOek11WWAqZlc+Di+KlgtWnNk50/qraFZrzJ/bUNXCADQVGD9n2SfK2pQLmCuzV49ufEXTgwUwO187Jg4tEYw/DydMriloRrDq/D18R7tBaJmirqrTpmNo2eKcnidaV6L+TOY=
*/