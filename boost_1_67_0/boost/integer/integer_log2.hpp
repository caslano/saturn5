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
+K/2P1RR+jzG2tRmGkTcxwAkJix6Hz1POhInjbaJWh12TZn1FAhf3cfw8gYKtins6V84lza3Tn6wvStc51kCGMKSIJyl+ikXOZppU7nwk38PqohuEp/e04Z+JGm8OWBRkrD8Z3ashp9SOVIXfw7IlOXSO64I26eXG1On/dxp2y9UaXumLRKHUm8p7a8GBdgNll+H57bim9v7XV5x0QeS4V1bkkvQy6jse//0+F588+RPQU2JQ3qAqHh7shlctWMzgFcTQ0W4VERSwKxbY5v1Z1vIu8e6abQZqVuQKcXpp/9dU3kVevGhnq+x55mjN//tr/+6UMQSzM52IlhxuVixV1ZEYUzsE4qsmvFBcPuHuee0NsqQPK/FI+zVOsFG4oDiUkZ9c3IKD0GQU4X6Gpd8tMmro49w2JJADLzMZKJHINLNDJgvBwsfPjBkiUdZuxfzaAqbOVMpupE97J12/4Fmw8xL+i8Ytk2z1MpwX2PR+GYf79yapXqmSCNqr/Z7cIuharlQkq9pSs9siv4KZ6oOUUq7Awr6gT4qyuBzrenxw6OMDkHJA9r40XuXu95wimvZXid3BYqqDE/hzH2sSjylxd6GsKfRao0YD5bq1FhEsrUn6ggqBDwRv5regUrNX80ZL6jPOdYklT4Ooyr1545OIS5PmEbc/VK2HyoaXG4tVBH/PJq/wx3h+bSMn1sbRM5mxdI9VWJIH2FcmqXN4Va3SEh3qvp0mWk9FVPtKaJ+yazmtdZgiXcQspesbTRg4mHT6X+/xekzgMTV3zahC0LtgyHmhC5HYm1yJV7H3Yetw7OoEOAY4JDWppOGa0e4Ug3bn7/H7uXQ3T0mx+ecpIJHffUfqlL6nJtD8N5i7UjWIsCRhp6X9ZcbQbha+d1xtA4Nkbupb7ZnrCN8r0uHV2hPjWyNYLzmsN+9iVr0sCBIIhj4Fbvk/7lLr2qzSa7L5el3i9w4IO52H+SfGNiuGbyFeXL47c6G5aaw/1TDInnVBtfQJIQj49hLN3Oehg7K6N9aczoV7q1noI3XWYDCKdUdbPCOKpvLB/lD9w5JmcaEVha+WEQMGVQ5N9qIagMJi+OOGBuztRtFb3tWuau0H5k63I3KuIhcEC2b/MkZszgh2zx4Y6IwhaCTVfhhN6Y8IP6UWKkAgr/5d+eaWgp6/CldWoiusnCaojynguk0wozJppDU3aI2N/rMb76PcjIrSvffEM4teWCy3S260H8s7yNbCzYum9fMQPEe4SRoJkyzapdhFY4LdizBFPZ2nhbPGCGu6Xsbuhhdb5HOOVRY1yydZFuUdGc/mSlV8xKt3TmlXC/JYmtNRhNk19944kO3uith1/HThmtWg/HhWg4BcxSjBCmXmS6Wu1CSUr68P0jEmyoEaaiWDJ1tLjNDWvwZ2Fb1AufLtqWPZKl7hifpDtGUdLZp9YWPWbCa+fc5IgoyRY8LbzPH2XOMGTTj11Z/j/EFzvcXemKzfol7kzXkcDKHT4ykjsnFjJNHNWDqj2rvAjF8/HvEb9yxhvlykAdgWDUGUBT2FR12Da0XhZuEEHQuzug4WIz60vyQKB2zopdJk5SRzO8XlDrSN9lfZbvwc96HrmgmqiQe7cfsCeDNhmJSI1nphe/UXb8hwGgoaz7yQNchFRJb0qek+BZ77Ev3t5mfEfIHGO6WZ6V1QSGpHnUikUeFu8XuC6G0K+FK2PBKehwnIx7wyhVvjUvWmjb8RPSmaehmqIydrLvnpcgWZhQlRToynYwfXxF/iOZAkC4dYwkYytI27Yo0O2jCfO8I5/otKevSYqSDdbM2laF+wzarI9ik+njaIBhb8vzXdUEp8mYwuTDvK7UnXBuLZnOcRJiZwpQuvWjT+4HCz2K5X88MAT2tgzHCojRa0gddV7qhaHN1GPzc3OfkRlkJbyx4ni5tt7XwhBwth3x07SpcV2Mw5cgopD+PGgwj+FuPcyRS2pUix4X4UTdp2uWXGcet5FDUIiWngNFEXUcvykdRTj/BgNedxYqBquYHSvlK2u5NrlTJ4NEe77F8KQYDTn6/VA8uZFMfGYXQmEmsQBIi0wsMmtogxTYK/uoCNMV0XPVhLjLHzCdbYyXalEuZPM9rN4ewJjNXqQ9di4CQ1GF8y2+DufQ5EGm3GWSihLFs5kMDZL41bNB4v1nEIgxraHy0tMByGSrJ+FWw0N/W0H+/DB9nRaSGMBbxcEeO1RRhsGGNPnZGdFFGqFLlD38i6CHirsvG3qBNUB6EvDrExXRSK6Gba0aq/h2NEhAYd0ChM9eJVzbqycXU1knHSK3/xoG6vBc7SDbwb381w7MqGU7pT7bvQMDaY2D06V880PnIlhLGSWdzgALu6s7ggUD2Q/thmvgc5sbAJ53cFZGd+6ma32R5M+Z6uN0fi9iLNLrsV8TdCXqhYOYcdqXYy6URW8hf3txo00tbzy4O9PZB9L0/NhvGaG5gyZb1hfuMlpYsLB8m8Wg7e481p3zMyZI3P34YlA1rw+dSUuTiJJtgBrgLXf7Tchip8O49mhUQfPjWkhlC28VbBneq8QsmhzN3kGSO5EriNYtAilFTUIIygDFK+VEwRjNVRVHi2b6lVc/031WWYzYBvC4dOQ2DggHLP9wRhcPti/tql5fp1IBO2Y0243ESq9/sL5d9WcYqLYtMzsoG+RRi5jyXkthzbXFclH4P/xnTgzAhSf9+mCc0zb/Sm8IbQruf/nDDMk+8hLFu8HpGs/XJsbQj4sK6Jwn8lw5PKq74T1aKNVZd//ZmzvK/EdS9YCWiHCe+hDGpY0m3QUltWBopZp2Bd360IsyKObfH9/zQU9N1z5jykdQmslDi0i6I4Rnkz354OTs0d+gwVXaAU6iuSGx/GhnvqdP7eyEe3Hxlsw+xPfDtDNeg6+U42wT/y0FTHzoynf0HYv3sdFgmbRUIE57mBibMmQ/v5nEQ/kaU83ufqRZqF119zCPBwMzsRbCKwqGA1RdkR2sVcqM1XXHscdnY1k9D41O4hdIngYG8w0q1uBfYq/7hn7E8G+LckvNd8vJDGU+IBEH5lhl4SwcSU9uBGZMrQl/IN9eRfOnR51X02dyOb+EF58mshKhMAQI9DAOJLYXJNQ+5D5sleuXGpDjTrZo3I6R4xW/qnkqeHp4b7CS6iv7QNi/JMECkS1SIduRdMEKUY3h2ictPoZDLlovx9CzerLa4i3MClJpfbs51kpid7Okw+r+EZW+icLBDo5G78sxucs4LYWYm0budJVlOnhajjIMgp/IZoR5/XTM9M+o5WU0EeE9W7f8zQdnzqglVrW1PsS7xSCFU/32ZhrbpyMXPCN/TGk/e+rhm103Dd99ypiyBtkzik5vjGJKAQeZW4aIL+UDQD4jbx4yV/57KCz2XWA2PCq+dQFXMaTAQK107sgt5JtAvsHZUw7rkw8nuHbL9/IqVXdpqJ7uI0tIZFrwJN696P2PJojYaa5IhZz861ZYjn/dJhDK0ScLr9/0BJ9Cr8O+93k9qEnMTo9dhUbHnn1otk2fnRlR0r/XSyX29vXYX93Jt6Z85i7uJmsZc7lqXMbNcSI7r4rfYv39a7/OzPtYbyE/cwv/Yu9dmn7mVzQpljo+96Q3pPcU7qDhhf/PsPFZS3UQ+aVmQoFw8ahkZ9O2PejdUPG2cxGkJ9VFsNXXyO7nKMGBUKXkmeESOlVd80w5aPqlRwdiUj2C4H1n+jSumq0tSu7bslEUwCbT6ejymTJTpZdqykh7UOrmUVKSSEqf9VKyaSwvYf7kaaSYZDw+Ocs4uriJDqvmm5bH5IZmw1HVLmNRUu33UFbXP75TOOzgScp8f/YK8+F5YkC1KGI5XG9L/Q75awPpSK6fx3QyrvF+PrLtNI3LPovCaEj6JYMA3oqEv36ydlcMy3h9nncTARTo2UL95uaV0egraLSeOfr2s+twIFg+7xrQvm/DRyxECri9z/S9ZCCzW35PkcZ4ruDBjzRbGooPJYmJ9JTJksZ+FqMUICrp1MGoaP7lCURes7I6iX2WGwznhPZwJN3mFpgyesjf3PdriTxqpnB3g0h3sjPp1aFzadk3u4AMs9M7Gi/mdwr8lOn/XzKH27c441aO+PrH+dfLUVlUEv990DY/AdlWmFynrMZAU7KRDjcV8giEI+081i9JFsIyrW+zOPT2BSvi03g/ignG+E7UZAvpj/YOkPpbFwdZ2a8JK/fvC99nPk43pT/oq5fMy1VoZAcVnn/V1OvgBwMsWybc0jx3YXp+41AY/b8GipTbM8pWf+OLDFeQv8ck6o9+xpK6hNLSu8yu6WfCoZLu/r6M7KcoWm77db3uDsfXaZl7o0J61L3iYxiznussCs3sxY27CxWg3cHJFX9JJvqt56fktDBGk9f1OS1iyGsIqWWp9J8vp8vjtuLYNg9BPKi+zM79bFJHQxMnZQUqFfF6C8c+9Adn9wKO33++mvuaHahBtOpfdxWr4+Fer7naZROyP2zjGotr0MKE8n/YD2MfXLLfdUAPrqRA1PlRStZjcNUawD4OP4vj566+YZeEiqbWxAWEW3tmSmKQoU3JO8G6iwLidZGxBRwpJLVhD0DFA+A7Aqew5HhxI3xc7wz1bLDrAsU5bOT8JUalJ4w2ddnLA57BxXk5CR2zrZIDu3tGdltjimpjELABE8Dy/2txWoaL0WA4KU1O6ug9plFG9x6DjvTJWWqyJYti+PoROIB7Qr084SuoJ8LwGPtEs+aWn7HpqFF5X0Va3Fz4vl6gjo9H1Ok5k6NXLLnWpESbCNvTOJoM7V5LHVIvS1slGe3ATrBGqlbGsOtqnOPzUU6hXaqyiqOltJTJFY2SXNiuSKRy4v02R74YgjYgyHhU1FBXa3NdeHWfBZo3m0r7IV/mq9qzTPqX5e26xJKOhBDKurWt2U0140t++p2ynBt4ofF0GKOtUXvZ9DWRi9aWR8scFdPhkDMK/0WZVNrAps6Yyde5cYB5yKHr0hOh8i7cL1auTnCKdKWA1DCQMyYxg+4MM9Mf02qxqM5jColGykeh9l3TZKyBgfKMTZjkUXJWGfpa5mTICZrqHD1Vm42nzJrZv9s4IWVlYejLSsiJvBFrUbW08HDl0YIp6pxt+vmg7MuSDi2nOqpNIv2GjvHWk2sRTJ8r08MkrZav9kTPf1/Vf96hugAk2UdxunfdGCvGjpuTrLiYj2y1f8bMxN2kPRU6C9GMZkumReyQ2juK/U873ajjEnk+nhrfm6Y/icJ7vyjbhAc0rYLKdCzuVddVTpkd/j1IK2xjUOBKT/Xin87IGCS7GajchV6SEwww7eL7AdYVa9jWn78k17fT6F9fGM71piWYjyMqx33LunXvrQqaVQWx6rQJhfXpLZnFTlBhXzmmabodarmnbbrP2TLAwV+KvB2VP87XUhb7HFPnKW6AOfhpuWubLsaKOhNmkplr6Ybbwoh0ut/ItN1eNoUfJv0x878I2R3D/0UUlZFnEA7arSha5ZmaSdDwNrvtHrcnWEIqRuYE8CEbi/jlmf5l5USI6Mv16aBClFlNbXBo9wkuj2J6Dl246EkvgPKk09CeDbfdciCLEINOKV9yruvcpLRvAHJ/8rcdFrz1UIRgsmLMVqBiK1NculiX8sHz18yRKaLITTqy0FSvjF/W2Uk55JsY3v1CIAEx3W0//IHh4yV9EeVnLaohwMROSQOz6GvRHJXSK5r8BkVNeARJzFkxKsquqdAg0lsCnBO3sipzqVvYWSILc/Grz9h/r0c27avvEQfaZGipKM1dOYTq8lite+ODGF4IhF8OCtD5baBk1Se4iP3L0kF8rEpZjDsi7Qk/VAsQobwejbkxmX2v45i1GtUiUslc3Yc/IZRJl0SwOJQnk37n46cddUJm8f1SqSFVgz748fZzjYQq54WTQLqmgljdyhOZKF/m9yYT0Xojtk/nilSn6mRY9DhCXKLE/AU6jO2QYM0z8LjP1XM8VHvXuBLFf+GRfNWfejXTU/DDwOOZ5YITjefL8d6qrAH8TVY/b2sWfvDqqsZxP8BEp5IDkb6hWpg1E1OpFB2E/utLuydcav9+muqNL2Bg6yLDi2FxOqovLWR0Y/Q1oHF5ogTknnah1nDkxlussusS56Y0rjvrtxi+9gfZyoxi9fjX1TmX99dciRfs8oZ3MzbKVufp9EkUWmS0l3GnjFzASF5NrWkJLi5X7KjcyqtqAc/6Ze1HZ0FCgYdfr+3rGnPDzCLQPUpaMa+RWwB2RHF2ijgoWUkDs1iJ+aaRCpIjBz73fdWMtWczRuS3+/r2dn6R+2rWEiqrr6mhtTwaCnoxUVP5aR2p7sC7GR2/DEi5vSVI6yL9Q227JcbPHXNQ4LPvunyKdKdEMU3CTgt78hRi0l/YcK8e4utrVZ9U5Ugmx5+CjWKqoHOYvjYu3ramWN2+zWsA6iWvzYJ3I4Rn5gUeObpJo/cDJZEx/DJ0i86ZgUzDrH39hBbu2X2m0IsQShWE4vSSfHLWpgHnY3Qa5OBXHd7Q8H/w+57gk+vcbmUsmXYxAtN2/GYKxP8XJHHIElN6V3km1UdqWR0WDHGilxeYhBEmG6UTQfoOtXvdJ+IHVReneC3rP1tmORI4CYZlqicI/Grj2ZhVKaJ+fCKFkC+BX/8lihothyYT9+fs0sNmXU4XyhWXyBc0bGlyFdpQpsJPkofm4tClzoc28DRGmPWSbxyuj1Ez+eaIT3BELl+id1gVjQ3UsrGmT8cJGuU01TY6TRF2ijMDe0AVgF1skFFwNukFobkLvLmMlkixR3CM/8Nyq0fJALil0Lrk3wqhe9nhp5/Bs9tEf+Znmoftviz7SxIPyl/NDpa3Nsg05B9KVrWvK4jQGyvmEHGtsGcJg7+V4+5d1TkLn9vs7snCSS9Sgs7BRufShDOoagX3tlBLv311FyClPuXHs5qtd7gQ6ObSxLQRCVvYzm/yb6BYerIua+tyLf1V3Roq4PQKT+f/uJ4rW1JpbFVi99/dxDhduMTmNiJHyHAY/YYcde0sJsJcKnQbLX8qui6aSKQNVpc9pKzB/kyqtBTKJOLOkFCi6aItfmEgu5tMqC8x1uqW3CC818kt5CMRxgwuyo1esByxfCzG/eo8+JvnG+n12+9Je/3XcL3q3O+TfchGMMHJhUu0rcRSBhjaC3b7EjRjpvvR6lztu40OjJdmwLphRY/eMf9gXxyH9JdxC3jo5DCJIbBrV9uHURN+z5/6tfoHpJVbyTs6GT8/OkObWwqO4a3l+VQ87OBdzCWPh1JZ/RIBWE3bjf3aCyCjunWwPxyo1Ho/MprMhtPzPpLL3ux1liZKh2GBMoWW8GxrTM/5dlsaahgnrSGFJ1i0oao1fNvhkfJmJidbjaXSZtLabRSot/fK3U8VAw1ObvFtZ/I3+CMGYIc2f68y1klX98NG0bXMFy2imEfyaAipd1jlRaeFTx/Sk1jdTYfJRxt6hVc4cPtkWS1kqHurLvzD5u5LZFhLRQoNJx9BwASWTbJqhmGK+zfKlUpqU3pnI4eRbdfHRddT4fyJTi4IhW+6jdSC+ZVoEBGGis7ntVoUbBRZdPpfxccvL89c32UouoZ1qsNkfFRnOvJKkfdEa0Fi8z+ttHGpNF3LOMxk112K91bBf9lrh3mHS/Is8FbKt7YYqbNQTLoEFakN5KyUKr7b/lBYkcMNH4JtmYuvfi8Kawtnd49C2DRG1mhSb0JB6Rze69LR83fhZx8s1Jn2KHWpRdAoztfIsL6FkL5douN+xfbRNZSuD37n6L3PLqOnQHjZFFxf299ASJadFKrct4dNU2Wtv5CaiqV3T307W57sPbFz0vuai2hl7Px9SiyiX5/guEZ03Bjq1CHq6Xu6Txq2QaG3lWyilrN/xupjz2fC+FkLqEDYdkUqOWQkoyhfzfPhD/L10N6SoiY0avGF5r4U12Oknc6hysfSGTyuhXAVTxyZKpNkdfjv0yjaMmA7B7Eal2uhyqY87OE689BqhxPxNrnR3c5RjG92v2AHoDbKkryyRbOXplXa+LBGY072aOU3qXuiJ4o2VH4XEdWsDMDBPBggpuikEfZpuZgpRFKktWGM/IMfPbu6MbyfNc33CUHLr2crhG2+sa5GydXy3yPQfxzor92sj5glvlajRjgJIC3YbhWVMKSLv/xl/DDhGjCI9Gs5rJ+5RWRXGNWORN7Dehr5T4C90GP3ccONUcTzustQnt1UQlMnnZs9nQMklcegnx5BTqmA/uaZm05rgblP/PuWR8RaGdAM7fmq7Xx5+b7agW8G+zvtTtZln2leQkt3s5B6PrV2s7Z7WSYvJfgs9Oh1TzjQu8IQXdWYWK2NO67aFInTdCbSwQiwuuZr1t9HKDxbR4IluHnn10Q1LFVn2iYjxv1VByedJnUPktwQeqYhpF6CWX9pkxed0vZzkuSFHsbDVkoEWI3zJFBCMsFn1rK/vSnG+gotYJL8+JJ3oAd+lS0ZxmbavGjOKlEiFDTHiLhYGnuIkiDe+FIxGlJSSpOlqXnFSi+g0RBEOdyTchEVX7Wi/GObmMXhLUKPGxzS98CzpNIZBNVsooYrJduh+P4CbFuUw7eLkNoTBeMqJJnATP7FKK8zjPexCQrGXd3c3zGk+jtBnLKa2+xPjGIEkWKo+QzHLllk1WryQQ5Iu5jx7oVVUs20NXdUCXzdysLxSjzt0a6dlAL1V6c5MgsxAH0VRWeAWkOrRE+9Yk/oLK4S7spvVKM2Ww2xJH92HqlpIr3DWlpb5HQpfPWCOx6CZ+xKpXOG4o+haciTLtK6jrHwroO7lPLWpZlCqGMehWM3ZFYkoKHiTIk7Lcp64Rz0xSK1XNpL7nNDcKjOk7C0UagK0+v2ij27hcpeU3XKrY+yYZK2Rx+IbrwW6gIfVLv2Lk3PmU0IaihVVYo62nAxCFpSrjcy4kXLPzBKXccSBpVOm6ryN9srsNd0TKlpbd2inKONUuGbUz6wgzwyeLYH6uDTGhRfFlV9epB4Y5vHD9HoWU/MZBLy+LEcs5Eoi9sxKJOWDryinEr2tPOQwtZ7sn9GG86/OMxBkDt9EiX4USnVAcdEHA2Z0kt99Wndm6miGavotp3oy4CVgSt0dHmPdC30RQjVKUVyJGqBjpF558PsZeJ9dHbeWMWvX7Ez9ILLYs828xQoT6FmjLOuQs9DUt4j5OPhCFM2nDlc7TPbaKyg=
*/