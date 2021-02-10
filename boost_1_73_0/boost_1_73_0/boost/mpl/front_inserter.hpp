
#ifndef BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED
#define BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost { namespace mpl {

template<
      typename Sequence
    >
struct front_inserter
    : inserter< Sequence,push_front<> >
{
};

}}

#endif // BOOST_MPL_FRONT_INSERTER_HPP_INCLUDED

/* front_inserter.hpp
NYpFeAAuwj5XHIkjeML6FWvZFIZBNVbljgFGkQLrdI56cx7ssAn68mH8NYZJNIU7R7B1psgKNOKHIkwgbfEUojlfvcI4iiOIp8l0nkQRXN+moqdJwDcgm+4QZmqD4pfiwO1QaqgST+Bna7kKJ8fjJI72Va5StU4gGMfR+Ewa/U1O5tPZeDr/HohLZy1qKpxNQJeuQR8htCTTXYWe+A+FOW1Lwf37/rwPQ7+dEZdl4dG9Ebo7MKSXuhQ5UcUJ++PCqi0P4aPJQLkiWCM1oDqXXpTeQJO7tjT2C4Hj1Le6IA9EyIrSj6UvtOASW2UNuMq3cB5YJ11LVUun/FVYXbYGg15GEobHq/un9OYhOfZDebh/TMP4bDYD6aB067BP7CMfBfpbH/B3zD2QMr0XA17KefAew4xBPJ5Mz2YBwz1owMbvwAc6hhv3ZkunDBpQZY3K7IbEeOmN3/vaOf6MdZHtoFs2lRHWnS9+QyBXDbwgWgjYPmLy1w7L7FXtyGlXLgVvOfR971dzJFauoQQ+2TMSv3ly8mLN5LwebV2Gx89Xj08393cjcaE1Vhw+CU9G4iaTd86ivFWkc161ofuRGLH6Azer7xX1M+90q5pH340VigZaS67lH8h8Mvf//PLr+a/p8PDf/wVQSwMECgAA
*/