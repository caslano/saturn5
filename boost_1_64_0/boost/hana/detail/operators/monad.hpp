/*!
@file
Defines operators for Monads.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP
#define BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct monad_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename Xs, typename F, typename = typename std::enable_if<
            detail::monad_operators<typename hana::tag_of<Xs>::type>::value
        >::type>
        constexpr auto operator|(Xs&& xs, F&& f)
        { return hana::chain(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

/* monad.hpp
aEIu/dp1vADmM/BLzRZ/f/6uYvyEQ8YQNBcz5FsSpFJKpFAO3mI+xSGnfevEtl/fuP4LeAp+CXXwOeBztqE7c4rWkzgRbpfS2cwH6m2YmpuZ7CazIQzz9m9e/9l+hDyF7s+C3janoHaPOkAi6HNFsdfCvK4Vpz6A8mznQ3WM6CjbotNvazbC3sk2jklts5P6gxb9lawxRMpe5F9+6IUMhMDrL/KSg7mAZkZF99G+QjJmoNZmqmQOXgi+Ec8S5Hg5Mh3X8sAxZj55arH54uNCEjGFEhsYI9T4Ca5jw/A6Nfpa9NUdfch/cHUNaYgoT45K4g/Nx1peSwrIexW9uKeqiOFVfzqrjARCGYFrdS7bsSM5isllevg+/C8VcgX7D1Rbrl1z4tX2nPuaww3wC0clo9Y1e2Je3t+lbzJOlIWOyChi8MXJ8MO7uQgAQtLCyFOCnhIJppGu9GtLJBk1YmplTsp5os6A5td8jCMsTX7q4fl/ZO+/eQbm4vV+uZlYq89GvfTaIN31C/qwFtmsncF6l+uZu/DYwd9Da1V9pLPBLVJoJwPeVZm1SUzv7Q==
*/