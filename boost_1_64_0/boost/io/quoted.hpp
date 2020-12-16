/*
Copyright 2010 Beman Dawes

Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_QUOTED_HPP
#define BOOST_IO_QUOTED_HPP

#include <boost/io/detail/buffer_fill.hpp>
#include <boost/io/detail/ostream_guard.hpp>
#include <boost/io/ios_state.hpp>

namespace boost {
namespace io {
namespace detail {

template<class String, class Char>
struct quoted_proxy {
    String string;
    Char escape;
    Char delim;
};

template<class Char>
struct quoted_state {
    const Char* string;
    std::size_t size;
    std::size_t count;
};

template<class Char>
inline quoted_state<Char>
quoted_start(const Char* string, Char escape, Char delim)
{
    const Char* end = string;
    std::size_t count = 2;
    for (Char ch; (ch = *end) != 0; ++end) {
        count += 1 + (ch == escape || ch == delim);
    }
    quoted_state<Char> state = { string,
        static_cast<std::size_t>(end - string), count };
    return state;
}

template<class Char, class String>
inline quoted_state<Char>
quoted_start(const String* string, Char escape, Char delim)
{
    const Char* begin = string->data();
    std::size_t size = string->size();
    std::size_t count = 2;
    for (const Char *it = begin, *end = begin + size; it != end; ++it) {
        Char ch = *it;
        count += 1 + (ch == escape || ch == delim);
    }
    quoted_state<Char> state = { begin, size, count };
    return state;
}

template<class Char, class Traits>
inline bool
quoted_put(std::basic_streambuf<Char, Traits>& buf, const Char* string,
    std::size_t size, std::size_t count, Char escape, Char delim)
{
    if (buf.sputc(delim) == Traits::eof()) {
        return false;
    }
    if (size == count) {
        if (static_cast<std::size_t>(buf.sputn(string, size)) != size) {
            return false;
        }
    } else {
        for (const Char* end = string + size; string != end; ++string) {
            Char ch = *string;
            if ((ch == escape || ch == delim) &&
                buf.sputc(escape) == Traits::eof()) {
                return false;
            }
            if (buf.sputc(ch) == Traits::eof()) {
                return false;
            }
        }
    }
    return buf.sputc(delim) != Traits::eof();
}

template<class Char, class Traits, class String>
inline std::basic_ostream<Char, Traits>&
quoted_out(std::basic_ostream<Char, Traits>& os, String* string, Char escape,
    Char delim)
{
    typedef std::basic_ostream<Char, Traits> stream;
    ostream_guard<Char, Traits> guard(os);
    typename stream::sentry entry(os);
    if (entry) {
        quoted_state<Char> state = boost::io::detail::quoted_start(string,
            escape, delim);
        std::basic_streambuf<Char, Traits>& buf = *os.rdbuf();
        std::size_t width = static_cast<std::size_t>(os.width());
        if (width <= state.count) {
            if (!boost::io::detail::quoted_put(buf, state.string, state.size,
                state.count, escape, delim)) {
                return os;
            }
        } else if ((os.flags() & stream::adjustfield) == stream::left) {
            if (!boost::io::detail::quoted_put(buf, state.string, state.size,
                    state.count, escape, delim) ||
                !boost::io::detail::buffer_fill(buf, os.fill(),
                    width - state.count)) {
                return os;
            }
        } else if (!boost::io::detail::buffer_fill(buf, os.fill(),
                width - state.count) ||
            !boost::io::detail::quoted_put(buf, state.string, state.size,
                state.count, escape, delim)) {
            return os;
        }
        os.width(0);
    }
    guard.release();
    return os;
}

template<class Char, class Traits>
inline std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& os,
    const quoted_proxy<const Char*, Char>& proxy)
{
    return boost::io::detail::quoted_out(os, proxy.string, proxy.escape,
        proxy.delim);
}

template <class Char, class Traits, class Alloc>
inline std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& os,
    const quoted_proxy<const std::basic_string<Char, Traits, Alloc>*,
        Char>& proxy)
{
    return boost::io::detail::quoted_out(os, proxy.string, proxy.escape,
        proxy.delim);
}

template<class Char, class Traits, class Alloc>
inline std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& os,
    const quoted_proxy<std::basic_string<Char, Traits, Alloc>*, Char>& proxy)
{
    return boost::io::detail::quoted_out(os, proxy.string, proxy.escape,
        proxy.delim);
}

template<class Char, class Traits, class Alloc>
inline std::basic_istream<Char, Traits>&
operator>>(std::basic_istream<Char, Traits>& is,
    const quoted_proxy<std::basic_string<Char, Traits, Alloc>*, Char>& proxy)
{
    Char ch;
    if (!(is >> ch)) {
        return is;
    }
    if (ch != proxy.delim) {
        is.unget();
        return is >> *proxy.string;
    }
    {
        boost::io::ios_flags_saver ifs(is);
        std::noskipws(is);
        proxy.string->clear();
        while ((is >> ch) && ch != proxy.delim) {
            if (ch == proxy.escape && !(is >> ch)) {
                break;
            }
            proxy.string->push_back(ch);
        }
    }
    return is;
}

} /* detail */

template<class Char, class Traits, class Alloc>
inline detail::quoted_proxy<const std::basic_string<Char, Traits, Alloc>*,
    Char>
