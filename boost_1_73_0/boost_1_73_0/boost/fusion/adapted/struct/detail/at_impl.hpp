/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template <>
    struct at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<
                typename remove_const<Seq>::type
              , N::value
            >::template apply<Seq>
        {};
    };

    template <>
    struct at_impl<assoc_struct_tag>
      : at_impl<struct_tag>
    {};
}}}

#endif

/* at_impl.hpp
0dUg2ILe63BgnbxyZwe/9l9PRwO7LAEupQ2+juHsU/Ua/g7wFcetRLhgVjh/+Cnd2lmN8Pof3H9QkBmRtk/SRdftSG7WftIqVfUCZ9AfqDm+VNBwfuFm9KETcQ7suXmI33iqe+9uz2ol59ogcDHAc6S4UGkXzz152cZFbxd4aS19ubX9JZz0rEWx7FrpF7ZPeoF9+/P5PD7F985DUI2dsM78Z3B4ZC3vWUHrqOXU30+rdfeLfTd+33jxRy/0m0rrTO90o8/59mLz6PSBpR1FaPTYZcH7uyP1T3C/5nadouMYkebIgQTebZfuTh4K8eHCa298ZN9NFz1vYuV2DyAKObC2D1qHPCs85M7/aJZIIwQPyN4X1git2Eth8d+JBwPoj+IJvoX8OHsoCh3kiBA6myczXBc2byb+4Z6o2yceHPkXUEsDBAoAAAAIAC1nSlJfiuvscAMAAEkHAAA0AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9YRkVSSU5GT0RBVEEuM1VUBQABtkgkYK1UXW+bShB951eM3JckopA0ldLeG1WXOLihpYAAp7VkCa1hCduuWcQuTizlx3eWj+YmjdQ8FBsvrGfOnJk5s9Z6Bkd/7TIsDQd/vLL+zvDC
*/