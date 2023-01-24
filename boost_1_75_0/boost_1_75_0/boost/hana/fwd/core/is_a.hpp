/*!
@file
Forward declares `boost::hana::is_a` and `boost::hana::is_an`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_IS_A_HPP
#define BOOST_HANA_FWD_CORE_IS_A_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Returns whether the tag of an object matches a given tag.
    //!
    //! Given a tag `Tag` and a C++ type `T`, `is_a<Tag, T>` is a compile-time
    //! Logical representing whether the tag of `T` is exactly `Tag`. In other
    //! words, it is equivalent to
    //! @code
    //!     std::is_same<Tag, tag_of<T>::type>
    //! @endcode
    //!
    //! For convenience, an alternate syntax is provided for using `is_a`.
    //! Specifically, `is_a<Tag>` is a function object returning whether the
    //! argument it is passed has the given tag. In other words,
    //! @code
    //!     is_a<Tag>(x) == is_a<Tag, decltype(x)>
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/is_a.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag, typename optional_T>
    constexpr auto is_a = see-documentation;
#else
    template <typename Tag, typename ...T>
    struct is_a_t;

    template <typename Tag, typename ...T>
    constexpr is_a_t<Tag, T...> is_a{};
#endif

    //! @ingroup group-core
    //! Equivalent to `is_a`; provided for consistency with the rules of the
    //! English language.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Tag, typename ...T>
    constexpr auto is_an = is_a<Tag, T...>;
#else
    template <typename Tag, typename ...T>
    constexpr is_a_t<Tag, T...> is_an{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_IS_A_HPP

/* is_a.hpp
agTMUazkvobgjzL7sEQRq7SNhmY2IoTZtElpR8u58pqm0RHx4eITKRm2IS7DLAa79e406y+9C8I/suDzSUkYUuimx/p9WbQPRW3Ito2p+jhSoqltD/j5W5DBHYcz42Aa1YhuNZY7RkWjwhgjL1aE4rhYecuLgY3P4npkL/aS1D3/Mt5HypqjupL9SnXjD1t1yhZWr/qi+2JCJUB2oNgy3aRfdvEl9rDTOIFryjIbpKskxgLxr1m2USuH6dgw61TbJrTJ0VmwjuLeyrGXfNjAVdwN/JzqeguzIGQh/3VC2yTDRqyLwEFcO5JuTqq98UknpvyHWXpdqY4MnNzWgt8DKDvO36RZ966AkG4u1S90upWbM80veTpzokfvBDNoZFAqvkWOTa7+fVqsw+hs2LFdHcZ5ltcFoUhcqfdhqcXD6fz6j9Mfn2OefT40GV4hS3b+mRtPnzWYKZuS6a0i1I2Wi3eWKKEdQCy+q7VLCTg8HO7eATOlcELN59RnXtUyFjdXqN+sebayiq+wnsT21b7uMItInGHv02j64FEzeFHf0mn6fPSS2pFtQfN63CM6g31rUH/EFkD3UnNTr3qNCYgoCTGoeo3nkdqxE6Fd7h2dkhqB8eH8tRII6VaLfbtzn5nCMoFL7NmOtw1RS+Hu8YSVXbE/XdWtkcf6BrYVuFoOkDcKzeCZmqVJ6+W6JzmJQqWPG+X3wUFR9cfjZ38z
*/