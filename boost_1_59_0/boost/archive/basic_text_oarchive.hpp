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
    ~basic_text_oarchive() BOOST_OVERRIDE {}
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