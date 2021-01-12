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
DB0VdcKZaNgClS+VVI9APUf01CYcEaIg3zbdVdJbLw1j8oFbE2SB2t+8Txn4XEL1R5o4sPJfzzXyG8Hf36AWywVE8H3mR5n28rmQITnmnzPp+03d7c6BBcbS9Xm3nrcZQSrdVEk3o8vchXS14mtufd7qN53Yi0mXPJCp+H0qrAhhsEfMMEcA2LJfl98QKn4XTjU9dJSM3fyoQKb2bQFFtX8HX9HSaf6WewTSeBPb2xGhh3FE
*/