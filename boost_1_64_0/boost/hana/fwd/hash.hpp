/*!
@file
Forward declares `boost::hana::hash`.

@copyright Louis Dionne 2016
@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_HASH_HPP
#define BOOST_HANA_FWD_HASH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `hana::type` representing the compile-time hash of an object.
    //! @ingroup group-Hashable
    //!
    //! Given an arbitrary object `x`, `hana::hash` returns a `hana::type`
    //! representing the hash of `x`. In normal programming, hashes are
    //! usually numerical values that can be used e.g. as indices in an
    //! array as part of the implementation of a hash table. In the context
    //! of metaprogramming, we are interested in type-level hashes instead.
    //! Thus, `hana::hash` must return a `hana::type` object instead of an
    //! integer. This `hana::type` must somehow summarize the object being
    //! hashed, but that summary may of course lose some information.
    //!
    //! In order for the `hash` function to be defined properly, it must be
    //! the case that whenever `x` is equal to `y`, then `hash(x)` is equal
    //! to `hash(y)`. This ensures that `hana::hash` is a function in the
    //! mathematical sense of the term.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Hashable` `H`, the signature is
    //! \f$
    //!     \mathtt{hash} : H \to \mathtt{type\_tag}
    //! \f$
    //!
    //! @param x
    //! An object whose hash is to be computed.
    //!
    //!
    //! Example
    //! -------
    //! @include example/hash.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto hash = [](auto const& x) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct hash_impl : hash_impl<T, when<true>> { };

    struct hash_t {
        template <typename X>
        constexpr auto operator()(X const& x) const;
    };

    constexpr hash_t hash{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_HASH_HPP

/* hash.hpp
0uJhNnvpoQQePmoDD5HZ8/lnUUg9KvQooyMVV5UTDx8w8XDj5cDDdHtpK9tL5WDRHP3NsYKkBjsP02FxBFZTY/x0wBhPXU5IHGzJCJmoCBAb9vwwoVRz4OExsys+OdwYt0uCh+0Oy3/4YFY8THYbSmwc0fww4QbODYZZP7ygcgv6UL1U8gFqSepeKVAYjKeA4THTsGgHDG0bSxNTpksEhtJYSliRqkR5ZshDQwMEDdwzkQqaLzF5UlmVLjW6In5bmJj924v0+aGNyKHLMD8kF2KG+aE7gYoeZ3arqeyCMsCNlNyIUHGb2RV3DndoOmxU3Gh2wwdGNj9M+A+luTRznClwkFgkvDTxUGq3hIdmx38CD9WE/9DnzI2HI54ftpt4+GAaHgr8pX+vlx0Ph+k/9Kf6Dwuz+Q+5u/NkcQRgaNhmZSjoiOaHBIWu3TnB0DRg8NCQhop2wbA15/wwq73UMkfZ9ePbdyFmd0EB4YhP1qUJPHQ4rfmhkjmexooYTpofjthkesiU2Ecvh8k0k7mUOWTukuHQimarQz9eToE1NiEx2YrYbqLEg5fTZDrIf3gqZX743Iu0lxqzQ1KipmU4jc29JpsP2QfDEfgPnzaRUJeSuS7hP1z94vyH2ZGQ2cw9KB0uEmb/6kKqGVZvmwbPD22CIVhLMZSm+A9ljunzQ4vTQ6b/8NGseMhI2J349gJYiEyGgYeD/IfFCTwsuZx4mLA+5fYfpuGh5UMEJAL9pN9Q7NJobNUDJJSfIGacH/Y70ueHA47hQaI9k+mgr0uGE1w6gvlhwpKRGRINQOQReFR2FuqA5hyRu8wR23g4rIDvS2AvHfpb4BY5sEmfH4JRiYQJbDT9hxMYmMwvgI8wNp5gzZoAw6zmjMsChlmMpdZndLbmh7aNpYkPEf4DYJjiP2xPwcMHR2IvteM/HPbSNtKAMdL5oYGKD5mouNcGKl4iqyljxYta12ao+eHBjP5DRl5C4pHNDw3/Ia5SoTE5xjQFD+2tZHPp5of5Jt4t5xGcxEMhu13EdM70XGI8vBTr1gzHfyjx0JE6P1SGaSwdFhgmEP+ygmGy/1B1JvsPfc6R+Q+z20vRAYnRYTnxLwEeZrGXFiXmh4Hhzg9t+g+HsVZNikXjEkKiuVaNLf+hbZNpzrVqMppM1ycg0ayz9FWGMmlQqDhjfrhX4uF3cKJJWzIe/sAmHg7Lf5hzlRpi0978cKhF3oBxCTNpf/KiWKzeCPnMby+4DXlNNzlHTHwKTAouIxLKjy0sJLRhAM+IhPbmhwkkzDG08VsfW3DXHwoMAYUm9JEfkcAvFRj5+8OVySu7taav7JayOs3lxcNMK9OEaPRow39Ib2Vcyg15muu4jWRlmmAc+uUMs/OUZIfF5TSLyyMsLhSxvjzNWCrDQjP5DzHWTosvtRanacoIietNSNwwMpNpxvVpeAE3nIdYxG0jF2igogTknMBIeicFGN2JddzSvReRS+JC5HHpCJao4d6oGdh2gAsz15kELPZQqcb6UWAP0saKfYe5lFuq+eYHBj6yejVd31gAjE2aNvARUp7RePqdBDjKQi7RkjUbOTMuEi3LxRiw3Mr+RKh4sLqLF3PjpdyWQ1HG8y8E6wOlXFP7abHS/DNBt4az5qaccEcN1rhRenGQkDGkBOs8Gm5quFnjw+Ny2E/wRK51ilF4DdQFFHLER+tucqhDpFDDA63GL4wFCXZryKamSITUIM1ZSJ1FCoVc4kGTaaB6IgENaWTrmcs4YY1bEKvVeQSJlLUsRKgU1UrMa5EA8uHmxUAmGCkxREGrKcb6t8iFKoXdaXWqkPIbTPpgKILghEiJMGw2NKyiD/pkOg2PtbpSLTQ=
*/