#ifndef BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// unescape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate char strings to wchar_t
// strings of the currently selected locale
template<class Derived, class Base>
class unescape
    : public boost::iterator_adaptor<
        unescape<Derived, Base>,
        Base,
        typename pointee<Base>::type,
        single_pass_traversal_tag,
        typename pointee<Base>::type
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        unescape<Derived, Base>,
        Base,
        typename pointee<Base>::type,
        single_pass_traversal_tag,
        typename pointee<Base>::type
    > super_t;

    typedef unescape<Derived, Base> this_t;
public:
    typedef typename this_t::value_type value_type;
    typedef typename this_t::reference reference;
private:
    value_type dereference_impl() {
        if(! m_full){
            m_current_value = static_cast<Derived *>(this)->drain();
            m_full = true;
        }
        return m_current_value;
    }

    reference dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }

    value_type m_current_value;
    bool m_full;

    void increment(){
        ++(this->base_reference());
        dereference_impl();
        m_full = false;
    }

public:

    unescape(Base base) :
        super_t(base),
        m_full(false)
    {}

};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP

/* unescape.hpp
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
*/