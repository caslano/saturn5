// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef INDIRECT_TRAITS_DWA2002131_HPP
# define INDIRECT_TRAITS_DWA2002131_HPP
# include <boost/type_traits/integral_constant.hpp>
# include <boost/type_traits/is_function.hpp>
# include <boost/type_traits/is_reference.hpp>
# include <boost/type_traits/is_pointer.hpp>
# include <boost/type_traits/is_class.hpp>
# include <boost/type_traits/is_const.hpp>
# include <boost/type_traits/is_volatile.hpp>
# include <boost/type_traits/is_member_function_pointer.hpp>
# include <boost/type_traits/is_member_pointer.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/type_traits/remove_reference.hpp>
# include <boost/type_traits/remove_pointer.hpp>

# include <boost/detail/workaround.hpp>
# include <boost/detail/select_type.hpp>


namespace boost { namespace detail {

namespace indirect_traits {

template <class T>
struct is_reference_to_const : boost::false_type
{
};

template <class T>
struct is_reference_to_const<T const&> : boost::true_type
{
};

#   if defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140 // vc7.01 alpha workaround
template<class T>
struct is_reference_to_const<T const volatile&> : boost::true_type
{
};
#   endif

template <class T>
struct is_reference_to_function : boost::false_type
{
};

template <class T>
struct is_reference_to_function<T&> : is_function<T>
{
};

template <class T>
struct is_pointer_to_function : boost::false_type
{
};

// There's no such thing as a pointer-to-cv-function, so we don't need
// specializations for those
template <class T>
struct is_pointer_to_function<T*> : is_function<T>
{
};

template <class T>
struct is_reference_to_member_function_pointer_impl : boost::false_type
{
};

template <class T>
struct is_reference_to_member_function_pointer_impl<T&>
    : is_member_function_pointer<typename remove_cv<T>::type>
{
};


template <class T>
struct is_reference_to_member_function_pointer
    : is_reference_to_member_function_pointer_impl<T>
{
};

template <class T>
struct is_reference_to_function_pointer_aux
    : boost::integral_constant<bool,
          is_reference<T>::value &&
          is_pointer_to_function<
              typename remove_cv<
                  typename remove_reference<T>::type
              >::type
          >::value
      >
{
    // There's no such thing as a pointer-to-cv-function, so we don't need specializations for those
};

template <class T>
struct is_reference_to_function_pointer
    : boost::detail::if_true<
          is_reference_to_function<T>::value
      >::template then<
          boost::false_type
        , is_reference_to_function_pointer_aux<T>
      >::type
{
};

template <class T>
struct is_reference_to_non_const
    : boost::integral_constant<bool,
          is_reference<T>::value &&
          !is_reference_to_const<T>::value
      >
{
};

template <class T>
struct is_reference_to_volatile : boost::false_type
{
};

template <class T>
struct is_reference_to_volatile<T volatile&> : boost::true_type
{
};

#   if defined(BOOST_MSVC) && _MSC_FULL_VER <= 13102140 // vc7.01 alpha workaround
template <class T>
struct is_reference_to_volatile<T const volatile&> : boost::true_type
{
};
#   endif


template <class T>
struct is_reference_to_pointer : boost::false_type
{
};

template <class T>
struct is_reference_to_pointer<T*&> : boost::true_type
{
};

template <class T>
struct is_reference_to_pointer<T* const&> : boost::true_type
{
};

template <class T>
struct is_reference_to_pointer<T* volatile&> : boost::true_type
{
};

template <class T>
struct is_reference_to_pointer<T* const volatile&> : boost::true_type
{
};

template <class T>
struct is_reference_to_class
    : boost::integral_constant<bool,
          is_reference<T>::value &&
          is_class<
              typename remove_cv<
                  typename remove_reference<T>::type
              >::type
          >::value
      >
{
};

template <class T>
struct is_pointer_to_class
    : boost::integral_constant<bool,
          is_pointer<T>::value &&
          is_class<
              typename remove_cv<
                  typename remove_pointer<T>::type
              >::type
          >::value
      >
{
};


}

using namespace indirect_traits;

}} // namespace boost::python::detail

#endif // INDIRECT_TRAITS_DWA2002131_HPP

