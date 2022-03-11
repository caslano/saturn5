#ifndef BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP
#define BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_streambuf_locale_saver.hpp

// (C) Copyright 2005 Robert Ramey - http://www.rrsd.com

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note derived from boost/io/ios_state.hpp
// Copyright 2002, 2005 Daryle Walker.  Use, modification, and distribution
// are subject to the Boost Software License, Version 1.0.  (See accompanying
// file LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/io/> for the library's home page.

#ifndef BOOST_NO_STD_LOCALE

#include <locale>     // for std::locale
#include <ios>
#include <streambuf>  // for std::basic_streambuf

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost{
namespace archive{

template < typename Ch, class Tr >
class basic_streambuf_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_streambuf_locale_saver(std::basic_streambuf<Ch, Tr> &s) :
        m_streambuf(s),
        m_locale(s.getloc())
    {}
    ~basic_streambuf_locale_saver(){
        m_streambuf.pubsync();
        m_streambuf.pubimbue(m_locale);
    }
private:
    std::basic_streambuf<Ch, Tr> &       m_streambuf;
    std::locale const  m_locale;
};

template < typename Ch, class Tr >
class basic_istream_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_istream_locale_saver(std::basic_istream<Ch, Tr> &s) :
        m_istream(s),
        m_locale(s.getloc())
    {}
    ~basic_istream_locale_saver(){
        // libstdc++ crashes without this
        m_istream.sync();
        m_istream.imbue(m_locale);
    }
private:
    std::basic_istream<Ch, Tr> & m_istream;
    std::locale const  m_locale;
};

template < typename Ch, class Tr >
class basic_ostream_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_ostream_locale_saver(std::basic_ostream<Ch, Tr> &s) :
        m_ostream(s),
        m_locale(s.getloc())
    {}
    ~basic_ostream_locale_saver(){
        m_ostream.flush();
        m_ostream.imbue(m_locale);
    }
private:
    std::basic_ostream<Ch, Tr> & m_ostream;
    std::locale const  m_locale;
};


} // archive
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_LOCALE
#endif // BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP

