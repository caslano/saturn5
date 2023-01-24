
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PUSH_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_PUSH_COROUTINE_HPP

#include <iterator>
#include <type_traits>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine2/detail/config.hpp>
#include <boost/coroutine2/detail/disable_overload.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
class push_coroutine {
private:
    template< typename X >
    friend class pull_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit push_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< push_coroutine, Fn >
    >
    explicit push_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    push_coroutine( StackAllocator &&, Fn &&);

    ~push_coroutine();

    push_coroutine( push_coroutine const&) = delete;
    push_coroutine & operator=( push_coroutine const&) = delete;

    push_coroutine( push_coroutine &&) noexcept;

    push_coroutine & operator=( push_coroutine && other) noexcept {
        if ( this == & other) return * this;
        std::swap( cb_, other.cb_);
        return * this;
    }

    push_coroutine & operator()( T const&);

    push_coroutine & operator()( T &&);

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    class iterator {
    private:
        push_coroutine< T > *   c_{ nullptr };

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        iterator() noexcept = default;

        explicit iterator( push_coroutine< T > * c) noexcept :
            c_{ c } {
        }

        iterator & operator=( T t) {
            BOOST_ASSERT( nullptr != c_);
            if ( ! ( * c_)( t) ) {
                c_ = nullptr;
            }
            return * this;
        }

        bool operator==( iterator const& other) const noexcept {
            return other.c_ == c_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.c_ != c_;
        }

        iterator & operator*() noexcept {
            return * this;
        }

        iterator & operator++() noexcept {
            return * this;
        }
    };
};

template< typename T >
class push_coroutine< T & > {
private:
    template< typename X >
    friend class pull_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit push_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< push_coroutine, Fn >
    >
    explicit push_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    push_coroutine( StackAllocator &&, Fn &&);

    ~push_coroutine();

    push_coroutine( push_coroutine const&) = delete;
    push_coroutine & operator=( push_coroutine const&) = delete;

    push_coroutine( push_coroutine &&) noexcept;

    push_coroutine & operator=( push_coroutine && other) noexcept {
        if ( this == & other) return * this;
        std::swap( cb_, other.cb_);
        return * this;
    }

    push_coroutine & operator()( T &);

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    class iterator {
    private:
        push_coroutine< T & >   *   c_{ nullptr };

    public:
        typedef std::output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;

        iterator() noexcept = default;

        explicit iterator( push_coroutine< T & > * c) noexcept :
            c_{ c } {
        }

        iterator & operator=( T & t) {
            BOOST_ASSERT( nullptr != c_);
            if ( ! ( * c_)( t) ) {
                c_ = nullptr;
            }
            return * this;
        }

        bool operator==( iterator const& other) const noexcept {
            return other.c_ == c_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.c_ != c_;
        }

        iterator & operator*() noexcept {
            return * this;
        }

        iterator & operator++() noexcept {
            return * this;
        }
    };
};

template<>
class push_coroutine< void > {
private:
    template< typename X >
    friend class pull_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit push_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< push_coroutine, Fn >
    >
    explicit push_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    push_coroutine( StackAllocator &&, Fn &&);

    ~push_coroutine();

    push_coroutine( push_coroutine const&) = delete;
    push_coroutine & operator=( push_coroutine const&) = delete;

    push_coroutine( push_coroutine &&) noexcept;

    push_coroutine & operator=( push_coroutine && other) noexcept {
        if ( this == & other) return * this;
        std::swap( cb_, other.cb_);
        return * this;
    }

    push_coroutine & operator()();

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;
};

template< typename T >
typename push_coroutine< T >::iterator
begin( push_coroutine< T > & c) {
    return typename push_coroutine< T >::iterator( & c);
}

template< typename T >
typename push_coroutine< T >::iterator
end( push_coroutine< T > &) {
    return typename push_coroutine< T >::iterator();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_PUSH_COROUTINE_HPP

/* push_coroutine.hpp
mZPwzik3Exuli3sl1vgqfyvKC21P3k8/HJRReQEVQwXRdQxiPDOY0wDPI5EKCNOoxVcUhJ7bqC14Pex5Z/qsTrcl/vS15/V0yz38SuvB/6bKsslB+vp8Fu40jzrJOxPHaKvUzw+GUvmkBCjAJeEYTm0fzgaSJeN2Qlqt3XEDlmT6FG6qPMLYkz9ZVqj1FXvQZqH9DsoIU6AZx46c4Sqm34q3lXHzEafNGhNqnLE5Cc7A6pHooEDtSa5ykvmzKwEdajHX0001r6HzZoHasmRNOJrbFVzzZw7g1VtcrNCjxB32FSFMd96oVBijr2FU0YvWCXrYaYo31pswWRyNpt1UU/VhhUoQZs181WHIGsFrVJ6nO1tAQLCnu0cc32Pjc9xeOTkFGDx3oRshCeahAMUcakLX5ze5fRI3vutSf4xS6XjW/8v7mzgBVwlIge/Z7n2jtnghBRa5LlcIAYVKP/c7Ts3ByDXXlqCzqsit4eXgFqxdi/NvDRqjTpI9CQ4EHdn02OcHRnSBQGIUqsoLrveNX+xQNqYNixj/hrvsKeIH7PfrsbwthurYC34uBAZkUd4s1UstI1RZVF9gtqDitMY4WGAoTNamZ7CdGzWnVfPUMVfJGgvYmWXNXflU5q1W/CLsVLuwyTEd8dG+VGWNzDl1yNSHo0dgiA/ouD6dvQ0aXB9xnDGKdFd69pXOpMy9cOVB8eIMo7i8nUau7wNy
*/