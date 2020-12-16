/*!
@file
Forward declares `boost::hana::negate`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NEGATE_HPP
#define BOOST_HANA_FWD_NEGATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the inverse of an element of a group.
    //! @ingroup group-Group
    //!
    //!
    //! Example
    //! -------
    //! @include example/negate.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto negate = [](auto&& x) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename G, typename = void>
    struct negate_impl : negate_impl<G, when<true>> { };

    struct negate_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    constexpr negate_t negate{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NEGATE_HPP

/* negate.hpp
fRyomX7H4r0x0iDZm5o/CjKnlR4ikRvxcXSfHBcK4QafzxnPCN5gcjxldjzlNUdIUPyOFaKvHTghHGEKveMMbccrnmP52yI1Aa/rEdrutK1HUoTFQU4C0YttjYcNCKy/hDd1SSCWVKEaIuoaix8QXTN+QHNHmOqvi1VRkowcYZaxIyxadA8VLay/Lk5FY++xWAdbzq43Dau3nF1A4bXvx1Mn0L26qwBqBGWWK5maUwnqNEznMEC4u8hAAMBvKnf5gX9Fl9+6+Evpciq6fI8Vt7fRa3TZfvbgVupwAXpcj2Duiuz4oGjH/x3eND7/T87PoedJe0lY/HvTQTvOtC2AIpZ+BjeCYjVYF5j5uwfAifP0sXFRWBfEM6wt8FdEAGc/A0hlJU+PN+FaITw9bt/RBTVWCX576hHQH26S8B0eWz/aTEgsY4dbtOgeWnRc/ej4LwLGVS62f5LM+JhBho+Bhe5YNgqRTRdOVATTBSxN5QB9JEgACNRNAxKsfMDfPNtaDZ0DhhLDorapE93PVVCmo76NTbhaQ8JMwk84x53RFEMxqBFTNpHmM2Yu1URXN/TaEKzXNsLM3z3c4LD0GlMQoNc4gmpstGJHlMfefekkROzC1T3p4ddKhEXyT/GS4SrUGLLCWAlpv7m+UAN2oQbswrj6cTATZaXOUVdgLgoGNCIReTHnUCfc/0kMzgyOsZpfZovQ7g9rO+PnFEdS65Zd2cMJUU1kFKQzkVHUzK3ak9N4SqKnm7slEUYSfqIUgiDiniz75d5JciIPORcRzi+hdzJTnMxUoGUq0DL5zPUFWqYCmam8viCufmw8o7KrkZ2gzuNBTJOCKZscSO+RyMODyINk5m9JoAii+gCu5wFcX9vSyROpfod2rS1YqE2ZTEyZ3BbwvChuPujiSNRSZUyXD5Jw+vp+EoK5pk48mPmba9pNGnZ44Zp24yHetru2yUrgVMjsgRi1rQtUkQHpRqPYIFjIjYYQEHT6Z9LoX6wE2XVmdR0RxQaOBPPOkXH13njMwlrMD5O6hXrI/akrlK6ryFR3JouKKjXXsRm1EUyjFqb1pVq/xli4UwbSGf1aT/3ibwPpkvFCq0wWssVhHLJAiiRuUPds7TRT0kTF20x3UoPjrGyuvyXenc9UCJ3MNbcRfGsj8XOuiaQ+vxKzdlS9aRR1x6QiAk9O4ykJMfUJo2RvTfjlyNDOpPoSXlfUzWroM4F2BMjKyyTQpgBqPKFgL+LH7h7OZfjcjU8NPnPwuQWfG/Epwycf7cvFJwufQfik43M+Pufg48Lnla//vtAf2eGXWmcutcLiV7NrX1gUw4osdKykls1Vx84zv7WpUW3EPlk7wMb1TTedXGPTvPqf7F0JYJNFFm6a0EaINGjAiBWqVrdSVpF0FShqC6VF5Qi2TVBoyyqyP1E5U8AFy5GipD9RZEF3vW/X9VZk64UtFYoXXqugqOCeUwuKx3J5ZL/35p8/SQ9acO/dQJr/n+PNzHtv3rx582bmLJeTlsbHBBFR3+y2Iu5clzPbdVtdLpKUz/AcyN7edm4r50ZWLMvhmnWnBxG5cgG8XMuWcDyfetopO1vlnixzW+NyT/IYuQ9Yt3dU89bVplL18vH6mInZHx205ihYH1PSoubebFW2Z/tBa865R7Wo+UiPavfBcY52F6DybeM8rxM4H9oa54M6i3Nk5ToTnBwA4dwDDg3n+pj+bdQ8y/PpwXGOEjNb1zyjszjXx6S35hZ353HuahfnzvZwruqNgwQcrWtu7yzOcQxBq5r3aYHy+JycIGcpZ2U3ti+RV3dw3uwvEMmjko3zW3d7/hqeb6sIew53k+x/8Yfv/ucTA3FiwXybXkoHlFo=
*/