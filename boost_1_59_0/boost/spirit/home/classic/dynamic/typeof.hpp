/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DYNAMIC_TYPEOF_HPP)
#define BOOST_SPIRIT_DYNAMIC_TYPEOF_HPP

#include <boost/typeof/typeof.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/typeof.hpp>

#include <boost/spirit/home/classic/dynamic/stored_rule_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    // if.hpp
    template <class ParsableT, typename CondT> struct if_parser;
    template <class ParsableTrueT, class ParsableFalseT, typename CondT>
    struct if_else_parser;

    // for.hpp
    namespace impl {
    template<typename InitF, typename CondT, typename StepF, class ParsableT>
    struct for_parser;
    }

    // while.hpp
    template<typename ParsableT, typename CondT, bool is_do_parser>
    struct while_parser;

    // lazy.hpp
    template<typename ActorT> struct lazy_parser;

    // rule_alias.hpp
    template <typename ParserT> class rule_alias; 

    // switch.hpp
    template <typename CaseT, typename CondT>       struct switch_parser;
    template <int N, class ParserT, bool IsDefault> struct case_parser;

    // select.hpp
    template <typename TupleT, typename BehaviourT, typename T> 
    struct select_parser;

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS


#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

// if.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::if_parser,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::if_else_parser,3)

// for.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::impl::for_parser,4)

// while.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::while_parser,(class)(class)(bool))

// lazy.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::lazy_parser,1)

// stored_rule.hpp (has forward header)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::stored_rule,(typename)(typename)(typename)(bool))
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::stored_rule,3)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::stored_rule,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::stored_rule,1)
BOOST_TYPEOF_REGISTER_TYPE(BOOST_SPIRIT_CLASSIC_NS::stored_rule<>)

// rule_alias.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::rule_alias,1)

// switch.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::switch_parser,2)
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::case_parser,(int)(class)(bool))

// select.hpp
BOOST_TYPEOF_REGISTER_TEMPLATE(BOOST_SPIRIT_CLASSIC_NS::select_parser,3)

#endif


