#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_IMPL_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/skip_seq.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/fold.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class Seq>
        struct nth_of_c_impl
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_impl<
              N - 1,
              typename boost::mpl::pop_front<Seq>::type
            >::template apply<
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type
            >
          {};
        public:
          typedef nth_of_c_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<
                typename boost::mpl::front<Seq>::type::template apply<S, Pos>
              >::type,
              typename boost::mpl::front<Seq>::type::template apply<S, Pos>,
              apply_unchecked<
                typename boost::mpl::front<Seq>::type::template apply<S, Pos>
              >
            >
          {};
        };
        
        template <class Seq>
        struct nth_of_c_impl<0, Seq>
        {
          typedef nth_of_c_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::fold<
              typename boost::mpl::pop_front<Seq>::type,
              typename boost::mpl::front<Seq>::type::template apply<
                S,
                Pos
              >::type,
              skip_seq
            >
          {};
        };
      }
    }
  }
}

#endif


/* nth_of_c_impl.hpp
3Dtyb6JUovhxKv2tJN45Z2ob6OS9Dk7KZ5N7xLV8JTu3G+vJpJNdPK6p5Jm81ZnH+2zxKiH3Tv6r6HjzcNacya6Qz+xGunyDbJcnd721+dzBTXh81FP/g99LlLjX+4xX9u4Y7tbwmxQcWbDuOCMMOt3uGa4/x8St3eAedy9rz7A351vz817f9xhzih6EVdlEWt19fDqwu6gBQA7vdQeny/ez4AX3seQTZh2pSL6fLzEGTjSa50ULx3SGSn6bkHEbyT63+4c1luU0o7FeKbW3pPLdr7p+NfJrrwPrRjQgdbG/6K2v9V0JVzPMKL6QUT/zXOtfg1Ov+kCOJZ8ZUgZ0rWbzrPU0FFHVfr8qzmWvxrxP+bUfB3ars6Q+I/w4BL1k4cXHp1XeNkKPfQyciI4bjdDzq1wxekZ+ItnYxDtfIBo6LZ8c7spGXnmuCO+z4cZ8lp9V9Iwja/akLD7a2xasKxdIDG+57GqPt8Iei+bb+Neunstz1+ONL/ozjgD64osyCSsRX0TzDPKvBeujfNhgk1/A1F6GluT7euXHqEfuyTjEL47Q6zXxCQFOKMrqnijWyzc4tFoPzc33YvxZlxUVcEbwR4Y78xi17Mc9smbHGOUjvPXuaI439THUCFH8PXmE1zYYvnZ8mLP6cQ2F02m0j5dG5j3Iff04FLpMfr5jyq8eB0Y4a1wcR1c+8eDkpE0toSveuPSvPt5AhPB+ZQX7EjXrNnB3knnmTNl2pNZWI9sqRFvvYoYsNb8CNPLEIQMH+GpydSOic5rwQmldfZUbvzWWwMOIR/FTMzhicpgAB1TfedLOwkGKksEC7We35od9k8K8Yku0GsvCEIadbOvpEoYm0cOrquAzVsB8VnCRi9vDkxBFtFBmD/etB+M/sYgatKawCuH8rSX2jkA6uWu7iyvezx3iGn5z4sCwTkuFu71IEsOvpEvNi0HZEDz7WaLMCHM+RNPIWVcoONY8YcC+O0LEWUuTXUXtoLuW8/1wmNHP2Wc+5Ald4Rwugv6aXzyyxPqFJOhykPHjRXbJuKsYzimIgEfR13NstE+khOonwmHElMeFfck/lhTXqu4Hft+AJdIrNN9xooRhYHpIXFQerj33oKqlwS1YPS85M8TjyQlMVGSvTzbm7ElzAZNVt6s7kRFv2GzAnKjvMo32qqvi3RmWTBQRNN3t9MuzEUOfrq8vGIEKZEA4XU6PKDGW4LMeR3d5+RxmqL3Ky7LBvnz2cN8BvtrhWaVlLNrvj0rpOHqp24Jz/HiRvPaytspeIK73+cQDvHv5iS3nQjyKKtprGnLp0jdvxYD/MrdlTLEQX75c6fVTl43wnNlFVlXdv5tLjkvZWgSQvclbsyGN3Hc2zfTS9ko/bzdITgQbdJ/1a489ElG0brOusHBklT6a61zfGEhLFk3UxsHGGHgydtzwZwkWLY+LvxIunep1OkX8+K3IEXqWG/eRrpP+N7hSX9GyQCzC994S8bYO7RKceefDxWGUDa7ryX145K9lgO+O3L0jtGe8rftGD46w31MpRFvZ2D8peN4HvwV4O/UqgyYaPR4FzrkQCwYOMVWGpd1BCHCcMQZbYwi47useN/qhVNqYT6p1C/I777C91uajVcu9260nOXHl7sQOHARrd0iaHF5fZcm2fd/lKbVORCBc5obf70QWcskjffYt6bVFb2h6XdGM7E1vadaikGIM/+YIei8m6hbzy7i+bCTPe9I2TmvbSbZ1am17ybZEH9U2TbZtIfB68ewPe+MtpJQRnfp19wBfDbFipPvcvs6LSuBiXDkqPrlNhBsqjh+q3jVrx/hVIxUsjHFCWLU5r5ETH2TCnHdSzAnhFbUz6xvRMZYcyn0=
*/