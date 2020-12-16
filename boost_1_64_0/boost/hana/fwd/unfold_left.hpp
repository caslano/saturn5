/*!
@file
Forward declares `boost::hana::unfold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNFOLD_LEFT_HPP
#define BOOST_HANA_FWD_UNFOLD_LEFT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Dual operation to `fold_left` for sequences.
    //! @ingroup group-Sequence
    //!
    //! While `fold_left` reduces a structure to a summary value from the left,
    //! `unfold_left` builds a sequence from a seed value and a function,
    //! starting from the left.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S`, an initial value `state` of tag `I`, an
    //! arbitrary Product `P` and a function \f$ f : I \to P(I, T) \f$,
    //! `unfold_left<S>` has the following signature:
    //! \f[
    //!     \mathtt{unfold\_left}_S : I \times (I \to P(I, T)) \to S(T)
    //! \f]
    //!
    //! @tparam S
    //! The tag of the sequence to build up.
    //!
    //! @param state
    //! An initial value to build the sequence from.
    //!
    //! @param f
    //! A function called as `f(state)`, where `state` is an initial value,
    //! and returning
    //! 1. `nothing` if it is done producing the sequence.
    //! 2. otherwise, `just(make<P>(state, x))`, where `state` is the new
    //!    initial value used in the next call to `f`, `x` is an element to
    //!    be appended to the resulting sequence, and `P` is an arbitrary
    //!    `Product`.
    //!
    //!
    //! Fun fact
    //! ---------
    //! In some cases, `unfold_left` can undo a `fold_left` operation:
    //! @code
    //!     unfold_left<S>(fold_left(xs, state, f), g) == xs
    //! @endcode
    //!
    //! if the following holds
    //! @code
    //!     g(f(x, y)) == just(make_pair(x, y))
    //!     g(state) == nothing
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/unfold_left.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto unfold_left = [](auto&& state, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unfold_left_impl : unfold_left_impl<S, when<true>> { };

    template <typename S>
    struct unfold_left_t;

    template <typename S>
    constexpr unfold_left_t<S> unfold_left{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNFOLD_LEFT_HPP

/* unfold_left.hpp
z29JYqbGoOeB47dinPOQ8dswxHls+B00wjE6abb248gS8xVtIP0hmk583dGLGqP+Brgxr2dFmyJRP40pzO0IYoELk3tO1G+FC7N7XtRvgwvTOyYhB1yY3wujfidcAZ+/KOpn1TCfvzTqd9OmxOeviPo9tIn0YYHxezGvj/HPwmw+xt+MqXwMz1SYx8fw3IQ5fAzPSpjDx8g5yR8aM38ROxrGzF/MjsYx829iR2TMfBrppBKhP/z4havorl/Nf/u4P8R9Kziy8JdPQEV3URbUewkZwN808mvsLgrofrPsw+ZSJcF77k3HpJihy/++nzz+ZlVrt8rbh2w8+St0b6lOe4T3pmEM+PimcBZPJmhtHQgQ0AyA9YCrxRkfYKwslHphq7OnTqEWWBrpjx91D1itnYzski7AhbOCsKCCPPT7b+yWt9/g1q++faj6lPfXjlqrh7kP+hwCit80Jt8HXW9isSk0OQVcuRtQV+xiezG2L4OT7bV47W0La26HZ1trzW34lLTs9zT/9csduRtSWp3ksWAhf+bGrB37LCkLnRR2QWyBdIDTBSJLhpT4OxgPBHw5bCt7Wawd/ZYFPR07LFkyTMsqc8v+85pvTmn1bgPYPjUL1dE+E+VMe0yWuZyqpRzdzGwfNoHcEzzdZony0x95+T3d/hQ9ODrZDXonu+EmvnTdmkd0BbSuZwXdCsghQNxo4UsBeQCoc3iwUJz3D8zbrH3FXtmBOrFwA3u16l7T0HeukV4r2UsqIwVqxXfJF3IJCkWtj+UlAC9cBm9ZXdFyoMi+kJ7+lZ0Vse5N7qvy7me1DvCt0loAcD6XuLJwxT7OdrnuU0R5v0aAEM8y5iYdEyGMi8v4DDC41gC4TUdOJ6SVkffJaI/oGE9A2GUWt+o+WQF191fMl2Hn6ph6wqRwKjOeTSJLamEFVLWKKokUerRKvPXSTxQV/Yu9K4GPsrjie5EssLALrLLAAisGiBI1mIhBrkRCEpHixri7UCChivbrShV0F9QiYBcq6ydqrUe1WLVaT6y1WsWTQNCAJ+CFYhWvdtKIoCgJomz/78033242AbHa1v7a5Re+uefNzJs3b968eZMBkTeoOlMMpOQQL/PMpeCPONi5qc2wLKCYAJf/8UbEtOmlSa1ZvRQRGzZmdU+NeHhj+34JiVsQCmc594YcwuUI4tdj+H34/SPTBFs7ZPr003bING5jO2Qq2NgRMh26sR0y2Te2R6bL87ahQmMBaTqXbgm/8r24Jfz9+bGsCHc2y2x0Ye8LOKzu21ucN9DVvC/owl7a+3pdVxgU3F9+u8pvy8z/jcvL/rmfwgKQce951TK+/xRN02/z2Cty2eWsiQn6iPVvBbme2rTm7wMvW0vaTSCPu7fQuRARyUFrmEza6iWhPHI9AvPxV+J+uIliqvSnG8fzkpLYaUV4EH8zq0gyRbFzfrKC0bYe1poAmvvhneHljzs3ej3SlPQRDakUM+vEoyXqwbD3liFBCilM1AeDohNCoPLx+GLkSuy0VRnFUAGjhVibLqCKC3htbbqA07iAdWupAML2nfaq5Y+3opx0GcRvr80G4uq12UAsXiuBmLOJgHC0BeKMdkBUtwNinFGA4AI6AZqqNkAMbAdEt3ZA7F0jy5i5mcrIaQvE22uygXh+TTYQjxkFbEEB+mwcYOzMzQQkJG5QhSyfgAJ0o4DE00EQkospMx10Ph58mep3tq2/FtGkmIfc4SC2KDViksxOecvWqPWK6CPqjObTEkVPQBNZkqsXRDrQuDKexa88jd3L2D2F3Zezezq7r2L3THZfw+5Z7P41uzV2r2D3bHbfwu457L6d3TF23wU39S/aQTfCwqCs19YDbF4=
*/