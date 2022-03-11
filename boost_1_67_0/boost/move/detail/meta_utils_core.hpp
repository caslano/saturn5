//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP
#define BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//Small meta-typetraits to support move

namespace boost {
namespace move_detail {

template<typename T>
struct voider { typedef void type; };

//////////////////////////////////////
//             if_c
//////////////////////////////////////
template<bool C, typename T1, typename T2>
struct if_c
{
   typedef T1 type;
};

template<typename T1, typename T2>
struct if_c<false,T1,T2>
{
   typedef T2 type;
};

//////////////////////////////////////
//             if_
//////////////////////////////////////
template<typename T1, typename T2, typename T3>
struct if_ : if_c<0 != T1::value, T2, T3>
{};

//////////////////////////////////////
//          enable_if_c
//////////////////////////////////////
struct enable_if_nat{};

template <bool B, class T = enable_if_nat>
struct enable_if_c
{
   typedef T type;
};

template <class T>
struct enable_if_c<false, T> {};

//////////////////////////////////////
//           enable_if
//////////////////////////////////////
template <class Cond, class T = enable_if_nat>
struct enable_if : enable_if_c<Cond::value, T> {};

//////////////////////////////////////
//          disable_if_c
//////////////////////////////////////
template <bool B, class T = enable_if_nat>
struct disable_if_c
   : enable_if_c<!B, T>
{};

//////////////////////////////////////
//          disable_if
//////////////////////////////////////
template <class Cond, class T = enable_if_nat>
struct disable_if : enable_if_c<!Cond::value, T> {};

//////////////////////////////////////
//          integral_constant
//////////////////////////////////////
template<class T, T v>
struct integral_constant
{
   static const T value = v;
   typedef T value_type;
   typedef integral_constant<T, v> type;

     operator T() const { return value; }
   T operator()() const { return value; }
};

typedef integral_constant<bool, true >  true_type;
typedef integral_constant<bool, false > false_type;


//////////////////////////////////////
//             is_same
//////////////////////////////////////
template<class T, class U>
struct is_same
{
   static const bool value = false;
};
 
template<class T>
struct is_same<T, T>
{
   static const bool value = true;
};

//////////////////////////////////////
//        enable_if_same
//////////////////////////////////////
template <class T, class U, class R = enable_if_nat>
struct enable_if_same : enable_if<is_same<T, U>, R> {};

//////////////////////////////////////
//        disable_if_same
//////////////////////////////////////
template <class T, class U, class R = enable_if_nat>
struct disable_if_same : disable_if<is_same<T, U>, R> {};

}  //namespace move_detail {
}  //namespace boost {

#endif //#ifndef BOOST_MOVE_DETAIL_META_UTILS_CORE_HPP

