/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_IS_PLACEHOLDER_EXPR_HPP
#define BOOST_FLYWEIGHT_DETAIL_IS_PLACEHOLDER_EXPR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/not.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost{

namespace flyweights{

namespace detail{

/* is_placeholder_expression<T> indicates whether T is an
 * MPL placeholder expression.
 */

template<typename T>
struct is_placeholder_expression_helper
{
  template<
    BOOST_PP_ENUM_PARAMS(
      BOOST_MPL_LIMIT_METAFUNCTION_ARITY,typename BOOST_PP_INTERCEPT)
  >
  struct apply{
    typedef int type;
  };

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_placeholder_expression_helper,(T))
};

template<typename T>
struct is_placeholder_expression:
  mpl::not_<is_same<
    typename mpl::apply<
      is_placeholder_expression_helper<T>,
      BOOST_PP_ENUM_PARAMS(
        BOOST_MPL_LIMIT_METAFUNCTION_ARITY,int BOOST_PP_INTERCEPT)
    >::type,
    int
  > >
{};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* is_placeholder_expr.hpp
e6Wv7iDQ04PJXmneZBv+TNZwoDcylfp2NrVTXwEHnZRJ9dWxU182B6rQXqlvsK36YjjoJ+14iLNJNurbezsBvThBtf9qYqe+Jzjo3RO4/Zed+oZwoOm3qP4PbdWXzkF73sL930y0a2/mZfYvt+lBcYUTUJwteqPwQcdGGzvL+LddpG8S6az8HiZ97OgnpI+qk3kZuLZ1zAMifzmMY55Ls2ZWIAHeGok3rICbX2cJ7c7pfGF+3b61qPfbXI6TFNG1OBwUE9RwWWh9BVjR6/BsQPaCRLZdMrEk1/aJZWQ/qv+LEX+CftvSfrAy1aylD7C0H+w6LsL7LtuGE759jS3x/Tw2QnxjOD5vliW+ZZHiq8fxOR6wxDcgUnwHhhG+34ZY4isz1r79ZSFHtbCf2f7yhTF27pf05PADGpnhh9uCL8vhj7YJsf+0Bb/7Vn4V6z4z/DcFduALOfzaG0P4t4TPtdo/dOVIMpsYfWvG+M9FgRSzlAn310r5jqQWRTwyecB00OHmTR1RGMpFYWiqHv8uH+S0nYBVq5WpbvKxskejOGoZwNUqkoGUSUd7RCQDB/lm1bO2efSI8p06qrEH3E8ymf0WbWJ/4kecqngNXjO5RgCpOutyKI7Sx5+jCLKUkO/RbU6ne7l9+HYA8I9w0T2yDmrlhfMpyMBTsk7mDFmrMli1w8VKp7hECTqidwcS+auDFZSeDMuLRWV7dnRlbKkkJeEyh0r6ll9NpFNBt7anG6c8ESlf5aT7PgbK9z1BlNd1Gim/ngvbo8gvO+DY6VQoHxVC+SidntPXGfaXvgok/i4s52BVPcQtlzJoNFVsj6NptnE0Lb7KYvcQlx5u93AuzbB7OJsmdg+B+9kCe90VQgbvAkT460DN3LwKCcd26AAtNItUO81k4RQojFs4ZB/vD5KJfwui+9p2SPfDRrqP97Kgu3daOLo7G+nOlnS3BLoDE/yf/SZtkskTI7U3qSbK6a9C39SOSNt8BZL2qJG07kBaoBHtSzKxcCcq/A9WOMdYuHovsUfJhqn87z1K6T/mU8jdN5IQY3EvkBq2sCyPxDpKN6n8pqyqJeF34qoOttAs9uXx0rOw8x7Bzpumn//1hJ6+WnHbuSSee7tL8I8RCqsAD/76VCZtdK8nhNMYwhwjwnI9j150qCnz+kTuWm7g4rfXuLWP8d8eHf4mAlva8uLFTYRYcgKjZz0Tr18A+uly9R7Pl3NotltCOg554+ChEer6yLUba2nrf+/lUrsxRbbIb90trvLclhruKs+1qYarPINSxXfeE2QJ/7N8eczn1mxufzPyBJFnID6nH/m2/snBi5PmrJzmLOsg6RzdN2q56eY1p2YU95FNUIirJoCwlcGFcsDzTLXYV8z4tHzQJK+G5dhEDXJzG1r+DQ0S8AIjh1x4HbcF135JPONo5eUT6RwopLd8zGm5dnnl2sVITMrhi9eNuHjVoGW3Yxu1RZr1pRaZB2NX9gY/fGZduJsoXtMaKZ5lpLit16ILl9UM14ULahq68Imaogtn+oDzz1QKSB0oXT1NHGhUtzLK9hFllRllM4yUPd3NgrKEsJSdr2Gg7FwNQdl3eDm5C1MHkrdtWvMEXbt+CtJAMSZ3AG2IHDqxTtNYe8KtjDXToNrp5oPq33Kt/IzYbNaK1koDm0VdLdhMrxGOzSpGNitJNmOBzcBN/oMgwBEtcjn8mmpf2xJrLzTWfkVXsRzm03L4LRWeygrnGAsndhXB27/O5MvhzL+Xw4v6sTxanD9IDzVI/mxupgGIs4liuI4v6hdwpYuNcR4l5ZkWQpH/Y0tuqUvR2KMcMDU4J6BO5b1PomiNYDqVNwGBfjtNoH3BiPZ2iXY=
*/