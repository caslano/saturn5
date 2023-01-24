
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
bLWP0pssf0mjrXYnkehEBDgvPN1dtzKPftUty6O1vLEw0iYjpY61MtjSk0kVHpfYETYrwibCwPcSoxOtvOYBttp/EJv38LhW5oV7MvIHUGrYwhD/VYuL9h4AAQoysu6ST9ORmG21j5FLWrS2/oFYEroxg3Uji/XC0xHDddSNPqwb7ViOdSSLyGEI8hh2wlb7OGNuBvk92DaADDUGUNVMtfpLyqytkZMY9NqhBGGMNtF+x9i8Ok+eu+4mAtVdV0kD8GuRr4oehC48jeEUqJKQ2pWASO+mgMgygm1iUGf9L+HaQ7WxBAAWUdkhRuEehA/AvA2FTx5tOdL3KQLoy+2qBRFYbLQgaD9tbo+nQS+jni7a55NOBGKTZDIh0j7O1FS0H02X7bR375fMh53fqOYDVC8m2xAxzzCxpPHGArSvI0cyBZ6DohfYX8PEyCGYl4rHSToqjpH3gC6Wx5sw64QYudqOGz/lJ3FWBLiKmf+9Fm9BWjY2Yd4O81P8d6TRKipnfHC3RbWfrTxnizmCJWDKFjVJH2ExmNdAqaNNplDu1jyihj3yXA47YKqZbbM35mHYhvuG1lJMAOgYMTYNAAEO65WmOObcjWsr5rkERTqaz+q+2ZTvf36ow+8Hs++PPdTuezGC23Nj5gzsu81LRnRKnc90XOfbd2GH1ZrgC5FNW/54kjZTZV+Uzf2dn8LMTc3r8cXvcV7/9J0MfyBp
*/