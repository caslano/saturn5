// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/pair_layout.hpp
/// \brief Tags for pair layouts

#ifndef BOOST_BIMAP_RELATION_PAIR_LAYOUT_HPP
#define BOOST_BIMAP_RELATION_PAIR_LAYOUT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace relation {

//@{

/// \brief Tag for normal layout. ( A,B -> A,B )

struct normal_layout {};

/// \brief Tag for mirror layout. ( A,B -> B,A )

struct mirror_layout {};

//@}

/** \struct boost::bimaps::relation::inverse_layout
\brief Metafunction to obtain the inverse of a layout.

\code
template< class Layout >
struct inverse_layout
{
    typedef {InverseLayout} type;
};
\endcode

See also normal_layout, mirror_layout.
                                                                    **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

template< class Layout >
struct inverse_layout
{
    typedef normal_layout type;
};

template<>
struct inverse_layout< normal_layout >
{
    typedef mirror_layout type;
};

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

} // namespace relation
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_RELATION_DETAIL_PAIR_LAYOUT_HPP


/* pair_layout.hpp
xxZaB96x0OnI6/y5AN4r8y2qh+86E2WMNdPTzQse5e8fhDSZIt3vNPNALn9E0schFvUMLDZofVnC1pdsOnjp97VYX7LS5V14+y9TcRU5KhxJv+Ci8p0ZY2xb83fDMcjcv9KKHq/zpsf62RPjOfjSY/EeD5sxcYxQ6pzyHvRnjtZsS81gkDMe42jYfaONaXMZ3WcqwF4izvr9afJRh3wB/bOnlyh/r/X7i11Fj8c46R4no/IYbfF5CKt63MLaBWqKoUkazZq0wEkXS88ogTkKR2QhQieMkojMyObJsUu//FSasGq2dgJ0B0gtGPUsY266N1nKtcWBbzKUrPnnEeIa9W16jdL+eeSKo2uEElGsGQY+X2HnROtNVoivN0WK9SYj8CuuN3GRQeuNQbfeRIZcb7Aa9OWfoVtXstS3Wbq3CG4rnd9/hjED8pFXYDHT3Ozbwc2+NT8fT0MyFaXbbmLe/4rA9cLzJEzKyb6JxrR+j9d5rmWDVgMyMas4EZCEVnRIGBA4IQ0OvvehPIv2V3NBjil6PF5XIj6ghKKVKF7G6aMdK1RtQouANDhBxtHIVRzzcdDKxKBJymPzAt+kKs/6cMTS6Cg61SU7csH+ug3YiLXA3r9nRAqpgWDz3Z24cNSgKSzK38cRC6I4WEd1+X/MfQlcVFX78AwwAy44uIzilpSYmKkUWShZUIwOOmNUUpZZWGm2WKSMUUligDKO
*/