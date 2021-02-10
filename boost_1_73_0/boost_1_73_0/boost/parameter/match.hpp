// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MATCH_DWA2005714_HPP
#define BOOST_PARAMETER_MATCH_DWA2005714_HPP

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    BOOST_PP_ENUM_TRAILING_PARAMS(                                           \
        BOOST_PP_SUB(                                                        \
            BOOST_PARAMETER_MAX_ARITY                                        \
          , BOOST_PP_SEQ_SIZE(ArgTypes)                                      \
        )                                                                    \
      , ::boost::parameter::void_ BOOST_PP_INTERCEPT                         \
    )
/**/
#else
#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)
#endif 

#include <boost/parameter/aux_/preprocessor/seq_enum.hpp>

//
// Generates, e.g.
//
//    typename dfs_params::match<A1,A2>::type name = dfs_params()
//
// with workarounds for Borland compatibility.
//
#define BOOST_PARAMETER_MATCH(ParameterSpec, ArgTypes, name)                 \
    typename ParameterSpec::match<                                           \
        BOOST_PARAMETER_SEQ_ENUM(ArgTypes)                                   \
        BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    >::type name = ParameterSpec()
/**/

#endif  // include guard


/* match.hpp
xiOeQ3xOhwRbDonl6GyFv8EgcHPjL03GjWGsDQxl6yeOSzg1TZQF/RjlUm1K5oF5htiMbEBj5uEv7tgch9oZjpVqCHZEKSvftWEgsAM00h0w85D4tk5d0VjMPBwisKkwcKlrYn114tigDDkczclkfkiWKmd8SH6eLN7Obhbk59H19Wi6uCWz12Q0vUVhP06ml+B6BoO5hN5tXMphcJcwa2Myqgdj7u86OTg4OSKfaQbVPnJX+wyVF04dzeeTN1PUdDK9mE0vJ4vJbEpOvyJBl6mzg2jTTF+nwjLoeYVTz98cGzL+Vi6Y22RLfNKDAHPZVgUXwh2duaSPnbjjuxo9ACBtwU0QbEMCZgN5EFKWAE44xKGQrzn2iq2PjUMpHEUsfQbhjBIhJndClk3B8EvHMwKvWSEsQmEb1TMGQ+wgRtpRsgawrR0HAfRMpxvPQDkfbWdnUn0NYbd0hFqg8T33QOCO9txgbGavJWjA1Wibz3W6YjaEys31lTKdKbOry8l4DvfTUwlMdZh48BIfSAgZP+D9FYgib0c/jZX57VyZj6/GFwvlLVqfQx80HyDJvocQ5R5HJCEwgEX7MDmYlAaR95vPPYT3DhATzR9gAeFFUd14cJjZieyOo39OTbYicip6X+hwM53MF5fK20Gi
*/