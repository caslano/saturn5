
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

    iterator begin() { return iterator (this); }
    iterator end() { return iterator(); }
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

    iterator begin() { return iterator (this); }
    iterator end() { return iterator(); }
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