//
// execution/detail/as_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_DETAIL_AS_OPERATION_HPP
#define BOOST_ASIO_EXECUTION_DETAIL_AS_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/detail/as_invocable.hpp>
#include <boost/asio/execution/execute.hpp>
#include <boost/asio/execution/set_error.hpp>
#include <boost/asio/traits/start_member.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

template <typename Executor, typename Receiver>
struct as_operation
{
  typename remove_cvref<Executor>::type ex_;
  typename remove_cvref<Receiver>::type receiver_;
#if !defined(BOOST_ASIO_HAS_MOVE)
  boost::asio::detail::shared_ptr<boost::asio::detail::atomic_count> ref_count_;
#endif // !defined(BOOST_ASIO_HAS_MOVE)

  template <typename E, typename R>
  explicit as_operation(BOOST_ASIO_MOVE_ARG(E) e, BOOST_ASIO_MOVE_ARG(R) r)
    : ex_(BOOST_ASIO_MOVE_CAST(E)(e)),
      receiver_(BOOST_ASIO_MOVE_CAST(R)(r))
#if !defined(BOOST_ASIO_HAS_MOVE)
      , ref_count_(new boost::asio::detail::atomic_count(1))
#endif // !defined(BOOST_ASIO_HAS_MOVE)
  {
  }

  void start() BOOST_ASIO_NOEXCEPT
  {
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    try
    {
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
      execution::execute(
          BOOST_ASIO_MOVE_CAST(typename remove_cvref<Executor>::type)(ex_),
          as_invocable<typename remove_cvref<Receiver>::type,
              Executor>(receiver_
#if !defined(BOOST_ASIO_HAS_MOVE)
                , ref_count_
#endif // !defined(BOOST_ASIO_HAS_MOVE)
              ));
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    }
    catch (...)
    {
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
      execution::set_error(
          BOOST_ASIO_MOVE_OR_LVALUE(
            typename remove_cvref<Receiver>::type)(
              receiver_),
          std::current_exception());
#else // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
      std::terminate();
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
    }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }
};

} // namespace detail
} // namespace execution
namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_START_MEMBER_TRAIT)

template <typename Executor, typename Receiver>
struct start_member<
    boost::asio::execution::detail::as_operation<Executor, Receiver> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_START_MEMBER_TRAIT)

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_DETAIL_AS_OPERATION_HPP

