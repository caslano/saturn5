#ifndef BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP
#define BOOST_METAPARSE_V1_UTIL_UNLESS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T, class NotErrorCase>
      struct unless_error :
        boost::mpl::eval_if<typename is_error<T>::type, T, NotErrorCase>
      {};
    }
  }
}

#endif


/* unless_error.hpp
mJzkwdQ/YAymVkyyxmLq4umr6hpbk5zxpcZiquKNx+NGpRqzH3GTh3daz+GR8olH2M+aYMogVDTMX7qr1yPEFUzDE7Sg2WIVm6HSNF1WJmRCqDeQW3dNeYCZygrEkb/eD1h90KsHs52xC/+n19Pg9SLl9kyv3owWq5K2/VjQFpGdLKHJu2IZ2/1gY6zsk5SROa9ndgTaJfcP5N2wZhBKgq8N4l/b0aNPe0b8Wj80gXd3XpHAVV7zVpyrpHCpQ93S+T693MrGgVBvvuPPb69ZqAFO3kWu0/eUIp+v3luBH6i2/VQetZtWLdHRX7k4y6irF2mzhuZGOq1S3T9wosSRFNXp4UHsdDFpuVFiZ4JwZvBYAqyw8AACHa42NIlUYCfFysoGD6tE6GlmnjiC+uKD2vWv6vryWK5RDqQB1RVEY59YCDe6PZzzsm7Q3QS6xmmHp8C2rmcXNuQzySnroeWIGeYdvjjufrx4MVzEjLzLHSJ6m8BZdt9xhH+7j13yBV1OtCAIJvPvjsRAHcAAU/7vL6IUPCaD54kzeM8MMGXUpEpRwv32ujUmbUS7hFfZTSG8XXLUyKbShsl8iknnTFmD4hbzpfciXpBahG74lWP+grAm1V1KCVb9e0V61FC2TGqychSOCPKlWgqqagLqvwl1lKaAqprYo8ujOon2Jiasw1Y8Qao/QHorzreCWV8xssHI/YJCp5PyK1HaEyC2
*/