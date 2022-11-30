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
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
*/