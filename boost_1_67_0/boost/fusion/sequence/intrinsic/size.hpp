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