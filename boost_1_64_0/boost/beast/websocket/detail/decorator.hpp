//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_DECORATOR_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_DECORATOR_HPP

#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/core/exchange.hpp>
#include <boost/type_traits/make_void.hpp>
#include <algorithm>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

// VFALCO NOTE: When this is two traits, one for
//              request and one for response,
//              Visual Studio 2015 fails.

template<class T, class U, class = void>
struct can_invoke_with : std::false_type
{
};

template<class T, class U>
struct can_invoke_with<T, U, boost::void_t<decltype(
    std::declval<T&>()(std::declval<U&>()))>>
    : std::true_type
{
};

template<class T>
using is_decorator = std::integral_constant<bool,
    can_invoke_with<T, request_type>::value ||
    can_invoke_with<T, response_type>::value>;

class decorator
{
    friend class decorator_test;

    struct incomplete;

    struct exemplar
    {
        void (incomplete::*mf)();
        std::shared_ptr<incomplete> sp;
        void* param;
    };

    union storage
    {
        void* p_;
        void (*fn_)();
        typename std::aligned_storage<
            sizeof(exemplar),
            alignof(exemplar)>::type buf_;
    };

    struct vtable
    {
        void (*move)(
            storage& dst, storage& src) noexcept;
        void (*destroy)(storage& dst) noexcept;
        void (*invoke_req)(
            storage& dst, request_type& req);
        void (*invoke_res)(
            storage& dst, response_type& req);

        static void move_fn(
            storage&, storage&) noexcept
        {
        }

        static void destroy_fn(
            storage&) noexcept
        {
        }

        static void invoke_req_fn(
            storage&, request_type&)
        {
        }

        static void invoke_res_fn(
            storage&, response_type&)
        {
        }

        static vtable const* get_default()
        {
            static const vtable impl{
                &move_fn,
                &destroy_fn,
                &invoke_req_fn,
                &invoke_res_fn
            };
            return &impl;
        }
    };

    template<class F, bool Inline =
        (sizeof(F) <= sizeof(storage) &&
        alignof(F) <= alignof(storage) &&
        std::is_nothrow_move_constructible<F>::value)>
    struct vtable_impl;

    storage storage_;
    vtable const* vtable_ = vtable::get_default();

    // VFALCO NOTE: When this is two traits, one for
    //              request and one for response,
    //              Visual Studio 2015 fails.

    template<class T, class U, class = void>
    struct maybe_invoke
    {
        void
        operator()(T&, U&)
        {
        }
    };

    template<class T, class U>
    struct maybe_invoke<T, U, boost::void_t<decltype(
        std::declval<T&>()(std::declval<U&>()))>>
    {
        void
        operator()(T& t, U& u)
        {
            t(u);
        }
    };

public:
    decorator() = default;
    decorator(decorator const&) = delete;
    decorator& operator=(decorator const&) = delete;

    ~decorator()
    {
        vtable_->destroy(storage_);
    }

    decorator(decorator&& other) noexcept
        : vtable_(boost::exchange(
            other.vtable_, vtable::get_default()))
    {
        vtable_->move(
            storage_, other.storage_);
    }

    template<class F,
        class = typename std::enable_if<
        ! std::is_convertible<
            F, decorator>::value>::type>
    explicit
    decorator(F&& f)
      : vtable_(vtable_impl<
          typename std::decay<F>::type>::
        construct(storage_, std::forward<F>(f)))
    {
    }

    decorator&
    operator=(decorator&& other) noexcept
    {
        vtable_->destroy(storage_);
        vtable_ = boost::exchange(
            other.vtable_, vtable::get_default());
        vtable_->move(storage_, other.storage_);
        return *this;
    }

    void
    operator()(request_type& req)
    {
        vtable_->invoke_req(storage_, req);
    }

    void
    operator()(response_type& res)
    {
        vtable_->invoke_res(storage_, res);
    }
};

template<class F>
struct decorator::vtable_impl<F, true>
{
    template<class Arg>
    static
    vtable const*
    construct(storage& dst, Arg&& arg)
    {
        ::new (static_cast<void*>(&dst.buf_)) F(
            std::forward<Arg>(arg));
        return get();
    }

    static
    void
    move(storage& dst, storage& src) noexcept
    {
        auto& f = *beast::detail::launder_cast<F*>(&src.buf_);
        ::new (&dst.buf_) F(std::move(f));
    }

    static
    void
    destroy(storage& dst) noexcept
    {
        beast::detail::launder_cast<F*>(&dst.buf_)->~F();
    }

    static
    void
    invoke_req(storage& dst, request_type& req)
    {
        maybe_invoke<F, request_type>{}(
            *beast::detail::launder_cast<F*>(&dst.buf_), req);
    }

    static
    void
    invoke_res(storage& dst, response_type& res)
    {
        maybe_invoke<F, response_type>{}(
            *beast::detail::launder_cast<F*>(&dst.buf_), res);
    }

    static
    vtable
    const* get()
    {
        static constexpr vtable impl{
            &move,
            &destroy,
            &invoke_req,
            &invoke_res};
        return &impl;
    }
};

template<class F>
struct decorator::vtable_impl<F, false>
{
    template<class Arg>
    static
    vtable const*
    construct(storage& dst, Arg&& arg)
    {
        dst.p_ = new F(std::forward<Arg>(arg));
        return get();
    }

