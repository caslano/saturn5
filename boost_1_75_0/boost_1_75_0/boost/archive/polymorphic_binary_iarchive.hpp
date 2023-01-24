#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_iarchive :
    public detail::polymorphic_iarchive_route<binary_iarchive>
{
public:
    polymorphic_binary_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<binary_iarchive>(is, flags)
    {}
    ~polymorphic_binary_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_IARCHIVE_HPP


/* polymorphic_binary_iarchive.hpp
WdcxyfVDAIb20fonxjwp+n9V9usfS6jzt2WNXR8Tu0ox0pQn+WO2vxgj/XzsTm5wJ59Skkt5+yCMGCPn4by1wskKNhhwpOcwXuTgdYjlHGGpJiwE7uIDf0DgDzWwupYOknh7A777dHyA395Nq/HNWvoeFJsepaYntIJDawkjzJ8bFBXG4QZLiy8phPWA3HFUz4+fj4tH7sIyHoAZV8xKgsmdfMhtqeLphXjhyANCDg6xxgKMDVpIyw2Y/TNm10NWCUbZARvacoa/U4gz8LaVlZNMWHGJZudU4/TsYIYtxNek1Q0U3wmRPP20rkNI2pPxw//r/JNCigPg/Nog5F7n3zqcJUIaZRdI/7KZkF5bRVGgiKGXUYxg3kqZukqbQgZT6MZQeig1jIU9rdX+QKtNU/v5qtun9ihN7XewKL1DXIflKS14n0DlQE92gkZLb0HL46v8BceHffWqZqndghhDsydrcruDZOqSmHZ/SVfk5jZzoQ0v3YCAQwSYhIA2OEeH1vkmJT0fYD0Q9p0OsyBsEE6U5YzbEqJYTrktDXweAFKx2ARo9hnW052/rneI4X3LRhmyDQa5I4L+qINyYNDtUN5RjYXeDw6W3aXaN4jC+VA4Jfo6EJdqZVPysLdTKGwwpDOgEsR4Vj5xO4cPEYcLXdoqRmMK8jtAzXq7A/I+iDyuzN7F1+3YgegA4EbwMugflyqHKeUHUCH1rRiM
*/