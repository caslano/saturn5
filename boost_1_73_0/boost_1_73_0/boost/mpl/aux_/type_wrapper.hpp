
#ifndef BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED
#define BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Peter Dimov 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct type_wrapper
{
    typedef T type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// agurt 08/may/03: a complicated way to extract the wrapped type; need it 
// mostly for the sake of GCC (3.2.x), which ICEs if you try to extract the 
// nested 'type' from 'type_wrapper<T>' when the latter was the result of a
// 'typeof' expression
template< typename T > struct wrapped_type;

template< typename T > struct wrapped_type< type_wrapper<T> >
{
    typedef T type;
};
#else
template< typename W > struct wrapped_type
{
    typedef typename W::type type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

/* type_wrapper.hpp
YpaOeFn69g/3F1BLAwQKAAAACAAtZ0pSs9cl79MCAABeBgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNDZVVAUAAbZIJGDFVe1K40AU/T/Qd7hExA+MSVREYyxI7apYW7FRWFgo4+TGBONMyUxau8u+ze4r7Av4YnsnaS3+cBcWFimkd27ux7lnzkwig9oIrrHNolymiv4ecTZVZaLb7DyOr+sHnHVjdnHaZ6kqCjUtlOAmV5K5bolaFRMka1rmBl1VGRZ5yxKR11RlK2wFhlhOsHR1niCLShwXMwpIuOEglchQPB47M9RO09gLtgPY9XdgcAl6qu9VJQWyU24whLjCLfAPoa8msOMHPgR74d5h6PtwdhWzjpIGpXF7KB9MFsLhqyeejSnb4LPxxgXPJevNJwlh29vx9/Z93w8YKzHJSxR2EotuDjJ4F+UONR5c/hO23XexHYHIeKnRHFfa5VrkOWPUpIEUWGbnDNbUdorcFmmoFfWCQnRNeJtlxowpYbGMUuSmoq1rszyR9GK5phRCM2mzXmd00usdoxzdDrdv40/ugXV14s/X3TdOW7XJiMbEmeWnzcZYFuBeXQQH/TDscflgRXBczI2tzuC0O+zG4CKsJTmC00dMNHCoS4KVV4EO
*/