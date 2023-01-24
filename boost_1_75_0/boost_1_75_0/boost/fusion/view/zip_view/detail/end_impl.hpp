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
vt4gf8T6z5P0TiQMDKW1/AM4BKmpdPID8/VAU5c6YevhtaCD7U+a/duMJbO8IZDL53pkSsiYgR/qj+ctjniLiUKe5kYnCd0cTLg515sV4VVZ/sV8Ve7BP9/BFEzThI9okMadLvLtuhvkrteow3hls5CNyjgRzeKTw/mEZ15c1rPdK/WutliO++Z5mot8YBhb8SeMxR8u8oGz5V5T32JGqf2NXT4X1r4I+o7qgIuJdzhc1isDlndjccojEm50SvBZmCdCrh/WykL7XGbr7fJA+qjCHQWuD5YBsh8Ph+gTj2CXl1wqusnlI/dbhflkqCeynuclNNrfWvHbpKwK/JOnfwDjDzhmIqpNcSDr9eEZtOTwyE3CLNsfsen1eT1hlwyfubnxD2xTBlkmIgv6/UDFUME85aMTEfZi8vd9nPjnSfrF0Qk4X6xTL82Q48fJ1tENyPlrD13SHH/Cl++0H42ye+xvd7kfm3KG4OWbw14O4XjGUQf1KPCEWBjmtcHFlcu3HpEzCBL8We6HZ1xv0elfwZmZBxqswXyRz50DyEeO2u+PWwYjJyszkYq4ppVnsV3Wg2vOWSEwc47P3T/j/NAg/xMPwD00+f6CQgMJYX4BV749T3NWXEu1tNGJbeTLFJfzXMmL8sRq6mC19L37sY22puOSaGALECN5/LGlc7Uo6j7jmXMyvWeU0sNrXDFapA1zneXr0SO3xy5/yEwm
*/