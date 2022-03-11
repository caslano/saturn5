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