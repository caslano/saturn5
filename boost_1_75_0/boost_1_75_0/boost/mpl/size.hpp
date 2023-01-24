
#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // BOOST_MPL_SIZE_HPP_INCLUDED

/* size.hpp
BDGfKxArl6IkUu9jkLBc3YOYskZb2iufFBiOm5Jgp08JT7Ae4Sm6KfULeUvfCZ4EGHBdsQUGbJ7yWFiD2Gwa8dtlH9BU7fCFrndWp7yx55+dW7bBsCEZnSWAWzBhmH/PtQ8TLu7BtEOM55JXugi2g8ktC7UYeNcgZ0kxB8akWHR127Xu3fYyQfyKEgGDhUKiruGPXLjSjKVWodwNwmkHP0RL9DXeQTHi/WVmwXMrEL/i83iPgsPe8bOcieJaWIfRFBGmPJDtGDxfO+lyF9vkN+VpyP0KU5cPuIVQPxmTygOLXgzBID8I/mNXyZd0MYQXsMx1l0R8560YyBM4Bg1+aYbEQyICb2vwrm9cIh1KTou6kvaAwc7H1UfCEJt7Hg+CVoSUcfE3XpIEWJBcyOyUEuz9X/oFW59+aC3/z/gGyv/eL5A0cbFg97C2OyeStyWTrlnsj8CFd2qG35Zzof9Rd4VtjLjzS6TuStJ3yy2aSuprdQnu1MXZ7ffYT0bBlwgfKai2+hAiLH6KU1F/jCWEp0bEFKXypPr4kcKovy+uHWeUBTusLPvCsDpruV/5I0aRTIOflrabppvbkv/D+WIan+iyUSBdDSV7kNghX+9zemd4LxYJHGD4Pufm5ibp4knxMidQDOt02p40kfy0Fo/XQfU8Rsde7U7xEhaEvfXoJS6OQqqIUpwcGoi/LVhane21LTvFY4/xIpbSd7Xa
*/