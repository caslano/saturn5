/*!
@file
Forward declares `boost::hana::keys`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_KEYS_HPP
#define BOOST_HANA_FWD_KEYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct keys_impl : keys_impl<T, when<true>> { };
    //! @endcond

    struct keys_t {
        template <typename Map>
        constexpr auto operator()(Map&& map) const;
    };

    constexpr keys_t keys{};

    //! Returns a `Sequence` containing the name of the members of
    //! the data structure.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` object, `keys` returns a `Sequence` containing the
    //! name of all the members of the `Struct`, in the same order as they
    //! appear in the `accessors` sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/struct/keys.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto keys = [](auto&& object) {
        return implementation_defined;
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_KEYS_HPP

/* keys.hpp
961qKOaSZ0hQGaZN/WexB1kJ8DfzIC2kl0BNm13XVaOrarOSY/Z0YT0urwNd5LZoOUWiJogGdo/sG5F2Wr2GlJc0mJFgTXDL/yvLakM9OjtImAImcX9MN5OwJPE7H0OZdd69V8V9NuRXzTzdAFzKysH60ILcYab3h+i3V2uWzhGc6GBfCiXcAK4DYL/7H0p5cnkKQBynxT60f/2CH8wLlnOZx6K1iVZ05ZGsb3jL/TLQuKJjc+zw+ib7rXOOtdc/mLoi/apqBiJNv0G4p68yreMKcT3WPsvMH2xdtNIqpNKkbi8LlNeFs+iCNeBl53G6waV2DDlQlIkvEfvGkwnZXGfhW8FVd24b0u1F7ajtLl041Oyz8qG+LduMA2uRIVZpa9YPGzOYxNN92C2DD2Wz0UF/v0AUINLFGao5KvmZSnWb7lxQx7Y1qxYGI9IB+dfoZSPJ08VhkAB9ZkYV36KVTN4OlzPfMoyCejReKUqDRmY6ED3Fs6m+orwQVPIkPZm3KqzctSdesSm88Y959Dr71p007eXV5s9eSuY/FB7qxRe3eG0owVyVgE50qInNQ5QH5h2neZZaNqhXYnmicJL5Ejw+wZkF5QuJWT6Whxl6kSn/liU4A41ci9oIDezXC52mnIa0uNe7D3TvBnTgNnsn7JjJU+8+/dohGabDF/4HQ9botYBPKhOaMI9MiyFQB6gIJLgjUqcS55snnxhq
*/