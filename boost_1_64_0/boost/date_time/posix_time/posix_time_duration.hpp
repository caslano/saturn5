#ifndef POSIX_TIME_DURATION_HPP___
#define POSIX_TIME_DURATION_HPP___

/* Copyright (c) 2002,2003, 2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <boost/core/enable_if.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost {
namespace posix_time {

  //! Allows expression of durations as an hour count
  //! The argument must be an integral type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE hours : public time_duration
  {
  public:
      template <typename T>
      BOOST_CXX14_CONSTEXPR explicit hours(T const& h,
          typename boost::enable_if<boost::is_integral<T>, void>::type* = BOOST_DATE_TIME_NULLPTR) :
      time_duration(numeric_cast<hour_type>(h), 0, 0)
    {}
  };

  //! Allows expression of durations as a minute count
  //! The argument must be an integral type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE minutes : public time_duration
  {
  public:
      template <typename T>
      BOOST_CXX14_CONSTEXPR explicit minutes(T const& m,
          typename boost::enable_if<boost::is_integral<T>, void>::type* = BOOST_DATE_TIME_NULLPTR) :
      time_duration(0, numeric_cast<min_type>(m),0)
    {}
  };

  //! Allows expression of durations as a seconds count
  //! The argument must be an integral type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE seconds : public time_duration
  {
  public:
      template <typename T>
      BOOST_CXX14_CONSTEXPR explicit seconds(T const& s,
          typename boost::enable_if<boost::is_integral<T>, void>::type* = BOOST_DATE_TIME_NULLPTR) :
      time_duration(0,0, numeric_cast<sec_type>(s))
    {}
  };


  //! Allows expression of durations as milli seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration,1000> millisec;
  typedef date_time::subsecond_duration<time_duration,1000> milliseconds;

  //! Allows expression of durations as micro seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration,1000000> microsec;
  typedef date_time::subsecond_duration<time_duration,1000000> microseconds;

  //This is probably not needed anymore...
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)

  //! Allows expression of durations as nano seconds
  /*! \ingroup time_basics
   */
  typedef date_time::subsecond_duration<time_duration,1000000000> nanosec;
  typedef date_time::subsecond_duration<time_duration,1000000000> nanoseconds;

#endif

} }//namespace posix_time


#endif


/* posix_time_duration.hpp
MHGOxbHVrAtsPRy5O54HOVe8/1BTsSLjU3PW0KpUBz8+dfzzqQOCwjal71Lfo3765M5ttvuzLpFHEcxVCHH9Je2PbVSl4tmJMiqWKWAdzqFxTXajCA/9+6Mpm47hM0Gf2rltl+/eKtL+g428bBR7ww8dYjoryNcJsUqKv5po/TPp2MyS9pDu8uHlkKO8XjW9yHzx6AeKComS8H/MGX9ZDv+U3KGfAfPEhPpSJUYJ9KD82HIQ0iMDJ8txklQ83zzD0HYiDkZ066B9vj41itTupZYLc6bRaj1bqd4umUFvifz5oH9eqYZcF/3wuBzVEbyfS/tLhjPP81F/0m0Cnp4ARJBrGZ8ThXeLUkEuFYRSJ4pS14hSES4VgVJ1UIpY8lGhLC5fHSi8To1ZcF1XRdJ9xStLIeRB9XMJ68m+A/P94c4iLMCu3vT7YbXJ+xcMGSYSIpBQywkd0Sb0koMDdm/pxeYh97OXXOtRg/lcJH1Rog9QkC+dJPAKj43A8z02Aj+kEmwbnU0xT9Jm25DJZLRq2gXHvTx776o68n/4hWbH/vcp/4dmyLk3o8W61BCMIx/HoKY/qAiAL6okX0f7p9yO+i+NHiOryUtgDjrIhBx/06vTN0B6GIws/LL9L0ChjI7zoFfcYgvch72tSUDur0MEwPTR+/F9HG2i2qZoGCnphDnl8X6FoZMurGtSVF7shSIQbkRSe7vSFkitzcLuKN9MtNoDGmA8CK+mNWHMSnrp0h+PDFXHIOWJAopCUpP7AiFSt21wrFiiUtDOFTZqOWwIBZRrThDXEp0k1qL4/af/9cdtxAW4C7WhK5p/X9JONQow92yVq5M6DkTKx4K7HiUd56PGzPRAIJX4po2gEdR5nsMpr1blydtsg4lOjnfPN0HtdwjffiWDtLSNd43MEs+WGw2RKcS8JyvgPI/gHGfxdyRHC1DRmz4NpmtK7bC29HEVEMpKjq63aPmRkONKFlJjjJ43Bvha3QS2F4N5qtlpxnSxhFEsEwP8gT/jKmamitfS/t6O1+K+3vrLRGOUiac7KtSLMLgFdfIUpTIg1xScRoOZa6Hq3aAntQmtltzKQIuvi1ShnMP288qXDJcJCHdaGaBjNeh+usg3xtpoyI60KT6h6mfUd1GSJCzt586fLfs73Ge7b4TvI/rt63nr8dR0ufiuQZmXqrVfuvIBkFXmHttD/jT4tbTjVatTNKl4uSh/Kia0FjmuaPdBxWp9yQFZ8/R58Wv8Oh4VBChFnxRzDWj6feHcsuccP12myuxQNkdlR6/v4dKrG6oRJXVgCxem95C4dlTEygzqAUang0ERTuDiC+YGNPM6KykMxepTxxoSAAS4FUiBtBmxKanDMahIbol7umvzr60I8QwWAg7oo81v2FYEdBSs6h4NU0kYE/urBbPTt+7NIeT4uHaEjI4LElAQGuHzP4tF2FWIzjTPUkkpHfgL55RyfOTVR5O2wo0wBkyH2ldg7WaqDY9cu1nXnuxUmx1rM6+rCFbgJ2puPJ1zaK7PL6BJGzLIK5hfuZvI8gypsq8BExcRlqNoDMCY+1+jmn8bcG0HBAKH6rvhOSKCgu3YjOWoJXAwRleeDBFKyLU4aZzIYbin/eiuNQLtTd3wEsx18CRym9ZWvyRfjt4urtkXGTRLISCvLWe9JSFFyfOLCvtshTcI+KK4hBDiezahaxilLMwQRPEb84r7HEnxivLrncpjzgbKyTwNYwLY2I1sdLzcPpx/WX0IhZ3SuHeLA/yCjuxjRqj8Qgk+M9qeUy8oht7T9+a+Wz/3+cxT66BfOv59rF+qes2uX7qwkH7piXG0uDrWRb+04QAqcIBdtTTrb/2OqqX9Xxv8dDg=
*/