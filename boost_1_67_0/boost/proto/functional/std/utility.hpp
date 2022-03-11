///////////////////////////////////////////////////////////////////////////////
/// \file utility.hpp
/// Proto callables for things found in the std \<utility\> header
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_STD_UTILITY_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_STD_UTILITY_HPP_EAN_11_27_2010

#include <utility>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c std::make_pair() algorithm on its arguments.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c std::make_pair() algorithm on its arguments.
    struct make_pair
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename First, typename Second>
        struct result<This(First, Second)>
        {
            typedef
                std::pair<
                    typename remove_const<typename remove_reference<First>::type>::type
                  , typename remove_const<typename remove_reference<Second>::type>::type
                >
            type;
        };

        template<typename First, typename Second>
        std::pair<First, Second> operator()(First const &first, Second const &second) const
        {
            return std::make_pair(first, second);
        }
    };

    /// \brief A PolymorphicFunctionObject type that returns
    /// the first element of a std::pair.
    ///
    /// A PolymorphicFunctionObject type that returns
    /// the first element of a std::pair..
    struct first
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Pair>
        struct result<This(Pair)>
        {
            typedef typename Pair::first_type type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair &)>
        {
            typedef typename Pair::first_type &type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair const &)>
        {
            typedef typename Pair::first_type const &type;
        };

        template<typename Pair>
        typename Pair::first_type &operator()(Pair &pair) const
        {
            return pair.first;
        }

        template<typename Pair>
        typename Pair::first_type const &operator()(Pair const &pair) const
        {
            return pair.first;
        }
    };

    /// \brief A PolymorphicFunctionObject type that returns
    /// the second element of a std::pair.
    ///
    /// A PolymorphicFunctionObject type that returns
    /// the second element of a std::pair..
    struct second
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Pair>
        struct result<This(Pair)>
        {
            typedef typename Pair::second_type type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair &)>
        {
            typedef typename Pair::second_type &type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair const &)>
        {
            typedef typename Pair::second_type const &type;
        };

        template<typename Pair>
        typename Pair::second_type &operator()(Pair &pair) const
        {
            return pair.second;
        }

        template<typename Pair>
        typename Pair::second_type const &operator()(Pair const &pair) const
        {
            return pair.second;
        }
    };

}}}

#endif

