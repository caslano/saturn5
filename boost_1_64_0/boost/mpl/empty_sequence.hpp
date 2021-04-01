
#ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
// Copyright Alexander Nasonov 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>

namespace boost { namespace mpl {

struct empty_sequence
{
    struct tag;
    typedef empty_sequence type;
    struct begin { typedef random_access_iterator_tag category; };    
    typedef begin end;
};

template<>
struct size_impl<empty_sequence::tag>
{
    template< typename Sequence > struct apply
        : int_<0>
    {
    };
};

}}

#endif // #ifndef BOOST_MPL_EMPTY_SEQUENCE_HPP_INCLUDED

/* empty_sequence.hpp
PPAdcmR0CXrYbLvcm96IUCJjVZKtSK47elJZCJnpJYkaOfS1BrTMT9YiX46mWXEc0BplVGWS66CsoDZ8aD1ErVUoHP3x0KgfVpAdvPbJJW4i7oiCkCBwDHTmMcX4rvqiz/vHxMVMYD5AUlSjSmRs5al8xaUkcN9zyGCkG6HwCDqpHLu9tgCCpWPABgB53QQZea2bqIuXXC1MLWHvgNfrih93pzo1TTI0PRdBpIvO51lPKorFmXHLqdEGdcTnBzTBSpW7wPtKYJtdPN7exwBUx3A00X8wBpLGp82D6bmo/ComV7+qYON/s4kv2ITJiwhOQG6OveczXWaWc+Pw+BZJQup67PfsXY2cEtqya4QlDAdKfusDk0j79fL8Q6/1KAt1HBTyXL+5acIsZ1CUjvLtHzeBKAKDJnUdFAz0XzKe/Lo5aAK6c8TTMDqRnQ2+Gl3dVpAUa5/xE5KzVGmOPYCpkPfn3d1vWHhlSwbjvK+MCRf5n34aFY486qxzB5KeOKb/hJ855+yh1hQERksFzbW6vlWFU07odGp5rcI1jrU6nNYEJLYnaBD1F88D4A==
*/