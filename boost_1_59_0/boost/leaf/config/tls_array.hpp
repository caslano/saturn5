#ifndef BOOST_LEAF_CONFIG_TLS_ARRAY_HPP_INCLUDED
#define BOOST_LEAF_CONFIG_TLS_ARRAY_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.
// Copyright (c) 2022 Khalil Estell

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// LEAF requires thread local storage support for pointers and for uin32_t values.

// This header implements thread local storage for pointers and for uint32_t
// values for platforms that support thread local pointers by index.

namespace boost { namespace leaf {

namespace tls
{
    // The TLS support defined in this header requires the following two
    // functions to be defined elsewhere:
    void * read_void_ptr( int tls_index ) noexcept;
    void write_void_ptr( int tls_index, void * ) noexcept;
}

} }

////////////////////////////////////////

#include <limits>
#include <atomic>
#include <cstdint>
#include <type_traits>

#ifndef BOOST_LEAF_CFG_TLS_INDEX_TYPE
#   define BOOST_LEAF_CFG_TLS_INDEX_TYPE unsigned char
#endif

#ifndef BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX
#   define BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX 0
#endif

static_assert((BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX) >= 0,
    "Bad BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX");

#ifdef BOOST_LEAF_CFG_TLS_ARRAY_SIZE
    static_assert((BOOST_LEAF_CFG_TLS_ARRAY_SIZE) > (BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX),
        "Bad BOOST_LEAF_CFG_TLS_ARRAY_SIZE");
    static_assert((BOOST_LEAF_CFG_TLS_ARRAY_SIZE) - 1 <= std::numeric_limits<BOOST_LEAF_CFG_TLS_INDEX_TYPE>::max(),
        "Bad BOOST_LEAF_CFG_TLS_ARRAY_SIZE");
#endif

////////////////////////////////////////

namespace boost { namespace leaf {

namespace leaf_detail
{
    using atomic_unsigned_int = std::atomic<unsigned int>;
}

namespace tls
{
    template <class=void>
    class BOOST_LEAF_SYMBOL_VISIBLE index_counter
    {
        static int c_;

    public:

        static BOOST_LEAF_CFG_TLS_INDEX_TYPE next()
        {
            int idx = ++c_;
            BOOST_LEAF_ASSERT(idx > (BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX));
            BOOST_LEAF_ASSERT(idx < (BOOST_LEAF_CFG_TLS_ARRAY_SIZE));
            return idx;
        }
    };

    template <class T>
    struct BOOST_LEAF_SYMBOL_VISIBLE tls_index
    {
        static BOOST_LEAF_CFG_TLS_INDEX_TYPE idx;
    };

    template <class T>
    struct BOOST_LEAF_SYMBOL_VISIBLE alloc_tls_index
    {
        static BOOST_LEAF_CFG_TLS_INDEX_TYPE const idx;
    };

    template <class T>
    int index_counter<T>::c_ = BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX;

    template <class T>
    BOOST_LEAF_CFG_TLS_INDEX_TYPE tls_index<T>::idx = BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX;

    template <class T>
    BOOST_LEAF_CFG_TLS_INDEX_TYPE const alloc_tls_index<T>::idx = tls_index<T>::idx = index_counter<>::next();

    ////////////////////////////////////////

    template <class T>
    T * read_ptr() noexcept
    {
        int tls_idx = tls_index<T>::idx;
        if( tls_idx == (BOOST_LEAF_CFG_TLS_ARRAY_START_INDEX) )
            return 0;
        --tls_idx;
        return reinterpret_cast<T *>(read_void_ptr(tls_idx));
    }

    template <class T>
    void write_ptr( T * p ) noexcept
    {
        int tls_idx = alloc_tls_index<T>::idx;
        --tls_idx;
        write_void_ptr(tls_idx, p);
        BOOST_LEAF_ASSERT(read_void_ptr(tls_idx) == p);
    }

    ////////////////////////////////////////

    template <class Tag>
    std::uint32_t read_uint32() noexcept
    {
        static_assert(sizeof(std::intptr_t) >= sizeof(std::uint32_t), "Incompatible tls_array implementation");
        return (std::uint32_t) (std::intptr_t) (void *) read_ptr<Tag>();
    }

    template <class Tag>
    void write_uint32( std::uint32_t x ) noexcept
    {
        static_assert(sizeof(std::intptr_t) >= sizeof(std::uint32_t), "Incompatible tls_array implementation");
        write_ptr<Tag>((Tag *) (void *) (std::intptr_t) x);
    }

    template <class Tag>
    void uint32_increment() noexcept
    {
        write_uint32<Tag>(read_uint32<Tag>() + 1);
    }

    template <class Tag>
    void uint32_decrement() noexcept
    {
        write_uint32<Tag>(read_uint32<Tag>() - 1);
    }
}

} }

#endif

/* tls_array.hpp
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
*/