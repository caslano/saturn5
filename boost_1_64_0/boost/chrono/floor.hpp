//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_FLOOR_HPP
#define BOOST_CHRONO_FLOOR_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds down
     */
    template <class To, class Rep, class Period>
    To floor(const duration<Rep, Period>& d)
    {
      To t = duration_cast<To>(d);
      if (t>d) --t;
      return t;
    }


  } // namespace chrono
} // namespace boost

#endif

/* floor.hpp
AVc0sAQYAzwEjAN+DYwHLrkDdgg8D0wEJteFHQLPAJOBs+vBDoHvAZcDC+rD5wM3AdOAp4HpwInusEvgj8BM4Ch0lJXAvwCzgHc3hH0ChwFzgBeAecCljTAHDXwGmA/s64F2BD4GXAW8qzHmZYFvANcATwLXAdvDoNcDi4EPAL2bYu8R8BHgBuDdcOgPAQcDNwIfBG4CusPRFQJXAzcDu2Ks8giwB3ALcBVwK9ANBrQN+ASwCPgX4A7gTWAx8NEWiInAImAJ8EtgqbBP+T4goCuO3QLbiv530BXthr9yoAvwMeD3It0VkQ9tSrI7jkdEvjwN/QJ4v/DXq4FtgeuAnYHrgb2BG4C+wIeAxcCHgTVt4AHoB9wE/CuwEPgGcDPwGPAR4GngVuAV4DbgD8Ai4GQX1B/oD0TsEuUV7x0Q7zkwl7cl6uUJbAecAWwPnA3sADwH7Ai8BuwMHICLdAG+AuwKfAvYDTjJBXwCzwB7AH8A9gIir9YbeATYB3gU2A84HuXoD5wEHAhcDbxH8HtYPttGz9JReXvjKBNx8F20nxfwI+As4MfAucDTwAvAM8CfgWeB9yLPZ8DXgZ8DjwG/AM5E+f4OvAg8D/wVeBGIsmpfAo8DLwFnoFyXgX7Ar4GXgN8A46sg/gG1qrAFoAfwe6AP8AfgReBVYCz8xjXgP4A/AqtWRzwErgPeALaA3/gZuBf4C7B3TcRJ4Fjgr8A04C2gVy0yzrQ9QBuwJ/yGC/BuoBvwNWAV4FQYXlXgaWA14A/AGsCO8Bs1ga8CawEnwG/UBs4A3gE8B6wLXAb/UQ+YAXQHvgFsAPSF/2gInAX0AJ4BNrbnAzYF2g3KS7RfribmUgAFYhyDn0WcFN8f0MADcC+wLvAA0Bt4EDgXWA4sBD4G/AD4ONAd1zkE9AQ+CewGfBo4BPgMcBjwOWAW8HlgPvBFYf+j5X0g7m1FedqLMaf9L9aG/gqMBzYCJgFbAFcAhwBTgcOAacCRwHTgNGAGcDYwExgAXAlcBMwCLgFmA5OAOWKcmQvMAeYB84H3A9cA84FbgQXAYuAqYBlwNfAgcA3wEHAt8BXgOjEOXS/Gnw+I8eeDwA+BG4CngQ8BvwFuEuPRQqArcDOwGvARYGPgo0Av4BZgW+BWYAfgdmA/YDFwAHAn8CzwlU4u/2TvSgCjKpJod/+5kplkMpPJ5CIQQrgPww2KCAgYToOcAhJycbi5TMJ9BUVABAUPRAVllVVAdGFFwBsFFRVXPFdd3MX1QhcFkXNF3fcrNT8zkxkIK3vna1Hp6qr+1dX9e7q7qv8XhwD1WiqRBagEbAUcAIwHfT2gQysl9pZHilHAFYA9gA8AxwAxrZVIBXQAZAIKAZWAOwCbATsB+wDHAKY2SjQDDANMBywGrAfsAOwBHACcAnguAh9gGCAfUAHYDNgD+ABwBlAPk7NWgG6AsYBCQCVgHWAn4F3AIcAZgKMtygPkA4YBZgOWAjYBdgPeBXwGOAYwtcP9AemAboBRgArAAsBawGbAbsC7ANEevIB0QDfAeMBswFLAJsBOwD7AAcAxgA0TyQRAN8BAQCFgOeAZwAeAg4BTgJiOsCkgA9ADMB5QCqgELAes3RopngF8ADgF8DwRKTIAAwGTAAsAawHPAOquuqvuqrvqrrqr7qq76q66q+6qu+qu/6/LBLhWSIoN6H3x2JLSguLykilleQVVf5YXts6dMrkwv3XbNm3bZExoPbW8XUbbzkbe9E4dWpdPyikryG9dVlBYkFNe4OPIK5tRWlEyNrcY/2fn5Oe3Kcm9VuC6WHRzifG6nysWvvync4SBB03OKyspL5lQkdrsquapV5ZWTC6aPHNy8cTUy0s=
*/