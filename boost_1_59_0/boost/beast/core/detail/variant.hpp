//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_VARIANT_HPP
#define BOOST_BEAST_DETAIL_VARIANT_HPP

#include <boost/beast/core/detail/type_traits.hpp>
#include <boost/assert.hpp>
#include <boost/mp11/algorithm.hpp>

namespace boost {
namespace beast {
namespace detail {

// This simple variant gets the job done without
// causing too much trouble with template depth:
//
// * Always allows an empty state I==0
// * emplace() and get() support 1-based indexes only
// * Basic exception guarantee
// * Max 255 types
//
template<class... TN>
class variant
{
    detail::aligned_union_t<1, TN...> buf_;
    unsigned char i_ = 0;

    struct destroy
    {
        variant& self;

        void operator()(mp11::mp_size_t<0>)
        {
        }

        template<class I>
        void operator()(I) noexcept
        {
            using T =
                mp11::mp_at_c<variant, I::value - 1>;
            detail::launder_cast<T*>(&self.buf_)->~T();
        }
    };

    struct copy
    {
        variant& self;
        variant const& other;

        void operator()(mp11::mp_size_t<0>)
        {
        }

        template<class I>
        void operator()(I)
        {
            using T =
                mp11::mp_at_c<variant, I::value - 1>;
            ::new(&self.buf_) T(
                *detail::launder_cast<T const*>(&other.buf_));
            self.i_ = I::value;
        }
    };

    struct move
    {
        variant& self;
        variant& other;

        void operator()(mp11::mp_size_t<0>)
        {
        }

        template<class I>
        void operator()(I)
        {
            using T =
                mp11::mp_at_c<variant, I::value - 1>;
            ::new(&self.buf_) T(std::move(
                *detail::launder_cast<T*>(&other.buf_)));
            detail::launder_cast<T*>(&other.buf_)->~T();
            self.i_ = I::value;
        }
    };

    struct equals
    {
        variant const& self;
        variant const& other;

        bool operator()(mp11::mp_size_t<0>)
        {
            return true;
        }

        template<class I>
        bool operator()(I)
        {
            using T =
                mp11::mp_at_c<variant, I::value - 1>;
            return
                *detail::launder_cast<T const*>(&self.buf_) ==
                *detail::launder_cast<T const*>(&other.buf_);
        }
    };


    void destruct()
    {
        mp11::mp_with_index<
            sizeof...(TN) + 1>(
                i_, destroy{*this});
        i_ = 0;
    }

    void copy_construct(variant const& other)
    {
        mp11::mp_with_index<
            sizeof...(TN) + 1>(
                other.i_, copy{*this, other});
    }

    void move_construct(variant& other)
    {
        mp11::mp_with_index<
            sizeof...(TN) + 1>(
                other.i_, move{*this, other});
        other.i_ = 0;
    }

public:
    variant() = default;

    ~variant()
    {
        destruct();
    }

    bool
    operator==(variant const& other) const
    {
        if(i_ != other.i_)
            return false;
        return mp11::mp_with_index<
            sizeof...(TN) + 1>(
                i_, equals{*this, other});
    }

    // 0 = empty
    unsigned char
    index() const
    {
        return i_;
    }

    // moved-from object becomes empty
    variant(variant&& other) noexcept
    {
        move_construct(other);
    }

    variant(variant const& other)
    {
        copy_construct(other);
    }

    // moved-from object becomes empty
    variant& operator=(variant&& other)
    {
        if(this != &other)
        {
            destruct();
            move_construct(other);
        }
        return *this;
    }

    variant& operator=(variant const& other)
    {
        if(this != &other)
        {
            destruct();
            copy_construct(other);

        }
        return *this;
    }

    template<std::size_t I, class... Args>
    void
    emplace(Args&&... args) noexcept
    {
        destruct();
        ::new(&buf_) mp11::mp_at_c<variant, I - 1>(
            std::forward<Args>(args)...);
        i_ = I;
    }

    template<std::size_t I>
    mp11::mp_at_c<variant, I - 1>&
    get()
    {
        BOOST_ASSERT(i_ == I);
        return *detail::launder_cast<
            mp11::mp_at_c<variant, I - 1>*>(&buf_);
    }

    template<std::size_t I>
    mp11::mp_at_c<variant, I - 1> const&
    get() const
    {
        BOOST_ASSERT(i_ == I);
        return *detail::launder_cast<
            mp11::mp_at_c<variant, I - 1> const*>(&buf_);
    }

    void
    reset()
    {
        destruct();
    }
};

} // detail
} // beast
} // boost

#endif

/* variant.hpp
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
*/