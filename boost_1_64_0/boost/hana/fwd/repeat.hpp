/*!
@file
Forward declares `boost::hana::repeat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REPEAT_HPP
#define BOOST_HANA_FWD_REPEAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Invokes a nullary function `n` times.
    //! @ingroup group-IntegralConstant
    //!
    //! Given an `IntegralConstant` `n` and a nullary function `f`,
    //! `repeat(n, f)` will call `f` `n` times. In particular, any
    //! decent compiler should expand `repeat(n, f)` to
    //! @code
    //!     f(); f(); ... f(); // n times total
    //! @endcode
    //!
    //!
    //! @param n
    //! An `IntegralConstant` holding a non-negative value representing
    //! the number of times `f` should be repeatedly invoked.
    //!
    //! @param f
    //! A function to repeatedly invoke `n` times. `f` is allowed to have
    //! side effects.
    //!
    //!
    //! Example
    //! -------
    //! @include example/repeat.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto repeat = [](auto const& n, auto&& f) -> void {
        f(); f(); ... f(); // n times total
    };
#else
    template <typename N, typename = void>
    struct repeat_impl : repeat_impl<N, when<true>> { };

    struct repeat_t {
        template <typename N, typename F>
        constexpr void operator()(N const& n, F&& f) const;
    };

    constexpr repeat_t repeat{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REPEAT_HPP

/* repeat.hpp
3Iay2ISOXe1ejMC5wCr0xFCv+NikTHMOY3mLS7z5PIm4XjEpidiBiI3XaXnQQ+evpF0VPJG0ZFEoPfgx5kwXrsa71vTdXA2YtphS8sryi2fguCDvMzEI8BSzdBkGZzOTObbaRrJMzOE/0W21IK7aBZJrVpvAxs5BXd3C/Tx3fqQ/qyVEUrRBLZr2wX5uGqkJcG5Yv3ziLc4DCLyPsLbI8ej+5tOrjH6ln7TfUwLa7uuvUzffYpQ8er9a9eQwZAaPW5b38Q3XaSKn6WGkAbLxdRB36EJYY6guzyUbDdXlw8TLFn24sIMvjM/7RkTlJUxF8mSvbdOapOBWS92H1vQjfDfAlLc1+Vm6zlByZFlf3+j47D+W2ZWyBI56xJvclRnkAVZQ9nDGyDxMoBqQ5BFf33RovMGcyM9POJHIz09pEV77XmL4uWMJYcM+IXY0JmxPSKxyBJtO3/la/o9pLRj3Drf0jOwTllra1le9DOHx9tCMTBnl8fVDQaykNRcSlZi8ZYCMLtOq5N5p2EeGsIFOku6RZ98p+UTiXyTb0gI6+zPgYhgMcI0TN7tqPJntkAiwSjJMs7+jll5lKbFAWVNrNb3ppPSLLa1miOnPyj7Au4XTl9nxyKgpy0zMEB1MLVMhtd+4DZJnN/MJXuE+JkkxchfuIVaP9J1pimSjbsTmWUA03juqa6AWbkFCKiqfDqujy6HymOES90hRIH3SfnpVN7afob3H421C/3FcpZZxD0V88jlzYNhJ+AcBTg5/DG6xu7Rs/r4L36PLreDWG7sT+Sjg2McRS7NAUq4+uG/4FJSpdcBjOMkPGbBDj7uM477NwKi+xagoSvHZoYHtazLqpHGyWUjmiS7Pii53iB+xSnOp/n0Vfy/Bd+xI5D0Mu7abFFDEEC7PGulJGxTqER83Az6omxi1dAgbGULzIaLqPzQpbxZdaHl2ERvk0q5ER0XQiz/+KzXp0WoCvh3pUZwO4z6G8WfESdYIpY1Rpf0EHYyRLIWuFdZzjNMkZo9Xsz8tHdpNUqxeXgJVZNut+SeioFLz/hPbn9P+pLzgE8hKeJmFFZ4aYDdxGx4vY9xSe3Qp+mr4CwbGEarSxln2FaOdV9R8pg9xOGDxAPMoLvAZYx6tDvn6N7uHsQ5HV/gGM4zwGe6zk099Htsc3a9EASe58LMWKFj+Fx0FAWUMJ+nGJTj0uMs4Loq2oNbBZ6niPmK6IhgNPYnGSd5EEi/80keXOkSfJIV+rOTE35/E91B5PPoh8tefSvQj85HZDPf7cmenZ93IWW+mnhT9QMQNvCsnvCuPw7tBzyi8g0sNhmrXYdzHMC7iFhREl+ZzMflcTM7Xop52xj/d39OU44ZoBGstNcjJDdLFxSEpu59b7xLOOtU4/nKj+tIGfLaXnrWDoQePpCzPg3pE5rxUe+0qwK6vrea/9/DfB/nvk/x3G//dTX/nb4QKuP1z/EtFPhP+HcX7x/i3sx2/xr82Ja6vEPTEwspfyC4wyDF9PgeZMqB5YhFvEaMoaA/3O5PkVHN5P1iEBc00e0iK1y3e2tsc1UOhgzMgEQGs0I68baEGfdHr84xrungMqVwe0sOoFCKJqZb+GSB+hI/f3EKBvNfcleLVNOmJWVuA9tPOwYeTmwvR73jPxfWFlSzVy4KMkhTNKtnG816pC1opZkmOkfSk50B1rxC4dtpLnWfw086HuXou8QZ0bEuKp/Qj14JJp70M7Z75nIjMseJaoG26KPqCP+UTJ5xUuAVG5UCLaJlcg3TzN1ZOF9swH3Stadt6krYEd0SVSBOSDXVU7O/c4ByTwoKVxoHsPp6WpQL4PSazQlfsVPSM3O1QUrNMepjq95M/Nus=
*/