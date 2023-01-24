
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
1RKkHFW5q/9Yy7Q5nLhGZ8MMxKjOUgfdZ/tFfBX3zk1tcni6OnzoyhvUgDL759wQF1xoA197RN68KW3/kZDSlgBjKxX5KZx7Ye750gNK9OcJYj9RA8oFxfJQd5Mqefw59G0nSLHkMWtMav1YlHOuE5/v2FIfWFEGe8gw+RMG8zBI9zsflnTnf08qltjWvO33M9+TgxY7s9PJvzv+l7j9G2qa3T83tNVqlmM03IQKjmBd8uRu3Uvk0fpFkI9u2tHxl7H4S89q/GRixwxXznJ5bH/O31XkEOOEV35+K7cijg7P7gTliVJMWltMMcd/zBR64bjzqoFV4oVY8dnV3nYPPCKh820L3X3k4vTcpVEWSOvEbKDix8JVASkttzxnfPGLP7HXSROu2EmWDbhRfmG//aUTJEpGU8m5Crso8+74DC6miVokHth9JDKRXH0o+QOwc/TAWzHtO8eFyqFc0e/LFCeEegXOY+Mj4jvcDprG/pSwbsf626ACfI6fWWONe0aow2fWdb+GvZDuLpCV8ii1fedmORzfw+B6JV2LaVEkYvnz+foHFY2cyrHcBMK24LM/FXqwq8jk14nZIaZNa//JYnDrsnpPqz12TssisPN2esLzxIQO1LvR/bTvdptjCJb6cH/xoL1rW4zW/onU8wflluYxwdx2/2ZC8+ihhN6OpaGq4LaDYcwHx953/C6DgODN9EtThyLDaWm8DqyP
*/