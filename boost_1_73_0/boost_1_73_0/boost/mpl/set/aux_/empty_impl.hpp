
#ifndef BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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
#include <boost/mpl/not.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : not_< typename Set::size >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
gTcWLnMpsbPoz7rClrxXX9HD/ok5uxMG9LapqQt3tB4OEzuF3varyZ0C8k61NL5ijKu7i2pqMyUhZ6MEubZtqzozQjaMLV4PRbkTm8XNLQ6yZM/rNS7PeI74jSftKMSsyRa39zpD0Xdy9emKRgWF6hTIYagIb3+NlfL4SdThzFc2zIBfBm1EkHPWaWtiofVTJP47897ZYLVtUthmIkvgWORy6JKAyIoCx0bJMCKMVRN4O+7KJFIeTs6mKPYY+x9QSwMECgAAAAgALWdKUqBaXNOWAQAAgAIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NTZVVAUAAbZIJGBNUk1vozAQvVvKfxil6jHyoWq6iiykiNJdJBRYQlbaU+WaIbFqbGRMsvn3O5A06QnseV/zQATsg5I9Rkxo2zh6fOL55HzdR6zIiycWG5QeKvwX2Ns6zXZlwgS/YwS/0NgDe4At+iP6Ra9rZMJjZ84E6KdL1dYRK5Mi+wvFeruFRVKWkLm9ttBIbQZPDP4NKviVPwnHRqMNV2E1HW7KEetc93RjRwyElS1e4oO2R2l0DWa0ohG/zEAo17bS1hf2ivPHX/m2SovV40gr8rLiP56XsBhgIN3VyTu7J48bi16vMaaAf9Dr5gy1
*/