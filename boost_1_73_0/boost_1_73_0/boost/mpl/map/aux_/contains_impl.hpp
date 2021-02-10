
#ifndef BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct contains_impl< aux::map_tag >
{
    template< typename Map, typename Pair > struct apply
        : is_same< 
              typename at_impl<aux::map_tag>::apply<
                  Map
                , typename Pair::first
                >::type
            , typename Pair::second
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
72dQSwMECgAAAAgALWdKUj17AxY9AQAA/wEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4MTBVVAUAAbZIJGBFUVtrwjAUfg/4Hw6KLwOJVTeGhI6uyCw4W7Tb2GPWns6ytpEkuvnvl4uXp+ScfLdzwjQqXXCFIWF1Vwlz/ODpV8hShSR5jTISN8gl5PinyXYRbeIlYfQGYdSzyIAMYIvyiHKk6hIJk7hvTgZQcs1DcgeeDAEEkynM7h/gMRj3DN+/M3rGO6G4qbHTZ6HCFQainHxI6pbvDeFSAut4iz7txaUSEtaLD2hRKf6NyoCoRwErRNvyrvQ6c0qHy3SbJ9l8aAWydJNTk+zJskcHOBiXucJCojaWV6q5nlO5vO8o6+oEdhTglUYJeodgVws7ruALsYO+2gndJ+zosEZiL4UWhWhCEo3HAcRRFj0nqyT/7NnGBFbpS7J2AcAHcP2pGXG1iHO/PtOYXWY2iV3j3jLTt9wu9+bB6NWY3v78H1BLAwQKAAAACAAtZ0pS6qlLmC0BAADkAQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgxMVVUBQABtkgkYFWRUWvCMBDH3wN+h0MRtweJbnsYEgpdKVtB12rj2B5je2JZ
*/