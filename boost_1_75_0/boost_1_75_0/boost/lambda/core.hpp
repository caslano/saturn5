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
cPEQg6kWbrOiFdr5ZAuNBY1xZetyuF3LqI58JUF8fVW7vONBssc2v7702/GVibM0mABzQU5RTrE0Nhnz+R+HNgbmNVz5xB8RTKtV9JcdPFWUGXidBf6pkpbxVmJhbCpeQnwLt7GKdqIvM1ERAys6WqW7vlWSOOWqDcGTAyQqfN8uUCV9CJnoR5oh41aIcgo5d1gzmrqwluTfOGqkfbYvF9jLVwQYCmjOfKz62mWzYqQ5ti4ty4veae1XOHEf8Je8HfLE85paZ8IzEJLIQsivoEbar4nc2Sh5A+T5qO6PLgdBtwYJyU87ifRSCskVXqSHFbtZ33RQJ0ktWfv88VO5BZE340IqCCMyrnE6rvkVXuHIYOCsRzH+iPEZwCfSuqUraGeJzo4HPbGlgI9Rqiz/WWE6xKp4H67Xc8DIWBpplJ3ef/Y/SljWZlzRtYSMC2IqW9ITFeBoG/IVKuF5R+Y6iQlXbzoQhtjtZ5JdwOso8o2ZuKSeo/neMx9kgBYsF63iNHnYTTpVSda9OHty1mxwemMBsApoMH+2crzfK7afIw3CV7VJFaahFm5vj6oQ0JCNhS071I/uId0uq+D8kyEmEj3KRykiUZ+1AFnLE1+n+x6rVUlfojNtas9Fn8hlmqtcdMavO6VNV9MwJ+2pIufSRMFT6TjQaIetFQcZx1PBz/yIMG13E2VCsX1OlXhihibFn8KkH2yP9ffQ3ZvR
*/