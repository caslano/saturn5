#ifndef BOOST_ARCHIVE_ITERATORS_OSTREAM_ITERATOR_HPP
#define BOOST_ARCHIVE_ITERATORS_OSTREAM_ITERATOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// ostream_iterator.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is a custom version of the standard ostream_iterator.
// This is necessary as the standard version doesn't work as expected
// for wchar_t based streams on systems for which wchar_t not a true
// type but rather a synonym for some integer type.

#include <ostream>
#include <boost/iterator/iterator_facade.hpp>

namespace boost {
namespace archive {
namespace iterators {

// given a type, make an input iterator based on a pointer to that type
template<class Elem>
class ostream_iterator :
    public boost::iterator_facade<
        ostream_iterator<Elem>,
        Elem,
        std::output_iterator_tag,
        ostream_iterator<Elem> &
    >
{
    friend class boost::iterator_core_access;
    typedef ostream_iterator this_t ;
    typedef Elem char_type;
    typedef std::basic_ostream<char_type> ostream_type;

    //emulate the behavior of std::ostream
    ostream_iterator & dereference() const {
        return const_cast<ostream_iterator &>(*this);
    }
    bool equal(const this_t & rhs) const {
        return m_ostream == rhs.m_ostream;
    }
    void increment(){}
protected:
    ostream_type *m_ostream;
    void put_val(char_type e){
        if(NULL != m_ostream){
            m_ostream->put(e);
            if(! m_ostream->good())
                m_ostream = NULL;
        }
    }
public:
    this_t & operator=(char_type c){
        put_val(c);
        return *this;
    }
    ostream_iterator(ostream_type & os) :
        m_ostream (& os)
    {}
    ostream_iterator() :
        m_ostream (NULL)
    {}
    ostream_iterator(const ostream_iterator & rhs) :
        m_ostream (rhs.m_ostream)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_OSTREAM_ITERATOR_HPP

/* ostream_iterator.hpp
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
*/