#ifndef BOOST_ARCHIVE_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <cstddef> // std::size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_text_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

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

template<class Archive>
class BOOST_SYMBOL_VISIBLE text_oarchive_impl :
     /* protected ? */ public basic_text_oprimitive<std::ostream>,
     public basic_text_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_text_oarchive<Archive>;
    friend class save_access;
#endif
    template<class T>
    void save(const T & t){
        this->newtoken();
        basic_text_oprimitive<std::ostream>::save(t);
    }
    void save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_ARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_DECL
    text_oarchive_impl(std::ostream & os, unsigned int flags);
    // don't import inline definitions! leave this as a reminder.
    //BOOST_ARCHIVE_DECL
    ~text_oarchive_impl(){};
public:
    BOOST_ARCHIVE_DECL void
    save_binary(const void *address, std::size_t count);
};

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from text_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE text_oarchive :
    public text_oarchive_impl<text_oarchive>
{
public:
    text_oarchive(std::ostream & os_, unsigned int flags = 0) :
        // note: added _ to suppress useless gcc warning
        text_oarchive_impl<text_oarchive>(os_, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~text_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::text_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_TEXT_OARCHIVE_HPP

/* text_oarchive.hpp
jGKimXRUBpDMmeniS3s7XYpcO1EL5l8Gq+YP+NoypVZrcX18ODB7MolXVqylzm4WdHijZ0FCF7A6mgpf7ibNgUBga4NxbnDRgGDxZKArzl5jbw8IW6D7DrSEamsij6KW5BDmRaskfwpNs9zt+DhoLSQUchj7p6l1468IKYeSLKWVwM7PQs4WlBlXYe/KVi7VNaV9Uz3etrsZo9/ULQc7GAN7nOVP4anuGJbYXHHxeKFSK/bg+dX9Qnf++X1S/fytV/V6o6Ae/z1qfDzVwhd8AdaPatOLgzbpKvzvXzT4VHg0JFGFn26u+J9xgKfjWDp7EYxIPlNQDbP3bbrdf3KcIOnHk1A8h0hac2WGo8kot3Y0BUiuHgBXvi27GBx4D7JHcrY5iQfiyJR2lP4H3NJhMPXuQH71c0CwVOCf0Yx/FZKAdq7iGvQ9yL5JW3vBqOzCsdPZFpinhGXRh2OL6dJfV/j3FP8dq+MRG9FCHRbs9iQASGhFunkUeozdjzDZ7DwrOY9AXu28DEqVbeMBeu/+KOzxiNsV9j2e/o+Bv7H54CjlB6A74XbFf48R5jvB3zbQMaBwbQbbqKR1dGnhzTbSc1ADkWuEiztcHOu7xBjkriXjuwwrttTioqgtTv6PYxFArd7Z0oEyK8v+p7gOaLziQiqUbdhv5MFASxjeJ7LxJMZwC5jucQ3DYbK0fzYbQl9TXFCsnqAScd4BNqO6
*/