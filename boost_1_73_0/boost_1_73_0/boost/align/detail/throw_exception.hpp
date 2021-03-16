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
YqyL8DtWnrrio7QLbjlz98i3nv/RxU8wdhPht91wS8Xm1EH/Kms95vaut49pZuwjwr/7w+PpV53Zd9Gi179sDq064i3GjvUg/uBL97367SGLTnuypOfFp4r2XsBYJ+EfnZ9zzcwnur7r+2zXQ2fvmnwXYw8QHp2w/Yu+E64+cev05ddnFh30DmMfEh7e13nOF58e9ezLPyyfePRf5v6SsXkpiA/6ZVawZd3MG6++497l/5ryPDR8LeGvXfyXZ8s=
*/