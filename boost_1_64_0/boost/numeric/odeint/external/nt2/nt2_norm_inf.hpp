//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_NORM_INF_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_NORM_INF_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/abs.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

namespace boost { namespace numeric { namespace odeint
{
  template<typename T, typename S>
  struct vector_space_norm_inf<nt2::container::table<T,S> >
  {
    typedef T result_type;
    result_type operator()(const nt2::container::table<T,S> &v1) const
    {
      return nt2::globalmax(nt2::abs(v1));
    }
  };
} } }

#endif

/* nt2_norm_inf.hpp
B+r88++H0E9dHl8tz/9tgIeE7j5vxcU8QuU/z+MF3R/L7xxPxncuL6nwtxHS9ZrCZ312AHdAW3Y6a92V8zjSNX0uT9LU+5koy0fzS8jDONz/5T1eT4pyv1+Jx+rPX/FkgjRLJl8jngD36fHz1t77Ny29RLou+1ukx89Yev8dCx/p5hsnhH+ehf+0hY90c0cZ4X/f4udZCx/pGv/7LAu0f1DPn7fayE7/4b9ZuxLwqqojfNWAWKEmIcCDBPII1FJFREoREZF9UUxoCLigxpA8SCQbyYugXbQtat0rVotoFddqFbe611rtoq1Vq91brbW2Vbsiam2r1fa/5/zvzdy59yXB1s/3kTMzZ86cOXPWO2eOwp+dgP+V0bXFP690vcqMGS9Q14BrXSMdrdtvpW5Cj7q9pMoGLFb27w1+ohkTXx5R8JvOkjq6mtfjT/1UQBzjVl6uX746wvfLTeiX0XfasPuCy5xZLzq/rVx6EP24FvJez5/U2m/w+5An1CPkifkbbWTMjFc5H4W4v43QOOwraFs6luZr3L/b84adtMfXR0Tft/F9HCfO9dE1bhHXuLJOxt2ceu0fyfWyg7v7OQ72BvgX+zVw4+rInVts7VT+KVw7v6nXzt4PDld4clqTtH6f7RRjn2/RPgGPzX9FZVHaf5EWcNLK9047P4MmtiZ+V/WTGiPHf8gbcMNL/F/0t9XdU4yra/pREeCqHwHPOGqkR/4I/Z5CL/xBP4j0qIeix9+GHnhHvzfpa4w8Qwx9DeX5YErqp/1szmb9ihX+lIR+X6rwkDmGL0vptojjhyt8TQL/VErqgLUHeMTPHEcZGsgeo6lIRc93S7hXsWf5Y6g/9FOrb+jH+pnjvVQl/80Jft/jjP6uMD4GHzL4Lab+H1b4sxP2Xx9J+TXv55UP5/6A6f3UxFR0z3CA8HQxPD5rfBQOFDzyio5O53r4oFSvfr1z5s+tr5szd2l+3IxC5YzmoykZF6em/Lg4GePi3D7v08+fUzcnx93Chf808nfnvyk5A5qeiu4JDkn5n9brDNrBoUaXMKCILg8j3SxHxzNq/n1ur2dA0XH48JSL/9K0GkNuDjYbMPgpr25Vd4+Lw7T3XN6Z828uC5oyaxp6WrP1Wc+P8FTQjjdRQyDGavosz0kpn2VpL9NSXodRP3SJW4L5DfKHZcl9xnmKb2oX7GA1y+gxOpqYi5WC0y960rl6Pe/eA17fA0R4LxKHrhJTJ3y3qRPnM5lcFod9PR9LZYGSsXiX7QnvFag2PtjYxWLaz6KUt4sltIsjUpG7144uUGdR3yzlW/K46WnOtBqbW1qb9P3jpUr+wRH5q2vm57Uch+t5F/JF5rvq3HyR6lfcCc83Hwo4AU5dfdzop9aUu5xpwGPzfbmZ71eSFnDSSpx0nT6hLM7rbrPnWEVegJM2Mne49siaWOcnUkeQNTInnGTmVOAdfQPpIW+EvtHQA+/om0iP+kTo10TpgefelfQnGP4tUXrgebZAetQ5Qt9q6IF39G0y/qPd4nNyh+DRVnH8eoWHzDF8t8KfkJC/R+EhUwy/IRX5Lg8Zk7/Ln5pfF8jaLWt08wkpS+5I6LcMUkr3pNf2cneCvZxhaJ5PoPms2L9vI/pefVzNWWeaPnSWmcfPNu30qFlbnGPwDxs9nid4xzur7Qz4C1je8+Ye33PqHt8XjIwXGxk3qzLAB+0dleGLgkde2z7w4QQs2Qe6saN9jfkkpED6+/6W3sa29/Fex1byy+07L0c6MPH+iky8vyvC+Z3j/n4cz6/U47mrj66Ir8F+hepuaSnbVaY9Lmd7XM15aRvHgmsM3dWm3a4j3fVmzLuafa3U3Iu9kfRfEb6QRew=
*/