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