//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2021-2021.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TIMED_UTILS_HPP
#define BOOST_INTERPROCESS_DETAIL_TIMED_UTILS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

#include <ctime>
#include <boost/cstdint.hpp>

//The following is used to support high precision time clocks
#ifdef BOOST_HAS_GETTIMEOFDAY
#include <sys/time.h>
#endif

#ifdef BOOST_HAS_FTIME
#include <time.h>
#include <boost/winapi/time.hpp>
#endif

namespace boost {
namespace interprocess {
namespace ipcdetail {

BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(time_duration_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(clock)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(rep_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(rep)

template<class T>
struct enable_if_ptime
   : enable_if_c< BOOST_INTRUSIVE_HAS_TYPE(boost::interprocess::ipcdetail::, T, time_duration_type) >
{};

template<class T>
struct disable_if_ptime
   : enable_if_c< ! BOOST_INTRUSIVE_HAS_TYPE(boost::interprocess::ipcdetail::, T, time_duration_type) >
{};

template<class T>
struct enable_if_ptime_duration
   : enable_if_c< BOOST_INTRUSIVE_HAS_TYPE(boost::interprocess::ipcdetail::, T, rep_type) >
{};

template<class T>
struct enable_if_time_point
   : enable_if_c< BOOST_INTRUSIVE_HAS_TYPE(boost::interprocess::ipcdetail::, T, clock) >
{};

template<class T>
struct enable_if_duration
   : enable_if_c< BOOST_INTRUSIVE_HAS_TYPE(boost::interprocess::ipcdetail::, T, rep) >
{};

#if defined(BOOST_INTERPROCESS_HAS_REENTRANT_STD_FUNCTIONS)

   inline std::tm* interprocess_gmtime(const std::time_t* t, std::tm* result)
   {
      // gmtime_r() not in namespace std???
      #if defined(__VMS) && __INITIAL_POINTER_SIZE == 64
         std::tm tmp;
         if(!gmtime_r(t,&tmp))
            result = 0;
         else
            *result = tmp;
      #else
         result = gmtime_r(t, result);
      #endif
      return result;
   }

#else // BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS

   #if defined(__clang__) // Clang has to be checked before MSVC
   #  pragma clang diagnostic push
   #  pragma clang diagnostic ignored "-Wdeprecated-declarations"
   #elif (defined(_MSC_VER) && (_MSC_VER >= 1400))
   #  pragma warning(push) // preserve warning settings
   #  pragma warning(disable : 4996) // disable depricated localtime/gmtime warning on vc8
   #endif

   inline std::tm* interprocess_gmtime(const std::time_t* t, std::tm* result)
   {
      result = std::gmtime(t);
      return result;
   }

   #if defined(__clang__) // Clang has to be checked before MSVC
   #  pragma clang diagnostic pop
   #elif (defined(_MSC_VER) && (_MSC_VER >= 1400))
   #  pragma warning(pop) // restore warnings to previous state
   #endif

#endif // BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS

#if defined(BOOST_HAS_FTIME)
/*!
* The function converts file_time into number of microseconds elapsed since 1970-Jan-01
*
* \note Only dates after 1970-Jan-01 are supported. Dates before will be wrapped.
*/
inline boost::uint64_t file_time_to_microseconds(const boost::winapi::FILETIME_ & ft)
{
   // shift is difference between 1970-Jan-01 & 1601-Jan-01
   // in 100-nanosecond units
   const boost::uint64_t shift = 116444736000000000ULL; // (27111902 << 32) + 3577643008

   // 100-nanos since 1601-Jan-01
   boost::uint64_t ft_as_integer = (static_cast< boost::uint64_t >(ft.dwHighDateTime) << 32) | static_cast< boost::uint64_t >(ft.dwLowDateTime);

   ft_as_integer -= shift; // filetime is now 100-nanos since 1970-Jan-01
   return (ft_as_integer / 10U); // truncate to microseconds
}
#endif

class ustime;

class usduration
{
   public:
   friend class ustime;

   explicit usduration(boost::uint64_t microsecs)
      : m_microsecs(microsecs)
   {}

   boost::uint64_t get_microsecs() const
   {  return m_microsecs;  }

   bool operator < (const usduration &other) const
   {  return m_microsecs < other.m_microsecs; }

   bool operator > (const usduration &other) const
   {  return m_microsecs > other.m_microsecs; }

   bool operator <= (const usduration &other) const
   {  return m_microsecs <= other.m_microsecs; }

   bool operator >= (const usduration &other) const
   {  return m_microsecs >= other.m_microsecs; }

   private:
   boost::uint64_t m_microsecs;
};

class ustime
{
   public:
   explicit ustime(boost::uint64_t microsecs)
      : m_microsecs(microsecs)
   {}

   ustime &operator += (const usduration &other)
   {  m_microsecs += other.m_microsecs; return *this; }

   ustime operator + (const usduration &other)
   {  ustime r(*this); r += other; return r; }

   ustime &operator -= (const usduration &other)
   {  m_microsecs -= other.m_microsecs; return *this; }

   ustime operator - (const usduration &other)
   {  ustime r(*this); r -= other; return r; }

   friend usduration operator - (const ustime &l, const ustime &r)
   {  return usduration(l.m_microsecs - r.m_microsecs); }

   bool operator < (const ustime &other) const
   {  return m_microsecs < other.m_microsecs; }

   bool operator > (const ustime &other) const
   {  return m_microsecs > other.m_microsecs; }

   bool operator <= (const ustime &other) const
   {  return m_microsecs <= other.m_microsecs; }

   bool operator >= (const ustime &other) const
   {  return m_microsecs >= other.m_microsecs; }

   boost::uint64_t get_microsecs() const
   {  return m_microsecs;  }

   private:
   boost::uint64_t m_microsecs;
};

inline usduration usduration_milliseconds(boost::uint64_t millisec)
{  return usduration(millisec*1000u);   }

inline usduration usduration_seconds(boost::uint64_t sec)
{  return usduration(sec*uint64_t(1000000u));   }

template<class TimeType, class Enable = void>
class microsec_clock;

template<class TimeType>
class microsec_clock<TimeType, typename enable_if_ptime<TimeType>::type>
{
   private:
   typedef typename TimeType::date_type date_type;
   typedef typename TimeType::time_duration_type time_duration_type;
   typedef typename time_duration_type::rep_type resolution_traits_type;
   public:

   static TimeType universal_time()
   {
      #ifdef BOOST_HAS_GETTIMEOFDAY
         timeval tv;
         gettimeofday(&tv, 0); //gettimeofday does not support TZ adjust on Linux.
         std::time_t t = tv.tv_sec;
         boost::uint32_t sub_sec = static_cast<boost::uint32_t>(tv.tv_usec);
      #elif defined(BOOST_HAS_FTIME)
         boost::winapi::FILETIME_ ft;
         boost::winapi::GetSystemTimeAsFileTime(&ft);
         boost::uint64_t micros = file_time_to_microseconds(ft); // it will not wrap, since ft is the current time
                                                                  // and cannot be before 1970-Jan-01
         std::time_t t = static_cast<std::time_t>(micros / 1000000UL); // seconds since epoch
         // microseconds -- static casts suppress warnings
         boost::uint32_t sub_sec = static_cast<boost::uint32_t>(micros % 1000000UL);
      #else
         #error "Unsupported date-time error: neither gettimeofday nor FILETIME support is detected"
      #endif

      std::tm curr;
      std::tm* curr_ptr = interprocess_gmtime(&t, &curr);
      date_type d(static_cast< typename date_type::year_type::value_type >(curr_ptr->tm_year + 1900),
                  static_cast< typename date_type::month_type::value_type >(curr_ptr->tm_mon + 1),
                  static_cast< typename date_type::day_type::value_type >(curr_ptr->tm_mday));

      //The following line will adjust the fractional second tick in terms
      //of the current time system.  For example, if the time system
      //doesn't support fractional seconds then res_adjust returns 0
      //and all the fractional seconds return 0.
      unsigned adjust = static_cast< unsigned >(resolution_traits_type::res_adjust() / 1000000);

      time_duration_type td(static_cast< typename time_duration_type::hour_type >(curr_ptr->tm_hour),
                              static_cast< typename time_duration_type::min_type >(curr_ptr->tm_min),
                              static_cast< typename time_duration_type::sec_type >(curr_ptr->tm_sec),
                              static_cast< typename time_duration_type::fractional_seconds_type >(sub_sec * adjust)
                           );
      return TimeType(d,td);
   }
};

template<>
class microsec_clock<ustime>
{
   public:
   static ustime universal_time()
   {
      #ifdef BOOST_HAS_GETTIMEOFDAY
         timeval tv;
         gettimeofday(&tv, 0); //gettimeofday does not support TZ adjust on Linux.
         boost::uint64_t micros = boost::uint64_t(tv.tv_sec)*1000000;
         micros += (boost::uint64_t)tv.tv_usec;
      #elif defined(BOOST_HAS_FTIME)
         boost::winapi::FILETIME_ ft;
         boost::winapi::GetSystemTimeAsFileTime(&ft);
         boost::uint64_t micros = file_time_to_microseconds(ft); // it will not wrap, since ft is the current time
                                                                  // and cannot be before 1970-Jan-01
      #else
         #error "Unsupported date-time error: neither gettimeofday nor FILETIME support is detected"
      #endif
      return ustime(micros);
   }
};

template<class TimePoint>
class microsec_clock<TimePoint, typename enable_if_time_point<TimePoint>::type>
{
   public:
   static TimePoint universal_time()
   {  return TimePoint::clock::now();  }
};


template<class TimePoint>
inline TimePoint delay_ms(unsigned msecs, typename enable_if_ptime<TimePoint>::type* = 0)
{
   typedef typename TimePoint::time_duration_type time_duration_type;
   typedef typename time_duration_type::rep_type resolution_traits_type;

   time_duration_type td(msecs*1000*resolution_traits_type::res_adjust());

   TimePoint tp(microsec_clock<TimePoint>::universal_time());
   return (tp += td);
}

template<class TimePoint>
inline bool is_pos_infinity(const TimePoint &abs_time, typename enable_if_ptime<TimePoint>::type* = 0)
{
   return abs_time.is_pos_infinity();
}

template<class TimePoint>
inline bool is_pos_infinity(const TimePoint &, typename disable_if_ptime<TimePoint>::type* = 0)
{
   return false;
}

/*
template<class Duration>
inline ustime duration_to_timepoint(const Duration &dur, typename enable_if_ptime<Duration>::type* = 0)
{
   return dur.is_pos_infinity();
}

template<class Duration>
inline bool duration_to_timepoint(const Duration &, typename disable_if_ptime<Duration>::type* = 0)
{
   return false;
}
*/

// duration_to_milliseconds

template<class Duration>
inline boost::uint64_t duration_to_milliseconds(const Duration &abs_time, typename enable_if_ptime_duration<Duration>::type* = 0)
{
   return static_cast<boost::uint64_t>(abs_time.total_milliseconds());
}

template<class Duration>
inline boost::uint64_t duration_to_milliseconds(const Duration &d, typename enable_if_duration<Duration>::type* = 0)
{
   const double factor = double(Duration::period::num)*1000.0/double(Duration::period::den);
   return static_cast<boost::uint64_t>(double(d.count())*factor);
}

inline boost::uint64_t duration_to_milliseconds(const usduration &d)
{
   return d.get_microsecs()/1000;
}

// duration_to_usduration

template<class Duration>
inline usduration duration_to_usduration(const Duration &d, typename enable_if_ptime_duration<Duration>::type* = 0)
{
   return usduration(static_cast<boost::uint64_t>(d.total_microseconds()));
}

template<class Duration>
inline usduration duration_to_usduration(const Duration &d, typename enable_if_duration<Duration>::type* = 0)
{
   const double factor = double(Duration::period::num)*1000000.0/double(Duration::period::den);
   return usduration(static_cast<boost::uint64_t>(double(d.count())*factor));
}

// duration_to_ustime

template<class Duration>
inline ustime duration_to_ustime(const Duration &d)
{
   return microsec_clock<ustime>::universal_time() + (duration_to_usduration)(d);
}


}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TIMED_UTILS_HPP


/* timed_utils.hpp
JMSsfnP3LwE8kK1NfrcQHUdubiXueDTcSOHYLrEG0BJGdtLzlPbTKHOHIZU6S/LT1R3UkBsYiiwBQHatQPMGYorBqdlAlc6E3O2cu46X08q9XWbXIWSeb8QA6OsksQsxgapJGSHIGNRi9WCkgYWIkskdb+qGnTopsFXmtGia0m7Hde/bYnKPDVriqDUV1TjqUU2punpHColYI+oVIgKbxLHd6RY2eBIEaUpBP3QoHWpVgD/PnfnckzNYVRp0lz+UPiEWSk9v8lAhQ76MMGUdWxBYYsiGVGDjGTmPMvwxTguBm9b2k7wPlZHlyMlthWUGaAi3CqXtv9reTLmI8x0voRdY5oYaR+OOrr6XuQ1vrC775TPOOV5sYt1a2ia0mqP0EQV3e1kEg/fZMJFuf2ndcBoy0OSORWczGEn9YsqhVguBSm0QW1oYL4cRWm5W/VaZhpnLOW7qTu8a01q7TMM0nqvuLLCfIZhRjOM6ettQTgkXOEUHYvSUOYVaTMVSKGSrbYM6jZUWtquWzbEqdQeOk7sLa08vA4xncahPr5J5YVg/Jf8dH/CNMOFDx7JQ8YCjFkCtCFkHpPAaVI7wdZv5fn+lbsnD9VgjShv2c/04RtVkxQBaLFOejNIgK9KgBT0uPhKz6wgFeVuny0yJUROh1PHOPJu5/eMa2XJOABTYeAiEABGCfmgEq+q+h+qncbBbVp6/4eWSf4H2iXfuhByBegEASHMEM2EYsIEMUC6SoQXoLQsFjgABS8Oj2uSYoBF1jUBpFOFvItDKWkXx17faLf91gI/13H/Jick0Iffq8r+InVWZ1rV7eBHeHL8FoNoaDf3YoDTe5sL7Gij6WdjNVKtyzaGcrSiIb5qoBagBTXzNFE2nA4vXUMx0Uetp9AwJHaoP8uRAvDru5gE8IQOrrmO+OEtaY12ifc4mQp2BlEaN2UYwiQ5OzYBJf8i+stKb0aB26GWwUoyJDNqp4upAhZdqgt5S0sQGXjgnxMOb9PnhxQkChZtUcVRv76X4WdEYizUhr5NsP+NzOoowWrTRBi9jmOqi0KAvp2NzJt3MSxzisjsO5Hgx/3UzbysMDzGKZQFcIW979Cyt09uY6MF+S4Iwfmd1MAfJnikjTkpaqiOCtQIEQLtXX9hIBq4uWWk7QhIyyiUII9tWuPXgqhZjrxNMXVakxEiEQJ3HitqzZ3ktNKleX0VwbMajMoAZYNb6e3jav1ZJ/o/RoAiwhcdDAXZyPjfVUwd5nUwTbfQxoEIesjYUtTBk22bboJQTvu7s3lRq8n0RSH4IGXwv3lMyGgy4rV1lhJhaz69FBbWTNoiC84Wo3TdqnTFiakr16eo5ieMgSskambqKGcTmFm8zofKxTQo/pi3n3mtHg4abv4e26CbBe/w8DQ9N9kxUM6BtF4oIxTrxsrXr5mZ5k3zLtG9gid/Q9zGS6ivU6EwJjecUKvlGUMwWg3ugk66lx3844VCDgeVi0r2EqH/7uuBo0BR5erz3dRCTDQ5jD8n3AFQcRw0W+BGmrEFV+FkwZwYXr7qGF85LVxRD3IvbHNYPpK6h/nNaaw34mf9bSzeQ4Ea5D7uPZk4C67xjOp8d4WIGJmckw/36CGEm/tMdieVfCY5gQhRypiqEu5v1v5i9dkSVdEORPjMZLrvFkZGO6KGDtBOa59XcfPwPBO6LYiY15Nfqa52/VQBA2WjR0Wdy862VX+A73l4rDdQjFEP2+p0LsnaHJGi0QtgqR9ZL09vpobQkXw1lzwUy0n2zXOPaTnTwL/Y9le/xumurW44Y2Qb3+q3tkFMoz83WoAQnnEmRXqRERxa1Y2EXbprT7yDSrfhR7Y9fscLyJcSkehSumveaEHF/lU+Zrl6x8Qpl0WtrYsA2MdDbBKq6YaAQqpncNmoE0NRphO+Mi5LXys+wZeWnWnZrf04uOuZFqPDH6TjpntKc8VlUTI5qUUzoma4MCepS52OnqplBU5dsM6crXJg/8VcaqXkms7/WsUplVc9AqDYoTXbiQCyHdFvGXpa7+gWigCVcqWa1gZCTFc/WmZcXwZ6885POOJ9bEb+O2pK88Fv3Czevo0opwqZLbUxp6TEa1d885Eypmuyl02kV/et9QumJ6AAWpJBelQgQwtGGuJCaDH6EWHzlpkUChAKZ0mwsxYEfurSVMunqqSYOle+S9Vq/gQjWmiQW8RsuUTUitC5mR9w0oi+evOGidLf3Q8PiZCku7KoSrUZD18jnLcNHLLHwvzknnnvIzzoXDtuID60uxHpmhvgS7HfDr+ymrw9tYTKum7SYoYK1kK1NA7D3VCGb9Rfh+mjJRrw7I1Ykn02EnC15fVrJCQRt3eougOTTYGL8dXjKawyPPm74xlgbPOccrUKK9yjgyW1NKjqJRmacc+0/HSM/mgJtUj3XF9jUITuqkeDq5g4ClDQDb/FFPy9scTuObfKfm8DE/qJz0j+MAKqYyoBNe63I54JnySsp96xJJnePMzTyoKL/4ByBpj4i4rUBVVoPBRnIYnV4mkqJrOvOZn8DhX+hqqkI7YWueuxWfhaj9D3ybhkv0XO4OSY9+os1zpjDyeByMy2ST0RZgTBrKdq9iW0xaEB48Kod9Br1LErWd+WqWWR4Undjhb22vktVQ6VyndW08taGdxIM2aKWnalRl7tPmsc0IhXByXqETajIKm33KsHLfmaJTOoXBb3Lf+Z4BDbz/u2mqneyf8FYt0YluMPil5dIj7qbvl2vDGLVGRlWExFEzanVOHY6WJDYVgu+SOH7YUOGyPzDsxTfhYR/rNZb7njgoRIu251400ZKbXLCPkzXS3puJEPTlWKDeAqbPs0PtgbpudCseNaD1FCw7go/YRcsVcwxzXUhaeyAF8Jmz/+8ULibjKzB5nLz6t0D+NrvXigOueXQWn8pjrZeNAED8j02sjWH47B5CTNjepy4C9DolV5SdV5RxrQDAHmS+hdxOXEAPZRzS4HuyZDRyX/JxmLFJMyoY3KjOH6I8a1y49N9E8YIYV1YJB6BQtHKRQC8o3Ksp1VIcoohM5r528k07L5A/ozE+2vzwoKMacl4Xf5tCfSmLVSnn123chN1KAcRAmt0bjTl2WOeyj1xCCnx6ydjntXme1CCDN4MM56y0PCdomG466yLdLnTJuqwHbcD5YLg2KOfT9jN3tmKsTHVCbVEih6VLAGTZXD7/IWQ5EnbiUB7t5oxGEqnuyR66W6wR/J6vZL/MfgAcO0DvMMHCCZP5cT9zShym/ymi/h5pnCIPvplQyYEvVyEllzxeKEp2LsMFwROqj6TsoGu9QYuT26R6+B4GW6pRf5e5cgKlq2u2lCH6Fnm4IVEZypwA/Drq8UQRLWjSMcNY/2Mpjlqj+VbBLYDtyDqZ47AspvdEsOJEt06DeY22/QyHnvGsO87FUffMQfVnxme9snBNVdirSarr4ZpRfROnAJjn1UU6FUGMu37hloMbi4B4A/yrNpQyn0TzmtL5nzEwLcC+KDhGvJ6gEdxnR4zu/e/eiwpBGOjAtHXlAazE3tzNMqDphheVnEtqkjO6ZK6HKO6w9FOiIEqjxEH/321srD+7Nrkx85Sd1EHO6rRbimZC6LNUaY9YUnWUsLF0PY3MfRS4n0sCO3hurgH5ylIVUGD4B1B7jssaX3Jch/1Un34+3xHsgh1hfYlU+b4AX824b30ZSONletrzDkfaWlnS5MDtVS1pXU38Gs2WqfYUgWcQd/c2k8SgNB36sA1N2P2cSwZ+pCRtrp85FD2eymycSnc0Owl96m2iRHPI1EHgISH4awhXbWtzLmemri7RnnieKemGD0O9wmv5nwRs3JVYV8vFEo+1gfKP+/75V+W3kM9YkjFpfwzRDsTZDLLgedy0AfXDTgG6EduhuLwFeiGrwaiDG/usqS0unp5CM43Lq+0zOM1PvJVta+GbDT6/lQwj70rL/mnJKMYIPw5aH2CcBOrjEYaviCm964yEh6xcDtBTH27sWl1fwUotw09FBSJKvKEXb0eZp8Dgiec8orKuYq62KG8ozWbwNU2M2QFdc6hN3kjvuw1tuEM7iFq1aQt5gIkZZoSWWu9e//EVeGcy3Fp8PNPyrDdwfUGkbYWSC2sCkxo21T0qCa0O0cbVTJxivd+hRB/TzkefcuBhg02t9zTQn7oJ3MRxD9/PfnnF6O31IMZfvlymtOW8kD7sk6nA+F1xGWC9moVMvcuWzqV1Hbu5NSBebOSDEfjfQzgaiqUV6F0QcY3SptnfoMqZvE6ssEyw38MuwtkLQeVmS2qz3hFsf1xdjNmTDG4PH6tAXFgmtJsEhBE7272DPYAPb0ymR7sDNB3apwIG53GgGIcN0Hxf3Gi3Zu6BDVKKYSQ7iHR0HYLKKmTFBTgyxuuTW5PHTs2LUFJg0ddYspjVjRqRoebWEcdlR7kSXP+cE0kcdfALH6sYwTi//KPdFLSdYnIPFWNIEEMHWtFRJGKHZ/jLxvNkNjVbj4XEY0ABCz70y+14v5wPjWEYynFRkeYHwBKLzoh3yFVVVVwgEITS8IwTXL11G3hPCH9sDoaZiGjnN/bclLBENsVyvk7vwQa+O/hRfr4SIj6Dotbbsuao4uqBmW86PLItmgd4vPvp7QbuV4SY6aAL1EGRlEUeGJ7G9NCKCfZj3kn3OaLQzLDqT1mcoTRsw589VPQsSjF7xAHVmsfp/kJTMkR4o8NhDfyzzR/5hJ99Vw3d6lURw5h7wkX006i4JZh9F+LmRqvHL1djjXPRlqawigDJtSdo/Dmpx8cnxRE1Dutr7eW10C1iYLZgNmoQPoxzE9P5AfiNOn6QmwdZFoacQ5+fv6YtJhluDOubFtySDXku69ZQTZhr6+IoNFzl9VbcyItFHtyYutXbRUhele5zJRYoyEi4eyyaVnloqBnggYfTkmdI8joGhf/2wGPyKKqyJkZW/lXDSzC335PlL6VJ7bedQWOp8zZrNl4NnyNE/LkKgQawxc/rMRLMnPZZ+uD6cJWf11MvW+CxADp1UMjWt7F2GlBlPZyoSLwRI6b++vK0y0gZ3FIy7YgGq08acKsisQ+k8jsRkPw3gdqeIvjfKlQenPS2cVIXDrrQaypGX3tUDsn/KGtfnPDubCtI8YBoAhpuruHHFrqFqkSq6OKJlvDekrNwXPG2TCCQDRi3aaPV18B4cjYbcDwzUy5/sowAT+VMwoPIbW17POZqKPwnyDd0VZ4OD86VIVY2rEu18VQa3I6PRjhulzWW2Ghzn9IoPMlVNkuFt9z5Ue+ZoGkh1/62yQkRbjJwMtdiFxWQ5Z90ND9m2YQwnegJOZpeamyRNwVoM/rmX+1zuxt3RFUTYGmMMsUyBZgJ+ERvnOX1s7xuFy6X99NO1ByjjWPdlM1LD2CkO/MLuzAsvKvDrkUDIn6Wwrnjuvbiubz+M3Ozvj3F9n1eUY0VGnm0Z6QZAj44NgRVQ6/iQ6T/z0P3MBS/4t/A12pn/2pmv3dBsHdPZ1K13dIXhDb1TqOekVmaJ9auPM37SrNdkD+Ug1J0tCnIafO5Re9OAE1vn7nxnUq6lYcl1C6ZH4LB/qmgezaf0A9Xpa9zQUb+urenn3sxcCKvP/dPgutIt4q1I0y8xdqfW+vZJVbnnCvJ7aq/wGbyqTupVxg5LV/pi+u6W7JMoU7lBvNAwjw/pHnVv9gwRqig2a+IkrSxMuqmjahLYfxRuABvEs0fs3F5nXY9ot1Q47JCrAoZ1ErT4+lVKcH7Y5lEhTbPCv0kwUsGqR0T3zRJvBZqN36uwd/x8oRKSKYEYJ5TP/TxY+gr/yI+y3WwBcW9FkVDMfOpquoJrLfZlLzFP9qoDFm2yk1/WMUTCh+K07QWScEJP85fvwufUMaVbAEgSpfV9AkVQ6DcE7554KXj0IGMXh133W5/+9gES+duOuOCQPygf8HGj0tRAlX9Hbd4BZao7W3yqM8TqIqSpkWjga1l4M3k/ogCKU8Q68cnLOOeK7gOKO+dH0XxMyQJ5khEzUlj2/3D2q7HLMkD7KZ543ndEewIRrrDUMGwU/9D4TKG0tPmBH9fsJx2JU5MqXAypZAd1zenCrvW8KyfGvBI2iJnst4MZP+HE74eALUNViOw0gZypiknOUQrWhe/aNxYi5m+9l96j7vpDj1MpM3QZWNHRCOMQGlQ05LSyibzoXV8SaohemE558kbZSut1o0PRrcjDuqV2WgK8KZ+K+OZ9LTXMMppSSFyAS7C++O2cfOHG9UcWmJIoQ8m8+knAnmZK2/3Cdth/QvPx2x7Kf8ekvIYHCz62YFyEWHpUJrlFppkvnkvriXTdX5P/Z0bZDeh+Cm1Arz5VfsQqsK4QAWpDYGgQ6E60qn/CQDN03rIncmRV8qEVJVJBStzXzTg4xodSzFLukZ5ujRZ+U89XE/PXCa+JpSqX5/RGObWjQ3yxlvoAjNzgkI/ooP3OVMqgV/ex7WaEIBVxf4iB7a2MZLFT5PMMQ4gptPDSYN0ZupIEOBZPBUzYybCR+B610l+BmDcMqrgveVLpoLMd2PnkPDqZnjpF9cYsrQA3DlGD7RdtVHg6iPPwpoZIlPgGbs1Hcuo8ZurxdfA5eXrJTSobW4Ag8c1RVymyqSZ1KCaQ2gFHAUTAY1kYGfzdxA3sBbpgX3x9g98UHmu52+WavYoj3lSdZbHK03WPZt+7WKJfDZctLqs+mvJ94oJ9u6DWmE9LstLBi7EA+Oowp905IxGrizOsQVgU/0/TPBnXhEf1stnhNEgjuRzTRcgCIZ7q4ubTq3zk4YH8lA2AGoys8QsuV8AQau035JJPWeufwYCAdj3HOsDuBkVELHfIZGmjnDLbmXJVBdSDYlpyxvjky8sCFL9igCsUptI/0pfaYjIYF5qc8wN5RLM2UvS9MyavW24dUXZNixl9wTRvqLsT3qdu1PlpMGqmrPQ+wsayMdTACmAdf2ot4KB+615VdMtZA5XPWHjYWV5JE5/vHY9Q1WOT283gXTVyYLprae4z1EvIxV6jnBWlQuT0RRUqZhXibqGYgXghDOCfA0NnPkMdhvds/JAsRHQhM8ED1mAvpm5ti0RsBd3Jck4+tvyCLEIniJjnbvO9VecSqqGYVjC8S9aI9mAwHxpAm2b8sc0TFc+uZDss9jQlH0qEAxaWL5zIuNvL2rZYJC/Ty04ACnIJciO9HgzFk+SQT4j+L1ncfYSLHOLmHOEzP3WghPiYZa5vwOPSXemSaMtnDeycMLSmMcYJ3Fc948/IL1nogCL5JZV8+740eK0ug8NoFiDpxcsvsXRYn75/CrK3ZsLDuSHCi82TdQz3AEYfANCXRj8gW7c2GdmVvXC1bZSXqTbY9ePj/1Zu06F7C/f6LYBzTkBNE6hbS7FZLS/eXmZb9gkbQPt2+9wiM0ChrxLsx33CUUXTkBxYVkA4cTABPx7XggbGG9cZPc6yIEuPACzsDwfgX0MqhHMTjHqgUXhc99ILVDRRQtkgvhc1Tu20M85gFaWLucf5D2YOZpGgSghhhiKHpIWcI7sd77CuB3uIasMMK7MnSbMLO+i3+rnDxHITH4eIRMuGjTnVFtN9Me1gV1xNKSE8RjM51/iXaE6lEuFBUqIKTvAWA1Xo1FukGfh6YU2rGdc2idQ3PBvebPsAx0
*/