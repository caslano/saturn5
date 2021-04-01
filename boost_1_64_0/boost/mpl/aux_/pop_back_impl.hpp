
#ifndef BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_back_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_back_impl)

}}

#endif // BOOST_MPL_AUX_POP_BACK_IMPL_HPP_INCLUDED

/* pop_back_impl.hpp
ZXhCO+IpjXbnBl88+ol3G4ElmmdVXZr3ggfWNyVy3ZMmGge3KINCzfmRdgiTwMFzmcoQr9srfkbQAnmdimKwxHdrxQlfkfsEOIZgN9uMv0YHNyy8Cd9+2Yt6ST/j3djUR72o9HYSX1XliMIOW5OjVtcFcLSU0hjRKKLIJC/wOi93CymT/IrxSqQNr6T9Y2xbGGYGgBauY2dmKrZNF/ObsK4DcW2vUaL+2iVieb5wEpYQgk3qzc6Y63nM/AQGFQlAEBe6A8D5CI2QszBRN08qUW6LAAndfjFk+VjU2DwsHkbFybsZnIB8i/egJIwma2sZr7W+esiqrxA4hEt6Zv9pbmACCnU8+Dk8OPEQ/q8aYYF4tCRK3o7K1lCVK3nIMSjKQoubOe83rIM8yVIz+3+TmyyGSOj+57f/KSQ2xRWowL4ogHXItkbpVKQuISlrJABhx8xFQMzlpb2HMNQsKVRgLP5L0SDOjimzFoDHi9xyuDmWjsMgFsgCtF/rv5qEISBaPiSwaUTwPgNd8c6+PyDQRqg5G8ixm7XsqICfN/QvS0yETkaEbk/oaWfaQA==
*/