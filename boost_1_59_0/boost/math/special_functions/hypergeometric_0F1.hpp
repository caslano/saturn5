///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPERGEOMETRIC_0F1_HPP
#define BOOST_MATH_HYPERGEOMETRIC_0F1_HPP

#include <boost/math/policies/policy.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/detail/hypergeometric_0F1_bessel.hpp>

namespace boost { namespace math { namespace detail {


   template <class T>
   struct hypergeometric_0F1_cf
   {
      //
      // We start this continued fraction at b on index -1
      // and treat the -1 and 0 cases as special cases.
      // We do this to avoid adding the continued fraction result
      // to 1 so that we can accurately evaluate for small results
      // as well as large ones.  See http://functions.wolfram.com/07.17.10.0002.01
      //
      T b, z;
      int k;
      hypergeometric_0F1_cf(T b_, T z_) : b(b_), z(z_), k(-2) {}
      typedef std::pair<T, T> result_type;

      result_type operator()()
      {
         ++k;
         if (k <= 0)
            return std::make_pair(z / b, 1);
         return std::make_pair(-z / ((k + 1) * (b + k)), 1 + z / ((k + 1) * (b + k)));
      }
   };

   template <class T, class Policy>
   T hypergeometric_0F1_cf_imp(T b, T z, const Policy& pol, const char* function)
   {
      hypergeometric_0F1_cf<T> evaluator(b, z);
      std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
      T cf = tools::continued_fraction_b(evaluator, policies::get_epsilon<T, Policy>(), max_iter);
      policies::check_series_iterations<T>(function, max_iter, pol);
      return cf;
   }


