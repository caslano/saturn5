//
//! Copyright (c) 2011
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NUMERIC_CAST_TRAITS_HPP
#define BOOST_NUMERIC_CAST_TRAITS_HPP

#include <boost/numeric/conversion/converter_policies.hpp>

namespace boost { namespace numeric {

    template <typename Target, typename Source, typename EnableIf = void>
    struct numeric_cast_traits
    {
        typedef def_overflow_handler    overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<Source>           rounding_policy;
    };

}}//namespace boost::numeric;

#if !defined( BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS )
#include <boost/cstdint.hpp>
#include <boost/numeric/conversion/detail/numeric_cast_traits.hpp>
#endif//!defined BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS

#endif//BOOST_NUMERIC_CAST_TRAITS_HPP

/* numeric_cast_traits.hpp
FatBd4iyOMYRPtkfgLjGtNn28y7qnPmD0WD2t4CbzmtucJZstGR8OfNxcYFY2NnVRuRAJFXa8OUfN6ux/2rNesxwtovjmm6QCOdXPehFtqBhdDGbXVJoWaiAf7tUx9EWpHnNeERJZbFdeOUQ+08Ooz7eCnTzrapJ5cfZKRUW3HTA3srBXp2N5xTrOeANQQZH+pB0t+TNOX1bnVP4GWxabTgFW2S3ONdC29lxtCiuP+nPriYjPGH9yWQ8+XyaPTlKcdzHeBMnGySrb4AdOltn8RnpHcyntY+GUf/64HnqsBDu/+NhWd8LB56Mr3YpfB5lMSTfuP4fCTa+X3xr0/K/Q4DNrdOtHtab60nzV1E5d1ai+ptnIywFihv8d4GgdayP1idQSwMECgAAAAgALWdKUiPx9oMfBAAAkQoAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1MzcuY1VUBQABtkgkYLVVYVPbRhD97l+xUSetzAhsk7YpkDRxgKY0LmZsMxkmZDRn3cm6jHynuTthU+C/d/ck2zhxoJ2m8rCSVrtv377bO1pb3+5qwBY8esX+L8YL7z7jzOhPInGbo+P4FqofZl3i/bEiLVil3MZNeDzlFkKfEtdVXtBzHD9W6JK4kWlR
*/