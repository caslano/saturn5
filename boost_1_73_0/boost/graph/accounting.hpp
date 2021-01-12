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
1Uspny/FPr8XFic8gN9ZOyTeeJF6DsQWM1f49CB2nhIvtq1L/NmBXaGP+6zniNgxqqwPkce2Ffh1eCn4gyOeKMMOkG/YGcQFkxh/N8Mj84JzN+cXmc6oCwvnupA4Ehm1MSbfoIwVko8adJ2Y+/NDiI+JrU9ejzgO23ZdHePyC0cc+hx2CL8cOY6vz1c44lps9C33YWvhY4D8ToRv2JO4YuoG4PDHv5M271t0FPnd+KuwwHyK
*/