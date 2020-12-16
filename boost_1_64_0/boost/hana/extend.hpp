/*!
@file
Defines `boost::hana::extend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTEND_HPP
#define BOOST_HANA_EXTEND_HPP

#include <boost/hana/fwd/extend.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_, typename F>
    constexpr decltype(auto) extend_t::operator()(W_&& w, F&& f) const {
        using W = typename hana::tag_of<W_>::type;
        using Extend = BOOST_HANA_DISPATCH_IF(extend_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extend(w, f) requires 'w' to be a Comonad");
    #endif

        return Extend::apply(static_cast<W_&&>(w), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extend_impl<W, when<condition>> : default_ {
        template <typename X, typename F>
        static constexpr decltype(auto) apply(X&& x, F&& f) {
            return hana::transform(hana::duplicate(static_cast<X&&>(x)),
                                   static_cast<F&&>(f));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTEND_HPP

/* extend.hpp
fEUbHxzMTvYlxL2npx1s0M6C73t04iHhfgfy+ee19t6E3fTyyFbnLDyitXdKEcUTPbKHJl//QBtftyJO6Oqsz3v929o6nFHENdb5sPucn6W8pOlnjyL6KQsVQnx8+w+7tPZ+roi5rNP9nOjr596brtUJ2Qss51baI5fDNfsQ+pYiqnWySX5fH9bKYYE2Kx5Z75KDezx+siI2CI/MNv7GMPsJ2Tad7OuXV3dq5d75z7L2/yIz9ivipzrZp17/cqqUyeeGaUI/hi/kaXsFsrm68f3+jawVWj/fU8SaiR7ZY5e+OkvbR79QhGWaR+Y1teJbWl/GFPdzKk3WGPDrL2nl/qqI8glS5n7Wtv2D4AitL15eIpyyMIG49I3MaVpffL1EkZAy9+HxcHQ6fVp8/LzEHZ3sJ59Z82dNNslLXFM8MuXn387T+jLZSxzWlevf8KnfaGvr7yWm6cp1PDT3oLZvp3iJXyjy/5dY+Tdpa/n9Bf6t5y/xb4vdx7/tX87fhrjlxd9YkenMQv4tohz+zfUb3vxtHP5txCfld3OiTA90yes7ooS8XiWv3/y7rOdikkxvPcy/CTSVv8F2mdff5/WF/K3SiTKtqJP1bh2U9Q18UX5X3pLpjB5ZfmevlM+sl/Vs+5K8bv+WzHdyuqzP1cffEkuX1yM/qcj622T57UkGef2GTK8+L/PN8edvLXxe5t/zupSf+LSsb/5KKd9xlf04wd/a+TR/w+RFKc+q5t8ae1jI1Ivrs1jKT3+S6zFfppfGpHzaI/xtuj/yb+OclddT/yj4W7Dy+uW/cn3/xr9BZ+TfqCuX8gMr+RsCG6X87O/kdb8tiuz3rxXZ7uP8G3MvcT4flemO2fJ6Tbesd3uMTEME5+sLBv4WHf92H/tf8VF5/dRP5fXLY4qsP8Qg052yHp9N1LNb8nrqAzLf8ljmD5fyM5M5np/J68ofZDuuL/JvKz8p5fatgr+NTL15k+vzEf4Gxwle/4tMt/jwNw8Wy3oORvL7FplefZv68Dz1hOu5k3q95Zfe/K18Wf469WVXiCw/7ROy/LEpXM8/SfnAJP7WXYj6t7JkejBYyl1eMj1wWuY7FyRTpYr1f5d/I7pCpq8d4348wN9s+7Ii5WYpP/uB+ht6PrLeYepzikxnXuZ3X5kv9vv8G7yzZP5FX5Tfo9fL7wk/l/ly2F878509Ja+foj5e7TXIfBupB9yfq7jvjqTJfBWfNMh2y7zl9YP8W1c/4W+sBPI3IxL4GwipMj39NVmfK9TA35Jn/hgh+/lb1psv8yWc4r5vl9enPcG/pcnz0ubnJct/m/U/wHmZynNrP+fhGSkP2cL6hCx345tC9v8FnpPH5fUKM/cRz0/Hl2Ua+APu70scV4lMXSy/tVSW3zNBfp//EvVlQJYbeIp/o6qF6878q/7O/X3TQLlMXR/ib8vWUj9/I/Od7JLyEB/Wf0fIfcjyZ96U6cEORZb7pGyvZFTIdvNlfY7PSfkNrk/0QSlf9I4sX7NKyrMqOK5vyNT+OtfjTZ7/3+f8eMvyt/7B0/3HVzn2cQA/Z+3QKFqKSkMUlUrzNCqmVi1GwyQMk2EYTQ1TqyZDCKGHPKIQQkhGIZkKQxjlESZTydRUKrVq1TqP1+t+388fve7Xzjn3j+t7fb+fH9/r6pz34Q0emTwsOCZ1EP9iv8V2uXEf7rsDTw6OjYsjwfXgbXn/4FiwM3g/557gvNg0v+0zIBJct7v6mWeczwTv53SSVwXicGLwfqd/ybPBcMO8jkiXpw/AvfnB66s+dv2H4PaQWHBd9TTiSPkgjuVvRPy2cnBe9JPgmPVN8LmmicEx9k1icGyr7sb7TuTTg9fzW/puvCE=
*/