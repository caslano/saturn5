
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
gjs16jgo1tfkRSLNNLg2q/VDTq4f/sSrwjHdeaQ4jDRgkc61KPFiWZJcLC/Axevy6N9QGa3NT+OYilDJXvm+IerSXt6v7h3gbaL+G6TZIc9+b6mcV0+p6paL8fMInIQq9pfJEox3O0OevWJJG57x7xI9u+UZJA1VtJVRc98ufR9Tztql3i7PztUmvLeUaY4sLbVJlXZpk1laaWHPrTg/rmKrXD+E4aZVqthKzRjd8lJbqCQiVtrVfuuis6xKxtyvyqsf41eaF7Z4VV+5B//9EhdhXNiedlNNxS5d+fcPUFiN5toZ0utxHchPhkg0EHrIRBUAL8xxQmDJmFRlKvWWKWlFqMmkzYYQHuaPyoP382+8+Ls8o8seelKQm774jHKpY7guGn9tlXhTj2p7BjsnduSn4EVLmfI2dRtp8e0UO4qmhP5Z0kOdMCppLij2NfmnD6BrSVqn6eaT7pNV0pmFK8zWZnzQvvAnOKTW2nKW+W7mp5nvZf4H8HnYAGJt6YOqFuMOC2pw5dI8fNPpGzq2g2bYyhviQwgIyxHB5+0jWQpkuxOy3ZCZIEPAq8QFCDM+3LBX6kAcagoCNjX2gFmN2b984QqLv1BajM9J0aNh6wIHnTDsnTKInCORQxI5nFUrRQ4nPrY50ZE1scLqH/j/ALl9fzczPwCAQ0u9fQ18k9XVeNKkJUAkAVKsUqW4uqFFrQYntUVbIKUMUpKUNCq2uI2xLnPzg4SPjVY0DfTx8lQ2+VCHzDmnuPH+xcmnQG0powUqlMImjG52jldvLXNFsQ1Sm/855z5PmrQpsPf3/79K2+e5z/0499xzzzn33HPPRY+ViKgQ1z7hFMz0h8OooJp9U6FAH7ecZK2V7SGnEBLh5NmQytw9zBZCrlIA6Hfw0VDUeij7oGltXSmrE97QpZH9dvS+YecxogzUCwNdS6IEaQ+6UZhWhhYMZ/gDcX3CFPzgh4mShnRWq66op2Am/3CHgKy2b6Et6D3tnuiQAIPxB7cZt9GAy1xkdovTesZVVFSM1ucbpVI9qEIw88LJW5fsVrl3k2RrJO59UrI1o63CngryDYQoMBaXg/hgSZtUchb5fMk5kIcgrJEaV20lo6luybfC6UFLaL2GPXcAoL+lEBYPxg4j24Bv2mI9OjGhIAb9zIiKSV7XqheAqPW+cWzDFi2y4Q242HRBp2HWsSTo+GyYd+gsIJIAQShSYAo38oWwOBTltb6SPhCmAgjpCEK+IWMVuod4tSD/M1bV4qNOiGseTm6FudeRySiHLok9h591jWTB5bjixIxKrmFFFExDabiZ/+sxUA8jSaz8AOh2/NRjyM5P4saSR+9NwGlLYgkLbH0MeUUj3/xYRKg0kyBp5nNuRSnSGJEijXwKpAzY5xT8b43gfymaNdu61mvwZ7/yc0/3es3D3X1/B/LHB66KXkC3O289UyTbD/A5T0IvUTMCLufEMwxEGFGjDyK+pJVv8n4OCsXGBLFrZGsFAay1nQON2eOUqreSie4sm2HIGKI74SpyoA5nAHGHFbk5H99KelImW485MSzOY2fCYY9DWrlVI/bp5hgyTMCFQM6NduL3f8N3kHPwTpXjRtgMY8YMvQeWFq0uVoQ0AtkmqxVTRbiSX3gGJc455m6NVE8FnWwW6hCQQw9lulYiPSX40kVB4AWJgVACcOSVe3FtugOtBA68cbMMVT/7ATUA44QnwuF4Q/Z29UCRRfwhnblTSU6RG95pZk8DimFHYty/uOsclA7BgmqOB28bYgACLP3TR3jzaRDd5RM0FM9XGiEV6/0TmT2F2SxenSvjMMx3XR0bATjwajySzYIzv4DCvICShIfaAfJUmLDoCEaSKV2j2kPSMFY4zDEhfwzRkZ6R8aQDz3sHSXwFhlZjsIr7ywHocXp2Y/lxBMg/G8pCMw4uR+d65HuHw7R7leLVwQiZXcxtZJ0AroNN1Tu9mmKEzSFgU4KVI3xIJu5U6JgEvTSUCjhj6bnqniud/0HOl49RAlNw4uKxF5TbLTQXzzkjUTR5EwJcYgHIiljIhe6TQAx1PyPDaBESxh549sDf34qi/B8/7if6HTClefCb8US/WSPkTU6fsxd0Dgg6DdYlzJZa7FnIQgvr/m1YCBrkQnaJNeKLaUctOwEpH5t2XGKnrF117WbcUT9T15YELEKyN0vuJliEyBW5Ugnup3ck0fZuk2nHIdNbx0w7WnCz/LBph/vjuotJ8GzaUWfaYT8L33SHMWXHobo2w/A6Zm/T2Tk8Utrx4ftJF9//U6SxdDQOshIzjBWOgxvmOy2c7CH/t9nxjBPssOmto/l4LyQsHJOgAl297ghIzIw6yd4Ji7oZqKC7W3GcEd2OjsyM/awRy5jeOqiU2K87DFViiXNQIpnZkYE4gWJl9zkXUKxlKU6ykw22k6RcfeNmwLD7ALM1at1tWhufEwybntPRxWQ980ut78/jU5mYbmn97NHWliy3AVSop7doFN3Okebi9Z/2GQX7rx8NODFZkgcEZyHIrBBbtYW8F9CV8lFYYchuUgYeRtXA3sPcIeT3qBoIrTl4CBTyFmBUzrTs/X4b3kZk9CeSH6QQZQ6Wl4YVpC5BbeJPjxK7MsxX3TNz0yKPY9Sa1RRl/RhN/wsusz4ArfckcK2bMcyjo4jfiDezhVHZtq2RyrdI5Vul8m1S+S5l2U3rSVa4XCrvkexrpfIXpPKNGNQKEFbkEv0NlK/VVCxqsL2ibJBU4YZgdsVyk0w7JflLdbZXYJnh4M+fRJG4Jtv2mv9eNhx4s2R/Qba/4HRI7o2K4uDeyGwvuIDstsBwP0Lal38qLjnCyZPE26SA7ZXZM7LL1y5fC0CL5UGgMS6znS6J0ddrIjlZQ8ef+ZfemDOLQj/Lzltefk2wdunQfs6ufefL2HF+XMR4uj7YtXRs9pPLy9F6zo7++NBs3XeWAj88oSzZ+PPRLYjxOR89Ppa4/Ok0jkMbYFrgHtWrrD0YmrLiEam8EzH7OmKWkkzyS1jkHdxW1vk7oVyx4o5MKtWzhYYqO2fFRqzQfU7xLJLthnDy3tvp0plvB2yd5hmisuW/hWzqyUPDYDhVMNk/I2uIl4+v+ZGKApo/lj5+h9eO8fOAIbFCt+JdevNjrBNO8QX4hFQO/xRjCpAckn4mTjFbJ0wxVn5BLM+92oxmkCTnMr7ysBpcb+tCbCWuuD26/Q5evFhwBOv7pfzOVXHl79Xah+rK+uxDjf9v7ENYDR/7Y8U+ZPzZYPahlMlR9FPWN7+Loxe0sJxfzStQfhWmoaN4T3RP8G5kmFVpCGbv27cCJG0uzN9GK9fVqupieyxGdSkVcykUVN2HMb56oEKvaUjCLQ7f3YC1rApDRVqR9YzivxJ3P2IemWBX/pBMsDF7VhH/2Rkp3c3s/GYtaP+FoBQe49/8kbAj5oNG5uFz28UCV49GjJHwyUtbMu9/HJ3pjkim6Pj3Al7ccvFZFXhvjIZ3gL1YQHtq4UBoLwfv4rJoUM52dvXB+90yFd7b2qMzvRfJFHue9Txf16tcLje0mE/5vhqKPr58wvzJ4b7811whP16ZMfly57PZecnf2ZB0ATCG6001wLg6QYdAP16ENkhpIqp5oqyv9ee+p7Te78B2334b+pP2tR+veVQ5RaPSyoiQzk1jY0hBZFMXqLvOZJ2EP1tV0yRGmMMbZGT7hDjGo1Kh5QL8N59FOjeiQnfvP9GEmEoLXAswErODrUxJoDPvwG/QKINb4qA9p0hkHQQNVlpPFkR3mkQmWFDgJbIsSusn4u+VmfCb/3IBIGKpXuO7sSzzVg3eo41/+Hs/CIcdghtIZMQR7E7pYh8bvF7hbhqesSBipR3JppaFmwM12ICGBmJvO85fpbMkvQb2d+D4v3kF/CcxRwTHg2BaPVNOA0T00SIQnz4Y4tMQ8Vs+Its9adX/wDFIIdyaYT1gdLH1KYqRSyCe7kCE7xLZuGkE0tQRSFdHgBBfTYhfT4i/7vtxEZ+/4D9F/B+/1888Ho34aRwRn34ZxJPeiSsNvuQcXrIW4Uc1dEmUf3yghrQmf0qghiJ6+02Q98i/cGaVto8DHldK0eZi779CU1KXYuDNT2M3INSO8Am06aJxL1DTBr97/cMaVuIDTk/hYXGUn+/AHXF4KPuX8nD8uyiH0drIpiDC1cFGw1R1ASFB/O8Mf6D0fb5vfD+8nSB7pIqzCqiydF59v3gECDVb+QpkKfAEQiNMq/5M7sMrTg3foAmnB/fCH1a9BhfV66vISEPkAAXZASeMzONkczPgWn7v5xEPLrQiUplqLENeKw4nlXGpZQShVcWUKTeycUpjMwzYEhXPqH/RCWsSjxEraJKuOx7S1bP5eulBvZRnkJxGpfkpGLV4voGZWD15QTGPnj1lhMx1ohqqD+t2inro5hi3QXrQIC0zYgU95/vBMl+PN05QGYABahQYAPbDrhV1jGQew/EQQKKrl5wGKc+odOttqAoAmW+ENRYGR3/KoAKlVCHAWkOmNHenAtFIKU+PHgvLACgjVuM9PxA7q/9n2Bl3fnDsrFGxs/oy2Pl7Z3zsrP7PsfN856DYWROFndVXwM7sGIhsBmUvgGaJcJDnb9rQ3qxmUYkRd7dd/GlvVPHThg2aa4Zu0OTBz/vwM3/YBk0H/JQD+Wu0CTp9YpL6X1+8V+Qf93CMUUp6K65XANl8+hekNA4NfNXr08ccn4sn709Nvhp7n82gmPwk24GsTTjdfQsvs434HVVRb4u2BMYo6mfJyMbLHDh+jYCStozjLsdvcHdN2Vxz8I9KUAwc8KAsLgUWxWbogdCYKaO5zKylEPguGOKM4/igFMWB+UMJbhI2Ndga0YaKFlg6bBIxCLsf6jPgjWLViJ5b5hjYejTd3eIxypt6cJyO8PEPhcmO4NILEyAZGV2YMsrlcBbJtmZsbR3HCLUKEqbpmb3Jm4jsRph11XaelKtxv4i//2CfY5wKkvjy3oMU6VbH5unZegOyTKimiN2AtbjCJxTLIkELaghmQP53ASOyRG9FeRMczNbkcGDcmEbu+gHp/AIe3OdE5v4uelTzkjMgC2taSSSMCNRsQRbuT3zXQfNbz6CjHmNG82A4nvFwOMoeraCavzn6zbgr7pZlcXbkBP0ZsqLob2LcG2+AUGypDmuXNcxf+ADvc+8E8k7FuZiJFwEMWGVOBMJrdHpTUKTTTcG+E8w+kfmbmK1Z8uPCJ3jIn8gaJUh0Twi2wPNfJPeErPJMU/B57H6JkRXp2RTfKMT8B6wThhXlHmV3shC8khjBwSuWbMZwcira9+2dTo9kS1XfJkq2TGabkGVr89+YZT/rv64MpD6Nu8dJkXJgkViGmxbjmPssfQPSanPFZpiAVdkyHR5Rq0dcaMzsmeL4LghfYFAIoy0lwzZRa7MEytM0vuWgBjmLRRGYg3wXrpfcEwEa4Bla73g0pLSpZs1foKS3pyNfcvEHFlJ0ojb+1t/RbIsdpkNIsERkNgtZZvEUwbkiNPTzT0nDbFN1/TyoqSOnmP/iIbKGiI3RCaCkRXoOlUx0kEo3S2zIIwJAw3YpwBYr/YPhRnwbqX8TEA4b3nMrmeMNdrS9hvjfZ8T/9EhuwZalN2Q7l5en/Lhlts65FFUHnr5fCc5MJhnNg6oa5YWJGajz8bWnhEqG70/XVRGOYK7UK/6MoK/Agvy5LtTF+NSH1N34pqZdD3e9oRmwPr/53sufj1NWVBuhrNj5ZDfgxqYV5lTPSDTrNOA+5gllh1N9eS36BTVWiTRHidRGqUb5jIHEMawpOyrVHCD9N0xQ34TujmG5ehtk8/Dpj4q3Rnr7NrzJ1cgB+Xg3PhJzGkOPRnwcTo8WfNTQYw4+fjkXH6fj46dzVRMObpHGyIVr4riUBA/5hmKC3qsNt0g19D16kxU16n9cwNrxGNpBW4+Z33U/yBY6swavJv4NekWBC68juIVe1yRolDhZcvUC8cnIf12qQgmvwxu0xLQujHhT6QUkDlMSP6TEyVGVTIp6tojMQ5TMf6TMRpGYpCS+TIl6kZjYQDyaPlTSB8QwfNA3rMQn+vBj+tBIF8P26Pim74eVMaIoYc/Ra5V41fL7/g2vhT4MB8af+Sx6yd37QDgcz6UEjQG/9BABHAcVobS/QiDo1XlvTAj5eBR70SnbjNYu0Il+0InR0kAr8HMlCMMxfnMHTr9l32LlBtlulMZJS/SDGwTTNdmrhNnyG4AF9P1atZpCsh1gncVKlWi4bCTDZRNbbJT8zXQHbq3fipZ3O5dulAr1UEA1PxoHPwKaDguLQ4F2jW/ZTN+kmabgr2lnEPhLOrDeNOBrKfDXUuzVOpADIZ9y0a4m9GrOReBtXmJn6ZAxDTKmwl/IjEwthYwDThdeLA+Zb4LMrEDPUhDCOolgzNe3e3D2DWgupq2T2JYOLRAOKI4HAnFbXimPl4pzx9wo+ymM19Lo8XIMat83F8Ho39pOnBGt093N3yBz/3BgrPTQ8Yiw9g8w9eOFu0XAQcp7+EtfhcN03Uql/QDAJcrpmK0RhMdQ+4Hulm80D3fT3b5YwN3IT9NKWLWxx1EMdj8hFAOj5j/rT7kFjcUPcerPzajXe0fxPxwTlhtyqN+EL26zy2vhz8Njh9N6BrtXskUq2SqVbJNK1O4BtB7caO7hey4K31Y3LBTMAfsBvWRvw97jZzcaS/nQK/Wn/XHRH/N/2h8z9ufZT6g/FujPszB1VrYCfquq8ZBox6zBwHe/5lLA7wmFw1AMffLtBxLwQ5X9FH6zNXPHJ1cAPPPxvoFo+s/py21g5wNf6Rc9BLpTEd//sdimktafQthtg1GWQihAWbkhQj0ATjdUS/Ym+MBf+vgKUP/ssSi98j/CtxHxfT3B6ZtxZdJ4pVuFzyzgO4kbvV/9dxR8HUNRSVl5VquJC+qxn/ZXgduPdPffb0IWjfcPqhbTEvsV7bVPZUddWbclOlpI/yWcETiyFJxNJz3T2Wlp38ZeUKaDk3CjrwvYePZBXyroAQwlTjG/fQFpBayR3tIWYE/TpO256H2yXU+/0+h3G9ayPZ2e8fhEJF7EtYA6ExbqEwDtU1MQO2jVk+ROLCjn4N0i70ROWMjla6XgOQJsMnz54ncNQbwrluyJwRR4enQlEv1aF3mKJi+nBZSMH3gFdI1tp/4lMUemSHXi5ZGsEDpuwIaCD2BgT1A89ahmrsM3FnwUz+1QkAJ5LnZj3Slq/yRee0IBC5SPFngnB9PoxIkiUReTeKGXEvUxiSGRmCgSrbWoK0hBjMsiBdEal0VD4TOwILbfkZwVaIZeP5XISwoBSoaXfTOtLNcScJnY48Xz4MO6RrzUs6vYJT6hWsKXfI+GqyHYAyl0xnx7Kw0Tp98OGiaMchCsNVWtSoaKtyO22T6EpiNJ7H9ABUooBDr+aZKfA5KWg0po1DSnvA4vhkFnlGCBMkR81278qGLKILYeZXmXApgio+m7SiemyhuG96t3s6iXD9tDtc0VtQ1Va9scU5tXGTYRzcF6aGEgdAdF0pKCaWJbdqqaATtT4JDXvYb1q4nLJxIJKY0MUxt5LaaRsgunfh9pR+yU+sfL6xBmEPppDhUJdEee7t1wuH2JEbQ6w+mrKkVX570PqGvPw1ITrq4UBWzdgKWGY6ncqytFV/F9F0v9GdBeVjaw1BSvNmo01HJDsdzMfehoFFOrRDTDTVhjAGt8PH6NAyEZhjV27x2sxn27oMY7h2v6DTAM7zD/xL4C74nb96KgVMqXY/nzw+KUHzp4+WF95adg+bchoezh0Bv9ezSVsUo0VsbpFl1YmDZotz7eCdU+hNXOHVjtFO9IWcYyTtmd5oqp8eiewWpcizUasMbZ8QANVJEv88Bq8XZevmTQaqdgtW8DQsumxwN0VBwawXuf+M2D1tixA2qcjzXmDKjRVNmVBB8y43z4G35IHwjDbYJhmoIHIUO/gdCrc3EJttkBgJWlXKaGyvg10Ly8G2t4E2t4ZABlm4InNDElZXlvLwqdI/zvu4h3KeJhuMpW9vbjhBOjOKE/nWwtSlpszBcWEqKiY/h7CyI0itNqm+BlEyO8rOzA5N9rWCOud8PJaVBJ96mxtYFaoyxvI8lREI6BILrXfOZ26Os+IIwy88CBCF6n7cent0Tzf9R3ON8Z3etr1F5viem1tdZ6SAqSxiCjxtAQNCvIjql9jSIFFuyIlgIj1DrXxDLo5q4BbGesI4ZGOduF/cd2O24vOzUw/3WOWGzMo/yk08hmopOH8TEmz7XbAGMMKdT41wEV5sSbdiMQT5pdg02Sg+9AhfdihZq/DiQ3Hc3lgTMPLUX8DzuxUsLuPqFWxMNxxxDlxHsM2a5VyLZ7WzSyTSqy114NsmMQc+POKyI7Gjf8sx1XRvbv/wi4uRHYYVkozlS8bxDcmBA3z+0ghBNlCuyEkxtve1Uj8IJCcU0MPl5R8PHJO9H4MKv4eCUWH1sH9u8ued3ccNTUxHJ0gDyWJru3q+pfR+nVoLVh+3+G1g3b+6M1eQBai94GtDYADsq2xSG5taR6IyJH4ekPUqr8wxqCrYpqGTNnX1DmbJtAm6IHj1TR9kI/7nehN0oPDPZSbRcoQD4T5jYqFgPs61sB2OsR2Nq7Xx8A7JoIsKNjgOUqsH3IkYNbsSWo0iqAVfTzUSqwW/sBG4oC1u8W706ZTR4E0K/fAkCfSBggWCK6citmcCQgwHolLbaGPZjhDsgQ2Id6vMZUiQEOGOUu8OUU+H3ombIPl2QZNjP6AaJdL3vPXjKo/ekLXDXswrOf+t06WlOxTon0/I68/gVfiCq4Ggs+Lwq+e5z3K5okysnBqt6Iqi8068gL3Ysg00LMacCjGI/AYiuwD0WtxjeGBVf34mIHVzBPPSlWMh1eBGI0AdFMQAxBIAK05pGxPTapiq2jKu8dtM2M7bhwEi3rtuPCknkWOBgtJIsx1i31ILAPKVfD9mEH2DrM5pvKZARDd1jW3xPs8hvReIGuucEW3w0ii8vBAugN4SxWXX8oWUwDHLrAPqQxjS9n8Kqu7auqILoqQZ5Yia47aqkpEB5O3nzHq5ow0a1Yn4lVHWbvSCbttb/qy+id2VMCtV8EQkmmVXiiz7RjjdmKLhXrDPAnQlGr+yiKrUNE++4v8P+U1SFdtJiqVpyHIXle0IUPt/DfEXSxvg+IfvQxPVI=
*/