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