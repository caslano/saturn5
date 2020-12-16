#ifndef GREG_DAY_HPP___
#define GREG_DAY_HPP___

/* Copyright (c) 2002,2003,2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //! Exception type for gregorian day of month (1..31)
  struct BOOST_SYMBOL_VISIBLE bad_day_of_month : public std::out_of_range
  {
    bad_day_of_month() : 
      std::out_of_range(std::string("Day of month value is out of range 1..31")) 
    {}
    //! Allow other classes to throw with unique string for bad day like Feb 29
    bad_day_of_month(const std::string& s) : 
      std::out_of_range(s) 
    {}
  };
  //! Policy class that declares error handling and day of month ranges
  typedef CV::simple_exception_policy<unsigned short, 1, 31, bad_day_of_month> greg_day_policies;

  //! Generated represetation for gregorian day of month
  typedef CV::constrained_value<greg_day_policies> greg_day_rep;

  //! Represent a day of the month (range 1 - 31) 
  /*! This small class allows for simple conversion an integer value into
      a day of the month for a standard gregorian calendar.  The type 
      is automatically range checked so values outside of the range 1-31
      will cause a bad_day_of_month exception
  */
  class BOOST_SYMBOL_VISIBLE greg_day : public greg_day_rep {
  public:
    BOOST_CXX14_CONSTEXPR greg_day(value_type day_of_month) : greg_day_rep(day_of_month) {}
    BOOST_CXX14_CONSTEXPR value_type as_number() const {return value_;}
    BOOST_CXX14_CONSTEXPR operator value_type()  const {return value_;}
  private:
    
  };



} } //namespace gregorian



#endif

/* greg_day.hpp
+7u37VRHRme20UAc0W202wnnHtxg2mcWcRMQs5QhGlMTnCBnOE3JQw2fVJNEhsc1pHhct/qRpH4k6aHrZ7ar+p3tcn6eqSW/z9QygQzNy91itEJ7w2Qkt8VfocFAM4b9clbwlnmDzMtaSq5ZdSw8corZP2vzKHvvmr8S9d41h41+3aLbMO+as9bXrjmGz1ZyhmylGWSQS5DlGGR0C5ERZDm/IHNduNX8LtwKUceUZwJZf9xgZPJWIZChebmzjFZoe5+M5BZ6kwYDzRj21rUC9fEWhMwrWqpdf04pbmqQSf+fU4qbBpAVyJw9NQ0gM9rwqxluo+0OO/egZnrxIeImkBU4Q7bSDDLIJcgKBDJRs2AEWcEvyGLyidqHJ6p/Glv3i0NL4DDuhsOBuMHI5G084RDNy41qtELvM8hI7sh/T+OFZgxb9azQr3ngnPw43/TE6E2PxqH0H7EzhrKPNz1RH296BA4jMW6j3YY996BuftOj4yYcWpwhW2mgsZBKGmsRCEU1y4XGWr5prOsTdcTvE7XoZ7Ib9DvZDRPI0LzceUYr9EqKjOQWe5IShGYMe+9agfp4AUPmw1pKrll1LDxyitk/a/Mo/xFkRTJnT7CR0ZltxFsh3Ua7HXjuwYjpZZ2IG2ZQcoZspQFkkEqQFQlkolrRBWRF3yBz5Qav+OUGJT/LtjP8LtsuIJChefl9ClrRL9guYCy9wm93KEFnOBRcnRWoD4YPc/YjXz2y6lh45BSzf9bmUfZ+9ThtzPvVI2z0ax7dRrvvdLgHr5hfPeq4YQYlZ8hWGkAGqQRZiUFGtyQygazkG2RxN5A1VNtOI/Nq3g8BvcIvAb2BQIbm5QdKaEW/7b6BsQStzdhjxPUdCq7OCtQHr4oRI9NS7TpLKc5okEn/WUpxxgCyMpmzp4wBZGabRoo7JXvQ0CDjQGQPGqa3xyJu2wmFW2bWYQAZpBJkZQKZqFZ2AVm5M5CZdn09Udj0i8J+P1Nd1e9UVyMUonnxRRVaGTvxVWOwQWszKcpg1aHg6qxAfayJybympeSaVIhWo1D6LxAGcgYU8lFD9gQbGZ3RRqCwoNto92UZ96CpUdiP7LNDHTfMoKQM0Zia4dSU+3FkDp90SyIT7ej3uR/n+kD93O8DteJn1Vb3u2obIZSheflNHVqh43tkNNn1pMUqljJUdyi4OitQH+sRMh/RUu26SDm2NMqk/yLl2DKgrELm7MkyoMxs00hxp2QPPtco40BkDz7XKKsgt+xQx207oXArTH7NKINcoqxCKBM1Ky4oq/hEmSs3+N4vNxjwQ0Bf8UtAG4QyNC8/8kMr+huUBoMJWnuFQRl6xaHg6qxAfTwryLyhpeSaVcfCI+eY/bM2j7L31zmlmPfXOSWBsrJuo93HjmWmwOavc3TcMIOSM2QrzSiDXKJsgFFGtyQyoWzAJ8oSf+HdQiTuc7ob7weITb9A/JyAiObll6BoRX5e9DlDLkKKfspj06mIRB2K8ZSsSoxdaYVsgw2OtV1TBrgh1uZb5T1TBMo2B1iopojXy7KRom7K3iAersHR6d6g3OabLD0kNMg64CgPuhFvkPOWHeeCPev0mFaN49tt2e3vh2Ak4z6XdoN+Hrrf+33oRmw5mpdfxLZaGTtOADuCTpIUA5QstEQK9uBQDPLYx9iVQ8FtjKe8D2gUyobGU94HDCg0HYGgmiJeD0tC4XjdXrtPe7k3SY3CQUYhuxVDQijUAUdJ74LCpEAh5YI9c3qMKBz0i8IJvDeOXYHa5xeow36my2TC53TZZ8tbzcvvn9GKPr4APaOrjxFM+Uw6FPgrFXBBrngTzaGgNtjgWLiWYIoJLQ7fGIBqOnJBNUW8XpY=
*/