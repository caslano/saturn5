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
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
*/