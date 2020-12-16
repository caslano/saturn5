// -- core.hpp -- Boost Lambda Library -------------------------------------
//
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// 
// Includes the core of LL, without any real features for client:
// 
// tuples, lambda functors, return type deduction templates,
// argument substitution mechanism (select functions)
// 
// Some functionality comes as well:
// Assignment and subscript operators, as well as function
// call operator for placeholder variables.
// -------------------------------------------------------------------------

#ifndef BOOST_LAMBDA_CORE_HPP
#define BOOST_LAMBDA_CORE_HPP

#include "boost/config.hpp"

#include "boost/type_traits/transform_traits.hpp"
#include "boost/type_traits/cv_traits.hpp"

#include "boost/tuple/tuple.hpp"

// inject some of the tuple names into lambda 
namespace boost {
namespace lambda {

using ::boost::tuples::tuple;
using ::boost::tuples::null_type;

} // lambda
} // boost

#include "boost/lambda/detail/lambda_config.hpp"
#include "boost/lambda/detail/lambda_fwd.hpp"

#include "boost/lambda/detail/arity_code.hpp"
#include "boost/lambda/detail/actions.hpp"

#include "boost/lambda/detail/lambda_traits.hpp"

#include "boost/lambda/detail/function_adaptors.hpp"
#include "boost/lambda/detail/return_type_traits.hpp"

#include "boost/lambda/detail/select_functions.hpp"

#include "boost/lambda/detail/lambda_functor_base.hpp"

#include "boost/lambda/detail/lambda_functors.hpp"

#include "boost/lambda/detail/ret.hpp"

namespace boost {
namespace lambda {

namespace {

  // These are constants types and need to be initialised
  boost::lambda::placeholder1_type free1 = boost::lambda::placeholder1_type();
  boost::lambda::placeholder2_type free2 = boost::lambda::placeholder2_type();
  boost::lambda::placeholder3_type free3 = boost::lambda::placeholder3_type();

  boost::lambda::placeholder1_type& BOOST_ATTRIBUTE_UNUSED _1 = free1;
  boost::lambda::placeholder2_type& BOOST_ATTRIBUTE_UNUSED _2 = free2;
  boost::lambda::placeholder3_type& BOOST_ATTRIBUTE_UNUSED _3 = free3;
  // _1, _2, ... naming scheme by Peter Dimov
} // unnamed
   
} // lambda
} // boost
   
   
#endif //BOOST_LAMBDA_CORE_HPP

/* core.hpp
nT0mRonclJ7fGnku8eoTj1KGrZhBS/bbjK6+MsT5ZGG5u2x+rW+fVe0vS+I0R9839WNg11PTjzPQoARZ7709c8AGPEPuNeVlC8samQNKnB5GJ/scsKtmDti1CXPArtp+qtrOpeIf4n+OJ/5x2jletPIPUd/xyKQTt5kfOrfzjPPJLbz7dARoTxraVgPZ19rH+YC+55IG/ouhXExDxdfKeU0T25O97PFSdpbTlo+9neW3NMSNZTs7C/QyyrqhYVndNZaoOMZEc6zwtLG7JPxII1ffL5ieyfbgPV60Bt4j/mcaPakD6a4Po8b0V8Q/ls+4DVKeoyRsDHUuOW+gX5rlx7wWqnb1VH28E64TPOMLymnTG24lMqvgQHI9z7nXcC5lnCEyK6mqdNcUl7h924PShQqRcNcaIywfrbwkLY7L7B8sn+gBi19n+/evWtJn+WPE/zIjC1xf6P2d7GP/TpZLuG6qj+2LPrn1k3yvKJs98q/ML8UVgkYj7231sqlfJCxwl1cUzqrUrltZT89J+ALwM0AjH6bHfuSWtrugtsxafdjmqq9LmDxdv0J83VpLv6ZQeXmtVSQzCR9lCx/F8Jr1iroT9i3xHyFxY21xYxnXZw6t5rufi18HNd/dK89DMBfqwD7jPX/eKf6TbWkVK53gD8QvS+bjnY2QE+r7Nja+uEFxSv5cJ3mvKSUsHrmeUvKTsLHeayrwPzD6G+FPwstzSDc8M017X0yINcS9yHrdyTVXroSvK1tUXVxZ2sj+yBgJ9yTO1J38Nnni9lX1wne6/ihj1x/FbwifoeXYXeYItrGusrLc9m2rkvDhah10sTyngYMuiodaeXerbx9XeoQV4r8EtR3G+oZmqryL915LMc93xa8Fnz1hnbawc5Xu633id57M3aQvqTI14/e64VgyWeLU8FnJwJZ+9fH7fCXs77BGcdjTy7SvM0slzGjf/G1j1Yl11HVt1t52pljM8H6NcO63jbTun5e86rCIq9GNUXhm25FwZawzT7xh3u2me+BzKnvYVBk35IurHZMYlvLj99Qmv0XiH8E6heazPPeEJmqo9nuQAFwgYfp7tVvD9o0uFf8OqAUn33nS7YUxKKLhXI/1fa6EmYZnWWPAlcwybPrzl4p/b8xGI1T7uU/ehSnZXiHPmSdV59o5IMeoVBl3RM4yzpwj+ci6Qp7X8hl8K73F7JPQW1zT0cT7nz096YoLx7z2XfOofnuq7ulwZ9P1B/3pP2aL3uIb1+/bMaKs/I6ln18y8+HUe5H2TuHnD5GttxZmZT2bE5I28KL2o5JOnf7jyegzrvDsIbPPZXBNtoQVOYd6evOBIcBK6qdVA7sCLwJ2B9YA04FLgT2BC4B9gBcDRwAv5X0kS4AzgZcD5wHr8H8V41HfkPupaCN8tusbPoxwFj5CvblHVTwrEPUyNfF+y3hbqO/4uC1eCuOFa+JdQP3GAmAYcAb1+xZZYRmvmPEiQRWM15dyGwBsBhwElPkisA1wCOU4FNiJen19eTfxQIbP5d3EE4BnAouAI218b26E74nkexL5nky+N4G2Md51jBcDWs94Y8j3eNb32cAewDLWaz7rcxIwz0oXWAicAixjuFnA81ivFwAvARYALwPOAC5juOXAIuBVwGLgCuBM4Gr6s31yfwP7Lpr2mUx+O7BeOwJ7856bYcDe5DcDeCawE+XZBTgV2JX8nwF0A7sBLwd2Jz89gNda8clPruwrcP5DfkKoa2u58ZT72cAI4ARgJJ9b8tlKp0it25EGqZnIsd4tZ7muYT2sBLYHruI9Pz8FdgOuZf9bA0wDXs/yr1XtBH7MJ1LTTqaR33PJ73QbfxsYb6yGvwzqOfenXnM=
*/