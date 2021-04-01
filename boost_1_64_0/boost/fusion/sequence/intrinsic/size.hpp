/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_05052005_0214)
#define FUSION_SIZE_05052005_0214

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_size.hpp>

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
        struct size_impl
        {
            template<typename Sequence>
            struct unsegmented_size : Sequence::size {};

            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_size<Sequence>
                  , unsegmented_size<Sequence>
                >::type
            {};
        };

        template <>
        struct size_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template size<Sequence> {};
        };

        template <>
        struct size_impl<boost_tuple_tag>;

        template <>
        struct size_impl<boost_array_tag>;

        template <>
        struct size_impl<mpl_sequence_tag>;

        template <>
        struct size_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct size
            : mpl::int_<
                  extension::size_impl<typename detail::tag_of<Sequence>::type>
                      ::template apply<Sequence>::type::value
              > {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::size<Sequence>::type
    size(Sequence const&)
    {
        typedef typename result_of::size<Sequence>::type result;
        return result();
    }
}}

#endif

/* size.hpp
rxgtGojQyVJil34+akrqCjfEK3ZmCBQz7PUC1Tlj5tW7wRME0DCobh7oJlk/9F0AOGci35PfeQn81j3TDtU5eGN3Y5Z/2tNA78d0PHuH72qPF7nEMhlOvUI9hBl/uZUBlCTAfemtgTuJyeER8qAWcaRxzhG9R9lHBPXN7qFQCaC85wo2dojHLUJN5E/sL8v4x0R0zalwb2qO8dr5qMk3eeHBB8hxasYEmR3ZcpljFoQfnqsWIpDJyDwHVLL2bKhlBjoWJXz3ECjjXbt03gSvw+sAiqRqxxccc+kaEk5YYuoKX4IpqbD2nxyK2VPJaMJkOySnYv00dK2GXzF/IxszUo7dy2iUQWTHfaL3cjqWb4l9i0pwQLmRHE8wp1eikV6oc/d7FFq3pzd+eIk2ETVbMM/GHbS7LEhsd/dSC+y0qzSynE0ym+/L6bGHmsXfp5yq6ngDmb5CJm+3RX0oP5Ec1NUGCH0+26GeQUcYyVV0JYKINxSvfkq6cCnAm5lJkKDUP0zbKnOVZCbKaiUhtwNvgXN6m5hWstJ7iKlEagPj0K37i9qMUJqtrPZmGQ==
*/