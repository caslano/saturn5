
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
ETVOg5MEv0fWnrx5DoP9WR3TqVVRu4i4Shtl9d5i0/eTcjIdOSrkgB2qh38J8cGw+Uxch5zGotOZRkZTtHBNRi8q9o2kjdC3ygrm4jnUuJgNh/ZFitLQdKpoC9s2xX/KWg7/W8CEWfgiWEmhChHHgwNd18T+yGwepMGzDobcxaa4cbnNxuwB7LQ3XAtnrn/0yBJTmTHE0hcK69lxSc14wO7nO94ygHvfdwIHAMkj1oumhRtLqK4Bq0upikCV99PtMdJ9THiBUt4NzBdUtug5w3iWbEqwInRytEjFEBd5U71eKw9J3jnYjDLtS98lSO2TAb+/fvUCwWmvnEKD6TCFMQsaz/mHk3RRYpW0zyqDVHqP9gAFiZoH+iqgkQxdcQk99sVPj3q953Kg1oPIvf6L/wcUEtKdOFPIFtJL6FxUiovbJsr6MgCbz2YaQM5F0HH/IVnXICRvOpLivdGj6bOxJAioOqleaQMSwKmAkncbtvrc5sB1WZrJOiB8bXuU2KMElff7YL6MRNUB1n7HMzKwRI7q8zDgkM+2y/p+cJ+YpAUxlRWSCuzPxMDOmA==
*/