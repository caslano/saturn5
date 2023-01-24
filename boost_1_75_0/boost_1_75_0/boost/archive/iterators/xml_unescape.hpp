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
JrFQNEcbWIOI1dEayNJDy7W20AXcy6unsT2JJ+S6vbiXrZi6SE3FU3bdq9GdOnH8mJ26BSXk2NMZ/9d1BZmzryJWbnWzajHHNNvfGBfv2/Ucq6FMoV3ZaCRx5LA6vHi65LeDijJ7A4xFnQp2UROvZFlDEwALYTGMeXKWlVEfGMj2qQbduuWjl5FI4emCcWMGsl8ZVMYcCFr8IucVYHpjddSHW3r/eUwUJ76upwNbQFDeib/JY/gX5ZLysr6Jr6EoZ5TamDv7/t/jbZWkKMCKp7+XNA4ET1r7Q0S8idz9QL6OV8hGqZmLwdHYLn78rS7KUTAu6+NeYyorqRkYfcdmaCxqX+4AFH2hGwT887IYBs7tTb0FDZOGaNYR2NY7X9SxG9OJqAIBvJJ/iQlk58tqcqKWPDKaeNa/arov/xL/kmPychv9tENR6Pe7L0eNylmomrQecr7koieVk1c5Lcw7YpXTLqANKCqGfbSzGOjLXcSTkVFmEm5rbBZvQTqkbwWK6MlgNsz5HP3ko0HFx8rD1J0KgkjgyZDLjbHirdRvSWu+mJWKCl8gNUD9hUnYiTvso9dgHwaSlYGheUCGRGphUutgqBqYlbpI0D2EkUdCRiDa9NW3FcVVzwkXUJ6s5zThZcRtce/0OIwPgdQPCcYfar91N/zdVie66peJE7HpQta0T/xSu01Aj4dMU+wBew1p3/aZYdvXetEinR0W
*/