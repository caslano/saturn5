//
// placeholders.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_PLACEHOLDERS_HPP
#define BOOST_ASIO_PLACEHOLDERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_BIND)
# include <boost/bind/arg.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_BIND)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace placeholders {

#if defined(GENERATING_DOCUMENTATION)

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the error argument of a handler for any of the asynchronous functions.
unspecified error;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the bytes_transferred argument of a handler for asynchronous functions such
/// as boost::asio::basic_stream_socket::async_write_some or
/// boost::asio::async_write.
unspecified bytes_transferred;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the iterator argument of a handler for asynchronous functions such as
/// boost::asio::async_connect.
unspecified iterator;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the results argument of a handler for asynchronous functions such as
/// boost::asio::basic_resolver::async_resolve.
unspecified results;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the results argument of a handler for asynchronous functions such as
/// boost::asio::async_connect.
unspecified endpoint;

/// An argument placeholder, for use with boost::bind(), that corresponds to
/// the signal_number argument of a handler for asynchronous functions such as
/// boost::asio::signal_set::async_wait.
unspecified signal_number;

#elif defined(BOOST_ASIO_HAS_BOOST_BIND)
# if defined(__BORLANDC__) || defined(__GNUC__)

inline boost::arg<1> error()
{
  return boost::arg<1>();
}

inline boost::arg<2> bytes_transferred()
{
  return boost::arg<2>();
}

inline boost::arg<2> iterator()
{
  return boost::arg<2>();
}

inline boost::arg<2> results()
{
  return boost::arg<2>();
}

inline boost::arg<2> endpoint()
{
  return boost::arg<2>();
}

inline boost::arg<2> signal_number()
{
  return boost::arg<2>();
}

# else

namespace detail
{
  template <int Number>
  struct placeholder
  {
    static boost::arg<Number>& get()
    {
      static boost::arg<Number> result;
      return result;
    }
  };
}

#  if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC < 1400)

static boost::arg<1>& error
  = boost::asio::placeholders::detail::placeholder<1>::get();
static boost::arg<2>& bytes_transferred
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& iterator
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& results
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& endpoint
  = boost::asio::placeholders::detail::placeholder<2>::get();
static boost::arg<2>& signal_number
  = boost::asio::placeholders::detail::placeholder<2>::get();

#  else

namespace
{
  boost::arg<1>& error
    = boost::asio::placeholders::detail::placeholder<1>::get();
  boost::arg<2>& bytes_transferred
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& iterator
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& results
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& endpoint
    = boost::asio::placeholders::detail::placeholder<2>::get();
  boost::arg<2>& signal_number
    = boost::asio::placeholders::detail::placeholder<2>::get();
} // namespace

#  endif
# endif
#endif

} // namespace placeholders
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_PLACEHOLDERS_HPP

