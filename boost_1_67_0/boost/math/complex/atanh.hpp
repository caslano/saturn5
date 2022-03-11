//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ATANH_INCLUDED
#define BOOST_MATH_COMPLEX_ATANH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_LOG1P_INCLUDED
#  include <boost/math/special_functions/log1p.hpp>
#endif
#include <boost/assert.hpp>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::sqrt; using ::fabs; using ::acos; using ::asin; using ::atan; using ::atan2; }
#endif

namespace boost{ namespace math{

template<class T> 
std::complex<T> atanh(const std::complex<T>& z)
{
   //
   // References:
   //
   // Eric W. Weisstein. "Inverse Hyperbolic Tangent." 
   // From MathWorld--A Wolfram Web Resource. 
   // http://mathworld.wolfram.com/InverseHyperbolicTangent.html
   //
   // Also: The Wolfram Functions Site,
   // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/
   //
   // Also "Abramowitz and Stegun. Handbook of Mathematical Functions."
   // at : http://jove.prohosting.com/~skripty/toc.htm
   //
   // See also: https://svn.boost.org/trac/boost/ticket/7291
   //
   
   static const T pi = boost::math::constants::pi<T>();
   static const T half_pi = pi / 2;
   static const T one = static_cast<T>(1.0L);
   static const T two = static_cast<T>(2.0L);
   static const T four = static_cast<T>(4.0L);
   static const T zero = static_cast<T>(0);
   static const T log_two = boost::math::constants::ln_two<T>();

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif

   T x = std::fabs(z.real());
   T y = std::fabs(z.imag());

   T real, imag;  // our results

   T safe_upper = detail::safe_max(two);
   T safe_lower = detail::safe_min(static_cast<T>(2));

   //
   // Begin by handling the special cases specified in C99:
   //
   if((boost::math::isnan)(x))
   {
      if((boost::math::isnan)(y))
         return std::complex<T>(x, x);
      else if((boost::math::isinf)(y))
         return std::complex<T>(0, ((boost::math::signbit)(z.imag()) ? -half_pi : half_pi));
      else
         return std::complex<T>(x, x);
   }
   else if((boost::math::isnan)(y))
   {
      if(x == 0)
         return std::complex<T>(x, y);
      if((boost::math::isinf)(x))
         return std::complex<T>(0, y);
      else
         return std::complex<T>(y, y);
   }
   else if((x > safe_lower) && (x < safe_upper) && (y > safe_lower) && (y < safe_upper))
   {

      T yy = y*y;
      T mxm1 = one - x;
      ///
      // The real part is given by:
      // 
      // real(atanh(z)) == log1p(4*x / ((x-1)*(x-1) + y^2))
      // 
      real = boost::math::log1p(four * x / (mxm1*mxm1 + yy));
      real /= four;
      if((boost::math::signbit)(z.real()))
         real = (boost::math::changesign)(real);

      imag = std::atan2((y * two), (mxm1*(one+x) - yy));
      imag /= two;
      if(z.imag() < 0)
         imag = (boost::math::changesign)(imag);
   }
   else
   {
      //
      // This section handles exception cases that would normally cause
      // underflow or overflow in the main formulas.
      //
      // Begin by working out the real part, we need to approximate
      //    real = boost::math::log1p(4x / ((x-1)^2 + y^2))
      // without either overflow or underflow in the squared terms.
      //
      T mxm1 = one - x;
      if(x >= safe_upper)
      {
         // x-1 = x to machine precision:
         if((boost::math::isinf)(x) || (boost::math::isinf)(y))
         {
            real = 0;
         }
         else if(y >= safe_upper)
         {
            // Big x and y: divide through by x*y:
            real = boost::math::log1p((four/y) / (x/y + y/x));
         }
         else if(y > one)
         {
            // Big x: divide through by x:
            real = boost::math::log1p(four / (x + y*y/x));
         }
         else
         {
            // Big x small y, as above but neglect y^2/x:
            real = boost::math::log1p(four/x);
         }
      }
      else if(y >= safe_upper)
      {
         if(x > one)
         {
            // Big y, medium x, divide through by y:
            real = boost::math::log1p((four*x/y) / (y + mxm1*mxm1/y));
         }
         else
         {
            // Small or medium x, large y:
            real = four*x/y/y;
         }
      }
      else if (x != one)
      {
         // y is small, calculate divisor carefully:
         T div = mxm1*mxm1;
         if(y > safe_lower)
            div += y*y;
         real = boost::math::log1p(four*x/div);
      }
      else
         real = boost::math::changesign(two * (std::log(y) - log_two));

      real /= four;
      if((boost::math::signbit)(z.real()))
         real = (boost::math::changesign)(real);

      //
      // Now handle imaginary part, this is much easier,
      // if x or y are large, then the formula:
      //    atan2(2y, (1-x)*(1+x) - y^2)
      // evaluates to +-(PI - theta) where theta is negligible compared to PI.
      //
      if((x >= safe_upper) || (y >= safe_upper))
      {
         imag = pi;
      }
      else if(x <= safe_lower)
      {
         //
         // If both x and y are small then atan(2y),
         // otherwise just x^2 is negligible in the divisor:
         //
         if(y <= safe_lower)
            imag = std::atan2(two*y, one);
         else
         {
            if((y == zero) && (x == zero))
               imag = 0;
            else
               imag = std::atan2(two*y, one - y*y);
         }
      }
      else
      {
         //
         // y^2 is negligible:
         //
         if((y == zero) && (x == one))
            imag = 0;
         else
            imag = std::atan2(two*y, mxm1*(one+x));
      }
      imag /= two;
      if((boost::math::signbit)(z.imag()))
         imag = (boost::math::changesign)(imag);
   }
   return std::complex<T>(real, imag);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ATANH_INCLUDED

/* atanh.hpp
b1+f2KsQH3sRRNsyRY4bXL90jduQunmC8QTy95kZBPnEUqrt6JKIRod0pTiHpmc+wQ01DGdGhYqsAit+vUd+vU86KWVXo3o4S9q5Stdp2HpfUII6Uu6SFvIv/HUWLo5weEichOQmbE4lvx9jRI5g+D5ABIjBojSfoYHOInGVKprWZbycUuWmqJropkLSBadXMA7CKAXyuYPCCwzMelu/I7EtOaLsaXUtUkyFSDt54/5h5xP82gPsiHfKB3JpQyBi7DWwGr6YW2T6kUYiO03ki0Kt4AUTmH1fuc4AsD7hmLwWvyDGoOIAPlQs2TkaoPB8c2JUprYzZY4Yc12jlzmA8ENFl0R9MpdwceO67mTNxp0cn8w2j3pRFzdr3zIWaHIv5MsexOHSZd6n8IHG3eE4yd4H4PywzDinqHHq/+RTAHy13B60YV9JYNtrTU820XFy5KqLflB2Kf7LT9dy8NrcSUlKcqqmTyj2kaQUmCVk0+n345J3dsajyXkPqFUUl9slOokygfR1xmhEeoI0Dfa1ttJNYCDGM0n6YDwinAJ2B8lGl07JWPZicdVUaPwViZQvInmyi3FjjjE+LWWQuj4A5e3FJQjfiWgBFKFYSARdibJSqBQj0QT/R+c9rMOhIxHfAq0zi5PYPRTNIM8Uwfzy2HcTnhkwJvVmUGpUs9iH/EDsWyn9ky0HrUByP7Q3uQ0ZIKddn4HEQWx9DHrJYnPjk4FJx0BQ/OLw+dYmSBfU9yVXEnhOrteqwdjKPL+bRuvvJH4BP09TWComP1KBY6FEMOmLN8CTpHGjcnlaFMTJsOMSWNLpH5npU3Qf+HQQZa8LQ+gyYb65k3pSluxWgVLCaMZ+vueyoDbtoTwjLlVe+SaQ3EN1Bi+MwKQtGm7qalqagbfODMaF3lrwmtxablfyowfpOEHfM3E51E7uCXlPGH0RWsZBrQuyHGqMTgYc6RkxXXFCpJeRrTJ6ILFIRjx4cc0FxnBvxxWmlACTT8d2NKJociBvU5Jo3hL6ZOMIsOLdIfV/fFefOLgcWsWRfkNARjuy3DCH1Qo2i2ujm5vyAj2P2/Opk0PZRaWHkZDJUOJiNW5KREuGKbjCBXDEKcNxwHRJdQmWtxiovQ11hgH4CixhNVNP+txB8t79kFZrpD//aGcQA70BVZf+MJ+ADfCMuiPXS2bmsPwL60yZYurvOqvoC/K4zvgNSONnZLA+z6zRrrdagSOxITIU5hypFojMDqTprP+C/16k4eXQ+NGkeU1+HHvZSfCCQ/64iPcbZHwRbsuE+PDGlnOwWKgAZ+SVsj9I89iISKqRBwYMz/cOuNZL9NR2j1wjtPm2/fmhPjzZi58o3Wm30Je9uqVfB3JAqTFWnJhyyP43MSi5WZWQE3yIjGs9jERdABRdercH8PdNX4xtnJfNQfk+mcYAfRXj3RSnQ8O2jS2ZxiooyTQq/sLViq26RdSSbSBA9O32RUY1arHt38bhqQZqQdu3y1Ywm7xSJilMjZO8uuVJRLhdqA/uWa6j41wZlqa3gR5hWfA5ghREZEYUyL1A6zYtPofOU9Gb/GFVOa+fqQz3qmEahIkMuoD4t0+QG6O4+Zh/v3gc9TavQTKT6DxpJLY7z8APf4Ud4oxGsshrKBoawZTNPTpxlOgUb+SVPFoPTR60ftlL+jmUYHBMWkbgk8i0rEUbzuf2Xp9EKVLWVBjV4C7Ej3dXkRcT+ZqavMjtnwVCplc/vu9q1BDQkxh6B1QeHh243K5XND6KLhBXmmARYArXZ4herT0I0Q1GTMNFoly/fs8vvjsbZDWelyLRlFBe3b+t37eL2KneMu/sEj4eZIFvld9gJEUkAZT7QwlVEuaiNEecPGn+B1FSkLJFIaTjnMlmwXXTZFqT0TQdA4wPMztJblQo0EUsn9aNFJQ3L4JEK5IRpHskaOjkP0IOxigndXA2Piyt6/n4CGW2KzBluECc6f1sqrJBA+KvKjFB//gpucoEhWRusthov6WJAj0WCJKNeC/a+zlfe4V5xtgtO9KucJVAh6cyC+HQ8YgOs+ve/cUilIJGnGDLrxWJEMh4ZabFAPJGRFtlArkMyuMZFfrh4AB+6w8AwO9JAQAp0fH/omk9ut7a6ttycemA7OjQagVAJUhvKAdoBQAAReMwO4R7z49PSIxIzExQyGqkHQc2BHsu9HqO8w4FXyf++AbFzYN7Dz2VPyZzI+Ns7FrXMaLdQH0W3hslIZaSz8hvFAcABvhf/QH+wOm+CWla4BbdtrBVqj1tRNy1GbU+sG+ivgyTPbhLQhnDMgZsn2wV/LhnD90gb3BzG3eYcHQNNgjK+elJCjYMYH5jSIrMTc88tXZrnJAYAMoaKbqSiW0dm6y996vTDVHJ35hS9bxUmCe8ngRWXpM/2AfH30SWweoUSljAhgOAm50TIz0gZrlGqnA8bL+fxdx03sOy/VgUM9rNLjw177qQPG+aEQTcjhNebWMc0Qkn3rpvLLObZaQYbdc1NWc3SFGak4r/FGe90NyXRFXaifWFG1TIS56i+cbjVxBABfjBpbNA4HKhQmk2M7FFuRcYTeluZBARwYVh9u4WDQlv27yFTWfVVtgvnMZ40wRe0pbLwXzi+6iwuKk8QJPqC5nlNiAOfDUBS4vAbSKyvARRsuwdJdkjlTyyOJpm4lSsz5msGlZSPTp6HSVishcJZdJVpGE0BaKEKOklX4urIQziE6LBbix0VeLiymwE4Nffzs+PPVXheicJ/YJ9pG+34zizRHfM8rwDk8MyTAFLfFCGnZrd96F5prLabTwq0tAdoJgpzMeTuqkUqUWShmYqjXxnAfF1xOL6ph2R4J4VVTYxRymj9jVYRm5HZpUDwIhUpBcvkR3c9SeT/hvDyg2YFRZ6im0Xw7olNu9Kp5w1KN2xVHRQ7SyVhq2vii25w+kRt2QMO4hrMivaz7viO67iP4JoQviYmA8fYDvYnLw8mRWoZMiaOGjJcHykPc+VgFxkPsis9d1BLA7n1en2puMFwmR7QvT0fXi4CnNGB4xKn+r0V8udosr3pr1fIAsT13SpU28D0O0ZmYFuZ7ZB8EpYksNCW/eYEptWbJIs0yRkEl05Wjyc2OTpVgDkPN7Ws9EpJVzZ306+bZiujnxNByz68gmXkPuNfc3JBtlVw43rISRP2MOR4Whc/EQDx/HrX7c/Gz5OizokdbNCxHieCWNdI5zF4qgVeQxicm00LBqw0CtCNKbqSBucB41nN4L3Z7bOwKSySzL1PtJ5t8pyCN3b9LpjnokOnP5eFvVLsno8xYsVs+bD2yXFjLB48lOnXnJXBtIUlJFXGhEm6KHSPUALniFY1k0XoNFVgVgCwJCG4x8NbW99nL2srIyTgqht2ReseUQySQr9x46vcquwQ6cw5YMY9se3zsyDvJJerqt1MpUx35xS2SRzbL+gs8HNqffqx3aZBa7af5vFlY2gG0S36eI1E5cJi0LU6aJieeBgA7j56fahf0+KlqOZ8hVjUeYOmBblmR1BQR0HYM3hN8N5cOOkbuRAZuzJNCNZRGUVJfP1jqBeA5vghaCls7dk9CCQooFGHV2g2l202zWxTgA3hbr0UU3rIEOh6lw5hunVSRVenkWpXAY7Bvr2MjhqFACLUWXgy22jPKvpY9LZGB0lSZl6lqAULM1LBQw2VKnHs/84AVlG0IRhA4AsjYcRbnoYO/km4Ed3Zz9aV60s7J+Qy/Kn1vcnMAxg3j0VGGxCLfnZvugYFdGKnwFwKeFC4hjK/Tj/8wBTK4xWQyZtZf+Xxl2W4UFIcowAwFO8JdPIAYV/KQaORjvVWyf+1l6aR/mdZZSuwslmRMWhzo+ZeDv/VKNLxCZGQlwgunwuMUzQLIglKQ5bewUpO55rJuemwJmRGw2gNyEoYvqivp+mDxR46t7kNIHOHVajGlt70sLFS2Oiw5cocyyMg958NdVB5MBbJlgSsTXLzzYlFLkUTG4UctRdLXGhGuHo63ME/tyRy+fx3PXXJNRsBH+nk2llfx4sdN2GGodFWjInW3TDsl2Xq8tT/4XtclBcpDvPUuPpM67j2aOHfT3XUg9MbvZUOO3ONyvizuBGr18eTfigyUaNObqCmlN7lk86SrtoUtkkIuMl328sg+2d++e1hnGnD5JQ4ap8e/DMdK9w00QEUSQzkfGBb2s8XE4UiHZriBfxwYKC4IWmpCDuJ4FeecyRF0zcNPgzyCBJA62ug06H4UsL5XeRr+tx5g1sV7sXV/94BpcWh8f/67H6JU8NwnS6ysGnbLb/94yU36x7ThZqOKIwhHCeOOSKTpPIYIvRzJsv8+PUYpxV1TnvCb/QcO+xsPcoV74WK+iHNgrH3EN/z5GLCGRKc3EQ5wGMPRlK2W7lB0r2H62whVjl+5tdVKPtQef3aG/r8xwyUtwcYiOZzImnjgJCnS4p7+a5MGi9gadu4vYNbiruv1SBWai3hU5Du+HFks4Bj30wxh/vmPRalzwrnSiW4RYWWi3wwFy3YuwuujDV0tQo6mw9HVQKtz9L7zYxm0X9IRXzIDxWoCUu3oUlA8ikFAsK7wOQZdUYEZ9NQC/5Zntw58cTWutNgQ4L6oO1Cd7yKfH5eUozuQSzffCcAcsLCss9jb52QgUFgKV95LmXhrPJB6Dg9ZeK01pnKocLuDsb/1LEQWpCGlZWesmeduG3HiEpT+PcfHvM4fifG7DzBsJCKjrhwyUYyvZX8adu8FnmgI2igfgxsEagoS4f3ZICoxneOWQmA1R7TPvkxKDFS7D1e7CmFJ5DcCgCJktdPlx0BLa/dvf4erMtKDUI/uyK5tXJ6aG2mo7sa+QK+JoAAO6IAqEOVWfe2TDldRK00iD+FSdtfyh/s2L62BlzDQan08mIWPCChgbr3Ab/t3SCUUinomlgZk03eLCmeCIfixCXMLAfD0xvC3KN0w0w780nbrTaLiFn/B8AD4Dwf2oxVyBo31Yui0JGZ42hjor2Ydybdl8u3Sm73dXH9q5sNVlH3d+lbpDiO37zCHLZrcEMTgXXDxZcCyN4lrnz9zunJyu14oQm9Im+olj6IQMeIEKcyWPIHw4KewYKiH18zwC8HjsWDlSgJJiZBfZK1l5P1eoLSd33oSfcRxMCe49BQ0eBMYU3ChB8vsM5pMnEEnkoe+IhEDTUQCEEf0y/NfljKKzfRIv+LQdpz2W0VFdEQgOagMb51BCDnaw4B7a2H2bd5VPEic1IU8KJ+b5NQJADF7qr0htTUGjM/1t3G592/5uk654k2qF3hNv24MHjorSkITmICnXE44xDpNWb/8XD2Nm7WLPFmdUemnmeIhY0IIrhWDjR8UlANKUwLh+uWVUbLa4RdBndSuDfWwilV6AGL7m/trbqW5NdQwk6QExTyDQ0Nm8qNsDzboi6jPlRRkFE9G26jBlKV3bpF23qFou34I9HUYqEShFmBvQtKYfTQoP5ARg6qyyg1u+5uFyy3BAJ4ZBMSVQ859AJwJ3+LZp5CIsIG+g+BoZVvg3wjWYl/Zu4ehuG+qLItZE16tRgjxbJPYyRE/E2HjF4jSM/FYR6D1VVjdXP790Ufn5ioT8DcvToJc0DD2F/61YlIlsDPRTYYpkt42y7blPyNBV0BnICtPgAd3iONXYGensDBhZT7xlq0aWJOoNVWkwgv+4X1lkj+w0XOM/sppMGFLU6EYibj47+vPJ0lBbbqxP+78lxkIHfJ/BPyTrwpS/rVb1PuS3JvWVk2zmH5zEcrjc6oCFKrEK6gdogwji9581+JQTx8335veTNsW7QO9SfXOgx1aCGfYpEzEl3VsVoC3rKc05Q979+qIJhLVqw1Lf5fYkswqmxE7E/Z8G1r4APeW2ZSzpv1uz81tZ+kb/Xu0pe2Gz98zOuFYqt3PGKQVwNq/ryj+A4PEIVGIcHrsl4+97f2J0vEykTio4uZB7frxyvPbiiH34c/XXUfBrKlA7zz6n1H9So6jUEoBmUPPGT57srcyq0zXixVT0zylbUZP9NSok0m9DkCjIK298/rD6c3VfCBuBArWe49PC/PI3xVokFg+ChNxyp/XHcRmoBWwE1YtHH4BvljkhzAoHvQ+FmMDzPWhoimJYFU4xWt0TYmY/4G9bewu/Myk3WjogZhdIU8mVz1Qti8pDtvWiLSpCpxD8wzjzjQp2buiK3IHP4kHr4Co6cw2Vmw4O2ou9gI6vzVKoq7t/mee4lRixEEZ1eB3g3D/nqG1CfElABfe10SDwGj6bpzQDLkGIXRWu2n189fDZ3jZCf2BDc942kQ6Ld3bq4/BRGzGDAnAYcciIoN0PV17TGvKqrs7VZwuujI+NGJlFsuPtlmctMIgX5eMVz9RnCPvcwVuy/h66SP56cr549kFv+/T7Z7rIULzGPwunj83Az3zOtCbBK7zyJTFv216wMI+Y3t/sX6z62QgxO6aMQdpOMM8rlP5TJ2VWyfD7U+NftNdLp5lGTHIdVzz8nB9WwIVCiXOER9mkDsZXTLrE7dxoawLKy4Bg6so2Se9AlqyG8vnqNJy9cfvlak7G8+BrFMtjX4paztSSaXfwULIo5KnmyBNrBDE8eOSgiDTvwiHOJUx+PhLf+amyMSFLDGnWb96L5sL1JVlWTAEWgcpJpyPh+GSqHvsJN74CYVz8cn5eNuUmKd0Ade5Wa3uOAnj80pU8NDdCPq4Bv0Mo38B6C6LFPHWMe1IfaBb4/7c4PiYEK8dIoVX+UDEf9j4QL4R9hQp8mPqXFqHcq35mrtfX8J9Qi9W1wpFylvVplmw/RbZpx6lcA5oe86dIrXK46+4YNuvBRPSUgfmHXTEonzy69pfs6Q2C70+wUciG5Exluq7X+YUQCPz+z95F+sZGgvZiV/bbRBiTJHKSOQoHkmz57Ju4HIx/DiZ7nk6ZZGfojtX2ii3f1yEo0mBVQ1e43fWREIMPJ/HkOFiUrPHGTKUpuh0BNYzcNG6KpHyZJMbSWN+O9I5AxQwlhuDN2OrkreJkfstpbai7Q17kQzvFiBLBW8KXvLY273T1oRlB3GjjuKhvQLMlzMDE0JdzBuW0kiAZ6GdItaGmhogJYasoicaPdKIRU5cqzE4rMnlz3ViMm0xg6vSgP3ZEABiO6PFFSsZLJaJDKUtjXzg3GyFilwPnaFOcyIhwEKvRFRpaauYxTcwHuzkXeqJQiV1+jmrsGv9PivPqGs97zttOr45F8JC4ZKu3+zw6+KZrrREFp6Dd8Vq/IJzx1BJQtLt/bUWQaKUV5yF2Ef13HC/aWKeV3JVINziAnsu6e+iKGyxxGDiFfdeacM2vaHvmtNVMUOVOrVzwVMxWRaakoTf8CtCb9pLuAM//hnI7NHOnw076lM/A+IhEy9o6OYxFdBlQMCq4yMosWxYSUBO7sgoxCBXOIkc2IefyNZtKSD9l41yJR3gdrxRPvtsUQEUy6fDcPpTHlgkNDRSCMoKjRlkwvhqntD1s1+R4ohIV+oTKH+fPsbb4CLFBi8mxhvy88472Wx/UZj2hgO7Kr6ibtUJBCg/2W0GKP4UrulStJ/18tH+Hk4XGoqxqOHBhCA5UyXHu348c80qP/uoZ7eC3uj71dHfsnsTsZ9KHizEyDfOABU9g+Rcxz7dBSWFvX8QHEfE6rzkMAACz/03lyjNZDYMm0UuON4AmCplKQVyrKyJewUk1NSozdW755zjZDkXSv7MjJ6rJF9aeShuJty8MH9hFH5HHQy5hay1QOJ5F//oulOe2oGwyHuN20Wvdpmv/UYGhC+AG/zLI3u/f5awHc1mNHfz/6aoJsTWDe7+POduu8HCHnp6AlBmG6wlEatCIIHge7VC2oZM9PEeKyiBNtf+2PwrwR/IfglTbskJ0tTNzcQ5R5aFPa/RdeyPihIr2zcC176cXTnCgHq1ul2UahMOdqEc3AHGcM0gZQ0diaOYEYFM7S6Udi1GJgb6xTAAJXg/y9lkxD3bTX0kGFaX9GCuHOngm6Rycxt3Y0bYwQII07Y9UOVHbrdZzrDyYmhQOZeg3QtWHO4PbwYfh6Zk9MB4nYQ+iwcbxeFIgyI5ymDzsO9JuTbFY3p4mhfP4gKbPIEXuVCdbL16GeACYv+psNcqwajbFa8U/Y2/4C1iPSnpAU7Us7v0TStsVZdrUS72AtkQZ+RuPjYAiUxIa/NRc0kCRuR0f2vRORThOOTeO3zq4zJLBt7OjYUbNtD5D0t+pJ1Jd4reugz0bxuKDV7VzdY0MqKK3tFHDuhs/1aFsO8BsvFiTCSHR5+8nn/vVh90Gp3f6lwbJ39QVT1JWy3KYoMoYgvl3x2Ab1KkkSjMQEgfkq2rASwpqvsmVlTIcgP6UuPr0fgF+hbFqnEyyKtIXqgkX3gAaZsT0tkwbKwXDUW6M6Igy3djy7chRubqtNuRsO44CNO9qVW39fgURXtY4uHh23pEllaD/Z6mgrjxld5QjLk/aSIUEwVJXS5zsWbqME8UafsWcdDvuz17oSTaJGrjAQt8fqYtnqi7TlF2lafVRRfvQwd/qvXhaUxJJVl5MGeach5qo6VJhxQY6JL0ve7DoteepQhk7O6fwO+1FKIlVgp5/nb4smEnI6yYIlyIR15Y48a2lVoe+9rNYqRfGChj7cZScdISAAvucyAg1bXvo5qoQFr1QZaAdbBgC2Y8KwOYSzKc8OQ8nHU6nba+cJl7EKsNxgrkX9rVTxxlUY3N/0yX+b3NxUYO6yMr8Ppg5xfqyujZyjmtzGzGwi8WiXAWay9Sdc9CaURACWvXH+Q4Jdq/wcmj5cRNRQrq+BbUpC3ZXGJEBgqtX67Zqu+ko3xiuh0CZ7+vtS/LhKNHnb4YD32km9NauDU8Gj4l8Kei+uXcQn11CUc6uGQiS6jXDZzUafXKbZJi8w3z4x75cnYkaQ7IBAK9gBL0n4qLG1Xr/iTLQbEiChfrb9aXc6VjHulZNEO5wJNPprjrxmdlP92y6V/QUufgAqOL12kMblS304WdsqvWY+uFPqTO1WGs75dvcYKSV5wRQq17q8hmyL9vi5Aput7rKK8RiqpnOK3RwH0pUoXyrtR7gHqZ2CPRcQkaJPFVGFDED+aXmHHXLTQG6TV1vMZs+4GZu4Quj+kqi1x+N94csvZG+90Bjl0okLix/1ystiD24GHK1R4e9r6G5J+sbVKDpNwg2y3WEXP0rhR5XXGco66mLD1rI+xQg=
*/