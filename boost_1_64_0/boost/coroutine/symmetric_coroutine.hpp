
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_SYMMETRIC_COROUTINE_H
#define BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/symmetric_coroutine_call.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_yield.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename T >
struct symmetric_coroutine
{
    typedef detail::symmetric_coroutine_call< T >   call_type;
    typedef detail::symmetric_coroutine_yield< T >  yield_type;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

/* symmetric_coroutine.hpp
QHJmxWoZCtpzyxnYVIpVmAf76xpLaZ20HxNx5meuML6glwwEuUpoAcBQTxDnzmWTsgJi9qA1PcGc2RnMKO+GUSEZInO3peD40WvouQA38EFrt+sv4kHC5arPTbKAjw3Czag6A6nu5slqKkRlJ6/2AltaZgvzFTGHyl8MBBiEQ8tePF+4SDQsb1Fd/fKFSRXi24z3emKfqc7mhQDCcOhzv354RbvLvtVElStD2vjmfPoxTDeBMKdTjQPsJGEmoSOYyOa10lrlb3ATcy5QhMkPEEO8rqOl15Gl5giQz0PLPOPjDj6m4DOObXmSs9nnG37yxoV9F5pfF1kJMAL38VHBvRCw7Rej5BgXmKG4ct6m1OEddA0EXYAp3zcLm4C+zhpAalVBHFT1yKipdl2IyAA/jVNjj696LHgpwfZbS05uJ0k10mg0znzixId2oPVSrRJ/7U3y1gVdsTA0myVlAqt/MerccFavabSrjN42vujpbaJkQ5FL+aUvzla1kOgZnMlucvP5j0ebOp07uoHW2fb6CHHzyrjJvOrD8gBA27QwVD6gchZLAbqpmtC5kA==
*/