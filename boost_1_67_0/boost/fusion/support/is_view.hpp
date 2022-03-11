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