/* as_operation.hpp
UhpldMpCyvDEyUSmBKbEmoSaRMcEssGmQffBm0HowcBBkcGeQcVNFOMUh2KHFIcmh0CHfIdEhzqHSIdyhwyHtmqtJoEmhSYJ9ZylsqXPSyVlyjZKqpQN1K4UrlSulK7UVxRXVKWJdwksgxqbPpsQmwKbRPmy6oVlaqwUOInBiWIJYokygybG4aefThtPA07zqlXmC7jzucu5c7lLuQu5K1uzW4ta81rLWj+3lrQWWKnpqC3LLysvKy6rLiu4UBxRHVEeURNQEFBxJWoPig3aGEdXq928vxG+Ub6RvtG6EQSbpSTYFEXnC71KvQq9Kg/UfOR9lH0UweajADYZJR+1R/lH5UdFRArYRKFBfbJilMQS6c2SvFcqqmgqKiwqagjTyjVTHhbeLJrW2azKOMWR0+8slOpSFrSsc+qVNYvLp1ktNFnELooPpy4tYOtyFyRGVLhKtacqLNjqWhaEDosvFT1L3Ut066b8sJXPpmOwVUkslA9zL1XuismLHqYh9vhZCtCLAi20aBXf7hE6f+EUxitBVAouJZmK3aNwruUUxSuNUuorfTsVuhe6R+pczSnCI5FRklmW+VlWqbC0Z++1c4HG56SSmqn5Pdw66YzSUaWh6RuLQI1iOnk5ldIpizrRchWMkvCpyamevd09rL2UPfW9+T2OPZQLrQvuC68LyAvBC+ILA+dij9Bm6TblNuk2rTbBNsU2yTaNNtE21TbZNh3tiuXs5aLlvAp5W1VbBVsVtZKG4tKpxWmuKa7plqmWac8pz+npPe89bOdyj45bv9vs2xiNwgql2VKcqci9b3ske7l775xrmkW8pb21vAW9Fb+X2ChlKWapZilkqWQpZanpyusq6yrqquoq6KroKjWUVpbaFtmW2Bbblh4VcU25Tl9NXU0jTSFNZ+zRXZA4NzSLfS/1KfP57FPiU+BT4ZPjU+yT71Puk/tTqUOlQ6lD7aqUr4ivhK+Yr7SjqKOko7ij1LfIt8S3GHbKH7zr+ZI6FSLKUmAvAwp4ZxlWYJFaYBlkYvHb47LlLOPYFpG1vRpvy4tnpC0r6sY1LMprZzRwysuTcm9qXTQ8y/1nFPbzNi0y6ug01MrTZrT3cy6mPMzb6rhHKtU1+OEtbjTE4S2RaUsuJm4tHmrf1j4uAKyz0Sdf1QrSVqCZv7SOYX3/3z4SG8eqnvY5I09mWnZGdqLAfLLOwDqIVYl6QrJOfcHKOkq1YGR6y3xzwatcsHQK3azQQkWjTjV32gK+TmTBfMHg0Onw9aH0Ic2h1SGudahLhUumS7vLB5ccl1iXqnrlFmHNAu0S7QLtCu0c7WLtfO1y7VztUu1C7UraWZtxmykbkKoZm2WDWYMFdd1ircrC4QLeQsaC9sL3BZ6FtgWLQ17ryHrVFl1Pfk95T/HSyRnz/TqEBdFD/UPkQwXr+Hr1xc88BTwVPDk8xdbT9eZy5nKWY2ZjFmPmY5ZAM6AF0BxoWWlWaVFpvlg3W8dWy1bXUNtQ51qLt9Cy4LlwtwC7ELwga518GVuvuZh7OM07wzvBO807yTvbPt4+1Q5qn2mfuDRfsVgxX7G8qyOoJajLqs2q063VrVupXanjq+Wr66iFWhA4jHF5/x88nNoWuqxsW8A2q7lDe6HqYdkWuaw6NuENDs3blgWOilxBjhejHhhtpcsyRxVX4557befLHpk/Z2l5smEvvHjygi9C8KfvdrwvfG5fevh6+/HKR+9Ce+Tgz4afB/CKE5QhTQTvfTv/cQvnnccrSVAePdG3t35+cvvC+7PPZ16JrDK5CTlQ4R75fuHO5PmuRxWvUFZx8k7+LY13Pa8YcHJ77+zcwbtdJ0dtD/5c6YKqTaNywvIi8Jb4gdm7yqfZJwhs9kk+9T5R7cJ8anxyfLod/B3yHeId73VLdD8DJ4HT4O9s5XjlVCWocqZyonK6crJyNnmfbYdtj22X+jztQvNc8yLx1vqW6sHlAfFB9oHuweYB/0HHu84nq11Ut3Slki8bvILyZnf3zy9uYbxzH788hjwWtUuslNlOEEwSzGaNZ0017C2C966FF6bnphfb59sXGOcYF8nnyRdq52oXs+eHt/u3OLdpt5q3i7dct4gP2g88D94PUA9C3oXtUk/iK+VHE1d7BPtZO1l7WbtZ+7o7unu6u7r7Kzt357YXR+dHFw+3SLfRt3K3Y7fA28pb29ujW4LbrFvdW4iHbB9xvjJyBAN5f6ylmNf6/UEGRUEmO0H6n0STFMaKbI1wECKCRElyqya6zSyYmVJxaCOSRKlz6yZ6zSw3MHlzMyaWd/ScmDmxmkRNc8P/5Q0GxzhJyPQfRduRGbtEu0OwvSPaRfnWX+R2MHRimnVHQOaOh+CIiHZhGr1mDcIUitTvtTMMYABhGkew9mIaRtr3uhl+ZJhgn/hkJM1agEmOpRQZH6kUYd7rlDv3SX+YWTJC0TCJYfGTYQKWY6S7aBPDShE9VSR0b7FoooL1FGZdr6BhrH1q1Rz7d/Zv7JPsQ+yL7H3vDdIt003TbbX0tMy0jLSsaFjoGJKwkrGTsZJx1DDVsNWw1HBmMWexZ7FmcYYicSJwItMi0HpHeml7y3sl11kNE+1b7IPtC+2T7Rvso+0rqxYax94blrH8ZMOnx2fGZ9yLcO71MPSvmnCbc+t2m5ozsmKtx4zGisaRw5TD1oy07lXqnexl6q3pdew964XvDe+V6h3qpe4t7bXsdVl3XkdYl1mnXbdexzMMPqk4yTxpP/lwklM1OWfsZXTA+jfvzYiojLSN8O5t6HXtver1WYddF1snXzddx1hXW2dbd11HWpdbB6772Y+zG+Gyxr1jKB6QtpEsoDdWYlBRYnKepJdhGioznWGrGYExEaqJnZ+zMmBlSUsZGUE3kapJnF+wMqxncZTOmh+1snWh50rNGNaqqZnvObBwYWpJ4xnONAHWNKSY3soMvf4kwLTyOkWfyUB0hNdEtybL/eP8Cq4eIrOhyQd1s94RYiZ9REbYNKHhnC16x0aOLlzzKEaxNMPhqi12x1aOr+lmmWayjORpSsPPr3kc2KLcYnZsVrcapTdNJTMp5hhKtx5lGBpu2uKuWUq3Vf2UuAV5plwzWMZqOazhmNPUzz2iZZVpk6mfaZ5pnGmdaUjHMMYyxjTGBqQHMgMZgazJqcmfhoalRoaGh0aoh6lHSodLRyyHLUf2h/dHNrcQtiK3ZLZenZmcoZ+pOua7pzUNtn5v/dY62TrUutja1zqrZb1sWsEwm3qVhvQJKRUpxXmL07Gt6euSGa8VrwGvhQ0jW5rmcN9w3wj5MPlI+RbrGeWZ+RnWmfoZx5n7GfSZyBnZmfEZ2pnKGYtjy03zTdBNwU3STf1NVNM3r1mvMa+V+8778SXzn4x8jK5pnsNtW31b5FuFW6Zb21sYW8lbaluzW2xbvGeaZ1xnno4dN/43uTfxNzU34TelN2k3LTfBN4U3ye6d3Gb4jEhpAzRxIjXv0cfiqoWT0vONitU1kjKNjVLU1dUvqvdMjU1Z+i0+TVOU2qvGlxWoj1Snmtb1W6RMU5U6q6aV1atzqLeXuagf1nAaOQ/vJSSmTXOUSqnOltmof6/xMLoY3kuc5qIGDmUZG0NXf1S/Uc8ps1MlpU6dJi+t3FFR0NQZ3Z69vfnIyEfAYtquqKlgou5OVFfb2mol4Kxep6ysqVKMRFlcRpnJUVP7WRSPraY2r6y19T1dirqKulauCh1NeUmmuroK1RiQ+oOBg5Woym6XYtOcgGSZg4uxyC53Pnvg5vXwWsngK7c5AftCxHw4+ESDnM9T30Go2DrcNfUFynRyOT+Khx1gJb59yFW2qcFLadaOFSRRyqfCTWCxkLXuOVgrWbjZ7KljUU9cTuBmveBXeRUpw6OWKLiumDKNyNg3VpbO18FOBlPTGx/TVxg2yy4uXURV+onW4tByJiCXfRa/x12y5HISL0/OXqQs62ecgTyDHfL6dsIM6tmE46Cw/c1Hjp7PebWtBe8pAx8pYX2mjWu2Mc5S1zTa9WTVVfdwY78TkRzdQ3AgzBIA4Ni2zY2TjW3btm3btm3b5sa2bdv4895UfXOYqj71dPX0aRhgl/3JpBPoh7EiBp/R8h6Uo5CVZXgDqCOMyqkkJJqSnNkkha8i0fIyvyThe8rRS7W3i/IbDlUyhUCfxBTEyUv/mKWWlcvAq24ls9KyC1v/IXeMcBf1S6IOnZ1LTFQONZ/FKaeWLLZ4DQcrl04UNTv9EzlOBtdpITEYQj2HzUpU9y9HZkZmxyykj2pKeIcLqaYfs2n9vBX8Gggqjyf62TqXO0iJexsYxqyhoWANeJWY3pblX9zHth7CeE5wwixkSeSPm2OE0OOjbqGh9vumSiiNzenGts6+UEUABCz709UQLWqKLOq/dAmNCKWz4ogoQ110M3rTRnUkaFdKSR13CjR0RXlTi1YEsJR5S6phF+tlqyKMSnpY8SXlUFBGZzLSycl8m/IowHy8MsYl3WDl6AmcG5ouB9WtpwRRDDP4tcDrRQnllT0krJKiYH5ypmv2wpKUqLbyTNqCsd5dExbDAX0pMRz9fKhBOZVsZZX8D6Oy9KfxJmrzv3wwM9/vUnO7nzL5yYBLD87wHXKo650P/KdeTfuS5xWZeN1CFUHMSsuqobD/ML2Kq08mQzRHsfhsRLgXjrn+AbQfBtBpQC7xv4Xl3VLYFHe36QgU7bp7Cf2UBU0OttEMSFQtCkJK+eZE6sPxU/oqKjFDjigbFBlIWBAY7yPYbF/UPom/Z/S7Q2OJL0kKHKCMvelilCRdp4hZsIegM239G5VaREpUQqZfREISSQvkjkXi2kloCu5J+AjLZ+xKjlVJLKNnpTVvViyiFoo2RXHur+wMX56hRdcdBw43hs5didzGj+uzzQdJ3z8xRuRE88tojuv7oc3cEfCP2xwUcCUO3XQsFZ2EKdgeLIbrNeGk1wc4JeIvyZhdSowd/VOREHVHs2FuGleksgQ1doOiZG1HLPVj3qUTND/WFyDD7T++xiewpRXs4Oa+x8SUnvU7WfG7pCcYw31ru5eqNKRLwK8d/TnkE2iAyjD+/ivJAvXF1riRVkB+Qz6Yvgd/NY+80G285H8MbcyfoETAcl3DkOo65MAv/M9Y2LgwweoLqRMmpytmnxmFGhOH7iJimzSFCAUafr+h6laniHljHK9wOiwagImxrKRBNxTxEaLu4Jjfh4N/iyCpnFFZgzRLFmblxl9U9CnW9BY1Wa9PHgMpuzyF3udIL43TiXsk3ixuehEdtEouXB+ohOopopy0FML+4Lo2ls0cwF2W+z7VtNyYw2nRlq7O9A4/Yp9S9JMHaxFfIBydVmR5pHGRCXGaOLh9QgaOckwJDROdzMfbsJdeoaOYC8MYQk94/tCn8o6jtqxlZDVQKnimV9ybda5dy5qsvmDSgwHU8DWq6Bv2Elvt0BpJiEgogWKAYp+CiMOnOk6EzXOfj5TDb3u4R61zxjcYbw2WJWYIb04W24AD6Mac1Srca8/274cqyI8MSD1/308ugT8s0N4PyNZjI+KmVXyVm3WRsGf2v/X7nJiw5h9lN1+sysiOgRSPCFcP2xzhqv0LYj/bPlMAW/g6X8OZTpfrsp3ozepZWFyg2M3QKH4STdGtu2OwbDdhO0GmIcutaLpzqCjGjUL4QRjN5eM/qxflhT7xMFuOV5dPfWWDdoOdze0u+7Bbfh+3GLqHinm7hWK+4JuwYHML+AKj3pjdLanGVvi025Tz7GezaVXbU6rQdhlapOCiiBaZsM5cRHRiu5Nfi29E1H3mDE0URe753buK9DmoVJ4sCo6tFCTDV0Ig9/wNLjt30CKPq3cCA5y4oiIDnRimfPM6U/4n9hl8Nte5VeQpmjAHPEVc1TSXuTDvn6Sv9+mjn589rcJpI/yb1oRHr2pIrCqK95Be5oYxHi7peba2IuJhFrFhFivhFqphFtLhFm/fUOw6f+doUQBpUcq0X2xbAvhZEbaAtlgJBQh3BMQEHARhBCuaHLHYNbtkeBw+6wpT5xLZ210D5KUPVb3FkYFLfwiDZI+72e0nOeWyTykD0HOPO7f0OxfjuuSgksJVjlehrhd1/aaoeR3fdOab+JClRWB1QdgJtDo6p0jkQZtJmziqsDKj8wtZYo8FIlEwHq4L2RlypVyAIOc2KgTE7TcNUFBSh/abw+Nm2ccn+yEQ06+lZAQ+uITqQkjKHdny+qslEz/Ai6c9mfYlF0+ta1J11Bbh8Spa0Y3vy+2C8/fLs8P06WT4AXszxDdGd7qeyJ1ODMD2Hb8nIU9cNAInRhsQC/DzV4d8b2TcQS3B9f02ImPMMOrrEcViycVXO6V9sSIJ0y/TKFvje0nm3qykgkW10I0o8gNU7lF2Ko+YdQ4XByAziMH9OhDuge2NOLcbF2jXzP9+lzVnBhkIx2f/+6ISmyw5WBnOMRU97tdIvE+LH+KI9tNHxxQl8pDZLNREERrAOtGLcUhAgJvA24jJond6PYZIzfIL4Vb2EHsFgJZG7QNp5pIyA1pIcXigPDIr+ghs57TqJ9suJVHlhv3aW8n5yEZGI6qeHujVS+7+fmAs7SevasQ81M3bTQXq7nrGrmOdx6sGA0XpOPrbtsdYTVe7tpHzl6WOTgxWHcicasNiUMOT7HRJN2arP0fClU7yIX2zpRiFX1CpoDcuNDQozhM6JzqV4TIPoC8HYw+O5pudI0HU7Xo5cqElp1E3Tw6iPPFufCrdwrkDo65Uyo0v0jc85hAzRxN+q8PPxyp/Td0ClkH55oQD+MQE6y3L6GCwyUMP7+bMNQUMGufQqJZiryAsGNKZcm97Lr091JK2lpS5Tlcjii4FalVloKlZ3/WCwM2t4RJHxpS17G3mi5C7t8ntAf6sAS4AUC3jEZOAjBJBcholINSb1pPSTi6Xm+q7YPzu4P5UEp72XtbzTEUnw7tC/I+FOEj4u9cHsJ2IuN4pfmH4lAK5jCp5T5o4M46nnazGWKm4z1IZV45vhXRzflkuznLZJDWwdwVzW7jVybcAND6RetVDrhj5C/r6K9CYwcGPzPassCdpZDN8fJXVMF72c2eHbZNd7jfh9Y6Qix387AD5O7YCti6vupUN8trRzti1tJGnqz6N12EvYfMdasK/Epb47J/gLD2R+6WxpI45PCeK58SA5RKNMfQiQUdKuHiL/Z5SwXOMdxcnj837m6JAz4P3efkkQ/CV00HZ58qUXsYMKBi0huE//sIyqLYLNBPdxglX7+cqtyb4yR/x3XBp/StEifH7DU7M11rgX1t7/dhk/0oMeDuUAVb9c2cgd2NthLkgSt8dSblRNjD5pruUkuiv6ysqv7UsiSprkCo0FEGI/oRbtyV+QbqqU2C83jNj+eFsf8MKfkk87qGKF9/DkXmDDnob1rrpYQTls3p4SuRVzymbbUxpWJpFD3hU7SJJ26tHBITILMS48RPYK0vJ7FpqEDN5E2rQGbnhUHn/3GtwdkIKelNoUHEDwGkBqs6rgGoQks4sGydM8296oUKmDlOkIoaUh2eSfMzxXMETH0+AcFpg09RCmGteUTi1eoOLWLmOcU0dFVwQu851vySgGRw5CgSXYtK+Xwk0OmTSNP3r0JFZVY+B9jHEkbEe5ylftrZst8eqV5C+
*/