#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct repeated_one_of1 :
        repeated1<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of1.hpp
55nh62rqT2spj2vHLDOfj212e8JH769Kky8vQk+p2WzWeWSlnmgEG+Hzp2f0WFfcM5lGO2Ht9GCLW/rac+BFe8Gbinq0llrR521hxAFxuIYTtuTFG/l93B2cTct9ZX0XfD5DPT7cpj/92/uTuVlXuvVnmHZCPuTrh2T2TKd+OpJH364+PuMPhsC3m7g4RJ5b41j/n0vuRppF5zXb7VopGCfe18zuiXz9co02iGEWrf4ORqq9KWoyVcBZvX6Kbh4aSofjhRdd1Zx7RwnOQK7RzAX1UADGzxazUXgibcDv11b/X9Eq9/TcFvMyerrWRvj+pecx+cM1CeBAFLhF+x9fAqt4d7kIVJO/V7DntdnN9Ajnpmos1i1ajUacam3P4O4i+iVkO/yWy9jTvcees86lscTZ33TwO7XFGad19hzifFiRlo+ebTbaTD2v7Q6vvpMzfX55iFzl5tErOHt8QONW0b+PnTVuENccYkBD98vlfBNflnttDutcKRpc352GXhf/Y2os9UM5xqkxUuCkq7z/JLPuxmIhT7WDHFiSh6/p3zf6APf3T0xrilHGgvANHo2mO47/o/Y+NUcSp2wl8HMpveq+rhMoGgm/1d7KKzSX9VyGVdl8vhN/NUynLvHPIL093ly/nH5qOU5PBH9nf35ar69as5+7a+R+qjmePWcar0ddP+Vt+sJzFiHH1R0fdFf/7Ojt+rD9e1g2cB4PLi7hobTaPD+zYK8z1fSvemLydvihF/rhlE674b7ar7vSNeTrIe6tukV/mgFFq0rnzDJziWOODgei4+v95dScHo47jQ8PgRu46Po23GpN/1EHpeqq3criuVq+ab5u9fS82gp9i5Nhw1h7+GyCtbw2GisBMyrAV3t462sJ1dDtHmYQ8pwltbUsEff9+B837mpID8fQi914Hfz4+Tr5E8vtmeWe9o+rPxfBp2UdgnMueio135sLj9ex1vv62Sw5iflp0rrqSp+vbcn7tJLrjLTULDwq5tf70CvD8HoMfXQPlv1qtk2D1zmkR3HhjedmHrtwdE85h5HJ6Mw4rjEkGv7jvZdGiO1+fZ5PLcpZpjjmPItwH/6NwGej1+DsIQFYxVv1EeNP5FTMT9f03p4wYCeOSWY//EJp87Kw7bQ6TGyGt97U5+lote3yeHB+KM4WmxNqUj83obFTbYYdYhj/ON8c5vlO87FWDegosRglfuNDxZWeGodn66ituNf4e/ttbi2dceqoP+m75DQD7/Faz77JEfD7oeWaXylFO+a6bgaUyGyhCz35X/bOO0yuqgrgk4Rew6b3EDpIygZCIAhsdjfJks3uZksSQnCY3Z3NDtmdGWZmUxAQpIlUkSggSBVRilGKNKlCKIrSQWmCCEgNoVd/d95979ZJsvp9/sV+ZEPuObedfs69771F+PFJ5PavoFeP4cMroPux2Jp3sMWbIK8bs9bPidXw7333gh61xF1PQOth+JAdqZeTS82DV3PmYBufIo7YHJm+GLn7Nn79UOKH+6gFID9Xr0T/c5ypP8CZLTnnp9RGHsJvi1rok3lo34b9Il8fRu7ze3Db1mCfmsjvktieF6lb9kXuDkT++pKT78xY4zkHOot4CN4+ho+agq3fHBv4wIfUGKZjw6uL54L4ceRkN/x7Fp5vCy2eoQZGbDZhJDKxC7ES8ccFU1nzC8jGHHzfzejXXsTRv2D/z8GbZupyxPRPMvY41nsw8eUDyFcZ6761ifrrB/jdDP+/EnvzOr4sS4zyCTJwX4ycED9NfnM2vuepadjjz8hD8YPnke8/+y45w2nUvKbAb+zRBGpBPfPw7z/viw3BxxyFLUMHbyG2e426Y4ZxfjST/Pc44kDu7F4=
*/