//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/remove_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element equal to \p value in the range [\p first,
/// \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove_if()
template<class Iterator, class T>
inline Iterator remove(Iterator first,
                       Iterator last,
                       const T &value,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::remove_if(first,
                                           last,
                                           _1 == value,
                                           queue);
    }
    else {
        return ::boost::compute::remove_if(first,
                                           last,
                                           all(_1 == value),
                                           queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

/* remove.hpp
/wPbyhqn6Q7z6ZUZmze5Y78cte8tSnRHBRUkjOgZhxk/L/N++pwWD6gGmIDua4ptUXWMkIetphXId0zMD9qIHrpcW+HjgGy7kx4QoUew0X12LvVsxgKdXxp8LqPlbWyJNp4xLe13Rkez0j+nxQIbXxZOSpkigePXKZhd6xiee54knncWHhtKe9fW1GschbbF1YQsBnC9ftX9cv2EiRkOULxBq4VAZxNiTLjutMQtYgfSBbJIp368eBjzc2fDEv7Up3Ujq/cOqKE4yIyNTBohtdlfMGkiE94UVIAMyodp38Veiz037rXDzn/jU9WIPq9CfdMjqhsmpra6qGL8pif1Jwd6gngBA58it/yFGWvUBv2FuUMKeMe4a9gXgg7bzSJHNoR9iZJqBhU5JXRKUr4iDpplIgM4ASfs8bevWtIJzbi7q7+2g9iAvQBArklD65YYOvO/KwVChIEPKju+96mOatQUfrd9HcDY6u1xKkiMKvXzA3Dhb6r5PXPrkDmLvrbATPAIhb8OcHSO6kUuyOcPjkkSQc+NGKm+VwlbA/6cMV3fcjP9Zpo7UpUdewBphp1JTvfcTe1RMtbf5BLg0RP+ds+sUnp6eX8ad76HxmYjlEz3fN06/40F/eEkqvsN7AHW50znHP1mjSFL3wSXACvgQ38Pf+GMFJT6qq7iJw3gg6tHAfFOFEH6d9ULVIydsCdtUZNn8fsbeyBcg+SFz/dw6kowfjASXx0UY58aAp8znA/k/J4kAwjTzYX4STNs6AvPyGiFCzRZI8FRwkTQDbBGqZQxlvyn7MuzMCn9QSjl8ZylkJj+9uwPcoGlb2TABdDgJzL9uSL9cj2TVxUzwc1lzMyFcHb5nXhTI2rwyzSwJ/GZUy1WHZiFV/JSQEdd8cwnGA/ldv6iR5r7d0g6jETlP9uJVWjwTRKh1VdxgdiAYXQH5oR/oBhJa7NZfE7v+VJW8wLNGCKfMB7cWC5p+kwYjV3DenjoQFqgFgNDXqY+iwkjdbu+GSPk09t5yy7oLXVUkyg0PDEpQ/IYnv3o9PvDxw55ZhDAWak+X49MPkqIn++/7Mu2afaHjUBQOtI9YpY43CFU93wJ5YBuU6K7FEqjkxLq2lRvvAIQgC88EzFaTekIBM2naprrOlYDpALUdHcOn74o7CYwXOYeUD4BjzIi7719bH8MwI5X5WyCYYJANOpB+/GBbbWQ9JcT6SjHOuWE0ygYtPwDye1HeFFDuF/LisSa4AEdYDOrGAtEzxtYd4UQ9EyiUHFE+ykGqBUw8xeiGvBsrwbzZ8D5Mznu7UmcMRWrsvKTcSBr5mhH39P3TJmrie+aydx3liNyBUcDjzMXpeaHZzA7KsGCw5524NsW9PF8ZwxvKy2ybmRdM710ds+DfC29AT4zVlI9NzzabalUuhOviXfctWuHx7aAEaALbz28t29HZDHQfV+nN/XFX7L9XThtEt7mxCA29jvj8Ea6jtTMpQIVVYYGvVAX08fBn5gXD1AXAaeg+tgpRw0ptzeo6mxC8KAmJswcrODFBogwwII53IRgfDbmqL7W3AcIHa058IZ3bdyIK2aSlXhDthV3n+EYi1/fvypRoe6njydke9uQJ8BpfymK0oN4XWFH2Y019j/puK16yVt+2Wm//unP5J2PvNwUM1fOtDuFwD/dcbxDuHL0od1su45xqewbwdgRA3zcEjxGtfp9XvGKavMrByke+JJakFBej0f1q4FtKxjZqDqYi5sO4Bs1XFs9YZQKFYAG8sUCf+KAwduhrlQpGpBzB9K5AYevQdH4i38Nt47/PCKNWPV+zBdPSqRWOMi0MvklRROtG0g91sA0aLVuWUohlxPuXJ9mtvfq/Nj6so2b23CGawW/hUPnq6hIr0JfvR9+vPhKP4MWZLfDaafIZzuifQFx4ZkA63mMn53zIuZlkeze2JM8JJ9CDo/2ZDdhLQdkcPIIvuQ/5YTC0I2XbwhvNaIbeCvccE8e/M8cdrX/rUFTFmFpeyJ8LmC2tWlDmKYyFKF/yrbH5ZjP+1Hbtgif8v3K75860zOvRoxncmMGELpPm031a55RoJ+F9lRHte/d/X2rUHAa+xydcjsteBuJgzPHRLRViX8JHLfw3MNhFndzHtgTYT2Yp49P9xnHNdn+EDfoASp3FdPZdwBdEB1xfPZ6JKcPk71L3NHFBZiA8ZLiibWnT26lMvx14OYKc+6Hd2T9veIWVu5teMc33sNpgT/4w4fSd5DNCo+/m0oemK/mY0RMZXthdhFTFrAYmAFJLhCx22kAZedvSUWvChI8wb36vCRcriK5bTHGQBmCvyJWr5VZ2seoZ0LYjS+BXo9YtUbS+yzLh7jAJPAJ7TKAuLskZucqNJjMySAaZ0NjRJOyNvI4JDbvdMeGiT5LBI4WHmLtcIG7S8bbY5a09sjw9g5K58gL2Gl2orupbuBBtxg1smlEbqzfpza25rsmwkvmvfee5X02fiunLvR8LQfuMdNTsFxLGgLfEADA97eLjrfA1PI3ApF2dobtpM2edbZ0k5mPu+H2YStrWwPrRHN7KKKQnXO00alQxE8LkjE9PEpplNdECNI2DyFeKumkwu/Ydev4/pRnxM/fd+rdU6/u2TPfeev4ie8nmPgiWcq5byOaWjF/wZ7bbFhGVfnrF09VZWUzlzi0RiNv0mE4TOVfHm0OERdHWBhXs14GOZL9kMf6xgXg+s9+P4SLrbE1y7D4E18x6eNpUNpIfueWuix+k2mfS+WnhcfHCHOqDiFRVJUNTig0LK2IAplTzdG81TWOp+ZCjkAl8HE6hV9dBieTZjTBkAgkvYFBkP4kyWE8NWy9pJn+uzF2X1BpTC35A6ixO57kFvAUnE39eesJNaEsyf9izVIo5OiMKxQSzIM2orQTP0MOMT6hqyPEmWjB1ESI2/lFKwf75f+g8cJRcwkr4qMemv6N8rB9XUF+YrFsKvztnsYmevSuSKkHXiVJaGxrXF2/JSpoeaVlD/DGmJSNbmxqmtczG3agxFaKik6QSfByo/5FiTOnnp+aoAJqCfo1D5M7caflnnV4GNf1BQFDfEetWQgdxkRMrJT4QY0lGit859JoUulPyu56Y9ld/llIARSVlxPw29KiiEJv3IEWWUvjFKddZdnTApD6hCc8ZK1gGBbFqzDLrYxzKt6yqH7Da4IC+g3uLK8c3R7DmtxQSXacqV/zWE+1SWHKNoALSoaJSR/HmH29bIJJYrec0v8KiwtfD7XDBmujrI1ykz7P85SO0sagpd0gf7dDAX4KMmoggI8PMfgbzkvTqVkG3NJZit6ROSAZSO5wR+SyBeSw+s5H0ROPdLGQT2Xld7LDOaGYBqwQqN8SlX6Q+W+u5hGesfOtf8ldVRs7Y3YS8Ny/FnfMi10eJTfzSBWuwR7tRkKP263O9bwkJNlpz0grKNCb+SG9Bcu5hjfDF2vZ4szNBZ00XOeiySclntIWQo7UHIi3GGIcQqaYTjb8YnAKhx58hfh4msDvd1ddx21j/0zxLB9g/4PsxSuialsYSFApPrw3z3M79x263Be8BTvEkRtbhm9Hcxq/8lJCusd0QS9gDGDbndGxRVrOqqFNKDTHfHiX6YbFJzQNdKEHgT+2yLMjf9dEGmgGDEPLcI1wZPr7ABlDyEy8wjbRgWSyz2FH/F7clyevEeMtkZximmZ5DdgboWRcyxJetN0iDhFszZ25jAHjQN6pYyo/c+OesehZFKwIHwswA6xRBGeZDiJ7SnDtaUkkgWBbttHdkp0XSYsmsLWhJcnLkn3WfqeDVEyFOiVdXGSyiH3TA+Zw4I0yssHHBNONCGvgqcgoUZJKapUoS/cxtQw+5E9NfLqX7jLai2JHR9HAa+dLNCSkXSqQYC+y6GFdqoaKny8mbJjf4LFeaQ2w0HBFwyW6Y+G9AMHlYGNh9kUYB784g7+1gorTS4o7hEW2jvB+Pzn6clGZ+5mPh0+pzozFuFdLyxnUpTHDKMRvY7n4uD45VzbpL62MbnVsj36dgVC+c4z79TPyvmfOYEHl2hOUdDhraxplXwIEaAJSShQJsO6JXMsKXUlgnDGbaQvoiGC90oTvm+vOChjMLpXRtGAU5AXYixWHIX5LW1DcLbdO0ra27DLdSylDzgAp4Ab2y3qXUP+DnK1d9itHqNKUYIJhHmJuaWXkuNrnB7PmfpFnvp0PW5tTOBTaP8yA7X6HFcyDGp2X08Ccf6FsF5f+I7dJZrTT6J0q+WlNXbOI+5AGg8VLi0YcEPwKUSWKDfQPVjkzTgpgJkt1Ri3u7FRSWTNR4zpTeVExwteSvmC8JA3Bir1QWHHAvvokwmksr+r3O5OFzugqGpQUJyX+jyi6s1Y7GErJkM0cSue4KU4T5rl5fY4Q1vkqEqOth9UjcPRja2UOMZc5x5tWIt2Q8JkN/fMACnHql4orKgq+Sp1pZdXTYYNr+KuwRh9PVp0UX1Ja4GozFaerin2BygyxIIFLCO69EG1FWhKWSSyQHrgDU9+lh57NRQ1TGe+xp6nxlpbeRMZfHs1WJCRPiandXifjL3KcZEGU9fSwL/kCfoQ3evzS/lZva8vHgCW3vSG4gbfn+vIx9LXE1aiqbfkBbJDy0JA5v3c1d5Y/m79SHRBDKBC7QHe1cf7SN4kmswQ+5Ep9wz3QzGzvheXP/rWSaskYJ+QvOS25gKtHM5COYrCzo7ScHgBY2VKGKcvDFviH8RNTXpGS2c6VJIHLvAmnd3QPFYcmmFTdKTMmhTTFBImIwdkwaZklKyJkx3CtmiwskRFj6EY5GSoJs643jLIBVrlKMamPyLyLTVXxPQ3bVLqlegCkEClVYwehvNYSj+Gm+9ngL2gBl8SYHESrGnuk12ltWCywhwSzlMsa4wfg4y5yjiCmE3nAfBl45bqgZaGpxE+Go/TCToTyZkSr6eTaN7lL6TYWkQ4id9G+SnFYKr8jxeJ6RmdROJcOSceX/N4DxEqg3FiwYxuLiMwiclWUYNEJgrLAzjJJsGeC+Chb8P7oAQ9Cjy6RrHm/jaA6l9vHHGSRgXe7YorqDxY0AZWUHA1QSbdcvi7APRMs2coDhnBS8iQP2GuoBoXI4I1nisT/2t8R1aS7KL4H48N1EJ8g2fAqlGw2oUcUKyQBSPcgas0B8wNZQDt8jZ7thxtd7Ajn85fUM/kQn1DhFike6mxAKPufqBeTGEXfIMizkHBqapGwyLO/KZ1nY55eHuG/U9tO0PIOOrk6dS3uMEnC70jc49u2K+3CFfSt7jgpvVpkxUoVR5tnidYU6ctTLv5efXqDXAA5YPU9wxvhj7HJ+/+axsbS+MY+GRZoizA5CQbevI/kGkkhO7eAkc58A8ZzS8C1WCt10obgghqVEfBBUELx16XL4gCNvZ0sdbKEPlsRZ/Fgyk/wQw6WgIkJxcjmS0EP2wQOSXtK+KqS1ktoladtcU2xY/iFLrbBmohkOW1KHDc8JnZxTYuTuKHP9rstFkmc7Oc+jwTn9mtByXIV77gwo5kbyngC2UxJH+Wy/pMs/a5s2gQqakkTYEFYcO1YHrykGWbgzASbACpgxRRxXWn6mCO2jHmJO8tbVteuLRfaCHENcIGfWYXw6DWkxUsx+wnSevVeGqRyieE/ro8Le3Wm16eMOVIq118AukjmP7aMPSSfqwu6sB+D8TS7weCmKwcNTCjVcy8DCs0gFjwEZOtADvh6gMZfUKAlAD/LcEJVHV26Dl7/78SwHn1AHNhKR/7bOQdWjOYnjMAUwClVWG9JrVfPYp3JHlgJfPTr0yHNZ3JhJep4o5nZIaJYtIQks/17mI90DGyyi1nkYxlKCUm73qGCvvgaAvXe8HXNeYzM5piNQCTBEmuintsmyuFPcMstrSXxjkc4e191sJckeSAypNTAZ3MerJkW4+j0wbQOrQDP50qTlVMt50viBjxmB19QHMcJRxsCF3BL565S3ryFVZX5gaapUDegF/0lwgFWpe7GBrjlxWGwAny/7Hh6R7RfAv2uGCHplQaLjT+KtD2aJSTaJkhjjA0EUMwfHAisqCymIiLiAdTwhaX/DUbYnWMdJ8Z0RWDCCzfGOT2aNewkyGP54sJ+CvZKDz1HEoV2cKf3pxdtwca8SiLKbAqentVvh/ZzYq1sGKGrYR5dhdjDe70wZg9i6yDYj8osWj3my+z9V/Uqpa6aRm6rxCkPZS5tCXOJixNRHSi3DHGiKbqvU+Z0MjzP3HObygsTlc8yiNcuP38AX9Df449ItfjFtfp+BN/rNwHrFv1hhpOqAC868xk8fyWT0qkoYO1l33oCQXIBIbCDKyewJCiJIjRYJiUBJdVRMgFgwOkTua3rF5UCeW57nwnI/h350PGVHWVLy/PypxcRL1Dre3AgwXVFuVa+5+YqJUWdE3Feq2AuG6AD2MMKQRb2lhSseQVhhs2MpwUPi+rJsAHB5R/+hVQ9LWtbouzi/nD602lpDig5Lq5+ovCYLhI4XaB6LqUqOussYXHQTQVh8TqiWjBgDAp/ye13oyAmoAPtoXHzpESWIWu6O5pu7zmAtFt6lwJf4ml/rEfCbzJJ9T2BBcFnFC8mmH8PkoBE+6aYP6mfleC0ZymJulUcwquMK76RHPxyFyV4qTPr6SRO8D2cvD112TNp/slZy5taGn+/F364ruFDvacbZ+GiopbmKu7gehP/5u3bsE7ve/tqaIkkazGcE8mvSR2GRxda2BPSLRd1+bGk1Bm835aUGBcx5LoS6vIr1CH+tYgSPwQsx2Bu6xAU/7qGCCXE+QKi3xKN+IPCycNjfJTIAAQs+9P6MprzHwQRaAh6UIKOrMYzPag84oXawLd7Q9SJHonshGiqoQ3YrTGUVntb0VKVyC2/ucN6sLcBBu4o1uJmgXKF3iZcK/YYF89YMPPh7VyQ6mDi9OUsDlFwicx8gbNGy1RKXNjvFA/idvKtmXbRJcon+F4srs9CZiyu8+vffkn1UjmtHD1/vYaLR6T6e4ALIUOyuS2xFtXDCI/mQBPIGGGTmpPdwm1x5vWgz7Mrx16P6K/vZ6R72j99Xfm6W3CKQEab3OeUhkjh33tUasaGgfn+Di8pxh0iu52XrAKcYEdz3ZUsebLTJLv9lBuUsqAITQJ3QjYsenKVaY56X0+YiV4qpoIx3JHxYmzWBaL3sWP8uU9U/tkT506+2hU0cUbjUkYbpzSK+HqrJES8Ah1E4PnUReOlPiK9lVMnxeNLWo+mNbdzpZSb50K6/VrZvixALvuTJlUYz09ASZoHIsQHeX2FCITlfbnBbvWBQlHWgvmNbOGX/fimvO651xsGVwtwB35xCSp0GmYnnQO8L56Pkyi0wnDzOXwRxqE/Vi6iO2ElYAoAI1vUvpWN/uXdK/X4Is07fmFW5NYjQUM/BpZ2P2ULE9CkSvFVsN2P+gVDitfMwHtaDnYmSW7bmGdTHEunRHXXO3PyB/48/5JhWvFdLMwg9isr0Zc3AAIEtxfP2TnxNdq7C4Yjg7+H3B3IYmozMpayj7lVGcNbo5ymDwE4CToiPSCHqvmGzi2FH69FODSqG0agIegur+CDiCJa9RIEyDXadOZ43QJih1zYYesBi3ArQGdVrOQ7zXpiHj/Xa7zFr1bJKhgZTgq3rNiKd2k20zHdFay1e38N/oIekNsTu+csawo5hYsAUAKX8C+c7Eib2gOxptoX5iioPXf8GitUXAttcdn7LoKFM5sh4n5Af4cq7idMtSNFMeIYq24fJXkAVRcoAvB2p/7mRgmhlLfiOVjomkp6N257pAHah6eYzUGu+IxX3msuykEub3Hzevmbkp5XoO2O6DMCZ/Fdo1I8zgrmI5etvj+EcspQsBlo150qN9O4NLMIIc9pAzEADoINsFDlESvS+/gXUGTc/Gy6uRf2V5xwMNiBLm+NyACuxSozV0n+KeAIuIMxj0sw3Gfx+T7DPguXjelfjgfXip1BcP9HEqyMtwH48PzK7mOSahTPhRtVilhfbAcqlGU73ep9EZduFvhpDp0mYcnZnIGI9vOJElvxGlzoQeBAexlcSvf1OsMMDDj+2q8pz7MxcK5VTI354b6kt8bA74V0uI+Z4b5SNnC2esaZskAbA39dqbCDQmm7lszmh0ANyLZw1GrpfMGsOwEs4Q4b4V6Rfjv70szPcIhmwavXgOGkWqGr0fyxtT8SY/dI29VrUX5o4Z/XZmvO3BXtB8CNGAlY2UMv7vqBuKAkCIj0hYcLvqZojcCII7Kwc4bMavbwxkp4A17Hy2c22xh2j87b4aog4MVVVVywbs4vv4u9/TI6d0J8rfWpk1kWxi8g3FAidecN1A1wL2wGahc3/6JHGctxLUmdR1fhuvdWka3hDDrFUMOzWRPFZKTvMcIXQaKwY7Vh0NUolM7hCQwBLVqjnP3V5K6WdA2E06Ig1Axo3kNsar1PLWtdZEVGpCZ0rbzHbt+zTP1Tu19DztsimJWB1s0iz3ta41tFDmH9PZ/Mt0buNaduXUH+2ez+UNy7pKCc9XSEbsPKxixsNoQ1AuZcInQ+AvYOiAGaYY4L25xLBWudanWJZvwGyYG6gXD8FfBWOGcdDqIEHMG7/Jzl1mVWaMvrtttqG/htH2LL87a5TAPxahH4tITu66lOkCKg4BY0x63hnHjLXEGzZrY5o52NFAzqxzb9CyK9UawjtcFEhfJJjm9xonjGpiO/ZdOgDoIbweY5lsX6k6F6xW0vBy7CmCe4qykRvUr8ZTKagk2C90CatwyzApsYq6SssJd5FJ/w2LbASkd/PxGzu173xa07YY/QF4OiWEYiNT+auR1XIvY6MpEMI6mI7tDxgD9KPseIzvJOuLVIpLXGtrEbk9o8m/k4kZYX9oFnRtu+YFTiDs7x6b0sb0UMqsmzOy9iCSXavpx5BkPBohftdvoRTbVHNPYSkaI1/kRvYTmGG6zVQrwAAqTblzcL9atK9zP4yPqyp/n2gcz+D37Z8nMoBw2twKO+/IjSBH86F50QFzecA25fBcD9cMeBFpA5w3aDEYmxFnuXaaIgHqgFXAlSFmZhPyFIRRPbw9aXC3BbHe5bNq5gTVroeUAn7AYwDv0elWPYzUcD8/L3q94VCA+H5WZLp+qT0a6yxnnsamQzmocX3W//lSNozX5fgo8qoL1GC24KR+EteEry75xd9UL0JdHHpmdP148wQ9BDE1HHBnL/PtQ=
*/