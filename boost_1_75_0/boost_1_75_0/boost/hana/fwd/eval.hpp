/*!
@file
Forward declares `boost::hana::eval`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EVAL_HPP
#define BOOST_HANA_FWD_EVAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Evaluate a lazy value and return it.
    //! @relates hana::lazy
    //!
    //! Given a lazy expression `expr`, `eval` evaluates `expr` and returns
    //! the result as a normal value. However, for convenience, `eval` can
    //! also be used with nullary and unary function objects. Specifically,
    //! if `expr` is not a `hana::lazy`, it is called with no arguments at
    //! all and the result of that call (`expr()`) is returned. Otherwise,
    //! if `expr()` is ill-formed, then `expr(hana::id)` is returned instead.
    //! If that expression is ill-formed, then a compile-time error is
    //! triggered.
    //!
    //! The reason for allowing nullary callables in `eval` is because this
    //! allows using nullary lambdas as lazy branches to `eval_if`, which
    //! is convenient. The reason for allowing unary callables and calling
    //! them with `hana::id` is because this allows deferring the
    //! compile-time evaluation of selected expressions inside the callable.
    //! How this can be achieved is documented by `hana::eval_if`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/eval.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto eval = [](auto&& see_documentation) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct eval_impl : eval_impl<T, when<true>> { };

    struct eval_t {
        template <typename Expr>
        constexpr decltype(auto) operator()(Expr&& expr) const;
    };

    constexpr eval_t eval{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EVAL_HPP

/* eval.hpp
usZ7LmH6w1a2RRNzqesO7DI7rmzDL9pjF3geEtAUl/GiPW7v6sd9K1OCCk+5BlBRkLnc/fnKGCl6ha9M8yE+N5e7fqx9nwluZam3ms4auN9HUvTspf/F+5NrprBfGlMEW3A6RP7B5EgZKWD//CWCYMvHyuqWH7VGIuqPTCuoXoIoYsnq1MgQ90Pe2fB2a8T+LvX/SN9gbzfys6fDju470TvyRBJT+dCajuzWUFjZ6iRcGB30tmXiy9R/qTVySZAruOaC3edbelIQ6pagScjSy5Tja2lNOwcd5UYxybu89C8Sa0KkPP9kvnzZWNjO0bM1r6F//mWJO+hodYGtPJ74XjYQHVd33PKloNh5J3mjVAedDCNWhjavrDmD64eIvpCadcB1tOZH76PBrk4xtaqj+47+8vKP1S+/6g45UXWi6mjNQ2U/lDxUptlX212zrz9oEzrERirc5awvoncfceyp7E/ELv2J6m2UdbfpgAbuD5ftcxcXnHZ5DozBfp1kNDky5OUTj4TUjBvOtjCTTqSEnJAUlLvoNlEa0LHncd5hPo7YP2CInH3e/gQ9tAmj4y6WEBUuGwvJV2ZGyov/aHspNvKOfLpX3P37IVueFxSFX7kgnyL6ja/3PDofPVP4lbwwiNit9l61EbajNd5zyBwtqYGTFI5WF+6TL3uFjXOi6vshirWCgpNDr48cLT7aUHX0QwHCedV9x/GOWyHM
*/