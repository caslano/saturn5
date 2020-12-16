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
eDqG/YfiV4mz2wgDqIlpOhLS74L7ru/v6x+2VJakaQn+O2Ky3vVXa/vSsMMh/S54fVioODts0xb8DuG+KP5l4YVbg/0QDpBPJ3tM6sS8yPxwXG9wOfYo8EXscRQd3TvFbL++s37Dq2HjCbsrIhf5rnYQsXL9bfLWEtW/7rDoL1L9U/BfY+hf94Lq17Adqh+5mP6CtvppOFp/vi76O6n+ncgfMvUfUP0adgq3JyIn+onTqYPVtmwqc6Pp/2iw2rCPH//ROFv/Q6pfw+bi7orISb0MDnS2Tyvxtkg67o3rAxfiv8PUv83oAzV8H25jRNa1D+zfWe2z/iNh3Z3IQijbiuThCeRP4ewy3qV50LBSZPfYspRBSL6WbJOHU8Q5Id8tNnUmRm+qmksfq2sfR66HviHWd7xFes+2WPwu94Ws33n+7hnjcepfu3A0VuL5fX2R1ffEKhtq04cWGPd4QyVOL6vYuIe7UPyW+Y57tqLtAsJizyeJ6UnlPi7al/YT2U2+yz2tVj9vZ6ufb5jYezD23JkX6Ut9TaXYNDsn7D+T4yaclkN203nazjWsBbfJlvHa19GozpOEbZHwruFw6Xd2cXwoptPbVKI6New13EZbxpfl1Dc0FUTLdf3L6OjWIeTt6VCu9rNZ/gi9v3e4D09WNoVaNgVG2XQVv2LLeGZMuK/X8jD8u1ixMgiI/Kf5Lj/HewllsNP7slxTLE5aVhAtg4DYk/5Wwg4RllcQvZY1dSLPhOj3tBo+uCB6TWsK2OWgehsLtBzWn5T2Iv0/fpWq09fkQaXHJzIatha3UWXcyuGJAr2urH9O+hL6AUnvvfi3qm5a70so95l92CO8Wz+P43IazoeJdwNpPB/2x0GZM/ERWIv8I/no0L+fKoyFm39vwL3GMX+L+3Mh5y6Mxbtb39//OUH+L7i/4k5q3L9B4mn8+O+OJ3mcvjumsGVMamz+KeZrdLU8skZNZFzGqqpZ6L7maWNvjvXZUddrk7GGZomn4xX4ncIvpwA/45m2WON+VfyN50fVc0TDzDWVj+Mn61uazwHMLZDnBPx79rDk+MTQ+Dkmnxwef3zTiMjxrvzI8ZN6/KAe3zkyPv6f9bhnwnqip7o67/lRygvbdPb8GDHWdc8PdKW+5wdxk66H3X+s654fyJ752qOp7PkRXRN3Rze9duh3dhfi7sZ25XG2W7Ci9nZ7Wo/rXgyzROY8a4DLvJ5ywy6lydeYJ27ytXBvkvC+zNXxOtnRlpd+q0g+/tM+r2e4CwnIPYCGjSfsC5H9GWTtghC9T3T/Bj9ho7u1v39DdhrlUxpb913Lx31/kZHdY2uQW1pGTaS5Oa58RFdK65A3p1m/zHXIzTa3pIfzXjEtY9PbK2bn2OR7xbS005Z2jXXfK6bFqAOju6Ovh8NeMRrWq8cbv1dMS7HzXjEHx6a+V8zTY133ikFP6ns4HDRsU03eS4sd9orRsJnFbfeK6Y9feXH7e2OkZTeXvWJG9tJ5OTjdA956J/LWuAS7aRflZju/xO/raDt02bbLzUtqO+Im37uko4T3sro7711iy8szHDbc0VNt3zNm+2INe5qwTcbeJYxfif1b8D/Ys337p7I3SdT+uXnt90uXapk06oYkY7RPGo27PbyGaJsyidxDy4pvS9ewKv8w1+vHKJEdYQ1x7gvQnXyfinw4W+IEncrNlne7v+8OL5U4PfSYWqAyCc9q9j3DDAkvdnwu6wKluCXOEHs83o8bo34l9HzSP1HHD/fWe/bC8K11lvhvxm8fzm6bXm2bGnYItykq4409e0d1Di2J3K8Hg7IMl+g8gkxeSey5iWRHdGpYGWEbVYZH9TO65jnuwZFQl46X6oY=
*/