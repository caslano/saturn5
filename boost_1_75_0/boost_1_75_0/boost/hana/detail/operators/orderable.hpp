/*!
@file
Defines operators for Orderables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/greater.hpp>
#include <boost/hana/fwd/greater_equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/less_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct orderable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<(X&& x, Y&& y)
        { return hana::less(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>(X&& x, Y&& y)
        { return hana::greater(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<=(X&& x, Y&& y)
        { return hana::less_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>=(X&& x, Y&& y)
        { return hana::greater_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

/* orderable.hpp
YziEPpXyRZIL7fyC6GIRXNIXkiq7zkvD4+qGxX0vFvfk19+U749icQ988U35lsfivvCNcRfE4g6eGRa3QCtqmUferGYhYCyxykHJkMunTTzRf3R6p3cSScRrTHhNo1Ue8/q/mSxyUVRoNi2lhrPUbvTTdG03imdNN7bC48ht0DVGksNKBsd9eCes2WTj0/humF1ALtY/lUmF2kz23Fv5cFeuXTkyARVySXiiCs0QX1SBYsmdDhKHSlb0L0/Gkv3o4MG/FS0K2dqh6Bpzbi5I6mCarZX/Bzngw4M/j5ph+MCRZAQKdjmBT4W+v9qcF6LSGS3tfK2j3gpwu5/uMguPmsycbx/Vsmf4XQ+FE8VSsxBIszXyfaTMvOc/dLpArr76Tu+SLbl+ePdat+T+AJ/TtuQ+g89RW3IBpQD//RaHGU/shMvhBe2Uhd3wgspL+C54wQWb8O3wUocvi7bk/kjJ7MdKZjsNLLM34clPg4h+jDgeXtDYT9gCLz58SYIX9OYrV5nJYY9Zpf9qscwctsiPmKC68VaB+eZqrGSrvA5mxAPYJIGrNE1iDWypMWOzcNvwFEvahvVXmyzSl6DM0rkhf5UE82A8T5aMvekxeF/tMUgzb4AnnsKsvTWyyGSBQe5Zuq+V95YEn0/pW6A/6ugyALTGQnI1tio5Knw6hd7CtwaOtlqbyIgeiGtr9Y6xfkh318j+owfIAQXxoxss
*/