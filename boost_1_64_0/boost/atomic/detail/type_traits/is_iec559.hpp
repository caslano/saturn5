/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_iec559.hpp
 *
 * This header defines \c is_iec559 type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

#include <limits>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
struct is_iec559
{
    static BOOST_CONSTEXPR_OR_CONST bool value = !!std::numeric_limits< T >::is_iec559;
};

#if defined(BOOST_HAS_FLOAT128)
// libstdc++ does not specialize numeric_limits for __float128
template< >
struct is_iec559< boost::float128_type >
{
    static BOOST_CONSTEXPR_OR_CONST bool value = true;
};
#endif // defined(BOOST_HAS_FLOAT128)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_IEC559_HPP_INCLUDED_

/* is_iec559.hpp
Xo912fev0Pc+7lJ9/k71+Rg8Ba6C2fD3MAfer3qthCX6vshF8CHV38MQJ+HPwkfh65rfVrhay7XO0jkxWKjXPVXeh6n9JVI/esMDtX63gZNgW3geTIWLYD94M2yv9a0DvAd2gg/DLvBJSNuXchwKP4Hd4HewOyRPqxdsDztrP3E4zIQZcADMhLKWD7M1/Ex4tNbj+WZegmuoek6Cs1Se5cSTd91hL3gLPBbeCo+Ht2n/+Ws4FN4Nx8M7YB68ExbAldqP/hbO1nhm/8/Xgt8vONu5b2WM8XhuNfFauOJNc8TLjDFedozxSmKMtzTGeJUNxGubYGG33zTvTrjem/B9Z2IHzvuuRNT3JBzvRTTNOxHmfQifdyGc70GYdyBsl+V878G881DvfYe7s1zvOAS83+B8tyF3bZj3G/zfbXC+15CDK1kbjvl9hrp3GaK/x1CI3/n+whLOUWXHd7yz0Jcw3lNwvKOw5+8m/Ju9MwGsojjj+L5cHAmQhBAgIERIOOQKCIJXiVxyKEaJSvEAcmCikDxJsNhqGyq2tLUKitaDttQTldpgtSKllQpaa7VNvYrVWtra1loPqtRq799++Xayb4+XlwC1x1sd/pmd+WZnvvlmdt7uf7/xf5fg/yZhM3XYCXq/RdDvENw+C/n2wPPdQYLfG2znGs43B3xr0O43Bqf4vi04/N8VzCa4vyPI2hL8DYH7+4EZ/N1C2/YT8vixOoWwkLCacCNhJ2EfIe0x+o1QTogSriJsITxBePWx5LcEyePQHf82/n/DyksOFf//eBf//2/6u+8VfU/xOGHlOO7BO9o4qvZj/TkzWl/TyvMx8z6eV2AQtNxcyh0id1/bM0iJHxX4TneeSR9uuBYPSfxbkv8Nz7vLQlB9nZj32pm5rLMJ9vu/wcorLE3wPbf67NN32toWwyP0vg90v+uWOsXs/bY+Vb+LVj1eoXps/rZPjw1sBVVx6WJ4CXF0ie5UdoTRzV7i5PPrUnX/POmOLucZ+WLzTUPhToljs73C9OvyqVhxKbshqix2ImVN5vlQWmB5BfRLuukXt8/FD69P1qXp3hjK4zxe+6RpZ1ifyGv0oD4xerhWZMcKN0X7ScvLDbNxTS9w3kmKrQ7pn/g7ySBdTPHoImYfWr3FVaofrQWES2j3vp3eb3qWVlWNXywFKBdK29zW3n/YMpTc1/ibdMoZFNZeTR/Qtn8dceXBCr/yKvqlLF2/d8g63vJ976B5GsmTI5yYQpPnj5rHid/Vr309Os/4aZ/qMVSHxnY2Knd/JRcZqrgaHS75TqAOGxqXNq6CTOXWI5cxY1nlxotOzia+QeInRd7lXy93RfWoMmONb6mrJf4xjcNI+65wv10+x0w1DHfkCyJzhcRrTJmjkCGdv/pIGVW0cYSrnJXciurrjM84I0ce4nXE10l8buQ9qwvnZM4QuUu45TCEXO/1VVbf63PbcuVvrKltWBWtcuUv8eSviclfV726kfwuvb4geXsa+Ske+ajKbxD+ZgP3wuXV7vF8peQ9NfK6vlfaP0ZGToPkUb2ni46ehu1S7NW9yKSOFUuptVwc1s9Lehczd2+Q+Enm24sjJb6QcTVCxkQLtl7Vlefdxba9T/bZu5NnHXmm23mymnZ7x80xxLMsrlUkvmkl1PD3kcXiw0m4MtcQX6fpd3Nua4L+cGmvw733cDyxc4f/4OHL6Fyu79HUNvX8QnNebU3PLwFLZUyqLen5GnNebUbPR815tQ3n3aOO49nqa2wTlR+uePk47OwRzzgW8k0M35mGGTvT/GPMnHaexOsjc2T/RJ0HPd+fzTNyR5lxv0jiKyNnWOmBe0GWGZljRaaceK3EKyMnWxHDK4s=
*/