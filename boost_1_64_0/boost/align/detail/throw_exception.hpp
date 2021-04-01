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
MkShn331j5r73aksfvIpczU90zLemb2fH3+3B7UkxV/ap+Qw+3AO/3k+JaFSQzi/cMXl85Q6YnwsdArBcHlyHAttcCBQ9BE7SWCczLd8RWaxLytWa1roX46jYIjQVDtQy3bHs3qzndICaq6Gd4B666iUtLlts9fk9zDYI/ElG/3VrcH685tBicZQSDx+PInTap/frhhPcLH4pl0QYj/wdEgku26buKijz0TzXFg8ASldjhNywYnEoit8vpz+cidcdyAoxrmBsLwqd7+WxpEEJVxsdwQMkDtlnJrD+yFzOL0CH4Z21wWz9DkoKJwKjt4AV7U8yiNkwFwrr3IjFkCO3D9NmcwKNI5eXZPZfeB/MxJTmGeDHtg73bl5FsrEtcwKTBobrtTZ00VSa1j85z/X6yknNisZemk2UkOBgnDT898nOfgFD4efKLDs4rB3yxWRsTYA11FM49ybvDdTiFmnZYWH78pH8DjmRqIYfg1IkAIqkZWCso4VAb6g9YBGsCY3EYbwlaxkAbFsD86kSko1yhAFBK3KPT37k/IKGCOX/uSYT8MUvtLwkTgheQ==
*/