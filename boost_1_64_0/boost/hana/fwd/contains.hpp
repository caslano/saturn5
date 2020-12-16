/*!
@file
Forward declares `boost::hana::contains` and `boost::hana::in`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONTAINS_HPP
#define BOOST_HANA_FWD_CONTAINS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/infix.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a `key`, `contains` returns
    //! whether any of the keys of the structure is equal to the given `key`.
    //! If the structure is not finite, an equal key has to appear at a finite
    //! position in the structure for this method to finish. For convenience,
    //! `contains` can also be applied in infix notation.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/contains.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto contains = [](auto&& xs, auto&& key) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct contains_impl : contains_impl<S, when<true>> { };

    struct contains_t {
        template <typename Xs, typename Key>
        constexpr auto operator()(Xs&& xs, Key&& key) const;
    };

    constexpr auto contains = hana::infix(contains_t{});
#endif

    //! Return whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Specifically, this is equivalent to `contains`, except `in` takes its
    //! arguments in reverse order. Like `contains`, `in` can also be applied
    //! in infix notation for increased expressiveness. This function is not a
    //! method that can be overriden; it is just a convenience function
    //! provided with the concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/in.cpp
    constexpr auto in = hana::infix(hana::flip(hana::contains));
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONTAINS_HPP

/* contains.hpp
fbt1L5Po+43+XpI/RI0tFLbU8UWH12kn3rh48sinAgE5xvK/GnCsmNcbNpBUd1ePD4Y4a3fs1GUNmW3g0MhpdPudqv/E+p17HXMgdVwBbdEjlN7VxrwFQI+s4JiaPX6Hnvp1EaZBmCW2qMqzccfyAF4uYu2rfoqhnKmikBJ6lhDo2lcFsilvruXZmoeE6A1VGk/qxlua9J4HxMHSyI3b/i0fYU+2nWzyiLu3OKnTyGRdKMLYEz5M7IbjDj3V4WTgNKka7eAZJ5xIviom3el/1JRwM8mehPZc7Fy9oQ7SaS+eMuO33cqKX2rMUh3x2hiI7c1iI2AlqeZviD/3WEiHJ+Nx7WaUIm8oq88YOSBwIsaqT/0048hLY35M93TyQ8rmX28hk0fZjP29qKnmVIRCvEyPGXgUh6zKlcUDyHL6bqODaMBvmDeAPJ62mfYa0l17lGteoEALM+JkjOgzepTBZOZEmn6lfz/qHlZAwI7o93r37KC9lYFeqRNwArE30imAhcS7buLuJlnoYiyStDyrUAub0MATYw38odrADZ0b6K9ssGEura7vPdKh+nWdYhzppuRN7Jd1V2LySdITOlSvxQ3aQlhARQMWKS/EKsmRt3VERUcoq0hz/lC6AR1Yw43PAzmdJcZWTXIFwkm0QP5DypTf20QnONAJLulZvbptcdWZH9cLPYsLzYwVClTLxlxw+tDdLzSBAofGG5Sb1hBPdyazsg65RUurlhFpZhxCeCJgrzRTNToEr8ZBsPyxTtVKv9PT7aLhmhKNal2wkoq5QY9+Ja6YkZ2LWZsfIgTtJn76FzZMQ/p5q+tTdb+6F6h+dTd04VfXXyJt0+F4KQ6OPz6KIVisj98vbtHHbzsv3tlHDNozCKdBK1cOpGo25rV0Slt6Ta/hxbga3I/ydDiinPkbyA5Xz7IzLstAykKdgxzdcyv0P/tpcDhI/9OQsJ47xAUcmfjlQ6JZDuL8nsBfIo8WqGDzpXRTAg1+TfT83Q/rxz5m0jLv4GX+zHW02FBNzWUJVNlzBFX+WNap8rvEHnpItar5v7PXEGLIFzLNIp7z2d8B7eqNI01A4UagcLFxZIkgQUSxGhNReJQ0yKSjcBzMH0HRH12ko/Azv1NR2KPYGhmFW6sotQg6tJ74DIfKZ4CRWipUgunQQ2TDP9YUWq1B0ftXx9LlIl2ami4DsvM95JgNTtkiOdIAHaKX4yCa+ZAOQmi9isroTRoP9cL/t9aKHv1eeNzj+TQU0ajZ18TwZ5y4lwx734ugTJhRVk5GZK49CJOeTwdz4yE5rZcC17ej4Qif/YDBIlCAmB/7+I8gAM54wGDlG06c67VLUj6spUi4Fru/yF7zHCY+YcFTRjEUviy3ciNLOUgJ0U/3VViIznqsgcKLmu0OJPTas0ftCKGk7OGP88+78+x7dtfNcF5kz37Znt08z/5lkqMepNE+50U8DzzAiXbOs7+7AwnfoDIKpbzrKEHkFYS0I+FBe3aLlg+l4HEUZUOezUjRgZTbPfbel0Aq3ZvuZXkeuwNpInWF8kc8lksL+PleCl7Nj54lTCMvAgqiZ7xe9hgo3cpxy3hvMc7rlZ7j9/l497KNn6RwwCwEEIEFg1gjhDxFLIEfhyjWng4j9gOmA5SNkFNq53ynMSzWFfR8IhUqZfNzL34u4mcTwXgFPx58insVcNzI7x/gnUSKxImWeZRXPkH5VMElqOApTrGRcxS2fiSkPXMgdQ6krNuMuMg4SKkDOVCR8GqN0Lco9MypSi3z5ZZ1B/Be27jWAKphn/hGJH1UHzPSpa1zIICQw0n8DcaF6pn5lA7kVDx6iROW8pgVK3mK2jiOn89lcPJggGAvk2Y=
*/