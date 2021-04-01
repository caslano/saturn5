
#ifndef BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename Range::start type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

/* front.hpp
baIQTzIl8ZqXWJr8Vg/HJceNGiR/0B5sQcDUwgNR4N7o+Tfhr57bpARvnOxP3+8D7iAtVeLR2zGyPe6S5VUewd82ALyxpUhhEKh6asceSMIJ8kfNdQHW7D3pu8CWcukVKQLsP/d8Ee0ejjZySPohOwS6iDa3rhNr5py71F919l8Fz1qWI5fsYCQs2uSMYQxFb5YWNWwhrogzSet3LwbiKu/26pRXGZdOtVCSsJQTTbhC29SyOrFpIGxs8sgUwBCu9pdSHPJIRMWU/90gPRRMOeUBhZOpaDD1u3UlRrjPMEo58YaIj0eVLywsjYYKoR7cXQmo/3TMBQ8fCZnlGPytBogevqj9/2X3wyJ1daStDLyfflAHBIC8gtNUr19YNkNlEw8UfIt4LtlQ3/HY2jjCpUWf5TUKBmuhlgObXL3yCTo2W/JzHuhyYT3o6clG8Tl2uZWV0xQCzQp4dqCdhBmXJbo/BAOqAuG39TlUmAIxSmWJXrRC/CQQVhauGxczZCQSICJLOK51vpnr4b3pp84iOsm2bhDvdN334ZNrCBuefr4TWysC6LG4ggyfmg==
*/