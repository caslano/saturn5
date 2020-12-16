//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_SAVED_HANDLER_HPP
#define BOOST_BEAST_CORE_SAVED_HANDLER_HPP

#include <boost/beast/core/detail/config.hpp>

namespace boost {
namespace beast {

/** An invocable, nullary function object which holds a completion handler.

    This container can hold a type-erased instance of any completion
    handler, or it can be empty. When the container holds a value,
    the implementation maintains an instance of `net::executor_work_guard`
    for the handler's associated executor. Memory is dynamically allocated
    to store the completion handler, and the allocator may optionally
    be specified. Otherwise, the implementation uses the handler's
    associated allocator.
*/
class saved_handler
{
    class base;

    template<class, class>
    class impl;

    base* p_ = nullptr;

public:
    /// Default Constructor
    saved_handler() = default;

    /// Copy Constructor (deleted)
    saved_handler(saved_handler const&) = delete;

    /// Copy Assignment (deleted)
    saved_handler& operator=(saved_handler const&) = delete;

    /// Destructor
    BOOST_BEAST_DECL
    ~saved_handler();

    /// Move Constructor
    BOOST_BEAST_DECL
    saved_handler(saved_handler&& other) noexcept;

    /// Move Assignment
    BOOST_BEAST_DECL
    saved_handler&
    operator=(saved_handler&& other) noexcept;

    /// Returns `true` if `*this` contains a completion handler.
    bool
    has_value() const noexcept
    {
        return p_ != nullptr;
    }

    /** Store a completion handler in the container.

        Requires `this->has_value() == false`.

        @param handler The completion handler to store.
        The implementation takes ownership of the handler by performing a decay-copy.

        @param alloc The allocator to use.
    */
    template<class Handler, class Allocator>
    void
    emplace(Handler&& handler, Allocator const& alloc);

    /** Store a completion handler in the container.

        Requires `this->has_value() == false`. The
        implementation will use the handler's associated
        allocator to obtian storage.

        @param handler The completion handler to store.
        The implementation takes ownership of the handler by performing a decay-copy.
    */
    template<class Handler>
    void
    emplace(Handler&& handler);

    /** Discard the saved handler, if one exists.

        If `*this` contains an object, it is destroyed.

        @returns `true` if an object was destroyed.
    */
    BOOST_BEAST_DECL
    bool
    reset() noexcept;

    /** Unconditionally invoke the stored completion handler.

        Requires `this->has_value() == true`. Any dynamic memory
        used is deallocated before the stored completion handler
        is invoked. The executor work guard is also reset before
        the invocation.
    */
    BOOST_BEAST_DECL
    void
    invoke();

    /** Conditionally invoke the stored completion handler.

        Invokes the stored completion handler if
        `this->has_value() == true`, otherwise does nothing. Any
        dynamic memory used is deallocated before the stored completion
        handler is invoked. The executor work guard is also reset before
        the invocation.

        @return `true` if the invocation took place.
    */
    BOOST_BEAST_DECL
    bool
    maybe_invoke();
};

} // beast
} // boost

#include <boost/beast/core/impl/saved_handler.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/saved_handler.ipp>
#endif

#endif

