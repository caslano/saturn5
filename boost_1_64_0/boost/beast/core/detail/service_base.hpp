//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_SERVICE_BASE_HPP
#define BOOST_BEAST_DETAIL_SERVICE_BASE_HPP

#include <boost/asio/execution_context.hpp>

namespace boost {
namespace beast {
namespace detail {

template<class T>
struct service_base : net::execution_context::service
{
    static net::execution_context::id const id;

    explicit
    service_base(net::execution_context& ctx)
        : net::execution_context::service(ctx)
    {
    }
};

template<class T>
net::execution_context::id const service_base<T>::id;

} // detail
} // beast
} // boost

#endif

/* service_base.hpp
qgI1gZLmIBx4DDQD/wtBJ8C/BZhSB3v/+DBeCLLOAtgOvyzgAvivBDbwbICII9ApcB/8b4HfIeAp0Kvw2wt3RB7SUR+mskH74T4IyoZfOzCvHrzAYuDgyfbzBRrrcU/gSrj3AnOOwB//60EtCGuF32HQKZTzFqSxBf4HQafq4Q+M34S4QKfxPw/YBJ7T4C/G/5S5oBzEg/+z8H8lqA3/j4Oy4d8Ad9I1uCdoFtxrQCvxvwrYCNqJ/9vB0wLaA/chYCvwlCU3D278zwO2ge8oaA3SfiwHYR9DXUM6yhC2DZQD9x7gQdAx0GnwPIfwCvjHTQGPhRhE7wJmwd0KXAksA20BbeeZCkfhfwCYDd5DwFdBefPBBzqB/xFToV/QFrgzgdkNyAtoG2gW3Dvhvxe0D+5CuF8F1gO3I90H4X8K7mPArM2+sxoibghX2xCe63JuQzP8W0AHQC/BfYLnOBRC9hD8snimg8IZDl7gTtAToH2412D4bQFfJtB/5sMxULHlD9rO8x8Obg6cAfHqZsg/At1+HDKgbPitBOYD28DTDjoBis5FucK/Cv7bQS2g54yzI2YBl4CqQOoi5AO8TfjfCkxBflPgdxT/ZwDjrkUaQcU8ayL/WvADq4DmuRNPwK8Ffqfw/yDwJbiPAeO3wA//c4Dx09DeQTmgfLjzgF7g4HzoBlhsuUH78X9WPuIArgHWgxrhH3cd+PC/BdQE9wK496CvOwA6CoreGaWyQAWgBlAz6ADoOGjwp6NULqgQtA20D9QGOgFK+kyUmgUqBm0D7QMdAp0GZX42Si0B1YN2gQ6AjoGS7kH/C6oANYFaQcdAcffiPqA1oG2gfaBDoNOgzM8hLlADqBl0EHQclH4f/EFVoG2gZtB+UDsoeleUygEVghp39Z7h0Xv1Xr3Xf8/1bzj/3+vbD1ttmf/vke1/y3b/Vwzb/Qs8wXtphmYj7lPBNtTF9M7a0PYKIdOtfTKhbP1i2CzXKAplgFLH4J3DPU2myU9n2vTZ9q+IbJqKlhUvUUyzP87wUGtkGD7qjPLE9W7OdTFa9yfCgnU/DLqPfyc4n3Ud654y5h4mcDN8sYSfednY9zBJvDa7uTk0yvwK9yn/ErQ5He909nywnELmgfzDtG33meJ+Vl2K3waec5mSpG2U6bOVpwvf99UlSNOnQcwz40t0PRshCfi4hKfZzkZ4SOyl99xWvpVO2i+Tdaj7cC+Zf3XYoMxi4d/Abz+badc6791g3XGPkFN/Wg/LRaZKZeN3Doh6ZVwJrnoYCNwq4QPpxomk4u7DdWFnrgsr3zdIXKgXjnzPiOI3atAI0I2gFPC02/Mt9ok3lpRa+Q9lP5Eyk11tFDNMZCPi9fp6vW455r04vXa3QPOPt58zYtj9HQoME5kacVdqmQyVoNdXWym22+1PEJlVKoFrx6OFh2lhfb9MeNIUz3aW6wOJu5B+YFKaT9t0TEY5RQKfsM70hOADoLeMtdV5HZZb5EBffCpzY3ltLby4ljrYbmKhY711MdwR8dwjwPWlFVqOeqN/wH418+3oC7dF016hB3WF89JWH9L8nq0+GNv8QvYjlIFtDOr1KXG/B+3j3FzQY8F9iT4D5OvCe0KtQNruBT2j+xPG20F/UnpayoXlofsT4IfTp1x5mn2K41yUxr7ufYp6312X3NwSsl9JeN+1X2F8ofuVuQg3+5XN75+9fmXO+7pfsY0d1sRwtSrXzw4FJWei7Hx5x1hKjIryeVpUX1tSXVdVUq/P3Bg4IvDsZD4pm+5a3xbr8KE6XxFDu27HE/fjM5XraF3GRZP8a7N5zoCs8QDlWAj5Nl/eJC/IlIrRfVcJ+0g/zxBtk/815om8ug8=
*/