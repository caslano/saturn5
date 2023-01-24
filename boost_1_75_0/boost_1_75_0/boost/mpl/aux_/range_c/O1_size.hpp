
#ifndef BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/aux_/range_c/size.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::half_open_range_tag >
    : size_impl< aux::half_open_range_tag >
{
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
OJeRGEjibt5mavFd9fWnjkpKSk9MmDGPjryNihpZUh1r6esXz5+RKcpVgt4WDEFFXc0bP05cIasSjKanrsndAb8cy43oAGGmVV8BeffHeQin/KXCKKo8FAGY6dErv6FWEYPGHHWadiX96gUG10FpbROGeXho+tt33wAy6lFPBHfj3eGVWb9WnaiztLkriUrxg1bjfLS/t59WOrikJTQFiaIb8K/t2NxyvbwKMto+W/n4Qny96d8ImF21ios6tNgBJUg/eqwwjd+cptOAesTq2FnhzzZTCcYWZWbayuD5Jt+Trh7PtsLWJrCizgQxRvmi+TE6AgWrSuckJo5awRIrOhktw7l2bXOHOBneWM/n73pGXz7RpFXSyE4Dbanlw+Gak8olgwMeQxt3anPjqo0aCMESUdsIjX/2EiyVNH2skhZzU3O0OUemMqINJRnFwVFxc6Y7PowVdUUkOtQCyE1tAoQaNi46ouOE8lYxY/JLRWd7T33hUwm7oXOiJ63pGgwQ4EY3tCs8e7Dsg8bulv6bGfmNBiybG7Kuw2Wv7ySHuvU4RY9PU+1ztxOefVZDKa/30rdk4H1iw8xPPpbjTR/fCtmouJJfpyTUdfqQRTk/HbV4j2IAikaE+Ljs3legl1NN98hE6JTLA7shBbKeP08C526EKRhoIcmk3/dKTpEvQvCZ83rQEWcCi1LtnaethKt1rbtWZ3bVZZRLTaWs
*/