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
swGrGDOuQV/8QZXaO5Xe/zab79GvKH6g1wvBqPJ/KaE/stcUhdWmxbgav+1jh1j1xTZ+waUJvSWcCXjmznjnh8gP576HxGd+D26Twiik1qIx5QE056K5A9VCvyrX+2vQX9wRVhXeMF4fXUJtU4k+s5WbjtSq5iEL09iS/Xv4tNgsLTGroD7x7o18WnuX3BZr0VcNjw4u8qmfADBfgVNiKNjfB9MmV7gP7ttk3AebTVbzO8Zejd5qCjxdSomJufIGYrHnRW2rX0ZtbDCavj+8yZ/lTd6RhZD34TGb4wB0ku3tCa3F3NajGfTx9kgfGuzq5UAGI1CZfv8kIjHnkAlzwWOJ+l8Nc3kesKVxqiAbSSLuC3KFXfn3Q+TgJ1dW5+WX6RI3Tv+hmKl085eFaMdNMlUtTtU+2e5j5y94wEZDdktO1+qyAMufYHEazMQAEiUJHI3O/eMlOte6Y5wsHGvDJLQjEKC7iyCI6BQ4KSXQK/EQ//Um4lJRZYTwSv2ddqF3Kzt9SDxFG3oe0zaoYcRgNne+6CKjazoBvMAI9ukDD0Zf7DUvlY/RFtyx09ySLvr9Fn5jfK+9KPLYJ/8u0uXOfOvDcrARsb4JJJt/HNMv+JAgQn4OTwMYmSqMj0mmr+BSJU+ppw9+j7DlOgpDuBHABtxpkNbI8a+3jv8F+/HviRj/jojx75Dxv6DG/5zt+He8Hx7/B9Udf59Nv/34I1V93l5nmYJtz5tTkArcpilIxRRs2G362qpfQY8HfJFoAy3dXn5iRuM3+QJ+XvnLmsATwzG+zvJqaMFXkIB5oKG69fozaajNjZDFv05bqMr1nv+5ZbCHJtmu9ze7yq/3wW3lh/XxNh7WB5Nkvf8+3na9Q9+Y633ljOqud7Ovf+v1VvefteZ73ER1Pjh3VX4fV3ziGCkFOWg5B/RCT7Hu7Hyx1ocyW8oNW51JwnmTx4y5r7Ibtrrshq0rMxkoUb4O8b9ZjyeLQ3gnjzMspkLvqxJaiVnilKfBOp4Fa6oxnqs/KDeeaybKeDrSeGZZxjNiXpTxrH7VHE+XZ43xtP4txmPwR9+vNjkcFbtvi3JcL6yRYm7a6NtYCpLzDcf4Aqt84jkXK/bo2JycRmHAkYYOrnomGKpmWDbb+e25uhrzu2VGufn96jmZ32N0qk+xzO+5c6PM77y95vweGmvM75ppv8H8qvf/VYb8auUEI1bJtirfD3gS7pCiym/P/ukG7fCnYLTfTZDRPkCjHW9xUpgyR24QkS5YNDexF+dAGVUU1VfgdcLgrx4W/uqhYCd6ajCUClMq8GF5AjckeIE1ZlR6BLM13GS20M8O6Cf3b05tno4ipmX639793fgqq34mUKKkgvx7pWkLcNzpb6TPf50fwltaQgvK0KoVH3XWZ6a+tLG+a0dHk38a8HVNfGi9K5r88zPLe1XZeFVkMRWxl/+Z/ZlvAKfb9Uf0R8ZX5P9XGP3LM8qP2RlN/rvClP8a8Ie3RBu/Cb/SgC+OBt9thSn/HWfIf6PBn2/CP2DU740Gf2R5MOxP9dVIe6LxNvhTsrycLckkhzIhyWeED6gQ64XePfptrHyhtXSS2G0Jf19LNVy4ib+zuc+jn/J3nb5PGsPfd/ILfyF/P0TfbxE7hmP0/eLV/N2hwm6ClOh3LOAkFzXzGYZgwV7srlKOqx3CR3WuILDQDLlN3cGfzUw/YvGN6sUfl/xpKX+4c4fEeOk17ykR9Srpo3+ZeZ831nesFu39V8ED3wx44qoq139bZtk/x40iI20sWRX+lxr9WWkAO+z7Q1fxWr7C4WIi4sRdnH8O558xJZXhv6p/RDGthVgOvxMN/xW8VjDcgL/j08r2c5NxFfU=
*/