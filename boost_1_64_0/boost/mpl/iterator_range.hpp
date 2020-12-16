
#ifndef BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

struct iterator_range_tag;

template<
      typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct iterator_range
{
    typedef iterator_range_tag tag;
    typedef iterator_range type;
    typedef First begin;
    typedef Last end;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,iterator_range,(First,Last))
};

BOOST_MPL_AUX_NA_SPEC(2, iterator_range)

}}

#endif // BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

/* iterator_range.hpp
3QZ5KtYDLtr/Cfg15InuQdjCiTXJh40GU9mjYiztfnRt8en9cEgcehcnplfqd+844+ufS5zt++81DU+sn/Y6on398tS+8et/u29i/BcdHtt/akJVjs++n5j0ZvhvX8Tv5W+E/14XkV8Vga/xrfDf0yJ+Z0bmbw/7be7zVdNu8V7dc5EejoCviYBv+JLgzavHxuAI8iflfynxTY2FzxzO+ebhcctPTlXlD45Zfgznm98cG6986l6q/N8HxGrP0LfD2/NuOuP7U1x8d+yn8N0eC595DeebF8Yt/9WhqvxpMcu/yfnmgXHL/zRYle8Tsz3u8PFgbiN4GrHHxMO3Ok/h29g/Fj1/4HzztrjlDz9Ilf99zPK9ON/8bdzy12So8r+OWf50zjd7xS3/uO6P1FjlK5dE8ONa9M8rY+Lhc3ZT+J47OBY9Ozxcvjxu+cvHqfIzYpWvLIkYb8eOw/iPi8+7s0mN/5j0NP7QxOP/6Hjlb3Hp8X9QrPJXcr75l7jlu4UIf5i65BHm0djrlTmF2hMOX3NIe/Blrkj4Fe3CH5EWCT+zXfjP94mEn9Au/KmDI+Gz2oWfTrnh8OaA9uBPOiASvrJd+Lej4Be1C9/fGwl/Rrvwl+4bCT+gXfgdXSLhW/u3B3/uMZHwm9uFz/4+crzd2S78n3dHwhvtwo8yCV6v0nOPSqCfmUtBv4I/JSH8k7vt+PdPCD+1qx3/l6MSwe+9tx3+xYTwdO5ng78xIfy9B9vhz0kIP3t/O/yvEsKn5Njhd41MBH96Nzv8Gwnh7w7jz30J4Xuk2OEvSwh/02g7/DEJ4U9usY+HvRLC72izw390ZBL7B0eYfgf7Dx0pSfsvnju9MA0bGKDMGKYsWnkGvzdh1L9H9oJrKapUf3NrH+yEpcVYXoz13ZWS39iruJlfMypu1RH0hx0sj9/n5hhjNZ65wLPAjgd+FnNOoDvYd9GOlS/sN/d9mfaQtDvQL9HUK/eBshzjNxrZPCA7MgwZDvrYVtHwlHLLHTNUtegA4zRdeDYK7+xtLxwiKnyxqcAL6jYqfqcRlQHRn8MQMQcQS6SGlmdV5EJdZA6KzBVFkre//9wfK/5Hrj4vNa8ibtkdkIuYMBoXp4Nat3Iqxq67H5vL1J2WU7oqK0937VksrGp7wThU4gWCDhjQrPhfOdgvwjunu/k5TXkE/PChap+d2snof3kGUqjs1H3NHkQcdSWob6Vr7/rsejDWBWHCNvuqJiCrB3pwDNXWSbuU5m8TCUEzSCuLndQCHpxwzKdDoG9HKGcVYUn75GseNwx2MN8NdTAaZfPcKPJk0I4JyZNm3f8mejA11nZB46Tw/1aOVXnpxZxLuiyY5gHTlJ32AxVq6HwdjG79MEX+vv4rxBi/jP7rb/6hJ8Y4bI9W+Dp5M8vHd7Rw7o8jg5Z+rGqugg98NqFyha6WVxSmaIG3tg40IrdYXwXX0Xz4coY5Qtg/R+W3lQ0SAzRronqfVMS7ELiutOHqFnpBjJm+yk593QFgDV5jhVGnAwO3kx/ln4uXGDMUW/pQ30P3jt+fwWyiVZecwZ1TRgd8Ph0gCce5wmjOhjlKCY9NhCgLT6Zovg2lQQdfA7MyRfGNz4FcQqpd2191N+Z3l9Bz5Zs7YWazzn/IYOLfrTt5p8tumi7jWZBPXSzWlTedOuhfAT9Wmz1R3chBI67dCwMOZX240uzrdBgTu790L6JOn7f8yeWIc74Er+o8ygif//sK+bUON/6EYwKHKxBukoE0mkObXOisfpRUPtJJuYhRxUfQTpozUpq6OxYBQ9FD+kHY79xI+gqIPuU3IA98jLscarWa5r+cZnKVYCwCQAqniZ3NkENjphNBJdk=
*/