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