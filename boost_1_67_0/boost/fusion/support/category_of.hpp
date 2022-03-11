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