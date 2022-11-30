// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains a simplification of the "trigger" method for
// process groups. The simple trigger handles the common case where
// the handler associated with a trigger is a member function bound to
// a particular pointer.

#ifndef BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP
#define BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP

#include <boost/property_map/parallel/process_group.hpp>

namespace boost { namespace parallel {

namespace detail {

/**
 * INTERNAL ONLY
 *
 * The actual function object that bridges from the normal trigger
 * interface to the simplified interface. This is the equivalent of
 * bind(pmf, self, _1, _2, _3, _4), but without the compile-time
 * overhead of bind.
 */
template<typename Class, typename T, typename Result>
class simple_trigger_t 
{
public:
  simple_trigger_t(Class* self, 
                   Result (Class::*pmf)(int, int, const T&, 
                                        trigger_receive_context))
    : self(self), pmf(pmf) { }

  Result 
  operator()(int source, int tag, const T& data, 
             trigger_receive_context context) const
  {
    return (self->*pmf)(source, tag, data, context);
  }

private:
  Class* self;
  Result (Class::*pmf)(int, int, const T&, trigger_receive_context);
};

} // end namespace detail

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger to a handler that is
 * just a bound member function.
 *
 * INTERNAL ONLY
 */
template<typename ProcessGroup, typename Class, typename T>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               void (Class::*pmf)(int source, int tag, const T& data, 
                                  trigger_receive_context context), int)
{
  pg.template trigger<T>(tag, 
                         detail::simple_trigger_t<Class, T, void>(self, pmf));
}

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger with a reply to a
 * handler that is just a bound member function.
 *
 * INTERNAL ONLY
 */
template<typename ProcessGroup, typename Class, typename T, typename Result>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               Result (Class::*pmf)(int source, int tag, const T& data, 
                                    trigger_receive_context context), long)
{
  pg.template trigger_with_reply<T>
    (tag, detail::simple_trigger_t<Class, T, Result>(self, pmf));
}

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger to a handler that is
 * just a bound member function.
 */
template<typename ProcessGroup, typename Class, typename T, typename Result>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               Result (Class::*pmf)(int source, int tag, const T& data, 
                                    trigger_receive_context context))
{
        // We pass 0 (an int) to help VC++ disambiguate calls to simple_trigger 
        // with Result=void.
        simple_trigger(pg, tag, self, pmf, 0); 
}

} } // end namespace boost::parallel

namespace boost { namespace graph { namespace parallel { using boost::parallel::simple_trigger; } } }

#endif // BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP

