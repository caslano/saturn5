/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONST_CAST_HPP
#define BOOST_PHOENIX_OBJECT_CONST_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(const_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct const_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target, Source, Context)>
            : detail::result_of::target<Target>
        {};

        template <typename Target, typename Source, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
            return
                const_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::const_cast_, Dummy>
        : call<const_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::const_cast_<detail::target<T>, U>::type const
    const_cast_(U const& u)
    {
        return
            expression::
                const_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* const_cast.hpp
DxN1Ax9JQcrU0G2SpMIGclfr7Me2sokK1w1PQ3VcTRxeIhdK1b6A2cCERg39h7CsSnysRoZRpTa6fT/Pe6xWHUDeuJ9B3WrgnPv02JUIppHS4/c0kJeEJqF2aQz33h77vFo3bgP8qFEX5UVzOAYx27uuh0hqLGepNZtstUgA9U57P1YarHBsgV2b2w709pvNDhSPHLjVkV2H56v1js83ZpcW1jY2AhA5i5e4axO9ti5KCF9fbbFrwWWI8FSnd5pW4hFRb2VlVFS9i4iPpKucHNKSj3lPfO+UffZS5MDAd3h8z6VFNLjFo5dQWsY/dySkCOhk1PXIyoxo3UIdZim1TxzsulCftJw4tQrt0lgMp+1uv2uPDpUsQuKR25zH29ta1bLFnUjRquLO9Fa1Eu1K9IidF9ES6jWjj7RhWDAvwNmdyJqZq5orzDzEPPG5OBhRml3s3QB4WDvjkAA4WiUTqh7sXJhFDrccC8lHur8IHDvZDm2gLXRt4Cp1F1zJePdTtrWLGDca92AJnBi0g8cbWvL0ZhQFSEBfMNfIq676lm4bLZ6neXl+nkn/27AwqiAXmAMRRr1e9W1qKMImInqOC7eqtV3xEftKTW1MQB4FB+FY/U52vOq8K+DFHwQv+AIh282cX+GHR0DA/xytzB6mqj9xmiiAwhBh3tvb6zoZkKZAeZzjIAWCdwld8hhOC3piIdIxmljL4HGa8uHl40OTwna7ap2GS1+s7k8/WDSqWJ/O/soikIBGIezLV0tj9PX47hrncrbIAsab2Cgt9+g2F4Cf83Spcot+2AEcSaDh8dT4wVF+5j9RthRGBRAlE9TKqX5N49fqb/MAvXl8fcQOcqc//ntN/z0ywPQTZy5gyiAt18RA7Ecq+uHr5hVRxEQTS7gW0BfG7cqC0KQA/ZswPjmThOavX786dVlEyLCxVfDIyCAi0h8Vy36V7Vk6xFJZ7ErLyLwgOHF++XKgpK29JkxBQTG3CKcNpRic8NyYfZWTG1HhGI5CNvcTSDYSnK5wgGfblw+trWk97M8/LCF0Nn1Y0nGofacBNZMZPPVZAh5108LgaL+35yPUZxREPwJlXd2Jjc3NvRCvmsSRI5upxUU3SucuiWmyCDPubqlvGUDqNHkJwlOsIP6PxEP5w/eitOVLNQOCXD7gi+bVnf6w1WkR6ESVfueY/VbHaDxO7XqzA4lo9yeXwwmjt7c3kxC+msQa+USH4DqNMXXG9AuhZIDH5/pWnBB++jR5E8+MWsdWosEO+yK2bhziLvyS6fxXEh57x3Q0NDQ7V8p432hD54/PSyrPvB4ufbKcE1WfDnjo2Nb/8S7QILiF+1t+3bAvT3+8cK2SuPqBJmE/yqLfMVKl1z5kv9lmFu9QISFwY5VT4iHeFHpfIfHMbG3uYxDCv/1iEwmw/NrGxZimYUJ7a0862UHygx30womvlmfk83h54FfsRNs68hONP9y7gY5CqI5jNC5zC/mRrHC432T2KPbv86Jp7YqGCuYoqZMqJ2qrU4Z/kq8J2VoS62mAC+XwLf0Hdo2moTtN1PbUydepOLPW1tbzJEVhIwMAhKu8rMy4G/JAgjia7J96OpvgyzDZ66ZJpZMxcE6OyTnRJDk4nO/hwpjEZZMODXHSfYvAodOUl0fLuRXwuKwBAqBZEskOFf0448tfaO74ZzQ9GyzTz/1hbrvTbOIBJ3NfhI8+G5QF15IrLgJYDDBSEdMnpHjSR8nljN8WtVmg+6NJ56kG/js37G/sx5SnVGNFbmImv9mpbh8e/pEd+QdVcgFInx/acLnfOeUBgTPZPtez3b4q+LPB7xK40WJBftbjjUwhH+7nKtheglWxdWipjYY/QA99LMs4oMMctj8t1e9x0+N87A9TR9zj5eZe/Kmoi8IDpomkup7epPlEWq+goCBtcDY5fwMNEHY6hC//NbtNWW4IzJwAKA04ODi4dlO0SyJV7vqFyK+voTG8fKwoAhnQ972WrIOqfqTY//APSGUdmAzmSgSiDful2RuTrOa/fsKhrbk9mq4/W66+dbK3tt6NPxW7Ydc/bLq+O5nXFX7I8d3G7EXMOO3mWwv8lijSY7lRdEMn/3cAzDLVSW9QBhcz/b7oP7X1r+RMZvIlLRk09RhVrmsBzI/7DdA0c4xUmui7a2rix/950WoRgl2k75+2gzGeiPNADW/SiPu1A1Len3SHF54tQh9AWmb6yFFMCjwx+b+a7Na5JbolV4f4K7QbI6cFTqSBxXLpdQbbN01xuxMtCC8Tf7lsXl7uz569HrZ8QE4kIl43psKpjyDgEaXXrsd1c3iRbOpNq0Gr8xcmRkZ+Bkdzn+OnzcbQBu9768V3+vHEC7ibleqQfxnYe6clbggd0Dcwba3pKHZV/1l1twLMBeUn0DcA8TMzMzPpvsvDxboF9n5Y0dMbGLT6LjiNcv30pzGtsvDqHBoJ91UrrpjLDLlldqFml+8zsaWfxZXJsIzNcpVaou8pxyrWrpcKKb/ryGd0csERcOz9mdOlBrN2g+XA/ECkpojrcpVeRVPT0gf+uEJKEkNki6nMPCfg14j2bMYf38lusOhyYDMwseKsDRCjTwzRbUKRvI9iJdGg1covijr+rLThlp1AGYyJsNDh4HT0dUgBXgpSmMjdMn9Mlc3pI8OQjsjDlSaS/4LkyuUx09OfKoC4nD3LynEX4W2XuZUVkXyGXBDayVIsyDORMGeX+SgtLY35xmtH7k++OQsLi2oI76w8r0H7p6Y5QjIhEoNoEx9DVLBBb/2Pb+MGG+nvXDS0dtNoRmRdz4zaPsW4pCdhQAido4AdhI+FdS1z7vnlzH0rbHgwRSO0LlejYCUci0Z6SHdAru1vbBrlxl0iYuX0n2JNPpn4eb1vKQsETHcJgWW/0Fz48PPj/Bje3hajVrPujWv3cEbCNoueCCD7k9HR0WcmQ9Gl42Nj2MoZWVl+eOMzna1ifWvH1Itke1n35CTG2nsykXZnr56+F+6cmaXznLY7fSGC2ULed/Tg940balO0L3+grcDQZjWKTVXUb4FOMkENhgFZrIm/xk0vhtF6cDWszofuNNnwDuouLKKv6Z7phDw/99TqVleWsAOZXPF887+qlxttOtA2DJnhktw8cf5e3UA21m9W9dIl5FLsb7LfHLPDdzLY85z5BSaO+TcHUSV9BJRpAAIs/dOC6mWoDrGMlaIhmSR7aQ5uCLflMiY3Dipp31QnTfStFYlt3Ga6CEZFMwv9CXfbfZw6WN85tnlkSGnmOpYG5GaclSLS5DvRvzUCnJsjmAV/m/PkEW9uq7SKn+O4UGmTP3/+nPeFoOgq7mlKJt9qXpDs0nCRLCT2m9AMthd4ggcEvvvT/hGzm3/FpnvPkwwrOOMP64rmCm2oVA/p0RcWVw9WmzO80ntoiWLfRjVYdJqiJX/8qMJ86KoQsAakVYlup4R8dZ61vFkWrKLRizEhjqSjP6TSj3owjTFkPS+8oAFcsjaBysbt+/VoCMycp753Jd1xxRKV+CVCpgRANe/HQVBMDfdiV+nK7zU6e8ah3yrC/pcbfE3vHG/qixUQ6WKvve95fbEF0vL6OakWsVERLMSJT/2I93z5vs1eqTUZftLHdEbnft848MECbfeiHCEiBQqy30Yr/6yObpCHd6iPlRKw6k8Mm7/ny/OiVH1+piekpNTLn0Ovz7ep5yu1wdVcc0TPnM16DQ8M7thie+JPT3txrZP0zMydYe5ccnXdm+Q86W6vT05dGOJOK4FwiE/6v3zSeBzIKXx0DehiHqD8tjnnl28QMMUu4B8v5Wr0Ow2I9iGNZW5SfE0c2lHWTeFlu66l27ZHD5f56CP3q2lZvf5LMMJ3NPRVmECAWkPwX3Sj0MwJ1L+zeNy3NncQrKHlg3tBuWtC5URdFo+7+/svL0vrT4J+v8QB+PmkRca1rZ++UlJuk4n5Lg8fWGgC5nvsAidOwqNv6TQ0lomCph8xjX37DEez20c4Jmouv70zcvhu0CRCNQa1zwwuCYlOmA2U2AlpAG/A7A6OBPxwQUJ/xSK6xU7j/DdydRN1HvSJBlBTem+SAFBVzRx97GS4xH6GXc1MTk6G0pJddbi+bw9q9BevjzWknLtluto1OoO8DOTNrpMWzsuru3b9de6KXC9jyYW86Zx0KnKw7zTQSOpkJ70XkAW3H+n38Ua/WmoQR5XImWdw2+0KG9ylzr0E2UmLkToLFT32osvLHPq4kY5PTOyfzaxQzG11NnTNDFEtM3ZCfcj9cgwqU5aLIfil0zQCctzv4blQ3XkxyniJbXO114BUK+7fj6L/9EMfVMGVLZB/063xsDvFWJSfWe5mj6B6NEllNeBe8SHuv1hvdskIPhDBWwrI61pW3EN1zzqdzya+12g44rTHlUoU+a5QJ9/mEHBf72inO6xonUGFeLAsWsidwfvRSarOh4+Pz3kPXu72u4ksd3hVDOG67BpPSUmJocvRlJDxmLqK3xpJHuGfc/KYevaSiTK1cti1WkXlZCBWzYSlVRYC6pr1YUOjyNzKVQD78VqD1lnjSRMoAucSWsvtB1X03++ZyqDiV7U47YAWc0AyPtdLFU7dZB0IjHukgL5CofW+Fi/zvPH7fK3QMMWtFcDVkWpsRuljugbqpW5qVimH27+pO7pCKLz5hxjnI9j/3rGUleewLoobphihWiw/IQGHgsgU42rrOjeygquJhif/BV5i3jBvtrA3NkYucr+b0vVrGScbYcvPjJTV2moZE/CuzZRH6zm4cD5QeL3bw6K7fBrknNkLR3u0VzQe5H9XQAE5lhJ5mY37/ypOniF+CLAemf/2i2R0fq0r+3j3WVO3y5d6q9OfVrjDi8p+S2Gg+DF1d3yYhB1CGrW6rMMO5cYR6ZoenB4U/wrg+A3rSV5g9buTBrndC9mLJ7pJB8P7TOuosxf/tmBS8J6myEtJwVajwo8CQS39qrdmqkM1ix9Yyperk2oDtDssWzsJZMzoztfyYQTfqECkO3VzF+aHrcEmaA5MQugLD0X6D36QkKrutovSdYO2x2AktcO8mfadMljZ7q0OICdvicT3XAuW/LEPsxENsEp2T15yghMPn/1mLvsRYCCfzyuRFAk30K+EuE4O3ZTf8DOSIKM8jOP+gmzrPbZeqcJ9Z26J6JZafll25x3qzRDhVi+hUonTRG8zSPmTmPjJsl8rinwHsD4b6cMHWzY+ijhaRSkn7cNGIGJ9txl36cXbMXlW0d9/a0B+jeHoKdImD5FFx/ZbnvVXUj/ENYuhLoGjo7pdCe8s1YI1ihdHazFwfiMI+tyqc53XYnFYecS2v8zmz0rkpc6VbbXHPufNEtG68lLy1OVDIRcTU3554+VOXjzv3uL4T6SzSWPaDmXaicnkz1Ca+fYbHQUGBFrtD8wxgO4VA/dSj6AiuH6YApbgleON8GK77iVEDfz1N2vQESnphGTDZXCIV7Jx9swr6Xd/BabbyKGjgK8TENK5VyNJg+M4jGd29fUOMUAH4+FMMdcX/VVeW4cPH3hRo4+sRl+/pgMb0ov/4Hopj2YfWH3hetaew3h3S4J/xsS8MYD6A/2gJTHMh8z+N9YP20Cfsr22S78FHEgFHeyH/zkCaGuykSD/KaU8ITJkGtOo/S/c2W20jXBDRRYsm6o2X2nSb3C+uTOlC5hNUA6K57qerzDMsJukiuftbpsDxB2cHM9D0PGSCTuBPrZyyAdKkY8bwqAblqPjvTBdQU994S14qt+YL1LGiuUKPtr7EZjicdmzpOLMB2i8SopC9wuqwGhvXAsFPbQ3BzrF35ji9Nn5oMJeDJHXq/7/nxMS1e/8CKFK/gsrCJ/i3emzlfft7tdOgF+CsG63/Hwcj1XnPh2sOJr/Dxck+V/DWpc67qCnlD2BLrMXu9bgnJv+5Ga/g8q2PxTPY+3Jy52CfONJ9f89kQ5mqgKeVd4khJPiDiS8WMEXSefl/g+SXcXueuh1BN6bCb70IDNgw5FXbY7fvL5X6XMt5rK0cPJjncN6OdgJvNp8sQhpDT4PEV7meZYTTgUc+VP/x6D8KcXsrqgJ8gcRz1qp/e5p8hgolU8hSOS8ph9d4HzSBFhD7qApAm+e04cONqgzQDAHIAj855qPrTskFnW86hZjvGuYIt5vmCJZDwitOX+3/2+Rp49289q8tpWiTZ5QpYqPdshDg3DUWVFHJeTrhVVlQ3HjTLZ6qVDlbvz/5XNNPgmJ0aSWktMstC65MIEecYks4rWtUPVO4tgOND3iXe6WbBM9kJ64HmhT4mMMMW+x/x9AguK+ybNlpwhUy37YWTDlrDYz7sDfnY9yHF5LYcRZIoWmTjfhIPqrR8M41WqHzW31ZD83xXqH7W395PwZ0/N34VToK8RrA+Y+YOu64n/BVesw/55LgXzumy3umvXupqbfx2BJmLCjeJKx3IzFyZBVvnz+FRHDwEQDEC/8RuP1mxnb2FAu/Vhp8anIwrisrPWDnd/lY1KFasbyKXj1KLXNCxT7X0dbyj9v7NVvP1YgPIv7xwk9aaNsZUI9e+DIrwIQBTewMdZkG05aw2AxPJ9kMdrJruL3YDD+e3V7t7e/W8cF9Dhv5XmV0H3Sq/G2Fjz9H5hVSZEvWV1AVkV+PeIsQiTduhO4MZmHNNwFK84abP2WEiqn+ZvuteiahM84u2r5K8fBETez8Z+iZi7GZzM/TptW6Z7NYSoKXg94cHUJreI3PvLdd9yd1AuebD11T1NAvr9LaKvw5fzKZ/925bfV8/8Dd43h6V6oHZY4kl5Oyby1atbSqX/+dYGd18N+9rmwHz1YIO5ge1CT1iF7HOwBvum91Lh7nv9lboD8/GZHK3Lk8sAqPgIinfx5pfTzWKWUnNZiVmu6sakz1crTMGggIh95wrWY4GjSThznp3VQoM0rJZuV7ZJmqPn8QN7PzT1VnDlFMcHry+tApy6/cpKVjyT/QORAHpJR/nYMeNrSRJljaU4kLjW158kBnZPIrwn/dGq19nmIvlc9c9RRaolEqr8q4c1Me9KdTbmcJrzVCVCH8T98d22MvCkY0SED/GI90YQ/OcU/uHa2Hb898qry9q3c00hI9THzsk55s+6+w3nPHOKXc/dEt7M1ljsWzYNmNlKxFLbASmNzcl8EIdUllJWjh/tWvaN6rrMNxqgsAtmh0LDTsxOQzcLuvdefSvbmYgsgyZaDpzUE1nxM0wBxXLj2FbFrn9CscSLpxbuEwMF533kKV3jpzwo4wJvt6X3r4v8/J6hk9wf+jYitJ4T/Ylav036fG/Of+pbIuH7jpa/X7zsY7p8EqTBzun96ihJOy/rxp2AQV5BQW/gKnfEoD/7JWvUEoHiAkULRRAKWN8lrrkJFJJglE5L38RhGDz/0bby07KLySTj9AH7tfL1IpjAePRzuUkGdMMvp66ZjJgZ/GhEM6UCeFuF8s6UJJ0ufFBVWCA+2kG+iqcn4rr4DMn6LOfziGA0Q3X3lv8XuAFBHxR+N7gM/brLoxEM7OFeRJgY/urZWaNEph0YIHmYLet3sn1wkMmcu0d0cKdpkJmEVL37oSPlKkLrMrDCuq/g7B3h8XOwwE2bQJZkDAGNlQd44Xm6uMSG3R4ickDOOFxCI9fgGiGKguj86f6ZdAKFcKdZT
*/