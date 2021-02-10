
#ifndef BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct key_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : first<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
NBrMHGk0TONumEbwDabPw0KU18v5n8mPPSKrQy+djs1O7nvv4irbiPL3ISta0/+inPoQ+n4LkoevhEKWqwINZlblJxUs44YHpKdk2YYSb7Qs8W2JCj2SyjYs+CveVHIf8chcZtv6bDQ8ArCVa6VB55Ww6cImGN3RMbof2G2iW+RYmf0mhLscVxGQvOSro6aAAKt4ibuNQyFf8gr42ixtTS64yWVlEXQHAWaHKnllx7isWdqUXvSTcRqP2hd1+Sh5SunPlk9/PYbxIB7eRc+d5iU01rC23doahUJjWx9Z7O9endM9RZUvtlCPBHxhUIHVAfUzgSXXMEes4EwvpTkjbOOwlmKlpJFCFtZg329CNxyFt7Z5OvOI8+WLKc5+jxx89cjBQwe+gnE0iLop2Blc4Dv0orTbhybcJnezv/9c8LpmSSZpvf1Tc0aPiujpYX8AUEsDBAoAAAAIAC1nSlKw2/lgBgIAAFYDAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODIxVVQFAAG2SCRgnVNNb9pAEL2vxH8YJYpyiJAx1FJLFxTHmGAFfxSWNG7Vw8ZewGB70XodYn5914ZC02MvXntm9s17b8ZYskJGtGBDhJN8ydWxZdWei7gYIsc1AzQ359Pm
*/