//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593
#define BOOST_EXCEPTION_056F1F266C1311DE8E74299255D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_open_mode_,std::string> errinfo_file_open_mode;
    }

#endif

/* errinfo_file_open_mode.hpp
geVhGeTugj6JYZRLnJgzBWbv+44vNfVJhKr56sPccA78v0vj/6t/VCD/v2Tn/z0vDKW/fj0r/62bh9B/PvGSrf9Mf62Q/rNa8L8q2uP/8yi14bFL+kK1GPKlVb100Att5DVodjFpJM0uSt7FFtxzi2ibr3A+b/iNfvInzpF3unC+tY6G/A98byTteTSfu5cS8t64YmIS2NLXQnon5F0ml2/rOjuqjLZZmQNlOsD7vL4h8TOCuud+BbVTQuVtT9RVGGoUoU5QUNEXHcE8QmDuZTD1EkzMst8wxmBiCOaPBoPp8Ao4GwjOhQznH/cQnCaEwxfYNjGcJoRzG0Qp7w9de0cpVXzNPLHfHRJvAs30PPqIN25qkcZr/lYH5qqgORhUeY0feuAHg6TPNbN3S+99Iw1a9KgAU3QqLqoRjwQ7B14hs1lDUAYFUleiDv4U6eBdkE/q4AtYB3/u8V3p3PgfLfBpSDxDJZ9JJW9qMW98HUp+oiHxLEVMkijVmR0QQRtzuuTGnBNxLrJs0+p3xMYc4T/l6OS17Pdqah/SPYEgNTJNo23N9+JHdqULkY5Z5fFUYSSVx9adOjXVhd9ai3d1xsgwwpUxsyB+0mIdmgZhiy/BN0BuItqu10zY8MReJcb9P0BLw2piUr4TA9lUmijBmNKKlglhTlgsTDAIOlUtApb42L4wMVUE/1aK4LZRENwBJ/aBJKpgZFMtZJO4gCKLwIY4V4y0S6YKKP0OyMS3MxYAy0fpxFD1aF704b9hTVYKeBxZZe4ANR2cd3aUnKw1rHNDjJ1LTvie5JKhwX/1dwr+qePywv/V/fsE/xaG350f/mWDwnd09TyZ4PM+AcUb5Nr5rZeEaWwEicAn/4pfbcLK8UCRkHNr7xqpvGvmsZzb8wth5ViHoeryzpgZTuoDHnWSW2Rsnbn51wK28Nr+GcFudIJ9M8BOzSGHw9eeA4iYW64a18kxw8sfzSjnqYBj/inUpzDF0eYN+R7xGozH+T/elX6LmFW6fhXh/OdFpV/8YCfrF7Eijfy683Ud40rtnzCKtGNrWhHg7p+wd9RU45oyrIHQJ9D4gvuFyJSzDLQFzLuoKOUxvwM1FbokXkbLR3yILa4x3B90UotwcSBYN6sDrDLTdWpL2glrYIaV80WGSuWe0bn3hHabP852FYcuZ3uUK4d0TuVkOtCrAGi2X8+LDAeZkw/E/IaCmHGfJTeRd9M7gawlPP2W47tST2jJzxbvEi1OosMY+DSjpcF4kWEA3bgJU/orIysPfPeJdqUsJUjq1CT25w0SS/4ROg7H+jNqQ3IAFkKRA2JFNPpPTYrRv6Xo4Bj9RX8QDkNkLC8jzzK4/nHjUNJfFKnKlZ4PlIz9RkpRaXAK68dnxkBbv8aD07T3Y2dDyyonjMgDNSs/BQnMe0dZ7X0jpIkp4kX97/0NiSPdZK87m47JCpstr6ezDgceRet/2NtCYPFtXxGAbuoKDPuswIwl7ILnaOrjmXkTWMLddGpEZT18iLVyz4nwNvj5vBnyjSR4nT+jCc7VS5bR23io7uLLVXDbjOhFRFVZs693BUAhcgWkYXyMS4j1S9eOVJtx5rNYf3iTGDLuhHcbkLkAJAr08SZvwC5+Lc2uHi/G2VUJULMtdQW2WrGl1WTr4oRCNeDtkMNMVlnORG0bqe6a8OJfKkS7ho4jRDd90wHRaoHosNsqP73veMZK76t1en82J70n3GCh9x9oKvLG7VyNi7kaZ20U9L49m94vXR+QB5ElMTS1BKh9QZGidmvqsoKoHYYc5hcOt1K7UlGbKb2HUPyYE4r3bdjPlM7Qt+FpK30X6/RtzUnfbddZ6PsmIf+NbzDyLYz83/o=
*/