/*!
@file
Forward declares `boost::hana::set`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SET_HPP
#define BOOST_HANA_FWD_SET_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! Basic unordered container requiring unique, `Comparable` and
    //! `Hashable` keys.
    //!
    //! A set is an unordered container that can hold heterogeneous keys.
    //! A set requires (and ensures) that no duplicates are present when
    //! inserting new keys.
    //!
    //! @note
    //! The actual representation of a `hana::set` is implementation-defined.
    //! In particular, one should not take for granted the order of the
    //! template parameters and the presence of any additional constructors
    //! or assignment operators than what is documented. The canonical way of
    //! creating a `hana::set` is through `hana::make_set`. More details
    //! [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Comparable`\n
    //! Two sets are equal iff they contain the same elements, regardless of
    //! the order.
    //! @include example/set/comparable.cpp
    //!
    //! 2. Foldable\n
    //! Folding a set is equivalent to folding the sequence of its values.
    //! However, note that the values are not required to be in any specific
    //! order, so using the folds provided here with an operation that is not
    //! both commutative and associative will yield non-deterministic behavior.
    //! @include example/set/foldable.cpp
    //!
    //! 3. Searchable\n
    //! The elements in a set act as both its keys and its values. Since the
    //! elements of a set are unique, searching for an element will return
    //! either the only element which is equal to the searched value, or
    //! `nothing`. Also note that `operator[]` can be used instead of the
    //! `at_key` function.
    //! @include example/set/searchable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! Any `Foldable` structure can be converted into a `hana::set` with
    //! `to<set_tag>`. The elements of the structure must all be compile-time
    //! `Comparable`. If the structure contains duplicate elements, only
    //! the first occurence will appear in the resulting set. More
    //! specifically, conversion from a `Foldable` is equivalent to
    //! @code
    //!     to<set_tag>(xs) == fold_left(xs, make_set(), insert)
    //! @endcode
    //!
    //! __Example__
    //! @include example/set/to.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename implementation_defined>
    struct set {
        //! Default-construct a set. This constructor only exists when all the
        //! elements of the set are default-constructible.
        constexpr set() = default;

        //! Copy-construct a set from another set. This constructor only
        //! exists when all the elements of the set are copy-constructible.
        constexpr set(set const& other) = default;

        //! Move-construct a set from another set. This constructor only
        //! exists when all the elements of the set are move-constructible.
        constexpr set(set&& other) = default;

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::at_key`
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key);
    };
#else
    template <typename ...Xs>
    struct set;
#endif

    //! Tag representing the `hana::set` container.
    //! @relates hana::set
    struct set_tag { };

    //! Function object for creating a `hana::set`.
    //! @relates hana::set
    //!
    //! Given zero or more values `xs...`, `make<set_tag>` returns a `set`
    //! containing those values. The values must all be compile-time
    //! `Comparable`, and no duplicate values may be provided. To create
    //! a `set` from a sequence with possible duplicates, use `to<set_tag>`
    //! instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<set_tag> = [](auto&& ...xs) {
        return set<implementation_defined>{forwarded(xs)...};
    };
#endif

    //! Equivalent to `make<set_tag>`; provided for convenience.
    //! @relates hana::set
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/make.cpp
    constexpr auto make_set = make<set_tag>;

    //! Insert an element in a `hana::set`.
    //! @relates hana::set
    //!
    //! If the set already contains an element that compares equal, then
    //! nothing is done and the set is returned as is.
    //!
    //!
    //! @param set
    //! The set in which to insert a value.
    //!
    //! @param element
    //! The value to insert. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/insert.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto insert = [](auto&& set, auto&& element) {
        return tag-dispatched;
    };
#endif

    //! Remove an element from a `hana::set`.
    //! @relates hana::set
    //!
    //! Returns a new set containing all the elements of the original,
    //! except the one comparing `equal` to the given element. If the set
    //! does not contain such an element, a new set equal to the original
    //! set is returned.
    //!
    //!
    //! @param set
    //! The set in which to remove a value.
    //!
    //! @param element
    //! The value to remove. It must be compile-time `Comparable`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/erase_key.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto erase_key = [](auto&& set, auto&& element) {
        return tag-dispatched;
    };
#endif

    //! Returns the union of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `union_(xs, ys)` is a new set containing
    //! all the elements of `xs` and all the elements of `ys`, without
    //! duplicates. For any object `x`, the following holds: `x` is in
    //! `hana::union_(xs, ys)` if and only if `x` is in `xs` or `x` is in `ys`.
    //!
    //!
    //! @param xs, ys
    //! Two sets to compute the union of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/union.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto union_ = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif

    //! Returns the intersection of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `intersection(xs, ys)` is a new set
    //! containing exactly those elements that are present both in `xs` and
    //! in `ys`.
    //! In other words, the following holds for any object `x`:
    //! @code
    //!     x ^in^ intersection(xs, ys) if and only if x ^in^ xs && x ^in^ ys
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two sets to intersect.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/intersection.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto intersection = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif
    //! Equivalent to `to<set_tag>`; provided for convenience.
    //! @relates hana::set
    constexpr auto to_set = to<set_tag>;

    //! Returns the set-theoretic difference of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `difference(xs, ys)` is a new set
    //! containing all the elements of `xs` that are _not_ contained in `ys`.
    //! For any object `x`, the following holds:
    //! @code
    //!     x ^in^ difference(xs, ys) if and only if x ^in^ xs && !(x ^in^ ys)
    //! @endcode
    //!
    //!
    //! This operation is not commutative, i.e. `difference(xs, ys)` is not
    //! necessarily the same as `difference(ys, xs)`. Indeed, consider the
    //! case where `xs` is empty and `ys` isn't. Then, `difference(xs, ys)`
    //! is empty but `difference(ys, xs)` is equal to `ys`. For the symmetric
    //! version of this operation, see `symmetric_difference`.
    //!
    //!
    //! @param xs
    //! A set param to remove values from.
    //!
    //! @param ys
    //! The set whose values are removed from `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
};
#endif

    //! Returns the symmetric set-theoretic difference of two sets.
    //! @relates hana::set
    //!
    //! Given two sets `xs` and `ys`, `symmetric_difference(xs, ys)` is a new
    //! set containing all the elements of `xs` that are not contained in `ys`,
    //! and all the elements of `ys` that are not contained in `xs`. The
    //! symmetric difference of two sets satisfies the following:
    //! @code
    //!     symmetric_difference(xs, ys) == union_(difference(xs, ys), difference(ys, xs))
    //! @endcode
    //!
    //!
    //! @param xs, ys
    //! Two sets to compute the symmetric difference of.
    //!
    //!
    //! Example
    //! -------
    //! @include example/set/symmetric_difference.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
constexpr auto symmetric_difference = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#endif


BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SET_HPP

/* set.hpp
KOAaRmDkij9FUkDpgz85ugfiecqcX+E8KM4CSz8Qhln9JMZp7/xmr5aJ5rbf2g/wyRaW0UfO8ak6dkcLlsY94MaqhkTy14d0SFg/c8pgOZBz2L0cgcAgaVMD7wh0O1mnrEW0M9+ImodbtEBhCU0M2621z4oMrYXIe5lPqVIZYPNcABJSr2K34vlfChXuYxtqT5btJQzl13syobTsmHeTIRoUxambB2KhQWwhsCgKu6pYAh/z5A5M8XUHAg3SXceHTFZL4Z5KQ4xYynGvIRdK7R/V/d3/LrlquuZZ90EYLMdlhzTqikQRE6SkKXSzGoSUPMve65VBLTTgqdk1VFJEj1LFj9oiMwwWTxxQRJMlnPM6oZgj1FfvZKGZKQnGQqeJ8hJ5QShxhLbhbZZYPWRjV0+uTKNHh2xbTa38CVxJzB2lj9fPZRynqv1VzTxLeajIG6HUetGkTUAgM5UPEiKikgjVdJBARRk11/JZ0uMKXN74vSniey/n65sEFZ9Kh5HyBriwdoumlyp4cD5uA82m7oZYMaO5GpLlSSjVmFFSFSFRw07qrbugHtsTmPSaerGORwMuaEIHUQxvEqOnZtWPi+d4nui0guF6ZGemIRpUzaYkyEKAQaKRSUG7YWlWQLLhUn/Ej/lG0BESlGn9EzC27xPpOi0ZJ2PhaFuOTr28ZP65gpjGGUkhoOz5nXYj4IlVdt6fHfWS8O7KlqWKImkBjImEPwPUpiDyiHOWWaZk5iduzHLQgegAuEYyFDnQxoEmt+wE3QUU5i3C6WuK8KBBGm0yRSjTzzwQ96zV+oumxyqtgbF4SRD4zc5pvCnDrQqcFQ45PrggZMbJyfKWyimS/YNqrZuLcCSStMyDTCzMZxWyiUzMCi0xQd7QKahwS1wqkqiSJ7EppYjzrXzX6ELGdzGTsAq5WSO4E5I1ZXL9fzMLV9paf5JUloHngebAUJQZpCR1YGwAXCpP+JH/LR3jTtR+JhTj0D2lclWuOV0FvHebqJ4Y08EuADJv9AOsqekAAAnCQZoEIUwVbygzzktsbyqEusCee4v3VLmJaeEdAMILmxw+UtaUo2giwEWbHONIhPlqJ+4xXvGDrjJAWopo591ZvbskHe7f1AalDXZb6XGFL0HKf0GebRnXwZ+R+bvC0GLiLKnrYH1qZ/yCIchHwmthVoW1FvI/HlYMYAGw5PLPUWVSD+q6QsVGwsvFBJ0SDll4nUeAvD4d/xUrFyJZBLCcm0+8RmW7Rm2ibfK+HTJE3PWzGi05gq+1MNSjwcFXhiEraF7/f9RfggqOIxnSFN0Xm9yPqB0rHot3529axLZEiPeorsJru5syWYtzyD0eiKm4X7FppCbf1xu1EVtXZgmo5/drwGMVKrOZx2nR3nPcC+EyqVh2i9kjLDZKaHDCh+2t5km4VciIFH6QdsMa9IvOGQHz+Vdk3MCRJVq1vLE32g1cbf29cJ7OxTSUYqTPSmDLTV0tQtQX2EvOTlbhbjRb3UuUq7HUIpTojTqtM+aP2xjKVVM4l1cvBwRT8JBTmq0r0EqgZDTQ1fYClE4R9vX2b1KbH20P53mEgU+rBrKDrNRBtbR7Tg4/fHwuov42e3KAJYeUyxRISQeByHh8oEnd149J9aSBx521nIFKKfBkAHqFnA+eeHEUxyq0bwZzkHaWlCuaNc/kauDsYtxdrFDQLLlCiB41aVOAgxteHNjBHoEjdQvBRaAOLmySQkfXC7jalnQZrX+xDrezwjahQYEEyys+wcOGc74g9GQ/TfdyTpMRAHj+IA8HOKeV8ZMUfjG1c0knBbAfDDlrqure3jYP+GEcPnW59pjGvRDJLy/Nrl45NWscSXorTMyn8AM/eWnO777Z+236b4teP9x4p6R40MCnEdCAM7Ugq0YU0Ew4PAjhJqNf6//wk2Gm8fmhwBOjtihn7EIHO82/0dXDP126WKOxskI2Ujnkz7ySmdbBRv3hc5VYXh1makccwLVcXP0aYTrHOE/3GgLVDGdBwArcL/kGBeKDtwDcX5wtAUQoXOQzwg58X3JRLbvyeQdjGGC14rAyjoss+iK3054NqNKTllMWLAjekOKiFENiW4Il2xDpLgG90knUyoznglBBqZ/zJpXdJJAkfVEpb+38o0Dh09uUTDZWaqYXUffY3tgkTQwkxCUmGTNju4knLJYOpXVCH3kZy1hzu2djBeNeDyta/TNoe1hXKOZyacKtvci0PdS7rY4otaYImFUq/SUu+0N89ySPIhnFuLvkd0+sSlUGMyvFS19hlDZzrWV67PONVMSU8zaNrs/uYDavN2mDW2wUiMcxX9LhQHgwJ1TETsiJjyjWQYZEPlmdTsy0jCp1oTvUxL0pE2RjlbPVI7gFh03xA3MdyK6sU7pnRJAtcxr8u3eyrR390yiO5OgrtM3rUBXe2GXT3Y1JgVSGBPagKxCuuZza76IkioDL2eRNMlj1jeTCZFcRNS9i27v8lQkAMRIoxLX7blI8nKVoZZwp2/KrOnGYONPEzE91aSzc3MI0I2RUBn+ohd74QG4ZinTP+ktCdx1p2liVkcD9P9vBJQ28eT37foCNp28acIWDpyqxAi9rNDe7lu3QMDIsBvhskFnUwgqS+no16z5wOPJGX70XhuQ9jj9O7oBxRfVG9cnn27E9Uffit1Cu+F0tNiXvjye9JIRdowJGTlg8djaUsnUn0LNPVlj8H0fH6po6MBOzFQcIcxpclq9qaSX5LKUFtAVOu8H7rh7MY8+9+L3IMhZsUhoRnIEbCAgNE3YXdR4GN7pw6OX0ybZjGTbHjAIyYqOCapBKo3vgl9QKqAdHK01y/+dbUJlWgPzwP0ncWacT3yn2+AqVff7NobciPZWxN1EBXdUtFYLKimfzK/wS8k8jqG9KXxAO3+dTxcrnDuswGzMiuyILTHvulLRUWxXFS+RqyWZFvRjLHNI7nywJQm3dK3NrxR6wzHwsGqxbWdwmtHHC/Jd7/OLdyopApbtqjxCIEe8LL9z3EVO9faLhYlgQRzk5ltcxA6woXCFyRz5H2yZ42hjCP24VD0rsyp3u/zNaFto3S4OJ5R148xwRx3VC1eFPZqqsbYj9lXtWO+gOQAoyK4MKRsXCKfIrQ6D3x10tQqVYxF7YQoFSF8oVI3fusWImrAK0kiULDpE4qjh7nvd2GkfdifC5VhwmYfh5hZ333zWhZ4QefKI/X0piuowk4NjnYiPdjWfhixS1OtEAq+A0e+ZfdhSGK/DfJnC0yOOL32dDNmuIwr46lrk1Oz+5geYMfX9caX7Uj3FN+N0LHyaVxTtim+vdOgmkvULcCOgLUy7yTp8q2Z7Hkl9D/BsODaIpPx/dRxZrju4UltvjKze5RaFRw/qSQW80eGV+kPFHYVuEwGfDEG71cQS0DrkQOccPzksdQ2dkU76W85Udn7NtixASLGoew0Jrnz8SzFVboAHkr7KLU1qejixYnJWiA0+TP7UDyfg6qk+hzpgjq53QgaWBeqB2kH8U/JpNlE/T7HssJ/Pwx+0laamnWF0s2e/lr16MvABSeztb9eyjXEoI9jENzcu/uO7qR+fWx6fSyp/sU/Yw9I/LEgzuYb4xBw0GFf5DxjUvQjqkWv5poVQ4q5x8wiFx6fHfrBDNWlKlxCKoGmbBGFAG8UbxiZZTlH1WozFvvxMf0kXqWPibsz88Pjjc1hrmIG2H8Y0Q65NORVGoSblZqgXc9KS+jdgpX6XYO9XPqowv1mFgJp8VN+EvV7+8Iyxzv0XCOVhyqBgnm7/Kur75ByBExywD/QuhYax7GDe1zXjNg+ZQ3hUF2PpoXxKo274x6leuFwnHbkFxCaJu/HRde8OqMaxX4qtKibQ0kii0hgbGWA/cjmiZxpFddbTcP5lcXDR9X4hv/yvQ7RnGUa3xQn2pvt1BFSbh8pqo/CiguB30ZA6ldQYOhtEWP5DQjJHkKMMxsdkGyXJsOe1w6qLD4YLD8YejInqwR3z0moOEnDtLD6uIwb9y/dkJeAVhigBYucLOKnAJqqQgseHFcUls9rtW99Hs5ej7jvdlcYAAHR8gSwIU8YJsRi9QaPAVp2TPQZKTpIPV8htVaG642UVaFl/QkONxdGzDke6BLDQ5XGMQ8QlZLXddpIEEiPVqm7W9UneA3Mnw3gBTlQTjnP7arZMeJSh0NEUdRTRhvpnKidCZSzN4rOZm2CJ/DdvDkMNAZ8KClatdX6sll7Sf3McBXZCv6xPzUlv8MElJp1dFRg0p44Ln8hvKGlEbfMJZNaUzj9pqXx1yEAaM1IjnUq/6mLciJYAUyCFyAZI/gRO40uUrblaDXUYnMK+aAg3m6ebfIi/JDMWNIi7m58vqTw2L5f8ha914z1g+dmAhGk/RxAAAAn7dBGIiRU3wS3CxtKYIsLWo04LfOococmpfy+IfSKq4fhNL/2FCYIPpVHjZApF523iI1lyDHSelfY4jm7nSTA5pyju+5tgIuUVWkWJ9H+H+GxiHuSWdU/aSyJWcjgb0jPMNko9UUGxFZV5om2z519W7stII+B8gb3PW7gxjk3Jv+HvN9gK5gqPXLAc5Ehyi24qV8rzuYNp8O9azT1o8vZabMeXh4z6KFOv6nv0ceHQzKBdOEIiKk41g5SF03vpNzjcATICpCDoYBgLIRQlDdWtajLJDekAFgCxZgjX2UdsAOP08qyhv8tsCufk9dznU9qriBb0ahDEDsZh7lEEg14ARVydvcK130xifSWv10UqrEbLTop1zTebFv3r6eu5r5K2Xpxm7GurMqxV2CdzSaT+C39Aaa/aZ1e92ot10etBGu+VDYsN15kExGM14duKraLNB4VNdip5ZtVrtSV+c3hFqF7WyD38xT2kjjCSy2o9cvZjXRELTjCxa6N2KUk1ogB4hGlTdnhbNQ4jAi6gshiSokqVAIGmCZSYRxhY5QmUEVutFigxCQYW1Gsb2oUmTNhlMp2HK7H+tLFzZOVuZpFlhZnWTdSxVX+FKJJOlPIrMKBQa2zyXY2d1U3hvoGpsa2qosiA9Fb6KfJ3dnxm2+ivGchKaDXPC7ELnPjfnVz8d8xzzZmY2NRFoS0tAVNYFFltzW+uUp5bmlCx5zfKhDWzOuLe9DRZRMTCIDmeO6NTV5EDh/Rg7hJI/TqdAl53WpAHEft87FnAS6fe4bAONCk+eMGCro8KqAC6Ln2Wl31kjpLFWFgRuCYhZKBYiAgjBpw5nIFnDQFXFr8/W1rTHfsG0NSvV0Nr9rFnEx3hY8gNmXZs6gAsOGWFRIiREha2NHKrtmhnh4EMVp/WltqrHcAcAAAEGAZ4GFaZFWw8rMuPA5dl2HTogvwecRfmBNfzRN5Nvw+s0fYCBew/XXDYZp5v053/pqXRspr+1Omlfa1YEyUHf+iYD1XkVEnikJn6YpzwbPYB2Gt96q8uUp4SaiT4pADytlIOd8Gy6AMmpaeac9xdYT4DppnaXGDKLGsbQojtkD+PLkBoshjEp839kCgkJj+ddK+EOjCDuqcOJX4dZn6fqm4UzxRve/DybJQjIzOQZO2lHP8z+8oYFB2s/3rXYmXD4bcRupoSkMUks/HX+zynUUkkL9DUEfoZfl16pFtnIgTs024EYGez21a7Ehyq8N8KIb/7/AS8AnmCaaZAqkkZ1t5jlJ+4G4CEaVMWdoUKBsdCCIBbnhtAbuVql4hFAXCdpPB764ThM93+7XcXdcc0xn7037K+X8bN2x5Qf44dxY4vi4LhdJkt6Owje77nCdxrWtFCAdIgpKKhZbD/nlZ5qhns7OktMuVZDnHKnTJhSJ2efYmjo7dGG5yNtd59rZ2b+3FeaQQpSCJ+xBs+J9rgJBYf5iVG4lQ8UqN2CQy7Oi7pElxmq3e6/WIS0X3aqsduNrcq+WE97aApVcu/dXPPTC6UVGAzM6EcKiAr5r3J8lCpEQ3J8g2zYiMkgWMz0ZTbJMK6lssOcfDzjJuuS5cm8neSB22mEr2vnVWCBtMBsUbo+m+2/9Wb/pPtgBLUVXBYWWG1AXCdpPB7iLn/OvSCSevi5hvOPh2fh1VSrlTHCZxG7Ym4pAAUnOp8hGlSlpZ1FgqGEQbilUKOaJklpkRQAd2kqVTjyFdMZr6+7Fg89qI6Fe1GPg1AhvIpiuywrZDxuqeIegCEhV3ACBCJSMVdrBVaqaV2vs/b067233SvLG18MGL4SVWzsafk69R8ceNPWM7RzjoCjOGtidNn4OMmOlBjGQuEfLEbfm0iYuFZe552axD3U7J23U4emXmN1hA5b6588bEVoCaycslaaVOOKtLnPVEstSOjelQSXAtUKUbBNnvieoMU2ogG0ALfYvJgkBgWslAYj1+P/byKaCicF76GlDP5mI9zvm3HSHoD69Lvw5kxW7EgRxyGbj1G3751iDw0J/vcDmUb/PNelb3/GYJSxQhChpcObByD1DP/Fka32svSKsngAHyzg09AcSyNgkvsJwnoMlbFnCz4AAAFbAZ4GGaZFWxNBhavU+F2ljZhfXUnoFTcQhmIzrIVovVUQl+vd1ynaQMnv7k+9qYNtML1XA3qkhD6iHD0AGA0VFSdChx8peSfjID1F3mdwlUbFevy7gqywUgmHRYGaU2mRHXS+RuPOK3i3Id1nVBvMnAs7A0W8f8toFyIlcILKQnXjSM9Uxkv07teitq6RUErXnFwL558gnr6sGeGajisIag8QE53iNNrJEa0mk/VgzuVOtoi0YAlMacM6eGLMwNxgG7fL+BK8FfoUg+dHjxujjfL06aXePjHjXG87ZpfBytD9zYxqThaXXD4AtKo58bGJKTPjaWaBWiQmS8Awaj+M0RWmAyxK+xacXrqE3O18/3ju+YcM69CYOEwPlUOft/GLJ++MDynt9CRCmric0yZ+mVqlungus4zs7p4o8xF4jFai7IlPNolvqfmrSeUGnM1or8RbIwuaT0WlF+IhGhS9hpKKosGY6CFaVgdlAMLqQlLoDOkC3YDmC7hmqV+Uc+2QDUJnbiOImaVE90x0FeuNQntkRQrYSxWeHl/Goae+iDlNQF5hcgfU1Qxp6IEkEtxM8TaihYMIRhR0UHaIzS2llSzJ1JU1l+1nmudNVgjYxV5/LqCC/xlk2ux4ssZtDTl1JIGStSk1lcWwq4oKc2VxYJhS7vev4DsIQ2NWVYo06ZTWrla1ilbIPyiy4E2GSP2ilPPTPr41RB6THO2mUfCu/cbYtRnolfGGmeKJ2SuvZRfLFolThbRYkaDlyvbqy4XZ5zU12DM4OwNalxEq2IZWxhFg2WmjzWpF7GvwsTwp2I52yDwAXITQMy0iZYbEuqzQD9Q/rwfln+pS0mCmVHxkh4sghgmW6PEhGlTNlhCHYVDgzHQQhIqN2jPCDJAJEUQYLSdWcbicH05PobSYKbSF1ZvzH9ZWz3NLp020yYAUFZf2NrauV7MkB/zT+f8aFF79OqYgWXcMbtm7kQxHZ0dVHejgkS7ipvxbTKbaOtcr06ArLYmngkNikyxziZb0s8nqVFFk+Lv9aoiz9vcZ13YX2xXT0XDtu+WxUxOPARhQywW57jio0r1DeoAPdFYgbXC1jZpmwDGuOQkgmXf4fyvXTTv9HmXLDMoTvqkvjSPmq41Tnc5CU8QaxYcbs0p52NLxt3XFtMeq7Cf5DfYBGxUi5Q1ZZNlQ9omyDCmDzOinAQAz8kOjE7khlvJZwftfsJsviM1XT8XWIJeBMwyBcC6igA63qUlhtniQqhLKil/zRKJARAN0WKUHZUAz/8/0AAABXgGeBh2mRVsqvB7Z9YIeJeeoGFmj9HibOhRziLFhqVxi5aCO2IZXQRdi8VP+177P97jpS3Na974Wu499FJqahYooYF341tHiFK3UMcc5BAaswbyrtGBlLYCesf1VGcOuLHcDnVbY8OqoTVt/uzZFYbTNEHO5pIoI9qXc6yFykO7UjumDtSBsUH39L9ZBAqwY3Uxvw9oR01TuZ9/OQeG3sF5JpH04kglvGyqbcyNzzaZ58eg/QiglQk0FOrtLYqfW3F1Wjvx0wy53LGuS3rp6Dja7xnTJhatFb/M80YgYuVNfItaDxHsy/shx+I06plICjz8rPlrLcnN+NBrNXX2b+g7ponul9sWPQfQzj8Pe7E4cKpN/2ig1PwZRHDuh68wh8jjoY8yRiFl+7sudjVDCHV+n/usHSZyv5SMlcc2AtjviSbEGLk93GzpwKFACOJrZ3tEMyr5nA/90qvtZlUPKIRpUzaWdQYOxyEISaGO9YylAyJCAhTYmlBR4fC+e+YZSBw2q/A3dfa2/oE2Him/SXVRJVdQ5UO81insRYqR2AiSYFMAoAxiGRr54oiJEq02Z7tnh1zdVV0yy6/Gkha5eJ/Z6hakpnx2882ilo/Osm5JeHBZv78kHHNnaubVSrksjxyeBZo3j2lxZ1k+emEys6jT5c6+1pYMLlRIS4i96yT2iN9iJ46tRcyYUtd1rM8tW2smbIdXAHl2U4x2dzoJnQsdqSTgeFWmS2StxluDhMeAmRlZFapcDqSrmD5HCXBNMYpbTnJQylUZwdHNcUxYTsMwlSMXJFwzuB2CrFd7y8TYCyI6K7sSQaAS1JYokC4kBmU2YPtd9ujYOC5TwZJmKJEQTCjq15kIXWteAXCrCdywHl8ohGhS9pZlGgbHQYExXPHeISiYiQkolArU13C5q7H7791rMOzd3UusyLNY0PUy/eW8HoA9vfN10ARwcD0mRUMxIlKQ72ILwnZ5q0A1C6Va5Z7S4ioaoPcpQQcIixNspa5eZljT8HOVrBbNABGZSjVctp2vak1dGhC1ziUkcoP8py20T+rvpGTavBGyWhhFQZ1p51g/FXJPO2gqZcHr5DMtcvUHQbEQ1Y3hI11EbM2vDuvGA2Rnj3cJzsivpNT4acWr26Ee6p/YlmFN9eLXd2N8w0ZzC5AecudTDJJAlVjVzmZN2IYl0AhSWelEgAcjnUbXd7poOuy1K5fCHzTj+27PqtUfieZd1ZgPLqwGIk/d+bLS8MgRlQB94+1l+5fePd65M1XFn57w/F6XI0zV18tuydWuVUvDYJ1uxAAAVMkGaBjBgO39Qbybax6oA6LhIuitsw/xcgy6eNuWvObb9tFHoAcGK5x0zJ+RHnEpJSuynI5ThOQtW248peUrNWZ2s0w64k73dSNLFkyGntPhgrcE=
*/