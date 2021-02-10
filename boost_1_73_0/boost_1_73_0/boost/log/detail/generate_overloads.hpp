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
WgDDLpfAnHvM+oKfPcbcKfvPJHbjMEzlWltOfeisBasKeJo1W9CNZuSDmEhS10kT9qQJWGmUclid66v+ebc/HJ/3zs66A3aUsdNT9iyrVmhfj85l8VFNcedyMOh2Rr1LBeO4rhJ8kMUnNcVnA1uWfl9T+rrX78riH+qKR0NZ+mNN6flIF/9XTXHvoq2K/1lbPLy8GsEilXV+qqlz0bM7ij519IOlPrxWAI7qSDi8HJ6o8jrqDS9t3b6OfMOry19/UxXqKGh31CCP6iho5yQ8qqOhfZGX1xHRtjWD1BFx1O0PunoAdSQc5R04riPhqK/447iOftfD/mX7TNWoo+Db7tWrS1tx0TEQcS9dRRzXexYk3jwg5ZkyVGAoe8bpi709EGAZ2CSwfvg8jFdjoWejNIwT9m9chaBYoHjhxOwJLLwXpUdYnZ5pmBrUi73PBN9JPVe22YRMPgRd9/4j+5lw/3vfydLFfoPtn3mzGY85dB5HRKoKi+CBB+1AJoJCTRfhNIHKhTX9uUFwAH0AphdURGj98I75/BZsk4Cnd2F8g2IrjFCkQQ2AAW3q1r4CBmNFMCgbpbBjKJgYCmnmpaC5Z2Y/8INsOkXobP8NyU+foUgAogqkBUkh66MOxgYkHaI4TEMXUNQ0wQqqTRpR
*/