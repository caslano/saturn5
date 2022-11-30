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
    boost::asio::asio_handler_invoke_is_deprecated
    asio_handler_invoke(
        Function&& f, bind_wrapper* op)
    {
        using boost::asio::asio_handler_invoke;
        return asio_handler_invoke(f, std::addressof(op->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_wrapper* op)
    {
        using boost::asio::asio_handler_is_continuation;
        return asio_handler_is_continuation(
                std::addressof(op->h_));
    }

    friend
    boost::asio::asio_handler_allocate_is_deprecated
    asio_handler_allocate(
        std::size_t size, bind_wrapper* op)
    {
        using boost::asio::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(op->h_));
    }

    friend
    boost::asio::asio_handler_deallocate_is_deprecated
    asio_handler_deallocate(
        void* p, std::size_t size, bind_wrapper* op)
    {
        using boost::asio::asio_handler_deallocate;
        return asio_handler_deallocate(
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
    boost::asio::asio_handler_invoke_is_deprecated
    asio_handler_invoke(
        Function&& f, bind_front_wrapper* op)
    {
        using boost::asio::asio_handler_invoke;
        return asio_handler_invoke(f, std::addressof(op->h_));
    }

    friend
    bool asio_handler_is_continuation(
        bind_front_wrapper* op)
    {
        using boost::asio::asio_handler_is_continuation;
        return asio_handler_is_continuation(
            std::addressof(op->h_));
    }

    friend
    boost::asio::asio_handler_allocate_is_deprecated
    asio_handler_allocate(
        std::size_t size, bind_front_wrapper* op)
    {
        using boost::asio::asio_handler_allocate;
        return asio_handler_allocate(
            size, std::addressof(op->h_));
    }

    friend
    boost::asio::asio_handler_deallocate_is_deprecated
    asio_handler_deallocate(
        void* p, std::size_t size, bind_front_wrapper* op)
    {
        using boost::asio::asio_handler_deallocate;
        return asio_handler_deallocate(
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