/*!
@file
Defines `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_DEFAULT_HPP
#define BOOST_HANA_CORE_DEFAULT_HPP

#include <boost/hana/fwd/core/default.hpp>

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Method, typename>
    struct is_default : std::false_type { };

    template <typename Method>
    struct is_default<Method, decltype((void)
        static_cast<default_>(*(Method*)0)
    )>
        : std::true_type
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_DEFAULT_HPP

/* default.hpp
7JLZNgwLillf3NAIbsi03HDFsAFxQ0FqTTeyhvuvVx1kIFUr5uHHkTfZGOZar0rHkqxz1pe/zhuDdd7+lOjzaEeRrjVjSF+1pmSH/sSrsZc9pT2Zw8W6ok/edUWfMjRY0SVpK3qlpOup68FDB1TX+anKWse0i+pOhtqNGpdMplS6iavL1lmywq1PH3zelVhNqUAvdZdiTa4seUVJI/B3aifCauEz0GwJhvziKtsSDbtuiU1Dgi0xuo+WYNSxVVU=
*/