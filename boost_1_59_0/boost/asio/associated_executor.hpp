//
// associated_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP
#define BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/detail/functional.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

template <typename T, typename Executor>
struct associated_executor;

namespace detail {

template <typename T, typename = void>
struct has_executor_type : false_type
{
};

template <typename T>
struct has_executor_type<T,
  typename void_type<typename T::executor_type>::type>
    : true_type
{
};

template <typename T, typename E, typename = void, typename = void>
struct associated_executor_impl
{
  typedef void asio_associated_executor_is_unspecialised;

  typedef E type;

  static type get(const T&, const E& e = E()) BOOST_ASIO_NOEXCEPT
  {
    return e;
  }
};

template <typename T, typename E>
struct associated_executor_impl<T, E,
  typename void_type<typename T::executor_type>::type>
{
  typedef typename T::executor_type type;

  static type get(const T& t, const E& = E()) BOOST_ASIO_NOEXCEPT
  {
    return t.get_executor();
  }
};

template <typename T, typename E>
struct associated_executor_impl<T, E,
  typename enable_if<
    !has_executor_type<T>::value
  >::type,
  typename void_type<
    typename associator<associated_executor, T, E>::type
  >::type> : associator<associated_executor, T, E>
{
};

} // namespace detail

/// Traits type used to obtain the executor associated with an object.
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type. The template parameter @c
 * Executor shall be a type meeting the Executor requirements.
 *
 * Specialisations shall meet the following requirements, where @c t is a const
 * reference to an object of type @c T, and @c e is an object of type @c
 * Executor.
 *
 * @li Provide a nested typedef @c type that identifies a type meeting the
 * Executor requirements.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t) and with return type @c type.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t,e) and with return type @c type.
 */
template <typename T, typename Executor = system_executor>
struct associated_executor
#if !defined(GENERATING_DOCUMENTATION)
  : detail::associated_executor_impl<T, Executor>
#endif // !defined(GENERATING_DOCUMENTATION)
{
#if defined(GENERATING_DOCUMENTATION)
  /// If @c T has a nested type @c executor_type, <tt>T::executor_type</tt>.
  /// Otherwise @c Executor.
  typedef see_below type;

  /// If @c T has a nested type @c executor_type, returns
  /// <tt>t.get_executor()</tt>. Otherwise returns @c ex.
  static type get(const T& t,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT;
#endif // defined(GENERATING_DOCUMENTATION)
};

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T>::get(t)</tt>
 */
template <typename T>
BOOST_ASIO_NODISCARD inline typename associated_executor<T>::type
get_associated_executor(const T& t) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T>::get(t);
}

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T, Executor>::get(t, ex)</tt>
 */
template <typename T, typename Executor>
BOOST_ASIO_NODISCARD inline typename associated_executor<T, Executor>::type
get_associated_executor(const T& t, const Executor& ex,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T, Executor>::get(t, ex);
}

/// Helper function to obtain an object's associated executor.
/**
 * @returns <tt>associated_executor<T, typename
 * ExecutionContext::executor_type>::get(t, ctx.get_executor())</tt>
 */
template <typename T, typename ExecutionContext>
BOOST_ASIO_NODISCARD inline typename associated_executor<T,
  typename ExecutionContext::executor_type>::type
get_associated_executor(const T& t, ExecutionContext& ctx,
    typename constraint<is_convertible<ExecutionContext&,
      execution_context&>::value>::type = 0) BOOST_ASIO_NOEXCEPT
{
  return associated_executor<T,
    typename ExecutionContext::executor_type>::get(t, ctx.get_executor());
}

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename Executor = system_executor>
using associated_executor_t = typename associated_executor<T, Executor>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

