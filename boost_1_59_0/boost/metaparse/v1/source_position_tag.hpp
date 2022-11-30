#ifndef BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP
#define BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/source_position.hpp>
#include <boost/metaparse/v1/fwd/get_prev_char.hpp>
#include <boost/metaparse/v1/fwd/next_line.hpp>
#include <boost/metaparse/v1/fwd/next_char.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>


#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct source_position_tag { typedef source_position_tag type; };
      
      template <>
      struct get_col_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::col {};
      };

      template <>
      struct get_line_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::line {};
      };

      
      template <>
      struct get_prev_char_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::prev_char {};
      };
      
      
      template <>
      struct next_char_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            typename get_line<P>::type,
            boost::mpl::int_<get_col<P>::type::value + 1>,
            Ch
          >
        {};
      };

      template <>
      struct next_line_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            boost::mpl::int_<get_line<P>::type::value + 1>,
            boost::mpl::int_<1>,
            Ch
          >
        {};
      };
    }
  }
}

#endif


/* source_position_tag.hpp
zLGiV9NHDyxm0csYnH1miUqjR2TivBqG6U6McsK8fwCAQ0tVulOsMMCSNbptG9+2bdu2bdu2bdu2bdu2beueyeTcyV8PlfRDV3el0KuyOgWucc9e8VtyqbHcrMCSMsKtwEbW93tcPHQXTrEs3UKum0f6iTF83mGLks3FwwN5KKSHIrEda0bK6yqoAMVIEcGNUqPqOuFsO+etjwN5l6fxFSJD7wYbxhuHelWyup2LPNmiKJvO9HJjSalhbeUppklHah++5t4MinDHTrfwa5ntbSFddc1HG8tsYxYWEWscRkWEmtnyHjFV4syVUZ3VaAYptv3wd4b9RsYNgddjH2cd0BGzPGsxXCYEAtlb7ymXJR7PWnUvpE50Ik8UbJSxa5zRQTrOnjXUjLrSicQ/oFgcq4AonfQM+dl7xJKS24iVA8llmmjPopw7jg3Oo2y2zIzgpST06k6N3BHpg1tZcnOJpB/9kU3MkNliao2gNxBXovJdTlW0Z3LQOm+0+DRIz2lwdQMIcldrEJcs2kDeJ1ehykpuRl9R3F8nA/uyOuDdTNiBBqHSSXPp2JXFH19W+nYyXUeFwNS5HotKBIFGaD2u4nfQxVS7lNqbECONx2n7pNJI8t9g5RRVmJD26Jxh7R4yiV30g4klbpP6S8wb8l+TqK6K4/WpHcI4XsMfVG/tVWYdmWphlRk3IUwNYUqaTb5z2QbILgdznvIWp5rTJzTNjTimx1AfW+kE38Ps2buddks1EXrrahmeEwq1KUX+P1/sz7qOlCf+HdrUAw0CsjZcWZn4g1rux060/lkp4Sl19TY04qF/7IrKvazkg6PBkRL0Rl8Yvp8c/Msfe3NK/qZF7o27oe99ax/daT8kmVhIW0grywfq5v2gPLYU7RcRnlzi96IItvhMfhDXOdrTs+gV2CpsSvFbB1EIl9pUq848rK5afZ0SFp613oF6yH6lkS2CBKP662vuPvA3eu3DmZx8LDZoyMRCTXrqzhIiPvPOx1fcO2fSy9fJditXV3/73LRjJJvFLCdfoBn0D2NkJX7FfFaTIeiCdt8ADIA+ckJtjuV3Q121tSP7EXDE8l47ttALcLbqfSwOj9qD5nx6ZE8eN5r5SpXxo99EQ3CW6UUfGKKv6Q9/TIMJ0XRGQY3UI31M3SZRZggnrnW9ZZY86glVYLSPZwzywt4zQEIIWIZbso4FoSi1F6QZgib7praxDSexDf8ss6PrlHmeg8+VN4Cvd+R9gjSl2nfhKeokItMZcHMgO8kdDS4pSudCiDdQuhYZphamAzs4NjJuKF7u2CwAAQmO/DTxe1+5y4qTm5rtLpu9ugwRPa4+3dYbZ4Xg473xhXG4A18m2XmQbOIuPmCOmz75XX8tXCuybeepXltxq2ABNc4h6IkpMdKMJyqAct+HUjZYYGta5PS7puJ4N4tLK+y3uWifZyt3u1LEhwhn+lK8ZLe7CxV67fJk2zZnswCCthn8nf+teHwKzTn/pYIfaAqiotbokWFm3ffOWnv+aD2nILQnJmQwt6rZ4kyFPyhWa3XhSzdnn4iymSU2bNe+zTpcJ0utZGabQQ6FNnq6JHytbUHm79jDjLAPjcJhBqbQV4FSwIFNGCZzpdR32bhfN/VSyfZkjl1EZO6agYDFs2/VJfQbT6XKByF971D8ZfeZdbKXP4R/iKsv8PBCawoIxUGrddgYBj57IhP+HCOB0QsqTSE4HTIIEvtDoBz9KF/r9zuuJd6PkDtEJDPyEwtRgL2T7Ct/zZ0f9h+zqhIGSe0d3xB9zK5ijq/xPgXc7qoskL9XB9TyeDo7NJJi+AuCb+O5PdgCqkZOWoOSov39CeU9O7pylPDRkaateURmwGKd2KflaEyiZ0Gdz43N8uSlnigLDQDr1FC2xfN0OCVtsRzFpDxH7HWgUj2EIi/Bjrva7YZJN7cfQ/DnarFZ2AKictDgEC3to07C9OJKKV4HNpwquY4xTMfclhoyH1NYe7H5cAE1i3+RdkyMWfzwKtzHJ5sblXCZ83AdMMRR3Ok75NyzDfpV43rzUa106V3/WzNGQwdc61iTKZXp0v94si/r2wI4fpOW6o98rqtjeACFDVP6weoETAL9od3xFRvnv7oCnf66nTBA1toWkup7n6jACnuehNG8k7i8esMrJ5eAiIClFGyD7uG56UtRJj8CsbsfEMfDgXYoyXZUjvhbT3t5L4W6MSi1YxotG6X4dWC4m/H3REGRvvIc+aRNbPMutXVf4CBqEIlj6l9EXo1VMOFGSBsU9mto3fupZ8FIwlmeL8J9XDlE3P3cHbQVO61TuDcb5TU9SuoMsMZWkf0e6QHmqXiROgct7ZOtUfBPYJEWWq7qPizwlGiFvNzVxJ6TsBQ4Io/I8A1CPYQ9ctGlxNQBuYXyBPbUAeZg3OljRiAFKBZ1bxr1RUcdLAwWjlTr59s7y5SedkyRF4Vh9PhMGXNjwUcn50+C+zLPoDDQnnzkaVDXwx8Ej4YHn4YLLfxoL13W3FNh0KkP8jDSnPExfPNywpY1oC8tjO/quHroHZhcXmgIT55aZes8E7hgeUCBRLbGxEEpzjW9ANH8JEosoME3uUHFxzlPhdr2ApXrR0xz+/1wUGQwmA/JNW2oONq/MgZr7Kd/wic8etp/0H6SAgmQrMk8jRqUsqLM6GFaVSM/N8d1dCrPQKEVXrnKxuvxubHTzqNtXnYDg/9z+DgatnMO9WGmDTmj5xeJELnhbaPy+intlpoEyAzSBgsYVevSidIWlU1RdIjTc1kimUn3/RXyWvlc7o2x5lsJOr+1Zha+mKjT8vh20OVYm30bEvvJI4ysf6QstyYPBkTLAfDSKmjLI8F42TRmv13bqLQ/cARmYT3zEjR7ULBkPMnYTsCqQJuKQ0iWLKAkNz+BUj9sz5pecNqwutvMqnJkTydexz0lh6pFldOsZfzeF8Uhn/A9V76+UrnrR4Jqeml1IY7eMojb9jLV8+GT49Ruo7AgZdHna7YQO9jz1lxCB9DHfinYjmM3GjpFp6bMrJ8QSqWrGZR7t3LLBeuTMgwecD3TMftgOBPY/HBOD/j9CXV7hChG5WMfthy6/yVjsFz0gdH9wExyQF7KSppg0kb45StjiaRLVHxSKe80eMkYpKYA8Iw+vxj3OrNYu5Zryldmmi4kxjEayQV7kKwrIHPQywxEtMPtXDWtPH6bedY0BA5vn0C24Qf543v2wn7/lDFdO1Riq58HzIDPfIv8SWX0Klpa93E3EDg2Ep7OC9nt2Vi5LbDxhKZrfqmtZM3yPrWmkkcE8ftGMQhxHO1W4dDeuHzv7Vr09UclX9+AP3k+Z2QQX2sZil+3B0exvNePum5PJG0eyaeBNB7qyQ3HlNYTlQB7j4USl8nt68gDnxIGCfDd4jV5qgXAJivwQVZgAvICM8IjUABZrsNSJLXgXgVFQuLGDLBePjBrK55c145UGXxs1+Xz+8SwxpILz7BluBxL6o1qjbi3V8T4x/ceA6wZAlEFMCrXNUlANUfI/lTuPZLgXr29r/53R/1rRG+4l2rRmkYTdM3NFrgLCkKEEJGtMGXtjvbyu9lGWPgvqfby6+HJfHFriUxuWvRXu8fiuhA3K9eAlIQ3gn1xIWz2EzMhDcvr12NdlA0WC2+KlRWXcxxoQJYrZBHXz4DpNcc7bifLAL/2DKzRwKcv8kdVTe7yArIzUaw2cN/lJbVFAPST5glU+6hobJvNGgjBXi4cmC072cKOCoIMi24AYdPCZH3g319IeO4kXzKU7A+KBn3yfrHUomWLz4ioKyN/mjxkvPsktIScCsKYgZRuiw3zQJMlxsUIJqnQatsNNh7sOiACuPYuLPBHn0dS+e6DQ5nVZbN4r1k5QtHsrguWH3nyok7yzdflXL4fbBttQMh55huK94ZUpFnArjugRlB9GysJieL1DIJ0IhYDFjMzGOyjm7J1kYrXhKn6ecZeqXR7bjRaTS8KUt6M4kxcBKQT1LRYpc9OTB1xcgX7w0OauMmswhNN3PtTXoY5q/sUCeW0bEvf2U52oRyy1eSK/JHuSMmthIIaTk4mH/4x6s2r7pi215dygREZ0aedTlcjr3SQb/37FsXAY8qBgRzqHOZPYMCz2QiegtOhLka+Zz8DPwUSsQQmJp9a7ZQDBXnth2WKWLIJeeAqx020R8iHC3EyPTw44oAWFp8KMg2i7LOHtEFf3c3uFIixDvHvg0JWFjwasszHXxSxqJDSYLMopgGtJ4DpF08lEu7XN2YqVnFCLP1NmPkl693acav9zyeaBakQsf/gGEF3Sop0pQs4rxxdJaZjt/+eQz9fGZ8NiCrM8Z7Sy+R7MBn6wcXpNA759MdheH+Dxx7uXVmDy3u8l0W7XpteuoSIbSzTkbbtJNP6rZ4hYY1uQG0mxgR6mthzqNLcARc/J1cNFP3c8Vko97L50YiJ46GfrRuAnycEXTu9FBKgor4R5hmM7kA0EIgWILaqdpSC+g4y8hFT8VKkZjE8qPDyiq/2OigFb/5WfK9mnwre/aiUfueJGaXgAopiSColTBc/okyHjNb4mswko4NQprYXgQLpUlB1ic2YU4uG3KqyVJdiRcbvHI0JvNgKMbAJ24DemvNJIK2Cz7R935tyqUNGt7ZKnXAzUcGtGw/8jtc4k3DwpmEXtsVVY6hawmJneMI5vjtgq3e5J4M0VdmMEIlNus8lgRhziKqOj4mP3URtlnSRjUKJvd4BzQrT52cl2sYoT46Yuoc2qvUGF9f7FzZMgztWRUxyrs/Dsmi00AM97YeYXlQZoRxi8O3SMSw8TSzYN5xTdL9KJKodS6I6iO/Rq4YxJyMz/L7ChPBxnYZxMhBMSAUNLwHqJ3cdHlT2LtXc2Lz/GtYD7zayVb/yadP1e8Ml4Wjcmmw069rEyvvAnsdYAk/8Ym/43nDWgslrmpKQJ1mV7+0+nktWi8UdzGE1vlrEJrIuGpo13ZzR/E84a4EBUVVY+xN9nJ/tWA1qjfyYx1OHjhuTwAS2k8nPL3AC8bLkuD5nO9seTGZmZMluPS+M46IIxDu58XfEgoioZOvg/i6AjNzsTBulEMTxcmgoeN+yaEMVBaLQ+vPU1jX1/aDCyXZzot87cNMATjwXy+4e1sTXsIWKYtLnp+llxEr5A9JQwX6nJnAgJaQbbE0HUPVjVtNfGtheTq5bJpTatGF8CUOitOnArF1mRwNGeTqJVEgkHimv8TOPGvzrBZTag/cphIWPpx4kROu+mOmtjpvM9JIA+VdYy6ny4aZdj0GjLshRkaBzxBzWDVlH8ujDJzH/NVc8I1OF69z2gxwONs+iDhS6fNUZZ+diXIv3iOhkQL29IL09PBZV7c/ULO7C5K5gS6Jy0M30QWu61PoxcerBqMiSrd2WnN4qqDDH5l3NdMnVirTsxNUSeqXZaV0NzFbpvam41T/H80I1DIu0d7WoimB2p4kcElbmvZf10THFhaI9g76tvAi3XNf2Z5ILR7Xu2j7GJGQDjmCww3Nu2Ma7ORFwGt2ycMpc34bmSAXT3L9aDl5xGLgkirvul++n9TTq6n8x9O1tnHcu7JVshEBf23ehC9+qufzRyw1deih3e4jIeTTLbTalZ+uRkcDgkSLFrdQ+QJN3ogkwHm65+5Mhs+yjpuD0oULCwXrd9+ndNBbf+vDCKY2fGmPLIQg45of9lE1rSlodG8VMI2nRyldRPXM26ikUY7XGIIspvFghTLQ2TX9khvfaAUUcjCY/Ngtl4/84yfMe+1jcAKZqIV5jsrxOaUSXwPYkjsw19yKTvUojL9OTbGxjpFcmX0FhI3xG96lERLXoABmIk6tRD+zevK77kDu+nj9MV7ZTUFdCP7/oG/WZYUxZ/LaGjMIVjmurbyEp5nQ2UEaogCLl7dZOd8ZKo63qVP4zLcqFEC0h0nsIihbJ0dJzUQVws6Se3142NAsXgxArB5WTF/5wS7Mn75TNi14vIxZ3nj0TbEpP7q/A58qYcVdqNyhWStZV9QpTthnjHjJhTnduTx4mX50BfwQPD7JIkYlisi71ipDjgZftwAEACofLo+78kucctKEpquKr9i3VnuiQfBe78tFC0nFXeS8jSF8w62SUYgCIhHWV6OSiGLQFUZz3UPId9ElSxk6lNgH3Wfr9CqxaNXXgvf7J4qW3luzMEJCYktITaTYF4mJoqaXKKfZx8/lBeHiCSWFZkvMZAmz3FqGXI2ppK5kL0kA/KgqvRHtLOolJNaWr4Y6AhttW633CfcfMa9m+dlK4ISjRH37eHzY8NdVUPX1ZtnZaLc+j0e6d6EsvEo/u/7nbO7HPLrSc1IckhWo+pLPNz3Ae9uTXz/ncnSmL0n3EKOs0hm6wEiU0yxcfWa4IPOLs/W0ZuxXjvQeT5yp7w1O2PVAc5LjDfGzhaQk4Kn9hweOY89UbCb7qHrOhvLFaVbHHWAsyXhA6BPFBQAKHsXvWcTPhiXbMM6Gf8L1KVaz2rGX7/DWtSxYVjM/VrhdN0If7TwA3M5ohGZctQHSpCj7dyf8k1/I1hlV8aeoZbDKK7X3Ez/hcuVTBIRyDN6WGKA4GZvH8cBJnZVE8i2g5tushyndxHvsrPB7pWqM5OjRsdXmQ3A/veUUeZJiZ6KjnSiEtpsZghzFPmgnkgR+kRnTgrd3diOPWIWvqg+ciOwDG/Zm/XltW5nqspGpUW2qQffyGMIiNjy8EDfuf97cQC4ugmtggFtspSzMq23zTHIKdDPcKKVv6EQTEKRHxjv4HAh8p+pkFm1vbUSSaIPIjiKQrISCIgXD72UOITMEGv41VEgymYGaMdDkXqlTezmyKplpwJNrSLss6TaLhYyemxowchay2VWhpxw1iSCHlWxQNNKI3TX2WTQImMKt1N9dbrSlum25jg6C/B59k2TLxvqX6aM6J89NlScuhMySMbnQrsaVrrt1kbywlCNWTXYTPOmEBetopb3TrHrmY17JUYYw5kTmUlXlNLv2wzTm37y/cKsePVHArcLn0HdH0q//uo4TdxzUvq5UU7lg12J+FSuH82NdN/2Z4pX3hLhOahFR9+LVlmKcP4GkmJ1/ioHmSZ6TEoxJgfmD7nh0NK7lbkkku8z8LfcYDHlaWG4GPbLfJeTuIZkgxOEWQI8MhN13YZBirF1+030+TQfLlz7iIlN5vexXa86zngr51V3EyQIDVhCEb+xmFMZTvNVjx5kkDayJ2jpFocw/qdXRKTdwZ8k1xbPBB0vkGgpATmlOYOlJAQvunUEwCyV9QgCnqNKU8aJvbKI7z42pLXpYxaZnwtdIZyA5An2x2DLSSJx6+I+BT+2nyVXni8vCBBqBeA0Ma0i4UR3JXypyWodJid2l7YvbFRqD2btxcE/tc7f8braT0Y4q/VX90/0k9eH40Knv+0FZjOvdWxT2XvtcfLvAtyscXH0fDaTEOYmjunaG0lRO9rjVT+3mCBQc0ocXp7wUsNEQ2FiFEIRI77WkIXoD6pnbfoLb6i2mH/ft3jOH7ieE2fjv+CSi1duJ5agqts+0OFc7IGXu7ulFgqK7FXjcLcpFsaWNVbSSrN2PlQ3Pfn5lUcd7QH9kfR6TWbExNv/8lBAujD8imeXJEaAv3VDnLJeK1rweNFnWE4QyeFyIQKlpdw2X9MRrj
*/