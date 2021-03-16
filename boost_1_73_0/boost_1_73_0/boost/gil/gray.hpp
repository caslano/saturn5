//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_GRAY_HPP
#define BOOST_GIL_GRAY_HPP

#include <boost/gil/utilities.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost { namespace gil {

/// \ingroup ColorNameModel
/// \brief Gray
struct gray_color_t {};

/// \ingroup ColorSpaceModel
using gray_t = mp11::mp_list<gray_color_t>;

/// \ingroup LayoutModel
using gray_layout_t = layout<gray_t>;

}}  // namespace boost::gil

#endif


/* gray.hpp
UNobWn2qBLii5Y9Uc6HFv1FqCyjt7hvOiCqkof98xVFVai3nAyEaJC2jqG3sdcTaagAKfeijCVwjjyHwwy5pqBmw7k6OU/D4yVzBQ2hDk6hBSJx36ZXfbdbM+WERMa0twaTV06XO3IgzXsKnpDosgpxlv3J4qw5VTynawaxcqnTmcFbWqjIbT6QnU7wFx7D+bomwLuaBkSBslYi4M7F42Oc8FJKqcd9aZ2cQV5H709ZIIAIT4UHahT57G2IhQUc=
*/