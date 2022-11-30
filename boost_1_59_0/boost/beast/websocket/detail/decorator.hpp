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
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
*/