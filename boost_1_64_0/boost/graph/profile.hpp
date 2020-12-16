//
//=======================================================================
// Copyright 2002 Marc Wintermantel (wintermantel@even-ag.ch)
// ETH Zurich, Center of Structure Technologies
// (https://web.archive.org/web/20050307090307/http://www.structures.ethz.ch/)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_PROFILE_HPP
#define BOOST_GRAPH_PROFILE_HPP

#include <boost/graph/graph_traits.hpp>
#include <boost/detail/numeric_traits.hpp>
#include <boost/graph/bandwidth.hpp>

namespace boost
{

template < typename Graph, typename VertexIndexMap >
typename graph_traits< Graph >::vertices_size_type profile(
    const Graph& g, VertexIndexMap index)
{
    typename graph_traits< Graph >::vertices_size_type b = 0;
    typename graph_traits< Graph >::vertex_iterator i, end;
    for (boost::tie(i, end) = vertices(g); i != end; ++i)
    {
        b += ith_bandwidth(*i, g, index) + 1;
    }

    return b;
}

template < typename Graph >
typename graph_traits< Graph >::vertices_size_type profile(const Graph& g)
{
    return profile(g, get(vertex_index, g));
}

} // namespace boost

#endif // BOOST_GRAPH_PROFILE_HPP

/* profile.hpp
TRTo0cfcXxNMxvY4BBMwBUdhKk7ANJyPGbgWM/E9HI1HMRsvYC7ewrHo1pfzDJbHCVgFJ2IgvoBNcDK2w3xMxpdwMU7BApyubXecofWPs/AKzsafcS66JfK6FX1wPobgAq1fXIjDcBHmotbfHHwNC3Gptn3wdSzG5XgJV+AfcRXewdUY3I/XMdq8oNY+Hzdq2x03YQFuxq34NhbhFjyJ7+A53Kb1j4VYoT/nJ4xFrX0q7sZx+AHm44da/7gXC3Af7sD9+AF+hAfxID7Bw9htgLn9YPwcc/ELzMdirT/8EgvwpNYfntL6wzP4GX6FpoGcZzAYtfbt8RJGoXsZtosL5zf+wF5C3CUmcX3zXELUMIkaRCsilsgkZhHriCLiLHGdcOKP8VWIECKCGEhkE9OIlcRO7eceLDNeJ9xq0i/RlkggMolpxEpiJ3GcuEo41aJfojkRRQwn8omVxC6imLhKiNrUI1oRscRwIp9YRhQSh4izxHVCBJqEPxFCFLBMEZhGTCKOkH5ANOD8P5BYSOwhFlN2FwsxO5FjL8f8/ejNiVgim5hFbCGOEOcJp2jmlPpBWIIR+BAzcTGxhzhL3CTcYhiTaEskEpOIAqKIuEw4xVJORBDJRD6xiThOXCceElU4h4YQ3nV4MgymEfnEJqIBeW2JIn4+RdwkRBzrQLQlkolpxCZiD1FMXCceElXiqUOkEXnEMmIPcZlw4zxWg+hIpBHTiHVEEVFCiN4cz45sHmxODCTyiQJiF3GeuEl496Gc6EIksJwDcRKxjjhEXCVEX8YiQohEIo+YRSzTfqZNIR4hSgiRyHITbYlYYqUjy4E7iePEVeKB+l7LECKKyCPmEYXEEeIscZPw7s+yEVHEYsbZSaTx8zRiHXGIdAmKAdQlQogIIpMoII4QZ4nrhNNA5pxoTnQh0oiztL9LjOfnlcQu4jwhBtEf0YDYwvJ71mXf5udsYiGxiygmgsi/i56DmWeiORFFZBLziELiFPGA8E+iPtGWNl0wmRhPLCOKiYdE7WT6IKKIgcQkYjERS5tNuIs4TpwnHhJp5HsOYb2JCCKRGE6MJxYSm4gjxFVCpDA+0YVIJMbTdjwWEHuIYqKEcEpl+xEdiWRiGlFAHCJKCLc0+iEiiEQik5hELCYKiSPEdeIhUTud8YhEYhJRSBQTJYTTUMYhOhKJRD6xkthCFGnhyHriXcJzGNuCiCWGE9OITcRx4jxxk3AazvYl2qrvfcknVhJ7iBJCZFBO1Ca6EAlEHrGQKCRmMR/n8SbhOYI5JRKIScRiYhdxlnhALKNulZHUIRKIYpY1G/OJTUQRcZZ4qKWp65/JchEDifHEQqKAKCSKiKuE5yi2PZGovqthPLGS2EOcIq4TnqOZMyKEyCbWETuJXYxRQrgFcW4lEol8YhNRTDwgqtTjHE0kEpOIlcQeooTg8VGiARFFZBLTiJXETuI4cZVwC+a6QbQlEonxxGKikDhOXCfcGphEbaIt8a/8c5K7qckHRJc2A7Oy00fnZo3NSU03/5ib2TBlbEZmWsMmjZo0ChnacFxu05AmLfWy8S2aN8wdPiQnPa1hTnpm+pDcdEuNIdnZuQNzR2WMSm+UlcL2ayPa+ohktpsoLzzEh0OEbs+M1Jys3KyheTWC4urViMnOyxiVMTFj9LAanbNGZWdkpucIX+Hq06C60D4BGBObkBQeFyeseUJmxXQV1jyTzIsIj4oVwk/lOcq8LuGd4/rFJghrvovM7xMeF9m1n7Dpw03mJ4QnJljz/GReXFh0F2v7Subxo7tFRocLm379ZX5sWHx8ZLRt/jMyP753p+7hnW2Xo4o5P7JbdHic7XJUk/k9u9jm1ZB5kdE=
*/