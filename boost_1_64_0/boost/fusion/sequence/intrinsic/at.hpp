/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_05042005_0722)
#define FUSION_AT_05042005_0722

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/type_traits/is_const.hpp>
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
    struct std_tuple_tag; // std::tuple tag

    namespace extension
    {
        template <typename Tag>
        struct at_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };

        template <>
        struct at_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename N>
            struct apply : Sequence::template at<Sequence, N> {};
        };

        template <>
        struct at_impl<boost_tuple_tag>;

        template <>
        struct at_impl<boost_array_tag>;

        template <>
        struct at_impl<mpl_sequence_tag>;

        template <>
        struct at_impl<std_pair_tag>;

        template <>
        struct at_impl<std_tuple_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct at_impl
            : mpl::if_<
                  mpl::or_<
                      mpl::less<N, typename extension::size_impl<Tag>::template apply<Sequence>::type>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::at_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct at
            : detail::at_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};

        template <typename Sequence, int N>
        struct at_c
            : at<Sequence, mpl::int_<N> >
        {};
    }


    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at<Sequence, N>
        >::type
    at(Sequence& seq)
    {
        return result_of::at<Sequence, N>::call(seq);
    }

    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at<Sequence const, N>::type
    at(Sequence const& seq)
    {
        return result_of::at<Sequence const, N>::call(seq);
    }

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_c<Sequence, N>
        >::type
    at_c(Sequence& seq)
    {
        return result_of::at_c<Sequence, N>::call(seq);
    }

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Sequence const, N>::type
    at_c(Sequence const& seq)
    {
        return result_of::at_c<Sequence const, N>::call(seq);
    }
}}

#endif


/* at.hpp
LlDaT+7UMVIjGp/WeIg/485dgHkEf8ZPajjNnxFsbnWMqCHG4ysw72qMtxfvqaPLtwx/tI4OliPKd4ifxDG8C/FcGUg/s1fQeWL+EoDj8Htb1bt0O/WTLMhs9oza0ebOkbcNk7meXXO6LrMF6aDHCb5176XvAlnu22lu5krMcoh/hgFGN4v8ZheexPgqIOV+4tnK29OJwQoOv6PMz61jqC/+N2ox6PeP74UnyjMMxSmY6wyD8aspBteFJ9H7Kzd1UttqbTi3H8Y5ehJZe2Gr4aew95pbevfce8RbBdrysjD3bNzr+mFf6W5imOYxfVuj62N6aRAwDxnTtxjmEca0s1nDaePwRoF5l/5tVJuSkUp8Dd8xYWX0ijeqcguRg/F6Z52/UaFNicqXw1YuTfIkSBQ28oaGfMZOatPg+KGX+0UuQL5jwdc38ia2SPhcAxbONG25jlJgm76nKfH8CK9pxLATh/NAIstUH9PQjhjmTXq+SZyW7QW5wcvz5s53hHEAxoT7XKUsG+YME04SRqdbVxbyXa/weVaSQaM6qCMWR3W8qfKlRgCOT2DuzLksSNPwRE/3w9xJ7XoC0/XAu5kzkU+HOaGubCFvav2VtSXpN7xL3SvBLbYDe7C4eJdal/tcGetpDPDKni2OoJ4A4FDbmziyrr3XjtMyLCfMwtQCHi/me1kvrdqLHSI8XgA5wl03NXjeTHTOw3yWE28m+SxhOx37WW6IZ7hj+Ha3i/hhB/DHDxVvzCB/19GqbYpBeIIozjLPcgmP0AfPSznwEF9B3wWznLjGfdT0gtIdcq1qQ7SoyogNMFWy3QzsAwt4cIrd3vX66JEp82qs76L+6YEF5xFX8CXgKkg5gWVN6P1horcH74ZgHeQ6QaXQw3VSMMYlaa8s92wzTjxRfB5PS56+qOtVlee4FcR2HCdC5Zm15eU29T0VZX2DfhuYVfIwTDnf67Es8rZ/k7arbSdp4poWZ7JacAJLnBnJiLm5Sdu4Bnhkh5HvBWrNji/NnW0vsRPU6/NUisAz8MBuah+QmWboJJHLZWCvmJbdQkqBPzgOd5M6RIEJR41Wy2AvLpVn8ABznKg8R1J4Howy2wIWgVRiLE4AlsZYNGGom62Nrumh6MuqPMc0csdMbMdteJs93z4PzyisQZjRwQT8MCdjhIHPV8WXv2WlZpbaje+n/BEWVxtF1i2iF9gRJoETJw2izpWClDXEGFDijY3vobKc0AWbxLzhHU/cjYMw2OOq9nlvUeUcdZOWl0at1FCnpkm01yVYP2OmdjDvqVPSpJhTuyr2eBBYMJl4rVLucdbhSg70q7lA8FYOQyP2S9kEL97nJrYxPK5E6iMe2mB9mmPIwoj7YIxfD/lFOA6XQnSSlvG9dhBZ+OSnltelGProV9kjvmaQlEfeYm5zOq0b3ZfPDNZh6L78BsWQRzD0FdvMMaSNYEAocv5Vi6H6LA3VYag+t2sxVB9nmGDIQ+ez0S+3DkNz+X6vFkPbOd5ah6G5yC7XYnrydUy1d9xGsFwr6lM8vl3HqD7FlyhdaqS+KxUYZUzTNz3EfW5HHa5bbNNVveHcr+PKq37EfHpXFaO/D+a7qxjmnTJ3rqOe8WoxtKzP7ali9HfG06Mapvad8fTeKk5/Z3z1k6uY+nfGq7W45nfG7j6GZ0B8ZxQ0uAtEGsRCgdR+yjv74n6kNb5BYuy4McAW5+rKOFd9m5+GGDr2FMw1iaF9XZ1zHtMwHCHntt8yjP4eKf3kng704ozfrO/4AQ2j6ftZgtH0xTcxitH1vcwxq7PqfDwg808/U9JpOfJbvm9cYPhqrchfeBajwX3n2+H7sRh2OB64T1RBPw9ZWPXK4vk=
*/