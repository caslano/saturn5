/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };

    template <>
    struct is_sequence_impl<assoc_struct_tag>
      : is_sequence_impl<struct_tag>
    {};
}}}

#endif

/* is_sequence_impl.hpp
trYOSxfXPH2qo3lRU1w7resvhiyr3D8lUTDb18OGZTA6OlKpPlajpwe/F0g8XKXOZ5u8o2d8iOB2Qhg6/ocwfop/Z3kK4v3Bv3mKQ37g7+0QS+zvhDjc4p4Q8ylp2l2VRD8w88LHRM8hui/Eque7IQ5Gs8+M26cIv56i+WGWYE2CJQRbJthKwW4RbINgjwjWJ9gzgmEbEWPFjsXSFmzdycV1bg9Yb10gEa1NLl+mEjk6iPHesnVOYggh9UDQhns=
*/