// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_ACCOUNTING_HPP
#define BOOST_GRAPH_ACCOUNTING_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/mpi/config.hpp>

namespace boost { namespace graph { namespace accounting {

typedef double time_type;

inline time_type get_time()
{
  return MPI_Wtime();
}

inline std::string print_time(time_type t)
{
  std::ostringstream out;
  out << std::setiosflags(std::ios::fixed) << std::setprecision(2) << t;
  return out.str();
}

} } } // end namespace boost::graph::accounting

#endif // BOOST_GRAPH_ACCOUNTING_HPP

/* accounting.hpp
kK1aNl4+HhtQ4rgN5RZH0Nq02++Mn0lqhthMr0lMXGC65vFeoOglYYgjBK6YZ/FbLHOOKO2BR1yqXDrj3IGV8orKWFIZeuyaHWoAKpEmfUE9GhAFdwox6Pt3QD2TW/jw4qwzGILpUERreicRKoUgi0i+Kkc16JEOJloqqeE7KNuIh9afljU0VW5udV6mJ5WUn8zan9jcl9gnQtwWoY2omjyUvgxaINhPakhQ1w71CofhbHRaPAwOXzxTGG6IE1K/9cTInVmVdEbv27Q3HnbOivoDB9LAI05lLnniFVVge/sk1S07Tn8p3rNo5AMC3XHn/PX5ybHSy0G26KTtztKU6DPiGq51nDjrsaWm7Szev6vW1u0pkJiB/YmPmuRZEYd8w4qKQ64cUSpf/L2pNSAVpN8DlKgqdhUEzMWTwWlvMlVPRej7PFAN5+ZMxHD6iToxIxlVv+HMKlzoWtweYY/FVxz4zdBjDezPoHj4yyfAOodlZ1OQwx5JlMBRfzq9WKZRQUSKg6pWfpmgVNAU2Fg4YFpE5/m5+tiSvbJzzZBK0rN0elWQXzGL0BNsgbNW0gH/E9KcjnlXXmHAKgtzYYX2yH3VpXgQ+lFvr8WC8KnJ5swErUy7pvDxccrrFIlIQ7++LU31ogJQ8G9ZHQLo
*/