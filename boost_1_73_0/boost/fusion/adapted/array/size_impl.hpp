/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template<>
    struct size_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : extent<Seq,rank<Seq>::value-1>
        {};
    };
}}}

#endif

/* size_impl.hpp
OHR6JCHSkupGiNrx7NBYf4T+E7bMy/QnouIEH0BI4m+qP4ld94MJofZUS6Qq3TYyUmR45EiIuP5J7YXi6xd5zFUvlfnMz+i7YRznTzmE94OWV4Q9vm0ncSn57aJutfPfFXHmG4y59jNY1cSS3/k+4hmeC6udCOwRS0OZiZlfUjaT/onCoiq6rSpdc3FFb77vGRZ379oDSdFy2oMverYJ1X9N646Z4o9klGx9d+TL+S1WKrbz
*/