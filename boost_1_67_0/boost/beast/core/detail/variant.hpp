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