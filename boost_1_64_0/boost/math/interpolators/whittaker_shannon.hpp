// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_HPP
#define BOOST_MATH_INTERPOLATORS_WHITAKKER_SHANNON_HPP
#include <memory>
#include <boost/math/interpolators/detail/whittaker_shannon_detail.hpp>

namespace boost { namespace math { namespace interpolators {

template<class RandomAccessContainer>
class whittaker_shannon {
public:

    using Real = typename RandomAccessContainer::value_type;
    whittaker_shannon(RandomAccessContainer&& y, Real const & t0, Real const & h)
     : m_impl(std::make_shared<detail::whittaker_shannon_detail<RandomAccessContainer>>(std::move(y), t0, h))
    {}

    inline Real operator()(Real t) const
    {
        return m_impl->operator()(t);
    }

    inline Real prime(Real t) const
    {
        return m_impl->prime(t);
    }

    inline Real operator[](size_t i) const
    {
        return m_impl->operator[](i);
    }

    RandomAccessContainer&& return_data()
    {
        return m_impl->return_data();
    }


private:
    std::shared_ptr<detail::whittaker_shannon_detail<RandomAccessContainer>> m_impl;
};
}}}
#endif

/* whittaker_shannon.hpp
5rn7S5gEjZPSFnMtU8chMc8s9W9ez3/Ab57P3lrf3zfKCLtwvfnYWb52f8r50e9l7bX6hbvu3HND+mNH9J1t2yf3fbb81l6D86N///lRKQvC2jp27wN7oltib6m8w7rwQTgaroJnwYfgLXA1XA7lfjf4FHxU5Viuh0/DD1We5Wdqrqj3v9WBYXMqXA9bwGfgkXADPFbNo+FzcBx8Hp4AX4IXw03wMvgqnA9fh4vVfhl8C94B34GvwbfhJ2r+Er4Pd8PPYBp53gp5h8TcBn4NB8AUG/l/cJfK4fseToS74XS4E86FP8Hz4c/wMvgrXAF/gQ+qeYOaX1XzO3AP3AZtnlMrREHBeiEAG8EQ7ABj4OGwCuwPq8FhsDIcDavDLBgHz4Y14aVqvl7NN6v5HhgPH4W14FcwAe5S8y8wETq0iyQYC/eB9WAKDLefW239rtLv6T4wA71I94Oka/tpCbvANjATtoVnwHbwWtgeLoH7w9vgAfAxeDDcALvA5+FBKp+yOyyAPWAlntULVoX9YA94BOwPB8BhcCkcC4fBE+HRcC48Bp4JR2i7OR7eBLPgC3AcfAWOh5s1nk/gCfBnOA1WoN5OhJXhVBgHZ8E6MB8OhCfDIXAOHA7nWtQPPANeDM+EV8Ol8GZ4Hrwdnq/t50K4Fl4En4SXwQI4H26F18Av4EJYI0T5wwS4GCbBpXDZ//z89j/97HZ/7tjOQQcqUIEKVKACFahABer/of6i9f/srHI6//+kS/5fimPO/Ytqgn6PQVvBerOmwnMjayqlO/tfsL70Z//x67Oe4bv2gV/fNQS/dQzjV++60nnFvZ9hKO08osiM85kvjHPPDXrORLSoHZ6X6/1Yp9t6WxlXz9vQOiuv2zMty29erqzzXSWdiRhkyjDaNiqhe3rkjCXBCrAOTIb7wHqwLkxRcxM1Q98zE4znzLmJS4NxVKACFahABSpQgQpUoAIVqH+w+ovG/1nTpmf/4fP/CVa1+MSmjGUZ+7EKls16btSuWqFdO7ddXKFdhtsusdCuvdsuWezGFokvpdCuSHxphXZF4mtSaBeJ7/Jm2KUX2nVQu4Iu2LUI203PmjbVknmMdS45Bil6cP8wBqM14KHwDcIU3GvmMcZm+89hmD17O8TvaXp/biTsQNvMbRg7//2fteCV92PHKNZvroOw/ns3dW/ej+J+jq33fKv/MSYOtfPshcxrb+n+vnjYdaXsI3NC3LDYlN0gQ51DzL60Q1aE3Y5zjrCeNc+YKnYPhqpE7xU2exrHiFuq2cM4V8yV2H2/x47cKz1d7FaE5M7tuhJ+kuXaDztY3B8KRdOb2969N/yTB8LuTdghX8XctT7wvrDdx04N9s+9yM2Trry2c9fXJslr9eg+PXlWrrmz+AKpi5Z2ZO/rExLvM877VhdJ/3bS/73YtY5xpa+duzwXivs9lOfF3Gl6kp3ozDd3b78nz8t0WlrxDrsmzR7TZAnTUXb/Rcq5u9i1lOfu5LmFZXlTyJW3DMu1D7GFlMtC5FBEn2dLmH5OR3a5tLE/Mvk8S+yvMe22jZh3ucs8w13mZ0jcLQvLXONoL+nb6VS1EtljU91d5m3d6ZosZX4+5XGWE4lvjoQ9zOlgvW9H2vICScOrZi/hcvEzw13OReLtI/4bOtWtKk4kv9eJXWennbXNbuZUNOW7S96BRsjlqG7enVxJ1zbT7s6U562zErS8k8Rcs8IO+1Spg92uOqCFxyW69xmW45yg+w6PkVUsUbPom1rCXO2j5q6KzrVO3UsfdbH4naN1HQnb1d1HYVdyH9VrTdjuXt8+irD+fZSW63Jxz9b+I+L/ABOH2pXYR418WPbEh0LMit7N+YoWThs=
*/