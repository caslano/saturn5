/*!
@file
Forward declares `boost::hana::power`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_POWER_HPP
#define BOOST_HANA_FWD_POWER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Elevate a ring element to its `n`th power.
    //! @ingroup group-Ring
    //!
    //! Specifically, `power(x, n)`, is equivalent to multiplying `x` with
    //! itself `n` times using the Ring's multiplication. If the power is
    //! equal to `zero`, the Ring's identity (`one`) is returned.
    //!
    //! @param x
    //! A `Ring` element that is elevated to its `n`th power.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the power to which `x`
    //! is elevated.
    //!
    //!
    //! @note
    //! Only the tag of `x` is used for tag-dispatching.
    //!
    //! Example
    //! -------
    //! @include example/power.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto power = [](auto&& x, auto const& n) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct power_impl : power_impl<R, when<true>> { };

    struct power_t {
        template <typename X, typename N>
        constexpr decltype(auto) operator()(X&& x, N const& n) const;
    };

    constexpr power_t power{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_POWER_HPP

/* power.hpp
5aHLZVN+upKaclcwvinzwTaiHYBAJZTX4E/kzp3/Db/YfBKbJ55iNvmu1veSmE1kIh2zaW0mIcj6ZWoYconrBX7kQvRD8pp96sjLP9jrFLOXqV5+E4ODeQJ1rFkNpVZDlfLs/JHG6RefmGDUv+9J9f/tVTGlYpADQ4sYB++jFlv9Hdzi9jQWontpgxQVDwVUs4opRrj9tC4tVTJAfy7dInHhFuB5UiU+KXQQySpEIKBowzap8+4RnYr0xeZsDPQBG1vcEZ5R2sod4Q9GtiG8x17/XycsN+RPv1/QUv50mW5vigjNAsTZxa2TiMAYtqcOYAgKtL5JMSHUD+VImb6R6EnpUkgowjdICcWoRdmBQdpAlYkHV+XbdqWU9LwlJU4g7L7Fxp56Gx0xL8r1Y5MIXecUYzP2B17gA4qUrFhK+zq+mW0NFSvfadlAZstNBqxVZinn4S+QjBUC4hzjPG8uCw68MJMDl/EmI/67Ti5p5yRjr0dSgsZcM8vPKUzXGUKCNvyqzI3fMsq0cqOyxRLMIu1iQzbPlnMCi2K2xrK1S07u0YfnyZ6p1+UGDJ6PrHC6lhVQujgObZrK6xXWy7jsRuUmKhLQPOorVaRR4rlLHF4YM9Kaxk4oIuuQgMFjDF5foO/1MdizjXELxY2bHbXT5sRK/q6bdwwR9kXoJUl5comy3eogZHSLzj4SyWw4NybKwiddmHXVwv9eYVYb9CsD9MvLt3G+jHSms17Ra7U0eHSEbtEBmyAh8hWxEeWHr+DhUo7wpn2KadTBK27HhkGqwztOOtb5vURCkKN20B/Wd/xyFBE7U0Dt8Ks2Q9AkCUGr6Xdwem2Mkf67radPXG+mjjvFenN0dqvcW5PIXKwI80Reb9yiVsd/a8lxui77gF9N5h6hCthRCU3EH+E2ruwVuJ1i1w1qMXqapcsoXOmOL0Dhq2fHkaB6Xfj95nS12Zi4WOF0f8gbDdE3Zx2fmDXKBKJSHJ4ZZz/qtEZpzuBn6D+PPUVnPjTrzOyHTs8OjWfLmNKE6Ax25uRLmRHdrdvZ7ae9aLR7tfZbWUqFKoUs7fbTXjFS3KBSDDZS1Lb7/gO1Dzf16fiv1yI19DO8FH56QcyuLmTzY1NWD29ITaEt3kAY2aUYy2pHQ6qFYuxkQSSdzNqmSnOzAFAhGhaq1fphWIKh+58LVRHn6/7VES88C5T9XYBAMamyGHyqEOsNEC9J417Lx+gj0d2fWF4m4HsM+FMM+Jmi6XrZkElkGibgCBZTLhPlIgDdAID3rSif4s0SWoXoYBT9OOxsUEFnai3yzH9S3hVqIBcn5fLS0v1qoJmia7fLsR51uaQ6jHRS3djOqhb7lNwq0Gdei0/98tUk3VYztn2mL2P2f68X72O9dPGOJeZY0zdYLYY/kPX6xcwEE8BUiDBP1U0AkxsuJy3+YEzpCyZWHVZcXw/x9pQW9oA3jjYm3P6TJtyYmWdrD7ixCLgQH37jm4nhzBbfn2jx3bYoMfyeLzE8Ynpi+Fst8u9a2EL/u0X+u1qU/44rMTy8Bby1LeAFL0wMz2vxvcjXIn8L+M9pCWEef49o5Pv0x4oZf8jjaX95Q/JKDIv0XrUSw3K/xxgWtm4EliUP3n2d6u6pZVQxfOzOQC6+QHo1sizxGGhs3CIiHnLSNGUn5j03hL2zFum7ZyzHllnzOG2Om8X3w7tjlrshCv0GH1Zn4jj4tFjd9o89ycJZ/y7VOti1/hbpf1cq0uoRhyfowote8TYPPOKOqXqd5RV+WoqzmupLA+nUoN9+Q/qirjeBow8MxOmkzOQpV5ngCNlVpm9lZs2tx1XAs2iGNilZDcudNCwa6t5Z1V2BO3l8O3yTrbM=
*/