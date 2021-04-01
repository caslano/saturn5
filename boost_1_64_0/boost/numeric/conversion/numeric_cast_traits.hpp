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
y+gekHwPhLpITjowoa35KMTMqoraBZuPHFDCCBF1e9LcGKO8Nq7jmOb25PdorK74bOaALnMedkqLYbI/E9guPsmbc5WOLtZR9i31x1Zdhv40MO36fHso37dFjSmPV0dicbL5HabI4OuhMiK8LHabh1N/72cXaO0sK0irIk+AJWPipQJaxLd1KBJvmfGWXr+v/PLxOO34cmdK9mDCqkNhgMf7yKfLdMu2AXl2B98IxyKrIKga1xyLGQc9cjQPdfKU8W/NRvK9Dq/nMqXZ0xbAoDTaU+MAI1XSrxs/AA+y4vM9d12Gr4nvwzxzLonutCAzuj9NCBhu+dzaQ+3QdsJokNSsnVVDEvWKb4YdUv+e4vrzNeb5c3uY185NmM0GZ6gKtsFjYVYCE+HNDjkbhrklSu+E08fvmIapPIt8y9rB4f/tlgR/Fh+yavC/KpO8atC5Le+ZoJd0QycHNoSU+WmuMnZ1+jgTWy3eXiB+JP8YfwE+IdyonVay8+DdiJ3YKO0aYC0xLe5gKf0EHNMthhhRkhg83zWMe9eoGtDG0f9VM/ER1Z0bBaF7cnRD5Q==
*/