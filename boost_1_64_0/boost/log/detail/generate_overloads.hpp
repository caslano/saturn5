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
/f+Ufq6ovuVlPvAfGLWLLbmMUU16ihEGRtAN1k5DrOwFq5S6IUNw6cmIyQOwD+k2TZwP2siCjrVli2de4K+1PZOrNW59/cO/ro6WZCjRFBNhWmiafkvan8aNtiHasniRCBBZ3q9qxPEh0HPh+h4y4kS0vuhfhBk1z1aMM0P9A0G6UnuWjxwXfqGAlVxi+qRQu03FvdJX+UbuPNNiIA0J+w7vnZt86Ot+yzE9W6MfNyTxCBdNe936ad+mss+ge9zoYP3QtCBGq21DkVvm6F5zOYhU905WVBTpsw8cq4ZRpk1BuMD3AgKH1wCRhQf3hFO7fCSrDC+w9TJhrh/W0mBaNCr5JYvY0g8JnB4vSB1REIxylUjlZhcooloH4b8MkajJ3kpNL2RlmgXZDRdDxV8O05XEtnjq6rXkHa2XTEaAyf2aPy+Vhg1FyflX4fvGLyJ7zGs4+nISZC69mn3jM4FmgAnZ4kpPuxxdMq1xun2r2EhFqEqdYQVuBFzGnu0cH2dvJdXfc4aygiDYuNjRo0T7ha/5MESc9J3fNDpFUoiSNyJI/ifvGSAZyImClw==
*/