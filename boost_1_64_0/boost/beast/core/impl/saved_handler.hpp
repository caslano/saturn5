//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_SAVED_HANDLER_HPP
#define BOOST_BEAST_CORE_IMPL_SAVED_HANDLER_HPP

#include <boost/beast/core/detail/allocator.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/assert.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/core/exchange.hpp>
#include <utility>

namespace boost {
namespace beast {

//------------------------------------------------------------------------------

class saved_handler::base
{
protected:
    ~base() = default;

public:
    base() = default;
    virtual void destroy() = 0;
    virtual void invoke() = 0;
};

//------------------------------------------------------------------------------

template<class Handler, class Alloc>
class saved_handler::impl final : public base
{
    using alloc_type = typename
        beast::detail::allocator_traits<
            Alloc>::template rebind_alloc<impl>;

    using alloc_traits =
        beast::detail::allocator_traits<alloc_type>;

    struct ebo_pair : boost::empty_value<alloc_type>
    {
        Handler h;

        template<class Handler_>
        ebo_pair(
            alloc_type const& a,
            Handler_&& h_)
            : boost::empty_value<alloc_type>(
                boost::empty_init_t{}, a)
            , h(std::forward<Handler_>(h_))
        {
        }
    };

    ebo_pair v_;
    net::executor_work_guard<
        net::associated_executor_t<Handler>> wg2_;

public:
    template<class Handler_>
    impl(alloc_type const& a, Handler_&& h)
        : v_(a, std::forward<Handler_>(h))
        , wg2_(net::get_associated_executor(v_.h))
    {
    }

    void
    destroy() override
    {
        auto v = std::move(v_);
        alloc_traits::destroy(v.get(), this);
        alloc_traits::deallocate(v.get(), this, 1);
    }

    void
    invoke() override
    {
        auto v = std::move(v_);
        alloc_traits::destroy(v.get(), this);
        alloc_traits::deallocate(v.get(), this, 1);
        v.h();
    }
};

//------------------------------------------------------------------------------

template<class Handler, class Allocator>
void
saved_handler::
emplace(Handler&& handler, Allocator const& alloc)
{
    // Can't delete a handler before invoking
    BOOST_ASSERT(! has_value());
    using handler_type =
        typename std::decay<Handler>::type;
    using alloc_type = typename
        detail::allocator_traits<Allocator>::
            template rebind_alloc<impl<
                handler_type, Allocator>>;
    using alloc_traits =
        beast::detail::allocator_traits<alloc_type>;
    struct storage
    {
        alloc_type a;
        impl<Handler, Allocator>* p;

        explicit
        storage(Allocator const& a_)
            : a(a_)
            , p(alloc_traits::allocate(a, 1))
        {
        }

        ~storage()
        {
            if(p)
                alloc_traits::deallocate(a, p, 1);
        }
    };
    storage s(alloc);
    alloc_traits::construct(s.a, s.p,
        s.a, std::forward<Handler>(handler));
    p_ = boost::exchange(s.p, nullptr);
}

template<class Handler>
void
saved_handler::
emplace(Handler&& handler)
{
    // Can't delete a handler before invoking
    BOOST_ASSERT(! has_value());
    emplace(
        std::forward<Handler>(handler),
        net::get_associated_allocator(handler));
}

} // beast
} // boost

#endif

