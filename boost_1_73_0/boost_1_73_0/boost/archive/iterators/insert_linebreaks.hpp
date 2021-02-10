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
sk5dY66jUfIi+QAkkOqLVU1pRsy2cL690WlcAHWSBRyCGhcAZwx2rvrwR+YVLtiKvHnf+8cfMk+N/uqrr3LtZpN0mFI/kz6dZQ8n+eQ08pzAZXD3b6frYliI/XOKX6doK4Cw76MJjUgd3gILgmWs+BcQPWcM7yKKSZs3LrmHakEnRrER4J0Br1nfFbyI9GapaaTutQAVKwmnJy6EsuLtQ1OOmWhgoVfN+2cIyrPXRBaR0ZkuoR2w2ubIqs4u1CF0b8KJflFZABoYWIO8DF+qTDWxa4hl1jenBartOAX64ZAlpI0hXl7+/YxB41foMAG8D27ZCw/fWcLtuIECfVwaKM2LH9DDQf0/+bvL849P355f5g+nPqyqoBdQGPkJf49qXgE5YcYpN82cSiEh0H5nfDT4nDFPbiAAMIqe1cTG/EUBi+gYH2OuuW1y2tSs+qOdzLa28diKEiyNs08TDynFyo1W2LvL1TZSAPlgpa3WtHB8cS9zakSRVI1LJ5Y65eD1Gs9LwxeUyhcZwAjvzUV+wzrvRIs01NEUS7XFzt5eJYbCYWK6wIMBsbtau50ySZsyxpaaRsppy82xcE3vaJRTc23v19VOLAGxDpa5h6wC31512faek0FejxFCcsa4HLz6cnV3rK+mrERshXz8
*/