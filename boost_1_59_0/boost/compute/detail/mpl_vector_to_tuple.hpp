//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP
#define BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP

#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>

namespace boost {
namespace compute {
namespace detail {

namespace mpl = boost::mpl;

template<class Vector, size_t N>
struct mpl_vector_to_tuple_impl;

#define BOOST_COMPUTE_PRINT_ELEM(z, n, unused)                                 \
    typename mpl::at_c<Vector, n>::type

#define BOOST_COMPUTE_VEC2TUP(z, n, unused)                                    \
template<class Vector>                                                         \
struct mpl_vector_to_tuple_impl<Vector, n>                                     \
{                                                                              \
    typedef typename                                                           \
        boost::tuple<                                                          \
            BOOST_PP_ENUM(n, BOOST_COMPUTE_PRINT_ELEM, ~)                      \
        > type;                                                                \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_VEC2TUP, ~)

#undef BOOST_COMPUTE_VEC2TUP
#undef BOOST_COMPUTE_PRINT_ELEM

// meta-function which converts a mpl::vector to a boost::tuple
template<class Vector>
struct mpl_vector_to_tuple
{
    typedef typename
        mpl_vector_to_tuple_impl<
            Vector,
            mpl::size<Vector>::value
        >::type type;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP

/* mpl_vector_to_tuple.hpp
WW3H7oribf5uTNMPiY6K44UmqeDR/y05Q5eXXWy86AoLSR4UL583Dfy+DXKz/m/XhrhJJVrdUi93etibHt4mdcr68XnyWK+LV5hjqHdtu65dwmrlJOOQBdFuaAF2dEgnirod/AJOGs0wVJXB+VINOoaNll6+5N+IsxAchkkPjZXzrGaj8PCmGF+jBNOLwNZOrrUbRCP2gWWC6bpFdqmnYmaTvvIwjnQA5qHpuGJfJmKWV+xNJ8SPQiN+CcykkEoKlfS6iaB6CnoKCGCVJNd88C+5ReKrI+7lzRX+5e7Gtt5BeTUTipXQCQKnyPrjqc2rQ/az+FlG++LG1bVSBq1P6cJ4gnxnGLvfo2y8wOYQ3dVjGJvUB/27/BSNVLixCqfir8f8l8FaaChD1hhIySxr1HN4LwL8a38XSxsvS4j6dWpkQLFKkqVcRW9rZ2+r98VzfxyiheLllbv+N6xl/AWeiAdrXFulzCjPHxw1pay6YkcU2aih770CyxrfM78akwtBJHB3qn5HoVEFxC7s1uysGzbFmoGnoaaxKWQ0ktRTp7tKZCHKEFK1ZMZYmRg36iEFE8yWIoYasFGWLPlDuxO7rY0Xy3wXPlq542ShE5sZU3u7rSV+a3jXxWEa9VE5DF2xeag+7AZYM1w4VTSUEof95l61NGdYryz/GAHsKUR4NtD2UkNbPhB8Ls9pP9Qslfcs9KBS3wnVGUuSwSgODEwG0kRpe6fiQOME/cwYhSnsHH6S81BEjz8+0cwjIQprY0mI3Le6l1ZLInzJ0eXW5W1/qbZV4uMbal5FoZZcoUuGHC/VJqOMe1elQfJ2tnq3t891tTqj2dh1MW+ZnxCKHv+egRAvm9plCr0wwngNPiLVLkgHOezibsYjMbP/DFZJZcuKX1yACjWphuCN7Quup4mGTe09k1VsiEIv9p+2+X93cXIeRNLDarc+2//0d/J7vjznvekFLmPP6n9eRTWGFT3CNoeojc/lY4mgBtZW9gSsw3a2t4xtISP8F6y4AuUN7z+d/9pwoZ3QH41vlI+UM8zpxi21prMxBodW5sCn9elSv4QQBVPIsHF+CeYXP4R3/hbMQXEA3igotxFWk1S8rt6CV5p0QibTegmgwxopPW6uN7sDBXg02pbGdOvWFs9u/T4G3/l8rehnbuMqrmaaivwlwOULAdCQCLIIy8Zoi2ya1hGcueD2GXFl4zBfIbU22otib2wPk9ZjSP2vvz4IxhjXVUdxfvrFd5WI9LAcJ4DTeATsREniiCtYCbKzlKIC4+iMuqZSivH5Xrb6DzNlCbwQOyzeLEmssfJuxKFB56adaH9Md1aOh7kvKMC4FAQmC5+9H8HsCyLz3TaKjnCGVvKibtMzHuOrCIMARQjBzf91Fh+kiIGtZ8Xo790FBHDYS75lcxcOcvYRvdp+DoN28vogQhOpR7/k6aDW/2M0Sg+RKVHJKf74uvl293/c/mGEaTGEKAGOPQzof1pVbtbWqp8r6RU94cBm2zXNzuafEHoQcxWsui2ZYlghGiY0i+7WjtKrS0pcoNGEZwKT3p5Tv6ulgDAsAP/Sl0H9yTSZLxWCYd5B8o9GJ/QNKiMyHDg/ZcnVCrrfqsmZD/852Us5RmtR7sW7hsz90y3CbmXGJR4LSFYAYw3aaTgHJEDMbOz0tl9VS6mrYdY0x3VVg5kQttaqpb/KZKOq5qHOoB7aL2oMEtCFHF3fZVBqyDvCw4jKeOEQvIDIahyojlwAH+UQrCBdgl88Fy05k5Ihd4HdBAzqCc/IweWf5s3a39d2ZUlNLVzbrNInpRlYAQtgVeLHxHShK+YQtjPgOtFsRLvxXuNk7WX2sbZCMLrBAr+L8v1T/u/B+/ED5vuPX0JNJRHCgL6e26JHG8uzgpvhsA8CW/xhMbmYM45eqDCHgr1sa13grCbwfe3+2QfuK/m/SoLujG2Q4QDc21/SN7o2VLZa4/S6F5S05t3gbKIiHs3EfjXu2GScUqn2UL+zsm7E+eCKGDRLyAPkrJw7LJ9Btjbf5La4Tt3oDsqzAojFTLM2onEyM+B8+UEAuG4ot0OeK2Qz1yudAIV7ZoBFa4eQQ3T1tGRHL3zFve2akagxc6q1Ahjr8qOMCAi/LZPoYbm5gEsMK0kVIB7DGNXvUJVt/KPo8Y2KvPMupbVzQ0BPdU9cgyaYgtudegD2k6E05os6ugnRGDZlVgass1Il92E8mLoEun71Pw4KTWYyRZdVRxshm82WOsP/iFpO1sV+TKtQbN0Pt3PkEIOli5Kd3RLiELwAfVUuqk9QxymZWx1yDdbJJI7ksni4zGWu3C/ssHW+wpdeiGsykDXkBt98fxABxUbi5AQEL/ya7xWWTZ0SdN1UuEJFkCwYb0ocwVFCTUZVzodfL99PQZ0EV24/iGaXKd97jZaMQ5vwojNqjlbRGSbpak4xW9yH7bYo1cs6k7lPK7CJsKMIWROR0zVl9m5MVjWdJwagtmdMXW/bba4kEQgb898xOTcbbGstzbkU9hqwq7deSAPTIu0uODoJryz3WxrW5WBVVDZIfkh2mTgCj6wY//3CaNV0NrighylcXdhl/ZkJWd8lNDvMBPz0yJVMaDMtauJPslD3108vbgkSj/0CUHUR3ktWKNxODfHExH6y1GpQRhU66R50tIiv6vIpf8byxkHV2xoZKilQ4oFhvJsHrzlyr61LduS4oTaruXqzh8o/ylD74IWhHxFl0WCiZgwEvpTI2BcrwI7G9XBexbM1ySYLYRAhYp/1yVoh+s0KhLeUckMA/ol68XHNS9E1WNb8CgPMEfhYbUiwTVJlkZUoae2ebve4X/S2eV+Ih4eH5kYqznWNKZQ9KhETEKOMXJvz9qUG4zoqtdiCANQzV2EpuODxognYFiHmHNAZE9vf7OhZG3/nJf1mNXOoR/ZZrh292q7+l2oriOpKleBVE8crkOqmIqaQHbQGB3eikCeWJXGUESqSXRb8KsUIeG2BVImZdqTs/RNgPrVl/JpZ7+MYEzJibtWqZf34Gb3EWlt51vS3brZxoTyEOqSGirRErbI0uY2OaMbpJE4J8sm9TraJdXMi3ih5oefGA78+4ujDjrowR87bvRMFbB/7k1kKA3N9plT8AoeXLlQgYcX95TjM+WsjMxSGqUtKlvrNPqokyVycnk8vz0wP5k8plwMKlMiHGIBo432RzfcEYzEsK892kUHq9nO4Fp/v7Y2KAwwgExDi5+N8E4eIlLVdkuXZ/zTJa8yRZZzvGpOlMR0sAeVYM/S7a68ajBcwNvmNq24aM/r8bsZTp9oG1Wg2KVTXNaY23YVRrFBtk4UYODCNVK8vlZ0PK6VnQibvGVPUjUynl52P0Ug12AtfYK+6e886bXJoFj3xn944O8pVptma5JpFUr1PvWjoOnKVL0BAKqRry3ImMvHIc1xDNRltYpltvQtNXcji0uRfR8sF0qTV9UNKrEGNcB2ewbhII94e7rfibkEuiphL1aLUgZt1809YAzdgDzFP/SyUNtYxl3ERlWhm/5tgt/1tf7+foJZIJkNkT/Bm0D6f+Bm7ExWEcXz5MWLeh3/jZjtm4F9l/i0ciFDTU2ydJAGdVLMuAvyvANWzqEb/z0v3n+sqjF69ZtnObdsQR9I2cDAkx7IP/NqF7z1mEWwTfrVA+51HMLMSV88EQ2Q6mENVtK/jpxQeUZNww6s6FZ/6rNHVgKjyzXaWWCv4gLsuZB/GvhCzzNZfAckLS9WDNgssjTyhXdEuJ5WlkNax6IKOy/M1DVIMs0/U/VCOc2fmNP5B4P6y2lo3hvlGaGY+SXCMsGZjYUK+UVn7iaj6aaZ0JTSajNPSJS6ZciEKnjPU9biHKX+rpKQiYhRsZklqxBmqWik4wkbSKTL2dGoGegldgvrgfNhvt8vRxAznJLmiXsMC0SREBkr7s2rzMikFYKHs7bd9HU7I2d16W8laIrom9l8VW51/cJZRHVA2EUEwULRDkZx5CV9HfhFp+d+eHZ7wazuP5qtkyWa3+z2uhgoD0v+V/Ty+/Tx1jv4YwpF3tjqfdrgw4aXS9NZ/fG9r83e0v4yuPWMbQmQwhYdLN+OkYi8Iz/Vq0hdXPU5O+i9nMuvEUA2X/OuSSoOnZ1KUBuaOXSW/edcvVrn0P2IlJnomUczcLQ9iK+XJMCn5WYHm0pKIzjE3Wd0kczJxv1lmS2ouRA0PFvPRmmv/WHkQl7LgAzBnS5bgHX8BcFj3PpyliusCzHd92O1QBjNRdCYMHpEBatUqdb9HnCviC2toSwxY8Jn0oKNZq/7/swDRixXlv9Gvqi3NoAFay6olDMVnkHQlv291D9asN/hwSimMBy6xXgbbG2wnX3LcsiD+SFccdvyGDaKAbenkln7Lgy+AL1iFKjvETcTASqwvYli/xrVbOEcvyvec5z/1fb2KDByAQAzPmBeFEhGTsT95vpD53lUgDJ4+F81cDnOO1FnFR6pYW6z9Pm7V/zx6s2h/LUsgF6WTIfVY6HBt+9nfHvQ3rPwyGElWlOqo6TVMQMwcDz5bZ7q1DSDmK+FouRDHHIcipQ/es2cbtjiny1x+l7YNjaLk8pfNZmjTUAWhhkdCla0Cy/ZvXom+u3g6FGXWiIp/46IqEhNMZrz2pCP2auQdfsresA9nzdK4qxTqGxyGESK0M+NyfeUbNoLQwWqDtyR7xkSRstQbV9WlYky31Ew9QZ76sdRdZX1dKljS3HgwnFEAyXIeX5PWVHch5lTPPWna0Nt69t0V1KM42AWmQccq6THwC5yzXWeuEHUmVLqR1L3y417PKm0U8CtX/tcWFTDsTTCQtHtOWMqmrC1vWdYAezrEQluQsOnSB1k/S9THmm6mgV3f9+VZ8TNG9NVZ24BcDuLsij9RgdtB3QjXO+/KlM5B4a+UAEShGio8J1IFFanCpk1WfNFPrh69vJSh0acrQZJ6aK+YXOnVMAo4roFo4wyMDEOIg9324/pY4Tq4kHgpyZic9JU2qIsrKdrVWhOx3tJ5qcKFDngfqyUr9BwtC8LTwm652R3OX79whZO1ljtmnG0EVdVT+vTkGHBUd8sgbh3aFBpw9Q+J9hvyKTT0kk01GdWILpddbbUsaJ9nmdRlKafbUYXOOtzCu5v2d5WYmRjFfrDNsIY6QhlctG2xWymvYT6oFWc3z4c2t31nSzCopNWjC2exKreORPOiti5HT031K91s2/J3RygobAB/PBNiF76V4MXJ17d3O1/eEcOfZSGFmuBYjxyWgvdku+cuGKXnYWExaERT5ts9ezXLAm8MNuSt29pfvrQ/+Otoli/B02Uh245Yc/NEFXSWwSY8Ile9Reb/Y/mpeVnO/yVxWt69zqHX+BsJ8mqBosSSEhZASn/vwzVdJqqJmTZvU+FKW1zZ9jcYWWj9WXT0dthytUXvzLptJPqwrUnxKqu5lOZVZ9Lj7rw3CoeGFTc+ihdK9QIbQOWoSM6HETmkF5du9lBuHGpR40lU0oQ2bEdyOeVRkZwr09hF8ZAtWeFijK61geg4U1fXbSJ0gc1NeZCg8z6s2i9PpKILSuSG6Znzm3AoUYq6wlX3Y2l7e33n+vrZza6p8PnCIhMnY4vi1JA+lizN1vkzCCtIl/K7+jCw8AkyD7s5qSR0vLZkHetvVJvrYZj93NeXG/DoDHWw+GeZGZy5Gjy4/0qU6lxzPrWTXNfJsYFl55rE3X0FaThn5GNB11WB16Uk+LU1w5h00uEiW5EdsaxDb2G8xgLIbyJmixgwSaps7pK467QHxftFCGOs4iVMdUZ27+rBo3XhwkQ1majOMz0SjZHdK0Na6B9wrlmlpOA87ZeF0mpK3y99zhk1M6cNPsYJCY/tKMHydN4r2j+kFT1UxIrvsCXFM8tojP+acNEmiEinF9gl0bwyeOepqmrJ9i8FE7Z2PTFTXUkyRhZdN41jaOf3ZQRZsNC99OJblTViipJUJ11Bz2EH2AcrVUlR/MjV6e3K/vTXoCpqiyzsU0rdCWqL1lDhP+vDPMdfSc/7fjdhu1wYiHTUMaPQbvXEINMCezgYQ29sv/43SFDMR5rVxY6Ivv/7VePeRiLMtLSFFGhWA/yVm3ts1+LWgutAse9cZCKFjAxLXzBLLZ6B5QTkYAjXBlfq8YWIU7x4kKawB9b4FhT2/hWGddGHBdfRQcja0JuYu1umfKQTMZh8I6MQ4SHaSaBzgQrv9CSn4fgq+6zrAOIXebEsV4vteuqRzZ5vjX2OB2/RkrUoI4TuZjW8V5PklibBiAXbYGZ/LqZ5kSjGp1RpcqpUUS4rIH+zNaLXomem/V/K1IOUJBzg9NH4nzKlbAVKsB1mx0hRDLG/u7l7WWfnYrcjnBeqW+oAACz/08gBaR7Z9JCeMhbSbjvyd3/rLrhNB4o0u8ZwiKB1a2fYx2676+FgK9jPLh+hyCYuvKNPFvxByu8uDFvGGlsNPQh8NdYPVjsj6rWCpbjAoYYT9QONUrcYUGHmQHMtSRf0VZWngoz3SOvPFVjs/0acDktsMQdZQufC/423qtyFYkIz39ql/q6h0mRcsOZIxyxJUFJNGSsFf9foQs6O6tAsJVvaYi5x3XYRYWMv/tM3dcZyfVziuDEsQwRBddcsK8Edae6Lglc8XONecYKtlWHNgosQHxKcsLb6hxfQpuHDYLjFx7P4RB7lAQ2QsiJqLldRVMnWdwl20D0wcNiE2GzRjRMpwACzQ9RpO2yxFVV0KXKvW7wivSsNkQfENyHIblZwrgkPVvRSvoFRdzjX1vtD0O2V8CD8RdZUncILuevf+fpw979XY93vqQYGeE7cAZogC4rSpZiOHMhVt3oMb52+KrhQ9MUwWWF2pElQAKGdK2hvCDPrFEUOhcU9V74FRx5HhL4W/47IkDVq9Ow+sQ71ILu5GGgJI0aR+LdZxw229YrjYRQZG6HeQf/Ud2UGh7QaU2ybBy+PQOEoGrxr6oDNSjBLAV2E9liU4HwA61RsKcxzNgV1l9awot6j4R6m2vbvQ4+KfQrVlH86xMvg/ble8EZEmeNqIAGevZLEKUL/FVRKSVcUjTnrckPp1PW1VFutMI0XyS1mueAubJ49ub14c3+kQSzXX1PAeFHIxgrOqOLQ2862c/4sYsIY/Opzu9/bPAUZON85G1EQcVbNUEMdCWPf/bnm5v/ClvvZhAu2UA8UphmfJRNeRGxr/epvTqp5XYwKOWcwnjZJMkQd4d52tWWTneoyVUm2XWLjkXB3hwZZ0E1UkpJ2Z1/YJtomlAhKLnYZBAhDSfwH/HB0rivtfWu21t73Z6dZbyWw3SyveRZvlO+ZBuAdwz2ahPbVjzdaRM7OEtZBBVHF2vC0vgkhuG63fUqcdkLZW/UhoOv0b1IlsknDb+W5IGg8qX+NQWv0ErufKUeTT74AkxEH6h+JXXZmY17eY4kyj92xWq/UpZ5TSxl6VVg2uZ3qjbsv1/PR4SbU+sLSi+CZE4bNzhPVIwtd9d8VqpkuWZedIdcWJ4r3se4GTyu3DbGNqukYyAiSdfTBQzJLLlCszxjyQGK7gbvGmGPTqhLZXR/Zvv/ExcMU3L0zG4dGAtYl10bZwJ+prDkFy9yNVGXj8LxblxNGOHDXTfycEtrVtA6nCdA+TOx8eK1NCcoV2BALvntm
*/