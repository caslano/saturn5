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
SCbXrtioe1ZBw0bswQw567LuvHMsA0AXqNUcFuJn9n1PaLima2WXtnWtD51zMvNpis/gTi3+FG6+QoPyGDmVAlxuv0eqMaOgi1zAgEKJgZDl2WRMoXe5J24os9/AUUQFp0XZq5hnir+YOxfIhm0k/zPAmIkcZrMOSdDw4BbyaL1fkyzz6aSf6Hr42asZhxi4uUh0wDoa7FGgQHerSpi61m6EXRIbtvEekPCEbTN5JFAgw9112+gM93A93cHUcNvX+6utiGCrJ/msr11O89nBd+HFObC8s4E6Vhe6pttHLPC4Dcwn61xIi6+U1fhyYiPtBxpN/rpkVB1f12TgUh6wvtHkW/wB6V2lioJLzR9/UkYIml1IeCMNmgQQv0RqjwQB0+mWb/ACjmjT2jCNCtIklATUdqRT4kPfFi3GToJQQary38TEO1IUsEaiXZaD0cGFjMKIzfes6STDN0Ta4yDXLjJSWr7MC50MAZV7bQVTwWjeqt7J0UVkdCDFsA9U0C+gPPFga3rakZc1iJPxcUhDRaMIEmihZMSL0jVfT1W3lRrkrTgFKVJ+YD71cg==
*/