//  Boost string_algo library yes_no_type.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_YES_NO_TYPE_DETAIL_HPP
#define BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

namespace boost {
    namespace algorithm {

        // taken from boost mailing-list
        // when yes_no_type will become officially
        // a part of boost distribution, this header
        // will be deprecated
        template<int I> struct size_descriptor 
        {
            typedef char (& type)[I];
        }; 

        typedef size_descriptor<1>::type yes_type;
        typedef size_descriptor<2>::type no_type;

    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_YES_NO_TYPE_DETAIL_HPP

/* yes_no_type.hpp
/bsw1+E6Jqt5nLnXeiP+gfNmcuyh11SXU3XhW4MmwZ5hmehNkBm6aVC2y1zkPWLL112/iFjArLQAB3OiOt5fpB5TXagXuv5jvyYeuIzBxSaJgZpEBPZyR75x1tDhGUFkhtGtkMLQEZ+F19UiBusqFH9xewDpx3LxKa3B5oAYie/+VrD4Sksr2fJ2sMxn9+gpAnawNExJpY21TcGA3Pvf0fHNULoWudPWL7mvP/ioHYNtf6jkGzGgaC8j+TH8/ZbHFOSyoCzoy9uJq7CsZCtYsIlk+O6XzYXdU7qFKDETjW0Ni4wG6Nl6rob1IpAfH19qCQRc4589HbdAAB/BlnujeLNcC5/a+7F4TlWzi9LXKsgYFXOCzp7uyJHajtcmpdtQFtVunSaMa1Aehq5rwqUNhJPX3Jknt1rs2umt1wE+MuyzOyA9h71ZlBUx10thAq6Qh0PW0u7QTNHd6SKY7kJaFhen06za1iyR0US45YNuRePbvfSo78eckCDmtPrzw933D8MHmH9nUjeHGzmt7c9EfbvK8KWdF/YwcnLZOrG/pUQIajNMGJYQFkMMK/mOOQKnsL+3VwmtQzxlsRcNLXEFLrT6tl5rOkCEpQ4WDmg8Gm/F8J8+2D6Suw4NSvbFPfZ2Fhk3hrgIzmrmJJE9l6PpZztZp7xn8O10e268Yk+c9catEbvHqZBgoGtzHk5P6N68DQs55hk0996Nu/1T
*/