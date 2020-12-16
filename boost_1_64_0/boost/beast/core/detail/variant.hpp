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
DXy00rjRT92OO7DHftleFePeh/s/vYn7NM0/bv+DiexOnzpTxrw1ScacayBRN8/2vTDqqMrPI15fmdKms5RHKppYmcOBQcwBv4s54Hd5LMX6nKFv93zpU95rUr5Ale16rOK93eddZJt3bmZVcy4KYs5ljjkX1cOcn+UcX+Kc31Rlx3O2Cfdd45y70+6z3T9nfHOmn4qP0ZnYKT7H3PE8sN9/TmJFjkE+LdGodvwN6WO6p8ctcteH1Z1+bngbGefY/KFXTvq100E9P3vts1M/vlSnn9Pt67776edqqodz1+dVHc8oxaDMwm+4AseeZrO5l948xjVaCBwGPANIenzL6+nPIf15pL+Q9BdZ6AuroL+Z9EWkv4v0d1vojUf09CtJv5r0a0i/1rqHL+nHkd66l18M97xsTj1VHPtrB0Q24hnnqRX3DG4DHMX6MSyLzy5yOX/nTv7OPsB8/k4i9wTvDDyA+kt5r9F3sit/J8Xi0zsB2J3xpHtR35nMuNJ9gAXUay4jHfd45DcCrl+Ow7rH4yGWvUIT6NObCBxGn9RDgcks92eZ/eIdru/3SPY7gv0ezX6PYb+j2O8x7Bdl9ous71ftdZvNvSNzeJ5nALsApwP7sDyAZbXXZRX9Xsl+r2a/17Df69nvdez3evaLsup3O/vt79LvGPZ7HPeqPJ7X0UT2OwnYHXgS+TEZuCxIfWjZ8j1DJ8o9A4PWjW7r27hO9KM7P2pk2zMw88jIOt03sEJfunvsF1ifewU2uN60AfcI7A6d6SjkfORC5DLkrcg7kONLsA8g8mTkBSW10616yUte8pKXvOQlL3nJS7tbaoQ8tX7t/7np8/NCjv3Xymja7JP9IXNPDjfCjPnZOXNm5M2aZWq2DfELGGdZF9CRfgE0ZYhcfjsUNEUVfgGqg2DXBfSkvh0FSV2Q92PMq7cxrjx/31NzZk6RPulL7oylwnYtLLGdMAOpp/1P6qOlPJLtrfaSvnGGMb4G9hKMwRaDIoV2SqvNqhvndg3n1hZ5H+TmyK+ZPH9Q5pYzMydfNy+2sY9zQhD69crjtPO7jIs7BiDvT76/gT8S/Pyel5c5JT9Lz2+2ayv1EWKjAsEU2pZVfUtlWx4o5Xhp38GQ/mbNm5mvzs8Ai99HGulRts17YojnB+PEMRmnsk1jLDgmY/FsEpVsEjrbQ/37DH8vPsNffl8ycE70qBv26jr/y8UDXxu7++2x4G570NlI6t9nmHEV+EzGs9oZV4E+uwZ125HA/hZbQB7purjYAhKog25PHXsiMJFl0vN5hfvUhT6OutsW1N3GA1uyrGwh/P0BLvSt2b4Ndb0HAHuzvCBIHe+yksj/rJ63PnS8nn7X0+869btluIe2IH+KvNPT4XrJS17yUkP7/+emz82ZdnrWnJB1AKacf5zF/z+NPtuvm/EsiWmxhrFprZLzDxc/xeNzps08UiTzSnJiK8p1O4TmNl+y0Rg2+abGYF87ypCB/vqp2KK9y/wyZYyS4TFB2Y6PciVp0FKtV/9Bynf4JvoihK5DgM4S3zJN0fVU68W/k/LdvpN9jay+sSqG6If3++XXMCNGrffvKMcGYiYHyvxa4Nh1cmwj2jWDXD/auMzooeJ6qvlIW3hsSjnPSDKGCL8+kzXxecKwVowf+o2M63bfvUaY9LqPb7IRI3U6+kyTXsnZvWU83VnmGKxraRl3nzHkLevsRW+h4p/GqDX7WPibLj+hYoffL79xtBHHeAl/Sfk6nMl2iAWXYuHnXOVPnSvjiFD+1F2kHGb0hHy/N+pfhnBxaDzaIceCoE1L+VvWXJ+Mv09rLSjyf6FhVLn2usASK36TQxcQh2Obla6G1xePbwF24HE=
*/