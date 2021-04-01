/*!
@file
Defines `boost::hana::always`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ALWAYS_HPP
#define BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return a constant function returning `x` regardless of the
    //! argument(s) it is invoked with.
    //!
    //! Specifically, `always(x)` is a function such that
    //! @code
    //!     always(x)(y...) == x
    //! @endcode
    //! for any `y...`. A copy of `x` is made and it is owned by the
    //! `always(x)` function. When `always(x)` is called, it will return
    //! a reference to the `x` it owns. This reference is valid as long
    //! as `always(x)` is in scope.
    //!
    //!
    //! ### Example
    //! @include example/functional/always.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto always = [](auto&& x) {
        return [perfect-capture](auto const& ...y) -> decltype(auto) {
            return forwarded(x);
        };
    };
#else
    template <typename T>
    struct _always {
        T val_;

        template <typename ...Args>
        constexpr T const& operator()(Args const& ...) const&
        { return val_; }

        template <typename ...Args>
        constexpr T& operator()(Args const& ...) &
        { return val_; }

        template <typename ...Args>
        constexpr T operator()(Args const& ...) &&
        { return std::move(val_); }
    };

    constexpr detail::create<_always> always{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

/* always.hpp
9mXfT6Yz3ndqBI7kEaAqPgpaX3AFc6bLRy+z1AatQDDXfKTercjt+Qa/ylpzntkgOnFwn70mFyq71JOhdqTveuHVBhTnG9f6DtoIUKeqkwIEruVl2o9Nwm1zSNFXKvIiwuAPrKKNUslSaKLheNHEoR3JvoR60m4+D7ycFEuUkWQBevSh0Vc628Qp7EOH0561YnXii4GsOldHqRDaPuCRIU8z+YeDT2NfdfoV2IBESVfYGzDNqnwLtxrHO+qvM5TntW5+LvdJzXqabbxtLXaevc9wIqONs4wew7HEJpZGdCDSd4Jg58MvhhFUhurJflbLkVSNp0EgVGx3aMycSf/cJQQsQkycOu/EwWVmiUzfRGZDEl1wkC2KRr8Ho1B3qJyCBsHnGU+6lTGk0aH2V4QaoNUQilnhMcee/SVnblaOpQm2j4rZWwSSWALY6Y3IFlQLbyfqfz88xR27l0cKo3ZCt4qU4qDFmZHYj7zqUvIl4qRIfW/XlwfA/SOYkpO2BHa0BG4JoxmfuaDSukDfrrfE90FnMD2uiemAj8HmfIFouvqtLiRry2Vi0OWIIg==
*/