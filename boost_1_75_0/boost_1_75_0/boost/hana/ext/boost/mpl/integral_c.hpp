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
9HiYCtKz9X1j2LDufmUn5gD+fzzurW+Foitr4A9G3enuXzGwE+M4oeFZlGbTDDad/NkGlbah57di+00BXwMNyAe5EmWvfSumS31UCu97mHZRhAG/OQbTIDyE8ntlJ6YqgXifxii43rM/b2LX+hHpIsQ0TgP0/APfGHSEzxoSEA4a/nOE0Tf99lg5ObRG+MUiasJxoWqPQ0Y7xVWlXQmLCFcI+g5WaaPUTbQ5dCEAq5mk0MxsC4fVlc5q8XmfoTPGNujbhKOAOIzFA5bXj0Q+5NuJLJnKv6E0mP10lDbT6SPNsJ8UvHjMmdawFRNUl4FBGOhAFDYhClq9zW+LAFdJt7xCWpXQQG25h9eIbvteaaL8vOqnPJ+plU0DnT2gaCv8L4ZewPpMbdBThgaalWWA76JiBlc5rdCK7RS+9DxsCnMAvtCAHu6gjrHROujKpXW02SJRaLTo+Eix1k7L1NFJsZ7uVthTJfYTgvdsmG6Hm+KrD4vG58h1jXSObMF7nLsUutDyGbdFw4J3E04ytvCgf8ej652F6q03czitqnB8nxyMja+24JwI1fvMYGJthx+itc32a48AUYUk2HvorPNwo7IOPMvrM/OPfHRSAWB99f+SR7MMYEZhUqp0UrYCo6VPymLlpJ2iC5MSTrM/5hMnpfxDNFF6PXFdFSOJ6UYiE2UQN+vVLPs3ROb1bycyR7riROb1f0lkZr9zISIj
*/