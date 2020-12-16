
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CLASS_TRANSFORM_HPP_INCLUDED
#define BOOST_FT_DETAIL_CLASS_TRANSFORM_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace function_types { namespace detail {

using mpl::placeholders::_;

// Transformation metafunction for the class type of member function pointers.
template<typename T, typename L>
struct class_transform
{ typedef typename mpl::apply1<L,T>::type type; };


// We can short-circuit the mechanism implemented in the primary template for 
// the most common lambda expression and save both the "un-lambdaing" and the
// type traits invocation (we know that T can only be a class type).

template<typename T> struct class_transform< T, mpl::identity<_> >
{ typedef T type; };

template<typename T> struct class_transform< T, add_reference<_> > 
{ typedef T & type; };

template<typename T> struct class_transform< T, add_pointer<_> >
{ typedef T * type; };

template<typename T> struct class_transform< T, remove_cv<_> >
{ typedef typename boost::remove_cv<T>::type type; };

template<typename T> struct class_transform< T, add_reference< remove_cv<_> > >
{ typedef typename boost::remove_cv<T>::type & type; };

template<typename T> struct class_transform< T, add_pointer< remove_cv<_> > >
{ typedef typename boost::remove_cv<T>::type * type; };

template<typename T, typename U> struct class_transform< T, mpl::always<U> >
{ typedef U type; };


} } } // namespace ::boost::function_types::detail

#endif


/* class_transform.hpp
M0XhyK2AH6PIS4YUfXO4vCodRVOxwvTd66gxcxO2n5UT0pPXIO+Z1cDYpwE79KKAmu4+dqZZDfFICwG5VyQE0JfgTTy0iNiBGdFzRqC2ty74FhFp5HnFEqU9N4D9mpT4ID8JXDzpj+uqc8OxHXJ4I4sAErzjhX3ZkoFCoy3wjjYnGCRLw7OT+JG9wCeIOh6Cjis3Ic7eFQDrP6Ce8Hb0WfApPklUCjYzu7GWdcKoeesn9OgeJ/LkEAGxpw2I+2Qg/kHlNMgPRiJ+oSZQd2HEiHuqEWnca5DUKwSvi/1oRus+6s4ywgrLUtGHo0XY1L33ECTXiOGcQiDA4IzcpXC401OOe0fmwjodPtRrXwrtg4lAvJ0MvQs/DXJxbGjDp0jUGumCLB02gF56Lmh1DOBC9okgwC2GnRBogvAAW3zINRh9rLqKj4+8B03/EZz3VTqyK+lB3nljEPIhFhNtPQMJRM74swszaFuK4uxzeoTeqAhga2gfI6O723Gjr2zAXaeCyeR+Rq4u4ug1NQ1IhVtgn/ovoAm3+7gu63lkyx6G6TwqB4raWtzr1uz43pmjjM4rYPMsHUvNYYcCobNY8esViDwFgGrPYWgxQZjkGQ5Y+bEMl3eVQwP93nCf3w6CX1/Dy23ckCTtGaSZLYWcop2xsTsi6KpwLYpbpo0SguNwwzcqYNsnhleHUQBvEwuuKmaMLgz7Ae5TAbtL1mKezBxonIUM1+l8gsi0E/B9TK4o7XwSLsfwEvVR7MAiQ8zhYWUC5lqkDyfoQpFH3XpYG7gXL1kuC52Z2fAp7h6y5o7B1POb0ROSaVxIjxldEGpCG7eRouPBD3CXI0/AKGIPZvUiBm6zrsdy95GguiIxxKXdCDkOebCC+BAoTjBhrsf1gS0pH0UkW6OvIRvx/eHE6N7bONwzSRs1m53Fzi1nhF1W1LhNMqDK/nKoJS9AefGt8O4YMww98cN29pqDRCYxds9eFAnsVcec2yhQ53JGlHryHnqkeRPXCNKCc4ED2MegYMQbSgVq1ntRqY4+VtjUAJnKcShJsQpyRSuw6bZc9OiDI3bgwDokI2ePuyTxQzoPE9qqgYNVqzNm4WMMLwdM0IZBUrhW44GvftaIfFL3gkPsZ9CfFsYyi2sRl1AUHlN5EQmeeg+kewKA71w9vt+zHTDHESARmIaYlZqwwWYQesbcURZZJbr5+gSyq2QHg01NWIbYXVCvGMcl1kTCxCkhrOWIKPhan8aZbqtB0reDGFl0DBLl2gDss+8lye66QXLFI0hc44JPyoqh69/sMKHCVkg3pUZuXQ3gWzSDeW/1Q7ES1bCt3BMoPoZD86N+5Jsyjp9OuYH6aCuQDx8r2sDeglNLaEETHRfiNzIBd/MyjKhqPdhpdqL6php0P9YNXJtOwQlWE6zmlidYpU9ho3o+QP94HTRfOYimhJ9ikVwDyKcR8NTLLOjJ1FpwuEmG9gSNod19H9F0nBI88ciArOVFiC6VBjrVWjFj231ogq0ISYhJINncNvRFuRVFZb+D1MpklIdb4CZslBCpOoAcT4qh1ZKP4XLHfTTV1IG9UkhDEmdKcaHBWT8uhcG+0HC4uFEUBk/uBAnD7bibCePsu6QRzKBqGmXfcMJIpiXRnqPGWMerYHA0zcQCpBzA1CoOMm9TAFtzCTyhzEOB3INoS8krMOE/jz6v4oWKtkKMdC0gtPM0HiYQiA6sc8H9uJ3gq8gH3DM4ADV9ycIvzj4vaCj8CEGRUvD+WBVml48A1pzCuNo8ERnPMYia1kaR9Q9guaElWjGRB8Fv/CAL88apauPRm6ExrF3JAc24pOEful6gZp0+ILshCW6fpTEXtUIkNVmPS9M=
*/