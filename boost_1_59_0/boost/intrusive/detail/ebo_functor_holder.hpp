/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Joaquin M Lopez Munoz  2006-2013
// (C) Copyright Ion Gaztanaga          2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace intrusive {
namespace detail {

#if defined(BOOST_MSVC) || defined(__BORLANDC_)
#define BOOST_INTRUSIVE_TT_DECL __cdecl
#else
#define BOOST_INTRUSIVE_TT_DECL
#endif

#if defined(_MSC_EXTENSIONS) && !defined(__BORLAND__) && !defined(_WIN64) && !defined(_M_ARM) && !defined(_M_ARM64) && !defined(UNDER_CE)
#define BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS
#endif

template <typename T>
struct is_unary_or_binary_function_impl
{  static const bool value = false; };

// see boost ticket #4094
// avoid duplicate definitions of is_unary_or_binary_function_impl
#ifndef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R>
struct is_unary_or_binary_function_impl<R (*)()>
{  static const bool value = true;  };

template <typename R>
struct is_unary_or_binary_function_impl<R (*)(...)>
{  static const bool value = true;  };

#else // BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R>
struct is_unary_or_binary_function_impl<R (__stdcall*)()>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R>
struct is_unary_or_binary_function_impl<R (__fastcall*)()>
{  static const bool value = true;  };

#endif

template <typename R>
struct is_unary_or_binary_function_impl<R (__cdecl*)()>
{  static const bool value = true;  };

template <typename R>
struct is_unary_or_binary_function_impl<R (__cdecl*)(...)>
{  static const bool value = true;  };

#endif

// see boost ticket #4094
// avoid duplicate definitions of is_unary_or_binary_function_impl
#ifndef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (*)(T0)>
{  static const bool value = true;  };

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (*)(T0...)>
{  static const bool value = true;  };

#else // BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__stdcall*)(T0)>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__fastcall*)(T0)>
{  static const bool value = true;  };

#endif

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0)>
{  static const bool value = true;  };

template <typename R, class T0>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0...)>
{  static const bool value = true;  };

#endif

// see boost ticket #4094
// avoid duplicate definitions of is_unary_or_binary_function_impl
#ifndef BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (*)(T0, T1)>
{  static const bool value = true;  };

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (*)(T0, T1...)>
{  static const bool value = true;  };

#else // BOOST_INTRUSIVE_TT_TEST_MSC_FUNC_SIGS

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__stdcall*)(T0, T1)>
{  static const bool value = true;  };

#ifndef _MANAGED

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__fastcall*)(T0, T1)>
{  static const bool value = true;  };

#endif

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0, T1)>
{  static const bool value = true;  };

template <typename R, class T0, class T1>
struct is_unary_or_binary_function_impl<R (__cdecl*)(T0, T1...)>
{  static const bool value = true;  };
#endif

template <typename T>
struct is_unary_or_binary_function_impl<T&>
{  static const bool value = false; };

template<typename T>
struct is_unary_or_binary_function : is_unary_or_binary_function_impl<T>
{};

template<typename T, typename Tag = void, bool = is_unary_or_binary_function<T>::value>
class ebo_functor_holder
{
   BOOST_COPYABLE_AND_MOVABLE(ebo_functor_holder)

