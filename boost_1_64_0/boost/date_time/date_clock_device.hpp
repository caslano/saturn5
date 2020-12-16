#ifndef DATE_CLOCK_DEVICE_HPP___
#define DATE_CLOCK_DEVICE_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/c_time.hpp"


namespace boost {
namespace date_time {

  //! A clock providing day level services based on C time_t capabilities
  /*! This clock uses Posix interfaces as its implementation and hence
   *  uses the timezone settings of the operating system.  Incorrect
   *  user settings will result in incorrect results for the calls
   *  to local_day.
   */
  template<class date_type> 
  class day_clock
  {
  public:
    typedef typename date_type::ymd_type ymd_type;
    //! Get the local day as a date type
    static date_type local_day() 
    {
      return date_type(local_day_ymd());
    }
    //! Get the local day as a ymd_type
    static typename date_type::ymd_type local_day_ymd() 
    {
      ::std::tm result;
      ::std::tm* curr = get_local_time(result);
      return ymd_type(static_cast<unsigned short>(curr->tm_year + 1900),
                      static_cast<unsigned short>(curr->tm_mon + 1),
                      static_cast<unsigned short>(curr->tm_mday));
    }
    //! Get the current day in universal date as a ymd_type
    static typename date_type::ymd_type universal_day_ymd() 
    {
      ::std::tm result;
      ::std::tm* curr = get_universal_time(result);
      return ymd_type(static_cast<unsigned short>(curr->tm_year + 1900),
                      static_cast<unsigned short>(curr->tm_mon + 1),
                      static_cast<unsigned short>(curr->tm_mday));
    }
    //! Get the UTC day as a date type
    static date_type universal_day() 
    {
      return date_type(universal_day_ymd());
    }

  private:
    static ::std::tm* get_local_time(std::tm& result) 
    {
      ::std::time_t t;
      ::std::time(&t);
      return c_time::localtime(&t, &result);
    }
    static ::std::tm* get_universal_time(std::tm& result) 
    {
      ::std::time_t t;
      ::std::time(&t);
      return c_time::gmtime(&t, &result);
    }

  };

} } //namespace date_time


#endif

/* date_clock_device.hpp
aZHyxm0mETqiSAbIw3ZL8Nn8nNLnEZXupb9Irk6SjuOrCpkRV3Nr/SaM1pptb62/XE2ttV7mpjrRXyqhiHzHmyjjQCkZL2UAuVJ1byfjV0r40d9os96OtCWqgLwAQ5m45NlWXBHS0p9Em4S2u4UbpeVK1XYFdE6FyfzZz6kVAWp0Qq7bONcjOtenj6lcj/883n3PLQ/8oFn6XjzxW1XLhf3fWrv9HzH8WvwuOn4pv4kTQH50hDUID45V7jbte8DBgygY6ZUrIb8ycoIYIEzQPuNOUr8cneQNdJLNupM8GQbbtHSj8VrCkQJmtWE9PFsDrqbfGcpJEhuYrLihNWYaW00TwtexP1d2iIT6KoE65FrxKiTHBRSvvpUl4HQuW7NvmkO9qu3olvOcphlatA8bqSRcYKAOYdafqZZz40GJ0PGMYT/trjyeUmys52Wh7aQrklBq9ZWCUn9xUPFLzbrl67pgm6GXWTNDiah0ScM3lybaZt4EQNmW9CJBQiOHRaA/F18B8aVlYnZF211avFLFAzn154kvlpSpDkNZVr30cjVgPAFjSgx/ZY0Hc9w5FId54aOz27qG4XYUBrCo0TZl6JknwNhvZrjrhcGG7YqEXI3cikCOxJ6gSXh6gQBICetiTeLsBHZRRLLdrFCBFizlFrz2MnWzgtmALy+nCmqgPU2gdmvSV+dLVz7L/18HzqT2bJffzOOVki+t5iiBZIZoxWSIhn0f8EXeefo4fZH1YgPfOejMP0anSOeAIALGoulKzfP6kdtnUOGmB8FgN1G61Y6rMjoEzf8nHuqua1DNf71u/lcu31eWWRbSrAHk2TepZdBpt+hlEN/CRyjoC3DvEnznBbHwSpf65BqhgWWNLp7UexLOGPTWAuRoGmxaMsHLMvUGEJ1P6/VYbZ4anbTohDC98lbYOgb080u5Q/c9i9CynLDK5E3A32vHJQo2i6+FkcbrW2MAaiw+uayxCwNbfqkFq1+u4JJVFcrJt4yuTrgyVyc8m9QKQkcp9WgoL3qkdrVUqBMeRxCZSiWEKEScjVzujqUoF1h1JTEGGZFniRRtNt0pRJs1/50eGm/lMnsNtz/zZpZgR7Quj/O/FQNxOjBHRLgyh7S4D9xi+gitMni5FQulg2WjF1mv7igGVxsAsV6DANnHvMRmrq1ECS5wuj8HgzHeuS0Q3efZwYaOTubjvUqNqamrHzp8TFWBqWj6yY3Kx1cFJmbzEOukazrU1QTiYH1zA9PbBGJc0h4QS9YmlRW5VqpcqdwvdjlyJt4v9o+LO0Q//v61UoZEDesxLHfPiU662COsB+kJoCei0wo7iy+0dgfWtN5l6CX0WUiYZuGXljf0l7Jk0YrpDkti0vXYFEANpQXTFqbT34sX1dDfMvF+2qKp9Ncn3ksWVdLfvOBx9PfgYDn9LQweSX+HBYvp7/DgaPo7IjiC/o4MDqW/o4KAeWjwQPp7RDCH/o4Pdqe/E4IedbseqZrUoI8wF8JaRlEdCV8XMX+jsAs5gL48+OqNL3fjAR3uK33bJ378vme1Gr9vWmMbv/WojY4sbLhUbzRHPT+fYk3mHU0lChsl9OVdiZWs3gIoZNdMixaXxAfl1Y+OD8oMDowP6hbMQlDelnKXb1S0j4jWrp0KcffO8vIsHw/0araoXHiwvt7Ep8fgLQ3CzSG2y/Ro03K4aB76WDQwSZbrOYu5QWcdnIfeup8HZ6v/j+tM1xHk6q5/EA0HpZMICRt0Yi0tbSMZzQ3fSNyIyDEqUjelokG0q/TqpXeCqCHptf4Um4EyaA0pf4QKdVhDe6tQpyU06Ir2jHbnDVWCL0qNXmctApj9wkiGWVp7mBXq/V4/DsopVnA=
*/