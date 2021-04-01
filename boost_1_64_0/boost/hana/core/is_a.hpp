/*!
@file
Defines `boost::hana::is_a` and `boost::hana::is_an`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_IS_A_HPP
#define BOOST_HANA_CORE_IS_A_HPP

#include <boost/hana/fwd/core/is_a.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // is_a
    //////////////////////////////////////////////////////////////////////////
    template <typename DataType, typename T>
    struct is_a_t<DataType, T>
        : integral_constant<bool,
            std::is_same<DataType, typename hana::tag_of<T>::type>::value
        >
    { };

    template <typename DataType>
    struct is_a_t<DataType> {
        template <typename T>
        constexpr auto operator()(T const&) const
        { return hana::is_a<DataType, T>; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_IS_A_HPP

/* is_a.hpp
0bbDmrmgciq6Xj7T0mnm0dvx/OS41wVh34uxq+YBHfzB1CTvEGVgrgMMI3zCaD21u0H8Hdoa2TCrk21PAJQsZn0Fndo77tT0ejufK94PLUC6VYv/t2ReXAAyBzNA4ObQLlTBpYx/7193ByzUUc2KTEIUBsm8a36x+xxpSB18nt+HyWEK2hpCNLZFr6eyFGX+gXezomlNSUJ+Fhm0XLGkNrOYId/nzOg22QJ+Sr9V+8ZeSKnX+GDh4YST+M7rUDi+aEdKS8iFNnawQfcWlAPV06/fjFyJMgHqLpmOtLQOh3SMW3FN/PsLBugMOkA6Vy4M1YLke0G1Y8vCzE35syRqetCsXmhxwsqTX5pPqNr+2F4pfIrb2r8qkFNj9s7clHPxdbrRy+C4/MVohSY4R1d4duXTFSnud3HBeDFe44S7HPl2nM418z0/CB4BUSGGAkewHabtF7iFK/qXjncxUoci9hi8Mm+vwclswY6lziVPKC/Bl16oWLvbwmcGFOrpy3CxMvOd/kZ+hASoE2eDMdjkWvGRunrzf7IfrS+qNrh7lpTdZ6blk3jQD69UVQ==
*/