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
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
*/