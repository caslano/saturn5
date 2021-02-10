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
XVtzmzgUfk5+BcP0oZlu7MTOZaeJ28GAY2aJ7TV2sjuTGY8MSqItBq+AtO7u/veVBL7Gt8R2Kqhm0kYI6SAdHb7v6Egil5+/9VzpCeIA+V5JPs4dyRL0bN9B3oNUkuRb5Dn+1+DwuHBakD9/2r+8QUEEXCuMHOQ3sP8XtMP9vSTRGvRhSY5LSOqHD/L+3s1Q8nnu6Ihc10CPFHFR146wK49qXrUNrST/oylnldOz8snh0ZlycnhycqwdKtr50aGinirn2ulxRdHK/5Falm0nFWN5cZbp28BtgPCRZHza37tsuCC893EvIBfjK5JOWkH6VizIeVo0P1n2UvW9e/QQYRCSpse1p7LGIjTTlJrQhSCA0qFEr+p96FmWmVyZqGtZ1cK/8aNovXoU9qNQQ5g03seDkpy7y038dCPkOnes+N2Nen737v3Uk+lTD5gcwwsh7kEHgRBOSHv3vs6kH9wRHbOCU/XjEYpb0g5g/f66opbkI3attMxr5KEe+g4DtRl5LdSDpP0Y4EE7AA+kXkUxLZ2qliik5fsuTSSKuFFVU/V7feRCTG8xiXuK4yD6WODW+0yXJTmvVwNbim8bnos8WIk8m97Uv/WBl5jhbHXDs93IGXUUwYB2ldjAAwa9CnlocHB3jWzsB/59KA0H
*/