//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_STRING_HPP
#define BOOST_BEAST_DETAIL_STATIC_STRING_HPP

#include <boost/beast/core/string.hpp>
#include <boost/assert.hpp>
#include <iterator>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

// Because k-ballo said so
template<class T>
using is_input_iterator =
    std::integral_constant<bool,
        ! std::is_integral<T>::value>;

template<class CharT, class Traits>
int
lexicographical_compare(
    CharT const* s1, std::size_t n1,
    CharT const* s2, std::size_t n2)
{
    if(n1 < n2)
        return Traits::compare(
            s1, s2, n1) <= 0 ? -1 : 1;
    if(n1 > n2)
        return Traits::compare(
            s1, s2, n2) >= 0 ? 1 : -1;
    return Traits::compare(s1, s2, n1);
}

template<class CharT, class Traits>
int
lexicographical_compare(
    basic_string_view<CharT, Traits> s1,
    CharT const* s2, std::size_t n2)
{
    return detail::lexicographical_compare<
        CharT, Traits>(s1.data(), s1.size(), s2, n2);
}

template<class CharT, class Traits>
int
lexicographical_compare(
    basic_string_view<CharT, Traits> s1,
    basic_string_view<CharT, Traits> s2)
{
    return detail::lexicographical_compare<CharT, Traits>(
        s1.data(), s1.size(), s2.data(), s2.size());
}

// Maximum number of characters in the decimal
// representation of a binary number. This includes
// the potential minus sign.
//
inline
std::size_t constexpr
max_digits(std::size_t bytes)
{
    return static_cast<std::size_t>(
        bytes * 2.41) + 1 + 1;
}

template<class CharT, class Integer, class Traits>
CharT*
raw_to_string(
    CharT* buf, Integer x, std::true_type)
{
    if(x == 0)
    {
        Traits::assign(*--buf, '0');
        return buf;
    }
    if(x < 0)
    {
        x = -x;
        for(;x > 0; x /= 10)
            Traits::assign(*--buf ,
                "0123456789"[x % 10]);
        Traits::assign(*--buf, '-');
        return buf;
    }
    for(;x > 0; x /= 10)
        Traits::assign(*--buf ,
            "0123456789"[x % 10]);
    return buf;
}

template<class CharT, class Integer, class Traits>
CharT*
raw_to_string(
    CharT* buf, Integer x, std::false_type)
{
    if(x == 0)
    {
        *--buf = '0';
        return buf;
    }
    for(;x > 0; x /= 10)
        Traits::assign(*--buf ,
            "0123456789"[x % 10]);
    return buf;
}

template<
    class CharT,
    class Integer,
    class Traits = std::char_traits<CharT>>
CharT*
raw_to_string(CharT* last, std::size_t size, Integer i)
{
    boost::ignore_unused(size);
    BOOST_ASSERT(size >= max_digits(sizeof(Integer)));
    return raw_to_string<CharT, Integer, Traits>(
        last, i, std::is_signed<Integer>{});
}

} // detail
} // beast
} // boost

#endif

