/*!
@file
Adapts Boost.MPL IntegralConstants for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_MPL_INTEGRAL_C_HPP
#define BOOST_HANA_EXT_BOOST_MPL_INTEGRAL_C_HPP

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/core/to.hpp>

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/integral_c_tag.hpp>

#include <type_traits>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace mpl {
    //! @ingroup group-ext-mpl
    //! Adapter for IntegralConstants from the Boost.MPL.
    //!
    //! Provided models
    //! ---------------
    //! 1. `Constant` and `IntegralConstant`\n
    //! A Boost.MPL IntegralConstant is a model of the `IntegralConstant`
    //! and `Constant` concepts just like `hana::integral_constant`s are.
    //! As a consequence, they are also implicitly a model of the concepts
    //! provided for all models of `Constant`.
    //! @include example/ext/boost/mpl/integral_c/integral_constant.cpp
    template <typename T, T v>
    struct integral_c { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace mpl {
        template <typename T>
        struct integral_c_tag { using value_type = T; };
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename T::tag,
            ::boost::mpl::integral_c_tag
        >::value
    >> {
        using type = ext::boost::mpl::integral_c_tag<
            typename hana::tag_of<typename T::value_type>::type
        >;
    };

    //////////////////////////////////////////////////////////////////////////
    // IntegralConstant/Constant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<ext::boost::mpl::integral_c_tag<T>> {
        static constexpr bool value = true;
    };

    template <typename T, typename C>
    struct to_impl<ext::boost::mpl::integral_c_tag<T>, C,
        when<hana::IntegralConstant<C>::value>
    > : embedding<is_embedded<typename C::value_type, T>::value> {
        template <typename N>
        static constexpr auto apply(N const&) {
            return ::boost::mpl::integral_c<T, N::value>{};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_MPL_INTEGRAL_C_HPP

/* integral_c.hpp
fECsVW/fYK1x2/3x+uYm25IZcIm+a+Qz/r63yvZqZ7J3ORvuWvxtW7Fd/ge8sn6R3/pSSNG5ixv8eRVfeYmjHAPDgNzqHu0wcMbhsV5jdyv+6TWjvKQ6nlshiv697u1PEnHhLDyKbHfJeRs11gqnR8mfNK6zV+FkVJ3b3bjeQbrRo+Zw98ixZdDue26vanfejHu93873G2txeey1Nqd+T8X/7PtGXY2zMTr6cPhDUR+Qa/tYx+E63SfIyNzX3yFZp+ddZWiu+rIj/Jb3EqzGJQitCT6jjmec04CwvuBU9hdQJ72CIq9jAkOLp8mn/PL4ysfNjGmq+vCNfEb25pvDScUmxfFZqcuvYz/w2xFf3EiCap8/iT7tUmOYiLfP32R5FYkjh5WTCAUjfpd7Oq6/jLxEWkvB/TORAedqSl4ysP+a4pJKu+zfWxcUpcypxlFlV8Y2RflzNlVW7nMn2cucbv9+NPPVV4knAcHJ2p8+m1jGsYK/7xBvvfdJBKLiV2iU9MX5Geiyp8kzv5Zy7sL1ihx7U7IWFqLKurXxTK1Lap2a9yN3IvUOlS5HzgAMXom+q1wiEa2OfX6Ury1uzWELrMPfGURQDuOdVxv/cyCyX6/CG5eTfrD5ZNnWV6emGDV/3sVfj7TFZNT8mFyvkkX09tshSvglme+RleoeXKjXywoxtH56Y3erbaID2+ho8DdtDHNz//VYpZVOT+MYv5t376SrVeu6R6k+yOCLvljcW5eZkzOmIFdP4Kpj92z8LL6crXNO4exWidcD+gg8N+rTuA819xk4vp4WEplhycN9z3tqsC6rsUKR2eEmTbXQIbVdTONxaCznagSk/hzAH/XJa0GNeEmtwxC0ajtxxl7ksNnAnL/P+EZ7VN5ojyIa9ykURfvz50R14+c6R4nnjBjZd+ZvPMcDBveSB3L+XKes97KBwFzoQF+9XLr+iRbN7zP0eqm0ntpKFVcHB8xZ1evIxnOWvuNPn1X13Tf2FbQR2VkriIp7b+Aam34nZDjl94Rgm7QJ1uT9Hsp2UNbTKPt37qHy8R3cRZN3Re4Jb+quyN2Uep8CC4rx5T6dS43SfYx0ezL77M9q+dad3mQ7kZ3yt8lsqk3AmWd2U21kxONtk9tUm4D4JI82eDv1HoTERKNcxGyKDvruARS7/XcA8mUfbFNVsRJLjZPlFfZKl9xXtW+xIqFUjc4fCxvdM5FnpoovLoxqHGOrc55AXVIBn+OkXoCbL6eglJe7nXXKXHzn52XWEmhWwgC1v4lRRp3YHbXcSjnksFzYJ5P0jVMiymXsrH/WW9GdCZzJ+soDuEdplFqHLSjP2bx1fM4rHgtV514m6yTrEUdZvrlUKGsWo6kyrpbP+VZgrRY3NHzPuqh3xNuUdcg7apSfxsZuEbxGljVEGffzQ4P8ZTNkWbAsu/RvbbG0GCsMsMFNjWwwQrHB0mLd+KT+GfeeJMCLdfj0f05j/c9VDMlntzc02cZ/t0q9i2iEGoKMSVVX9ml+lD8HEZh3uJE6g+OjlTqLdJQ5Sosb3bX4RJ79eWPMi5Vyoe/6876ErebPm0gb89pRjDJf5RxMJUUIj5kSLql4fDP9oHnq7OQ1Tr+e3hqlxMsB+f9f5J2DwPh8IfulHrY3ysdEqTGcmnr1j3kHbaqKp9hZ4DTnFDt+vvE5HXZY+y/urgM8rqMIyyYhPbHjJrnIspM4pNiRZFmRAyY5q9iKJVlIcgkIjtPdST4s3Yk7yYUWeg+9txB6J/RACBBaCCWEGnqvAQJJqCGUf3fn7f5v3558CZ3v45AzM1ve7OzszOzs7nQOxXJjdr/5BdzPCfrwXGECbEqrOMxSml/QNwrWWik6X+4=
*/