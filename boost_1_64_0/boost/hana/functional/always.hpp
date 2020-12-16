/*!
@file
Defines `boost::hana::always`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ALWAYS_HPP
#define BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return a constant function returning `x` regardless of the
    //! argument(s) it is invoked with.
    //!
    //! Specifically, `always(x)` is a function such that
    //! @code
    //!     always(x)(y...) == x
    //! @endcode
    //! for any `y...`. A copy of `x` is made and it is owned by the
    //! `always(x)` function. When `always(x)` is called, it will return
    //! a reference to the `x` it owns. This reference is valid as long
    //! as `always(x)` is in scope.
    //!
    //!
    //! ### Example
    //! @include example/functional/always.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto always = [](auto&& x) {
        return [perfect-capture](auto const& ...y) -> decltype(auto) {
            return forwarded(x);
        };
    };
#else
    template <typename T>
    struct _always {
        T val_;

        template <typename ...Args>
        constexpr T const& operator()(Args const& ...) const&
        { return val_; }

        template <typename ...Args>
        constexpr T& operator()(Args const& ...) &
        { return val_; }

        template <typename ...Args>
        constexpr T operator()(Args const& ...) &&
        { return std::move(val_); }
    };

    constexpr detail::create<_always> always{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

/* always.hpp
4Xfv+hJ4+9iErWMgQMNv7w96+NAZ8CHQKM5rM83bbx0WnDb2ZEVi/bErqJeMD2TjR2Ea0YmsZ6QteyeojEGsPIftoZLxsAb39w+LhFbrOkmDDOHLedxcKQQ0bveP2sLi2CKV0J3wARqpSIiidkaFxn9qM+L5g9bwGwCayo5ZWnDR9ZpaK+lH3aDDjkiTLk1iXfbrksdJqSqsLUeiQVVs176/wb/HETty/Gah2DWqLpavrMDtOkP8zhGfNIHcwcflx6U8o6M290l5cTzdu9dLBK6OvRRyVhcEz8bIU0429mb1xNS0TjGk/qLe0B2TqV176+bWb1MVpeImC8X9gZjw64NrxP417r2AlClr+6j+H/UZ+c2XyzyPnrzE4MbzpfEgXO4S9eHK9ymSL1JaI3DMOBz8szxvOlXDYaPA70Y9AbiavyF4aVbWhjLqbgN8IfDtknf1KMD2ATZ7lIM9UWBnEN1lAmsh2AsF9rp5DnaFwJrmO9hbBPYkKnuVwL4vZdtlHMcvGM3lRg9kZ0qlycpotjyDf8szkaP6/tvRqZlRNSrYKagkyulStnRX/kBL2yi2vEcPbWwdzUzl2ttGO/s2dO/trrv1vjW0VylnbVOjGA+19G7ITutchke58mggU0aIZrQXqZ7lqXyugAU5qtJWsAHKCGcwscY/JI1sr/aO9o628zdvGoUOK5u+gXTMNp6OysGERLA5t0Ft90BWNkzntG3wV2l/fbZpfe9dYhroqdMbdNM4pTK621g9werwOwgW7psLCUnbNz19BIrs3BSdCHUOjSQoJjPFicx0YbRQzE7Omv2P+fPM91elRVqE0qlVuIOteaVkVI1HpjDDcwQ+g+7IFKamGlosbOxoT5D14dNSg72WDbeIDFQbUchjOTOIxvW7CSjppgaquHulRg/c/YKjmZnJqfEkm5h13Ycwh7DxoIsP5Gd69o4eaNuwSdHUHS9jHibeVVS7QLnOoRGpkFUC4si5wgHdj2LOiiC6LBVMF9BaF1x0+NilYvUe7R4WijmbOFAJt2DiXYokiAdD5sBVsrblOjf/qxFPzlVTXj5pDjGYAyXDGIlhkA3VObgHW2ulg5XRlubRSm7/XaHDz+DV/L+nyMJdLjxqdhaOWG6PlNs/VdM4H1lKjiAJXAPjzSqWHu7ADd6dgwjBjW4tIwo0AN2m1j/SAf/EpehuT/EjzmOscZ4SNBmwo6XMflSPCu5/ftP6YgnHITBGe9rw29u0fmcrftrncDpg5+H1Teu70v1b0/0p7Fn2DsHPUgAogK19XQbVOaz+Do104k9nJ6JdasfePH48PNjduaXFwNXE37sX/wXi3Sif3tM7AJ8e/z8wsoX+QyP2DoIMblFfDVSpvr6de7Dh1qnCHun+3uH+1EjndofpHcF75nCw0l3dW3dtS/d17+7uC5AN7RrQ75339W4dSg1dIhR1kQ7QpLp91JAaSKcG8O34B6ADCO0M7e7t7DYUXRtbzT/Af8MqfEiXOp40tLV3RNWNvnd1a+b09vR2Dyn+dXXvbmmOWsBffOCuQTBLY/oM15gVzYea25tbHbS3W4E2N0sdoGgxtfQODIMa/8bORlevHpXt6HsfcipMremtu3r7upCNtL13oDud3rK7cwSZkcNdLZuGRvrrbv29lX3U1tXVq5g8jFq2mP9CWx16qLb3msHo70IKhfvXcG//rj7F/SBssHuohxB7dg7tSCGpBqxVwIiFGqkb2dE7mO7tiVc6oIdVoXFnfnq4a4f+rJ09Pb2dvak+83WaAVu7R1L6Hz171Ufot5dSI92aIA2Z3dLVBZne2NK6Vc2B29x379LC3j2wO90z1NsN3l2yZUhffmvqgrgMdG4=
*/