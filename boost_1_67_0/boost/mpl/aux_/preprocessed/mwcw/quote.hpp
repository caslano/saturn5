
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
    : T
{
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
/sKBcyFn5s488zyQzD18QnmAwM71ep7+xRRkoj+XjyFtXsRJ29qCdbP456dI0XBHJ4s4l9j8L5t8ChvbSKXXiFNR83VeP31HlSC+sMqIl7hfJaNd+EZGv57BsDlCqhzMltxsRdRwn0l7EfQeY2CpmHH8DVH9iSbQg+H4i0DR0TJxk7XhF1z9YoaZbDFzVeo6ae9oG9T7IzdFeJ4y4k6P22peodsoCnYIpfDtpbJSpf6+eOAfCx/N8OgRP8ESfeFl5hZc2//8EyfwNZ+Gv4MlItvfJXqZ5Bl0DkOGdumYklbc6enT/NsJKH2f2YPDfB7Ko0/zed2+qkckM0AycxmX+T50TkvhNONbXWAlK+lZeJ+QAV5c+jrtx/23JQIMaD9+BbOqYUkF5EryljwnUZ6HjlJ5cedAxHKxhy08WqFF9VwSZtcK4JkC2ExaWlqbuiEEFI7ULHHoX3f7CA8HaLjP8veYcTSS1PN6jIYyNlilaqyBiTVOrF2hzy+HUHgP204gbS7FIfr2xvFIRU6SfVLPyPTntJVz6+5HxQ3ZV6zv1vqHVs+n/fhh+43KS8Z2lxOzzGmGZUEoHU4bKcO8O/LOiy6dsB32vHcWvX0t2TVOjfzctidr/GbUeKtqhXA72d0vo7k0p+h0dnhotm8CrxQ3zibwBHetRi7pnZd6Wd3rjXezk2Attiajro8hnX/vdkoTWNwLd5/ahNV2uif+upbYbW0cSx+2K84zOjbmPVlsnfRsbG5XAzfoVBmeVJu6FtLSormBOy98Qe54FTpSeG1jiG+lzxVxMgZU8a8433y/nP8Ke0wkJ2ixdlXpyPQCiYNA2x6Dc8R/is/Urve2klWu828eJWZuAJy1h1KENd4K7zdrvYe2Vq/0sTyGC0eoErq97t8yApZp9sweX9SeXpQ8IwJ/DezecHnbWRIbf19i3GSBZu+8WjYKjHZH3HA21L7vCVz9hQ4lV1s83oHyW5gR9NTCvzKM4bD78DmIj4uaCLqrkY0fG7Jgt3ceE1I781v//VLdbwuIVReu6Zltwui6mZAK2dhn2F+fKNA51ZG/i5MTzpcvKTST+S9PSNOE9QlSL+biyad86eaBPNCgZcnJ3JC2oSqDxvPuy35MzJ7glyCztThpb2/Il7ngBADk/CWHfCtPeI8aMrcYvNmomPyuQRsY8Qu5GzMgjOq3WaTjb9yUUFBfpIVKUvOuifUIp2x3M2X4wYe0c+P4axN7jdR24um4O7v1CzaROvRqHMkmksffG4sm+4jvcN/uWN/p/sGFfDaJOpRi5eQWdMYioFrmFMHjFNnKqreaeflxz/ovVbbD76PCTgjptiAKOId+du3AAuYOkhyF7auZLCe+66Ept4ROjIPsr91N7/mjIWPdZcs9s4MArxMhxd9LQ2BMiJrJNZCnway65PcnRbAFleKEZ1O6nR17Q+Gr1JtK93ca6WSR/U36e+cJ0qWgNX0xwLtry1fWpeu5He7aq5fuQFi3yM3F0ZHwzdeOTgU6lEyYzk1fyt/i5uaDRg4jgcDJV4uDu1ymLbKCDMAiwaPIzFt9LfOppMe3N8jDCMV86ZHTiGCxcj5pdVVUDEzMEW9Pz0csLKyPAAIs/dOgLgBE6+DtAuJBYC7/k4hHkB/vl455b2Ky+m59HjDTT+STgxcND3PiU+nYpE7H9xJYZhG3h5AkqpY3qLc6x5v8P8fs/4mzf/8iuKVUxmW8krM1fZPhY84nEtOiJIbHKoIXdR5jPheMNxfs+A43DMPb4nuggrpV6x5yJ8sBzm2bOJ9ghuFK7AiY9F8oYJEJxGAGEkplPAU8QFZ/WvUHIK0kQuq4Js2cGKDtzzhutWz3XO2eY3eeFmaQuouUAq3TWOHq/h6d5274QcTyofqQ8IS15dN0bUmbvmLXQEi2GCbOReJIX5fr6BpBrAn6q/71sLVcJx/RUq0J9X12QhhwMdrgJGOmD8QECnBs2n2NpNmZ+B2Rg2vDUdgBfQtFeFWWnF6VgAZ1dgXt5fG/lYhN1GtE/niPzoNCC5skqWDjs50+JeN7dqoregkCNVOa61OxcnK+mioqjoSw6dVob7S5g4O9h4NspU8Rd23DeHZSnx6Tj3t796n3yI3qjT2CDOt0PcyhMUvmuKZxaXVfl6nq3wCsdOlFLfhxSO010lpxIlMECy0hCgul0J1RCcmPew8lwlwIjuHBxUhGcwbkcTUDfcVIdEIGRDF//1jA+/c3FTmJMX4KiVwMjlylb84mc/2BXfRMies4WUK+7tNLqTSo4LkNxWc5kbiZQNu/1j8gp6bKrKpWR7H2ErTbjAHVfQQuSt9XX3szmQlZ6pwWVPINXlD0dwfXfEcaYcMae/Rs+mEw5z+LoVeU0O6PTbRCnGY9vCtlKNbgLb/7AlLXEvG9198mMZ2ojYF2Qc622ZWNjIyeG2OgNDWoajkCZzSy4FDs0JeOdPWD6TwomS1CG0kUEMH/4BTPzKoaNPE8a0gLm4KBAzS+o/OHe4ZEE7DUULxDwjpDfS6DvBEbi+szKkb62eIMes2Adypf5Prd8CrdbrDi1ZG65RLK07YS1sA46PNwjCCToM8JKprJq8pySMZW6OWPZYI2DIAVSDHhKwfGpKdQZhN+pMSl/FC+ZDTOw7bSos3Hg+tNwWA7DiyZkT48D+rViN1I2TkTMuarXq+fiLk/Jb2tI/dQcqsT01qN/QOAH9UWogRau05xt2GfMZ4SU4D56JdiZlqu3ZGA33bBRF1NxL8Po+tAH0cl2rzJrjuwr6ARD/6y9YEN04T3qrkVAnPK97gUdlx8W5z1n9adwxulFL/WRMyzY1IeoY+qxCsut4Ms5qqUWUGNr/W1XI+2BWgXOgyusCtbMojkcybv10/0Vk/yEpj1D3nyBd3X403qmSSzGane+ZhunEkvUlXI1/zfh1ygwXYLKIuEQrafxS0muYFPHiOZsA3MrTPkhyt3CYLbBY8gPhSnFoBXYGDgebVRi8T9NKkLThhYdpPqXclPJMEa3EIPdcrNAknkCTlU3emsqu8bzfApTPU7mbwRJevKPrnEOWjgnE2kF7r+UMQ7RfMnC7EYCT4opYuR+uDDMArHgYAKDX4MRFeiwX9sJ5DBtV1tkoxJTGHbx1NoWnDEzzLATXLwSbSJ7vQkVAI0AAz8TXfVXQc6/QpKEhvA63FGg5bVOWNAmdVi8yoblSedtU690aEjbKqU1dxzpk7FPxektOrpXHuI/vnqpl0saaRZ4N8T1PH5EfgHiCufWT0dDv8ZaS/zxzVAPXB6+q1Xu6miphZQamJaoombKw6965kqELxYfrjadY6p1QX7VW1fUSZ2ILaxRb0g5JLZOKh3G4hSOgkiWCHcY1yJBfOhnFKlLTklUonen0X6IXZCgyOn3wLX3IMsPOHdyMHB0XN8dqaaQXnVDZFAyUXt8r05qDjpLZBsDx5/0a0y4Ca66O5b34Ki6T9hkr7D9SftIv5Wf5L8bSWIcoAkIS9AKHMnsWHDSOMHddAqMLgCRBM23InXiikjj9ovh9q8u1zkMheMZsH1zsQyz5IqkonZzjowMGUH1kOeFCLRcBHzI9PMDbBt8uhvkX8K+UO6c4O9vXnpArKOAQmGA7V2gNubE91/mX3DXWqXW9ChAo8dApS/65SnnWVP6LR2AgjuwlG+X4e/OFChQr6xKrXQsjGRTwSK6lgWZ8x611zVv3R7N0fOFN+t5Ue2wrZHJrh6JkWeM0nM/F1fwtAJtFUT/VMtFmG+1L0mwWIk1uq0nsGury7uwXsFPJIzWA/ATXepR4o1Gh7Uh0B//5F9ty6/q50hxu3X2r0C3GNEW5weTqqtrF2lOPD6dAhhFWxAvU7OwzwrE7ZTIItrGLJRT5FE3oKftcq8t/q8rbQal2KCyLpGEDXeJV0xgSENvBf4eBDZf7acsFiM1pQhVyH85FWf/m4M3ZinNeCDpkN55mWgiIGBmehKYqqxqZbE63xhz4Vz0Yzg3IkAvGteQdqnBc51ypx0us4E59+8hsRfAryrgUnAjgarH15zVKKGEw52nPV9OtbFzb1y8jX/DbcELKrHbyJvdLvRaaKhJzcyPZdP/iv89wcv/heMI7td7RQjYv04INs7UkGndaZFCBno70wjcy+Z9DSqqx5tz8Epd5sN7hXJEEIuz44BLRi1lctjOI5MlWESsVuUHJg004EjlDf9rRgpl7/9JI9n65RuJqmrg15RBfWVvuCrtzyxwOOz9r/eCmQKklesVd1o1B0BuqmdSPbfPYe9xEIpSHKoIRr55HGVcXgLNuE7Smqk5DhhJfW0b+IT0D5GUed6DO98b6FaUjsnVPnybEZyD1jLvBj55f4ssX/xraxhkzinzpng3rFffIrzdI1psyXWdHnogsVvubZRxcmCxhqUQMAfnWLLGHOhPqhp0VO9juP9Cxt7SECIirnyWjXtKwXreBO9pAkMN57wKo3x3X9vwTkz8XVZ+No8RYP7lfIjOx07fT9WFD2rCJ/QhwYup91r/WEL7Xt5AaLMJLV5ABIij01kElBdSUlGRldp9I0BLR7tQKa5QQihrrDWxQ/+2phKPV7Pg3wziN6wtkdhsNqbntpjXaWKYw/vp1xAN3TDXZJ0kaP3tBy1t/XwfTySMzH0E8S9Z6ZrPYvPtqbGuM3NR33+RfKPHNLk1dXVnE0kQYvYzO5nvKcQYZYgcelTgsJmcBYCBGqyXdAlLyZq3hVkuNUGzu9gTtxwFdAHi0vZqhd27zXSZ9vLycqGgv6bAVl30vviZUtKUz/aNClB3y/dTdIb9dYwk1BJMW1fyXMypoamezq5xOre0iGq4FsYBgObf0SB6jGUOxbpHWdQlXANEm9n70bxOCuUoGgciiEu9xX44A+qajh4z4LEjyXM3mzHuPVlJKwPtm+/bQ92aboFJNkFlBwC+4Asp0t7mYwXOW+hzNo8DZMhwBvcZXX+sXxQWLEcwfVu3OgKTdjkIW2p3Fv610aE05fBILwT5k4RX1JiiYvQxqmRdb+CB0HNTerH16ci2ch0nzaegRYKfilkgH/F7i9Eob+h/FLfEaYx9k6lXuMe8zxDamyQLo2T+OXyEWclBw2krzPL1ABBCflS9288O1k0zKh8gqhDn56eVBsSHbRMGfIpNIz8slFX19ZcGCWJ7Tdzw3xnRHzNX281Hx5eVpbbHN97kaUzfLRjomf/jedoFppJZV8fCDYcPDMN3Xk7vcm79dkAwfBDGFKCkPCWXJ/A3FsjV3pJqb93Cw/T/s4L110RQJJzdbtlwW+ttVbTMPz7KUPWU5op7hL6DfplQcz7KdZPvLHngtHngjHngvQcvGjoRdJRj2kPuL07GSyW06WIrMqYHiddmuK9e3bf/+yOJILmsUBO8wglqDiUD3mVSNfsZnfIaenp391lf6FXYB9iWl6Y6ZFL5bE10GQCh6n8EANqSJQeEW//eeL2bWVnZ/9MiTVakRyUoH8aPRTW3mzImbtvIf/H9H657lJ4EmiDcDAW8Fj9PtF8F9pYNxAoHIKka5Hoyi/D/hvfxij+uSLejv3yr5+nT8CSMXkQ336D2cxLrLnnby+1GfKA0NMjCnmQIMYmGfk55ucQ4DZ6XxcB1Kav2+C226DOmfjUuxeYLu9ygWXZI/aPHhCAGRP98pbvemeyGKpaDI1XwhCkF2DUqKOJmmIzHZmMfql3f4x16on0h62AVasX5+fdvh0v/AoFWKkafeylObqgSzAYsDXjegm6RdNCqlPPtA1dgOTC5nwFgo5JSm0zgcF76MfRkdR+h461NS8It29/i4acLxW93oglpaV9LGxu9qo3f2WERq8Yfe4aayxbG0KqMgDZfdQm6b3oIjM83/N9pAmQxDqBfaRKcOxHCq5CrpI1ubehLO+esXXu7tEdqB1fjrku5aiYTgLCghFyR7GlXqRX1sA8ceQHJzeE51PFEDLibSyWc3s3ds5To4/rejYGrh//0meDYhiOdNPKDZggmPepHKyfm2glN+nbQXGTXcylctl4XG2BoHxaf0vDROGZh628DP+rJXeWDv94wRBg/tLlBW1g6IW7m9vmfTs2n3+HPbougW9g0PEZGJ4JYMs54828FWaJA0rkwkbIA/UACG4IJ2F7CAGejyGBxwmFCeCgp3ZE6sIRqdtemRWkhYbaXFvVcfflesipTZ0/m+u1HNmbjJl/x7aNBeeJGSzQrdQ/f10/+oon/AyMW52cCnGfe2wLYFVZjut/ydFMZl2VnArK9gh9Dix8lmRQug3SAi3tV9baYEP+tBGznDMlUCWNNo8HgCotenhTH1qUN70VsrZ6GIciBpR1CRn1kynspXXjkL9pMjNG5NRJDkYdbiDqc1vlDpvwR8pu+G1UHtSKvXh6eqJ3qUK8TXHFLqV6pENR/tQrZto+VT3W34+YInxHOEcVkowCSpjcvdVEmqXpfULgf0NjtTMYrWqygMDsVYn4LBN5P3UVdOnWc3x8vATP7mN7Xu7XApOR0sAaefKAFNTp3CqF3kq9epdPgadrQm/qaRKHg/MaXT5Gi9UhIyfT0LM8MxCe/XimOYksiX6t+CxQ+EHno7QfbcLXt9v6ZY3pZhztprFIWOG+AZ473R8mwl/Yc8xBCQzkr2cpUEdW1T8q5y3K5y3b5rlEqJZVo1HNtML9ca0aqafQ+OXLc+PPBbM0yUZmqeAA93ZFZJDZvatWbPS5c4Gwe9nMxuzEfK1Zz1UD7kOCT75kYLcAXxI13TRmOcpWPjz+3+LNqyy7SiStIrlIIPC/BSCaAIJaOl9vqCye3EJRQ0JDobo6OlPC3ufGwafINVqxKagPbdrk/1LFZueNI8NMJupuuoqiDAXfQAXi5ZafSJJO9aM7Z5oLuS3ZPhW/aJDvJl4LIX1490YjmTCK4b20UAp5WMk3BW2bzCZDU50yLZBem0fA12aCm+k60foCC8Vwubatno//gncIRWNSTkfV6+CNjj5voeWfD3ng5rOU+bxsoR9KRoBieVSleNmCCd4YlgB7N1CfZG+LjvzO6RJvcfcFAHqkayVnnoR2Q29CfFB6yegWEHKJPl1IvkjkXWBuUweZ0nlSS1EniQetnIwEbCU8mo3AHLcQQ/tczHx9hS8EJ9r97o4hzw4fZoqeJv3gFzb/m9SnUcOHnu3QRPAT7eEPCzSTqzc4Dmbh/S6ShApOsppNkjgjpBqUFEEpD1JpzOSa6Q5yvpXKbm1kRN8aatW9z874GJdUuJcIbj58PC0XzvUFhb+EvO2IeDklpZgvrlaKqaMVWKg6epUUk/x0/4KkYfZjZ/HkSwDbNftFJB428bFnpM2DF5ic2zzogAA+8ySC4M0yQ5h509/f3yQcYnKH/FscAYL3LCws92qyfWfFRQtAEMI1t4vkkwJuUItfmjExMd2S/7yEr08qyagVOkfyWgEDRkOCNCcKO7XVHKxqd4qXO/h1nQKEwVy4Q/lMqck2RsHPl46jsZeK0k2IkffIxdwCaJG7cUK55vPfIUxjVbuN+SzJNn9DfDfJcNJ4Pp7yXYi+heIQMookkTiPBL94WZ/+oWOa/9AOCsmcYdf/Y/6hTPwovpTq4nXvpit5HT4Zp6ambJEZvD0inL1r6GQj9ngSb8SCfMrvwVUa3xE2WRZ0zFxGxBFC/yA8vhoWSADL2t0kgbO7IgswmvmTwJYC1EMeVnZ2f12Jkm09eH5Tds5jzoUoHjnu7FMi1P3Pzh5KUXl99uAxVotPS7klaIvmcCEW//aGd0+BNImCLCh0Lnh0jSTs+UWBMoaviDuf3/+37sRufrfQUMS7sSumEG9bh6Udl3EvQmZRF1bXDnNQMFK9l/V5IwPTeMSgC9t9pKHFSgPW32GA1Yv97uzmfZtRbfAFGZRr9Fc/0tI7AgKz1hyPQBLyoEakGQLQKeyrM7c4YhWqmxfpxethJVdmbp8B3SnLlmmQ39Z2JI3pUf/rbs2qJOT1lu727wzsnBKXOyYmJl/M83jhfCKDC1ZwTc4TqdlTKcyYv4N4/06HBDkWhfS3a+8wWfdlgSTiXIQkgyg9msG7FU2FvVN+OsHhuE59zOtd/YkW9O4z1s+WSjUknTf2Ftde2BDkd6jIUOF6HOvhZXnIWjKpBcGGs/xeDcIk9MxlEuhFa6iW3nHX+cPGMu/Hs4GODtHpfhFZ90abv7//8OhTAqmtGd6L9KCkbeQ8hdxFILjb/DvCjukUjqXzVUmiBPnBOBQDKlGzPgPRuIDdIJAQEhLGifpe793Xdj8dB/4YkfLFEZ9CIllbc+1kxwKkiyeoNkbaeR8FPDwJ+bffJSph4sr5heFnaTJbn/FPSGzS+21Wnh3hDq8kZ/S60JrRcwULB4q67TYziHp17AFRvyBDlZO9BsPxYQKdkKcLRgiExPEqeW0m4wIXxLa55v10+y1x+vLsfP/kRFSR2z9PHCgGK2eJ8ka7Mg7apN3kWKjnarXCDnJHOuKi5P+uXaJy03ggOBr+gtrpAUsc8ZW6dynJyc7+bBbwuC+4gEglHkkNDo49s6v6LDV6XF7nVMa1CZhDZQO/YIhKGAeVatwf5ySTf5X2a9Kpc5RN37s/1f/+TEMP6JENOJdCqe9ZKrKQlJhM0EcfeJLc/jnSVe8410gObo0F7uQ/kGzA1B/X1TtzPAP17JfrLGjw1m7vNSDw+dAl/QmpTqHwKUQHO8i3YLm8x2UwCn/pogf2Gmly94pq4guTqN0EkkjVHiD6YYWhPsvNmOpSIy2i+zT/POe6pMQ1HhxbdZBzeKDSVYd4bjp+dHwbd7IpZ6xUeLrLEWLP9qXYUWnNXrH97VX+NN5kuXKpnHAS6ZGUcWuYeaDtlt9kJjfaTQAfXrUtxfriywJ0/K+ZgQHZ1j8k8Zd8/ZDtvEpiqUCECzwLdVp+BCiy76Y69qwwzN3rYasvlE4khHrLrH2zR6KmM7BlBnZ8JSaVKG1lxdClQOKr1nvzZl9Y2xsPDyk/5u+db9Tqc7EXiBj8rutlx8XB4BXj/gxdKuT0iGzySjnkbo/VFg9yhT/YbTIAmw7yzHyZ5P4MaJAcbzhzEscND3SjfyGGx5INkYEWlqq5EsXyxotI8aBTbMbXFYLRDuSVmxkRBHfJk8BOlqiXQdlInK+4ePDRbHqWdON5CuGmxhMXrCsqslA1MlpD3uf/kj9wvhXMFy+/2hXOVvb4vXtAjwV3aNjbluE=
*/