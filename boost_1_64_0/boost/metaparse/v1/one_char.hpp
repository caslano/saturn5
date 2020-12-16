#ifndef BOOST_METAPARSE_V1_ONE_CHAR_HPP
#define BOOST_METAPARSE_V1_ONE_CHAR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_end_of_input.hpp>
#include <boost/metaparse/v1/next_char.hpp>
#include <boost/metaparse/v1/next_line.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/get_prev_char.hpp>

#include <boost/mpl/empty.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct one_char
      {
      private:
        template <class C, class Pos>
        struct next_pos :
          boost::mpl::eval_if<
            boost::mpl::bool_<
              C::type::value == '\r'
              || (
                C::type::value == '\n'
                && get_prev_char<Pos>::type::value != '\r'
              )
            >,
            next_line<Pos, C>,
            next_char<Pos, C>
          >
        {};

        template <class S, class NextPos>
        struct unchecked :
          accept<
            typename boost::mpl::front<S>::type,
            boost::mpl::pop_front<S>,
            NextPos
          >
        {};
      public:
        typedef one_char type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename boost::mpl::empty<S>::type,
            reject<error::unexpected_end_of_input, Pos>,
            unchecked<S, next_pos<boost::mpl::front<S>, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* one_char.hpp
/ailTAzGL6J8L5/Sz8Hx4VdR2TaTmb4/a/pvLfVhfsbqLirb18/h2y37dyRLizOm7zPFuZvooj7645LvEWNscFzJnwgH7YdfNvehjt4r7Rzi2t/9UU17kvMA6Q/ooWyzh6gNdQwH0A22dY8iH48hH/A3+BqyX/816reBjyt9GaK2Br/E9CXpCzzJ+C4ovp9CHp5GHo7j5/VxPkrrAuAwO/ycfmZoKJ/01v+BT3cOm0qO4EsUCH+t3l3nLCRHndJ+9zN8z8OuH8CNQt0rWvtK64gCWHm/u29Fb3xZR2vf6p4OOqmpgaU3Tf/p6qfhySm9X2FdTf2mhluL0pzmX9z3H0eZZkz4PYsXe0GNCS9iex6Jvtp2bJOXtC+vzrC9jHivRMeMNalKtobP19jY9TrSPcmbk7n0Uu4EiXSiWPp+w90Hg2bOjsCKPunNNAdudi+mS3oC/gfIfqiYThBOBPeFPNnH8F2GRfgGw5t8f6qqO6mMnOnM8VtqvHw7Cj/VZ51Gi1vTqM7UqvPNExvZHMrMI5QvPanRfkM+HOeIFuCKtp7aKO+0gjy+e/V2bnTzwx2s1DbTFI+7NMp+vSvx6KYVHGkTQohfh/ivhhEf6ztR+db1jTId6AjZNVCd8R4uwgdcqKPEj6GsH4n654xv4phH/MH+GOJPb6TYjdejdK5rSeW5iPu4TCeFg3FgSV/2RNr7VIojaHTX0wbzDr3N+Z5G37s28lEb1El73zHpROD9R2Xz4zsgjTRW7N0o5yr7wDfw7B/zgON9bftAHr9OAkzo92xqa7e+wLNouzmUDnn9483cRsET8BPM0zyJB20ZjDff6j+0D+n/AqX/C5X+LyIeIc3SJPlPcBY38rm+3yc7SNTRP78+WKXPVP1rCfVrqBudoaI2mOgcanUabIFsxzbCl/YCZNGOed5Way0dlIfqCWUsE3z679dbzviEMqx/ynGAxuGMBtD10VhB7QhrEaac4Hv2uogOpPtl3k28AB2634/LrKexXL9JbsrGR0u7ufbL9hyvzGesfMT8cbW/TNnWUOZRxDekAT76hTOQxroAGkBf0DimUc5jDnUcq8fsbohFYemPHodtauaccdN2DdIfPR77RR/rFwONNO9KNPrOBcPYK89bAI66E2qyk0Rem/E8+JvAazUxt92re7pX9VpHKDAF13mGkcf5AW8ProCwiiLt2dm9A0zjbzBvEDYXzjquXYd7zp4GcFiFd1KqzGv4HmkMeus4m+iGTcoV7m5PO2zuF3L9KfJ1RiEP8J/LbN5SeodwDdYh7a8D3aZGEcXEVDkEHB/2EbEliX4lQ9xKhf18LD8rym+D9fj2oM2ugAQaj94OcTtkdTXH7G0B15byjaTXjSFagyqwuTjAXL0uNtL8ka8574l9k85t0vzxRNZHU/B3St0TsQXHB4CzeU8N6CJ7e6FR+oinUj0gn6VzWiONOedgGVCevfdG8XCBWn88s1GuoW4gHnF9hGhD2SLtbPqmvLYskLn/7oGPN4rzFbCvLdM/0Sjn/1tojA/83iWk5pxhTt9/TuSiRvae21l4F6wqq6jKqqNvQRs+hRwvVbI4GvODHaFvsF9v49mQxWzNKBn2y+pzzH4ny6ynXIllPhemPJyH50keoP/mJ8u4SrXHNjVnuJrS3XijFiXPL6Ot35fNz65V+nod01egb9dHSV8hXfL8NaQ5jdH8hvKrvqnyfIvPKyDfh8KyHt+hdMhL/CxAud0AsMCxZAftz/eR3zVBNP8HNtW9s8mWIdaDYdzEMVT6OLfQvAr7CcnyRuVn38ba5maVdkejPCcPehd4d8iPVD8G3ae1OJzXET59w1wT8ck3gHJwDZbKgp/wDX4=
*/