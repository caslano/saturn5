//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPES_PAIR_HPP
#define BOOST_COMPUTE_TYPES_PAIR_HPP

#include <string>
#include <utility>

#include <boost/compute/functional/get.hpp>
#include <boost/compute/type_traits/type_definition.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta_kernel operator for std::pair literals
template<class T1, class T2>
inline meta_kernel&
operator<<(meta_kernel &kernel, const std::pair<T1, T2> &x)
{
    kernel << "(" << type_name<std::pair<T1, T2> >() << ")"
           << "{" << kernel.make_lit(x.first) << ", "
                  << kernel.make_lit(x.second) << "}";

    return kernel;
}

// inject_type() specialization for std::pair
template<class T1, class T2>
struct inject_type_impl<std::pair<T1, T2> >
{
    void operator()(meta_kernel &kernel)
    {
        typedef std::pair<T1, T2> pair_type;

        kernel.inject_type<T1>();
        kernel.inject_type<T2>();

        kernel.add_type_declaration<pair_type>(type_definition<pair_type>());
    }
};

// get<N>() result type specialization for std::pair<>
template<class T1, class T2>
struct get_result_type<0, std::pair<T1, T2> >
{
    typedef T1 type;
};

template<class T1, class T2>
struct get_result_type<1, std::pair<T1, T2> >
{
    typedef T2 type;
};

// get<N>() specialization for std::pair<>
template<size_t N, class Arg, class T1, class T2>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_get<N, Arg, std::pair<T1, T2> > &expr)
{
    kernel.inject_type<std::pair<T1, T2> >();

    return kernel << expr.m_arg << (N == 0 ? ".first" : ".second");
}

} // end detail namespace

