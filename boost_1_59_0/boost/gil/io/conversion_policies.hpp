//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_CONVERSION_POLICIES_HPP
#define BOOST_GIL_IO_CONVERSION_POLICIES_HPP

#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/error.hpp>

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace boost{ namespace gil { namespace detail {

struct read_and_no_convert
{
public:
    using color_converter_type = void *;

    template <typename InIterator, typename OutIterator>
    void read(
        InIterator const& /*begin*/, InIterator const& /*end*/ , OutIterator /*out*/,
        typename std::enable_if
        <
            mp11::mp_not
            <
                pixels_are_compatible
                <
                    typename std::iterator_traits<InIterator>::value_type,
                    typename std::iterator_traits<OutIterator>::value_type
                >
            >::value
        >::type* /*dummy*/ = nullptr)
    {
        io_error("Data cannot be copied because the pixels are incompatible.");
    }

    template <typename InIterator, typename OutIterator>
    void read(InIterator const& begin, InIterator const& end, OutIterator out,
        typename std::enable_if
        <
            pixels_are_compatible
            <
                typename std::iterator_traits<InIterator>::value_type,
                typename std::iterator_traits<OutIterator>::value_type
            >::value
        >::type* /*dummy*/ = nullptr)
    {
        std::copy(begin, end, out);
    }
};

template<typename CC>
struct read_and_convert
{
public:
    using color_converter_type = default_color_converter;
    CC _cc;

    read_and_convert()
    {}

    read_and_convert( const color_converter_type& cc )
    : _cc( cc )
    {}

    template< typename InIterator
            , typename OutIterator
            >
    void read( const InIterator& begin
             , const InIterator& end
             , OutIterator       out
             )
    {
        using deref_t = color_convert_deref_fn<typename std::iterator_traits<InIterator>::reference
                                      , typename std::iterator_traits<OutIterator>::value_type //reference?
                                      , CC
                                      >;

        std::transform( begin
                      , end
                      , out
                      , deref_t( _cc )
                      );
    }
};

/// is_read_only metafunction
/// \brief Determines if reader type is read only ( no conversion ).
template< typename Conversion_Policy >
struct is_read_only : std::false_type {};

template<>
struct is_read_only<detail::read_and_no_convert> : std::true_type {};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* conversion_policies.hpp
JEW+g5HbHfv9pT29DWZhtvwl6D661qPNdXrnXWepEcbKu/i2VZzcVXPTCNF42638l5U/Qhrs6ECxawyjkW7t7jUnyXO7YnyGf4szg/lWI1v7N5q7BdQZZlJRTxj9VsqlERlaUcjcEDqbhFPHzD9SdRxmNGZ99lgjPEKNhaFnf+wt+jHQH4tZ8nx0LmhuUVJrZo0QzaqbyeFDld19860GkDUlB1PQ4SD/Lb2vpisMyqytBhOop25mNSffYe0NMQLTF0KnW4JZnm+nGWOuFgFJgvRNR4PHHrM7Sr0go76OwtS3F5UDoBJTRV5ri1fMa5dqqsg0rMpjz+nqAb5ceQEH4Sf26hXveH6YiiXnWt+QQGmbHyeOdH8hdZyEftPoz7WKo7zkn9AtG91WaQVnKPESNHSEZCW1wUcYqSMKOMrYN4zC6DcYYdQW/EwxpTnXjkWg+2Mmm3po1zX1L7gyqHVe7HOhwFxV079a8HOZ8z/371/EP/fvmRpbt8joYVkYIQ0YNT+BB+j3PxvTvPR+ZaLmrzVBKZA9eilMeS5eCoV6McgtNUfMzoM1/SYxZwvtzF1yLlMs3+yI1Knrrir2eElzN/2Ob7ShGaZHLKSDYmCljnNYDCnYX0o71GV4e3u5xeBPxgsxh9yyAkNQqpegXXOJcq2XoNEsLpNRqZkIow2djNm8pKwb1djt2BPR+3TQzqKMOtwkWFaHdutTOZxiG0ldQJtO0+6Rn5mF84gALru+YtkIEx/LO65ZQpls6AVNTPDCZ/Q+gz2cc/et/qIoRZEt78h5IKgSDOpFjJjuIThZoCPHZSp0x+Nd1Yxo6w2ZBNZDrtVBojnVfQjv9ENPm7lKrRMmYB2UnHr9O16i0kwaYzUwmk68GSPUArQC9yFSuhsnqUZyUtYnqVwVfJlptza+MFhOIzEn5QqsL9MzsfGDIX+9gIin7dYrN+8ZStJIdg7Ep3rS8duHOFxGh2H9/tKgv3Qb9HmXkAWfxWVtwSXA6HZcOV+BdorzbeigpMGf3yaFPvS790ptqpdeDw/ASuuGfgbNVH87naJyfOPaJCmSti53s8+Kfsa2bza62/x3cOlFe/kd1aOkkFVyt6kQIRXtVeX8NnTcGvoQSCLFb41DKe7DPhP6D8vfLZl2rhBPMO7drIptfvcn/qIWcmYtzIIaPkQjdTHDZ/At12+qPkrjYWbnbsO7uAxJ6EywUNplKPCQJg02ElrPOkZyf2KUiloMsohcyEWAWyKdME4I+fHu+baCJLxWsTBj150ev/g3svQt6Pnb5flWf9HOzVp2W83tsntnRoPX795J+LfoZSHA5FYHRk/QorNpdMWD9ATlXpoAmMxoQNhWgOkkzKWf+AwZ7pYy7wbl6/sNBp99QpOnkDyPmbZgJ3xgs9cc8s3O2HOnh9TosejpxRzyZuzxzYZYnxabQiMz9uCtYkV7QYyEh4i6Bv3iBD3k1Yc1BevOgHubhzTob/Nk9zaspoC7zQP1hDdykqStsbMo8vwsvml9SjXvEiPrbpDdwfNRD9TD9HmcF/+RbeMwpzZ6qyexP6KfC+CwLqB8U0sCYnv36wpHDm6H/mm7LnByQ5l2E9lSYnsh7mgXxh2Q31vP0cX4nTX9OavG1PRnrUpmX2/Y09EotzmDNUcm7jna6Aw6dw8egIZec/32uCSvH6cvZQxbro9OyuCGnjdl6HnT1iHnTfl+YbS8D9fQx9LzpmPL+V36eVN6xvWQw80sK9sVGbJGWi7NQiN4waET2YOHVsew9TPw3Orngk1qgMQjYudWEVs8OEgFVLwZ2PiTPtduVeyAJqp5DebdXHUGds+fq0U2s2j1iwz2R982uzt+4uvXCqkbbNDJdFBfv3Z6kpmOB4v/jFPbmAsdr+5D58QruGSEWk+3OJXMb42X2/yxibzoPEE3Aaz8DmEPHr7LgcYuzvtvO5jh95zvYMbhUwt8qrfCyOGFn+/QocUOtDnyt5a4gvMgjmjBAY0rzbi/7MI+cR6NJySPjvl/6hPnz3GfOIN3N1jorL/Iin6Z8zmUAnQNKYws500iAwRBFpRjEAkC4QjFr+hA6bWRUHOc85ANFeVWuhOFu0gsea15cPtIWU93ogqLfyLb9HB8u4/7yfbUgg1ncXhd7eC7V1+Bp048Pgv6yyqOYd6jHaRLA1XTJCaBQqyMJTOah+5EdTTpO1HLlg65HERa0WEo9qVo14N0v7kMlM8xpK8p/iV9GfrVIC63VTjW7D6+ANe36V0gGwZ+cvvGDXSiot8hghOSYfeF4El8KJC4x/GKs++kc6RSuzdk8A4VZrOzwdEQK9wLXDWwuCm21FSUMfSqgQkv/levGrgXrxr4NV410HHBqwZM9KqB6iXnXTWw71MsH3rVwM5P/zcAAAD//8S9DXxU1bUHeiYzk5wkE84EEggSIEJQa6BGBpQ4RIIwISqBCSETIiRgL07jSJXCOXxU8tWTwZxsRmmr98lVr1CwxWpbestHQIGZBPOhVANyMRHQYFPd41ANEpMBQs5ba5+ZfKDta997v/f4kTNnf6299tprr/Xf++yzj6oSzv8HjuMycvn18RavU4mkB99RVdckf7Gqqtb3yue5Oiynl/VeloMR6+71zI/mMzkDx20cRW+FbOSEtUFMbuJOnuS4QLyddj6nqkUQFd3EXbjAcbKXJ7lB0uY+J8XRlZC/iTNBXYGtxGYiXF6+S3UUqmsTaHsh5D2R5PaK8fmqxDvop9tVVT5hIl0BE70d2bmzSOHJ5Xz69dFutYg0eh67tLJkOcnts/yFLvulqrY0ELWAXJIvmVXJ7MntouQVYC6X99i67Kpkok/2q2plWR9XVCRGAUfyo2tvhIq4OEiHOulbKquyOEwpCTgxeXIpzUJSxXzVdU7HceuXklwqH34TWqErT/DYqN0VAVwB/xh/whSII1XNkCgcMiyTOyKgRQKpasWIg4Yk/2/hprKsmwMmbF3yqrU3SIN/J8QRG5XrNJp3K8W8r4znkTSx8VNUiLXTxcdArkVAbWStjXdF1Nj6aopvNNr6uaJAIo08gYK9EzJaWmqK+xptN7i5QNGlU9caPAVBl35Jnie3L6+Ui+A4kDZSpicPosRT3V6h+glseFAnHLQFxWjhYO5VXwcf6wuxmduFsloelm/m23KSmZPMwJkn51X56tiN8bK3o7gBpcjT+n7kMiTBvDyHxxa0q4n21FFm7ClvmjHpZ0nmcXHJcLX06G1BR6n5do4b9X6enVYfV9WSln9Qssfihdyj3t+N5RWtvDecu04FEcmXEpwZNl6ofgakkO9gPXeJbn0Jek66RBYlWM5Z35MSGdfHnci2wSl7U4RD3sDDdditLh0WXz8BW/G+yHEgauGQjS8Sp5JnT2q9pwukeAr6lrh0ngJ+iT2PTikI6SxmFA1w7ZtVHESRdaPISpYPUTCe5qlDRDOcZc9Qlj/8L43lbGS5IcTyq2GWKWM57zCy7MQRm+KKQOrjhrI8nTzbGmb5NmAXuh6vvKYAdrpm6b/D+MNDGYfxlR8aYHcCo5ZzGcW8NJm6faiAo6FS6h7BcbOK+1DBg6jg0FS1IuDIKDaJbaDzJMsMrRJCQ+7gp0g7MNWlQgRe+FLOjCymvspYhKxx9I4B4oHfyN5+jbg2hMOcWrwZRlRM6XYQqDSGfusd4OfbOI5jPBQ3ZNhMYmexfy5Uag8xcHt4zJ8M/5MzU18EDReqf85hF/HCH1akGsj8VMOUygqOy6ycyHGS0D471UkMqU65o8IpBys8q1N5qcDf/meO2x4qL07/d8oa/e4/Y22mCwmp9Nebge04rP2EqcGzNNVAcyFmyUtQULQ7q2anVkSIke3Tlp1MNLf3v/Rpx3//bLyc2bwZmXZvgZxHJkBZT1z6iCSzfzOEz017BLO2tH/LMgcvtLf3B/5CP90EAh33uqoKnPSNvCWV56TAhbZz01Igc50Oqw8TvX04UZryM457JKwPS3dtM8FofEex9eU7Cl2GZfTjbaqqPNbtSvbYWkHO3WqiadIoMxoazdKdUWxdHtubMLx5iCdl+0r5ylFgD9TEqTDcrY3ibaWd/5NohvR0LTzakxvMU6Sg2ooGkM+Qghv0RAp6FqieFferva2T28QI/acewxxr2/oI0ubZqOrLunrPTpa6065Ye9dNcxmYVsEQSzQwTsRbPLZL9lKDTosUtUijxZsViLB4PY/tHHAtNwi6lpND/pW2fmA2r1ZnctiW+almZU2q2QN/aR3QfCaLu219KI5Ou/IYVaUgsfU12frAMKqKLQjuaPVuLNpAcjuB/itA3/9+vap+V/+iDv5b+ie4zx6ADuWuCOWQ2SnckWj+c6IZfpvhL+gU1rfOcArlXqew1JjOEq61OoUP332d4zlOXJipxnLcljKncOXdzOngoStincLZhamGC0CrwSn8UH069cglPTJkVpammsgZuT4Bbnj4Myigs8/+D6qrmWUPc3DlXai5zSnU+yIzVSi7ZUrmdAAOFfuQBw54+EZY1jykmgvGLIiE2urHp8BNJGQbzzFWz64IZRkqn+MH/k35PHuTfFb9I/lsv1k+0kKtASH5GL5fPn//J/J58k//TD46Tfy3aqJn8rEz+awYKp/2r5hsKiFF5xQc7AZltHa4jIjqoD9KAuXscveIo0m2QQ6qYhSMpvOTR5kdNPoW8BRg2RPpraPMJ12mUvuGMWYaCQaTvgal5Mf6ACIsU+1Li+j/gM4S2yXCk2gltxM83oPFULaogaBed1IneOyTzArQfWBq6Wuj0XK74er2ShPRuv6KxTRpMXeoibNhPNu1mgGakbylin0pyVum2JeRPEOeYjfQ2cAC/bEaJpxfSMp4yzm3KkGhtwZs+q3QJ3KzGih30HsgojQhAh04NY3HVgNK6hEfom1jEOuscdBfj0ajYy4qcrgMjtI5o+MBIZqU8qUuTslepiZeQmaCSrnBrYqmQrBBICWQGDSAsUvaHHSPG7yU+5wYlU/rj8AtVh1BmkpWLge/Ebb3T/479n6u/8ZQXzH73ykr+F+HskeuvZdo9j9eF777FViL/6f+6/W6//v+q6BuwH99tu5m/+VZ9wAHLPjTj/yXepP/ehtyHhnJXE0W+q/D677Xf6ngvyau+1f914+HE6Wr1qP/Cttbjelp32G67achpkEAJjEvxLiRbof41xHGSxPbrw3Uocc6jKwOOzLOrWO5uiqkqRqLUzQWJwRO0seAQmDScM6nIEVx3/c34Dc/HUacvrpusAFHVnVC95/aDznY3UK4g1G9Fkd1+tswcRpBL26AYYsDm0g8WWRwt4h37UoFCH0kBdG0rRNnXRm8NJXkGJSHDHa6/+eg5OoGA30Db2SngQs5MBqDo28iUG0grYF3gPTvJSA9zD8SkB1ZmMr31oM55KTZJOI+nfTDGK94232P6qQpMZ3ieB813zc3QhoLkfH3PaqXzLLPINcbYjql00S1eBu2j/Oe6pC9uobeehSDmFQbIdfrgMwXsk8Hhc731kdg/B4ngQSk/z7ENiL9d4D+UdkXEagJ4UKwM1bTO0lvJ5rFmCw5OHrdVxYvYFnDO8kQFQK1VZf6oJ6hOAYEVeigh9H+BS3nipSjBmi+9bpQvQanCnr6Uj1KFKZM1VFaRG09w99SnJx5HvoMEr4CDqv6+xCHV98DmUoXHk00lyaAUI7fAWIvpDeqGPQEXOSGscMxNHLsEUhy5Dt3/2hLkllNTAUD9Nb1CM2gliYDgXwHfSdcTjRZvHb8R49DFgcdC7YpC7iaveFOBzVBwGOwdQIzpDntfZf+1NXSmqujzGnt+Xb6N0YiAageLU0AqseQLUch/a+fh0hLr6kHsMkQt3Ug7hel5hQdV9oMgiuk07xsqARK8vGffzOIygVIz4yIrst6RcyW+1VxrsVba1pQs83IAy1nRvICkc/K7IZ2rqP5HjdWYPe4Mc1eU3yd/ug0aFs4AmDZpUls8reyxPKX5VT8OQIxkHSKTxO9mAiBUT5N7BNDYpdGl6LE6RQgUYoTZzqOzUhhesogIPq9BCBraQGxv+Dbba8E8fga1Jl4oyYmQZI8Be85TTNg8rV7KQRDiqLOXMryrUhlgBFmMbyGSRE6FjcwzQoXWzFYrOrSHfph+kWK+UL5uooOZbsXm/NaRx/MCF0LPe5OuHGB00zcCv3nxmjF3daH9+k3WEco7vMssgOCiuc8Xl9ow+srZ/B6oBWvR0/C1bnthSD78VxiP680sx/3Cfbzmpf9/P5t+Hn5OXfXDfT1Bk+uQfF0w30Tq08H80zFTTHtwT7F04k3uSbFg3yRXDPEMF4uwRW0FaTn4khQTUyBOw9jG7x9MkPXkhmcuCnU6JeOQ6Oxa7Fn/6tSW71xuHTHxhg4r8MVQd/pZ20FJTg5iUGGO+CnJNwJK4Z2gr5Y7VClJFVKgHlpaFb3RwQQ4cHRxKZ4CUO7YndpFS4jrMZr4iq8jl+B15nL8Jq5FK7ObYmV7CdOZD/j7ezHuJD9TMlhP9Pmw8/Lzxk3wQ+xcbvXsF/D7rXw6wEd2IJh1olNxjpgGsW5CxN3r4FQk3EVXKOhyU3G1Sw1pCRaj+/azm7PD8h29z7IBDCn+FgIwaGYSyth/GpCljMxAyfxkCcD85Qi7WEibGlo0m2HAv7+30EHokAc5HJTJEbRAET12HidGOWgf3i4CxfZSorrDZyWDYEYWWAAgS/w2PnK+zhxDpFM4E2sPjFB9vF5S2jEtdASlcHiDaT2RIKz7InixW8AfBFurw5DOrFzL4uOEM/BkFlZMjhgCEe4zCXz5nWIEzNzF8NPUuZ/rP9Jh3QnHTECTM3O7Thr8s+IhzF9A/y0XMciymPp1xBSazCE489lLt2Orm/mAWhgmRmX7SoMlZBYESkcW88H9GQ9rwB4PYylKrEUOkarlCD+CCxWudG60bDFSMdCNaSRLObJDJ8idYD7Y/54i8/AiYnKer5Uj1NHSFdFn4FmxGtUAreo0iWahusliJGZx2UsEKkD6gzsCLvRsUAMqzTSfWCUgB59bz/6VMzZSScMa555oHkNhKuaxWQyS95k1kvTSU5C1dUU46/Giuaqq7fiL191dRL8SmPkTcmcFE8/NOGS4FylxgQeAgwdOFcXX1qHAkrYz9ZHAQzcWZXBqE4ic5Oh98aRLOzmBGTfrv40if64DPQ3xPlk5NPinWUzCS94sZH01wIAT60Tc01Eh65T3yhvNnBbzADqyYMgwunENEL/rt4X7m2LF0CXNSjF0D9BYboKLjU2mB13Z0SVL86HWbID9SErmWSZSJJnrSGQAoyqP00mkXZQQb0taKc/vhH2SjEPy40G97mK8wFDo03VqbZuYuuWbUGzNWpLXcnyWhu6DUPdvqsjzfQRMAz0eCyK93kUL3TAXYLWd3QU3uT2qfQUqBv9r1hcz+Vd4DGUGsxLJ+8Fm+KaWpq+EYT3EUyNSDspM0FrleJO+bGTHFnQp9jOqxuSPLYTdtpRjmNBsbVRO1KqrAESiu0MfYCFtrFQK50BIWUfptEfsArNSs22kErC8FBsgM76VCkZ7Fs+GLhC+sMKZssAszF9ewpmZ/TzG6g60BOfx+A4wZ4GoJcAzFWVD2j+YtR8UOcSs/xYB0yHOqzZpvVJT3gTyNIkg/Xd
*/