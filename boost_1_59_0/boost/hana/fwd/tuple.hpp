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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_tuple = make<tuple_tag>;

    //! Equivalent to `to<tuple_tag>`; provided for convenience.
    //! @relates hana::tuple
    BOOST_HANA_INLINE_VARIABLE constexpr auto to_tuple = to<tuple_tag>;

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
    BOOST_HANA_INLINE_VARIABLE constexpr hana::tuple<hana::type<T>...> tuple_t{};
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
    BOOST_HANA_INLINE_VARIABLE constexpr hana::tuple<hana::integral_constant<T, v>...> tuple_c{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_TUPLE_HPP

/* tuple.hpp
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
*/