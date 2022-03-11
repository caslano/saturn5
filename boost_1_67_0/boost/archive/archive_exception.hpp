#ifndef BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP
#define BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive/archive_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <exception>
#include <boost/assert.hpp>
#include <string>

#include <boost/config.hpp>
#include <boost/archive/detail/decl.hpp>

// note: the only reason this is in here is that windows header
// includes #define exception_code _exception_code (arrrgghhhh!).
// the most expedient way to address this is be sure that this
// header is always included whenever this header file is included.
#if defined(BOOST_WINDOWS)
#include <excpt.h>
#endif

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by archives
//
class BOOST_SYMBOL_VISIBLE archive_exception :
    public virtual std::exception
{
private:
    char m_buffer[128];
protected:
    BOOST_ARCHIVE_DECL unsigned int
    append(unsigned int l, const char * a);
    BOOST_ARCHIVE_DECL
    archive_exception() BOOST_NOEXCEPT;
public:
    typedef enum {
        no_exception,       // initialized without code
        other_exception,    // any excepton not listed below
        unregistered_class, // attempt to serialize a pointer of
                            // an unregistered class
        invalid_signature,  // first line of archive does not contain
                            // expected string
        unsupported_version,// archive created with library version
                            // subsequent to this one
        pointer_conflict,   // an attempt has been made to directly
                            // serialize an object which has
                            // already been serialized through a pointer.
                            // Were this permitted, the archive load would result
                            // in the creation of an extra copy of the obect.
        incompatible_native_format, // attempt to read native binary format
                            // on incompatible platform
        array_size_too_short,// array being loaded doesn't fit in array allocated
        input_stream_error, // error on input stream
        invalid_class_name, // class name greater than the maximum permitted.
                            // most likely a corrupted archive or an attempt
                            // to insert virus via buffer overrun method.
        unregistered_cast,   // base - derived relationship not registered with
                            // void_cast_register
        unsupported_class_version, // type saved with a version # greater than the
                            // one used by the program.  This indicates that the program
                            // needs to be rebuilt.
        multiple_code_instantiation, // code for implementing serialization for some
                            // type has been instantiated in more than one module.
        output_stream_error // error on input stream
    } exception_code;
    exception_code code;

    BOOST_ARCHIVE_DECL archive_exception(
        exception_code c,
        const char * e1 = NULL,
        const char * e2 = NULL
    ) BOOST_NOEXCEPT;
    BOOST_ARCHIVE_DECL archive_exception(archive_exception const &) BOOST_NOEXCEPT ;
    virtual BOOST_ARCHIVE_DECL ~archive_exception() BOOST_NOEXCEPT_OR_NOTHROW ;
    virtual BOOST_ARCHIVE_DECL const char * what() const BOOST_NOEXCEPT_OR_NOTHROW ;
};

}// namespace archive
}// namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_ARCHIVE_EXCEPTION_HPP

/* archive_exception.hpp
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
*/