/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_05052005_0229)
#define FUSION_VALUE_AT_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };

        template <>
        struct value_at_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename N>
            struct apply : Sequence::template value_at<Sequence, N> {};
        };

        template <>
        struct value_at_impl<boost_tuple_tag>;

        template <>
        struct value_at_impl<boost_array_tag>;

        template <>
        struct value_at_impl<mpl_sequence_tag>;

        template <>
        struct value_at_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_impl
            : mpl::if_<
                  mpl::or_<
                      mpl::less<N, typename extension::size_impl<Tag>::template apply<Sequence>::type>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at
            : detail::value_at_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};

        template <typename Sequence, int N>
        struct value_at_c
            : fusion::result_of::value_at<Sequence, mpl::int_<N> >
        {};
    }
}}

#endif


/* value_at.hpp
haXFzO028z9QSwMECgAAAAgALWdKUloPssPFAgAAGwYAABgACQBjdXJsLW1hc3Rlci9saWIvZXNjYXBlLmhVVAUAAbZIJGCtVO9P2zAQ/d6/4gm+lCojjE9jY9OitBtsqKC2CHVCitzk0nhy7ch2+LGx/33npIwNlfEFV6njy717d89nb8tSF1TiaJQMR5MsPZ+cZKNpmpyNsqPeNn+RmjZ/jAcvN3oY4NmRtU/Gg+cWcWbNd8r9Zu8su0P3Y9Qlz8+RxHiA3GU7eB5yh34LydYsh+E9y54jugy5hb84IC+z8MoWhgVkaupbK5eVRz/dweuDgzd4hf29/b0IQ6ElKUw96QXZZYTDorV8rMTNza6jDxHIQ6jddahZJR2cKf21sAR+VzIn7aiAcCjI5VYueCE1fEUopSKkp2fz4/HnCNeVzKsQ5NY0cJVpVIFKXBEs5SSvuhi1sB6mZDgHL6TzHLDx0uhd5iZ4sisXYgR6oZyBuBJSiQUTCY/K+9q9jeO8sYqzjwuTuzi/L3+38qs/lcw5iZW4hak9vEHjKELwjLAyhSzDzIKwsW4WSroqesiGqXQRGwtHSoVYjJPkurQJ07U8UXBDzRlLHyZntAtU15VZ/ePIOoYoZWM1E7EO7FQYljlCw0fJts5t5fcU
*/