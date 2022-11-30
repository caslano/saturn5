#ifndef BOOST_ARCHIVE_ITERATORS_ESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_ESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// escape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>
#include <cstddef> // NULL

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert escapes into text

template<class Derived, class Base>
class escape :
    public boost::iterator_adaptor<
        Derived,
        Base,
        typename boost::iterator_value<Base>::type,
        single_pass_traversal_tag,
        typename boost::iterator_value<Base>::type
    >
{
    typedef typename boost::iterator_value<Base>::type base_value_type;
    typedef typename boost::iterator_reference<Base>::type reference_type;
    friend class boost::iterator_core_access;

    typedef typename boost::iterator_adaptor<
        Derived,
        Base,
        base_value_type,
        single_pass_traversal_tag,
        base_value_type
    > super_t;

    typedef escape<Derived, Base> this_t;

    void dereference_impl() {
        m_current_value = static_cast<Derived *>(this)->fill(m_bnext, m_bend);
        m_full = true;
    }

    //Access the value referred to
    reference_type dereference() const {
        if(!m_full)
            const_cast<this_t *>(this)->dereference_impl();
        return m_current_value;
    }

    bool equal(const this_t & rhs) const {
        if(m_full){
            if(! rhs.m_full)
                const_cast<this_t *>(& rhs)->dereference_impl();
        }
        else{
            if(rhs.m_full)
                const_cast<this_t *>(this)->dereference_impl();
        }
        if(m_bnext != rhs.m_bnext)
            return false;
        if(this->base_reference() != rhs.base_reference())
            return false;
        return true;
    }

   void increment(){
        if(++m_bnext < m_bend){
            m_current_value = *m_bnext;
            return;
        }
        ++(this->base_reference());
        m_bnext = NULL;
        m_bend = NULL;
        m_full = false;
    }

    // buffer to handle pending characters
    const base_value_type *m_bnext;
    const base_value_type *m_bend;
    bool m_full;
    base_value_type m_current_value;
public:
    escape(Base base) :
        super_t(base),
        m_bnext(NULL),
        m_bend(NULL),
        m_full(false),
        m_current_value(0)
    {
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_ESCAPE_HPP

/* escape.hpp
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
*/