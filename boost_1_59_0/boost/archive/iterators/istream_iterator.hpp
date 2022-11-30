#ifndef BOOST_ARCHIVE_ITERATORS_ISTREAM_ITERATOR_HPP
#define BOOST_ARCHIVE_ITERATORS_ISTREAM_ITERATOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// istream_iterator.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is a custom version of the standard istream_iterator.
// This is necessary as the standard version doesn't work as expected
// for wchar_t based streams on systems for which wchar_t not a true
// type but rather a synonym for some integer type.

#include <cstddef> // NULL
#include <istream>
#include <boost/iterator/iterator_facade.hpp>

namespace boost {
namespace archive {
namespace iterators {

// given a type, make an input iterator based on a pointer to that type
template<class Elem = char>
class istream_iterator :
    public boost::iterator_facade<
        istream_iterator<Elem>,
        Elem,
        std::input_iterator_tag,
        Elem
    >
{
    friend class boost::iterator_core_access;
    typedef istream_iterator this_t ;
    typedef typename boost::iterator_facade<
        istream_iterator<Elem>,
        Elem,
        std::input_iterator_tag,
        Elem
    > super_t;
    typedef typename std::basic_istream<Elem> istream_type;

    bool equal(const this_t & rhs) const {
        // note: only  works for comparison against end of stream
        return m_istream == rhs.m_istream;
    }

    //Access the value referred to
    Elem dereference() const {
        return static_cast<Elem>(m_istream->peek());
    }

    void increment(){
        if(NULL != m_istream){
            m_istream->ignore(1);
        }
    }

    istream_type *m_istream;
    Elem m_current_value;
public:
    istream_iterator(istream_type & is) :
        m_istream(& is)
    {
        //increment();
    }

    istream_iterator() :
        m_istream(NULL),
        m_current_value(NULL)
    {}

    istream_iterator(const istream_iterator<Elem> & rhs) :
        m_istream(rhs.m_istream),
        m_current_value(rhs.m_current_value)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_ISTREAM_ITERATOR_HPP

/* istream_iterator.hpp
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
*/