
#ifndef BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright Dave Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/reverse_iter_fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(BackwardOp)
    , typename ForwardOp = arg<1>
    >
struct reverse_iter_fold
{
    typedef typename aux::reverse_iter_fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<BackwardOp>::type
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , reverse_iter_fold
        , (Sequence,State,BackwardOp,ForwardOp)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, reverse_iter_fold)

}}

#endif // BOOST_MPL_ITER_FOLD_BACKWARD_HPP_INCLUDED

/* reverse_iter_fold.hpp
XWGzUfatZmBRB/ZJljJ5fYf7GWNamVyxHl+tViwChi996/DFmEFZAOMWzkLthCIoF4uElBkzXkBapKdRqSBOX52ypB4b/2aVlteNOgUuy46g+X6N/SBs3iD6m1l9CFz4as2bB/rKIRQCtY2rMOcJtTsUrFVyvV6umvYkf+hIyPKAjItdOjZEiRjZ+T2NV8pkBSMX8KIL1QkLySRmoYCbbcduuw0oYFFGfQ4uErkTVNLTEgkGSsxeU6getEo1Gwdw/bDaU1ilB0ol6pns16UCkvaEhABYf1qJoqgVsNav/I5W8tj7H35rk6+mwcsfwnXPm5SEJc6QIWEBz0NWcnflqzbmMOJouxQd77zT+uTmTxc+z+3dqgbm/d8mEp5WIiVGePrZ03HC019qGJMWNRw1XBCjLKOSX/quvRggPSKLpZVLTEpsmPijMDk2ChN/GX+kPorBpJxBAkJeIjHOp+rb+jIjMEZ16R9etsgoXyGArM9QChAAqefzdL711/Y2AcLGmxhkQbkclLkvW+ygQIFE1vMkyHGBNHRUATm7mH9cG6UjwTmOlnuHYF32QdGLnZWPaDQGgdMZAUAcxF3/5ILvlKD386f0XYVrOtd3vbo6uX5q15pE6cKsw29j479/SnFmTXOrV/BEGaLI5akVFnm6BGdnJsYUH19+viw/WpW/wlbercq7ufyE+PInyfITVfmjVnRxqUi+Pu99weZ/LJBaQxtij6D9E9LmlYmJ5mQ17OuL5V64crTm+MIgirh7pSK7ZawNkV1i5L8hv1+H757Iz1M+BLbin7wQq09mHYc5eqncve82RqTT4ldGHYQY0bNfijp46G8cw8mQLK4myeIZbB/8iBaDWCQt4UktrNPacRuAmr2XWhfd5AmGK2Yf9Eozb1N3F/U1jo8BPJ0BU7S8E1UKJugfeadju9kq4DM+VGe5t4GV+iKDoElrZiHNGKcgQH205P6uOIfuw8+K//S8lNdKQj1ZcQIruT5m2z3oEuXN7Za+rYcqt2lYrZi9bgeidoOEvsaPHFY/zaN+GvEY+qkrrVH7jWHdhZcmhdcehpIdyL+MPzF+gfRgCmFsRUgrz5MnCAV6r0Uq5mM4LHw0yh+lWShXE8rVy7uGsmX/8ZyeX7wtFGjNR+xpHYfNJ/vyeBC28YISizW20FjBi9O8vWcctocZW2zYzids334U2ELZ2GOfnOi1/3DTL4E5tlZPPQdQagO/biVeYSWDziSZ/pGDgJ4x7AL6Jt101vjwTe0rq19FMdX9F6JBLmSmuMgDn7TqKCB/kCetzINIdOZXY5lqMNjLlfekFAMwBfoqnhyzvyzDu13/SzrmQBV39jRzLjM2awszRw3DjTQMk3+ptjDDzN8taWpHaA83/M9GLH20lw+BBEf7lvdiv/Diskd7pRpEwpL/CR/Vdx89bsWkyxcUh4QCsjW2JRTohEEUKs2WMEgkYGs8wnzxWtw1pLbE+RBDeotdm6rrcMqh6HA2HeKJUgtRqpV9WoPjCzimulg91HDunGOVGksRc0Wp01BqNybD7mD5IBwH9BbaAzXqv0WpKJo3FB67HkvQ5g8eS9DmtUiwtdlwW/wJqnMauvAjXZvv+/vT9HUFSZOYUWoTPtVraaA8aojURno8OMabd6BFNkbnATkOMH6fZrVsIbfsuYf3xU6Z7ZEz58AnHWThCU4eooSQZPt/UrIr7U8Nb/ix+b/pGTzbiMwPnPUI9zdetCF/EyP/xUMpDgvVr7AsBj36guMnokhc+giVPjI6nYTuLHSvg8+gasjLdoBxl0aqyqhhpC5QSEWOkPqFRb9C42QN4HzOMvN+VpSlJLnZ8NOiXnw6tttFLwKsPRYkdtU=
*/