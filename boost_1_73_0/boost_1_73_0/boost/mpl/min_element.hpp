
#ifndef BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

// Copyright David Abrahams 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(min_element)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct min_element
    : max_element<
          Sequence
        , mpl::not_<Predicate>
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, min_element)

}}

#endif // BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

/* min_element.hpp
bGQBeSKLNAaxyMjWKjIcGyTfci11YvZc7FOZuQ1SpTPwff8XrcETrSSRoAlxKTVCIk0WckJMU6N0JgtzQaX5/v7+RcXlw8p+orhbSn5BLlGRW8WW9V5BcKCg6fswuj5gZOsipLucC5lpIuZ+wWyhkxCCDt14I0iACQgFSx1VFwS7C3iC/OFd1MP7SdMbh3sb4sir+vYiFcbXtjMvN2Rg6/fMSbRekfluG82RUcUjTYSjyWR85XC1WWnp2MESedVriDK2RJtNWAuiYTtflSkU2cLdBoICmguNz14QgmchIOJyuWRZbOmEXimlMVdy2bDEGnvnRlw6NxJpPg1y9IJuH1zXlsvW//hyNJlejcNjw248up3uDNyCAGEuZTijitodWkza7helmd2FLJWapO850nIbRYruHSox39i2YnNNXqZ6zNiGhOpmhjRM6tSHuu5Ej6UtAdCtWnKZnjk0ueFvNe9Kh4qIqjSEPwGoOV/JyD1fkI4QeKFS7/ju0+3kanRD05JzXNHxiXey6zWqwAy5aZAQrhFX7nkqHtEU8L9TUE2Bfffuu8/kzxTXsE65psZ7fSycQqHEsG54lfb5Sma58Z/1u34ffZ/Fg2ZrwFoxxrOgPeP9Tq8z6Jku/h/KNwvlaxQs94rFS+P1dzQ4
*/