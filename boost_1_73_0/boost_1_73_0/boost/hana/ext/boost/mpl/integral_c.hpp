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
KwosPGJBGWkFZBLoI6wlhLpJKMLq4uaGCNfP0ETMFiqT9DC0ij/P6pNDpx+uRPw/N7yDDm0DT+JkiC5F/yeiwt9i/44s4DGUDPpUoscliH0MDnFw5aUTHtaEq8MmQikBKmJ9PrN6UOaSFuqJMSg0F+1WYy9Bo88pJ0/sqnybPQpROlvJiHeYkzPwL2PMSni5EjkzEQwlo8TstARPA/YWp/w0HFN6P9wHnHngXjEslPExQlZqhnp3kyylBLtXm6GUKQVlFDOMD3hHwJUpPvjZONLjwWPuNDFMtgTj1sw7DYyUwqpGiacFNVZpERga5tj0E3KS19cMZTpzZbJLpVAiLRNqXZzxuehRhw0EyiRgxBkUkLzCsuRAfZciPKxY4tsorgCH8nCti1zB/f725+3PSE2Emw6Gbehqr3flawNbVO6FXm5PlXOR+EDIojIv9TJPZJlfAGsL9BLGIv0dvcxTWWYUANtZ+qnLjfUpdbCVgJVpJk+NenYV80LGm9fQY4oQnx2tVgDgkuUXLohBoYGEuNQkCidotgDJ8qHtEFJeiPrXv6QIlF3CktYaulLFLEyXUc3F1vZUon6F1UEwxtf+GkAJx6iVcL+6h5uO08LKXuOwp2Kaf8DDnH3dfa01wiy852vhrOUNiq+LtxZY
*/