/* typeof.hpp
4eI6QZTie98oIR7zxwnvEsOfxIsTLZ5PUFq/bS9aInHiRH/HKGRbRQi9PEJ4fyaIvB2wZPlsoyeixbm1eJpRFykP3XsXLe18Gn9FY4+2dffjU9grVANawxdxq8QIiBetJIwovIoQTyMLUL7XKJGjo7ii2Ff01HBxNkqmtyA9aWJ84ASRc2U0RqL8ML1wA9N634B7y/TmoaOtpX3mt0jtI7sjFrGjPC2ksqiX5W/qu27udsYhpuxfRal6UNolO6ZLeWHsM048KP0des0uW460XxyYHLmR57ErxWjXfB67MfbtTQkaLO+gwQvxGtTurIF2SL6P2e+oMOS8A+Lc11+4r+e6r4/iNcWdqK/Qn6Ks6KpBdrgLotzvzzhIix2HzynPxFGNxTZx8VVXInysL1joxDNmqLDAAif8fw3HcWCBkxzIwfa8bIFT/bphe9t4IPKgep6ZhXzdIoAo/uyi2fb8/ugh+f2D3GVlj9MGywMbp/GL//76zp656hWtt/yZOJvG9w9oLjWQVHWJCptwrKzOUaHc+6p4Pr0PczwVSgTvjjjmvC0Py/c5prqMfVfa+8xa+X//ffZepF639znjP1RYtUCFO7Lx2Xjuj6nDhyo8hM+MRlgaprEL1St+n92QFvPno078lirWOJtH8XrlC/heuH0rq/AZugVO8TiaIb7LAqdyqS5c3I8PZsh1LfNB+Z/CunFxqG+bqbJx1TrPU6GRB+KFRyG8ogfihe9ZZs+vKP4mxeH0X2OS61OkZ0lfCm7Nh8PvhLZCoLi0x3YA/qaZjkDz0M724TbrPBy+eb3INxfx37Ztpb1KWmHSZW/cPNL35+N4I/hFC7zaTAmPtcB7uuFxFniLhRI+xwKfNpO3J+p9ZP++PDa4ye/tDLaB5JphgyebYgXPRf71EvKllI/Llkf91gXGvyLX/f35V1n29yerfO3vDdg/V8u/UrA/DmIfP5KrwvnDUh964ROpH9mtz16tXUw+YiVP8vyr1ee8XXw31s8d+slzkJ405WPeXp69Stq/j1zywmm8Pv2VhDe1wNut4sfxhDX24/gJ8SfHs/H1rTaDUhLdQ9ofnp6aPsgAMPdNt5SSdi44qPDrTDva+e61crX30spavJdv2jNt9sdseSQUCus5oPx6SUcTPwi2paOdDRwB0RFnf+zFvERH1Y4GQY/LQf/rdDTwWBDs3x7soaOdWKecA0EQijCrHpCxLDhg+4OSlY4+dAbD245gOFYcJOIsFwUFw+SVwbD1UhBEHQmCWZiyMd2KfVP5QhC8VBIEwXgv4kQQDK0cDJUPBcHXRUHw1uEg6P5TkGcf7HMPOeDnxg74/WsVtmI6gunFnGDxTKpH2pfB8OnyYPge06N5weDaHAwJp7AuxcFQpb70v6dE+D9gvt6KA1KPSjrft0Gun612X5fbKOlejpraLc2RM63eFnQYcZiMe4H7aPQS0o6k8xB3tBda2Ul3x4MpK691ns8XU8ZzCaSccIV23yYLDpakSH8RWbZ5XtA+v9lL0OCJgeTjo49SzNHhouZXl59Wsqk+iqL9FApxSOuTXVqZcjMHcQKh987rA5ObFXerZdJ7WD7qLpg+xmffe1aF5Ns06I/X72KqjWOy8utOca7rTq0wVUPYCwdVQe+tD6m2cnNQnuonN3X92s83hPyuQtxeFdqdUaFlsQpnjmBdT6piv/ronQjXNCjCM/V50R8qZGD/VT6sQuutKvxjiyposhKWUYLJcUCF9ZgOY4oSNCf9g0jeGnFrhe4f742TaD5IfjYv4PX87gW8XVC03l7/L8fI2+yfVbjTgk/l9CtU2e/Z1N/F2wWP4/vh4vWNwb4LsTyXVie/OaWCytSnHo6zWr5g8Z2XjXv4eY/WFTUoz8A//FFl7Z2z2C4ubuG5H3m94+2fVHb+59Q+fr6obpHKzgsV7lfZ+Z81ebwe9POvKA8s+BSHcNYu3v768ghvf23G8ZCkeUAeeE18LhcP8NZ8Xm+acVbaC59f8rUX7j0h4ast8HpHJfw/LfDBbnj9i4pCj1Hd8ORtEn7qonwm6Tst8XxXJU3Ggyvvxaf4cZORRgnudMMMeGSehDss8O5uuGaBh+J7rMq098kN9nqilYOb5WMdt29iHeGFJP1MpD+Sea2FZvppLptm5mnu3bz2EinykS5JW3uND4xFdnbBwGDTmmaKV0fsgnLhPPLabVXKlgv31gxMLuRlaX5y4RTCrqU9NSdV+1N6oJ09FV+Flwt/Zj6IvqOzNlmDbpha9NTgUIoGX6VrcC5TgwEZGsSGanDgZQ264vUIbNdITL9jPex9VElPGSp+k3eCsX5ZGr6vdwPF2CLNxqxb8fmkt0emGLekYZAUSiwjT7xC0cKTlSFC/5CzFWU9Jxaf5LUKcYy+qgF0dbF8u281jZVHUxDOyRd6Lxy/7VJdY+XUaoRz8mU6vhOOv91aQyt1fiOmz+DnkxLlZvgCbFO24qXFVNO3/ugoQXoMQzrrVatseuz0WGD0eCOvC12P/Q0P1vTSlr+PN9khfQR90NcFZKQcs+3A57HSl8xXeh7pAUdUQFH0BygUGdSIsV9aPgNaVp3MUf5bua0F+lrCQEXqjgN7uFj9Z/ejGkt3p5trLB2NxrHK6Z8F2M+VPlN8lFOSmzriKwwdHaqLdGcDL8/AF9ynsfPD+x/Q4CYPxAtXa2twswfiha+pzdP1prtLp+v2KWnPG/M7S3q6INlGxtIRdywUuiO93hpeNl3XigyMrm9kOfuPVtdXzt73L1852wf7/pnH/eVszBMGLzD2dJBfidxrQ1Y00Yr1fpSg8lRBtRmCekvH7yRmAaQEpfmJDFscKfccvV2SbkwHxfRsHM6P02Wt7Mfp0mMyvsWkyLLHXYWYwMbd5vb+4+5GkScfRPLj7s/Gt9jYRoPs1hq48CzW6o7L+bN328h+9+7rMe8GkrHYSD8i+UFRsimqsOGfZuwq8s7/2OePFxKAZIfXD/hK8hvzCleSV0ZTHy78j6UHuZFLypeCvvy8/nEcP5y9PC6KH98r2tmPb++ew/DERKloCXjccelfU65z2eOefDsCGfc3sh51PfxrVmO/Wf1raM8Q7cmoo5h1Jm6vmzFn653LUpJc18SPpinW50r9Zd6ywKl8ikGZzcDvitXYea+ZsbxdshXh3DzNY3Ea6DZwjg4Ku9jTwf3KE8qjyuNKliJ1E7G+5J4AiHzWBUttdJNEpJMmaJNu6Vs2nXRIDoxObmS9ZNTI66uXGPb/5mc0GIO/78Fz40R/vaR6Hw2CemmwFt/P/jzsy0SrHPHfH2pECB2KfJr2LZi/jWbMFwxQzLtgS99v6ruW61+C1WchFn8nCwl0JeV6c1nLI12oqjFWGXtkSm+e3jKfsZ8H4L7DUtTPhr/05umwRf/S7QJj3m0t1j3OTXfDcPxXNdn6cCIUEnA8vJNVNt1RP/w/3f05urPaAzTvNmI0Yw+Ices7WqPFmO8vxmqaaXaLjrLxyToYGACu3DNXOo535wKHJ79uQVH2vTqg3XPtbBg7fN7GCXRO0n9OMVORu7FI7pekytiu5sNYd+Lk7PEhPL0+NZTnB1OH8fMWTV7U2PWiXcM11q9Nw3HCraf9mMnPI17M5OcR40doUNnCz6h8VxavF7+E45Jbt3kXy+fWbco9p8EZBl4b4WcZeOEoDX5l4FFIH78w8JhUni+OHK/5fT/qjUbVIGR8Kfwytq/YTn0P8sMOE1Fve12DWzBFxERGJ/TpGzcoPSOTPolK1xHJKamJeEFf3aua7oJcTfLWrss1CNvq5a0OvEc2Nt2b9j72hcnvZSA+Z9AbGhxfqkHFk97fPfB3j481WITnZ6Zr8Pn7ZfPlHv8VGF++ke2G6zH/WnJS2sYzsN8N35LIU6GwY4oGE5bLfn/jVJBtv7dbfXX93vobB3ScKuXh38kfydzvhj/S+Dd95eGT6x0wr5sz4H6380e6a7vDxx+pVbYGaXM1P3+kHfM1eCXP4fFHivhEs/VHuudbB8xA3E/w3Q2dpol6PIXv6DLS023zNLj9Te9YuH+2/E04lMbnaJDzLuK8p8EFzHsf0t5w/J3xjgbz8dwK6bAv0hnFBpFfqaeAGv3S01L6ycjng2l/FK2MhitxioztgLgdk4ZIpITkoQP6pvVJSbXA26cMS4oblDQsJWm4O4I62m95j637/t/H2k1p+Oms/TMfqV4D+2rmYHv/Cn0G2rwWhk3y6pY5vJxogX3hsuDTHu28BTzf34/9eY8FTt8H3LKQt2+PYJ+Ns8Cp3OaLeTt202LeHi5ezNvVNZfwcnQMwt+24BM8+V1eTr+zhJfTm5bw+1YmYbvs9APOz6H6WxrcanlhBB83jV8v+BH5zmgGXhd5RT9Gzq2Z5i/netSpBv89zV7OkZ6zb6gL7mbKO7hSg3sZeOoqtAF9wcK/PQtp5C4LnNo1Yzrf7rrIZ60Vo/Gycrp9fSWtyJg7ng83KF5fhI5KJ7cPgowkSxoi7Zuko5ZSDxPJ9tSkyPR+0XEiRo8U3JuHueAVt9we8IUG6474rpMcRDmw4lMN5n0h5UADPNvJgYyvr04OkPw9t4aXAw2/0uAmTH+1HKj0mcbKgTVf+NtF10IOZOHzzHIg+3ON9UvtjfBA/VIz12qiLgeHOOGPYU7omuKEdelOWDjUCfHPOaE8tuUk9m0R9j29TwfW8USurLshD2jOjcqg+5TqYRlVM11QyzKuyX9tWC5PHx2/4sd7ozU8n01Zx9N587XSf4i+S1LuKPKco3K/aoN1br8iRcIoUVyi2p978RWEKQy+AbfiawjTGHwDbuBb+c7MGtVEf1nh2Qgv+cwfvgjh1deUpo+nJvkQLB6jR7jgNTfNTsJnbfvJS7MFp0NhJNLhmo2SXuM22tNrz2+vnl5H5v+96PXQep5e9268PvQal+dLr2EbeHo9kX/19HpTui+93o73tmxG2syX9HgQ3/Pa9aXTaxHmzc/i6fXJ9Ty91t/M0+tneTy9dviGp9fdG3h6dX3D0+vyfJ5ezfhmejXjm+nVjG+mV8K/Enp9OY+n13fySqFXtIvN1NpwpAuW1pO0WuUY9qvJLo5I7pPWP0nK9JikwYP79KePNQ1JovnaTmJfe7xfJK+wM6HQD+m2zTFJ37DNnr6Tj109fXcv4Om7R6EGDxf+9fSd9h1P37u3+9J37rprY5eVK5D0DWijEn3XOyjpe0m+Q9B3Lp6Jvr8ulPTdbCvaV/heyv3ggKe+1wR978G6mOk7a5MDdmI7+u9C/RLx0/D9vHZcg6T9Grx/GK8x//KLGqzA35t24r0CL11T3chv3aDvA/iMj3d56fwHLK94q8SP36tBo9/Q1kN7KX+0HG8c/Tf/jtfvY7fzfGFUIc8Xeu/k+ULdA7wf0tDdvD3WZA9vX1XH9nD7zjbv5e2uDtt4u2vaNt7uyiri7a5FRbzd9U0Rb3f9UsTbVzX28/ZVS4TX9EDkQeshdfHdcusi2gGez362lbejUrG9dzD4NfD9PmipD8HnbfXyzdZFMpF/2L4Cno+v283z8RI33MrHzfhmPm7GN/NxM76Zjxv4dDQskonqmfNj4Pyd7MO12/zhAx+sJmiIkweLC3h5sAHhVZn+fGB7KXLCJCS6vOyCmm59rqRYgwxTPMTNyO/TT2hQ97zk93WL7fn9rHL6VfP7f57i+X1+iQZvl/z1/D7/JM/vo89fH32u8Slffe7uC7w+N/t3ye9TzmlCn1uk6PD6acnvn8ezmd+PRh68/SzKhTOSHxNv/x7fZdGvGiw76a+zfXnOy8/TUU8cPY7X25qd5Pnz8RKeP8eW8Px50WV+/st5gefPj/zB8+dhF3k+/Gwxz4ffK+blQvlLPH9ufYnnz7mXeP586BLPn2++zPPnxpd5/tzlMi8fd17k+Xar0zzffvEyz7dPn+P59svFPN8+Wszz4e9+4/nw5bM8Hzbjm/mwGd/Mh834Zj5M+FfCb3cUXxm/vXSK57e1TtvzW06uOYpL4cMxUZ7QtOfLyXW/e86GwvL7dCjBdF8FHfQFOsSKnZz9hV8deaNHKzKeOnlVGffkF91pl6r5LrbxrFxf+f12Xayv5Lqva9+hi5hGjnPyOhqvK4/Qwdiza6zxtnL7rptXbalk8umS67m+mPQt+ERFRoUuHYdibtGVXO+WkUdlne3yxYn/Mi6f9G6U+AnYhtWqDh16ARTM0Etdp2uy8OrllHWd7uQ8vcz1oglvOMV+1sqvOWHVHCfUnO+E6LlOeAKvV2Dag79pP2vUPKdnP+sm/E37Wb/HvCSnovE3J6e2g86u01WfrQs59fQs5zVbp1v2qg51O4XAhxdDYCCW9etYp4Bf+LcTCrNvFng6wgnW6WQIdJnohGLs68HTnBDxqoRTemiBE5pjehJh9KzXMA99F/re7IowHH//PNMJXfFeP1OeAfh7AqY5mFKr6p74N7uOhMDZcyEwb478BvRHz+iwpZ8O28tVAOWnEAFr6MYf86YTWkxxwtaXdNg6SofgqU7YgikR63n7iRDofD/SG/Y31Wkm9vd3z8r65bXF+jl0iLpTh/oTnPAp1qEJPvtLPJ/G9t3+WwgUYvoWr7djOZSnjlIBKuDvQoSdwNToaAhMxLourqTD0V9C4M6SEChG+CNqBRh/HOHHQuTcSxUdNt5SAYbcXAFiL4TAH5dCRDtzT8i20Dvy2FxYJtlkOXhu11a2cXFeCJw/GwJOLPO9MyHwONajC+bdj+cFQ7Dv+utwcyj2a5AOjmAdOidjnV/UYSXS/ekOOsQhbDGmKpMwYZvfxme3f032gxP749tMHVIQ9gryio2YJsXKe1R3Hfs1yYX98ajUP8JCsH3pOkxtifjhOjSYLuvYoqYOPbEO8x/HspF+MibrkO7EcirqkInPuqWeDtXwt+sBHWZh6ovvtFFDHfYOkbRG48EzRivjM6dK+EX83egxHcbis9PaI7yFDrV761AjTdax5y1YDxwLH2D6COtVS0QGUpQF2GcDJ0udl7PzFjbWWbndsrPO+qN0rKuzcjgD+Tmnd0x4U2f1o1U366xesB/7nNMvnu+ms/rCnp46u0/5YhOd9XcZ2VRn9a/QOTrrvzK5l87qQWNwLHB62UyEc/up+0bobDy9sDa67XqfwwORB5WTiPjVLfB6mFxIW1U9EHnQe/of9q4Dvopi62+Cd+/eEM0BL01AAZUOIs2CYkgiSAmEDlIDCRBJMwQMqO8hoogfKvrUZ0FAihCaNCVKlCAtIJ0goAIJ0o1PpAlKef8zs5u792ZuKB/+BJ+b3z975+zs7uzUc2bOnJOHuqLi77hOq/R0H4p0FPAjJcIkWP6b94SHTmESTG8c4qGXDJNg+vM2ujtMgukdB3vopcIkmN6ePPRbwySY3jTeQ78lTILp0230kDAJpr/8hodeOkyC6ceR/1MV/MsbaEMDFPxg7wTkp2I/+HLkc0UFfR3oZRR0CGnUWkE/Br7Hl//KAv81983CdNYr+mSIQ7nv+74JDr/8l4rHYI6C7YOyBVhrNZNteEaJNU62XtoWvwrHCRezptLGqGX9s3ActhLKFl+lbVDf62xvle2Q+rte+B3S50KUIi6/SVon9b6ieq4nrv/vY/8O7bSuIm4LxGgj6P7je54prdRa
*/