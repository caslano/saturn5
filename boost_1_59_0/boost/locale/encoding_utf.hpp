//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_ENCODING_UTF_HPP_INCLUDED
#define BOOST_LOCALE_ENCODING_UTF_HPP_INCLUDED

#include <boost/locale/utf.hpp>
#include <boost/locale/encoding_errors.hpp>
#include <iterator>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif



namespace boost {
    namespace locale {
        namespace conv {
            ///
            /// \addtogroup codepage
            ///
            /// @{

            ///
            /// Convert a Unicode text in range [begin,end) to other Unicode encoding
            ///
            template<typename CharOut,typename CharIn>
            std::basic_string<CharOut>
            utf_to_utf(CharIn const *begin,CharIn const *end,method_type how = default_method)
            {
                std::basic_string<CharOut> result;
                result.reserve(end-begin);
                typedef std::back_insert_iterator<std::basic_string<CharOut> > inserter_type;
                inserter_type inserter(result);
                utf::code_point c;
                while(begin!=end) {
                    c=utf::utf_traits<CharIn>::template decode<CharIn const *>(begin,end);
                    if(c==utf::illegal || c==utf::incomplete) {
                        if(how==stop)
                            throw conversion_error();
                    }
                    else {
                        utf::utf_traits<CharOut>::template encode<inserter_type>(c,inserter);
                    }
                }
                return result;
            }

            ///
            /// Convert a Unicode NUL terminated string \a str other Unicode encoding
            ///
            template<typename CharOut,typename CharIn>
            std::basic_string<CharOut>
            utf_to_utf(CharIn const *str,method_type how = default_method)
            {
                CharIn const *end = str;
                while(*end)
                    end++;
                return utf_to_utf<CharOut,CharIn>(str,end,how);
            }


            ///
            /// Convert a Unicode string \a str other Unicode encoding
            ///
            template<typename CharOut,typename CharIn>
            std::basic_string<CharOut>
            utf_to_utf(std::basic_string<CharIn> const &str,method_type how = default_method)
            {
                return utf_to_utf<CharOut,CharIn>(str.c_str(),str.c_str()+str.size(),how);
            }


