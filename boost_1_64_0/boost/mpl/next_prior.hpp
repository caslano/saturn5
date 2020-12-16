
#ifndef BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED
#define BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

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

#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(next)
BOOST_MPL_AUX_COMMON_NAME_WKND(prior)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct next
{
    typedef typename T::next type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,next,(T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct prior
{
    typedef typename T::prior type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,prior,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, next)
BOOST_MPL_AUX_NA_SPEC(1, prior)

}}

#endif // BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

/* next_prior.hpp
E4CK6g+Rwgjv6GCWxjsXeC8IHirY892UxxUuuf4zT+y//1HrVZbx32G9ngbVK/403K8iAunWxydWsSBecWpyfZwhpEqP3CTr4zfKz9U3ffD18T+Qy2E8863kbSJ8zAoXVn1eBqhGQqCRrtiPIUqtYcptZn079/E5fov/w+VdainvMJSXiVvWLLQzmbY34qlphTSnva/nUKKnLrc856/kYbRuJQ+jPZT0MHZsTeMG18J6tFBymbF2omj2mKat7BVcbrRMTbJ4HDbezpRxay1jKDy5yHfjRUixOMMVORxDy20gpEi20UcTKGSrG8b/UtB2DZdaakwei4wfwd2Yun1zyQwaf/9m//b1929f/97bF/SeolHXWGuh9zncJkWuqZWcF9RAaC/r+ZOIHhoqpb9GfG8v/cVmcDJu1DgdM6Lxx1nvz52AZfXXL0y5U8KPXQm5AsQVV7mN6OvHLWertgodQl3LnaVQ/nAewB/+KgPdflUU67JUdHSwf0UdTkyPVVKZa3I6jHmj0xYXmM4t/zR3YEGuFP7RH5ptze+vSDWNR69K9jeLOK5mySaRph29fS/uy+UVWj+rvqXv7zY2XUF60Aj14X8xq8HBLt3XVNZwXlTsNe5g3BbgtijcuMKNmw+mD+engXv35ToXng8FeT7EjQ7cdPUnQ7CG21TVfwgufyTB8+Icu7evjSztrFFoaNXuP5xi9lMj+uka+bm3+VnwXGrqWqpnGn6+j/0vE63zsyCdEYjRPhb4dMto+PB1DecN6sX8YGLoHH6psW9YvsCOEoXr/Sbsd9ZmmtTILOMcvrTa+O5IeT4aT4P1DfNTJqF+YPAcQqUCQEwVwHmoAOCmFrDCXgC/CGAM0AUwpyjA+A3eIlhJNFrpp+T/hpk/o/cQM38h++rGs59H/r5hI1/j3lgk2MfZsDPxNucywbZcpH3+NfvREeL+23A2uq7f/YessmNqq1hkz6gvjlPNd6C5Kn3bswDGA6dSmYlXWyZ/3nrebdx2NOqBtZcZL1acZNKqPKZvWEsXpFKyHqWzogl4GFpMWfd1PHaSt2Mh/1dZ5U1fkdztwn+xJogG92mMatYGjuQMwTcotYNSzcikepU7FelLhNQtJPAseGpqgEM5vjQF5E0Py/UWO7uM1XyXynUd8gi9HM81SpOljS5O3PxNJoI/fbz7nVz/Htp02jfsZAgTNqBXjKZIkHEZaLXjke84Z1DbySkjUbVkRC8q64OARy5vNQWogNimH8TlRtk3nrd1yIwX86avMI9bGkV/HyBhlS7KyS5FSRdtkh1d4rv5SNn0FZdQn+tC8wi47yb2UeaxtHwtWEjkjdjbIEHTr/qxbjdh3HyWjMFx2YD37AXIyrBgxx8K/BgUjfEAcigRVORGYAFG8swtfhkEfZaWCy0/87bmu0j+vFiL7IwMxEwRwf56aiwo2OtX70cF+w8/WO/K5P2fX0+R5xlN/zKf25zRan5jrwL+YKfLXAjLqQNazy8JEOx8pUA8icU3SBgUGWueQnaag87iGfaJZC7rdxCETo7HuJd89Yv55/g6YJMkrxQ/nw1hN3+Tdwgvosyiz+Vft+jziYrYtiO5TIq6VA7Oe3zGiwQ7ik+yVHyJ+OwjizKjgbnwyrqPL1zPP+sW87+0mzGUoUv3SpmUiwJP1fQvNU1VDrJsIYxI9vYZ/D+D6xbzt/DiRhPeKHBFq66eAWX0TOPiXvpCGrwaNfOHZ7SgXfhfPqBxNcXIAJL6VV6pliwBLK2v70UNu44Qo7WYW9yzmNPC+A5e8zkABBbksTAmnNVzCg3kQeZJEfHCi/OanVJB1FqFt1ppdelPkdoTJnwSpZbltZTlteSKVHlt1PI=
*/