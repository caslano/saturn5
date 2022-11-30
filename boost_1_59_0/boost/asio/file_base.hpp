//
// file_base.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_FILE_BASE_HPP
#define BOOST_ASIO_FILE_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_FILE) \
  || defined(GENERATING_DOCUMENTATION)

#if !defined(BOOST_ASIO_WINDOWS)
# include <fcntl.h>
#endif // !defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// The file_base class is used as a base for the basic_stream_file and
/// basic_random_access_file class templates so that we have a common place to
/// define flags.
class file_base
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// A bitmask type (C++ Std [lib.bitmask.types]).
  typedef unspecified flags;

  /// Open the file for reading.
  static const flags read_only = implementation_defined;

  /// Open the file for writing.
  static const flags write_only = implementation_defined;

  /// Open the file for reading and writing.
  static const flags read_write = implementation_defined;

  /// Open the file in append mode.
  static const flags append = implementation_defined;

  /// Create the file if it does not exist.
  static const flags create = implementation_defined;

  /// Ensure a new file is created. Must be combined with @c create.
  static const flags exclusive = implementation_defined;

  /// Open the file with any existing contents truncated.
  static const flags truncate = implementation_defined;

  /// Open the file so that write operations automatically synchronise the file
  /// data and metadata to disk.
  static const flags sync_all_on_write = implementation_defined;
#else
  enum flags
  {
#if defined(BOOST_ASIO_WINDOWS)
    read_only = 1,
    write_only = 2,
    read_write = 4,
    append = 8,
    create = 16,
    exclusive = 32,
    truncate = 64,
    sync_all_on_write = 128
#else // defined(BOOST_ASIO_WINDOWS)
    read_only = O_RDONLY,
    write_only = O_WRONLY,
    read_write = O_RDWR,
    append = O_APPEND,
    create = O_CREAT,
    exclusive = O_EXCL,
    truncate = O_TRUNC,
    sync_all_on_write = O_SYNC
#endif // defined(BOOST_ASIO_WINDOWS)
  };

  // Implement bitmask operations as shown in C++ Std [lib.bitmask.types].

  friend flags operator&(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) & static_cast<unsigned int>(y));
  }

  friend flags operator|(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) | static_cast<unsigned int>(y));
  }

  friend flags operator^(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y));
  }

  friend flags operator~(flags x)
  {
    return static_cast<flags>(~static_cast<unsigned int>(x));
  }

  friend flags& operator&=(flags& x, flags y)
  {
    x = x & y;
    return x;
  }

  friend flags& operator|=(flags& x, flags y)
  {
    x = x | y;
    return x;
  }

  friend flags& operator^=(flags& x, flags y)
  {
    x = x ^ y;
    return x;
  }
