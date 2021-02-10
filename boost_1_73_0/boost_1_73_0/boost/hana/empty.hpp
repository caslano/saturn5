/*!
@file
Defines `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EMPTY_HPP
#define BOOST_HANA_EMPTY_HPP

#include <boost/hana/fwd/empty.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr auto empty_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::empty<M>() requires 'M' to be a MonadPlus");
    #endif

        using Empty = BOOST_HANA_DISPATCH_IF(empty_impl<M>,
            hana::MonadPlus<M>::value
        );

        return Empty::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct empty_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct empty_impl<S, when<Sequence<S>::value>> {
        static constexpr auto apply() {
            return hana::make<S>();
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EMPTY_HPP

/* empty.hpp
7Ple5DLlSCJxau0FwYIt8SKfJsLvuEMv1V/bLr3mj1TorXlBXIAbDkwUSUaBpmBf4Us6tsmJHUV8vsCLWlPKb+PtAHKltGs0kftlwoQvYoz6YESbSMnLqfraBpozRC0weY5GDY9LF2xb3vrSNOiPGei7X9MJ3pzF1/1tEF7gH6hWzQ3cgeNKdyDrDxgwblo6XTV8nB+Q/zzNL1hNbSM/oW6ethQOIyhKRmMO+YKD3qSaY9jUPfmabGrfgv5kBK76g/SezBYnjYqN1Yp7UXuSB5fjSELUBkzlX9qsemfzJGm90dWTjS+fkGHnAgp9EzNTqdBWBjxDjiskiMPk7X3J/tx2ZvgyOS2VTU+Fjh5/EG6snK8Yp9KnLFg1QlOdjakImktBQHq6DbLk+kYT/BqTWn8ZAHVO8yuounrJrJ4nUWiw52qmhVWUW0M72UsEqtdqo5DHfKnEMCkLU+Whb3uiti5NUKl8HKrXPxvQiTa77F+OuqfWRXvY/ihFJ9M1WGlcd8ulXohNeRhp6g9DheTQVfMNskWyf9DA4GcoUskf+TASe7vsoUFRB3ImcRA6jC4vLix1BtGgl6FlmrPij0LUqU0m69coCIEGcZVHRCzj2xiW43HbjxeNfFtVLpvn05qNAmlVUaCOLrLl3GV6
*/