   template <class T, class Policy>
   inline T hypergeometric_0F1_imp(const T& b, const T& z, const Policy& pol)
   {
      const char* function = "boost::math::hypergeometric_0f1<%1%,%1%>(%1%, %1%)";
      BOOST_MATH_STD_USING

         // some special cases
         if (z == 0)
            return T(1);

      if ((b <= 0) && (b == floor(b)))
         return policies::raise_pole_error<T>(
            function,
            "Evaluation of 0f1 with nonpositive integer b = %1%.", b, pol);

      if (z < -5 && b > -5)
      {
         // Series is alternating and divergent, need to do something else here,
         // Bessel function relation is much more accurate, unless |b| is similarly
         // large to |z|, otherwise the CF formula suffers from cancellation when
         // the result would be very small.
         if (fabs(z / b) > 4)
            return hypergeometric_0F1_bessel(b, z, pol);
         return hypergeometric_0F1_cf_imp(b, z, pol, function);
      }
      // evaluation through Taylor series looks
      // more precisious than Bessel relation:
      // detail::hypergeometric_0f1_bessel(b, z, pol);
      return detail::hypergeometric_0F1_generic_series(b, z, pol);
   }

} // namespace detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z, const Policy& /* pol */)
{
   BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   return policies::checked_narrowing_cast<result_type, Policy>(
      detail::hypergeometric_0F1_imp<value_type>(
         static_cast<value_type>(b),
         static_cast<value_type>(z),
         forwarding_policy()),
      "boost::math::hypergeometric_0F1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z)
{
   return hypergeometric_0F1(b, z, policies::policy<>());
}


} } // namespace boost::math

#endif // BOOST_MATH_HYPERGEOMETRIC_HPP

/* hypergeometric_0F1.hpp
pKwqRpBljDYuHOr81gXzR6Sc5mG+z/R6rEMupl3CJvEGd2ajvEivtOcSttVRbDRqoeKU9Vld5TVq5CqmsabghlA56d+XH19v9cFVqH6C6V4SVvJj9VPL5zMpBTxesl6mFnpAMXn/56DgthJDMR5k+18BKVsPNPw/KjqNC+RebZPv/gWZWOx/G8VwftL/Tf6/9u/2Qvm+z3umz8jV/gL4/r/n6zU1UeEwutXCmEezztGZzHuzWS9dylxRYB4YcqqZUQrRuajH1cdvKnJKzD0mld0xgD1j/fDcyGbQjvYF9LLIedozMpQN1DTdIFKnpAroM7UBuNOsUNdgRl8Y1UH00cCjJeAoVG5VqTBhU+OAA4GGTTGFr+aumlv0WN7pZI/aEc2yeQb9ZaSTV1FOxmqfYGpg1SLwDhRlBuEiWGDVYczIOcdHy1dr6a0TEu4cNkOYtHH59b78CvZhOj2E3Uq1uz47tRGi90ugnw6t6sGwPYDP3wtz9QL5PYa2YwgiawnNS9NznAId+UYLdm25k0C8BXjGN3KJaciFqim2qbc8dvQN+OyFyHG6Gm9yUnAaCDO0d0794qSJjVck0mPdLby1XbGMiWzyPWpPTb318wYOchv4l3iSBRguO39FShsyOtunJO1qhOhIqPfEqYDGWqa+ip4qQckB53mAm/3yR3v9Nyib32Pyl/zQHdBBrnR3xqPm3VHkz/tytCwAfHp/3BDx015/2L3heaj9GFu+Bk+H90v1A0y3Hp/OL/z0kX9gpuLS/tXTFLvu/zeqEP1P733/8m+E0ncDzcw64A9aq8lyQDZ5uyViAQctFSKyj9F7T0ml7+w1XPWQZDDUQYE5Rmn3YlpN52/3GBlwY7Vg1BkC57hJHrPJGDdrQtaprQPE7khSzuBPT9u10I6x0lDjGkYdZhk4dFtQAPHZcYv6Lu5OZOU6sliPfpEiNoBN5u1yhqrAOdNpBev1TJcUh7Zk8sko4YimrDxyeLTO+8wBNVqmrbFkmhFo94FGGIW2cJEvJ+TnzCf25T0j5jA5L4SRnF67I6jorZy2gQAYQSs4n8yn8hHSxxnrQeuv70OFMtvR3sCjX+ZTZel9RIVkPkvqrUxBw+UxzYWZYUQOaKxnbAc2UWhBU3+H5pWGdq9zwyoxSpwgxirwDAzCKDH9kqbX/Zsd/b/Aj/3PvHQR9GB+jwQkleSA8Xt+2G7u/T/HcD0vPhY5N/7PV1IAprTr/i0W5OI3xY9ArG+hbfEnXQoaw02hd7J6Q4ggG46fz6rzJuidc2opFfsZpGct0/fFVH5og2TuPja+FuH4rGU6YHKq6jEDS1XzuLIkJ8zZAQYUGLOAsyiNLDbkxsEkPNZObOR0HsYLr9vCLuRvVCLEcEun+O3XzZ8mdqTweIFuD1/PRgrmHLWyhBcR49+u3oEf8zbVUVTS0pAeRFYAACz/03h0bAnzObbUzN1mzv0u/CDbW5SBVCAGVVHG5mo/ScFOzUqM8uj4iqA2iQSPBfontyJRFO/vVwQdid12cdmF+Xh50JDfuatT2qeNFnhcu7tY6UdEQZSl69maunymC/GR7/w0wDcXsF4DEgL1t/H2eLmpgOR+vEBhZiwjKveUcDcuWWF+ty5KIEkQkDl5YaOcq7ph7O9tYDwnETJ7dYA36I3+MUgP5J3UD03QJqTFSBF0LcifPHcdbYP3sVs0afRiPp9KZ/ERGUpc6Fz866EQ29im4g+AzYOcqNAdeRWfj9O7Tg3veW5uG7KIb3pQbNGzKjU6nnS9kp73aalowLX+d4RUtCUwy4vqFzHarFdSxtUUNOPLaDzqSBFQWobCsHPchi/hV6oBSyXDweXym47a2yFXQ/c8IB80V1xoZeGveRrQPITnl2MvsGs7FoBOWSO4phr1/mKjEPEmsFqaLY/LvDyVFzGY9fm4VnVq9apMCnAWOlaEXqmWUHTSHni+sOJsO+lafU0nfhftZf5daerMBort7dFAdXtTf4qeBiRpEa9ZKbYb47HaYB6M/ygEXc+Yw38VY/xkGkGek8+R5jzhy3CMlS6zehhcFXmxSjNAv6WjgLrIJuECmKsMbWi9vM4uem2MZhNeXHKgNYGdbEr2rsp7bgSlwmiMrBVJRkWeuPYG0FfAq5lY3NUnu+nny4uuaaiihYi4f1u0v7goNpIR6rliFb0INq4ui0Ojb5u01Oi+16KCYc7yIPT21HrbIOTIy0UNKaHxEl4fgaXB+AqLYOXnqFPyuItnCg80szg1D/mGsSjmOlZEVJE0B9KDd6KuTpxSV1Ntk1x8JSUL/RxBS1N0QwvwO1iu7aav0rZy0deQzW3VYztH4n84yw4SxSeQ2+0bNNski2TemvwQS7068FAjBHll//HmJbTo6DAIAl49bD74qQHu3Ye4178e+yCfDx+iYumRDtYJjTzDbwzQGlOI18fHM6YlLBBg6c+VwolJkWmbRWmMqdE/uZYk50rpPpPWuPtZjebIwM2rrZem+iXIZ/g72873kgwVuyF4fOPoDl1b9e+5SCqO1bA5HhKJV5gakAdpicIwFO/4m7ydKA7/BVsXFPhuNAVeM3d8QEkBLH2/ndWwbTGMpoeFvVWquct9hBdZOqs+mVkdgc5Q6hmp0iWLry/1XxW48DxNSidH+U5boIpQWNvShGjwxQJskKW3sNMO9GpmE5NO4ux3edidPp+rdV1kb0wH3BvfaPuoP5/SsSOPXEjCkPddd0mN/W1fyyaz0+y7LqigMC7eQ7duqkbjVOXHvCt9GWfAK1Nsz+NKIlA1E3lwweDUISim962UpFS+ZWTazdE0sbySrsjrc/X++gWUC85tpwd09z+uK/7zpRwEy3mDi3L/xi8vmw7HlXPWP6QkHlWDQU3gTQOcH50DjM+CA6KlOutz2fgyPlTnixbVfpc1SA1OHW4ipi789GXumrAPnOa4Sib4VRC2Zf80hPyxg6k9uFYTJZqb5bRBem9vABCIDi7+ud6opMHmfi1wbyQdcy6H/pdUL8seJDNjVX0hCE2M0KJK3L/iTXg3d0PFABD18Ej8oUlWzvU5s+ERI6fd8o/AtubOX130OBrwTDOpmtyyKj7q5miZ0S8TiJNK9JopQmlTRmMTc/dpI4x+UgZv2TNrcMhHgx+bqLoE2kpgk6QvPz9RRqsxedWTQv9azsuZJkhJsrmutJmewYgHAoVfumx2troZ/smS3szeJlRaQq6ikWDKrkLeyUPDQv9WDiQ2rH16OTA3nJJYtXqNrUa7DFwzVvTDmMhvn4TzARy7TZQBn5hshexNGpSVnT/4Czut6e5r1QVJVB0fpbuVchImh0piyj/oFjZdAl7GDHkPfdp5zZUEL++K7V+bYQH93l6XNnYO5Fc2C+bxo5i0v6rdv/lMINHO29E2v57+YRPYUeYMDxuZgYGKbR6uAfn2VGrB/nDEZP46vc/xAZhOZHy0ngFXb0WG9zZIs6/p8Mzhc8gZJ1NFrTj7hPKbHMx5ppt/uHMPszuya7G1uO8fv3o/xKunb1OeKg9vJZpbaU8of0/vwMI03UXEw+qO8MAT2TsFAa2jvM3pMnzNMCHZJPB44bk9WlfdcAlgvH9zozRSR+dvQmYqR29bArEu0P9MJGXv/3KOM9xtOKycs5qV+G6K26gFJbnvnG1cZe4E9+xiFEt3gO4QrdqQKR0TqtmqipjMbuvG5maniII6HgwL+ULwfXQcQPfCIO2QweQ1TVe9rrUmJ0iZDaYbc1JSU270W6cHMOgcqxodveuNRpRubn8yIiSyJsm2GZlk3rl7Ss6V8xZBg/RDJ11nZ2h4pwuMTZLrs0fM9JnynTYzTpytkXYGjg0Tsp2TGP5ieXxxciSxolbnTZVikrYSeaycyLw/g7CDZo8Y8Q1qhqj/4HxyfpqUWTRXNRGf9eGq9yfBloIsfHd7mxRtzBcbPN7ftp9+fNDmn7DBD2Akiio14Z+XdK3961z/LtwUcczpwej/8fFhRZ3E+V/ExXz4m3n0bjVfPeVi+Olb2BTftpH5P6kAxA+othsmIvo+6lT2y5fYpv7IGotopWshErfQnecci1HylpOEzu0CjKeiThPgb75AdeHIYEb2w+tjlXxyanWP4YCDd8c8vD0Y7nyN0SjjGS6u+KoItnrBtr7jFY9gXz595/LXqEvVZ+nx/eYyfW/ZaK2ekuWChIxWXYhKdyTn+QHw0PC4uOgT55EaesfpgqmeNW+nS5v+glLjTcRJtLtsWS5SMLKOxJAHwkSpBKBn+7FNRk0W2cbGJKquZyZ8DCVd7aKLGtd9bio1cnP3ZYxHKNLfR+fz+biua32nm1i4QRlpvTr0oY7ugluq3U6UJkpgQL5HHNJO7yZKlvcXFMUdeaiuAAJeAwGXae1+NumDIyaCH4xTy88DBhyPwu++24vWPVs2980M/cWEnhSRIe4eYGLzijYGIOzPnlygN0AL7OZi8rin6bUJFsq8ntAjQaQcZwwwLyPd77fFcz+mcRcjZ1pkQbvRW+e1pSG2oRKWjRj/zdJzfzJJhGWp1W+PE24SdvA6tbtxqBNoG9DwPnR9Y3pLatxhbFSGNx+p+QXlJwvjUfHr/43yuWtc33QeQYkFWqzXc4DARTWK5PpF9iPsapKB2x2aqQ87ToV4kAo6l1z9Xt2n0kfK3YzJLxrqq/MMBFYmZG+i3kjxeyjqLmsDflGYmuvz1WVfVfMr5Du6RGrKBG4aFun3h+YOLv1CilIcwncJXVD58/DPHOFOtY9a/7MLzQZhZ9qcmL/J5d/pJJTuKL/j4XQrHukLS7/pzfnk+LO+rj5D//jmmGxGS+Z7M9ys3sHOPxvygbFt5B8RTr+z/W4P/+mBfoM3+n9jse96eND4nYe8NkUglR+EePEWHk/60+yEVmK9JuFQ/xcaBsYandhNCKzj3iOl8faJY5cxPdHM0Bp725eXrU7ZuJNoBDnkgCoj2zm8/loaF8J5m7raiNBqHf6Qdf5TbR0bDiqoj2FVVQJKfdKaFPOm1lZ8/JaGnJgF9+sKS1dlbDzILGF6VOQ419MBZXO1EwbbceBt7USIN47kcbjnqongiGMvW2pgsSoBN2NKTKM1jE3KzPuz6armSyf7L8L48iAAUY4Q+YBoEQnhDRsxW+4AO9EtzpwdLhtI9GgN6wjxYkgVyTw+6PdbarwamzDeFUIiG+qeP5RmeFdqjpD0fFov4y3jY791UaE1TpyEJZVV8T8Vr5QOyz84bDIBRkoCW+w7HrGN8Qy9zPSRMhBvYo1EggEVUyUn7ZM5d4jy3nqfktOYd4ESOqtiIws5No2RQkjvxLd+QqHEaethF280nSV50lVg1xQenoq/Ab4B5uJ1a9ncivEMPlKAuNAJlAxuvcgxuK+1SjAFf3ea56bX1FOICwGPr8FS8BMJM4VjED7eRMYlpiKle+Ri5IbUQAYPlCc5wHOU4ddAs/5cETp9FB+gflTB65dAnrm/K3vhwS0Bvh1ZMOtEOT/V6Ha6gY/NRsp//Y7Crrrsxzfqn7c2YUciW5iXk7rzpaoN8BAF9hHjxESUAHWa5h/IDLBHLnTzERnUR9HZLhnMGdb354pg5uWzx0u/S0PeJK4hfHLRjMJ6ZJ5pEtPeImdWPepd2UbZ9Mi5Kr6ghk9mBwg2iPerXAzhc49LjXY8+96lKUtU77LtFf8kAsvLkuYkq+FtwtELiSUiyb85XCnFoQfz7FvZr2m81Njt9441pLpeJQkis865kgfZnQqlNF89ONYZrAfYco2sGR7UofNPx6u0bBw0WDmY1JgYVLBp3HqUmWA2uxctWE8SL0Qzmnl5czx66dXTiUIsRZ5okUfGSrIfoYdXMhAKk8I9OFIAxvw+rHHMohC0KTC/TbGt0umDvR7JzWqiGPtUL+ilCS2OvOEtwL/mRyTQf9OuBwv5zDhBjQCjv+VJFuS3785hfLSI/I98T/UH1KXMNYHq6Qb0CdZlgwMqEkoENqm9xH8M5P9XE7F+BG8AOhxukC+T6cd+O8uu5ltDX0hNEpbZ1349TO9LuIiPtKlUXsIwz8hn41lBsx/p73vfuuuV21WHYVxu4vC2rJ2yYuSo5630T4y55O/pWGJrHaIiijGrp+V3aGs58vHM92orinsa1C52im/oyKpn1UE/26vMCNQ7c2lTUkWrE/MUTcgsBrWb3twuzKuuvn9oUzlbku0/FSNOp7rH9MmiOYZtHnpYb89z0xG8UlOtJFNQQuZ6Ejctq13/3IKzoBVs7DBv4eIkxxAFh1cYAF2USMnHrvvYe8qk33TkTsvKHfJR0lM9NKO1durQZhaMvlasSq4pd98+liT38oz6KIIkv4PUsZ7rIlHxtpbQrxZ1Lw/Gk4M8DZpWBAQV/JTFsrxVbLljbCtK4sOjduH1NnRTfLtfxC23KX1tpMeZc8IOd0cmxnIkNMtNq/QXWiHNYZ5hceYOQy9rnmq5eUlxJ7b/5e9/WRwImQQ/clYuiZuNZmSL08pzfH0BR5c84GXd43mLI7Vvio2PrbvsLU7eSe4qIS6nMJe096Hvbt0ZUfSyhnk+zrfzytkUc2c5dHVm871/m/yW4a7d5zXFmv0UuTcUAdwDWV3/xk5dYBnNy30RZT3iDkdHNG9c6AjJaVFAmBjbefLylpB+v0jR2pjr/wBysyezF4LzKKDrf42M5Z3VOVkj1t5O+DHmdxlvgQOV43PwutEo/Oy3HxXrNhZmVroF4ldxMRYJ81lfNCaZkF6aadv96N+rVazs5IQDOOpmfu3iP9nU9Rg6q8cGAnrDru/IGpilt6ClJcGDiPVylbtNRf9x09SrsF9E5mFxUHC1at+ztdoxUUhNVqfWgWWd3psCQ4LXO+Wn6YBUxF3QBRUrNeX0kvYXu+uLb6Sbu2YJwK9ZDlDEw8fX6PGIqmLomwh5y+Eo1ap+nrKPD/TYo5Di+d0cABb5NBSGbdLmHTadP9B6CMwFHjBe8Nyn6P0zXNxeXod74O1nX274yJgtxb965Q1RnKg4vK5t0W+fHzb6tfYDIv+SWbXRg62dqO85bt/Y+BdqAZqcI6oN4KHvSE0bwWHrDyLqcr+hfF8MRw2mtTSWa4h2EQrSNnhjuIc0RkPslWF9Skhfb4eAbdOSzYAV+4Iyqj9lBx8pBsEXIsowiGK0pafRPPQgCvQis/w4YZG+X18KWPYgKbpdcu1ArjqsegoUCf+3UQKKLvcWXGl94H2OZpGevyMHyLgxQeXQ69AAWDR3ZGZ35hnS+tlxPZGUiOI+FG6Z8oi/j6Db8KPvCEO1jesJsqEsAnf0pDJ7KeYpyDXt2CO05hHVCEDwnCYtvZOSoH2pMaJ26+Kcp9JVCsGdPyl8uainjGrHxGgqAlsEGtLkLp1qlTtnY8Fz7QQRqmPwdyzSWoJgKnarr29DzaJnYz3pMx73EagAZz3z5DCG4Wg8vFmb384rxiMEMtR0nfB7uixLoXv9wc/HpN1APxRSBaeGM7I4gwEgDef1b6mHWhbaY6ZFCVBXNcC/IheIQVp5Icqj2o2EtiO/+iVGGGf35ubdfwYbdsnEYFt4eKcTOIl4DjmwdGl5qt/871P9/Via5T/h4KUeFrkPjzqxv+D/pfmo/XOlrOyV/2KwklE4qwkzv4TOUZOcm2tSfR6hd2eBwo89T1sRB82d
*/