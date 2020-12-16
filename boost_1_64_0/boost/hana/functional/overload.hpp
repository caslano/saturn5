/*!
@file
Defines `boost::hana::overload`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP
#define BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Pick one of several functions to call based on overload resolution.
    //!
    //! Specifically, `overload(f1, f2, ..., fn)` is a function object such
    //! that
    //! @code
    //!     overload(f1, f2, ..., fn)(x...) == fk(x...)
    //! @endcode
    //!
    //! where `fk` is the function of `f1, ..., fn` that would be called if
    //! overload resolution was performed amongst that set of functions only.
    //! If more than one function `fk` would be picked by overload resolution,
    //! then the call is ambiguous.
    //!
    //! ### Example
    //! @include example/functional/overload.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto overload = [](auto&& f1, auto&& f2, ..., auto&& fn) {
        return [perfect-capture](auto&& ...x) -> decltype(auto) {
            return forwarded(fk)(forwarded(x)...);
        };
    };
#else
    template <typename F, typename ...G>
    struct overload_t
        : overload_t<F>::type
        , overload_t<G...>::type
    {
        using type = overload_t;
        using overload_t<F>::type::operator();
        using overload_t<G...>::type::operator();

        template <typename F_, typename ...G_>
        constexpr explicit overload_t(F_&& f, G_&& ...g)
            : overload_t<F>::type(static_cast<F_&&>(f))
            , overload_t<G...>::type(static_cast<G_&&>(g)...)
        { }
    };

    template <typename F>
    struct overload_t<F> { using type = F; };

    template <typename R, typename ...Args>
    struct overload_t<R(*)(Args...)> {
        using type = overload_t;
        R (*fptr_)(Args...);

        explicit constexpr overload_t(R (*fp)(Args...))
            : fptr_(fp)
        { }

        constexpr R operator()(Args ...args) const
        { return fptr_(static_cast<Args&&>(args)...); }
    };

    struct make_overload_t {
        template <typename ...F,
            typename Overload = typename overload_t<
                typename detail::decay<F>::type...
            >::type
        >
        constexpr Overload operator()(F&& ...f) const {
            return Overload(static_cast<F&&>(f)...);
        }
    };

    constexpr make_overload_t overload{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_OVERLOAD_HPP

/* overload.hpp
wm5kwOb3EtOVJbGP7ovE/74aMm2iUUv2Ut09e9GvWMUeX5W16S1sqY9KVT6thjaEqx/dunOe3hPTqOFCpBy3l3zH1FAoKmKPwWq8Kms3wEQktRMEoieqbiWOvqySqrvjrNp9j+5YFzVlIIeqey+xqndAYnQvIi7bpmEfzVeZVR72L5O8iakdXF/YkoXU2sEyAlkQ78CUKVoI+ZDAIoj7Fw35YYC4zDcSojgKQbyNk/bHcGFnNxBdRitJal1SHRzgZqr+JipVroTA0UDVcGwvBm8Y02OlhHU6LVl+hqOvtRerlaNEcmqXEOOmiWn4QOwZxIhla3RZpeyIgSIugCxdpytrtFGpuJ4COzMFtqaI2MegHtW8ay9++cUv1B1766hSuc5iD2LXDn7JfflYYpzxEnGBT2I69oNA0ZGcVxwytx+KQT871V3MUbCrncpmTXMUv08G7V/uj5vFWH+cAmm7xO9ImoiXTVU2sgT25SeVGXEpBXmjTybYaH5fCRR6rWy+u5qenLU0Gva7xXkt105njpGA5WLgDMmLByp77Mf5jPET04DzDxux4B8lWt4XYtWxh6R/aCq65nB5Vgr9z4n+bpcEs1ne09hRE6eI+FYtU+5fpWw6cB/1sBM/b+6PbP3AVkN3rrEa2h9lKX4jbNE31Mv4bWzxsZqPVamSKrmbmlw3AnvmGfrfF9EN2cj+uCPsEw+I6f6832q80V5L8atqrf7ao2/4sv7Oq6xFuqptt1E2+aT4TUTzGEPZOw6tOp0ky0suqpG+2B/DRGLRDflqs99oYz4q+zYs6+Fs9h51hdjeWX3r7SOmzpTldtZYuby3FL+PYjCXC/IQ5twPc9bfKu7f3hKyTUnOg1siGVUXm3iMuvqtoBjcrKYBu1ZeoGVf/BtekmBzA2WzbFU3aSD2PlbWUFbiwLfYR1fYb0Po72i1kbhWNYZbiPPlHSoLD1O1DEZ3IWB1R1U7OFINlduIvTAYez9G4MELld0+JpIbXVV3/1DVHT9ddRtzhNs3Rb9yYX4BS2spa41ouaNVo/0p1fAyE8Ivv7rq2Ij9sU1lr7jjDwfgz3kl4q+/BWahD9mbCFgd1UD0R/AGnE32mMOZTMUZejnphso+c+tuqSMJyp8xaD4GC+FUUbNaIUEMxg/C/rjBecrCXMvRUoJqDTDXewaJ5BZly0Zwf3w1hx/63xxJNRRw7KDATHq+cYVImpeS9MWdlOr1TlKloto//yYuFSM0sOuaqSyzEfagN/eHiRqPsVa273WRlGfrrvVXF851UnbjQu6Pb2Lw0UIgdJ5qLCimVIl4SX8ABSjtLPeHhxhUWm8mfthCn8PU0IwTGrrJT4WtwYb9sEfy/WzL/mWmRz1QQ/EFTcUvlPucoy/gDwJlj0vwI+glfWooe2CiZDnaW+0uXyH2+8YpNQ4xAk+Kbn99ge63xSWRVfKrgsQ4znG4/Qznn50GMbawmiz5xkL97apsq4Gii6mrJq8/kkBxyQIWSSJ56qa6Ps4SfNA7/HW1lAplie7urF5eGI+9HyWm32+JOISRbN+G+TATg1KspoYpysb1YL9hfB+Oxn+wSGBNIwnU+Jx6dOqz6l6ur4a25xFYOlGIhdiwZk4aDQ9Wp5cV+j3geiXswY/cv9eV2lqB9bJNslxKV1mYh1KhS4zFr5lAVRx5vRuLQex1NfTihMoORquNAth+1X8oZfRBDOK6Sdxg3AkdQdhNVrspTYXotEOiLWHjpBZUFzoXVY+S20i+nlMF5uAyM7hiX8ap8c+Zyr4/qzZsk7P9OdgLSWJV4ZZAPsqexQqcuiLiWviWStgrtRREGjbdmDSVTS+o7Pr8ysZglXdIVl3bXtirhzQ=
*/