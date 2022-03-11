/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_ELEMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(key_type)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_element_type 
      : mpl::bool_<detail::has_element_type<Type>::value>
    {};

    template <class Type, bool has_element_type> 
    struct get_element_type;

    template <class Type>
    struct get_element_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_element_type<Type, true>
    {
        typedef typename Type::element_type type;
    };

    template <class Type>
    struct element_type_of
    {
        typedef typename 
            get_element_type<Type, has_element_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_value_type 
      : mpl::bool_<detail::has_value_type<Type>::value>
    {};

    template <class Type, bool has_value_type> 
    struct get_value_type;

    template <class Type>
    struct get_value_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_value_type<Type, true>
    {
        typedef typename Type::value_type type;
    };

    template <class Type>
    struct value_type_of
    {
        typedef typename 
            get_value_type<Type, has_value_type<Type>::value>::type type;
    };

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_key_type 
      : mpl::bool_<detail::has_key_type<Type>::value>
    {};

    template <class Type, bool has_key_type> 
    struct get_key_type;

    template <class Type>
    struct get_key_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_key_type<Type, true>
    {
        typedef typename Type::key_type type;
    };

    template <class Type>
    struct key_type_of
    {
        typedef typename 
            get_key_type<Type, has_key_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* element_type_of.hpp
+j6WU/HLe/jtx+zjFXteMpr39JVDODZDkRvWEjG0QbiP7603KAtPRyYk7jFztSF6678+bCPgqKU0U3mL97ywWVsnFgZzYXl4MDXB66Y3W2Q9XaC0OrTmXe86RKVa7/4eKeH6GE0dSPd94zu1+W2P01BVoJeaVnhmkMAroLnLbqQZM8KUdEw85U2pgYAyFNhbZOOja7S8Sve9OupVcO08UeR7iEcivuVTu6qHeNWrdhG//7x1u71JgBwqZfiR20WWmqlVYiIRroxw7lE98eIPqsDF2JUY2KRzDUmAr98DZpHIN458eFj8em5+uAeA40wDIfOpv1GW8HNgie7y6i4onIiZvB2f9nS1gAEeQfjT4LgQUrdedPnmqVxepKTDx4BC0EA7IemKybyLAizcN86RbOnRB7FaaxHM6F4W2vK+3/voI1ktY37xLlYGNfcQTVf3+C1qHXxbmBoYw8+JZe3eyb+X05Rkq3YoBYzBwDPVbr4SpTMYgsCNlnUqKkXcQOsVXZ77We6pzLW+IAia9FaAeTnB3GQ1UPlQ12ZyBVtEyhSgwIHC2OXc4trVGKOGONURpTJTr6yeUONoX5qd/oNmZ8JyYdxqsRD0AKJVJRiscHVlqIbkKMuIX4xXIDOfzA3Fk2D5t6aIvFszHSMMrCfnsDYJQ1zOwFUQ5ATyOKeSPA2p0Ktq9C/EFeY+mMPUxj4aNEJ/b/iuhA4HTliiQYsIAS86ILl996BLiWQHvRHk5tJe/fLKdVXvP4cPSdJHE6GL9B7wwxcpzyP80quuywuUel3glaLMbE1iFl01fw8EHXZOVNspG+Bv76iQwIbKBv/fCWZlFVIzWEHlELErY3hqMGBSzOkU7cZpM5HJrPsmet7xPvL6FjiDFspiiW7dnbm+wurxxD5BUSni2fAuCAn3G0BTBivOvMiz0y8vC5uNTZdS1QmOcsIuh9NmC7kHVBFIAcMtVyRiZKeQ1ZLgvFlrAB3ildUmSFRwK/LLEB0dO8U+/duTX50IkuaNYihTQa2BlscKRBIm2M4CBvktc1g2gJsHCMcQaO8gO+8jy0H9155hRrrP7tPCXoAGjZV3pLhMcz6WJdRA+fvzS0ZbEXpVcQRjnyhVs8e+nmUbIWt+Vyw3LFuP6daUepEOWP6klrz3N4e3Z9mPIzZhsb64KN8croW40cYbFvK6IO5eolZa0JtW3F2+BjAiGisiSAGdCsPcb0MqxKp6HNtUFqpsKkiK28dgFdSat74sU+ib+6oyr+Vkq7MQXKMYv0IY3lg4zBkKKBwg/rG9xG+99L2ogVE+++eyMTxS+tuBLd1MtYl12hIYlBDg77PA6j3/lvXa1cwJ5VTu/wIh7+Cbgu94C19/t9FWg3f2iYtu7tUC1qCbW46ird13HRZ27neqhpVPuX9WiwpAzvzcszJiEv0rUwHRpSIanF1uvzhC8viUfhioixwvp2edXJfLA9Dx25gEkoPa4bBPbfgdoJt75MF0m1mx4J9NZnsfsothppbLYxueNGY0zkLbNJFi3YqsBoXLMuuYWOz6O4hjGduUaP79QyIpzHrWoGCFubn6/AhYJzmIyixqrO8f6CiAri79zLLD90lJJ/QiPaBHTtxhPq9QQGyVNCeA7RDDozGx+IDWf9PYgMYH0EZXsHKMh3BHK2QlU4s/dF6b9Xg695Z8Pa40uwrPj75BG3z+KZEJSnLVN8Jw8MdXxU82o0wsL2m3OGfTGDafHNOQ4edxnu2rF7ohZcSvxO7ja9CCEptrtDdI6UAM35+ZfNT1HwoQQeCYhQgKQ+cR0+5Xzp/91zFAJ3fKhRaFl2cx8MWr+GLf2NKaAhfx2tZT2QuvylxUkJHl+a5uOIMCtC1YyQDv0GrS3eyW2mgc70BANrF7rUGCngklYAP1e0hrD5dBgoyC0JodsJ4ahTMB4ezyaJy7w7qm8tLM4PJYb0b5RU6kA+JF/N7OHls2mCv3tlB0J3dVzY+sMKRuUSyI80ggQGhgE3cJmXlkYPr+j3IFyDe8nF+JTAL6STh51vXezEP3P6Ag4DFzrp+QZIIQJ5hSL7uXt6aW+N/2rwVjmgdni5khEOsc6kZVLOvJCP/zgzuieneSfaVXosXOyjXtosWFKn9WmEpgV9d0DcdVSqY8iEtb6pzk8lnzQdNMFVpNtn9Y/rmaTnxqTHZiwhrrL5FX2Gtd9G5VG746MGy+wdLVh3LxIUyPJcYsTPUh/wgDC3EutMQhkN9vles/oYz24nblBn0vDuAk7HPjjGRyZqRGpd/Pbzq+4GnFIfu06G+v0OtRmHA6LkfpZs/otJ6NlUqQbnGGhH8Vn08NcBWQUqywUNYaCaVrw+QA6EmRu8JxJhJ+sBnmWS31kvM2wDn/k6i2DJYr78n577+QBgIjwn+x99rddERPeTEHiFuuvpdmvqAXtxyyZVIeaJ/6/xn5ZA2Ib4FQSSGqAi+lPsNc4JW2mF8GnTENP9p9LBqpgDxsVS9EHGKSyMTYM+e2pIjvsP0Itg9H/HRhmq2yjSmcEoJKTHOhxaKQkvgyqeXlIW9f8h+ZZ9TJXWk5eL+aXRK4e2o3ew0HDyRJAUZSgmTwn0E/+jOyKvhdNRXF2ZI8WMu5B1V/78P39A6f7v1G9MeH0HlKrRQHx6nSPG+ChD1kpQFc3kuHu4wN2RaqE0pQHr5EXibSyEA2NhE26lJK/ic2dUNoVYYwcWC4BmGouX6tYltgU5E6nhyQBYVhlUD6un+oDAULW2w9wu6N2fHu/xNSiwY11uI2jmdQpuo8eYyxXdmnw9sRS4gf6ImWs7a3OSunzzkAf3rTO1I1UaG2/U/Pcy+Bf5uIixnIXljHiKq330LZyjssV1W970TlP5inhTeiuJ/yxDQqV+631mlKOCGjJVkr8fcXh6uEtNvw+FTAgV+0ynTOAhOgM5fRVfun4aDgRwiBqWUVrFGz1fSo6f0sYdyBPGPDsd0QO3oDjzyz08n/IO5x6uhXhMvhHLd+VLkAhguUCIs9CtE8/wsi2NL1tK2iowdo4wjfS1SYt3bIdnu+7NKQEaIaZpOKqALSss30fOs5A4ivfxSeVPdt27V92hzmd7HoAgLxneCLpLzIkV1+ytMGrc93xXoRaZff77wM8OzAKa44+mTl1JNxNG+RfACNbdXwUiQoS9iiSDLkTpLE45K34Q1yGEWJMCQqAIMUrnWXEnqpc8Whm5dt+zh6P/gp0dN7tbtwNhru7sofJ/aH2xeIvhP7ljUhEpzkgTsCIsN69RMBtHcODBp3IRn+LCu+z0/ZvhhKCnq7DOj671n3pswZBMuOKZgnKMzXZeJLRCaeDdl7qvbuuwk0EFb46FtmxdczhR4IXzBJ9TeGPapewfTA1WzVrRrlvtOs5OlQiB5SJfZVrWm/7a3130CCyGdzgEeL8qAItVGVADM89DGkNMHGb6i/UWBx9xNx96bg6mlQE8z+jMX732wvsOItNMuEY+RYdTVmOzfPh7EOmGjdDYnAWxuwD87fFetB9ppKg4sDTxTSgHXxLn51TtKVymbHdtJlFPAxacRKyA5teqk5FxY7sLoa+wQeytzADGJu8fZPGLXtc2XUkqzEyPsXqcPtwSchxaAheirlnSm9JCykZHjRrdymIp/e9ugIJ2t8l+NftNzZC99R4uIerDjCXXFSZcBsyyM7s4IL8vzTAvzSuooAp1P0jYgESPXa1+2KYjQLagz/k6ndPzOT7qJWsnlSzzaNKt19AzBDxH1ToyaCKG08bvCuBl/+W8KRkKmEr3zhLXy4VGy6Xb9wEYDzmLh6Rz63hX3sguafupcT2HFfWxf+tGhzabSlCio/4tVWZWLU97sRo9QBHx0Uwyp7IktukfVgpmqzA6hPwRwVKadaXRhJBFONoHOqg7bg8hlfgvoNQW7ipW6UXXe6akFJ3uZ4PmfuaXVq9a6pZGbIIaqipfxcY5cLoHR9gc46bbLKBbwfsKpdMx0GUdUYh6UMBxt/mEri56Tqn6vug1HjDWSI/UZZ1LEBPNB+uehGATDGeszKkihMae7RsV9aIxb+Df1rkqxpln+uKMj8DhicHYWnzdB8oQMVgGclOvNDVhULAC45R/cZa3EaK70DifopRHodFas6SEcH8fzpgi6TP19JRFYUYWhw7J5HTtbOnmxKPd5c/loq1XmjyzZkCdgf+hkAB2HC1we4DBGp18vK5vi3AAEOHI7EETjzCOH+xO8DEBRsYTDpdSMJCjnjaKU5p+69jFk594BPIhJAETEqUzuqbGH225pgQQe4oJyMg11pTSyfcXuOkWsr+aV/mcLxPLU5bgDExNh8M5ejJ3qBzGPMvqY4Z6TBUm1GThFag9adj5w5gbNREgFQWF5aFav3JQ/yah6YzBK+mpuoywI3y7kdYroY2WW1GQ6qBn/jAhollaqVxwc/nQKZiBj+9+XgCM7Ct/LDhOeNQCzRuWYZGvYOkKNVxRUl+e5zqFxmI44HkL7jIRtWBe1J+F2I7cpsU8uPjmwVEqiL+hVedwilSPkBla02KtH5qnPAPiEeFH1JO27gvk2kndLIghtGUXfxLkaLNHBbT4kPkvKpejX2rLV0K+cHSYB9LPQtY+DyXA5pGrpWMBp9jA3hHbf+degyL8NLEe0tyB3MQL2cHExehBF26rWdgloRkffS9hx+3/W89jXHYrOY132BEyr1cEVeBMe018NxUuNJKogoiqXUEq7tbOn5grnpp7Dk/d8Tcp9tnaUeTLFMX0ob9w/qo3unAes2CRjHSZcBBOL9x2DYSHfVY5i7Wj/i9wp0BwTANTkO2pmb7/fv7y8QKSAA8B+QP6B/wP6A/4H4A/kH6g/0H5g/sH/g/sD/QfiD+AfpD/IflD+of9D+oP/B+IP5B+sP9h+cP7h/8P7g/yH4Q/iH6A/xH5I/pH/I/pD/ofhD+YfqD/Ufmj+0f+j+0P9h+MP4h+kP8x+WP6x/2P6w/+H4w/mH6w/3H54/vH/4/vD/Efgj+Efoj/AfkT+if8T+iP+R+CP5R+qP9B+ZP7J/5P7I/1H4o/hH6Y/yH5U/qn/U/qj/0fij+Ufrj/YfnT+6f/T+6P8x+GP4x+iP8R+TP6Z/zP6Y/7H4Y/nH6o/1H5s/tn/s/tj/cfjj+Mfpj/Mflz+uf9z+uP/x+OP5x+uP9x+fP75//P4E/Pm/tx+KKLHhQxWAVVkXBfuX4I4AcxrtY/7jc6vSQmEfp4S9ei4p+q2zmRm45LFnGU1/wM1t5agnImjnWOW+YNuMWGBBLqqK0EZk+R+CDXWEWCdz6B1WNbd6eSOJ1V5mqb+ZGUf5hL01AFWTvZ0l+Gowu30v1Ezes2ygT7A5KFAenAu68XSysbC4K7p/VuWSmicncEKAUZwsGnKhZiKP8TMO4uY/lnmxV0adnoDi3eMx6C3WlIaYQkOt25aeeyJJQdXoego1cc6Ojbw6n/X1qA+BUFzR9515KnDd0k7Kw+4G1AYh6DNugPiMrsTDBIZ78bw6rypJCDp4pspPehxJ6hJYxXGStP8Y15QHM9X8SvfcI7UtR4zP0jh+Jq7nG64oCYblCnjoo/M4SHRfNcKDn8CkdO1cJlX46PUoizNW2QkpZ4dZFLTnx/eB7A2fvvXHbRvTevyQGv+ytpGnmPVo25VH6VHCiIdVeeS6hc/9UrlL3mKf1QuH4emBw/wqhYOdhZGsnHQ9QowIH8qSx1VheQoU5T8SM/DjjuoheyvIGlG7uxBTUOGBOB2qCaA5ftEGoaGexWfHKWGT9jbPvI/AcVjZZQPE6y7B9LmlibM4CGY7fQvYQ8+jH+t75aCUDQfzWFJXM4Ar/g5fNJxz96hyJrrohysI/mTWoYHjQjYyNa5ZsAKYJTyfSqKreWhAHgadLnVuCAL+Bv1AF27XzyDJIo4XcnTEpO8qbZRkF3T97eCzPAU/3SncEylJ/uU+yBaPfuaSIZE3LadPwDLGsf/0L20zu11GnPDEBBBZ2PAIKhCTvbOAEXv8EIKLHP1Z2BINZFKvqCFePXmaLjBxpWrRSSIfp1xtSh1TcA3XFocRo5nwe2uO9VxjgXO7j3+kT13RjtpwfsS+4t9LhB7Th+QA4wksJinrU+dZycaN4ry8+HYJipYc2chR400Uk2vdP1mT/2vZLXgnQ/08fadMhNFi2yTecCFuf8HDg7vpEXFLukjHK5RrS8/c1Xs5/U9uVbRj4wHkMbygajp8cTaecdWknO+fdfpz9Rm/IAS5Gm1Zzsx2TE6+eil21YtjkzSXyKkr15JYo1ywlu6eE257kJffT8VxrWljbJJIaB2oeEZN77zhKe8uXsxHGMEqWcEY7LE3W0beyJP/ud6rFgpRdiBGmgJCEr6qM7zN/W1Anx0K75Tjf6mV3k0juJwNISINenBF0325ixLfomROSiCwwgskwuqbeN253ThOg1nErzGfslJwIy/1UNWfeck4QENdmUzg7mWUGeDOyZ9Yk10T+NIjEir5eSB+JLt8iXMUYuABlIXv2sUBhl5CSwS/XaaDMWBNCMXyHYk+yXPFk0qiT+NmPzNfJ1JQwMizxp9rl4xaDiyidWjPE3fTizgXSSQP9gECNpo7VR1LOHv/vYu+EhNTGQwPlwTfvEH8zg0kZilsFzktSfP5Hz1CQN9iBWyixLS+FqjTfxq9aAi2AKjCZqMp/870pI0lT0CaDoEBXj+RvBrsvqcjMIRYgWsJnbQpxbsru0uMmsXfN4g9xwdF+3L1weJJkc0PG4Rxpxtzt/bQOrzmEkoWlZgKyVw3B/WhC1SkOQIHNsDjbhWlQmr5voDexAmYsh3A93GG1uO9mVaIgnVl3Igeu+eHNM+6+7aXEKJ+B3bTh2lDG+V8BjLuTUcDXPvoEyyKZ9MbHto9/XoCEDTGeGTHs2FA7GXk/4dkasP4WZPsNBOSIgp3GgxDpnioQu80wRGlxisluV3kjc0Yo+rzBZnuSbCN6a926p3OwQ9aUsRQeMRJ3L600DOUB1OeK6eBoX5T4YLdxh2WlmA+z7WPp27Xe++d1geGjJVtzuB1/K5Nqn7oQpiLsHuB8LP9LOysLQ0Q/NSyIzZJ6Lt9DG3R3D0xZ/2e6cISNhFaXqwJk4RakcdpT2swJwcs4PcCpb8weSF0qsYvY5M5DMtjRodC6XfMDZmHVCRYwVNFlx6I4Xwd6Y0ukbzklXSn2hZ7vX4TrmxuIEdC17diNLMUDO04o6kb+b1MMaIY1JgHmbd6bjWq3zSZc1E/i9GTrwsm0vRloy0ME/TfxYA/kCmGR+IvgUw0txtM08b2fKSaBRq5E2m9lEFAvvmLUWacbKvHCBmGTlj+I+h/TUJoV0xipci6EtYfZEbu2iB7ypgL7MAVQCnNqLa3xjrOF4FImsACwEOGqu/r3zwf02u0fU1IauKYW3wk0jDlOLT30376RNtSuT8X/os1xy3uwo80tsZwcnFwDhCyiXSbsBfLV8+QVGVdlAGX4QzSKKdygl71YHq08az9ZKPVQYqCM4YcJJdNJtUus4AYPK6vGb4KqCGhvrkKUtWy9bOf8310sY3dr54z8Rx6vg/4MVgfOwqj7JuMP1yNqYk+8t4tTqrwzSWgWb2MlDn4pK5tTAjBt1rhsIDYifUTEG31IdLyeViETftfuUjBzFt3gPeQo5FBdYE6qeqV3lwiL3ZmnO/VkOYt9pSLFnsP5JGau3E2F/Rn65x7rJKGSNM6tjTblrUiiWnf/3nXTM/QY5iyNgGuBrVXvtIgnUhdzuQDcFAU4FjCBeRaj4jJDovRR8qxW28n/SeGJbsRx+b37YucoHbL1DEQ7gXTEmeaRLcgRHEYdlpgS5HObDYH/qokZX0LIRjfBN6w3tF6uaaXGKrhaTRn26Rk2M5WFWVOxHWzWSLquaTkybo35aFSFpDtOdo3ZquCgq8KncT2AKpqngRGt4nFUJwLs7FLJp23G4jsYxEtO1RH8jtY7DYdPbkzd3tYaAvnbTj+ALyCwRPz7d68iUbf3m3pkC/Guaje7MnEBnssO12fmR2MyP4vHxVwkhaKlqYYMCWqQJ7xM0uD6YD4cVHS4bVSNT509jZQ0tFVO2BU8YlHXe97J04Mlq3FJpgPzOeNjYvETmLKNiLHjxgSL0LBukkfr8X6VSxFbnwm63tf3DoLx2MXWkEZL4Vsb1rhn5f9VQkR5crZK0s21jMTjIkQNA0Q/cdFszHZ8/wEnrqUE6nRRlaMmfq2cUctG1cdrLdFlwqiT9g5WzWgNfyv0ZjdRga27sedfZRtJHzFU12t34V9wswJxJX8aZ7j4rlfwG2EXUt90CVW5NKMIPZDeW7U7ViXiCDVhvK27AS+wLgLkhmQojDuQltO8KCejiTAEYD/jLp+Hu5gw8G/KkwWqhLoyN3+ZK4nJo9mMk6a/ssPkdoDLbV6w9R8CjV/TZCd0HHU9i68fMo3pkUjwrG9GrxsCVEEahTL+Mcv19YjFy0cDpU8Vc/DW5eldV548hleSD6CeNPCQY/dANGh6oLRM2ib4/E5tdhyFjYgfRSlTP2oNA22pYRL8UmBC8F76YlMNpYCZcBWOXFOK5+AyMHMIJPzykKQtRw6x3TSmkRCHfW+Eu3mUJLHRY20zsRsyRgicpDalgTDJWjq1KfOaRO/5M4hhHL+NW3C5ZQ6Dbvw7gOQeIeWRLBLun+uBqUTG8611KzsRa19TrSNuc3iQFAYl3vYqnLpFiqghuhn/l7lhYrTWZsyCgn90gaIvUdhYZLkRGmeWsEQW/a7m5/yMxNRxq4QGOFOIGgo+VMq1R42Roh9UM/yj6Y0/ZBReAIir9k8qQYQYM2I0YHChCCrbZmKyKr07HnX2IpVc4ljfIFDcryHDNU3SsF4TNhZ1MnnEOCuriP6bN7+vCJ87NcaAYrNwUoON24TW0BcukrJ1KhJJ+hi3SvknLIXgl27dRqZyei2hlqhUOn1fTaSQCEpD/jESMnEX8G2qyuWcNuSdOb9y0guMFwLj05IvJ400fK4e4adW9Ctt7y+2C8aKoivsZAnyN+g7T0P5chNplh6TFGBNvYDZ5v9r6fsnT8xA/+1faCF/2pEotGYw5ase5WO0FxzchYx4nAAbFn51Gp3Sud6k5blC2f6KDeLMnXACh6MFShAbtT0Zo0+ukrNSodIAcXqEY02RL9dw3oaJaQbOCU+c2zJGhF6Nl5f5XS2MWpiy1UqC3YRuDQ=
*/