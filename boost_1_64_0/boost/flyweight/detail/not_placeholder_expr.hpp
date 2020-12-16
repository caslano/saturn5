/* Copyright 2006-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_NOT_PLACEHOLDER_EXPR_HPP
#define BOOST_FLYWEIGHT_DETAIL_NOT_PLACEHOLDER_EXPR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

/* BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION can be inserted at the end
 * of a class template parameter declaration:
 *   template<
 *     typename X0,...,typename Xn
 *     BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION  
 *   >
 *   struct foo...
 * to prevent instantiations from being treated as MPL placeholder
 * expressions in the presence of placeholder arguments; this is useful
 * to avoid masking of a metafunction class nested ::apply during
 * MPL invocation.
 */

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__GNUC__, <4)||\
    BOOST_WORKAROUND(__GNUC__,==4)&&(__GNUC_MINOR__<2)||\
    BOOST_WORKAROUND(__GNUC__, ==7)&&( __cplusplus>=201703L)||\
    BOOST_WORKAROUND(__GNUC__, >=8)&&( __cplusplus>=201103L)
/* The default trick on which the macro is based, namely adding a int=0
 * defaulted template parameter, does not work in GCC prior to 4.2 due to
 * an unfortunate compiler non-standard extension, as explained in
 *   http://lists.boost.org/boost-users/2007/07/29866.php
 * As it happens, GCC 7 in C++17 mode and GCC 8 (and presumably later) in
 * C++11 mode (and presumably later) go back to this old behavior, anticipating
 * the resolution of CWG DR 150 (see P0522R0).
 * In these cases we resort to an uglier technique, adding defaulted template
 * parameters so as to exceed BOOST_MPL_LIMIT_METAFUNCTION_ARITY.
 */

#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

#define BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION                  \
BOOST_PP_ENUM_TRAILING_PARAMS(                                        \
  BOOST_MPL_LIMIT_METAFUNCTION_ARITY,typename=int BOOST_PP_INTERCEPT)
#define BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF              \
BOOST_PP_ENUM_TRAILING_PARAMS(                                        \
  BOOST_MPL_LIMIT_METAFUNCTION_ARITY,typename BOOST_PP_INTERCEPT)

#else
#define BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION  ,int=0
#define BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION_DEF  ,int
#endif

#endif

/* not_placeholder_expr.hpp
Qcxd20g1xdOjEnmf8nkHn3ARQ/KejGVSbBrUkIZS7Ep8QCn2YZr+nsbzZhn2+OMCJuXVEbdQRBzl3h7E9YA4NOwd6AygPgPoQgJtaLIg2+6U7rhzPPrsx04eq+MQw6RAAg3OGzpdymBblvZJbTpRd37Yx9I+aVifCO2dvs4hfNGZlvgqR4pvPseX1NkS37beEeLryvF9bG1/Nqa3LXssuv+dra+6/D5rdfZCp13U/4+355dnA0k0WP1XWLgluZzfl6yLYsx8FGMW6/4fG7MrkT1oXHNt9/W1uQim1l6ezVdU7yxgJICK9HtToCTpdWD5/COddJibNnAlNe2M/BD/x/l27LtWcvidTczw26+2A38Hhz+ebYafYQu+EYff0NAM3+1qO/ZlI9j476if16AKowN06+h6hqOCPbXFUcGtlx0NygyEwO0DZW3CGXC0PHlgI4aXRAvX2YnVASnWm8E3ignGSibKShxQSc76WlEPOTDcFl4Ko/RJ9ZkofEMDFy+4uj/XjfxBpxe5VqqtbR1Kuco03c0X7XxcH0mjn5kuNPo7+K2kbK1BVZJWCcrBxvZeylp8JeNsaoYo+3E/+BjmR6r3sZK3yZLFSUyIKKjYSdQpM9KoUzJJfFH85twFObn8ptxztYSke0sKUhozrwoklOwa0penuHYcpeWVYY4CW9Nt+HipHsIvfnF9IdEfBY219JJNSbsgKbCQwPA4rb6kZQ3mIHyehH+q79FLGKjL0l/nsnZhIhvL+7Nd8NhffjRedzC55bvs7mgTkSpW33Fa91+DJsPLz1Et1In0SWVNmLQDd5ExTDUnXtfpZ9wdxzOR0E8Lurmif7cx7rCbKr4yr6shZ/V/yVn9vXpHg4RwjBOZc3oMO++bAd8sMd9TFa/3lIZ0pDGgF9ogE1RRsDioRL7L0hqUYf4RYvwnZHDiypAU3CFuy4+DN7YbY+Ysw4jgldWR4GeMBFcHgv3PwROLj7lFXvTCjWE9xZ3ASAa8xAj8WTqMrdu03ZcDC2RG4xTQKApdzcMU1KZEsesXb9JGNlBLL+A0FcjCAmTHVR/69hGn2OHfGs06OzpeXAjNhdvH2PT/H6e09n/M8scDWUavhmIrQ3LG5BahHvKk7QrrtRj/FyV6zGvvFOL2ywaPeRi3RwZ30u1LLtMaNJI7NSelU/dOgCludQWu4eRnKmKKy1CUB+1oyZVHLt1uJ2lcd22bUUg7QDx+ftTF/UzXCoBYr6OBlER/JnQvbejoonmSEIKevETBUUvx/9xG9X8cbe98bVEb8/na2sYRnK9dR+A69BXd7Ozv0glM+zqxhPNCh8rPnVH2+Nnd2szP540iOT8tDIF/ODmC9shrbT7/7mr//Lu1ev7tssfvkVYh598NI+F3UQj8wkoR8HtdK3P/d7HNb2orNf6B0x6/gZZmep0NI6D3JQJXejf3qF3/HVlM/icENOsvjiOvW9IRc2mTT2OaX9iMV1Ajp6gFzRybQDSjUiggzDtfDDJSYIPiVaV/jm0Hp6Hnw3NTSohXMI7tf1vQ57gaTaTMYQPyacndnyK138PlkntnTXbNvY6zlMPDYdHy8NBhOjx8IFo9PCStrcdwdjUIG1Q9WCS3FoO0zu0NFp5J0yZTcwbdQiffFBhS3DYlMR5GGnlYXsPirCz5dGyYs7JYyFHOyqLhlc7KznRnW+iqigPZ79GE9lsRL+BP0f+b+3c5O//N5IM2ZmkrcLbXcivFSSUZs8jBdfDhdZyvO/l2qYOu4+zr4vowpjLYkM+aHsfqDbiznT01bTNLga4GTcIO2B4GVkBtlEp9D4Ts0b7CXc7krcsv1KxTXf+a0SgeW0G9//pjsY316AkO2r4=
*/