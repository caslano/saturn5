
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
nSdd2Qd43NnL+fDrcg/wnrwMtdPnAH5tRTLwzsHHzSFkvzkVyGUpyD5Gi3/bBNBnqhj/0eVfWAOZ7/8DqapsVFQfzPPskhTo+wL6FpZB5mKuk0/lIrvnTYxPKdoyut7LDORO5sHlJXP5Pmc1Uut5PPv+97w/mAeozDd4/cFD7U3pKEulJZOu5fV+Bq/PP0dFMt9Tn3gwah/j298/ns3f00L8jPUKg7fHB6nA40Xm3T3xUb4rQHtyQZkQj49TlyJb/Aya7HQS96MPkTqP0+ppxspXzuB5Nl3lrEm7QF/8OMSHggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkCBBggQJEiRIkKD/BPlr1mb564p92f66Ul9ecV2Rr6AYWb+/Ptk55gCHH7+xL1PQd1Yo5A+wZYAtA2yJLFrGLR2NljXzs0Llbhu8F0cTL0bB+6wsKt4tKp7HBm+IhBer4NVGxztUxcuwwUuV8FwKXm50vJZRCl6mDV7TKOLFKXirB0fFu1fFy7LBGyPh9VDwpkTHO07Fy7bB6yvhxSt4RdHxNl+u4OXZ4C2+nHhuBe+XM6PiPaXiFdjgjZPwEhS8x6PjDVbx/DZ4AyS8RAWvNDpevIpXYoO38jLi9VTwXNHxXrtMwSuzwbtDwktS8F45IyrexSpeuQ1eoYSXrOANi463k4o3wgbvp5HE20HBS4uOt2CkgjfaBm+6hJei4M0vjYp3tYo31gbvVAnPo+BVRsfbR8GbVo2Wk/Vkp38F8VNV/aPjL6hQ8Cd2A/8OCX9HdfxPjz7+Kv7kbuAPkPB7qf4fHT9exZ/aDfzFlxI/TZ3/p0Wf/5cq+NO6gT9Gwu+trn/R8Y9T8Z/uBn6qhJ+urv/R8VsuUfBnOhziZ/cFCRIkSJAgQYIECRIkSJAgQYIECRIkSJAgQYIECRIkSJAgQYIECRIkSJAgQYIECRIkSJAgQYIECRIkSJAgQYIECRIk6N8gviyeydfGM/gCucePrLshj++LjzkO74v3a6653jfCUTmAv1qwIwrQMsuPd8fLmcrkC+RlxciW8KVyvx/ZguDcg0OhtgPR4dPUrnVwHoF2NfPz5n3YOVnK66e8TcdK8oLvx2G+eYFaXzWqkMymCGNVYUarwowopmwUpozClARfLZaE8XdFGFt5BqjyHLE98qzf8y+SZ/oxijzPe7ZDnhkDuymPUZSxFCU9LErNG+APqkxncqKU7MnkZCardi1s+Bo/h+Ov731Ilg9fyffiK9R7yMcHOnIa/RCezSRJ57iZCqsTcAeLrvY69go5QlStOFx5q1yZENyflQ7UQp/ingsDTbNdbFDxnoNqZua4EmkGI6TfFdxwlYZZYsQ83hVcxlqC0kh6UKcOtH8EqDv4gA60NALUHazRgZbqQWN0oNkRoEnBY3WgZRGgScEDdKBletBYHWgR8SazR/UGfC7egjI6RlZTMCPQiKH4bAefA82LmtZ4xq0KseGS4vq4t3b0OQoDaZMDrnE5c4Gf3dTqHrdSqn4Pw/hIus+R45qEiv660rqdpVJFDJdOjAKw7K+wHCKzzDKyPDGCZZGRZX+VZbauNN3IMk7HMh8ssxWWPyaTJUQwsFyWamSZZWQ5u7cETll0pY/1MbDsobHEPITBFZbXySyzjSyHR7Dsb2R5rMoyS1eabWQZr2OZy8HEjz01ZkrzBxl/aCHHGMu931EV17rYCRAMgCLW6iRJrFyjWB97jGLlGcV6IU0RK19Xel+GVGo568AyX2E5RmZZYGR5TgTLXCPLfJU=
*/