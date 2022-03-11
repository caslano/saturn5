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