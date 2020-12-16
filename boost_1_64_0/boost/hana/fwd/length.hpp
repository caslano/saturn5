/*!
@file
Forward declares `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LENGTH_HPP
#define BOOST_HANA_FWD_LENGTH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in a foldable structure.
    //! @ingroup group-Foldable
    //!
    //! Given a `Foldable` `xs`, `length(xs)` must return an object of an
    //! unsigned integral type, or an `IntegralConstant` holding such an
    //! object, which represents the number of elements in the structure.
    //!
    //! @note
    //! Since only compile-time `Foldable`s are supported in the library
    //! right now, `length` must always return an `IntegralConstant`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/length.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto length = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct length_impl : length_impl<T, when<true>> { };

    struct length_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr length_t length{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LENGTH_HPP

/* length.hpp
VplmVEUsshktX1YaCDJ6YwNyOR650hxENAhduSa7s8HJddpUHmHp6bXwRzV7G6k0zc9vLWpu7wHfVxcMkg74NIyA6cQOERk2NAMrMmoF6OOvWHUdylmSnXzlrRNw4zNe2nv8bQ33Ijmo/lorOSHmEECLMmmft6scQ/LylVYdf0sI/GJrhKPV16sR/qKyPAzKitaDWhyU97So7s6Vv1RvmFE/auGSdMRV5xTZ3or9LZ/Dc6rtKat20wwmMwKx+x1vWTU8B2Byy3wpJNs0q0OyOWOnd7ydms4Gr5X+le4bbmD9K3fb1jVWrPds1JUWDXsqE/KCGVJMITzg96yxFBlPINTYh0552arQbxTUQ5Xh/EZnwr7H2LSs0i/dS682xFPpUtIRtHFPsOaD/LCd5b5hNyOo+xWcEk8FoPqLVrdfYXb7y28a3b5h5UHdHuYpeT+2dgfvhyGQ+dlBKT7GMvyP/fXBf28A/+VlHQr/QSBxEP5b9ZH474bVGfyXn5XBf0sM/LdT4b9TszL4r+MT4T+2Z4JCHA2Y0I8wWSBp8YvqQgW+xhj7dUdTICKHr7ZWLm+45tDtGe4ldCLD4ifE2OWiJSHzxLpEZ25su1t4G52oIsG88Kab2OHM8cYJgrfEW54cFRx7zS2yOexh+tRnbtYoL+9y0ZyQLqQTLo5Hn07KZrszJwPRYjvc+wOz+f0Wzsu1mWqpfwmrxLebmxKB8FqOAcdLg2Fo8TB+hNR5uT6mpvY7EPO0NPOq+bgde5S/zPz5msT8SR9S/tdz8Pw5t/Uj509LVq81fxx96Keu5k9vp5o/AzL0c/7WTzR/1DEAHDs5s3ZIiMV4Z27eaxxzr5qT5O1IPvyRoz44cdaUkeWeCsoEm6jhr5qCuKFhtTVgetv5FFdQyLAsTxg2bnOxZzxizWi2OsMh9Gczp2PnNdDwoCpqsi6YBrfX2LOa/CjYxuLltuiZj+Hj2j+OUKBG1/LoMD86st5Nsz+uDddLH2ZD+vL2TuygF26JvZ2PzBY2Vc1CNG89CxvASKfxK4e1y5EravIfhez/GHunzP6jQLn2LaEVc9Li15Dl+YC6dBREvV0Zd50tEkR6fS19uJX8uHeAaAYnW+BrEcpha6GvXSfpUmtCOnzPxjqy8TUarSgRM6/zilYA4mP/QskTb5zoiwKEiP0BFVPwnkh09Pd1JTqP97UTfEAf+ACCDxetvnZemhbcRXCvgrv7wN0EH6zgx/aBH0vwQSr/oX3gQwmeo+C5feC5BHeqfE7oAz+B4P0U/CQFxGYn0XESsgDP7evanbBHByE3QLoo0yzfht2JrGiOaG1/O9Exwtfle460blX6EL3Wpgxzr+EdZuHRjuPf62fdEunhm3uCofg0Z7zcNQMbS5LOlGsCRDhsmkIE5BOA+rAPjUOG4tsaDAXwUgqmBmDkVIItEVxH+Sa5fGCWxkxyCodvktP4xB8uxYTy9eOsd7rkA57a8SBX7QcnXOHl+0/B3bL+kS1l0/LsJ821WFwzonoJ4SK7PPE9pjTs3ntQzckKPKHz14o3G92SbVMGBKaBgTfJgrayNLSr7uujFG0t6wmDm16To2jztIoKsSyyE8QgjvfDIxW+x39bU84ogrIXCuwaWh55JVxmgI28bsQSFG3Er2PGwAfFSTUTjRpVL1VIs/UV1i8XdA6ioh1x79m+tABuqE3jN3KzSLBcMA+28m4gP0erH2vTHfseH8qEEDlaLpKNW6O58an2ombHekgtvVfmGKnbe0Ymxbru5/0J91JygwQjnrjA806w9jHSIW6OOv0vRLHZrL2Kb019ssn95Cr3feo+6NaKJa7CuHYmO0uWszfsTbvva0H12vcCszo=
*/