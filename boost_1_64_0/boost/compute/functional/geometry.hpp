//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP
#define BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP

#include <boost/compute/type_traits.hpp>
#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(cross, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(dot, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(distance, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_distance, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(length, typename scalar_type<T>::type (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_length, typename scalar_type<T>::type (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(normalize, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_normalize, T (T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP

/* geometry.hpp
ugS3eubIjRo3yTg+auBQgAY/t8B21Rg1PzDqBYNRbQJWs9hRbqO6xLxyQn7HFLbYEVh23GA3Er51EVZV5Aj0WgKnyvCaKIVThdT9niTnKPBWhLvKYU6NcepGxvMIdxMK7DWLu77i8WVxXwXMpxb3bY/51OJ+csBcJPvNYUuYU1YEdlZZMMayiYDRipUcO1dX2c9w530B44tV82fWSb6ETnk/c8KWduDAjnuq5OSnaXeAYv/0+czlzgHvLnbmqvL10K4KQ7+zP53Cq0a7MWRWYdQohF0K990DtrZYynn4vie+30TI/+brxXdnut0Y2BsYc03I+TQFtjCSrWI83D1831gYad+44YcLjweF3/TGHmedI3EHLgRsV2JG9vckZuR7X2J+fIV67NyTMWqvJeQlv1M9lF/wrMCcLUuNJ/yYnwqcrsHSwOBYoHwvbwiHdtjWCb4J7K03gtfNO2uL9CI717njMfc8CjWWKKPCMIctQ+cpvGqwEY9RK0iMGowwjNunAZNjHu2ZB59zN5ZOYyzJ79Wz8TwGtxRGtp2cnyR2o6PqdzsSI5tR/e7dATu90t1YzXu9Vd6LefglCaP3iccmToydqKKI33V69PY+7irP882HDuF1++yflE4rxLe7CeTlyIWJd7vx1nS5YdLheVR/L1uVz6qr2Lm3H5sYm6JbwWXs3PA8WHYa64EEh4rH/nCPjHD13lsjwqtzfuD5oyJ8cSDwbYv7VsTdpgj3b0X1SelOkDoVsRBrj05zT82tDoi3hjlR1Rkxh9sYo3E6VGURH/DPlzA43jDDnaydOI0C5V7X5W4+JsXlcmPeeYnkTd/12MzUmG+uAWz5BMdVjzn7SQ5VkTgXC3nd+ELEucOdR49no7CPbhq+sfc95tKbSUzHeM6OKoz6hPRdlnWQrsapIOIOA2Ps6S72E7dvDlx7ulNdoI9uAU64RrOEeY2xcpOT5eqW+B5uNLDdcBtg/iYDp7cFTN85rd+2/D5+Ymy01LM4duK4AJMBdxMTGFQPyMoUOKRvweD3vccCDuwM2mkaWM+mDz0qOHnpgFiw72DtbsD4GK467qJxhflVcSgH5uB9zZ+enTgUivxGI5Wegd4P36lo5Xe0y9tLWaPo34uL1PfF8ZVed6Fjxvzu6xMcM+br70hw/JhHOppzu7m17uoZk9ce58Uck9dBKh2TV/YexZncmJpbX/YVg7xzXszxFcMaIJ0OZcac1gcUh3OSdpXOCzlhH0GngVzUnfPeJYlTxqIo40PYt/NZj8120zw5L2Z5muPzXMO7rL84O/FOThKJfp2NB/219YJyLN75BE343cA9eIr/5tUAbLinhe/6nKO2Fb7P0A3/onyYBVgDmFcB9OdiAXuDw25CtQh5tF7ov5m8ay/2303eOb7HeW8Bi/M+8HkfHxF+9m8M36D/kH/zTcCU/tvEd84E8+z2JQmr5imKYzU9MzVKHTONNy/XYCe9dDivfXyC10qvSPG0LGy/JMUxspBMR78XsH/n85ScKv7W3ccnbjRCKz3oT8aCMxKvM+8nsMFaToeuPfq8jrHSNvhSznkyFr21W5tVWIjRtg4bUuDLLtTCPB3kqTQac5pTdKrAicB3NY7VBMbTPPAq4pKMoX5gMF9vnicXNE71xthqLAJT77Ht3Pns5fexmenjo60xF0hmeuwud6WblN6cYdto/xAu9T77rQ/nBVuaz1t/rbjTrTvRbO3yHcP6J8WRPpO/iXGfzxj2Q690CcMZb9PUW06epQl/muPLpnmddceDHqc8DS+Mpx78V64cp0V97qNxst2/GadF1WMbeCvGdVyh+0d4MIIfgLVNoiyFKAvs6atGvODz8gD0WcwJB+k=
*/