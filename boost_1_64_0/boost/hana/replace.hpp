/*!
@file
Defines `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_HPP
#define BOOST_HANA_REPLACE_HPP

#include <boost/hana/fwd/replace.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/replace_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename OldVal, typename NewVal>
    constexpr auto replace_t::operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const {
        using S = typename hana::tag_of<Xs>::type;
        using Replace = BOOST_HANA_DISPATCH_IF(replace_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace(xs, oldval, newval) requires 'xs' to be a Functor");
    #endif

        return Replace::apply(static_cast<Xs&&>(xs),
                              static_cast<OldVal&&>(oldval),
                              static_cast<NewVal&&>(newval));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename OldVal, typename NewVal>
        static constexpr decltype(auto)
        apply(Xs&& xs, OldVal&& oldval, NewVal&& newval) {
            return hana::replace_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<OldVal&&>(oldval)),
                static_cast<NewVal&&>(newval)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REPLACE_HPP

/* replace.hpp
MEm8+8IaxlyJw3oZxNf9Iq2zqRonvMX6IyKyaIt2xF8c1SmAsOrEqE7EpZ1XZxrbo5TXMVnLVhuroJ87u2fG9svsiyMsCKX6xtQ9+HWnzdAtUy0W4pgEZWBW7w7ldbRsTS102zKcQX4Zoh921t+OtT3QNpXK30PmzyJqR/fqrP2CdV1fFEK1bH/+Hpups4iN1qcon+PGONiqe80mZDruoU48a7tiphRVWdRq+FZDETJi+JaIMR5p+aWud8Lxsoh1rfSJfhOx5b40euOvrda8VeEbYX09kZdyG8vr0fJLxhYFzAeX6tudiYN421F9TdUZ1/Air2/3wPpYVp/uROXDyaX6dmbqc6P66hZ0rbVxeX07M/Xh+ajCvgpwz0szcu1D8ewLfn07j4xejDSG/3O+n2hW1ycri8eOg03K6YVpDPsXYT4IUIM39qmU97LvJ//csLlS/C3wycKzEvOSjuv1o3IOLk8rAzCTsp4S2pdo34x8DqZNdb7v++iDChevwaU35X0k5Hkex1Z2TgWNEsr2n8rzFoO6aeMROI5fmJc/fBqUM379vUQzbmNoxkaq6/ffw/H0tIsO6AhWMPiMUXkFsoHI56d+HHojyBjxe0e5fim18ztQduTHmcqjnPPDXBahRLsJF+Dnc/mMOwZ2C+jLmvE8sEDqw99xPJdQSZj6f8kfYJ4f5iN+wCH5RJRlAPNvhMVRuKaVLdHPobEoTNgZi9EZW9GnjPh5gHbdcDeP37I6mB/Gds/4VUzpVpaVQxtIUBSCchZtKVPxs+jnlZXvGQgGona8Htk+jnuHd0TE6s74GFbp2kOu90wOVtrxqSycLi75s951FGvty3lfGunRuTTaJUd5Y9yXW6INU1ZeMMsbLnQp6F2XFM7x8KFs7l+ojSwqHtt/YJvZqM1WVj44PsZqWluf3+Y+vZGO7m5dbU0tXfXfysqwLuFtf9Df7CLe8Enr2qUgP+8iTl1v9UnpbT4x/QoxnS8/wJ1M6Yg7fCIlY/qVMN0Xm6ZfmaYvT9OvQtNdbCPi2d0XvOGnaVcb0u5C0w5FOlgIQxrquUJPENdu7pkEtqEt2FoCpohf3HdZDG/6ZVGFeO5nIKT8QqB5/AE0O4+a0jx/Hk3YZwNNsEPdh3bEUyta9U71WqDKWbgR2UOp7urBnx/j6dZWF6Y7SO9EH9pV0mNQHlywhkvtaol4uF4nDOVCSJhJtCpC/wZyT/jSGSrL6kY0Ba8EIxHoFzbxfT2rs2ON4bIrXJ3qhGYHQ270JEJs/SBgZ2+LX6O8OmYayWvdhHpDJJUxls5PKb0oWdvVXLfWMkdKHEMYYcBWGzrsG5He9pM88zmZ5s5FxFYjYo1+Lb3rgWXw8LCH58bT8Ey5KFzyoyrTIubENynWSAR+JfmHr7sA+R6YP8aKWT8f8vHN6HXp3L0ozZm9Wyc56Ouz51+qCbLR/uLwF/K9XfK+aTTv5vjwho4k35yxb9/OY/IzC46rrjduLvZmaPGYEYy3X79nppiZPrgUjPOQdgVMC4jlaPf9EMib+31S3CNYVzfMxwjnsvt4jvHMdVXJGu6851bR3xIxJSltKVjtOtkUWsQ1SG20uoLnmF6btOxdK2kq6YRhpmvzNbpD6QRn3PKmd9yxYg2G3/s7wFKBtgEIYESCXd9DDxw23S/emLXVMO1g3Vk+hrkbocrmNgSfojyO1z0XWmjJoHY430f38699PF/nXFZcda5jAXaJXr2oFQEMU9KSgo4UsSE/kdXrhCukaxg0EISuod6HoO0CpeUN64zSxlYiw6McSyUE547aMrFP5Hus317KEaONM4NOFppPVTZraEeT8VCsbtuSF7xlHrQibi9JS0wYMHw=
*/