/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_INTRINSIC_FWD_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_INTRINSIC_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <typename Tag>
        struct begin_impl;

        template <typename Tag>
        struct empty_impl;

        template <typename Tag>
        struct end_impl;

        template <typename Tag>
        struct has_key_impl;

        template <typename Tag>
        struct segments_impl;

        template <typename Tag>
        struct size_impl;

        template <typename Tag>
        struct value_at_impl;

        template <typename Tag>
        struct at_key_impl;

        template <typename Tag>
        struct value_at_key_impl;
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct at;

        template <typename Sequence, int N>
        struct at_c;

        template <typename Sequence>
        struct back;

        template <typename Sequence>
        struct begin;

        template <typename Sequence>
        struct empty;

        template <typename Sequence>
        struct end;

        template <typename Sequence>
        struct front;

        template <typename Sequence, typename Key>
        struct has_key;

        template <typename Sequence>
        struct segments;

        template <typename Sequence>
        struct size;

        template <typename Sequence, typename N>
        struct value_at;

        template <typename Sequence, int N>
        struct value_at_c;

        template <typename Sequence, typename Key>
        struct at_key;

        template <typename Sequence, typename N>
        struct value_at_key;
    }

    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at<Sequence, N>
        >::type
    at(Sequence& seq);

    template <typename N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::at<Sequence const, N>::type
    at(Sequence const& seq);

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_c<Sequence, N>
        >::type
    at_c(Sequence& seq);

    template <int N, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::at_c<Sequence const, N>::type
    at_c(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::back<Sequence>::type
    back(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::back<Sequence const>::type
    back(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence>
        >::type const
    begin(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::begin<Sequence const>
        >::type const
    begin(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::empty<Sequence>::type
    empty(Sequence const&);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::front<Sequence>::type
    front(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::front<Sequence const>::type
    front(Sequence const& seq);

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segments<Sequence>
        >::type
    segments(Sequence& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::segments<Sequence const>::type
    segments(Sequence const& seq);

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::size<Sequence>::type
    size(Sequence const&);

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_key<Sequence, Key>
        >::type
    at_key(Sequence& seq);

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::at_key<Sequence const, Key>::type
    at_key(Sequence const& seq);
}}

#endif

/* intrinsic_fwd.hpp
/opo50P884kubcLWPdhYzeFcx5FoXQJIvQn/KLneIR194Am6m2kVeG/2ugJfojcD10+772eTcv/CrTnu0qjGBagPu326hbRwl4N3uct+BS0Uble4XRKTcP//DmrQ83L00XShMXmL+fnSdPFIea5wl+tOz9bvcuu7XLdYLOTeldSN4B6cKRUOzc2Sr25utuBoVfen5v6U3J9596eOPxX3p+H+LLk/Pfdn1f3puD/r7s9p94fyLfv/nwXxLpPyp0n3Z8r9uaf/+a7R/98i+nsr9zcWO/eCpK6k3NPVQrly1+LskflDkdwbkQAQZU2L18ZvbfCG+GeLszyh01qJiEi16wGIVnyil23yAVK2cmF+bm7mcGn6rgV80eVMTuHfgzh9IMsQO1W1K0Czpbm1l6UpZJk8VCxUizPztcN3nS0kaljsRXroy3Ddx/rvzqoyHC7MlYrlmfLcnCnD/6MnRVMiqyxejjNejtcqOYqF2pFyrXxkvmjk+B/TX0TdHQelzRnfJVn7ny+89p+vLswVK9GcdonLXJ7m+OYPXJ9dG5zM5aK18fxV3BrX7wmk9fAsPV5cp6mkQpZag8y+UjRf02jsLLrp0kwyBm/4OTP+t1/jzFVnliol2C+N7okTjSHPg7TjvZv8+7rxnEGDePzvT9D3s8UFCjROuznDlSlYIszhOcLdpODn60/R92vHB8PoAQJvK5y6SsZ66RZchkarfaYxJL6fR75L/7vveXbMu6rHN89zuBpPCbtBhC2e32Eb6zRur7bX2uvyneBmNJa210921tvxjbK95ZZ76YkqJZH3qZdx82TsaSUHtbck2cZ/doT7oH9qnTK8fIQtldPLam+f/prqM+1RvSp+T3vmyKdE2D/jedtuMEficd4vjOWC8x6Ghk/n5TFuNk54KwBluGjME05UTsml82bkk360COmgrMob6dOfQPrxpux0/lew+YPh8KsaXNuebyfcCReF8H2a7xEyV6rVuy3VtA/ow4xzZr7ers35+YaJHdzptr++LRdwl86Nw+mYdvpoRv1K3nWgF3LjOZQCdXU2pY8yDYd/WuuMl5nz+AJwGRDSa+/vECdSKp/mOP4GEQ+QjV6wJ9t996tUv0vLumdlpYbievtzRr2l++B5NCiKTgC/DuRKn/bw6U9ltF/aB3AhpM87nHTZtXfd/X4R+qZ0tNYg/hHfLaP6v9RlUSYO6KFASm57GiPpT0gDj8/he5f3lQhXu8x8218D33GgVRb2ssgbFRJ9d6PQd8jT+3wCHN8RwDkYLjvlz2V/iBlvtU7c6TJm7DTE64Bn+pIad2ZiDgemU+3wB8Kzdsm5PA6H80ChHec2lw31Ny3HnS6r+pdU71hOxuX4ifFxlnAuRFz+Cr5B4NR/xP12njh6p2D8e83/jl2I3hZYpN/Rmb1sx6xsTnyUvxkuPzi6HjG1CM1BexqOLw84/6HsumPjaKr44SQQumkfoQcIvZl8CYSa3dtyu3fbiA2EernYl/jAPh++MziAUAQIgWhBgEDUIEAUIQgIRBGggBAdgUSLEEJBIIgESKH8QYff7M68mbezR1E+f3H2vTfzpr9588qq3WazHDqX7cmDuaX5sMFUStXmxJo3fA7ntXODyNmeQZOG3iA+ADrLulPSzFqSRint5Ho4c3tLBmjca09YPPO1+Vy776x5ONY4lhwh4Nsabskh1G7y/NL9/oJ5bWiWtchri4+p7YlFZyqfN1a7XsTXnzWvXtK0b1HTKx5epnGs8l9h7ddEW66rZ2BsaLLINh1iZxot0EpnCXzr0JLz4bXUl3Rc0VCYPL3B4okw6Axq9KSTe8GvwYMmrup+U3Pd1hp8K/CswZawt2u+NJ0=
*/