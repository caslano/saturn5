
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_REFERENCE_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/function_type.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_reference
    {
      typedef typename function_types::function_type<Types,Tag>::type & type;

      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_reference,(Types,Tag))
    };
  } 
} 

#endif


/* function_reference.hpp
hZeZabRpMiT3VewGrWOOoVrSiYTf2kavbtFYXAsfqgN96bxB400Q7q9LTEZDXw0kK4vFuUqLWgzVWFm7VawmoM25CxCXjQrROtJXemCTaRJSHFOfo1J2s81bPRw2ha1Fq8K/wh01QDONx+4STNojn92YewsIwdXQGjSQTOm7Pt7CH1MQz5se+/vvUYN7T6YK391vKYcWJZJUT2RXrusrbB930t/aWGvgPVQPCIHeEI6fYdAMAqAxdIYw/HOFYPrWo2iTyZCsM5ibBUQZ8aeukk3unulJ30/TLID+IJsoHU7f4C6E8W0/YrY9rE2e+e9m4s61hA1hHcjuTu0hIGwZc2lZGAlrv5TYO1SHXjOCSHrHErDEepoUnNwYRlx/TIpMngaBlXbBxsdhMGZaPWb749Jk+IphJH5MZ8g8NQv66qqRvyQtgI/6B5P717YzwUXXwb4Hk7h7IVvJ7bR2xJ+0JiHfreeyjq6B9EojOZ9Cp8nDgJ6kz8G95MTEF6SiWku2nFrLlYrRQ9SxRUwBazwoV7XjvmppJD+vK0XKbF0BMz9N5PqdXkUswxYwtxqugNGq+8zpu7fhmwK/QNMh7UnBTkeJYoiR9LpdmpxJ2UGC596D0vUN5FqfNCag80RSakhhCEhiSCSznKk1rxrxXb6JadX/JtEdfwX1XnSFQysiSInG90lkz/uw7XQPUmrqc6gTGUa297FD36sr4NOfjjK7jywjH3cKI99c8iVTI+OZsF8ewb4lFmh8dh4saPCQW5CdTL4r/IrTGk9CiQJfwK37S0mVuQsZ3cwihFvUhev6/CrEVAuAzm2yyfcVkpkxncaQHQF9iGrNZFLnxV/BGpkN466nwciYWTCg8354HbYIqpB0SHvBQacejeH62QZwLWMzM7tzA/hwxD1mS8peEt38d9LMxpFmWz4DRalvoFN0NvO0TTWo1bE5F3L3e2g04QmzdPh5YI1lSGD5z2Dz6a5wa3UcPLrfgmndfzJEQTT5MFsLf/pzBpc8Yjus+7YDeVGvD8wbW5+Je/U7zJ37Pnd/fAdgW30Kjb7YRv48fg0zru8J2LLmY+7FihKkc1pZcmFzW9Kp0EMmpGA36PupgWv5RX9IDfyFK766PNnTcAi5P6crWfbRSLJ4JQPN6t2AGR1qwGTTIGZTVAhMtzYGzVxfUuFqJWj682VI63Gb2zm/GFmvjiMlileCrN3PuZCdbeED/17cyCHt4PSDL5llVzrB8aXh4B84FxJ6VoJ7n54ip3YcY0IbR0OZjvWYFocj4K/jZnIrTBXItzUCuK/qHCThT21w7Px8GJ/1HdOmYUX463ttmW2lX0HTa8cZ+xY7rFuzkQHLL6AePAue1GsFI4sf4h6vHAoNz7Nc9O0y8Dx7H3N31G0yrcN5GNP/NGk5pQDXucz3pMSh75hau3+GJs0OM3V+/wwOVy7ILepXG34OnElGDj9D+rSrTr4qXgjOPonhXtVqBy1PZ5PxulaQw5bmZgXdhkozljCW9JHw7NUL0A3eQ/ZNvcw1q78eJhYrzKV+fZzsvbuLedjxE1B/2oTMD25Jzn5Wk+u+dg2c7dSViRmWACfX/UL+VP8GuQ+fwJOeG8jgXisYv1M/wVeDukLg4GfgN/cv3N5jnciqxyW5JeoN0LT9A279oN2w/2pB5kCBUmRSo1+JYbYSBkT8St57vydp3vsI8+dy6UR304/5U6VgKHAghtRYPpnMudQNFMcqk4ZPljPnfi1Fqp3Qc1PvnYesyCeciSsBF2K3MxcLP4SZYSeJ4cdk8r59PkwPUUOtqybYUWMnMZ/ezlnnzYXyiTHQrPszuLx/GndoiY4c1WxjniT7wfXfq5Hys0PAGBM=
*/