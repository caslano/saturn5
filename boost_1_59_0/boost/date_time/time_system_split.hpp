#ifndef DATE_TIME_TIME_SYSTEM_SPLIT_HPP
#define DATE_TIME_TIME_SYSTEM_SPLIT_HPP

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <string>
#include <boost/cstdint.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/time_defs.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/wrapping_int.hpp>

namespace boost {
namespace date_time {

  //! An unadjusted time system implementation.
#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT))
  template<typename config, boost::int32_t ticks_per_second>
#else
  template<typename config>
#endif
  class split_timedate_system
  {
   public:
    typedef typename config::time_rep_type time_rep_type;
    typedef typename config::date_type     date_type;
    typedef typename config::time_duration_type time_duration_type;
    typedef typename config::date_duration_type date_duration_type;
    typedef typename config::int_type int_type;
    typedef typename config::resolution_traits   resolution_traits;

    //86400 is number of seconds in a day...
#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT))
    typedef date_time::wrapping_int<int_type, INT64_C(86400) * ticks_per_second > wrap_int_type;
#else
   private:
     BOOST_STATIC_CONSTANT(int_type, ticks_per_day = INT64_C(86400) * config::tick_per_second);
   public:
# if BOOST_WORKAROUND( BOOST_BORLANDC, BOOST_TESTED_AT(0X581) )
    typedef date_time::wrapping_int< split_timedate_system::int_type, split_timedate_system::ticks_per_day> wrap_int_type;
# else
    typedef date_time::wrapping_int<int_type, ticks_per_day> wrap_int_type;
#endif
#endif

    static
    BOOST_CXX14_CONSTEXPR
    time_rep_type get_time_rep(special_values sv)
    {
      switch (sv) {
      case not_a_date_time:
        return time_rep_type(date_type(not_a_date_time),
                             time_duration_type(not_a_date_time));
      case pos_infin:
        return time_rep_type(date_type(pos_infin),
                             time_duration_type(pos_infin));
      case neg_infin:
        return time_rep_type(date_type(neg_infin),
                             time_duration_type(neg_infin));
      case max_date_time: {
        time_duration_type td = time_duration_type(24,0,0,0) - time_duration_type(0,0,0,1);
        return time_rep_type(date_type(max_date_time), td);
      }
      case min_date_time:
        return time_rep_type(date_type(min_date_time), time_duration_type(0,0,0,0));

      default:
        return time_rep_type(date_type(not_a_date_time),
                             time_duration_type(not_a_date_time));

      }

    }

