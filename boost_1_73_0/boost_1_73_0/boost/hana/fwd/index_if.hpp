/*!
@file
Forward declares `boost::hana::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INDEX_IF_HPP
#define BOOST_HANA_FWD_INDEX_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` structure `xs` and a predicate `pred`,
    //! `index_if(xs, pred)` returns a `hana::optional` containing an `IntegralConstant`
    //! of the index of the first element that satisfies the predicate or nothing
    //! if no element satisfies the predicate.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! `Iterable` structure and returning whether `x` is the element being
    //! searched for. In the current version of the library, the predicate
    //! has to return an `IntegralConstant` holding a value that can be
    //! converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/index_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto index_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct index_if_impl : index_if_impl<S, when<true>> { };

    struct index_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr index_if_t index_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INDEX_IF_HPP


/* index_if.hpp
h9XkimzlOFpMYTBx1Gnv7O0CL/CfrFaZJ143Gs9vZ2jjl1bpqCrTSedHQOx0cLhizd2s5t56NfdUTWTNelXbLa5bgSqDwWHj/WCwvLzEEpvqdHbXbKxtVN7bX7NyJ6u882TdlneyynvtNRjT0Qxlli4puGcW3DML7gDZ4Atg7WdyqBmmS5JNsZ4bJY/6GUS2OLsVR9nKoFBuz1ku8eeBF/ZzOsA19p01jvLFvnEWO8kXe+LGc5gv99SNZzr3/fRwMsGxPV9FSa9d5V2hWNtZ7KxQruMqlwZp6BeK7riKsmuZkyhZwUWtygzGWy88iieFBnadOOMgUCjpxPoSxoyo7yruxDyIghTkoUDhXZeUVS79yJ972M3/XnhhcBEUZWjXJXaVn/ZarbMouF74vYkfpe6aLvGrTMqb2nc2NUv8xSSObqdLDMPTzML7U3DQS8TsGyeF57EhFjyYu5W3kvBwfhimRYbgqO/QkEqQJAt/XlrFoSwV9JfHR+gVzD3wgKxutPe556AyaI92gRLMWWnI7ynbzsru7d9TtqPLgpm+p+yOLgtWWZetGr7SVk30z05OdG8dz8Tdxt0BOm8YEpxgCPXZpziSfTmI1cDYYSwgehFFbsF4EXrzuoCAZxKDaxnFCBC8XnGB4dJtlHpj
*/