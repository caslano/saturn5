/*
 [auto_generated]
 boost/numeric/odeint/external/compute/compute_algebra.hpp

 [begin_description]
 An algebra for Boost.Compute vectors.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_HPP_DEFINED

#include <boost/preprocessor/repetition.hpp>
#include <boost/compute.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct compute_algebra
{

#define BOOST_ODEINT_COMPUTE_STATE_PARAM(z, n, unused)                         \
            StateType ## n &s ## n,

#define BOOST_ODEINT_COMPUTE_ALGEBRA(z, n, unused)                             \
    template< BOOST_PP_ENUM_PARAMS(n, class StateType), class Operation >      \
    static void for_each ## n(                                                 \
            BOOST_PP_REPEAT(n, BOOST_ODEINT_COMPUTE_STATE_PARAM, ~)            \
            Operation op                                                       \
            )                                                                  \
    {                                                                          \
        op( BOOST_PP_ENUM_PARAMS(n, s) );                                      \
    }

BOOST_PP_REPEAT_FROM_TO(3, 9, BOOST_ODEINT_COMPUTE_ALGEBRA, ~)

#undef BOOST_ODEINT_COMPUTE_ALGEBRA
#undef BOOST_ODEINT_COMPUTE_STATE_PARAM

    template < class S >
    static typename S::value_type norm_inf( const S &s ) {
        typedef typename S::value_type value_type;

        BOOST_COMPUTE_FUNCTION(value_type, max_abs, (value_type, value_type),
        {
            return max(_1, fabs(_2));
        });

        return boost::compute::accumulate(s.begin(), s.end(), value_type(), max_abs);
    }
};
} // odeint
} // numeric
} // boost

#endif

/* compute_algebra.hpp
/LZAaCMiPnKNf18wtG3I/nbRwqGdA48d85fjRUNryfjnZLHQliTfdwVfkK1vtDi+H7a+7pKhjULmb/ZLh/Yw+z6WCe1e5suG+O+k/LhcyPsf4LR+J+IzEV+I+ErENyK+E/GWco/gtP9NxGfCC3H8SngDp+sjivheuLc8v/5YeApn9ftcxJdwWr8X8S18DPb74Wx/9XyFkPY/VPDzSf5SrxTawiR/T1cJ+frt8EVZ+Q1+MZs/uSov3/Vwur/YaiFd3yaDL8DWR4Oz9t0WTuu/wnv4HKR+l6zO41PhmfAcPirxEn7XkKT8hsm9KBvb0q7+CfiWpH8iWie0+cjvz+GLk/gWPgnLv9bl708Mn5N4AV/FkP+51o+CL8HSjyy0r0j+Vq4X8vqt8BY+K/FofR6fwMcknsFD4gWc3f9axLdw2v+zQWgnkPStgR8zBMzlG4V8fBWc798myhdwWr4Qngkv4Cz/qcT1NXCav4r4Xlyftwn3WHgqPIfT8U/Ca3H8Vngv3NsU7zdrfxSewgfs98OnI+lfDR9mCLb/G0//PeGR8BjOxg9kIj4XXggvhVfwsYg38DGJd3DWPultwT0RnsPZ+okdfCdSPiq2DOn4gGgr8fyEJ/Dhiafw7dj4NXjC+he35uXTDE77t4VXcFr/gudsf6JtQrvQ3POz4zyk87M7OF1/alv+fkZw+vzgH5P2zWy7kI8vgT84hHv+QLxjaOsbYh3tD7XweCcRDx+RzH+wXZB/s98Pn4fln3DWv9zBjyLtN9WuaP8l5Q/bDe0zhliHt3Cav8BZ/u7tzt/vGE7zV/i0xEvhrXBvj9BeIe2v8Z6/u6v9bC/kH+z7hk/Fvl/4mmT92KIIbUY2fgnO9ne2fVC+ZfO34BsTr+F0/i58PlY/2Te0udj7DWfXVwvv4DOw+QX78fuTwdnzqeCbsvu3P78/GXwZVv6Hs/vnHcDvXwZfjHgDp/uTCo8O5J4KL4TXwjvh3kHcEzid3y68EsdvhdvB3GPhmfBSeCO8Fx4dwu9PKrwQXgvv4PT5H8o9gdPnL7wS3gq3w7jHwjM43d9VeCW8Ed4Jt8O5R8IT4Rmc7s8rvIEvzdrvjuBewOn9Fd4I74Tbkdwj4YnwTHgBp9+v8E64dxT3BE6vX3ghjl8L74R7JfdEeC68gp/B1l86OqT7r5fCazhrX2vgYxLv4Gx/b+8YcX/gtH0RTstn8MmGMJvW1T9/HNq/2fhn+GdDmoUOj0/i9ycRnsLZ/c/h7P6W8OlIfAtfn5Qv05ND24etn3QKv75IeAJfhLXvwmck3sFZ/42dyu+vBx+TeAyfkPUvwUdn6Qd8GuINfEC8g7P7Z6dxj+Ds9yXwJ9j6R6eH9u0QZpM66q/tmfz7tYp7LDyrRP4tvBHew9MhyP5DZ/P3p4bT9nXhPXx0uv4Hj4/hLD4V8bnwUhy/Ft4K78X5vXO5x3D6+0V8DqfrWwkv4TR/FN7C2ffZw9n3EZ3HPYXT+pXwGk7zd/iYQ/6WPkT/1/56YWjHkvbh6KLQbmDjIy8ObU82fwc+g+Efx/znHk77Ny8R6afwBM6eXwan66uJ45fCa/hirPx0KT9/BKf5A/wBMv+9uDy0bdn8yytQvh7S3T5aX8nf3064d5UoHwrP4YeS/a+iq8X4MbhPPBPxBZzOT4TT/EccvxXH74V713CP4TT9hdP1B0V8Ic5fCW/grH+hE/F2LfqnhnSXf6rrQ9tvCPf82vLG0HYh9Yf4Jv59p/BZ2fpj8F2IJzej/ZikjxWcvl/wMYm38J7uP/tb/5I59ndq4Gx8QAffn/RPlbdxT27n3guvGp7+tHC2vnp+B3fvztDWIl7CWXx8l2j/g3/F9tc=
*/