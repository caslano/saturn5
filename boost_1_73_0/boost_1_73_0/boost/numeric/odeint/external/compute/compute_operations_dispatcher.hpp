/*
  [auto_generated]
  boost/numeric/odeint/external/compute/compute_operations_dispatcher.hpp

  [begin_description]
  operations_dispatcher specialization for Boost.Compute
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/external/compute/compute_operations.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for Boost.Compute vector
template< class T , class A >
struct operations_dispatcher< boost::compute::vector< T , A > >
{
    typedef compute_operations operations_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost




#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED

/* compute_operations_dispatcher.hpp
939Xc8g3A60oGWj1pzCctmDFrbAhzIezb8ntDOb9yaQ/mi0guYb+aOHJvg9HX0NAQWIG8L40aEncgChKKTBrNN9uRME7oVJZZQgth5auqhW8MFEXSG8+WOmgSlJiz60FFhmuqk1NIRTdLoHbac4NnNxO4k7wKwAY0CrVme89Bx/r7RVLvvcaF5zkKvMb66gfmWdgThT0MNqdXkB232BsI/WKSyaUcG2PYjdx8qUfs34c76OIhMjrWOR2t4/seF6xbpOzAz4X+CvCoqOG9L6wTiQZzxhNIfjMe68IHiXjSXIzuZpOQzh7HeQ6ieNkHieD/myYjF4Nu51eTcZz6pIWvR2zVIoXeFFya5dqq03Wakj2BT5Q0UNYa1PUx38pk0rkqir/+B5fVPrJXzuJmB4MtOmKO7TuBY/Bb1BLAwQKAAAACAAtZ0pSeewSa9cEAAD1CgAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTkxMS5jVVQFAAG2SCRgrVZtU9s4EP6eX7GXm06T4CbApxbazoWXQqbBYcAZyhwdj2LLsVpZ8kgygV77329XdpJLG44vFUOsyPv67LOrDHq/b7WgB8+u2P/HuPDpNS6N/sITt106jr9D/Ydad/h8zskA1irf4y48
*/