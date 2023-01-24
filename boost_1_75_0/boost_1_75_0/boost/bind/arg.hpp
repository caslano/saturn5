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
AMf5qIVXuopVFQeQzQPjp4B90v1WU+1zqLQCbZBATJbZyAc51oiBrUstAtnUvU7pnECzUYTym+eQy+dZh0TqIWzXyhqjkV3D0eE86m3SLKC32WxG/FsBxlgjxoGaFuYy4xBNJg+tI/aRNEytXKSEalrPskdm2aMd3gBIpanDkxDw7ESCAE2hkzeRFDo2nICzp4DPfUik1f51CpaCdDitXKoOB/KeQECgd7f/FVDdESL5PJRnwoBIDimhfxEimR3KuMInJDWfRBmMSDZJLEPoRflsRWNEIjfgM2ESkSxSVlgIkVQJRLKIQLuqOURiAA8J9vWhKiI5ELAPmyQRSVWziGTEfcGIpMqASJ4LNSKSIk6fiumqUjWMqlmuIRIbwvzdTSOS3aZ/i0hWN4FIIv89IlkePFM8i0VHQppAJLtD9HC/h+BeIGH7wOhGcL9Hwv0eI9xnENzvYbjfQ3BPtghNwr0r5Bxw3zvkHNA9b7wBupfD/ZeZTUD3ff1ozBeEMHGU0B0SIqFbcMv2rE466D5gDobutc+EMqbMOGGA7jeJ/TkhwetEs9BdJbNUadC9qEnofv/eYOhecS9BdzhOwP0Ya3euSKu983Sz0H1IB93itTfwLM9+ZxE88tLYcpy3MYlpvinJab4nnWm+nyXvgpzL5T2JQ7mkJ8lCF/GzC6e34/eW/AzpybbIyy6kDAsvpA+1F9GzkN+/5fcvLqJ8
*/