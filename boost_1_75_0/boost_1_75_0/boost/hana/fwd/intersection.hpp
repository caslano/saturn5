/*!
@file
Forward declares `boost::hana::intersection`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTERSECTION_HPP
#define BOOST_HANA_FWD_INTERSECTION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct intersection_impl : intersection_impl<S, when<true>> { };
    //! @endcond

    struct intersection_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr intersection_t intersection{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTERSECTION_HPP

/* intersection.hpp
UPmjtJcuQKEiilirqebzO/M+53vI3rHesd3RxlOPtRnncVEkuXS2Zda2UKVeB24G7vbQ8/s4XmvwlWmlWMD7BLXiuuIoVa+tcTCAhl/MQo1vGkCWdZ/ZYayTLsB2wO5axe+c7vOPh8BpI7dbw47V80a8r/FOrrO1SxSZkGnXKNeQVakzgtWPy2SrwN6xqeXwvooBbhTS21prYTYW6FXjjvNfIaP+Tf/k909d6kKkgC4zw/IXPcOqSl2wtpmWki6w9KmCqfxaZ7oCXiRcllwRUOpzPHs8vMBZ1jLAeaaN+IU/671wyOdPSaDX5Tm5lCjTtE82aaha21zhm3xHUmmZUUCU1B5lWWXsY/4PJoNqiYL744VIIF6BAcG5QDA+u0bmTTGvduiRz8MpERNnZ9NYrt1UhF0+T0vduvWsEW0dW8Np/YvFkW2eQ55r0DAIl5TSUnvVJXN7lr9k0jVgPt3d2DFg6K7dlWD/6Z3VTLdvTlDxq/ld0N3AXc9p0iWzf+0WS1TiJ0L+UPcuz/Jrvr2NcpSFqHKuW8k/9ilv46q0EQXdld3K1hAbRwxnutADk+Jbh3xIN3KFa0LTUmQasNHtl1v8ueYGLDqw+fDuBP+k+mT16GKuYjuBNpykpwDxsXMG/9XNAHYBqrJE+ZsUuKO0UzGkrio/4czWY4hheDBw0OkuZtU1bBcmVt3sWqt4xvIsGJD+ajyxQpGdf/Tu
*/