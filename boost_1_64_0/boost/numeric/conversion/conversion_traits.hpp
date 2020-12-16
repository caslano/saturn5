//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERSION_TRAITS_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/conversion_traits.hpp"
#include "boost/detail/workaround.hpp"
#include "boost/config.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct conversion_traits 
    : convdetail::get_conversion_traits<T,S>::type 
{
} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* conversion_traits.hpp
lGGLPli+DGV+bFOHmZ0tU20RLJmOaZmdXD9lM3Ifb1NXmGWp8k8k4ibY1ABmdzOlFUd/kuVhlt1/PQ/mC1lWZtdmvPMV1h5u2vdcaUKZronmZSZw055H5iZry6zIb3VaYs6TuS2GxY2rMQFxk0PnxL6pxrWEJLIYZvGF+qAtKYL5tDKrnbANR79ocZ4i9TEH1RRzc5E94GPb+PpDrD1TaTuCaceRgqWQxcK0/cpUY16/Q5+F1k7sj7hpNjWe2ZFbrmHoz0+M7b2e/rxRwTyCJQmWLFiKYF6yukGrq11vVdNteM9kHfpc52+VDXOQrBazBc3jP0FbyOzM7g9qeR31CeYny8WsS/+i67CtCOb61NwSyWJgofMziczF7OqM0e+gnWQ897Zft4vA9k6G3PV7Zmew/PR7ZgXzkCEH7R7WFMH8gqWRIXft3lfrTJa7du+rm4znXsrV3YY+I+O5tziQUABtIeP5DZrd4zi2d8HUrNAcLs/IY7yrQTCPYClkPPfFR9/HPsBHxnPv3L/p+2gnmTtotemzbOzVDmjL7FBzv0oYjjmv2dmsE4zv8cgaMqsd9+N4lJliU42Y/e7POgg5kL3LbIfPa1yHJqvCLOLeh8Y53hy65sHsdKu+pdEWMh43/uLNLzF359pUT2bTzty1Ynsgy83s3lT7KJSp2dInPXtjbOfR2gMLvUZtJYtn1uvGxrvIgaw9s7wrGhr3K5LVYZbyVWQ5lDnfpjJa2Bgd3lUB8+Uzm2rG4kqlTRmNHMjM2hkg28HKVClLsqG+hXQuyqyH5UQ7jNEXNpUjzLDt7z0z7mlbTOdqyrD1Fed1Me7Ls6kWzDK2rZQd/bLEppysviq9a/6CMVoaai0z30SZaplNbVOGvXj81SPkR1aWxf1x4PFU9NkKHGuQafdLcdPut0nmpj/jk5t2/OLlph0v+bhpzwb1c9Pu4UnVLMvRmDrInczO5+7EZ8bvaFeyOP05rNy0Z7u6uOnPYdXswoDc72BsuenPYeWm3SvmIYth1rtezHSMA1mcxTBnw/OtkPsqlrv2Pj61muYusx+bFt2H/DSr+ZNrL3LQbMjaOgvRTs3+tMUa77rRbMqOcl9hTmg292lOL8adLDez1IGZS2P7I8vFrOzLzBhb1xrz3N1kvL4Ouaoa+xzNNqvGS5GDZsUO5tqMHDRrVj/TGuQgtCUgmFobWmZc83ZzkJ9mJ142/xz5kZnNFw/ZGGYnC27JhfrW0TE0TPvuhSwCpr1TniwWpl0bFSxJqC9FqM8rxPmF+gKCqfXm5iIzq88tmEewZKE+r2B+wQJkZn2WJsRZN5hbAtkUZju3ngtHfWS1LYZlzNHsEPLbZFOPM/7f3G/W1gnhE9CWHegXMu0a/FfUFpjWFrL+wfpq0b8rDUothfHbiTLJtLlLVihoNekzZm7lxZifZGWY1Zvq+RFzULBUway7aD/N7OzXQ/sgB7KRzJYt2vEbyiRLsBj289JjN9HOPVgnyELf15pE9h6z339b9TbGiCwPs+fJL41jm702VZjZhGcTtmJek2WFafcu7xXaQpaLmatt6fWY14KlksUw65Fn0NeYL2QRzEZ9em8ixn2fTZ1kVmTwnkTYfvPcE8hQn3bemEiG3LX9tEeL+/nbwbsx58myw7Tv+8lyWgw76f3HyO+ATeVlcbNKO7dj7h402lJDO55I4KYdv7i5acdLiZptKN19HfIjK8wsOqq/cZ2Bx2nHfF6y3MzKj/vZuLeJLBoWeo91mpCD8pvnYCXLz+xWK/dZ5K6Zd1D9U5ifmhWK6XkDOWiWL3+T75ADWV1mVT6zNcU4HAqNe9/R6AT6k+xDZisuvLyP3MnGMJtW47Rxv9Q=
*/