quoted(const std::basic_string<Char, Traits, Alloc>& s, Char escape='\\',
    Char delim='\"')
{
    detail::quoted_proxy<const std::basic_string<Char, Traits, Alloc>*,
        Char> proxy = { &s, escape, delim };
    return proxy;
}

template<class Char, class Traits, class Alloc>
inline detail::quoted_proxy<std::basic_string<Char, Traits, Alloc>*, Char>
quoted(std::basic_string<Char, Traits, Alloc>& s, Char escape='\\',
    Char delim='\"')
{
    detail::quoted_proxy<std::basic_string<Char, Traits, Alloc>*,
        Char> proxy = { &s, escape, delim };
    return proxy;
}

template<class Char>
inline detail::quoted_proxy<const Char*, Char>
quoted(const Char* s, Char escape='\\', Char delim='\"')
{
    detail::quoted_proxy<const Char*, Char> proxy = { s, escape, delim };
    return proxy;
}

} /* io */
} /* boost */

#endif

/* quoted.hpp
xK8zUOhMedhuUAaOiTKEHWaIPMXxwJiFMdb+YgDsUK6yQ2VofRzyCJoTsA5JlTqDN7R6lvoK6sy6F2WwXVHnQUOD1ox0V/trtUrntWW6M7ny1eoQdQj21W1Ir/LV+B5qeesU8iLSX4m3OM+1zHVhyrxHklm2cVVP/JPeDQ8AbRuEPjtA5gLvmtUlhfru2poxp8X0E5W8TI+/RHP+S8HqNWvL8FXtV+SX8q4o9qrnsMi8st2Uc1gaQ7SbV/JNj7yfvSQ/55qQF3IGzzWhPMY8irqo0Oct2O2Le7i7fjzq7UGVj//6hr5rmm94eVzOy3mh76tsN09jtZh30S/lvU7fO+8P75Z6dhy658Ta9fb766r39bXfx1i9v67dPs8dN/9hVE8xD2TIkrQzUxJem3r5a3n3lD7+e/v5LRyL5P0/+EC7HMbsE4HrgEzH+2u0FUW6q5juamAv6d3eCD0t03Vluk5S27yc6a6Q96sjfy9FOUXkLwbGApdL+5FlMV1fppP3I7uE6ZYy3aVAj/SOLwNUzvRDmL4LaIL0rjcKeCawO3ASMJ7vnAYDpwC5/yLvkZAn85H3X+zDfJKAScBkYAqwH3AE36VNAg4AnsN3BlP4DmEafxv6trCceFlfxbu2HsChwN7SO7dy41oPnMn08r5zcyjnudTzfOAAYBbwVOBi4FDghcAzgEuA4zmnYCIwm3LnAGfwPOsX11vWk6J+Syj3N1k/ZZK+uMbZ6juW6cZR33Tqe4aUvk6VPvidC9OPYvrRUvpGph+oSL+J6TdT7m/TXt8BrkSimHmd2tzzLh08Q3FsJwKVY3xZjCGXg+pBr4HkfeZyQUWgLaAakLEf3BRQPdIvAG4F7QO9CxozFedAPlAdyNhn7TXwGvuszQJp8zGOBtwOasW53dwDzQsy9jlLeQ7jrsAjoGOg1OnQDVTD8UV9bDH+18YeYSDkWSTtA/YayBz7Q14TgLNA5dyrKwvHGoFFwGpQPegtUOzz4AUtBW0G7QYdBrWCUl/AmNoLX82xrH+ydyXgUVVX+M1CCCSEJCRDRJawyK5EREBFZVUEjJFF0WKTQAJEQhizIChiVFS0VOOGSBGjUqWKGhQUrUsQRHCNCrKKUUCpYptaXFpp7f/O/O9xZ96dZCLa9vs6L9/JP+/dc7dzz13effeeG72iV/SKXtErekWv6BW9olf0il7RK/zlBRX98t///YEfx74GwPzGv8aHZa+cO9DPVf58c4P6OcDGz9livsyei6gDhcw52HMMg5Q5hBwQ5go4RxA8L5CnvvuDolf0il7RK3pFr+gVvaJX9Ipe0St6RS/z+i+v/y+aVZRvvvwf87v/s9F3/+i7f/SKXtErekWv6BW9olf0il7RK3pFr0Zfv/D7P4zYTpkR+P/zfPt/3mfY+9M289X3r9z/WQdajw0e1Z/I/rQLskZkjhs3JrtkRnZefr4fO+X9c2Vf2MupJn/JDIO2dVOAr4mfx4xY/C8EVWrt9DJs7l27ObB/GsFmTy0rmiL7SH3gOetTk8dvdEQutfbEPwndg23uYQ6EkcD0zJIwfNo9bvQveVljPuQ+Mx/8pgE/Fvca4wKk+EbDLfv9S7krxNrr2l/Cv9LoiRh8sCG8Bs96Q56HkR5P+Wsx7vhWydxfjL3FQmJLOBnPPHi2NDH8vuPEMPvnTLmnUu7W/jnIEM9sGcrzeHvPuCqX05JGS5rFj9xfzXvwBp+3zz3/51MvxoCehWDqPnXoBZS2NB/OlKXohYjKktM34udcY5heHxgm9yYa3G8ITKAt73+K+wlaPVD9JiXa5UgdAO4z3Xs45BsP4jVKle8akS/TH7Q/kWmCzLpLmNjPFLI/tYL71Kc=
*/