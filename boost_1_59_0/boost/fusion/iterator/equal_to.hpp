/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1208)
#define FUSION_EQUAL_TO_05052005_1208

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl
        {
            // default implementation
            template <typename I1, typename I2>
            struct apply
                : is_same<typename add_const<I1>::type, typename add_const<I2>::type>
            {};
        };

        template <>
        struct equal_to_impl<iterator_facade_tag>
        {
            template <typename It1, typename It2, typename Tag1, typename Tag2>
            struct dispatch : mpl::false_ {};

            template <typename It1, typename It2, typename Tag>
            struct dispatch<It1, It2, Tag, Tag> // same tag
              : It1::template equal_to<It1, It2>
            {};

            template<typename It1, typename It2>
            struct apply : dispatch<It1, It2,
                typename It1::fusion_tag, typename It2::fusion_tag>
            {};
        };

        template <>
        struct equal_to_impl<boost_array_iterator_tag>;

        template <>
        struct equal_to_impl<mpl_iterator_tag>;

        template <>
        struct equal_to_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename I1, typename I2>
        struct equal_to
            : extension::equal_to_impl<typename detail::tag_of<I1>::type>::
                template apply<I1, I2>
        {};
    }

    namespace iterator_operators
    {
        template <typename Iter1, typename Iter2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
        boost::enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
            , bool
            >::type
        operator==(Iter1 const&, Iter2 const&)
        {
            return result_of::equal_to<Iter1, Iter2>::value;
        }

        template <typename Iter1, typename Iter2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
        boost::enable_if<
            mpl::and_<is_fusion_iterator<Iter1>, is_fusion_iterator<Iter2> >
            , bool
            >::type
        operator!=(Iter1 const&, Iter2 const&)
        {
            return !result_of::equal_to<Iter1, Iter2>::value;
        }
    }

    using iterator_operators::operator==;
    using iterator_operators::operator!=;
}}

#endif


