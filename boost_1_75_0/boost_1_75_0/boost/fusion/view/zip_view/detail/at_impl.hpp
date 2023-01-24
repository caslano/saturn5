/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_IMPL_20060124_1933)
#define FUSION_AT_IMPL_20060124_1933

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace fusion 
{
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_at
        {
            template<typename T>
            struct result;

            template<typename N1, typename SeqRef>
            struct result<poly_at<N1>(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::at<typename remove_reference<SeqRef>::type, N> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_at(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::at<N>(seq);
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_at(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::at<N>(seq);
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
        struct at_impl;

        template<>
        struct at_impl<zip_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<
                    typename Seq::sequences, detail::poly_at<N> >::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& seq)
                {
                    return type(
                        fusion::transform(seq.sequences_, detail::poly_at<N>()));
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
3z3nvZdhvLIjG6bJrAGaZ3hC/23yFuG0vuleuv5BVpIcP+eFiLqMXZEriKJzPbyzOq3ijL/lw64YD8LbHSR1LV3dvLJerXuFR9Zpd/CvOulYUGP0uxiRPsmvGDP9PEehnJZriyDyPR9xlr8LZsg3ZQ34ssh85XgBavlk3cu7qAh0KedllY/pydJ10KtBT/t+kW+Tf0OUyqyX+tAv5g/rwnxu5h7vlS/L/WfqrrviCXOrG5/dKSYew8y+WzBhmtwB3D35PAymEyxRKCokI2L81Xy8P/q67f+BgaeeB8I4X4+ONU9dgMnB/X7m7ILFgW42Kvh0lWJnt2y9Wjko90bSwbzr/ZlPtVFkWCpawMPbZM2ni3ww1LuWCqrAfMiT/MlWPlKp/Ka5+XfptFw+OozrqMP1POM7PVOAXADsF44FJuUm8Lvz9TyNYz8kcH9Uq8gaDQDesVB2lMm18DQsl/VWxVhUUajoWF/14RnNlaLtKtwN5wxH/crzLkGVDPmWMN+mPQ/wjuh7kPzmlueO5PLRtTkf8pWy8DdpDrzIUjqWWRelbjGMoWtmj+CIasIda1Q4zMdjJjuy56ATXJ+j74QpKdtlPboK53AHGRNYed5S642yUeSudtnYNp2t6U6+QSe0k39qJjbwL7bJVOY3ZSKcIXVO/lzP7Fhm8QD/Yv5T4w+qw5+EqZnOaaYu53ylrEcn/mnPzTW0xxSeP+hu
*/