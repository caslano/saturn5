#ifndef DATE_TIME_TIME_RESOLUTION_TRAITS_HPP
#define DATE_TIME_TIME_RESOLUTION_TRAITS_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <ctime>
#include <boost/cstdint.hpp>
#include <boost/date_time/time_defs.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {

  //! Simple function to calculate absolute value of a numeric type
  template <typename T>
  // JDG [7/6/02 made a template],
  // moved here from time_duration.hpp 2003-Sept-4.
  inline BOOST_CXX14_CONSTEXPR T absolute_value(T x)
  {
    return x < 0 ? -x : x;
  }

  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_bi32_impl {
    typedef boost::int32_t int_type;
    typedef boost::int32_t impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i;}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return false;}
  };
  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_adapted32_impl {
    typedef boost::int32_t int_type;
    typedef boost::date_time::int_adapter<boost::int32_t> impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i.as_number();}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return true;}
  };
  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_bi64_impl {
    typedef boost::int64_t int_type;
    typedef boost::int64_t impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i;}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return false;}
  };
  //! traits struct for time_resolution_traits implementation type
  struct time_resolution_traits_adapted64_impl {
    typedef boost::int64_t int_type;
    typedef boost::date_time::int_adapter<boost::int64_t> impl_type;
    static BOOST_CXX14_CONSTEXPR int_type as_number(impl_type i){ return i.as_number();}
    //! Used to determine if implemented type is int_adapter or int
    static BOOST_CXX14_CONSTEXPR bool is_adapted() { return true;}
  };

  //
  // Note about var_type, which is used to define the variable that
  // stores hours, minutes, and seconds values:
  //
  // In Boost 1.65.1 and earlier var_type was boost::int32_t which suffers
  // the year 2038 problem.  Binary serialization of posix_time uses
  // 32-bit values, and uses serialization version 0.
  //
  // In Boost 1.66.0 the var_type changed to std::time_t, however
  // binary serialization was not properly versioned, so on platforms
  // where std::time_t is 32-bits, it remains compatible, however on
  // platforms where std::time_t is 64-bits, binary serialization ingest
  // will be incompatible with previous versions.  Furthermore, binary
  // serialized output from 1.66.0 will not be compatible with future
  // versions.  Yes, it's a mess.  Static assertions were not present
  // in the serialization code to protect against this possibility.
  //
  // In Boost 1.67.0 the var_type was changed to boost::int64_t, 
  // ensuring the output size is 64 bits, and the serialization version
  // was bumped.  Static assertions were added as well, protecting
  // future changes in this area.
  //

  template<typename frac_sec_type,
           time_resolutions res,
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
           boost::int64_t resolution_adjust,
#else
           typename frac_sec_type::int_type resolution_adjust,
