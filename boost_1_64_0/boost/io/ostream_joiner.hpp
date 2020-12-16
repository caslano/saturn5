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
47RDgH5LBlv1ewF8dcH6heDbdS71q+tg3x6u8G3vEKtvv5iG9EH65WT5ffuwUz8egm83heDbTWH49uEwfDs3zVr3R/RjHwfbRndud74t0uJPsqXKPuDrWN8+rPDtCUOt+r0CvnSLfnBul76d7lK/9I871repX+D4yzCrb/8RfPmyfvIzPPvvV+19HGnd+3j+x+59PP/j9vv4q2H4eNVpVhv9Bvn5JBtJrzCFfeqdnplCsI8vBPv4QrNPwHhBfTvsY/jQ0uHWNvI68qtV2sd9PyDS40+yp/qZqYP7gXpFO8kYYdXxDfA1KnV03xc0utSxsYP7AuoYOH7F2HkeP+A8ygGfdkzoWDK+yDqG0t/2uZfp6LufCz9fs9ar8nPyyvr5Qmjb/YOeZVEWfqOsoGeOmFFW/d6BfqmmfvZjIG87tOfUEPRMDUNPyGCrp+yrzQo9P4WNMkw91WMYnzi9ywhBx4wwdIQMtjrKvnpotFXHv+rXLVNH6xjELgf98kPQLz8M/XYNcVeHdWOs+n2QhrJM/dRjCO87XXdC0NEXho7vp7lrjzWnW3UsQ9paU8f2jwHUUn6+y7e/dgTp+dcQ+lXVtQNlWcYAfGOtev4NejaYerZ/DKDBpZ4NQXq+F4KequsHyrI8Jy0dZ9XzozSkl/SUxwDOc3pOCsFXm8Lw1fPS3PU3U9Ktut2EtNonhm6hP8MjrVl3Y+3rDnwd66OcZxD4/uQMq34fQ79UU7/Qn+FTXeqX+knH+uZYhW+eUOj3KfTLkPSTn+E/sfdNpHHvmxmftN83P3Hpm0fGW3VbhrT5pm6hP4OLtPiT5jior4Ud7JtLFL5Z/zWrfp9BP5+pX+jP4D6X+vk62DepX+A8rAlW/f6uXwdN/dTP4PVO75xC8NHaMHy03uX92oYzrTp+oV8DTR2tz9CbHPRrCEG/hjD02+Tyfi1/olW/S6Bfk6lf+56Bmyi7NFdAfQ3s4HY4W+Gns86y6vhlGv4dN3Rs3zOwdtydjtrxjm2LsxVzrGInc3CEmcwDDcOAT3pzHGO2VhRXlufpmwpJ8X/XlAPMed2TBO/ZWLvVXaEv86LvzugrYjAj2q3ad2XeT/1jRV7lXk9BvJ2jwYt9yQoqVijjEpMXx0T/hw9VwzcP9/Y4W/BM0hLwfyh0SdT3noUPbJ2EeRwelBk/+OTcFM5PN37/IoS9GUT8YMOGrBvYBceEXczxJ+iPY9Bf2vMCeuKY0DNwTu3Z/oL2cu3BHtBS6Jl6PKAexf4WnKAfcC3ozzn+wwT/r7Qp+P8t0PdBijplvvIe35XeAu/aSjFWRHuOFTy12ulaN8SznIBYY52ETePhc02TadNeMySbBu418k3O8Y/16Ohuvr9qPuExEd/NPu6sOg6rfdxWdbxV+7iqU3box6/XXhw2t6Bf7v1j32wYWzn1a6HHu1XHZ7WPC6uOj2sfb1gdH9cunq59HOKfj9GPxzXGblme9sbUjx+asDd59byVHRdX+DhjmuEj1o5UMeZdL+k7Y3FxHSdsAcK5gFhcr8gxwBz4XpZjlJGvq4LvJTkGGPninPPjGkJ1uc9LfOkOfM/JsdYc5Pu9xJfF/OLayK/codw/y+U68L0hx24jn0q+1+XYbfbyMT/wmGufYHvyJbPv0xg7VcTpBCYDPwR+jbH3JgI7o2M8i7H35jP23ioeLwUex+8KxtrbDDwBvBb4GWMT/h14PWPJ3cQYfHuYfi9QY4zHTsCHgVHAA/z9IvlMf/nQ3n65sr/8zZ4vR+Zz8INFsl8xv7g28styKDdZ9hcHPiD58HGQL1H2K4V8qvzqHMo9S27nDnwT5fZLPpV8E2Q9WiifY36gFvty90p8GQ5890s=
*/