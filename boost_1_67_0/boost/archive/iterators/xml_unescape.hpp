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