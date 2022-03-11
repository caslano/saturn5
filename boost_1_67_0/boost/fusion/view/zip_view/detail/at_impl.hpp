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