#endif
           unsigned short frac_digits,
           typename var_type = boost::int64_t >     // see note above
  class time_resolution_traits {
  public:
    typedef typename frac_sec_type::int_type fractional_seconds_type;
    typedef typename frac_sec_type::int_type tick_type;
    typedef typename frac_sec_type::impl_type impl_type;
    typedef var_type  day_type;
    typedef var_type  hour_type;
    typedef var_type  min_type;
    typedef var_type  sec_type;

    // bring in function from frac_sec_type traits structs
    static BOOST_CXX14_CONSTEXPR fractional_seconds_type as_number(impl_type i)
    {
      return frac_sec_type::as_number(i);
    }
    static BOOST_CXX14_CONSTEXPR bool is_adapted()
    {
      return frac_sec_type::is_adapted();
    }

    //Would like this to be frac_sec_type, but some compilers complain
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
    BOOST_STATIC_CONSTANT(boost::int64_t, ticks_per_second = resolution_adjust);
#else
    BOOST_STATIC_CONSTANT(fractional_seconds_type, ticks_per_second = resolution_adjust);
#endif

    static BOOST_CXX14_CONSTEXPR time_resolutions resolution()
    {
      return res;
    }
    static BOOST_CXX14_CONSTEXPR unsigned short num_fractional_digits()
    {
      return frac_digits;
    }
    static BOOST_CXX14_CONSTEXPR fractional_seconds_type res_adjust()
    {
      return resolution_adjust;
    }
    //! Any negative argument results in a negative tick_count
    static BOOST_CXX14_CONSTEXPR tick_type to_tick_count(hour_type hours,
                                                         min_type  minutes,
                                                         sec_type  seconds,
                                                         fractional_seconds_type  fs)
    {
      if(hours < 0 || minutes < 0 || seconds < 0 || fs < 0)
      {
        hours = absolute_value(hours);
        minutes = absolute_value(minutes);
        seconds = absolute_value(seconds);
        fs = absolute_value(fs);
        return static_cast<tick_type>(((((fractional_seconds_type(hours)*3600)
                                       + (fractional_seconds_type(minutes)*60)
                                       + seconds)*res_adjust()) + fs) * -1);
      }

      return static_cast<tick_type>((((fractional_seconds_type(hours)*3600)
                                    + (fractional_seconds_type(minutes)*60)
                                    + seconds)*res_adjust()) + fs);
    }

  };

  typedef time_resolution_traits<time_resolution_traits_adapted32_impl, milli, 1000, 3 > milli_res;
  typedef time_resolution_traits<time_resolution_traits_adapted64_impl, micro, 1000000, 6 > micro_res;
  typedef time_resolution_traits<time_resolution_traits_adapted64_impl, nano,  1000000000, 9 > nano_res;


} } //namespace date_time



#endif

