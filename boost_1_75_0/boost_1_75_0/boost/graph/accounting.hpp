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
w+aLu8nbtYs5wWfPu3rDom2+mP9395P9BcfJcWZvp7tqlIcVMRST7Rfh0YiYWCxwZB2T44RaqaoHP07ZlOSz30+rLow4z5Jhd5f0yGPOH2ks6Ifya72J9Zp5eYqiZ17RMUG1kJdjgp8B2AFRPpTSoYEOr154V0yt+ETF55/4DE+CR058s8kKs3MedEkZoKRNMkmeJuMaf07UssxfKH+uKJhKKBWF951yv/O/AVf+NcqeoCYdIFguM14fXmLtoDP9tcDGcNHbxXuosjamfNEHfhrWSjRI/fRDyqz64SIHjJr99ghgWlj5y97EA5laGsLf/35DJ8/DJaDsqHLXq7OO8Se1IFoXiOrzBz9k4D+/CCpr4nvN1bpqeKsMeCpc0ZRbySJmMN5nzeaUtXPOG6KRS9/3DGUtG2KH4u77LpDtcMWF0i92WxKKRFWm1Fy0qml0cYYhhoqKitHSQyd8cVyYEpsYlHT7q7vYW0uTKGI6X3VhFCkRUQ9vwKNnh8XDdV2lKEaYvHz09obiP2biThYKXJB0yEDTPh8+Jv73M3UMFgg+ZRHXlpLruDRfc+joOZSAfWfPTvXxhEUZksHC2ADFJ/coDDEMP1L++600f/CIQdkD+1GeS27u+zGHry3xX8sWXkQiXryQwtwuLkQ+bF57XFiU11z6dxsGXhe7B1aF/XW5E/V1++mBw6SL6mOWJYoS0HnHaBFYKmXh+CRd
*/