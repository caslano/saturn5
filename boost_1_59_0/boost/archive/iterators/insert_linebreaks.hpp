#ifndef BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP
#define BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert_linebreaks.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ using ::memcpy; }
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert line break every N characters
template<
    class Base,
    int N,
    class CharType = typename boost::iterator_value<Base>::type
>
class insert_linebreaks :
    public iterator_adaptor<
        insert_linebreaks<Base, N, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    >
{
private:
    friend class boost::iterator_core_access;
    typedef iterator_adaptor<
        insert_linebreaks<Base, N, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    > super_t;

    bool equal(const insert_linebreaks<Base, N, CharType> & rhs) const {
        return
//            m_count == rhs.m_count
//            && base_reference() == rhs.base_reference()
            this->base_reference() == rhs.base_reference()
        ;
    }

    void increment() {
        if(m_count == N){
            m_count = 0;
            return;
        }
        ++m_count;
        ++(this->base_reference());
    }
    CharType dereference() const {
        if(m_count == N)
            return '\n';
        return * (this->base_reference());
    }
    unsigned int m_count;
public:
    // make composible buy using templated constructor
    template<class T>
    insert_linebreaks(T  start) :
        super_t(Base(static_cast< T >(start))),
        m_count(0)
    {}
    // intel 7.1 doesn't like default copy constructor
    insert_linebreaks(const insert_linebreaks & rhs) :
        super_t(rhs.base_reference()),
        m_count(rhs.m_count)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP

/* insert_linebreaks.hpp
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
*/