/* placeholders.hpp
+qIZLbW73PXSjH/GdL/KTT2DngLbh0fhg5qIPBAPpl5yZHWSKUpoNSL96zXxfnGMJiJt4FgW4uSFo0MN+0ktHM3wVoNb8nwEYrF7o2IvnfZE+/F9xREKuQT5BGJaenq9tPSUlATiSZmP/LdCt0q3ibP44UqhIgOtSbqiTdw0FbrqLuWOu95b8WVCcTZnDT+j6DXi3nqBNr3ull7yOmLlqqxtjbx0Y5mL0fG/ZbrFWp85dc+2tx+xLZRiZufmzZkmq/kXtHvG0VyfbhsKL0OvzB8HvhIbOSK+N7vldjtPITJ4w7nhOnYHURXsnYfxvjcmF5SVjV7mEuUjMBfvrdRFqpOxD1BZvblZoTwWT/0DiMOQE/oL96/jwLD4E/l0vnq+Hj72fqaD/CHlHFPW/fgBGDBZWgHscYTiKEHWZPcQRb/ZsDRVCeGXAEAafI/XqATV+GrBWK4ZocPrBPU0xVyn6JYbPcuyqUhrxaXqo4ZutEpZ0yXqB46Pjqlx1tGKTiBXfp0JtI3UVE0eWF1+yg4w/1QJrBC1dfyQvdj+Kr+WU4OlajvljR6g/PPYlPyqirWjW8UhYnGopBJqKkL15XryAoUxYnkoRKiiEmkqfdW2IeiKK+NQgSrn16Hkd9u7Z0k14jJfeDFqX96vs6srD5f7HqTyleupst/Ce2yk2E5Fo0Y3O3DRnIy2Z+CFiqnrpcfke0G1DaMyNs38wq2isq2m8K2kiq2oxzUix+42F30HwE2vjGCtwPXkCcEL9Q/1S/Ux9Xn1iMAjj5vzq4+jj6uPp4+vj6TN/vPaxcBFwYALXqzJTqgP0CTFPao+HL6fgrDwZHSHDoeK6Eb8HDajsF4sA/p+Aj92rNrynyjqgbhUhzE72ENpqriKunbnUx+tLC5Ix9wjzYIE9mTGG8Q+0VT8BGbzNQbTCVJDW8ehswjrWHNdSsdoNuTmaUf+zawaSnBsWUMEodxaemWXvpOoJjJO+mqVAp0MP51Ae+nXvJ+rN+hHqmep48QfhV+gW5QVngpbNeVPw/25ENP3TkvqUYEPhG2Yz4cx6enH+HuYKcMCWd7edn7mQPhYoDRqGmEmsOH06XEwVczxnxaraApqNlwcdaYPP98GLgl5EHWZR1yeWlLMlw86D/qglWf6DAI3kO0qz2ZL+Ite8UtEk+jWHOWW/SwCKvffF4NpG3v+FEZ6grRpgPepXIfPRNmyKovG7W0faqPZcP9C9hN5sRG4cbhpOK4L9W/xH8jfCJSYZvwquOMKnjiUwXViyWfOg3TuPOAG7oVdaO68O2RBAG0ANy/o4W6g8y9qEMbjgCj93XUvB1ne0lv2X2ONibBCsNB90rvg4+bYTX6OHIgHOYSNtlTc6zvQrMJ0uY6XSmXJLWRiyXRDgX01jcRhg3JJj8P7hM296ZbHs3sq1eQpuE7l2srCdpXgGFzVVzu9XZTeddceua7RpSFowdv/dqGCBIYOWtr/i55Eiu0/qPeEgiqUEzvcFqcinzBofQ4SN66obE3nPdiw31DErKZYdblzim/UvkZlLF0Gv7ZIN+XMltKNcf25islbtfWKEJUst+LsyCu3+nye7GjYtrnJMBzGLnY39akpL3hnzzhtOqafvGxavk37LKaEj5dtXWwt1aUJedXXT5UJ7bN1LCuLv8XYOTzCEdz91BMV3D19+0gbbRY0m/68W5tu/kb4/TGdrUD7VbgsJ/ua+ZXF9Qcc3onwYuHPcvw2v+ZPiHBV2KEzFe+nH0fGbibl0PXqa7yZwguSFYMv5TcllrY/AQ/rRgOR/oGwbti4T5uOs+atDk0LPywzyNar2/saAuNMxDy2DvPuAHEBnGwXFeQlvxo/o5rw8P0yoj/T/tUSko1KlkVE5XxeXODjCjpYzbOoHmD1DcMPbZSJGg+gK69DQIaJQKqLCLYBdtcisJG8qzJd1+h5fOHUJRwCFgPVPmvqQP+G8tFf80MwloDL6CSMcUQZa6JNd7XbqN9Tj60Zqhcj4eIxX/2RJAwkfzbzQkAXcLI56pUjEZLQalVmzlfFe7P2d+vO20mgK6o79BprvIh5WWHD9C1inOi3Lv+PoEUHyIiVQXcAihzUJIzZMUk4/0o7PA2a1VRAXB2CAg1x0JbCQD23BtzO5wHiKSkios6ntDTVAklc0EAMVKnJ0Ijb24Nfb//ftjsi4QRUNBqpFHlhs1TfmUQ9+Olt4ZHIAUyJjdQin//R01ZdKYVqMekBPNfLh821/wRm7juRbdo5nvnx6dUryrkEYi+GpY5PwX8saNPfEdcTn1LKfUpTYJ5J+J9THG/0beaY7/XW/ZqK+QR2MkCgn5X3PMmMQLog3ntJmOPbjd9GySZySe/HowNLOMHcoGrFnDjvBkQefZ8yy6G6n+/uSCA8qZ+ldFQxUmp7cLBvz7RbGeItel6RdNibcyQgr/z7y4cp8D4oMN7wOUeyXnMs326sCydksDj+PQPZcj6i/3ICt9biaC84CE9yOTInF8947LXzDH/ScL3EfXAW2sNMqIKcXw9ll+EpJHlK19mI3RlmoitEzB9F3MuFWuCOGGa6KHv/Y8LYKkR4duOZTDLDV3uSGFp+dM7J9KDt5x+R5UmJbLuK1aA8Nt0HfkyCfN2CnfQwcOvX4amgDjrTAum5heecmMhOIOYFjFvwVV1Z8NgiA7BX89GCGXmfccG6e1k6M/JleV0Gew6npSg3GaGrZJxeOWtqecTsSqRr/3a7LJ5LrPDpfe6WF32LncQNeaLlr/0O477kZ6eLHEAUgvoUuhsLpqPZVsFkwGSIWcpYRzJyMIf2uAtdB+H86Qro5Q6l5CPoodg+TG9JO/FJRbNLVnZCbQu88RQAstceUPIy5QV8MwqX3O0NlMDkGcdU13ISYSeaJuhg8dlJ7YKICq55jtYMXkBD3vsNimtlLuvcDCXvNxBLfVy4bppuBDzcCSp1C0ehZdKHkEY1S0RCxqoDH7Ws+932C9obEEXZjilAeej2WPGIXu0ePiKN0NsjMfeK5UY4eJ/qP2BJ6LAqqyxCjSK19SI2ojRU2UAxQNUXQQbBvgoO2K/gk+I8MIaztw6pCZC6O2AxY5z96jz9j4dkw6LWqfl3DVC6vebktcm8HS9tM+dYb7Bnn6fRWl/2Qob8ht/HN5XUHR+x1vNuPHSKkMBnnxNfK727xjXrvKPhAQoD8QwBkl/6k0X3H/nBaKd35fUUtjKY/85ThjgxruldYOnGfAxIoMEX45Jjm0cQ+th3YG9/VxVkSm2jXUBkZqNeDWk6H22CSHop3PoSHn9KeFAOtfRympjtQWBU9JqkkfMxF/AbUyL7ftWGQdcxJaRtKUFBY9GcIQI6P+sipgjGaJmm/gdLXOyP/Ijx/ChYfc1JBqPPng9IrgfgaUzzwA19PNEeGRNZdUB1dW7A5qEIpDB04HtjN4J9Pk3kgMwrMeZ7/Muez8fWCH2wez5VRQIbfmF6noeXRn7kGBo34McZRZVvx7GkWFU55OKKa/Xototf0tR3XC2YdyPa7jeKSSQROhaHYcui3ra/wuOp9cUGkm/n6vO8UucMnEesVA726rwjEmvks8Tm0zvUtUhks8NkkE/1EpmJGzcKE7XRmP0EcDV01lViQriTd8g1NshXMsJ5txH/Pd0/w1mXs41p/6MEzfUSiFgzjmpXoxNQ8aaG8aaZhcUmKJ/F7H9QUDHJwj06TbwXCsf1anovolEZSG81q2i1O8WuUmgNb7FwoHyPL8pXLw86nK3I3oe3duhwu1x6FC2WtUKb/LINVq9RvTKCY6Jyzxjq/lxNWIAzCZYxVi5YBuT0p2TamwFRnzWUWVHL+z7uV9YjsrxSGImFMFTXNpM5U8vG+bHRJhTkfg81iu8xYY/g00rocycia/bIGbXrrcmkOA3IFUyZ7QQivVXPcjHz88UOqUbFYywdjTkA3dG15wpdp5LheglsZQsXot4ZZ9BJKhKqUeNME8yuktBqUwe41wXaDO71Pu+Zltfb2vnsPlaisAdN434/Kkj8NXIaQYBJ4e0kuav4mrUF1hroMse/+QrNlDdNqj/B4LXFdlRbievL9l+MndRWSOfSQJ66qBuowzM3VAXSHLKM513ZcJLV8/MmSqBYusJSn1LrO4LuvUuvEp9DdXltMA/70LQuilElBoKGXfjHDPUmCPwFul5UXon3CtOmD0KhE2dDTCa5jnS5CsasEjhJr4c0XJhUOAP/BySA23/LO9Q7rr3bF7hoftRtaoBhxz6uNg3sJn6MnuU61DCKS87iLIW6VXH2icG/Xm3VoSbGEMoWxoFeOPikz4dhZ9bcDFfL6y/obcI62GgCWucnfMnALQtkWNWVNBP86nvwRWqoPmTUojUA9eaAqTlLrumEN7NlxvuTi7nlr+jLuyvdyW25m2jtS0+yifuU1LmvlucZHdf1fX7f9JLbBGx0T6qZVMg9wjVkJRYRcPxkqT0EtldESjssp0jXkon6lkCP9JQ7qkXVSV9MZuEyN7JNaFwOzLSAFfVOxRT62Ww+DhfcWiND9wwESxl33z2Hxd/HGLIcPt5wsq+efrliGmNRd7BglE3q6VfQqhHm2cUv1o7f+CCac27ylI+roMSXCiCpY3laznDnNvm+3XgdTFhLXAbYN2CGSxhAtYm4MrkztjSvynJkdKZR73XiO0eb0Ui0kafNjDscGtarCeYbydKryXH3lHZkp2jUX2rk7wAxD1ohHMMFforbf9Bt8R59EG7xXkmU0ql9d05LIGAJnldu4elcSyapzuob33p7RMTUjGE462ovRqPMgBI/w1nkaP5NU8DEeaEnm1/XIridr3tm3u5IS2Kg+mBzmTQiEQ1bT+sHbaGVViKrEofKuvgxuzzQnrjpfAZbyM9meNgIxf/OWMWsUM67kYqkh7yDbnSWlZ2oTsmVZH4/gLyp0maO5LBJxasrm6TTJ+V62c3k42vAc/v91Wxhc35Npwz+03WDfyp5BB5XzM3+1Hk+vcy4l9FwaKbEgCbNLkVjuTbTToWIBP/Ty76CBJoDKwVpByp2hIIIzfIMzGHq9WawdjrCp4VyEXFxGRenTZpWMXSlhSWr+KUvmOoIloaYDmzlvNNvpyM8+uWhrlMo370x+1b9By+5TkG5eLUZjDM79nMfQ2u9lHLqunLceFPM+blhp1KbYqeEbcvMOYSghgCPq6Iuh0aABVhs6oIBp0hscs3Ow8WoBnZYaXmTUZ9cCAfBUkvx8V2hSrqCLV/jMa9HFn+dpdilR0VRk94ouhTcNVnqSD7OtppWVf1DbDtNe9npuM0Wa5M43ejQ9V5ZYrEWtUrVqJ2uiOArLI5Q5cAL78YwAoNe2hHsfrCKwuk5HntClic3bb7wPAEsowdoppwcmL34VQxlH5mqyTilrVCLztssx1Fd305CK43x9JgNjmNWfK/D55EnomoJ9Kplvur3ymX+ni+pXQ7Scxp8hh1fztv9an9qD79tg8nzcOoQ8QVQltC8nmKQwQtPWEuDT8XnN1o/+tJJbYu2TNCyNUN/Y7ft1P2J5tXzbvCI9ivmjQY8672XWtAgeHQ0qZjWdlXIq3b8nEMx4NUEVfKL6X3tu+sjPlCaokgaOHzccoLYpihzGD2JyoI2KBmyjY8KFZ9wTtGVLp/Ev0l7QvgeBvAIeACXhbAI9CABSAP6tSwpW/s80X9pfpwz3sJmFhsiV9vs7UX62STtHTYKpvn+Cq+7aJufSnZX5IHe3S5dUHKSGnyiPH4+HofwFf2bAMqFOngWxMFyQBbsxA5JxXBK3Dw6VCxhJ86sE1WHPcYLPMw7trCYDT1ykUwRID0Ufh5wAPhZKLXQPw8wsi9jwuVD5Qi9Ai1LD3gZKff2x9z8rjgh5uBHyPsDZhoDsAq1RAQchxgE7g/jExrOR/ICvyG2vQ4N3UK5h43WrC16UFgINB6cxtpsMXIAJiiAIC3Oc66Pc3ONzt8I3392INCCdccX1PFnsuFJZYCnQN12ybvj2kD3X9MCLcE5xCtKi1PPGyYxYlHYEXNoWfojsc+SRr9rimV7wkD+5CWTr3aGX0Bor6lXsy5JcEN3QOZCvvfJty/n5RKgLpJpsPigKN0P/rrm79O914igB1+N7I4nOzQU/z5/ItAXD64NQWcLmEUAzfjuwZRKMHgO/+f6QHzz3Knz5hRj4jP8sGwD4EJnCXBqd5B/HXnNOzuHdX0WDSV74s+cEqB7C44OSNOxlQyoMH/ncCpWXMTmDzGJn8PRtQdwA4yC78MxwufQnJF3pSw/wHIbHxRWEOTgbMoQilikV9QNuWna3pqDRleiXbS8QfnQg7xBuGXy1m2a3HC2Wtmly9gqyeP51RXrlzbtr2ueCjJFuPDGCpyCUFq21QOE++qwOlsISzZRIWqMBLTQ3ij755DJ49rHMoYy9MmVi8wBTAHfOg/1Lo+ZwL6gxEe0+ArBFpls/OTapi92amEFtxnGZtYsDr5eVTP5fAYedm6X3/QF0eOMX7ExC4/QGE3zUcgg+tNVlOUdFNy2njP96OeyYBfCCb1t9diDg276eaUFMTFHvU3ruEmNXpcj3PQXHHnoB+eLrGA6h/VHg8tXBf92mkrw9Gb686hvNHH+t81L2CgXwDTEn1KGg+uAatSc1unAtZzRvHTTL5/JhH2BxciwUgY1sRDfK7AoWaF5EI2BFxShBAm2T8ygsGqac6CedHKt3rZRMxdVAJtnYV9Euwx9dVcpwRlYCj5entNBS2I3lY/cQPKYROYwFO33u+WAM6xue0DnJ/z34Jk2tmPvk30a96CrpwAYFNds5yl52VWxrUCDtOkJVr7MlMJs8Rb9QmMvO+BjFnbRZLSM8qn9osRIvxb7dK1TcqZUksJA5Z5GdUPOQDLemnzhz28noYyoS3cw0T7VPZPrFBTIyryOVfVUjgT28d8UmAN8CQRlV+BOfT6zFMlL4/bd1+tY0cvtovCxxYTzMxMcL+o1tt+H6VpP5KEc35RM92zrnn+44lkQbG23doD/xJu7ehl0QHiZPijtHjPvjRUpMQj9xWqo9wROWFvr8hMbxcWh4Pi8rjNWs/8plN93z3kJ7OXLPkEQc/0zGg/iriqcjsfm0DbCAYApGOajdTZ5gbqB1qlhw8Avr4JoE8qx7/JHxPobvpQzGRaKdlF0gcKgqgqM+brLrlwwrUGWMHhuHuRhzetVOwEVybQc3pNaU0MBxI7Qgp5k2hz5Ei4s60cU6EHbTQgQc2Tu8k7BtquDGUxkxGNOdOtGM4y6zs9m9htvHzwuyP4foGq5ke+7H3Rei0gRzl3O+M399aB/ygiJH0rSOFINOmQ9nzARWRqnaG2FVJF5JEdL/gjAa3wKOxyEzYWmSt6NGyE8ZdascIbsSBFeC2b0vTQ80gebMM9bJe96RB5sysKzuGdOjvkYhdEcy5qUvOQLqFn+eE/Vle0nZ7cnMgSa3AoF4Q1uEE9HLAioWz2H052Tf5fPDqxmhmG9P1QbImAf29DatqHJvh/U6RKiIDUcy9UJupRsZoz7sgJn3MR0QNYGY3ytAGKZIJ0J0hga6zarnZaGk5PSQCjj7YDxlqHxo8Cy3alrIvQBTyW+CtlLSZA2xC7ZOBS6XSNKY4R7wM5CYYDmO4CYeIW4Jp5UGELlR+qf7xN8TXXvoja/XEjk
*/