/* utility.hpp
0QHzd94XZF4mdQ8l/qr0vaTPAC/1bl4MtKlskX/cT90AGs+QwLeDPORI4F8E/zMl8DbXGpiH+idq4pN57bYwv9wto/Hbuny/kCt42zOyxJmmgF6rS8ia+TLQdSNjReQ/d5uvjywrSrI+tlhTkvJ4jhaUZD1lgn+pe42R4F+q/jbecKQXSODRb9C3S+CnAH6FBP7ZXxzp2RJ471+k6ZMI+LkS+JsQ/0oJ/A/gP08CP9vC/L3dmhJyjzzEkWq0HzhMPRn98cOctzyMe+RVMorl7dwvZZLzjlSoeyl+LwS83BTN3iv7z3qLP30/G99VsNkrrS87E/ohqXuULSnp9Cc4SN+nm+sgXY5awPPrk6VKYvE6xNnefH7Ji5JdWZ0+PZHcBOK3KnxKyT2Yr2SEbxtavxY9RXwrvAdzAOhWd28cyni/fPtn1q8hTmQ8E96DIY+n1z1JikbvM30PRqhvfDnQLdEKwiTq9WkaNiCrKKQK8EucKXph68bp+UXg0y8PvzWn/jtZD5qeO1tRdXq+F0Cd4ndfcRo4LPu+CqaO4G0V3xNkvO7WlmLlvDHd5gKufRuK3iSn6MNg+XVOdHuKPutC0dWh1nXvqRwEf3/1PRUVxPEo3lNp1o7UBc6LcD8GW/49lV/ATyTUBa81iGgVGYvGslpQYlj9MP6szh+iM8ioR4fTC1UnJ8/WdN2GgggvoABCm/bLaG0z0rbWdKRMZOmXwLeF3JnYYXeKLj9p/FYOdPoB/HeIt32gcvbX3ezoiOft6H4d7czK2eP6w3L2Q9rasXQyJ2efdYXIqUvJ2df2I3FhOXs1lIOXs7/6gh0rZ1/WjaLne9s9cXL22c/aPRI5e8+TpG1eh7rBc+ls+F0K7k3upD99UPR+ZYotXaKyrUfvpRpbE3r/Dum6ppKyvTTBlN74+8rOVB29L2uM5ebpvasP0em4JBm+vVif3pYJtib0ngFxfA72z9D7N8iXVmtLD0o2pfc1wH0eZytJ70rA8/Te3o3ksSF6e+ps69H7Iy2pl79C7016WzqhN0V/DfkZ7EnRp6bZ0v/tSvLjn9Sclvei6La9+PmVzLf0JHlneXG/xuf5+V5Pz3zpUc7z+XeWd/Yj8/3Mw9Jyl3c8pefJS/pTknInXQZQknInvgOk5+FjAG9ufSC1j5ns1bBcZ4wqLTkN6/IV/zY+H4aMSJPhSoAPTkpL1xuyuE9GfLhqYlKCKl1jDIPf7Ijk0r8EfDvAm2qSnEzHCQ+Ob/+Rk3ny5GQuh1OPVU4G5/dpkZNZjWnzEORkruqoPy0nM1Fh2pax/atyMpGnnOm3XwKed7Klc6uM7zzKSiA+sJ7F1myd47TsDjX9nUds9VybE56/LPiO5F98/iJclzR0/iJcl0yqJusS/vwFlycPyqMfSNGxUFfCdyu/gfDtVNYm66zKl/76OutxvVsp5AF+nYXLfwPK3wzGgflQxqel/NvHwLx2oHHNba78wWWwxg4j+y7YTn2TYmVCS4/J6HgJ+ZZd4ebH82hWXiSdeysujcVhHdthKAjWpzFIBe5ksLwOaaE27sb9wRwG8qoAOn2XSdHFU6gGx+uxsx7ceI3nmbd8qcc2XpubZ0YFk325hzVe/x30+/v7EN4V6/efowU8zNnE+v3XA68Lx2vb0aQucBxYv//pQOof/f4N6Pf/Cdrfq4MpVr//m1D374MtCKJM9Pv3hbY5FOxEsAvAhgyn6OdDKHotWPW/KDp8EllLfj2IoselkTIOy6JoFwV5F8biFYqeEknRN8rIvkPpJLKunKjD+2F87yCv6x+wwW8JLDzJne+J+iV8XpeXQ0nqbegYQUm+D704Qvp8wjVKel20NUp6fXU3Rnp95eArvU5LhbqS0lOROkJaj8pEb/PrManzmM3gX+r9q59HUpLvcoUPMZ6vNOMsPl8JVBjxFpzF+DCF9PlnPNRnnzqMEa+C/NjXYYz4dKAXvkd2mdNfivcdfQF2m2BMd6qSWJxu1etG/DQlsaycS44R/5qSWIzf4mPET1cSi/E7BfhsJbEYn8jFg+Uz+XT9AL+X84/xfLoYbwg34vn4Mb7Sx/z4aW784++IkX3bWJ1aL1gDG5FEISqYqT8adaI2yzXdx1XDNy9uH1c133Qf1/dHZ/rF3Mezj4vtg9zHFepL5ff1Vs76/72PuwTo6wX0vfDW49m3xfRtaN927JyG921DNeQb3rcdlPtk7tu+Ne/h7ttuzDW+8S61bxthsKX3gZ93p9qy+7YVuSQ/2KbPpmh8VzVGk5KqZW+rIrSpQkbnIuN5qsn7hNDnRGSka/X6ZKXKUP/BrUvAT29DH/IH2Mbe23phwYOdjz/O/bN/3tv6572tJ2U+jtNu6ntb+M27gmoZPZNv4JzB88Jt8xvep8e371iFi2DKIQ5Pbn6BjXyoqfxH5GlnugfwtP3Cxs+DgpY0rV9IXUQ9kH7hSToPuh7icN/9Ao5/g8KePgH1gv3d9bOnnZT2rFuzgNDStuT9VIXtFWbHUAc6/7xM8h7jgkXS64fgxdL3tj5ZJL2O6gL4aSI8nseff5ti3yG4wfEKNlgepGAhwS8R4XstbJgP2VsLkfrUjFR8FgTz8hoZ/ZmbkRc9XFrXhT8X1YLOq5Eut3ppw+kEa1RqjYFw/NEa0/fAa6JM+V0N/B71DkXvWNE4v8e+2zR+37Di6eP3Sy/fP7+/8TI5/8TpjII6zIL69l/G3X38qWH9fFLr5nErpdffHZZJr+M9l0mv+1OXSa/vRy6Xvjc8a4X0OWmv5dLr5gPLzfPpjd+LMy90/pIRyA8F6XXp0UmTNfx7CELZIvytDo/NLuDb9XkUfec96Kvzjferbv6b+tvq7beAvJvT2//lelKX9BlnWg/+iqHcT8t7BQsbKLdQf3J0okaDdTrl/SyjI4cY+7Q2icY+TQ31s3QjRePXAuUoFoXA/4ORHqWzupbiWT/7mhVE3rtHoQLw67KFouPZNydTkBppUQL7vhg+BVAjLP+Wymqaiud26iAshAnG+nK3NN5f9vukaf1lwpanr7+M8rp/OfRfBljT3lB3g7eQOsXp8fIhuM/87IpMsv8r2SI9Hziy1Xw/1GK2JW1Ty8mPWprqPRu0zXw4l3JnenqOJe3+aeP3cndsaxofPKj146PiA/ttxnvWj+JeLr5nPX5b/XvWmB7p5UTO1HV74+0ybPvTSQ9hu4zefv/33s21S9z2PK/LJGVHB20331aeq4H/uiLkhiEs4FwwhIbqiqEf62UPQtl7CMTKfLKxQh+mZOsYVrEPwD3Ycm6i7Ach3w1ZlYxTr4CYO8+39D1UTs5b+jhZsvRfuQKbjUybCqJvenVx43xRW9w0vji+o35//Rng/g588bD0Tbf5nqKXHCZz2hG/SPfPXxRLz0PbHZGety7bI71e61FImdc/Lpq4Yjm4yq8oSTnoZIhHipfnAZ4S3R9wBZsPeCcRHvvfW2j+HEtqfo3lCaTk7/oWN7yu889IS9ensKvIejoc82/K6AALMifqWULV02uRCu0g+hhFjy5pfLxaf7pp7eDv0j/yei2mlRjHq0el16J9KRmv+Hkttk3Va5F3i5uXAM8FKYnF85LLJ7lzPsCHKInF+MNlRnygklix/wAlsWL8YCWx4niClcSa4MGEKYnFeNfjRnwrP2IxvuwEwbcQ4a3ONMzn5Lkmg1qK0xf+JqO7cnwuO1Ofzw8Bn394uml8fqPi6eTzgDOPns+zztw/n+feMepvCVUSi/nk+XIjX4UricX4Tzl8C5F/zFc8Xugf46XGkcKKpuzXmS4+29yV0UeR9NoTm66VzvRtiHd6ZeP8J696uPxnvdLhkfFf2BIHuvgsVW++EVxZfx7aHXBN4T9z843KfzvQ7nkO9IeQ3tr1DrQ834E+9LtMksZ2VQ3QONKQpEs3ymfehTjKkLR8Jpat9PjDyKd4rYgt5q/ODaSRDfzwbVXT5Dfdzj9cfnjU/dHjkt/sdF5afvPzaoomJNcmYOFa8XvVchSDNCiTdanYHSA5ikBxaAJgsSbvNEEYod8gpEcGlMJq8cYG7x9hjd3hgEkBOFwCh00ou8+UDDFEs5oPDew+k5zVb57G6jPH2sHT2dixEebFnC/pOGEuAKnGsVrExV+E39ScD2FKpuny8ZP8TGLv+BgE2HC2FpLQRC7uMuB/j0sU7XuRomN1yTr9JJ1ckxmvYVWXwvdawXefs85056ukLcWnpZQLp/J42i1vsbgt/3udtfCJtlpuTVjL9LUkLh6KzT3xQoCYbH+9ITAzCatPj9ekAaFT2LrFdaqBv97s3iA+QIzWpMckGjQqNUxS4pMHZ6gMKl26ht8d5E1j+andQ6CHP4fI5mG9/B1oTY8AG4yC0UB2l3Ig5IzcT1Zzf1j+P4z7k9dhsrg/xOLdWbw7h8FyRGEs9ONgAEtfDccJhN/CofwTRbgITqc9j8H3pjH3CX35AXclsJo8SXsYAm4tly528/ce/SCkgW0XOI8qliMTEW4rWO+YAXxiHB8Ot0gjhuSXzyOfLz4/fB74tPl0STpZiE+bT5dPk08Hx4P5GLcSNRcC+8G5Nf6OgdxiH2kC3HC2BZGbbzw2BnwJf2M9pzpBmGg2b8LfpCch6fHp8HHz8fHx8OFhnh48MCVlYBrLHGowPeVhYOTYkQUGhYW5q9XuWWwikUB2P7ABmnhNShy5FhOun1jnjohP12NnNLRUHumXkQArUKijDC0bx5AMVvQN+aUaklgaqgzxLP00cQZoGMSPSsc6IR0cP44Xx4njwvHgOCBcFo4Dh8dhcRgUrUrPMKjJG+5BhiTWFZOYYUjjcMM1ap2G+xGTQVxheh2LiM7goCodh8XhsH/sD/vB31GQNi3IAO0WIDTpYSptBuseLHD7abV69sAg1H9sTEhYIIbhsWGBQ0P8WVxYRHhgjN/QkdjtHzMyMpDz6x8RGuoXE8i6/UJDEWtGWzmz/RUevyLBHRDZmh3LAjj3TqUT7cW5+zBOdE/O7e/jRHfi3GO8nehmFs0tW1hZ27S0tbN3cIT57jPPypxbtW7Ttt1zLq5u7eXPd+jY6YXOXbp2696jZ6/e7h59Xuzr2a//AK+XBnr7KAYxvn5K/4DAoMHBIUNeDg0Lj4iMGhodEzts+IiR/xo1eswrY8ep4uLVmvEJiUkTkrUpOn3qq4a09IyJkzKzJk+ZOu216Whs755oLJTDG5Ezb9yBKbzZOXehHSkq3isp5Lu7dwTueeDm91vmC9wLBO6FAvfbAvcigXuxwP2JhdG9TeDG40VLEh/Cd3S7sr0H7sO7sd+76jK0WnBa4X/N8BvAza2QlQVtGRgY2AKbfh5E1rKr3CtyhLUNGuDhMTwSOme5nE3CZlziODAIZaZmgrEBH8ga2djY4KfzbBD+ib5ZS9M5MKYdfZdmx7c4ldpk7NP08PAwPTetnc5BbgZazv2Wm/hC7HiRPR0PF1AVAAv5mwjZB6+FvAr26jjlew5g5428fmtve936ZhycAUtrFK+HESRJh1L06vE40HitXo/bd7yGbcZIhT2B0WSm9sH5U+EAGOJAYPB0GSz7DfygVP2kuozdYw1VB6lbGC5Q8hDKxF4rroNet/9Q9j7HeCTsXzz8em+FaTxGU5cAa4zjqymeN/y4ykO+PmunkzmFEcZ+7dByeche5lk3OaRyZE/GtGNhX8d+vWdDLDbHmOjJby5fseIA48L6L+fGbVH6M6+YQhsRXHTZFLqJ4Ec/m0KlCJZeMoUGEXQUwU0XTWG4CF77yRQuF0GlCF66YApXimCwCN6uMYWbRDBOBNuI4NHzpnCOCAaJoIUI7j1nCmeKoFIErUTwYLUpnC+Cw0TQTQTPVZnCAhGcLIJBIigTwcqzpnCLCM4UwaEi2EkEb1aawoMiuEYE00VwiAjKRfBWhSk8KoL5IjhTBEeLYH8RfEYEL5WbwoMi+B8RzBHBOBFUiqBcBJEYCo3P5vzdC5hnw1/b3OXAaR8YIFqtmryWKTn/XJcT3TtB/7a344nxG5gvO7m459e2VyBfpy897D+GgXln9Jv5fRSoMH5V68CtzNFIVVFzpUKBxrWYO/TKp0zABI+ogcMhfOHBQSlLdzIf77MIzYofpEDl3VOtX9jNlF0+zvh7eyhQdvHUNSWFTFVIZk6HT3wg/Dj7ohV7mRM2ZTBBgviy9Ya3IvYxn6zq4b/uJvzOOz+xoNk3TPW3Z4pLhkL6kVGtWhbsZ963OleUHSeD/FnmrYw8wHzTL2xUghujQEfpYbNvHmTUPSx3Xhw1AOJb+b9f5x1idG7zf1FehvzIkyfP6v4d085m1qQZHb0UyOOyrnT7Ecb/Tse2R9qD/4IpFyzXH2UC7JPOLfGA/C7/30cu479n3ppgbY9ceilQ5pU7M7r9wKy4u3Ha5I9bQ3wVuyov/MDsdZ33jL0HlD/482EuG4qY13Pyt+n32SjQiNV77VTFzP7D3q+HjYX0fOnFrq7HmPmrHd67XdBPgWrX7nM9eowpeuX23A99uyjQrdBObd44zrS9+tYtd0NXBbIpQ218SpjCiTG/npL3hfysY3IvlDCzr/kn/PYxlNdj9pyi5aXMcHc36/E3oX7GNe9qOeQEE5A8t2DXech/4p4bHa+eYNr7XnOWz+4P9XHqw7srTjJO788au7rGSYFyZVOXBZxiTnXexnhOAHq06bLm8E+nmKhVs07p5nSG9D8/vn1RGbNXO+ve2j9oCP/VQsf+PzLHqYARp3p6Ar0rLD8o/pH5vV1tr6jSFyG+zLgf0k8zu4Yv+Tlwxx8+qKC3lqLPMKXXB7w76buekP+Vq7/ddIbR7nekHQa1AnodWD/zhXJmbsXycG3PDgpU5jva0VDO7GYKoDlDfXn1Oz90TzlTNKto9extbRUotPeaiy0rmPN2g7olnHxGgYo/K+obW8F8VVSQ77Ic+GWd3c5P361gEt9b98aIhB5Qn/qEM+cqmA9e3zFj54h2CrRrd2mBRyUzZXywzuouhPc54LZmUiWTtapfWt+hUD8uOb9121PJXNpepPKa87sPso/wHG59lvGsjRtWswrz79L87NCzzBeem+4u9nVVoEPVP/ouOstsHbH9p1OLoT5i2iWvLD3LDHLLH3t4P9APvXnjyHNVTE53xx3H9da4fEdGxVcx/z34TPGxGqiPTp5xNe9XMeqcXxdvjIDyazOdj9ZUMR37exwt3Azl37eqc0r3aubA7JuJHSwg/VsuJW9rq5k1uv7ffzyl3AdZvjQq8sNq5na85ubkuGM+qE2nD2ZermZ2B52097KA+KTnL9l4hsO57pVtKNnxxvhXNzv8H3tnAh5FsS3gCoFsEBiRkUWQRoEAISHsAZpMIiEsEkAI+5L0zPRk2sxMD909CWGRfZPFiKDshMUAgqwucEUHVK6ooCxXRRQBF+QpatR3ARXknVPdPZl0MoSn37v3fd+lm59K96k6VXXqVPV0V01Pqnrq1q3Y1GtdetVa0fDq8puBkSQcP0rpW1g98tMhk+n7N02mn4Fmbxh+kP7QrVud33A223i2zju3NA2llqjq8PkTINVrqQS2Usu0anr8lFT1E9WPWgl1xSsOaWGqlkavAdGf2wzxeRTBzTP0laZMb0kSpRhcF0gfhTBu3i1KhQwniXD7xWRzePfEMQWczNhESfLBbaQdYqcxeNrF5HOSwFldPI3gk3k7Y+UdosQzgkJPCR5BETiXMImmMuRhVApbGmPjZIVRRIZjZDdkzkuMHT7IMkqhl2ecmICj2XBQAFlmRAcVJzJMPwejOAVZy1XhPfjpnHPBPbPoY2Sn6HPZGTcn50EsnpFFn2TjMTUe0SwLBMVJjzivVxLhVphTeMYqKJgG1GeIEnzo59xeF9+dYWJio21OTmJsTE+mlcC0ZJImZmS07hET28vJeXIFT66qV7SDITx6uaDCgsvFeESF4RwO3qbQSBN8YB6lUC+LxMs+l4IaRLi/cKPhqJ5E1T5ZECUf72wxfu+hg2l1UaOXzm+4ChmZy0fz2CQ0D8c4fB4bWgIq6XJBPbKwLAK2FeQL0TktR9SHUTDnoFR23ubCH7xXzSN6+EAkm+jJV42syoISeUVsAMmQmGPsAlRbgkSVKNHqd7me2XT0XrNpK+AF0oHmgP4MMcyA6k+asyrUOJpDxpG48g6WWGa/QBSIA7aw8lgW6lZYUtGnaKeCvBdSQ79JyCrrOBmc4PKBpz/Uws4kMC3kQP/KFO0+0D6Qc/OBcxmCi/fgCW0bQp/1JJAsItDnyAzcgTvpszB85ptBOPo8DZ9Koewh+vYBBuIz9C0Fenql0tS9IZVEn3kmkhgSS3D9JP4Kj5U+uWbocz98viiAJnVdZCEcD6Fv8MMnkDx9Mqn+ag8arZyN9QEhYFZCBpQfCcqNAroBOe1euVz/13SgpJfW6/U+T7s7dnVshuCeHtChO1mQEtiu1DebDgFbgSnAWEAy2IoP2IehbZFF31o4lK40LZPFgu3wmVw/MpD0qURC6PsP8RcYMEZlcrWdu5Ak0hF2PIvtl0bfT4HPWfF5q94a6u8lofUxxwHwFz61ttNzDqrXTeM6aavhvIZMU7hpq2L72am3qO+9YGh768/vg3WhXKAS/GVWgUzS4uETyBj6hFLVr66cxTkSjpZWzZOB3HxUP8rx2bQ6A4EyL/UlPYWqMREk/WgtVa1uOCvTY4yZR3it7Ar1XoZ6u0yf72AcEWrOUH0uGl+tGUdz1u2UQNRVv16izstgL2lF2sFZF2hrTa2HrW8LlCnYnlijipby0DKi16jPyLF+6v9lKdNpmfCps0Drqbe53t4dAu3tISKtDU//QuvhrBP2PHU9MmpVtbsgVGurt5QqUWek1NIb82lfhV9VbG91BFDt3Yv2erVd1JEGJaqFMTcsX+L/iV8Y65EUqIdeJt1uldXAbkjfgSQH0mNrG8e6yq2ANsDyVeyvHUjXP9l+BbSGt+9nleXX5U/kh15q/5P5dQ7k5w1cZfIhvkRwtgR1VNZz9L5YplHX1+lPlD+basXZVyx5O82j1CNsOb0VK5a/PelmaO+wztVINSAcqA7UACKASCAKiAZigJpALSAWqA3UAUzAPUBd4F6gHmAG7gPqAw2AhkAj4H6gMdAEeABoCjBAM+BB4CGgOdACaAnEAa2A1kAbIB5oCyQAiUA7IAloD3QAOgKdgM5AF6A=
*/