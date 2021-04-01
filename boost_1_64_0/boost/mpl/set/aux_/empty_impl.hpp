
#ifndef BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : not_< typename Set::size >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
E9bmFncbScKaIm6ujXKN84AGBLE3BZ4zyw/liIVzp1/2KL6YjeEEjkM3AsqXTkSCgdxyRVDx1MN61syTehvNwsuIAx/0TQah2D5QYE2PFEsqed8z/W+QR9EHhzQNYH7ifjyljKtr4vXQdSiDdIA3219FV/yeThhAqeZxlTIpD2NshAl9eYcnw+Q7Cdojl3xnPGxIkHbKXghpd9KCnSmhf7KthW0ZuxIKZhJvejUNkSniiU3ezl9bP6oFw70FAxgBk2B+5khQ1jwBfzkYeO/+qs5yipFU8/JFDA0LagOwyE/2UdumlbpHHEzMzomF+kB8YWnMrNAGxdJmaqoF0QSctxKjRl0+2soO8G4rQ7ObyRwCm9INrciUR7sUO2Ov1NeHZqL5Rypg6jrWz7clyiBk1MmMW5plygV+uLRsWSvJZEU+gLjPqfCQLiiFtz2DNs01Si+v0jxYd+oa5blb+I+lW/Xzf0Mx5p26k7ng8ngj2CLR09E2Gx30wREvD//mL3loOWJRb3Vgtsg0P/H/pyIaq0qVIA1rRpefFuXQdE/4O1wpKiTXQQkbVK83IQ==
*/