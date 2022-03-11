/*!
@file
Forward declares `boost::hana::tuple`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TUPLE_HPP
#define BOOST_HANA_FWD_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/integral_constant.hpp>
#include <boost/hana/fwd/type.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! General purpose index-based heterogeneous sequence with a fixed length.
    //!
    //! The tuple is the bread and butter for static metaprogramming.
    //! Conceptually, it is like a `std::tuple`; it is a container able
    //! of holding objects of different types and whose size is fixed at
    //! compile-time. However, Hana's tuple provides much more functionality
    //! than its `std` counterpart, and it is also much more efficient than
    //! all standard library implementations tested so far.
    //!
    //! Tuples are index-based sequences. If you need an associative
    //! sequence with a key-based access, then you should consider
    //! `hana::map` or `hana::set` instead.
    //!
    //! @note
    //! When you use a container, remember not to make assumptions about its
    //! representation, unless the documentation gives you those guarantees.
    //! More details [in the tutorial](@ref tutorial-containers-types).
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! `Sequence`, and all the concepts it refines
    //!
    //!
    //! Provided operators
    //! ------------------
    //! For convenience, the following operators are provided:
    //! @code
    //!     xs == ys        ->          equal(xs, ys)
    //!     xs != ys        ->          not_equal(xs, ys)
    //!
    //!     xs < ys         ->          less(xs, ys)
    //!     xs <= ys        ->          less_equal(xs, ys)
    //!     xs > ys         ->          greater(xs, ys)
    //!     xs >= ys        ->          greater_equal(xs, ys)
    //!
    //!     xs | f          ->          chain(xs, f)
    //!
    //!     xs[n]           ->          at(xs, n)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/tuple.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...Xn>
    struct tuple {
        //! Default constructs the `tuple`. Only exists when all the elements
        //! of the tuple are default constructible.
        constexpr tuple();

        //! Initialize each element of the tuple with the corresponding element
        //! from `xn...`. Only exists when all the elements of the tuple are
        //! copy-constructible.
        //!
        //! @note
        //! Unlike the corresponding constructor for `std::tuple`, this
        //! constructor is not explicit. This allows returning a tuple
        //! from a function with the brace-initialization syntax.
        constexpr tuple(Xn const& ...xn);

        //! Initialize each element of the tuple by perfect-forwarding the
        //! corresponding element in `yn...`. Only exists when all the
        //! elements of the created tuple are constructible from the
        //! corresponding perfect-forwarded value.
        //!
        //! @note
        //! Unlike the corresponding constructor for `std::tuple`, this
        //! constructor is not explicit. This allows returning a tuple
        //! from a function with the brace-initialization syntax.
        template <typename ...Yn>
        constexpr tuple(Yn&& ...yn);

        //! Copy-initialize a tuple from another tuple. Only exists when all
        //! the elements of the constructed tuple are copy-constructible from
        //! the corresponding element in the source tuple.
        template <typename ...Yn>
        constexpr tuple(tuple<Yn...> const& other);

        //! Move-initialize a tuple from another tuple. Only exists when all
        //! the elements of the constructed tuple are move-constructible from
        //! the corresponding element in the source tuple.
        template <typename ...Yn>
        constexpr tuple(tuple<Yn...>&& other);

        //! Assign a tuple to another tuple. Only exists when all the elements
        //! of the destination tuple are assignable from the corresponding
        //! element in the source tuple.
        template <typename ...Yn>
        constexpr tuple& operator=(tuple<Yn...> const& other);

        //! Move-assign a tuple to another tuple. Only exists when all the
        //! elements of the destination tuple are move-assignable from the
        //! corresponding element in the source tuple.
        template <typename ...Yn>
        constexpr tuple& operator=(tuple<Yn...>&& other);

        //! Equivalent to `hana::chain`.
        template <typename ...T, typename F>
        friend constexpr auto operator|(tuple<T...>, F);

        //! Equivalent to `hana::equal`
        template <typename X, typename Y>
        friend constexpr auto operator==(X&& x, Y&& y);

        //! Equivalent to `hana::not_equal`
        template <typename X, typename Y>
        friend constexpr auto operator!=(X&& x, Y&& y);

        //! Equivalent to `hana::less`
        template <typename X, typename Y>
        friend constexpr auto operator<(X&& x, Y&& y);

        //! Equivalent to `hana::greater`
        template <typename X, typename Y>
        friend constexpr auto operator>(X&& x, Y&& y);

        //! Equivalent to `hana::less_equal`
        template <typename X, typename Y>
        friend constexpr auto operator<=(X&& x, Y&& y);

        //! Equivalent to `hana::greater_equal`
        template <typename X, typename Y>
        friend constexpr auto operator>=(X&& x, Y&& y);

        //! Equivalent to `hana::at`
        template <typename N>
        constexpr decltype(auto) operator[](N&& n);
    };
#else
    template <typename ...Xn>
    struct tuple;
#endif

    //! Tag representing `hana::tuple`s.
    //! @related tuple
    struct tuple_tag { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Function object for creating a `tuple`.
    //! @relates hana::tuple
    //!
    //! Given zero or more objects `xs...`, `make<tuple_tag>` returns a new tuple
    //! containing those objects. The elements are held by value inside the
    //! resulting tuple, and they are hence copied or moved in. This is
    //! analogous to `std::make_tuple` for creating Hana tuples.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/make.cpp
    template <>
    constexpr auto make<tuple_tag> = [](auto&& ...xs) {
        return tuple<std::decay_t<decltype(xs)>...>{forwarded(xs)...};
    };
#endif

    //! Alias to `make<tuple_tag>`; provided for convenience.
    //! @relates hana::tuple
    constexpr auto make_tuple = make<tuple_tag>;

    //! Equivalent to `to<tuple_tag>`; provided for convenience.
    //! @relates hana::tuple
    constexpr auto to_tuple = to<tuple_tag>;

    //! Create a tuple specialized for holding `hana::type`s.
    //! @relates hana::tuple
    //!
    //! This is functionally equivalent to `make<tuple_tag>(type_c<T>...)`, except
    //! that using `tuple_t` allows the library to perform some compile-time
    //! optimizations. Also note that the type of the objects returned by
    //! `tuple_t` and an equivalent call to `make<tuple_tag>` may differ.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/tuple_t.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...T>
    constexpr implementation_defined tuple_t{};
#else
    template <typename ...T>
    constexpr hana::tuple<hana::type<T>...> tuple_t{};
#endif

    //! Create a tuple specialized for holding `hana::integral_constant`s.
    //! @relates hana::tuple
    //!
    //! This is functionally equivalent to `make<tuple_tag>(integral_c<T, v>...)`,
    //! except that using `tuple_c` allows the library to perform some
    //! compile-time optimizations. Also note that the type of the objects
    //! returned by `tuple_c` and an equivalent call to `make<tuple_tag>` may differ.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/tuple_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, T ...v>
    constexpr implementation_defined tuple_c{};
#else
    template <typename T, T ...v>
    constexpr hana::tuple<hana::integral_constant<T, v>...> tuple_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TUPLE_HPP

/* tuple.hpp
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
*/