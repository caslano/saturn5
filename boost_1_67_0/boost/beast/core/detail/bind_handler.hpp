//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BIND_HANDLER_HPP
#define BOOST_BEAST_DETAIL_BIND_HANDLER_HPP

#include <boost/beast/core/error.hpp>
#include <boost/beast/core/detail/tuple.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/handler_alloc_hook.hpp>
#include <boost/asio/handler_continuation_hook.hpp>
#include <boost/asio/handler_invoke_hook.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <boost/is_placeholder.hpp>
#include <functional>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

//------------------------------------------------------------------------------
//
// bind_handler
//
//------------------------------------------------------------------------------

template<class Handler, class... Args>
class bind_wrapper
{
    using args_type = detail::tuple<Args...>;

    Handler h_;
    args_type args_;

    template<class T, class Executor>
    friend struct net::associated_executor;

    template<class T, class Allocator>
    friend struct net::associated_allocator;

    template<class Arg, class Vals>
    static
    typename std::enable_if<
        std::is_placeholder<typename
            std::decay<Arg>::type>::value == 0 &&
        boost::is_placeholder<typename
            std::decay<Arg>::type>::value == 0,
        Arg&&>::type
    extract(Arg&& arg, Vals&& vals)
    {
        boost::ignore_unused(vals);
        return std::forward<Arg>(arg);
    }

    template<class Arg, class Vals>
    static
    typename std::enable_if<
        std::is_placeholder<typename
            std::decay<Arg>::type>::value != 0,
        tuple_element<std::is_placeholder<
            typename std::decay<Arg>::type>::value - 1,
        Vals>>::type&&
    extract(Arg&&, Vals&& vals)
    {
        return detail::get<std::is_placeholder<
            typename std::decay<Arg>::type>::value - 1>(
                std::forward<Vals>(vals));
    }

    template<class Arg, class Vals>
    static
    typename std::enable_if<
        boost::is_placeholder<typename
            std::decay<Arg>::type>::value != 0,
        tuple_element<boost::is_placeholder<
            typename std::decay<Arg>::type>::value - 1,
        Vals>>::type&&
    extract(Arg&&, Vals&& vals)
    {
        return detail::get<boost::is_placeholder<
            typename std::decay<Arg>::type>::value - 1>(
                std::forward<Vals>(vals));
    }

    template<class ArgsTuple, std::size_t... S>
    static
    void
    invoke(
        Handler& h,
        ArgsTuple& args,
        tuple<>&&,
        mp11::index_sequence<S...>)
    {
        boost::ignore_unused(args);
        h(detail::get<S>(std::move(args))...);
    }

    template<
        class ArgsTuple,
        class ValsTuple,
        std::size_t... S>
    static
    void
    invoke(
        Handler& h,
        ArgsTuple& args,
        ValsTuple&& vals,
        mp11::index_sequence<S...>)
    {
        boost::ignore_unused(args);
        boost::ignore_unused(vals);
        h(extract(detail::get<S>(std::move(args)),
            std::forward<ValsTuple>(vals))...);
    }

public:
    using result_type = void; // asio needs this

    bind_wrapper(bind_wrapper&&) = default;
    bind_wrapper(bind_wrapper const&) = default;

    template<
        class DeducedHandler,
        class... Args_>
    explicit
    bind_wrapper(
        DeducedHandler&& handler,
        Args_&&... args)
        : h_(std::forward<DeducedHandler>(handler))
        , args_(std::forward<Args_>(args)...)
    {
    }

    template<class... Values>
    void
    operator()(Values&&... values)
    {
        invoke(h_, args_,
            tuple<Values&&...>(
                std::forward<Values>(values)...),
            mp11::index_sequence_for<Args...>());
    }

    //

    template<class Function>
    friend
    void asio_handler_invoke(
        Function&& f, bind_wrapper* op)
    {
        using net::asio_handler_invoke;
        asio_handler_invoke(f, std::addressof(op->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_wrapper* op)
    {
        using net::asio_handler_is_continuation;
        return asio_handler_is_continuation(
                std::addressof(op->h_));
    }

    friend
    void* asio_handler_allocate(
        std::size_t size, bind_wrapper* op)
    {
        using net::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(op->h_));
    }

    friend
    void asio_handler_deallocate(
        void* p, std::size_t size, bind_wrapper* op)
    {
        using net::asio_handler_deallocate;
        asio_handler_deallocate(
            p, size, std::addressof(op->h_));
    }
};

template<class Handler, class... Args>
class bind_back_wrapper;

template<class Handler, class... Args>
class bind_front_wrapper;

//------------------------------------------------------------------------------
//
// bind_front
//
//------------------------------------------------------------------------------

template<class Handler, class... Args>
class bind_front_wrapper
{
    Handler h_;
    detail::tuple<Args...> args_;

