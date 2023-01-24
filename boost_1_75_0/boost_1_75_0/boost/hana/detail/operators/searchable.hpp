/*!
@file
Defines operators for Searchables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct searchable_operators {
        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) & {
            return hana::at_key(static_cast<Derived&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) && {
            return hana::at_key(static_cast<Derived&&>(*this),
                                static_cast<Key&&>(key));
        }

        template <typename Key>
        constexpr decltype(auto) operator[](Key&& key) const& {
            return hana::at_key(static_cast<Derived const&>(*this),
                                static_cast<Key&&>(key));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_SEARCHABLE_HPP

/* searchable.hpp
S0yWcAo0GZ+6YRK8S3NSlEIhz1Eb7rPoLBvugn+Sjm5ybHgIARsQ8NUAAgD5pOYERA/RGUSP53gRDsCzsSrX69ggqpOzpdN0u9DURO6XpK2p1PM5VLJ+Dl7TkuYBLRitpL1zKSky7/t5NqbO2xCUzKDYgayBVpgNA5ZLHrMRHpj/ncjYNOBFgByEbjzmIRyPW3FNZF6gaY9zDSooev4MyV9oDG7JcdlhoPzsLXT9WJ67LIM/IWzyjqz6s7AH/ffpQEJe3EeE+6M6PKay4Wm3zoIlvMQGzenFG14CCBoFH5Ou6CfeEfQShULeD8qEmqgOGxWiTMIoyBvSyxYNa4C29ktsIjfeUdKBvPn4guaeBEAMWM+2C8pW68+x6WMO20AqG4q9k/Cyh3estGaxOgBsW4QDAF00LSyR/rBAp9uApv3ei0Jiq1xcIo/Zgdhc/cNlJot400/hP4yDCbU2HW8gH/txBQlP5gyINb2ukpJCCY/uouTtxZvh1GJbRNiXCW2cJn0GJXnS1ok54bmQDhO5QA/3m54EFUx6lB5FSEf0+LEAXvbLOiiKNJP+X9bjy6nwCiCsWBN1FUvX3hTbjU2A7hS+Bn0uHSaNuQu8Zn+eKT83h4+C4jgCc0Cpckocg3m4pD+MBhaAPIqlX+Mb3bSNC1RiT6f28VGaCtOhr1hadLTT2NOgCc1iDr02mzavrd4p1942jR9R1/b6NG5b
*/