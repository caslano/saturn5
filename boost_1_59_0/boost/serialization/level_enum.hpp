#ifndef BOOST_SERIALIZATION_LEVEL_ENUM_HPP
#define BOOST_SERIALIZATION_LEVEL_ENUM_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// level_enum.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

namespace boost {
namespace serialization {

// for each class used in the program, specify which level
// of serialization should be implemented

// names for each level
enum level_type
{
    // Don't serialize this type. An attempt to do so should
    // invoke a compile time assertion.
    not_serializable = 0,
    // write/read this type directly to the archive. In this case
    // serialization code won't be called.  This is the default
    // case for fundamental types.  It presumes a member function or
    // template in the archive class that can handle this type.
    // there is no runtime overhead associated reading/writing
    // instances of this level
    primitive_type = 1,
    // Serialize the objects of this type using the objects "serialize"
    // function or template. This permits values to be written/read
    // to/from archives but includes no class or version information.
    object_serializable = 2,
    ///////////////////////////////////////////////////////////////////
    // once an object is serialized at one of the above levels, the
    // corresponding archives cannot be read if the implementation level
    // for the archive object is changed.
    ///////////////////////////////////////////////////////////////////
    // Add class information to the archive.  Class information includes
    // implementation level, class version and class name if available
    object_class_info = 3
};

} // namespace serialization
} // namespace boost

#endif // BOOST_SERIALIZATION_LEVEL_ENUM_HPP

/* level_enum.hpp
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
*/