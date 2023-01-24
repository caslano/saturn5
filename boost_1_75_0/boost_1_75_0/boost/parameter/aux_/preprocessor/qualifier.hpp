// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_QUALIFIER_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_QUALIFIER_HPP

#define BOOST_PARAMETER_QUALIFIER_EAT_in(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_out(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_in_out(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_consume(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_move_from(x)
#define BOOST_PARAMETER_QUALIFIER_EAT_forward(x)

#define BOOST_PARAMETER_GET_QUALIFIER_in(x) in_reference
#define BOOST_PARAMETER_GET_QUALIFIER_out(x) out_reference
#define BOOST_PARAMETER_GET_QUALIFIER_in_out(x) in_out_reference
#define BOOST_PARAMETER_GET_QUALIFIER_consume(x) consume_reference
#define BOOST_PARAMETER_GET_QUALIFIER_move_from(x) move_from_reference
#define BOOST_PARAMETER_GET_QUALIFIER_forward(x) forward_reference

#define BOOST_PARAMETER_STRIP_QUALIFIER_in(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_out(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_in_out(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_consume(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_move_from(x) x
#define BOOST_PARAMETER_STRIP_QUALIFIER_forward(x) x

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_GET_QUALIFIER_GET(x) \
    BOOST_PP_CAT(BOOST_PARAMETER_GET_QUALIFIER_, x)
/**/

#define BOOST_PARAMETER_GET_UNQUALIFIED(x) \
    BOOST_PP_CAT(BOOST_PARAMETER_STRIP_QUALIFIER_, x)
/**/

#include <boost/preprocessor/facilities/is_empty.hpp>

// Expands to 1 if x is either "in(k)", "out(k)", "in_out(k)", "consume(k)",
// "move_from(k)", or "forward(k)"; expands to 0 otherwise.
#define BOOST_PARAMETER_IS_QUALIFIER(x) \
    BOOST_PP_IS_EMPTY(BOOST_PP_CAT(BOOST_PARAMETER_QUALIFIER_EAT_, x))
/**/

#include <boost/preprocessor/control/iif.hpp>

// Expands to the qualifier of x,
// where x is either a keyword qualifier or a keyword.
//
//   k => forward_reference
//   in(k) => in_reference
//   out(k) => out_reference
//   in_out(k) => in_out_reference
//   forward(k) => forward_reference
//   consume(k) => consume_reference
//   move_from(k) => move_from_reference
#define BOOST_PARAMETER_GET_QUALIFIER(x) \
    BOOST_PP_IIF( \
        BOOST_PARAMETER_IS_QUALIFIER(x) \
      , BOOST_PARAMETER_GET_QUALIFIER_GET(x) \
      , forward_reference \
    )
/**/

// Expands to the unqualified version of x,
// where x is either a keyword qualifier or a keyword.
//
//   k => k
//   in(k) => k
//   out(k) => k
//   in_out(k) => k
//   forward(k) => k
//   consume(k) => k
//   move_from(k) => k
#define BOOST_PARAMETER_UNQUALIFIED(x) \
    BOOST_PP_IIF( \
        BOOST_PARAMETER_IS_QUALIFIER(x) \
      , BOOST_PARAMETER_GET_UNQUALIFIED(x) \
      , x \
    )
/**/

#endif  // include guard


/* qualifier.hpp
RleAVgX7e2JxcfyohvWXPZkOi1L/gE1i92xlKaUOaKhVCGhGuL6MhfNIAC1YcZHT7nDvPHqT13QYSZ2R5ca7BEtmtn3Lq1zq1ndhxdU+Y+d2mMPjrlNwO9LS3sERcMLeQeJYW6PF7fdnY+ceG3EDwSb88Fbv7rdqb6QqB8iBdw+uxoFGL1+P9CrKp2MDmuGA9QhtX65+ChO+UPnB6dayLnqisr7h/9nSzZbVORMctq3LDbw8aOjaPK+ectBqWT91dS+wPbLF0Vxu/WoEY3MT/oDF2HJYkJc+8shKVyI+dvcL/IdDkCiHFGfyZ1JkhAs1F0VOB3lOun5UcmaGevlUzxU0WEQ09clPo+nGmcvFXyw9JlqK2jVxVrLQgihfreWe8XZ+J1Jvp5SDNAcDhDqZjx4g+KnOp+2eXPzFZrY7Tj44krBqITMwaguzRn83ov6UUoJXHK8ikeSUv1ye8cSFm1ZG71BTfIKD19P/fUaGXgTLmz/NR5K4gY1eX0NSVGKHi/LiHYQjv4BJyu0sFv9CBd6wjb49Y+eO9Usef2XMAkMjoJupkXvV5trKytLMSX0zz4r+3V0Md3Vx/5JE9UfbmH7N+WO+FV09NT2D/tHDWf9yyN+i0JqtDSd5S+9d4wVtVPz+9jMqMO/rbBrW2PSUhG30H3JHuh5aubAUpVjcTs1czYssOukvvJZt8ECG99gwN6UPPNu5Icvj4Von
*/