
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_empty.hpp>

namespace boost { namespace mpl {

// empty base class, guaranteed to have no members; inheritance from
// 'empty_base' through the 'inherit' metafunction is a no-op - see 
// "mpl/inherit.hpp> header for the details
struct empty_base {};

template< typename T >
struct is_empty_base
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_empty_base<empty_base>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

}}

namespace boost {

template<> struct is_empty< mpl::empty_base >
    : public ::boost::integral_constant<bool,true>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,is_empty,(mpl::empty_base))
};

}

#endif // BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

/* empty_base.hpp
nmoxLXUcIDK60IiXbuCXkI54rCQ0ohP+O3jdf+Jjy/+Xqfn6S1drxuwgyveuPcZbDC17rzk6vw5WfqCVcyYDpH2uEXgZ2IHupRWNgAcnx73FsyD5Tbe8/XnO1xO9uCe6s6fS1DViXuX5nWd8Tov7o18YlmBEOtBLgpbmmsOVPCAi+VaeTw5359k5NSbPxxx5Nuk8m6w8myRPuOrsF7rRp6eP1Tx9VMj00TpBTR+f2XrP1v9P0/L/HNfEyjjKWoYGc4G0PeLdf44AInUlC5vUkgSn4iVeSmQ+eu0v0zUHG87f0T65+JKvs0HLJqM1oU9bfyZkrMhQcABbbDtTJ8BBg2SLm5tv5iHBqW0o+/67S1X7dO/nOmgf0hpBmapaFij10yXWlZHJOFmZHOlILcXn9XDejqb7hf3kasxAIlrQSEQLNEtdofKJvHbclbH0p701vjtmu8bP2P4afbsjyC+BtO3Pzm6jbQdgCKVW6Yg/6naCJygs/EouUfid7cbvQbt53YTynXzBrZpMKpEw5ez4BGj+MFVun9IRfSeKrBPf16YqfBfOcuHbeGYb+L6fF4Vv6Kw28B032Y3v9K4nh6+B/tf47rDOA4QS0tSE+2i+vp3zK+jOs+1KuAfbeboS2S2qFwa2MVx7T5NK6IirDbsSWCGVlTBfN279KjJ+Ok0Pm6gSX8jVJTZLRsMdJYYoWqnVbt+/VLVbs7RbqqFdX5U1UESSvpIjYVzJ+GVkPUGX2RRV5hSrzCYp88UBrlqCy+uKjlSl6rjfDZ54b538Y9//OVn19+y+Lv6080u6+yFaCTufiAbg9zyLPL8kM5pU6oX+bXTzkhzUPpKpm9CRw+nOHO5oK4ffz3ATyvVdTmX72effLtb0PyPmYNbloUVUGsSTBIgndT1shzi1/bSCakzZIi81VmroEz05Y4gvwir5vfMw4R8v2pZ8U0LbP1+cIW65Z7g0bnxENyW44ju4eaKJNG5bugRZ47aKfiCmUqvbGjd0qF4UPz/JVq4t1hq3pjPtQMJdkpXSSys9EMaXOzVuleqLjNw0wsJyP3CaAMaSBaJxy1jGhSy5Dv0YlmLoy5hlqt36t1PtBmKhQGrqrUOUDZP+BqJ4ViyvLRxBq/wiB/G/5dNqtXAlFym4LfcpbWB3RmqpqNoWT3Pq7K7x2To7fP7aeUp8vOG3WITpXEutXM/TufZDrqlIdpaVK6corynFCoVLaMVK3JDcT1O5M8Gb7aQEyXVfInJtLR6NVRVXAsMCEFeUfFi8hfi6R2y9S8MDkti3uKuVOL3AKP/YDwxK5CusGFRNbTItlUzRQ9dcqisxBDGQD5IoHBK5Kz4apOYGdHkaZR4Ho46JahUI0ikKoL9aEnR/HVSu+dFZDnQcQ+4tMIsAWrqLi5wCViXh0UDjJ1kmrlG1z+eKmo/uk+rpEqyk1VlGCxlT98exbtD14QRnBaZoIpMKpKJXUYEi2U0YeYmTjnoguoEui4+O2V1QsbvXJnqsQLnwfJgF6E52Y/SM6LY7o7zHPZqqkoW3Ppeu6PaHv0ExWofNoxUR7pMIlCj4TJH/09q/CDcrcwRP97d2ei9czEsl/wIuZZLoocpNv54txk/VK/HuFMtArN4e0VwdhGuKOS21EXGUcJaVdeWV/k/pQ9mfWrXGIsn5rRUSScOb+Jis7oIxh+ZpCQCEVIR+OFN8bo5ZwyBaQs7YNbPf15VFurK9e7t5dPEZcCHcXgc3CxeJzA6t0mzGongyv5eNIisa5S3MRmaHYfEpt1mP0yG/tsc1NO1XzRZd+7v+oPHDzkFjXsegMSMpaCTQ3yb6+3qnoPHLQNAYS39lXSi8ozwer/ySt8r25E3yf9I=
*/