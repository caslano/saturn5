
#ifndef BOOST_MPL_EMPTY_HPP_INCLUDED
#define BOOST_MPL_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/empty_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct empty
    : empty_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,empty,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, empty)

}}

#endif // BOOST_MPL_EMPTY_HPP_INCLUDED

/* empty.hpp
M/MHkc3vuZ+LF6x8Nlp/hKr1FwfS/yIpFW7amBlOTrWNEINrpqjQsfRsFQYJ0zR/tH6BRZR+xaQmGb8UNG/WlsaXniRGIX70sTgUnOo5cpxe9754P5Q10H2YeK1bv2KglQ4rD9KnXlAyUyZUpVYRCBRNNaDGQFRw3Uk7MUvxg19gBtAt8HtdHzrrf6qGX/pgExgV4AocAlJEtrJz5EM6tdb8MiD+pSYYCCv7RfaRO3azmicqSpw15HWvk95KfrK+OeV9tFnekVZ1jWAd/3ifTEfeHWop/dMyjJgPLv1d2CrZgeKp5Q2j4oLqoVCsOUur2U427AzAwTt7xiVyXwXZXAtdPRe/RkxZKe8cznK7xChzmmDdx1qyMH/JV+f+1pmUi0+3eY2HUyWKbFdfNKCxsbMXlse1YnFhbgxA+PuZvDoEH990Oih+4OImOgS83AnQxoF6nk3PJ6V8gbqHcT6eI/L/2Y6+9lUTdJ+zneop3YD+cnufcBnsfOAfPrKhQQixCXIPqXXNO8sldi+Ev8qrgyBEPTl3dNBd9WT7pznrQZ+5wv4MSIVJS1oXyr73p7jy2qbdtt5GIX/8yeFRR3HyehYouA2/LbFNuS0PzAqMAU4O9tkV1gDtgGAgITAHSLnNyFFKfIm1bW9I54DqwORAXI/SbjA7+TOHrfl6Op5Ju+5DqOwaatE6Aj9sN4oHxhPtNouhUA//Yw/ZS7ij
*/