/* simple_trigger.hpp
f3f4foyYQrNHbMStnorl+712KObkWpj5iLtJf+GoDd05n82hbc+nTZ+f4zsfehcWMv9GYvdnxc5kKnh0nup5bA/tHqu2ZvS/mxb7y8Nd9ufL1wHWVT/XhoXrLzuvXzzS9a2ggqN1u1eT3isR3O+BuGuP/Ts4t6xf5kdZvJV9jJ3+fg/KApr2kzxt+atftf6vAyo44v/iWVNsAZ+nMIr13hBX8pfIlj83MIX3StgLNn3KNgFejJDMl7r5j4tapRgNTU0+gl4Gdnv7+n+TK4tX0FU3fTck3W7ideUeqr530TjMW9ZX2GPmFxJqJ3mwoBnUnK9P7byib8+SakYF/xJTx0r8Sm1FP193i/KYjhqXproG9AivIpoznBMzXGNVfcqCY1L6DqI/0SWpkP/Y80xkfRJr1ZkYrR+qI98oC8OZnvhdvDbXbO1YEqoGumCkFIJqT/DfbpMnbrsQiQxV/XLNx+9djVmPld87y95tAXJGVuRWa84hvqvj8l6STYFnfyBS3Ji4KLeWoqDJlKZUFheOch7/Xw4XrnOgFaZhsy7YAs/dm4uPMaO+r0+NWZPwdx9omhjabUzq31tb1qhD6zme7pKezvmsas5rtmzgF36cYI8t/lusot4Tld0RfB4qkV1Z9MnuixFXXrkm7z7LVnbXaoSsC5gaU74tr/Lgwd511osKXHtwm8YHv9KjB7FHj8KZDAf9+UnlIT+cb6rUyYd1fx6puQo0dX6Hz5iXYmKUH8XXGsNXc/Vym8DbZX3iDMTs87RGz8rzBhmmv77bX1iO5cx72QujqJ6AWlUb/pzNyU1fF2hhGoqNVd/nHLVony86zSai+/K8aPee+jY/ogqlznDyeImhdi11Hs+9O2WNob8Ne1dDEIJnKOh+HWKWINji+yHKBexuTkU9mhuzXz7WfP9tlwfUKUzNbTqPxKmduA9829rzyxpBHjfHgsB/ETstYflEJw6umV6BFp7z3l94Pw3CH8y+tSoccjAnPolMFlevq5VIUteHVlFgMjgWzjkkmPykZuQYwfwiNaPvLaZcMrahoe4/v9NAw9Vb7+CP3nxdA1k5uI66VVDhErY98r5b1dif8TBmCIn+MZDvHibMIUjabkM8mtmF8k6NngLumgiWRaUPKOviD0/hA22bNvua5jcqXtpuBLeYN1Xf8joYHdXaCN3atLJ0rOdil1J5Yw894rByhY5S5Y6/l77BJunsL1om+w3rNrzXuICUcXlkPCT77NqW6c9rvgOKrY9aUxtU2gX1HB89lYvFL38VnDuFf6+kW1tb88IePXRcbMzbB6OvLlTl+vrtGkb5j3hF+sqXmYMiuRLZHlFt/KyYrvHDGlVbSmSotxjzpvw7cL+LdKp9zBh/jBa779sCGuoANDu/wbshJA7dg70zpZopLizVTYcZc0izumeFzrYp33T7i8rgzkduRpbdmjXgHGMGuqmWXzBLv0HI+wlt8zwL8izqZQUBNguul4jcXh5ukjmaZc1KjCUJwZ/COxCKvn/KcBHr/9ne/u0syHxob490ZeLGCbFIWipGkzD/Z2aGSgGG0ukMAjfEznQ/WIVqSnns6qiXo8SVATXKzfcQ/q2R8lTpzhcXd8vey69/pq3eZmq0UoBbnuVzCP0mjUuIIdwAEmSD5+xidjJ7NZi9IAjsDr4vr+WjmfGDMWvLWDvX6IdXfdFRAXLD8zjWhcLixkCG68/mIdZrvn+nSsQjx6DLINpQRAgDmFWU4IT1AyiNHawUU8T/m4IzZLTjuTAZT8zU9MtiTb5BFQzpAwubqfWsXbXo+0xmsRy38o1L43r/47Yh1qB202BJ786Mz4PJn/UyBAbn+B/bVXjUTCx+eb2461ij34KaazbNsEwdymo82+NRtlJQJf0rqHFXaywzniwxONs9O0iAC/ht7H5Uc/r5ifV17khGj7QJrTXErZFSvFXvGb7yTkru/ZToQ6vDyodCj0lWpAdgnqVN0gkQCWUmXyHkjogYBYtMf9usZxJSXzX8wdQiEX7vZzG2wnEYWSi/0OytfZBRi/Aaqqkw12I0Bh7nW8KVOyq45oXneMHJgMvzfWD54BtcTtcJzOvv46JRb6XvXNEPGD5Lv2Py42XnBP/uZ5q/zVVPmPBCsD5z0fRkKf5jjvi+vVbGabDHfqr5C4cfLcPrMlGdQ531Zclrmsh7Kc02+vtfDV0XXMKrTom0s1QFf+VmdPafa509o8wSuUV7egOwn1QwIgnO+T5/HjiCfsBa/tr/EU5J+GYdMsRDh8XwkL6E3lIs2apLnIOkUYCOIAiEXgOG6yhI+Ztcx9HWgqTI5lAihqRLSRSTfhZWouMtWshEsGuR/hCGkhbPfh6d0cLOCOZK+Y3kGjml+m9ZlejxGTBMXWBs3SqKXE0h3OSHvOIhChMf/CbbaE1Va/iZDFVxY+u4rQ6401+zlQ7miZqLjogQs2nyI88qfVMti8gZ/BjC6QDvSFvCLKfdVxWVyZj+KSDwcQr1dxn69nzIIRiML7kKuOV/+tWy2Tz/FvWKHnaI+KUsXHaua2eeAvwBy0WmnTb32MyJo3Vd715ktfhi/qK27gvTli91n4k0dJywpsH35huj180mbB9v1p13j1rHPuRgtZNI+dSShmMS57x4cEHSrEXdbv0YqbQFhI1lg9s37QI7kYGN7Vf85k7KCvcXI1xgFKPlH3vz4T8wDYKxv+avAyWrdHXXMfDPp2o/eGzpNHlprZ+FKsXcpbyKfrniPqv8gV3kDCCwbKZssnubd/ki/6DfYVaGnA7pgoknrTadN9SJ/irYiVtwMGctrx195IgN8i5yfoFHkPW5m9CSUK3DvMeEiU3b8QVb4S7yu4Y1TZAWiLV18Ik9hIEqw6T9T4zn8gntDZ0qVyWcCThF3vmF/cY0dA9tAoBIQdfcYbHdoBjSmbR09zPG54+zOk0/G7v23zLHVemtx+QrOFU/aun9KBW3c211r0EIK10hAdmh9C0R6cOXl00tvOxb4vhiWWGDlb1PdZAt94MU1fxDeil8rbuw6V1kwmZw4Q74m6AqW1D809NoyRVntBWrvQ+NOER25TjaVi7f6R7STdv+17pEB6xl09dewkCZqNG6FT1zJ/abXBXS4pO9HGM0v61stbWbIGIbTMgsMxtq8ThIv2BtjZUOriA027z3VSos+76xFubHqmXS2/JbHIrL4tZcxoseJkDHeo8tXPGHpezV7tU5v4gcf6loc+bd6de0OQsPZCM4mYAwK4N4bJltu0KpixSgILmh5dO0DCuTZl+ftTLvCB39YiPU9W/m55JayrDgWUOa9art7pkKXiT92yhyyFuVVIzzeXb/DpDVvXNyzVvoXPj9uCncVRefX2iXAXlx2O/V4WbO6Km+my0FbWW0TOo+CjUq9/UxdavLLXaTFYxJtHV6++zzTrUK6C6ADlmG6h9BiRIVgMBJ3d1jP2zCME9xpkTa9aLo+y3D20OzhKr22VPbUU/VE31luezyL/U4d2H9rNFXay7ZePVlMMmNMcP47c86ocginR8dP0VtUDmfBnws3piowjtlO71Cn7hrX/wVaq2vOW05Ay8GDLK1pCKMJo1pmuoYSAE653bviRk7WctVM7Mpq058j5OL64k/8OuI2Sxxw8dF3u8/YN2YO3Mf6lGcP1LmR/743EzDl58/pWbyssl68VtrxEyq3mBgW7X/4t8/Bj5ZFdBBjGrXuZvX2dnd88vAIwzxkw40WQiHGL1bNNrWNSNa/53K6wMDoUVPvObI3YS1LXy3sjxPW3lKJlW5GEN+6T9Ih9Wtto5CsZB2gO8Y+FgXTNTGxPudUOAMBMfBzIs8GeGvl1g6Rn65PPN80/oY7/V2KhhEJ9VRqbCSp89pYjFpt6qmL4a5CrmKk3PjLZsuY0VO3Au75jL4uXCFq9zCmtGpOa3nAVyznzNa/po0ljC0V+zG0Ay2RmTLYy/2ymq2IuBbRWWtY8xH/83WXcLsVyEGtn6oyQ1h1dfwyWc0EAFSwaZHG6wx1nmFLgRf/wtX1TRht+XmItXzC7vdd1VBWiHc4qP2jMlmZ8ya42lsGBtPsZsxY+/rLbxklZo449QgDw8kKOmjqotM76ldfqmKb/W5+ptztavWiI2jeWRe16G21KdnRQqcWbXm0iL5B2ASdi19XuR8qdGdGumHjj7k2vVtXiPMRj9YiYdxIceW7NshY1uqNtzFUL6DhygATo8vu9dKnHuzhkhPcYbFDkk3fUh3kQgKaXi2O59/7BJPhR/IL296HHDw0j9TTjKpV7jxbmi0ul1LADFz1a0wq4Gn+W+elmZO6WvI7NBXYfHhKFM5ieSOKTox7PAD22Ml2w8fXsdUMI+yu0093kHBfA+lW1TDPN+IpvgDRIw43HclhKnc5+yLH4BH9gplX0hT+uKvYaKwJFupJt+VXdBY89yESRi8GQkdvD91I7ZFYN9k35QHMTuqc8Jeu5N2lfdBgfNyFNPLmvEZqExASx75LBUjaQrHVwQaOFl53W3kK+YNK8De92y1+qXv2vqdWdcKWBBaJ6zLXfN189rZuHsz0nXm3IURTlK/b5SSBoR8VW/Q2TbwglJjyK0xaGOeJWSHwqOlYzeAgs6UaAFWIf7MZW59wlrzl5Km6abwzEKQF3eJ79w2+I4S6VHzH2PzpYg5qH8PmV3MyxMcTYnd5/fbu7GmqP4brE9gyisNZDEwulXnj7ev5WnPGG+3Wy+K+agkygSuXBZYwRwPp/KCxSZdNZZpmYGvCp/SG3j6P3/wl4gRAA2trbFJn9Er1fIbz2f2wJCDNzWieJ7KyxKGxBDbWdLN2iE1ZSnGPq+Pt/TLk+Gb7VTHVars3d2rd97S3mr3/kMhUMnoMUsRbngoey6EBWKxsJ55cmhFOJiaVHPiSezeFgv/hv1hc5/YqXX3k7dLtdWbI9iLFb0KAO2fWXjcARbwE7s33iiHe2pXty59ikFW+O7234dCkmt/9CJPwDuEdK4N/IRwoZKyFrff9oaJ5ahPeIPK22PopyP4XmlTtfVGko6xloky4c/zZsLJYL3TJK89tsDdRqAswHPmZwvLYtIks41NRzWhVNc/5p8oIUPn/wF1gIp/Gv8896Hu1s59ae4hJ0Y8L3jr85zYegjbCsdRWucX30JbTGLSL/hFktpPRq6pWkM4oj07xu4t7MdUU+aakIfOaI96cklrM9wpwV7ZZDRfUwzLWkTR15+TeMk+cqsflHdI8t4g+h/eJ0U++tBDD2ncpRb04A9/iMd/8o9oPlUGn92hPcPtpadR+/EODDVd1L0Xz/fpsn4g+Le0tbWtOP4Sh3jWYsjoDqZnRHlbMga3L4ljFR6x9zSuLKQED8mBs5ZuwDNExF9zYPHjbuE7FvYuq2dq3K11LNq+5r2hb+2f3DUpOR7PBJhaoaVJpFSHWJiP6FkMcirWjp9++mm9x4n+njyUd3jxPqcNGzbo2tD+n1y7Du1n6+Afc2O0dwBtp0rRWnwKA/WSL3u82lPH/411A8m/Wlcaf8begYGBDwcHB72mB9/0f5uzKSnhEoFgTu0wmu9BNnd2m2f2hwaE27nk/3YJ53GNWz5owm1hT9tnbhA0mg/1zEQWswnJFWIZPZfLr5n6VDJ/ZsjwJOLF+HvffffpvblPPfWU5gPr1q3T+j7rzORAG4UjdYm/uVxWifaSckyM2BHWfuyQ9nUZrkD7F7u7RPy/973v3bNS+DP2stecM++M/mv4idHYWLNIp+L5uSXZpbk+zGdUd85zUPdwJ4baqjDUXgvn8CA8shfI/8n5jZYXyuujCclLPaFxXPCUoWOqEYmorEcyq9zXzPBZXq9lvkX8eY8xe+bEXvRz3nFF3sk7zciNnhcuOupywVbfjL66BuFxM/qe6Xzd02gffD/xP+0rjT/7fbq7u4uFD98wtVnDDTV/XLiiZ6uNxrxc7zG+W/vBI1F4hlrRX3cQPbX7YOtpF/vPn0sxs1NY55XX0dZT8RSq3YXY0vsaPh74Ay7565COZrTP1OjURp/m72Ldknjff//9av+PPvqo7gXeIUkuRH/Ez5+T/GtCfFVQcq4peY4nE0v1/uXnZujPBP+u1tbWV1cSf/l72G9SKf/nX77VEGKqvbH3JxqaEj4qGOf7Ds0sQqs2My+2nxM/LZxJuIZ/fAQjLeJrG47rvB73pD+f32asuRp5nSiVSCMQ8eOoYxt2Db6NHf1/xO6ht2EP9SMZsXSD5bOt6DecjhE8/S//jDvvvFN1nuLiYvX7a9as4f1tePXVV3Vtnn/+efWDUfZfh2aW+gKWz5/h+9KfyZ6/vJL4i5/9iDMGBP964/ON/2EMzMwuYqyvDj5XN2YXri/Vw6zapMSESRc8o/0634SafUhw8jouw36pEn7fpPC9pPom5nTWvgmprpdN5mAPDuDA8BYUDP07ip27sXPwLRyyf4BA1IdcYm6pV07P4yWiaG6z4ZGf/Fx8zL3KNXl39h133KHPtP333ntP/Q9jNHMs6g+mJrQce3Nuj/Yv+PesMP5bOV+J860M9zH2z2di7hvtFpsuUq5DP2TqVsyl+jqaMOkaUt9KXBmnuQYBn1uxVh0va/mTmbyup494BsPBXnzY91vsH34XweQUmiar8F7PK6hxF2lsSCetGQfWDJ8wzn/mwj/8+Bn8/T134c0339T+OuYB5P+815a6J+2fGgVr99euzmNuNqU5oqm5mLNH05qfe+l/+lYSf9YcJQdnD6SXOf7cvNhMbjZ/1jqpM07os23nD2C8+yxyC9e0jssa+IkTxWhpbtQeiXS+v0ZjAbW7VHqpHmbiyPLYQs4ZDAdR6zmJS9MXkI3JukZmcGJ0F7b2bUZP4DOkIhnVfSz9OgCn+P+NGzfh7rvvVty5BvRFvGOQd0pTA/rBD+6V500YddrhnvAL//Vheorn+UL6XmYvGPzF/vtXEn/OeBgaGtoneCYXJM7O+JwIB33IyBrMLlj6YUQ4o7O1FAOn30fQM6R9Hox3tbXn4HW7tM9sXn7W1Lv+et7qkjaUPw+m/bDsdZBcOR6RPCAS1zMFmVgOEyEn9tje0cdYyI5U1Oo/ZU7ndDrEtjeJj7FiLv0973QmB33jjTe01+vBB9cIL/0FiipHceRcHPvOhHDyXBBDwxIPIsHv9J/nz04OtrS0rCT+7DU8LFz4+sLiVUxPjmC4+RhGO6oxNTaIKe8oRjvLYG88jMGSbbBfPIOikyV4+623ceToMTjEzqaDAfEXUZ1Fks739XAdrDMzSYkNKdVvFhfTWFxIaz5lzXbLql9IJ9P5Or7Em/gseqbb8G7Pyzg9flDnAs0K/h5PAKdPD2PDk5tw111/p5one7qeeOIJzb/4IB+6f9UP8MiPN2LnURfsUwuw+zI4WjGDT/b5YRsOyPvN6HqafkSx/6GVxJ81966urpNiD99oz8LcAoJTExhrr8bIucMYOX8Yturd6C/bDvsZ6oi12LP/UxTs3Y+2pka4ez/DROdZOC+VSix2IjvLGRxJwTqLzz8nf2KPcwxjY3F5xCQ3I/eOaL1lcTGOa9c4xyOb713J6BmmRCSpMWC//V1MzkxgNj2nuJVX2LB27SasWb1KsX7sscf0fuu1a9dqjzX16AfITdc9Da/4/1AoK/5H4of8/h17A/j0
*/