/* equal_to.hpp
G1aozga3H9CDgjOXiNKD9HEu9VQUbKGuPJ81Nc+WaF9aAhYsvbfmPj6WdgdloVe9fcKaWG9iFTXktMbhJjy8C7JZsHvpDQw/PvVqS6BabdObB+XXYyTAN+wMf8U5bdnq/kbHd18CmfJGBpYhWwBuprw6405LMCVfsLzmdjflXAZchUPqXSAUmWeGzg+ZR6jhtO3p1CQmbxRK8+S1H+wJlVPgnK/SVmoF+J/ZRm9ZOnaGT4YbZxCyk6sjpQOVJF/Y7mN1WQ2VsJYnbP000ghDcUW5neFa73pnjbvvj7VM6eHePMQTLEfy+IeNJTjgSwgLQOj+WHxgPB7xK/Q6C0nJUJKokUbJF8vdIu/U+2wI+OgdOrxr0OFtk/5PeGuC0eH9xyjJDxZEeld3owsJA0/xY+v2ZQmHgcUEYM/QNc5jiNSsTsUJLpnRL9gxLBZ9DskqIaj6pKS1MzWyl4U27E7y3rAIwIk3bJkkcKVUXxcBUBPP2fJSTB45guhHg0WL0JV+UxR9Ll0Z2nmflaGryYyZ5X+TiIQgxBRHAvinp4t0Pk+Sj6KxNEI2CgPuXZiFAFCxPT2BvN1O+8/LbAGenUMiprHQkqDOMtCE4BRChIRUCMrdmeR3NOIJ/xPd0rn4+9uHeA+By6SW/0S3NztDdcnn8zuN82mdXbQERxcO0xqiNdlKHLRccsm5go7RhhtqP7Z7FRjiAk/z7KKRtplVi/Tm9kQHiB53Onjfl2ItYN3T1nRUjTsLnBktz3dcnfIhRMy4BmTziQMrk38cPTxVhqWlERSxo8C2AgpfmEX88CaggiEXLB00RAOyMcApRfH2t2TMqNaAEEdrkb4BO1pbgIz7gkvI+7XI24+KGlsA7kn0XrSgSvvOud8/BBmU7Z5AqKx6oDWdZEcAjUA2H9iV0FdwyzZ6xKSzqO0BIrJtoDoccHtSXG8YgAUd3Jc6UDCEKGRIljjcr3RAWwRu2JCJjmRJAnJDGwISOEeEyzHEB4A27+asrIlmndXyeaFSUS1/D86grhwY5Oby5Hd397R9hMeEgvMgm6pHCfF+rOWmVJiZH5xk5bZxJ0txOU6KHqX04TJxU9xOeJi/rHqPEaX+3ioqc9KN8tp3904acX+ZDs68vW+XdTLPLMI+QgVIo1N3XIkwatuTDP9BqxT/FGLtB2OVhdjvzPTtAj6L3V3mc3mpgGwiBQuzP9E8cabX/xUKzrzotI+0DjJqmV9xCNRgyzamh18NuqkH4dG9cGn/xv/pE9w7AO3VnwXWniHwLQJlpaGZqYk3ZM9eB9be/u/u6f9cadNL2aoWc/PHyhvkak/ZbR2HhjjvQmq3WIampxftfyomNnhofDTi9xS7lZt/6qrGzsuu0/ckVB52zOYcIxD2MtWrqaWd8NmRNYxfCe7e6Dfi8wjuLnX5axsVcSDdvnJ598hmu/szcy5TWxp5pgfnY7aqZrQsS9l12W6P+Xq6Eu6n6AOySSPbOtO6NFgEyiAEl8uqnvM2GeS3Cofsf2JbLFPQ/LQLkPCz4jqTsjDxgylbxBxtgjDqfWH+ZGEGateMfS3z4qef0W1OlyigSEKWBW8YpbPrspMgBi8UGTMV6d8jSL7Fbouptw6Id6SAus7r+sDTDp+NRAcyT64CLgMG/s+Q4BrwwA2rdVcBWupo1wbxhmkIUENdWc1XATHcIUzwtGvhfxr+K+XyocibgIRDAFlv9PuhONdVqA4TVHibWfuqka7HJxKQDMU/BNAgIR/dqe+lWzUW4RKKGwfcl5DBU4iQ2pjevb6r7kREsAK86SiH3RtWpP3QfSfxGoflgznGNQiRHInbGmU0OhJBnIeEsLTtkUOFsXTMD0CsJ5Cl05w0MImSd/akD+t6aM1pTiZYPuRHqVQtLjQDG11SFXEkF6Tx5aE6tysnu9I2w+s6rBeQP3WWa4DPFyankPcoGfS4sDmS/AH2f/wNBWA9caoBsqJVWnCkwb0o2i/ETOS0oJfSnCkmXm4AsopeCcPpv+wcgXVt7zWgWA3SCF9reJoYoSHc+wMS4INe/AomgeIQw68ezMNBNk8vIW4+ioRNDv1AxUVMSnQZky0UhysjSmpn+LuBleiKW8QVrAFX7o5azt+QXwjP3LmSrN4FvJfUIeLkjqZ2y8Nu7DwE2QjFgv09AFBhQ+2OYmHLJWBlARLS+RXqWpEj/pD/4VEOWai9tA15AZiEUk8e2LWF4cubAAPivfGFvXylwPXF0ggqLJrup7gHdSU9fECxKjehZAl4DwDYQkenS8Fhl1L2gWn/xFy+rKKoZEVNAVidjHyFBTSNH+2rKKsuIxbAcS2KQtWZu+DAi7vtI31lM7zrWwPX0/Z3Q74hITJNR7vfOYYadbmqveA7sf29NFkaJ8g8zcz4iqVZ4dfOP563CD25qo9xifSfw+U5hUCbTtt1B65XCP91HyC0+YCpucKvYnEB1y1mna0MB3GEPyqzXKoeNYSYofVzGuEBwsoRnrYr8OilcZkvCMETZjBo/+TMwblxtgKMEwYeGp2HARUd/vj4laczwa8I2FgiIGHXs+/0YsEect4warSrdHiZ+e2FRukxBOzl+p/r+AEdixoA/t7FgdYUQ/0U7aQR2OjQtWlBO++muCdw+9nO/4YAOrJLwZn5x5BvxsKxUneMlxAHJARIrfeXwfCq0QFtLpAQXer7xy5Ul6cenJcQdXQ2jy68+R2dUSoIHgdCA5YxpW1arg8bxFA1BQzD+J9LNy8huEFPaD1yiVpzqN6eQYUvpZSOIYJarAMZ2ipbADlemlNI+Nbg4nSL1idcAJ20cW4mmOQlvwvNGlbzwOYFhCW9yt8EG4w/gJZOr69FpPOVfhWAM9vf7wKorMt9FLs11OD0lIhIaI0L9TeUiMjRp5/qTvAmJ2oKwRUREbhkucEykJnh1VCjHigdDJlC+/mMLxT3FW2vplecnas3AVkRIZPAi9R1UH6bHhc87TkOAbypaHIcaA7RnwaKk2FdQtBF+icm+lzpqkVK25hGoQ32G1mf1hQ+ZXdZbb/SqtuQPqC4OTiZCrSkpFNNHECNCwyq8kNupxyrzwminfeqeXS07dn4W44SA+3EFuvmSwgTV/R667hcO+q1Lw7uIgq4B635kZEnY6LuseYmTuhw+oYiA/tpUUweG2PzLo/IMmex8qKYOP6oQRY1DeFOXpmyX1EOm044Oo1ErS0CjdtRzm0asb+dAjZLw25R2aZm7+HejaSnMoX+hEe6Cf8z2TSjeU9KmT7sAM4/sj4wK0LzoK5exFzZrj5ojfQUTiFtYwjMEQsrpPmwNjXyM9LGbetkwFtRlp1L9vsg5ZYJQuviEGD20LPRbftTRSaO/s+1ZFJZTuKJQ1fYauCjNfL3fTrp4JaF4BcoQRUplKAr/GkVeDGA2P1GSYKn2YIu/m4eD2leMazvUtWmH09oay2+Zk4Kb1CDp93h2712bn9Xt3LJ/MhRrlUS4wvL2z2An0PnbwPHAbYzh19GF38BfiTo8a8/GaKBPvFZks4qskIIwGCg0kb+sbSVjCbUIAY8VIW5BxXuznExpyUrsv8syTu2UtYFnL5y/z/DrUsz6g0Dxx63gzOHfx4CUJg2hTFC//8JRJN/SmBWFBMxH8W6R3+eKz1psqU2cAkPx+qDpDyO/NOf4VifKbiODHodO3AIqe2JeYeQ9DYtSt7y4pMURli6XDDL0IknXDxpnHZ/1bVd8yZ23JypRqTuXZ2lWkGo095fKyuXmRlJp/3voGO1UB1h3GNIlFfg1so5pPn7M7TFNfnfved/9ZqsP8YxpH35Oh1WIEyHtjOqPcCReLm7Be47GQ+xfx3Jz3actG054J1PoNO/mu3qzi8498Z0k8wzGaoKv0IGiK8C3GHkD92VzMP4zvRhl5AYOgriAWAOHbVVsB+s6rAeF24YiElx9Ak9JO6MuL+DTRkUvFli0XYfb6/nFBJYjGtexm6yapk1CnVdZcKR9KuJGwI6VZlEgDOrxM4hE/WFUJ06HpNuYMPkd19YB+phGl0VxglKUWK2y/xNivZwetHQ4hkJYxH4VaW+P3xWCnJy/c9CsL4o3BslZN2mMWV7qlFVOAj8TUbhBxvjaQFPGhBuADLwdKDIEh5d+NXmkYjOPz7lFILlA0NiBoMXdVU2AEy8BdsAxxFsvsgljEXd4UzuU8g2z86G/EDgS8uZGyvvworsz2CSTQ+3vGCZl2y6AdXyDjeSUV9b3p9DXR0FWVsGzK8eiPc3cXYCQtHKqI4xQesNWbnpISjzA7Ng/inG9yMsDsplUrWNMSdNtrgCD+aXE1nB8ne/LaMkPVwpfxXZBkBrNpQApxDHZdRRh2mjAL844iHIEKnopwhePCWhS0cAY9D+F23Bf6Idt3oEJwhRUXd3m3+DpQOymQOoyzIRE/h0x/qbHENyP9KTItWbFVrmp4B33zlYFujhOwvRu/ByGOT0IBM2D0LU8acFSjYY/WAJqLgLxNmIsv/R8l2YM62fU1r+uRvnFiBLC7GMktpqQbmn/TPHkpLV1XJvoxWDjm3fjHYDkzr5xbIbLvUnLINo9dT+zrgAPClmrbnzUzflAlKmcYf101Z5GvgcQGFeAcwaLaMpNCkDezyPOoYMKg56wxjY252d3qNNt8VfivunWpz7ESJveaBIE+wuoKZY5BHAhvHKbO4rGyHc+/Y35P8mEaONE8DSiwNoucKFthYx4HK08civSUcADCjRQe7kLvJ/cyzPQYi4Rgwosl9RJrYk8h1Uhw061vZ4fUXz5DaBsfufOcQxBI4lFH9Pw780+p85RBvrZ5bFAN8HbTCNni9sYUJk1w82gig+Ov+Tc52jBjmGIl9Nhgoo5tNN0pNeQh6hAgcM/kJdfxJQVJkqbAGW3ub5wD4qEBwBCzkQoc8LvKHCzeQ1HRGEdFfJr+3hTdrBGGBOIrT/NSjvBh5qp/nC+Il04bPAXylg00iRc0h4csMOoHEz/4ZFZWvJIxFtQddtIn0PIOg+87ohQYhMPNe29xu2aLEi8B28WPFq6DKGoPb6kcLoJmDKpwfqKvX4CADuxj2BsGzmSdu4NZWAF0WeVIIXkwel819CkXbiHUCHLnRtUU47k0Z4027cgudctM7BtOlgU5KCZKr3QMyQjyOha+laQCnvrTry51I6gXisiZskhmwIQKY8V2jFMtC3ALuLUS3iqD3oMGiJ9Piq7KcfTGkc41q0oHOgQBNhS8Uiv41pm02k/IONJkVZm4c7McFgRzpYfxmDIykLS60HGL4Xgj2zDYhQRP/o7QNKZ8hzbxDTbhHlTDCLHs7fIT5Qk4ghb2i/3L/z4xFJQnm5AnNJUFewCOphp7y9GOq6QVCY/eQhrKXzzwqttI0Rm6JcD5dRT9m9a5hFchs2IwIApHJhvggGbC/kZdf7wZq60wKvOIx/sMxQXd0XzwvmJapG9X7tsJJde3KSVdUjbWP/+PD+yGbkdiXCR9EKhIhkOL2Y6Y06BGTHIY6mqloVFstSbYTC9fyoDqfoWirGgZryNpo74vUFoPyM7xbBuIL9vooWNF1l/D6UvvVq0Om/gIBv/zzu9fOdNKIpeqWRmsxBOr8Oayy+JCDs3n6Zmwa+Qx2Ojn8iJCjfvPMoGm6u4q04U/e/+0S54PJApg0AI6Uk1PXU6d+HPo7a8Y4hButSUNcjd2ofxbfA/+eZD+QmazCYJH5rIo3X6d8M7ovz+i5jfMMvq/LfR3zj8TC20hn/ZG9fNqf98wA7gwUWSb3ZCEtpPvE36NhbZ2yo6+EqCqV+x5ihASyN/f9OIDZtaZFThPu/+kq+hkUn3KKBo0NMKTGjKPj8+3s7E3ervyJFjrwfN+ycct99LClw+itkIpVavsiDK1A1Qw3wfWKhjKuLg3m0uRkd8ofUArptdJnpTgb/lXm7eCoBbt6+zjqSwheAg9tRe+BvwVufcwn/+sFIJsMeaSlo2e/p+cIlt92djyESItqBYtAhoGYceAuwDWZtgXvhiQik2VhuA063nnDtKEl2lrk6+MEST8lXP3x8jA4qcgkMuCSb5i7g6A8PCBFuCobWiOjvAuI3fPPBmdlxA0Ek6V6DUToLQGYNuR5eyS9DQPHdOT9FZblM5zlfEXhaIfqHDKQjDC3cReduDuO3BoGH3imzwOXILj9F3a+q0Bo/gQGgQBTaARiZzPnC9n91AUs3AN3b2t6wfWU2eBpzCQg++111AvVBvLVINU1jC8BP4e+WR1X3lCglUzUC7P+G07vw6pmM1NjlM2qaMThaZzlG/2CT/eLXAjZNVtdpMek/uz1Srv0RfKS5vgS0G/lRHO/DZdb0aejrpN2YvAxZzpwKNY0UVN4gMT6Jg0aFDHGKITKUU6y8TPI7uhz6pER5PSzEB+bIGA72eHhAAZsCFRFmu2DRwGoQwo59y+dv769jadlYKqjOR7g3PwU7A1Hs4Rmkin7zKP47TOgcQqplc5Iu8yVBIiwOiQdPkyXNf9Km7BFjEKP1tXcjI6ETCcGnEroeC29yaTMKBS0BA6VokuMvC39xsmBObFxfWYrKsdcLMlOFLuuERfRd6zCcQjJIm25l+77dyip7K3qCbOT4ti4kAGl+MAmSk1Zf8YQ18/o/lljXbqxr5rGkZ8pw+yn0+Co19PKDvas5wdDDs58GVsYoetd/XwszP+hDJyzIXh7apaodMcNnGfjhCyJBTtKIrmeR/nf7SmnxHwONkRC4Ept0vkx0K1hUIxH8R1KdCuq6q/p/D/Y+iKMNSgqXsjTCLOsY0uINW7Ciho4xCyIheBZx0oiLxv/3mUWWuIJjSPYOTeCBMzlUhxHqOpUs+sCvOgavWjiXJoD39QAPCe9RKBRWKgYGNhocNLho8NDgoyFAQ4iGCA0xGhI0pGgeoSFDQ46GAg0lGio01Gho0NCioUNDjwaAhgENI5rHaJjQMKNhQcOK5gkaNjTsaDjQcKLhQsON5imaZ2h40PCi4UPDj0YAjSAaITTCaETQANGIohFDI45GAo0kGik0z9G8QCONBoRGBo0smpdoXqF5jUYOjTwaBTSKaJTQKKNRQaOKRg2NOhoNNJpotNBoo9FB8waNLho9NG/R6KMxQGOIxgiNMRoTNKZozNCYo7FAY4nGCo01Ghs0tmjeobFDA0Zjj+Y9Ggc0jmg+oPmIxgmNMxoXNK5o3NC4o/FA44nmExovNN5ofND4ovFD448mAE0gmmA0/1z7QkO4M/vmnpGjgRcoHPw4DczHolBTPEVxojDliRmPjj1rwWMIedgxi+slRj/+PZOswRywkiUqbbTS6Sxs+QjPAd508xad7GywdQLPBch9YGMBCHofGCk7+TK4kSmyadW4V1IROkYZnLa6JFBLqO8ZMgB1dcLAymydw5WHChcE3XhAa4qoqKE1Jeg/Y0GJQLj3SXvNG7hh4ygjCIEXpPfwIrivueIA4xsIQSMr3+LB9HIDINiA7Q5P24j4K7vwSB7q6vui+gRiQSp3vvIzseLoEaPLJiAmeBY4bYi5B4g/j9X5A4RhDgDbLHHDwabXbCbwJr/if59kHeJ+Ko1YF2dFQhR7hWJ9YMdPRO/hX0b9SmciEnxg47SrSVT1V2+o9z8yMUFVJlWO1R8+oleZneQWK6cImil0BXDSzK2QQA8Bl/fY
*/