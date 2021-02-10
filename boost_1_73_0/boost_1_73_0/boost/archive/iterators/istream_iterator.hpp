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
xdO3P5+rycKR5SvfPWFzPTZwZNwOdLIStbcTBEgF2Qgu3tqJfyfNKmOwJs29Cwn+43w0AYg9BTma+PEEVTLWZ7qIRCMr5vL76E/fXMT2lTaICsLQD8iMemZ7m8u7Z5sLdX0rgLRmRDniqfKVpA9fsE3bHJifgWqt3cu4NuC3sM00T3PrUBOjEmmvJuwetiwvGG3zhkX9D4ZHn4W7ZIpsnz8KgorEnM+xs7tVNiJMUB6tTZ7ypIHOwAIIZk25QqYlc+a+RRh3jLXe39FLQhSOwT+dzGa5HPlRgnUUEJ0NN9X0yy35kilcupDJLMmmGznqgiUXRhKlomE52TT5MkrcID5uC/RFOYqvM7sGOHxP/6fhLrNgRqSrtcv8UuHNJd2tvfWyGWIKX9ZX2Ey0Tuq5Bn1DydOl8Zw0+0Cb1iCp+zYt8LUwjceVtAfnmlkSDRJ8tmKf1qfOiISj0sfAVVxXTKUvbkWseXMo27G0P4U3IEqTKyxXx7gnXc9aCb70ItqyCBvi/ezGyRUpgoRoXcgTSGjIFbMs+Dzj+03CGbQi3jrYts2sYubbKAymnfTso5pzOU2uyB4JhhTLrWvNzsXVbd9ok5PR1b0Xiz3Xbvdd7Pdc23Npvm+8fe/e7rsW3k4Y87ibs7v3t9o+73EU
*/