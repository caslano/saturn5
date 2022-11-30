/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_05052005_1126)
#define FUSION_VALUE_OF_05052005_1126

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct value_of_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template value_of<Iterator> {};
        };

        template <>
        struct value_of_impl<boost_array_iterator_tag>;

        template <>
        struct value_of_impl<mpl_iterator_tag>;

        template <>
        struct value_of_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct value_of
            : extension::value_of_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }
}}

#endif

/* value_of.hpp
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
*/