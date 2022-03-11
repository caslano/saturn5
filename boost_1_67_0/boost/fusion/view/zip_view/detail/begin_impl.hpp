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