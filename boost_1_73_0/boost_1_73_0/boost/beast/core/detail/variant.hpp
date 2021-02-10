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
xuX3t5eX/fFm6+hFFMq21+ukH44MCtjNd1Tfda+Oj65ew78JJrbBj9eTUMfwun1cIhKN7q5G5z3F/DWin4+GQ9RzZefoT91XLAZXZ3LT7184V4PrwfR1nKvFxNxw3tmM4uzhSDMATwqOcG3tZnUYVJSrRM74z3phSrnyRtuxBhGbJajBuuPtZGr1J1A2irmXghyBcLTGrC0eqGDM+L0U1X371HAkvE2DxYJaLDJ9RALHX4GoCFKSiaRH71T5eb2sbnMupgjPJN+Yt9f0VUaSEGwr9OeX4gtkBLVZZTeEv3Uwb8PLb5041zBfO2xriND4/9QPMW+H4fn8llIcdd/9mapKzgRCiTU5x8KFCjOzAiVhJ18hGHdo46dieHt1pV8dTiAdfSRwz0fhxxrrP/QJSJCVp2ltPuzifr2SoP6+E0Ieizaxx8z2WIi9PKGOeGpa2YgqeFolndTDquWggj6A+ClPqjhV5XuiCp3MoJHis17MfF1aE6NnE0Y8rMVOq9TjH8VRSUe906AOx7qEZnpTTrFFK6T+jNXCQpuFpX4q1Wh1YLjOTfHD4Dorngzhm5Nh+isqbfDgpDGsDt3EVvVdw9xqUXoPN2TDqPRVbYcViaeNB0+164ZSt7Gy1slWq6urDSq1d3n1mU+V2axt
*/