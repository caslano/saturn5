//
// traits/set_value_member.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TRAITS_SET_VALUE_MEMBER_HPP
#define BOOST_ASIO_TRAITS_SET_VALUE_MEMBER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#if defined(BOOST_ASIO_HAS_DECLTYPE) \
  && defined(BOOST_ASIO_HAS_NOEXCEPT) \
  && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)
# define BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT 1
#endif // defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && defined(BOOST_ASIO_HAS_NOEXCEPT)
       //   && defined(BOOST_ASIO_HAS_WORKING_EXPRESSION_SFINAE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace traits {

template <typename T, typename Vs, typename = void>
struct set_value_member_default;

template <typename T, typename Vs, typename = void>
struct set_value_member;

} // namespace traits
namespace detail {

struct no_set_value_member
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = false);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
};

#if defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

template <typename T, typename Vs, typename = void>
struct set_value_member_trait : no_set_value_member
{
};

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Vs>
struct set_value_member_trait<T, void(Vs...),
  typename void_type<
    decltype(declval<T>().set_value(declval<Vs>()...))
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(
    declval<T>().set_value(declval<Vs>()...));

  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept(
    declval<T>().set_value(declval<Vs>()...)));
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T>
struct set_value_member_trait<T, void(),
  typename void_type<
    decltype(declval<T>().set_value())
  >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);

  using result_type = decltype(declval<T>().set_value());

  BOOST_ASIO_STATIC_CONSTEXPR(bool,
    is_noexcept = noexcept(declval<T>().set_value()));
};

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF(n) \
  template <typename T, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct set_value_member_trait<T, void(BOOST_ASIO_VARIADIC_TARGS(n)), \
    typename void_type< \
      decltype(declval<T>().set_value(BOOST_ASIO_VARIADIC_DECLVAL(n))) \
    >::type> \
  { \
    BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true); \
  \
    using result_type = decltype( \
      declval<T>().set_value(BOOST_ASIO_VARIADIC_DECLVAL(n))); \
  \
    BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = noexcept( \
      declval<T>().set_value(BOOST_ASIO_VARIADIC_DECLVAL(n)))); \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#else // defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

