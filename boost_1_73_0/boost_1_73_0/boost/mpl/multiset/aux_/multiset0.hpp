
#ifndef BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

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

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

template< int dummy_ = 0 >
struct multiset0
{
    typedef aux::multiset_tag tag;

    typedef int_<1> count_;
    static char (& key_count(...) )[count_::value];
    static char (& ref_key_count(...) )[count_::value];
};

}}

#endif // BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
OlD9W64b6zoAq+uwMQ/UdZQ2W7DFHRjFoDat1ydd+yxVeOtJFC1i1SbFSw3va6jBmcn6zX68oeKG43Y4Pm5631QK4s1UKpcuTaUOZszf9M7/0BZ0ni5m9UEMUDYf9DD7zp45fdl/d4ud6OWnKB2bYuzl0a+SpahScZwoGDP3ypCiWVKkS2WxxyMi3FFmfnbWOB/Idafw6KO1PKLdA8c9cLwXjgfg+LVavv9yPxz/Co4P1PIHcEEmdjVGsQfhiFM=
*/