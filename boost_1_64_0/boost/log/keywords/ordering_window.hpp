/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ordering_window.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c ordering_window keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering window to sink frontends
BOOST_PARAMETER_KEYWORD(tag, ordering_window)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

/* ordering_window.hpp
Vwm82jbHaDnpOTUv39ZvKzxNzbW+7mjUre4nM/MD89fdRHi23AyZGXiC5/OCgqCxf0wDrappqPcxixiC5XaCThPI3ikKaZ/UYwh1bSsIqIceP/Y+VTLOMC/bdSz9YIHmCz5G0zwXdoyzzccljRX1TcbpTa2d89r2zp0uG8v27ASrB/Q9BojccmWvNg8qa/0251Tq9QvjbbwaG7VIr5aEgT4pHzmUXShlOwzSiMuuNZa9qSq7vJe57EVHqLKNk2Y0Za8YHVK29hFodyh7yZFStnHgkUsUcn91rLPcS5PM5beUqfJDfwSiLHvVmNCydxC5r0pyaLvIPfSHY/3lZlDuiQPJQ/1e1JC6sZ6iSRu4VqO4t7ns4nJT2dH18+TQvqbLXe5QbpvoO+gHn/SRlzvF0M/2EFnvm+wga9Fz0ES8wW0vzTf0danDCoc6ZInMHSa4qGTw6jhn2RdtbC5/5ZFB5W/AGF8y2rncZQ7ltku5XQ+D0Ze7Ntd5bhm/icPYlnKdHhqiKT9lrPP4vseh/I5SVX7QC0B05S7dxnlOy93UoVxpt/2FYoP6mKHsidLmpQ5l50qbw79ERjfWVuY4674gxVwPS8a708taNDr4eZRz+Usdyk/R5euHkw0uv2Ok83w3vo+5fI/oIczLcFTPFctHOT9XLHWoQ0q5qQ40Psrf1hPGhdF/X4e5VuRv/ngQXf/zjHKW/zKH8lulfMcXkChlUBLm2aagn8NYlDqYPhZFo/s84/gT3TuUbcmzTciHhw3Q/6vbhun//R3Kl74X7uUnGhmUFzj3wWUOdVik52H9sWaD54DWbcPof4C5/HKRQfBLerR9L3H70LLHStmLHcr2hJQd3Zgbur3z7+3QVIf2iryDPl5E9Zu3JM9Zz9c5lFso48z4YTPKeTZnlPPzVWaaw1zT1e4N7l+1uYYxJuUucii3WNrt+IE5yn42L8zvfFa6g86lDg4fLKLS/XUFzmOsKKMzwUlQEnQc9IRvY3rp54Efrzjnv6Gq2r+W5Md+FjyequpGh7VL5OH39x+r1gbMqJ5RUTvNMq4P0Pwq73zF3zyjzrQ2IChvmqTynsXSLFU3OQ/mXMVTy/VufVJ0mrSu9T1BZQ5WEmmYQTaqzA45P+bdLZUXaS3/6LwuUemmqXRXFfjuVLvxxlfpPiKd36e/pU+nnjIj8On3yXOAkmfXmjXkRpyWm16zlu+LF/mk2tcLiRyEV7VhsOJV7dJri2iTj7dW+FSdaQdxqh0B89KyDIdnkYqgPhLZb+DEgG8r2zvPC3mDHOZgGRvycW6DvmsUjHN+7lviUO4iKdfwgTSq8Zie79zmEZkObT4ysOwNed7MNMwD20ibcwd3JjjB6sItfd9Bj9Bn/Lj5BGMbb7ztNqpZyTj2SafH1W5pap44pqIWHjnT50l1fypj+SDjXGBP/52aZ6ixaS4I4o1P8PFWz6xonKbP7Fqt7pfTVhdrDhKN6/wkD+O5X+ngCnXfY+1I6ybD1ZfxHU98M99f78ZB/9khkZzzlQzwW6h0Sfmc7dS78++h++4/OteSs8DWHeGPy1fXH+rrsWqsJ+ixrnWg1zgha+JF1jJXID/ilPz0+EdOxCk5qX4wRvrBR5vL2WLS9w6SftBSqvvBjIrGGjqDsS9o/Z6t+Mfxm5Jt/m0oNfYPU1+AN/K+AK+pLxh1buf9fKxF8DXN0v3mDHV/f65drKVxgYepdmQgj2PQ+zV0jEEDQ/WeEKj3P11nxfQ9NQ9IoZuJzgq7dNZYPSO68VsYhX4Ko9BPYRT6Ed6utbf9Ipnr/lxZj99CrylR4SiRdUrXPNk5OqKQdcoRkcs6JYp5MeWIyGVt552tnnd8I8HSZ+s=
*/