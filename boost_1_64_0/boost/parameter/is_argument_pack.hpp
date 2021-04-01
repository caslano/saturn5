// Copyright Cromwell D. Enage 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_IS_ARGUMENT_PACK_HPP
#define BOOST_PARAMETER_IS_ARGUMENT_PACK_HPP

#include <boost/parameter/aux_/is_tagged_argument.hpp>
#include <boost/parameter/aux_/arg_list.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace parameter {

    template <typename T>
    struct is_argument_pack
      : ::boost::mpl::if_<
            ::boost::is_base_of< ::boost::parameter::aux::empty_arg_list,T>
          , ::boost::mpl::true_
          , ::boost::parameter::aux::is_tagged_argument<T>
        >::type
    {
    };
}}

#endif  // include guard


/* is_argument_pack.hpp
rBwwU5tsaDaDLYOd0fqHLKnugXa0zbwZwMnZJBQpDs9lTn1wNV864Pej5btQMENJiE2ngI0uIkylSq17DbKK7oNk3xntxq7SiN/wH/3peCsY5yyRQgYMZGp757YWJeUCCTnMzUZmPnY3b8kQuza+Z5S6LHJ95XWl59zEmzqPaeRSsGK++2YWajcDHaFMskH3P+41Jc8GvglVokY0Wi+UfJf0F2NOo/LCo+fn3H68DVYmNR4mHyg82aQDNJALhucyAKKc7p04fX1ndjvpoK8fmrAoEInl5IeeENnzaxppix21kCpwRn+tEFrcik9c1eTQifmxqfj5TpGS32XoZheeWzGhHhAJVLPgPrBXSSMZIR3KYs5BNKDhGSwK9jaHvmEWvgeQuoCkP1zNoGwBU9tCMXt2viz7YOLutd/paHZDGrdYSS9tPvt2Pr51UGXEGtbmt3Z2K0y7uASsNX/utjpv57J5aTIghfnoV5UO1pxxi9N33Uc8UHCuXhNqVf+UTFVICB8+hIumIBpNL5qTQpbwhbhKQC40C+cgkvcB8DDjD45SxVridxekTIB0Hg==
*/