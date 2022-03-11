//
// detail/call_stack.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CALL_STACK_HPP
#define BOOST_ASIO_DETAIL_CALL_STACK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/tss_ptr.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to determine whether or not the current thread is inside an
// invocation of io_context::run() for a specified io_context object.
template <typename Key, typename Value = unsigned char>
class call_stack
{
public:
  // Context class automatically pushes the key/value pair on to the stack.
  class context
    : private noncopyable
  {
  public:
    // Push the key on to the stack.
    explicit context(Key* k)
      : key_(k),
        next_(call_stack<Key, Value>::top_)
    {
      value_ = reinterpret_cast<unsigned char*>(this);
      call_stack<Key, Value>::top_ = this;
    }

    // Push the key/value pair on to the stack.
    context(Key* k, Value& v)
      : key_(k),
        value_(&v),
        next_(call_stack<Key, Value>::top_)
    {
      call_stack<Key, Value>::top_ = this;
    }

    // Pop the key/value pair from the stack.
    ~context()
    {
      call_stack<Key, Value>::top_ = next_;
    }

    // Find the next context with the same key.
    Value* next_by_key() const
    {
      context* elem = next_;
      while (elem)
      {
        if (elem->key_ == key_)
          return elem->value_;
        elem = elem->next_;
      }
      return 0;
    }

  private:
    friend class call_stack<Key, Value>;

    // The key associated with the context.
    Key* key_;

    // The value associated with the context.
    Value* value_;

    // The next element in the stack.
    context* next_;
  };

  friend class context;

  // Determine whether the specified owner is on the stack. Returns address of
  // key if present, 0 otherwise.
  static Value* contains(Key* k)
  {
    context* elem = top_;
    while (elem)
    {
      if (elem->key_ == k)
        return elem->value_;
      elem = elem->next_;
    }
    return 0;
  }

  // Obtain the value at the top of the stack.
  static Value* top()
  {
    context* elem = top_;
    return elem ? elem->value_ : 0;
  }

private:
  // The top of the stack of calls for the current thread.
  static tss_ptr<context> top_;
};

template <typename Key, typename Value>
tss_ptr<typename call_stack<Key, Value>::context>
call_stack<Key, Value>::top_;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CALL_STACK_HPP

