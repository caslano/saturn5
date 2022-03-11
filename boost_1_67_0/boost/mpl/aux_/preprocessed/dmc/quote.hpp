
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
PKII+Qhr0kyPopmwNRrrEeXa7t9R8F4Xgy4cPTxAzv9Jw8Xe6dip0Y7HlJV8HZZtW7YAvRPqgLR3WRDUKGfsEGytr6Nw7/cjuHppNegOHvcbBNeD0RvDc9D3x80ny2Q8tDJmgnbOj7ASTTpTppDnElps0P/2xbdXvS6Zl74yhuDSXEFvaAS3YcDrdbT58y+k1F8D1nvnYroy8YU9o5TKh5fgtrXaIUl5fP3h8AFU/kvrAFFNNvZflYK6LhqMWQo0Awq0M3o2zUhWenAyz67XiseXQIjSNPgzCFpIzTGQzP4FpsaLSAcc3Bspmj/BuiVv4vyxoC7vQ3IpC4c+lWm9YjVJHU22aEf7k7ewwNZ2KvogSbsJofFqjErBkTIeXtSi+ufcXLa3YYs2E8UhU+LPAFBuFNPam/fuFPAaQ+zY7m0GS+88YcajoCvlQaRq7RySA+R8slLrWWpp6T2aRfy9bViGrx63JjwUje0WV8hb2cFs15MYkp/pR/oYaJgw7CMzu1dhRCAcoElAoKZaT4Q1I42EpvYxfgSbfthbso/y6+MeuhaKxCIV7UE/4xkbEA8bnQTD1vmXpF/P2wptqXpZ7+v9Mjp76lKUsq6UnTPE94hqLElGRpgFmnGmzni7OPaJOhwK3K76cSrSnx45O5kqoZQG6g0BL6qcsEDk6SArXxZJ/NJ7+fFgEvw3Lsv7XFy+XhAJMPOGujP9ox0U43YSS6HQhHPK8PrYvZ9uFBH3BypgRN0a4kEPMZWgQ/4a6bgKjrVbPWwoSU9crkSepEiSNdv9cJI830j4WJI5CBLMzYhhKIF8xkmpLJSBBq7ii9IQgINcWO3Jeb+ROiUsXXzuyloxcsRe4ImBIqyDWXzUSbg3puaY3U3CRhXQt7e49PrDA3BAD12xf96eOUrlg9Syqrn4d7VgRmb68hmhpuIG2wSYAvPwpf+aylHCDvv2X4Fxxvbcf5r29xUG7BhVb+ry5ljdTv5KbAr4NPTB6JiHm1GYbcYPRicXbrbBE0JWM8HrQFh7MnNHewyu+oRg9WW4Lf0T6Q1Ikbs7P0M7JGfa3SayNDRi0iAKoXmRLfiYAAirRhL9By7z6RZEqtMLLG/KmHZhugQuZa5x/Pz4fv4qZAado1qHoGNDvJ/J/G4l6c8cNgvFXaRKlNzfB+BbGVn3qYrZhfKgCzqEdx23v6nJHyrxV8T4WfpWHfZRYxdUa/gvyLyYu5CHlyYysq5imbZP2e7D2LgFYzCK4Ayat+O2qYyjAtU/+j+RULugyAdOZZfm1V+ghAxF1MGvY7oSafkJJAbkvsKHlkEBqhcJDclqugFvx7lofB/U5q9mJyGNSinqFvvGDt0UIP579+Kow+jx9HSSklMjUfkdqmaU6B2ETKR57T0sldVgM8JEbHtUpeXLxK4JjmDxCADk0Wu7oPzSgxj+z7nGep+dRDEXc3r6plUW3wg7gAlCFm1H4Ap+UAgjS/B59ux8oanEX6Hw9LUc5QpBzEWRiqWUalUWqZXslxrUYaWaIDa50Rsab1nUilC9eGGJOyIMPMLe6iXfmEjUNCgrJJHPDODcQvDAn/jyBb6PplPqhmjBT6Hdav427F4kaYVeqMOMWbguss4ZXBRcscrCb/t9BP/KlZANTMb4ruQGwDt9FW/QPHpADatIl/We9OpZypSmhEyqqpSa9up6lIayYe9Zb6PwHNSpd7UAIX25BWeX2EOvpFyZ5EFK+SaJSfac3qbm7S4fhW33i8Vf43diOuE9XyanNJ80GWE4j4odCGHEEIA1ySBxrYN4symzW+l+CNC4ccdcFZb7QAqdqodRtGVZUNUBXAHYoHjZQtat9bqoaXL65tr2KY0NIVAgJ7jeuk5TyIlc1mr7/QN8YtBetfuE5jhQOxDRP1EIaDSiuDI9nJa5bc5IHMpwZWFiuuA6Lwe7Lt8TpMyBBFKXccrO5KMJO2JDjZk8ms0PSxPJO7OrVKWTOxO+V7NLZMoNarL1nsb9GYmm454q4Wq6KXs2Ajm2ZmAjyQynGgOPvS+KABixosrPUfPozIuRk5Kl58HZp+Va6mYI4hUubJIHSCKxy+xAwhxmEusUR+cjDAC2E1j8dcPB5pFzmbEFLqtEjpDY3v9Fs5F5P75ARC5BUYOtOhesaD6FyvkAdyYneszKfPRyN9wgXx65Cu6mjfpnLmbCHojcaEsh6IYpHJ+Jeur2E30xiccZVM3a31pO8cnmYXy/Y98Btmvt0YtnEvf6MgP7dXyKCO0mcn4ywMbqk+sLoC09hsp5XbWbEEPHt4+xbKd7zORmZs1ATmNx8T7sDv4lLAVZT1ji5y1p0I4nXCBCp4I/lQxsHikPhOhcCkKCh/HOQTGk7MJJFlmd4eezTd+zLcUgq140YTbSVfaOMNb/5E49dNXe9t+8zj0edcUWvuYJcAA6tcAnLttPXHyeQ8SCBJAtpfgwSxMEpn4ofkvQzk8g0mC9ZVatGE+dnxwG3QM2ek9+3w8wuQUgZMrvgK0uASbuzvEmXeT3frJobuSLohOG+DHKbeKr7e8R/HopagqL1osFVD/CQTKAw9i2ltRfreQzW841gTKpnaOKEDseIcGCDXnH9xBdFpAH/APVS4OoA1iQzfB1JVd9Qsl4j3RcUMrYl/L56efbBI6pjEISTrHdEVFfzIP4jYF92RmKe6jnHZcsb4wkI28BuUzwgZH8SNpkGHmxFX61keTuAKjTbHCk7Z+neX6xBGNFoy1VxxJPgqdvSDLaZ9s68U3o1PicTWVzux/n4aTUphhI5c3D+Hlo8SqJypBFIAMvgI7TWfvn0e2bjlPFDduA7tFglhFeNY5RhbOUcxAah8pFxRDCMZRZjlM4NilX3vRZ4bthSDePu3hg1YwOdl706gcAE251elPw/+PZIz7w7iojKy9kG8GgaK7EgIFgsqiooKg6zcMhWN9bCMGwWcGy9e0DL9QlLCtom9tY1FEDM6FbcNALQKW0hgo7qX81liKxSAT8l0EkCQ0rsZNWNJa40sOrwGASPfucZre6/BL9e/XybjzywNle5rY6mJ3msjlPp2+ygVE6vBFEBxFyjrrAiISNy7oSCCMLSnd+WC2VjmcoGV9p94jfQKdtQkW5RxYDoCqLkGu8cm1BkvoiJ5h3WVIMJi0vT0sbT29vQJU3mMOvP1hjM70GJ4l+PjlQec28hTBsFl3OKiCJ0zLztVJ4zpr/6Sbuy7jRG0ctqurvwgA9PzHL4zsVBrE7OQf0Uo0V8evyA6t6LDbPHXOrTzIzRFe5j+DjrekO2HUKGO0EQ/TK6FRo5RP9ERiRWjDTG1gLrWuDSewruDHdureP05Q0UbUK71wJVWe1wLTBAz2XYTIs5kycMiGfvLyg8gn8OZG2VspZ38Pc78QZYVuitsPz3eV5f0K9VxqSUnAW4aXORMMyj2P2JrXm9zjXS/jCmpPvhaO3IfsIGNKfmzn8WOAvXcC4vGFdQeTlD52Gu8FpLr/cUrvJBuNqh015hjUa6iBfpeASVbfWfeCeHiGhfgxleHu6x4/+OjL0p7iC94MIsWobcJtlzbNGdrJv95GakGkc2Hy7wY9e3PDDdJduePZSQkSzWGNGlCkQwHhz8o4JN8IOzkNBiNQt4vdyrd1dSDudmz2B/sdX1ZxnMJOTtHPJtcax5qPJwMht11bLHJsGFGBqiBwUQVpv2p+Cb6Wu4oPsxJ+f2vMNV/o6mzLdtJhxKteKOBA+rQE9uWuy46NTLBQLwmqI94+2xTTC8VIrEvUnFatR/Ba4BV84KO5e2CrJRfFVM+EO5wkzO/CYZENVoXhLCohMbQVyC7MqH2C9Gi6hubEoTvVfCfYXQSvneET/0pR8n/zFEg9IiFjWFlcYa0fPI8EBKrgAlo2qsj0w8D79jHBUvsBVZblA0g0oVMVqDGTxm+45TSZMXSjmxI5pLgL3bLZPP1F6mR4LcEN6K1+zSCq8IIo392I5ipYWUHgYQ1HpAhH5ofosy3iHp0ctIHHot8G+ZoiHZ0YSszY7Fc+2w6NHSJWQhG5tmjTMvhNtvXCrIIVgULBSstte0n0js/HRa8cLggHVxqgp42vtyC0tG1sUWp2xFSyKB+c5RbMj9PXzFxtp8Z57wDirgzqmbV0CEJiheQMAbTlr5wtqDcHUfft+NcLg59ClbzbPle/0/Wxl3Z0fEF9MKWW2TZn4yOwU69wsMfdsGT4gYHBhqQk1Cg5dNppDlFrkmedeEWFAWOjeYb7Ps/l3AlO2j+q3L4QK1nO44LP9FOelemmj+m3lJgWQ5BCLo6af6e1n8Mzax1MLTM7K6MG0JHGQYyARZlO1XjV0f3EbThOeq4f5mlU/3D1t3uO7L5Tpgs2TfVxJPO6p/CwoVAbglTFT/BhkDZITYOr3oyKIfYGqdlv9qUvukwCJJRoYFWZjkNnlwZQvDp2y23XfFMXUAemBlYfXkv3KtBi/rDnxNb1X9I44LJdbYsmQ29VCwwXx9+8AMq+uGVT2D9TTsad/+ikxm85VG3J6Yp519RNwc9icPDXiMM++BaKYDnbkpkxCPQmcUrgSjGJO+FQIErTp57aX3oqj93PIGEs/GbKlaxIeAOt3TroC//DbN51a+n4qmXyDsCOyhVsDlO8nuebY9q5w6v8NflVqQefZ/6YopKWIDTs+5yZthi8zMH8NbkM1YSVLDpaiuxnIeDZvA1gtf8UumKngarWqIPPrFCuooEqSUQ1BIz0kaNjW1rdo35Aaw5sG9JdR1xP3RAFiVVJpsS2gaPwHa1wvyi+1CnuZB5AYA1hper1KL2PiV7wuMZ5XLVvLOJ7nr9ulyuDJPiGPUo+zxEGAVvMVrQe1HjQLcKstj87/xm6IbMX0jJ2P/y/CfhNtHHa3Na94M2qPyb799vjBTr8WhMBc37mRGCQ4KFW5C1GjAgE5IO3l4cZHZpZPvngUOgrgBBd+jMKzRGgTEhjPFas0XZ5RNf9tVaqDjwdPjS5w0rG13988iXQnUSWHekoaFrTzMbX4/M+u6TMmjVfplX/qtGFGU8K69baAZQcKxwMIAubNVcnydcoyjDUOyxD1XXPIgezl5NDZg9WgzcHNDwOnWN5ICR9OVTQ9lyyT1rhjJYJW3gm3aqKtTzafLdVmGD670UlS7dSJpvaaS91y7gYQayUBYRjiGmz0Sp46wW1R0O0/gjmiw5Fm4FNZvj8MPWHjnXZUXqkavORdo2aEnz6o1HAFWr5ywTf66oFn347gf19OzZJ8+I3P633/vSOK9UmM4DKzOiGW1tyQROBXBILn4PTq4kO0dg9LbVpgSsDhjAcIC3b75rV/00bzQIl6XOJoCSfdrbNeVyPtUEPY/omSlq2RMR1Lp52z2+mbKve7qcas9bPrech7rLuY3f9Q9zSz/hFqIv667HIw/9FCxCTA5CIRPoV2L3CKtn186Jwd/nt06vI5ElmQ85P39IN88QMfeu33Ifqxi7n90zvwVearZgJzzh8jbRG66hfPaZPDYxzz6HcJy/hVxjNWg/2TdOO1ifn55fhk/8WN/ir/rs5u9fqtOhd5ncdZ6Uc59EivgvfWSxrUd5N1jP7R20EgOZDpuAmAWcJVHDB7XXLLMnkd0ccAAjzgyHMsLwA6NMo8S0tRDMXXg1Crb1YcmLUy9lDh4PwiXxKE7QbOCkdNfmd3CFDrm9kX8rc375t7sReq5b3jX8M6H8+1jEzIu3sdfWuK4nUXq9LArAQoe9TYW1SvxAcVWJtdF32pj+xPrG1em5tkNT9abQfneUejSpkm0k8j1ExiAfo8jWYbFG9aQKBxBR7qZ9nBOCuC8OdbL/wYZuLGUVfaomhO+GjQ7Ra8QGhmEJuP5l8r3gut0IbDV8N2KHJoxnpF8sK6Pp5QbL/iRNyFU0LAAy4gR4YTa3+X0HvWYiLjcO94xX8JHETZOGcToiaMAcIbD8U+LPnJXAewCOYldM5q6bFh6XyQR62LmiJxa4xm6EkCxlYiZQpmwMIvF2KheKsz5jP9pLHaXINZfB5NlMPwYsQ8pM70MhyRhH7lHoUF7UYRsD2KK7ONT83+2OaA7ItAtqZK0GDozo9F1Jk1diahTWs2k/bPHeImHML/hmHM+qwKNTTfCm9IqwLujSFzQ8Uvq8VV/VVMuc7+NXc5veKfLNj5d6rZmT0sRuEv6DO3AmrZ/yhRof05ZPim1gSDubOnSCKWQXMhhAJnlIpNaoIxZotvevxrMPVDrJvE/nnmQ/vpjO2hSeirTMbDeuP7b3eBYrwvaulVv3A/wsx5IGf8n6QGDJka30u1nAB5EHeC9Phx1YHiYuLU2h5r5ofs8Qv0ZxuSDIvXD/bh7BDnAWcQy8tRUNf5GxXXjvBYCkdUrhQ5g6nQHQVqteaumL4s6iQlfjFDoZ82dSLfFDjlzqkgiAhEdZIMGH7uCnpZVGAY21fCbT5xfkIzJCX+lmBfc41HfCsr/GLryQDWe02J3tYVrG1d0SHYu02xHstTUllBd0dGZPPiMQDezVXxoe378eOmdB/h+3XRru87br7elkMie5EGLT7LfENC7MxjllAfxMABP7ccUacXkR9GrH+zpwFRnS9aT1I5Yz8HBWV/5JoiMQvaWIHQ7b9LDPo9UmPst7GFi6LTKL1RZkle7nr4ud6aXN53qtxtglkJ9pGceck8KikHHL8TDBUezJb9abOFCUGyeLrHCN+Pczd/X0Rwem+4BepD/UqENfEEPUsDwpMXqpsiFrJ2RgSv0wPARNUKxfEyMQ1LQR+cMTutBAE+hX958czqpcc4mxTxypDw24ELTOIf89eOH2NEHEsQvUaGgbVmOLtscN8YHgvhII8CHz4MeGgm5QzAle/bUuml2uPIlCiXy82MV8sgTo8pfICs9fITK652gszqNLdCWe9+mJ/k3710bH0hL4hBdIFR9nqoMrfST66IoUKYee9Ok1wMSBiTiBtqS8CZsrDXcoPKKmjFLQUmJW4mFuCp24h0WWAmAZRwVFkgT62PJO5xlFUZRuBEWZ7qRY10T5qxCfy2P5ZkKwDcj5uW6lOxzFUm58zG1amh3Svl+n8keKNqu/VAas3Hg1EnM1mnePHFfLUUKm3sFGQdwzbjXNBmEC4PV25y1eKQZa3B6v1zUWAyO1sKqgeOpMecfOp5MfQ1mzTlyKg1CKRNaKi1U7VGwpJtUGnMIq7Wh6GuMPj7EfPjq0Q930dLmcBtJemLZdBHilhDs5qif9/RfJlstUx1yrtan4FSm1jES20Ra1VtTGo0qqJRvYPlFUG57IsZkGFQnIaBrhFfM7Lkh4lIpZslZ6pQm80csPY6zs6YViRHn+byCSzmsdbPljgnLGxPudvZPMsI20A7co/aA3aVYE01yomomXINYpmX6YO9xXZ2BkVOO71eBf37HwAhgN5/aaBcps7JdjgVozayJz4YEPPa0aVp/rDYCuMBxR0r4/dB+ygE3UP0UpNvEsFZWF4mtoY8+UQT3VdT83Ky+ZhbqXmXsZzZrCCTZS2Qc2bIBTPlrFkMDmy1DI4de1nWLAyaGy5jK2M52bKt1W+rlB0VrGCJLG1iWXYYtGrZgcA4/tKMs4rpZSCmGiiDtkO/ozoPl+keQy7uREFJ/uDMswqsw7AIs1RY1OlhznuupE5U88e0g0lXqt2qnaweLNQO3k2jgxD/6y1QlwEbbNdTRXtZJrzJVgvt5ntu+kR00lHLpL0MwxFXy9Ju2baHrDE1OtctCAoGZbtRToUhhQbCqFIbx9wm6q0kXX8r2jWlqp4bGRAP0JJjN97BEBZV9CgUoMBu2AK7gejFL5VRJ3bfggPtnonRIvF85gw6n+J3lOVhJJYycT/FL7VSxJkUum8qS0agxkZc5ex87TzioPA4C/Bnoev4HmkHnwWHMNKWBjqPeNHzQ1echVltq8GZDZO1F2d3H1ALTHCYx47PUJKznMpdjfYKy3joqa0byUubzbbdODegyj38+32K8usvLrCTpheO4ivH9yn0ymNAzZ23Z1/2PCz4nYc7pB2dt8/K361790jn7TPw7+H/hKxhmB4A+mRSNYbvcOyRpUrZtlV2VAGbzZyK2UIqc5GuSEtainM+rni0CllGt19TWSPWXBgx3+ap4ZnIKL9QfcIeBjkL8OxJtEqohpqxD2ku+TiP0sWs7iIOr83wUfTlXEvFl63lX95M53eJL9vFR02i81vI33/OabRbquyDuiF4CErbtcBIctkb1J2eMTHzlo1glWrbToUNNj/9+dBwAaq/N21HCDl3tgx0bc9EI1H2ArQQ2bPRGJm9BHcd7BRyQnYM8N0cGpbEKhu0dM5JqF36HTyPVdZRotiaeDWVdNGg/aBckSDys7egBo8BI6ahpFaIOMub2z9UmNMoo9HUZQM+YLM0aBgoBD88wMaUogk+Sbj+FesK8+kVRH9YHPO0LPqjTq0TKhlXyNuB9npS4O6LImTcn8jv64O4kKJVPYFNiDHtF+aLUTzBbdBIqzSAbuFmNO1nDQMwjNlxQPmCtD3vh/jlDN4So279yohtMz/fp5SUqMbNtapx01jnTzsg4jwgooNfH/gQLWaT1WKL2HZhAx2HBIjiystfKYpm/nxhxUq4svvvtL8h3NfHgfo3GHwo7GrfLkgeTv7vvyPKvp89zP6D28gw4YjbPDiAAnQRo2GYCX3rt9Xwz4si6XhsNQW5/FXakITZWcNC/P2i5Mi+dQ1vgdNLJywS7Vsbvf+w4CL7DxSOi0ynMIQLXtyvoD6WMpwtv1jJx3jIJ/mV2z5WZCe3nJPd3Oru9VwnO7vJFu4w5PEH96Ck1m097jKyhSgcn+Q5IAhm9ZxqPxPE0Gt1NN2cKew4d18v9s/m4HRYisZeLNOGFXeqdRdhFPDgVOBPOlailz31bLkBtVW7UXY0+s65JwHztLWxN0FEYZkwBTqzsGqPseeQ31afi74sM24kzmCUPW2yM8AcjbIjXOg3+VjixzfgMhrCAAos9dN3NzPJDDSUhkbuiRhd6LKwN8AiEZqzZwz+4mMfTqBlsY2v1w7Gawc149Wl81fYcoO6Vyd1QiuhtSDyXo1pkzBGEozCyeli9Wum1a+FSrb2XJkvBKQ2/gLeN8uOZlKnW0idbi3wS832Qv7sv6J3lXtW4cbM/mVAHh4cfSDtOZZz8Dvdd64k0xryzGZL9X79n72zdK5kpqOtB3NxHGtm8/RKaxY=
*/