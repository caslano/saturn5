/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CATEGORY_OF_07202005_0308)
#define FUSION_CATEGORY_OF_07202005_0308

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    struct incrementable_traversal_tag {};

    struct single_pass_traversal_tag
        : incrementable_traversal_tag {};

    struct forward_traversal_tag
        : single_pass_traversal_tag {};

    struct bidirectional_traversal_tag
        : forward_traversal_tag {};

    struct random_access_traversal_tag
        : bidirectional_traversal_tag {};

    struct associative_tag {};

    struct unbounded_tag {};

    namespace extension
    {
        template<typename Tag>
        struct category_of_impl
        {
            template<typename T>
            struct apply
            {
                typedef typename T::category type;
            };
        };

        template <>
        struct category_of_impl<boost_tuple_tag>;

        template <>
        struct category_of_impl<boost_array_tag>;

        template <>
        struct category_of_impl<mpl_sequence_tag>;

        template <>
        struct category_of_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct category_of
            : extension::category_of_impl<typename fusion::detail::tag_of<T>::type>::
                template apply<T>
        {};

        template <typename T>
        struct is_associative
            : is_base_of<
                associative_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_incrementable
            : is_base_of<
                incrementable_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_single_pass
            : is_base_of<
                single_pass_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_forward
            : is_base_of<
                forward_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_bidirectional
            : is_base_of<
                bidirectional_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_random_access
            : is_base_of<
                random_access_traversal_tag
              , typename category_of<T>::type>
        {};

        template <typename T>
        struct is_unbounded
            : is_base_of<
                unbounded_tag
              , typename category_of<T>::type>
        {};
    }
}}

#endif

/* category_of.hpp
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
*/