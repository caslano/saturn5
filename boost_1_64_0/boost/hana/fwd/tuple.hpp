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
mHt7ARtTbX3LBgzx9SNj+0fiXb8XF3Em04FwEAf8MGdl2vumScpLsokFVVGzJLbYShPYm8Rta/DUZ2yTBPMyN6ngObDIRmwJZDYUEVEg3oK34gMIKMx8AfuAUhmlhg1/5+u5uFo2UpR+DV72ZZtHxt6HEEor9nCZMjdGm1FGiOR0UV0Nm1SvhKgLLP2TQGBC6B1JgquY9mSUlrjn5eyEkF5NaMRZx1AVVGgA06VQieVLhkDJnZi6PQmBkjdFzhubdXHhNCVWMmY3qpVksVK2EivJeYXYn4RYqVRGyEkWK+UNECu5SaYE0ZIS/yiRkhlKNJAlkWhKD08LjxIrDZZBSbFS0QCxkjdJrBT43xErKXuBWurezVETXq3DByczJVb6WrUSG31tWomDvg5YIKSvE8YH6evSStz0dWslHvp6tBIvfb1HeC++mfVf2nn/3Krvn0O85bVojdhI20jiq4Vc+ORoITc+pVrIU4e9MDa7NDjBs+MD5mQ0PqXtlrPxIdYXHzAw5/HGFsHORG+djNiBGQ0YaBg49TMg7j0T6GygPWdG0cDY9AZoXxwBmrg9Dzxn8dWzNdHERtZhbFTzGerWocrkcd/uHK1PBDFG9+rIPEbacC6PqQUjRqPBhz5P8dptwxFOAvkI52q3jeZNdpa+OXYxuwZNL8AosuRueYOcBZaMToFjRgKOzHfkvhL8kNpUIiZiU34N2pp259k8EXkxJ3brhfEajHWRDmUDIhK8Kkve7GQxFIrCn46EDU6aI3VrzcRN8+SSCrQLjBEqtbndeV5UciGcr1vbT+mr/Tynvp8qXYdKGSoiKJNCVgKazLhOwKi2RJ48HjP3qcmzERWJaZbKQrRzExZigo/pDVjI5drCZQbEW+dChvPMguhgdz27S9kdgZtY9y36hA2QyHoliogaupHKOUIpY97mutUEajbGLLJgjtkjOeZSPZN3jAwrZZWzO5/dk+HmvY+a8AXF12LIcFbmXlRwoZxeUdLoIzxuMOOjsELuVIyUsyWLq+e41ki5FG5ZxG7iZjePir0/So/wZBQIDfkY+6AayXQHeF+JdCRbzKkk9oOVsvHYnS+bDm6q2ixurmadZ+YA9bQlZI5V1dxkdBK1i2EeGrsY2VnMIoo0hqEfyeVK36WhlsnWP7QtM+WuvYjOAGmE8R6lh2s8IGu8krurqtkeo5MXsrsCbgFXp1HbevC96K4sWPun1nvwasZ1EqKNiOqcal9v7IqK1F7P2IhkHev+obmNmYtQ0ubBMRovUCTtHBy0RUzeOUg+PQq85NO12IDjm4G7CHRnYwshN30YzEn7h0Ig0Cxq/0Czy6DNQ5ZajnnzQONMphuR6bJoDMume8BWYW7yVkFuWuRGZfBWAetn82dw/fxf/8n1et38/8B6bSzVtHAPXK95rcaaPXCtptX7I6/XNODUYLMv6THRsDI/QfMLDT19BVcrt1rJeQXHqp28iHNSLvbpwlqRpYsVmJ3XZ+fdmWujCKNWcMa5KNvdlK3LvAewLiVGAryEJ1Z1Ws2x3mhrPu5qjulvyTMm8xNqVf9013S5ZAxa092Up33JCyaSym0wr6d1PQpvqtuk9R3etCahtj+N9d2+pM9Ea/xOucpHKfIrh13lUd9i4Noe4yoPfJhVXrIz/cj6LVMsLrOOoXiDl/tPZq23L+k10Xq/U0ZT633mk5/Aig/R75JtJlrvtTW0ypm3EgfwSaz7tNqj0nn5V5L6fF7zZY+bpq/5FaolEjxyAG5V/3nsLhq45qPjc70/ISNhBDSj2v8pK13rpa3tgGV/mr7sl3LiXBlyWMvKUKJfljlOp0pimeMaSBxJecckK+bIDMB1cz88A0Bz1H8=
*/