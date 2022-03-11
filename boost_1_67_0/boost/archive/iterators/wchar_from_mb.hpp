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