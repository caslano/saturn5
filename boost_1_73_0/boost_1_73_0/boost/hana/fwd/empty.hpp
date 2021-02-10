/*!
@file
Forward declares `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EMPTY_HPP
#define BOOST_HANA_FWD_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the monadic combination `concat`.
    //! @ingroup group-MonadPlus
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{empty}_M : \emptyset \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the monadic structure to return. This must be
    //! a model of the MonadPlus concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto empty = []() {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct empty_impl : empty_impl<M, when<true>> { };

    template <typename M>
    struct empty_t {
        constexpr auto operator()() const;
    };

    template <typename M>
    constexpr empty_t<M> empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EMPTY_HPP

/* empty.hpp
sKHUIO6THrBiXRkqPHaWllazM2+xEg079y+plgMa2+Cw6IPibmuDP5f2JQE9ueh30KloPiT7a3H5mcRDGQv3M+2JEh+TKke50pyc8h5XSmf5Wzt3q95a6Vt+prQ4Zm8LmV4rfatAPDyDK2qq6+apXNP+0WGZdO9859UlHuPAUhYu33Lc+TLQWJHp0Imp+Le9/b/+ziNupw9hvs8/tZ4rPz2rTgNK0zmfNK1FKgsTPliPs3ATPj/ghYuFC/oEM/+YdsEIFYv/UyWdDeQHdBRSHw+I8Agf+DnLSNI5KA90vbyCiGe230CDuYu7aurQWXq2rH/6Zjw+39fKIFMW2EMnfl+pDX9smuak9zOVgSUwy7tahtmftGVMH9UbQg2Fxnw8SMH0jsVWI1MiluJHeoH7h8e6cIYqf1UFJ9XmGY9vihoOxLPDVGtJDFqOSb6bpqI2o2BCsUleShrZGlZq89Ra1ovoVvXJNuHOSZmOe/0LYP++8643etced95U1ayVSVsuP2mxbvxt0UV2SM5gxlxJP5Lx3sJzzHwEMWorqnLgIHLI5wdAmOjsDXgHWb6mpHC3qMG+5XiAOUjJyY0CJ9xrzNceMmhofz5149bX01lefxfWrOsMu/3u6WDca6MleZLn3hEZtqHUZaVW9l/r
*/