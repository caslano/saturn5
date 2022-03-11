
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_PULL_COROUTINE_HPP
#define BOOST_COROUTINES2_DETAIL_PULL_COROUTINE_HPP

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
class pull_coroutine {
private:
    template< typename X >
    friend class push_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit pull_coroutine( control_block *) noexcept;

    bool has_result_() const noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< pull_coroutine, Fn >
    >
    explicit pull_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    pull_coroutine( StackAllocator &&, Fn &&);

    ~pull_coroutine();

    pull_coroutine( pull_coroutine const&) = delete;
    pull_coroutine & operator=( pull_coroutine const&) = delete;

    pull_coroutine( pull_coroutine &&) noexcept;

    pull_coroutine & operator=( pull_coroutine && other) noexcept {
        std::swap( cb_, other.cb_);
        return * this;
    }

    pull_coroutine & operator()();

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    T get() noexcept;

    class iterator {
    private:
        pull_coroutine< T > *   c_{ nullptr };

        void fetch_() noexcept {
            BOOST_ASSERT( nullptr != c_);
            if ( ! ( * c_) ) {
                c_ = nullptr;
                return;
            }
        }

        void increment_() {
            BOOST_ASSERT( nullptr != c_);
            BOOST_ASSERT( * c_);
            ( * c_)();
            fetch_();
        }

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef typename std::remove_reference< T >::type value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type * pointer;
        typedef value_type & reference;

        typedef pointer   pointer_t;
        typedef reference reference_t;

        iterator() noexcept = default;

        explicit iterator( pull_coroutine< T > * c) noexcept :
            c_{ c } {
            fetch_();
        }

        bool operator==( iterator const& other) const noexcept {
            return other.c_ == c_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.c_ != c_;
        }

        iterator & operator++() {
            increment_();
            return * this;
        }

        void operator++( int) {
            increment_();
        }

        reference_t operator*() const noexcept {
            return c_->cb_->get();
        }

        pointer_t operator->() const noexcept {
            return std::addressof( c_->cb_->get() );
        }
    };

    friend class iterator;
};

template< typename T >
class pull_coroutine< T & > {
private:
    template< typename X >
    friend class push_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit pull_coroutine( control_block *) noexcept;

    bool has_result_() const noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< pull_coroutine, Fn >
    >
    explicit pull_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    pull_coroutine( StackAllocator &&, Fn &&);

    ~pull_coroutine();

    pull_coroutine( pull_coroutine const&) = delete;
    pull_coroutine & operator=( pull_coroutine const&) = delete;

    pull_coroutine( pull_coroutine &&) noexcept;

    pull_coroutine & operator=( pull_coroutine && other) noexcept {
        std::swap( cb_, other.cb_);
        return * this;
    }

    pull_coroutine & operator()();

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;

    T & get() noexcept;

    class iterator {
    private:
        pull_coroutine< T & > *   c_{ nullptr };

        void fetch_() noexcept {
            BOOST_ASSERT( nullptr != c_);
            if ( ! ( * c_) ) {
                c_ = nullptr;
                return;
            }
        }

        void increment_() {
            BOOST_ASSERT( nullptr != c_);
            BOOST_ASSERT( * c_);
            ( * c_)();
            fetch_();
        }

    public:
        typedef std::input_iterator_tag iterator_category;
        typedef typename std::remove_reference< T >::type value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type * pointer;
        typedef value_type & reference;

        typedef pointer   pointer_t;
        typedef reference reference_t;

        iterator() noexcept = default;

        explicit iterator( pull_coroutine< T & > * c) noexcept :
            c_{ c } {
            fetch_();
        }

        bool operator==( iterator const& other) const noexcept {
            return other.c_ == c_;
        }

        bool operator!=( iterator const& other) const noexcept {
            return other.c_ != c_;
        }

        iterator & operator++() {
            increment_();
            return * this;
        }

        void operator++( int) {
            increment_();
        }

        reference_t operator*() const noexcept {
            return c_->cb_->get();
        }

        pointer_t operator->() const noexcept {
            return std::addressof( c_->cb_->get() );
        }
    };

    friend class iterator;
};

template<>
class pull_coroutine< void > {
private:
    template< typename X >
    friend class push_coroutine;

    struct control_block;

    control_block   *   cb_;

    explicit pull_coroutine( control_block *) noexcept;

public:
    template< typename Fn,
              typename = detail::disable_overload< pull_coroutine, Fn >
    >
    explicit pull_coroutine( Fn &&);

    template< typename StackAllocator, typename Fn >
    pull_coroutine( StackAllocator &&, Fn &&);

    ~pull_coroutine();

    pull_coroutine( pull_coroutine const&) = delete;
    pull_coroutine & operator=( pull_coroutine const&) = delete;

    pull_coroutine( pull_coroutine &&) noexcept;

    pull_coroutine & operator=( pull_coroutine && other) noexcept {
        std::swap( cb_, other.cb_);
        return * this;
    }

    pull_coroutine & operator()();

    explicit operator bool() const noexcept;

    bool operator!() const noexcept;
};

template< typename T >
typename pull_coroutine< T >::iterator
begin( pull_coroutine< T > & c) {
    return typename pull_coroutine< T >::iterator( & c);
}

template< typename T >
typename pull_coroutine< T >::iterator
end( pull_coroutine< T > &) {
    return typename pull_coroutine< T >::iterator();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_PULL_COROUTINE_HPP

/* pull_coroutine.hpp
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
*/