/* static_string.hpp
psCopi87mHRZM8d9JUgeAGSxneaU6umYRxoVFO4ySpUalAuzHNtTRlU61OH+EOJZ14wg1pqtxW57zc66/9nsILWGl8kQTS4PYrc27CYYWkxKDIJCaShH47iDGP0Dx0NRD8I7uGWiiLOMxRo1k++9Zu+fwGAcsypZzWZDdzwqRlyDBncrYQQ3Unl9bGGfOpbk6DXbOCOyh7IEmVubdjYKfAdTT+q69thN+NxKpjLDBQpjJwUO6eq2TXe9etNjYKnexQROtGXjFlQUW7TkhEbdhFt7melzqF4QXV3QQqPA8AHSC3OwUp/AtHi8DsKJoYmo4DUqOpd8Z5QnG/MjTfvRxDYcAdT6p9qOyY99kGkXbOlCNMqDMFSECRr0YbEKtlHQOnz+9nVhU9cJ8JIvB7ZP6uAuPache1DGvzX78vX7bcw0H71e/fD9WJeLVdJbrp3ogireCJJrBh7YdOVN/RmqwA6xurJw0XH52RHTTJDFLzJpdJUTfPIyL77lEYPbs+vVpQMVzQmjXqdztLJA+6xkq1NfCQiv3paBAAos9dMUmiEhhVEB1/A6zvRmiQGPeyW3S69n6xNk5Pyx0FqafGq7Nc2wugOhUqYhUQctvvJymE3UdJqAqrG+9QmN4j0XrwJTqvWsL+20UYbDNnJOTsqqj1B+ae+3ce2zaRHbMLItIhzUt6t/ZyqX8pn2NTV2vTLUvNkZzcxCM03HAkEAqKb74sDww6fiXq+OHUNCuqKhX7dMZMY6eig94zdSLrLrQmyZpEPHi+PZfkr0ul9MH/Mi6mdhkNXDPCzNsnRi3/Jfjje31dOdQR8MpWfxwyGNxJVFhkgcK8IbI94YM7BBDCar1YJn+CCaayY8WkGUCZzhAhpR+nS60+nZnleVdF3l2qtCx+ZfrApWPKUs0rUCtSvjgsNTynI7ccAb26eNx+skTt9mktmVyXLdMea0eboceH1ptD6lGJ0PcyLr2zuoiHX49JDz2yJlYg7vc4rGTEkVJ/QN9R/dJnSXFuFQbg2bk0GKZeDBzbNbHlkalOkjaiWfpe1Ro+dBUOnZuxAOZcg9R6mCr1U1jMhgK6cLu+PQNU2G0rZa+KzAIoZB09/c+vhcxKdrSsTQZiN7Qx4bHs3gcYo7Hl2w1jT1EpKOMriy3PEsKpEg05ozVO5VCnD+WJPeI+uX4Fv0vUFDilkpOFFDzJFo1uZqQl1B1uGzcx7miZ2cdPHd5Mu6tRKfyntMIMc4G1iwmmPjGOyRFMd8ZHpvzrt/TPTeQc7keKO8HTtzTSS/Yc0bDBGcp7qa4xKRboABe15u/OU1HnTBQjxnxvDjxUjZuCDYpYGrTryak0aip3b5aYZVlUxl5ptIoDRKZXq66bRGtErHbo71tgB7ooep/AyfgUSLaOZyA76jY/7qQxuYg0WvgX4Ew4Y7xjtIH1z43qzQd/LPZUmbLOGcNQuggOfD+JYq9xDN8yvXpTqyvwsBT2NQsZrg2Gu70fI7ZVlv8ad6jsMhBPooa/0ZsUiYyJKFZtz//DHIztf9r3vDkzZMqllMl7NKkU9PAQdsePpLM+DCZrTMaNSpd9MiA0AIc2SKmtLy8CRc6j6wg79tEhErMLQVF3qAA0dHMU6i+wE9miys25etwuabWgcAApTg4mhhG8GBYKEdzPtC2N6QVZod391/DhcNGQASbLlau5ScuQvEeE5xapFTV2wh3+ogdzyEDI7pP3uRCcFdvwLe6tSklu6VNuxkOl/sO52j6rTPBlto0DzTTFgkJOnRk1srT9ek3sPvfDR7pJfb1+rf45ydTxkIoDiVY1nscBiZg+8ObV46axeuBYs3W77pLH66u/RQM4Eta7ws+0ThQvDwham7+f6JIXhKe/PtzbTa+GZDz7p36xa1+znZDA0DYz+NkLEjfmxR2UB/Rgyw1es70dRRlQ18fyA1HCZ4/wktXFToEmRlsDRYrFj+JPPb07XQS85+CkNRm750FGJC4uRcVG6EOT9ciQQ1BtH+1GN2aEVSgIJzgSyu9B7So1/9HFhGQrF7jg8WnunB04ZjMh3Y5KHDM0IZxZd+nNnv1gP5grzxRGkPcjDJ3yhJqd0lJvlRi7kbB8Z2a0rXAO3cVh24TIp87SoEH8cWdetEEvO52eW4ku3jPuGpUEvfJ4T/DJXpLVYPmpLwL9AZ1u5ju9sSExYE2XG9xxMMjHZuXva8wbYCGS7EWNSE+C1W9H0hopFVgQAmZdfyiXyFG/lb5MMSVnOzDxudCk91a4zm8HEuXLiUW4XMunXNoPvfW+dfi0XyWw/Zx1pSK0Vm91nk8ayA287mGjq1ewOeS4UQy79io2I1jWIf9f/Z1ZFpKTiu948bzTpgxwGzv8m0TYtflbXzkkYeldGqhqauAULpHr6CyX0YM+XoDCCI37hVGT1xONefKbd19DtjTuGDjejBQ+jKBQOYZUN1OvlyI60/Tg1vg8Y4HWKnXN/XJYAza4y1F3ZY8ycIicpklMmReFZ74dHqK4DMAxCeKU4quL21cZOjFy4mVP+rhX2s2fylPl44tyt+4Jn7emyR3HC8lChXRYAYFogqqISf/knZ67Tvu2/i6vWvJnsv/z3UNDvJezs7W0MTE+oEdA2PQKPNjTWbs3PqQsOTd072xB9o8/9k2vpFKQ/fjD1sQ1Y/ImkDLyBAnx6hxLbYCEBU8V98n30aJxz2nEfF4CTBR4DgJp7dQ+gVBEfHFnTxSCUVlhmrRAZwDDuuw8/zF4+C8nKFQ50PsTF9RYC7MS9YFl+IaJn+4MgGJJzBwLH9PfaEodzutr/J5MKfs4GSpOsD3PPDtgeAW6k23r+FnnFQf3fS4QSNkoC+N/CPeQ1PHpEaMe837vL47aLulSXeK7srdud5frTkolNi236g+X3cxBcCYGnwgx66wtSDRFGWpmu186OYBXmVAf3GChomBJ399dU33xPFUxc2Z5ekCZB8U6tCgfbtLFN5bpnsTXp9x+k03RgGwI7250XJPvdn+K+Hn5yPaS/A85RP88m+eD4/wZ/DH8JflCWBktoaW3sz7uiV6Fxx0zhVAPo2ORR8F1AMFBwUFgLqisPwUnY3S4DL8hF77e2tdbqxV0FpFKes9nld70NOyAfakpkcHamWtjjGqRwRuDMndavT/R4p4zh9pC0iaGuzzjwh2tmaeDDUIEBxfvHBGCU1mWtDXUB61JK5OVnUmUi/vIXGuRxPRf/XQmx3c/LxcX1RyMrq3Hsv8ZJm9D320sbs94to9ZfmdsTZvltPKrsP/Rg2aiR9nbmz1eexcjsqY1HIbn30XqwdxoVaRE6Tm/bWbLTV74fAN49Pw/ReuuUdcaxxzNbuDDpi/2UGWVywlvk/z+Oh8Iai/yoiNfMlV8SAlAM5AxQBZFtpWuHPPw95nvl/4QARMEKLKCSLAKGC6zaQWqQxBJuZKDm29wUguqW3J4XqBaW4sTOSTJTXxtWk0gxzt0Ny/yXpdGzdUaQJxHZY5UJAcxQfTkZAQMMOBQ/iqaXSt/i7F8H1jqTf+48z3f8LrUCq1NppX+Mf6AA09Xd8wflvNgg01mHyIYVGalgvsaarUbEHBopx8gMtWtjb065YEhOD4bmyaSsKgJoCz5w552n78zrVtnFdOxeqn/kfwcXkUwaLpSwaLMvq+yH7/d6s66VAdzcvkN+/zrqe/1T/895WWLWlOHeKD6cHDsWnIHBHkmby+Oj4May0Flzfx2P7OaS+r2cfAPWDQFiJHfcIgW1xSFQnwMGKr4r28TcUYxkhE3ho7JMcQ4Lftr5i+ZX9h3o6wHR09STesD6oPKwmeKiGBTjFSGpvL+dBJUnaZhuZTe2SXvQze9NymUoBquOI02YGms9wuTn1DgtoHxz6u7O8tPSkqKXlVaHiTKyo3GKLon40mB91rB5/uEx759tLHDWbjYo5xrqWLJbbAyMlPG6MbgF522ESffojoUXawU+8Gs/vdnNE9WWtezqGVdiML3wFj0GQXkcPS9Z0lm9SRCFFpcaP8RkZGvAfdzx5YkSQEA7KlwhAGji2C7PzQ8iNmzlryKvUm61/hBUiYp16+VvE92y6QWYZcdLbx1Ze4/vIc97Kcaf3OmmwQdnDXLMn5dvg9niL7yzX2QpkJj4ZybxoWWN7QVMT87+BvShq6g6EelE4I3L7++Xhzt2rvn68ME4jQdlVzgBoPD9R6S3uMIvM1ASCfH1h25Fs0PODjF2KowG/dOEgoGPvJl8bvy9cS8tsR1DD3MP+fGQ3cxBoYjvAomJf95dlZnkNHyj1riyot6rWp3flR1bXJD0RsH+YgRjlRpAlvW5oYvfN553zsUS/e5Z4LUgpzZ1JpzbwSnUg81TimqS73AyvAoJ7+gpTa+zsV9DiTwYKOY3OkygSKoEj+XWr69vANvHDT7X2e20Y+v0/24aDD3rOhu1dMeckkes6T9HASItIGCR5jEiCUpxVp0K8bSirdYZ9AIY/JdImVPcA8h0qxHPtRT4xXQ7o5fP97VjY8AWSK6+3hwsY34k8/8qk5fxQfTMPUudu8Q348Al/o7pVxJs61UHQMj4+7H7zWeDjNUdjbnII5VIBFIeXzDQqQR0B8ZdcYicyMzGE7ngztOMKtnPF+Qs1ib1aM/TOijmSBA4TdMv+yY1++h4E3F+qtGY5TN1OxQSEgDuNPhoGMzc0b/+X+KQvqnm4WGX5KBwNSAj68PkFReneRcNSjDIKaf5TMwMRbXyWnxlrDeKDiUxA7U1Wd4dplQ6nRXH2Ztnc4V5JhD2YT42aU8DzgCURlY4y65yxYLfJa1ezVPSKxIm5Xjt0CZ+1t12cQRYOrg/9+Lr0c3ITpDE3utWXv+dcNP9GljXoO7MzEenZBCwZLXfSWxNPETo0ROi/20vUwxULr+B2SAbp3gOb0V5bzb0nihJDs6Z8+AZk/19hQGKMKJI1ZskVHLn7gKCbKiRIFISpvwh7QwqwdLjJzh6svZ8fLd9m1I5my4H8il55p8MdWX6hd7jNlid4l5kua/oawxm1tbUrEOk6sb5CQDQm7ZYxeKRtzJKIjY5OH8cG3BW0jz6dYJpk/TXqziUMMf8oGhqaoG4c6p05SOqPgPoXb1zvjjjdsXD7ZO8JdsxChIX1cYd9nEYpLp60ErXT5yuJVkcO2tiHyBZ0MFWV4iHLbpBL5+48lqzkMWA6sWwdRSU2ryzf8gyGbijqHWLqDgbZ1TIMoypiIXMaQ3N4Gtq/DNMFGgOjuzT76bAbtECLTzy+3ovmtLJMTlZPlYybtbvy/diXcdNL4sOvAopPAQWj7bcXNzcXoXvpmEe3gYGB+HW+/5QhhAMgz6PXCoouq3AYawbIPuuN/KGyGl4GQ75VheAJg6FjNMQIcurZueeXtCt1FgpAjrJ/Kc2vhD5VxqxBu4DZiLTCBJJncT8HFV+Aw7YB4YHunapAvorja/GWzl3FdHR0RIzAprtaRDHwFV6qX3wrunWuX3fPhdoxCVXnAqFr68YxVyBJkxkq1DZd3VzWj6HeTutDEpdoftcfxGpesQY16ls1GKaaHv/rOmhGla5cUsqUCtrDjG8CGmFp0EkL/fJ5SGAhIS/952AAo5fAVkwX448J3vIygRKFTQlF5sr+rh3Ei6q/3eoXz4vCpNynNuRcIJLtQSEsfKVlI4jd19XV3m/VLPoA/hq7j6dFfQ0h95xuAhwx92suEeN2x4EhIzQGDl9J1pHrp36ttCQ9yGYQqXZBnyMLHTm8zx4UAI6ohB8SAUfMEI0oeuKVIxs1r+cXO5wVyyIHB0upNXP2mH7EQf0jHenOffeA6iz8KnserfFy2Yg7ZUbWddTLW83Q/9r3bm52sAzJdQf+Hlj926UzQ7iAnWXe8iSkpaHFBZww8k+WEDlYxBUsahEEsRyLsTyCqoKIXSzXCxOcWf2u68IXpbY+1Ln0bfIbuIfud01jQp9OOxqcQI1Jn7SnP/MxlVX/qIb+E2u4QpW2emMeqFgDdYjNQQQGgpfCD7ECPCMU/LvM47q1+XF4etCIT2OYKh3FmlUjNkXUAZlY/XUJE7Vv6Kzo5jRnrqx35+DOwLOawTnqUW4wLqzbb5RIag1Bnbha4ub6mubn+pikJV2SOongchx22zHPWu2B08tEUXlP73LXA6DhlOgIXT0+gm8hHjl/kfLcuRu2GRPylUZTSoMj40RUQo3Nrctc0SzONtD932rLGLv7GE+z61y+7RlEFID3kxSBEACeG2R9WYTa2C75qSwpmjn10K4bHDyiy2B1n6Hmnb2OLSnemXEcF/JFv3+laHw2/a+c6AshZR0G4GRbKi5yhJR0SftTkwgJTMQ4KiwLC+nNE7V7LCzg16IKmrs72VMSdeMgkNVKYrvsiWFuf5FOslmycb5M/daO1KTMGNlEzAyWzQ0sN/C3QxUjROpewkRyHMJR5OuY8eo5mn6Ga6o68D1ul504RcUq+vDBKioK739MN84uj7ctonDs6Oaa2OnERw03Lw0HBWjNOjUYug/uE2TRIsJu8fH7QjBU5loNs18GWQ9067w8BbhpmY1g7kBWuLx3H1smi9hEzZjYNPBl4DVcsPZ80l4L96pBJB3Oo8F8C3TTod5BNSIgvN18c1gQ7Ak41UmZz9VJJGPyixhZHceLtER1ZrSnplmgL/2kCESroe7CLlli2Ln64B2S+e71xKxmg1udFmO8um0FqrIlVQdvwo0tBc+WkDG9cUjN+xdVps6URRQcjYzhLsDsjvDadG0sEY/OpK5DE318+ILPZeO84/ELv3ox5j4EMNIqWnqdtD7dN4Y0ZkDE9AP+P+SBAygYKaoPD/mVxtvyFnt+vt8K+Tm1UfF9CN1PsERu0wCp5XnJEolXyV3f562z1ylex4cHZ0dn2cHHR+vOvfNai5u9PLPvgzlZJ1YiAPcX4unghB/0ryWPJ+b8AAyI4dnwqz23qzZ8XOeNheS+kZ5UfU1zxpw6qm1iiu6ysdgYGvLU7LgI/7RTQ/xXwZ66G87EtK9iGotmtum8emGfhnrotejpnEc9EvEbRh5n05SxdUVkrlGz1knF5I5OzjlRiXNfHQKRH2DfCpETkftF9M/PzsIV5BQUEh7EEuiJ56KKAmCCQBXnEFyuUi/q2XP1Lma+9lDfDsr9S/H19jwEin3G2f0o8Y6g44np4SUZr4DfBVD2h90NaEhIRGaCQadnMzVLS8rKwKsrHvSk7+SBGRX8qZGxK6bJpNDerv8N3+zs7OhDyxmoAbKxtUp6aWG9k5zxcSyYBpQ0NJCg5merigLm66q7gxwiTau4tdLtB/92U6C3Ap+ToznEFgMQ0I94RKH8i2kAvF+FcF12Bp2/rEVyQKB35dhugnQqUV8roUYGOs64WCeSqQ+vsLTEd4IEoJRI9fayiurEz4iNlUXSj/hOTyBVoTQbg4ZQsmXVcUf+ABdiHNxxKZsaXfbnHzvVEI6TKAU3FJeEhJeF0DP2l4HASExJQX1+vdUrQ39T0lYWxKMO8gdqhC0Mp+5EaZT4sUy1KFA6pubdZig2N7tEedYphf2nv5G1vq6x+esqw4UQxXAwZhzCFGuqC3C1R3TYCGD0z45m5TmNkNtiOn94mft+VsSha9dy8NCAvR834A6a44h1Hki4EZE83X1oZUVVWe1f62Qq5QYPLEdB
*/