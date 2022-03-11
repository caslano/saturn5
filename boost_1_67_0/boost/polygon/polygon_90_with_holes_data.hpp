/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_WITH_HOLES_DATA_HPP
#define BOOST_POLYGON_POLYGON_90_WITH_HOLES_DATA_HPP
namespace boost { namespace polygon{
#include "isotropy.hpp"
#include "polygon_90_data.hpp"
struct polygon_90_with_holes_concept;
template <typename T>
class polygon_90_with_holes_data {
public:
  typedef polygon_90_with_holes_concept geometry_type;
  typedef T coordinate_type;
  typedef typename polygon_90_data<T>::iterator_type iterator_type;
  typedef typename polygon_90_data<T>::compact_iterator_type compact_iterator_type;
  typedef typename std::list<polygon_90_data<coordinate_type> >::const_iterator iterator_holes_type;
  typedef polygon_90_data<coordinate_type> hole_type;
  typedef typename coordinate_traits<T>::area_type area_type;
  typedef point_data<T> point_type;

  // default constructor of point does not initialize x and y
  inline polygon_90_with_holes_data() : self_(), holes_() {} //do nothing default constructor

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set(iT input_begin, iT input_end) {
    self_.set(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set_compact(iT input_begin, iT input_end) {
    self_.set_compact(input_begin, input_end);
    return *this;
  }

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_with_holes_data& set_holes(iT input_begin, iT input_end) {
    holes_.clear();  //just in case there was some old data there
    for( ; input_begin != input_end; ++ input_begin) {
       holes_.push_back(hole_type());
       holes_.back().set_compact((*input_begin).begin_compact(), (*input_begin).end_compact());
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_90_with_holes_data(const polygon_90_with_holes_data& that) : self_(that.self_),
                                                                  holes_(that.holes_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_90_with_holes_data& operator=(const polygon_90_with_holes_data& that) {
    self_ = that.self_;
    holes_ = that.holes_;
    return *this;
  }

  template <typename T2>
  inline polygon_90_with_holes_data& operator=(const T2& rvalue);

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const iterator_type begin() const {
    return self_.begin();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const iterator_type end() const {
    return self_.end();
  }

  // get begin iterator, returns a pointer to a const coordinate_type
  inline const compact_iterator_type begin_compact() const {
    return self_.begin_compact();
  }

  // get end iterator, returns a pointer to a const coordinate_type
  inline const compact_iterator_type end_compact() const {
    return self_.end_compact();
  }

  inline std::size_t size() const {
    return self_.size();
  }

  // get begin iterator, returns a pointer to a const polygon
  inline const iterator_holes_type begin_holes() const {
    return holes_.begin();
  }

  // get end iterator, returns a pointer to a const polygon
  inline const iterator_holes_type end_holes() const {
    return holes_.end();
  }

  inline std::size_t size_holes() const {
    return holes_.size();
  }

private:
  polygon_90_data<coordinate_type> self_;
  std::list<hole_type> holes_;
};
}
}
#endif

/* polygon_90_with_holes_data.hpp
c9ilPE6YwdhHEiiTcBqvMSJSjrNOPGo0UUAb3a38vqtK7gGL5DSbZPYlG3F2FXL6E+78W9Y4I6zCepG/9Kh04dLnD4Bg7ACneJgPYS4+ABAj1vFFT3YYa/wultRiKv1jeKekfTNkqQY7SgoeBGudQlsWfpalzfMFto5+KvT8vllZrI/QTfU44WvLkd36i7s/YfHO0DCrQdO54coenCL+YdJrHnMPa62SwTCskxFILv07cGIZAXsOWZPlo1Uwj7rmtTfW5ykhYImcbxDnRwM6GuDScmxg69im0SDAuYZJHh6p3aWSpQxmCl9Ih4dpjCc17ETd27pGlcNutH2SNfTmf4KO9yYcbBy+Cu+g09MU1v0BWaCSA40K4EuiRyIhx/jVhOv45/wf3DGjogXTdlP/MkjQTC2UdM0EdU82QEBdBN35qOWuh1QDdleYXbif1JqllrwTAdWh9/Oz0ERCgN+vtcpH43bxs8CaSt2NtanKxbGTEVRorpfAF3aehIv1K/Q1Ogba0KqW4MIzX14uI9FHYDKR5lC1EOlylWXhEW2XF0s9CuSUTjRFILtfGbRe/FT47jkym05bjnoU5SgfcsQwiKyHbEKZREOi5UM8u4dcuA2c8olqzLrOiEQMpe0/ij/PDo91MECopw+4Zv/JGyKRjasTHPuKD/t00skMr42S21wNzshXmPoOlaRch5oEaKwgibOEZ1zYzG99DrKMstruTHHkB36YXM8fc9x9p1cSPwy1Vj+4jXVDz0k2sSnZxm/Wrsl7qsiStIFUNCQa2GVdlrvdy4M7P71BumqO9scmaMzEOjnfcPjInWk0HINY5bdmfy2O8xSk4rHMsi4vlnTAT9ofMbLAdTy44Ms0qFngOoNvnNmStN8AMCjkJsSYLU68dGWvta1JRhaHlO3Fj4lhOgln6YjEZj05+kWoOhVPUyfsUWuOrwiu6TdxNBqFrW+hUSWq83/5a4ihsGjTZhXbo1gtO6ZFx9UuJZk0z9XICng2ZbZG9n5HHaWMXsfLdzTgZtCOecYC8zNb3gzmcyQ+z2WVg7Buzqd4ojdLat9N3IAlRvP2MAZirYeHF0enUKUgDKZWd2cqtvCNLjb8FwWT3RByCj+/3EBXvVWePVlunq+671m1cleBYumG1g0I8Gqe47KMS8p5ozc8qLOdOR0vwr89xNxTaVO7ATSd2aGu9wG3GPaDV1d/HtmprWuzOlr1X9NcBswxYPkONFvK6/GyEejkA16tik2eTj29JOm/WrJ/7EIddVkjNdmBhkMl+QvdxSoQvkHihAcLncGcSduaHUgBeM2jOJoXE3QXCW9dCPJDcMSUUMhbol34QBHGmKx6wjupyu1WEGiMoctKEirHSCJDkLEqTVE97FIH1X7RGtdUzpxuCAYttksRFfoBNayNnTUJFivbcpaV4QmcX8L4Ea7Zw+fN9s7gqhlhNUmD0ZhUNKt+0Tm3xWxZkYM4/7ZfTaZIAQmZqSkl8KrmVFksyGQArj4+eyrm7408uDmYcqT+JUZSN3tDI4tgDs/rJsHKumzYG+ergIwGPOYDMK3m5gG+XPTu3TNIakJTUf080L+4VsBHDsCXuIhFRqSKLpRYUtZimbM0kaHpI1TRdoEUmt7q3d+GeDD1leKShDjIUl4HW/af8T5hOJr/axLlPmnL1rmf0xxP8RRnrUkvY6k5lLqY4v7niNNVYa//pn4ItK3SMmq3/+ZVJbsJclOiZD1AbWInp7ZbtxNi6NglxFBrhHEhbAOK6FN3QyNgk+Rhn60S1z1cERVPNzwq5swjdE9EuhTU4WH2arS1R41sviGYw5sN3AFta3loJBRi5gyN/uu/UyAi5ZM5ZBV4eCFWSR/YQhTunHDtgb2JIpxx3/b4ZgZ7EoBwmaggWHVgZT3rXP3uGcBMsVZyhh1gdaJC+x9CVkzPb0IlyO5817oG8o6ZZ63l9GEOlfigv8i7Z2Bhub9CI+C/OJUqXE+f0IQY3qJ8eGq27GV6yoOxw59BhvW0Xj2sHh/XLrsykz4knIlMkj42HbuAK/RoYsgfodolhkXzZztBoBkvmo/kGOKfTKFOeTnVGnjpW71YjfSn8M1FAEPlFUU0yeXvFmF4eK470HbhTasrSLp+/KjIOWyvc3vCnbNVDg/NMunbH+q55HYgteQRjMDoRtjF6aStwH9NPPH79jnRTBU2KGgURiMvjsv/8mCfXIOSd6ZVm7Vs10suMxNp6NVp2BXuPdhCWcaPlfuVM2LPFFqkK4x98A/aVySHHWaDhEIpW8c0W8EzYz4+hAmENNPVCXAu+vL1tvFgpK0kx24lDry2HsOiId+7x7Niq6WqxMfwxfa/DMfZF6THXGGOvxSfNNwM3zW2I8vt3Jvx35RfkUo32b+hSuEdPaBLNzm6kxdH2bujF3GzdmbOZWTYFDtuTO+ciy5tLy3OUMA8f+3M5SwoWCvylbvYtyKbQZWIy2GlzZRlXFqWIzkXd7hrLVlf6IlgufRhKnpnrNr10dw60GMCkWcRJ4r9Ej5Q4JJw0N7avoXgAIcDXSIpvVe1BQTF3sQXt09iWQ80pB0uhwhbyG7B6Z9Gfwnfud4YdEvVRQGabY3why2IPzutcDBiJFspfl/u6f8Vd7oLgws3kNky6Qb3OV4nMjYTNOHaDNxBJKcZWX2DhlN2zmeRplmMwVThjOUG58y2Z0rrS+58Pp4P+FxyPOJNSAAjzPKOD8DOcDqwnnlYPnzJli1dAr5g4aBQ28QhbqVUiixbzDM1myUnjSyPePwkA9bZssWKhOFny+PgZKiGtkY098Hcoh3d2Ww9LWTao2mvWxfWguJMhzLMlVec17lzXPL8DAW0sS1L4FubvZ8mo1S7qP+87+2aEatQe2BgL0foxDNFipR599vbSwUttKs0iVGryyGIz0ecWJJKRqgzX90jmTSg4uBkKa3XM9dOM8zIIqhhomEZ0AS0ZHbEMx9Yq+F4DztsdOdPWQeXInnzAImFiVB9Ztno+ChwGh43pt8mfBFu5rAdLjSmm7gVTasgKwuK+iDyBdGkI/Jdmet4UuWvwzBHunEdePUXT+/4v53eVklbtRDmr/8ERM6y1hNVhsXyp00VTrgZKNSUabzHBxbFXKEYfFZL8Xr2zcw5yAJyLX5XBR83gqiMhi6XaQ9nxR+5D0WkI6CGX/vrYU+14RwmnsZuAflUTIgfR5oYAD5aZAmQJ7uOJYIvtiNzHwUoBqi/s9Qi02s3WREWnfqxOOn5uEfhakz1iCBLf4UbIudEQ+AL8Xdyc3ON+WkJjVXx9IOL42iF5qsZuJg4PliDBNWyDeyIVrMne5LdykOGOgNYWsiz+4y4AvFU38C11Prjmmz1lAg1XQuZNR9vZAyuDcNRHOeHNtDke/ffbYXzMoLkykCelZQQOI0oCsJz7GfY83D9V4Amc/1PFpczKjbM9UX8OsSXdcJPmIFKrBI/hMPZbBK3nRbWFIFwanA9V9NIqXqP/czvvmYg3k6/fnE7wt7PP5F33KxUstI3+7GI63wHUpgSre2GtAqKZ2f0dXVC4n4j0IvxBCHWKznbu7HWd5l2qABcrf7URhvxaYP6RSv1bHab8GYLL/rT8faA7KctSfnG8/3g6wmkPL6hVDVpV3g8Qmf6sE/xXvqKb1sVL8yVl/s/qhPZo4RSQRaelAAKLPXTphCdgNubaL9P5OHvD/1/Tlq2PJU+A/91RvnGM9BlJaCD6n9+dEN+B8bU/vyLurvBEb4toxBK5ug+qIasIq8rENiAlQgh9Kyz5bfb3DAnkhM34HUmZhCO8lw0cOeItNvX2aLVuYVuq6Cp3M8wlAJ/wdVBu99nubsPVTjAXp87FVulCtM8xu27Drh5vfryltg37tqsYo4Bf9PbK2MHiOW+yZGTTLDvObg5dlJqQbGvyHSLjMf8bzlCBidVea9NCkY6BepGg3p+vPBAC8nmtN4RJC999dyYvqn4A8VJkQupLgycra6m858eOLLHoJ6qeG0VA+4cmYH+j6wzzyuBjXzY0IRf+moKDdtW86+PpBIbmhEIoEYaIpIs/Ty0tQeaoNtFvzpvdfKP1EoqVxNXpV0BrZbrGHB5CHK/PcSq+sb0XGpFsI7AmUorcdoGf4PLEOEO3cXq8sQxNGEuDmJjZ3iLrzS1Bpw1kjUtVOrA76dlvQ+FJCSDS52Rj5LWfcY5VJH7QmmhFiN5bfvtcTLHMmZMk+nLDHHIe426wR5cG3d0PIFLBY4PSSbve6JubuoPC9OaZaVu1Pu0O67J1z/ficfQahN74wEB6Q7ZDRKExzEZhj2KcAqLLVmFpKHUkJSNeFjyN8FSpl7D52SL4H8J+6jGm0g4JBzE4wj+Yiv28E/oKH73Rad3JeiMbbOwuXH2tWI6jDaZTwHMzFVPZqfF4uGLd6X/nbEgojyUcwbi+8spHwWxftXZibNaXzELWMiHnK154Mlji73Rpxer21uNsGZZyPtrZM4I5DZG9UFCfGlZkoNgPwKH6/3DmeKWkvAsMdatRIUNeTFy/QWDnSin7MF4hYB0kAUgL5NMdZvy+9ffBGZHCMFUotJUhvo5/a8LLaHUVBwRcLRVVkzVbHoDeQF1g26tubE2b9BCpFPDXqr6jGE+xvr0dEcKQE24z5d9VAhiQ+WVP5M0ci07SVdthd8Xs19we1rN75vjRpvDk4jNnLRxbXe2vtZ+WvKSBBHrsKYQnZ0KGFolrCuC1djMVx4wtS2gFsFxwsPaeN5dQ11XRj222lunnI1JhjpSgbW7xDTprD75eToQy5I8xm89OoaeAeyk6j/n4kihOFesHsGosVxJcznN/EWbgkdfb9u43ICqSG0m/Yv3Cv8XSRGtEVwlQkbUCdjjfY71ghfVvZH1nkmuyt44AUa3XqdcBPWC/bsfFP0jJb22Qqiaa2XZ1LF0sBW/lw8Q3wLrTJFrOO1aW3kz906aCV5pxPhflFHTgCzoD7Roae6IWfkfTve3LN2zKtzy6XEYNWvr4o0sdd56SyytnkZ5xkmInft6/Vwvkn0zlqXE+E+8fX2dcqH2Ht8Qf0FhLY31/7xfffjrK5v7ZmQZ2ietGSNAq0GZZWOjZDfnEzwDzNiSsH8xYT6agWFNAyoZ5jbd8gayybv9S7egVfI2jnS3gb2gWVEzlaDk4TbYEB/svolciDGa+54aZ1XmM09v1HkyWMPHwr4idpZZrwpveKnrIU2TTPfiqqtMGdHx5+90rsU0zU2GKFuQYtftClZMOtkSwRTLTWiUul/SxKqm7SyM4Zy2V25WZ46FlxVMjzxuXGQEWzNLsEzUR5qDE2HrkuDtGGEDKCPOqEOnsQnAP+U1OHgdgNmcHA/epkMUvD8mgKqlYTZFvFYwj70vD2AOfWSzqBk2mbKYcpPplJrXG8sOpo8ZkR9+1h2iTUxB/utje9MqrR6qSWEnHqwad8PITyHZWc6sDk8lsJvNVqaz6aSsIGdl0pcjRqZbFSsbpdwWns5J1uN+eSr95uQbmKxucfPyHVU2bVqPIeJdIIzwDG2Bb13SqBfqlHgWNldo0LvpSYb1Lrh6XKWyFoQ8hCBqMNtfqNWf1UBLTZBo8mU79nIw9b1CGOGJO72BLglwNFFFf4zYvzRpMZyTdi/fL69yULjjHfDKvdEuWo4ZJdUQSRqq3HQvzS6mtTNjvZYRmwXjJztGXQ9UHQhg04ByrXwyoa5+AwFazACUrM522fwOCVS+dXNBINtyzYhEu0jnfnvol+VeVG8G8xFbH7mU3+rhL508hZ2dRpv0kXnbxH630AmGrmceJU45EV72jnru+vmEM0iFwskIqGvo6nX2myJFkobEsZPwAmVuTCij8b4DyHA88sXbKo4OK5rbvdYIz/6vwiMmXWiaB/hqUtNctpLPhJH7lYxdfV9IFkDDR8TTroSkNoT2xAjYKsDwAQWdFcDF0RU1MU9mSPtAir1rsIY/6XYJRFj5So0nSocyVsFCGQnKO5IiG2a5W10RLvCpd+gbomHb7j+ScB+gEj4CR0V1b+KYmn0sKLQe/yeF86SQ7XkcIv/lLunlHv66MkNz2O0hNtUJ7MbgA/xJsHYxmV6ccr7+op+r4s4qjivELjSeOVGyO5cAHrvBN7hWIEdj+thdhEvjBls78v1/o1txUgpXmqxjryYjpDKAllnCGjwBe6xvtlsmkIGvkCUy1XaUQh98L+/EQtFGBYb4JmXbgtQ5pGTfvc5PqfDkdj3o4hDotsmpV4kARNdyB6AVGM46q9HaCo/sgYUC5zzZTYnxWabE7b30TAkEYyccIpulF+ciKkkvLDmGxx9uq9+pLtu+8qu/5Hp03bME8+3kRKsM8T9UBusWrYjBRD3LFgoBec1xYY/iPRRr5D3p+KP3AZF0GOXtW8hRcxbTPvX3pafqfR1d5FZ3SuFdKWJc4MG77BKug/09LnoWoDOQEPW3g4fW8UpFknE6+qsVuAtqCwTqIAGfj2gIRLH1WDKRUr//baCXpUyZutBqVFo9eWnweJmauyoUJvFCJ3RswEkM5lilf7NqyCTSUg8uRbAmfP3kUVqb3cGSYWRD/nBvfzYHAFXj4qdpvFKm8Uife2J3ZRnYmol0jc4sU5s3P/xWRVmZkRJdcjR/EHr0TQ7gFCtyIVAyXSw7Db8NfWXkKP9jDvjkoz5kh+7Z81DdlpoVRTSVkYaHdB504C4lYvUbwKtDzPmues5vCteF20tAmB/GbvGK73v0ViDNFyhzv3fOdh4frpfkugnd3Ru4HzqmprWQxrb3eGUk6HxdLHEtZwWovSOU+8pwaT5J01gkDINdWeaCYZCtDB2ezsAiL/aZyFxnLMjZ9uLd30kOY36v7l/OCFzVeL6SULsp6hL0tJvIc56pXcfvignhCQveoimxXXb2omLv6AmOkzQXQBjXnojtKD3fownMTW8rHeJO0di2jj8E6/1od3OjInkZzLs830JAfIELrGtF1v8vJwNHaiJfgzWzc9ptZsy2elosKa33NS7r5mtFOQCkvRcbmfecyLZd5PA77dSQefy8vqOVx6ju9AbOrHtwxK9E5MYEFxL7da5Lo9NpJjc2+wUcLApOg8hRUVNR6BoXis6ARjrNcb5BuWJCwqBdp2MnraQ2rSj2PPglDNyTsYCXbKrRtnENytVWopO3BD7YDHmFWNzgpdYp4yamKSQ9rIQDscJC1ZsYzvoQGTzXM+D5l3BrWNw/zT6EPyUtJQJOsKd+BE6c+z87UHEktSSC65fqJmqvR8m3NEGV9LY3o+Bs3y7Z7kiY6OmweXY0DD29q61uFVdwRu7Z/wQNxq0BQDGXvQlGt+M/Y9zu/QWQhAvoNU+QRgdbtPtEYbCWjxHeO+6ahg1wLgSebiUI2Ab3ehkpbet52o6QPjCJWRyh90Q+nLZ31Yqcnm4Zj+VC1kmsbeG4a8OXVU998TwzqXYH2h0c4Lo8EtvWk0f0/agR2QnUM7PNjcG7mYVPUDRSJurDKyjvSSfbwtofB6BDEV6f5pl4eHPexsEn0qu/4GKjUw7H9Iqy72292DMHDCqe5iWj4LnBB1lqVT2u9FHpNKLwR9vSpRpjP8l1U8LeHWSTdKGUwxupWgnzveGUz5BVGAs356I3Cd7vWQXFq9Zez8Zjn7miSvO4k5KTzu0KGEIxkp7f0W8FFallQGpZAaNGVs2BpVoMvUrZ3aNcQrpy+8wE0qWDk9fpuURjnde3ZBoXUJH7+FpBe2uu842ZiSo0y8OrIG8M3eIJ+1lfTjB6zDU17Qes9JvOlZt4RjTa3HoBJDKzRMZpiF6mtIy0cA3pFOgOImNG3okS/COlMNWwUz3tNnr+EmjQdqcEITHO8wX2lRBdBlTjF8Q6LhaR6H7S3rgsc9agOSy2WaOGlYdAjldvkV/B40pbkTv30xtJ+akWjPS+QwI+XvDX3Zmw75HJkRl4AJyBjQ3hCWHwz45YlNCZveCKRWgCS5g3hojVDGIPvhGiE6l3UMvSjqQ7tzBlwg8WuLthlKf5FF9e2wOKqVYSYQlRyTmqIWBsRKXMpUcAwj7IS8Dlv6AwOgjELMieWQKRgSWPzv3ME3tY4dcxdpP9Gj8382WbxdXa+Jr4kMW8nwgzwYPl2sdko2Nj5kUCQrwp6vShRfbowE4dHcloyFhCf622BJBTosOgIlnCojAsOONV2vic7nZdVcfeGjBNZ+xPVH3d4pJXn4vt0aXWpdrRIW/M7BunNhLNJFtu+MJlVpcT31TiJ0+uyG5Ql4QQzaTe/3oIf7jLc5eJmlAPiYWaxJ/yL4/cJ3X9k/FKXTJ1vWSqg3ZOHv8zaDzzPFmn7pfh6IdKzqGhlk6AObZGf8SouUNmF4gWogcAheIeYKOUsSODy5AlwmjyP7w5bkVzG+i7cDZjMr1Mtd7uUlUO1R1dPTK3tpk0Wd7GXHRlSaI/5Gc28+0JzD3Q4Fx5XQPy/EH95ZJnVFrUF7ekKOwmOMFysyVVUaDpPG4YJCnXMcW0iIsjzgmhlNh3O/gX5pxpa+Va3R8xaeMszoCQLecKIMQq1ruEsGVFMMg4hdPPh/gPsKVacl3FHEWri4F9a61EUQTbJg32taqJHnoj9ToZEu8E/JC+2vum38GXKO70lrDoGcAc2r8pOKpp80jBqQGfDOs8f/qgf9agYeNg4hcYAOD3N6sb1itx+Zk9h9kcmyAOAJRLoFoNV0OJuWzIT4UQVDeAMhgkqMWmxzl9Uy43FN0aigX27gqpCg4Rl2lrqX48S6aPEzFSRKNIcFhmcmN6xtnBsgKs2tpv4jvX8SYxteDzp2e3Nzf2uP32Ncfzxr2XLTKpPj9vOU8trbO0bxsRd3ZLG/Rmx0yGiE1l7ybKhJGN3m403bTvHu/X3Txlv28TDRj5UV22zPSikQc9pplrZ34LeMqa8p5rYx2Sdq2gPTO7WEVzWqqwf8+RhYJYoit+8+E9ilwGEi1Sxi5lI1mK1dJgachEemHLugaMJbHX0bxXLxitpEXA8qTF4mYlrHO0MvnFrJixukmVOjqSUbpTdENbd9OC9x8GzLxUGTTwzegNTU1t8raVMDP2z3b/Sdo6EPQ/8xxWF7klulD1oMtlwhl1E81p6DmmhwuTt8py6Xi90ce73Mom9fTgwHDGSNeYJiFtcsfWJ3Q0rBYsGAhiLoFCYH1i/aVAhoT2bABsXNH6yO3qqe0L9r2NToewRUPVSC1P6n8=
*/