   public:
   typedef T functor_type;

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder()
      : t_()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(const T &t)
      : t_(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(BOOST_RV_REF(T) t)
      : t_(::boost::move(t))
   {}

   template<class Arg1, class Arg2>
   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_FWD_REF(Arg1) arg1, BOOST_FWD_REF(Arg2) arg2)
      : t_(::boost::forward<Arg1>(arg1), ::boost::forward<Arg2>(arg2))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(const ebo_functor_holder &x)
      : t_(x.t_)
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_RV_REF(ebo_functor_holder) x)
      : t_(x.t_)
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_COPY_ASSIGN_REF(ebo_functor_holder) x)
   {
      this->get() = x.get();
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(ebo_functor_holder) x)
   {
      this->get() = ::boost::move(x.get());
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(const T &x)
   {
      this->get() = x;
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(T) x)
   {
      this->get() = ::boost::move(x);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE T&       get(){return t_;}
   BOOST_INTRUSIVE_FORCEINLINE const T& get()const{return t_;}

   private:
   T t_;
};

template<typename T, typename Tag>
class ebo_functor_holder<T, Tag, false>
   :  public T
{
   BOOST_COPYABLE_AND_MOVABLE(ebo_functor_holder)

   public:
   typedef T functor_type;

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder()
      : T()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(const T &t)
      : T(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit ebo_functor_holder(BOOST_RV_REF(T) t)
      : T(::boost::move(t))
   {}

   template<class Arg1, class Arg2>
   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_FWD_REF(Arg1) arg1, BOOST_FWD_REF(Arg2) arg2)
      : T(::boost::forward<Arg1>(arg1), ::boost::forward<Arg2>(arg2))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(const ebo_functor_holder &x)
      : T(static_cast<const T&>(x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder(BOOST_RV_REF(ebo_functor_holder) x)
      : T(BOOST_MOVE_BASE(T, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_COPY_ASSIGN_REF(ebo_functor_holder) x)
   {
      const ebo_functor_holder&r = x;
      this->get() = r;
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(ebo_functor_holder) x)
   {
      this->get() = ::boost::move(x.get());
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(const T &x)
   {
      this->get() = x;
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE ebo_functor_holder& operator=(BOOST_RV_REF(T) x)
   {
      this->get() = ::boost::move(x);
      return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE T&       get(){return *this;}
   BOOST_INTRUSIVE_FORCEINLINE const T& get()const{return *this;}
};

}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP

/* ebo_functor_holder.hpp
TN1qJoCyahKhlwPqaK2Cs7tzEavuHVj3kDc7s90j7IT9sly7EigxsyRl17kB20Zn5m591vNqnzb9A4F89ejiWlg2Gtf+p/a6TEMt/Yx1vZUs30bGLF2R6uosa99wlGHJZdmfvUid6MVrcYGAXV4ns+3k9KENYje5dPPlCzeDkh86x3NHByRjvfWnDIvYq7aXktWDimQRDyGWUz80Dsd2M0p0ciylQoByKK0j70AwTUi36MT4nzzhMclAw5XR+XD990KQz9hh4NcD8laZeaWS+nOUMOYbokUTPALlPiDiGgMlBeKDf6gJ6CfFuc2YTjeDgfU7fvjKobj2ggL2aI77Nw+9cnqHxgRg/jEHcamw3LG1od+619VfyAFB2ct8KenMq/CMNUtfSgfNz5drwQzULcSjtSxVqrvkoKBOy/rk1tCClwyA+pp7zIpOoWFSyuPWLMbnAq12gz5TUzQXEb2/7ip8+ic1DWtXBWGs5nC2Vn9GGkk/3e1/UhYzOBPX+KRtDGcgFLjkIvEvHFvuvO+pCgi4HQLClTHuW/ZALRJdP1dZdYsVgnnX8btEUQ17M4KKJAUms5z3YAgDSoSJhV4fr42m7TlkWChjjQ7SQW7XC9FIajQAHSKlh/7+IUfHxMk2bEdW6ZS2oT3Vvoh+VRSTf/MwwIxzJ4nAOsEUYiE2w9CFsjJ3ERBNBYgOfDNE1srZz/3cYzT7d1nq4+AMnhfYNreQpgZDsOpRX1t/1kH8Pstu4s0oyCF7ys8xqYp4O40tBx4bWdPU8R6IsuwDR4BxOU8px9Ia1RgxOFX6TwUgQpCljO/pEuEiyJt2TsR+BhVN8SUFfriJpJ8HQzM2ARbLO2hkHO01gJ+PaXDT4r0YVKOy3g+8BNRj+tpQF8sqDHKe/242BwdTrUQ4j84H0dmKKOKwW4//zJSccpdD0+iZTdKaqEPB0M3H8e8u6pqOM46BuuHKBCKbILa+M1hxjLmA3QZVy6vTMEiCWYncfXwnZ5pBfpsLR2PQSareIPiwahbC5EupYYdNuLlHqBJ1w0AeQMoAuoYQ97wUoW91fsPmIKlkxi3i3BoTRUZBEh+qQVhxsnReu5IQld55Uh18RMpj84XaRgMbQUZHBSjkHLi4LibQWG7o59gUzWProXRWfxbe3KKFBMe0qizB4ftDCUvEjwRl3BOLwe6H+SZTKFPcAgLohFZ0yrJmPWP+0u2bpYFhv6e08MWD0/j1WiXXG7IDNPbCO/UjSMT3bGek1P7tF+7ndPxdTyqRRffIu00f/mhp3HyiFRIzfzZWRJNqIzvQRMHl2HpSJOSgsnCD8FpO4BVrQeD79gDVI1bT+SU8NO5ORXsCa92/YMj4b74eTxyAua1A7Q/r1uNkpIHDKuo1jsXzJCdfuOvPM0WdgT/e8oJshieltIhJkUtOqkgAO1BvlhaZcEsLaHQVnrtGUXOjMi8ROHRUWaTzM6gUTUy0lgp1E+vqT1ffIEaVzOCacuyad9RTbNnl8lHB9gtkhuDmxtxby+wInjv1Db1s+jqQ/xx9S+XRenpyn/VGPQt68nBmLtFyo/l6y4q1VywPlI9G/ikpS43b16H/0aF0uqM+HtrU8rDg+yuyosZ9m0uiP6dXbx9oyqxdenCXyXBchQeUdGsq85FePTD4sP50PpNa3EQUGOx3lZz45NAOLUR+oTWED3tNYMmjLO44ZsNyIssba8B0tLOAFyYn7OmSd7EvMzKUqkwES1gDV+sXWgwp+Gg7vQCodvsYwW4gI7zUYFxYUlOspKkvY18eOd5jk9XjuaRRjps6lUpehwtM7e2d64r0UfiEdhc7R6gupi/Eg733FNAa5z4UtcqIYviYmQYmQ/KC6s8/q4mr4uYMMKGwqC8KNHOPKIACCCjIkvm8jrzCMs5eWr7NaYf+hC+CM7okCBFiT9/Q7oIZT6yuDs+7d3Uy0pf2ost3k3iR3B+6ZO0RcybHjzGgAzjrsjij6WStYXgsLl3SEqYezQHSugIp2sODpu9oRSNQsxzcNl6T6XGeM2wnAYmaXNtNCKMYDtVkJ5fVHaKl06+x7Zv894kAcbx+9qDip7FTBOYIKCg1c55GfsBqs5GFlU7et2vJ/Mk8kApP1ZedddPQZSLN9XpM6W3riBM75Tp19aLpuQq55eUVSiFFZLRtF/yGS70Ga7nlSC+hWtTXdx2dQgFby+xmxUQMHxvbFgjubOblaGRVy91PR/neckKvIFfGkXJ8FZk9f5DRHFY8OBBDEQxZoS/Qe+Zt1ytu4lIIs6yKxp+Bn9JS9TPBDwOdz0/3uNE5JnMFsuuxjgRicd8clykqSVn6QBLDGOUut0ty6FZcNTKePaG7zWuzDqoiRNfFi5GfyCJ9swZwZQrUbahy7PEd9tDLvaKF6OSl7UmYa/Mt8VwZ/E7NB9iRrWt8ihWFAvpWNGPeYNYo+p1Ki65fp4C7ERG3dpKlpo5hhFzOXOftGDYYns6fRzAqqpPtkIesOJ6HWDnLw60rJ0yCnDrDhsrlcpWDcBCuLgD5qsoC27+q4uokT3HSqBVST8RPEEaYJTPFvF5nniANAPmPS+XwQ79yQ7bedHCHcZvLqIRCjRFZ6IXn0eDyXhbZMCAwbrBgc6yXaHuFMi9YrMrsWRicpbjwjgtmyJb+fOiLOwUzQq5BwrWFNEemfTB7RTYqyTsRizVj8zUcspfjHbERg/QWbtSQy6jzH+YXw8L3NOIbJc22HOEnW5jgmRyfp/1u/nsgJqeXfgRGrXJHS7IvdTipnSpGC9wM5GMtzehJIHAlnby/dEAmlEMFK5v4FPuEA76NeaKPE+lArDW4kCMIdH1gEyno8srQguGrJPdpjHVZUC5E+ADGeAuJEYUnis/0TO5SyeGZzB4O9hfE9gpvoRw0E517dAP2r+gcKzXhFgs5PrCVWxVsm+pfoT6CmF11E/asc8m+jmCa/nppdqbxbia6DiAUC1ROuVqnqueGkaV8TvvUxDD2OS75xD6KwkcMZ68SJdh/YEgV3a71YE3m/ZUUZRgCmijYaL/ntvjAdWWI6c/PVB2PMQERJRHZR6gTVNNqU3aNfjRfj2lobVFtazci++ZQdpLLzUuJ2ugUJhpqMV0ikXvKHx86vYkRA+CMElBgr5ieY4QUYcrsnXaxD46vkZ5dnYzJJjdmx+V5Co3RyXJ5iBJLdIaxLyLTqKejea+a9sEsyuNITpCgEO95HPQoCqyJD5sJ+MlXGmiSdrGNsYzOjo2+yZj+OGAhMGMOuofkBxbE8Tc5Ks91F6cDvlBK+EbJs0WrfNKIauPp/f1za9apP7zzOdi02KkhPoPCpMoVXsx/87rTV8v3J/X9yLbDFJdjml4Cly8VVwW3FcwRmPpZJ3t2ILtjUqt9Zbjbl9KecFKAi1jf8QZA+hn+ukV86BNU2MBWffAO1VJDMLM807j1stuf3DRNpWRie5rACDr4Gx1BcNU5lFEPKKMLNLbMglbZQ45uSQWRnhIzQJGXtygj0zBRT6S055hY/5jg5oV9bqnFT69fGFH/UZtMGwws2kE3NkydITy0O0UHED+13RAPrJgp/ChZDr4wwJsYvpFeM9c7ICHVYIF7u6dCkGBShRbwBi32C+q4SkFBheX4/SxSjGOM3dTngFRCcTedJhAWAlMxldtD8mHqgmwXbt61vHZYtOqPU1dzCxcPEpGxjUwVy1yf60/RjqYo6hJ7afYI97f2H+JudPTsxqOVgcS1e9hSxSeOvORwjFAZxLRq4b8pBvsy8zuIXSsPmIaM+gXsyzMfzq3z1vsddM2rgiqBnf+qyJjCmpqzn9slFKdc6VQqtqPxy+8IhQYzP9ThlA2FOctXbnrKz8fz/bEt6avBNm3H2XseP8pCpu8SCKiHCnOA9h2zweT61dXEQ0d/jBQQyyPTenB9HZtGT5khEpN8tOjfkzT2xkpqgquFqR2N7Qeb2ArI/50RzrL96Yq16dd4omoazVH4J9X2XU2IxNy9K+f6SnPSJ7Yico7qxinWni3F4JnWQt95Kkjs1t1PnSbZ3rdTMZGY6wxY1a8tAlnZspc4tj6vn9jvID8HabU0VpeeUxwxGU4pqPXDDswflkYPBnQWO+Kmw8HYYbZlPRXL6s1+z6f274aXCyjrEnJ7Pmc3+XNDe53KEJC3ue1Kje9LYlw1yPYlS6/OQ3C0DigxF7u6EwxFKPRtUWF6kxnR9wnu0ElPWIHmTpKzcTwOaiYc6Y5xXLyXYS+GOOX6utrQSqBkZjnzkAIriorNfHA87xUKGEV5RKf57bXgequ2UF2wjEGFJiCymkY6Y3pyqmhD09pGUt3VgOaqG7YSedXeaNGxSCAh1CususBSSxCCNu8Qmy1SzMf0nvJQc32ioix5n0DLZrNThBw3EyJLLt3BkW1grX0wPJwgFrs96LNvMcaYpmtan0GUiiPa58IkoQIQ8IFErd/dbh1SSHkBDXKR2mwd70cFWl4UOM2q3GL9lry/Hm7GBU9gHyQchTIwgxy70UvFWUojK3chjZNlSFMTAdOlbjvmBgq8IzzAkWbV7cRfG9EXIo18uN0piSqcO6I9To+ii2Ny1o/XSk5M8or9NZ280eSV8x2EPb+Wc/YMC5XWz1TSn/8oaeYGdUdJUrw6aDvziqjP5O6JQg+t0u0de6HzOiRxSdayiWhfDFRSWEfFjSo1Jrtf2bkXoNNnXNNn3kwXWVtG0t/lCZaEjkI8eiywSjcevG+RdIIqXDQGFbG6b3hAa/wuaqmNCDTLbkfPb/f1wqB8uXVKv9V2H3k0hrLXnsEE27E3Za7O3ZbCyAonKohAoBI6ec0R/hK3A/AxEJmDTUTVI3tYVH0R/2gJYbtEbQNdRJVfI8eE+vUIuIGhOtAQ5RnyWxYglwQzdUvBhvGMhbg5JttJvl2d1s92R14iIFk3cMzGltwk2amh1RRs3zRS0BVy9oCtK8Fu11py4h1bU9Aj6ofLQlIUQzLK7FZqYauIXSLEZc2x9i9P/d9G1oZVioIUFkhpe6nSqOuErPxT4CZ19DO8IM9LQsvh+wEeDKPdUM9rq1Pb8syykCE44MRpX+THk3gChEWIgwZcPOBheMqBBipw6enKjnV22yOI+ADdMA2Y/nsUQAHPesJ+bC97128WCJ1kC/N11RG3jJK86woggUvgrS0VlRjjDiLvZ6R9jUKg00t1uXCfmFPoGkSIUVIciMOVVmhttqAjq4hrd18W4oPeUJMZf19gAyhWfFZ7jUG0Gl9HapaS7n/2XSgaqkSvyxIR0qoOcbFLQrdoKymfgNYTb8aagFjqSVmUgqbgeTONaigWmiazunu4jwHNj7F+oldoQxYRTzcJa1ekP7CqNP+yhOCSvQRZmVV6yrLUJQ8VToAdedFQNz1dZ+KJXql5G1+13ZveJs/7Py5Q9UWt7LKDRhfnqafqXlLh0vNXBELV2kHJ2dLAcxbqKeI8TyBMxEUXYf92QsGkRQEwZHTMM4zo3HgIKVn7Qo5/A8xBQkNlyhGnMjeDIQlokxMo4RiP4Gg0QNBJ1ALKxiM0ax4e8m3ee3xxeMFJFSShciOQx8YcbvigkGG8Es21Hu6+KddLgMy2Aj6397lDoQzRj1HR+2V3VBw7YMLmTBBCJDlyx040JSVjTTa+t7jXhA2mIZjfEEGl5weqfEsTa2ecy9TNw7GU/CB27FyxYW3S6nuXn0yyAuVcJxZSu9mdo4umVR7kfytKoKg7wPosrD5LuA0Ns5yk20e+WXfWZU8DdgbGJcWI3cjxDkLzLwhFS+cymgquoWxaewfo8GyJMAy4V+FDgpJcXxTzrCwdqYT29m20K6oFbd0WIIK/2PRI/y0BZFtnco3c43u7k/U1giLl5u2iVPrL59Dx9m28VwBuxZ1nrBApuKkklGWF5ILJgQOy++3QxikiZwD4sdCfFWnA2BNdC6MV2SjBZoTiY2uqFzJ3lMIM2w/NmZHTAdbyJHSfqtlpcSJan6dJQRb7Z+f5odMPpDT1L9t50txt7VNbBQuvValmFJCuJinigokaJnZsIYiToFYeDbzmMsLyTgYbrgJE1WaJW6ltGgKjLIQrQuFUC5JIOOAOQzA6pmMgeWbTCR02ZaW5QCSXLoPQywR09vUJ1upz0mZ4KURR+lT9UDb/KnVHY0GHqjRzwXWfwbftjsUl4TOgjEvckwyWgNaCgqpvtSkGSiEY2QOOqekPxKUl6u4/847bzNCDo2ZBPNpF6jOb3uveRQvxQzvn3ooLSDRkOOXv0dCjowhrZTT2nAcxbuRyn6Rb2eUGWmS3eli8y2P3zhbrfGlD6uvbHj24y/apzPNqGg4v7XxWAxe+rir4aphMy9eoCPNUem7qz33V3RY+T6abmx+WWQFQjr11xo9WCRDbFyq31D6OtW4yYAFesshcqyO2UYGNa8wv3mhFeNz62C4/TdSr0B38oDEzKIIxwelzeH4SWAprmBPFHU/4n4fdsiGSnzX3hSAPYJB1IkIFHW7a89jYvJtkE1malnqRClZmO71yhxd8b5bLfanhIIQwscVyQeYIYuP8a4NoAAyjL8tjze5ZlZcUffbu0WApEHNStCcuqPb3w7mWQFi+SNhSFb3qYi62qSBt7HAOSReBDVdMMPZCDQZYQeKwygGG7IoAGdhOETwUFukfcNzyYZgHCr0GTnl578Wt5H/AgeXdesNEc3PBuK9Zz1OXWw1XgcuyJNp/UgeAREwN8kOWCIHpxwLtqY156FxBnXhuWXZNlb8dWLi22nrrrg8Z709I+r549SWahxkudCNrZWkqn3UcX4IPobZFXYGC5D+RPYyXCa9GtzQc1TQPS9VhtHmhdLTgaSK7YYjTcNV5fegUrlj4YAe6YHpBbH3xho0B2GaSZwyLsxbiMPAziilFLD4ydbJ/pL3xjlPHZjoXVCBYaE+hWPjXiZBbeNjAEtpo47OW99f8ilbUo1x5KhEOB2PvXEk60gDbDpjdYpZ+6jT+tIA16PeWZ/8ILX0bSUY4jZ86hufjvLbzfQuQ47xVUcUBqF8P9TFwRtXACXvHa0XhaIsFEdOW4NbI3BmCrK17yu/EgT3XKxjS8y1EU9QJASIg6ig+4KwtkEumo0lmDpwoMESeHkgv6OGxW36DlpA2ivEAqGV3L1kDIW8RcLdk1QEzDM55ZChAnjPgPgvQdlYl07oU4HrUB6UPojL1Y05fy0I3gJMGD6A8k519MU3cRHdRo+5ToVKrrqMUJN8a8Cd0N0vNJkT5rNKX9MMnPieN9qUzvUfJhLvQ5QoSTlh5WWYCAhG2VEAAtXQYyvfBS5nNcUEgyRSNyUtanNjhTygFHbC+hdstpqSmuOoBrZVo5wL+laOQDSNaoSn6xsZebt31k0HizWZ1LhUlsdC6VaRvm5gt8EB5hGYnhBe5GuriAbzsbazGgO4i/W7J9cEk21G2/yHmumOtwXwQdO3nZn9Idtw1strQdE3r6Oa195pnFRdkz/auP+bLCr50eQO754CiER37YFE8zIKdxwAf9JE7uxcvV4oZ8sjncCICEqqMLdgPkz7STZ6eWOsTkDXJwdwfsAHI2P9HyWKbG914LFuvrYHXY4BUDpgDdNl0dKdK5/Zkn7zqUZAeHKkJ+mSHSDRxbl3FZmBuVo3fE1SeVx88qrJz+Ib2
*/