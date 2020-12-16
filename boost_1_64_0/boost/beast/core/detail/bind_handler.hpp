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
KT/i2Ai61K/8s86i/j190c44JaYC1B40G7TLvLPePz+zsRzAkbJ71Kose0ELyuDGtw49YTvotwh/JfbcpvM87vFqEP/Wehy8R+xZkE1r/p2VsbPs/VoDBHEeHlzm3APG/ZqSP596mNjRrx5Y76mz/ModcNk1+BjiIgnfVtfJ181sH+OZL0cnJaYP85XE9pHfjHyxlcjfyGyUrwF0mbQR+SMZaclT0PxXSDodmt2OPN9RCfMdToYwyrOW+Q60oAoWkY1q5t/N/UwjkgytPGPt4GlQJkwnaFl8x1sZnZWY3qyD7ixLXYB0OAxifYO3meMgT5n2Ma3+TKs3y9QQNC3fsXRmZ/CDLtdjoTBvXs5iLOT5LtLjA9dj4mzm5/RKg2bV5ySmtT0+cH2mNi8tCqJ5det593lPFyXmZvZ3y83fyEemf5p6VaCgwqWCrucwXJy+w/0KsVfiezbcZwsR99ou7vUAe1zk/MheqKOY9lw38+nXgvaP10mcrfVe+2Kx56lOcBumwpu1VsD+0LK+4vv9bkxQYsaC2hOfQF6OBZYLV0sQL/NsuPNcaT0r21L2I6VQVp64Out126Hib/itIZ7xjMR46zwKaaM8TNvv29p4TtMydUXc2SXBy5R3bUUBCmY5r+C7JlnqUybGZSnTHSxTP3MtCDLNRx6GSB+ssHhkbx8ZjnUkm3UFVQUq/1nVqT1cy8B3LYDl93wcbT39GMvvs+jfzL7Y00eWdVViOpAhlt/u/kBx80uNMef+yFMWwuaYMmnlLmdzvt/jwKO2YHtsg+01DrbnN9ge8OB7sV2yh3rVQ3e/deTF1NQVL15eXXrrg40//P3339ee9Dayd3vpxmsGzX268veL7/7tXf0/mNEh2N7ws99bHWwP9TaJ3xW/5usVk++acUO/6fdGp7U8/P3tbR8tcs74JrnP1BNLb9o+bkanxohblgffY745yXT/2Y67nn3j5QUnl8Tsiu3f4htsWv2b1GPdx1d2vzP/4VY3RO4z4k489OTZ7+U/2z3sQfaSy57x7fwI0rhnvK/Zd/P3jxSQv+83v2v+Nvdqj+LvFxXGBfz9ujmu4e9DCt8gf3+uMI/gbwdoLH+3BY3n7y6g0fzdB5TD36NAQ/j7EtBXsi+ZOjzqCE2/KGAZy1Jsc+9DrQB2AS4CpgCvA6YClwEHA+8BynvawCnA9cDpwA3AGcCNwGLg3cAF5DfTVwb1Y9SbIX1ZNzvO9GsM992Aq4DxwNXAPsBa4BDgzcDhtF8PvA24xswHsNbMB/A24B3AO8z8AOvMfABfAG4G/g64FfgGcDv3ye8AfgDcCfwU+CSwEbgbeBL4AfDvwAagDXn+CBgBPAyMAh4BtgN+AowDfgrsAjwKTAT+Edgf+Dn3zSd6dEPUW0EOMo6NBZrmL+BrDzwBTAJ+Y4YH/gN4OVDZ3PvcZ1LOdqBZ3gjgs8Ao4BfAaGBnA/ECLwZ2Ai4AJgB/CkwE7gX2AL4K7AV8F9gb+BWwDzAM31IyMAHYF9gTOBA4GTgEuAw4HPgIcBTwIHAs0LDjewP2A04FDgFOB6YDrwbmAa8BzgKa5VgILAAuof0r2c9PfRBwFttrGDCN7SXfcO9PLzD4VgTwKtrzaf9K9k1T1yJzSX5PwBTGs4F3Ut7PfdibgR1lXzfrC5TJ8N0Z3gDGMvxPlDcd52nS2cp0HmM6O5nOryzpbDpNOg8py7kL8p0b4NzF75nOIWAc8ENgF+AH3K/eAOxHd6ZL3QD6qgDpHiRfCSiffKvI1wqYS77RTHcC30S4lPvYL+P5j0XAcTzfMJFvgOTwnEQFz0csJx/zxXV09BMB8nWRRe6Z5BsQQO7PMl8vAjsDXwImA18=
*/