/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_OSTREAM_JOINER_HPP
#define BOOST_IO_OSTREAM_JOINER_HPP

#include <boost/config.hpp>
#include <ostream>
#include <string>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif
#include <utility>
#endif

namespace boost {
namespace io {
namespace detail {

#if !defined(BOOST_NO_CXX11_ADDRESSOF)
template<class T>
inline T*
osj_address(T& o)
{
    return std::addressof(o);
}
#else
template<class T>
inline T*
osj_address(T& obj)
{
    return &obj;
}
#endif

} /* detail */

template<class Delim, class Char = char,
    class Traits = std::char_traits<Char> >
class ostream_joiner {
public:
    typedef Char char_type;
    typedef Traits traits_type;
    typedef std::basic_ostream<Char, Traits> ostream_type;
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    ostream_joiner(ostream_type& output, const Delim& delim)
        : output_(detail::osj_address(output))
        , delim_(delim)
        , first_(true) { }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    ostream_joiner(ostream_type& output, Delim&& delim)
        : output_(detail::osj_address(output))
        , delim_(std::move(delim))
        , first_(true) { }
#endif

    template<class T>
    ostream_joiner& operator=(const T& value) {
        if (!first_) {
            *output_ << delim_;
        }
        first_ = false;
        *output_ << value;
        return *this;
    }

    ostream_joiner& operator*() BOOST_NOEXCEPT {
        return *this;
    }

    ostream_joiner& operator++() BOOST_NOEXCEPT {
        return *this;
    }

    ostream_joiner& operator++(int) BOOST_NOEXCEPT {
        return *this;
    }

private:
    ostream_type* output_;
    Delim delim_;
    bool first_;
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && \
    !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
template<class Char, class Traits, class Delim>
inline ostream_joiner<typename std::decay<Delim>::type, Char, Traits>
make_ostream_joiner(std::basic_ostream<Char, Traits>& output, Delim&& delim)
{
    return ostream_joiner<typename std::decay<Delim>::type, Char,
        Traits>(output, std::forward<Delim>(delim));
}
#else
template<class Char, class Traits, class Delim>
inline ostream_joiner<Delim, Char, Traits>
make_ostream_joiner(std::basic_ostream<Char, Traits>& output,
    const Delim& delim)
{
    return ostream_joiner<Delim, Char, Traits>(output, delim);
}
#endif

} /* io */
} /* boost */

#endif

/* ostream_joiner.hpp
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
*/