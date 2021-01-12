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
hw0jTg4Iyr+P4t+19Kf+6/Ee0OzW8q0iX7ayd5ZYCgKBA8fxLHCk57NA035YdTrrJwA0mDlBwm9ud+F7syeAy97o9gQgATEGRzeFSF0TFLqmyRl/LJEyA/jNCZY+yX9MMn/6eYKtEt+6quuBiZdiFjIJafNGVhhzlXCv2W0c+EHkpbZvYb9ShaRVyXJSuX2AjNQmjFRqY7pNAWuVtADneM5zBUWXBGYC67U0wmvubbtITZAq
*/