namespace detail {

template <typename T, typename E, typename = void>
struct associated_executor_forwarding_base
{
};

template <typename T, typename E>
struct associated_executor_forwarding_base<T, E,
    typename enable_if<
      is_same<
        typename associated_executor<T,
          E>::asio_associated_executor_is_unspecialised,
        void
      >::value
    >::type>
{
  typedef void asio_associated_executor_is_unspecialised;
};

} // namespace detail

#if defined(BOOST_ASIO_HAS_STD_REFERENCE_WRAPPER) \
  || defined(GENERATING_DOCUMENTATION)

/// Specialisation of associated_executor for @c std::reference_wrapper.
template <typename T, typename Executor>
struct associated_executor<reference_wrapper<T>, Executor>
#if !defined(GENERATING_DOCUMENTATION)
  : detail::associated_executor_forwarding_base<T, Executor>
#endif // !defined(GENERATING_DOCUMENTATION)
{
  /// Forwards @c type to the associator specialisation for the unwrapped type
  /// @c T.
  typedef typename associated_executor<T, Executor>::type type;

  /// Forwards the request to get the executor to the associator specialisation
  /// for the unwrapped type @c T.
  static type get(reference_wrapper<T> t,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<T, Executor>::get(t.get(), ex);
  }
};

#endif // defined(BOOST_ASIO_HAS_STD_REFERENCE_WRAPPER)
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASSOCIATED_EXECUTOR_HPP

