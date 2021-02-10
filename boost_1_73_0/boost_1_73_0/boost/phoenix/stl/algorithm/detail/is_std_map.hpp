// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <map>

namespace boost
{
    template<class T>
    struct is_std_map
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_map< ::std::map<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multimap
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_multimap< ::std::multimap<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_map.hpp
XFwoUNq6UqgiwKjSmhdYFdANRqIK2ZQcG8VVFjDMNdfIGlJtuGQOe4l43Nt3us6tKUphWqSDSCvZvBGyJGmb9LB9GyTOVdhBmLfdYPt2hTmXWl2QHrEvxdwwc4tIcy5QjJ1muHLyFgjT+Ugct8Q8FcNyZgoq65xTXo8h7m/D0l/LWlsr5ojDpOGsRDwspbKOSflwnewtIi9XVd/KrrthBauPjsgH3YGfLdYQu0cxec8b9Y19ykQXTZ5aX3DFDaNsUOavVV5otRAXncoDPYmDULYh7g0td02NdkSR9v21M9fG6Gte7rwYFZJoN2EJdeAM51AckHQrOhKsrF4K7F+BXiApEAuYpXEeD4/jKIqjPJzGaRAO8/5k8mUQnlC7HiTPF2Izk4PtGb1R3+YdXlN/TC+8XR3X/6JOjWvJB23eErsn9a3opBxwafn/hcGAK3yXBEH8ZzYN8yhJM8x2yC65H92YJvTp2wCnte24GwfTOIyGcWdZBkF/xc4vR9Drz6aD3H/PPVLao5E4MfwKBw8MkuMUFgbfKquB1NCrmJocBwfePXUJjuGbzNnAax7htTgehKPTPMxymrxZMoxbQTCIwijyp9vcYmLd9V12WsuOZFssPFOKjXqz0t1S7w0in1cPd8mxT4yiwoQetwQm
*/