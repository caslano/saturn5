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
/rwgOVx3JUM481Gt1/PR48TP4/Juw5JQv65htZL7bwLltwZj3zfjE6i1y/nEpImtSzgphstG9f3O+9xAea8vdJ/73OY+vHcTva6nfVeU3j/CRbYwxalDbBT5SVWaUVJbNqp8bsWMshqnvrNd0Xrc8L//OqoIT8eS4XFd5qL37wdkq/cWV9Hu5BlX/Ner24nz+6/baVcDdM4F01fgovPvZ7t9p4Tr0zt9LonjNmIvjwWSGNIX9qNL+pYeQFkQnqsOxk4F0XH1ZVO/9x5XLQ3v+K6ptzw4fwDl8WMDyiO4Tnm1Sxr/Zn+3neKlA7DsDEqishI5885HA+LmnAcNHeGud3B7yv7pHdx+AGXvpXcwzUU/32Zkk1M94lg9v6bc8nwPWv2lO8ae1bXzzLwsdN68a7MPaeB6keWtYz2uEZGubSPd9Snmp+6fPkX81VePOb//9bgh+hSD6ZruottvC/4LU8N04I2YNO6oow+kDgfvq3tcrvd8K/pR1+uF6u9zraLyED/7X38Jz7X+vu2iE3AT+bHULX5G46Gl7+JGxxF/5tnM8SmuOg+R2X+dhzkuOg+5TqTOQ5P/a8ZEp++lbNxd00fb9E6b+knX97yj2+aaA2ibXC+qDnMNbZvhaVo0NjpNr1G+G93SJO3Su05trLddcv4A2uVzrfbeLkcG17Vd0rTR7usj0jR16tETRh4zdcyBtM0+es2l46Kv+ZHdd7dwXrNeHZ/IhudPQere4xCpvzNybWW3S7yusfvesHiZHNj/9I93179a2KLh+lcLW+x/n2R0fUbEa/qE6HhdjWx1WLyktXqWC7KmXr8f3VY5v/9t1ZRb1PNzrhFRlj0Od9e5urTFvulcRb6+dsr5/W+nDdW5Ot5T56qXzkkvXaz/fTpX3XVs7ruO00Jxf/s3pb+7pdXX925tecp7zy56rNsvp9O1+/m2u7Vj7I/V6yaVfvXw8dXLn98w6pfT6fq/oqPVXZfvf5/uVi8drd9aokeJX+D9pzUc223t8NCxrOctJn6i4yd0LGuHGXAU5rbQsbxrWoffJzi+RI/v5vgx9as6XfUYOZW5HpOSGdCZV4JJDh3zDVooPmMdx+Mdx+NU/jjMCQ6/JzqOp4WO+YYzFIcJ5ljWgiQ+wDpMj8/GDNbjxzB99fhlzDF6/Gs/eanHF3C8Q3SR6N5uMMcKnPND/RTA6q+6ewbAtnCIQ0dpnfobpv6cOko3+mx/XB+2gZtge7X3VHtvtQ9S+w5YbvYC49oabhM4XcONY6t8m/FQtjiCSTABpsDGMAM2ge1gIuwEk2Av2BT2g82gpl/34iLs6PSLjiqb18BYuBwG/GHq8Xe5+lum/q5w+Cuox1+Kpi8VxsIWMJDfGPV3uEt+P6/X2wAPgS/AfLWPVfs4tU8Qe0iHzxoNd4qGa3T4qC7ATPgYzILrYC58XK/zBBwC18PR8Ck4Hj6t4eeZfYRkryIJvwPHbSE/0cmZCs+BmXARLIDnwzHwIXgkXAxPh7+F78Cr4BZ4D/wE3g9/gmthoupgbQpt/+nwEtge/g7mwqWwF7wMToFXwtPhVfAyeDW8Ev4B/gVeCx+B18NX4A3wU3gT9JGum2E7+CeYC1fCYfA2OAOuhtVwDVwA74IXw3vg5fAhLWfavu5NI3vdSH7JPnbB8kCuBXwctofrYVf4FBwHP4QT4EdwKnwOngH/CuvgBrgEvgCvgC/Ca+BL8GG4Cb4M/wY/hq/Br+AbcA98E7YkTm/BTPiO5uN7sA98Hx4Nt8Ai+CGcCT8yOmV1vxTdt6UuQqdsI3+gX0iAh8LGcCBsAgfDRFgAm8MxMBmWwRQ4C6bB02FLeDXMgNfCTPgIbAOfgO3hG7A=
*/