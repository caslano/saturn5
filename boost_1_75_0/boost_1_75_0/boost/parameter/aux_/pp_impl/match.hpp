// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_MATCH_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_MATCH_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    // Recast the ParameterSpec's nested match metafunction
    // as a free metafunction.
    //
    // No more limits set by BOOST_PARAMETER_MAX_ARITY. -- Cromwell D. Enage
    template <typename Parameters, typename ...Args>
    struct match : Parameters::BOOST_NESTED_TEMPLATE match<Args...>
    {
    };
}}} // namespace boost::parameter::aux

#else

#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

namespace boost { namespace parameter { namespace aux {

    // Recast the ParameterSpec's nested match metafunction
    // as a free metafunction.
    template <
        typename Parameters
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY
          , typename A
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct match
      : Parameters::BOOST_NESTED_TEMPLATE match<
            BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, A)
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* match.hpp
AM/aeD310IcFkgXtfKuNXo3Bhjr/wi4omtugflal8Azy971mciZfYrJ3y/66/oaYfRVLrpRAPVfvyp4Eb3Zh+BKq7uEl4gA5wvPuIgCI8SUos2hY7M3KuxCjpCd54RXz4UR+/EUjxXNZ8PaJN5nqEsJFmHGH6sTdqBDUQvHhZHVrjSz9Mf1KjfV+47sXWQXIic0hfY54+FJ0EuGqlQWTRQbDZ/whQME6Vl4EGubAk9gG4DHv8lQ7EPeII2Cda78XiO68rNoNBiwDj3/fT/g9ZY+nWcHBKy0VfuF3b2DJXQbrTTlGsGUhdkZN46dO0V9zEylAZtUz/bFLoxmPPKdl4Lyo6NlXHOwPQD9yoAh46d09C5QxYwQx0TzOg0cYmPrCh5E9+ddfWek9MFZj7uQ2mTZtN1mL7QNYncmchSdf/Z3xHV+uY/1B/5erXzubI5sPEM3bIJzF16u4qyjuKGtf4kuHpIGJnAOAvi6cKRRjzDr8A3RPFEA7jpOu1/tGJDITN4taM8+HyZoMC28gJHWCJ2SroOtCtYqZNCb+u7+mO6Vp/MCJc7lbYJ7B1mT+WAZ14nk5QWTsxmOp30nPonP3r/Aws5x67T4RgnidKZFj++oVTrOLiDmglvlk1GIBVS0ZJ/UOZNSYFBQfEyahyTC/QUQUFU9JHenaLxzSVj0Rp41W72zeicSZv3/DxfP6jWmis0rkci34AS/EpBsr
*/