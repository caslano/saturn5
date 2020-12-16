/*!
@file
Defines `boost::hana::max`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAX_HPP
#define BOOST_HANA_MAX_HPP

#include <boost/hana/fwd/max.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) max_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Max = BOOST_HANA_DISPATCH_IF(decltype(max_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::max(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::max(x, y) requires 'y' to be Orderable");
    #endif

        return Max::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct max_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            decltype(auto) cond = hana::less(x, y);
            return hana::if_(static_cast<decltype(cond)&&>(cond),
                static_cast<Y&&>(y),
                static_cast<X&&>(x)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAX_HPP

/* max.hpp
D3Car83kIJ4BH8pNPTQKcw+CqV8zYrEzrD0THIbkfrFZszSuaQMOPVMvbmAdUrge0IaBfJ3to5Mr3dNrUA4KzuNwfA6I1jEeJG04ar7CU+2EB24j3sdjO8HRnFNwDx2BQwwpKT+uH5dG4FQcUeesglltwxAxMF/DbI7AIMARpzagdnaCYIajPMBTGo/CaMOWH2CMBN41gbax/R47UgePuXQhHqc6ywrmnAlD4y5tyGWlV54+AoPIYjkGWAoo1u4mSvddErBIJLvcP6tsC/zsvEnm16MLigv1jr02ITtrTe5QfucwtJCAGW+JwRGBBy2kG3O/Sm2+vbxK10vV+QQ2eRZQLCtc+7c6Zs51eBeRsLOOPsF1d4Qob6zBj0CVpf1X32lsQjQchevRpl8sd0M4gIqdU/FPKgydFbWPr4DD2BMje2KZhOV/lzMYG9vJZULZ3AXsGzjhcygiXNmJS2uZQpXA5tMYJX2XeNiTZy3tPNJVZMbNI2oUJx6Jg7vI6Ff7cQe65EnxZm1f/zmOa7ooMxc+bFwYh6BwH/3WnQj+XfsZ/AE4ZHDJFDfzthTeu6k2vp/BTQImwMVZH9cVFw+MnHOcN/gSWzjIdivPyywER2Loaxmqlzxyiet+HJpQ8spxlJa4d1eUYUgne2a+VJ0XmtdxYytMk6osqqzOEUs191MMjpI5CLPEV6fiNWKmL3B8hZUESOvuYDpIE8tsQqD6/rtW3wMfNxECTIBxfZeImtg9NVcfz980mUg8vC2xtVQDbSuZ2bXF6AA9jh3KOIKvcJZsA3lYKvrV3cQUoQMQPjVYbl0DVw4HK3KX+oXDcK0BFZo+DlODJ+J4XJydpWmROGWiJurK9paU53rFAsLtjSUwsMYJPPq8lOPBcxlZmMRlCDzHSQ8hXoqzE9OW3GN6pqF/Db4LU2YOW/QvRX77mOX8rVWPatL4OWapOZMd4nOmENeKEOltPaZ9xvJegx++5XhhWhWOa8iCeF5olCVoEfrA4uwucFwVXFmhE7hpYR1jIW5NlF1zJvTjf7C2HkyyMi9dhKmx0D/YxUp2OY3DXuYg5bdvBTaisLx2vv9LW633YWIwIYgdnDaJwPpmvtEhelun73sYH5MMZzMOLlfiJRrKgS5vUFC32lmOA4XDGNccnQoDt0xJ3OSIgjJ7l4BGtN2WXcDD+xLgthGaErURkYhxHDJebmPf+FiS26Gsf/XLrL0U59Lbp+PzsMAjboh9vyrlDVXJa25I368mvz8QcVsP0t+urvJq2qo+xd6xHA0ES7F3wreiYCnuDoYshWLp79eiuD78H89rNjiurfOnNrDXrXGUyL4Jc7j5fn32HW+vaxw3oPy5VfYgBYsy3bcAsqdh91C+2tRXsJQLlt5tbPoHuvhO4UwES3lgycwHKMbuOjfo43tHxlpi4OBzXe8jlzW9qTtAGd7XIwejeluvLnsML2u9If0kKkMUGJiDFjeV63wOvG4rf8ezUAZLr9YH9F6gwHm+hbOd/+lF7XLWKPVW38uvBluqQ3tNmI9q93RzKn/XNVg52eSq7PXXasrIx6DL7nIdVibX846mOdxNZcb+til/xB5WTttWXDPR5Wf2opzuFPCJo2hfuBnK8ebaGbYRUmWrtxBlokHAWT8w2JTdRpSBLDk9O6zej/fVZf31pp5qz/k7iTKhtGGoa5IYOyq/eGdR3gyfegdx913xXfkaGfyJSfGdOg540CHdxr9TI1js2u++L2R2sNVnCkefzyybtoGPqIvKyQJrfnH9UdCsQqMNcY67Ck5CO/akbhuu4sdAxzmpdefcA8x7Y66XJHZaWrYRW9bEAam15DyvN5kjbhUxZonV3Mxn9/rOLJs=
*/