/* meta_utils_core.hpp
13HT/NzyleJ6vAtC1tqqRLNrH2J5rptQfE0Ynuc8agbHMUoGOS5ffYyJOYEt87ULF4nj4VW9h5aEG8ipEoU6fx7+HMUt+Qw0W96+yN45AX37CE8vSX0hsTTjTYmawmaxbpKYXceC9+ABP9oCOZBYBdFrk688YAHWWTcJ86DULEIHSqZm1/HgN4/k0F+fBEvN7cVohOyoLzWRUyycXUf7IlPon/D7FoxniQ//2OSnphBVqYUyxFP4Pg40rEDCNRMvR/oNMATY/8Uc4gA8gvigTf7b1DByNBihf8Yqa4rJnVifp5T4NtViNBjlfHzD+sJNRU9edMhe30B5iK5Ak8HyNt7+DxaMetN9i3XH3jmMxyRzojkqtYC+Q0vdi85S+qkAUwgdaJtsJi9yHZ5iC45Os+ii673jhAX6uCCpj+3fpOQO/TvK+ncxeE8v618kmEeHcTeMqVUFEZKij2PVUCcdezNsK+S7HK06cRYX6lWrQxfRh+5saAGrBcaO1kMHD6+w4uiVhJtFK3FPfjG4ILwQPUzrh4C4X77oNAUzG6+8DIgar8zzJMoD2vvXb+P7hzcmvUd/t78kVdyRt956KweN80X9rrPPzwq8CfxIPSPsP3elY5x7PoNqOK7x5x1HMW/ROdfx1gyxmiPj9eR53hrBYIuhSfnr95vRgx0ZsN6w3pBsszFaVhVnDVvDRe7rYt2YFc8qjo1ZMEXwWj/zweas5FUAm7K6R6EgRiFvm2x1HbttIZ9Zz1vP+7wC+UKsUzNBvXWjsGsWhSaDs8iZkjC5ee1n6AKoerLr42ANaRuLrpJyP0SKOHbTopZXi1bZJL636Kp1lLjHoHoEWK+9xEDpuZkgJc8iZ8nNkjCrtMrmZyaGpyro7Jm/Bw2NNYkP2b41pb+BbyyZTh8YV/JsGKdhjaOyfA3XipbMs/Lf42lPK29tdZA1nOtkq6VoFPXdikOmUG6LUy78puppJLgYb2bbDuM9rdLDII+iTyndzeWjNGCKA0SsCnSiUc22giH9uvE0ogJeu+71w47dH8pC7xv1URuZA7umRfO+Qd32rnFMaT+F/suP/3Aa/ykt5no8PDris+g+jNASVlMgI2uOBcyVX/JhXNGKtoNUkFxF41F51ahliReSOM2f7Cbj+JdNYS+Bjbf6QvnDxfZODAYgfacA7+sza0mLGRT7fnmBT42h7v4AdcOtFUDW+J2IreTjqIVkE9A8vJxrAObpOFlnIxUvo9Z8MWYeoRf24rXoNXHmkUgoBwTbuRigOpoB2R21ynlQCcv9jmA52mE8PFRK1jtixpbYAbXY5FDgvYcv93CtIBDwSo0jhP9pPMV+2YOyNwVSp1o+Zqjm45B0Xb+N5zypFP0/PMx2QCWvMnHzY/64SQ0v/2frBCikHDacq5z3xyR2NPus4wV5x88nFEw9uTLXRNZxKsL4WHf4x2RVvkGu2oQ18hj8YAyhPwl4saUiNX0OGSSrcpUBkES5LiVk77oEyxgQzCGrHPXKAMDX+CV+P7Akjb4AciJM/8pichqEekGPpG04AJO/0kfDuCccc/5p9Zelqf/kiT+//tI09TdPU//4khnEf9Kc0m4YY9/pSjWOSKZM94ywFsS+Jl9/sLLbLKD+iB5ecueKNbkCminqnUpewRBKK6jqOMWaAlgUNbktZnnrv4zHOEGuqoMme2bITdZ/6+6b9vxjnMrdJWGxcbi8iZdaHbCwyBmp09TZCNqcW1by3oHmOpHXolvmOtknFx9G/qv5UqPf9SJwut7UyN4YygnTccxpVNWRQIcf8kbcwzT05+8OaVXQq2t69NDA0BuoMCt5W36Nh4/5DTR+J9ZCjzkwGOsyFrY6Fq400P2vsTJ0tLWYn8aIqlOHxjaM1777pvN3Fcg9tJvhVaPN0+Qap1dAW4W8s/+6enhhibVcUxAIf3+fCYO/y30/ukHDjQcmewz10BMQOrwYI35UkNv6tHqsej2MnutGkZ5HfPqoZGAmeW/Y0LA6CWlCoPoTA2qq+v3R7WnvxwaKae9HE3sPwAQ5m/V9Zq3OsL0NadrbFfmT25tTPAN/02wla9agmvxI5jOHDIsZ1nexcWWXxla2VFMWC8dL2vhtbk5s57s9ueoNNxCpVpIfVJipkUkEmfwHlfDbS86KngL5kSeogTJDoMyiYEijCs3o9FEZ3glodwZ2vL7HRDH0X9xpUp9K457K2FMaawqX2t9MoHgm8QqowzlsZNA4CIPG4VEfTLQvBlpkAQFwfFGjXrBsSq9BDM9E8fTnt15cD8OBDYdxjgxkAsut46wiYOh42B4vf3tCO9qV/MUCqoY4xPBWXy5qRauNFancyavW8mNWCw6AmrtUz82+ZBn1URYPeVsgL86nmjHfmDETeQG+xIwrWcYsqb1UQD+n6tRn6MCAlwb6du0xBWyHY4wOe8DY38DtvXqqkZMe2m1I1pnlB4bkFlPg4Dd2mbBR0yU8+Wt/JHBXvWoCVaGCIqwV3Xsojs9mxGizkQ9cHv8xxfTKbwzYWmjdhb/aaYq2YaYL0l49U0ssWwzAi/NSlJWqeX1ZZQe+QgHyegzqHPowFUJe5Z2mwFb1HTZEqh2iGatnxbYaimE4grt8MWhqCTELT/yXYTrahq1Z5JSQkIWcErNUyzHJoqmrL+n7VgJHHpkiKLVuQGP0//Ol092/Bh6JpJHIIwOjQBSUgDDxbTNeJawpwN3DR6O/yq98hMwTD1QsAl2x+g4+Yli9GgXCQqIrRe1GYD6dA1lv0ko/HEYukLioAiUJWfF+nEZS6LYijqjjSjqNlAglMwwl48mbFlNpMXB3QrHMuGIfTFVsfkKxrLhiW2daDO0C2rLq16javuuEsRD9gfTcecneuYeJo9k4afdqle1nxxE52nFEMnWnBcFTEDp6nUAHjaW6Lm1+nK7aWiqo/SoVNdqwNkxRV10M2uyZQZtS5mL0fW3ptP7NNIIOHKaSgHpbR+8qNY6B2nNoL4qVdz41ofxd+MldX9ym8icZY+PcwAqaaUEKuB7EWrQMUonJFJMdpvF3VrxsJvujmckNxl3QkWYXzCuaQYjqXnOlaavhkyZqnw5xDVK7A79apPc2Qgu6bgTt9ZFM7u3dJvk/vkqrbSoJswC+WXExzdV4q44GEFMCpb/bbWpgF4LlaznvKqSRY9ecLOJfBB4dgZfyZUjW08j90NAckknW2uqVc03+kjA1/Tf5ey2Akv4uCR93JtrX2nj83sBdIFDDDE8Ezgs1oFUv7qrHjP7S9n8R7f+90/Qfz18ffzWN/pgrHy1SL2SNUme8rmPBWRETjq64Fh2zhGN3WEgdjx40YF8R0O1uqvg70N6vlxnofUNqfr61PReatnfuw9konwZAxyn8DFfcZItUcgPF20yRSv6ntxTlCLITUN6axeoh4hDIKpsyoC8WjpSTuiFSPcyCYjtInUyhjzDoRx5tO6guE8zb4MT42NAIWXHac5CeoCkXr+xHcHu/qoFTJSWgDjuDF6mkAm8ixPC0EK0zgihMD3HWJZi/m/caENqmQqjDG02C9ybA22+Al6HCu5vU7SfVB3R4b1J4B1V4G+Lg1VJ4OK2hh5BVmYngVM4DkhUo/dX6JxQg3aUBbDWwHxDUy0236GkoxYDjA8OEnwBqOFCAjNZC9xbo3UP5MWXfUApinevZJaYbeyrqsZ6lGfiNKXpGBS065gCpe5EBUvY0kCqXJo53L0DqMUDKUSH1kOp3dEi9FNIHKqTHUkACIMpfG4DMmgpIDgOyPwlIPwAJG4DwKpAwqe7TgfRTIKdVIE+mBvKCEcgdUwHhGRDTskQggwBkwABktgpkAO9FaUAGKZDLKpBA6kni0T+ccpGJzGEv/ZWB3l70OIiSe7+QEBg9/r703JLpvwcceX01GqnLXGP2zivUvIz25FppvSqlA7MUmDwCErW9cysVJEbZRo1r2D0Ce4Nc0TihVGLIv0Dhgd0mL9uuSd0IWVXAAgE2OHzUoHLiHRRk86nmiaIj3d4TGkOpxGidSjQZlDXlhZaTNVzZxrwQ3knLwh+F6o/gF9G7yRobJtldm7lQDqRX4mPwKhlzrcDO2ru+pCTdBktlX9piHL/Vqfk/kEzVX+lcX/XVBFwfNzVxo3HbmWpdxy2ieLafZh09k4KnApb3Cg3ka0mCQi8lUxxC6XRryKqCSLOGNqUGscwIwpYKhFUFsTzt+nk7gypCFEWaBRRMjeLgQgOKTLaSF8Wv5G59p1u+bRpumzX9Nrc5BQ7swHJ9m/uMqZcDXvrLjJeklc/01dwDGaaISaHGIyg10OPaqc+HoE2Qp8fJGTF0UGwM64uVnmWL7nBZEwgsn1NN5vTeMjSeGZyF4DUI9Ir69DM3FFVQwGfIegCyyj6WjBt/bS286JELmm8wf4/unpH7dzFF3n0aln2Pl6zn5UMvTiiY7ZdP3VDs74bxLLhj6MsZTzVS51X9Pnn7HmpcxknSjdPMGtCvy+RWqHwYKqfuMyhmzZ0Jc+6y9Z5k5y7R70HzeJDixOOVYCWC2VGP23dwPtQdeMFvMnnluXs00zaqb9FlACnwGrzxyWO7tTez8I1TcvcHWtEqLv+X/oZPsqj3a0pjHzWhe+VDeuY7KO/sS2U7p0X7pjB90/Or+x5gF9VtBvvovy/X6eHlEQ5mKi1JtHHkKjkrfjgCRC7uK7iNUUxVwpAkEx5fdmEiU7vCMX1N6iqEZDxJfIHda7cY7V5mSSqkVTFOnUxPOHuUoJwtjE6M1GRjaRlIStIoVC+ff4KmZEa68FElqCz0UgPil7QTE31yYyvQFMv//ScMZJWXUbARyUqyUUiaTUx7ZuP+E+AB2AFqPsIjOKnLiSfYvkUC3XizA6U5+0xat9Q6cnT1XJKc9EUQdjho9VIVFjEOQoA37U4sPmuq4uFK0bM4qYbVB7AGzlgDT/rZ/FhjarGxLqBqd6DsQHzLKtFpRbNSF4105cNvdscwlMOemMMCSt83aFlbcF7HG/hjIn7CqSmEZbFoWW5p2JnhIjgnVmdvGKg+mtfxIW0ymMWeM3rRKiYEOt+ITQ0zlBk68/ZsvAK2WNkLqQ7j0NiprWwn5vQJUhc2LciPHNQsZg6BWr9VerUbseGyU+tSGU3cPHS0LzYFnSwHNIBrxIe3TGdfUZQo9XBpG8HrNItNoQXNxDP/CE5O88JjzR1j2aHsKfr4pqGP+HWdJPG0QfV8CKiRpx0Y38EOztTXhrMzrTDDBSj8v6frcm7MALbFQOO0UkMv2bEzckXypXco5YTqJSlf5weQfx6qOptrJxSBvQgcyNgLUt2noOVoOVk7Tya1k6+3E50bCL62xxSXR5Jyje3kkprCro9DKyRpESTL//PTcexHnvr4vy3jAGBnrgbARwFgMTXDjX8bV6J3yR/RfF16PkEFmmsAutoAAifu0nU6ZHO0XLHp543PnLZO1OcsjZWozxmMTQ3fr/sMR/6HP9XNCd01/tZp3Jwibrz+BXkuMGMTZb3qzKR0qLW83Mj5Y/dF8VCaKwl3/f9O1ofUsDb/YixnB9fvsYeBIk4gEWagCBNMxAAkwgYUYYaJyIFEuIAiLDARHpAIfznrDlawCPp6KxHQEM4x1/8Mrd/4W5aBT8XoDgCdkgBaatg6FdxQcP0SHgBZ8N9d+6VbrDv2R7dTDtDz2nUW3eek42z+XwCN7QcyMgSHg3Ydh354sdAW6L0f3W1zwNunZ2ofl77YerLGo561+T9/kWPrpRrbepbWA0XmQQEv2CDNdmBtqu37Zmb3p+7QH9KhH6AGBgV2/3gRAjTM+loNVz2L9fEiFqBbGeOju1z/x2E/7zTYjPB6gSwL4//hGQUJDAwvFsoygUdL+1ZAFhBsRZlm7FsDrzhBdWQWV2/fBtCwy30ZJsisQt8VZAUs3aE8oOuUfTk6pz0A1dGXrI939p0Bn0EiwD/1UGfbF/DqIpnOvidgQYnOfRdAlWpbB4icBjqepHMfaHS1s+8DmH0D5Kq2O0AScuBuybcZ0xhwnmqGMd4HDI/NZkTcNwLyNmxioO0CZJBGEBjnEqANGGABSPJG+Bg+7wgJkCvSTCghBh92BYcrSpcPmFHVZJgwj7s5090ICqnmH4wl/EDruZt/sJSwgVP24ZcfxSHrxZt3gvMZaAnhFKCNsS/jJJnQ9kP+N0NqP4lw4Gw/dZfyAFtPGQwcoMbQh+/A0hlcORnfDuuc+wLIzTjhAuzc7H3wHdSwevIdnJ3BB7+VKfT2gvjAygOkLYOnZi6wFBONAa/a47E+XAos/d98hxWI0PZWWG8rSCxjMjDNAcP1AGTgOzjLAaYWXKK9+CvGBKm/IIKgUIPUMKBi7g6kXXe8FeQ8LBdOQYuWWyaQogVjfvnlYgmU9ZZZjC8OSjExoJ23bGFO3H7se3tPEtiPDVou1QbKBgBGfjabdjwAgENLzX0NeJTFtfD+EVbYsAsERUVJ6y+NrdRoa+5KRWED/izubppdqwa8vTbNXX+ru4rKhuBmMS/DS2klFCsgtVptL1/Flp8ofwnBbJAIASIEEm2saTsxqYIgJCSy3zln5t19k2zA+/Xe5/naR7LvzJkzM2fOnDlz5swZGM0fBQ3BRLxsnUlwEv/OBeh9za+A/sJUDwFVgC0uFIkOkfiESLSIxN5xlBgWiZ+fT4l/h8TZtenrM2r1kbPLNlFgA2IxavX9XiSuEYmyvmUikYlEWd98kfhkv/rkef33v8b8ytqUfBMmOb/GevjqMWIRSc4wtgQnfGwXOex5LEFjYn98YbPMTM0fnpVu/uB5gnD3jm5bhhKDLUG8gdKr2MImComxaK7BkLPwDaoIIXIWvgr/3vbiqR517srOb7DlCObj/wFgrLtqJVQmoAWcuTu6bQXiLf02IyngFRXw408hyBpCu4LAV0q0Uf5A5xUCrYD18ToAfptQL8ESOUsQ1lyTuyuWsK+oyd1/22V7YeVZseP2y3Y4D5ea2GFnM/zbHGt5+jx5ymExyJsOaf1dz+XPkjR0aePhtpK7TwPQNGhOndLzh8n/xxrd1kqc77KGR7W4rK03GP7PywY+FSeZ26YYB9qxaLlO7//iz63GoUF5abQvq/aULMIF6PIsYq2Lx5oMubuSuTXeEib5X+T3Aqvk7pf5bI992Q5fiYLl28dSfgvmV+ctxHzMBvS1cyD7XZG9ZYyec/vdr/igJ/UeUqbj7PcrUhGs8X1ilxUEKuvh/451HM2tdh61l79Fhq7sAnbJ3NvXAtW2KK5qxbVTcdUrrgbF1ahggNJmxdWquNoUVztdOsRAJYrrhOLqxnNxUElZfrZauMUHgrIVXWsD2Xg/BDRFdlc2WiG8Mt29JcfdwApPmEFrinSzmhxXV9BobmQunoNXEk/kuJpz9pmhfneX2eVgzTlFUM1Rc68S6c7pDvjQn51vBcKA4Oybk/v+bP7ytVqY0xQ/vfv9c92fwdc1+pRI6zayxIT7mHa2LIIQHfUGAsFhgWCGEm7l70+jC0r2xLiV76L19Rl77AOkWOHR6A6Lj784KvlQSpvzlL38bZGnIfL5CRF/nrDIR1hdXc64feFC+PlnE8vwUNi6VrEPwmujyYN/YabS/DQIrE3sMS/XG2aFFbddfMyI1mU5I12Pv955Jc6TQu4b7GfYrwALt/n54czkfc6k9wd5XJ7dBUrQO/PGc8V/Ysdycb4BxaWtIyJcJjStTUpyJdKmRNr5TmDpQIA1s2nZJTOMtPquQ+bpjiYS4WtFG6W/hd6/Irc6nS05lghfpak0wiczfIFKItJDJZE2dO2j8zp2R3bQECjxoHeZqNIjdaWNl+LohTKj1dZUKRZp11QrOT5HNRtAeKyT9MDwSEbaYkcd2ZzaRY//bNIGI+ncuqSNnA+CImZ4eE93IoiuWBhRbe7HX+GxFpUeVE+mKMnNe7sTnbfpTPk6mJGxRGg49/79q0TnVQLcvukXqLH6dKLzl+1fiZce2kgadg/JLoCsNJAY14g3wEHEhx5IIUFHdJifV50UwSY8NEpJ+xSG9hImua7kSGQXBHVeVik3rMS4NRQhrBVqasBZF2mDDXxAaLf9GGCQH6Or9SwnCoJf77vx3P5xeqcJvRFON2om5rJJxo0LFWnkKBMNIrDuHYJ1vXrWHaO5pKG5Eed358PAnTmCOxUksCTLeAZckOIzly1OKlHntUNzaNaEdBwatqLvkuZSnApqYtSP7ZCOHIMnvKBfvZ5+Nw3lEdo0cNnejJVrM72ogX9ok9TqZjOyS+7Aia4UNYpuRbdtoV3DSNm9T8bg4t3EFDFP1NW4ZylYUIeU83PX7m40Jz/JxrIMnwdviB4tWXY/Wn3vvQo1gqwgkVw6yPEMH80ovLEed5EeV1J5P45tdVLsGpPOVoFsdgMRGlTZ26GNPjozEMBkXskU+RITzgG8BIMdC+KF2wy+eAotIJcmF5DQ2GAiOLmkGhf7bmCZjndMuGa04XoSnJoYZ9tJXkdF1bGWsADdjKDvI+jPBahWja9AVnLVFFRGnDVhHe6VWMCDBVzNzhr7wp3Q/GitVXFzxV2vFO1kCTat26N3p0bHA+dUUEWANt8KGtCzGv0wq1J+02aE4g+4vxJ+LfZYHkbNmtaH10X1XtldXhiuBTU0eD5YXChb+sTbyWFbY9LO+XgTneSL5puNI7jFS0nTjwjXz5J5319FvlliAbQvqxVnE1vEKJS3hDLxeQRRBr22Ctthme3PDLOuIGYQDdRWv6KdSQEEY42jPE2MMnouOpibQ6rXU+KViRFugPUjKbKAc2FCuGmROnjSbAldEsU3lFMQoP94JIQ3cTDh4sLXvFU/+zS3Rlf91GitDfWuop1OV7P9OYzfRzVeCoM6NXdXyU4Y1s7z8INURcXdwDfBLGJFTYzROvBgNc2EC6KRRkNoNDQd+bBklmh85/SkDx2dpLHkooOh7Q313Ymkb1r/ZotmJt1WqwsS446KQI5Z76YTwQ1DiWAhP0bm6d9zO6u+0AX6QNzVNCoph2HBTykL/NfWoTUFe3mLCZ3Hw5MGLP8XDlz+5aJ3NvG64fw04nXI1R+9QZzLSQEYJTaPoDR3bBAhLHW2KnerbjFJqQAwt/njdaQCuFthFvLwYakCtKapzJ7naguN4D/76CuMi9l5A1UxCMohFYUjgBfBRsVdXOxQmzKSa0I/rmzWRhO9aMZ4xJIP+j8=
*/