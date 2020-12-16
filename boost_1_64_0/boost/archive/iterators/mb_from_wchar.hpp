#ifndef BOOST_ARCHIVE_ITERATORS_MB_FROM_WCHAR_HPP
#define BOOST_ARCHIVE_ITERATORS_MB_FROM_WCHAR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// mb_from_wchar.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // size_t
#ifndef BOOST_NO_CWCHAR
#include <cwchar> //  mbstate_t
#endif
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::mbstate_t;
} // namespace std
#endif

#include <boost/archive/detail/utf8_codecvt_facet.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate wide strings and to char
// strings of the currently selected locale
template<class Base>    // the input iterator
class mb_from_wchar
    : public boost::iterator_adaptor<
        mb_from_wchar<Base>,
        Base,
        wchar_t,
        single_pass_traversal_tag,
        char
    >
{
    friend class boost::iterator_core_access;

    typedef typename boost::iterator_adaptor<
        mb_from_wchar<Base>,
        Base,
        wchar_t,
        single_pass_traversal_tag,
        char
    > super_t;

    typedef mb_from_wchar<Base> this_t;

    char dereference_impl() {
        if(! m_full){
            fill();
            m_full = true;
        }
        return m_buffer[m_bnext];
    }

    char dereference() const {
        return (const_cast<this_t *>(this))->dereference_impl();
    }
    // test for iterator equality
    bool equal(const mb_from_wchar<Base> & rhs) const {
        // once the value is filled, the base_reference has been incremented
        // so don't permit comparison anymore.
        return
            0 == m_bend
            && 0 == m_bnext
            && this->base_reference() == rhs.base_reference()
        ;
    }

    void fill(){
        wchar_t value = * this->base_reference();
        const wchar_t *wend;
        char *bend;
        BOOST_VERIFY(
            m_codecvt_facet.out(
                m_mbs,
                & value, & value + 1, wend,
                m_buffer, m_buffer + sizeof(m_buffer), bend
            )
            ==
            std::codecvt_base::ok
        );
        m_bnext = 0;
        m_bend = bend - m_buffer;
    }

    void increment(){
        if(++m_bnext < m_bend)
            return;
        m_bend =
        m_bnext = 0;
        ++(this->base_reference());
        m_full = false;
    }

    boost::archive::detail::utf8_codecvt_facet m_codecvt_facet;
    std::mbstate_t m_mbs;
    // buffer to handle pending characters
    char m_buffer[9 /* MB_CUR_MAX */];
    std::size_t m_bend;
    std::size_t m_bnext;
    bool m_full;

public:
    // make composible buy using templated constructor
    template<class T>
    mb_from_wchar(T start) :
        super_t(Base(static_cast< T >(start))),
        m_mbs(std::mbstate_t()),
        m_bend(0),
        m_bnext(0),
        m_full(false)
    {}
    // intel 7.1 doesn't like default copy constructor
    mb_from_wchar(const mb_from_wchar & rhs) :
        super_t(rhs.base_reference()),
        m_bend(rhs.m_bend),
        m_bnext(rhs.m_bnext),
        m_full(rhs.m_full)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_MB_FROM_WCHAR_HPP

/* mb_from_wchar.hpp
c8/mi3Ca649Qrf8LOPG4AcSUNMZdAwrhzhGeUGPzA1atvytcWzYGXtdZDNIsX76y7lT49YUrvzI7P9RpXYONvrIJum/sjhWOL0SbR2N5/x1d4XPSZjZvy2B4/aEwPC23BcYPGA1WlWuDbZW5ODSkJjw42BGm/LAW6o4qhXWLlcVnuIAtCQ/EqO3lMPh6GDS+NAoCiqbi3DnT8Hn+JeC3wASqhnUBlq8/tAyvhh8WbAOp3VGs2XYaW+LzGlzua9i4SlnQOaM8uEck4Ls1Q2Fv0lswmvGEdy4yGto6FGXbTZZj5/HJaLm2CE76rRtufngFT89egS+u1ML6PRZyk+XeuL7aI2hdNwgrNqrNnwb0wNpDfmT20T9A7BgrWDCmAjw815tXH12T6ncYr3E3GePyDcTKxYbCXN8OzHv6WVx98DpfVsIbdwSWBYtYe+hSfwAralQQXDx+YRferIei1pNYxiVviLmzBAb7jwSnp5ns9p1CeO7OENYzrRlEjfVmvV6dQpsiNdmIsD3QM6o409Q/jYmn6/HOeAPt2pfAxDoazC79Kyy9W5DO2XoKne2PY/Cv59m24magOe6O/p1OQe3d2az64aFQfUFZPNfwEBQZtpy9X7wbjUdZQ+m+kdgi4SFz+bkG7rbejZHPS2Mt2/IYcGU59rhcBVfMyI9JBaqzsFsReMRtC3TQbIPfGljDxvI/YNcNn1mj6ENo1bg3XAnbjEWaFISMx25wwf9X/rL8MKh7uC8/ZfITjN1cEqLapeLZZpuZsXMFMJ2Syus0Po/NnePhcOnlELBCC4VLxcHCyzf50oJXMfq1G4ttNgQ2H+nOU4tvBvez53jqiGbw+GMZ5tt4Lj7F4ni8pxf2nZUMG5cOhMyAH3FujDdMXeGJPpVPYLUGxTEgfgzmf3oY3r8djjP2VgHbB7EYdvUaLu+yCl3L/8gXJHTGSgt68oLDzWGGU1XWIPMzVLArASGeJ3H5sQcw8N0KuMPTYf+FU7ji7U2O1VeC8b7fWOLWdmD5jGPgnizI37Qd7+/aHl+V6MLvXxyNzwtswyL3N+LdG4eYuU0lWH7lGC8UZ4x2We1g4IhwdMt6CPt+SoRh7eqyCpt+g34/lucVH1SG4hMGsTVr9+D64274qeM+GD/0GLiW8cV6c96z69MCwfHQEox/cQdGbJlOTsJh8CQlE3Yumg6eJw/hrvWu2P52EnQq8AH3ODlD8JtzsE9KwfRyL8E5pQt/NiIBS52bzWqfNMMCpZJgSVx+2G42Ba/XLA5lHWfw9hWKQY97TdnpoUnwQ7lbcC3gJJTpWApLVhwOi1pegYjKD2DramSNPh2AG6d38K2LnbDLonxwJH0JrL0FkFFEwprH/WHNCkso612QrdgTAb41xkDmy/vwIaEkvORRmK9BP1boRQHsMmYeT/u8Bp2HZsBrnw5QqUpdzsKv45aePeFTDTcod6I+unWKhDGZ47BWv8qw2zUT29I+42FQQd7p4URY3cCBzfSLQ7OKt9mqs1MwYksabhu1DKZMus2Kpbtj9LyqzD/4NGyKjmWrz3aEX495MgdHZ0hpEMmOvU3C8RkZfHHUOZgfiGyMZSicSOqMiRcW4HK+mzc3/Q0srkXxyled4OdiMXxI82OY0WwXf9nzGAwx68hnmZ0FF27NHsbcwgtLndjPHv5geWQXn9mqGkzIcsKrU0djk5r1+Mn4ixD20ypcetMYrg8fxFeGLsWu19+x7E3jYOqksvhjihcsHe+Od+I80L7iaGzlOwHnfqgF+xYUh0d2s7lV8UeYdb8Qjt9UETu292Ppl4vA2PzLWOjuVDB6H4pWL9vCtZ/LQ/lFxei8UA889r4sTis1C2xdp0M=
*/