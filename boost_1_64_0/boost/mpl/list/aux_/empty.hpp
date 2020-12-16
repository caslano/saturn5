
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
n0iVfSL9iNpWcl3oZLyvE/vEfU37WZ8fteMaxMUYBoXKtu9yVL9+E9Vpqzgm2bgpsi8slH0h7ajV+tV+8vUz7wuyfjbHYilZN/X7UFB0WBhfCV1knUp+oV8nP6vpvlbTm6ymg4/ZP9ekSRtUlGvb8sbYR9yvtoES+vjI61pH6y9xj/rzGxmUl9KHXhAX4C+UGbhVLVM5BI1lej1GmY6e8xWkua5IkHnAPMu24Xt4PDg8z1y1OlZPUEAaa1Wfxl2/TY5VzbYcFJ4QNVRzrC7cqt8uO6ymv7eafmA1vXybfvqw1XTJ7frpCVbTh7bbPxbSPWWMOdkmAWh8JtYOdZuYD/XH3i5sDKvtoj3W5fpUe67UbxM5ZvTtH06BkdT9S6bz7NTEQGrbX46vW/aOL822+WOHvq1Kf6ifbmY1Pcdq+oHVdOWd+und6rQ2BtFR7JqjGEFHMW2OYtecj+2zHxPpfEyh/dhH52P+nI19tB8j6Cjmz2HMooMYUEexno5iNx3HSn5kjIlsuHvI/Aatk7v/tG7KdzPfG9zIcYypxNjJvVL2adIdqxi7M8rYAXgWS+B3aM4Xk0m+ryXfKcl3WpMvWfI1t5MvXWJUzqEf/iD53HLIvUa5B6nkU/q870u+tZJvHZbGDVgRP8B6uFGWtwlb4GbsgluwJ27F3rgd++MOHIEf4ljcieNwN07CPbgY9+Jy3Icr8QB+hAfxE/wYP8VDmIaf4tf4Gf6An+MlPIK/4VG8j2mYi3U8jgXwSyyMX6EpxlHuN2K8tKM2xvGetMcD9MaHWAv/xAaY05UYHHTF3pgLh2FujME8aC4nXcoJt1POZSnnmpRzXcr5Rcq5Ie18E/vgLTTg7xiCtzXrE/Ox4/UpKb+J90FvLIO1sCw2wAqyPhVlfZ6R9fHFGKyEUg73+xyvj7uUU0DKKSjlFJJyimAXLIp90BMNWAxD0BvV2FUpJ5+d/byBxK42RDdshDeQ/V/u15nu35GP+CPjGBBybUn98B/ojcuwPq5AA76PEbgGx+NafBPXYTKux1W4ATdgKn6AH+A23IT7cTOewS34E27F67gdf8MP8R7ulrFS9qAb7sdCeBAr4sdYHT/BuvgpNsI0bI3HsSN+iV3wGwzGbzECz2Iifodj8Sd8HX/Gt/A6zsFfcCFm4BK8hWvwN9yIv+M2vIef4R94DP9ElmWM+b2CufAh5kZX2twdS2E+LIeFsSp6YF0sgs3QE1ujF7bH4tgVS2AvLI1B6INhWAaHYnmMwwr4Kj6Db6AvTsFKmIyVcQ4+i+9hNVyNNTAVa+IWrIs7sQF+gw3xB2yEyg7ohxWwKdbEFlgfW2JDfB6bY2tsiW2xHbbDbtgBQ7AjDsNOGI+dcTi+iGMxEMdhd3wde+IU7CXHe6qS5PgoLOdzT2V/No8xJeeV6eiNM7A8zsSqOBvr4hxsiu/iSzgXR+N8nIgLcBouxA24CHfge3gAU/AILsGv8R94G5dijhzUB/PjSql3jIvcf8Lxclxrn53XV2IP+6MnDsDiGITl0YBNcRC2xhDsgmEYioMxESNwLA6xPFtS7jlRJ2kv7bMlB0h7GbA6DsQOGILdMBRfxsE4FMNxAkbgmxiJs3AYbsQo3InR+BXG4LcYi+cxDq/jcGmvEehNXRKxHI7ERjgKm+IYDMCx2AWTsDeORwO+hkNxAsbhRByLk/ANfANn4GRcgG9iCr6licX3l+3SjnRHH1uLMsYHVsAuWAUDsTp2xwbYE1tgL9k+vaX997nIvStMl+UXw82y/Guy/F/RG29gObyFlfB3bIy30R/vYFu8i53wHvbA+9gfH2A4/okjkIKTkhRwOubELeiKBzAXHsXceAzz4Dc=
*/