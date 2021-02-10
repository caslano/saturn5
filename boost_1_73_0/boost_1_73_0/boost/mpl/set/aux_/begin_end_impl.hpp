
#ifndef BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/set/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : s_iter_get<Set,typename Set::item_>
    {
    };
};

template<>
struct end_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef s_iter< Set,set0<> > type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
kttq4zAQhu8H/A5DS2/KGrdJ2KVBGEJ2YQNl7a3dzbUqjWMT2zKS3NZvv5KcQ690mvn+mX/ELBkruKEUWNNXyi1Hmj6UliaFPMuXsG2Jayzp08LzriiBJdcAlsw5cAu3WJB+Jx2bRhIwTUM7pe52TzgawuI52//M9n/QKtTE23ZC+iQtGvdma0LqZayq+E3JCQeuTdMfUDkcdmNrm6Elhxq4OJI1wExQEp1M4cx1pXy5dbI19SiVx/iqv+EH4YFs0JJUcUfFtjEW1WiH0WLNtYyFkiSx6UOUN8aBvAc4o4FJbrmoSRxTeMTHh4cIFrhaPK2evv9Y+dMSF35hyZdAlpy8CCZt24Z6ezJJhEN6biiFQQ3LSycpIOt5R/McQhvYkTH8QAYrrTq8993fn6tDlszhyITqOt7LGbhOkrvfWVHu8vWdJ+XZS5lgPPq56LUhock60UuO257qChX/I91UE/qOkFfWjeTsjjPN4Bs5o29MrewNsPcQ6xCDVlYJ1aaw3eSbCF6LXy9BL4J8UxQ4q0bhR0Xw93VXeteuWSy5oJLrD/0PUEsDBAoAAAAIAC1nSlLyXcDFMQEAAPoBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODU0VVQFAAG2SCRgVZFB
*/