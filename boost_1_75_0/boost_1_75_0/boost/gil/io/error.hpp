//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_ERROR_HPP
#define BOOST_GIL_IO_ERROR_HPP

#include <ios>

namespace boost { namespace gil {

inline void io_error(const char* descr)
{
   throw std::ios_base::failure(descr);
}

inline void io_error_if(bool expr, const char* descr)
{
   if (expr)
      io_error(descr);
}

} // namespace gil
} // namespace boost

#endif

/* error.hpp
/fSnfmr3wUZaeJ32a3RoOSVGyUmbcuW5lz8AlNPARwRvo715Ucqse3sE+YVOFLDwvYB9dM5/rnrmkBz77ZocuzvWWC33io1ibbQwGSNQQiCX84hHnT+cXOtNnymLfAr0O4esNJ8IH7sIP7tIoNwGW7j3PW5Zfkk7u09vPv7i1xtJoGB7WshrZcnNbfk1Mf0pIw3G/iqeRH3E1XLtGWsLQOyr0MCIeqLIB1cqXiKMagfi3Qj7XclkTj49dTq9kDuCgKX0aq5wlf4RM0ZXhT9vkT/eBPyRMDR6UxDxJjGE7EcQiKGwMD0tPe2JUk0yp7SIpNZLotvIM+4Ni5m/9yxE/yQ2kIxwTAwDWTPf+PwJZVJ+xhUYNZCM5kxNd9PaeqQ9SCUY/qf/kG9Cy3W4cadAm4g+OVt+mG/osUAYehKznMXxHTjcaPiwRKlOwlB9kEP0PlRSXDz0fv7WYEZiRhkhI7fesYifY8Wz4OmtatgjMVtPukLmYQ4BXcUlunwrYd1QFJ7hzZuwZ2/7KSSpOiMBHMIT60Swzd2RbDwpwgZQmN/HayJWuU71kSPDrkb3ED2+HyFStrurYEoy3aLb3xcQupKjWBKzw3NCvPJNElZhbVIPqPlsudb+DJ8HPHn1EDbVWA16mDltm4Li1NkdHhiIJI4M8zaWJKn7tOvms1I4NPjpIuDpT3dLdY2VjPTnZd17aTXBrhY8Ex7Klap7
*/