/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_04052005_1141)
#define FUSION_END_04052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end.hpp>

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
        struct end_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_end<Sequence>
                  , mpl::empty_base
                >::type
            {};
        };

        template <>
        struct end_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template end<Sequence> {};
        };

        template <>
        struct end_impl<boost_tuple_tag>;

        template <>
        struct end_impl<boost_array_tag>;

        template <>
        struct end_impl<mpl_sequence_tag>;

        template <>
        struct end_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct end
            : extension::end_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence>
        {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence>
        >::type const
    end(Sequence& seq)
    {
        return result_of::end<Sequence>::call(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::end<Sequence const>
        >::type const
    end(Sequence const& seq)
    {
        return result_of::end<Sequence const>::call(seq);
    }
}}

#endif

/* end.hpp
LKWz2Fg4KorAxThFbps2YbSzJwphKDlj5cPkjHZBaiXN4lUg+xhY8spqFmIfOCgzbHOEii+VrYPryvcSO09rg//Zmpd8MxjNyeBda4Te6B1mwikX4bE3vhtMxnhsDYet/niKwRe0+tNA9rXX73DrFYtZ0Lq05FjcQi3KQlG203y7ETf49u8PRWnNjDu6wdzwSWIzQsl1G1JIEsGRAGgqnRZVRrgK7d72XF7XRHPSZEUo3NdHY8WF8HEpQMLVLVehF0xCa/ZVg42q+NYHiiSEbCPQ/uPZfft+GTTz8C/X6d5Mbm8mvftOgxN8HZekktKfR0ujsuPLRpM0n6b99AtQSwMECgAAAAgALWdKUrup1LdTCgAAiBsAABgACQBjdXJsLW1hc3Rlci9saWIvZXNjYXBlLmNVVAUAAbZIJGCtGf1XE0ny9/wVJfuUCQQCYfUUxL0IQbMieCGcuurL68z0JL1MunPTPUBcvb/9qrpnemYCyL53RoVKTddn1+fYXvt5nwaswb2fkf03wg/+thTvUvUnD83tp0ejb+D+INVn/H2fkDaUJN9GTbif5BsElmSUS3lO8Gh0n6DPpBv9aBPl5xGBiEEyojxQ80UqJlMDwUETtp89ewob0NnqbLXgkEnBEzgzXI55OmnB88hi
*/