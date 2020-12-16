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
CYXW2JGLgmLsBzkwN3jl8rVQPFcuGa3JU2OLV1avvMoqF69j8SZmLR38Fui/W/yelDEGIi4PvZLTzIvIt0Mm3h42UYkdUmu92VtZSIjhQcONGIg9sfnlRZI1YPbK+ko74BjxS6GHprFUcc8dxhrled2oQsbuxCo9EVYb8AAOZ+jnn82o5MZQKck1o/ERoMSvBMBP5FBg9XQiIHxx2qBHuVLH8gY0CWqkdw94S/PgtqzXg7syXh9bpG0bZ4pwlIrAaY2AgAOGzqROik5jEZpZweHs+C12tw7/kee1oziKU0DdIS3zG3RUexEfDnfy7cppPq9YrMlp5fwpOi+uSzeskhena+O0tojbY+4bJf3RBFp1xrW2rBrHiBo0RgEao1D8cY/dYr3WlngAwbT8/wRMa/d+SfWYDGrx5+egArewuk74F6tj8BZS0aXedD7zpXawx+fxkt+llbizqkI9y+cZsipeX0by8N8tLphscMklDmuJWwOYmoSMPegAfQNSwNPpHoNn/hK5g16DqfN5CIvP7pQkP8+po1a9hHi9fdRzSzzaW2Bw38zaGxlGEol1SOHi6/UAtQ+l/vI2o9e+oEvTE4UV3HDGNuoMjAQd0wSqNVda81ylUYK7hgUaI5ghA0SJyN0xUDfTcCpxhQfSBEQEInhKv+O0fY7hA1HEXoU0VTHj2fNnu0VycYm7M3ZYUdEYAW2p/NUvH4zygnW3NpPHs1gF2W+h8K3g0mIdlog1Ag5GaK9zB1CxFvPhDASonqECipeZu3RmBWKM/XUn6v+5j5TfOTDz8s1XBuP05HzZw6/+nSSCG9GyKaR5xWPzUr7/2V0+JDqAqExxkWPVHNcjzDr9+DBe01MjJU597SNsYIM96npOasG9LGZxUwu2RWbK2lMB3y41f7nO74AcIB/q3yWpRpSRwo9wnf2SMXSGZ/bumg+xHpHMjkuyOd1+0dmcGR9IFkfQqiy0iBgRfXlDXUrv0MJ6hz5AgDwArtThlxhZEZNyB+T8xN3Tr4BwElsfkEzKCUzN3Coy7dFow1MDVi9ufXhqGlejCqMlrFdccDNTVCTtNxtz71D0aSz79QoGXh5xEgpr2Mg5CqQY0MSV8bAmLp67Itm5Bb/v8bOg+lfgNxa/UfgtwG8r+Vvt8gEvlGD/5zytTO6kemGtN/13PD7cMJT/C/ilbNpTeOzPMX7JLW6bRRxSKnNIF3Is2K5cZHBITHYVJVKCbCa9Ou8Uuk7yTg9c3zLeqTH+qePc+vxTqrhoAeBeGUO7UDxfLpmnxOvkuzfnmN4CJor5p6nX1OOfRs0w+CcXclEAYvJ/9FNVyDJOq9+Lm4hjfd4C4D10IRsD66Ht4QMpfLlTe4zRgK0gkOSjzRIXNktOoeoJT5EMg5doN/3IAsyUVLGe5SVpNEhw2oMv7gUQDDAzEITAH3+5rC08VGh6QAX5an/i8+i64H5Y2zsWkXSsgAqYCgOhYXnMIU1c6NcXlYjkCqbO/SboJBLmLRDbJslF3x6feEHWB6lNY1JKL6RSpbHmD1MmGCdy+ETOXQwJZRpbNLoSgNqRbwZ8feKt++T+DA7uIAzzTcuVNfDo+gDUf4oquQjotO/+nppLiAVXc7bIbxRtGXoJ+0KPOH4CBW8TB8PqtE8XzJfHegsLxCCF92w7bOTQpfKVhGkpa1wcLzEFe4hiVJKA49Ab0LL/3IJZk3VhzwFmpF1OZNGZdYF9lo3uDSSbdAh2esQ9T3N4SvhNff06/E1tXTONrOxfLIvtT7Ht/kLxNpYEhSjkvImACF6eNSrIqAhNamQYwHEz3TqPiW3lkzyxLcWrUHz1e9WcIzGZZXrFNc/EDmAtSm4wnb1wt5w=
*/