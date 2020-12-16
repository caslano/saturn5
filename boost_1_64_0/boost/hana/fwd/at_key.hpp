/*!
@file
Forward declares `boost::hana::at_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AT_KEY_HPP
#define BOOST_HANA_FWD_AT_KEY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the value associated to the given key in a structure, or fail.
    //! @ingroup group-Searchable
    //!
    //! Given a `key` and a `Searchable` structure, `at_key` returns the first
    //! value whose key is equal to the given `key`, and fails at compile-time
    //! if no such key exists. This requires the `key` to be compile-time
    //! `Comparable`, exactly like for `find`. `at_key` satisfies the following:
    //! @code
    //!     at_key(xs, key) == find(xs, key).value()
    //! @endcode
    //!
    //! If the `Searchable` actually stores the elements it contains, `at_key`
    //! is required to return a lvalue reference, a lvalue reference to const
    //! or a rvalue reference to the found value, where the type of reference
    //! must match that of the structure passed to `at_key`. If the `Searchable`
    //! does not store the elements it contains (i.e. it generates them on
    //! demand), this requirement is dropped.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure. In the current
    //! version of the library, the comparison of `key` with any other key
    //! of the structure must return a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at_key.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto at_key = [](auto&& xs, auto const& key) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct at_key_impl : at_key_impl<S, when<true>> { };

    struct at_key_t {
        template <typename Xs, typename Key>
        constexpr decltype(auto) operator()(Xs&& xs, Key const& key) const;
    };

    constexpr at_key_t at_key{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AT_KEY_HPP

/* at_key.hpp
OwMWPhloBDiKoIypRgZlhP1TjYhFydA9XnhakPB48YUer8SLGe6uiMSX6ALRxBJvwgKTKPgMChaIJ4dQI6ijlKu+sxKfRN9GaYpy8954xHI+RHBgmEBVLloKTw7y8Oay+Nfgeg3kbppLLcql0Z0XUA+DE2Y1ovIQ+tPxs2pLst7qwtd0ZpQgHs5EBuU6LDF3FlPhwWQ+r6AGZR279BcRAaBC0s848DQD6CpcgHzZkB346C2+A/C6MQ5DMndGn4q56NgCR65pDg5pRoTbke6pR+aYWOaqLetzjbZr8bMUPwtB4lNz/3t87Ahqovyzx+xdHrFVGr1NWIhu7U+6Kju4GmMVH4c5QqYxgX0mcMeDBnw9LgKokxmjwP3xxuerC1iPhLCXV/j4mUBOizjJ0tqhDjvepXnTyaSq95GraaU5clriDqD/HCrR1GD0s6+6HxacinL00Mp4yKFG/GKjcsikrRZS19Fw+KaMyhUJ/PCILxydyHdsBkjcD2j/m5i8HsX/POEydJBGucIMXXdMODJnX+LdAoyoKfgyXOqhQ12abwgdYVA7nscufWTvuObg/ozqqpJKMjrYwoTxUloCAHoigG8mAfgFAaT1AZCeBKAFyhcBbF7qkMsbsWfXIkZvcGPEIYFTo/iPIk/C+LJKsQpRt+r0dvnBlq2Xy/X0geDzUXlwQEutRQajz4heRrMXTLLei2lFUjfLY92AGbYCQdYjMyTb/VjNGa/WF5w5GVxGrN6P0iTI1/PxcX2X9wHApYGPA3+wAwM3U2nrMXApGUYbuJQwao+tlBt4gxifvpTrnXjwmby/0ZFE1dwYBmgKJGD4K1HDdu2Edtt/feIp2Ape4mUvcPwiRlyG50xDSPwFIv4QAQdKS/AVfh7XZ+L/rMKwNot/91EXexwvLMbl2lKqnDyQDS/OPxKA1AlL11Kgn1wAgR4/wU9Hwa0xgVok45Qx6Z1caAxSYBcyuqh5o/vbc3iiYae/9fM1rp+/jOteP/WOuyjm6x33cy9Xvum4V1jLHnBs5ZVgqvJODaW/EQ4QLn55UWcIa81TUd4GhZenZNWNXzFHdrUueG8XUMEUv4KSUvc4e40gs4ldtUwCHQ3nGwxmw/rr/JfgwYirOPhjMgSaGYdlXTXSRq2Nkb/xfTB6JUukWAmHSd+Rhe/Q24zJNRexpq0/GBPRiYRvNnmALyt9cHU3OH6ChSANMZBmgerDbAd8aw1u+e4d2zNRCBdvZgVb8L8tPpyFHLnoeR46+HX5y5hb6IYwLVQnnALR2S5MN3hfzKMSTkF3fEjxepfjEUDAtSgoq4vQhOJ3ljyRkbbmsigN9JXp+oUKGiByNf/lbnWngznSbCgOgWzqd+JspP0+dia6F3DNNdjNz42piI7usnqU8cpvRbn64w8JReReR0wYLYthmzvdqhcd6Ce6H0S7sOHsVW+QcJBFzjK1FgKAsQRUNNW6Lo5UrueXpvhcYPDPhuA6B1Y2W0W4aoh6zxtdRFVpj85mud0QGFHxuzFkvbRovGSi+A5G9BSfsRxLZiW9G28fZCE9ukud+5RDYXci/OAdd5n4JgZInnQEzH93w2eO1JOUTCb/+JyXy6nF8Edt+SAxUAaomo8TAF3XtDnxWVCH1nBaG8yt0BskHjHBpgTIAIIjLXgwIsidxzHcnm5mUyzA3IwWF0g51xjfWM/kt6nMnTwBLirgVJKK8Isv3jCCnKFggg+cCq0FawPftmlDF1xtVdVCE7lznFgiHx989X+YYt//G01bAWJJhYDDXcoyaZKMjYhyGEZ7BKfK9Mfa+Y00IQ4PRwr8F12ifvEDMCVXmOAVxisk8UsF9SMx/T9EHxCZHVjt3ZkMj+U=
*/