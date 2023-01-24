/*!
@file
Defines `boost::hana::make`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_MAKE_HPP
#define BOOST_HANA_CORE_MAKE_HPP

#include <boost/hana/fwd/core/make.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Datatype, typename>
    struct make_impl : make_impl<Datatype, when<true>> { };
    //! @endcond

    template <typename Datatype, bool condition>
    struct make_impl<Datatype, when<condition>> : default_ {
        template <typename ...X>
        static constexpr auto make_helper(int, X&& ...x)
            -> decltype(Datatype(static_cast<X&&>(x)...))
        { return Datatype(static_cast<X&&>(x)...); }

        template <typename ...X>
        static constexpr auto make_helper(long, X&& ...) {
            static_assert((sizeof...(X), false),
            "there exists no constructor for the given data type");
        }

        template <typename ...X>
        static constexpr decltype(auto) apply(X&& ...x)
        { return make_helper(int{}, static_cast<X&&>(x)...); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_MAKE_HPP

/* make.hpp
TfJkQ1kM87DiId+qQa2qQwnZsDU5GDe/0ZeQu1WoCUhfkx+JLz04LPs234hsh/7+hHpoaVVmhu+beeMlYelWY+7COnzdt0rr+a0wq+Z2ZN+wSRT3NIg7qtKdBpvcIeJRyWtbhkGh4o4aIR9eNjAzmnd0lQMylcshzLbzv89W17Icsn2C2Vp5nha2fGge5Nninngn+90+POjotqA1T9wBjzftRQWkRDpBH5V96OcS2ixhEEOAtHVUDJ4MdfF5W+PrRm1t2RqfB20/FRmIyGz8BQPF3uGF6harerE8zaDm2dCwm+9k1/yBZA5cIhDUPCtoBz4ReHxWnm19AhAzzAfG2QH5GphxgAMalYu5/K9317+BLTOjk2X+99AR8MM4zNjoJPJ7isMZsBFmr8wym1j7No6AVScjU+TjJ7hshdHLlLJ5SllKFx5QF86zZZYliw9h2JPwxhRxR94s9YCTfYYqfh6oUxbf63IoYdNb4bTa1Z8LGPgQwzIGHfKy9LBSllZXlqGUpSplM+rKsoPz4OsxXIqfBjen0B/jIqUsPTgJnqZghB7MvRZvEuBmSQKt5td4kGfk2aB78mbh6j7yEKgUpChK5Cny8M2DOKTlPXg1irVZlCl5VVnjgS7BdgT+uuHva/gbhD8TVNQKf0lY4Rg8dV3wHXg6SLrbiQiebu/heHo3iqcH0TybZzMSoh7VELUzbzYi6tRABFG7EFH7
*/