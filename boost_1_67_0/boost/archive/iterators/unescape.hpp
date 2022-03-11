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
    };

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