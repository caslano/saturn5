/*
  [auto_generated]
  boost/numeric/odeint/external/compute/compute_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for Boost.Compute
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/external/compute/compute_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for Boost.Compute vector
template< class T , class A >
struct algebra_dispatcher< boost::compute::vector< T , A > >
{
    typedef compute_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED

/* compute_algebra_dispatcher.hpp
vFs8f/g8rP/vHpF/wmn+IuIz4QWcls/E+Ws4zX+Ee/eK/Ed4DqflT+El/MAhSPvE/fz+VXB2fxoR3wm3B/j4mBjOxselcLo+KpzeP/iYxCs4Xd8FTuu3D4Z2C0tf4Cw+ekj0j8BvJN9/8jCPz+F0/DP8HlL+qR4R+Sucvh9wun4UfEzi3qN4v0n9oIGfSbx8DO3zrPwDv5PNn29DOv85ehzjv4mncHb+Gs7OXz8R2tzs+3oS43eJp/CY7d8HX5a4PSXab+A0/4HT+g+ctj8Ir+EnkPpJ/Qzm/5D323sW7Y8sfYHPyOYfvoDjk/gSztZ/6OC0f/JFMf4FTse/CM+Fl+L8tYhvhffCvZdCW4/dX/h35PtpX+bvXwen5f9XuEfwBYkX8JXJ99XD2fg471WevsbCUzhrfy7h7Pw1fGrivYj3OvH+duL9hd9JxjeVr/P4Gk7rxyK+F+69wT2G+0O4y8/lmyjfs/2T38L4JZa+wsdg5R84q19V8MtI+aV4W4wvhdPyAZyOvxfxvXDvHfF+CU/hNH0UXsKR/lvkGl8K35bsr928F9rrbH72+2jfZOWPD0T7FJz2j4r4QsRXwhvhnXD7UMw/gdP1Z0V8CqfPX3gpvBbnb0V8D9+J7S/1UWjHGf7sGr/9cWhLkfnL/SehncvWN/0stFvNPX61hw+DPyztiv8mtItI+tLBnzJ3+3D/LZ8/V3yH9I/Mf+q+R/1pCNK/8JNoHxceC0+Ep/CHhjPb1LX/0PADfn3wD4ck69+PNKDlgx5O618jD2x/sj5CA6f1Pzg5Pg40sM2GMJvD8fvbUcX1w+n1jzawLYc0298xfzEagx8/gdP+HfglbH22MQe2Pen/auGHGmIdXow1sKfY+pdjD2xjUr70fJyfpA8VfBOS/0TBwJYayn5vY/6f/Z/GHdjYbP+E8QY2Dpt/BF+N1S/HH/y6vubSjvejmWBgr5P2yW7CgY0+rFniKt9MMaD121p4J9ybknsC/5jMn8inGvDxXcJb4TY19xi+zBBkfsc0AxtjSLMp7f/X586nH9D+iwZ+2hDu/T3aeGDTk/WF05kG9uyv53c8/1kH9gZbn2T2gc09pDv/a+cc8PELcFo+nYvHx3AWn4r4XHgpvBbnb4X3cDp/Z24eH8Np+UzE58JLON0fQJy/Ecfv4Oz32zw8PoLT8ruIz0R8IeIrOE0/hNu8A2vZ/kLzDSzB/zytw6MFxe+H098v4gs47T8Rx6/hdPyOOH4HH5O4LcTzhxhO21fhu5H0MVkExydeLzqwnJVfFhvYSmT9i3jJgV0KH8uxvnW5zMBuJPWLZrmBLUDKD9nyA3uApN/ZCgMbirX/rjiw44ZC/jKEY/2r1fjzS+B0fSQ4Xb9AxFfi/LWIb8X5e+He6txj+PhsfCb8DnO/X9kaA9uRrO+VrDWwx4Z2pw/p+vz+ZMJz+GZk/IVtwOM94RH8AlK/jjfi6UcKH5NdP3xE/GFx1/z3zfnxKzi+X5vFEV9uxc9fw2n6J+J7Ee9tzeNj+Hlkf+AkH9hrpH8n23Zgy7H96+Ap8WQ7Hl/DTyDtM/n2vP5Twln9x3YY2ATk/cp3HNjVw6KY4Sq/7snzF9uLeyw8E17Cj2Xjy/fm+VshvBbeCfcK1A/I+5XvK8qXcFq+Ft6K4/ci3tuPx8dwFp+K+FzElyK+htPxw/DZWf1h/4HNNwQZn3UAT18aOJ1/BKf19wP5+5PAafkATssH8K1Y/fbgga1DytctnNZP4TT/P4TXX2I4i09FfC7iS/icpP2jg89P2nfiQ3l8Ad+LeHQYj8/h7PwN/BUj7c+H8+PHR3Av4Bl5/nbkwG4m8T2cjT8tjxrY1qx+Wg5sG9Y=
*/