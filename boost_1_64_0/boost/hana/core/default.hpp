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
D2JLHK19DVtZrHVEvkZ4Jk4r4ol1YRYsdsnPBM3LNtRZ6Udzqbtaz4iRBxinFFS81DX+FuUwbRM6kY9oYohz2fJLJbbFtSYpRqAuOpIoUv0pH5VcOSQYHlShjvUS2HPJFUkENdENTN2Fgk8TVmQ7GCQLuQdgdkQHFOUwViax0D05g8wSsj8vo8aRRMw9Rn0XNThGI8u42n6hgAaVQPX6gVQvBoh3zQuU8zjEIehh6xQ7ylY22RKNlQyhPfz4/D8UGF5NKxutT0wPbn462ZfRb79IAez4yJm/hWcRtubbkEXMzUhkGOeSz+LTiBIvykKgrOzyvw7TyICMXgDcj62XIMpJ5eZMCVZnZ8VxD1sMZmvwTt0r2ZpW8+vyL8EUmuRqHPpiTnqcmlyO/yHTPx9Eftzn0nO0YrRHZbFJh2RbyGleUawjCZdewnaIZUD1lDhMyGud2z2diALlPY05qhFMkzKTp7wSUIJn/6gkNPsDtdTwfS6aKN71qlVobXBkSunyjETlUoHNczaaEFfLkiuBgBMO0BeLU1LbP0Nv5tNPUikwzW935E3wTlHXfA==
*/