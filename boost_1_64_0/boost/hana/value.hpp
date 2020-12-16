/*!
@file
Defines `boost::hana::value`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_VALUE_HPP
#define BOOST_HANA_VALUE_HPP

#include <boost/hana/fwd/value.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C, bool condition>
    struct value_impl<C, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    template <typename T>
    constexpr decltype(auto) value() {
        using RawT = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;
        using C = typename hana::tag_of<RawT>::type;
        using Value = BOOST_HANA_DISPATCH_IF(
            value_impl<C>, hana::Constant<C>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Constant<C>::value,
        "hana::value<T>() requires 'T' to be a Constant");
    #endif

        return Value::template apply<RawT>();
    }

    template <typename I>
    struct value_impl<I, when<hana::IntegralConstant<I>::value>> {
        template <typename C>
        static constexpr auto apply()
        { return C::value; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_VALUE_HPP

/* value.hpp
D1kYW5eK9k3bvCwdiDLhtwxcUMc9mPIwKBH5hO3yQrqrBrv7MQ8r3SO6Bjdn83THCPKft3FBvXX1aRYmqLeue5iw3oL823ipi85gvdpnYaQuOmPaee0pFsbVRQX0m41zdVEBa/0TLZyriwrPM/xs3Fhd9KEnudiwLrp2yMZJXYR5bGOCeuOcjbH0BvK2Pd7GkN6w5+Z+ix7UF9fF+HiZN4UsXpO4gCyaOt2wcdAX0E+iznWiy8ysKVFeb6+Fc3VGF7axSeB4jsOi0+rry1648u4B7zHfELmPu5fHBXEp9MmjHfqwT0c+XEn1DW7ygIvrQm9JXOkxNo69WOlE+bbIJbWPOx+nXBNFzKce5cWxUaNH52L/g8s74mP5vX/ExnI4RnTg3DpmMOAnMCJn3vkDLl2c3ujsiHueEE7WTeQTmXzIx2oP4SIHkqfiNnwowNd4ruOcH8Dopy+4aCmLV9329ltURQw05mzqoI3Tl2pq8HC/uS+ISbUQwyxkYDcZtGcM3x2/wycNrMtuu7qNQa/d1FUS+SXdvqLDnNyT5p35xDfYTTb14Vy17ZaFvpYiK+yMO+Hp7Aq/S9F2O4O40KcuZn3LzK7Y109gQtm5ceYM45ChG/t6H+fK9ybsHkc9rAiFqnXazRi7ccDFenNhE2fKJ7hYfy5c9evpzoVNnKUk1s36LdaV8492cXC9Hyl5x/kizA8ZytGOBJySQ9xtP9XF4EJBG0LrtKGOZexKqI7y0C18wiae7mNP8YRJrRhMCfwERif6xjkpgJkWMW+wQR8O4PTA0YI6pEUtPl8fSMbKXKazR0M4X74vB/lBvmHD2XbGRNsGu7CNuH3GXcEo8PiD2x/N9nqL7jFgL32MS+cEtzT0AuPyoDgyXjuJhjOWgzFG4FG/p+Im0O8PnLaHjMWQcbHX8TO3py5ALgTOzRCP+gUxWngErzlX11Imofog0rXwgXl0CMOjCMwfZL/KzP7CFnvj0T7mFG9ykL4/ltcglhdKgPEeiDNPdbh3rZQup5dUU6LBa8POviMew9jAHmnHbyLDuMFf3hHfJL+bDdxffmhHvPIdoyvPiy2Ou0TesJ2+OwX52UQes52/YVnCXeTOeC1XYk3Z8ZtUC3Pk4Dgsbw5a8MUYx1eHnEtfjNTDY/AkwmYBgT//8R3w09ESBvuO4B/GY99MAe3jsKzGOrhnHttOmgzmQRbR1j/IfrRfe5H30g3cF4sz0ZjXYRqwtaFvXDxyyfdN/eceDmPFCkoPSm0MpMzcC9ZfXvGmetBJwbqzsNTgj340hOHrUnlPOkB8RJgnDwz6IIyhAYHwdXBOk+VLbBSXO8KdYriv7Bu3lPDrDePllTz0yt3j47DTrH3ZJXsYBXdAlsZ/Z0KOazi7PiERz2OCvW4ijq+aUO+biTjz2gvt6Mzml/Dmu/vHx36nYmVHHd3olPguJdav3bxmBHvB0cTv4B6uVX0bvs8Hd/4mhTzghN+bjIf7tx53yP7kuG9ORR6swifogShjp9ef8P7b8R2+qXO9+LCPM1F4XHETjHsJr/6F08xV3H3fepqPYS6EQR3d/Vc5d3b5TC7rn/dFzvcx34iX+7MyRm0u4Rt9tr2IM8XBMI73N3xQIUs8hfBjX/U4D/9612704IiPgZ1F3OtPPeTjHFvKDPYIB4JY97yZxbiG8Tgb4swQqIOwa8SxQegnFxefwacCZer+buE9xhDGPzdn4ddj6YHwS1jYz4Z5y7NSHBMRwGpZHUEvhDD+eSGLd2xDfclypJLhKf04VBtw4E/uiC8WsmJM77h7kNJKubRcyRlPB9jSHg7jxPaqgD3HGJ6s0Z3xODmG97RGQ77HYiPGODfLerhYYVM=
*/