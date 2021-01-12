/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_THROW_EXCEPTION_HPP
#define BOOST_ALIGN_DETAIL_THROW_EXCEPTION_HPP

#include <boost/config.hpp>
#if defined(BOOST_NO_EXCEPTIONS)
#include <exception>
#endif

namespace boost {

#if defined(BOOST_NO_EXCEPTIONS)
BOOST_NORETURN void throw_exception(const std::exception&);
#endif

namespace alignment {
namespace detail {

#if !defined(BOOST_NO_EXCEPTIONS)
template<class E>
BOOST_NORETURN inline void
throw_exception(const E& error)
{
    throw error;
}
#else
BOOST_NORETURN inline void
throw_exception(const std::exception& error)
{
    boost::throw_exception(error);
}
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* throw_exception.hpp
1p2sZcF5LquIzw5+WtD7dim4xil4BLJoyKJh3CBdKVVvkxQFToopSFGBFBVIURHJ66/18VLv1Q5pybvXsSVqnDQRpAqP7tzf2RM9NlXRHp37BSgbL3fuL58a8XQu0mrKIRb7D7CEJ1n0UU/QrP2ZDU8DkgKsX5P4sDh5nQPuwTEiyCrAcRDl2BOl7v0rIeOS+G6K18ZlUZVszRVo4CvZKtAnMrFkK+HgWaX3U8TW31ebrREP
*/