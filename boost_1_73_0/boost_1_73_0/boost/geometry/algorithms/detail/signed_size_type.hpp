// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP


#include <cstddef>
#include <boost/type_traits/make_signed.hpp>


namespace boost { namespace geometry
{


typedef boost::make_signed<std::size_t>::type signed_size_type;


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SIGNED_SIZE_TYPE_HPP

/* signed_size_type.hpp
zDTOd3CfBJav6JtBTkaTBdT58Gp24u0wk2TMUuC4AXdZZoyE5GgIE1CvZYY7sd3aDXG1qgzlyFVm2H77/v3Bmz5u3WD5X2vSjNTCLRvc/Xz4hzc5m8wmh6dm2z+d/HMMjEMR+LA/IKPKMp2DsFnEaM8A98AmC5EkZi5AdgdUlJMCFBqNaq/hRmFCQp/vJwYgiEt5w0hFsBM+hvboFpWZRE5jAsQBGzYuOALyJQ3FBkxY5qBGBlEhAppCIFOVJ4IiGZimZaJFnpilXSrNU4psNezhHRoW0dYULRLa0I98UQCpubgGw71586kPLl1qGoBAv880agu7IljxIAAX0mQJJCeihhas4DhDVZVhWAhsoqwgw4PSaFoIO4DzcSY2sMM+UBhpGd2Shb9Ef2UQo26TRHqS1dBrdVwqtAUO8dDVALZpq8CXSK0m5EcgQmh0xT6A6YUIuDHHRBsNLZ1rkEw7Qj+8+0RTu6y4wTHaPz5Phz2aV5ly3ulAlUd2u9f2D+923r7Zf9dvTk/Gf1yMj2Ye2N2bnVyOpyfnp8foAGhFqC8lB/mwh6HdLEsEThXRqAswKVzOMSzIeDQebfkG7Nho/De+g9yvf2bAYxcnGUKWfMvNSMBncN7keKkh+wKUkRgtLTIFacBxZbaQDS80
*/