/* basic_streambuf_locale_saver.hpp
bT5Iq2X1mRQqMWqSfYLNT1GC5DPoK0X3QRxNNMYYm6EZqvnn4GOrziSgCDgU9j2MD+0DxmXR0UxxELvsE825tVXfIH4p7WUO0SsFZN/0wwwR6M+I69m0eB14/RDuVDgc5dFL+BRbHw/tTw82VdPantGIf+zMLS4uWltM4tFUv5OLh4UBagGAn9zjDSwG+qy0w/vJiCcQKPc+GK/JhLn+1OtACf84XkxowMDPl0CCCQ3nEj51HgyMgtY90DI4y3lWHEP6aqhoMOW75EXB4a3GalyLRIl7rbra9oWXJO96xlymz2Vm1C8xX46//IEdwy1EBylOeJdvMM7fWeBasftMx9GVqES/by6+3wxrIJFZUVQE0L7S6x5rW+UzpEM8bYZHRlFN9WtPubFLf4D+FlkUQaTyjnMtWtiDKCojn0jiz7yHRMAgCEQcwlJKDGsjHsot+KC8i0h/h+91aT689/sRfOgZ0MEJPg/+nDm38TReSl0SV4hI5GDVNTyfSKiU+IY0xkVIBkaGwbLRx7IKm62YqcWx+wNQ1mfi9p68Ro7SJl/f6rtVV1i9cxO273sEFCJIMMoslOhEQ9vw6XnwGa2juOaLMg5FLp+SxjnbyGC/iXxigsqBqWj0MmAB4GvrubQTXS+ir/ZV+4gbX+qT9pPuZTa8qn69eAObg487hXNdM+8uRtgbgF4WNTGmtvcoMkoKCMCky+FKzuazj6jEofQJ630TdragimBEipPDilHcyTRJKJBPGPWdZiILGv4jNXP6/tZ6+JEIuk0nHoSEVhSyeOYxQAA/Pld04ze7EJL6zVNs0Zo5CQVC5dJuOXtRhQihZu0OsPDthnv4hBSLPEmJVdoy6RPFNGD72pfwfLI4ZLg6pIk3Ov4DBXnUz3SGKzRiDVIigND1hzESl638VOV2xyYD0fa9crzwoPfvZLGyd9qeOT3zMS/MbCUzCQh4lrwP/r4NPr6uI0ZLH9cgcDiXmrGy6a3F7hIzw5XXXucdO4keh8e4djmRTSXvXxbyJFPT+OC/Kn8U/DpgB0QBZ40uRwo+V1uHRFC6BgbuFRqmzidwgG7SoHTWWbb+BiHc9mbQmO6fIozkHlAF6L/ODzkuuXlxNCYTlVTPOLl6UaIAzfW4m9JGxHqNVZTahM/rVzeubpRlmSYH88tpIM4F9iKzIQaDN+pMcVTO3w0Hy6Hl0sqWh5/zv7fWF4seNGlPYlTny0Hwbebug6QI6ZmBSDf+DdxML/qxDv28fiNAgPC3w9NGu5CcW/OGWKeIdLaYUOLF0EzpShrM43xx+Sy7zkgzhMruEQraiD8rj5A88V2PphnKwF6hNHAnCGEEn5EgQm1F9S3yNCu3J8cplyxgtWwM2yDc1uOE2B4h4YA+JZmTgCzBROWjoPQLcALLbuKQUJULJ14IMVIAcPbgbw2ABgAI/BX0K/hXyK/QX2G/wn9F/Ir8FfUr+lfMr9hfcb/ifyX8SvyV9Cv5V8qv1F9pv9J/ZfzK/JX1K/tXzq/cX3m/8n8V/Cr8VfSr+FfJr9JfZb/Kf1X8qvz191fVr3+/qn/V/Kr9Vfer/lfDr8ZfTb+af7X8av3V9qv9V8evzl9dv7p/9fzq/dX3q//XwK/BX0O/hn+N/Br9NfZr/NfEr8lfU7+mf838mv0192v+18KvxV9Lv5Z/rfxa/bX2a/3Xxq/NX1u/tn/t/Nr9tfdr/9fBr8NfR7+Of538Ov119uv818Wvy19Xv65/3fy6/XX36/7Xw6/HX0+/nn+9/Hr99fbr/dfHr89fX7++f/38AoT57Z9xg7C/jTlFes4N8s3QTIzMunkCgRGsjt2gMZSgKpMr7li0N9LYCV2CxTx5v+V4EhZXgPp7qcEfFdNXLfyJfx1JGKbVXEbYGg5JVKuG29VYxduogls9rpzCSXH3eVcfs9Z5Kkr0/QhAMEOgAKSJNS2KfMVT5V38YX68BFckkEqom1CZx7h1B/v/kORUPDo+2gu4LWzkEubOlFICWfiPKbYoCwnnVmU77gC9EawxdNc/4/SptF1xxSnEnbEpe8oj0GRq9j7K4yGypnNnCGBqBAPJV838kufrvPNJX8ZmXIMoFoIzPJTOnFeRCZDLqZbh5JKl1009+Ln9aN24csNVG/PHhhQVyWvW9RI0LsU0VFutIiSoOhQO+CTBUfKuB5jzl+e0pQRmAxk5WFJ4nB4XXLLJSLIIDODoWX+aTd3gotupiXzOWuL685WXWh1XYek7+oy/sUMhVc9JjGph5U0HwE2TTVjsmSDhvBcNFwmcMp05QfQ+ceoIwasO5ZbkUiz7Csih3B1Vc/QIjUf/hUjuVAWQjyjXdW4PLYTlM7a60Rw7oPZj58SnBFk+rP8RwVom1ok6LN5vKzNzx08NqD7vboKG/kjAXDxvZgfbedRxrDLA83DFrlwCZwhUID5RVxOT65p2pHrtMa5fk0GNFNWJnzCplHpLqjOc02+txTffASh8jWnDbQ9Li16ZDVGN9xe19ap+Q89L9j778a/IjxEqI6pO3Di5xfQbBbLzIFtCQbssz0wnCJtCpee5Pskj9mezkxybfkVovKHDHMhSzN5/D8BcOAXWRKC4vDeY7onljA6J2uEgtyJCNAzdxom+DeITfg2XlKV5+tfas57i+XP5EXCJ2qCcqAF7EviOFMEjgdgoz/ulDZXMgQh8ACXCQUTXC0xCiq9viRPXnGjBkp3J0/AXb5ASsp/1phuSKeXG+FS6XU7v1ofdiOL442fruKd7bKW5ya4vn3gclEJcRDnxHiHxGUqnnSZz8O7fYCVo4kBE8YoByue8GrQbLw5uonhSfCLuSAfRsidPJf0zjkLdp/OEfmQlmhjiLAj1RhKVpAXoH4/NJRUY/Xpekqf6ryORISzZBnoDYVvjhJ40MHJ86CJFbj7hjsfreGEjPnfykXmjRKxUyflTrPa5QVqgkQFXUbImd/WVY9IsKnFwUKr2H+HA/AQK0oZ5G26CW+HYiEOhicpsquZW/KHlbxVJ7vJ57RXZpTdTStkLdlP7FxSgcdXrV7MAM23ZXOZxRUVHO1qYnmcN0riKtaRYyhqGfBuB04c9d0enS/zjL7VLuHBBrBweLMw9lc9BY+9Q/MDaB1EaPPj2xEZknYtR1g3hh+07QlHP2p2c0QMJSLHZjw1YYY9beu6rsnfrUFVSb7KcFfcejqA+EgrfgTcTrT8VB9RnqUMgRYDL14EVcIidDhptpW0+SQspfE5z7wpdCSplOtovsztJ5K0qxXEHF105a5rXbDK5UMwg7b0fJCQizpxztHwY+ZAGkVArdXWGNX71Srb6Z5BEGVpB4OqYaHjmh4afzYXXYdu9XcSK34oU9n8AFF3yBRBwluWKGesaD31SQDeoLZ3BXFNzuRv2BQWIp8IW5VhDAiMuDGH4LA5H1TtkbT4iZtrHIsBzGgmol5o0jroIJEbm7Wq/47vPJpbe73USmQqXm9Jt+3ioDymCUpuajSrfKgPx9fX10tDO4e9cNpr46K9aEqUoEsbDkE8kBG6EWhUBTTHeNuMr80nuj+C4I9sCQR5AMOv/FfvXllXUv+Bc8WfJvpbnBwGNur1YmL9q4Lpo6f1sfYIwPCR4bawTzfmN1JBAezAyuoQnapn5CNSmEnYsd6eR9TPwykEAbUPgbAHbfdarQZxuPJyFFqKpiQALdXsFFjpJxvIG3PftuzHk579PqhhwlfdzqKZEG/SE46G/aKO3J8wQkQoK7UE6wiOitJkFuwyzvyS1yyFMI3CZm+zVTlnAYtKX/e2BKWhnsTNtry/ARmzdKf9j78HAzK/qgpliiJTxXi3afHBEdjbWojPzKAks3FgncopoUO8sNVGLIpHcoEjJLHbenHZLVdA2NOtoFXsyX4+YOzTkS1xOdY7oIq9EGA6CgEJtY+VczAycK2gC7qFx6BlsR/WV43EKURR1QBSXpGnhRXqCXbv3HdTc/QrIOItMDG+PwXp2G6UYahrBoJHOEZ/RGECNdfd8PV6Hi5Q+IgAcnzvM/q/nS7q1O/5nLVayNllH5fuENOXCGYNpGLKmI6qS65NbdP9jTEm0F/CPEGNhoRTgZFncp1zuz0wHL38tDSUa5yF/4/p+P+hmGkUQjGpSIYSSkJIWYZ/15+VQTE9N36EEubzypGa0A9ZHf7NpsmnvF/FZ0xSHVat9zvG17U8junFZN8oRvfFY1hU9RbwCK0QvOMZdOcyPe57fH9Fbwkq5w7ERVkqT1F39ZNMhS/tW60V6KY0p81VPJw6K7FTeoHxfD/ADDtKseKZqj5Cj1sUfbzyKumx6GTn6sUXI6Y7eYEFg/ez7taKkWxd1QyBOzyQMz8F0PbsHQcADGapZfcskExc+9w0rl4BSdFCD12UivAUsdD1BmdqgsnHKKBNNop4wjFw/QYfgeRfyI4/+NCC9rM6bMIRCyDG/EQFNF4qZjMdu58vSJ7o1YHiag3P1jJZGQVH8cRTeIsodTRwUhfRsCRVO05BqL0+HPyj4PxqIRpAYOME3iMznN6e66gaWt9qslBZej2zCqIr1VGTHJWL+Tek1hwV9J9DX4FXOI6XCQpeb8ADdz55+XoaJcOpxFbP+FjcGCFA3R8CUnzppSyxQmQ4dtcjANIhg1TSftgqffUBNRJGhybbn3Ak1BUWzkoSU5m9gZdv0uMuPgqIRH5wlhaG4fvmxscEixIR6HgA3ZyosPgbodXGb2VZWOfZl/yLO0O1/LB1g+0X215I/3hTLj0RJM2mGYRDNzCJq0hGybwHPe3MvrDoxfeu69YE0ITR+NqfQL9DDpLXVGkDeata/P/sCPnZo/AeOAZi2G+UeAQ2SJLNnfX0U8t0DtS7BOyNMxwX+elxu3NuB3atinnJXkPYPvPdofk/1NsLWXN6ETqxPrztyFgjJLOk/ugvvkSWF5PXMLkRBAW0cPN9D/u23L06m+dz5QzOCrFoPUtdvlFneH0Jxqe1lpqBQlluh0Z5Ya5Tv35TN4jN7BFBDOTIBRzP1loaQDEOFbIkmAgES/CENNVvASWrtC7RCkBFzE0J+XDbEzeEcsFbVQtomCIkZAeCpmUqX1ArRAvyQWsQABAX82GsLEVN5/7wdaIY55iOpGhMdv0z7IHWllH9Ej5gJn8lRHISGDaQAAMK0slQjkmnBgB2YrO/ui1qU0OOe3jxyrQefqbNtYiA9heC1rbrDHbfjoDm906cEA7nN5guUoIdZ9OWJ+fzKb2p0J1JcL/KT3uX2UdZm/fZPC7T+wmoKyYqnwnMBozg89r7lpInzhrdZA6x/Yh5k72fvFl7NiNGV5IkmnKTgNn8hqeGaNWqtefBxi1SzjbtKcwfZUt4GDowef0BApoKZalnzufotfNlMnuyfpDdv+t/HbsVIeVWSMMHKDBIFrqn7L3DrhEoto38ridYUiz5kSvl3i2vUof8KAlNu6MBOtnpqppYFyo8Vw3DlMPz8PHsGqNynZdEZQ3cqEDDLWzAN77453ARvBIUySBgLxKBK5l2uYxkEZSJCzkmelOPwpPq/nXxFgMkH1HkgiBkWhg0GkzhA8Bs9H5S1nUm9Wc57mbBy83B8ZAyNWxqzcJiooLUkFgDubTntkYr5OLiaOYd4f6DjQsxGLUIH7LyIJzlr0SjsSQl7kZRTpfng7woOyy7fPr48vbQj0Cqv6644IMj95c/Ub5kl5DlCKJUWsBHsNtw+h8u3+7eiJfhRTTV0KapyNCjRREU8yZpCyYV0aIh1yTc9no5g0hpgXSizCTGuYjuXo1GGp0tEAYpbJjZmcEY1SgO64F0EgPBSTO+SCzB/eG7RbNhrFN1Y0RVBFjm0U90kf4xf9zjGNS6vvTH40Cc9G7Y4JNb9lu6XiKRjtGT7lljZgODTcGFrNEszcBgNkaSQ2GILqC0+JHLQmlFkH9PIVQ6k3eA/BP3AWe4h0SHL9eqgpotr4IzxU3ATRlJ6EKI5Up9UhmDgpr392lkbEKNE1ZhVwuLViv5Rq+4HJ8+RAt8FpMN7OjCGyOi0ZY649p7EIid/GtYOhwYa2dRFsSW3pSfsc6mT61rl+SqIvAKs9+Af4JFBuC4r52Xl+AcU+AeioxQJnyr2U7b2aXGU9VT6KuCVDtqqdoKT5yG3Kv7YosB0hQaMqPkugTRC2Oe+ZJgfFe8Ie9bnfiJ8+TtHnkRM3rEOMV0AACz/02TWrp/s4/eF2Vv93QzEOgsIAhEJ/td2GdOeI/xxNYnvHOSPoMWDBasFojaeIsp7rhhVd7ApCQpCveceAo11UsyfDw+BNQraZJYdnnc7osEo1VlwgcKeIoLl7uCNd8+XSGqHJJPXEt9NEhZyIACtj/vYLV7FRuJlNqkzTdNELRnuLXwHBh/kVzm914TedEmuJL5FG+n6JOPImensGwzXT4qwj+2W3J3ednhAgxHT0qWgJavH7t4DQaC66HaPNXHfCjVGX03uKTxrzbdqjVmFkoYKw79t+PqhKC4xLlMbxykf9vF1CWkoUjNyjDzxVEscPzZphU6+FDUKq6dITwOzyCDRUmRimxR4IwNSWMl10W1CSIjGO6hhMgMDFZ+STYh7btNeMNT2p92/rHydeUvXsVxdhPHJNC1LDZDCzsWFEAnoEo/5Jk0ymBDtj7U5RmbTO+LLBwLdmA7HFN1ZoNppYO9FrDRqfaAX3kEr3VNX4OjiNzV3thtH8K1tTJzRyAMC4ES3DScOFpMBx1f1+WXYVz5BNKPKiJzWLG+sagiUKhmr3X62idRZyk4zUhBeBsUeLhMIgVBPtWa2XxlIaDkMgqicZKr2RFczsaa9mpkyL4FJKgz7Mg0oRAhIk9u4rrMtU5qPHWegiWlt0WRdoAc3rLyvyKMH1Fo0D9itPzp27mWNxNjyRyv7mT4ylHlMcG9FxmsvfcnuHj9YVPYaKlGd9/7rgvd5FNMh5Q1C5TGa/h7N66F7TClvKkPBM5EBgZxkJ8a6531M6IMYmmlIlOXA4hJIi341ttIQ2ryr98XfV3qFM2oYlPyL+PYbQy7sNa3QM9sxtpL4eQc5G2IisqcCAHi1qGI7ujoseirDCsGkgK+sSqXtoATTG1IaLptXnpZ+Gt4mw6JiN1rocQ+tHUaPBqRJ77bmE3/DS49+WnGOE6JBbj9wcNA2xcz928nmzbMvPMv5JgQIyb8VOrGcWsmoC+pE5zN0QBZLnvi1+b3bE5X0xxW+wfh5H4OOQEz78nF/8YY7w6pVkV49uIuXbLYGTaPF0GIlAqFdaLw7mVdZyXa0TgPsmkw4/K3o1XSdusvg06T3k2z7x5LacYgE6We29Ry4eaZlxYOMS3uVJhRmbtJn1gB6yAPb/o2XtcZ2cYQEISiMiiiZBUmTzC6H/fvb6dzYAp6jj1HVPqyV78wkbY94DOjy8nzoLaA2QAtF+uYhauaB/2jGz/wn1OA0MwoC7iUEMjm+8spjrXYtB6MA8mz3T2bz8xIAqP1UN37yXtiQn0NfNI+l13GK1Wkwhhfx3/KNgZ6eY5NktaV6zDP1iH9IkNBhwthWkwIuS7OuYLDFi8v7Z7D37FeUqShCWjQKbhf+sx3evWJwNOcVpn9K3OsQALUMHuQLJPJb4f8A6wUnrkdf2lFVwe5touTTivFi76C5zNCdunO7hRJHxXOSlTiAN6GrLtb2rrrRi12wsGFec3eDZ93YW7BjBA0tdVB88NKrv4nbo0T8ddsA+KHnRjuo4kkkdX0ezj5YFp53slbASfBUw4BRQZFs7E1K1CuLnI+/waqwnOKwHOro1ESi8VDUIW9DgAVc5WJgLM+IlweKltbiq2SAgKDMZdinMNOa/npwc90o6Poaz/XBFfgDn3jYtPR940Jm9tJBHgRuAI7zgTUyVzx+thOnjeYVqVbWg0ZioWsBGqavK1GzrtdjK1nTxpqkH7IiogB0Ons3UWsQK0PUNu4ZQweEKGuTY2HUA0Ujn8twUyzuoA9eJsg8xydZi/qOr2YBc346UmTtUPMIavoV8vgHqjk7hKijpHJ0EFIwp4+/H+JygM6pgQCGBed9uAmuPEVIkzalMmox76MNzo1afuaHpUiLYDOI+qy8Ah2GLLn/lrnDJ3bth4oD+qAR3BJjF+cA2Q6us2feaRuWtl8+wjUDN3Yw2RypFnJ2dpSitrSSUXYIeDiccQnoUCX5rG78rYN+L048GP20CD7isSuAgOcnKaTB9Dk8CErEknRq0RkBLur8ElXt2pLLdfvvU0SGY3Sr/JnD/gkEXtNL/wPO4yih9m4I6EQocHi5YwoWq6sbB5jHEfVoa1+qTLmiq9AjZL7FqPuyJbN0WuVHxAhynW2t+FVBTi1w6GVlkNqVLsX7EWl2B0I2tTL3FDipzwqm5D9EkKgxqJ7ySo/jnr0aXFVNvz3UZc8Zqlhgmba6pk3QlANkJCQQUE6D5MWE5yzmc4xmhE6UelR+ux1oKvZ2k1asSmt/L6GcaFl/HVw61zz36t2OaUWVg2ADfKOGeZP3R7YHI0jLlFRlhr0oaKDWIhoSjo5lqSCg3M/t5NQt0+aU7rkXRAsYUOVkB2auqxZuBRodvmM5Fg+5FtrPf2bH2zE2opYng9Zmtvpf3AFg5v4SZj8kagAy/LnTT9k62o9QEDFsNKBtXN7UrdzVxd5nYhI/YBBOzZJATdm9kGAubswSf+PUk5vv6wZNUiY+A2jlsY7+dhYCYsFA9BPX+eiwWciIrfm+fmwUaxtyZGtj0UKOBEJj4dxQpEKEDeTKRmLHRTmtP32dKX9tV1/bYRn92xYj5VhAtFh+SMjO3tT9KuU097m78664Ja+jpqAIdy4uuKG5X72QDPT4KNXpo2lXx7R5STpM/yEU4dI3dCd4lBMCj6f4Q3hvUUSVB9YuIxYfwjeIWpBpE6ClunUCa7w7ORgWWKkhPLZ0FLpjc5MsxlAyHnZHqlOChWvmGQwadEF1fOU+TGubfgmTjePZ+jcemERxs8SpYo0yppX5kS1WMba0Twsemjgfm32WIK1PRu3YoUNYlMYlFEbaRVXKPHniJzni70JBRv+HlPQ3pWNnLUCtGDkUTBtOfO6dpR7yCJOHqMiBQOJ0GFlCcmrbjd12uPgz6Y2EcKdEbJEYNeILdOfrScYdcZyYSpP4YOA7StPiChR7p41D3jwqLiBLe19ThplWFdwwEsf6d/++Us+1m4h93hWcwyNCwQvMML29XyW1dyg=
*/