/* saved_handler.hpp
Zzp0c4LsM5iLMs+csJCN2XnZRba6OuZBSeQzGYNTb8E4v4tx5MEslS+Ecsbb1pDletn8US9gkl1MS72ZVoXeLNjjm9bFvTBgsXyrUUI3VvRIZcOGOrrZxEV72LqZ2zeY5xNspf/gLQh34plRr1m0b2FGUfZM2/ZlnodMvzF5M/LSMsjzrvhNpv6Up3SZSSr+blN8roofbcrvKSemIe46iVtwGfSRUmcPfaTUU+4lqntSN7e2HMzD4YayLQcizDbG6VZtWZSaWYlemXn6mMbUzgxsS8Y3VG0T8Fv+Tlifp8n08aa2G6VkbIjkDdLCaQMeLnRbLfQS9btOOSP19mhP1M3DL9jIJizUCdJ2Bc2gS/utyy9YfI/k1PT0yv2CMT1/b8aAHit0qJcMZzsyfR3VjpOE7uktt/l7fJvE9/vR/sKMdghT7YC6eLTDBbZDfRYWTv9o5aZ2qI5/NEmPUqzG3s9KXN0f/Q5Xwg42Uc6YeKfbhcmj27dveMenjy59bM3L5T8tO9hmmlwyB0oEFiKU0ya2NdqKNoxcowGv6V42jGKLKf0AeC0wAdgJeCOwO3AIcBgwEXgLcBj9hY2gjeNIYDbwJtqQJtGv+zjakN4B/C1wAs9DSAGG0e9ZQ2AGsCNwKrAf/aANAGYBbwBm0xYzmmsQBpzR+Y5GG9DW9TTSxdJ/fzfge7StfR+YSH/9NwE/pg3sJ7SB/TNwIf33L6b//lL6799A//2PAL8AbgN+yfMrKoC7gF8BTwK/A37A8/0RJ+f3nwf687yCQGA7YBCwCzAE2AMYChwErANMAtYF5gLrAecAw4ELgfWBK4ENgWXACOAuYBPgPmBT4H4g2kP5gUtx6Ycs/MDNQLoOwAJgF2AhcCCwCHg7cA5wEnAucDrwbuAM4D3AB4HzgauBJcAtwAXA7cCFwKeAi4DPABcD9wLvAx4ELgWeBC4DfgF8AHgB+HPgD8AVwADUsRQ4DrgKOAm4GjgDuAZYAlwL3Ax8CLgDuAH4FHAj8BBwM/AkcAvwj8BHgH8B/gL4GXAr2ylF6Xug72I7Ge0ylu20iHx1H/vDEvoDXEp+WsHzJEqBU2gLPBW4iny0mjbma4CbaSP8GHAdbbnXk482AvfQNvgl2ga/TtvgD4Fl9K/3KPvPTmB9YDltrZ8GXgfcBRxFm/SJtEnPBr5A2+KDwKXAQ6ZzVDYAXwE+Qj97T9LP3gv0s3eU8WPpX2888Dgwh/715gBfAy4HngSuAr4BXAN886KtOufRyGNhq96F/NiN/NiDfNiXfHgdMAfYH5gPHAAsA14P/AUwAbgTOBC4B3gD8EXgYJ6LMwT4a+BQ4OvAYcAPgcOBXwJHAL8DjiL/3QRsDbwZeC0wCdgBOBoYC7yF/XgMsCdwLHAB8HbgMuA4YCnwDuAGIHhY2ne8UT/gBOAR4ETga4w32jMFWABMBS4CpgFXAdOB24CZwCeA2cAngdPIx4lqrI82JB2I0M/Dn2EjYGNgY/oNbEJ5HwnsSv+GPL+I418Zq7ufX8Q9BPW4h6A+sB39ZV5Lm/g+wDhgNDAe2AGYAOwIHA6MYb+J5XlCnYAp3GOQxfNp5gDjed5Kb+AWKZf8pHGMCRzK+gUb/MT6PaY76/crYGvgE8D2wJ3ks3Ly2ZPAAcCngAN5n+VzrIbfRovyWyKdtAOwDrADMAzYFtgE2A7YBhgN7Mj4gcCOLD/JeBbLr2/h77GA36sQGMBzhIz4OcBQ4DxgXZ77Eg6cz3Yy+Xussb3/sYH+Vdr8N04OcrP7jwU9GCEdYQnCboTTCP4p8AGJMBIhB2FRim9PgO/yXb7Ld/ku3+W7fJfv8l2+q3rX1bH/n5J2uez/Hzf5/zs=
*/