/* saved_handler.hpp
Snw3JGmifMdIyTlfK3me036Hu+c4sZwkRdNKKyhZWr5QyXn9QrXfgWsT0C3u39VyvYNBLo+yixiujcD7JX2bloTx17v3aLJ5zHdhzI8lB8cLc8m4ByeD6zvuG33GndfIp0GbfZ7P17l9v4M66Js5F+oK3HOBa0nA59Odv696PvZKfIHdHGD+VPW87ZF4CuOYUYXii81/PpCX9pTkn8X54SmvJ9M99An+zy/lrp6Q/Ks4Lzz0PZjf4KOCc/RFSXcpXlvHDl5+5+MpwfHaQvFH5DuuOcZx9RnDkafR1jXPL/uQx9mYp8YwIH8TY8j8nf35mXw2nLLGJXIMPfnb2/IzWV5AfqYxX6bXNoz07e4g+7a5+Zievh1L2e7ODvfz8Y1nrSyUvuU7MfDz4c7fV83fbRL/xH6NLDQ/Hzcyv+36WMj5z3X4eol/bvv++jHL4/wnfQ/f9U18zpQAH5H0evTTBP81kHn6yx5knjYI49eaa6Bn/XuK65//tVP/LuQ175pofU3xs2scdnxcO76mHf/Yjj8aOr9zsfB3n9/1zoKvVt+Sv3zLn59cf/vbL9jxd0Pnl4fKbw6Vvx4q/1vJyRR5+bu1mpm/m0T+bjdgFOPKpvIJ0jWeIJ1WfGJ0so8EfmNDN4J0bxrosjXua4CHSEffA4ounnRdGR/H+D7GX2X8DVN7+F4E3mHTnuGk22ygG6lxTQcOJJ1RnqYnfRb0ojxcb/pkSFX1cj3iumtV72DW+w3j1cg3FrzIHIQqhC0I4H8HlAvJGmPmeR9GeOhvLcjrVrxtW772TPKzjwONfOsdY7286gOKRy18aT8+9FgEI/95n/43+cxHEBRP2cxP9uUlK/5xNoLiF1vziRVfOKtpXrDwfLejL3cjNCB8jZDwMWQmEOYhVCNs+zjMAw7/wr/wL/wL/8K/8C/8C//Cv/Av/Av/wr//1e+UnP8vKRgmx/8nef6vn80/lOLWmeoblh8+ZXrU33e5352O4PTErHh/RxAg40r5VkvZVsq0Wul5NS3D2hdhJoKNXhflVI0yqma+4H6Ew+nNp7u1DsEoa7ofwSxfaiVbaiVP6itLGrz8qEd2NPwL/8K/8C/8C//Cv/Av/Av/wr/m/7VAWPLf//4fmluyKL8gd1HhsGbQA+jp0QOYp8t8LPGWTQk7j63/ewy2/kfaydvnKdl1YyuDkl/3yEpvoSFTiFZoqcDTgXFoX+zFUrax3IAygG6awUqGeZzEP3SM0Q545V4voU10G7lAlGGSgz9b4nFOX7lAZbdS0sc6lmq1QpOtyuhPuU5IXkqdow2ygmKuU8kKjpT8iU7KCpK+r0FW1gUCr2xttqQ7pE2t++vplCOl7OMkSY+S9LtkJNCDMq4TxVbfeMgPtqP8Z29cuA9j/RsED07qoYJf2sBE+VvGONN6jCfEiX2vM+PSRdbP0Yz2B2iHmvb475J8uDefOfU0bfBf6HTTnQVM1OV1L7GYU1VLyuxldkljmA9Jl+rxZKdX1rZqpatI+ehj/v7K5nVXPT9i3vz5SxYY5KS7SHofJ23Mkr6f5I+Q+emqWqJ5bfTHXyrpzu1e3QjSpGl+84HzK01oujrbI/2FBD1dbl8ycU4YbKxybrL9dbk67e3KZvdGibfSMjCHojmH7lfzg38bMKo95xjnjCvAnMkzzJk6izmzQ8mQSr/LtZ3qGvqW+R4FRsjccvdfPOcM7h/X1P3LvDmb8yaPYlbf0mbuy5Tzrp/rN28Cynvra8MnQtebc4nloBeMa4leBNcepndVz/Ehib9jJ//N/L0Cyn8b8+GZ9Z8nnItfSL56k72LTpjUU4D3N4ucuNxvSHLiR4C4Vxt+7H+fz2wn7/tiF/E=
*/