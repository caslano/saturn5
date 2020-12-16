#ifndef BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDL_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class ForwardOp>
      class foldl_start_with_parser
      {
      private:
        template <class Res>
        struct apply_unchecked :
          foldl<P, typename get_result<Res>::type, ForwardOp>::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef foldl_start_with_parser type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename StateP::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename StateP::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* foldl_start_with_parser.hpp
p/2Gy/Y5rp7/FN5ReAa/RPV/4heL+vk0fJzovwz+asZnbP8tPkc8Pz3wc1X9A29W7Wf8NlF//BLPq/0z/6bHT8t4F+FVXOUv+Xedv/1xlb8qLtcnxOX6hP8wbvsP8d1F+iweU993fD+1vj8+QM2PxWX59bqn/MLV9zeJy/E1j6fxrZsa7z8+Em+L2/bBD8L1LfAm46vwdrWznYp/I/bfG41/JeavFN6g/6RO/jvV8vcQ3sy/sZrb9XeD9cRfq/0l8aS4fyn87ibH7f5p+M1m/4LUjs7+afgNxg8/K/o1V+CnG78VD6/GdfhI49/gLePjFf18jsTV81nA+6n+PVzGH2/w7L+Py/ULPJ7yeNpz/ownfdbjOY/n8aNU+YAfIa5/FV8mys8v8MUifudL/C7RP9DzTeoHon+ghMv113DZ/+vxKq6er+RbtH/F/TsQ7+G4nT+XxTuo/iu8k/CCx0t4T/X7POcP3ib+SHgCV+mTuBy/wOX7gQ9u+n/vWvMx+I54m8ip30f7Y5yGb2+8iIfrq4/HOxsPukf1x7PxbV239ft3PM8PLvfXfFenj3k84fEk/qJYv7sZXyfar8PxB0T8ZBpfJuInT8IXO27HD5Pvmf5Buz4zfqbjtn2wP3662D/3APw08f0eiI9W+5/gKr62gsv2+/u6fprAL3POb+vnffBpYv/bA3G1/+0g/FDHbf98CZfjZ7gsP3FV/lY96YMPtMdw+X32eNJz/JTH0zjXN+jeoP+ziB/krF9t63fP4rvj7SKnfhXl9jt8Y/B9Hz8hys0BHzL/1fhKvGV9qY2038X3ewh+nVhf8Vh8luP2+TkOn+m4fX6q+I/U/dnkuT+4vD+e9GlP+ozHsx7PeTzvyV8BV+9H0ZO+5Dl/2eMVj1f1+QkW87yf+JFqfBE/XO3fiU8U659cjI8X66tMw0eL+LIq7u7fYcfft+AZPOb4mF2j8aPgY9ovxp/LRONHTfhxxruMd9avxt8z7btL8Jb1+z5h/Nhtf9r9xfCD8HaOjz4qun7v4T2N3zku+rWb8O2Nb8TDvw6s/m//I9ePzTjzGzZz/Zznw+5vPx6f7LrZ334Cfq7j9vt8Bj7Rcft9PhM/y3H7fa7inzn7V9j1Abbgb+PbOz65a7Q+wLf468aX4+H9/Q7/u/ETjonONuFT2ifGNzn3t/AF6/8499fGpz+Az8Vt/3RYv1mOzzFexMP+zxX4ZcaD7tH1W4nPcNzWXwtfmfUbbP7w+5zxPZu/Ir7YeBFvFeYPv8t1mz98geM2f/mvw/4ZvM78pQX4pzULvUPfqH9nIb7R+Ag87N+5C//A+F341rX83YNvcNzuD1f5JhZ8KNYf2YC/L9YfeRN/23Hbv/0evl6sP/I+/rpYfyS2hfhJtT4+/rnaXw7fqPaXw99T6+Pjb4n+9/S3uv884/Gsx3Mez+P7bRW9n7Z9eS/eBR/h+Ldjo9JoM76u7fd90OnO+qD4WuPX4+Ffn+G/Nf4J3lL+tonr34+f00rsH4U/K/aPmoY/4ri9v5fgK9X+UXixSax/s3Vcz2/D5fwp/Box/2QNPidovH/XWjznuI3/eB6/XOxvl22n85/HVf6L+Hd1yv+9a/4i/ld8N8efPSnaH+4l/DXj/8a3C9ePxl8xftwo/rv213p8tfGVeEv7u73+fWlcxhfgT7aOrp8df/0ZfjN+iuPzTov6Z67D5xsv42H/zPV43nhv3r8f1H7NLfhc41fhLfE5Mf37Urgcn8PPUfHv+NlqfAif7NRPbf1uC56p/Xfop+4cpc/FeT5F/Xg2fpnrdv0W/CJRP050jgf3iPUxe+NLxfqYO+OLxPqYVbyPah9ux/UT80v64Bkxv6Q=
*/