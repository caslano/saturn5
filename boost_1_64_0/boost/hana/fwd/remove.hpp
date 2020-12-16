/*!
@file
Forward declares `boost::hana::remove`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_HPP
#define BOOST_HANA_FWD_REMOVE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove all the elements of a monadic structure that are equal to some
    //! value.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a `value`, `remove` returns a new
    //! monadic structure equal to `xs` without all its elements that are
    //! equal to the given `value`. `remove` is equivalent to `remove_if`
    //! with the `equal.to(value)` predicate, i.e.
    //! @code
    //!     remove(xs, value) == remove_if(xs, equal.to(value))
    //! @endcode
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M` and a value of type `T`, the signature is
    //! \f$
    //!     \mathrm{remove} : M(T) \times T \to M(T)
    //! \f$
    //!
    //! @param xs
    //! A monadic structure to remove some elements from.
    //!
    //! @param value
    //! A value that is compared to every element `x` of the structure.
    //! Elements of the structure that are equal to that value are removed
    //! from the structure. This requires every element to be Comparable
    //! with `value`. Furthermore, in the current version of the library,
    //! comparing `value` with any element of the structure must yield a
    //! compile-time Logical.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove = [](auto&& xs, auto&& value) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct remove_impl : remove_impl<M, when<true>> { };

    struct remove_t {
        template <typename Xs, typename Value>
        constexpr auto operator()(Xs&& xs, Value&& value) const;
    };

    constexpr remove_t remove{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_HPP

/* remove.hpp
MQLbos+4hENUBg1ytbnxEjAoFNlYEaWB4bTOxjLEaocMXmS+71qwLUkgD6R2xp5tko+hKDY4P1dOEc2eZHA5nPzv4Kg56WtftkyaYST1c9IHVNKHTkqaZiTVOOnqgXGVWNMyORpAM1UbqnJttaTRTbGXIdrBN22YindDNr+F5T0OXr4NAIc8Ircl1J3//7X2i16wAgyKuAZIp86vKMIltmJXrjnS+PzqieI2zq+U/N2WD/lG5pQ+dgDoKL4FkeO9FILQm0X8u0kLgtZYukjAvp6J84H7fDq3cbQ9NAb834PZ9koFCjE/Pybm6a/9GJ+1z2/nvYAG1BqYzVioi9hjdfqgR1ydaD3kWvHeKpNk914X1ZGrRCKeXw5RIp4zFM3L+kaHx/eHr0dr/VGDUlGyBQUTd2lHX7SCprV2bj/gsXnjBmSQu+OAgzPTmTr9g5sQbrk9UhIr+NPuCY22omRk4nMPZQ49k54uYZXdNpdV/7d9jMXTktOuCwj6+Ov1y8SufUKs/BsTy7fofS6vj2Tw/e5jxvhd71uA8buqn1LupH53MbKICnnvcG47hkLWZ+0woz6BIuOUUDSOUFeRKjW7WRXs8y1EwY19VcGJiPNQ5kltIMUAwhnqR3qHt7Te3PftqWCr9d0FEY0hycwSnw+JoXiWr1hWM8l3Dao5vm/r+J2aeTJ+E16QFjatY6TgwDjuwFFqdDcM6m3x2iYigXhsEEM8c1SPH//chPnfrSW+U6uobDyNGUeVscvKbAfnNZHW6rrTKprJ8n42NEYPPLnxnXWxIgbXobO6Z7XeWa93PdvO2jDwq3SWzt9z0W1sOGOVLIqrpLwVw7PHznevrW0x4mw7fjsusJYZ+P1N/NdZdOhj+F4y1yARkbq9J+f3yIuWwjQ0dpUhS7vAHKOyPgB7sreaLOyf2IsSc08q8U49ERRX3AMMvxko3jOd6SxL1zxipPzWzqsKsn3+dNWIjOje+lN9t7f47pYqwmhTP6O65b7FqK7opW4GSadhfPmR/sHUXI+YDRYLbUYaknlvgD1AmssDy/zcGDrc3mjEZWO00sNrzeGMmrBlUk1yYmIa4pfmzT3zS3ryPATje9hk9DYTzmGq+jwihAIn0dZUI0kNkrBvwQPQFT5leXSopv6J3wxX9POyUciNIlpS0Xsdqgitm/FpAX+qxieillru96VdcK0ALz6LcLJ4L7dwS3v6wcDvl+LafyO139ESv3OA323nPxCXfxHR/54t82eean7sHRQ/P/bFcSFLAOyenifPj5NKXN7TmB+F/eLnB1/hQfmgSuhtmiPd+p3JHOFfIr6kiPehM+nCHhEwlZ6SUZ8y3w2oz4fySP7U40BH59boyGj3J6G64JUP9IJxEOazRLtvUWoR/lTpuDxB/sXmRvCtqyva/cof9LGrS29JhrM+CbV93vrEUijniEf5j/lotHFz90SE1l4DksVpavgztX8QYk5CNE4lpPCvXvSJNEchb5i/UT958njzntEiKmF4RSdWAlTHr6wH5BUffNQcdeFmA3rWqwmk84gPe9L7fn7fw+Obc0bX33X9pIxW9ZPa1F8qtbcIWxPDNNsnAWZCGHlazG9w+n+z8CmS8nTSVv0yW4HPcdhPZGHJEs8rvcY1Sz161EuIUl5YL2mh7RZK1X6gOjs6iU97PrRi//FDFUmnPS9TzJ0qxiOetXL/6uBnG5qUt83Vo1Yc4k1NQwqFTO00iJP4k/6kSSEWR3hzWPeLVxDSecWxW6W4065I4hCS+WRqxagbfVhjfOgklv+jOTpLblHhv7JSpJ9ojr90OqeelXB+NET12bnQJhuPcxR3dDFZn6sUqfKUEI1LoUsO3aBuu2A=
*/