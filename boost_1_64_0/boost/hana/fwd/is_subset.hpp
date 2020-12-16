/*!
@file
Forward declares `boost::hana::is_subset`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_SUBSET_HPP
#define BOOST_HANA_FWD_IS_SUBSET_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <boost/hana/functional/infix.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether a structure contains a subset of the keys of
    //! another structure.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_subset` returns a `Logical`
    //! representing whether `xs` is a subset of `ys`. In other words, it
    //! returns whether all the keys of `xs` are also present in `ys`. This
    //! method does not return whether `xs` is a _strict_ subset of `ys`; if
    //! `xs` and `ys` are equal, all the keys of `xs` are also present in
    //! `ys`, and `is_subset` returns true.
    //!
    //! @note
    //! For convenience, `is_subset` can also be applied in infix notation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! This method is tag-dispatched using the tags of both arguments.
    //! It can be called with any two `Searchable`s sharing a common
    //! `Searchable` embedding, as defined in the main documentation
    //! of the `Searchable` concept. When `Searchable`s with two different
    //! tags but sharing a common embedding are sent to `is_subset`, they
    //! are first converted to this common `Searchable` and the `is_subset`
    //! method of the common embedding is then used. Of course, the method
    //! can be overriden for custom `Searchable`s for efficieny.
    //!
    //! @note
    //! While cross-type dispatching for `is_subset` is supported, it is
    //! not currently used by the library because there are no models
    //! of `Searchable` with a common embedding.
    //!
    //!
    //! @param xs
    //! The structure to check whether it is a subset of `ys`.
    //!
    //! @param ys
    //! The structure to check whether it is a superset of `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_subset.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_subset = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_subset_impl : is_subset_impl<S1, S2, when<true>> { };

    struct is_subset_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr auto is_subset = hana::infix(is_subset_t{});
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_SUBSET_HPP

/* is_subset.hpp
SiJEUDETa44w1gsVsZMSmpqM9LD/JBsTKox2Q/QMkJXiOVYVH1dCvkZhsIKVMm4z2bZrBFaOAzCHUsGXhiM6VewSM0bt0HnLyuGs94tWkncQgb1AcecJ2qyN9qPkutNJ3ilmI4+gIy1PsxLYwQO+X/+GQPNJOknxqQUwDY+G8QIz0w8hl1Rxv0KMqwP73VCYu+plM6R2SFkoLJ/Bp1kLZEVzjJkZ6lr/+3UFaMGUecvCEccWeZcV1T5JlY9yKR6XnY6e40czasf07bf2dPqhJ3hmB+QMZaJDwkBf2tdElSZTGmZqC3Dqc7T//dpR+yXem47+dDZSDrdSlkFx0URFUso09gFgqlnuql8A7pQSGX+jeVT25RxSZQ/MGLCkddN5WNUptsVv7DX19UxLLI52yMkKr//3crT/XT/lxQeOq31vSs/pdJB4hNybDkJgP1wa+15M2K/hmMKX2VxOXptnri1CI3lh+S0LcH5Y/5Yrol/mkud2W/hWeebGKs4CYVHxhgfY2O5slRCSe0byZZ1BeTqXqYmVn/j4uuH/FsbVJOnTuI59/+RPFDfC23nNFj2+OsaH+YhdubTmMrAr97tVhJajcue8YjTLP443/KNWwjTNEl40FRJnsv41LJWukE6WXEm8h8Rm+Tg9ieWSDxhv4+Rv1RsQ4G30hhG4BU82eKaVBtUpOoqcW8u7sZ00uZAtdpJicH9+F0Scjr014AnARdjQHs9WgRTvHjsThSlh+efjrf36DwE0bPiZVA4Kw4j0FWPoFpwZR0MCchZEWjUayb2CAfkoBKAsQy2F5dMlrAfIp5yItwwS8UnjJ4e/btBPdyPpI1IaIUuV2zFWbuGA/AblFqTcmCQxpf0Ub7ELKNNuQ8WRq4OS4lko8AzLhveYcJnyRsg+5NPv8lxlCznDJImdokeZFyjo3hrk7l/EHapRtBrUE/rW4wT6JILZmfq0xb9da1Z5Ck+YIUNMKdJ0MgGoPQmxF71szm8P+yMIy28cp9QPHuVfApCpXlP5cRYN/ig59VU1uVuUSfjoZDUIuDn1qoU6l3eWUnAI4jezWOJTCtMBnGrKNVQl2chFiR41I5+jmKX/Pr8gORBmB/7yHcw0lqKomUJ20aCfssTDLSWF16ekL/NxLMa57FTTwvnqcDg1OJIaJAerGOEwx8+zlEYhDMGDu8xhGqkuNEidIPf0M2P4oLfaaX2dMikiq16x5kdUud4YGkSpywcf6PNftBz1gbAD8UU+YYb76FgP1gBJ0mz40RZDnZIjfDwqRNbN1ShVQEyh1mrjz/phfmD8ZwBsgARAxObStQMzCwh3f3UH4Rqa7PkygvegkHI6P3tkBT15h3Se8VYsfXjDJJ8NlFSIVyxmYhcY4UDKmd/PQDjj38kgnCwAyQw9F1wviTU9eBILEZLzhlnYZq7CNsVhOSOjaZ3cB9vUM7YJybM7TGwznFZ/GJ4xhnIDuazhRjaQs9FWVZ5i2umyeJOD5L5shp1nc4JrufFSkmPKH+2w8M+DDpIZhZHtbpObi0TK5ZZjzEU9jHLBTPjBNguFkLkqIBscVtWXAoI82t83+bonGnc3uKm2s6wZ+U0Uw3j4HhWLSo/RiJbLb1qlkfsPEiSeYpYWPRtf88ySooUqi2qroAQKKmGUgon41inmRBxDsjRCEjFIzBlB1HoNU8rXOhhBjLYQRH6SVhmqv2qr2dneIGmNt5p1+ANakjo2QrocC/azEAo8z/q8MSQnbLdWx93gITsvYnF5kQVtrGDAN7EEqRHYzX9FrUaciyhgGpUnd6hRYLkyVhhjd8LsnZtslHaMkRaureQpZmJ3I2kKCI+DC//RS1YGH6ASqmfk2yZ04Uk=
*/