
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED
#define BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright Peter Dimov 2001-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/arg.hpp>
#   include <boost/mpl/aux_/adl_barrier.hpp>

#   if !defined(BOOST_MPL_CFG_NO_ADL_BARRIER_NAMESPACE)
#       define BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(type) \
        using ::BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::type; \
        /**/
#   else
#       define BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(type) /**/
#   endif

#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER placeholders.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/limits/arity.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

// watch out for GNU gettext users, who #define _(x)
#if !defined(_) || defined(BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT)
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
typedef arg<-1> _;
BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl { 

BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(_)

namespace placeholders {
using BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::_;
}

}}
#endif

/// agurt, 17/mar/02: one more placeholder for the last 'apply#' 
/// specialization
#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY + 1, <boost/mpl/placeholders.hpp>))
#include BOOST_PP_ITERATE()

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_PLACEHOLDERS_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

typedef arg<i_> BOOST_PP_CAT(_,i_);

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl { 

BOOST_MPL_AUX_ARG_ADL_BARRIER_DECL(BOOST_PP_CAT(_,i_))

namespace placeholders {
using BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::BOOST_PP_CAT(_,i_);
}

}}

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* placeholders.hpp
o/DXBTn0KhxrsCWDK+/ee0DmlvbCmulbfbi0KypFmxit7F+r7AhjlcpJCunt2hLVWHwjZDUXmG5u505VJg7Gqlt07YtTQB98QmcOIEUOSC8C0h9UCdJFOExuzaI7mwNxNcOwap9XaxmJZCHTxxvxsOH4/tXmoC8ZGF4IwFgiA/Y6E/aOLLPOyOomZ2QIj5KAkKkznTWs6s2jy43B9wFN7UsP2aNhjCIDxiV5l1/Q249UmOvyUZMfy77PwMii4M4047qHiFVcscdV4UVlw1gB3IkqMLIQnbgJOnETiraOqmiq4oNQCu20lbL3IYb0Xlzg8oinp+mW5+R/zsRz6H6CBErogbvtNvSL3D2xzH3wUy/5vGvp3/fp3+0vHX8fvV35x/JoNOx/V9j8l2wXedSCNyWkdiQ54duP/ZDTptutFs/KNq0WV662rBYfn4Zn5dv6QfXaquTOKXekmRuJUFwNGwZ2RZ3J9i3JxrUtbO/9LxQVzr+ZJnrDF2SiPwRbOWLQnWSi6IicSv93RcbR/7tFBsWu1VyJ6dxC3nFWm1zZRJnC7NqeySj4ks68RDE7YyZh3R7TmQND3R0Km0XAZoiJjdsF8yJm6Q/UhTMF4LrlFks3IRPsBUny5hTF0oFQb8BWXA3wr94h4L+hqo1c9iZfOam8RNyh7sCmhfGrvtDAxISKidZfozkecKpNODcSHAjVT8Jk8wIM6O/LzVEjZtvLtQOOZJKXmbULnMpobS+wB/c/3YfbFjnidFrCJ1B5LmFcfUc+LiD4cKT2cZoWfJwbuQxZRXRojqyhWZGhIgGVzWCrFje+9p0K/FOEV/PrPDWnX68M4xjf4R3wXbNY8F0IgzkA8ovN3OOyZBZSVr/pjFyEZrW84xM1xmjL6GmGo0Zb0KHupmqQCSJbCUtdGeDVNUMA4jNQPv3zawCVJgBmMsjz2ZKAAYH9nPioaxW7t9d9FmG/geWqv1tlKUhjm0C/XoUeqaaNuZ82J9RSN+WTHI51h/0o/YWJ5R64Qfx8ZSpbIiJgcfAlF5bfe6YZFy4zRXYTeVNUxu27Ydy+G0WbRgV3k8iu8FJgzK1OFtkc/my7mM9BPnSfYt2SGXetiOwb1Ghp3vzJHFNkb8+oycfyY3lfyOzx17tt8r4lSf9ss+ufn1to0z8DIXZTo1TQW4iPgpVaCbwuVQU9e5JSQQPi8EPUR9T8mFXzDJfV3sEFNi10hNJC/8yp0EIJhw87QHo5oiH9lhXRFUH7R6nOlEjGu1FrouVMVoooxNv7k9RHSWG+YEHaj1IPp21iGn+/x66L6o+SXHnKdWqJAywLBMvmg3J5tjSYWDow5NOF5qLQhwul0G6t88mXxrhkqfWB+EEHna9xovWBGOi0fyAA81kT5t2ODmpfWydqX/Hdlto3KUWSpah9rSlqH9X7mMOURpezsDJFUPYL2byD9EpWvc9d/WZe9XueSMASVgBlFEWtjr4uF4FJxePPCbJfWqIEDlR6/pjhw77fFbmK/t8tUhD7rHxVm7T9PDzIOMOgAikQsZnyUW+CdJRnGvFP1uoCpSJ2mmym1zQzL6zXBQaERjv1Rx5ELluAzNjprJJU+UNjdP4C5J8p+Taz4VOvssyGrxKlKHSlqqUvOm292ZR7Lf+fco/l1Qj4/1pik1f7U+QV/dmZpJ8a0E/vnGgXBW6ln7bUWfpp+8cV72NYWtVrk5JIt8xPKwrudNj107eWWqKgFaKgyRIFVTbl4yaaDP7PC0cuFj8JpWUsCu7Vheai0Du3SqGrqRDzkNJIjWFfsDjkImRa3LOpzBIFq5J0RcB83ITZ3omuuFN0xac9oitq7WmtpSsCzrUmnB9AVzSgK+5UuuI=
*/