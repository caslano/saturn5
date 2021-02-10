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
j8rOJ9iNOjXhXlSRENqOh2C45oY/Uux7xFLwjKHKiH5V3BhNjVZ7JqVHBQLCHTjiy0xLdtLck3esjh0fdvlq3a7e3Ye7kWb+PUtkScXhmbvn2tditfNRPMRj0ncIENj10WYoggjeylhY6C1yI6MX2GY3hiTTCX0irUvAZCekfbD5vMryYyjed0nMPClyb6ASk+8Ome/SUU1OqUyCQrpE6rQneYS162cJJ32TGqKXVhLcI4zE8/G0cqHksHZ65TcB3T1kfvULUA10xCxyjNl857D/SutirdO3yU1P1IMGx78X20TLPg1LeetSCVPhRQPbEWgqrC3IjYrWPCl/i8NZsTQJo+5SNaM+5kFZzc4jb0dKo7XpoUCrBWslGd5WX6blHiPg9jypMD9ttdsE/0Xe71P16OiOL7FiTI5/EThurrGeCUbyacYq9uxKrm28XbmZPU6yA0qs8TJofr1p5Z7tNgMZNPTJqn4HVw3XVvaQQTXhtNS8J1qw0Wkw0tcZmyB45xQz3haAKYqI1EdvohXrTx3h5/PW7xFLDaWwGO3TF50L60vYdcH8jvtRihvaQ1QdJzb3Gr4sIJz6wOFB07eLI9IRP1ZFo8Bs5x2Ys15e/24TJT5rqp+Ylm06KIYufh96pFZ8lEv0x5mUfjD3
*/