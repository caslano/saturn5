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
FDSamldrYoULU/iX5aiEV/huVE+zn6MkXmrJN4WULXPUZem1rZVmIO4M+3tqY79kXVq1N0NZlq62V32TuWU0nRX9eGCwJa3DfPOM+cY2NW9OnS28bE7wLbibDiDm5axW8uaASgkqPe+nwu8sNhWLLbLmQ9ExJcerjSP2+uaTj6Q/N7zCpeSlswc7BUNVQwaaSNqrTlMtEofUogVrYcFa7DqrFthTNl4PkMMzJduWlGI0GxZYitGU+8l4EDSuCfvi87Ik2/1dq3Vq19JOcpWLe0qteg4XOzUkfXD1Kj1DoT2ggIAhKLlmJdei5FqVXJuSm6jkJiu5KUpuqpKbpuSmlyu5GUruvLrcbKU6B1ChVC9GImuIyBiF9vcADMAaDUlnqw1KoVkptCiFVqXQphQmKoXJSmGKUpiqFKYphel1hRlK4by6wmzlMYL2GEHTYQHS2U1h7p9qUB7MN/Oo0PEoh+eZ0aKbZ8EoIXm4jKDkJZK1ONkQybv2v80Lw189cXbk1B+hMPY7Jw5n9hO0B+dZ/3OmdTGZSs/NVKyehm5pWmI11LaCGiYoS8xqrjk4dlvOYtIfxmxrmWW2wdtt++nXElzsZq0NwP6LzUrCCv8mi5p/vTJczc93KqOYsB99Y65il8CvKqJmW42MuuwFDBfWYlToCQoT1ObVfPgDlsI7aLiNbAK6+B0xq5KyCPrDV7LetwBYkUW+xFCiGgF/
*/