
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
Dd85gi37bIw3OPxn35X9LylC34PnOOzSrsWxy9IW6BNd/DF/FUj4NwnfdhPKELXp/FICWu6MNuaMKRVpyLAp1JjkDuV5SpogkuRYqr2cSMgBr3CE8WSdn4pEhMosTmMb4uCKYI+wJdqt/9Hv/YgHVRbQYSaz55IFhHjCczyrohw3kWqX6qyJ23S62XM5S7WAViz7tvmuTs9OFwL5CSQavBtJpZbdZ36MTDnfgVxDLyXDdLPrclr787K5dTdp5UZDppnIj7NN1rUKuMFlOD0e0n4i7kbamdI3VJ/M/Zl0uHpJSaNou9ME4HQlVtGogVHvhKLLDX3Qr3BGOd1zh5pYjKAD3mleZDW81qy22QyGB3E9EhUPVINtu9arHRWrMqglIJrwgDPl9Bpa93Cc6t+Zp2ghYzZKuOCoF2WTjhyXTt5+XlmiuyixPHPI9UUBbLej6J5xIMjXxs4qT6YrLuzFoy78s9hR/hR4LvfmxhELAvG8hlKe4XKyAJscu9nGmnbsw3Nrl9oPeYwg0WZaUdiu0RS1tMF1CDNx2TcrLpmdzXs7AWy94zPu14SuGw==
*/