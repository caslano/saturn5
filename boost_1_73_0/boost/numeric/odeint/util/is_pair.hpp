/*
 [auto_generated]
 boost/numeric/odeint/util/is_pair.hpp

 [begin_description]
 Metafunction to determine if a type is a std::pair<>.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED


#include <boost/mpl/bool.hpp>
#include <utility>


namespace boost {
namespace numeric {
namespace odeint {

template< class T >
struct is_pair : public boost::mpl::false_
{
};

template< class T1 , class T2 >
struct is_pair< std::pair< T1 , T2 > > : public boost::mpl::true_
{
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_IS_PAIR_HPP_INCLUDED

/* is_pair.hpp
NygPpnjPEDgXK/yvUfAC2bNzwDqRDwMOh7wiZEOB28tpT3+LAOemEnhawUlNRs6hrQIXT9Ly1tKGdeystejpcJiTpNY/OzsaN7ektNxl1pm/t5Y8iIGEMXkT3hdgiyI+Wranw5+ObXUOytnb5m2rocfXFtbM89aGfeWstuq9ZBPh9fy4LaXxbcCFPeJ2Crc38g9ze8yXx6MO5JN1k3GD4Evfv87DT/76dLgLvXhtks9tlP5V
*/