
#ifndef BOOST_MPL_REPLACE_HPP_INCLUDED
#define BOOST_MPL_REPLACE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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

#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct replace_impl
    : replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

template<
      typename Sequence
    , typename OldType
    , typename NewType
    , typename Inserter 
    >
struct reverse_replace_impl
    : reverse_replace_if_impl< Sequence, same_as<OldType>, NewType, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, replace)

}}

#endif // BOOST_MPL_REPLACE_HPP_INCLUDED

/* replace.hpp
sO9kR4fL9mbB+5H4MpuAw7dOxobzlOdjsLMrk/VQgUHw21n013AFpZCYO3oqfiuS6OGhGC+XvQx12sn8A5mZL+HSiQaj3zdIZKhjJWuc2VbtQ5LKWmcDOIW/D0we1y7HhO3j+O3+nQm4isIqlUr4qfC8l5PvO+c49BcmIJnNmSmLJJBh1IupQONyuQ1KhU3ASWnGn7u8XL7svIPQniwC1KAkJNYsRB9UuxFboRK2+6zZLUauU7Tk96xRkxFDoBWwaSGY0Mjuv6/Piztq6WdCQFcQnksuUzAdQfvbcxVe/iw0LOLwCck54o5jDNr3xV+X+UZU79iWZQ593vjJ4ob2HiPPImkSd2UOJOO5WMt5v2NKF7t1ZxBEh9AeuPWL5x9IDhxjYhHpY7Mb7ZzEDZqXLSvQVMOepN5elIEwcqXSht4W2/DxxQ1+ZYWdAraI1WxW9EJhS8zSPROyYLxcIpnPk9+j5OOGhzrMbmZrGzE1rsOTTOxZT9D+CAXcDhga6eU1VRSPL1+58nA9+qzpEr2utz92vCAybzJXNzenctdULDa1JMhmrGT+SQoApPBj1PxJCnCzXHx39zu/5u8BIzK6wHXya/A9AE2T+8KJi7sFeUeOrOz8BNH1pOGPUsBApfB03YLoAEnyey3aX9tja3+WAubDhAXt2V9XMNP0aLFCUWJGoi2n7kMBL1jhLxK7Vging5Ou1SVdsZC8NDdQ
*/