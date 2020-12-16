
#ifndef BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::set_tag >
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

#endif // BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
1TDmlrWDdxgLy7nHjbp9mN1pzFla1v+Btecx5wFjma+zLi2Med/n4/wx1O3Hx1FrxNuZj/2njQXk+Wp7xDuW89sJPsuaia6I7e9ctwfsyh6/ySgX5Xj7GIuILv1gQ/anGQxf4vm+x494Zf+IUYhjlcz/GXMUk/V/8G+yvP8LXY5wzqdCZ9HlbdSVdfDvwmd5/jEXsYnPi9BePLe3DO014XPoKmM+sbHemEfYRsRbnM8zn6CctLfNmHuC7P8H/wpw3X3QVPQ7jNhkzD4On2XfvBPG4lZw/zttLCR7d5w15pL3wX4Ek/Wnl9BfZN3S7/D5nOz/V9rsyt5ohYx5vuVyRYw5ZWy6xZhb9jUtBTaV+0F5Y75OfCy4jIX2cmzVUbcw26htzP8st1cf7f3Ox2VjlLufj/2mYI9zH7/fmFfWPD1kLHqAtWqJcmXl/V+ww1y3jbGAXMu3MxZ5Svb/MxaWe4N4Yw559tQd2sseBr3gXw3uaz7koyOzvtBU9pEbBP+Gs1bDYfcTZi+CiX9jwORZ2wSwt9i/SbD7BNd9w1hQ5l/eMpaZxDrPRF3Z83sObLzA5Rain47hvrEUusg+aCtRdyFrsA7ay56KIeRS5gk/RnsfsC6fwT85fndC+2Lsy17YfZxtHDLmnm/k2vk/1G0q6/+MuWQ/Whv+7d6UbXxvzCPPU86j7iOy/x9ikz3sLyOO7Vw3TxmzsZvHtYLG/PfK/B/KPS/v/xoLTJb9/4y5ZPwrh7p3sS+VUU6e5VcDG8oa3G4sszmXq2csTq7HG6GuPF+4G3XlnuQ++LKU43jQWFj2fn8Uscl8Yitj0eIc71Ow+xq396yxoKyxfh6ayrEah3IyV59oLLSKzz0vGHNKH0qFL/I+TgZ8voc1GIjYZE3MMNSVe+K/QtMlnPOXyvzrvqbj4V9j9u9V1P2ctXod8eaX939R18N2Zxjz5uHYZoPJdfYCxCHzL0FjnoZcdwW0ivAa3LWIV+aHPjTm+5X7/WbUlb2ZPzXm2My+/B3xSt/Yg1zK+smD6H8DWYNjxtyiwZdoT/ar+ga+jGR2Bj7vZA3OoW4lPr/9hHhlvuk3+CJzAI6yVleerxYwFpH+cpMxrzwbu9lYZnlmJY35Zb+Wssbc8kyukrGQ7CV6m7Gw7CVfCzYk3rrwRfZbamjMIddSdxlzLnMQa4Z45Z3l5vBZxthHwOR66C+oK9eiXmOuSbL+z5inLl8rd0C5PMy6oNzzbCMBdiXeJJSTNVkpxoIBmf+Dfhmy/g/6leZ1KEOhy3AeY0eivULs32j4EpH5P7Qn18+vIB+LOB9TUE6+LTEdNmRPxUzUXcztzTLmWMt15xsLnWddlsDGcJn/A/uJ21sDu6kcxwa0V4iPy4+Qo494rNuKcrVl/s+Y+wlmu9E35PnqAeiXzL4cRd0BXPcL1JXnxF8bi9aT93+NBaRvRI05PuJzykUwGcN+BRsr6/8Q71+Y5S9nbBmPGzca88zk2IoZ88va7hLGInL/VgblLuUhVhHtvS3r/4wF5bxf05hb9gmsYywg+9c1gM9yDmhiLCzPXe6FXVn37zEWHcL5eBjlZB7ucdiQd2WeRLxy/dzWWJz4YiYdvp7c1zpDF9nnpBtiK8tzFD2hy2k+9nvD51TWIA02PuW6/aGf7OcxBLHJsT8CNrxc7m/GMmV/0Zeh6d+4bsCYQ/YGeg3tLWJfpsEXeVf1HWjwrsz/wYac8+YZ88p7NosRh7D34Ytcb6yGVv1Yqw9gV+ZQNsGuaLAF+T3EOd9uzCV2d8Gu7BOzH+XmchxH0J5b1v9BK7nXOAntj7Hdb405z3N7PyCOEezLBWgl16e/oE9G5P1flJvPPucrb/4=
*/