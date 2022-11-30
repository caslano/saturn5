/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    compressed_pair.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_COMPRESSED_PAIR_H
#define BOOST_HOF_GUARD_COMPRESSED_PAIR_H

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/config.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/alias.hpp>

#ifndef BOOST_HOF_COMPRESSED_PAIR_USE_EBO_WORKAROUND
#define BOOST_HOF_COMPRESSED_PAIR_USE_EBO_WORKAROUND !BOOST_HOF_HAS_EBO
#endif

namespace boost { namespace hof { namespace detail {

template<class First, class Second, class=void>
struct compressed_pair;

template<int I, class T, class U>
struct pair_tag
{};

#if BOOST_HOF_COMPRESSED_PAIR_USE_EBO_WORKAROUND

template<class T, class U>
struct is_same_template
: std::false_type
{};

template<template<class...> class X, class... Ts, class... Us>
struct is_same_template<X<Ts...>, X<Us...>>
: std::true_type
{};

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)

template<class T, class U>
struct is_related_template
: std::false_type
{};

#else

template<class T, class U>
struct is_related_template
: is_same_template<T, U>
{};

#endif

template<class T, class U>
struct is_related
: std::integral_constant<bool, std::is_base_of<T, U>::value || std::is_base_of<U, T>::value || is_related_template<T, U>::value>
{};

template<int I, class T, class U>
struct pair_holder
: std::conditional<(
    is_related<T, U>::value), 
    detail::alias_empty<T, pair_tag<I, T, U>>,
    detail::alias_try_inherit<T, pair_tag<I, T, U>>
>::type
{};
#else
template<int I, class T, class U>
struct pair_holder
: detail::alias_try_inherit<T, pair_tag<I, T, U>>
{};
#endif

// TODO: Empty optimizations for MSVC
template<
    class First, 
    class Second
>
struct compressed_pair<First, Second>
: pair_holder<0, First, Second>::type, pair_holder<1, Second, First>::type
{
    typedef typename pair_holder<0, First, Second>::type first_base;
    typedef typename pair_holder<1, Second, First>::type second_base;
    template<class X, class Y, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(First, X&&), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(Second, Y&&)
    >
    constexpr compressed_pair(X&& x, Y&& y) 
    noexcept(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(first_base, X&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(second_base, Y&&))
    : first_base(BOOST_HOF_FORWARD(X)(x)), second_base(BOOST_HOF_FORWARD(Y)(y))
    {}

    BOOST_HOF_INHERIT_DEFAULT(compressed_pair, first_base, second_base)

    template<class Base, class... Xs>
    constexpr const Base& get_alias_base(Xs&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Xs>
    constexpr const First& first(Xs&&... xs) const noexcept
    {
        return boost::hof::alias_value(this->get_alias_base<first_base>(xs...), xs...);
    }

    template<class... Xs>
    constexpr const Second& second(Xs&&... xs) const noexcept
    {
        return boost::hof::alias_value(this->get_alias_base<second_base>(xs...), xs...);
    }

};

template<class T, class U>
constexpr compressed_pair<T, U> make_compressed_pair(T x, U y)
noexcept(BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T) && BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(U))
{
    return {static_cast<T&&>(x), static_cast<U&&>(y)};
}


}}} // namespace boost::hof

#endif

