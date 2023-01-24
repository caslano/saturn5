/*!
@file
Forward declares `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIFFERENCE_HPP
#define BOOST_HANA_FWD_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct difference_impl : difference_impl<S, when<true>> { };
    //! @endcond

    struct difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr difference_t difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIFFERENCE_HPP

/* difference.hpp
K8SZQWCcUtqfT1PT0kirBKWd69H57B2Xd6OlbZd0ozsoAGskbaF6TW2jdp309UV0qeCbDeArNyE513+NAwlQEW9TgfQWfgenC4UWJ4gpX/4OKVCpUABvrdf6dUs6T6JXuMJWx0fWJ46ScUnZ+gQ6DkbznAIcHx/v0feA4VrewB1tmqXYdVOpRxBhPsJ7G63YITdDAgcFrpkUydWqoE4KD5u9ElSIFaqTXQ8AgTwlw4o2tTfQ5x2iIaJQB0fnKn1ubCjdmN2G6IokXv6CSPMiC/KFACymY2dEVBJ7/t23RMjWLy8mDll7dhCYL7NEB8HBXfA2Tp8J9lz07ZVm81rFF1hwgFtZ1FAf8SoOWC+fsYu/7THbTPoSe0qmxleGQ+YH2LS/+5LmCFYyBM0PFmZJ4Q10zGuTwgF6yZTC6y4KR3ggMpn93sUtR8hWeSRShrOh5OQ46IRfTU4n6PKsNlx2MbVvHe1O7Vtbkdo/Q1swaGWFAHlqw1vVav9L9S8WnolnwseDo6H44bCY27ZOTMDPUPfYQAOVhVBvyURmhKako308YL9CIoSI2vOhEq4LjIWnKTAcntrAECjDzJytLQdwMHaLcuRtSIHYL1EjUNR4k+qLLfwHjShNlZ+S6a9cbnAdcypQ5rt4/TeKhogAe0RBN+hmec05Ul4z1CYtYkiP5TDTYe6oW2PahXebY60JGKiLAHA2ERzUJ0xUsUuF
*/