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
JLjTXWAZxdfaX4YMG0uDIoxyTlZgxtb/OK5/Osc1HBqH+wU7ibHeli+pOc3sWSy7cYGgilbXfLHhRU3DB5+PnsTFvRDtyXY7+39ibU/j2u4/fgqAJxJIXGcqOvnaqOvrG4rsIQMThqdUJLQHWlvDM3edoSjlmqTRc8RUEliHteHOhnYPGpLgnT3ureWH0EwGQwV7S/7TSmYmTCBteE5SFmy6VgmUzI4o1Q6SXHYTTUOB22m9XKvcirYJIRzF3gRNwyEWV+BaqKNvEIhdZZaaa2fRFp0lC4w36Yis9Tv5z0XXNOkR+a5asdwCQEid/EUtcbXWmqJXSIUv5vXSCnHPaA5rpyurK6Ut1iwYZcFGGugdXdTQMnUypMvZBbeyGbx28PRsaXdr9QQ4lSzbhD6hYDvQydhPOJ9V593MIlJDEiiUetdVHygebOV3ol26nGTlRCyFU6vyRyLqiM4unSddUh42KGBX2kKi8cYWCe5nIU/aTrkM7LRNy3zdalyBnRuDuuZY31ohqFq14cEXFujf0Fucku7bWEYqyot4CBpq0bAXo5B1cymjZQe71FWF9ulIdYd8ptVhaj8MuShmyvJlMkDVmzdSyX139ueTt9/QtLBnEuMkb+0StVCiU5tg6pcKV2KL+daovIDG2zmT
*/