/* compressed_pair.hpp
mjgK9SF9kZruv2V0DR/IU7Xv6+JGizltps35hC0PSNZl7vLHUaQWRcfTOBNrZhgGF0tOvyyYNJcf9pC4kcUcCzBrbUvhBItYjfH/RqtMgR1gHqYZjURzd6xDVll0w00rNdd6T1vEM8p+pG6nCFuJReRNJchr1ju5oqbAqLsKfoEheaVbtjPXVClGokUEhDXI8UaLiPmx9cOLWtOWmSoDY19ebeOpFZxEjKqfiKCX1iTV2TQ971DFKxKQfhbwvYKO/GRHohi3PA4Q1uMoa590CWA0IJGnJ8mkCHBi9DWt7K0fziAf+L1E5JmiKqEEraGGGhRYE6yFaooIJUHdP8D6gaVl+UnuWcrQi4iDXDVq2vM1uoduOoqX1Mjn32dZfVdzPYOMVaJtjuGJ0jbfiDGCd/wJzjghCqZm5KghCJEJnbvCEP4NQqT3AONJWBD2YDVUL7MKuhTUj3UqG9Wk8z1mLOhGKH9JKnQRansXGMbVd9LWtFyRreuEudqo00mj0rIlwjdEn7RoNyZ425CxBUo3NHddakQJMJfxvHuW7ZHw57nEUuzjJWB+pIPh9Nl5+tn/HlTnk6zETFiD+R6pAnesQ39AwQChVXZOz7GuC7vIyQrf/huPSXz2zt+nHgCkFw/p1Im+9As9tyj7SFqRLMwQfFYGzXcvJuoiMQrUjE/Q8qgqk8RSRr53oibwQd25jLMKVlRWXv5g3sXf0pMgVUmttx2FEo+VxtumwPrPQOnJeDxzVajY+CvsI4ZEMXa1b2tO9YHoKZNw/W0ZWeRzAAelghfEUJK6HYsjLZCoLmc2cCo2tp1vgPOZlddW/hbRDzD+FBbQkVVH0nhYcWQ0ZMcCfD3JmCw5yfRqnD0d8cn6YcdrSWtrP9tr5HLj1OfJ6lb7pis6WYKh40F+JnuSkPuNg/qGwAsoPtBmh+E6OqX0mxzjKctZ5yzzHW03NrSEgCX0FCivuF8OkN6Xk1pVqZg2RB/2AzVhbQoPlIf1UV/EY4Qcc/ovlT8TM5bxhN0FOl/9rMWsjXbmL/GFMGYKAJI/RhlpT8nsgN83lx74hFwaq+3akkKrcbAQh7bVC9gRfYX4dxVrTIFdOyZg6YxQsD+JZgi/t8AxY1LgmuN7JT83n+bQKT2Y08s4zo/G+IZdGqSOqKk5ka/AftHkCIY1b8ahAAJzx8eW5pt87Mb2O7vYLZxq42AnsFrot0mCkb2j/WgvZHj2kHRPIHmPmiao/TKP/kHcfvVg0i3kuH52/6u99NbrsPem94v7po0/cHr2OmL27bbn5AzA6/cjg8KL7z6LndtbKrbfOJUSeoMW3WvtynZJULtJ7/afpNjAZcy4u2a+jYmbeDn28IqnmrlV938LfiHFqxwpU+ioA0V3D1HbAq+h1lK1lV4v+l7NQYu/D61pO3fdi14U3dzsPCV50MUNx1KnJkf/9fmwb/qQYE+jYQBSTTqsGhj84HDZxPP1Ez5ib4nBpP2OQf+6vZu8ImI+2nG5+fb39mAZjhVuiqRqT+AlM70QtDrigtg2DzyU9Xtkr5JqxBJzOQoq2Rx70MsbsRIxJxpcQHon1JfWxTuljft/Ck+xGjSSAV+s+t7tLs36CWUXrtBTP3P1+H2rwajxJf2WEVb8LMYVeeqAFX+AsMqIMpKiE6QVswYUHfApLOGrdJbZPfhp7I4vK+fiqOhN3z1v++hec7nwf0ou9axbfpqC9+jXBF0p4BCK6gVMsV3ElQXFAXD8Y/QehHZPyYL/4Qi69xPey60+kLsTp+JOB94rH8MoMBi4lBreBtwZbNmYgyALVzPu3U59gwj34P1uRD2mvZji0/ZkjvzEJmj3y9VdRZth0P7Isf9oG3tS+BILff5U7cGe1kHmHCXILsJk+HFLrbPkoWmopTLp7SPDANX4QZgJpGt296Ri3I98aCk3fhCuT15mTVZdTOAGPO0k5CQvvRAUu26DPPqHHEJnFJzoiHL6n3Yp8D40Gl+bGwSjagavLf6zylyC6zVJuiuKgqVWLrvAiZYdDKSiToq+eyOlMP5lGEB+9FH5wL/oOCmFrAyywSyXW4VKu5NL3dWorof3GwLqObMr4UcBM+2ydoJ6baGK3V10cBITDhNr/kXclGnZiGTxcq6v0gP9BLylYl+DdS1ceJnQnxueTILDGX6KEFt0Xe+28CvfW/a8ErvakQUjZ1oh0tqeeMFy1wjL1WYBdK3uRdXHZTUgXDSpquzji24nPRNmveZklI3qnXYr8abGbMB/ae9U4aItSHr3ly+KY02hdv1zhuJdYOHDM3UM26IUnUOmIaTVy1xOsGwG/4A6HHrLbTYwNeVFguZO149YANNctfmrBY2W2/lRU7WpS04sKl2qf+wOnUvveU2yj2hX3RL4FtKt0i5VsDPfDSF70R+S7mpQJvwXcPAhHzk5Q3Oo66/Lc4FeUnR2LGqxxlUx+6zMNr/0hgGdSTtoWa0I3QqOwMZbgZPKcwVL1wmkLsoVMab9u2L9QtmXJKw3sHTw+wAg1Wtpn80l8gMRViH1rgI6AfFYlkwS60hbNvMFXGhVfxCPyNvQZBjMATBbYp6LX4S+lyZUrSj5XCOxFm5AKUq6LWlpj9Z9MBrAAuZ9LOmP6P8heXfYnXjJU45zhQWFBQWBnK1734MQ8gKjQntu84J0T/AXhJAW8xdWYZc9WfkON/IXHHvO4p1lyQTUV/XFd5DS7Fu/uMWs2oApihwSKzl0WsG7HKgX1ciBU2F2aWlrc7O6dJqgz984O49+6oy72Lg38EBBrvcGVaa7KRMTMHbEnE5pZQM0b8V4fmK7bHpLuL39oiqN8WHSj7Xz29EDKiYn4NhYulWfw0JR5whP6SEzYr85WjqoJ2LEp/l8jHp/kFbxUwkotmi8C3ULpxtzDkDCsgRDlF0GgSBwDUyY6RXG114xc5dYvZKyek7C7iCNZ1bCv6bXFYPxhDCDy7WTSfe5acMHgAr3cYEZ2Vg8ziRVAvaMfn0a3uX41BvTzzdr2oR4I7cIAWpm3cl8bnAqnyz1KGKYz6G0SU2pPVMX0VIWfbukNUVMTMhCoAb283824Bn5/rYylttQQbCal3CD6JPR0Uak5C8HuP+ChRBwdyzyrzsoG370ScBLojx12EF4ykSXrPp8lSfz15J6zs4wsNncv56jIolMZqE0QxbklbJ+fj6PEcaUd6LGfqj1eelDbbNG7Z7xyqRguDqXn6vEXuBTcdgvZRu4hiIQiC0j80y3XXGJ37mRE0nY52Y3C00uKW4aaAn+rsdnX7hcj8lCV7v+zEUwEMcc5Hke5BFbf21WKmcAY63YPPlBM5q/dNuyV1CnXH9NVw4ov567ELa0M7pA55mvg9mr8UVfKd5ml89h1k/VehZonPDqp3v2M6ksaM5x+Te9wBJUX8bBi2kCcG6WqJqLmEJyOwrAK6RIqs7pVt6jDbNAbsKX9ca74WDHNgg+BN0MClxOCpp81tLSXddkGqdoBavOKpsJs6fkdv3LGNPSFU59Pa3bwpGiFuUmIvIGPd95wLHzyGnlzpXyb64lKHeI5UjAzrmK2yrpvELvNsy0fWGgVt7fhfpu/YUJKZFap6F0ueQnEyKP/IhODBBuIWV6Sfu9c99mVEZpULGANghwQQt7ceaBiETlHYRKep7oXrhKCbchMo+TwIfr9fWzt7BjKNRggc4hWtzYzsxsgBkaGglsGtm67G5H7m5P39misbONZWObzcyUM+10iupqN9nZ4pi/9JYIurzNaES8vM2sDdf0E/KmrBTiSpogISm2xWaH9Aic2VSPIHRZJShpq9+o2mJiA1jXkMrDlHznEkaKqLsDRqrqsxxj0q4xbv0Y67hX/WHnF2Zs8qu6Swp3uFk/71I4ppcfX3b+lx4XaF+WotqMxlGAhpP7QkWr6oAKgXE875W+/+13FhIr0F13RJAxpVAkmRceHYeb3GjhVz+2qb8TXoI1d/2Ev4oP3aARIX1JzZRI3TcVneh6q3UCJ46gHaAag7GhaFQY9MLSg+HG1bJXgnoTduKllqkQEJTKj83RsCjhS3dgEiTZ1PqfvAc7DliyhwunTZhBQLJlQL38XsO5RVNQTmwDd3QNt7SxNb8MlBgiwUBcD482D6PQ8iOv5H9i5WQU0tXnqwBVn9bR82EdprEsFKv5/X65329k7ZYFhZi+3jKmT/8Nnl5zojizLwhs2DGw7SES/74ug8Uc0ooPUKOqiwJLqCfQMVVD0bi/Mr6x9BPVc6Go22YhDHDohBiz8B+klbIepBkkLIoRtcqXGCYRtRiWRK2t5HWjFd2xtyxzjWahaQfoGswv/ENM+e9m0WGkhL0r3FUhGUyRN8b2IW2KFUg9u3L66I2hRhKakZrI6CSNmZDdVP/O8tE1QYCN/UQlPyV7FzOTwyrQOgTV3uxfut7H4I3+6LLzQrIQOj4T10q8RmM0T9/Ytk/99TZAE/BDYX7TDBgV2D99nutthOgMlOzrkWO7SFKsCk8roH+OBNLcE9ts02deSFa9FLOcCMPJQHTcBtrbCnHgCw4tAXWFF/AIxGT8GAV7uT5SbvIBWyD63aRQk1vdkHno7u2ZRiWaX3ovhSo8FAVgzZaZVAFexLr8UrhDhK33pZaeQbGuqWd2Z1pNYkhSP1m/eCJSsKYPHV0CT77ad+dkBucAQmPSILuoCQYF/705B8kzCCHVi4+AMfVQXhyDd28LuOl1WRUYDccVinev7YcTuKyaUZXXkii2Piq1tVnlMQWchY/lqJ5PxGxo89sIWFXbqf5b5toews7Q38mwFRyUcXmtj4Jatu17fhTM8XpWOCKEp8AYetQTBOA0f9jTMYzeny0jHA3OfwSvkmfpnV7FT2dMIddxArlMt7So1RnGkzI+zGufI8pLtoHmlSFrWWAONEYiRHbPKPAIg6TZTGISZT9cO6OyQbiOKtKSygOd04G18yEDw67GU6SAFAPqlD7sVV+JQSChDoD8QoJAOG24CXK3tAzU/k+YFQPMg2xBoYK9fXhR5R6sSHnXh73sKUoxIwDf+gpOsx7dnp3PNQsp/vc69YYvGn0yg3UYsZ+0/fscczpyW4g7Q3EW4c4UGi7K5y72FTZySmKyBIDYJYb0K4/duXgSGZBHXBP6QNA3HwvDm1O00Leu8IvC21NW8NDkJsDgw1xbzFpmBWR9cWte2Ai5eYcTK9yor24oNFIaLGIFSodXbERiFk+8TYfEOjjYZYU/y/GXflfbQunSD4Za+D+EirnNOzS4XvsAnjKvIdUMNX7I9pRDXFie//ixs51in5drSrm01snyWrgUmpEUnS3zd0zNHax0TEdy5H3c9ZwkG2b9d1wY0+nvKag8UDXeB+WcC62Th8gyHberG47Nr2XzfpiKfAmorhCseXCkueE4Q7tFHLIdcNHvliCZ6HtX/EXxFKIamNUUgW4RAm7l86pAZIP5x2S4ICmo+YE6dA/WpeCiOl/2pZNwebipcXzcQsJOTzeX99eFBxdHzAYNl9USQKK9pDadHxrGm3d+9CFhW3XUhGHZIvScSGHpVm2otOx5ZJW/AZ4+SBHM1vc6kEqywK+soXevcBmOdDsfxOusQMd2gQ2c2XOi/O9LroHNJlvpS1EpJYUdCBCLqZEUcCJ0+oQ02kGo05OFCcuixnbZCYwLVqzt2kEGtGuKosUz4yN22Cls9/Z9GkyUFkviCf8ROc0kgXXZxBs9LUFMgkS4S1xH5EJp4SHf4tBXFniolceSITaFVp5n5BN/jN3LcFxOLn5UOLjKvkC9SFU62vFickkEGIhlZN2m66GgXayaBxO+3vmuu6pP9jHxIrsJsB4wmYv9F5gSAYT7gDEVrr6nA74zAhmHMtQsEkraE3nplIFQo+ayuBHT1HuGVetGms4B+oYFSiMDlIIapL8eUGcNpD7km7/TgKs/Tq5e1s1YqBMyPDBcbBVcjKkmSUUDa6B+1xIBBX2hSSZUyA3Qjg7U6iTotAKj8TuN+KyHXYPvI1eZ7Hd33TdBPzQR8JGUQY/8Kiu/PsFfIue86YJ9DwZajnNaaFXP1ehBT3NRpzYuGi2kjVsu8pmY71uLgDdhggFiTYUAta7qavnZdQZEL+YVSlNT8J1TLrK036wZFFiJmQFUXQrs4b8FkO2vqpePXKd9BpJYt5BbpP5yCh6H3DcuGZeNyFOCGPFMVF9EEvqPsadSAWARGTCaEiuNmQqRP6VIXP8fKIOpgm8kBZ8MaIkgAHGHdfF7HsBJGUEungCvTwYCA7jE34yVYsVYPB8QYuBsbE+lhlHdPDo6MTNlZ8xVS+jKiOS+8nC1f4Z5WBLeb87R2WxSj4v/s2Zi9a5cIyGkpuz+9nA7YxWYb8bMPPvRK1bbwpVjo/vlF4ts48j/PPTwyIkviHHwqKYgj2taiBqDFqvufKdJ2rdvzSq20r+BXVHm8xi1RpBmD6PBSfeWQNoGWSZ/881/Ji1AviRBOYhn8Sl72X8xS3x84egDswzQzr0qOfQMMhSDSldXpDCoZogeqhx69gIRJmuWtObJH4tmTTkT7JpCAR4xd5Pk48xzshuK2JKIXdbnhrxhBgfTqPbYJyBzcgJJxHTUnz589aW9MoDhquNFatUcP2u3a1CtT6S58JFjyEgOnGdBDOMAL8XO6Jw6zP7FghjVv2GSsHcZJcljUKNpAuGAGXiRAq7TVY4GM/YC3VQR8Jbta/GkWFsg1mdGRq8RoqOBajy48NroJVLdFbLfTQU+MGwkP9Ms2gh9LThGLDaqmksWKQNkOqKx9xH+Vgs26yBywpRxwn6lXsyKXsxaYFQtPlnil2/zBz+YbbRm8ezCMskjgIA1BCxoGv2Q96oi2YcOffQanJaet0Fi/KxZpWi8jVHQp7RpYN0ik8MlGHsoOdX4GGtTW9ydkRfnjO7G6ZiGGtBpucGI2XPeM+UYKfliHtKUd4SSmIu1k5jSQSS0fCywEyqopSp99DgOSxAl92Qtb4AIv9FE2DYRibZA7hfUq3my6np5kHtTjWPjv1s9hCPEc/i6IOI8MHdZ2kUlHdw6KYuON0Brgk1qjI37z1xWFpP+siQ21cS9Zzyixy54ZLMj9Vh3d077AqsfcG8vdOuymaZV3IGDuL6jYYnXT37W0Yl72loAMQf4CJYXXJ8UmYdLwyO2Iy5JQhHZy9jQor55LrS0zGIOVOuyIwjVWEx2G1PQpw8+jL0KsAzneblpheWu9RfgchiovpVg/Rw/R8cSzIZmT8P831ypN6gbGtg1xl7wmkUgxPVeOEpkOCZOgihiRz/iOUo+Pg5jApEhuJhxAZ1rKWWXWNqSYeQGEXYJD1I9Dwx0GY/xz8Tk/gtD8AaxSFNYw4ZodpexZeRnoSZ9W4EAjdETWvmWB+rNnXkli8InJIQRRN+RKlA6WgBiwCmo3W3GY8BrduosZO3L1t1KFl/XJr7qXrav7l0sO1uXwnUmN0gX23/wgJevoa/rqTPgO50rWXqfOfRdJSf7z+uWZmKXjS68SMWzrm85jytmn6/hAR8ejZngreiR8ekhZ6VNk5E71+5CKnYMRnGzJpaZJQJ5+rLBIpl4pnB27QLbx5I7AP9SUsx+8LCsS9ZqJBsW+MLHoiCv/9GNDEkgpFQflzLes29NK7hl7iDqqrSAVjczwHqUFt858IFX
*/