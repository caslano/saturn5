/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template <>
    struct size_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
          : struct_size<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct size_impl<assoc_struct_tag>
      : size_impl<struct_tag>
    {};
}}}

#endif

/* size_impl.hpp
VZD5ghcZfCqqxzYEpemxF0A/+eltLwK8UnPa2h4PiD4cX6ngHQti3tuyueVGZWuMqLOSNs8B/+uOGN7ZLFqVc8/K+nGVPmneOAbbxsl1MdhgYvigAr/WT80l5Cp7OtvYe9kJAl3LNFGzxk9uCuja2QH1oADhxnzSh+jN2vnDhvHkDkTWixFlfoutvm/x3XYSU6MJA+koTwCoIwvUCBlf6auX8SD4ovR6GA/GJANp6x2pStvRQJCmHB+jeUV5t6Nd8f7LQjES5gaUBrBlMzMJYL9YeOuiQAZddVoWpWH27TBPHwr5wTAGNx5jcINys82ICJQGBkDgllgxKRgwDSShn8tn378OYOo+mxQIU1c2qSlAaVG315Obrc9cc9yVvIU2ytsl9fKW5ay4DZeDO42rVwNSNmRH5jdqvU3h7qH+9XA3+32URfcnajy85HNIs8b4nODFwJ2iyzRL95Ok7mOJAfXzZSk38vV9VgBfQTzsDG+Mh1MvNNBWWdxWkauC2mr5C01pK2dWPW3lmYNt1fHj+tqqe6N89kc+G2mqxPrZCmqqD28Laio1nzWr5ZwwC+5dIhe88LwC4/nKswrQ+2oaBCZ2x0HgquM4CPz7T2s+P29ebAK93/C8CfR+/miC8bSA3seWqUDvCJnrQqijF/Go87heTKFMCCIYIdFn93ZqpbkIytrzNMzKrn+sBVoNyG3NlPWyIIx1C3qWstbU
*/