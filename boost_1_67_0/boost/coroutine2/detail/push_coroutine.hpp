
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
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
*/