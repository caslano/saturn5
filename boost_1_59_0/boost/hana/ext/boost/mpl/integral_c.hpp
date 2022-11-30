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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_MPL_INTEGRAL_C_HPP

/* integral_c.hpp
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
*/