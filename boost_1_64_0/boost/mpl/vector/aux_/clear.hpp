
#ifndef BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/vector/aux_/vector0.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct clear_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct clear_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
87jbfcT24I/217YDKyz/s692Htm4f8U+269tcfYbCb6vxDy046wDn/f4nzH+WGCcesM83LjtqvPEc5vsf/aZV7rf8vJ4pk8xP+e85RbnE/fNsj4aF+ytM2/QaB7P5xo2mNeKe6vX40/Wm3Gvp+Pl/ZbDaePBC9H4ar7zdQvM49muP3POvLl5gOcbjTNvMx7c633qfFqsP9+wzePxPVtr640PS2zHfN/vQq/T3FfZTpi3Xvsb61ml8UeC7daPvU/sv1Z/xvUAe83fjfnvzl9Nf415x7D54VvNvw86v+Bz3XtW+V6tSteZj99i/+R5HvJ+M69z1HFwbIv5V+ch5pqnfM7zPTPFdqbf+nSz+Xvv6+ftbxZ6HvvpN5KD9jXk/fNu79fo9wl+xHbE79Houtn1OUvNX5jH3+fnqnHX077Rfvbtvi/Z/nrVJvOOQf8TfD7pPPt7fO5po+Wx2fbEPN8hx5e7nP++3d9r7J3s3+eax1tV6H1o/V1xj+2J84fbH/I++n6C7aBxpO8LOvik8+/ERS8P6sVR/33LZJyU8Gafq4uu36D/aY3l9z9ruxyszww+n3BezfmpA33Obz3mz70PYh1/HTDfeugL3hdfMh8w5rzeG+wPmxyntRr3Og+723n2I9vMT/za+NHnrXb5np7nHHc/Y/3YluT9ca9xtsf7jO3TOePjy0E5BJ9/tF0xf3vhIx6PzxttXBd9j6XH4fNLJ9uNN8j/vymo5+ZdZs82vrthe+/84Z7Pef/OcR1H9D383l/P1Bl3vtZPxn3Hg7zETcYVGZPPCScYZxx/tdvxfA71uv7K4z39uP2p6zL3vtq47z7zbqfsH3xP9EH7oeMPmt+61XWHXq8rU8xfJPt3f3dd6C7np6e6HnFmyLyh/UGc9c387ELv163r3Z7jh12ubzvj+OqI+brlrsebaHB88yH77/e7vsL883HzzpvWen6O03cX255dMm+6M7qe1XyX62XWfcp/N77Z8CvjT9e5xxa4fmfCvPEbnX8xXt/pdlbuMT9v/Lyvy3XiiYnm+yc/L3zXOOiQ7Z55iZ22u1cchyzfYfnt8vqccpzgfi7/237yZc4z2y4edr3ktlfYXj/l85XOY130/+81XxAbfS8e8Vxc8O/mP9fant7mcZ1OtT/zubDkAve/0+u+1HVWZ4LPYB2V/b33y9lu55+sJ7dnm5e2Pq41n77/L64DOmH8HfL+/4R5yTHHlw+Yt650nfSg99tK49I3Wg/tTw+br1ti3L1vj+Oyb9o+GRec/oHX3fUWuxvtP6LxQzRv43v+Li623rkOau804wPnSXb9xOvp+pS1622fityO851H8l1/c8H4w3HwkTWOS15lu1Ht/VLnePyjlu8c68t168Od5hXfM3m+S93vZZ7jnRrs//uWy/2TvxeJ7Lh+PTLxRCQSefDrE1d3XNsR+U8kwg++9Ehkx+aJHSfOn/hxZOLE85HIjcizj0Su3rh+Y/N/rkSun7h6YuL6xL+uR3ZEInf9J/JE5NOR8zf+G3l2R/CL5yMnIpGrkYnI1av//tyJG5dunIhcvxb58NVI5L87Ined+E/kX/zyNf74Br92NPKXr/4zcvU8ez1xI3Lp05Ebl74Yuc5/r12KBP95InLi/PXNkX/96ur1iUjkBX7y50jk55GvXWIf73o0Erm+I/L5iYnrl75+IvLryKcufewS2zpx9cYL/4z8N3Ll+nl2cj7YzFW2PR7ZHmFTd70Q+WdkYsf56zvO37iL4/z42NW7IsFx37jKqU5EfsX/Gbty6frVK+c5rSevHrtx/unI+ats48Tz116YiJyYOBu5dOKdl3Zwhuev/yVydfkN/selTZEdVyM3Jk4=
*/