// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP


#include <boost/geometry/strategies/area_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of area function, using the default strategy
\ingroup area
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */

template <typename Geometry>
struct default_area_result
    : area_result<Geometry>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP

/* default_area_result.hpp
PzNosXPqHyxc5KC8OnrhKjMdr3U6CYJTzLaeYF/OsLu3E+w3EfYAR9hv9gh7uxmjFLWD0M8GozQ4xItLioxeCkYfkrBoYizqGQs8AYu23ulUVsQgpzo+ISCtDGQ8AuFoZWmiVAEjKCUGxlwJBXgp4Rt9437AkzZ1X8nio8VtenTtHXF57LSI4vmyfXTHsep+/4UUDkOqirzzHswE+/lMjilVMVvuVuBKsiRivKWhFfVZvMX7GiLVzme3HLL9Tt70cW3bcyG14dWHnUd1VnbwnQpOqeDHlyP4ZpgO0LtSw6Qq5mJGTjVZw0vqiO36TNvBWNfffBKSpn30Owik+cXfutJiwm1X2E66nUbfPKg3n95dBsNxSMD+qqDKTBU7ahUlP5D8kjQMwcg6FfnuSkWyzxUimsbTLaLUumg2FjKN1IEG2/20zsXGFHwy2QuMXHKSWxV4e3OXxgYitnHWrfcSLlrWas56ni9xMCDKNevMZypehWfoEczDGBFNfxCtpWhtjZF0zvr9naqqg4gtSYcvpBZlIZ3X2ecfYtI1OYObKrvhMmymXEs201O3KtLekaE57L9zJUHH8GsytBqksXmSbSrhutU90OPkDCj3qXQudwA3EpYdUGUfdatiEQqNzlhts0h+RlJDN3wzqWmQxgadyG2mzxIm/l5RoN9e1QOaD6QDmvkCzSx/61MCzR2Kk2sZzYkAi0Kj99zDi43hKuRGCJn8C2X8tONZ6RZnRnoqtch1rEWBqoUq58CeavFuGtRiRhrXYlTDIm1UWUmjSi3X5f27eVSJqNpdc5sYVai09tW8VacElXjQuS15IEGIjljUIBadXsYix9/6gKBlkyqt8MeKlryTPvPuZMo15Kno8rttjnCnJdMypFLmQUp5L1YFPngrV25DUm2inb9QI929XkB7kEA7zd/6A7fO8EX0tY3xn3+b6i71XpFKv8Fe6eYauxSTv2WPXRVsy2KJMd3xVeLnYXUKWFO+6DF3UaXnToue/bA25Lc3Y1KtZfHT5dAMv/LAaLCfNuNBQvqpEv60ikrwL3lLutbVYw9eqfolRUSfWGW3wnwAriKOh+akc1cV0gFJhUH/GtiIjL9L2Aph2xEE4XAdwliEUAYQwmRuthpmW6rDYEzEBodNSr31ENFzOKc+HFIn1x9HvFxYd7GWkGyJlTerlnjSzSispIOXOwUxWl1a6OW3cNVqocUm3a7orq5Bf41bjBPfeKeqdS3Uen9aVqlmqzGbjY0H5KvMxVhSGZREI0YhxMbykteQXXUWT9/oJbFhqkxg3k9uOMhpqckTUYnFDJ4LIhLnzIc6rwl849U6Z5EFgP6sphhHNZvw11XOIdDHQtjdsdyBPcEveb5bTjXDEf53XYzokIZ8c+1Hs9ycxCHgTG7dPJgOpQo+h6y5mToPlqgWShytr5RIsKdwad2CuCyi9Q8S7eC/EwxeCD58O4/7eYkcF7sI8K1yNZzDuCn7guHjzYUy6AV6kZRTbQDF4qjPzbu9s17HPdFJuCcKqj3RZyv0PVHz86X7LtPt++377cmvytH//1ba38uLO/oyeqWDqihHmPrnZtKKyLRMmuqXvWLv42+7wU5n7uNNmF49RFfGAxv2mezoXx36tVu0UZIuV6OH3SROJ0+DnaUK/RQmGDL7f8RG3vKs0Tz0dR03QEtaWE5jfXKq0QPEsK2SblzBO9xunzjBUTH3iJjfQwyencj1gErwLiUI7y8jeSeIYtOlN4sK3JgpKaBtjSs0muS6hXQUgaBYlTxe4JBeqoZ0TspZ1P63VO5/uYYSM56Lj31RrQonZzEr0OTp90lI2v53F2xRWGZ7BMcpq6ZsrHsKbUK5GLXD/A0=
*/