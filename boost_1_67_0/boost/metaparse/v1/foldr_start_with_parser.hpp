#ifndef BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP
#define BOOST_METAPARSE_V1_FOLDR_START_WITH_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class StateP, class BackwardOp>
      struct foldr_start_with_parser
      {
      private:
        template <class Res, class Rem>
        struct apply_unchecked1 :
          accept<
            typename BackwardOp::template apply<
              typename get_result<Rem>::type,
              typename get_result<Res>::type
            >::type,
            typename get_remaining<Rem>::type,
            typename get_position<Rem>::type
          >
        {};

        template <class Res>
        struct apply_unchecked;
      public:
        typedef foldr_start_with_parser type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename StateP::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      private:
        template <class Res>
        struct apply_unchecked
        {
        private:
          typedef
            typename foldr_start_with_parser::template apply<
              typename get_remaining<Res>::type,
              typename get_position<Res>::type
            >
            parsed_remaining;
        public:
          typedef
            typename boost::mpl::eval_if<
              typename is_error<parsed_remaining>::type,
              parsed_remaining,
              apply_unchecked1<Res, parsed_remaining>
            >::type
            type;
        };
      };
    }
  }
}

#endif


/* foldr_start_with_parser.hpp
mbw6xfw5RQrtloGKInE6V/8U/BhKMhH+Ef8fwd+WBP4l2v8D+Leb4C+7jA7Uyg6gR3ZdalHGa9f/67sQGdJeb3hcfMSkXYAFAw2bzsNxUWp7I+dw6gheRGHQ2RtY6VmYkXSU6gyOZnu0RSkw+R+zF9TsD300vbDHX+otLgO4jggHr5HkZjMU/ydDSBvgQO2NHinVCs97A/s+ftpScQXG9zK011DZsfJaVnQeDjn36e+jGcDiKqP124se/Vgvpsi6lL4H0yMZ1KG9K/T4PQntod0mNlmBt1t1C2S9ky+r3hiJhB+GscxAJdjgtFJkGuxrRqMpHRqmocoqsAL2qnfZrTafMXgrEvStSstwsV6Yfa6dvb89JZjJltp9iPvAG8AwjcSnu+CJfwdbL7UDLfi9gOdWYHvuGBjPSfiTQwOjSDpBNbMsL5q/xr4mW/hLgOKao1nAttCzBmFbaoLtjk9zOYfxfXvsZUTQklEDhhldIc4Q7Yz+lBakuSkQFUWEvIPCLS21FSv7Q2VsgUutPu/pf9iKFFd+3nrSerJY2PgUV1i86gIbd9yDEaJceSeVKHQJzvOl0NoPlP2o2It2Q/M9b1Z1w8jdjjGZFjhE9Sscnk+cj2+i7ts9kWo/OzG93XrEesSv2R5B446X7gaG7PD0pfZwmwOq3u/cgEsnxZ8gjFuPao6NsUYo63zPH6rewmaoDeeGVCgxPQKl4UjZh4c3dwtdSZach+5Zi85Lm4QF9jAwyPOnRzydVX8xilNkzVAufH0q/OcM629f7beG+23VGc2IrG7HHIw+vCatGf9Y93j6q9PUwv7uNLW6n0VgQ5cDoU0gJ+cSYxiArNRm3W/d7/MXewGhfG35O1FogQFEh6fvoy+a7TvU/7uM/udg/9dchf2GI9Vg/Yaa/WJIcZYU9SPrsMCmLnUYPYpbPzeZ7OOKB1WIpuXTWfdqzX76Cc4BlEgJ3fWPotSVFF1wH/CylGg7nKf7YZmMOjftWfKZ8l7zHFcndY+jFTRT2Djr6b9BwbShQ2KPWxYiibFSiez/RfCH1hnwz4ZN4P82/Kte/7T1/yO12uADKSSfGtLDRGKsO1ihymKG4sLlAcrWVQAylIkuDeX9lQL9rO7FM6oEU/1i7HbrXvwaGVLHXMCbeqTOzC8m04dGnVNyQz99T9CxKLgozK1O5SncnT5x1pAu5K/wdIwHuDCm/gqP2NUPleW18mlfInnavdJMn3xzztQ2oaZ09zRUedHt/3tj9v8pqMLAV1goiFn3dTB2svrK0bLq4Vj1a/l95M2WFaGENcWHN1NH+V9VOJ53DrAs3ZNEZ1n0/+2HTfoOK21D+PN0qAo56BXqZHaf2oD+bPmx+2ZgxM3iYr9KHmx52+rJaLZTCDPchVe26Ib1Yz7p8RnS6GI7xTtaNwMZkLQzh8gdsKfPqbSl4h24U0HPu6hBgbGrSivmwWLWhoSCSd/GpGhWO0YN7Efs3ylui7HGC8oMNBBEB897Qt+KFHInBdTt2lvYYXnRBkeKcM8ElAigc/VALsxszn7+NxFCrKgDYzDKekqenmF5rLPmZHB8uJq7WGHH/VatsIOVdM2DzZC/uHKWdN6UAsX4tBd5tDuATyuWnI2+mJ7QTM4zT1v4We9ZEfGgsMMba2Zmg2xmEjRjN5op6tKWDUvFlhbHtzQJ6pdF50NPUdHh6ygGasAxUU5KLxPzc9icfoyxit59Q5MD7Rk4fTqQ24tloY/OmvGkJ3QWPQS3bCNP5MppcnNURy81h1DI1XiwATIdXNwIDDEQMf5lnZBANQYdEXKMTIL2DBiYbEj2aYV2HQHevL68k6agl8JVuEYhAv0UXTPywAyLrplFg8cK0GptvnaTRbs11RcbflgaZsqhh++fYVRHmd/LJ99BeCqtGJkAn/TmEouFcEVpRUq3dWBG7AgsIkZXolmWRY24FmWWigyyZ0K1iIZgI5DvgElGFXRPNmX7ZpJsA6+8UE7T9fUBKknNW0+Yw2XK+XpDbH0tHsRBBywrgT13w/OhaNbKUzGnDGiSDbzaQaT9X2Z+KNxRTNyFyn27caFlh9VqR/QoKvtEMlb1Pyk0cHdXxX2yGZ/StA22VJONW7q2wW5+zwDGa10upKjrJtCvJXUwpx+3SxFVEv6ylKM3rEtwTyzx0/H4p/kLIQRIHwyMAJTnn1pxDWjT+2E43ZD9jPnduA2vMjYgYqTjkw12/VmiOZp1/kTs3nOg3+YkJk8AfzGbGIABE2z6+9o6rAkOLDCWZdGj2jpsxBvYj69qoR1SCARf4IDIEP6KJTguvHsCRYVBpzGP7LWJBXPbG8jB355s/yt7/Ik4/0PJUEbHMrQKKjwdZxWkOwvVvW4Ybj9eSTWMZsLRUaGrK2ywRX1e2I5Z90CBLh8VcgnFLmt3ToU1PkdJl9+cwxbz+kHVdpnCz9/4RzJnm0b5sbwXbZToTSqOpZHKJpq94UgggIGf0PyIFJ4WE5784aJu/HagDbIq/BPaQHB/YKcpgZo2GRCZtdMtQxgICbQLfP+sPU4+lfSAHM265g2M9lfGDqm7HUR7Z/GsuxvPxLaQW3ATZRXZ8F8K+fXtHh2f9lvsXgFG0NuE198Td8BvmVdMR7YOnToF6OYvetQTMWjfGD44GbENOMKPvKqSlzv8QCjajalkG7T7gvRnAxTZJhebgxjGYF80q+eNRJSsQ8jJ6d9vU4XxAGly80pRSyqzsA3o2R/jWawlbdCjFI4gVoUSrRzFntxJkWHLAj/A2wiYAFjRKKxo1gWpe3g5FY0yKgrvxsXJHlpMNeL1Dv/TearRdlk1WuNBI9O5OlFR2mVVlBJfEQar50tERemXVVFmfEXIFPHU89Ldw+VU5IxVZFIFtwd+meB3Zxgr7GVzkATQiu5EXHXmkiMCOxJKOmArZBORiHyB3wmSOgrkNHgVmYHnE6pwMjz37L2UwqMCLyQUHs3QqCUyWOHIgmDH95+0nBljs4gYZBvJzqLXp1WO5r8UYa3cgNInzSj1J0fpOkLpGIFSL6HU9xsXjs09oqKsy6rIFV/RaKxooqho7GVVNDq+IppaqEstQpNeRkWjjIrEqoWK8k7lhNntanbg2YQBGJeMAIiUBgwG2+DGjXt/yM3Wnae1ZUywHDU1blP2BxeGd2O0Iox6IT+6ggWYwxPuHx28Adah4LWoOvIFVB2ZiuwkFBotC4WGhWmVcwVHiocxTuWnFksc7YwPNCaAPgEJb0h6nxT4eUKZq4jeLolYJwf+K6Hw1QztbMzEemYlLuu/EPn4Gz8nK6tclmQaBn4mM70sMk3BRXxQOALbZW4mck/D3HEN/9Xs6uDzOggGqNMBN2IYh8bQjMBPE0rOxLWECMJ7aSvCNXrXjCquJTxdEpLz9J4ahWfTcjLoiiA6BevCJlgXdMbLydbZyJhC8oSJhiGJBrsJ9kOjCzaa+IOB3IHezJ3Gbq2LhNb1pwhmzMdH3ZhrkZuzthuhKeNbHsdbZFc8/F8pk1DSlj2UCUsSM+diwVaUku7A+2LeB2rlpEfz+h8RuBjVSHS6jM3BoVTXnUXVl3XI2ISmVKQFfi/wewJZB/RiAUn7E5MwHqF8J5cWcxpPUXw9ObAngOeJ6GVoTyONs1q5qYkdDIjoKbFuqYQr/tjFaBTQLzuWrCNZ2EPoTHAkG8u+U4MnoUMroqdJrl4qGgdubfsp4UblO7FODgB4nQQqGlgXq1lwWeoGguY8WlsLdEUIOYiz0JRiM4YmriUnVNGj8Tg6enuEkIr/7tCF/sBbmmB5PxEWMXoGmsSghcaZsLdOYu8QH3XRAE1YFJuHMPdSAIyhOU6+39WPIs9DJhOoVVZdBNWm1uTeBW86i9zm1WpyKyFBZ5PlVHAqH+O4iFnHp9w9WfdT+jYl28VkFEc43dMyOhrTbsmdIGdQTe5aq8CePnlvzs0JrFpp8uPg0EV4LrYsdwJbmlOR6/X7dI8NGU5lpajSJZcTUWUKpLjjUlIhJTsuxSpmrgwfSV+J1yaq0DlwgpXOWMtys/2iVvLjXiWeyYv7zblub/JP5mcGQEIf3KgPV+oLZFrWwmD7KxD4m2EhOPk/tR1/bBPn1U5MciqGc8AFV01br0pGVajK5LLK9aaVsis/jzoxTrqNiO2PdRnqJCi+ka25ZsFJlY8vl1ZDgPoPmrZu/6yTVk0rlFYogQ2nmwdu8JgR7rA2Bpclm8okTNJOeO+97+y7EJuxSfxj+e6+7927974f773v/agg5oE7LSLdOMk7mHIACYPveARoabdcUCEwRSTa3YOWfmR9qQBoXryVGrl5FHPcsaiasxlFqxRRhJYp0DweQRlhWIwOW8MepvETSpuvbhTWlZ112Hh7/i5jNLkbLq31fKjwX+JBQ6OghX79whFM5sgU0LGnmWKivt3jNrSCeSV6tcTVIFe8XLvM481tXPW387iPNXAlEMXsoe2UtdZU60SK6BlrGe+wwFaOw2qdkzrmI4KjCR7rDK+VXmkQlhve5eUHqMaO7usUxhF2KIjGnMqiYyXkpEHQaWVDXNfLM4zkL1HelitBdmiGkvYG2AhVhVP9jDRDrA51CAU6voyN+MhYRIU99/XQilvK0PjDGZY8Qa+E9ViRsEyUP9wj9S0nnHd87StdJ5tdU43l+oljYgqxzb2DJXmoGZPh9UiysRRhRj3ce5z3oxLM1ACmkDuIpvt+FGxlg2H3mQgVETLeQF85fRFfJ3HPMaYEB0e10E7YUZuDxVLkZfTEBOg4N+BCNjCjJt8scf+7LB6cakwpQXHuH+CMfDE7+afmS5evI09B6HzAPP/TovAde1qSj27wo5l9iKiVm6pHwut+Q5RoN0SJdkMUDjZE4WDDKtEu9n7z2zFKou6wAfkMsaBZPFGl9UCzyPckefijcpE2i27iYG9HaFRcluWRbQXH+UAUQFU1WXT5Qlb2M73A9DzTc5gu9pI8kK4nNpuvcXIFDJpXjpOv3HK7KoC2kGlm+L03ka31TDdx4GhevlViSjo0ERplcZgRmchZeaSvHh26pxrE+XKoFEnJw9eRrWOygelQ+VYPf6Lf8PZHboisc/wEnZwAfzBLbeSE4O7Cyn/jCPFW5jHJ8BznMAWzgM8a4C5sel94UPD3Iew/4rb4O4hgYSh4jxkwGtQssjhLNHgH39WB/P3hX4C/ejZUjNyUB9CGF9Zy2udCE8k+qhoVOZ94iJ818z8por+/XTUq8i2qGhU5rS1gWg4B5yilkZbXvOY/f1ksMS2PpsqUkhf3C9pifslseRufFMQTsmdhKh1YMuK5KFcKMKfz7bhQpM2v0hLhTxYaYZXhSgbYxuPTgthkq6hPIaXH5GGMlxqckAcWQY/iyTrxFSllmvyCtSAG0yAVYXTCh/xqWESS/IMGuoT2fYzhNTdPVooEggBy1vwU2lFSXhPWMUAtAEh5O9qjsTbj19jD/D4VpiyLoRaU1r9XNRefEuO1eNKdkJg+PfkCdCme9ID29olHHnwera5xWBoHEUjUHDVL5bAJej2sp807PfD+AKyl3mhbrN1C4cYnThSs3j+erI6ClR2I9J+kXnAl+riStqIQfNpLOO4P7xe0GROHtlHDQJBt5uMCIaInsAAZ1gyoBIAsXsyMHotaCL0wByGrd1MNhJJ63pXYju99iNF8U51EeO8qvZOyZavTPG4CEcok2OlyEOFfs1i08XLFVh81fwToTsHkvDw31+6t+SlCo2FFSmwKK/7EqrASSKxIzvpA6Z5dCkr37BJQumc9oHTP1uODusTDsAA+mJxtmloCPwk/tpWx7T3YVhRNS+peWOvxWsI29cnxuqTucyU+g5Ca8dZyBAcA3NhsMTaTsZkHuOPC7e+O6iFiw/+zHuLkyG3y8TK1zLnSvZk/HqydC9eGd8qGV9UWT6HvF2ytT/GnGt5E6eHZ3nJ8veoF+SDV4L0Ed0eonO+hoRr51ukUwic+i/djWxsp3j8051rgF7KF9dvUsxSfPAR4zidkLR84AZ/Z31/N+YG+AI/SEPZcclY/D1p5R/U3bRb9r/i6z9wZvvPZXx3fazvuLr7v3xZ+94C7XPbWcs342HbNCOPYy4pcrO5Uw7aPjtBxWKohW6B/NUfYKZRxLVLUTAeWLrXmALbj/HPgQpXzz033H7gtfbopiNV2Mq7gjzGvqtTRhlpwHl6Ee251rGx/xq5Sa6GCk0W/Dx3y/BO1nSVwb9X9sJ1SCkXMn69mWXw8paTJr/G0PHAT6T3jnoNtnmn/BpnAy8fNX1y8DoswSIEgC1h4dg/P/ba8NeOhB4h62c5YW9R8B/fQHIYAWZ12+m/pUSd6LGGr2S4P2yWxXV62yyeqGZcJEs9xdbyTdXq63ZOYcOdJtldie71sr8+IF9q7Xa4fREWZDBDdmDYNwtzT2ynMooMqlGLWfCn0AVPzkdN93+Eqlo15ppttTuDTTnusqpnwbkke+BuKEg8gkmL8nePk5aXnrd0qcjPxIjonWmPPk2q0xt6CVKM19mBvyk1tAlEncqb3qci4/nkke9RjePZzVwdblzAXi3PeZdBEcGQtYjfem57sQtchLT0ZpzmFQoWD4qjmVPD5jRU+AvisQHxMgU9jqvHFi7DWHkWdhR1F2RuPaQD/KRDk8vymzYlzxAWEI1XngpNzggsxFitzIcT2SGyPl+2pwYVGmwtnSxlKjkLmGDXLm6gk9YwbdYJs+G2sxKItMN9YQgm/+FrQpSKnX9kC8urwLMaUzcjGNYzrimf4Mx5Qe5CFTVG+b8Dykk80AR1hLqlZM+4nwi6ittL6yEzvuzhm00hoN492lyZiNsOVdDXnh6vh2vlYPvjD3d1v1nzo0G+a3ba5yWlz1SXXCVFHMoD6zOaEFT/AVAkL5hyaV3G2ElkVoFqz15rmx1XBIKwUAP7G+eslWGDbAPIcOAD/VlA/qwIKplulSu0yAAXKS99hUApA1l7K9x2jmD8sCgSXsTY8Vv5Y3O2k28uiHM0iGayKhSHGCddjeAIcfrlXHkTd8ZZS6ApGpGMqEyyp3n2l1SUOgew3WfoQAASZ/2ip1WXBzbsfg1bGrpJoeOPP/Pf3F0uZZwFNeWA/WsAogejZleP9Y6O0e0pbiMYmZpkFadVfF/HJgwG0Akx6kqMekAH3XHUmkRJ5sCoFoR0pzzyGmnOUgnYk32sgx5xK9Q2lILwTMPPYa140yyrXHhUlcNU8jPdpzMTTP0ZPVsITruSihIKwLGoPw7BvIzSsG00kgSMq4gYqaVkrUVGDM/3UAmepC4Fvzvkl87LgCVO+5Y6Q1LOuxAZYh19/X7B7ArjzO/NxlPQFOdvoHyIOWyBw0Xxr+lF03OP17XM6/fabn8UszUHMuy2h3laamFpqsfA+GBrAwLmxjvTkudIqF/8iBeP+qRKMay1ziNUx+wXbLra60H1FtJu5cJDmV2IpTAAZmtx7GVbVSgrHypnEQnN4/V9rFwty2pPfyjimNAbW2PZkjGeOzTEoI2mc0eqgESxjX24JiEHKEi1B1tvSDNPkDLqLUYjx+iA0WIVanR/jfZ/zb+zpimyQ9OetDWdrgq+25u+WFj8G6943WOx5Cv+sgUlLUasAAd2wn8SQ3nOLiuUY4B5qLmPsrx9jf9m2Ft/UYrErpaAL4QlAheUq2mGumIDpvqXFZ44cKOKfZr7RD7D9xtqboQnosZrkg5O9XzJ2l1aOw+f4+GwYgPb+nCdaVoHeH4bO+hH+XQ80OhwZ0w+Qedg7EvG+qt0Dn756w/r/AAHqPtCpPwCAQ0u9fQ98VNWV8EzmER4wMANONNapjjrYKFGjiZY4uA2QCVEzYWaSzMSaBHZL7RjtfqgzEmwSoENKnjcP8U9c2iLSlu5HW7qmK0JUXCfAJqEgRKQSCApqWh+StVEoRInOd8657828SQLY3e/74Pcy793/f84999xzzx/Xjoa9kNrm+syy8krEf1HSmmU9+Pc1tPEBzSyEpxieEni88JTDUwlPFTwL2TMHeaqZ0LYCVuh0yJiixDmLFTv8PqhmVjyjDkVQSq2qtibasak1yS1O5Asp1jrAHYXQu3KnLTpQwobll3Di0F6P4dSvmehnT5Hu8RyrF7K0k3+E5hsN0XpnyGhpIoXfEmce5J7J6p2ZZMFEEiGoBC2XYIOLRbRYAvCwkdS1tVJgwGbBU6DEH4cGiBIW4hWwI6xYpPZ7zZBpjYGz7kM4EMrOJTfSV7EvnjGI90evKRA/wdJ0iGgHVQ5znsBu27gDOgln03dMhc5Z8OQRYMUTKWrhRPrOu+Pqfv+CAWIL4MEBtLMomtlEKEUD/33w2/vpkRJntvLAbTdjsJNFhxMJGi85Al2GaLtyN4/OOpn2bi9MqHdG2FkM7VykvC9ebjCFnVmuwcbb9REAQFkIckoMEszohMIuS8n3GwrGIqOv2Ykva0PolKMOhM5oh1VlO5Y4HWx2OBpzqNcTpG+/0tnNmccwQCTnHb4TpthKZotyEd5qYRTRcIChDxHn0qtCa9AIHhUwhOsQwBivLTCJ8whKH8C4nYFxWyIwphDTCe/bauNyobPQi1co9crQ+MsNOLfINVVOyhb6QKJG+WTJx3H8wOODcstjN2Lx5dDwYi80ykv2/334CYBb54eFV3OLU+uCyvzXvKwByiAHIsfoSoLwi47gaSEclLtX+SwnoZmrp0ceXaCzd+64sD+cCJ4yJHmYzEL1khuJAXIpgU2SWge5Q4hjSWZBOmumZeKz+nmGeMbeY7TOPGuVzeEbU5c2LVr2Ei1wt1JrlNDf0VEvzwmb3FogbqWK48qjdSjLHXayiqPEHjouPbOX+FqKFMWCJEar/xkqugnbNnIJSy8PQZG4kNV1/PowObCwokniNuXplbCUG7YYuiizgQixRWR3sk15Lnwjqbzfwc0x5IbeTJhjkOXTNCaK3mAWwoQa42N7lMvemo6K7z3wgwj9Axx35ZpfOtXj78vDqukgNJyTED+2rHwJG9lKbr6ex6b7a41BbVxaT5PDCOoj9Y6dOvVrWRZQm3zTKyQFnxZ9HRs1Xm4aIu8G+NewEK+AWiL5atL/evVGvHaLWKgM+eVsPBGcg5Kg0089ClMl4/wajXxQiPFDkODTSz9TSSYoiVFPUgSZTyfs1Jz8BhSaLEe5VVe8BieLkk4RtKAe8jFsiI/tvmDaTRy+zaP258d7dEc=
*/