/* time_resolution_traits.hpp
QtPEV33L0NfLY/gRKXsol92GyexFyey5Rv7ZQDbVl07xJVN0ky6yyUxWPt5M4WQtnZWJbJKek07TYS7n82S1L2dZozGTbt4A8qwrzElTdtSQm6qMoC0/UrFJW3Silpqy5ESrL23JOVeQouJcbu6pP/wB1kvmLFLA+z+/9+Rro73i2l8yTL9RJCNmlxEi1il4aqIiXYmg7UQ+ViIykSIr2SLKKVUdUCgxeSgVCS05kbRQUHJswHZso3niNngMN4tucJZms71vC25mQ5UAB59gNJhmJHmCNprWhpUAL/sX/Y3E/zLH++aj4yaR6U3kON6w7Omal+DFfa73ZTP+5dFlNYRuVIEs9po1jPpNpeyrnOmCP1Xy52z6Tb44aWvuFVs7tUjDdU5pWJW9PlDtWvNSrhntVazG3kWNxcr363+tLtb/28Jn/7+tQIul9/e7WI2d08nFiqenA5yGvr/MMsGjKwj2A89i8WJw63r8PcAbOLyOrBbeX7fgNvaPhCsFV09DOA29I9o20u6r6PYNdFv62j29bS7utnfH6+u9rSPZyjS29nejVj76tY7lBXX65cSGKr2RmBVeNwyrWc28P7nyxrdP9PBhuxf5/f9tjP7bgAE27iokt08Ef2MKVvwjmIL0fhjHIL2+IJBITmtzG2pz62tz6+jyaulEd0Z0lm2xmsLM5gT8fGjRL8O/xEiE+lrQLJ9TBm7vDvzg6ru991m+eZ9PNfkz3kf6/Fw94Vjo6vfOplZqcpZCyO5WTVrLJMCsrh1gXSpau0vWgwbJNeZfh1W0GeZBYbDze6xg3rMNBA9QdGwF9VFoLXyQFLR37YPAYulRqWHirrcDRtt9Vb+Guuv774IDq74Lt1Z2Xv8Kqv4k/tfYE1L1R0n7o1sbIqsB6d4Kz2aItblMvRoi6uBubYCCXrC1tBMC1rD3ZH+qd1JSaDVW8rou5cXqoOPVyNMwhMEO8ZrOLX3D8GfP7Hl4wsKB71YUK9y/1SmW3aJwWCPhewurb7rJuIT8LRXju6xZYIwp1KVo0h7zQkilMnqew8/YeIoK3ViJI/luVRR4BDpyMF/ewkIVr6hAXzdQRW1MCW1HsuwiMtCKLknDCq8xo4Tc0XTGqysZfVtT0UvHGYH1URx9Shr2fsRjq4pf/6LsWgciB5PWRjNOi7zXTO4nT2BvG+RuKfL0VMfBiI+P1duIGhNunn38BPxXcZbXfk/RXSry19DPsaqb1kxUvPzYLA/+vOoO78bKMDXFmfWYcaDHjgAHZhZsXhR4nDtEcLPHYH4AbVxIObkcWDARdf7CVLmcrOycCIW8kqcEfX5kHhcSlJyMwluFHB9qpIxs7FyOyav5XdKAtFw5JxcWBydSDg8nWpzCFlTP4Z3SgDQyvWVPTqLzVNNk1zQK49gvilG5UIriA1QnrX/2QMbkDkyomVAQ5an4ElN0BZ1JbQWFhAxZu6i4whkCrcDF4rfxLsHDFof4wqlTCS91vd8ehGG0fwd2NvJyiwSwmgq+61Y5h5MbAzk03a/EhI4wmyq1RF/Y7MslXMOmMyqaz9cHweBUuPXcvd2jNEwrepWfPvbigEti3vaMXf/pcV+mB3pd2DsVN1bAugrZtsePpTfjKDlka8YMd7ZJ/TTd6QlGVCQZTPVKWczqysZYmDbIuyxvWrdYiZOyGAxKbkmA/rqzYGLu7sRFeN3zu97UMrs+HNYx86xW4RhLViHS1JjN2Zg8WWn++/dv5l2mgQtzd2uPYs7UYVoTzgWWZH5z4OAS6ffbU0uKLr8+R/oUetpcrbmzft5U3clKO9NF4tNRaed054O29UTm5rFyqzx8q7A49mnMRNfJlFwjJ9zbYGRX9TYVT3VhlbCrmi73ekmg1QUv2iWq2IJAq2s+hFW4NKuCdceslPUYKJuCZe+QFndGcaDUBb/rDSrUcgLOCndTa/AjdkXbt2W3MqqJ8FXtC6WqPYMwiBiLj7MhbUDxnrLbTC1r3/ptZ1EHa5auJCrbHLnTcgjtsxDcnkhfgkxzBPHysELUiNMAB050P1eqxggFXXaiSGOJoawJzCvF69SdKGwZQ+L4MUMLVospKo6QvHxP6d2ZQWtV2cMmrPFecrVg2OwJTGUVnL7eVGrTed2abIiqEWmCvar3mvsvzGhbWWwEaTuT9IWrODhhmUtsQcyUrQEZNmASHTBheNgqaBAt5QLO52ph76hAHvekSELHGB0s/nP9c+nX+JIDYWHfr7vBQpKvuz2S6PAD4cihs5HhxJGlov78anKMj/Q42KeXMZRokEgPff0qfj8WztP4jy/Jn10lo4F8zHlQiZgx9qS7o+VX9DVTDmFZEx5gmcv30YTlg8I2Lhx9+hGUktC/Lyx0VYqKyuttFwHxWtqiPWqP/B6yQos/stE3Gt0nmmgzZw/HnB8m1rq5bk/olrKns+uye64sxaJ/zlnm589FTt7QLTUN5vDMOevL1r7LrAI4btx/GS/miAWCxNu25PhlsUUxhA3O/RrUiUulvNYBPZEQiyLaFNAF3GsZhV5a8OUbC6coQjBus2bV0TNIPK5q2BzLDOUq2dLIRny4OZ34ZveDE4q72Q2A+nAKfHAJXmEWAMvCToEXjKz6ChX0dnDZ5EsVRCJVRH+Xg/5U60rA9eroRgARFglCgEgBDXvPSPG3wIrR60nQjyRP11/QT/2Rgttjtxpt9vAo6edIzyObYnyAegqnk1CrSB5ZSZ7QAe4qBHoJeUMjl0PsGiZDrSX2Zou1pJop0faigmmidFTuxH3OD/lkgJPIkijdX6gmpVIqYDe1EiPWVllkMSjPJ/PFbI8PF4o56oR/NYsYOyLOQZuq3l/a52Z4lXZ6x9ONpx5o8Py7oW9riChbVzOkS4U1gnTsyalHspmcdJeKaj5kBRcnsz8yrMSlR11T6ulGlUhTJmll6+mJot81OH5abSPX7C4A2ReQPJ2QiRbDhi5bg2aJq8Wv956gLVG/6OGdkC9nn1LC0wuXBtkjm3bfDKXz24NPU0NbRwZjlImhOcGRLV9bW27KhDSXskZG0D7mqGm+6Oi1isWAzGxzOmoB41SSNDP89w4l0jcXqCHSG5RYXf6/4U16tT1Dn0ElHyp9jTDtPY28LfQDjSZ1K6FIpSAFy8holuCykcWFQRXqaeHrOSGqjqnQzsK4x6nNJq0Kv3P1Ow7bqIZApVmTqBj6+jS2v/+g8NHyP3ZE+gi95WjpR04O5zANmujM1BdQgxE8FCfkUBcsk/Rj4+13V5pNpUkj6p2QfMyS6ZuEzC0ztKZDUUTFDHQ6ETNy+cXLEzgiGDA1Bqff0Bh+tccyn6BTQRx85NMMKCVhT53cTv1qVBV14bo8afyUYlI0MjuWjtTh6FejTILiQkUFtgQC+gUAAgAKAAYADgABAAkABQANAAMACwAHAA+AAIAIgASADIACgAqABoAOgAGACYAFgA2AA4ALgAeAD0AAQAhABEAMQAJACkAGQA5AAUAJQAVADUADQAtAB/AbgB6AAYARgAmAGYAFgBWADYAdgAOAE4ALgBuAB4AXgA+AH0AAQBBACEAYQARAFEAMQBxAAkASQApAGkAGQBZADkAeQAFAEUAJQBlABUAVQA1AHUADQBNAC0AbQAdAF0APQB/AAMAQwAjAGMAEwBTADMAcwALAEsAKwBrABsAWwA7AHsABwBHACcAZwAXAFcANwB3AA8ATwAvAG8AHwBfAD8AfIPC/XGxwwvnUC0Y93kaaDk1FKkJlpOXRx9Gaa0ikxypGwWpFZWCcN/Z0dMGG0WD0YmGjc1TSeeAt8YdQQSlW14SVMjQlKVDiVJ5KRanm928LazaOcDkYE2NNNJWfb2sLZnGRxVCX6KOlavxpsqlMOmjOLpiLa86ZyJzBJIKiOYoqrfeOgVni5Qd3FJafc6UiTHi0QujBw1FEEobDf8zHK128WDOGxo+Vd0NW+Vq1STZfoR8NiAKnHFxqM4juvzKa9IweQjuHvMLzHCxe9XywoNowH+Hx79He7dDeBfLgc8wE04Epc//QTwFBT4XNBTROLqViAO9K9ZOOvE374Jc4gdOYJit9LiCYSO6sMHYm0c5fIQ2d3+NaMP0ESEaaTbDA6NC2SoIfKndKfOmfX/HMzWdi8wmSQC960h7NlYAhsUbZtr+XBkMi2XtSUJNxGPOkhjoWkeTro1WGGxqTvc6JUM+FSWQd7kKkgSkFLYknJUwNjomnEaaXLqB6gp5aViWTXajUQ3ai3ZuO50L4IS2gJUF0xlul7maRYmn9g/j8pcOsg3AHQygZYINyinoo+kWWcDLBdCiVchLs8+sWxYBiUaMUG6fFB0HiYCBSGW7iD8cI7TyyxTLjqwHOsQQoX/j4kECoJY5Ui6vo/FBWk0K3vEDVP7WWTkhssCZwt/QQN6mvhBCX0ij0Zl+0il+Pw+REL7KJUExi+CSKEsGEmmSHA4vDCG50Q+bAShoiE8whLbxCEm8zhLUhWAOEi/Nokh11SsWNWizkUPmsFSUDrQb5JWTQVXGixk0t3jAtzNVEqafzqR3ONX/rpCoZRsdP9oKDUyC+sV2xUo5V5Uj/cnbsD/DLPCMqYa0KN+TOzSN5ZD0K2iG8mb7fJWryBZGtZ5RyxZqWIrXrC+BAWE4iLsihb3ljonqDuzWU++Eumperdh1wyTZhbThqLDVrcVPyVakXbPvBV7iub4vqIXdqaiHM7tKu7TuDWpcOaX4f21XxIZg26yTTEVlSzmGPThuSPZqVqPZFoDhHelnG0Ytx5Cq5cErONy0tkbsldahsNifn2enN2BBJKrlT/lN+Uc9Wb+/Tv3BM2LHMAwbrsjZ9e89SmEkh64OX/t0IrgNGJgsBrf5FzHze4Zht8db/TrZI4Hv10sfQ+9Wtq+tbDPGTsvrjZr13CRLsTu/q+3Fxpn4C/nO8/IcA96f73v3lkLz/J5nelbePj+VlcAWeoPs70/fox/P1Rb9L8pf5pe8Pg8/zMslieLfdi7/QN/P9er//91YpxLZHz8fVEAYB1/pTqPiN/1vS0Ye9bO8PTP/RZ+ppv++HwhiBu6zf2bL4tmsN3l3+DZfDes7X2wvfy6P188XYgb6rr/kciS6F3vvr4SLB93p73/1msP83TvtP5/wLxr+VLr6X3fv5FzlyPwb/EfyPUf9cv4vwfj+WtafT5YV99jr+u6ducb/Xh/wez4vXW37fR3rd4p+7l7zu9ryO+3B+jobbrVj/r5k1fs+7uRoInSP7rOk2kOv7dpnrVjYOQQ3IO02Zj4iJE4Y3+Dd4165PBOTmub2LC5dUemb4Et/cPuEELkWTk82TK3xSIvdA598OvTR41D33YBhVE6ifPQJHyLNgUq4SKcrz16vi03KZiKbHX7/OuC8dKq+UrZJU6qCXWAO9JAv00CvUuSyFTTHH/FKErrlOdDCW6ncgzn2tGrt9GpMzdqWwVkWbZlknsN3fNIGPwOnuanT2wwh7JUvTTc5kBb2ipfKTS9tBzy5U3jeaHl1P1TpxgFRE+2Apk0rZSYcGqCPdlZkgoiR7tJOQFJ79JtI/Nzszwl9vlGM3CQ/gpHK9wtP7STB9xR2lNQO7N/DOh91oKrRl3FrpvXPPAx+4BI6p+8ei3nALXlNuGnoXQ7TQUV7nhMkt2YAmaFN9dLgx6lyonwh91Ruem8Te+xggfl8cD5jmfrYx0PyGyfPXzIFMv/oj0gELd5fAJuvaw1mki1bf1R4Wuo3tVqGtctepIQ4r7VJ+BjSJdV0Vc+q8aPiIp0R9V1lb+zr9y64dvL0b3K4dv1174Ard0Zulg5fVwfuxg/eXXXzERvXgVW3gRvXYFZqDt6hOP/iKPshK/dgTTIcfkrtCMLcGiLtCPDflLnxUxxD25h52x5DXpiGwu8Yw3t/duKUBvL8HcZAdJMR2AsE4FYE48wfgoJsBETgLu2FWu2GPHUTA7KT7YawdgDhDXjuNAbjoDiQ4uxJwO5F4HCQHQJhKME5tIM7ygRjYZkUEzuLuqNXu6GMHIzA7+f6stcOJ9e7sheMJ2KYnkrtgcLcCiLtgfDfh7u+MUGVxsKZfW7WF3iwu9WHP1qeCcLw1heIsLgLC4SwuGsKAlorwGMtjT5ieA64B79lRN/uFYH2w3b/c27N93tMqH9HrITgkE+HNYbal7N/n+wO4bg7vUcm/pCZtwtun5tXhKYeCH1l5YlTqrNyWrM+L4VaQZtNScT4LmvGMYq4StHrwkoYNZyEXD2Kx1uHK2wgGf9yMmDhtBbgCG4D2+Hox4mk90s5cTC8fX39lugltjum0dOMzSZvnyiUrbPSgOfRccx5Nt/MiVCTBPSDLG9E6jAYFCOX2ydO5BW1SuU4+/9EL8IekHXnfi5tS/7bWfxN9EbSJxLAT7oGQ6P4i6sA7c3FxW0jREzRqR0JJHTiDhxHObgC7SnBdxSLOO6B1q0C1Z7nMfYSlIBtgbKxJETDvoh78SLzhBh3gAEnFZUk+8SCeWWB7o3xRg2h5ouLOq9w9ueJFfmLj9eQL5UxZ2wN9TsH7Xlt1yOhg55/wOpU8npFXYrDBep+lXg5Fr5Q3lfeqRi1pe53cscTA1eq4qdI5MwKjUTcJD3ObV6b3ED/6x2dFdKgHlC9OAOJ8F4VL06VTPiGXahjWor23YOb6lFULH40mPycQM6+ToUdypab+BpelW7Di2bwMzwW8q543LA1dQWnGpJai7iQwpuGWmiZR2CDS3OlmbV6Od8ak9zvACpIZ484Ji37uwHTIqLROUFDPbEJd4x56pHHxws/rqkgdoffaWMq+4ZBNettoYoPWM5zspukQXvq66dA3zWcgCUHz3rjllHzqJ4WMoPkQJcsGJa2leXgW2Wzi2S/NpXF4CJle2of2zEwSQdpro2aXQu0ayhadJmbdtXl5usQvDbbJJIOMhBaqgXQ4iYH5zlVsT8DW/FapTesMdVhsS0Bs1ujL5q0fL0O31fBfq66TAfQPt6wtn1HTqwNZ0/up18J1sOe6mWt+WD4czD0PW/7aVwj3XqmXfIA4nlNWrRyOgkfz7GStofAkBscDnlTvwe3e5Eti9SdzQEG0Hvd4rrePbcqA6Lz4rpXo7n38ALp5N1on7zirdq+A7VhDDB69mUJDMVIdISY7BEzFWG4rSjN3NAGil+KU9Yj3CAYvreAkCBXLBV8GW8PsK6R3RtCIoWYQMr7aTzXDg+5Rf4sGrYRxXEauHAXqeQEnfYoD72IgGdfzQCh/jGHoTomb7T7aCpeyeHgs2zcnhengJWsw1s2gf7l9/YRhs+Yrv47k1apiXdSIqiPQWaO2w8SjwY6KDkPyViqETmqwS/+4kPOlDcWd1+VqvF6CkKoeRYkay0NBOroP0OPVx972+uXaTeAsAwiwtBaOEn6X+yX7opvau0HrcwEWvgU5pOWdpAXbc3Q1E7xuHI392/NPqr6fyvvPjzsB3M918dbfsDGS+JuKEbujOf91W7NwmbcNG/IcrvDNUjecGgoBrxq25o8W79nRKDeNDYf0h9vlOdU+WM7vAKVjXvvWPWghDGf3t6Lp8NrhXvAMt+ZWkKoQ53Hm6+APmys57rkN0+WLjtJeSNfFSASYyZFetaO33Bo3ENG5KhF2k7+yqLpKkXaTRdqUXnJkXWTReuqO+u7r01VjmRhctrZWSozP5/jZ9x5KRnrJzvQTnelHmzR2WB9VKVoFU1Op+i2cJVoFy6o/yiPSDqFg1wE2S6ylGqF1W/Srr8zml1PqPWzdUsDoBdH45GCZ4vjDNCRtvguUk3NuR0bpDowp68StclX4aXiXK/4+82Lhbou+iJCll834K8d5bG7e4NFtI7DleCgPCe5XPe+C0bUz8F9SWyd4kRfp3ldxNid43KG/xFuaF1uHnPs7c/GbeV9pFV0P2+aLyw/39cJZ1PTUZsB49NZKu3xa1HeaNdcC0eKE6uw4gJ44bNHHA4ntgHjxoWw1xHDSEHuSWtHy96XR8i+JHeipqFyqUbvQQu00C8VL54spH8ehe6lD9UQL1dVuq1E/o4I2S1MFU/8UFDFQ0sBWo4ahhRpqGoqUMhRRxoxDA6cKCShCjkMTpQpJKEJOQBumCmkoQk5BI6UKiShGjEMrpgqpKEZMQjOmCskoRkxAP1CHeooa6qlpKFDRUkLD/Nb2Lo/kG366/wBfxnbG+If5hJuc0l1N1U8v6W1SOXy27PjJNVsQx1xzEHPKAYxHUXIQ4poTEYey7GjENdsT16xQSkC93cv2luc/D5U134muQ2nhT7w2M/GCtTY0gcDliK3uRecm5j9u0S/yk1GX3a5ZKKh3Wi5juboweBqf6RESzW+4D4ShDokSntGxMDvOQHEVE+PgREBSnLM5N45J0Y3JOSeJQILBUUnLguN0nTUzie9V4SW9r6t6VzdOVlfRgRO1Qp3AvmsGemPPVeAkg/f4q7sDBGMspgTihaUj589XzTDkDXP2WlAMgpiD9Sske1H+X1Z/7j9JFUNmvKeu+/yjEcBMNhoOVmHBwDqG9UzCRoIkTBw8Gzj5jWsMe9GOb7x+lDvW1mNoO6mOBA+XrdTcQLhcca7rNTZvbd3xhlA9I6yDSggrP7bXn4YbFcUcfu6ORt2O2fmEEuCmDLuFwWg65wvoilSlVKARRZDdtglyVt9YI1XZWnEgbFEJoUwmtwqRkKLEQoLnu4XC4bD4PCbjiIWwaNDEyHbn5FiwMwMJhcKgPe4vrTfXY5mZ+i7fr1u9L507ub7fR3Lma+IQBgj8lq6bboT+xe3HcVD2ATYsk28yoL3b8HwjZyRWjyXx8nOjHp8F4gf7kLHEx6JJdces6XbYT3cs49w4c2c+Sc/BnluiF9BhPfTZGEavgzcvYF+C/Y545BHPXFeBakEbwrd0N5U/swxNNfOrzdG6x64YxsMlREgrjqf6Ivn9WH8FoqqZ/ezFE+ToTluKuqe6Ig4U0UTvKidVD8g7+VTvsF4myViQ+pMnN2XMlPPLy2K4T1UnsRmauDrF3hRU9S4IOvMY7MC+7vWe5UKaTijvJjEavympZh/b0O++us4i/0CGBlkL1ZIVYq6NYyigcVEosRiDjdx8LO8b9TCkS29fxR+8/PsQf6NYOvGAc67N/NdT3anDxsqZLy0m5H5Sdm26WDkhUbFGco74Iyq0crzY+WZzP2njxJeeKyEuVPyQfLa0AAIs/dNEMRF0d3Q=
*/