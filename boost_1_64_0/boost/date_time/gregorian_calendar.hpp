#ifndef DATE_TIME_GREGORIAN_CALENDAR_HPP__
#define DATE_TIME_GREGORIAN_CALENDAR_HPP__

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


  //! An implementation of the Gregorian calendar
  /*! This is a parameterized implementation of a proleptic Gregorian Calendar that
      can be used in the creation of date systems or just to perform calculations.
      All the methods of this class are static functions, so the intent is to
      never create instances of this class.
    @tparam ymd_type_ Struct type representing the year, month, day.  The ymd_type must
           define a of types for the year, month, and day.  These types need to be
           arithmetic types.
    @tparam date_int_type_ Underlying type for the date count.  Must be an arithmetic type.
  */
  template<typename ymd_type_, typename date_int_type_>
  class BOOST_SYMBOL_VISIBLE gregorian_calendar_base {
  public:
    //! define a type a date split into components
    typedef ymd_type_  ymd_type;
    //! define a type for representing months
    typedef typename ymd_type::month_type  month_type;
    //! define a type for representing days
    typedef typename ymd_type::day_type  day_type;
    //! Type to hold a stand alone year value (eg: 2002)
    typedef typename ymd_type::year_type  year_type;
    //! Define the integer type to use for internal calculations
    typedef date_int_type_ date_int_type;


    static BOOST_CXX14_CONSTEXPR unsigned short day_of_week(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR int week_number(const ymd_type&ymd);
    static BOOST_CXX14_CONSTEXPR date_int_type day_number(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR date_int_type julian_day_number(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR date_int_type modjulian_day_number(const ymd_type& ymd);
    static BOOST_CXX14_CONSTEXPR ymd_type from_day_number(date_int_type);
    static BOOST_CXX14_CONSTEXPR ymd_type from_julian_day_number(date_int_type);
    static BOOST_CXX14_CONSTEXPR ymd_type from_modjulian_day_number(date_int_type);
    static BOOST_CXX14_CONSTEXPR bool is_leap_year(year_type);
    static BOOST_CXX14_CONSTEXPR unsigned short end_of_month_day(year_type y, month_type m);
    static BOOST_CXX14_CONSTEXPR ymd_type epoch();
    static BOOST_CXX14_CONSTEXPR unsigned short days_in_week();

  };



} } //namespace

#include "boost/date_time/gregorian_calendar.ipp"




#endif



/* gregorian_calendar.hpp
tMoFwNCz0RcY32PcMkwIbjrbzK9Nvm3+e8kJGzfsTZi/1+O9/haHkWML1aFOzzUeqfOHzinXWe6hLCqJj/CKjzm2qp2LOjOHmSb6yq5ye7Qug4H2rLMMtJ9ur9EOOBXaF5uil5MH29EWKpBFUD0s0hfXw89iibgn/AM7EtH2WPxaGv5l5IM4P3TEbTElrHs+oAzjlw6YEBqJ8fNkyBBaM81oTTOzNZ+3k8zfQm1yKFyLXVo1ZswQvkm0PcHzQ3OyF/qQBrgFyKZoo4+tEBQTCL4oZMnK/Fo3nr35CtieGhaOrv+EEZLF86h3DtxPNeNZq7zduEzLiWzHHHFAGfM/eL1z4P1gzdFifeszHvdxOvexcpw9hL68859i++dIrvGiK7/9h79qI7jd4/gl8syuNP5XZCoq/sIpeirDcREvbwwPJ3/cUy/sRfq8G64TlYkJd193nmLZYsK1z5Qhxg8jxobFyQkW5mA2mZSm6jucqaqf0UZUD2p4WH0fosxaz/jVDJXn6d4izyFQzKb9RfoX6jdY9Dr82IzNtPz+1EJgY9jFqrLLkSGpKAle1l4J1Rr6W4qmDtFlfwA0sVRasT8THIYQLsQqoupuN6s7LbI6T/C7tvaDUAcqc71ZphuVCfUSF0dupcajEwceq84tQ9rZQCuBs19pfQe6iS/pBecMs4YnU42i2Gk7RDXzuTO4mUWymb3ypZRKaEwQwCwT4MU2gL60KmHl2YxR6JXGcmWCtxGwTOBdNs8hH7DUtLFUyjvnVyfztNpxhlHpRLqLZhjDqLzAencXxrpYzOfje8gQP9NRL4/lQQFT+aQxBrz7vCQrusicxak9dDIL+0XCf4e7nij+R6+M1kcqeafjaJZ3gjWwhHH6RrilHxpianfeArYEMX4xeymYo+8KhACR/gql9LmABV9aoqA7cfP+H4gaVLS07F3yuQyLDdKqkXS4O7T+jdneYsHGHMHtVa9egL13HSNYidnHsxSET2IFimAZFNfuBkuCT6QhUWrlzPUipZxTxtK6BAGIW44A/IR7y9nJ+OleAQrpxUyl5dpy/2h6i+WeZ0CyGpUmbocGqUNbtktwrKdLok3tc2cZLEaLLMx5WkXmG3wd2UWXwiN8rSRsHZfT4mrMQeVha3J0//NcMJ3pgWJp/jYwFZnwya7MzlZBemkLOmEFPaAvVjAVY2oFW1BwuAoq/yA+y0mGrz6BmijnKLsBgz/xZSi1bAwBXoadq5bmKmrV6HkXbAM8VQ2ccPjdRjAXmhA6yAZ5reDwJf4WljdGdtqomDRyL6JybnE4QdR6gRLSABld0A5ViId8jHhFPpZdgVuIuy45DeKu2yHuKtXirsFdqOd156boKuA4XyhJoSbFBQpohQyth4B2oR1asPNBoPlY9WKl6Keli5mMDx+CJQdKAvEcBVaj5JneZ5iVhRtUcaCrd1Hp2KCBVDEjdW0RkFprR+p0Qoqq3+CIDYCbSO8rqa4e/onccfL50BiMAlltgJVHTCepqdJKlhDi/EqnJoeB1pyQrogZ0gwHTBgdbe1PjPQ07zqaBZUem6kwMRM8ejGwmscvyTHnT/RXUBmDPleK829/O32u4lOrmiU0FJX85Ve6PWW51hQqo0dkPLH01WeCU30qYlbfw4XpKbLRc+M6p3HVNE3qEPIl1S3CP1qgwKqADTG9ncDvIk/BHLwLc/BiPQd3dBRz8EmCugWlUOEFTnVdqLZOqcUH8iNnp7DzxrizB0mJUTa+SvyKMJ2nOdNJwRVAT6L0EaM042SgNNSO0nBGKdsJUkrAyHThgmsoQWpsJs4WED5jCIMEhOfsEL7rICB8SN/yFMi8mtWMbN0MGlhM9fOwXU4=
*/