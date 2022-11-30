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
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
*/