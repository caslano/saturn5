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
yfuwoyFc/FNF7VWpdbjDxPGIBB45oijiel3fLle+ZCbrtvR4s7zl8dDdejN07JuLbB0s5jRJl8M9vimZNO+palXRbfSzHqWamCgVUgQpeoiZXf9nXuvS8i79j7vauz+SyPW/Nr83/K4doWePjzxnolRoO6tX84Jeo9KoxA+QHHrrPWB1GRXltcf+6gNKiv2+ksS0FkVWqfqs3gP02M17kQVpwUAXcFF1p2DG+OTX3JYb4gnD9ZSjBsCTqQIRbVrwsr0+W7GkjwI0LFf8SemDix6w5FeRFDjfiOrdsryt1j0s6hQEqddqZN01peV+CI1kPddyzxOmCKXIfxLDcesWkCqXegJ44iGOfyyppoTqCE3Rh6ijjY59rbomXy8wdZNvdpYAbq+AX9610xKN6VjWrfz2E2NB5Qby9a1k+A6Dw04IaZFCtBBXIbY9cvgyUBMX1lBcca/EC47MQLsLNZxOW/AYrV+qExbJflzXrWYCiMMfrn4pye2+iMBQoeFeIN9s4JpgAvV47EkH+RPkprkhNk/3MdMVJ2rcRqDBDQr9xbgNLqL+DPnEjtoEaA==
*/