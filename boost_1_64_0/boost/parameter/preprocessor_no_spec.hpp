// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_PREPROCESSOR_NO_SPEC_HPP
#define BOOST_PARAMETER_PREPROCESSOR_NO_SPEC_HPP

#include <boost/parameter/aux_/preprocessor/impl/function_name.hpp>
#include <boost/parameter/aux_/preprocessor/impl/no_spec_overloads.hpp>

// Exapnds to a variadic function header that is enabled if and only if all
// its arguments are tagged arguments.  All arguments are accessible via args
// and keywords only.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION(result, name)                       \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, name, 0)                   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name, 0);                     \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(name, name, 0, 0)              \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(name, 0)
/**/

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/control/if.hpp>

// Helper macro for BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION,
// BOOST_PARAMETER_NO_SPEC_CONST_MEMBER_FUNCTION,
// BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR, and
// and BOOST_PARAMETER_NO_SPEC_CONST_FUNCTION_CALL_OPERATOR.
#define BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, impl, c)   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_HEAD(result, impl, c)                   \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_OVERLOAD(                               \
        name                                                                 \
      , impl                                                                 \
      , BOOST_PP_IF(BOOST_PARAMETER_MEMBER_FUNCTION_IS_STATIC(impl), 0, 1)   \
      , c                                                                    \
    )                                                                        \
    BOOST_PARAMETER_NO_SPEC_FUNCTION_IMPL_HEAD(impl, c)                      \
    BOOST_PP_EXPR_IF(c, const)
/**/

// Exapnds to a variadic member function header that is enabled if and only if
// all its arguments are tagged arguments.  All arguments are accessible via
// args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION(result, name)                \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, name, 0)
/**/

// Exapnds to a const-qualified variadic member function header that is
// enabled if and only if all its arguments are tagged arguments.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_CONST_MEMBER_FUNCTION(result, name)          \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(result, name, name, 1)
/**/

// Exapnds to a variadic function call operator header that is enabled if and
// only if all its arguments are tagged arguments.  All arguments are
// accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_FUNCTION_CALL_OPERATOR(result)               \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(                             \
        result, operator(), operator, 0                                      \
    )
/**/

// Exapnds to a const-qualified variadic function call operator header that is
// enabled if and only if all its arguments are tagged arguments.  All
// arguments are accessible via args and keywords only.
#define BOOST_PARAMETER_NO_SPEC_CONST_FUNCTION_CALL_OPERATOR(result)         \
    BOOST_PARAMETER_NO_SPEC_MEMBER_FUNCTION_AUX(                             \
        result, operator(), operator, 1                                      \
    )
/**/

#endif  // include guard


/* preprocessor_no_spec.hpp
kS+6uOnj5bOUriW6eehNh4s+xa+G3NJZAzlZ2djyWSCdt3ov8TXmZzO+UIkHHNRdruL5hMKNk2ly05EFmpSvG4imtcsicybRcDl5h2gWivqVTXGX6GmQwi5E/Dn6ZzrRF/qW+G6uOv8EtmNSjvjoI+T8mcu5HJY1Le8RTYSRX0SDK83G8/wb00xnnZg2bzWPUdzVOMNZXmcUfolRJnfCuRhPwYal/lxVJoszC4uNk/PSxxV435Uq9oH2JvptWhP8HQ83Ge4euFWIjes6h9kL5ae+qOv8XrQPPyXy2ayqs0gstCeJlr/VKvrBTGvv57I8Q8n/ZXEe0GvQ5XrH9y9GAaArPQzuy241frccMKgbPb8snrvS81LxfBk9PyKeu/js+/4kzpmrGqecpHeUbsu3SqTPcvfBcs7fYBY+iOeSUk+J/C3B3BGOMsiho/OLitP1gIthSQOeS5h6yllfxN/5jWkplm++3Jcrn6WQjyVzck9K+azqf/dVz8nxtySrnHx+VJpKj5MKxkrCVksGub0Y0dGIcz+f2fgen/lcKsXpwdR5Ds5Jxwdn5TzrXKLdxnWQeRFiJ9g6SV94rzw7W9i5F8l/ibJOMq88zyLakH+RX3MtntuQA/R8B+YPW2u50vmwa+j9U/RNZA90fbiDS3sUAUSFl66hbxz8fe0zvNsMNxwaukRx3lyUw3MepfO3aazxO8WPMVmM8dzltPGc0NhyP0JnI09mAYKB97v4DDrQc55QG0u54n1nspibmk+0U10lrlBOv8nfWs4TvFPaL9HOLjTidN3qMmhWJXmP9eOBrc7oNIfBY+5DxzlRJTTvIcrISKIZaD1nTfS3XqB4OkEPQaJtjvmFvi8I+V8jmiwXn92Af7znmeN4lfwzXC9oa4148fQzxZvIe7DEeW3sj3jJv7+VnsrISNSN8E7m967x9jOHmGYkaOJiQFN3uExjXWMn2td/k5zRtnTKYZYizAZ6mPVKN1i/KXXBs14GN3A7shG4CW4z3I1wW+C2wm2D2840OxyeL2akX8Ocqa1cU5n9mvxpLobKbDtzLXFnMV4WGItyXUppKy0em2+sI3XjnUtLH4ZnlU1lepfjtT8ID7JReCQf+EWdkr8VZ3Qx5OvKfZDL4DrEovyzfDgaRKx/jxDr/4pFOXmU6DqqZEYY0hnJfD5QYUzAM4Jk28Fr+oq9ZO57mX0dyRN4qJBkzs/W53dt55mo5ASf7/M/gvB8jPzrq9dQBMwXrb+zMwkoTkrnKT2NUNgyRO52LXslbGPrK+f81nlR+Iobhj2Ou836hOrvJzZvm7ym0byXf5vy2sx9958cgv5GsP5+8GvLB33216p+P7742IKIFa0WYS4tQn/f/Zc2rYedmXbfyj43Jpyo88CdmKuro7/fFdVgc3qnTm9cFXpht4nNekOPazT9fWWPwU1K2syZvTWh+5y6FX8eh82lcBJ3TJt97vwRW+6b3P/leze9tBff8oh+6aH63e4JHvhHnwvqb3n3gs9xlx6mDPB+/fuvHvo9qc/UXamF+97s9MYc2H+Sszjx/tPT//H4jfe0u/4pd6e6X6HfcLP+ftiqWZ+1bH7wzLFd80pDb/vqNOZ9I/X3wdtiskdNbP/M4yteuf7PFnuzUJ9JnheeXtbr7pDgP3tkXfbihC8uy8ScBtGfmJ38RPudE85NP7l0w11Lm6/C90eK11Oef+/pytZvffBwzyYXfdl1G+xFjP7+jf0jvnshL+nYXw8v7vXx+a+ehH0g/c94/omDX+9OSZm+e+jksQ8+hzPufiT61V/ecN7CjBcj7onc64o/8/wGfDvrp79/9uXHd+x/e+LZqbHr4y4M/2UgzvaM1d+Hnmo=
*/