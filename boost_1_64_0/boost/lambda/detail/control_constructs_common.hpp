// Boost Lambda Library -- control_constructs_common.hpp -------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
// Copyright (C) 2000 Gary Powell (powellg@amazon.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------------------------------

#if !defined(BOOST_CONTROL_CONSTRUCTS_COMMON_HPP)
#define BOOST_CONTROL_CONSTRUCTS_COMMON_HPP

namespace boost { 
namespace lambda {

  // special types of lambda functors, used with control structures
  // to guarantee that they are composed correctly.

template<class Tag, class LambdaFunctor>
class tagged_lambda_functor;

template<class Tag, class Args>
class tagged_lambda_functor<Tag, lambda_functor<Args> > 
  : public lambda_functor<Args> 
{
public:
  tagged_lambda_functor(const Args& a) : lambda_functor<Args>(a) {}

  tagged_lambda_functor(const lambda_functor<Args>& a) 
    : lambda_functor<Args>(a) {}

  // for the no body cases in control structures.
  tagged_lambda_functor() : lambda_functor<Args>() {}
};

} // lambda
} // boost

#endif // BOOST_CONTROL_CONSTRUCTS_COMMON_HPP








/* control_constructs_common.hpp
AwWcReLxrryOsTHEIASSsFcCw7O7IZCu7UJXjdfG7dSOQHqembiuvXjq1LVjEDWS8rgxMjbSvk9EHt63YKTMidBdAor3+kDq+cOb/fIOASumbBemHF58mxCVHE9T4cf0r3Dfnpm9Rtoydc38VmymOUptS/TG1OGd7oHrlHniSbK6jpc/FVg7qVfVbJeFo7DM0GytQ9b7h7Umgpqe4zlx88qXL5og4XTnLatryh+gKrEIzan4ixdV1iys5WrdsL17/09NZ34wDJhPbLBlNUfYRsE54P7YFNraxyIbr1s5pbVB/EHGCJdzwj1f9QhNR6d2hEV51oWnUVyfJVth68zZoML6rWSxm2friKt3MdYHAHKdBu5qSHHRkI7k5CQuL/4O7wBmGUeqY+SPKoK7//T9nBHzMW5Qh31gfaCuH/gcYh+axajy5shdGXoE9iEIvEQogPsHOmGtC5TDXD5KWuNCVvKMAzg4S3yRT6ohqBD2UDBex/BV5j0l9QN1jCRdbI6jpbbN9gKk/V+vY5By4SLhC7J8KSqTr1QH9FeMU955SsNvjsPLWfdqWzMnEw==
*/