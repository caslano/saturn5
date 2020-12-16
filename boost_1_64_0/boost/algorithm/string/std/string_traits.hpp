//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_STRING_TRAITS_HPP
#define BOOST_STRING_STD_STRING_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <string>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  std::basic_string<> traits  -----------------------------------------------//


    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::basic_string<T, TraitsT, AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true } ;
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

        typedef mpl::bool_<has_native_replace<T>::value> type;
        };



    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_LIST_TRAITS_HPP

/* string_traits.hpp
Cm7GRjt+gtqZm4HQ6Iv1C2u3BdLf26P1E4Vas43a5wrs+LIXQyr/Pjs+7T58uC2KW+RG4x9AlFN4Xwy5+AIg6mYhF6QWxOIl95B7PgEYJ17KDZlNvFlkCG3saRpJ6r7VwJYMtDgA7NEI2oc3FMEXsyeIBZRQcFMIn89+Mazaw5nwUnASqjMar3mR1WglcTNsdgA4soUvoqTd+LTLFwGRVu+wS8jqJw74SkL4Y13aZXbX1zyMb5rFF75IksJ2dnAEm3Vpj21+SXy2D7iElE/Z8TEqPjsTd7H45HstdaJQo9pBDVZSCkIm1sFgpsgdQuuZCccAYfz8+7B3pTbxBoIahtWiemGQQBi7c41o/EUsEmciO79EZKvWCP6s0i7+4JMQ8AYvk+eAGWBKJhbVQAbp2SpgD+aEgvn4qO38F812sAOiKAEtUbXwPqYHOzaAMGFrxauygUxY+T4dixd+mqkAOUcjAtXfBBFoASIY6VBmHlbEaHsA9qlBben5I4CkUEboB9dzZg6ThNDChrBcckJGZsgwZLNZo0owcWFjA7tkMgOVYLeMgChWa4Zrg74Scc3qJCMBEFAuCGrZfbWJQaxfCRLRvTYEM5ASkAFivJTE5xx0CcGSOVshqRkTReaRmRuc/7BIAreCPxEKE0krU5fIwqew+JjFRr8ylBmuhZ1rj82c3kpu2wkFJ5Vo762Gw3nbkEZ8To5rQz62IUiOFepvaFO8KnmoHIYgMq8V/kMYQlA3O33Yjd+VAW/VwbIkfAW2N7hatV4oQT3sORoUMsIPhzLZNNinam8fCoIeWFMURgLMapv9RI2lhkGrSNngjmBChBWsE7YSg62InokkQBSLoU2oYUqIJJBCYjCgh29qGzgyIfPvdulAAjoBmh92xRE292nzCPaDlvy0hfjJQnweC2GqiA9oQgI5EYvGQBqAoEv7CGOigvaApU3DpUHVPCxkgAZQchgZQ8JiFL6jEFHrEgFCgYTHuPtEDOApehcDXRUkgYMztrCPajS70VGhyO1K1qIrEXNAT+Liv1/jTwYUUnCWHty9iLvahAwTGSNImXAWmJFforpgANqC3Q4GfS0MBCEcdTXom4COWqtRt2vDXywmzwuHnPKxhdzNZGFHLaioZfNwpKtBgRbCWtgTMCMiaA26Kgs6VFu7r6Lgns/vSyYBfK3CwFzN/6EFAjH0DNMeu2WP4dXZkMIo3UiGVM0vQ8ZmVfObsPGaWvZ7Y5etwn2W8UZUfaQVg/r6kTKsj/hkaH+xX4b3l2NJGi3rbwjQMP+GQpoHCNXfUoQRf/0tY+gbYncZu+ibxDRVIJ8AbOOrTCfYyJcPFWLSga8yDQGMJ9C8eOPneV6cZjKshQvfvsmS47/jv+O//6sf5svpq5zOI7WpCdHP9rmrhfJZ0kas4L0KV1NGHqiBFjcXfvUxxLJjA9lDEcKH5GVcu4HWO884/cvvi6om/R5wt91Aq5/vzrz8M7zGJy8KN9BS6IaXzxpBt+V2Ay2JXnOaeQ3dVtgNtDR69+xf3Uu3tt1AS6QnnJm/iW7n2g20VDrW/vUsur3MbKTL1fwONdDdBQSdO27yvPsbfAhLjBvcJcblC1Lv/jJp5Epr7mdXSjx4WxYY9fz/J9Prsw9jgj9dnmZg6/KnUkytz0xzz663/Gm24S7gZZhV5OWXVexll1Xq5ZZV5mWWVU68sirwZ9cvRx8jayFvnWKhr2Z5mr4CrNserk+X6Boqe8b6o+hTBeuTf9Xv9tCCDPRpV9YAfZr63fY7aY1mgD5N7H/gIK3YePVp93lj30PLN1qfuj/55x/TMo7Wp3HXvXMiLedoffrw49YBWtbR+nTLKbcNp+Wdo+pT2Q0=
*/