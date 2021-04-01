#ifndef BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_pointer_oserializer.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/basic_serializer.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

// forward declarations
namespace archive {
namespace detail {

class basic_iarchive;
class basic_iserializer;

class BOOST_SYMBOL_VISIBLE basic_pointer_iserializer
    : public basic_serializer {
protected:
    explicit BOOST_ARCHIVE_DECL basic_pointer_iserializer(
        const boost::serialization::extended_type_info & type_
    );
    virtual BOOST_ARCHIVE_DECL ~basic_pointer_iserializer();
public:
    virtual void * heap_allocation() const = 0;
    virtual const basic_iserializer & get_basic_serializer() const = 0;
    virtual void load_object_ptr(
        basic_iarchive & ar,
        void * x,
        const unsigned int file_version
    ) const = 0;
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_POINTER_ISERIALIZER_HPP

/* basic_pointer_iserializer.hpp
JIBtrB/OzeNyqlH2CIfhRgYxFAfxFg35ZwpqNVdvsYqhOwCz6iL+g5IJqsTbyhtXWZn3RSe1uHoP7TZ9lHx7qbw0rlaO4HCxl80oGD6BNCbi8klSAz2aVJdsaY67Et1gXnkuIg21KLthd5Utluq6bDDaz4kG9EbAc1wVzZGczBfeRl9SIiBB1k2dw+mWyH6X6dXgwg10bGhp1vy9Og1U6yGHXUE3wCUIgcGKN+8MLLO5awZ1i6GhIG/io1fU49xOaiI4ug5KizzAfKuO7EkqnCHO+gIzm/YdDrEXyY2b7yXGk9My9hnONCaYCRcs2iPNJj4K7/qFA0GeXS9Y2RlRV9z5Z+GcwE27x6BKw5P3CXhKKlrfZZePHTSZ5xDCBC+xW3ioAhR7rj/+w6ynWamYekCo9N6WeZ3ApTQG7Ra6Ql1C6WHAIgOHphhi5p3baZX7++Ry7wxoCBVXKK5fKe8bh7wkc7feOY9m4eE59EOqiGRf83To5eXU8aGORivxhpOIYDLcKZnwPMkiSuabTiqD+10AcVi09KiUKJnOidqjHtgf+fg0pLQqCvghJQ==
*/