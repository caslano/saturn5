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
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
*/