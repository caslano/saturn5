/*!
@file
Defines `boost::hana::tag_of` and `boost::hana::tag_of_t`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_TAG_OF_HPP
#define BOOST_HANA_CORE_TAG_OF_HPP

#include <boost/hana/fwd/core/tag_of.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename T, typename>
    struct tag_of : tag_of<T, when<true>> { };
    //! @endcond

    namespace core_detail {
        template <typename ...>
        struct is_valid { static constexpr bool value = true; };
    }

    template <typename T, bool condition>
    struct tag_of<T, when<condition>> {
        using type = T;
    };

    template <typename T>
    struct tag_of<T, when<
        core_detail::is_valid<typename T::hana_tag>::value
    >> {
        using type = typename T::hana_tag;
    };

    template <typename T> struct tag_of<T const> : tag_of<T> { };
    template <typename T> struct tag_of<T volatile> : tag_of<T> { };
    template <typename T> struct tag_of<T const volatile> : tag_of<T> { };
    template <typename T> struct tag_of<T&> : tag_of<T> { };
    template <typename T> struct tag_of<T&&> : tag_of<T> { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_TAG_OF_HPP

/* tag_of.hpp
n7/7vAmYjWQibIpFCbvVWKzhpkj0irR4DnJmK2GpnYATp5WOG+z984OfneawixdUe2cYvfML679tDZ2fjKe4j2stkDXkvNM9w/vM8qSbyM7ksRkIbcS5sU5IJnS5A2Z1lQarND+5s2MuDWOKEK8t3OM5TnVEHjxuLk2D66QFf9HCeniSU2LptrjvgI7iKlYTwSVSg+qBxs/HVBCMLkUE5qd2QWoHFq8TPeSW1Brv9dtAY+87wxHG6Tu/bCL5FVhGbDOozCQ2Cw693ZDc0Poh/GAIV999zuEE1fhAejhpsAsJLtFqrOPc2GpRSpAlHZu0lBikEvHMZj09ya2mRLU8+6rJT55Y4j7WLLaxcie0nJsGFSqmIkuW17BhpLxW2uQnUFVeUWPGJuFXJZW/jsn9O2xYeAaQNahmd69ibBVscibSy/n6RpxdX6Ip7s5VLqJO7ph33rvunrF91pbCW3PwRlet/oKZNv+t0PxX5bT47Y+Y8oygyRlXoaNjiauj5uy4JZAvb9Hql2i5u12JQ2PWI7BWcHVEit4TrkoeJp5leXXknpLr2ZaLrLU6kUwNTjP8W5aAIgla37B4tPXdCoPY+xxn6qj2ik5ZEvLKcfnja0vOiDTOWqyyZnhoYZzdl9ZZ1z3+6YefDn/kEaIJ
*/