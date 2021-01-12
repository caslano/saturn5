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
4b59/DlYvHXQAtdL+2W247HE/lo6z3Vw0/i8Nz5udr6b/48stj5/PeDfD72u/XChz58Pmjemv+a6aH3wovNlic+Tt1vPHPvY+FvquDZ4/bDrZKzzzP5d0uB6XOJ6/KJxdaN1t+O72Py+29/b4jwuGLHum2r+v9vzZXq9Nuuh8XWl3fomYl77hs+NvuS+Y4b5/7B541n70Tp+WtD8blwfGF/vHNejb07wc3P2k/NmlnXRvlMc
*/