//  boost/chrono/thread_clock.hpp  -----------------------------------------------------------//

//  Copyright 2009-2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/system for documentation.

#include <boost/chrono/config.hpp>

#ifndef BOOST_CHRONO_THREAD_CLOCK_HPP
#define BOOST_CHRONO_THREAD_CLOCK_HPP

#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)

#include <boost/chrono/config.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/time_point.hpp>
#include <boost/chrono/detail/system.hpp>
#include <boost/chrono/clock_string.hpp>

#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_prefix.hpp> // must be the last #include
#endif

namespace boost { namespace chrono {

class BOOST_CHRONO_DECL thread_clock {
public:
    typedef nanoseconds                          duration;
    typedef duration::rep                        rep;
    typedef duration::period                     period;
    typedef chrono::time_point<thread_clock>    time_point;
    BOOST_STATIC_CONSTEXPR bool is_steady =             BOOST_CHRONO_THREAD_CLOCK_IS_STEADY;

    static BOOST_CHRONO_INLINE time_point now( ) BOOST_NOEXCEPT;
#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
    static BOOST_CHRONO_INLINE time_point now( system::error_code & ec );
#endif
};

template <class CharT>
struct clock_string<thread_clock, CharT>
{
  static std::basic_string<CharT> name()
  {
    static const CharT u[] =
    { 't', 'h', 'r', 'e', 'a', 'd', '_',
      'c', 'l','o', 'c', 'k'};
    static const std::basic_string<CharT> str(u, u + sizeof(u)/sizeof(u[0]));
    return str;
  }
  static std::basic_string<CharT> since()
  {
    const CharT u[] =
    { ' ', 's', 'i', 'n', 'c', 'e', ' ', 't', 'h', 'r', 'e', 'a', 'd', ' ', 's', 't', 'a', 'r', 't', '-', 'u', 'p'};
    const std::basic_string<CharT> str(u, u + sizeof(u)/sizeof(u[0]));
    return str;
  }
};

} // namespace chrono
} // namespace boost


#ifndef BOOST_CHRONO_HEADER_ONLY
#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#else
#include <boost/chrono/detail/inlined/thread_clock.hpp>
#endif

#endif

#endif  // BOOST_CHRONO_THREAD_CLOCK_HPP

/* thread_clock.hpp
Jevmk29AvKuIN4vyBhh5XmPPdqFRj0GunbBTRSLvVVu89gjsU1vNjminMPb1iWcpeFrrPFpPop9lDzOUDYw9/FV++9Ld2Sbjk4LiH7mtjgTapLygIrswp7yCOkWoNoMdWMbGMZJnbyNbYBsZMXwHWR+NJRTgPvCJkaRPYUlOfnv0J2MvGr9HZXlGDJ+PTzunDm7SwdfXqYwAPdYlG/agywJYCz1iqvQoK6ko0/UgO3hJj2mkA5VNPCZKu4VPRvnx5lFerJFnPae+Ppt5Sd9plI4x0nkBuo+vV9OGM/Tnr0r38oqSsgIo7+evyi+vMGzo49NI3ynCqBv0NfLIL4Nbn1NvsrPhU6L7GLpPEVSXAN09KYKudlxKW0AZdM/w071Dl7C6M1870r2Rn+4DjLyWv0jnRqyzL67ylAwX/xYuXjFcHOb5xzGGi8O0LdfpclzlO6l3n96U2G10QUa/SHwIoSfR1/5q3taJX8Sktds/se9N437/arh4xfP/NtaFim883/jD0HGY5x9fGibeNWz86gl6lwRd5HddDpwJaM1/1we05L/LRJXfdj3Pn1rw310AzfnvKwBHAaXC5wcm3zPl2QH5fK/TWLJ6gc9w7ONPwF2BfwbuB6zwoAzk/CGcHg+sARdwugTYAjwT2MbfT5ok2AcL/CTfNxIwlu+bxd9nGApM80fgFsCjgNtxfkdOdwO+Grgn8/0aeBzwQ8DZwL73qpBvEfgtul/ge1VeBV8j/p7VJcDvA/fg71r1Af4AeBjwh8B5wH8ELgbeD3wd8J+ApwL/GXgG8BfAK4C/5PdkHAS+i79j9Sh/x2oL8HfA26gt+D0exnyM/HnQM/A9HgXguwx4PvA+4IXA7/D7NP7I79M4DrwF+H0Myr8DHozn+nHg99C3tgKPQgM/AXwgCr5C4AkYbLYDf+vG/YEXxKFNgN2YDzwF/Gki9jqBy6DPi8BLgHcBbwbeDbwN+CUjltU3f8LfZOfAWNaO9P0N5HF/upjbsxvLjwKUsvwYlrf59f0e3B+vAK7H6QacbgncD7g9p3sC9wfOInnj+zs8d0C5Ib6/cxHHCGdwjHBbQ45/75l/eZBcHMvVB1bATfzkYljOGkJuFvPPBrYAz/GTSz3L/Xry/TJZPkuXI8y/Pfy7tpzv25vlSlmuHNgBXMH2nMLP21SOMZ7GMcbTgffU4vsboxD3WQFADLIRV7znPN7NgvPC53w/C+KEa/WOFooH/gXvZqH43rPF9p7nO1mWwy7dgGfX4n0sod7FYsTgBp7BNeJv16P83YADAIGPf6UCugHGAxYAVgO2AvY+WRebW3fVXXVX3VV31V11V91Vd/1nXf/K+P/cCxT/r++BVj7id/7fL/4/F3k7/fP84v/jQsT/38L+grmAEsge+EmrjtnOPXf8/4/EP5j3KH3yKbRHWeQf/2/ktTL8BY6f9XROQPx/PMWsN3SYO9SM/0+gswGB8f+JFyD+vyhE/P8Ztk8Fx0HlAqbgj7U/B9iH4v+D6wo7MN81lDctKN7fzTH6ixXXydyK6uSjrwUkU4x/PaJHoq5S14NjvKefwwc23s8HVkn1C4zhnxYihv+QSdD1Me8DvwiYB74ewuRXXyOGP1Sdmbe70b5zKX1LuBh+5h9pxPBvp3Tnc8bwTyG+2yidZZTTMWQM/2Dkz6L8lWFj+KdT/rqAGP4yce4Y/ueJJ8o4K7CX0v0D4qhLiJYpvESjwrme2f4x/OjHgPOI4S/6hTH8+9lf6Gxc1cefTgdGmeOln28sNzCGvyjQJ8a8u9LDxedvBr5E0bmMdGpjnwzuepfUGoWKz98B3FSRzdKpfQ2Z188aj3+aeKam3yOGNvKPx/+Y6PU=
*/