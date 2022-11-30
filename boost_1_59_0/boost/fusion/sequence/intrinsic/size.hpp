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
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
*/