/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEQUENCE_05052005_1002)
#define FUSION_IS_SEQUENCE_05052005_1002

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename T>
        struct is_sequence_impl
        {
            template <typename Sequence>
            struct apply
              : is_convertible<Sequence, fusion::detail::from_sequence_convertible_type>
            {};
        };

        template <>
        struct is_sequence_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_sequence_impl<boost_tuple_tag>;

        template <>
        struct is_sequence_impl<boost_array_tag>;

        template <>
        struct is_sequence_impl<mpl_sequence_tag>;

        template <>
        struct is_sequence_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_sequence
          : mpl::bool_<
                (bool)extension::is_sequence_impl<
                    typename fusion::detail::tag_of<T>::type
                >::template apply<T>::type::value
            >
        {};

        using detail::is_native_fusion_sequence;
    }
}}

#endif

/* is_sequence.hpp
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
*/