template <typename T, typename Vs, typename = void>
struct set_value_member_trait;

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename... Vs>
struct set_value_member_trait<T, void(Vs...)> :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value
      && conjunction<is_same<Vs, typename decay<Vs>::type>...>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_set_value_member,
      traits::set_value_member<typename add_const<T>::type, void(Vs...)>
    >::type,
    traits::set_value_member<
      typename remove_reference<T>::type,
      void(typename decay<Vs>::type...)>
  >::type
{
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T>
struct set_value_member_trait<T, void()> :
  conditional<
    is_same<T, typename remove_reference<T>::type>::value,
    typename conditional<
      is_same<T, typename add_const<T>::type>::value,
      no_set_value_member,
      traits::set_value_member<typename add_const<T>::type, void()>
    >::type,
    traits::set_value_member<typename remove_reference<T>::type, void()>
  >::type
{
};

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME(n) \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_##n

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_1 \
  && is_same<T1, typename decay<T1>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_2 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_1 \
  && is_same<T2, typename decay<T2>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_3 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_2 \
  && is_same<T3, typename decay<T3>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_4 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_3 \
  && is_same<T4, typename decay<T4>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_5 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_4 \
  && is_same<T5, typename decay<T5>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_6 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_5 \
  && is_same<T6, typename decay<T6>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_7 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_6 \
  && is_same<T7, typename decay<T7>::type>::value
#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_8 \
  BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_7 \
  && is_same<T8, typename decay<T8>::type>::value

#define BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF(n) \
  template <typename T, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct set_value_member_trait<T, void(BOOST_ASIO_VARIADIC_TARGS(n))> : \
    conditional< \
      is_same<T, typename remove_reference<T>::type>::value \
        BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME(n), \
      typename conditional< \
        is_same<T, typename add_const<T>::type>::value, \
        no_set_value_member, \
        traits::set_value_member< \
          typename add_const<T>::type, \
          void(BOOST_ASIO_VARIADIC_TARGS(n))> \
      >::type, \
      traits::set_value_member< \
        typename remove_reference<T>::type, \
        void(BOOST_ASIO_VARIADIC_DECAY(n))> \
    >::type \
  { \
  }; \
  /**/
BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF)
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_TRAIT_DEF
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_1
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_2
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_3
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_4
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_5
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_6
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_7
#undef BOOST_ASIO_PRIVATE_SET_VALUE_MEMBER_IS_SAME_8

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

} // namespace detail
namespace traits {

template <typename T, typename Vs, typename>
struct set_value_member_default :
  detail::set_value_member_trait<T, Vs>
{
};

template <typename T, typename Vs, typename>
struct set_value_member :
  set_value_member_default<T, Vs>
{
};

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_TRAITS_SET_VALUE_MEMBER_HPP

/* set_value_member.hpp
hyIP1g9Aj3vUgFPQUfhQ8KsQjxR+yurFrm7K3qGhmeAp/8tL/UugdnM/IyNLIz/m0UqUk8zcZEXEJyFdesLSo69eQLL5VEln9vJm1M8iS1pi3Tipx8DDjy7cTKMNBl72nGIZa+UYK/V5lq40NTHR/0KrMWSGI6a+1Q7vXHtWtgc0PzQFkQpWzZku7XJzveUu6/i6JIzj4WhCYkLl/Evn6E0oV1i70EVuEYMVxQ3q3fnVD3tY/XI+AoqBoLYCTs67Zla7CuLeH33LR9yJ52+bgsvt8qM8HXwpTgSiT0335bexjrhdFvIMpYlJGlyEF14tEp1/fij1fGIixKfrfDh2hNu3X+x6/BP+fhjpGH3vVH5MPI13k56brjNkqvCpq0LTAgE7MtNUWj6Cdmu829xWoeCjEJfOX19fmblNsgkWM0iIf53JSdVUseCaFsg12MZG1b9IH4WqhXMYN1eobz0DGX0SqQ11yPVfWKi1C5Dxs685ItUkpXjgkXXx+R3Xrwl1dY7M+YUftaXaWyaSLVokx50tzePpBnOzTWfyzyhNFx49Wp5+q4J+l2LfH348yzHx6Mp6mJVO1Y1r/XA5eAG0+nlntesAID1HPn6ge6J2+215NssCvzYTgpYcl5enLbmT7G8r2NkxVNE8hyVHj1ZsCfAgVpy/BNvzIRYvYlgfm5cZaU5X8pEpD9kh20m3abQlpVt0ZeUBT7Pld6R6zKPISsSL6yaPL1gHsNd0a49zBWT02uV7aN3dHl6ilO1dMvtu64BFhIDnLhzZaNyjhvuN1wpbtmrdbReuJ12jvcKwurSObRwxS81HJ8zNrhiCxAQNhQxlzcusy04isrRF9NY70VERpcaGlo9hivG+cb46oiNBI0FtduV7y8NoxlfNPSXtnKqn+cey/DtnIozgT7i196xarCasP+d87pV2Y0BtQChJxUBFUaf9affTizww8xRnqsBEyzoVSX2pCR17U9JJ+nVHriSd0ZgtPkoEPpi/dHlooVSBDktgmIrOJdkXTXcccYs8mqvwYahgrqQqsSyoejlkOfecRByua0EysOSc6LBiiAToDVJUFarqOcQ+Iuu+fH45k9FcFAbuY8tjv/LeDAjeE9xdz9fc+nxBctFKFNfYqjbGPvJKcnZjXHBtPV8jvHtBbVFaVBVW7T7Etigot3J+WSFzS9p7N8Yb+5hzdnow5jzJmBN3haZ+kjRKD0eMJi5bQgIfBs8sjdw2QU2lOR5Kc+zTaLrLHjSZ2K+1GBTis7hx5Ab/yA1u6elNuo44XUc+XUe47rCDjdTlNNJujYigk5DFrdLTrLrDejZS9ldIVZoRQScgXacgi5ulp3urtR1ZrXQmJfk+ZpCqtCLeakUsh0AWN0lP8+sOO9tIVaeRgjXOLfJKzyjrjvLFtVy+Vb8cPk0ImSac9iGE+RAiITrZsHUn6xNOE80gJnt1pbhuw9I55CPk9utKnYmjn5bKgaXLMV6+Wd0j1Uq3bFJ2FNIeFp3mXzyLype3Zoy5RD+9PxOWHmAKMfmvVt4yKI6o6xrFCRAgCRoIFtwJGtxdg7u7JrgMFiCEAMEhyCDB3SG4y0CwwQeHQQZnGAaHL8/7vn9ufffeul/VrT61Vu8+p7t/9O5T+5zaa1MUM/zmb2H4bfsfVlaWc8pK/g7mYHxdHKDyXgVP9b3KeKpcqv6/h1XrUBQ2KSsrOGUnx4EnweTFwSoSKtipmoqpmoJjjIuBOkOxnrBIT1icJ0i6zVsZtBvKkeRBFQMtkGv/Ldf+DwvlAvPl4G4xCLkYhEwMQiEGIR1DnC8HaJFTS/1Ow/hGKgbj03u6VKWldCUMxjfyMYh/TTYelpAs3LfwC5UlM5wlUyZVjYPxbd3xnHOrOLoZPl+4dIUlrpaloKMmXAl1lF1DIVl5eMUSFpv2oX9+WFTJzOa4rrw+8ZpLe5H8DFXPOiOIptwljtB1jO2aTnsRJa+FRxbJ9PogYcv2fSaqftfPHPV0ClEqjY53GjTCOb6iOciPOUiRHAnfj8HJe7bH6M6J2i8DNt77xF8A1dOk1q+VHktJgw+bDvhK5fNEOe/6nWYyNGK7PY0RzbO/PXJIT/yMERGzv2mApI/QphfDEifqQRHos+nNjKm7de+CuLCmJojqusJEwtjO8Va7MNcJaeTI79dKsETnXkVTHGoNuKpE+nmoGEfULg2FwJnvy/NOmEPqVZ+dMx4mwKRIIjErp/HmookNO3l3tJ496YaYTsydfUJyYSw35a4mbPxpVG8eM/sv83nf2t2byh3eHS7zD5mjH2JlQ061akXnKAmuStSNzMv71hsckaymBkvX674qXTtaoq4/IhAUSXvHZvc4lYwZHypJFpft1r3SnEBVgtWWU68JGA3qroFZEp/LCKmcS2VPPMsS3jm3yp58KesSZIzYWM3yL7gOTHkFm+oVsmxF68lwrWltIMufq34phtnyBsy90sa+HJvYkRx8PHeFMyZjn9HILm2hXx+UD3X2lZxZijiWBv8SqPNhiHWzpFTWQb5YQaOWbBXf2csXSCWGhFik754MNLYOxDe7cs61vR7zQmIEoQHkp8V8OUdj6rKXJ1qo+6vQ222qlXonG7KX1IvQO6LWZERkqEyUW2oO2d6WeSy0Sj++9I5TJVMl++DS3Ns2kevyboFodfObGU3qpoUq1Z/iW92xdBEjziIdkDH13nIn5dR+VxtI9kEsBLUnkXt3/Gb3ATeEs+fnxqgBXPRG/EGiO12yl2b76GYAwBf6VXIob4f78uRBvTsitFdym+Zy6lboweSJ6jn8mcGXKOgH83f0oV+GHMNDkR/l3rH9JB75QTTEus3/peSjYg63fmzztvXFywvXLzH+uf7h/kl/dE2ZuMi4yWqJa0lrSQy+C30Ximn9zj6kt2227XwRUi+9yiLB5v6ahqj1x9R37u+132tjPX6cfT+LFR0S3y7dNthu3Sbc5t6m2Ub9wPpFOd27vH5OzpmpORmiQrXV1aXNXN44Jz+W0q4sXpSr7VEuBVeVZn1/lYKl8qHcMIttInGs2Di4q/tT6KDlN1tHBfrC8hmwo4stpbBC7szEgRWCH6Aw/Z3iMV6mcJDcOo5HgXInXnlY1+bbJ3vdr6lnu7itpj9dc/Efp9P8GF8W5RA+Tsdeo91v7ki8h9MSvonJG59i5JXMy9MkTnyKktslu4yNGebeyngFtBjmpsdCDJMMDtSGU7tidHlSOb0U96IHbbfCTZSJQkR7gPy7fpcdynwH5fdKXgfVzUWYiCX0IkYERLaIBLEqAqYIPLMCYwV+5nPC67rBcMIWvyV2Iuy6fQfrtdjmTvr5IPBEAfqWG5ziX+Dnl6gxPUCTODk9TpP07gCW0JcVPCnJ3Pbg8iQA2rm/kQCTBD6JguPP9u+V/Z7on5MQKJwHCnBposDkXOvQekkYI8Er7MR16wJDpbvv8tavWVFOvhPROCp9/bVt+YXnIqLkJSPqdHoSwwsKvvRIKRemZB7HSeI3qCeZCr/zpfmULb60fMxGEO33/SjpMWTUTyIapKj/9vIVWUzsqNSF94W39guIj2BM+DdOOvl8u/0k6+kmPKV3TSfvtdEoWlMZpI7Sk6TzA8ZBltPd46BX073sIK3p/koQz/SgC+jz9DCJLYYjFN+WwXFX3ZbYcY/Tlt9xX4UXi9+b5C2ecSDZW+ys9qw4bLeuPDWUeDdaImkXoWSiIcVBxVEG1SCQ7fRGNZRhesthVHd6h2wUlD9em+iUP1WbAsuf9Uh+u72yvVKkC9AEJPzFeFxXtg//eUZnl7+fl+x5oXqhymuyynxK7zX4uB3Ca/Bg9JCp+70nticlIP8ZexTwgZVJmTEOXYO01zBRmSQOG6g78MtRjbT/j6OMRnj9TNxc742jvHOxoDalNrNPokhiIDk7EPSenNVsFMZjDB99y2PdnsRnNYegdegbhSlPfpuZzc5Bpy8L40hSAzHsq6CySk1GzBDT7asGF3dD0ZzC+MNMWUhUoqDvy5XY3pMNvMhWSe9nyZbmShor4m1Qq0hyHi2+EwmmMqrxmBZKHEdEX0WDdnnuyNvQFPLlaiI/lSVVWjIIvjcYcHRVqQl/vZxsilfYwNk2eeDozcAeN6ng4CkeNy3miR4HdocqkJeLj6rzGAclZ8ejFYatWmPEobTNfyd/3fBGwSPUkzJuU6Zh7DvlF8+OD0vkaqc83ygHQECe34opHZa6Ccx+A6O5cqfhM+Jpq3j0ACwj/MLOuFUH3X5DC/TCRxPtcdGL084w7JupB+0Qkp7cjb8eO37woFusJ5bQOI9mzr3KB/wngtC8M2jQbemDal3Gxo+12ylrvw95FmwEZIqxO0PK27pfvhkyTZKwD0VZA/0r/Ev8o/0T/igAtEwJ25uM/pLlEeeR5pFZkLZe+qH0sIewhDCEcIRwhdCHcD8xPDE9MVKn/2JQzoJuWfwYKCbtbJzTqEiV2fbPL1HmKxbeHrljkuUhHuBpiNtTcCns2hJoJ+/C73ktePcWPd7aJvHDX3K7OAEmCp04p2E1m5ZPmGfGNiv81iv8ziZ89iZ87iZ8fS3Gv91qGVa0QS3F2q6qxZB0lUbONHcThoEWJeqV9wINnNo2K+/tlknLY9ySsiCk5Zn/aIW0PMotyfiflfaP/lnxbkmQfxbQLRay0lIW4RYrAmlhWWnhM1+Z9G44UXNYmYQu+ZbEujl4uommOKxk1rQAYfYrmaf/yGolE7AyiWg6UeNeQUO0cErRrKARL5H2OpigzLaghKygYbjivWrilFpqQXm9gibnhje92ILy6Io3vdGCwrxEahnmhooFIc2fbkH58O/GZdL8fwO/rKClLpHSWpmESbdgkruahNH9I2eTMKt/5G4S9vofOZmEffpH+DaS2XH1I3DDIOKERsUL/yCoRp3iqVwQNNcxYVUZ6Qh0TVhgRTqKg6irdU5mAhvEjUuXC33axY0dlgqb56ir+U7qhceps+2QSxytI3uuQa6T9SN7pkGu+ks2XrnigvsrNo1g6my843oju4QJ5yBXrqaRPVbkUtWX+AmJ1WeakT32B58nwVDC4T3qINevBFtLxxcWCRPq1oQXOBesF8IXjBcCT4KbVNvYHwV7SHuIQolDSZ6JCZV13zDOv80GWrpOto7YM/9767f624MPIyVOkXHdwyiFo0rksvFJIyN7F/W3zwM2KdoK3oYWmvSVlqRrSrkM3JDKFe5RQt+cQXOhFOq6n1+vKJ9JvG/FnkRNuTdD+31YJVEWx4uLI2OYlUr7ffK9RUxtwJmfOSUU8HuWBR6sFs8zzAakO76pHlNoNLp8HKjZ4ujAMnxWdjBhdD18F228rbUvMhdA4NMta7apRQZJ7fotGNLiuJPhTWCY3RX5PXpwIDLcLMzn/RJWjJIlDf/v3j+5bicvkwp8MVgTMI6NGxAGVvwDKQ/Z/JiBVtVIi4i5qbrA+1Guxe956DY0p8U8z8PmdMbsuNa1+CxibSPGRJAg4h9d249v9AuvTT68amFr9mQQRQwHFvacmBq6NSBLRFJyaddk4sg6rWvtLHwWHvNQfRrVg0+1LIpYner17iRr4oUtVGoxJHD910JkHDuIsVz4sgX05EpU0RqfXgQpJ0AFPZ3ru2iwQ4cTWJAylZ2giO2V6BGtHrGwmughfzAkighumUO07ePbyOHoUTunvECshDpvi/W6AQtlBIXBNvF+mR/U6cobFLZ//qkza/Gy0QrY+a5qz/cpe/O1Ag5ZzESvOYD+Ca2wHXMJ4UpeMFtU1Jk/0ElwKSo2u7VLAPq5793ZtpNA9fzXPWmNroMhSA4Zs5zSqDkmIXxfdRy/PGXfA+ziCwpFci9Hd8V3AbsC1tfX0Tx6VxZXNkR7Ka81LvWDpi7Mj4L/pCyVG5XqA0X8xo7mOmZHNXZE1Y+8pUuPRKpP/4qoAin93CFt8vstwEZRv7OcjYDP++DJXWEOZvZSHS6QXZuCu7775epC24lXBxT5Fx+KnKr+a5YcJH0KXt1tW4Su5waFnt6tcrYl7Etk3zufHrXRQEOSFiVreWpZPBTWqzqXAy4vK4L0kaarHfNdbmcn3mFUL6gOQi17w5fCb8J9sLslEsU+Xk73ykpSifh/3D/vg0oH9cyq6odve1vrLEV04tFMHN3AeO7SI76t43Sfn8nQWzXV6XaqAGQfUFPNsct9IgUCC/hlqdfCw+bYRMVWtj4rgr8oj+hRhY4xLVc3di1HNCoWzpU4cINCGO5vj/0aJceeWO+FuC8EMcuvUMoz18vomwNom9m7Kl3Lm+XK4w/4a2aV/9lU5QKo5c2w1dfFgoVemZwCZ5JKbk30zexeBrs1X4qQvEonwYnGForOuwGXUs58gQvhc8ZrR+JShN4fX6GWk1CzSCR+PEeGR2CXUlFYqk4E+ccwNkNL8wvuUdfROj6jSfmpchMaGBps4ecHvrqf6hMi6H7fXyZ8Q/rlCUDz3ranjkYB1u314hYNEWQRGzyBFFhe9M9zyKvX3Cg90bkG3TP8yrqRaEkA2Fy9Xg6i6/VBITt+vNyZDyILFSU8UOyJ7/dZXm98scznMeUU1HocdDKbG8S94TeQOx+kf2xef/9zLeNNwz310a14tW9eQ5BIEa4v2Sny7LSBvb7S1uDZbMaswOzJDLOj/eyws3KtZq/jYPLM73Tldn5yyi/EWrz58hZo4ifRdvkpP3cl4Hoy2jf9mAPydmXZzmEfCPT1fTge7tI8Dra9tmk0mXBnk8CRPSe9tb9luh2eC1KxUEUXowlc5+9+jZNnF2/g3M/zRM3AT8JAim2I5hKE5nKjrgVBeaHsN5qtrclOhYpLrMOqo1/egTNjbNxmrBOJcZshaSxFibcYhRJr2oZ3UgksXIMnTJnbhrcQ65AlPt8lCOpl703rPMXCH6mcW9Yt8u5b0XJWlbloyeBOtph/28iSxkHFUH1Pmja8qjveV7BbKMWvmFCGjKQjkLaKlf26pn6/2iPfbcyDzCnt9QDgUSwg7C9D42haUVyn2hgID8rYAOyUMWesTeIGucKZAoCd0tQMXqPXUDY4wd8zj5Q2qEtDgqnMXhIubx4HbVoRrliYsyeu0Qtzac5yZh/b10Zq3e9Lk2dBTtCXnqTCKWIq7sz7iY2gN55ct1iddxPemF25vGPlUvKeYe+KhKYpYeoIe8/v70repJXLJCNIA9nNlD0KKw9OdIsp5sulz/L9kjdGzxBcgUJd0euqBrP3BxTt6euaNPmE4GhHdDPFxVl8KGFDBFdhBjgeYXX3IjjV/Tc15Lt7iYmjTZZ89nSJLfftL8HCCZgN4gvka0vROIwIodye5l6oOVPqxA7JEpOjcKSEpEvI5hWfOAZBwn2Lpmb2QXlQbjjObaq9DveJnOgs2UEsgvGONziqW8WicMWJ4ETGy4k6GNgtvVHkMdMKE7XFO1HpmDltwr6NA2j4KY0XqRbvgu3Au2AScBpYDzwPFgA3g33AuLBAGFZ9rHehN1GbYrtRu3y7njHrGlN1snvGaeJp6mnyafpp0inJHs5l8Tw4GEzhVO3dgwhD5CMS52irUxZUKYviZYrrpAINA+UCdSEMbuktSgnKCaqaSpoqJsVuYB3wLJgP3Aj2Al+C8cCxYFXwOJgdXAl2AfvCfGD4W/mflT5yMMi/
*/