    template<class T, class Executor>
    friend struct net::associated_executor;

    template<class T, class Allocator>
    friend struct net::associated_allocator;

    template<std::size_t... I, class... Ts>
    void
    invoke(
        std::false_type,
        mp11::index_sequence<I...>,
        Ts&&... ts)
    {
        h_( detail::get<I>(std::move(args_))...,
            std::forward<Ts>(ts)...);
    }

    template<std::size_t... I, class... Ts>
    void
    invoke(
        std::true_type,
        mp11::index_sequence<I...>,
        Ts&&... ts)
    {
        std::mem_fn(h_)(
            detail::get<I>(std::move(args_))...,
            std::forward<Ts>(ts)...);
    }

public:
    using result_type = void; // asio needs this

    bind_front_wrapper(bind_front_wrapper&&) = default;
    bind_front_wrapper(bind_front_wrapper const&) = default;

    template<class Handler_, class... Args_>
    bind_front_wrapper(
        Handler_&& handler,
        Args_&&... args)
        : h_(std::forward<Handler_>(handler))
        , args_(std::forward<Args_>(args)...)
    {
    }

    template<class... Ts>
    void operator()(Ts&&... ts)
    {
        invoke(
            std::is_member_function_pointer<Handler>{},
            mp11::index_sequence_for<Args...>{},
            std::forward<Ts>(ts)...);
    }

    //

    template<class Function>
    friend
    void asio_handler_invoke(
        Function&& f, bind_front_wrapper* op)
    {
        using net::asio_handler_invoke;
        asio_handler_invoke(f, std::addressof(op->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_front_wrapper* op)
    {
        using net::asio_handler_is_continuation;
        return asio_handler_is_continuation(
            std::addressof(op->h_));
    }

    friend
    void* asio_handler_allocate(
        std::size_t size, bind_front_wrapper* op)
    {
        using net::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(op->h_));
    }

    friend
    void asio_handler_deallocate(
        void* p, std::size_t size, bind_front_wrapper* op)
    {
        using net::asio_handler_deallocate;
        asio_handler_deallocate(
            p, size, std::addressof(op->h_));
    }
};

} // detail
} // beast
} // boost

//------------------------------------------------------------------------------

namespace boost {
namespace asio {

template<class Handler, class... Args, class Executor>
struct associated_executor<
    beast::detail::bind_wrapper<Handler, Args...>, Executor>
{
    using type = typename
        associated_executor<Handler, Executor>::type;

    static
    type
    get(beast::detail::bind_wrapper<Handler, Args...> const& op,
        Executor const& ex = Executor{}) noexcept
    {
        return associated_executor<
            Handler, Executor>::get(op.h_, ex);
    }
};

template<class Handler, class... Args, class Executor>
struct associated_executor<
    beast::detail::bind_front_wrapper<Handler, Args...>, Executor>
{
    using type = typename
        associated_executor<Handler, Executor>::type;

    static
    type
    get(beast::detail::bind_front_wrapper<Handler, Args...> const& op,
        Executor const& ex = Executor{}) noexcept
    {
        return associated_executor<
            Handler, Executor>::get(op.h_, ex);
    }
};

//

template<class Handler, class... Args, class Allocator>
struct associated_allocator<
    beast::detail::bind_wrapper<Handler, Args...>, Allocator>
{
    using type = typename
        associated_allocator<Handler, Allocator>::type;

    static
    type
    get(beast::detail::bind_wrapper<Handler, Args...> const& op,
        Allocator const& alloc = Allocator{}) noexcept
    {
        return associated_allocator<
            Handler, Allocator>::get(op.h_, alloc);
    }
};

template<class Handler, class... Args, class Allocator>
struct associated_allocator<
    beast::detail::bind_front_wrapper<Handler, Args...>, Allocator>
{
    using type = typename
        associated_allocator<Handler, Allocator>::type;

    static
    type
    get(beast::detail::bind_front_wrapper<Handler, Args...> const& op,
        Allocator const& alloc = Allocator{}) noexcept
    {
        return associated_allocator<
            Handler, Allocator>::get(op.h_, alloc);
    }
};

} // asio
} // boost

//------------------------------------------------------------------------------

namespace std {

// VFALCO Using std::bind on a completion handler will
// cause undefined behavior later, because the executor
// associated with the handler is not propagated to the
// wrapper returned by std::bind; these overloads are
// deleted to prevent mistakes. If this creates a problem
// please contact me.

template<class Handler, class... Args>
void
bind(boost::beast::detail::bind_wrapper<
    Handler, Args...>, ...) = delete;

template<class Handler, class... Args>
void
bind(boost::beast::detail::bind_front_wrapper<
    Handler, Args...>, ...) = delete;

} // std

//------------------------------------------------------------------------------

#endif

/* bind_handler.hpp
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
*/