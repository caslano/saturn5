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
4KPCGP/hmxW7Z7K3wPLH+1PbCYE3r7f1ujUtSQwpbXpsHisBYvmNYH5mVoYu8somyjas37J8b6HAwpfV5j3xzxXwletpZvdZMdTG4keF/RjJ6XiW9MJwlparGavrS4M84ZnHXXdBJQ2iYjfS+yV37mNvkIPqrO7DXgdfLoLy6dU0x2O4kaNTi7SGoQsiuhsz0RroUzeEHW0wn1lwmJW/s/Pqi6KgfkievjRpT4OG7Tj0OxdN8THvw0LgjUxckpJKr4wJpl9xVjKcoL4idVs+zPX+Bys5TtJtx1fcrb9W90hQiU+JWOWk/GMxQmlWNkuuSQ3xuyU9CBDQKlA91RRtQXCBC1E6J12bboK/6f0UyuvVXsMJiwEEVM2o+lJ0jDot2zpCpe+nAFxmRMlhx2gy/vEFkekl6vTljsA4Kht8+ztHTxkPQW7SDVHyxs2XTUh9wj812lrBVLFPf+ossXqBSi0lH2a1Kb+lYm8BtZWZEtnrxA4oaCkviejjv4JM3swfIKu6s3EZ+fkC09oPgipenVc3pvGxDdeLv5hCJAjFL8jZqW5JRHAw+0s9/V1iZpH85v6+6e7fvXPco9OOB8xjfqxEO07dzHXPwFtkXz2KfadL2VqprggbDkviaDjU2EHdDADut4O9tO7VTqAh2rRzdTPUoC4Zze9SrEjk+Je88XZ5tX/PT76ypClpkee33mWvm/iFlYkKi/xhpSEM
*/