            /// @}

        } // conv

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4


/* encoding_utf.hpp
pS29HKkAV0WPn7CWibMk7Hiwpv2cGaD2fIZAA95rTCyeFRnwm6/lHc/epBYWjUF6gQ/mxGrFdRAHAl8Xx0rDM9D4hUwFASxy8QBPJt5JYSqxrtDzKybh7WWOU1BkDi7EXFDE4/LiDNjAwgsv66E3Q47AhXpm+zdi4ghgCnxbGn01hLIbv39AUSQ6NU28AZViENHNvxLvZpAT7PuBnp8sYTegWoou1KkT0TheDUYl4cS9y7rmmhdjxT+QACRlddKYOzKrn+6a5/YIOjZghGgPn63ABloE0dSzaj6kJO/wMa6XwCeve1425yngl2Y/1GSC5Y09bZDF98XODHHIQCZJaRwut7cwXtYQuoz6ZScD3kBVV0QldxmSDjow8Xs4MLVoQ0QeGJTMG/cEVllbG7uHSkJFAYRLawMPaTLt5mzvpWYy7t15AIhBuasi8UKtDPAtfdj2DXleAk/AsSg+6xASmJ2QKl/eImV0HIfA8mZfzfrvOZhUwt9E1ZtYPEUY0icbOlEHBM5OCRsf+msVeOOhgC44AfLv1H+c6PBjCke9ZA1k5Eiop+y3HVKoKVeaLTVav1QNK7sV1ntzUMbmXHSPo0fGkmNeKsLiAcPldJdgwvKUteVROOQSoia18+DizePCBax5jdr7GUBPG66dsLw9AtwG3KhaHhf5qwHav7eYmkA8VTgyx/oFnCkyfV03Ta70ArN290T5lvRb2YGcsMWkjGsDdoumEFJaR9OFsaHzEUhOWEUGw6GJMLWTal/kZWPUBVDqzo8KarMPqIhnNFaYQ4MyNS053CgWam9QZOY5Zzcogl3rfhEW7srmITCYPz2ezOQxTYXLkV9bXikWlFG8XoTLfh1oh2W6e/KZrcE+VXcPT4kc4D9r9r3j3uP34t7naw97PapOt9L7LhxuB1P7/0J0zy97KKVp4TdKfWG8p2koTMLvVzCzHlghAz4FyTIJbddSTnKiCgwNVaXpiraAvwU1+8zonn+dpSIghAizkVST4rtdqSPQjq0uHaFhIrk2tajU4bf1BON9Wv76Im0Mg8TgYpqcCktQQUlUg9GhjA0uonHoYndv7CjAlwIVbriwjock/CtKIA3Zp9vyjwqO1Cm8LknwxUQAzmEywcd6/R+NJp7QsZrg8sXKEEPLb953gshnS4ScEc3x0xOI6cnrqrAYLV9OLMV4nD/K2MYWxVoDCgmMRLmpvfETzPymeHbEHJkDEcR3c1R+Ld0bPbxfu58f2KnARNhkOwwKDfAUVGF6b1d9/X4gvjzzfO11J0kAyDr9xRoNBqt7Rpt1HqV3rQ8ZXd8nT/ZN0iu776D0g0OSnH1hmTeGf3VpeR+fe886iRM5OOovh5v1VFgYheafsgfbcvQhuv+6FdWFOihJZ/OimF6Eojc0ZP65K+O4/bmAKmCIcnRMk5BNlry0BEjANqpklt4NynEnUPDyBVx/CZdv7jJUeBzZVfA3A3H2NL6NkAArhRn3kJVjAvLwzyMXR83zqABI9YRUKrm1SX+EogHdGomZQGkBDYIOlFK16LgfRqD4Ko9m3KQ4Ts16opKnGSX4+zTsZAk9JYOHlfFNOAkoSs9bsFZpMrRl4KzdR801aYOFdxjWPrQ4QcvmGFFXr4oNMqdLCNSnh7oJ4Gf28IGTtn7VlGWZqdG5ZJzhHRpdv1S2CDGAK2mSKH2WpGHwE2ySf7Oq6ZOg1OuLGp8Mtnyq6s5b8cylc83z+HhFCv56rHqpiTcjTI2Scf4nSKu9E3txsys/+DX9Anxn0jphAZrKCymGHCRQgWpTBNhDB06p2nfczF9uK277m6uvQ7dZCpOhaoW62vOG1O4EqDRQZlhMCDDoJS2BTMJ69jPgPwnmxmF5UlrlO9RmM2q7oDd5psI+/LPCNbJIBSSm0lmu6xRuAICMY2xq/m+Hgg0Lll8ZFWGatZqYTaoFhVo4jvpFMynzp6YOy2r3A6pGVGYiKCq/I80Hq85V2i+etlRSn/uGWhieDIiVgRKsCmQwR8bPxYj4Q1hbtrFFkdCQdSIK82gaiAPQOFYozxMETrLJ7nwHhaTLhmeWV9ek94PWTiaRuu7kBpOT2a0lozZtKp6JWXDpVbqGGirh4PBg5gQugfmaEuMOxas6FhrVprEVTXhM09CJZBhy7kjvtnIqWntDhD+C9wwdfetm9fVyjrl3NG2ZgCOZ1E3dsg63IFftIxuX92QAAiz904+fX5+VG8t9F/xqybcV2B15cGvHCYX2OwzMJyipzNruvFws1BtdC9FoCGPcHvKPSAyJsaALGZo1IVQUIYRc+OoeIfACojITIVrJZxWQfw32KrqSDU699ngAilpj+0NYkOcELhzeIv/l1DphekFGrkI+tk04gDrYawRgL2MtTxGyAwDAgkB5cKpl8vYAgK5H4sj3qFrQYiZhkpFfwNzVOIzYdEABL923XSkZQ6EtykUHE8rh2e4AWbQ4SdOsqr7yy5E5mMFItVDk5icwRXz3HCiCPSzwXLWpplT3KpdMalBlcoViD25q8W2EHaUcAeGb9QEGYRGoqlRpJ9u0tXrJNUIcEhp41CX245hmZhL6c0HlaSbajHlbj+yyWJHuapJMjvjJNrp0RY19BDt+TIi87HkdUZuqf5MN5kNWS7705i02sd2EX4T/txK1ZMXU+zZUn5CFsut9WBO7W+8tGeh7UZ1oRTLpDH9NjNefFPir8hyiyX9b/VeQ5nHYLWReZJypWznTRR7OKKbenntf1QOqaKMidIezLDZb2PS5HPJqO9AtvN2QBG7xxevulHJX6V65LWTujbsevC6foW0oLhNsHGb2JzWwNrRNa21nzsMtGA6RNXs2I1u0abzoMuFf7b8JdVmaHqDyvVmAxqDZnMQY5oZu33sZKETvWTv0LPl4hwlnhDfXkj07/LClrPjLYFq9dQT0e2rRm+TuMr4E6rl6YQu6i1A+FAtcEBP7d8a+qajUG1+VT4BbvUqLODOT7LaPZpLx1HBsYLumWx2PhTOsiSPVC3R4/B9gPtyIQ+EMzopFQGPbCSvCvehZdLalXO87N14fnBdgqnxMWSLEu/gN1lKSCuDT0H5L3RbNWmI8dsS8trGd2Nqf55N3mIQXODitSkZjyvc3mKoWoEzyaFpT2nKvhDZkcdBlFxxdYrzSzJjU9/EAbAQIvVRaktIhTArWTATStRPVSm/oYm/bS2hVUtrh6upAxaIiWXHFsd92QPs2qMa91ZRm/G28plDee/bNE1IcCaQyvNs9tGhHV+11+YXbFYfU7iAJxu8QoLs+z3LnD5Ek5P6w/2ufxjxMJ0t3Rnt6hsYwcUmFH+zN8/HZyS9HmSqovDE8hzaZMC7S8Vl6UXIkOrFlaNEj22sSOXEdM09Kc1cquVcPyiyluqxG0obXIgKRmyA597xWgAJ89DLuuZqM3p48ObUcBkQigUm9NO6t5/AkjdfC7qCgNNqU/b4eKVDv6GjnTihIqlCyE5JQ0zL8RSIhuRI6VfsXd2QW3b6bMQCQUkrZb6YQIIs5LqwCE3D+dquXvZ4fi++/gTHp83fhQs2CLOE16q+6HauL54Q3e6eaeQry9uryU+bJCi/z6T9U0HdbLvG3/7Zh76T5w5CalpEnW2pNa4iKCkTBZY/fhqfUIH/6quG/sddJHoMtiZPsRfqvZhJTzI1CH1zWmE81Uf9fyVAjN7xB/xtT3d+L96jrUKrcpbSjyhogHhrrPLjWvzFqRk8XrMekTjLm63SysbG/a5dS4iTDHUKMYGKCUapbeNw1RRcmZnIJRVf1GFkcFX//zhbJSpZmlVyvaBoQCkIu14bBmhgrSQkgC6GXNUnGeiDUGueA4Ybi51ApVZJ0ihCTUlGGk2RjbaOTM0JmkCzDgCzIfYaOBQde1g3vFVHbsSetStLvtjBdtG3LjxgOEaLeP/QRnUGgRDr6dSQRUXWXissFPMTlo2w6meiZPCh5cTRsrW7NE+PhyAiTMwvTNuZI2nO8b1dSNxK3124qT8uHGHu+KEyVCzDHXxXeAl3CTLADT1ptEasgNABhztlbux2o33NbgrU1a4plCARxklLh4MKdegltear3tzuY2xXbWL9pyRqv41q7oovNBAApR9wAADTmphEBIA4Aavs/EsMdejCme58u8A5ei2rnbVsv3jU4DBABgABhaSBAwLc/iWXbtjWRloORCIJOqtnte2cJAADyvwPIdvwayYuFvl5Lw8ym6vPjqV63tRZ9b7wKo47PIRQncMbd6dfE4Je2XJjkd4/mpUROimK4/7TwZ4xVnYVjXVChC6s5B4SyzXI6h/bOCcfgW5eYl6iv/tcpcmeGZ6tK9POWsFPuPsZ9CHIHnTODa34YJG0eojf95bptluD0pEn8At+qsC+71tLtf2djlwfwpvKfW/odTvO9al/iJprrrWxax5iAeW1nKvoOvkoDExOgp3AzppLA/JekcbQEB+6VkNxaUXsvX5XqHJQTwqd6yQaZg+62sLDVQ0pjuNjciojjo7uJWrmpQfKOyglpCu60JFfIcH0xxT8n2igGk/0SNR4B54GJvPi3+7kSCQrVkPvdzr8eZh07PiTXZdG5VkZcCdhYLyTGdYYEev6I5Q1xxltpetjrC0gVwW9Qr07VIEbBCPt5Q7M48yy1sFxdP59X20r0AlKLOeMlu99PByIugCpZ6zFdf3eYCFkmnWp752bcyBvl13nr+yKesdoaEH/SBYOZRchjlCYJks/3QFrseZsq6jnC9TjFwbIVg/Abx04VBbZ2UpCgNTuNCsl6U7zpi4Wv7EsvW5ICIhGS5NWpZ+uP+7zkOVvLNlAtYIfoYNVF1y2HEbvyPkZ6/GotnJ6d8wsIs9EhSiwQaMuvDGi5QygSbbGIY2bGnYR/rnjf2244dYLZzJV1QWv2vJv8U6JZmu+O19nuCb2Klx6otE4DANmO+THO/v7bVPt3EmSKWqj26WQ5pJc/EZDUhLAv3sp3z/dQuGBEnrpM5+wIHaV3nsnkgXpm0dKA3upDojv9a69gzteq0hDOMVR1SofGwTM1zax6p0pIyfVUxVf0OJMmeKwbFSiCoRE7atgIgtnAmjSwRiEhcxVCezAwE2KxBUycMiA5AKZM2SMKfxfThfd9uQOrUlV5hI+3Fk8cTi8F7DNvWiCkC+zywFD5CrWwwjWuAE+ZYedhhfm3AGSn8Dht7R6Lez02Gzk2MfakJREoKz58vpndgEtTXuO0j++0xCi03LuLp0vVfpDxlg0l+7+0s/tLGcOJ2zzO39QM+jdmo09P0v8EufkcY0w9UIFCd+z5+ylOivue86YCggk5JnXdVfGfCeoqdii5hpPM/aLOWsCz+5wlx3hE1jDX6x5hVorBS9/N/q1b4IrhvnMtDVbxrzFGQgHNPUkzrO351x6CI25ANujsQ+wr5HkFIIQGCZY2PS5Rv/xjcK2rQHBs9+mDId4dt3REmGIANRwHKVHfp2lP6lDGMhsU/j8AfICDf8pDzNE5aOSObobCDc7FmQX0vkjiPhmpt1uXHYMBnLGsT9Wne5eOdlOzubge3vkj638uVDJJ0OnZAbh2lmeXx4vRAIxkXTWASmooi0m/ZCL/zGeySGBP92NKO3TirJsZwV/SaGC0IbUPxZtIMYDS8JXwJzvXj/DFBy9sdkY0LXAmKba4YMW9FF4hmQAFJ4ZV8gKk38ulWKektJCoSg0YCcJjP4Zapm6Zpia0qi5o+z9kpOivLvqlL67tUPaKyMcxS1Z9wRomrXvGD8DkJCw7kADh36yDMawaIxbzitWmwAEvNwHNp7/eCat2zmY3895JKvblC3i5gGide5JX3KszNRuZSvtsS6K4v5sv1JNFiB6YTUUZI3p9WfZAL8zHfzN1RZBsby+CNih6xYd5BXN3MzKsVvtbhKILxf7qbgNTSEw/dWM1YLP5kWGtAlWuBZBAHK8qX+hW23oqAr7DwM6ouJv+kZ1GrJ0tMtHikTZZXHl46pJLzj/kL5itGmHYLNKJB45Tb407y62CpsNSJpo+hMRVZb44GfKrsEB8OCqs2Ofmg2mc2CLHgw/09YFp983MCqCCCTYpmLqbEb30utWRRS772V+Xe7tLAYMUkvtbiuCMqsn/+Qe/z/+kIfR8qnHpK7iHIpGWEnY3Er5av/V8omyPMDHSA+2cWcmeFMsChGmET4pJo6N4pcnMifwT9nGuTbT8WVGAZsL7t2a0JdH8RmEnpTfF8IaiOGX915kKNG6BtIFGwkhHaE9DNSYfTal7ysS811MpQSh16CqfQLWpFR1mcbCifoh8h+ibt0cE8E9G0uXCo7AmaSOpPMQYzB4SbO5glrKQd698aVylylv63hWX7tbbjbgqSPVmpm1gHKxyV3HkQt9jbn7lTp0Td+YaTrzfeaIRIqSZsGneh8oBftxVsr9J4OLU21sCakMhKOqs0yCuzY/mFFGhv+msOTCp/qwGnQ8gICKKl2MySfz0rSVK303LLKdKVnymEHC48ge8GFhZgda9gqILgLW0x5cCaRJR0l83QbrYdiGvi6YxNPv09lVV3aGXh0tHpvBHyZ8qSrLLvjspqaESnZF+stjl9ko9Cs31BLBw7L3R7LQHaZTd55aNcXDuFiO/J+hHI8A0JxQMiXF9C7jwm9DjrxO67fsBPHalR/MvKDCDcYMdeYfbeKFyFKoP+efL5UjlI6+6Jtj6xnLQLKg3KF0cPn08sDBWpDgYMOX6oIcZiATay7iG5IBxMJa+Wf3S0P5L9sezn0hvuzlZpLdujzMg4cRHHOQsG2CY97Xp0d8TW1zkl7aMSe/1aRQHHLw3g5vV9hTZRk5mz/Z8AaUryApLGjIuF+e+6dR9QVYC3joz6AWW7DMz1biptrmVrfS6eM8bn1MaviI2f+9dCuaBVsOTsE0OAYA4TkyH8q/WcuhneL6yrx3UUa7VV3gkO8CeWABdyYHZUxAGG7El6VZOtobCZju8bp/AzBndRWdMz3uaoypYy9fYgm4/QPP7exeANRD5wZczX2cUOZcAC/QJfq5s9g2QaiooQKJf19FZjcOOD0UVdmE6K+fWV5Qxu02kIXSDaDcy++WTgz9wgeFfGZoAVG2mOtdmEDlyeBuDTOzauvFjIRVPe9mDG4Niuua6SfiKbNOjTxBm7uZF8maa0K8qG5PSdGxnyw84CQDSGFaFtO+rSvOAqwyMwF1wAwd+6XNKOFzM9Aznn/LmjYucowJUlhiYTJTDeSV9I/pu7W9GyDfxNO47E1ZfpqLNBKfR4FBGLZGCx78cgFA4rFiPTj57WOo30BciwdrWrDstHmm8qrBkxUA4OJq/dvn/pbOQfwRrVj5x3dftuewfjIzgjMRl4Y/dvDSuTzocAjXqNj0mZP2wkHY6ZsHf+yjhBOHJ+v6AXqS1z8IK4UUytS9ugxgHHchMUajI7xMl5Qe7KROslfDXFwvbyRecPGzS2OkikK5wswm1vxq6/SFdJCu/HLpIwB2UDkzWy4w5toRDXqNYcY6mLWNCuqKLnN8Eh2o820vtQmJ3Wng4wC3boezGr4tapkSO15A5Pn/OQExSTMDRZoh52rwDIVroM8EzWNfjI/MPQLd+wAVtktd5dnAWMf3dbGbNibOkCIT4d9CqEeW2lW6uYBc5gg2xUF0GpOvh9+/Uw899XOEq
*/