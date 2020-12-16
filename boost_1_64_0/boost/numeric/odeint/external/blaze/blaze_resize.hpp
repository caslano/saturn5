/*
  [auto_generated]
  boost/numeric/odeint/external/blaze/blaze_resize.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_RESIZE_HPP_INCLUDED

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <blaze/math/dense/DynamicVector.h>

namespace boost {
namespace numeric {
namespace odeint {

template< typename T , bool TF >
struct is_resizeable< blaze::DynamicVector< T , TF > > 
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};

template< typename T1 , bool TF1, typename T2 , bool TF2 >
struct same_size_impl< blaze::DynamicVector< T1 , TF1 > , blaze::DynamicVector< T2 , TF2 > >
{
    static bool same_size( const blaze::DynamicVector< T1 , TF1 > &x1 , const blaze::DynamicVector< T2 , TF2 > &x2 )
    {
        return x1.size() == x2.size();
    }
};

template< typename T1 , bool TF1, typename T2 , bool TF2 >
struct resize_impl< blaze::DynamicVector< T1 , TF1 > , blaze::DynamicVector< T2 , TF2 > >
{
    static void resize( blaze::DynamicVector< T1 , TF1 > &x1 , const blaze::DynamicVector< T2 , TF2 > &x2 )
    {
        x1.resize( x2.size() );
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_RESIZE_HPP_INCLUDED

/* blaze_resize.hpp
S8/z7Sh47FhfLL0A7Vus/g6n9/9CPF82fwh+whDu+ev1xeifgI/lOv6lPl0fIYaz8lUCp/1rcLq/u/BKeCOurxXxvYi3y3h8BKf9s3BaPhXxuTh/KbwW3orz9yLeu5zHx3AWnwrP4ez9LOEpcbvCt0mIx/AjhjCLXP2TV6L8hv95Ulf54Vo4GZ+RXefbnuZ2ux71Qxx/SocnN/t2G5k/Fd/C85dEeAofkXgGZ/mL3cq9gm9NPL6Nnz+B0+sXnsHZ+Xv4rCz9v12cH07vn4jP4az8WMJZ/aWDs/qFNbz+kjTi9zX8+HnD6x+V8Fa43cHrLxGc1V9SOH0/hOfCCzit/4n4VngnvBdud4r6E3wH1v8P35Z4eheP7+GzEk/u5sdvhWf38PPbvdwrOF0fBk7bt+AZW//2Pt/uHhLpu/f/5cPuQd9WZPWPh3xbgbXvwpfC8cdz7R/zKM+fGzj9fSLeHuPxEZzFJyI+E/GFiK9EfCO8E8e3lnsE/5rtD/w4f797+HLEsyd8e5GNn33StyFJ+b99yrd1hzSLhsDf/2//o2d9Ww0eeo791V/w7T1D+ci1v+uLvp1K2i+bl1D/GcK9Pnfxim+nsfTnVd9GZvMrOowPGoKsn/U6bz/o4XT9vDd8q9j7A5+WePQmvl82/x2+KGkf6OC0/eMtlJ+JR/DxWf0dzo6fw2n9BL4dmT+TvePbI6T8XL3n25ZsftX7vj1P2seKDzE+EX9IHN5/ivH55P1IvhDpE5ymTyK+Et4I78T57UsxPgrO4mM4rb8Jz+Gsf6OFT0Li7SvuMZzNb87hv5V/HfOf4JOT9KUTx4++xvjQIfBvx/wB+9an6y/W8BfNPb+y/Y6Pb42+920XVn4Tnv3g2zVsf+Wf/ph/4Zj/9/Nv/btDO+I7+GqsfoE7NQ3bPw1O14+Ab8/ejyECm5EcPx+Cn78egp+/gbP1aXo4qz95Q/LjR/ARicfwmdjvE16L4zfwsYl33PEH7pHwRHgmvICz8Ru18E64NzT3RHguvIKPxsYvwp9i40eGCWzSId3jP4rhA7p+UAln9fMGPga7f/AC54//Fn/PuH/OD8R/DOj48gR+Ivl9NkpgCwxB9pcdNbB7yf7J1WiBXW5wR3zhBba6ucd39HDafjx6wOevwOn4BuGZ8AJ+C5v/PmZg67L2ubECu5Fd/9gBnR9Xwen4SviCJN7zuefwivVPBIHdQDwOAxsOf5hy2P+vnyfjB7baX+2v//Eazr6fBn4jGZ9TTxDYAYbjD/n/588mxPWx8b/wtfFiP/e39/OAyGzw+/zvft7g1/bPSx3lk2K+wPYd2v1+xwsHdgLp/4oXRf7H0mf49qT83sNvIeWfbrHALmPtH4sHth5JH5IlAhsCz3aWIf7//rYpfz87+GikfaVYMbDFWP4In5nVv1ZC+YClf3DafwSn/UdwWj8TXgtvhffi+ryVeXwsPBWeCy+F1/CphsDzd61fsyp/Pgl8FTL/rl8tsOuJR2sGdhfxbG1+fws4rX8Kb+C3D+meHx+vF9DxGS2c9i/Caf/i+gGdvx3DE3zfq7n259o8sJ3J9VVw2j4Ip/Vv4bZFYC8M6V6/odw6sC+HMIsd7WfetuL3w/fC71/atX70roHtzcafwtnxvd0C+9Tc4yuS3QPried78Ptbwun3B2fz9zr4riR/LfbE92P4s8v3CuxgEh/vHdiG5p4/VsPp+t5wNr/OisDOJeN7vH0DW5ONX4I/zd7v/QJbg/w+b3/uhfAevjhrnz0A5Xe2v9eBgc3ByrfwBdj+k/D9SPkiP0i8f8JrOM3/hPfCvYP5+WM4zV9EfAan9QPhFXwRcv/tEF5/jeHjE8/g57L6x6E=
*/