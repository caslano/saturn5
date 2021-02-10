
#ifndef BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::set_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
6nav3PJJx2+lpUkg22ZzSBviGgv6sVBuHv5BWubF9mm3fi7XeQG7x3S2WPwBFp9pLB6UYAITzEl/kZ6aWhIwTV1zdAATfoqDTCJIV9kKvTKW+XoXOfbl6QRfK2pRqrr9CKg7/Cb8IIu2IpS0531jsamNRdXbrrdYcS2nQkmSWLcB5SN6JR8HB3FnI7nloiLx6Vzu8T6CGc4imOPCj3B5yOLT2CFP2tTU2lMeETZjoAQ61c3HBAkga/mBhiKHjDf/1XfrEPEAQSbU4cBbOYgs4/j67zYvNtny2rOz7a7AaY+9k14aEto1MH0Lms5vpLrP00hh2BfS9f6IPg3yvSU99uFqMvhOrtorUyl7BewrYJ1Ep5VVQjVJuJoI/LUE3wiyVZ7j4B6F1xDBc7kpfEdnFotHqfj8un4BUEsDBAoAAAAIAC1nSlI8qILFXgEAADwCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODYyVVQFAAG2SCRgVVJbb4IwFH4/Cf/hRGPcHgyLmmUjDdEQzXxYQMBlrx0cBxEoaavOf79yCW5PbU/PdzlfyzQpnXBFLrC8OgqznOh2FTJVLgR+sACvIC4xph8NsR+Ad4hi/z3c7A+bKIZw682Xy1dg9h3F7I4IxjDG
*/