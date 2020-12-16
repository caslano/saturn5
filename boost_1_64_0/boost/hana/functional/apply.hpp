/*!
@file
Defines `boost::hana::apply`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_APPLY_HPP
#define BOOST_HANA_FUNCTIONAL_APPLY_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Invokes a Callable with the given arguments.
    //!
    //! This is equivalent to [std::invoke][1] that will be added in C++17.
    //! However, `apply` is a function object instead of a function, which
    //! makes it possible to pass it to higher-order algorithms.
    //!
    //!
    //! @param f
    //! A [Callable][2] to be invoked with the given arguments.
    //!
    //! @param x...
    //! The arguments to call `f` with. The number of `x...` must match the
    //! arity of `f`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/functional/apply.cpp
    //!
    //! [1]: http://en.cppreference.com/w/cpp/utility/functional/invoke
    //! [2]: http://en.cppreference.com/w/cpp/named_req/Callable
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto apply = [](auto&& f, auto&& ...x) -> decltype(auto) {
        return forwarded(f)(forwarded(x)...);
    };
#else
    struct apply_t {
        template <typename F, typename... Args>
        constexpr auto operator()(F&& f, Args&&... args) const ->
            decltype(static_cast<F&&>(f)(static_cast<Args&&>(args)...))
        {
            return static_cast<F&&>(f)(static_cast<Args&&>(args)...);
        }

        template <typename Base, typename T, typename Derived>
        constexpr auto operator()(T Base::*pmd, Derived&& ref) const ->
            decltype(static_cast<Derived&&>(ref).*pmd)
        {
            return static_cast<Derived&&>(ref).*pmd;
        }

        template <typename PMD, typename Pointer>
        constexpr auto operator()(PMD pmd, Pointer&& ptr) const ->
            decltype((*static_cast<Pointer&&>(ptr)).*pmd)
        {
            return (*static_cast<Pointer&&>(ptr)).*pmd;
        }

        template <typename Base, typename T, typename Derived, typename... Args>
        constexpr auto operator()(T Base::*pmf, Derived&& ref, Args&&... args) const ->
            decltype((static_cast<Derived&&>(ref).*pmf)(static_cast<Args&&>(args)...))
        {
            return (static_cast<Derived&&>(ref).*pmf)(static_cast<Args&&>(args)...);
        }

        template <typename PMF, typename Pointer, typename... Args>
        constexpr auto operator()(PMF pmf, Pointer&& ptr, Args&& ...args) const ->
            decltype(((*static_cast<Pointer&&>(ptr)).*pmf)(static_cast<Args&&>(args)...))
        {
            return ((*static_cast<Pointer&&>(ptr)).*pmf)(static_cast<Args&&>(args)...);
        }
    };

    constexpr apply_t apply{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_APPLY_HPP

/* apply.hpp
T+ucuU50fgR170717cKI6Amih2LbFCZS9/aK+j/Mv/4RgIYxD7MXHMSOXDk9o/+NQ+PDWfhXQA7hl2taPwKuHsy1NW/apP+2bGrVf1ubW8zfljb99/xWg9/c3ix/Db69eaP523q+/tuxsUP/bdvULn/Pl78d+o2oo5aegG/+0DLsJeP3Efyuxe+j+H0Mv4/j9wn8Ponfdfh9Cj+lK67HX6lms+nuZjTf05vLjWWKRdjV+/BfnYaifSO+dBK/afRkWw9+h8GOQaWOTC6ifsByBsozW0GJlrbW9k3mb1ur+bupzfztON/83dyu/27EdNB/O1Ax/m5q26z/treYv5ubN8lf0E/MZsq5NtXHmn0T3HeswhG6ZHqqUNEXNagv21oo4nv2Wt/3A+DG1fh9EL9r8Ps0fs7Pfj98Mh0TkEZ0rDENLzRv/Md7LACfT0VMbxPOV4kfd7TAbu5zsKvXoFbAFtc52AlCd27Kwa4B3XLEhnqI7mNrDN364xzsM0L3UqL7vNC1HuVg3wZsB+gWEN2PpOwTCHZ5oyl7dL+D/UTqu/ZkB/uZwE6nvtwisPOI7nfSxhuojT8J3SeJbv5a5EB7/TsaMNAh58PBTlpr6vsQ0S1aa75tFcFK+O9X4XfdPAdbIvUtv8jBGgT2G+rLOYtN2RtM2Zr8YXEl8b8KvBWklWKFz08iIf322sormZ2omOUf/9gHM2YyuhtmrFZ/2rTNJkxLS/PGje2bW1vZlxYy9prhM0Y+893xgY/Mh/8F1/k/4TPevVL/BE+zztmLd9fpvEu+5hFp/pNuVt2tx99dn+kuF/gHnKx/jyNl54HnUdXiRtWmgYL+zT80F6o7RkdyhjAPyFb2/KJ0V18f/oAS/4i8gm19O7fCQlXpIN3p3uGdMGlhWP+XelFB9wgUWFesf1y7z3V3HCn9uVK9MrIHUn3DERypllt06+7f+BaFQQ+Gd4zsHPznuWJ19nv/Q07Zv9kVq7O+0H/UKfsHHTHfAeua0wGjMYYrth7/l/t3+WH/CUeKfL+fie/3c/xuxu8X+P0Sv1/hdwt+v8bvN/jdit8AeHQb/v7jfphSknslv+TH4j/9BL+f4nf7Ms7XXwE7O53eNrzdGLadKuOB9+1XBfBmfauzNI2Khl7KUDRy0VOd74Ntofslb4Atf+wJgAX8MsA8HwywgC8EmO9XAOb7C4DVuF9n7H38Tz5A8mOIj39zfAz4Q/cN+FwRbK3QfYnoiDeA+bwBLMAbwHzeAOb7og52Dtr9C+rbXedg6wU2RTDmK2C+jwmY72MC5vuORNcm37v0FMAC4wSY7/8B5o8dYHd57GAg4aLU5NgtqndjR29KafktZwqVvJViyXesa2QZl3rTExVBuzyLS1cQvgwHJq+nQYLugY1E5zXGd190r61O1013TW4DHY7HzgBM7wTQ/T0ezXQZpxNKsxVLdLvbU9+w2OypX0h76oBhT93BLhNYC8FeKLDXzXOwKwTWNN/B3iKwJ1HZqwT2fVW2Rp9ejbMk9lRGxydnzF7z9LTZY71re8wJh/juuNn/E/7yP+4Y3C0P4F+4t6JdCNpPuktbK/+rLgR975G9if8DD4L2jWtwJv7vXAj2B//7dnb+FU6E84/+q/Zz/pV+hLJv4C+cWAebqj68V3QG4OvwOxO/e+F3Fn5n4/cQ8Ooc/P3X7enwfgzbUqeJLXUu/vq2LH4BWzaCDYm9N7bZwUYAezbsgO/OAyxg80aw3aD7GOjeVOdglwD2R8AeSTCyjQHzbWMHS0tfbqK+ZAS27AKBefYRYL59BJhvHwEWsI8A8+0jwHz7CDDfPqKy2bX4LuRiPu3eDjYhfX469bkA2CjollJ9U0I=
*/