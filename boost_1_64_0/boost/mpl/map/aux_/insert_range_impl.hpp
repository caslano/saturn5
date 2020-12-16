
#ifndef BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::map_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
ytlf/m6A/N3hGI1J2BcH4WhMxmxMwVwcjGU4BKfhUNV52CD5RXs5r22yXqT2ehxvuQ7L9TnRKW4bKvHVHhiKPTESwzEOI/AY7CXHORJbVM/H5ZwbZDCRPMVVGb9AGbPAEp9J4XXgQ56enSMRC81E6zgNxS2d+xydueXf/SzdSsrfQtKau3Bri7tn69zOZejx2brEdR1/vm7bRu1n7Lp/2x6zLFpnj1m6znXoGrOsXmePWzau69izd8vXeX7+bvW6rn0Gz9/n73as8+0ZvBX8BjeRdpDCzgsyZJCKSY2klaQtpJ3nBe3J+v8RxnrLeyUCsFv1/1jqs6dwAVpVqtQ7CsZMPCm/0Jg/auKo4wqkRt9en79BVZ8vlvptQADXMvyB9/2Ucc+TbXWSI4ym0oohbMEsBXWYm8qHOQGV5wbKh1iurTN5cMDy/rwhrvOuDKFEZVWmaeyKw1xD9SXVZud6jPKZw9wEnKiSqlm2Ol9fUp7cw8bI+zp5nyjvTSTrswSDyJt5CWxzEDzeS+YyUM85UD3VaK0zf8ZnV3IAlENjUM2bsoACVs2SOUuk7z73zrY+/u9IXvVMVDezwrFOmio3/Zl7cS5wGI5QGvKGqs7FrCFyFoxstmrWVDasnIsGP87FZUe4PsMh++vQt8DEXAjOx135TD3PE3Ms8Vmd0hlCjr2cR9X8Tifyr5nljvXGCmXOSzxI5lWp6Wk5Tpb3zbxXn6/lvFefz1Xy3iRlWybHWf2dWKN6PkRZZ7E8D6L+Lq11Pj8y101COutZdkrml+A8pPC3E5V9S+XYSR2sob0crCtbkLgOyTYGx8pA13hZf7ZfPMxyTh1/pEqkzI8Yg1LOElTPRRWxt/tYWYO7/HyYG9IaI+te5hQjU+3j7L1dY2QDKNtid3kSHfMljqLepwVSd79axjG5ApOUa9QwqTeX1VuvocpVyoe+S3uHJKWpfgO8D+G9XJ/keuR67emOqu+Z7Xch3yGHGJT6+xrldP2JQ/X392e5JrCNytNryqSfjsP3UK93d2G9+99ev55gqV9ffUtk9FsPfnBCXem+U/Z764stXV+/1opXKPWptm5yDyH3FsHK/8t4vV35QPq9hOMR2A+PxCRMw6E4HIdjOmbgSCzCo/FUHIWX4WhcjZl4D47FDZiDT+E4fA+PxY8wD7/E4/FbzMcfsQD/xEkYTBlPwEg8EeOwCPvjKXgUTsZj8FScglPwbDRiA5biAizDS7Acl+JUvAen4QNYhc/jdPwYq/ELrMEfsRZ/x3oM4Bia8RCcjTF4Fk7AOXgSnoOn4Fwsw3lYhefjDLwAz8GL8WpciCtwEa7CS/BuXIxrcSm+iFfg23glforL8Xu8Gn/Aa5DzTuVa7lfkPiaY1JvXO+UC3CrnfTsehh/L+f8Ek/AzTMfP8WT8Ao34DZrxWzwLv8PL8Xu8Gn/E2/BXvBd/x+34h5xXCmQZM3pfPAf3w2vwALwWD8ZVGIz34iH4HYbiTgzDEPalJ4ZjOCZgBA7FQ3EY9kKJO8j/41mXFOwUd4hXxScaZL0D3KzXV7XeYlkvVHt7jEEr/1+U/1+ynsMYtM0Sx7gBw/BGjMKVGIs3YwLeigNxFabiHZiHq7EA78I6vBvPwHtwCd6LV+JaOQ/344P4IL6MLfgGrsd38RH8DB+V3+Nj+D1uwAMp8+N4MD6F4fg09sbNGI3P4mB8EfNwK+bjyzgZX8ESfB3n4DZcgG/iMnwLr8C3sVwVr1k913OsprXJ+7hG1rhMKill4v6dFpfpqphMW9beeyQuY4/H+D/OUVeMcbRto3/jHNljL773F/Ml5vJ3jXfkKdaS88i+HR/viN/QTlLUPOIspGJSwzy9P5c=
*/