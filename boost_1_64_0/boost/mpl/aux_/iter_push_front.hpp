
#ifndef BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename Sequence
    , typename Iterator
    >
struct iter_push_front
{
    typedef typename push_front<
          Sequence
        , typename deref<Iterator>::type
        >::type type;
};

}}}

#endif // BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

/* iter_push_front.hpp
KM73Jd8zzQPrlNMRYGD5i4nnWRGE/ED2Blg2/L1NoOFfd0P7IL2Rd92t7CVvH9QGOn88mB4X3ud8XJz6pANhhM1502kHnDXXuqFxI286lCbedBTBX2kArDSuvDbx5l8C7GjAzRzRG28qxEvmmiOZNv3tdgivm+jbNqPnDZN7rQ3ea23sMD4WMzqIge1jcT7K4OzS8IVx4UtjB+SjTY9XJvkojmv8a+Jb7xaQd1Dbsw0FJbtQDLYJg2GNM/7B1/Z/u52kxTGwX552gmKQT9Y434pNc7dDvwoJYEcgn5Hw8EXFB/PwMYPgnQTBcvGw2LAjFoAujnH4UByHD9vZgLd+VGuTCRr0BH58ShCTjn8WgdGQHNExBvBx9IvR0HRkL2RA740cGQSkBEXyrBTBOlVKWCQrQpvJTuyZci+PmjC8SmTPUr2VSnL2LCZ5qKno3krDXTpbO/REVsS4v2/W0HZIkas0rQjzvRwj8cb4rM6Rq7We6aWF1UsmDBZ1KnxaPWi9cmfaiv3ihvePFNZtrUns0j9bN6Tyw/GGc5vnjYhyyEq/kD1/9Cen7LzhP2LWFbz8TBQZ9GvN0id0+ALAfUrCnt9T986z3PB1LXuT5NQzaxKn3luV8HGiwiLVvb5zCqdNLx5fbbBDLvDzyGEn7t9oWxqorZhmc6fVtObciedpa6QUzQJXSeXEWK1UO3EtReGxlqvhpWf6x1MDZwT6fdH0a9542O9Q8FbnKdbyLYyo8Xf8ztAOjzSeUXa6vMVG5niGb96GN4npMvIfC0YWxTNm3jg46ruhInuQ1YxytQ3Lto+58Oj4jIrhMQt9jGanZGzS3uq81vz4eddo5ZYr1zdoaIeViT4JWndQozPwSLqz0YL3M2fOXNJ6MmnpG9KwEc+XK4e+W2i1YtiNI5urvsTHSo+3/bp4kb24HoW+ZO/EttuRs7ar59hG3NTYFvPme9AOifC25VWHH+R6RUXo+z7RPiC9ec8Yr8Mx4q1xTeaz5TzbzC9sHdk5TzX0U14y8fh4q2l3wpZL2S1SyviYeXpXvEPJviVzL89aZf4kKb6eRb+2dJf9EOv9UdcmBx+qchdKmTAuse63siVpu+3wx5UmzrJilVVvpWu2X/3kUproIzxHOXvBk7SHmj9etHwf4vm70dwt7cyl+pgtF4SuUs54HLx2PXCXdXHOjFmM4VFKx+M7Iwp9YqzenRovF//e21zd61fs6E0G2+0dFpaJXpp1nFLZeLlr4pgXwtrSYQWuekpT8u9elWbfdhgfIP6gprPq/KWraX5iRoFDbhLyHqUljrb+rbkrvGyPemf7m31r2oca1dQNSrJQiA7quq3mqX/Ym3q0o9DSKHDZsC7nOYY+i+oIVhenzMjJzYy/ozd52ZCayMF13/Ntq0u652nfNAo/wvLzyDyh5R95e+qdizP3dDfkyrSd22rZQTu3WKMrpvDXRP+q+7ppTT7bQh3azxS5rHmQtaXT9dnn2oYx8+7utZHrDG652VT+7A69leiWMu53zrzK0+qfRk16VrNp67qsYwlrjr7Nrd4QXXl/TWW95q3j+v4Wa85uTFrT+fL72pBRsp9lzy1frtImmZU766iHSsnaiHWfKu4fvZZfoDhUXz9lsNTl37pJb/PUSauky3JftbDjCx99OaKY/XJFeb1H/umz9XJdC82vpz/NP/ogbHfAIGrKpgXyrLINKfJDNELpR5szOgpTvtn63qoYu7NT4vi9d7krrOZUKds8cpmndkxXSpMwqyCBfpEQMfR4/bkp28eFDFc7L9qmuo7hd2h/3bQVdtdS5/tMf7rbfy79xvlXpGTyiMUHKzYFRyjdlrGZyHK/o+tUMPGg/Bxvgpc=
*/