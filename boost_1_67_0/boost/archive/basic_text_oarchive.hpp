#ifndef BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// archives stored as text - note these ar templated on the basic
// stream templates to accommodate wide (and other?) kind of characters
//
// note the fact that on libraries without wide characters, ostream is
// is not a specialization of basic_ostream which in fact is not defined
// in such cases.   So we can't use basic_ostream<OStream::char_type> but rather
// use two template parameters

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_text_oarchive
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_text_oarchive :
    public detail::common_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
    #else
        friend class detail::interface_oarchive<Archive>;
    #endif
#endif

    enum {
        none,
        eol,
        space
    } delimiter;

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    newtoken();

    void newline(){
        delimiter = eol;
    }

    // default processing - kick back to base class.  Note the
    // extra stuff to get it passed borland compilers
    typedef detail::common_oarchive<Archive> detail_common_oarchive;
    template<class T>
    void save_override(T & t){
        this->detail_common_oarchive::save_override(t);
    }

    // start new objects on a new line
    void save_override(const object_id_type & t){
        this->This()->newline();
        this->detail_common_oarchive::save_override(t);
    }

    // text file don't include the optional information
    void save_override(const class_id_optional_type & /* t */){}

    void save_override(const class_name_type & t){
        const std::string s(t);
        * this->This() << s;
    }

    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    init();

    basic_text_oarchive(unsigned int flags) :
        detail::common_oarchive<Archive>(flags),
        delimiter(none)
    {}
    ~basic_text_oarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_TEXT_OARCHIVE_HPP

/* basic_text_oarchive.hpp
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
*/