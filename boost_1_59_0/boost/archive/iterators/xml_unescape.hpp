#ifndef BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_unescape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/assert.hpp>

#include <boost/serialization/throw_exception.hpp>

#include <boost/archive/iterators/unescape.hpp>
#include <boost/archive/iterators/dataflow_exception.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// replace &??? xml escape sequences with the corresponding characters
template<class Base>
class xml_unescape
    : public unescape<xml_unescape<Base>, Base>
{
    friend class boost::iterator_core_access;
    typedef xml_unescape<Base> this_t;
    typedef unescape<this_t, Base> super_t;
    typedef typename boost::iterator_reference<this_t> reference_type;

    reference_type dereference() const {
        return unescape<xml_unescape<Base>, Base>::dereference();
    }
public:
    // msvc versions prior to 14.0 crash with and ICE
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1900)
        typedef int value_type;
    #else
        typedef typename super_t::value_type value_type;
    #endif

    void drain_residue(const char *literal);
    value_type drain();

    template<class T>
    xml_unescape(T start) :
        super_t(Base(static_cast< T >(start)))
    {}
    // intel 7.1 doesn't like default copy constructor
    xml_unescape(const xml_unescape & rhs) :
        super_t(rhs.base_reference())
    {}
};

template<class Base>
void xml_unescape<Base>::drain_residue(const char * literal){
    do{
        if(* literal != * ++(this->base_reference()))
            boost::serialization::throw_exception(
                dataflow_exception(
                    dataflow_exception::invalid_xml_escape_sequence
                )
            );
    }
    while('\0' != * ++literal);
}

// note key constraint on this function is that can't "look ahead" any
// more than necessary into base iterator.  Doing so would alter the base
// iterator refenence which would make subsequent iterator comparisons
// incorrect and thereby break the composiblity of iterators.
template<class Base>
typename xml_unescape<Base>::value_type
//int
xml_unescape<Base>::drain(){
    value_type retval = * this->base_reference();
    if('&' != retval){
        return retval;
    }
    retval = * ++(this->base_reference());
    switch(retval){
    case 'l': // &lt;
        drain_residue("t;");
        retval = '<';
        break;
    case 'g': // &gt;
        drain_residue("t;");
        retval = '>';
        break;
    case 'a':
        retval = * ++(this->base_reference());
        switch(retval){
        case 'p': // &apos;
            drain_residue("os;");
            retval = '\'';
            break;
        case 'm': // &amp;
            drain_residue("p;");
            retval = '&';
            break;
        }
        break;
    case 'q':
        drain_residue("uot;");
        retval = '"';
        break;
    }
    return retval;
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_HPP

/* xml_unescape.hpp
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
*/