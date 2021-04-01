/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_IN_05042005_0120)
#define BOOST_IN_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/in.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::istream&
    in(std::istream& is, Sequence& seq)
    {
        detail::read_sequence(is, seq);
        return is;
    }

    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::istream&
            >::type
        operator>>(std::istream& is, Sequence& seq)
        {
            return fusion::in(is, seq);
        }
    }
    using operators::operator>>;
}}

#endif

/* in.hpp
ppoFFwDytvedKazu0tPRf3JfOD3ZxmBfOVHqQqptxC37NYDGsvrcX7sHSLXUZgbeor3sa2cTumwfMai23894V9wA3oUnw4GWBnlW5oJlmehODsbsP+9sLmKX6bz31Lsf+tmpRV8bmGivg/Q99QjaXVJTgc/365KA7PWJVqA9WCe8/QzlLOQLi5s7oKL1XC5XcJbxtu49vcbnza9YHeU00QXVygDWh+yI0fp04HjlFYJWFzaGAcGNPqBIvdn4bB4cx4vFAz49yQOkB9sODq5uafi6CjuI4ZBcY5XHsFK8BE/aVSZ5gb4FlUiKAiqCYDZ1GJhf2Do5DFqVKRPhho/e3fMLIQUEJCcWR/jOZYHzKr6N0ywEtXD7VmnT+YYs2rnbV6oO/QtkquqxJfmoukoOo4R5I0YINCrz1kaMvXZViGwQIozDAmUDKCVXoDxkcIhzWCjS0eM4Y5pynUPyPoi2vHC71oR0k+el5BN1L1x/ShfHuwoeU6RksjV1s5JItyAZ/EyaA733vGe0gQylCEDI6xdlgJsCkzMatJedRIbDdVFg9aFgZFJPuhjOzA==
*/