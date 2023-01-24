/*!
@file
Forward declares `boost::hana::one`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ONE_HPP
#define BOOST_HANA_FWD_ONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the `Ring` multiplication.
    //! @ingroup group-Ring
    //!
    //! @tparam R
    //! The tag (must be a model of `Ring`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/one.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename R>
    constexpr auto one = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct one_impl : one_impl<R, when<true>> { };

    template <typename R>
    struct one_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename R>
    constexpr one_t<R> one{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ONE_HPP

/* one.hpp
TS0Yb5RsZzO3KfzGkgc3xtstinUvwnWo1utjBkykn/hYTCzqs8W6Osluw81HTFVPVMl5UX9dybCf6nkMmdIk6JLUiFmTRcs2plqz3/MaDubJkPuscErfS5RQ+E1FCqFYdFBwHujXxRLVUHCH7j03YQPDbEWtez1neQ159AjVOcoeYj9k1KzitNztD49CJFIyMxWWhF4dV4TIvMZ4ZyvBP06kHuuq0SF6HLzwN60Imp62E0slJd10p48XPLHyUgp/bM4tBA/1pcp+/J07ZNvwns8qTDGy6ie16K1guXfPwKBJ1FsaCe7IeLocuVTbV0CuKM8wg4pP+eezkRSCeo+7sy4lQjdunJmyozrIj7DcdZJpOwyQS/toosCAS7z3LI/RImhe4z3HN/dy1esJ+pLACW4sbTYzZq2/x/hx9OdK9s965afjiz4wHoMKyXU0DU2E2GLE58WddaQqiUp548ZIfegLDxZvl18zMKT/0vg4qP+RyW65vSQEuaX2j5Y5i7wcQQ1GPXiRKnkVL6kgAfNa5egtbvJ+afzRTD+sWBVfulR1SgxQWlHzjX2RJcN7clAqLdnc+vWqfRp04807YgO04bV+EjGgtWg9cErWDeO1hrHjVjbiwPj++hYz4I6aTbtosClbDn/4cwNZbWNfcpke+8HSzoBCz23SBxb1Hnkg52cGt6Wd7dv7QiqCb4gQgBpDEaMaMBXVIQPBnXkl
*/