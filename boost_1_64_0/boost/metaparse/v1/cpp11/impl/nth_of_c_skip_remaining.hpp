#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_SKIP_REMANING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/return_.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class FinalResult, class S, class Pos, class... Ps>
        struct nth_of_c_skip_remaining;

        template <class FinalResult, class S, class Pos>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos> :
          return_<FinalResult>::template apply<S, Pos>
        {};

        template <class FinalResult, class S, class Pos, class P, class... Ps>
        struct nth_of_c_skip_remaining<FinalResult, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              FinalResult,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};
        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c_skip_remaining.hpp
T2wO4elh+nmfRcI3VeGgOFp4p3smJpiPTSUNx9lDWkC8visnk/kuv3N/Hg0bisO2m2PhhqGRMHeNn+9apfTZ9WO8g4qtbzvmu8sjYaT8PyseO/HzZ/X9+9ZIePdUJKTfZi0zq75dfueBT4MGys2NsPF99hsVwkRx9dYO3z0TDS/OlJOf8WEqCT4jGsrAzRTzHpUUCVfC1SK9+fOmEG96hvYv86kYPdsxElZsiIZT9aKh3Bw+fzca+nfxnseX7EHZYIwl4cTCWLiHnQrD2xaVYBt77frQeipbfThKrLHPD9PFOdwbXVG+y4cvSuoXnQ/hi+P6Zdv5oIm1vB9joYP5r79ST3RTJBzey+dyd24O+0zgxe9/ioZnxEMXx7T+FOa7cTX5MGx5xJBhVoMVsbCUD7894rrN7d8Sc9lOR8JTad6nX0N+GeOC5yKh/slI6HiGH2HysMu8kSCHevRBD8v8KRaK1o6Fbew1l21eFl8PwbzyN8iDAfaVd46GW3HLIz/Y6zszFoa8YWxqnoFjY+EATrqzOwz5KBomvQjT2TKlunl9EA35z1r35KePYfnju5x3YjS8NDMa0pZEQpEC0TB4bTSUlquft3QfZ6rYuCcWtuKoXume39QtFvqZ/8HB0dDhN7FQX87XYqdxbWBdHPv4akhbeSU+2rLhqd5yoo9nOE2LhKZyc9TCaCiaF361jYS3XnPdXPa21rWvYLJ7tIvLvxc8q7hrLHwt/sbj4MqN4cVV+KR8NFSGLQnHrd7PUpNdGw3ly+CSKpHwuXPfXz0ans3rONjy4/ZIKIs3/+CzRPnwXVOxdRMMMfaja0J4+xZP7KvAP/g658BomD0WNj/Ln2x+vg3cro8Lm4kjmqJxJXHY35hP2U+zwt8vw6dFYcrvYbKfa2F6XXF3cohcfVX8yLNcj0bDV/RJf3HYOB97pUdDN1zzRB54xKe1xou71tHw4/diqjof3Ok8nbyVAhYv6cPfOGUe7Ck2TuyyWeVCkTBljN9XRkMB8V7K/IbQOFd8676/1x1n7HlhVvW81tXx1Y5r7QM5iUOzwNav5eYAHFkrEmbmioUJ5rI3r7EU8Wz1g9HwzTfRcNhzGSI/4fPPQ/jcGKZWcj/teb9/C7PKmFtpfzsL0/h18Rdi/Gdaiv2Kv+K9e+vsBdhv39hwvsFDj5+NhnvYqv90dhfLL3xpnHNDOEhDlSzppzztmci3k6JhPwyt0Q3Ov2bM+11nrO+Jj+c/8e9JsfCb3tGwKc7DO32W3R6hZfLhHZrhyWiYcCgWjid7L8xL0fB6a7H8iLmmRsPcc7FwGYz5uam8fV0ePCX+xOK9ByPhZbZ6Qny9vAo2dKDBhtOR8rXaURpFTo0tLH7eoa3OwEtze3KHXDms0ueHXEnRkBNWdSkaCdvsr74btzVdDXfwYTna4JIWYjcbLoCVL7a0p/6sa+RjJ1jZpi3+GSMPceTDxjBrmhg87Z3m/cWveXSG038sBaNwdHy/QsPanv8qH59ix9K4uLFY+/3XIaTVhrdTo6EWvN7+MYyAf4mjvKnWPJf0c44ONAWMvaMbDQUncsPxFqsjoQQ+PfawZ8LScefejIQPX7Kf5l4xACuOJsHeQ5Fwz1Zxhk+jH0bCfnPOQrd19vfrUyOhmzje0s7K34xIuFpcvfmK75lrHnk75W3H3B/CijOxsLMtv4ibgXz+yHO0TRKdNJf+xsfFB9Eo4vD0s+b0JMxvGAkLv5GnH0fDrlr22JyBGfiwNI19+bIoTSSeaO0O1ejEWWK2IT3jnItg3vQidMTT3i5Gh16Vh86uEA1bu9Cljl0ffx5FOgy4nnaGcZPoio1iOjOdeAK+XcnexUrjysci4Z0=
*/