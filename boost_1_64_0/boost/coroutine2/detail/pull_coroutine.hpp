
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
UuFgjB5c9dLWZuSp77Er6z2rVJJcSt/PnCdWo6Ql/HXWe5BUjT/5aRa8haFiqeRdHSR/YglIDKJLVUMdnOn9vcN0nl5NsvFigjefzFhP18NBE+3iET60632XgqW/1/2Hgt1NQT72CClLyVMZ7I3kT1WQvyYFRrqqbeEm/997SJK3UlB3FcFUNd5ddK1WEBulE+QkmdNplXV/qfcR0Vqq0nVl38nPhv7VN5mv5Rs+odmTO4e68xbo9x5WGpi/XXQevOIPf7qxa6p9IUrwaXd1/3sPxcaZ6z65HUkPnS97NYek7QaEKdqVgsYestfOQPe7+ZA0KWyCvCvpowHP5I+YKP+QjiOnC+v3VUa6Ie94GDKkUuDximRWcX0/fU7fk0zWeNa9xr4gCrr0ILklgoJMd4JWHfTe4qPuazMAmG2h/bwqeT3FUNcYR+bHJGLDM/SecCRJ6+PW4BWCpKG+BdjpRN2CtQkCXPW+/ZTu4xVrXwOSn56y1+5r/dNFrr1Qvh7Ueq9vMtfKEF5x2Vn+WNlDibDWv4nstafIUWK4vm8M0HtbWYI9XljRvzt0v/CKeT65jr4/v6L9baT6Q7LtrUvyhBV9/lH2WsNVFno/RN1PM6i2vzaxVWG0O2oIw/aAvM6RdWm84wc6YNht4O13mcNfWfI6aAUe9EHjr4K+N9WhsLj643sPnVcdyOv+Vu+lHoPy2ZmgyidKK+hTxGYNKYieJ/tA2870NgSHtOr5Tab0W26SlxbAkKOJvr98ovfeQbqPWkG73vJoJkwD4IJegP2MJzatNTUO1qH0zHDyimjXXaTtuNJJfb9VTf5iXXztmyT96cx05AQF6+W3tX0I8VZ9Ltr+gvy7xwlG14YkX7y7vu8O0Pc4lOYdTafMfarvnbPIi9+v36sKYZ7bZGo/n0+s+xi9z5bWEprAywG9RP2ZDxG+vNH3Blq0fKX7azeg2ySrYG5rnd9kRsUfJrkur/bLWbRbpioA55W0jQAlu7ret+tLpAr6ZYBjtvo9FNnFwfqwcPslSs1ktey9BPfWkndEit5b6LRY9wckj/WkOfMYpQP00zRun6lrqqk7oRfJWo/1vaQ2V0Mz/b6F4HvNZq42cCY244o5+jviL/tZ75XP6/w7mNh5S913XwF0q7r7wlG975SvufB4rfey71/dgSR1OskP1fU9ZzWdf/PZw59Gp/9IaqzcIP+kLAoTPSj2lm1Wtou+t0qndIKOPJYH4b5qhr7njJF9ddQHvEmUvvbU70fI+b1Zg6uhnEnhGru/LSM55KP2N099b6or4h5ZgN6SieN+QfuvOsowW9/ryvnzh6+Mlzt3dV6YT0O5e9FRxvqao79m1OOi8ufU0nvRazSZkKX3OZZoKOkeNfrKf7rxAiRn9Ia5yAn9vsByhndGR9idMUDfR30Bqrid7qeLkjwykwKnp/RCovpjqd7aH0ilho8lyb46GL/X+aOiLIrjNTT+vgYgbwGUM1ZPAFxWEKscpvexv6fJqRrKsZ8gqWeCwq54aL7JFbH6vIH+XaPvU3RY8S2o9dkI2cysNH+76L7Cx5Hx546aBuvD77o6C5VRf3T/SBCkj9pHqfdLyqXXWj7pbZHIMUzH5j3G3uAVh+QPUmw3c+j63SW2uBYF62SreH3V/ZvM1cyK8g/V1e/nhFJwfwg8R74F74sKqmojqK+leXkJ1LlIW/RcLShhGiouBxHBUfvqjXU67w+Fbv8TUMbn0v3+NGKTHtHuBM2AYzoHxL2T/0/nAI8kgvynKJgr/X2Tl6lxXeAH39J6/4O6TbSzrz+t77FbI7TbRGoETpe/8ynsFpYcB2tDsieYgmvZJM3kB/Y7Rsx6CcFhXQrcVcE=
*/