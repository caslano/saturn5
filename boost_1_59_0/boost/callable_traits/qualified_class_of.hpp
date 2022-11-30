/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP
#define BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ qualified_class_of_hpp
/*`
[section:ref_qualified_class_of qualified_class_of]
[heading Header]
``#include <boost/callable_traits/qualified_class_of.hpp>``
[heading Definition]
*/

template<typename T>
using qualified_class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<detail::shallow_decay<T>>::invoke_type,
        type_is_not_a_member_pointer>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct qualified_class_of_impl {};

    template<typename T>
    struct qualified_class_of_impl <T, typename std::is_same<
        qualified_class_of_t<T>, detail::dummy>::type>
    {
        using type = qualified_class_of_t<T>;
    };
}

//->

template<typename T>
struct qualified_class_of : detail::qualified_class_of_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* If `T` is a member function pointer, the aliased type is the parent class of the member, qualified according to the member qualifiers on `T`. If `T` does not have a member reference qualifier, then the aliased type will be an lvalue reference.
* If `T` is a member data pointer, the aliased type is equivalent to `ct::class_of<T> const &`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`qualified_class_of_t<T>`]]
    [[`void(foo::*)()`]                 [`foo &`]]
    [[`void(foo::* volatile)() const`]           [`foo const &`]]
    [[`void(foo::*)() &&`]              [`foo &&`]]
    [[`void(foo::*&)() volatile &&`]     [`foo volatile &&`]]
    [[`int foo::*`]                     [`foo const &`]]
    [[`const int foo::*`]               [`foo const &`]]
]