namespace detail {

// type_name() specialization for std::pair
template<class T1, class T2>
struct type_name_trait<std::pair<T1, T2> >
{
    static const char* value()
    {
        static std::string name =
            std::string("_pair_") +
            type_name<T1>() + "_" + type_name<T2>() +
            "_t";

        return name.c_str();
    }
};

// type_definition() specialization for std::pair
template<class T1, class T2>
struct type_definition_trait<std::pair<T1, T2> >
{
    static std::string value()
    {
        typedef std::pair<T1, T2> pair_type;

        std::stringstream declaration;
        declaration << "typedef struct {\n"
                    << "    " << type_name<T1>() << " first;\n"
                    << "    " << type_name<T2>() << " second;\n"
                    << "} " << type_name<pair_type>() << ";\n";

        return declaration.str();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPES_PAIR_HPP

/* pair.hpp
EWZ7MC5yQY3RqYYuIhkLVGeGY35iq0YRNHz/2er7Wmb80j04VxNAY0fh6shaMXM8GdouILe8WcLVO6DcqhHZA3S/VLrCyclnJN9pF1KcYT/eTtNe6IVTFyRa9Yy2Ujcw7xQ8CuWUj/zSV2fGmCQz3VRXrdR9yuzWF5QxcTzFH6vUsfbUKMJIuR+Mjs2OU33v4PqhuIKtWFT76WwjeTVb1lYTsOYRh60B60Cct59gTNHNCZTWK6jqn7f5GaxxdC2MtgZmb51vHOi4xiZb8coYGUY8HFGexQrIrIFbpeOiSTgiq21Zbox9ooHgOCQCva1sEAKSCwNFTgX4OrapRuv9jnoMTWbANpg7hulbNOWuQ+YrbhKUrEzx7WH7qiBw2xotKWXsKQjnGQuCDuq/M5Bfx9N7CulqLLhyIhsh9isse4LqXP0Oc2Yjx5wbVietvz/qai6FAexPU9A/v+UIixMg58WpqjrgZ7VZljKTPxmcc55yb3lVfglc6kGvb9HNIoY4NNtGPYKf2jthXQcsSDOOgfsG6aXVeEKpWiAe/H1Z/rssz/R1l2RIPSXO+CxQ+xXiS4CLFi+SpAYbPKBJbVS32tmMvefvzVlejOlF048oynyWLpCBtTcNjYCZmzxlaFFEZJ4lCzYMg9q2qZcFPUsNaae2BKGyJY64F15NAuth0Bpj6K40F5iwd56S6xUeIHAmC/CMBEhLf7anIAP6H6yRi51EkNKV3qRGapila2GB+UXgN3eEolB9s/Mi4Mg799YgaCYolKSzdca1PC83WEynQP7yqQz6YEQrqQQvQ/jUHPgCIN4CZPJ6eHKEEazBZBEgNB0yqDddV2IdmvYRnlZu0CFZ86VJGydxE6gNnYmJbgqVDzOgcweWs0lv3Im6016/fHGk8bC+d2Id8iVHglnnv4cU3o8VP2A9mFGdjx9KahCzrxhMSBP5jVYkEsskX6SubyJe1D5vYJwIrSBbjKRZRPjbBPtRn++YKoWnNkG9vy6DRC3htEWMmCS9EGBMRORsoRrXcJ8iVzQZw3Rr0QcyXTI8Hcl3l5M4gCFiAB8J9dcRjKq8UVPIN95UY9oCo5YMIaUIUn6HqB6hgF5MQ6ZxkBA+Wgwyd99DfcYq2ig492DI8DcElgNEyhy0Y6LXpxDWkuQ5aiMI7ByIhZH26AXieFEMchQ9K9Hd1/Rf3IXcz8brZ4A6ch3+HHJqgQWamWCamkOZikOlR8XZMsXLD2Cp1pav1xBMYrjEHcAPMIAKJyVMSjLZPnsjv41MPV9OQyZyhC6GqI9Bafgre9LkEZx1KbbOczRXHEBpYEjL8LtPSQt5a082tVg2h4JXBG/lg0ymhcIFUWaXXqg6eTPDLVRgpY9zj2SLoY/NbXFxP1KsBRWiJkqfdRx3n/DmSnyH3p+MmQwgTL6/P4GtAAnkhkCABCzsibOK9HM+Stp54vFIgcQOrgPptuVkOihseBXwYg0M+4tsa8hBY4FiSyO9Z5FWnNBs3KLSFsURV/IERwBTnlRVGWk1CbJJqGjkLD2XCWVD/13JNXQ29F0ZeYlLqBgxZmgqp/4dcZIieVH+ZTKeZVUOfB30p/nbDHPeglNbztm/EeIuxZQ+mZreayqWDjhAC0NS5tyBkOEWMHLT/j02aAsxZCvLrElkT8A04YSAr9SOlehvYWE3A5IODpM5akhTyL6H83z9ogHpYkxR6ryaIuVhpCBqZj2fnDPrGzh4Si2oYiqdmlOVs7gfEuFPw0Yh0YXiwBOFnDAJ8j53MORPLCrlkRFuaIjAwPzN+xCBdNBQ63erp2+bYTVTNXd94OkWXkdF2sIBcEpLjML5Jk/gDIR4u+3UGQNlGQZTeAbKkQVlcVNwYRWhMtI0+2MmCQlFSESSGE0BbGdh+BlEEKwHRjtlEEeAaytxglczrL0sqpsQKhGqXqWcoXVo4Fy09EmIK5E/GaQ//Y2mnZY6ZGZfRd15ZiwtZHnpNeaEZXdZecWFm5m1zjzFnRKhnLzxgdOpCr0Qs5YYNjLFPM8+oQwk4fJcntVQ630fsxpYd70WEuRgQc6Qw1piiQwVN5YKs1OARHgyYwU06toAeuDi9z+RDENLDgtLFanW7TnWXk2HfIm0nR6zAl6nCDq5GUJiuiwgCTikIERuaulHKl2AKJKeVh+clZlFMoSdKNFSPOdJDNydfz7L8voe9E4KtZ0vSlOPnNneYfvU/NBEuPZTQNw0hR2goBPxkDkvEP3etrOkqmxBHK+lqL3hYlIGxu4+xKYtJnhHhkfcyCB0aKhJuMYkXQm6/PIInaErcRt4KBUcixyd6LuUPk5eBMCflQmHG9rPMIUU8goIloiEnb1HEemaVvsEDiyTdozYrQ+U6dRcTlTYOWdJEFQlsQHm1BImQDxV5AX06fR9wDy9PrBC+3tZgjl5raaJImqGkuX0bG0GdkztiJ3zl8e4khNJUydwIm0obAZJP6LNp+rEop0wZEjQ2kYo46bHsM0frKmc6/aLovQ58Dc5KlnlY/G1wOnXkAgwKJCnP9wZ4NJhdZfX38Yfs+UEYZBzWYhXv0MqeFxLE8klEOlYAQSE+L0EWFFQoKUmw+EWVYdTQuieu3kSiUXDuMhxuIi83VzHeqNJOyup1b/LbpEglKiW/ba+xmw32FMRkvuEgk0ZaBYdWfNNFHJuFuxjGA1y9+7E4ANuzlfARJw6B4l2Ps+umMr6VNPLnqdaPWQjyeFeqCyWEaaS6e9NPJyf02vm9Y7v0O63IHyvS2EbfHYjUSZuf6qNCtlgach0oa0Nkbs8EZDauUxT5AJtqJ+c2nMDWt+H0TDDLdAHtEc4fjfMPMaQMjHbpGBrlcmglH4Sw4wdd7tSbI3vUYcjCGN0JUcSXKLWPjNWgma63MeGmarJk3NtR4FdgoweqHbIATZ4k0ejf7UHZYPmajQgXRBqE2Wd5ZQBGQv8k+nrW08aZTNZYMNoUQ9be8Q+Bo/7V5aiTmjj06jtSUSiCR5jFBK05AQQEg6vDr7CuznnThHzJ+98vLivj2b+EzWuRsEWHtgTAMkoIa9QEpxrXbH1R/O7uBHymRI5DhscwcPxTkoLAyub4Oju3wZSAeOAzHnGvh3yGnGbIb3NdVTa36hAyG1SZOo87OKQIoST89R5biuga9TxTTacFQRhiRIBFKgA8ay25DqQ7U7j86cTW60xmeYUCww7uSIDppw5tMKhaJ+CKUBk4B6gLTE8ZFEoQCj0gmdb6+WK3fInvqPBGRl2+wRG9DLV42aLjC4GDnUCmVuUy97h8gnnknOE8Uro+OSP0GoT9g+FjQZzwYcH3SMkZieLpDo5BCyL2BM9vcfTzzXn34iii9D4luzBfV/larJHGagbIPUh5ishgJ5sKyI4QtN4HyDQDzJB9MPaTk8q9EqkuYVF8bbpLYXxHO5RfrZZHnKkx6lC6SIy5Bn+d7w5588wVocgk/htC6VTCUmKSU88McDU5uOkn10QwzhaS6KU45FLq9aEW0LCNg/W2xjInx176/kNnQbu0ouUTX+SQ6fl9CmvVrf1ycnqkvZ3ZHtCZDhtzgLeaO4+Y26q7qWTZlUPdD7FEPKdf9X3vq05pU4eh+ID8dZwEZ945O2MedM8FbrSbXbw+NIxcJROD9tejp8NZ3A5LfKFpHbNgVhfMRSrJ/aZcwirsz/cGL7+RPUKSVsoSdeop/p/6BPhcmEiDn2kh3YDURw5az2ZyzjJ+87Yd1USoo8s0iwbE+yRYsy/WV2nQ8pHcYX+5mx2dmZ1bQ1THM7Qr+wZs6BsQEL0vWDfu9bwKZDYc6yuavAAi0cKHYEowygPWHLQMDEs8/zbIl7M3eeallDtrmoWrJrcAEqYRKygH1IJ0YWK+/ES9rAoWEpro8lDLmiFXNUQigXbFmmrzWOpHPwnVUaUGSgaOCVf8ocgI0PL+nat0voa8LBNlaBg4jyhSuT0jnmUofUy2xcLIQVGP64cOpEVqusVmlTeceGWLNqu6RaOMp50745zlWoX1iQS1jmcizX0C6IN7884pX2iqDLOTj6SGk+zRKPiHTeAaiwaZZi4vYOokOkNNrNiMrY1P+r2hr242kqL+WHH4dt0uN4rC8cpWB+g+hucKkOqVukMvnuGo20yY7OwBkNf3uFQLHZHtSVfJrzW6vf2qtG3nWVM0z99pvZ/IdBnZCkIBR2qdPfmPsOHeEGgsfs2GNr4aWp7mVQW746yePY3BpBIqJyityA089ddfEHQe+smll7rSb7te9SzUnD8EzJ/scglAIiKCAatIXaLikJRD9McgcU8+G1Nn2bbq7ERDcFL+82IldVsOTMM/GtpidHUe3C1a6X82Zu0a4aNS4ZFjDCzzepy5Td96yF7q0+4nC89H/xy2aUId36+CHPwiBXA8UaNdp7qYwZhLVInLHC+a3X3p7wZDdUrYrLUvb1KukNmsLB2hwB3GSciOCpht4+9h2n85iQkYTDoIkDqM3WMuGoI7qYL3kauZTqoe5ANN8zy+8osVNeEibr8Mju8ItYtOKLeZ87QuOOEEBYhSDorBSH3ObcDMK0E7muLKBLoryVVLtZFJ3D5Yyc57XGV5KuQRsHmIyug7k/75qI4+fFhO6yk209vKwhUflFqhhTfK87FpKBdmULU6i64IpnyfZcZXL/9yS8Zyo7W1q8Zvq1dMFFu5A37nSRk5tpjkjAp9v67uNkSIONICUJIOH3i78i5Kt7O5Uk9hp7nwrNL1V9XEEMJSpKwyPRSSkCRIDgUTrNXJ2OxEAwimSopNJMKa8k2ofwQGWgGF2SPeHJNFWhaXV7A0wJYMIZYNPa3UF4nMx1qYj63pbPlqNU6/U4AWIM5nbkUHrLEDt95Hrp0OcX4vMoFQJsIBQxbrlNaCTQlV48zPkEvi3Gt1Wi7mKO+mXqt2+5wPlKNgHOr1+n9sLO8qXki1A8Hg0Pps+ZkMhSFxSVgFyiVrbSKq+nhs+5iMfWb48fJx7qr1VyheBpljBd+HWy/lbQub4PZuDerysbBcGUoYm0JBnGdlxFqFL6ANwuBhW0aQ6GU8ILFRHKW6pqqtI7+hb9sNqzeDwIB7le+28WD8TguQ+JPr6fz9dofu371hn99QBX2R0VRmH3vl7Ont72CbwBCpT5wENtdrVImLBBQpOUkVOFdRAqDBaO2YJyGL9dXjjUBuXFGuovMDQzLeX4t5xby1B7Hjs/0vi5fKyMor0iWgt8LgG3T2gPBoonyoI4BgsidpCAjMNHHyVLYE8dJs5Mvu6m9bA9gKUWUguFomoMdJxnbPxZkmSSvxgbiZSrIeV3G8pFoNkPBRQiyYvOuMpU48aWGIPxxoYe/p68fcx7HykzwwGUnKo2IVbsCYAndj+4VYvqy2OVkGKoxF2U5ppcmKXIhmaskpPoCwxV/y/1RU1TmSFlW18++9eckHevHrhTLlJHntB+cxsM44BdB5Ld/M4Kh+8kTnGHgYSwhvgltryCCrxipXFFmU4UKS03sbzJK3P+HedlJVz1Fz9mQo3XLeV5fU1+BS34MkhW4dqf/47oaZ9d7sEk1T2nDCBVLx04ek7Yy9sAcRK3rMncCwHCJzw8188aDNg6Gqq5rL8kriN2TqTIJSCUkXfMIgJIQk0OceJxOO07Rd8A7SeMzf9Hrw382ash0V/hhmen1tX5KqfotPAqWtlwp9NxEFaMoSD34hDPPM6BjvVDoDXeAiHZ9n6a0TQBDpJKWvT+Il3A/cMLDW4PAqiXIg+Cm+dhBlz6j106LNcV0Z/Om569DOxw1t/U9R2JLbCzNaqzOlrYuunWSUjFPyQzYpZmVKF3Nxtj67QzomfBxVtww42bBm5zPcvFQw/emVdcwu8e6Lf74ohhWYny4yOVHrERseYiCHQzzbk1lWI9L9tNRgiHx84nhr5ynudkgetDtfHXa19sVVyNbMlQe7IkNXgBz1uXOtCJbSzVVrQ8NsG0sgY7YMZPyeKepl+T9436XxPt4uZtJcOaB5DFdUggM+hog7yRGkDgQWOZj79JaiIzq4Y++UQfEvXWF/NH2QoaK5eT/DXIfFkVLBCJnjuENAimlKpgC6w9KKJMPntPGHFqKljktX54R1I+yQXgVSZEOBOjYmZVgbrwThb7McETTNTFKgfmIM7T9JBGOCpX8+GAt9n3M5lfs324o8Dxlc0GE/mVEW4WBllWpavRm+fZWleE843A51ANMjDssUZ5bJsR/2yS/hNDY7jM1PQF4wyLEDWxceFMcJfMwjHmkpmcgUUO8DFJO4j40e/u7VMfHEilRP/SEfMhj6v7FUddteveSJVMczXWZTHlTMDQnoai1F8JivXgMtDKIH4nhqBoV6Ol+H8XM+tJyb+ELzJ6HhDQZEVMWzyXe3KwBMm6rBZzJDAC9dImsxDM5R4GH3/tbhiwQwTJOeBjZg2pUPBFFeVCQRmYonv4eDTwxMYRxMpK4G7xB47NuDY25APcc7vJWOWdizKx31QwBfu10tTWxWNdEahGazLlIgyUV8GUEwNOhYpwNZhEY1rmg5Nt8Ymhy0fkHJUJtMkVUD2YhS8i5nLmOamYodLFJOWm5is1CzglmGRXWhWLYhWohNAcTZAoOqNtuY+k3L1aFYoqN2vcwtej0hzLx5guN5g31Aj+OSqPjio2hcrluZfcKa/FLneUNjZYcyyrYfhu984vlup3mGpNmW4N7HZVAiZE8B6wrXRhdrQHilmr34zIDvM3VkT9YDd4pV6ZUlTMpGuXF4ctVxjyd2rMe2KHO2+dYZLLai7zYzcXy9ubqmxsZ8InleZ9Xdua6uhs7Hiru2XS2Xt46q28trZVQN04huq3Bmcst48PXLimbeieBEq1lfJbOv2S39zRwOleXGZ3Pn1cvvq+270Pdeg4j6AwflBauH994VHcavLTg9Fwsr5vrnqn82Wntel129JOk2SALjyy9N6/1gQPxG0H0tvYNqV8A/3YawnDhDqD4Gbs5c25DIuD2w4zchTJtGfcSr0LuxtyFU8iZYKStOWAqmIdqTxkjebcNM3vUM3cTaGHm4o5yrTjHyrruAGZwx1ix/0RFEB6S5sb3ZBzfx2Z0mVFxtSeXElUnlBMekaG0T2i1uMRjE+pSC+JNGWK7eqnb7dPl8kxa7fzJbN46ySD9MeWM/JB1PLXC2qg97aDwkHM/dYqw+lrlhu2WDaNvxWf7o95XoykHJ9tS8v3vmLRHfj6NvJWs5lvxFxSzNcm2ldSvjcV8CzeFTjkpOUP85VKN5q8b/guFTvylOuynSmuNFdRNz+V2hacad6RGkMYi70pfjntdxHe7OPCO1S4Nj4aMbBqSUs21hlSPpnL9K2tZsYVn++eWtG17hyTJRY0mj+YY32uXpM0tHJqn1u5tB4/eTZZe4peuWflbt0KCXdgQtq6/1w6/funuPGG/dl9n3wYgEKyDNDx78fzOLXEID2DiuPspek7smAgPkVZf0weJjCJ/be0Bcz3HBD/k1zJ5D2l2XyfuCZwSND+OWaj+jh1a2KJVEp7Sr/J46gu4pr/rnbCDvBQxelwLTwnP931f5zKIH0sgiC5ofSllqbLdKkmILoOvuUtDbtxqJT/P9blWO2oNnqtyt8u/47xvDO481zZ+SnGONq+fx3p0/jpUvXaAed98Qn7pJis7c8f5
*/