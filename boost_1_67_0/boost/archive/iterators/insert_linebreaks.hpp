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