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
GGY0mVxc2qt7jcKRBGDxrcrGs4ssLkWK/bNeibVr3OsLz8Zsh0fPGsWkt7kBKhNvtVib8oODiBc78y1DfhFae4Iv0DzQ4WfYhbTnMo/sdVAT1xsHm7kmuxqOR8QBaqIKv9/38qRuWEwVCH4EU5uDG3rims9duFfCvU0ReaHCMoGzEq3formqpg+9ilT9Zg6ZylMVh9y2hpQL/tMNXmNTc9ZH2sJjoo3kfkAka6OqlqyCSlfTYAH7Whh6l651Fwn8Yue6e25qDJtc0dYVJdbey9ync3XrRrnV3aNSg7NR3hY535TtSKjj+3RZZyVjOR/eGnQG/Ack2OxStpwZflmZ1jZod8zGDKlcVbQataKqoK54oiLZC7lYAiuKTb5u3bmrcbvtV/r9fuNV1Lt3d1ef7l09cWR/q+Ovnmtx/De7NwhoBxn+CjvPpWzzUMxNAj5joWpp9s9nawF2mqvtodlL6f6KxTL1rxLdtMqZ14Wor+GNSUndxjde1KY4fjcB6rLAczt8+b9PunML2DfWxG1nM068M/Bq25EGgKzxCmXHUZ9ump3Jy+ZFUCyPhWrH9WjYPsZW9grzcyFE3W2l6xHEjgdb977q+cRXN8zhv1BLAwQKAAAACAAtZ0pSI6SsB8UIAACHFQAAGQAJAGN1
*/