    static
    BOOST_CXX14_CONSTEXPR
    time_rep_type get_time_rep(const date_type& day,
                               const time_duration_type& tod,
                               date_time::dst_flags /* dst */ = not_dst)
    {
      if(day.is_special() || tod.is_special()) {
        if(day.is_not_a_date() || tod.is_not_a_date_time()) {
          return time_rep_type(date_type(not_a_date_time),
                               time_duration_type(not_a_date_time));
        }
        else if(day.is_pos_infinity()) {
          if(tod.is_neg_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(day, time_duration_type(pos_infin));
          }
        }
        else if(day.is_neg_infinity()) {
          if(tod.is_pos_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(day, time_duration_type(neg_infin));
          }
        }
        else if(tod.is_pos_infinity()) {
          if(day.is_neg_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(date_type(pos_infin), tod);
          }
        }
        else if(tod.is_neg_infinity()) {
          if(day.is_pos_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(date_type(neg_infin), tod);
          }
        }
      }
      return time_rep_type(day, tod);
    }
    static BOOST_CONSTEXPR date_type get_date(const time_rep_type& val)
    {
      return date_type(val.day);
    }
    static BOOST_CONSTEXPR time_duration_type get_time_of_day(const time_rep_type& val)
    {
      return time_duration_type(val.time_of_day);
    }
    static std::string zone_name(const time_rep_type&)
    {
      return std::string();
    }
    static BOOST_CONSTEXPR
    bool is_equal(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return ((lhs.day == rhs.day) && (lhs.time_of_day == rhs.time_of_day));
    }
    static BOOST_CXX14_CONSTEXPR
    bool is_less(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      if (lhs.day < rhs.day) return true;
      if (lhs.day > rhs.day) return false;
      return (lhs.time_of_day < rhs.time_of_day);
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type add_days(const time_rep_type& base,
                           const date_duration_type& dd)
    {
      return time_rep_type(base.day+dd, base.time_of_day);
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type subtract_days(const time_rep_type& base,
                                const date_duration_type& dd)
    {
      return split_timedate_system::get_time_rep(base.day-dd, base.time_of_day);
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type subtract_time_duration(const time_rep_type& base,
                                         const time_duration_type& td)
    {
      if(base.day.is_special() || td.is_special())
      {
        return split_timedate_system::get_time_rep(base.day, -td);
      }
      if (td.is_negative()) {
        time_duration_type td1 = td.invert_sign();
        return add_time_duration(base,td1);
      }

      wrap_int_type  day_offset(base.time_of_day.ticks());
      date_duration_type day_overflow(static_cast<typename date_duration_type::duration_rep_type>(day_offset.subtract(td.ticks())));

      return time_rep_type(base.day-day_overflow,
                           time_duration_type(0,0,0,day_offset.as_int()));
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type add_time_duration(const time_rep_type& base,
                                    time_duration_type td)
    {
      if(base.day.is_special() || td.is_special()) {
        return split_timedate_system::get_time_rep(base.day, td);
      }
      if (td.is_negative()) {
        time_duration_type td1 = td.invert_sign();
        return subtract_time_duration(base,td1);
      }

      wrap_int_type day_offset(base.time_of_day.ticks());
      date_duration_type day_overflow(static_cast< typename date_duration_type::duration_rep_type >(day_offset.add(td.ticks())));

      return time_rep_type(base.day+day_overflow,
                           time_duration_type(0,0,0,day_offset.as_int()));
    }
    static BOOST_CXX14_CONSTEXPR
    time_duration_type subtract_times(const time_rep_type& lhs,
                                      const time_rep_type& rhs)
    {
      date_duration_type dd = lhs.day - rhs.day;
      if (BOOST_LIKELY(!dd.is_special())) {
        time_duration_type td(dd.days()*24,0,0); // days * 24 hours
        time_duration_type td2 = lhs.time_of_day - rhs.time_of_day;
        return td+td2;
      } else {
        time_duration_type td(dd.as_special());
        time_duration_type td2 = lhs.time_of_day - rhs.time_of_day;
        return td+td2;
      }
    }

  };

} } //namespace date_time


#endif

/* time_system_split.hpp
JmbDI2Srdut3TDLgKu6Ch2LHsaSvCTOesbR2lBd3PzfXuio738Y7W6yHvU5lBb1HFvmkQoCyadLVJkorZ4CjXexxYjX8Qn0jJiaE6PgDBmGv9LpRqjFXcczB0lMfA5T9NHGwsk2ksAgjaV+BhXRJQ3NKFZLQgC419hyVvgDgWEGC3Y83klBQsMSM2FRE4xXYJPaWwyyKecDeenPS4PIaDHsqnIacMr46iQhlGwEmqSnWqaW+9AktM9+qF3QdwcX+zSdrKY1mmkvgQ3frKE7EfYN9lxUY9n5ODpKLDtZpVb15oa+oPlI4PVoNdOCJzfQWtdSArGVtQBfqn+q/HIOF0AXY4AiDb5GdjYd2q/8oMTiwnqZuASARiK3zhhzSjNlxasgBoH3SiD2G9qWS7gyPVOr7xHPOXjeOM4EMrKEYpNhywYEfIUTR5kMbtBlWKnfwdZDzPAJ3+sdjewNVFCiSYFMCOg0ipyQF/hG2r5OfZuf+WyVvkmKKh19aDnSgZbMvqdnf/MY7Cz6omEWwXUeM6mUFTVq+9clSnea/ratHsWZFhWKYTmv1ReyQ7u16AkiwVyGIZWTVRF2gDZpI87SM5IapunCSJldv9A7tSYNQIyjWeEmzAzAxUMrrG3eqExN3yG6SPhK9kzzFeWCDzo846PIJKh9l46ZowI3EmNSzDqTANk4Fz45ug6giJXr+WNF/q63YGjmbraFKV5geBggYem3nHxYejtIxRjJ0A44CynZTJfBmb3UycQ4ml64V4dhnEYUKTNcODKPdW5aR8kJFeQj/2L1Yi58VRHc9yRQl9w00ZnqKh+SUAFnRDtF/OI+d+/oAegs8s59Xk52T9lMmJhH2Z3M6P+QR0PBwWQqcgVii2Dde1vvLRD2Vc6HMWBA8syduc3zRljo3J4Z+us9PsDCuOEjjpK1aDlqYpVBvf1hEx9ZrOqI7tBl+Os0PkVxoHHycHe7YdhSRb/XITq7y9993usacPjKDFdiASJLbbsUfROiws+jRD0W7XlT16+BUqcYQjHe+Skvegxap1T1Ip9XVkA3AqETg8bnqG/+QNBzlge30zPo2w7n1BO+N+6ooWzWjvwIQ51/zfoSlFBmwzzrv4wHuFKF/ibXKEDpZwAHDAdLx0fwr/gL2qGOMu+PXDAAgPguTFu56YbjIKJmezybxYbKxp/oPwMWLtt6smavVKApkIO/nrqdv8lOCvEkkOg0P0nobobEGlXGnSrG3s02YQ5GaoDQrOdm6k8sU9hy7kGDdxYn/zO1lphn8swqclblQgb23wb6M5dJ0rXwmMCQfbNCl2wHTeU9/f3LJt53xcyC4+Z5Od32LoNdEXGgrWRhKZWayKfhs/bohewGSbAqxF3pTBRHebggiYoTqcK7dYto4fD9G6xz/6kGsmuQl0v4Lv+K6HMbEL+p+uyBPgE8D186nIs/OLVHosJiAg9TezUin5vBMcMMQ8K6YbRg4YN9LFyV3upkj5JxuC+1bUZM8CzqCTIDqxgXm0Z4nxExLTdltflgPUTBuPCs4EhwhFRVFy/EyNlxffJnvY4ujjsvA/FqSkKi+1i+grcykXhtsYCAg3KTO+FdEiSJrHTLMzFjSQPLMuwhnzxRxzvijMR/LN6/BJ0vfSEjg9Ms/4Q2Q0gp9YxMBmBUm3WImKbrpLu2ZzcQgV4CBFZApVN4OxsHO12mmSSNXYJMFFxw71qen+36S9vLg+hLRHJwjZixVXp3j2Nx8+iJ3eIqRp6AUvonKtRPBNfPHFqG2rlBLBP+sdSFzVpsF7Gdxmb6TiX+0Y3fiIV9qfMaWi22q4GccikKbEM3zFgtEenm4O4nl3cEFGCaEdeSt6UwlY6LPG+HulkiORI9ApYtDleJS8gC/BuKep90hSt+rdLRatb+v+Y9mFdbfms5xhEG4TCNtgwzmBRKwZC0qBFFmUrPH3rhlACYVwuy/CE4X9Rjk0uF6IVMuYKFulzaQExc5BlfVmZDOBWFgtVJQKDPfRpOzyhomnDhJKe49eVV01Lw0w9kjNaTg1tinYTKG1lHBt+eeoDtR7J3VdSeFSf7JblDK7QHJUputHbOckj9dBgUEKLXpZhZEAR+mKITqPU7p0qSNWMK9nmJxYjbUKRNHy1/Y+8FzWrNR9zugnRKzgmsYbNSTbgKrvuID87n0J8E+SQilJPki8EHzlfDx6Qbzmgn/CrAXJfacn9jKxi8orelSGuOY/qi5/S1I1qPArejFb7o5H57s/ynjAd3CspgcTiTh37KhPQ2lEjFIVtfBAeGGnMAP3NcmjiGf5gqC9Uqi3+EJPa+ChuSSZvE4uEI0/4My2W5wSwcvc9SdrXm2aQQ/p3t/3jMquXqRzF8alvhed9sUDvZXML/mQjIRGNlsqONeqUfTLrHnJCU6Bl4U+szgEcpCMIvKAEa8mAKuieDOlyM5YwLFKNQOnPkAYeUp4Aab8xBRNeLjmo0ucnVuPT6g1kcIvSpa6cZZGeRjl5oEVv82+qwUWna6ngjkpgM/II82WAmZ+T3yZSBGVYGEqePCt/HGZFGyZE85+gWI1256jtY+nvVANkjDuw7wo8f8aOscSKM8JQA6HdemgAo6pxPPuzjFjtWTRr9oYf689MYGzXNDZPm4WzH9rpEb+vlfICZONNs83M87TF+7tpsDXZsOkwqslJGPIVtZF4nNhqW3MmSRBWnxuRDouq/cwImj0du+ZDCQdZtufc4q2qitppqhjBsTlvBm6bke6OYu0kYtvLiQ9theYGahUqw0Bxg1NvSZdlwx/OVp4N3K3F9yvsqUWf/NEetx5cjF2PNeZiTbsQrG+ksa6GrNZH/V1AzLvYbLr1ClSAObSQGOV5Oj7SOjYDcRa2LmZhliMM9HvPVzfuEwDvGdTYYcxPQfJzxlnLTqddmeFyzoYkQE3DFfhiCEFH+5XKVaEj1qyRZLNOR94xpJ8bUjhWFMyiCs0XNM21AZOmxZnmel0GJSYwXkv10FCqg4c8LUi3ptrEGD6n+ZgPezBaru9TYe4EzEkfBf3rkRD4bzC4z/XK5NYZLAvywF/3VSOZ/FygiFNlUpc7RXLw02Kd8l7eaKL+2JpU7h2Z6wbbq0hLJisiKZVRCGPuzhdZ+YKz9a1OkBhzDoTgAl4gV7O/ickgAjXgh05Um4dW1WdY05W2UBx9Qhif1CrmOuFfjYx4+Pg3TVk/x6P8vLe8rIJBNcRwfo5tu2b4ZBXqnhufqnbNiim9UIFaRREbxoP8JKowIEBxvMlFGKOL0WOVuNfD5eGmf698lvNJ7QEd+jkm9GY9GBarY0jbtjKIM/berdVYq86UpfB90CxXm6+qyg2ecBz/fdhugHVEzdPlSZOefSWwvdx+isLmtEznMjfW6E9ggZf/SERwztJ9e2xvTzzxh+yHNW6lSPZcVUEsi+J3dDvS+NO3gX+sYRVVJnjL+d7fIBRCPnNihbGePXhmnXGpAAVL4im7SpJ5mWKHuJyvXWPsXrklZvJCQwFvaohpEqJOtPhrNJZgFlMePmky5RzY0qLLTBfEqWSQuCxd0KLkial2qtRIo/B4+crSN+r4w3NsNVs333fUuuqFlaoCunu7igKOWZExDx+uJ+vCVMhSWVOncAC0f1BeSBA+7n0FEvi0aNQFl3bNatY3RovKv6jWof4nx6SgKANVhKen0HeBhMDHNNYBCxg0ZB/LIK0rVVWMTIDyFSqSs00CojXA23LgWO1/I1/bGsyDLgVVWVjNNnNEzgrT+jnMm+tWbM6NzqTo+7F4fzJL/W8zeZsaf7u40TJyVLsLeUWhk0u7vSLgzRQA9j/6wwlNiVLI4z5x2g7q0kK8lwZGztBluJ1HvvBxzshWjtRhk3qqvs+FF+2s3NO3zC1RjlUnnAO8CKJAmAqF5B6kpEEP5qf7mAKjKhwU/FQDoVpkBmJ1HlXKMnxyI46JVuhemtPO5wkOQ6sbyDFucwq0yBPFdMMXdQgClkwT8QQ1F0h1FZECPDgReRny+k7nlJEskOveuNNiy6Vgjd3FlvQiTjyltzRm1TXeGV5lqbTlKyORNT2yROFadjWyOKhU9dc4gBKzcX0JHXaYIJGEAkcQgWD4LK6WiH5SZKNZlOTh0Z2IdASqZL69fyqUXKaFTbHweSvQueHH+2vtps5zqUYrBsns0cPcEtB0xEbXE6Y/KxffEaK7DnqPQPh7NBOLkcT6V2Em8bnUzhk8wchfOJVZssvPyjTd8xw5YkOFh4vX4hMcDp9URy50V19FVWIvZgt3mDhYwYdq1qeKCTsBD8Oed+z/Hkl2ql8auUQQ2sQJdcYGtwU/R1apgBKkHwh+MGil6KOXW4NgBOTyy5Vc5VfeOPFKcPDFLa55QHXZ/5hfglgllpACUwJluVUmkpauNkxCzjYwf7ICy2x2qKaA+fnHVvirfWovv5t1OUR+BKHARxnCzl9BhClTW5scyyxaWf5c4rRA4ePE762EnomsZNRUKn5qS9jCi8hoi1FO/zcY1jmFQdaRMMoEzbwoYHrOGFKbMQh7o2trfwFC/P231pJyJkVRNv3tQ9bF1ib42sVzRz8+DVJQZjKw290Xnt0KpDru9/braGqU+5tTzKqzV5X9bJoUJcySXssfHDp8RLgVgeoROOfxXlEnGeSkwyMcr/MAtJUV7dMBHuhNl/9fay/5vIjvG9uQrQIXmGtaYmRzsbsqYhjyHdofyo1bNw1Q0358UStrW5wAist6GQYVWUvZ5E5898vbhSQho3uuVL0Yjl0Xt2kmKGtTfVDZcy0wpBC05g4n08op40Sw8S9z3fWg6E6xeoDY2vmQuazJ3dMEhr3KjRIYXYUZblvIniYImMEs3YnJiu8RkLdmi7Tc3PsloxBl6PoBO+xKxIYC0Bf9kfaza24ntQsqowz3IZ4KCfAbwK2PQCaSADnmeE2VrtVaKd9AYOdYnPPSVOslCUvreM2PPBQrtCZWN8OUIDT3EUsc5eArYnLt3203bmtgqUDjzyb10PaE5Ebcz0L3cPSDfVc5RWXz9eqpsOJ4Dz6YghWjp0fIZalLxE4vay4TPlXqdPRc4sLgWQkHGXyHZIxS0j0u+elBLOegjmkKsPcrxAmpID5PAqUWAvH67lY8elqlQQgw98H8FJnhi0sddkxAgU1o6HMcY48L2P/mw4IYpiG4OZdLFySvRo9DkPBSE8M/5TMzFWKLu82CifuXI6JTrcwWOvKgpVxHjjUkx2Koe5r522VNHAJUkgE5ncAFJCRPNTHR0ye6wCEU8drZGZph70TtW7TNrPnhds6pdiczMQCrSWjVnbjsJ2QnAmoxmY+TMpt7V3kLtcAmRHR8UUxsBWOy2NMF3mqI62yswkxOrcX2rDRKxUMN/EqJjT9qbsa4LCkOe4X3o1hrJ/jOByJaZhaxYqvbdygCZY7GuIr3PFc4usSV+jIBnYfIPwYxyTgwm2NUMnh9eD4UW4sH/GDxFqoy+G2bbkDUENYQBShaGYc5mt1soeRFPacfURMmuT3iEdsOPS5IY7Ch7mybTdmHMXSYNF/HlBF36YZR07mw3INJC29ReC6jNYB7R3lSHDrCwqs8Aq2WsBj+kt0whJS9Dfmc1uejkc3hricNnOlj69TTSDxoU8p8ywoJO0BJ8BN6dgWd/3spUEKpDdOIFCwq4wQAbArnwsj3OtfZbY5DxFVYmz3UxiHvA435k9emYJxbTUPOzgUTyp12URD8+giBNnTxIuYJMkDGLFsYLtavNzajvwGaT7yhqR0WApOaFJPj1CqYpjUJkpdc4WerXhH3s1GpWjYH6lZn2rYGh8aFXqMErUnWasbfdfUUOkz58/xM+TAX8Zm5tWUkltSdLJyA9vIdQlJCiKChOT+ydFikVyuhCz7iWPkLjVKGinF+W32E6Ws6VMto/QOIUPxdrHq41thz2rMxN6ZMsWHRMCALFbGUVDmEhQ210fCKs5IprzZ+907nXyH+rUyNkoVEMXKaaIBUmiAjTM2KKF9Gmo1SvJn4wW5DMcQKmn9v1KRP6Rlx6D1QcJC288K/VNVV9BB7HGG1tat/l6Y3xTUj/aohgatMnt6Nqn0pRmKjDD6K6lXX5dt4hSXRxXJ+87pN2EQ36iHKusndWWRqSQdJFdvowujLhlurCLyW2jyMGSxMHQJWqdkvZIVtqndGiQQvh+FsbR4oEKIVUEXwmeqDCDK0bUGvu1COqMg3VuGzYUOA/kPRa9IRGAr0RCJtbROTdbCtDL0iK4q2wTta08c1Oz+3UXQTVADrVkPTiu3/98eHdsSEmZHVffO8mxgfUjRimIqiOiaY3QzsKmEazqj+i7UbZJf1XCxoJ01P8TAjQAAAD6BfwL5Bforz+/wH6B/4L4BfkL6hf0L5hfsL/gfsH/QviF+AvpF/IvlF+ov9B+of/C+IX5C+sX9i+cX7i/8H7h/yL4RfiL6BfxL5JfpL/IfpH/ovhF+YvqF/Uvml+0v+h+0f9i+MX4i+kX8y+WX6y/2H6x/+L4xfmL6xf3L55fvL/4fvH/Evgl+Evol/AvkV+iv8R+if+S+CX5S+qX9C+ZX7K/5H7J/1L4pfhL6ZfyL5Vfqr/Ufqn/0vil+Uvrl/YvnV+6v/R+6f8y+GX4y+iX8S+TX6a/zH6Z/7L4ZfnL6pf1L5tftr/sftn/cvjl+Mvpl/Mvl1+uv9x+uf/y+OX5y+uX9y+fX76//H4F/GKrYDCpSL/tuOvQxDhxSGE/YahCJF1Xjp5LzAPZ2JkGyUsX6oL/+2UZgH42aqN7Altv1jL8stlKrRp4+/FqK6M/t9xc3S3wJpKXo91WfhCg2frKodgen8T+Z+OsyHljt327877R82dHuh4PG+Exgn4hL7F2KgGjxeXo4APZTlci2S7MKozoEBkiwz1UZIuaSYjqI3+DYTh+ljn64AdwGAhf6Zjwvy0WH6nUC/bEI1VPsN7Q8xWME+HcWva1J10R45Voz0Ly0leFwGKvDlYsJBlPYN75fIdpgCarZMf9WC+BAOLwugHeaiLI9WIoANwY7d1F2yoLQTq66ufh2mtmeX6vAkWvTds7SpCYTEEeamRZ1QirJCCEpfa0lqFSGuZrSYxQOnpfvrma/EiPesrofjxoS7JJC/I0ma4unmewCdm12fOglXXr3GUBWkG/2afgfCHm/joyYeUiDUe7nDZd1uV99TqYQzplgDRfLuSZj1SvIobTHgzp66qyCN6C3qow6Akowar3XvCw0Blh0FKuCrQyLhFVxfwU6jNih/6nJCiEzAjGRcrg9pYT/sW6Kgtf6DTk4o8M3P0pNALMwYOZ9I2StxnFbwydCZ5WCIYW1sHij3FdPxDLw5ab0fiNeeFRoLPazq/OtJlTwdo70E4avYCWedDS++CFkS1L4KVwFQ6foqwBw+j5CTx7rVUP31Eqv95pYFsK9kcqqI6URxt+QW6yDw6AHhT9LQnyXfTT2bGGN2aWka2fm6My/+uist39nGM1s02JOMSBkBjzz3IsqZ69hGs3zZ2/QRlNosRwV54zMFY0ffxVPDyhAw0SfgCjrC9wWWn96lh1acGoMN2la0E6gR55UdEr/F80wiBRHw5skSAdEVtWFOmWT2M5rqM6H3cs2NoWXCxp3JYambyHJTZg52yRPSgm3PFWyAPOLHYvgSBF
*/