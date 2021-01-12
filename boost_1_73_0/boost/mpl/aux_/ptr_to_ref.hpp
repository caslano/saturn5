
#ifndef BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED
#define BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

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

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    ||  ( BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        && !(defined(__STD_STRICT_ANSI) \
            || defined(__STD_STRICT_ANSI_ERRORS)) )

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    *BOOST_MPL_AUX_STATIC_CAST(X*, 0) \
/**/

#else

#   define BOOST_MPL_AUX_PTR_TO_REF(X) \
    aux::ptr_to_ref(BOOST_MPL_AUX_STATIC_CAST(X*, 0)) \
/**/

#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > static T const& ptr_to_ref(T*);

}}}

#endif // BOOST_MPL_AUX_PTR_TO_REF_HPP_INCLUDED

/* ptr_to_ref.hpp
aQMP/bTfjiYl06ptvLL1zhfVcQ2j6e0Xf9l59lt7nmqf2aRCm7s+OdOxmzX9rUvfXrn3h5t2jJ1yWOWnrj9H3bAoa/r6j+8/p/vY8VWvvm3R7Rtv2KOxWaxRNP3Tp8sXq9Oh/qjvVy6YvvfwZ7OPedO7PXTH4T9e8OY5JT+Ydc+aHr0udGweEE2/pPzty5ZddOjpa+674JmNDc9po+2f9T1Td2ZmJp9Y7ZMO3579/IGVrx/q
*/