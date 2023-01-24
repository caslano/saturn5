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
UpZ13uxqhfaZqP9R57diU91T3S/i/T8xuhmW3p4LpR4hxWn7UKpOvE/UjGHp//qNrdI0KSNq1v48O/U39lm255FL5S2J9hVmLXKK6VAuHf0H5JNXby7T5U9mwX8SuX7el5/qIC3ZgZX4/+LYBDrjfLhnet4hNb4VM1peLabP4/dTXCZdsdLVK9yRq+37oPOAJqUJAJ9q4OlP8s5fy3JtcVhNxbB2s+/5HkZB5XU5ptzEEvrA76Sd0TwLimNtS8kaSkgZVMLEpNGPsbO7gPmZCZ4BMSbsEB2j4jyNz4YwJdWjvL5N42kDqDdM4xTIMU3d/hNbgxtOch9NcKwl8zCXV1gSjQT6Gigvy6RilAZEPyaGE4hGviK7MctYh+IzDBfVzBr6RFIW64HPcOeVi2pmCqEZrAvTe9Ai+6ezcV+sQcG/PLSJlQ9GyST/MUljZTFvpH0u6sJWL7bCjZu5RnjGoTeMsJGg1GLjxwqNhXHHi+hkbs/9U3xxWWHgG5Acx8zY9kuCgDuK6e/AYi21Z2ZnpTtkGDUcEx5pWBgIDJRSpIATb27nrkH4Eg3T67skxAvyQoa8YSRwYTg6PDtAons8OnkzQvnUODXquOOd32XQ/MNMoNQSZiQYzZ7fZeRXIz1bV1pfWl9Zq3M/qSqSyAjs64fE+EoJkX5e/ckAzU8azqiDuNV7rZE+gpv1VrLm74VpmDrOpT2dVYsrE7Q+
*/