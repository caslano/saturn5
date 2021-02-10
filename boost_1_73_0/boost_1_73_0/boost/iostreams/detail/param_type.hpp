// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PARAM_TYPE_HPP_INCLUDED //-----------//

/* param_type.hpp
H7MjVM3sB3pKzWa8t5fk79msSodXhCf5VSfWVzPyJxzhprGHnuvd+dbSDNHT3hFqNtQWOoaPZqOGJiFeY/TetVe4hl4G5NvMJN/+NN1wpVm2orurV8qGw6lpBShwF+GN5mMEf9uWjp0AG0gLkIED3bfm8MVyUGhitLBsjHqjD18Gw3c1dGNauhk7unMjFJhuZBvI1ICIj3VsrZkfT/NDSBtwAR0YVhCC0yi0XEeB/jEKsb8KYj+EhmYHLtLWwFmbQ4daiMww9IKzel2PfFsJcN1w9aCux8FQzHBlb47sCxBaaXfI9UIUuigKICzEooZWrmEtyCf2l3DQi+a2FZi1lBl06Rh110cBtu3YH9haOGDDwGjCQ1YjUOTBCKyQfASuE5Dubkx3lQNCbGNPi8h3oEOIDQANF8JfQ5FjYJ8a0GjE3fBY08DvlC7lbyDXAWJIOp+gwURCcy2wghr6NJi+H11O0afz8fh8OP2CRm/R+fBL7PA/g+GbGsIWdOwjfOv5OAAiPrJWnm1hY6P/Q07+Xx+dzfHScn59hBBx3jOx/h3dYJoNfuQ4lrOkQ0KfLMdwbwI0nEJ2+jTBRhNiZi2Q44ZIkkcTWULdLpI4dDacSmjpQqgd13AD0hnrZIIhKSMfrTXfInkWkIYAh7ar
*/