/* call_stack.hpp
PUXF+38CMgq/iI28OQvMbt4wjIpVh1BiolPm05js97/hxdgWRVvWn7m5BGs/sCTg2QNhJe6vSoLo2ePdXM6XF3jAm4hA86e9/Uls+N9voV18mQdCwqM+Dn/CJB0awfFbNNzRQML4Z5Ut0PJk5Nx5f1qCowAlYyhz+VQRssWp+eAb/IfyYFjqu8Cle6r+2XeB8z+qegSlYCgJy/iQLW7Nh6zgf68Ov9LzhdnscOvSCvoSrkd9EkDsgau99Ib4U/G+Keg/FC3hesgWtOYDf0DIoQ893+FbBgPEaZC2x9Ryn3M3RvZ102VmzT+H/v54DaussW9EMPqp/w9x5VKLLv7iwbWCQPrKBET5ZzGcNtj3H0N6ONcxtO5raB2Tm/2OrMl/gsF4wSFKukzP/x3RGzpc15r/K0Ks/B66/31wXpOr/69olTHZYYgJ6WDD+D33DwT89Ac/etR5A5eJ1tG4DpeI1n+IwUGkOoFviuI8mQmxpoUF2S4jQ9jH/0VVtlSeuuh3otv7JdoIpyQlWOY227vMSLFdJVhOYvGKfMhIz6vWvRnTldzZCn5bim/MFvBdVPHSXyi2o7DM5UW7cJHij0qWnCKbLbg2/oV4r2NMeQhkzjZ/FffdiQb3Ydtdf48xXcAfLeV1SgYmRDe22F90/VFSdHvB22nigJ0tvxtl+7Cf0aeOar6K+4ewgmkzZw3eqiQsIRXGMrcT7fJnJR5tKWoKNuJMC7su8Ec9BBKvfMgK7BKiwSRvJ9iMMl/AnyzlfavmDdW096l8C2/irEFC9Euk6Y0GWUEPyVvpo6W0LskuVKT4/9XK6VDWE2TCfb+/1Pr07vukT5zspgTtRYoV2x7Icuh6NvqwANsuyryRXu+t9T35b4VMHtVYivuLvVUxXUnjiOpv3djl6p2DZLGALzD2/FWcJzHhbumcHvetxYlK7gCqfVJsK4eNTe80ljGfmolmUb1XsgDaRYhqRehWYaRtBPYA2oUv+u0+HxyJd0kG/ngEreKnCqFRDKmbBvvVDKc3xeofyMU59EOXL0RPC8q2F1vA6SxEtQR0KwHS38lDlznEchGkbhzsV36c3ltLiOWCfyA9DSjbYNaA02mIakHo1pcP/0zc7yCfpgQCtlbhLnkfIfwsCHsvzqAfsnz/zPbfgqk4/4fgP+R0Rtp2r34LsgdstcFe8i5DVDtDt04hbfNwBpz++o+JCXRr7BthDzj9BlGNCtUq/36bh/ififc7yF+k7wfmb407vsYRBSTUQlTTQrVWv99uJwk4jfx3pHCY/r97sUAIhgDagIQaCPHufyYRNxf229hMeIdC0TnvmKc+DbwgG/vD1fUEr2wJnV0Q3bl/fOQNf8b/Z7ch1STKdKmRPxxz9aeBVvGPezhC0TbvlAiDSlH+MP7uXUglGmIPwlp+H7qHZEFfxlBTSpXD3lW+9CJIzEy4HuwYSzTEHYR1+N44kzT8n8hVDNEQZxDW1ntjn38g4nM9nIG3xk8k4VeRREO0QVhx74353kg40RBpEJb/e+Mn4vCrMKIhwn9PQoiGMIOwDN7KfCPBhkbtfM0oe3BC0YTvmP0+DjwIffw7GXH9SLosFE35jtkJf6BV+OMeglA07VvDPtLRyNsJaFkh4kSXMDdD0It//O8Q/Y8h/L/DZEso2ncv7hxyyGDhSxwJockW6EgLUGCREJctJuCF8Qc5LDrtNzj5ggLt34nC9KL83gsLdGQEMCFjJCT1BGGNjg8nxMeREv+NJMSRkv4XkdQXEAcCHQGAvZHR4YTgHgQ4LNDu+7HhT8lxpFSEEooCsbk+eEIPNk6eb0dAAuMb/cU7Flfk30Ye/unKEIxWS3l+XwgtISXBZ/V42lFLqZecgFw8vu7zPFjmB3smYUuMTIRMMiWBJ4z352NkPJG/PUgWRXhM6CEE/Qfif31o/qcLLt4f4j8SCf4f/xNxSPrqA8iJe7pO8BcATku8gEYECf+9Myze//1/JBL8sf4TIVHb/X4J8yeYRNPg3WmUoe+nSsagW7E/nYP3EbuPole++Q8CSj45VN0KaCCJBP+/ipKzFsHAO5r/MxJSq3v+MgALj+Qz+v8CgX8BwX+ESjZBH8FGCfj/CxD8F3D+D2CFb2SMeHLpWvFrpIT//wYR74FRRD1/E4L/riIRkumE3YxrGe/+N4iubYr+bbiG4/0//CcCk+RVGGAQ/oSY4E8MZBTtDhlp+QjCINkSBuiE+yAmOBAD6f90vgdhEG+RAHS++fz9A5p/43QE4Er8l8CU8PtHgSoh4AhQifaJTFBgBlKLCww++A2u1AyOtGCBMEi3jAE60T5RCQ7M3RZ//ehGMPDp8wjjH4Iy0Oe/i4ckLeoumOgew7Q5nd4HVF1qfpg/XgGiBQfRZZaTwMdVH1/eafiVv34+0qCcqZHPNUDiMpyiK2O4UNFW01FSVwkedlfuMc3WCI+RJrSpnRv2+apD0F+uTuTrA9Vyb3J87jvQ+tD09cpmZ3e5b7AmJMoAEbMHI7Sfju+9+Y7xijThO5ltDn+oFhBq62RciWnVu2bSwB2uDwUwl1jKEHHE/0b1O0DymaONKISBLgXcvPCy8rh4RBxdQnePPgzOYkcWsKJJWFDFTinyMeopoDn+w5JGGucvgX/K4XiFMTyog5dVwMUj4egSu3uENzjLHVngjPaHF9PB0eX77hHd4KxWZEHDW7nUsVPKeFlFXDwy/zcCn18ocA0Bcf+aYG+XPjaqhYtHwdEle/eIb3DWM7LgGk3ikPoPL8Pm7pHs4GzaW0vRJSxoYqdU8bLKuHhUHF2Kd1s9ogpU0P9sUMWfCU3/aKCEBW3slDpeVhUXj46jS/Puke3g7OpbLdD/FvAAH7IzP6D3bWu8DzYg/uAXwqT5RtSonhvyW+kx+uzqPtpHhXzVoQMo+BtG57zf9kAp8scckSbURUTfk8Ac3JwmjLqajzS+KEH/48MqQROpPw68l2iYX9B/u580fuKC9mcv/Ph2zPQZmNI3+iewxzbu50EfG1A2X5ao0D0do44/t5V80QdL2AYgdKgOFOXnD7zkCSnpdRcWQvm3oZeE8mXWXApCjsq4whs+hRg8beFfWpjTPaVh93LF7e/wfQ8TRE9jcf0u2MUaQSEY8IZrSz7fz6jul3S/fjZ8hZtGKLzYWwjg9cD4va3VGmxh9LQqfbG9EzEP4SdG2JtUAsnnifOmAkVx3lKpyBMlxN4bd3IlxEoU+zvi7MVjSU0PS3oJiM+JeB4b9IqlDLl9q8UntpV4v/6pr4w62SDzN/2vKPgSfzra7RcP1d7nK6rcPs2xiwPRedUB38/3an3HhKsIrYJ46F/9uRBKfehcH7IrxD5pRH2tIc+8EMB09ZTYABccL3XYxRIU/1qSmK8SzEyy73oMVvpSpEPo5gzFgO5S5nJKaj+1Awy7nqtyBz3MNw3/ynRZR9zIdNkQs4/VaeHtfnpx2bhykQdT5kP9VhCFTKnuWpkcdS+LlykiT/rq/AsDTnd028+Ty4VrOCXaBv3paDNExN4Gyv4U2v7UEfBmywTbg7Z3+Gx9R/ZRXXQIXXTiHnd34tdDc9e9NHKeQW/VY29NP3z5qgrx1gjptibCpeB+36wc+y7vi8t1Ar8Cxfbb385hnoTVgsn2XesH/aordr5cG14aDn32p/1veCugPZmgjlgjte+4ucML1XGd4A1SCt1cniaFJLEJkVziNLtYZeH/b8g0l7jAHlZbuAngjUR5tD//zeYSZ9j9/x/BJPGPNhxgDvo0/F4cjxTL8f9IomYKel+LaRkjsyXAr17h+YefBp2UbvgQmHs+XiPOg6jjCleaBr7zlmj9zjQv8v/wqTReBt+PZFf5+JP9H5SqR0aLYR8Y3s73K23SyYKD9uRPu41+e8ou8CaOGMqsTbW3KIgh5UKZOPXPSadL4JcatrW/4+75oEfwYsixVkfakyBr0cpQF1KST5cJTceHbrZTRoWoIKZl+Uz/d+JBM9anooSRHVl/qZqcIoAeUiIF5ZFO9lE+h0fy0bzVPW4nmAjsJHSzH3Q0DjOb2v86g8z0W2iPhUSwq3JoRbvzvQTs0MoulkmUSTR9LHMz1xuBx4OkFvgueCsQoJIeu+WvLfZAOIe+4y+p8e2VWO/TS5iLWJ5Lm88A8YDRwKcBpYE/HlSpCI7row159WkqYJ1KaT1oruQM/RGqQ5Onf4V8u95Gvb/Jbm9wuFilXQ+ZdPKuQvd63N/yr+/z9XUA3U4fD9FsD/A52ezN2aNvDwSEpQwOT4Jt0HuDIXQgyViyWsKebFuz4Ws/bAsFVEE4QIx8613sPoUuhWrFNozzDWvZs1t+dKo30fOk9WhGNyokdhC6gySD5BoNtDEImIWYh2SAacX+4ja2yq0GYQFlC/Pws02lV6eyhwTCzqHuhQTO7oeGEfdooqrTWoS8U/+VirIHYAUtFkUO/TSVBpYgMfgRrfjrsj71r9aGpokhr++3ppXcDsiMq3g43R+rk/llcJSlnUZwNqMXoJkYTOQhHTrzVDBPD6p0SZJZ5aWoR6UERo/BleLqshZSzXFsFNxn3nd6J8iP9iLB4kuTdUZnqECiXnWIKYHAHsKGuNE02zh651bkP1pG23sK8Qhh2gz38ju0p2OFYS7eVxQM9QHqB/JX1l71AF8IhMf31au2lAvimRVyKFCGtpS6DavIHlX4X+1GBN6diNwRs52f3+6U3oaL3JxFicpbkGk3CuU7Otuwets852wIFbR/UQgW5x/jjQ8k6+WtvDibXp3QqSZUzG5I823/ucxqIUcX1yVyAonVCMDffkK+goyG/AFZ+/EL7Ile7ib5OAQDtCa0IgqENuyyLQShN/a2WoC7FMEXyF4siJSuOoIVW/OamgvlH6g2U811mJKI8Q82Z2JwPWPZ7pe0Z9xwPe9a+bdTV69P1w/jf0Dew/MlIXHhfjVoZVxRweVhn5IawqmrIurAa72DwXrHhGPI01sEwbI+xlPJOGn1IYVPWl8dPllXodvtMgugnoI2MU59pPwO4aiBUQ+MD4ema3+38SsE3UXLFZ/sXCZVphpirNuF251c8a5ofK4hoJ5RjwYD0sygPXkK+i2QxoNP9ThndvMud7s+rcqvVWU58/IItIBpM4IRnPxXoEbQN78mCpJ32HFWXsxCk7n5Ck3/5nf6bpc3TlAwPjRr1jJnZuayiu2yquWyCtF+RtZeSam39J3BRiEVfcYsbu59uDE2/YqHKIv2TCKDdxpDRw5DRd54+4xZ1nG9vEtaXCgiR8OvWxFoZBq3mdAf/EcQhJwfKxVEviN+noTJmobJqEWvroEmy1KFRAO6SqLbL24O4XPcYCVL3x9bqA2G1lps/7TIxc0m7oAkO8q1+BKTHSidHYiA0+f6sdclgBLyj8lgSrUBieNX5mz3frkbIhiiGDoTvhbli1t6A0pAAo3tbrB8P9i4QGKd+u7D0zmEv7OWvVDHWfMqf0PYpcz6XOj58dHd6B2dbDon5Tc2+0KONdkGjufs2+ELLdEoqz/+8ZkVHL4j9q7M8usqgwVrl5tvqoSz8eQRe2HXO22JgkLE8w9cwtaZLgJWFWtckmv13pA6p+vyQcM41RdztBaIdoaCTdSH0805+z4bbqzQwIrmuIPOw3W62VvudeLDTTnui8YupsOi7gy1Ec/KcXMEy6hparDkuuTUMyOv2HQQ7nLNNHe/eIaTvAMvl4WfzqG41smQFHs8jeUP1urxhUxiRYPO84nMIJxSZ5Wp3GbK/Q+SKWMtOavJSXByR2kk3l9MOlpcf7jZXqhyMXemTdEfFVUqU9AWpMQbU3cl65JLWJU0KqWXxyzaNgVal7eXl9fTlMmSW89PjvLD8MO76Klwr4vXmxqQh02Z36EzxM4W0JD2S/qiCmQiERpIhi0Lckd9yDmueLXzGZ5UJeRt0nehK7yNCUvaQUU4JeUPc1BP3Dvp5w9bpjWR/9EZOydT/MWeX6c7LRE+iXO+MMtVPwM8JJZESJzMwXOxy8Hx221zUKU4/vskJpI1d+lVr/is6BNVKrbHueeDwjjpkdttRWhcjm5P80ay1zhF4nnxh5oep06HNYDEkcJN2O4D6Y0Erlza03tCSX8aAovD68ArapVQh+KkTKcBCf9vTrnMgjz7qj9+nDsNlDQrpHQIqFWz8qHs86y+H7PCOT5LPq20kueOWNtfWnShia05XRilnu+TsM5kYaf32WRhdA9lyeLlNUtnJGXkNdO3755gUBGcoZ5rpkez2lqiFtZJapZPaG5sUjGd2yHxrRsJsU9AxJfPJGCY51CjsFFol10ioJq/7nlWUV9poNyY8R+rtBo0w4+ycKFjgP6h5D+b30Z/mjp5A1qaTDfeuly8ZmA1n0q32UusB1Pjj+/eNvAM+Z6CFXjHzq3uzl/w905HGnfhk5blaKmiai4MZnpaTaR8xkJ/mgTtkHroHQERYrmlzUzOxoI4an7uFPxCXm+BW+/s46ipnbT5+tMwDNPRxWcC4EpDnanMRh/CySQC55s1S+EubXR9FgKNv3+esw6M5tDp1WnLwOIvWcjARzxtgDjT6TLpMrmjx1K5q4KN3/jo0MRX4G+fQX9j35mCtBrDg5GY3eTK7lpo5ujJd1sD+/JF3S6L/nKhyWJS8DnQe/AWhvwqXVs4dPkeS7DTb2alLGmZGgEwVWtQ1m3AM80UyUmZI2t2Fzjh50ZxaC/E6xCQVWKleXnxbBDWOkIAM75SgGsp5K0tY118Cb7rp2RigkEt7uuQz+DxRHxQvrtRZIXRrw29K2Q/5qld5fdOVE1fucgMXeMpVMRoCldR6CNlt0po9bc1unUhV19vOHyFlu5XA5vZmzq7OJkZ2SG8WQ7G1gjM3ERMRH8YfHyMIm8BFysHe1EjFzMiKlEeFiYmbmYWFi5mVjYOFjZ6Jva3OlBS/yWZgxMRFZHQWxFmRIqWDi4OzpYOX4lEVNiI5IxMrOz/4NSMcg6mfy+KmYmJi4mdmYuFg+2tKLa/FKXo5GDqamL2VtZ/L8r87QR/L0pA4L/qy8L09/qqWHmZEbEwMyo7OLgQMb/5lRml7M0diP5s05stqsPHwsrKwcYhyi0iwi3GJi7OwS0kKsTMxiTKJMrBzszKISJAxMfNJCrKzCTEJs4mLMLCxS3CzczOKc7NxSQixMn95mIS0GNU9fxqxqipbGbOqKHDTMRCxKzHKGtmb+FiScTF9la1v/YoxNsfJATKm3z3CgnB9wd90w4QkJCfICChUd+OnxCQ76QhIGFnICDh2SEgEfkgIJGWICBRxCAgP1pCQH5ig4D8rAkBifoWy+6AgMyxgfiX8XJ2MXJy8XAyM0dgY+JiZkYgJxdTECdXFBWnZ2bgRCDf3ZueR2D+excpGlmYOROx/tkff7ZCxMjFyNbB4u8dyvoP4+/gav/WkYwyVqbOOux/5Plr0/8s5e9Z2P+eRcjJRdjBQ+ePQeHifhsLvbdC7F3M7F2ciTj+PKmcmamV0X9Lomjk9Jbir7VSNnN2cHUyeasl599r+ccJ/34+jr+f76/dzsLOxMoobmXrYubEKG77do2Jmpk4mJr9fSw81ny1eBPpW5D0fp4ZGWtowcJDkTmTI6NbQSZx/bBIvct5+GjI2dvtrqq8mMGT+u6K+yH+eXnYgNDE7/NLxeALCAwT7legnIyYu3Vw1mD1/ATjEqskcQr/rH9ka0dD6fLMXhRupNfU4mks/Ovg4Qk8QsU+q86QxqlNgekq95TpD/WOxhjOLuXzQ8qNwuVnGbIqWX6xj0r9KMNa8OvaaQu4XXQPArPrS6e5Z0kaOX6+T4d70/4+T/d7Bq8vYjk9rxd7cWHXNf3+do2X80pSlsrUMCf0YH3h3FRl8mQcNqvG9iYLj+PUYSs3e/hnAUUP7KmrPZE+bzaybxrWyrmfl6uLD2e0BtDeNzLdcqtjQeHySBOe924n8BRqfYGL4zYX1/gYUXs+MHQke7OCb5mJqnmEulLUdt493TZTqdCnf/bSvtEfwdaE+nlALZOlvaNE7WDoj9OEk9GfiLaSd0qICA+UkMOoT5z2CpsTuHr5WPbqmO+HMOQVMYhozHgrJY76qS7zqPmJoxNkzJN/ZWyKy5kNfUcL+KzPpkNh2PSBRD87RaBdlSUm6j0NEqWLUdWJrny80kGlsWZIpfFKvaO2alSyuDWL0s8Rac1PVJb+1IursknfUhAsWroexW2og8csvpe6flj0zKyiM7trdzfQJokpclsG1ovrnPL8Sh//jdiwMR4H1iwzUz0vETX7csOno1OjLE+vlq5pTWkDNe4Gh0PQTk6hsGlBKNDTJDvbVjWq5DP0ePoTOrt07WwCCR4zXcFYlb68RJ5P+5gMxf/rRZ8JXnMDySOiINPn9/4P0Az2a0eXcMoaFc3Xtr/fJaD4MyURUSL75/5QLezfiUN85HnI0dCfkP7sgExgsWUrp71ZKb/07vu5/NF5XjxWdnRDw7TIeLi8JqqST0TLda5xlXbY/s+1lVMhMbisDfrPMDZXGoNCbPQC6PQ5S9ljasVmkyH0WTTbS0Nt9QGz1ah+u9afEXW56MwLvoB+dzCL53JDh6TolpyLQ+/WV9pezuaiBgdfHgo8ijNzEZWNqkce6YK/YC882FtgVjaWwxdYHprCwEstWFsRWneVLjUjlKpt6Fd45rLcMJnr/Tj/vlQY7UzuM7b06RM5xmllIHFWR7TvXUz+5wht/lLFvLRuJGTb+RvPiJVYshbhZihqVtO4GnSYMCsKF60IedVKjPyBuhtoVCaH5rpnx7wqBIVrKLKgOmOfc3xdFv9ceCT5H+ehJ8ogXeoRptOgXNR7GjjY0N7Grsf/B+g5WdgaXQCAQ0vsWgdUU1m3vqFI75EuRFEsiBAIJAgBKVLF0HuHUAUEqSKC0qQPRaQoUqUFAekgiKAovXcBR7o0QSA04Q+gM0tH58167/0u13t/knXPPufuc8u3T/m+lS2tng7G6nXd4vPU+WhSuoU/jHppI2MiqBlyasJMMK/7XdSArLva7WWzNamAtafk5qkrfUtGa1qKWL8BT4y5J1+lKaS0kK7Qfs5oLZTTvE78fQS5OVXZ3ZWGKy8K2ogKle0qWuqfa7oRTTwSiQ2VjTbv4ciVIjy7auZiFDdw61AhNPiW7MlCQ44SjsC4jtl3z+carrqIlQOgOv8PL+ZYhGM9UwMHykgozsc=
*/