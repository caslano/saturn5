/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

BOOST_LOG_AUX_OVERLOAD(const&, const&)
BOOST_LOG_AUX_OVERLOAD(&, const&)
BOOST_LOG_AUX_OVERLOAD(const&, &)
BOOST_LOG_AUX_OVERLOAD(&, &)

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

BOOST_LOG_AUX_OVERLOAD(const&&, const&&)
BOOST_LOG_AUX_OVERLOAD(&&, const&&)
BOOST_LOG_AUX_OVERLOAD(const&&, &&)
BOOST_LOG_AUX_OVERLOAD(&&, &&)

BOOST_LOG_AUX_OVERLOAD(const&&, const&)
BOOST_LOG_AUX_OVERLOAD(&&, const&)
BOOST_LOG_AUX_OVERLOAD(const&&, &)
BOOST_LOG_AUX_OVERLOAD(&&, &)

BOOST_LOG_AUX_OVERLOAD(const&, const&&)
BOOST_LOG_AUX_OVERLOAD(&, const&&)
BOOST_LOG_AUX_OVERLOAD(const&, &&)
BOOST_LOG_AUX_OVERLOAD(&, &&)

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

/* generate_overloads.hpp
syxHPAaziCWQonkw0JcUqFl1XL5rFkHv3Nv569/dtX6OUSgvPf+qAso6HgGQL/EcOo/Zivufu9ztjNMwMj1I3WSeSuRSklbG+Cq9gDcFV7Le44rhUs8SDbL71z3rUsoMNS7vP4ifpGExPmbQYt6ojZ7LFFaSoMKd+87V44ipZ9bn3Saexqzxorv0++KFF7+iJtG9AhB9eEc9IOX37Ib3Bb4fduJLo1LUKaziKR7vRFiLoRqp
*/