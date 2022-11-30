#ifndef BOOST_ARCHIVE_ITERATORS_WCHAR_FROM_MB_HPP
#define BOOST_ARCHIVE_ITERATORS_WCHAR_FROM_MB_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// wchar_from_mb.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cctype>
#include <cstddef> // size_t
#ifndef BOOST_NO_CWCHAR
#include <cwchar>  // mbstate_t
#endif
#include <algorithm> // copy

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::mbstate_t;
} // namespace std
#endif
#include <boost/assert.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/array.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/archive/detail/utf8_codecvt_facet.hpp>
#include <boost/archive/iterators/dataflow_exception.hpp>
#include <boost/serialization/throw_exception.hpp>

#include <iostream>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate char strings to wchar_t
// strings of the currently selected locale
template<class Base>
class wchar_from_mb
    : public boost::iterator_adaptor<
        wchar_from_mb<Base>,
        Base,
        wchar_t,
        single_pass_traversal_tag,
        wchar_t
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        wchar_from_mb<Base>,
        Base,
        wchar_t,
        single_pass_traversal_tag,
        wchar_t
    > super_t;

    typedef wchar_from_mb<Base> this_t;

    void drain();

    wchar_t dereference() const {
        if(m_output.m_next == m_output.m_next_available)
            return static_cast<wchar_t>(0);
        return * m_output.m_next;
    }

    void increment(){
        if(m_output.m_next == m_output.m_next_available)
            return;
        if(++m_output.m_next == m_output.m_next_available){
            if(m_input.m_done)
                return;
            drain();
        }
    }

    bool equal(this_t const & rhs) const {
        return dereference() == rhs.dereference();
    }

    boost::archive::detail::utf8_codecvt_facet m_codecvt_facet;
    std::mbstate_t m_mbs;

    template<typename T>
    struct sliding_buffer {
        boost::array<T, 32> m_buffer;
        typename boost::array<T, 32>::const_iterator m_next_available;
        typename boost::array<T, 32>::iterator m_next;
        bool m_done;
        // default ctor
        sliding_buffer() :
            m_next_available(m_buffer.begin()),
            m_next(m_buffer.begin()),
            m_done(false)
        {}
        // copy ctor
        sliding_buffer(const sliding_buffer & rhs) :
            m_next_available(
                std::copy(
                    rhs.m_buffer.begin(),
                    rhs.m_next_available,
                    m_buffer.begin()
                )
            ),
            m_next(
                m_buffer.begin() + (rhs.m_next - rhs.m_buffer.begin())
            ),
            m_done(rhs.m_done)
        {}
    };

    sliding_buffer<typename iterator_value<Base>::type> m_input;
    sliding_buffer<typename iterator_value<this_t>::type> m_output;

public:
    // make composible buy using templated constructor
    template<class T>
    wchar_from_mb(T start) :
        super_t(Base(static_cast< T >(start))),
        m_mbs(std::mbstate_t())
    {
        BOOST_ASSERT(std::mbsinit(&m_mbs));
        drain();
    }
    // default constructor used as an end iterator
    wchar_from_mb(){}

    // copy ctor
    wchar_from_mb(const wchar_from_mb & rhs) :
        super_t(rhs.base_reference()),
        m_mbs(rhs.m_mbs),
        m_input(rhs.m_input),
        m_output(rhs.m_output)
    {}
};

template<class Base>
void wchar_from_mb<Base>::drain(){
    BOOST_ASSERT(! m_input.m_done);
    for(;;){
        typename boost::iterators::iterator_reference<Base>::type c = *(this->base_reference());
        // a null character in a multibyte stream is takes as end of string
        if(0 == c){
            m_input.m_done = true;
            break;
        }
        ++(this->base_reference());
        * const_cast<typename iterator_value<Base>::type *>(
            (m_input.m_next_available++)
        ) = c;
        // if input buffer is full - we're done for now
        if(m_input.m_buffer.end() == m_input.m_next_available)
            break;
    }
    const typename boost::iterators::iterator_value<Base>::type * input_new_start;
    typename iterator_value<this_t>::type * next_available;

    BOOST_ATTRIBUTE_UNUSED // redundant with ignore_unused below but clarifies intention
    std::codecvt_base::result r = m_codecvt_facet.in(
        m_mbs,
        m_input.m_buffer.begin(),
        m_input.m_next_available,
        input_new_start,
        m_output.m_buffer.begin(),
        m_output.m_buffer.end(),
        next_available
    );
    BOOST_ASSERT(std::codecvt_base::ok == r);
    m_output.m_next_available = next_available;
    m_output.m_next = m_output.m_buffer.begin();

    // we're done with some of the input so shift left.
    m_input.m_next_available = std::copy(
        input_new_start,
        m_input.m_next_available,
        m_input.m_buffer.begin()
    );
    m_input.m_next = m_input.m_buffer.begin();
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_WCHAR_FROM_MB_HPP

/* wchar_from_mb.hpp
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
*/