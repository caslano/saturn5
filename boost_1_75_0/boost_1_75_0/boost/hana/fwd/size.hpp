/*!
@file
Forward declares `boost::hana::size`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SIZE_HPP
#define BOOST_HANA_FWD_SIZE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/length.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Equivalent to `length`; provided for consistency with the
    //! standard library.
    //! @ingroup group-Foldable
    //!
    //! This method is an alias to `length` provided for convenience and
    //! consistency with the standard library. As an alias, `size` is not
    //! tag-dispatched on its own and `length` should be customized instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/size.cpp
    constexpr auto size = hana::length;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SIZE_HPP

/* size.hpp
A2zqKLhtTyPwsg52Et+NWntHKncUXGNzdachHAXXUGrCPwrAiKDabPXMQDii/KkLQE3tgNBVNyCkBwQhfvsIV0n3/ULoejWEmtENobENoE7ngrY1umBM+p3ImYebtCPwpqGbxobKMqXKMqcCdrgbe0zeNLwNg8QfEIRer0G6Y9mrID8Ob5r2hnrhD9At/T4urQnAR/CmZW5oFf4A3dHvowJsH2eSheviTVvbUCv8Afql3x6HwdJtSzV072t3qsWwLMsxTKMz1bInxjiCj9XpCwiy92Ycun2t3W7mveVa9BGQ92VaNtffTYX8AXMteyDvy7T0QT4216LrZpveuq2Jvf14cZe5lj1w92VatuD+lnItkwzav1Ku5XAH5pvOtRwL/G8u1zIIBXUm8l8r13Jk2B9jrsXwXNWzPbXHddI83TXhz3l6p8pohqv36Tw9vOvUhPzuXIiR01T34TrprRTFvTtPh0/Q0TL2g+armgi4fy/qAX2o7qTc3XpRD+xDbR59dk9e1GPxobbBvxcv6rH4UF0H392hF/WofKhN2O/Yi3pUPlTXcXD7vCjHs21X6/aiHBcOluGY7p7pqvvO1D0zNMfRdEtTRTZqYJaVzj+Z7j88rskpykJ2TU+RG9DpF+D3UQE2bQJA12x1S7kLn5d+HxOEEyenXFfdUGCuAA+/j2x+cdzklK2qm6GKiFXwO4Ru6wUEj5Q3TWNDpfAH
*/