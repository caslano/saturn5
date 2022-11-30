//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Krystian Stasiowski (sdkrystian@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_STRING_IMPL_HPP
#define BOOST_JSON_DETAIL_STRING_IMPL_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/kind.hpp>
#include <boost/json/storage_ptr.hpp>
#include <boost/json/detail/value.hpp>
#include <algorithm>
#include <iterator>

BOOST_JSON_NS_BEGIN

class value;

namespace detail {

class string_impl
{
    struct table
    {
        std::uint32_t size;
        std::uint32_t capacity;
    };

#if BOOST_JSON_ARCH == 64
    static constexpr std::size_t sbo_chars_ = 14;
#elif BOOST_JSON_ARCH == 32
    static constexpr std::size_t sbo_chars_ = 10;
#else
# error Unknown architecture
#endif

    static
    constexpr
    kind
    short_string_ =
        static_cast<kind>(
            ((unsigned char)
            kind::string) | 0x80);

    static
    constexpr
    kind
    key_string_ =
        static_cast<kind>(
            ((unsigned char)
            kind::string) | 0x40);

    struct sbo
    {
        kind k; // must come first
        char buf[sbo_chars_ + 1];
    };

    struct pointer
    {
        kind k; // must come first
        table* t;
    };

    struct key
    {
        kind k; // must come first
        std::uint32_t n;
        char* s;
    };

    union
    {
        sbo s_;
        pointer p_;
        key k_;
    };

#if BOOST_JSON_ARCH == 64
    BOOST_STATIC_ASSERT(sizeof(sbo) <= 16);
    BOOST_STATIC_ASSERT(sizeof(pointer) <= 16);
    BOOST_STATIC_ASSERT(sizeof(key) <= 16);
#elif BOOST_JSON_ARCH == 32
    BOOST_STATIC_ASSERT(sizeof(sbo) <= 24);
    BOOST_STATIC_ASSERT(sizeof(pointer) <= 24);
    BOOST_STATIC_ASSERT(sizeof(key) <= 24);
#endif

public:
    static
    constexpr
    std::size_t
    max_size() noexcept
    {
        // max_size depends on the address model
        using min = std::integral_constant<std::size_t,
            std::size_t(-1) - sizeof(table)>;
        return min::value < BOOST_JSON_MAX_STRING_SIZE ?
            min::value : BOOST_JSON_MAX_STRING_SIZE;
    }

    BOOST_JSON_DECL
    string_impl() noexcept;

    BOOST_JSON_DECL
    string_impl(
        std::size_t new_size,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    string_impl(
        key_t,
        string_view s,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    string_impl(
        key_t,
        string_view s1,
        string_view s2,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    string_impl(
        char** dest,
        std::size_t len,
        storage_ptr const& sp);

    template<class InputIt>
    string_impl(
        InputIt first,
        InputIt last,
        storage_ptr const& sp,
        std::random_access_iterator_tag)
        : string_impl(last - first, sp)
    {
        std::copy(first, last, data());
    }

    template<class InputIt>
    string_impl(
        InputIt first,
        InputIt last,
        storage_ptr const& sp,
        std::input_iterator_tag)
        : string_impl(0, sp)
    {
        struct undo
        {
            string_impl* s;
            storage_ptr const& sp;

            ~undo()
            {
                if(s)
                    s->destroy(sp);
            }
        };

        undo u{this, sp};
        auto dest = data();
        while(first != last)
        {
            if(size() < capacity())
                size(size() + 1);
            else
                dest = append(1, sp);
            *dest++ = *first++;
        }
        term(size());
        u.s = nullptr;
    }

    std::size_t
    size() const noexcept
    {
        return s_.k == kind::string ?
            p_.t->size :
            sbo_chars_ -
                s_.buf[sbo_chars_];
    }

    std::size_t
    capacity() const noexcept
    {
        return s_.k == kind::string ?
            p_.t->capacity :
            sbo_chars_;
    }

    void
    size(std::size_t n)
    {
        if(s_.k == kind::string)
            p_.t->size = static_cast<
                std::uint32_t>(n);
        else
            s_.buf[sbo_chars_] =
                static_cast<char>(
                    sbo_chars_ - n);
    }

    BOOST_JSON_DECL
    static
    std::uint32_t
    growth(
        std::size_t new_size,
        std::size_t capacity);

    char const*
    release_key(
        std::size_t& n) noexcept
    {
        BOOST_ASSERT(
            k_.k == key_string_);
        n = k_.n;
        auto const s = k_.s;
        // prevent deallocate
        k_.k = short_string_;
        return s;
    }

    void
    destroy(
        storage_ptr const& sp) noexcept
    {
        if(s_.k == kind::string)
        {
            sp->deallocate(p_.t,
                sizeof(table) +
                    p_.t->capacity + 1,
                alignof(table));
        }
        else if(s_.k != key_string_)
        {
            // do nothing
        }
        else
        {
            BOOST_ASSERT(
                s_.k == key_string_);
            // VFALCO unfortunately the key string
            // kind increases the cost of the destructor.
            // This function should be skipped when using
            // monotonic_resource.
            sp->deallocate(k_.s, k_.n + 1);
        }
    }

    BOOST_JSON_DECL
    char*
    assign(
        std::size_t new_size,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    char*
    append(
        std::size_t n,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    void
    insert(
        std::size_t pos,
        const char* s,
        std::size_t n,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    char*
    insert_unchecked(
        std::size_t pos,
        std::size_t n,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    void
    replace(
        std::size_t pos,
        std::size_t n1,
        const char* s,
        std::size_t n2,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    char*
    replace_unchecked(
        std::size_t pos,
        std::size_t n1,
        std::size_t n2,
        storage_ptr const& sp);

    BOOST_JSON_DECL
    void
    shrink_to_fit(
        storage_ptr const& sp) noexcept;

    void
    term(std::size_t n) noexcept
    {
        if(s_.k == short_string_)
        {
            s_.buf[sbo_chars_] =
                static_cast<char>(
                    sbo_chars_ - n);
            s_.buf[n] = 0;
        }
        else
        {
            p_.t->size = static_cast<
                std::uint32_t>(n);
            data()[n] = 0;
        }
    }

    char*
    data() noexcept
    {
        if(s_.k == short_string_)
            return s_.buf;
        return reinterpret_cast<
            char*>(p_.t + 1);
    }

    char const*
    data() const noexcept
    {
        if(s_.k == short_string_)
            return s_.buf;
        return reinterpret_cast<
            char const*>(p_.t + 1);
    }

    char*
    end() noexcept
    {
        return data() + size();
    }

    char const*
    end() const noexcept
    {
        return data() + size();
    }
};

} // detail
BOOST_JSON_NS_END

#endif

/* string_impl.hpp
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
*/