/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_VIEW_03202006_0015)
#define FUSION_IS_VIEW_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl
        {
            template <typename T>
            struct apply
            {
                typedef typename T::is_view type;
            };
        };

        template <>
        struct is_view_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_view_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_view {};
        };

        template <>
        struct is_view_impl<boost_tuple_tag>;

        template <>
        struct is_view_impl<boost_array_tag>;

        template <>
        struct is_view_impl<mpl_sequence_tag>;

        template <>
        struct is_view_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_view :
            mpl::bool_<
                (bool)extension::is_view_impl<typename fusion::detail::tag_of<T>::type>::
                    template apply<T>::type::value
            >
        {};
    }
}}

#endif

/* is_view.hpp
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
*/