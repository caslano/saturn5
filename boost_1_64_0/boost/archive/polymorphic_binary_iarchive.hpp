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
IuheCsNiXCHGRdW1FaV2V6wBOLPTryzvYTFpm7h1lr6VWfWVARoFHWcB3umfP+QH4CN5Q+74kxLNaSUwilF1Ne+lT4bAVp0kD8+bUBRkwD+Z2Me5YLNE2ZZ2T4AOis5eD+tkGV3dvuWqqqWKS4xG1Ce+bCZiau7QhvgrjBKKiHSayw/f6HBmH6ip3j8KfF7LFHS18h2NpyCmTUa9IoDoHJTsh1an3SSwjpFyUKquXu1ba9QX2S8W/Cc4tX0c+IQoCacqokyWhO+qIzQwc/3VYaq9g2JGoamDnHMTVIX/1L7aAZvHfndttvFtMexcZdnmiqJYv613YJzG2uRNi2tDD4kReiv6EzS3QUpNt5q4ZrSqgugsupftyTo+209fS21iq8ATKix8HJw9hS8F+i/qZMHGTGqpfJc5VZ1vf3BU0/aMDn9qleeE9G8FmuGmM9wczVVZlNQ15lrMeL1drizKERmble97PFkx9hJgHb2kU4cF3opuMgYNL+zduh8gIuXsCKewXkCCijJuWQ0aOwMsxKxkyC3+qtdXsgtayQgn04S+lTnOb0Zhm4N3zA==
*/