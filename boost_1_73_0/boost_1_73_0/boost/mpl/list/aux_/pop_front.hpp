
#ifndef BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename mpl::next<List>::type type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
nHEOiKHx7wNu0tHtut6ThSlJ29TE+zps8CHCuF3fnSMvVOdpi25cKFPLXjuVbgcxkwZfiRSOTabtGMK3DssUzGp1rIslXF9F2GkdNn4EN9pYgftORvCbnfQuNlyTF6qpC3/ycvW8vl09jnYrKfDYPx7BiLUdmEN/X84//LP/AFBLAwQKAAAACAAtZ0pS0khthJ0CAADdBgAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcyVVQFAAG2SCRg5VVdb9owFH2PxH+4zVRpQw1OSCklC0hdW61o00DA2mfHMcQa2JntlLFfv5sPoNX6sGovkyYhsMk99+Oce29iy41l1PCREwu5VPjzje+2Sqdm5NwtFtPqCz7eLurDjVghAGhhMycmR9OY1Og3MOf6kWvPiJQ7seb5eodPU2pp7Y8EnQDO/QCu0IXS4ie1QkmY8e+F0DxtOTU+gqucsoyjedjp9uHtDdVbId/B9G5KzjtBp9tyHh4evNILl1YwankEH6gRDDSn683QXSplM2HclwybMhrLkoPq6J6BVJLxoRv4vfDCPw8GA8RfK2kR6y12OWIt/2FJZjfr98Ayqg23Q2GUd3nZG3jB0fgzlyubRdC9aDktZ4GZAH6ksoCJVJEhpyvkiNTkIHV7
*/