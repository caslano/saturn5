#ifndef YearMonthDayBase_HPP__
#define YearMonthDayBase_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {

  //! Allow rapid creation of ymd triples of different types
  template<typename YearType, typename MonthType, typename DayType>
  struct BOOST_SYMBOL_VISIBLE year_month_day_base {
    BOOST_CXX14_CONSTEXPR
    year_month_day_base(YearType  year,
                        MonthType month,
                        DayType   day);

    YearType year;
    MonthType month;
    DayType day;
    typedef YearType  year_type;
    typedef MonthType month_type;
    typedef DayType   day_type;
  };


  //! A basic constructor
  template<typename YearType, typename MonthType, typename DayType>
  inline BOOST_CXX14_CONSTEXPR
  year_month_day_base<YearType,MonthType,DayType>::year_month_day_base(YearType y, 
                                                                       MonthType m,
                                                                       DayType d) :
    year(y),
    month(m),
    day(d)
  {}

} }//namespace date_time


#endif


/* year_month_day.hpp
HIx/VvSsH5/Xe9bknGKk3c2gJYP/SJ8bTkKGTaZvlWcwAALlxjLlTs0gyj2agZTLPwUpp+YxMlXkQK2VGZuHMcb9WY0PRYepQ9HdOSOIuR5sNZuKQ1saS5c23g/puN+OIS/3ntXkcudrTaO8ANlNdZhwvTgkoSEsZ9/XFaALt8QRbY1KZgQSA5EJ6KB6z/6uwMgkarTIcb39quZRrogS8kUJLtsSkKoL2mZrNfy9xQeYuwCibbHMEiAqFYiECAg3QAxWIBIjIOIA4mQFIikCQhPV9KDf5bZ8iI4RSU7sV9VXCxR2Wy1gkiFpslFBEeyFpG+12XfSlpg0stR4SDrHJmmxkjTFvtQWkPTSKElT7Uv1AJc8cHUoxC1P4yBs7MWQW2Hcm7DBXeNiemmpLyS3Kozj9iSbjCnTZKUlFSUXY85Yg5ps3fFSLvijtqefTwYb1RFBPhOkRwaby2ivl7H+S83Abb9QvqS1FWVX7Cin6dXJ/9I5lHvrZbwVsqLcrXZKbeqUNBAdIxuoPfKlrazIu+2Qd5kq1lIG2/P7FKiYfaNPkMGRyCeYIL0y2J7f73xhlOGllE1F+do0K8pxsaMs+F34hXMoC35/Uq+ibM9vtxxV7JEfkWpF3mOHvNtUsRQZbM/vc6Bi9iNVogyORD7RBBkvg+35/XnQKCOeUjYV5fEpVpS9saMs+F0SdA5lwe8fPldRtud3nJwK7JGf2NKKfLwd8nGmiqXKYHt+D4KK2U8vSTI4EvkkE2QLGWzP772fGWW0oJRNRXlmshXlFrGjLPhd9plzKAt+e1SUG+G3FmVwm5VkRd4XfTJLjTJ/X/1pY8gnyuBojd0bpX+3+NQ6uDUV5fmJVpQTYkdZ8HvMJ86hLPjd9pPo47kryuC2IMGKfGL0ySw5yvx908eNLV6SZHC0xh4fpX9nfGwd3JqK8pM+K8pJsaMs+D1tt3MoC37n7I4+nrujDG5LWliRT44+mbWMMn9X7Wps8eKTwdEWqy2irM+P3GUd3JqK8sp4K8otY0dZ8Hv2TudQFvzuvjP6eB4XRTip9VqRT4k+maVEmb/nftTY4iVBBkdbrHqirM97fGQVTpqK8useK8qpsaMs+L3oQ+dQFvzu+2Hj8hi/jdoTDjdFLHUBGdbFOSCJP/iBc2Kp4PypH8QiiSPKW90OSOJP7XAOZcH5s3ccmCSOyL/tckASf2a7c2Kp4Pe522ORxBHljzUHJPFV7zuHsuD3n9+PvnJrXCxl5D8LZzW/JL76PefEUsHvS96LRRJHlL//Pav5JfE33nUOZcHvq96NvnJrXCxl5H/6Lav5JfE333FOLBX8vvadWCRxRDnut6zml8Q/fNs5lAW/b3w7+spNizK4xf+a1fyS+K5tzomlgt/jt8UiiSPKbX7Jan5J/Ou3nENZ8PvWt6KP564og1u7hqzml8S/3eqcWCr4PXNrLJI4onz4P7OaXxL/fYtzKAt+37cl+njujjK4dfk5q/klcdcW58RSwe/5b8YiiSPK3fZmNb8knvKmcygLfj9WF308j4sinJz0U1bzS+Kt6pwTSwW/n9wciySOKJ/+Y1bzS+IdNzuHsuB3zRvNJYm7gQy9fshqfkk84w3nxFLB+edej0USR5T7fZ/V/JJ4zuvOoSw4X7vpwCRxRL7ou6zml8SP3OScWCr4vXZjLJI4onzxt1nNL4l33+gcyoLfda9FX7k1LpYy8oP3OCCJ93jNObFU8Hvrq7FI4ojy8G8ckMT7vuocyoLfOzdEX7k1LpYy8td87YAkftYG58RSwe+P18ciiSPKY79yQBLvv945lAW/96yLvnLTogxu4750QBK/aJ1zYqng9/evxCKJI8rTQw4=
*/