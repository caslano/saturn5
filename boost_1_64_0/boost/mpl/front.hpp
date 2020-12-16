
#ifndef BOOST_MPL_FRONT_HPP_INCLUDED
#define BOOST_MPL_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct front
    : front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, front)

}}

#endif // BOOST_MPL_FRONT_HPP_INCLUDED

/* front.hpp
UCcZLBbcW+knAYCNn1wUN+6XYSi6uq1xH4smDM5PGHdQSF+XOe6JpvegjG/1UzxyDQos3/+RY5RvHP5ljLKl/xmizhu6qfs8O8MmlrWPVX3Dm3g4t9EYhL/LTQyz/u80oC8+gS8rNdjsANwn+oSfNQvcqwt4pAA7PDwgA6dM8z2VVZAzaRaFhdmb1xeGt5hwHtBwnhigZbUrYYuX5bh4IjYOt80UFrfMsJderkvPNUuf6Lh/zHlvwUQ+M8g+At1vnX8Mbqu/H3H0d3ixuv+3v9XlsfNwZx/6W5Wc4NI6+5NtcQMnYF+k1VqdRKhO/4Aopf7znOT44xbjcK7bgf/3BH+XDX9MXiEZXFF8UjjPbZGMVWZrP5Nq7o+jmls01Zw5ykE1vcMnuy2qsUDV9NNDPykZ4RSbhGMHsNwGoMgEcGySAI2TW7cdlMo/vf7uNShVfzO9bHfSy/cF37tOTUIvXpNeKpLSS8WRoZfLz1b4D1T497fw764CAYdcVZ3VRZsTrQZOZYLa42zgcmngI6fYCCrqdhDUuXx+cXMAlxidyUqsOTRXQGgxB2/SsK4+xSQ0PmVQWl2P7a6UqXD40j3DscRwORO9ebTImelWd3zR7vOkcLNZ0fdtFX2eb1b0uj650kd7xDm/0IUiX9cltlglVukzvtOC+vBuqOnMxZdGQ3Hgg3lJJ5OIv2er/hYTWGySshc3NorUq3e1fjTe3Ubjs3AVmF+RRUxixmWBeR/2LfEh/az4l2emmD8hnj8/dK5v11I/XXRy8vXNjfXtAQcNoUDvk9tf3xYNj1vfHnSsb4Dz1klpr29W6eW69IqT0lnfQkd8fbv+jLb6u945neuENHf2TcKv3Ca/Gp+UX40/MvzqoYIU+OcT/pGhNuTvEOT72JBHbAPxVvRV9omcqynFyv23vPaJ5bJCJ7FERmpKseA8lJcusejSy22lb8xLh1jyjxSxOPxfTk/d370j+bb+rhfcf9knkVh8LpNY8pISS95hJRbBPynWBYx1hQ3rbwvWX/S2YT1OSIQuko5M1iRiZX25tyaRNkenAKOTLurW+SfJwakxH2fD/E5B57zeif0dsPq7f9L+7n8E+ludf6TCfzDPz2ob/ncJ/rUn2ubnm+b8zCWBoMbBzHWBMhTAFP1JKsmz4Zw4yfM2Bz/XoDoKKFxTnWSWlpiz1A5guQ3Ac7npTNTBh3+iWvq/fqn6m+nlOlt/3y0od8tNpJdci14GJqWXgUeAXuLjb8PbwoevebETcZTZWSSfwtK8eazG88vBDctk3rvbtcfQx6WoIrX8e2qK/stler0s7K3W/fcd6b9XjrfRa71Jr15iFldK7nttuVcfbzKLqSAxqAsv5RhiQ0ghatzfsamVZTsPnzYPVslDLZMzIIPjZZttXQ9JN+4XQzEqutl1KIPRJv8/JVX/MH2NtfXPPYr/90qkL69FXzlJ6SvnCNCXOv/KjzvPsM5Ab+/msOZnCpOw9I8cbWmTCmQ+Z5dGOkTI/RLpuz74yNQhBer1CcBNpwIcclyz96N2jyRT8P+TU/R3kOkx39bfSxT/z7HR42qTHj1EjwM0PVq5j8kx6XGuRY/fNOmxS6aTHntFBgNIZKSG8EpPQEhOp8GkdPpZwRGj00T9x0mp+o/ptYet/5ZKezJ6JtKrx6LX7KT0mn0E6BVWCAvyAwEhznNUXIN4+bevnPcYH3bVS9zjXjh0oe4xueyu7+2Eb5t2iQNJLo9otpvSmVKV5a03zfjffZP3p2z/+/NWdjB1KWZ/OCpduu5YG0myipJZO6wC2F23sNxfifAqPzaJlePqn2WCWmoD9fVjTWq7hV16K0+T0Bl9ygNUZrBZZomtzBk=
*/