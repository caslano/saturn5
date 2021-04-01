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
E3pe6fgfzzhD/e7cXvb9SNbaDDf0lHqpdZeAg0kdMXP5JQ0zfGavaKQ3hejqHnG1U8Lxyr6PFiygeLcpnzI+rNv/WNrVNyZmaEyx6Na0fMtXaAXw9sxVUZL39biJLUlmTdOVkbSeB+AftWl96SWCnKNZvXonuNRtgTpFuy54OCQWv5Ul4E7Cg7H06jbdFZLMOCau7lPpbPtXT+FQOGccvEkZyv/HY30TM6uxWeSS3S307hDaTLw59VW5EmHwuDUxGzx/xHiYtdbzEDS+xPIRqVMU4w/HIemWc+OU47xVMhBkb0mGC16CBrvv3myEEwKYB6OfJ0i9VwgcZOkrrIaTtI8foIadMbmEc6nXOGR6yKR6Zx4ThRSo8s+3gt/4rnS0C1UAalQo/dmVy1ZSsCT0WhzrtwHs/D+r3cRsJmDo/CZxBrlB9YcaqKOzQTAfB6PnfGPgnVDMSAQJWIhkVMGlQ4NRA8jT0eiwohKznduXzaqiAEmIbrD+aMncdOcqyauxPJzX3zX+r9oCsmZHcOOqGUlQJMMuKWySXzNEHduWWyth8qVxOuhkKSwa9g==
*/