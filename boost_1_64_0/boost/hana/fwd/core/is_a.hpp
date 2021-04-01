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
tk5V0qcyGLEBuv21cK5iB6e+JExpPB65530fEXZgJ0MR6b+BB+2WFUjvI0ntF4C4KweKLIv3FLmMscFHj/pUrZ55a+dT4BCAoOFb3ti4/wrLZYimhnLakIwvFNf1TaujwCU5timy5e6gClKHa5G0oADaY5vN0Fm8O5zrKoIp8mfnlFeZBQ++yqghmV5jCLHwuK13UCKnXxKfU+Yh+ses6BOq/20hCOYjpUOF3J9XLuAM88g4A6CU9sHclg86L2ICq4F5HctLby6ifT8r8lfCa9hWdryWEzKjCsMIsdff4+5zfsLybYE/gy4rDW8pCZaGSj4HpEHBAhUMSm1gWQOjMOKZSwrYogqJ4V/3qERhLkWapWh1X3PFVspvMNYA6ii1ZmZJ452ynUp5j3bFIjcen6gfYst+do15oaC8apjgBn2/5Vd4Lx125Wek1NaBshKNOcc4w0IbZ9kRvl/H3cJVkEBzCihatmVz7Lw8H0kGChPJV1Y+Cm501S/kOkD0X3fr7iwWqHFd355ygic/Rwh17cGQBjgwPOWj4YWZE1YlB+W8QGq70fLSXLNA0w==
*/