    static
    void
    move(storage& dst, storage& src) noexcept
    {
        dst.p_ = src.p_;
    }

    static
    void
    destroy(storage& dst) noexcept
    {
        delete static_cast<F*>(dst.p_);
    }

    static
    void
    invoke_req(
        storage& dst, request_type& req)
    {
        maybe_invoke<F, request_type>{}(
            *static_cast<F*>(dst.p_), req);
    }

    static
    void
    invoke_res(
        storage& dst, response_type& res)
    {
        maybe_invoke<F, response_type>{}(
            *static_cast<F*>(dst.p_), res);
    }

    static
    vtable const*
    get()
    {
        static constexpr vtable impl{&move,
            &destroy, &invoke_req, &invoke_res};
        return &impl;
    }
};

} // detail
} // websocket
} // beast
} // boost

#endif

/* decorator.hpp
x4l3C/HeLjpwjYucQeTUufuw35Eo+jhyrxfO5WIZ377B3L+33K98cWebDHSfQ6N6MJ7zFQbpFNII7VfSMHuSqC+Reatdip4+J3lyuKqFH7t1G1mv4aqYM7k8ckLT/Yj4aUEuxRfoclK+b2PWSB51tSLPYEpSP7Gkda34qRAfX1Pbq9YXjPh1wt5Rgv4uUfOF5yBf5Dk8efOpnr9knzFaBZ4Dv2CBc8J3/nmj1S9a3mi4WpH9k3Gf/r3IOdUBc/xXs5JUvjYWe3L4dFL5o3UkWHCdk7MO2ddHhlqgFXYk2FTynjbnksETaaCF9eZRiae95e53kvS80SvE7bHQMCs5dE2okZ5DSo/yg339ZNN33ST+3g25ZPYMtqSxkrWP6SnuceE2/Hud1Sy0X+Oiv9G4Wkpcdn3rLn67h21Zm0YZHynnyOep8TGN42OWjI0PlY2PKesnn3dqmATK6mbR4d1QplIoBoW72FAcQjoUKhOOD8XFxaIJWzFuSJn4+IRyKMRWjmsW1zGuPn8llUkMheVKE/l3gPzbGoZDtTF14waWOYkI7fNsk+JD5eJTytsxNo6Lsz3ioWFci7j+cY34q17caRL4jDIXhqqVyV8WSsQ6qgxpEMeGZUaETolrCPuGgmWqxMfGlcm/N75ed6s3z1VR5HjJZHiE/Mbu3w+NCuBP8nZaKFHs6Ctq+TbnWsTYizBy9qL62R1yZOd7Yp8Q6mX9Fky2r5k6NyCUZN0efCPY32oYiik6TiK+La74/MZJM4n/ddxJN/fDbtK4JtSYa6aOus5ODh3GnVX0SWJ30tIr9GFgivVTsLFV3Jjpqu+9Y6ZNrvT5jpm07Q2Se1wRtc35jZuK5BW+NK+8clHbzKuSjnNDzUJ1fdqK/3iqncR9pzOe0me5LbSYa5HjqZN0/B3W/JLxuAmzPjSca3YbPEr7W1bBjHc2xFPHY4sZY31JeGeMlazht1TQNhyb/wsDrG/iY2L8x1fqH11+vd9FySUZX3WSZ0g8Zh5HprUn/sw4S+89/iQdZ5W/KCE+VDFynGXSGF+xoC2GllSLG0Srb0EiYxGakX14Iv4zRH/fGU8sSS3JeKLvYe94Ik3s1RhPhCUdTryxFZ3xxJLWkeMJxySqXOxQ0Xm2/FWRz5WIPYR9cqIzhjy+8Ue3w4Xjj2XH6GdXuftZvbbOPVbUMeEn33nHhF0PGbvn/XRZQtFzoVpVQ0YeKa/nQvUZOqRf+sheg0ac5j5zrEW1omdCEeZ3nzlGfHrmkzd94ysVTV8H/O7wS5+Imqjp0zDRz6zC/XefWdWi2rHPrHLG4Ud8nqkdN9lvnkmnIfTsNK3nRZ4H/7/77Dvi883vST7n87WxI/zRm7Y/cuadkw+Wzzl77ZvgM/JenCNnRc8H9W/ygTp+7HREyQeTtr0+aWuN39QiaeP8t+hpU/9Jej5n0fPfcP/d579p2j11jnt4zn9r5eyZpPvztNN3vxaYJoTPcJ4nOyd90uw5kf2Eee+bK/5qUWTmvU/DVnX3D+bdZKG4VULfscwx36v0edzvxSKz7HtqeZq1N5+W7hdwwvcLuFHW9lRrvXjxl+MGpjR64pGD7YPPX1C6X8CUE7xfwE8x9vVNH46pe2PGhvKXxO0JJB2+65Hi9xHIwfCTMeCWYMEc8veuvxm/yHq0Pvy9xvX3atffa11/r9S9Bmzxdpv+Dayb9W+7DupZPTonzly5z1k921Xn+jFYD+6AjdRuh99r5oRl7lvCd+bvXdD+NdNwLWFr2AG2g21hB9gO9tDrg2FXOE51nzNgd5gPe8DF8Dp4A+wFN8HecKvqKu9Q+5NqfwP2he+oTvLXcAg8AofqGU1psDo8CzaHw2A=
*/