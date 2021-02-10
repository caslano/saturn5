//==============================================================================
//         Copyright 2014          LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014          NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_NT2_NT2_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <nt2/core/container/table/table.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost { namespace numeric { namespace odeint {
template<typename T, typename S>
struct algebra_dispatcher<nt2::container::table<T,S> >
{
  typedef vector_space_algebra algebra_type;
};
} } }

#endif

/* nt2_algebra_dispatcher.hpp
vb89gDGtYGDrP+ruMpnbFtNwAek0Sdk0jtlf0Z/LmF1GExtECWrpk7cYpqnKBgbuegGL6/l85FGIKHz3+L6Sa14xUQvjW252NV9eRnMWzed9eHXh9KZs+akP1gtA0SgyWvjaUAVVAL3vWPpQUP9iflf3+iOHUWioB17w+tW6sSTkznEh17uOabQ3+sru/7+BZ6Dv5J87zCrkddv4P+zMVoRpNPQ9uYQFLiPLVco+T+PLZTIN4Gzu2F6OjG4SlsyuPr8jt9vt9ny32/VOQK6Taby6mfw44OM0mkzjAN6cMkNTALa5bFjXFcdGYbxpsM59uybxsazpHDWv012D50DP6HDk9uwKv9Bnf9JTmq4Ovixh33XevnGPVaMjpJBq47A2wvF1dTo/NEfnrlCIjFeV39HBM55DaTueF+vufSs7ORl5X71/AFBLAwQKAAAACAAtZ0pSdGFd2EEDAACpBwAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTkzNS5jVVQFAAG2SCRgrVRfj9o4EH/Pp5hyLwGlpFvdwxW6p2aBbrlSQCHb1UorWSaZbFyFOLKdXdBtv3vHJpQ99bb0oUbEjjO/P5mZOOz9vuFBD04O5v6MBs0OsVTyC6bm/6MZe4T9j1C3
*/