#endif

  /// Basis for seeking in a file.
  enum seek_basis
  {
#if defined(GENERATING_DOCUMENTATION)
    /// Seek to an absolute position.
    seek_set = implementation_defined,

    /// Seek to an offset relative to the current file position.
    seek_cur = implementation_defined,

    /// Seek to an offset relative to the end of the file.
    seek_end = implementation_defined
#else
    seek_set = SEEK_SET,
    seek_cur = SEEK_CUR,
    seek_end = SEEK_END
#endif
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~file_base()
  {
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_FILE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_FILE_BASE_HPP

/* file_base.hpp
qiEniXUPne6w8EDyS/sqGwLIIDJq4gORHXYR3Gn0/vmWLmMnJlh+kMef49hxBRdLm6Elg9PESn1iPDGYNVmLnS37NjPnYYGUo27kAQcoLqOFVRgk1FKvyW1f1aZAKMG6j4UQf7rEzcC8EUtNyTPRxdz5UqY/qh/nK2XjdTWKnzEuMa+z66VgLPrpxxFrR57DviVIW1aboVzhv/wbWnz/b9jgpk5Cg9kwv+7rRKvBSVoGcZVC1LVgYIckRi/MYLYt37LEjlI4H6K4bT5rKQZ29CItBXlkxJ7Fld5/SWL4Dg1bEy8TOZCnVy7ZuP8+bS45zX55wYekdMAjpiXcwDcFsyGeBigjkmEAZgJ2E+ewN2EtAWj3VEGWy9PIdniiaOJpmKThC6hAPP9Fo0X2EYLgNdnZ64sT372cT7TRSerFwC0nJ9GreWKUUwqFhmVnNZVYV/R3r9iQQMgcwmnbebX0raXLsouEF5Z9mLffnJc+RPBThuCzE+XeHa7aPJ8DDW4FTUys6LkovdITWKtv3gfrGNvFtLKXxNxtGkn2NR0kZK5vcoYXM5plUmoG0h7rJKmATx6qbZhFosYwMtKujnOdLFwWHneij5I1bR538N0YoGSRag/pE1r/6DXf1WD0mf0XJs/x7gGEfX5AqoFhxfN0zRw2D5f7CepEVhq5ADdsPB6SkEiqNGNQHjphs5U4vOSxuB7E898kNP1kgQYfZOwVAQ2J2yX60UW6bRIjEMAHTaY2GJWNlGj1aKWB3kacWFitmEjGlAq+gSsLbncAsyz+Tr0Fv581yVjmN6JpfY6dK2cmHhMf4W2U73Rg/j8rDxSNnCkZKKokRbB/nbzUCpOjTczGgLVfROHUfLGgEZ1sA7xnnHIjlHp1LvmQL5N1cok5I0sk7mPoyAOUSCWDSpBQh6CtcWqY8pP4q7RW44K1PLH/xu03XH60RT7JUM0eOECmEccGiWH6T+sp67eC52A+zyGroIS7Ui9zJyzoXeq6OzoamPtdqxlTI2Vgs4Sod5PjhfDat5zSvCr66CUgobShEjX50u2l3/mKRtiWJNV0n2mHH8Uj0XO+AhZ9L3uZLbLhBOJ7MHciXQ6r6uyAN7GI2wgGznwN7Yvhucpy64V3XvJBzOX6Wd2NYsJXYUTPIIqkJDbvPuk3V7ryrOVcEtt1TtL18bjKmg4AexjxwnNO6tg/+Eg6yTGSpMMth3wk/c5pwMdOr/UWOETJZTyAzVud4g+tXkpDgexItDAPFFcNojIxY8W586Jvj3ANSsRPgJZDLbzmLzyL9Y1Jl/dlgzryuovLd3XSVMWmr0H9DaULQu+UnoYkumkkfaQAT7MHaELMW6t4jjzzchrn1m/nRgvaOe+Tdv7FJy/82E2p/VQkfjYnwbkgdIM1GvUkItRsTNRHmlrXZaqitCbBSr0zpjzBQqecmCgIp3DWrltmp6ZXGNIKtspnmeWFpn8fCLMaEWv/QJcOSH4f1APPNIguDVatxwFipwQRIDYTmDXlhkALwPWxx9EnC+6Nn7ZsEoZcfxE/zEgJXGOjEc5ZBsVhYQAk69OGbUI/dl1h7cxTosc1t4iSR4kdgKnktW+TyGjWe7oDZMn1BPRCfy7rg8wJN0E0DC2K6ZOksxPWtHtl0dBaWRBLDZGOHcd17DYz78R5OXYp2euv0CvG7nuZ7+qnuHnd67uugu6szea8C8K32gocYb3meNA2nkKaCXcypfRvh3srSte0lYAKkuD5csySPlD0+npqavo0eAdbIhdIUHNSUKZ79WxmNBPKbsLLDh0C+H5GWNxlAxqgdNWRUJqAgJTc7b2eROfyTA1SR8HsjywGaYYAKH9C09ugxNNFC6raFtsEt/dzUIzOL9AzIsAuNgKfGAClRWhazTXLkVcRgPf8UGxs3q8s3i9tZ+F9QX8V9ySgv6F97Foh6Qsy53P0bTm0PFLI3V/Euq67n8sUFy6PW9sA3E5o3G7nYmg/C2wjtgbuLNs98HMWIvVBVAV8wkFrI3X6vDp9LWBhS1kTwL4CbAT4cl3vOBGGsfdQ7sBZAjX4O9iA7aCiUm/Blnw+l/PyrQiId8JdujgztmAyizWXTBocAfQoGav3YgeRL37aaE72qux9M49NK+nCQPyuijFGvNby2IZtntzDMzIBtgr9HIHwETSWEUD+6Oj1cD7fBZQE1nvzy68yuRO9LMJ5LOJjLbx6WYzcycpm5jTl74S683SbXL9GKvr6FJzelUdx+75eVkqiDiVgg+okjd/vKvbOeflSGiR/El2FniL1CZzdjWtV3Hb8p+p3zzX6glvfstj6o2KkpVmAVzy+6T1Vey8Hto8bMBll70qv1Ph2tPFj87iZgYUgikyEZoh1HRF6EPJF4rv+0B1++7ndkjKCNvbQiQxC6ChUxX3jmyx9IbH4Gq22JMURblqGbkXNeZ48fJNs0tvUzv6Z8IpE3vdZK01NhHkO0KvgIQgzKB9GXFrplsS++cj+c1XvNmi+Wt7+ympWaf1+q/1Tbj6IYJBsHjwr4su+Z1dU+9JzekujcWpLz+iU0pOgrGHve82popvkO6xH6waqqpXj5MvCRrinodtDtSm5By/T8VoP86v9Ywmw3BJ4KNED4/Qe4w2meY9XH8o6VT1DSdxIbk4C8g9EwiT2Ptgy3S7Q0/nZWmQ7YfDdFxqRO/yow1pSNu0tpV/NUbE9tfFFlINnByWvxkP0BhgIxARw+T+zPT11zSEhx9dLRnVrbetrmavam+RHs/7eJbe72aBOEgpjsqkAW0uJzFEOF1CbbCh8ID2QerY1LMNzv39I9MZ8Rkh8Wq5Fw0Eu14qabLhnQhmaBlc0BAqm3M8SQYxBmXHYHERr6vC/XAFi1ei9X4cVz+aqOYB82C9ks5ZAraO0vYlZIj2mpcH8N0UiMxDCa3ScWcqfEQsd1DuNsRqwpfBqX7TzvGVJIAmA+/lJ0odQ39XNSt2+fF3fZHAA3T0qLU0YtZ44BglFJM3MFw633OTHUtsR9japyjJzNMNeHxkgOhf1cTE4gV/adkmmmemSK8dLZHZz1nLBFuz6XTfVPCLncVTXaq2VDAP1u99jIwz/4EUIvWpkDyavN/u9g1nHvOqiF3mzXZlbvSp5Aval1O6rhtoOQDdoaUOlwan+01iQ5gIAtgc5cj8l3QjcjmlTnWu1xYQ/Kmnd/t2xmLiy9WyB02FgD4j6olX6icF5/JQhv8U2LvAwOGQHAZKmz74zW52QjBKCwF4aw6SEudj6b2fEq0tmfhbKGm65lqsgRotJXR4GorKKIRY1+nVeEsjZ9ef7pDv3YoWwvTJBC0m92INAa4G7mg5j2vUJpgqW0NYuq/28QTXeRjwb2w3dJbBGoGRXkAiCXdR7+yOTqse6dcKcxkJXHebKq6ZbjPSFD1u0ICp6ZKj17D+ASSRNzYMsN+XWTpu8ptS9/1xRWleMq+t9hbRzYdOR1sYj5kq2o8c8BBnctfVT1o12BVsnIW1mdTuHjotmJyTcTgHq9Sq/KwW/ujXnkVi90MwcVsaZibNzJXo8CVaqQSr3NGOdF965Q8YD+5Zz3joRFTMsP+E1NPq0f1aM3TNBx2U/+aI/QCJJ0KfOJAMVQWaMvjNvIY4gr3mQ6VwiYVL1K9nPCrFYjDmHcp+0Dz4KripHSfc63/GeBF1bfFmae07fn6YDdEO7Bmp1x7lzyAeGbXHv2TEy7SG7YHc7Pj6/7DmzBdnrQAOs+Tmcu410fC/HnxFnAUc1/8EvSj8P428CAHKuX6SCliskChM+5Mat1O3QPdyG3Lk5MCYAjt73f63A7UX9Gz+3A1kHICV+nMsaeNzH1AgEcefA1uNHHMT2OMdDnQtwltBe9TJnb1ewu3wzW3p4Y/pguaveQqepJ2XLtdJTv6u08xcYZMzLzgw8pPUPO5SCujZ/6Qu05JjKC7yAbPaPffHAC1NrMcgO4I22UVzd7sRSJqUnxJSpThv9ts2485CxKbZk9SteYtE95NM48BVVxQPdB6+j1ODxkfmJ4HP1zEZSHeqLcaeUa/m4ckB+owpIkNHlZGAdSEDf/TV3xQR87kYGuu2Bdt1xHXa90ucmxUM80q0tS9w6oqFWYlinGjzJRjFNAm2nvvNVKjpX67DRLMxdj1Ci9jJ4hm9d+U96wHpeIvkbZFPj7VxEB7nJ4TlZA43kn2cAgImVjRSfiMIdep0vneIJ6Kr6J836KP73o8imVHaAIeChUFLmPAdZY90qekPgxTw/wLyQ1ttpHsyl6xTsGT1MXmQksiR43PdEgLFIja5hpa4j/FheZCgRT242HoKpyrIvLw40eaoqnBZufeegcOeuz6RQbTv/h3qYR51OsJTUhUb2/LsA18E4ex7L9i2Vjr+2bRbxFX0vJqHX+eBVwMA4LUYO6yKSotoSMe77RMwIh6df+L8jfZh0PzCLjVR+dxFrv3CmeMYjX5r0uKDWkdwIOGqWFomzKIsRlxDf5ae+kSLHC4+w1SxS1vEjAOApMlGyo7gJIBDoxBdH0YuZFLKMV9qaI3qR0AP3Er1wezoiASpLDT749kWgjnw6UByPJtdR0czQMYC26jR2cP10PdQG7iv2ImYlKCN7Y7Tr1rZ21l0+sRdQNiHY86WST/EVGsQD1tOgzNQFXoNN2lb23YReFX5XsRMLLHonyk7jhx5Or0Vbp5QGHk8e7H8X/nIeAShkB2Yieh6xLS3aXUZX7oTW6XjFt9ko1zs78r3cZrf3/CsxHCSvcCZeEj85whx7PPbegea//w21QKxpL21uMN3sfVjuFw+S8IXXH6rB7mHZk1xExSKcqhhNwe9eHIhubp3DZg12BcOBpAJHS08SRGYBywUQCgYK4IKf3O1lqwt1r0L+m0iOHGqFNF7eRIcsTwcQyzOBm7pJhl//zZzE/7kdDUQu1NjEc/YvLJKT8yKZtLv1JajPcwjJLTOxMWfJ9v306TAuCA8mX5D4IVz4JHbQWVcwBTF8hBn5DlCiE34vdn3cTvmd/vG49Zm/7C4qx3W+qCsbGVbJmazpfvAxfheTDRCUjS9x5ooH6V9AOCMyH421S0aAsazEOpG4SQudsODzZMb7fMnZ5aA2tvBSb+g8FKeTA7QkhgPTqE3Qt9jhkRssSaiFvCbxIuO0ShDozuKjT7SZYpWJNKtZCEDUduNsaebSDIGu1sHzeX1yqBkGPhc/r0AybtXFk8wvFSTeqPN0MW5leMRviA1Su79xj9Un4CX/508ZZnnEt/3tc2Mv6aK0t1wEf50XKdPGwlpIsK3+o7uoJUM/OUrCUSttobWoEm7m5cury/Ev2YxdBOFVYBYMlMMq79Caq+f3ka17pNFaLE+c1AxgqfakY/x56ha8JHnSx5M3YZCgOv5zhavTSvtjROM4j1UJIHpVq85Bvpn8aRH4OPGUSs1Oquu4EjaBtcfsLlTJVDcYIXU4/hIiBirCd1jb+XBrceknCr0AACz/0z4HYIg9Ltf/1ZHEq/RfI6IS/w1dfSu9upDuicDk1zUBRxxsmieVoP5ACtk7v4duIbmQTSDqReDiU80FqOsdcUX8l2Vjra2pnHwHTOLMJZPFcrdZSlRy3hPmlhpu8PhhIQYTxcWvSh0vYmrXN5t9+w4IgG2QktVVtkcykwakka4DMW36cPNUofXsSyVjCb2US2I3mAIa046mENR/ALzjlXcWb7E6AobLUfLQz7krmt+n7xzRNSDJZw0iPINDXm+p/bxWjrbz32GZwv2ky7QaI9H7iEVK/+VhrVxnROKJzrKoqXwnUpVuITSSNHLxrde52PkQINyuvcyWqtn8R7kH89TtdiD18fV8QkRJv/gY2Wg0HGGHCsfoSS/GwnGVt6jq89V47ypwy+T45S/5mRq69pdCErQG2hBSCxHUYByZAMa1I1ipB+EaG1phE24n6HOfRyNU630RM/TWlXa+hcknDwkqC2OWuAJ0CJbMsY6XbpNEYa9Z07Tl1Qj641Y9+G4jyd2cl1oP2D8eFgYzI0ZOvDNeHVsZi0qP1ItNF2nuznpi2VWqI0xD8RzmqEeNZswgaSTj54XDVb5eB5DCic37ajUCpztLuWVHZgSvx4Cs3fNiH/eojDQIVlTl8chH9p229jU80PvIGT1JLyW+8sxx2yuh+1pFdY58V72ftHoyvmmai6bqMgZ0NWsWSd63RdZN/veSXto/Om+svdshBOkttux85p7yEF7RxyQZ1RQvpxxLwYW0CZ3rMedYmJVLVNHatug2THZ9yJ0mzxewmUePfSVHVILIH+b7bB29PiLkKei3lWGHJKVm7PSfVorCQsg2g7JVfRuqgOMJ3htEosKrozm+c3xGdCmxahR2V9sQnBmESvTZPKfYvFyNj+uQHyTYqJP+z6f/vk84Fey6PZfr+mfH7xo3wUm5zWq+At6K4F9T+lpylss1CbSM6r/2/jmv2t5qd/UvaTPJvpbapgPAt6ZA2mdOzdAeB4mFsU5KelT/Z939HaFGernyF6rv6lKJvWTV6kDp0BkTr6Nz7lJd02d4mqbraUrm7uZ+e+j0/Q3GnALjrfwmH8R+n37FD283SZ1vPTQHUk9chtRCaBZIo63q2T/DlHe6Rf65v1Nc4cbf19MNE2a3P7hd5sFMA1UI9cosvAa2GEJAov1Rfiln4nlS8pEUF6exYOklGiyQlglZNbewiuPPFMt1MuNNtnacxT+hB+fiESwPtScTROZLDp/BjFiEsAQlp4aaJBbctUgLUD0MjdJZFZf9sEKaCWb1lgnN4dwSAUdIiB6myrstMqHtNmqHqAl6D8bFOrtr69bFyTtkEQrES+JMS+aM5eZGhIzlRb/GRg74mNzzamSoegY0ibniwQH9qvJ+TO+xVxg6RAAtiMF8bLUWzWnNPNBKa6qVHqzpDiVv1K16DTRe2/EqI8bblg3CyTTc/zKP9lJhuBtRZBbbw5lnh1XMMGx7HddPSnBy9YatKksym8VeayyU2LSthn1ZxRxr5HyssbHf11KssY2GNzJgRae3I9YbrHDVLcxbSNjlJ2FrnRX672cNCMtJ3uziduuPXo3SPcNI5aX4v0miMQAP6d6rmgjyuoNYpHdpfLCnqstALkathIDTIPjqUqImCoBW/WmEbm3+xSN9yqIbyvpcqNCHVwpgZTJp6OroiutaFMbu56cMc3WRwpTsDbmBtvxnKSIy87UJ59KdUcbnNldTcX1tbvz4MN1lwgIV1CCi1V+jhaeZ9/DcJW4w0Zn9HKJveRrCTyq83CG++taBypVCRRKfhISHLElKIzVRT2WfPftMrfvJeeoT8tli2w6glGD1ebZuffqJcJ2odomKY9nNorONhf5i3d9S8w6ltPjuk60m8eYei11yrIrFUZrxI2TtSvN50RNxjWbSSAmunTzJy1auhs9BD5S/b9A39p3ROQ2FWxTzHt6VsAahV2HhdHhg/A5/uVB1k/N9ctz2j2K0gbkl+EucSkumgVNRTQMj8xF7sylBqKeH6gDUcGn0ioTzwv19QGWYueIlZ1iVNJI6HcaBtCtMSc2GZIbdNoGzObkpZ2LcOFxx50tDUVhXRNhkm8fuJcd4bBxP7evmcf7V3/XFo/tQK3dE8nuBDnOyvHI6Z6I5v+Qh6yENynWc7nwC8qMApXkVkX0jT3r+E+Y5
*/