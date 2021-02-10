#ifndef BOOST_BIND_ARG_HPP_INCLUDED
#define BOOST_BIND_ARG_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  bind/arg.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/config.hpp>
#include <boost/is_placeholder.hpp>

namespace boost
{

template<bool Eq> struct _arg_eq
{
};

template<> struct _arg_eq<true>
{
    typedef void type;
};

template< int I > struct arg
{
    BOOST_CONSTEXPR arg()
    {
    }

    template< class T > BOOST_CONSTEXPR arg( T const & /* t */, typename _arg_eq< I == is_placeholder<T>::value >::type * = 0 )
    {
    }
};

template< int I > BOOST_CONSTEXPR bool operator==( arg<I> const &, arg<I> const & )
{
    return true;
}

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template< int I > struct is_placeholder< arg<I> >
{
    enum _vt { value = I };
};

template< int I > struct is_placeholder< arg<I> (*) () >
{
    enum _vt { value = I };
};

#endif

} // namespace boost

#endif // #ifndef BOOST_BIND_ARG_HPP_INCLUDED

/* arg.hpp
mv733VFy7aAbjAGlYVE63r33eHdkOvhxI4IBnBxZ+Gc0aA4RM2v+wtz/u3eWPUL7o6h7mk+RpHAIecxiOB3yCP0QknUsI37PslNE96yNHylH3mf8ShYK48ixqXdWrioP/XEMz1++/A2ewYuzF2cJXAktUcHco16iXSUwKoLlTSUeHoYOLxJAD0INO6hFJR04U/qtsAj0rmSO2mEBwkGBLrdySR9Sg68QSqkQxtPZ3eTm9wS2lcwrBtmZBlxlGlVAJTYIFnOUmxajFtaDKSmcwAvpPAE2Xho9JG4Ej3btGIPphXIGxEZIJZZEJDxU3tfuVZrmjVWkPi1M7tJ8v/1h5dffdnJHItZiB6b24A00DhNgzwTWppAlz5QQMtbNUklXJQc1RKWL1FhwqBRjUZxE18pGmHfpSdgNalIsPU/OaMdU28qsnzhSHhmlbKwmIsoDORWG0pxAowu0wTnsfE/R5TQk+D9Lc9BbgNEkBnqXc5jMe7AUTroEPk0W76YfF/Dp8vb28mZxB9O3cHlzx2DvJzdXVHpJZBbwobboiNyCXNdKYtFx/riRRukARlfX8/EF0/+BdgeOyRDeLRYzmE3nC14YpXufNPpZ6lw1BcLI+UKaYXXxxGSlXj21cVe0rUHmSGpPDSB1f2NkEUdf
*/