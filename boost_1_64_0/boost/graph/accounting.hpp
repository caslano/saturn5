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
rgCsH2Hu2yOwPz8DrDthM+1q7SPsBsJibLyvCLuMsMtt2HLCagCG994Gx6NZLEAYxWOtzWQ75++O4PNHhkrNohl6hcdOh6GrJPQgQmMYGk6JhL7E0AUIVbOpDLsHHVW1B531Ktb/+KzG0xBPMzxX4UnE0xlPKh4/nn541F5IJXNZmo6i4278lI5KYIEC8ex0RRt8TbpRju0ZZ/X8QNylso5d1x1uTKt2PQeXfMVZiGMOBqjA5P4GvuREnjfcJh1YFefNpG8vXAS+ylhKVy1XvWrvos1CCNqBb/haLKl6jMMwCfEYX+Zvn9TCg07J6V5et8fI3NM3ZtXA33uzo4xD4bVetI7k4pyD3uHrje/wNvEyC+varHj8vS2rto3zmycZBxlg4vWXzFVx4AzZSQ/Z3b28WQ+MYEb2CLTu4QusbL0AIfBrh5XVkYFmk6hCeeqGcRchLiSsHa1XOqYaX/M3EQvJqfhtm7T9s+B5hwMwOgb3D+JcKeSC6aMPoxAzCqnhGOvoG7IT3MtTWz8ykg38OiehZTdk1x2Z2mkEb/G4DBDjikVYpoY9P/6G18Hop7uxrt2a3DUpufuLXGtA49lcxR5e4l1zwIV7PInVeOcg7ZWY6mF1g/6QYK3zBVqvCdUDqQfL91f43ijl54biaKmBJ3dT+CJVeEbso0tdxXCeFG48Y1DFxiYX4iDoV11IB0iLpmGNGeAfGmlUzw29ejGdG66Ty1Uq4zcZyGFU44UQUhR5EX8CzUrCawON5/Cd/EqXezJkk0KXrgTwKgA+QwltmRKSxwQqR2WXMUp3LhNvFwsuyqLq/Ert4c3uKpvDd8OfKfIE/e+8gP71Abbp/9fHpH8/lhtas4aeRgX5D3MYWBzNpTotkIagVtsvHqLNpFJ7sXsQ2fmqa5WrYDRns0PwZHtxbiADCU54mY1oPUyKY2HL5w30RaWDoC/mO1udnAPg/oX+ainSCpqTm4Kb4JCiO8rhC9xyO37MctCR4S4XZX98f1U/hBwjzXgCOFwEIW3fPfskGhR9mcGw1eP2Jq8ZV9tbWBqWf25v7v5S836PVVLMbTk8areZ+sO9PGpkILq+t+CeqJEgVKl7uUvawMAomSmjGSRAdLVB4GDNARmy/ekzzgpWlJOnOO51ABejvkaKHXQotpjTIIONuadbuvPEhjN5S1bdkQFwY0NU8GO1ehrpSf4yu2HF+mTuuihUqFXWyZG5yS2z74BNi6/dmvRvytLRJ73kbbfW+00ZxmQNuENW7nEv/9LYPPLP97wF7fsJQu5+pzdpLdHo0asfa6PZhXpw76bdGo3etXr00DWoQhaq8GRUy+w4KxZLE6qLAI+xAT7AUo2NhFg0yo8VDxsPONJh2vdNOTqRBsZOjocWwVsTw3kaD3atSyCJa8yk88rK92XJGtiTboKVM9vpVv4mwtSJzc5u7BytoP30tQxAnx2OxAp6OqXRz+2ntlbcNab7sqQipCKTKKTC38Sk7Wz0lVPq3Vdc1h1cjNLE7MVfNPbuG6IT2aC/X0yRa78RIhg8i3KyksHjeAGAfo2JzXXOHHGYtACfrMKklunGXnQ8dcKNTyJxIHLQxWXkcHFy1ycXs/+Bn1wEQapHSxa3PIyfUMdw4/Uwq5PSBWJ6AQT/1H14c1MPSSDuFAbEHjkUHNMFkPRAdGtznEzM/bHepK/NmrIagcZmoLEZaGwFD8RH+lzRGhe3x04U+89u2rHutrYHm1+PjEtzyxpkTcTQqg3938/V80HfOzGSvUptLaXNYH6rhr1cEV94tc4IWrWVqi9DJAyb1LfGKXiZwvj4kfYM4uTfHN5B/T5q0v2RNGWJq1K4HML8uY3ld0L1TkVGWy4=
*/