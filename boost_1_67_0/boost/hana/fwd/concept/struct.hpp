/*!
@file
Forward declares `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_STRUCT_HPP
#define BOOST_HANA_FWD_CONCEPT_STRUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Struct Struct
    //! The `Struct` concept represents `struct`-like user-defined types.
    //!
    //! The `Struct` concept allows restricted compile-time reflection over
    //! user-defined types. In particular, it allows accessing the names of
    //! the members of a user-defined type, and also the value of those
    //! members. `Struct`s can also be folded, searched and converted to
    //! some types of containers, where more advanced transformations can
    //! be performed.
    //!
    //! While all types can _in theory_ be made `Struct`s, only a subset of
    //! them are actually interesting to see as such. More precisely, it is
    //! only interesting to make a type a `Struct` when it is conceptually
    //! a C++ `struct`, i.e. a mostly dumb aggregate of named data. The way
    //! this data is accessed is mostly unimportant to the `Struct` concept;
    //! it could be through getters and setters, through public members,
    //! through non-member functions or it could even be generated on-the-fly.
    //! The important part, which is made precise below, is that those accessor
    //! methods should be move-independent.
    //!
    //! Another way to see a `Struct` is as a map where the keys are the names
    //! of the members and the values are the values of those members. However,
    //! there are subtle differences like the fact that one can't add a member
    //! to a `Struct`, and also that the order of the members inside a `Struct`
    //! plays a role in determining the equality of `Struct`s, which is not
    //! the case for maps.
    //!
    //!
    //! Minimal complete definition
    //! ---------------------------
    //! `accessors`
    //!
    //! A model of `Struct` is created by specifying a sequence of key/value
    //! pairs with the `accessors` function. The first element of a pair in
    //! this sequence represents the "name" of a member of the `Struct`, while
    //! the second element is a function which retrieves this member from an
    //! object. The "names" do not have to be in any special form; they just
    //! have to be compile-time `Comparable`. For example, it is common to
    //! provide "names" that are `hana::string`s representing the actual names
    //! of the members, but one could provide `hana::integral_constant`s just
    //! as well. The values must be functions which, when given an object,
    //! retrieve the appropriate member from it.
    //!
    //! There are several ways of providing the `accessors` method, some of
    //! which are more flexible and others which are more convenient. First,
    //! one can define it through tag-dispatching, as usual.
    //! @snippet example/struct.mcd.tag_dispatching.cpp main
    //!
    //! Secondly, it is possible to provide a nested `hana_accessors_impl`
    //! type, which should be equivalent to a specialization of
    //! `accessors_impl` for tag-dispatching. However, for a type `S`, this
    //! technique only works when the data type of `S` is `S` itself, which
    //! is the case unless you explicitly asked for something else.
    //! @snippet example/struct.mcd.nested.cpp main
    //!
    //! Finally, the most convenient (but least flexible) option is to use
    //! the `BOOST_HANA_DEFINE_STRUCT`, the `BOOST_HANA_ADAPT_STRUCT` or the
    //! `BOOST_HANA_ADAPT_ADT` macro, which provide a minimal syntactic
    //! overhead. See the documentation of these macros for details on how
    //! to use them.
    //!
    //! Also note that it is not important that the accessor functions retrieve
    //! an actual member of the struct (e.g. `x.member`). Indeed, an accessor
    //! function could call a custom getter or even compute the value of the
    //! member on the fly:
    //! @snippet example/struct.custom_accessor.cpp main
    //!
    //! The only important thing is that the accessor functions are
    //! move-independent, a notion which is defined below.
    //!
    //!
    //! @anchor move-independence
    //! Move-independence
    //! -----------------
    //! The notion of move-independence presented here defines rigorously
    //! when it is legitimate to "double-move" from an object.
    //!
    //! A collection of functions `f1, ..., fn` sharing the same domain is
    //! said to be _move-independent_ if for every fresh (not moved-from)
    //! object `x` in the domain, any permutation of the following statements
    //! is valid and leaves the `zk` objects in a fresh (not moved-from) state:
    //! @code
    //!     auto z1 = f1(std::move(x));
    //!     ...
    //!     auto zn = fn(std::move(x));
    //! @endcode
    //!
    //! @note
    //! In the special case where some functions return objects that can't be
    //! bound to with `auto zk =` (like `void` or a non-movable, non-copyable
    //! type), just pretend the return value is ignored.
    //!
    //! Intuitively, this ensures that we can treat `f1, ..., fn` as
    //! "accessors" that decompose `x` into independent subobjects, and
    //! that do so without moving from `x` more than that subobject. This
    //! is important because it allows us to optimally decompose `Struct`s
    //! into their subparts inside the library.
    //!
    //!
    //! Laws
    //! ----
    //! For any `Struct` `S`, the accessors in the `accessors<S>()` sequence
    //! must be move-independent, as defined above.
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! 1. `Comparable` (free model)\n
    //! `Struct`s are required to be `Comparable`. Specifically, two `Struct`s
    //! of the same data type `S` must be equal if and only if all of their
    //! members are equal. By default, a model of `Comparable` doing just that
    //! is provided for models of `Struct`. In particular, note that the
    //! comparison of the members is made in the same order as they appear in
    //! the `hana::members` sequence.
    //! @include example/struct/comparable.cpp
    //!
    //! 2. `Foldable` (free model)\n
    //! A `Struct` can be folded by considering it as a list of pairs each
    //! containing the name of a member and the value associated to that
    //! member, in the same order as they appear in the `hana::members`
    //! sequence. By default, a model of `Foldable` doing just that is
    //! provided for models of the `Struct` concept.
    //! @include example/struct/foldable.cpp
    //! Being a model of `Foldable` makes it possible to turn a `Struct`
    //! into basically any `Sequence`, but also into a `hana::map` by simply
    //! using the `to<...>` function!
    //! @include example/struct/to.cpp
    //!
    //! 3. `Searchable` (free model)\n
    //! A `Struct` can be searched by considering it as a map where the keys
    //! are the names of the members of the `Struct`, and the values are the
    //! members associated to those names. By default, a model of `Searchable`
    //! is provided for any model of the `Struct` concept.
    //! @include example/struct/searchable.cpp
    template <typename S>
    struct Struct;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_STRUCT_HPP

/* struct.hpp
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
*/