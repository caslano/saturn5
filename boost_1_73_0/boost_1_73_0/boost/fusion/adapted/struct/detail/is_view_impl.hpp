/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : struct_is_view<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct is_view_impl<assoc_struct_tag>
      : is_view_impl<struct_tag>
    {};
}}}

#endif

/* is_view_impl.hpp
nLx2a4EmSBrnrUSI7i2LUgHOOR47Zkt3GOwrf+n9edA5/stxfH+9f3sKS9JYG4/QCUoFxuXGoIMMXqksoFSHyAvbGFLasMxhB2blmpEo7pk0qxV5tNFvtu3ERimL7oy5CIdaWpShkhG2pL3Z2RlfmZ3u4y5W8O4dZApu6cMddEYu7P/mz/5YzCbDYOibMf9vgMF4Og58+AdoV1Ur3CMtx/ngwnH7FErJCw3NwfXVBFdi2AQKTe+o+e/+d7r1GrQnzOaYSW9tWZ0Ez7xQs7zc9FIiAx6Cryb81GzsTX8dCr1eDTfhgrVJQwk8+eog9MxTXi900sDKjLX3OOt2BL3gv5OQT6TRwfMKp6J6nfAdBO1teV8P7Ej8B1BLAwQKAAAACAAtZ0pS/EkeM0MMAAAATAAAKgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL01ha2VmaWxlLmluY1VUBQABtkgkYK2cW2/bRhaAn+tfMWhf2oU3dtLtoll0FzsiR9KsKQ7DGUpWEWCgWEylXdsyJDlJgf74PUOKijl3AnXRSnH56cztXOco3/3lz/u5+A4Ff2Tzr4QfeFVAsd/9t7472h+W8g/U/gPQe3gNiLhCX4k/5A8oSPyBvm8IeZLxi3ovZUDMezUw
*/