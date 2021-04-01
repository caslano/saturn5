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
7tUXGpcfH7ymNjlnats2n5a4SBoYBEYobtltJGK7G9K1X6ZWjOI7l33mXx6zY8zT9ivOMjk304tbFM7JSplNRU3tlktXIekzQqAjFRlm8WnFJ8WUKSE2tiXgCvMI6hUwfoVY5JqAxTOKEbwzdspk+CRnEiAjmDX1noMOJb49nAUNU+X+jhD1aKf0NPtCdDNkOsldBGAELAcCSgelqsbTPLGkk/fnC0Qqg7Ek1cGKGiX9ZO3SoPvB5lsVe4MdYVJmteIdnbZkqYaFyYW9URdkMcvcHWfNx/JZd1fedJIElo7k8hHQkRIH7jtX+aX6Lz/xnlwpK5IGzAcmUf+RdHPSpmw7y5qiQ2SUFWK5BbT72xK9KZ2YfYjWsb3ZUnEmnf00LRtDHq3+vBMoWew/0tLfx0QuWiuaIRKx+wPoI6f9DugZB3nKQB4PF1lnRcgfr7JJSs8quGdPbyswBpDlDoQPDTtIGl3GjkE86VHZwVrMnQ4lvCxCsxYDXJF37KGRsj2V0+QsPtQaGGyREAQtW5YwJn6Zdchornn0aDmd5Hv2tI9c8iC5HBRllYbdwQ==
*/