/* associated_executor.hpp
eehJU1sQVmtPv+0ZE7t3H2wPhhNOEl0ugT+vy0eud1iin9OLufscE3gYBxkJPeVaPDWpJKigYIgNjS9ieme49aQuHMhyKK0THobmxN0e5oh0PQKBjs2ElYHIELR8IwCMEIN0VigJ4B5PX6XVvACepmll/FWvnZgAF1KkgGAV+xtdmzbG9BQycdXwQDMiBwg5vRMqMer21ETy8ljfnuJYMiFP4v+pWOwhQDX0JOiPpX+gb7WOCvLG672uzM9hqyyKXVa3vor8567EnIPNWp9I2rYdyPwZRnxvWkZaXKVTeE+HNBHKxlc2jAVqU3bWEEI/MQCivcKYHTPt0BzzrCB5w3spPzJK/kI0dgEodkCi4uRkKYCiQo61Y1UOs7h73geCjRC2J4Ckc/PWjcAlEg8UIsuYzuvKP8Gt7rU8JrWEkWyrdPZp24s7VGa25IxetpasfIKCcooSNIqkd93OTHnjwgW5MNNN6pNEbfgOxf4l3vWT/NBP5tcq3BLrqUG6GijvudmIBS/c9wjOmB2HfNPbOugXthLxT6QIyaJHSk7Sxl90eC/9+kWxojmJCtGOblkKHyci1n9cuXnpXDvWi6s+szX9mwJGQJ8ecZuRLwp3glwoMRbqSrFvurYkKlPpAzXC8NtnaDc5TkF7xReGdXcQCgoWqBgcq2gGrjxUDSobBSZ46J19bB9SEf0q6GHK63F4mTjfKo4U/WV7a1Iy2b3k6OlNTyqp6Rt9SCGZBAMeYhwWluqto/GsBh5hR0FJ0bETQPDAldmbHUs3V8rUACpDdEBnFiD0nGwYloXa6ort441N+q38zJwFAp7xiN/Y3X+yUwjoP0e/mQml9ZCh04PgDme85t9FxTxwlHswUVccdCB/IIJ+EA1czgGgKi24nrsPnVDbR0ZsNpgJ6Rp3Ds1DbDYooR7+BJ+XfU5XQl1G6g+NF7hItzIHbXlEZbOSOeQ81Px4/r2Kcz5ZLp4G+jmRncdXkZ5SRoU0P/NU7hmEMxrGKcG8uIDGTaJWGchCEr1XMLkUNt5AWt/d6TYGJZaqCWivLzkV2mJ3CtGOSKmY/IfapR3skLrt6aBGb0hwIDWBKn74V3MvUzCB/T2sKfICQHJIRwxQyE/ZyGmYSDpcUlgG/6usNVM1xhBEk/2iX29Hy6FtKsAfHvddDWLXL5+9GnClBF+NR/GOYcnltdLb1A86yYF5pTGRTDEi2J4OnbQAWbt978tlBZ5XKqugaYwieEWR6xIogPnNNwYf8jJ64HMopBPIbdwHSoP7WFIm8iegal7cD1nb18JQHOslwNZtVOTsCvuzrCsBXgP9OrXqMgiekGAI9mX4B3IiQ4SCLh1wvCYuSpUW1n9SZRelCsJOhS0t1Vkt08fnogkRXj1OVuKGv9CGMjOjxy2zNavmLZJ8r6Py/7jd/mNi+QhrsBbc8K4KQQyeqYc7Z5tyOXZTRh9J5ffEHAMUwQQc1rs7ONunwR8Gb5sVz6pfVSlzEilVbaWWPDe4Ol9PkWVCW5CAxoLlivNp/3td299rKP1BINa4YIS5aYtDffy//HjmO1byRTXp2dnfmjdiIdM5bwL2MZb9dFuJFagyK/W1POvGoEOyS983c6RcAcMVQYa4u+WL+T8ncar9DOoMkaAc41j55RTeH52tJvmjT6kbZftVCBmf+LUi551zla1NLORdvX6ufXLyimnvIkFCa475oJhra2srJe+nsUo++ASTYiHfdXyJ4iaEYiApebsM035Q6IqqZOwu2vfJYLKO3O33xRDLJM/ks70i4KKjYNHcJzxmT2t5+vjpmF70HD+N2dNy3Javu2CyYJZOTqtb4RgdOaLusuYVY1BDkP/myGkmq07SFnNwLlatxMp7xfCW8hX1GicAzU8/x5d2IUyrnm/tVRohEbng9zafuWu6Nu0ydiLEH/AFB0Y6vKn/Und6YCo5IwuAMcwoLQQYtJ8y3bY9mZIzeY9NVSPtYzsgF7zgRdmiy+HWCGJcCMUctUaN23NGZEueDpZSzz5uYYwLrqirFTclydsYPnDtB5+D8WpDV6o1UsG3fnF6TmVBun/vyy0FDZoUYkNE6qFlQRF0u+oSBy8Khm9u2BcnhSbKkIHn/9iZMyf9Fje2eOc5ek/eOjw8ND8caRlTuBD5JipqPfaVMqS722FoCKi9HUa/xy/bgV8iypMQzraAbQDFKu3lYUMMbvzQ70keGBz4N/WURKUc30DB2a0BneDNa0EIjq9vumwB/LkJV+Uehy/pjcLkwdAuLc413VVwG0oua6zIL7KQ9mDN3Kdfnl/2Wyfn2r7gY4j8KpPBGA2Ci55gAfg+qH4obdbHpLZ0mNEZjTrDpIQyQkpdub8mJZo4Mp4o3aLvN+7qOdWNfBWzhsWBW9+31/Gewk7WqMszP5jtQsX8M2eYlSqK/E/urg1KdAnX/HuW9TyNh1VhKE4BIlhyviD4IzypjoZVD1NGI80fAUFo9Mwc3/QYBtR2Zu/tzDewNlXf4PrsOIGffxGMr5jBiDP3mDjUumIToYF+4uDKoB4rjpM/8NczE425WaB1EufH2ceZUlGLRRGf9Z63cVTeyUlEXKK4GwYGM44ZRS7SG3pY9U32yXvVBPvZfrZe5wJvnIl9mWe+5kE1TJVLAomf0LRZqOMflZ4gTWyjWfMo/jPicsBbB5E+HnaZvmi/gTiFdw2RX9s1+nA3SSkzFgpZi/+ZZh1RqBfrJm8xiUorLou2cnfvbWH4hJz8S+cHix4tUXz0XtGSv6cPzRwnbk9i9F6buLcUHnmxmTO5Kshvr/DPXajidqmsg4IWAD1+EX08w9jjWhhDfXS9Dw01kWXpG9dxdudnT4iqFW4AHkckFylTFrseUslYGTsBQRmyDtY67gnuyW4rj8dztXE1zw0S9lH09D9KW4vJZToLdHT0jK72rOEVCr3ht7nSAUJrOtTWJTkkroGws+sW61ZuvA60h1krpi2j45znQoVf1OovPltafcKkM/0Jfi969C+KNA5l8Xl4TvzHbwWf3XW4IXjwUprdvkc++B1IA5Huu2qdxGMu0py853m1vcFBQdjJ1TH2GlhOJhylnFdhEpgHaXv+rrs49MdzIG7u70VCsH8fl0CIbgiI0qbkgejeDADbHnqBt6m/n+4cM2SXpT5mnFfhz+kbvqBW/oiMJReJoZis+4uTWemoeCFD+EUgM+Sy8srJ3EtJH84yyk3t5eWQnRV5JSVg/7nwQKHFkVRId4PZ9mO1Pxf2SWLcxl/FFEVoLK+XH1ro6yMWwXtDJ7yr4JOJ5kMlEK3igyxHy7KPd8k50ixxxHovidJcZQGMkG2AMu4Jfwr9G9GmRVeBgfLn0EOQX0MMoKrII6OqIedaM8qhEOZh7u+O+YFgXinduxJ+VlFWLi55ESQCU0enq6ipGTnMzs2VBSFOQx49VKrQIU/1x3RwPMP3kee9boDRSv5W0pICowTMjSHShVVs4wcrQjnvD2dATWeI6xdeXlpqmpqaMiMeSEbUj/fcSw9GXW+JG4a+Xxv/GeJNf1Q6I+2ULOGEw7HaxzUE6XOEAjDqsLC0rOzs7NyHsouTq48orcN6B7z79t3bfTbESC8iiAwGA2Jir3/m+ZGA5JapJ9gvY7poWoMK0RoibP3KCFw0gIQiRHZ1dFxMSBTc644xgO3nEzYpWrn2EqP4HxaA6X+zoRJwW5THcPXp8QuAAWhUbnIEu0NAf1Wel0loJQOkLWRkZCxsbGyoJLA9SxXRQe6d1/KBX9//k0VIgILjRUuv9buq9wEC0JeR8+gKZoMFh2GV4RdLBsLCwmgBxaDPytCxgCBKCGm5DT05xGqd6wm39/BK6oDYSdZQmn8ayU6WGq0beioixYaFkfOlcIbnltbW1qNX9JEdhVLK9aNG3wjvCgA4j3lEHg7YhAhKCGZMUe4dsP19UR/SUGiyXyjCSuOJoDF0g0tDUEGgQ7BxSKCr0zVn6scby/HmKb14VNm5ZggqdULXF+o+c64iRe70r53MVa5X252tsdmAFv9sxR+Mhh9cYS9B+tvgZQd04sA0MGZMHcMchMDIfsL/rEwHxVzVWFahSNxWhpEEBvqrADv4hhxbtTLXPEUdyG2Oa5MWNzIy0nJyciJ/B2aL7CZ0JQSmmKf8DvWXBxZ503stsgMw4ETxpIWOatuLGUck1IPbVxGoiH5hWdgHpH4thrquko5zV6vT+5IoGuetVuaT00DDd+UjZlkDMusegVEzdHrcrihBLMszQdT7wxXQq3VAFfOcAbS6PO8jTuAkYibnzhxCBWNjZyFeQmDQrHmMCxLhoKEhoEJz7bNEalNLfgoLxuBoV0v0moNC7P9bFejAhS6X0xl1i/d/0J7ObEBnKjJ8W9jJyZpfgnu/3qUgxv4zrBcE7r9pS0Mtz2CUX2hU8jXDrlWwCFlozCku4bDUTYIiycQFznIblTDwWbCol/JGIruwBU13++RvYF/cvOk68jzHKb2Q5/GmLwVgJR8LcBKqX3S3Xnfk7AeScxUWwqN3/AWeCyXSzZqeGoUgJvgkutMjpToiyOySqsdhBczgYKk2tFKWkK64l8kr15utXCZkMcKF3tifn/4foTLq8CJO0+0fiLYutUJAfFYkWJCYccul2SKQXXC2sHaz+RQalYtGuUmU4FE2X8O52oKC3KzfchtqwpZE8KlrXeNP7LeP0h61+mYL2zvJbv/o8/iH0TlilMpp+Hzr+tsxdgUyMP+n7yetX6m3jUnN4srPgZ1aDZLSwqDTwm6UnWHTNawW4HOGOfRFCVzgzjjGt90IBxeewyaSKNaF0wuuFLb9jw80m4zG1YqBDbv69UsgBgXFXtPC9gtXvo6syp5WacgaT1KiGfTODMFEbHfKnVoTdnGEhTd4x7PiqkQVgbuc9lcRjrIhcsnoampY/C6X5yr9i8T2y2QE2nHiZIrjWHKKLXSZI4Ll7rcXBjjc1//0/d4riuOqhkR7vDZb7Kap+zGg+eAIVmcBSfnwvpH8UWDr5kZm/HscY47yjX2fh30FCkWBmIMxsXhcdbCLld5tx2fhQaSw2BtnRjHjo/XlTvVWOt8pVjrPIVY6jVOutV7L6G5ukXNo0LqQC/RBrhYGqCdpNqjzHYVoACQR8b25mXEJFIncBy/JrAk0zKyLRXmuVLgjYYAoom4l84JrM4Hc5zkWb6k9sARlVpm375D99Yc5Bg+QsgylHyULe8rx9/mjvsEqmeO+AewIweBDdQVUAkLQeyH7GwFh0E6nji3KfCqDBXOWZWJQAh405DdIoTn69fdnci1D2T9pJHgGJAYOmBh0DORvWPISaWRugoCAI0j2nL5Iskf5jGtmNGylKsxc0yoFwemlHLcW4KkwGzl3hW7C3A1oaLS3oKTXdfPqsyHJ/xX5e5n1vFi5xbf8tn8/orJ3zPXaROIB8v85W5C2jHAQzocgOATF32zJkR+fQe8XlkOGJ2fmZaFl3/7WWHwYEys7zMQoQxXeg8NV84qBPV9ATWZkYqmkLQkBVBbx6S1dqges0ltesjcSxhBoymA0eWRqWgwMHWTaYHL1bKxzuArn8Rm29Msae0s0LOl5Jlby/SBAsVNMQlBHJA9YLgwRMMGhClp+LmROOmwWm/EjuzSAOCvWijBb6+pqKt5RMPuBepQj8l013K+FJrgo8zojY1cFx6xCIrxLtrfbr30EcGWPbDpwVHJUyyH0Ma+AktEidKglV9WyV06wJtfRY7Gp6Vkt8ACJk8xVAac/09dlBbVguIAgRsvC7MPw8tenIOK6IB5C8z9O+edtp4yL0F+4ZVjNMjMsJow+cH3O+yB2gITTqq04GDJpEE6ZkTvo2fd/lx5GrdEWO3GiOt90EsmlWeYB076b7Lu+iFk0KyZUBu4CGfecZ2sZLCa0zKUH1dV+EghY+PbFxxMZ6CuIci9bVu4/+61lj42SsgwbuX0RunwA5HGWZkqOMgnZDZikfdVG+xhWudqyhsph9Cs7llCfRnN3cM1JicSTigXQv8U9hMLtWzE+qz6yECvMH8WqmlZVK1ZY5boAeefDkVifuwalVcpeKKmeLiEvq6wlqt7KlS9WpyJSmw4UoSDD3xwQst8ducoYUzk8aLlKYgg+NBqdfXO4NsGVfNmZa43bV6/3SFM32QEOtFlZsgSkCoXgoRWqfs3ScbXBdRiKGQOJbi+/OkrGyKmWotMOqFTKHD2SaTbWLWFbud5V2AbacN1qwjJtbVkZel8rtR4n87MODrEyIld959h1nTMjeVT6kdXFva1OS4phyIoQ4Cxm8wRAdG4/OB12tkKe21EJdsGH9lNsxHsw+YskkeUr+5bqgYkIOcoE/q/73ym/+wv7FNn+DJOC8qrXsm8GPAmZI5Upm7CM1of3hdRCKi9jUPLYdZ1ncvaXTP659RU35TDuMnMF0YzivGFurOu5xK7TyALmvS5Vmi80E3Ee1n1KqmhqZXq8uaErodmdMx05WXP32G/zyre/sk5wNu2usmRtZTtQBgsExWgCAfirwYWspQPPdhQelX1doHUc0JCgQxAQ128VcRrqWdO7Pf1Nu37hwKA+6Cp2fRwFeQjqAhW3nGEi7ygymf0TvTJLPkbpfUpgMTQBaCnEYj0N0VdJpuc/qAf9cmR8VSNikezShsnmzXXEGZ+J1O+lWNGAgABHAeGVEjJE4gzl1KBMLlD8nz6InRqtv7gNJ3flqrCIKxMQUivavIG5lysZclz6DtoOXy7kzEnJo1l552hyzkVd3jclgiG1AMl5TIDZtrrK3ARLiYbTZRuK8w6ve03mc+bl1JCHgZnx8FtsESzy6hJKKBIWSIqEq/cWbA/Y9TuObPtrRLkBxxoARynZAmjCn/FMFhQ8On9v6m6MjA8eWq0bZvGXSkdn+p1JzyJPzzeK5vMyf9r2KsA8BnfN/DpTYN1V3zEpMt916RIO35T6Usgl6ZzXozAyn3WXfNQJ44SG0YQKeL3ofssiZ9A2ww9GyGl8ND1ya5ixsCAfS2kBspRBsvSndv3E1ueMSBjzgmPaMYsMkthwzJX5ZNTwKtPztvMowyQuc+qld1zYrIo1aqocllM0A4/B0P3zwsJ8WHo0a0ghwPbEjUouOLjR1SnxPI8LrI97nTxOYKuELuykJnnFjDwLn+ewnMimY0YfGFf0Qo/t8UAZ5HG4Ws+lU/cu+XiQzcSpOxh6LzAV71baS2un0cJC9DCTLxTAupoV4YJoBsLKIn0okWn0dnSI9UvjSxJcmJ7bH7YMP5hNwEySyO/J9Ily2GhvLuh0AJxzxwUrz+TZ/2bR/H2H0gux4HzdxH0207wDEHNDZoFbxzXnXbyxL1JVtzGkkOvQkQagnokYCC9RKZwk8lni95nBOWl28B0uOfT0jGz6ssr/WSkiLows3xi29blydsrq7gsy9WaeVuwI90NQdnpZ0DIccuhLiPz379/xfzAoFxpSql33JJHG9bRIWS/X/LDVnjm79yXfPGg703mRwkKWfVtymvfMo3iLFyG02/BFUOXzgJc/x/bx72Hy+/aZBq/FLKfLz2WA7LaVxavRlxY0ZRVxxdxM5XK1xm0fzD7j2mphcRekTZJc4ZPgV63ira7Amy9lNu4KCvgeN/zeK1p/4GIrBjjUFc6eIxyRqWlG51cp1vSijDyb
*/