/* indirect_traits.hpp
7l1FoxrRqwOYRzJdfXTANltsE2PVtcywkekwKY6/7Ral2C0yYstkQ/Rcu7v5RBFrqj3XikV7mdp+nd1OumiIIkR/21E3NvGp9Vg0gmQwdP7RE7x2s1Qy9Fw1p6owNMnZB32slq8Yrh3Cl5Bcn7bBS4rBlqn8O2bP09AWIY2xq0qtAPXGcC3CjHOfIoLenCb6DdHXkMStPI64ELsKKXlM78d5xFAJzPXMYJL2Z5rN2l0p+bk5JvcysSUdG70Ta0mmZW4bL4XZMlbzoJmTKw6os0+nIu6/z6/mq/nVXBVCHSARp9E0hhKIuP/5X8d/MQeB4omuRF6c1oiZ8xdgugb0OxPUJDFp3dYsopmkRbmtSPnn1edAX8yR6wxn4hMcOCZyK9pgtFG5r4jHRC9z3kCM+nMGvcue84c0ASIh8nxIxGPhGUPh3JysAi/ujtaIFIkIyweBxRR7Xp5cq6GiMz5xOZy8ni2HzY97++5lUrf6ysWJFtxiWmC/VkYZjVUbyqScXL26eOvVdKdtyegbsxlcHEBb/eOtAl0FY2vs/8AstiGzUSGoSv0qnY4b/2+14w6ql+Nciz8yPnVSlDHiafbh5lWbvZ8AHizh00ykatST24VK8faK+b3YBxYtOOKu/4GpVCU7UIAGRm4nhRCLtMRjpX0v7NPPV9MAX7QaNXa98PMglU16iU+DsSIdKTHme3UZ91o645uT3p+iZ3grsb+56n1G2DSyPaP0BqcF9ui7OxsmrGTI4qqw79gjWbWgfDe753xI8vP0u0Ej8WNzAF4flqqEFi8RvxGnpMg2QuPq0XR6tHbzQWqnWjKkNruOXSydjhUs/N+lkj4vXlbL2JXlkBGqgOBYD4X+hthdA6KrWxjvqq8yC6W3P1AffSNRVru3OCKU/0mBbp4FhWtmYNmXBbR8zgDWOre8+mOhvmIu6N3hFOhySBdYcpsK4Z9AhnQQ2uwEQt8l81PzxlY5dcZhyHxPYYtj9vEm/GK4IYWa4scWWk0TDNQc4O6SU6DCLeKVh8u3DizETK3tK+y5Iq4PBlOfTBzBKSdwcWHOVcDk74itAJLcVn3YqgLm8n/w2RMVFBPREuAKnRby1DxJGkTqjq3E90uv845GD2MjC8pG5bPOsFl3rJKG9czSXX1dCfr3xybnxe1WcPUDzku+yo/c5pqWyMOtnLFL7rVUOQqtUjw086mKbJA1niDXOTPQQk/gNco+hQOzh6uAErPR6sWVQzEF1ekqEU9p31XRTin2SWpe/jnFLToja5f/D5IDMR9JLQCAQ0tdfdt227iy7bt/ZD3qG+JOL5/2jrMcKZ2T5I2SKIltilR4kSP/8f6B83wwLwXQa4zEnBMCQRDEpQAUqpbR3/ssWwQtXmVaNoj+3d30JhvUJcGK9fw1/ftw9zxVLL80Lzo3R8sfEzSIIGPtU8W+yWQy+6Gv/0kAdtnoH9kI1UJY3xxHOr3Z8zzfXWapkc/WIYfMwbPEBLoDKoN37xUJQ4sQCLU3/WWJSZ3QKmcL3cLCo4GLeANLxMpLQdTAyGL8IWEPSpSG3GfB1It5JUXM+00mXo01y/eP4dZCZPUYWmnzVqWz2yU5nhEsDMgkKz7PHE7SEIalEuqZwD5r0XsQ44g0yzT9LDO0LAw6DHu0HX+ywVHipO4sR2IYA/eVrzL0O8O3WAx8iXjjf6632p8GkKwhxGhpGtVyqZUoF32a6dXsnGYeBZ1rW5eYD4dteOmYuZ0R4GaUFVGIWQ1nLtIiIFu5TTiyJ998l1nqIrJJi+CTQpssYwmzDzbkY1xyx656f4Yph3BpQyxeD05YJELML9YSm19eqvTYNB14kfXIud2dhrKImKnstTNEt6abmunNI/LctrReviHUicNHYq/yAEkSSujsxpugVBWIrjmtsw/Lze2llGsbfnYSgrX8B8FsqDVhK+TM7VgNDhsXK5tknqMmXK8+cDEOcNAFUsrcXnV8w3CpaugAt00TLg5+LFyVw2RU2ztrnXA+N7tQCphppUvtmi61oPHkKgavWj9hy4o4msD5Eo7S5m532kJgfRJ2hoD6EsM5CQ9Zj/c/xVr7t+YvjqEJe0K0/6BcmCxUDksQpV7QuYrZVmY4M5Vp7q5EF/eV5QNz7zgXlu8bcqFhV03LYoTOJNxTjCBAEgbgsbHjHdvcsW3btm3btm3btm3btufm7pL6kn7t7of6K+n00j/KFkQF1Sxy8UlomVGHlCsVqHZPxEmKHsNF7WG+rDaPFgTDcu3KD9IpkrU+gLMTNBlMRH4OUvt6xZWcooy46jfROyxxL0hd+IOC6/ByT7+q+8eWI53hDsEksGakNlK9IjID1wZUFLs6nMiwI9F9CKXq3IQaLw/e9c/MEEYcx4/H5IHpklskdqUCDQg7cyDcVOx/LV16NXfpAF1ntTlJC3nbcOxJ8blTlsDkaAJrGr0hPt93T36wemQW+/0r63HRamYrq19btpPfBr5Kk8DI/HVaL+jfJMYUyVwIo94Yvh/dlfWM8HPAJhqjrNkKTnCE85+blZusQdLdYpxTt/QmCzQPs8xPWH9GVNwUNg48x9tjXRHe6z/O+Rj++dCp59WzIPy7+gKOccp836YCYlSMNXqAkJn407TeJwLfw/UZqpMSNbAZ9oY8yBmYVev2d0IRadDm37SSJJMQid89x9PmY/wBVkAvHRqKZhzkULjZDqfmxQbB3KAyzQTIR2n2YvjRyN+jOHOcoiu2mBJq1CK2LilDFVhrMsiccmOI+hsdDqBOtBTt482KyPujIAvFk0ffhKtCIuQDbP6SNb94OBpVAguFrjDiIETdKa0auJnvWIP4pKN7mNvZF25mSLADkUh2MerQXiGGoPSNB042g4Vz2kPH89JzaFmJyXT90mxXbvoaG5NoNeIweHXAEJ0bqTykPE9hLvQTdpB8KMao2G9AWa8fxNBES5wgYpqV5XAAPomCYyI0PRn/f+6dXXzTg9xLJblFJ+AH8T8tjEWtxeuOR4L7P9tcpGt6T18XAwdbD1eu1eou/JAS+eS7jDDqZ11do7nzD1LNmDZVEpSApzr39QtK0e/WVNeYkrr19Nvv16kU/3Twl9b2iGLwyTWt4Wxmx1Yt7kksl44zGBezzZ4ZoyYA6lWdBMosCA/Akra9HB1rU0vyu2ChfRqhEbUWrcguNgcbB6jtg9/mtszHCKTUHsgF9R9gPzz0RpQ2UVXnktCa16nUOD9csGuAVkeJb6hRkCO82I+qgvDWtQEsyuNUfEQAOQdHjH22vNo+7veuJZp2VMAj73QoNM5+5KUcSd6Pvq8ncF10vj9dX4iVGryWSi5qjgt35nlKSXa+MK69icPuJd5/LMR/rF16js+vJzSV6rNBw8WQM1j/udsCjQdByoFGq0RGAdQa5R1jRjIT5/hLH5Giz2gZQcmg+dfBZ6B3p4cxYY2dVz/cGxSvj+NLgV5ZeKE7QDk2SGSN7ZJ37OSYflAArfp/x5Bb2u49eH0jAFp5JXZ9gdKqWVZLJSGc+BI5ILrId42xmjh0r2I6GStIWyTTok6ZEhwGK/CTyBnbjVjwCI5ngyOeTbr7i1R/3pfK65d8n45KUY5B1U6oo+vPY0u8Eg8m0fau9zMlQ+Bfdo6avdKGboZU7j+ZgJjmUIluLvC/vj3sfRwfmMxxAn2mN+xz7K4p1XF9SGcI7dVs1eG6ZVEY1TasiQQXnbgBEpAZXUsGI/6D1M/ZM/vqAG61JWNVgh7zQAdRG+Q8MVGXnJ9Ei3GDFigulDMAc/duEJO9Res5o1u02oTdlBeZMrycedq/EIplAG1f163+wVtPDLRmXzHWdBHOtCD7+72/+pzHfODrRf1gUMzWFgg/m6v2WXw3XdhVdQ9/cuk0AJjK/eMKYdyyBg1lQ6A/Jx9Mzh7PpzOW5yVcwXj3Rv5aPK26ijBMUZ7beYLA9B7xZhov2Q2Q46Fe8O5/tter5KuDTgGMl8zVC6bRIPUqfmGDKRCW1c9CVJrHCrrpyigv29LPoOLBELpGgz5YcuLo0lXlMqmCEWi89I7x4SxZPJychUEYs1x08yKAILzB9JWPi+xWCyDduT7LdsigivkEx0D9TKZjzAOYXF8gt/TvgAXLHrkMbidDboipaFasmXCeCRIoyRqDXSdialdqj/IIGjYH0bW/APk7qDb1758CrNnznYyebBAmY8BRRTPrKWLTp85Cli7ksmRqBkxUFvUKGlMVpn/G5HgojhSdHzkxUH0EJu5nZ1XmLl5CCovkWDSCP392Oz0aUNH3T+Z4JrJExXerVPSYNvdik5vTrM1r0xoQ3Mv2dI74Wu2eXQ2vNPcTswNFlrl/Xt+/1iwr272+yZemLVKZFXsLFa7CXE3N8X6bG1j9IrblfIqluWcXT5RpwLjraN57rJSVQlfg2cBfantNGYNA/sy3ixmIbInIpR0d3GyWshaxoxH0yPGyJ9NRXnApudArZC41/zIWL8mrgMqBiNE0TdvOD7R8LGcNNjL+zt4YOiOAUfSzWfn24X7ZhbFKEgJXU+BTCpFiH0SeptuyzWwOyczN9bf1Y039K6oT3fs8chEKerniTRr5xWoKOtlNTFoWoSdJg0y4PC5kZf0pc/+pIdywCcF2uPbyNeYU1QLxvxNMuN+I9ZEwrAR0ReymZPp4Jga4EDqoXmYMh35Vfnm2VDaA0ukZRYLDzD4ufFssV+vlbCftPHYU8LITTBbtDvGXdbYcUvEOPG2k5uMQc1TCocOEgg8dL72ghTcvHDeqZy5ZfpI8nW/3xfMeHhMyEraLTBJrvZN8Pf1ow/7RE/kjdSCQwbVoHsdOlSWPrFpIJfLzOoL4v+G/O/xolzwmyquRrHNpB8PBA2tRZwdp7rD6xqaS7+MChUOrO9LlwhzaIsMFGIZKil29LjiMOITJlYrvJKGMoOwSqBZENBG7bwlpRgR2ncrblV+Fwp/1DKFWHh42INLJIgFeOzZXBbg0bUm4pT4IL9FvsCNrkx5guSNbQm7ysjq4YiHudBGePoB7FtNZUJVLztWTaA7z0ryUhU9bM6FLPFpVxSy2eiNJVspOwBQQlo7r2n1cizyIhGMHmh6l/36Dj1tN5fmN408pKdjxoS/etcdcvo15eQz8MTskuecBihPfnIKJAAoWCTVxNYj8CavZDmVqv9O0e+l8Ym92J7M+RdAXjRQD3DgpaW0nTHskkv5lxiv6FRAgi50MS9hmchD0vhl+ml6eQRGurWniVL0gffYyhMUUvGsLmVmdZyMDuGmzqXnaUGSITOhFnFGdDcaP+RQUj8KkAjJoZMLjdl37Hc0hCcWPMJs3K2s4yJgIdRbdrmoTSmPE5OUpFYQWDacVamYUveiYCgM/Ll1KIzIJau1hbqk0CHWZqT1h6jEz2LV/AGzcLZsz/mhtqQFjSXlDDWERNAnN2mrIQK5pnE3TcQDE+T41D205h7cvbOEncFVZyw1iFN7SUnHIm+JbuIfMyM/+Efafwsohg3DmwY/YTAH0fbB0h6DMguovZwXEqGloD5KL8mqybiLfHtzvrFn8Jw6UAd900EyoaOvQ1plZXrQRVWE2RXvT2uPwkcJ3F1bToOBS0+y06lVxuJDl5tXldL3qpvRkGnEBa7JQ/R6H0ugkqAPVrKYUGjDgT8/eOR1czJOjOseb987vu6VUGkTAuZ7CiuFqv2oW1ZyYKua8laW6CsZTgM8etM/hImulnANF7C9e9gJUz6qmXhBRFeSzZySh3Lx86BxBCwVFDAsFoNmFjwGZXeeNWVi83XP4USbeOeP0ZOHpqCpKwNXlOdd059OKTMYww1JdMc9h9jdC4FU9pivKqwhQR367QOMsXXPq98cpNdTuKCxRNeSFa6uf844OLWgtzYNu+yyb3YOrfcM58xWgaRuXWmnQf5bIpp5iO5kECPvMbPQmDQAnqsAM5MQLZ4HR7jdEkzKOKjWhNUvI2ASaxDVycumrce0NfWbC2A4I0XIf33vSJDV/KL73lglZJQ6HdN6Dms+XMfmJk5V0UycjMobbzS+C03Egy/Qa5Srp2mPQRPnQRmrN8prST9vW0WbLbGfoXLKykXle59/cKzJZq0gNfgJqPJtbhQqd4/RtPMDtGnqooKgCFrtnaktL75uKZH3rUcndB9Ycuv8kC+8kFhnfKnyXaV1N75s499UTxgN5MMlx/CNcNSnkoGEsn2mGEjHmiAr1RcJ8f+u/6gBn9iFT1k0hws+hZZFnARwl9XbVl/HAoXzyPIkL2YBcBMweUQC1YHRx2+SqSGxfCkGeebvqNOtedibyfvaHlavhqLMPWAokHTffql4z6QMsfLTXrTABeuN816uklzRCktlQQX9VXwG0x7rKBWBCJ7P4mO1Qs/gy3wXlQgZyV1HPnRjjIR0rdp0I91WfUM2PePG9Ql0t4cNgIeWNCquBKNdSbBJZuB5twgCiKbUK1IoWoVkaPW05UKDOLB1bauEwJzaJerJYyb4mi1mw6JgbcDqpN+VE81vfSF/RaWBYrs05LwyT3q3k/bq6iCFS4uG5P9Lm176xzBHSgzMv2Hd2Iza1+skgt6x0ZtuKm2fX7CmBKOjG8/9wMLS/nGGzFEI79DxJdXRi//ou7TW9tIeLC4x/ETdk432oiFAcfRTgsj8lVKzqyKy/tbv7BPeXKRtIKe3vr8C1KBUFFuHxNuO3bTeETBDXltUXve0Pdr/TEyFkWouYZkEUNE857aNd9E51cOWRBASHWsR5ku8NVfNGum+Bn4Zap54QSbA/pHBIQVJZkyef3MoYoqA6Uka/S87bZvYeqo/DeTzuqzjtBajx9vR67kUcJ7B47WDbh3kYPzScgRJgss+/D+zWi5wmsdAHqs5WIN7KlY6pfipwYMves9d6cui0vNCrbWXXJsiTEJU9AB0Jw28s+qBRxuOlE1lBZlbSgOdb1Z+Vcxi+FY20he50LMgNIq50lm0zvQVUo/H5nDFBmQR5KL3LK7BfyN5sT4frcnO3uHV9O2PsNrXTahmiQd6zAn3qCrnJubnM5dv7krbA2CnkVPXXN804RLSq3VbHNqO1tEBmtztOWCvfTNEIO6uHj8rNXKObx3c4QYi3MPjr5BX92IiQJp5v1bkYOytRZcHYFgZ7dXcywAWBpXR+ri62w9gJg5CbDF6DoiFugYu9PX99QhgEXVtXIInMI225aCwXQUJFo6Cc89pRz6jGn+EC/SSgwET/ojmrNTgfKld9mLcQ6uxWxLWUo27QrvzPWtOiir54sNo6o/X7qzcbaaQTZymqWuzRI0Xjg4m04R5ILnxFVLPb/G/XenaX7Q6ze4RFQsbRUvgKT6QK6+o09w2GehgmsatRfw2Koj6XeI91nQSQrfnzcqyknGEDHABmCjpNrMWtBfnqytIDWEIJsl5jrdvGdICcdkt7WUDb0G86Gq1zP4YFUufbawFxnOY5LBuckpdvh/uugz47XHYz7HCyXmr53aMV55FqAqP2woxNszNUIea2+00JmNneo7Bqv6S/DaXXTUuLA5Nf8U1Xl8bOD2hsYBAP9yZsx0Qib3hTj8SU9dc/SFcsIAWepiBYocyGooUEukj9/q/2XjillOSt0tGe8YH3bNFhvzaqONXMb6Lpl6ScAc9kg1FC3EkUqsjTUPucKVm550Ua0aei6sZtRGZ4ENdWLC3GKFyyRj6tA6fFJbG6OaHUSq0PMDFO9Ll4/nPs65VArk0QiCmFQxQPp9bt1RGAyu7vr05hChFYEshSpuVLkxGAn3FRUCXLNGq3PhqWM0pwbw8dR5jRj2RivK0PTTITLKezjoeuu6lVE4P1ICSUYwHp2Gh9UDVpHtHpby73RpCj7G9ieriHtXGh9BN9AGR7wwhIpyLH6bveB3Ga+AXasqB2PI5sQ5B2wc4IbPp/A3/PfIBg6jdEXDMpz/p9Mz/s2jVet/G9qxo75VQO9IFdHx5fCCCSM+kHStQTBJmHb1WJsRy8EKsg/gw7Pb1wufO1v+qB/hDBFG0bLIJgHQYgAvl4SAkoojE5Vcyvi+NT31l1FQwNMD3/MKwqUV0HahNcBlGC8AMig+Xwx3LB6NuyqEFssQUeQKeq7ypfOWxcPqk4LAXKh7zz0kmSau6lxADe3g1OgPB48ToMDuXPVvtHSoU74DEuSV3GkfXF+ZBylKIsG7i86jSZCcdGTdMCka35MmuEW+WM9b8+D0eqrSmhfXWJrhM+MpTP2d2Od/jc2XSZFKY/99sJJh6abygQWNsGlvP661EOaL4PvhSuk5LUv+Dt/+a+ppaZnu2xFvkmi4MqIxFCY6o+NKIMTFVWS/dpwQ0XiRepNQmkpRMoTGu+6iIG+pRWUhUZMZDXYXuOomM1kbbsXIHCXffVrG8WQud1VavW4WzRWjElmxVTzJLkMwWh1llfjWAFuJAzwattkAO+oJsdbhoCybbYMQedjoAEmIhhAmJOxa+x/QF94NQmjql4td/U56YdHtEj2aabZHutCmCgCCStZP51hxDYMfXCf0IQObEUZ1N8C8Okn2wu8eO/w21zHe5DLhwwQjbsG1DaQoAF0uIZa/ZWpb2lMRzj2xWSlhvBQahCdH7CLAGnhS4LYXD5D+lynsydFFxpFZGU0+YMh8xAiDXHiEhzhkPH9OeDL0eRpkpR3avFYh0rhuheqD8Jb2STZSEfJ6LD6DHLc4MKqqLBJaNJVeUOa4OmXBDKLy72tckEZc8SAetc4huC/KCD7wArVDITBN14QvWifyIkUGqKPN5PLsH/Suis4W3WknBpuwquQx5oQLt5L5D4YjZgcAZ8metaEukWRp0cCFfMYS/foQMe+Qp8oFVD5t8O5DxrCHyOGUotyNEKw83SFAwXsUCum0wVgY/Vgvw9Al1YYjOkJ40WsGm6kUHLG9IbrHay2RflPzdf/FzzBvUN5PSp77D9LZpECWDajwT6KtLkL78bHp4IibHZsjPPAnqWJ3SYu0vulHMiJDvbEuftc0P0W6Hmu26+ijcPyDG3NPAvbNQiIWbIqEdBPFXr/TNJge596ic+N88Ovd22kL/NKVZJUXrX+bz6eGsWNmF9GqO8CiSw8LtA0+nDRGG7+x33x1L+D3SCwc8fRA4fYZvjNU1JMRXtW1wsjAuTnPhb/CJ224agF1vPz05e00nohk4932an3wGxCz1ACBQ/ED9CKhZGW9NDEEcRmnWo3oex23krmg3buGxuJkQ=
*/