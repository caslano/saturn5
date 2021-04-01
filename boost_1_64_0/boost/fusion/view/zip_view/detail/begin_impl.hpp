/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_20060123_2147)
#define FUSION_BEGIN_IMPL_20060123_2147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/support/unused.hpp>

namespace boost { namespace fusion {

    struct zip_view_tag;

    namespace detail
    {
        struct poly_begin
        {
            template<typename T>
            struct result;

            template<typename SeqRef>
            struct result<poly_begin(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::begin<typename remove_reference<SeqRef>::type> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_begin(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::begin(seq);
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_begin(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::begin(seq);
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
        struct begin_impl;

        template<>
        struct begin_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Sequence::sequences, detail::poly_begin>::type,
                    typename Sequence::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::poly_begin()));
                }
            };


            
        };
    }
}}

#endif

/* begin_impl.hpp
BYD8iNyHaiCeDJK16Dbcg1XsSdlsTwTXH7d5+TcRx0KpuIuDJc66rLC9T83a/z5ACxAEpJWoTsELYTFdKeV2e+RkvsL5eE+DrpqoiAVV2clE+irrwUfxWSlIMiEi10NRqe+dnR1CjZ6tGBtgqI6IYUZTY7BOiBzV3wgNG14oSQATxp+BlQ/Kv7apHPezjIB9Uy3l0VMpHNFO3BF4TobhK5Me8Gy++XKAkwLxpknKTCQD+DqzoHVyDkOM7HoGxSzwNAWvjjNkKODcWAJKEDhHr/9unaSde1DuXKjQnhjzj3ZEByFXHXqlFrLoeG8O6bgaK9o0k5bwO42CDuqo7Nw36Ew2erDtK1hGNJTnSKhmI83gpydAxd0ZCg13g7HcvJ2OprRY+TNThU4XC9jVasdsktl0tMbY5S5eam5MsKKgGEmyQ8t7DxwnMDS9Jx4nyEEguQTt0w47DcuGMXQIVT573KsQos9YiDn4h1d9ox9JvAV6ITflqD1on13xXlNUTNVlGomI1nAT3yzYCOyjzFo5XZqe1muPliTtsIW7teytwOyp8F3+5M9p6GVOQQ==
*/