[heading Example Program]
[import ../example/qualified_class_of.cpp]
[qualified_class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

/* qualified_class_of.hpp
uxnjvcWyt3tgu2zlS7uyS+Q4IgA5CjWSi5KFAMWkAtzKYvI1y37vm4nMTYwLnbSziUxmyIy1m/9aN3KnDzK+Sbiqg4dRqTylfmHSBCARy++9fv3OD87psN9Z4P2+UXsedMxyVKxWDpjMYJuWG4KXG5mMTAWjpOiEDQlpUXA4/vz1bdfTcZnDgKY2jiyJfqPBIZFQHm/wscT/vDmw8jd0CKHDD2TM1y87KnaBfTdryc0Il1Sv8b00t22D/+FFGKGPgIas6Y9pVyao52TnC40QqWZQFxp6gkMntp4q1/ZnH5XPsVrNuiZ7Lo5+PFkaUD5s2uoW7X4GGTs5RFUoT8sbYVR3OnOpHB8Jakzh89P7qoS3eTgosCXc7gFgqseDURcf5KnB3ulTVtW+3XWt4HO+LOhpp4gZPNyvbdsa/iItu/ptoCiElh4i9+9hDCBGxMHOgBI+whbxJIR37R3fTe/vYTOTuxAbMcVD5auPYHQ0c2JPLxpFv1pSO4o9iJyShpJ15yfVth3Pbzmb5+2BH+qofOqgpOkSRBRMIksJgXU/wOFYkyYHhbfTsGG84UCbXh563S5ck/iU3OymGJ9fa/nKriMl+5ViPY2xDWjUBdB764yffkgGVpzBtZjfDp5A0nvxovFeVRNOe9+gt7RdEfkG/4lau+Mz8P1NsMMkkhC+O0a6sw6gAM0vmhdq8uD64AvSqLfb60+gkrpgEAAJUFm+W9LYUtw3HADOddhRM07d2OHb6g5CO755GHTYo2qt1Gn2n4+YQUHZYcYwcr1p80gPOLL/knzGBDfbF/hgB80Wtp3n1wlgaA5R+VtEnlSynFw9skzs4Ot4OW4kPDhvCG5Pu217zPleyRKhQxhJfyuM2YvGxtIGOzJTy5vOdozMjGALKc+g2mTE1Lcd0CXhTGg7O2uyC2R2uCnOmpd1eodNT+3vk0CXGH5k1bjEaRAO9RMtdkCUd4e0cWYakUbgpI3GEg0RFAEJsqAhUCpluWDv4wVII+sNaNGwG/GmGOHZe45XcSParMS44P5oE7oX1ZlzWj5ls9e/+VnsFzCuptqnWm2W425KvH7UNeol+hMkYDAQC6WfxNggFvjL7tgeEhS7096cbszrMNNyy/g803kbFdUZ6YnHjebeICqKCAUpBq+LP3teGwnhZkL2gzgjrq57c5cMXUVlT/m8gkf9irkt6fmvjHFY36K1nbui5SbSwFxjSyl4rjCIXFFLC6qdnWI6/CKKIfVAB3FyMqALPqMO3B78gl06dEJ1/KnZRicyQmGBVHAH4fPg+Nr5OJtlYipXe50via5MsUXrtn7uR1qd723DBOO71SkOaLSdVCcwhjciQFgi39+OPqQrGd/fLNt5WadKckJ4sMCPBPWY0ParV67G44Oil0xW73GMnKIYdSA1FP89TyQOlZHXscDzOlNeQrQeFXpOi8g8JZb9fRX72qVasi5En386GegVzyyhNl5ITEIoYdtyfipwQbn43Ob7fYE5II+sN9No+Cux48lTofB5mA5GNA/atmTH77rWaYKKAErHVTJU20UksOORynZaB0OJXtX9+3q9ydIVRNAn9eCOrqbVSLLenUG3nCfqEJ1MlPmLOK0WYcc3zU9mWxot5iiF8bm+pxv9HolZg4KAb5YTeWc98SpQd5SEfgSG9QY89mq4Mgfnpx0+CYPgfrj2e8hv2AGBFru3n4mHCWaX0ZpnuzeEp15FkPYXgXFZ9ncYL48dN6LFoXP9m5iVLXt47viFY2qBhdCcw1u3kZQSIpOvUtme+2tYz0u21aCT8wjuaO/kwLHC3aUeaoaWEkZNIcWUgyBPXD51kR26XEHfLwz88BMs49rP4QEbW8daL8/AQQodtOGaRKUH6e/geUnzq5t4ItfvM2wdbe1MGEj8+TQwfSPnYi241D6DT0YNgZFHxzvkpeCuxhO74kLefu5VLAyYyRESkuNsTm2IwbM+nmRp6JKWD6c5mY5P6IzNM+eOuagKB8QmZZVatnc9A65uu0fnrBUPh8+vAje6A3EdD4H0ESW/Bcvr7ver+4ROTZgVYZq336ZSBx2wBP0s4ej3KOUiwQJNe37ve48zo8XG83MkA1ltgbmuL3cqs7O6o2JvpDq/m52UCh/ePrAIb02R/7S+eQV7T8KL/N1OeBkMTtTxtk4/b8ZkkF2N/y2LO1rPqAwiuS+dZQ3B0qKiJWbNxF7kt/se2MpsXHs+2JivtT1miI+QjbBgFjUQfa97xXylwjjSWVJQsv15anZl39NBVKEGS5dp/ix9Yw48msrMnHMhhjBFTg3Q/UkOEy4K/swHSLVrApGMocKJn0oW4/Z5Y0bwBaudvAM7hckg4E7jAY80RMCpgASfiIATKGvzkcm0HIDmkmMg82kscQjmNxQQXMhs4knAKM1lJUQYQQ3CjjfGwKW9Gsgi5oD0Uax969jiLp0aZ66Z6z1Lqr0yJFj4VWduMdnzVh6Y5nrSgncbTcA6GmfR1/YVAKQse0N0++AbgvKif+QV1KAywX6rdymI7GoLX3SKO2alf9dTprbF0U/wYyYPhnjyfpjJ5IpVf/nNqEfCGkwviaSm0j1CWgcCfY807wRA2Ls5I4aD1Zrib/8SCmlbywvJ5bBhqWFJaIOSXKTX5BnaBlMfD2mV5iR4fGZW6cLbjcCUiGNLnY5rR3etDG0bmu2dx/mkt0U/Ssh0Jeg70apmpzJDTiwvr3b6m68ZJtxxN39b63OOetHQYrY+dzN2bHRADV0rT0HgtlMJEvnO0M6JgYDXyhTYlbDxlgZye94gTr7hVbbwudBTvawtReafFnDtgezyk6srogLaMbYATKQBb4eJKsbKYJm08fTVMVRLFzby65d82j4tXavD8sAVhmHbfYwLgv2eD7R9pYR+/cNgOS6PBr/00Jj5iBclyXPN+qXL9ZVdh6tze/YGUgfhy9e4ixdq2hOIgCX2OjnOlIVzcEXrfKn8SCnt77HcP97B51e1g48lyDK6VURDrR94rJwN3MWtEIWjJkPJMcVHRuisumJ5yHOxhpZgVIIhBAMnM2ZfT7nETqEddayk0IvMVvtpfVaaOzFFP/SPlPdnI8MzgvWsn/3VWsB5H+FN1aUKC6DjPZLAYiyqc45Yo/DTS3MAkCN3G6TE3kiDuzdDZYW2rZUMYPPn0zzOIbt/AqydqRf1DH/IAk7mmZn2thyOOV1PUNJaGrARNjFrBSEocvv64DsZdWO4EF9/Wt9A5owN8Bn9juSgt2Fkjzpe5gLlpLpwbm00jvSc0XbtcEyZmYQWwILunDiezv6XTnrzgnzz+n/DUda9DaJBI4s3mYL8ZvnoDPKX6fgRTVRZd/Em4wUdR4dWUAkezu04YgaDusv+m+kWkp+Eguei1vstj70kmmzgB8XvBPgUY5OwSrE6YzMOmSU6brUA7nlcmdIRiE2IYhURfGJmQcm4Unullytv3TwObOqCNklYoVdlAskk8PfY1q6XA07J7GMuzjYqoq3zHHejno2Ad+/nvWRLRjT5tFFdiEa6L7fXgR2dd4MqeatIkRTJ/bXyQqKsyCwthApxWBjQeIBBVew8cTQRJqmIxAMz/cP3wEq+Vr5RFQndOB0dFeSKKtrVDW5SvzvMEclmowcEvoJ3vNYga0F7ncD+sWP98tng23xWcxC0hDNrlSTgLrYgwSLIF0IyiqhLI+GSZ/NSHpvAWXkKkGF0bnkqRVezf5vuXNrleIg0i9sPygMEgObDXey95N+wcwlbb2xTiixEYDKwUBc0lEDhJ1ZfpfByHmJGUCiAPTvcMe71fvtApn23mIOCprWBvHmgRBSOUKCtw6iOdnkeujwD0pIwyRGFjblcg2Lr/pK6QwRULMfLH+f4fClK2FL+lAXcJVIRWfajtj8CVNoOWsN5Ivxo5oxuZQtfxDq1WCy227qWqn3hum4SPTcvaGb3/I3D/r5GisuZj0kEGuo1u6qr12q3mRLjJZrVGoQqAe6AQwkPbFv6n8uFNaUrtVWY+6L705jVZQK2vdT92wy1NNQkEBLgz3jtXr9Q0B+kyYwHWQOOHXru5HRQ4fYUyVLawgHyaD5hwXahO3nsZZpZZb+klgWqKzUHednVepir4gSrqBbOoAjUGn6Ppd5IKki9ebzfch8jtZy2mZZRvm/Cz3C2eXds6JhJYq+Xruh6fPGVy4exfRbjzIcRwiGq0s3ffC11FANp6EZAF4TL1IuTcpOx6MdqdazXfVY/z1qYiuB8NbYQnhv/VwuwE6c+1nFguAz7ZK1Zhw4KCRl0Sm5gNofMXzMHhwzfXFfkufK5scU205Qn4vOQxhHKlQATQH7msBQ4EUv/ni5nba7IWg/HOdEiYdYVwaEm2M+iMaHQh0ab+os7wEDwd9G5BK6twCqNyO0B8H1zWY6hoTyEXFKJIw6kX0lt+VrP57ZfVtIUgK2tXvK3XYNoOVfEYSWwQ6UrwK6OXERahhWOsUPrKnqx1fd7G72mRWFjcZ3SqTp60oRgG7uermyaKchKCQyMpDZAdzoy0H5I+qjyr8SN15Xvxw3NRYDRA4hoQlhi6SJ3Z7w2TK1heOpw9JMYVJ3B8yjbWqLzr6YoVLg2izC5dI1zLEMOGxBymB6GaQkc2IWQjR/c9t5oVBDNVjwUIvGqGGBuHulgnnjTenK9OkxTGBVmOAp4cw16VufeKNPO+FoBr5L1VkkhYyQDvfJZ+jZb7qv16NMjgWMAHXHVUEctjQ8Xs/9OJE49HCCxnQIj64r3qQGjgIcv5jj1JfgzleEMbUe/yTUfpfkjN2wm1NcfEKNspfPrb6efhkRlIT82kPJ8jM+sx6qk5reJRIIRCab8AjzmH2QBwpvFdu+rNkRo8ew7cnFWwSBw8rQoUxxhgMds0Iu0EKwgqbdsV/u7P6HfWDw4H2XiPRoIkrayFIxbQvZ1i++NSlWMofdU7oH2nYNKy85MqLIeaDirA6AdjV8Kd/sZZyagSrF97Jj5qsfnLopI4uAEdANQvrwm8/Yah7cMSJpowXA/PIzp0rVhenC2PKm7laFhqyp8LTddazizo3922a07XJ5iuKIpU+xwacTsaaO87r657NZzPQxeO8O8ZVgOeqj3SHBxrVJ5jKDCFNL1K3RhfgspbrjXDYUk8ZEas5Nt/0l0yLatjwYKGqZuiLEn41teggO6J65jkkilcGRWRwuTJcZKCXTMOLRsbNnqYkjL4tXZYHvjSjQnvz+BfRaj3aKtqsXvLgobTt3utYIIFP3W6YTix+/oxkC77Is0G6wzeemf/XuObIR55scb9um/WSieRncHjgxHNSEIa/tbPlcL2zgjiQAyMEqg6r+F1pMYEp7+h/DirQPoybugdq4FsmVqEf4dQ0oVHVmOKbBHQL2eGzIoKHyS7kRkHy+K5gSrgevjDVKdsgJzd7cHiVZ/wG3rYo4o9EZy4O43kz5kcYYqkKivY3oTnfTWXENhoT4aF64tgeUw9DjbCWNOqTnp7ZahPTqNXAlATRHIolJrV0NovXCu535qzy2MUZE7hK8LEzY5xNkD/IrfeB8Nt8uBkV+ms1d+j3l3aQ2cyoZ8nXdLu7R9bgbtvHHTYvk3tHBhar18B9Iluk2VeYPCkJ8F/FQ/ki0Xvt8z5fS6RH64lRyZ41rYwcFKxDeTf15pXqxqEUbhSg9N8cAsZ/vgKf3tzWuoZKTTCpZEvdK2cvMQ5BxA2jd/3oUQtZfUJOAnIdDpa3/ZfEWzQjB8+bPe3yOB3c5e9Z8cRUCwHjuKZd2T2P0G86HODyTL53FjilsS1dIWqNm+e2p/YJ0mk2c69iN0LOEODgZt40R4q4weA4LcLeP9htxzq+ZT10BK9iAOFdA6hnMladJr4K+J9YmwnV7eG281La7242GJgg1ERGn4zEbEYd7+Jc3EGBMvfER+FuggSAGP7SehISkZK9tOg8Nnw/KbvJDH81WvBWTihIo+izrAshV1RTlqLug1qvwKuA0do06Y3BWbNRqYhmJUobmoVSV31zY8AqI5PUMtlqefqCZW4RcHiG9LY3RqspegcKyOY3/29f2Lm0hVZReHfiMIK9PxpqwO8UgN0JlqyH4s1Td3JJzLgVFiUe1PK8DhUsdMyeVDBOv/xKrgqRgOtui4Ta5imOHqeESZb14+eRFLM4jzQZWAgT4mVtcpK4QW/gFZmNYeTyRrxmhYl30tUOFJ3AYramNi1ul8jCq7igxTY+E1VhfnexqaYTJRcVyUHEdLoiRCVNOWENTfbt+FaZ4wZnYfakOFYzsU2FHPPUKoVkAUTWRRHGuUxtlKxH86gHZorMH6w988vIdFnoZasysaa9Jzubx9szLRGS7sus395iqd6mlM2ZrmEENe5hHuMa6QUaX2qLhZzhAgAHkqPMCTIOGJTGAfa/x1NKN3aEyIbKbiFUALgZd9d0nnUrKc/VjnwqpXEunN33FwM8mu47iMBpEwF9hC0U+s3UXW1y8i8v1Z+dTKaI7QiRjvdo9/iAi0/xHFV95LQCjoKV5jutSr1hGaO8sfrwgIEZVKYcg5Gl5KCRTgCcjT1RmJ12tB9RThbW428NmHpKwWhsIMERErHoBhBSee0YkBXrJbYaPvK+8mIBHwm1dVX2v9HOb954Btf0C7waYXtWw6qL5LSM+NUx76jNR+cPa2ebDj38fRk47RkIyShJfrBYMZQMwcftkMIcX/RgXbnXJUVzJLqnQpxJ4OGVGc/Kup/bxrknNUE5WXaZe0X0I6/bpsQSWXGHn+5uFZFzq3z8nX5BuGftOY4JVWoQ44AgNtO8hqS4dpVjKPKNdW3mps7gEH658Dml97Bz3Cfl7EuAd47vTZXIQTjDohtL0k7alxMT5L1DHCG87n/iChMPo9XTJR+CN/MNiHrldHnk+dr1HymBgsVFLmYeu+kNtFY02jthcSBNMNHuX4LwmFZd1K7xuKL95C22H+aG4j1C689GW15OZwqUsHP0pcY5tU/G6klMSjtHot4NsNMsV1wY4WTJEy/Nav6dxjMj3kblsS6gbGM4xLsNhuZ8CTddLWGUYXaOjYloG5pOkmIMYmI1QgVaOV7b9XSpDatxTcuxBma1hJLLh70G0oH3Y7Ar89cgiAxyBj8fC5NAFoHpMONylw7eVlIrWFgMOaIBgZBuss75gPNupcbTV1acovJrhLboqZ1VKyq7SypZ5quwyOrBcn3Q28aR/bb0Rc9m0au+28U0O2dFoU64/MoZdp0qlfTi1umRvUzA2tRzJqdGI9UgaxXXXey2cmStm3QRw4DYs0NCBR4s31g01+j6JD53XbResYABmYy9Tp+9pvWHYdbMQI3Ger27pWuuqq5cLGeOIkOCNwCjEcmkpud7Q6OT2QrpKKxwvf0cipKVg9yjyc9zT/+vtqhnCLVMEtDZzZPJrpzRehX3tv9pgir9shXHoHYU689Om8lMJ99i+7tMBTcUcxJdrAITvmzkAAGxGk3BxgRx0o+89UU/zSKErakPfxjzBV+corRzlFhIaTnMKKjJwS5US3NPUDV+yjDarQEdOLMYwbDUTTvsfhscPsTg64uzNU4S4+LLi5n8+WLGv4SBM3b+p4TMjg3KquJBLf1S8jngSYv3f7BtEsfuW1GkaXLIv40NVW2VUSTQki/4SbCoJFH61iv9MK9XCE
*/