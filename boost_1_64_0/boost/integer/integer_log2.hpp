// -----------------------------------------------------------
// integer_log2.hpp
//
//   Gives the integer part of the logarithm, in base 2, of a
// given number. Behavior is undefined if the argument is <= 0.
//
//         Copyright (c) 2003-2004, 2008 Gennaro Prota
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_INTEGER_INTEGER_LOG2_HPP
#define BOOST_INTEGER_INTEGER_LOG2_HPP

#include <assert.h>
#ifdef __BORLANDC__
#include <climits>
#endif
#include <boost/limits.hpp>
#include <boost/config.hpp>


namespace boost {
 namespace detail {

  template <typename T>
  int integer_log2_impl(T x, int n) {

      int result = 0;

      while (x != 1) {

          const T t = static_cast<T>(x >> n);
          if (t) {
              result += n;
              x = t;
          }
          n /= 2;

      }

      return result;
  }



  // helper to find the maximum power of two
  // less than p (more involved than necessary,
  // to avoid PTS)
  //
  template <int p, int n>
  struct max_pow2_less {

      enum { c = 2*n < p };

      BOOST_STATIC_CONSTANT(int, value =
          c ? (max_pow2_less< c*p, 2*c*n>::value) : n);

  };

  template <>
  struct max_pow2_less<0, 0> {

      BOOST_STATIC_CONSTANT(int, value = 0);
  };

  // this template is here just for Borland :(
  // we could simply rely on numeric_limits but sometimes
  // Borland tries to use numeric_limits<const T>, because
  // of its usual const-related problems in argument deduction
  // - gps
  template <typename T>
  struct width {

#ifdef __BORLANDC__
      BOOST_STATIC_CONSTANT(int, value = sizeof(T) * CHAR_BIT);
#else
      BOOST_STATIC_CONSTANT(int, value = (std::numeric_limits<T>::digits));
#endif

  };

 } // detail


 // ---------
 // integer_log2
 // ---------------
 //
 template <typename T>
 int integer_log2(T x) {

     assert(x > 0);

     const int n = detail::max_pow2_less<
                     detail::width<T> :: value, 4
                   > :: value;

     return detail::integer_log2_impl(x, n);

 }



}



#endif // include guard

/* integer_log2.hpp
wgW8hJOYcyIpMqIoaqIN+mMilmAL/sF1PMcXeEk4FkmQD8VRDQ3RBiMxD9twGJfwBG+hkzJuIDnyoQoaoyvGYz6WYScO4Rqe4Qdi/Em7ITNKoQHaYyAmYh524iTu4hWsZMQGEiANMiIPiqEqGqIFumIgxmMaFmEd9uE0LuE+XuMHnOSUB/GQFrlRGrXRCr0xDNOxDNtxEGfwAJ+hUtCHEA+ZURI10Aw9MQZLsB1n8QAfoVJyHP6LdMiPSqiLThiMaZiPFdiB47iOF1CpOBYZURA10B7DsQDbcQK38QY6NTkIOVEZrTAUM7EVJ3EPHxAlDfkReVEJTdETE7EcO3ERL+GkJRaQBFlRABVQBx3QH1OxCodxA69hpSPGkQy5UQ410Qr9MBVLsROn8RhOeuqMNCiMKmiDoZiKtTiIF3AzUCbkRU10xySsxRk8gZ2RuEIcZEAhVEdjdMVYLMQOXMBTfEf0THwepdEE3TEBK7EHl/AI3xDJTP9EDlRGO4zDcuzDJbyDl4V+gVyoiGbohUlYiG04h1dwshJvyIayaIRuGIel2IOLeIJviJKNtkBuVEVbDMU0rMQWHMdVPMQ7fIfJTv9AQmRHadRDZwzHDKzBfpzHdbyEyEF+RArkQUXURHsMxRSsxB6cxWN8hJ+TGEUaFEJVtMIATMUWnMBdfEQkF2VDQVRDa3TCAIzGAvyNPTiJm3iOr3By0/8QG6mRG6VQG50xBouxGydxDx8R5GG8RDaURE20RR+MxjyswR5cwEN8QSQvcYAsqIwm6IXJWI69OIun+IwwH9cYmVAcNdEWgzEJi7AFh3ARD/AeTn7mnEiIDCiE6miLUViGg7iCF9AFyKvIgVKoi26YiMXYjCO4jAd4B12QvovkyIMKaIY+GItF+BsHcR738QY/EbMQ7Y0iqItuGIdF2ISTeAhZmH6JtCiImuiAEViEbTiBK3iM91BFyEVIi2JohN6YhGXYjCO4hEf4CL9oHOtPFEJVtMRQzMVWHMNNfEGMYtzLICeKow66YwpWYRdO4TbeQxenPEiJ4miKwZiO1TiEu3gPrwTzUmRBeTRGP8zEJhzANTzHF0QryZwFGVAE9dELU7AWu3EWt/ACPxG1FHGBbCiCqmiNoZiFzTiERxClybVIgWwoi3poh/6YhiXYjEO4iVdQZagzUqMwaqELRmM+tuAIruMFfiJGWdoVRVAP3TAJa3AA53EHn6DLUS5kRFHUQweMxELswGW8hipPGyE7yqAGmqILhmEGNuEo7uMzTAVyAlIgByqhOfpjAhZiL+7CrkhdkQFl0BYjsADrcQD3ISpxvRAPqZANhVEL7TAcC7AfD2FVptzIi+roivFYgQO4he+IXYV4QRV0wQxsxAW8RKQq4ytKogkGYSH24z50NXIZcqM8GmEgZmEjTuENolanjiiBFhiMOdiMi3gDvwZjDHKjCtphNOZjA47iKt7Crcn3Ijsqoz3GYyl24yJeI6xF30RuVEE79MNYLMJOXMRbRKnNuIHCaICuGIMF2IbzeI2gDn0AWVEaTdANIzAdK7EDZ/AQXxGtLnVDJpREdTRGB4zDKhzBI/xAzHrcF6M8OmAMluMgHsKuTwwjEyqhBfpjDrbhPN4iSgPqhLJoiaFYgkN4AKshc3jkQhk0QW+MwAwsx1acwiN8hteI3I1kyIYiqIYW6I9JWITVOICzuIuX+AjTmHEMOVEYNdAa/TEBy7EfV/ESpgllRCYUREU0QFdMwEocxQOopoxFyIC8qIim6IeJWIg9uIKXsJuRO5Ac2VEJLdAf07EGe3AOj/ARujnfgdyogGYYgBGYgeXYh4t4grdQLejnyICyaIXhWI49uI6viN+Sa4E=
*/