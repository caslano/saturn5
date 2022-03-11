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
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
*/