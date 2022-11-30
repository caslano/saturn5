//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_ATOMIC_HPP
#define BOOST_COMPUTE_FUNCTIONAL_ATOMIC_HPP

#include <boost/compute/cl.hpp>
#include <boost/compute/function.hpp>

#ifndef BOOST_COMPUTE_DOXYGEN_INVOKED
#ifdef BOOST_COMPUTE_CL_VERSION_1_1
  #define BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "atomic_"
#else
  #define BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "atom_"
#endif
#endif // BOOST_COMPUTE_DOXYGEN_INVOKED

namespace boost {
namespace compute {

template<class T>
class atomic_add : public function<T (T*, T)>
{
public:
    atomic_add()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "add")
    {
    }
};

template<class T>
class atomic_sub : public function<T (T*, T)>
{
public:
    atomic_sub()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "sub")
    {
    }
};

template<class T>
class atomic_xchg : public function<T (T*, T)>
{
public:
    atomic_xchg()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "xchg")
    {
    }
};

template<class T>
class atomic_inc : public function<T (T*)>
{
public:
    atomic_inc()
        : function<T (T*)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "inc")
    {
    }
};

template<class T>
class atomic_dec : public function<T (T*)>
{
public:
    atomic_dec()
        : function<T (T*)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "dec")
    {
    }
};

template<class T>
class atomic_cmpxchg : public function<T (T*, T, T)>
{
public:
    atomic_cmpxchg()
        : function<T (T*, T, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "cmpxchg")
    {
    }
};

template<class T>
class atomic_max : public function<T (T*, T)>
{
public:
    atomic_max()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "max")
    {
    }
};

template<class T>
class atomic_min : public function<T (T*, T)>
{
public:
    atomic_min()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "min")
    {
    }
};

template<class T>
class atomic_and : public function<T (T*, T)>
{
public:
    atomic_and()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "and")
    {
    }
};

template<class T>
class atomic_or : public function<T (T*, T)>
{
public:
    atomic_or()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "or")
    {
    }
};

template<class T>
class atomic_xor : public function<T (T*, T)>
{
public:
    atomic_xor()
        : function<T (T*, T)>(BOOST_COMPUTE_DETAIL_ATOMIC_PREFIX "xor")
    {
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_ATOMIC_HPP

/* atomic.hpp
TJJnAemVlYL64THvIxrdFaVYloJPXLDPgVfW3V18jzxjQfMPw73jaBuMb9XNaXDcXM+T0Zlsb3LR4GCTxS4gFX6PQ+efZnaNs9Elj80Jk8t+EHKtVyUurg31EQaJSr5RFaAC8PVfmwjNI8xuh8OvwOGOXVETeKaNepvkafsikCfJOgt312YH5anXpOARaqZU6mj2WiqZLfINskNT12G2JQByZGJx4ssXQb/U6+kp47KyZ50x7OqV6G4JhHCbR4u31hNFe18gNYSJQVtTmT50fi7rszeo4ofDHBkpjXfw1wEKNNW0jKN/Gv/M98V5+fdWZMX58LUE9ECF+SFUECAIWj/1dX0hXSAJ8kHucx1P588VMVrrgGmK/L/sDowO2OjfgheI+BcvurBODGgV5rob6MWSuBhpFsgVOkrr2L23vAg+TqOOewJTavJ2RfnU8+mdGLi6e9X/gciQcGYNpSweL4yTci61z8dPTZ3yVV+NtjkbWE7YclcKJIxykpHkzFIhppVyqLiC7OMAEe1z1UvmzUrrnkjU1ptwKXxSue8kTGPtTwircX5fbJXr5LYw8xYG+HcNNl483DTU8w7cn042P7R+tm7kFmyS7V0zXgRKU8WHG0wNjB8FrjgrRPGgWDt8UWdrPAnH8LczqCu1Tws33wxFjmX/ScaeyZHYOlHvipptIvISmwFTFvRhWrxDyaGOZRWsbogYqjM/GKr/VwFMC7KIozX7vZzHUlrd4+SCfRTfDYrPs30HIrh/mSaIDXGHzdRFN/tz2waQ+GbeW5KatCA0v3ZHSwqRohMszuy2d06UNYJBJZuEuvJd/BL4YVKGWKFBnSUWAj9P1/tHJYxMbVUV/hOFCx+dXZdrPSUdDM+kqxN8xQasiy+zoXtTh3h5yOvnUNIUMnGb6tovryC3jEaTJOShi/fKvR0RDYqHa9juCmBR8LviJZ94um4csCQCnI9b9W8pa7dPBaq3qfSzXA6o7jBwXsW1qlVTMJRZ7M1eGqapcnTzS2RKhvpL0mZKcnn/K4XLIc3UqTW5gNwiWTyqoHAy6WnzgJllsBVblO6Grd8ABEXBdNFKLVmDPNSyd8spFBubHDcXKWN5KuuKArxSIyqaqDEmLR2XViq2gjOtKktVRawB6dOOJw0tcVcKWe54flquEJmg7h9N77AhP8a7Obd4trP9M5qbqSEW+LuWs6A8OyO0Czh9v0/c059PuvtegPu/vfjkeN4QfnF2NPpdV6cT4vwAfgT4AACkAIgAcgKyf2Th9F3+aCioyMpqoLLKEmnIqgC6aIAJsCrAseqDwZECgtl6uHsLSXkrGnKyWVKRAwD5zYBB+AEC+F1WMU0wAr5O6VW+KvLa2flNeovftC6VGgMF/XM819SK8ITpeNvZ7zqiW3Y8Sjhz9dvpIJioNP9cqBhf5xGyNKmEbqpwS5N5e5f5k9+R0qtjMlNZmQGkDvEHrtwiNBtM3L6TMA+3+70T4fZPgBFHDbwk0IesrdbOguW4ZX2gs9IrzHHgH045URcv6B7iHnoAcD6KJEEzEeZw5TiPW2xH65+uEe9EPbzg0LznrUZsspSlxHNXxHH9NFQC4V7As/HdT3HtStpXTu7cABh6eiCAgzQXO1jGNVBZ5Ioq1W9x6PMxS1kQcsI8bZGkf3/l/8q6oUvgyztJyazJRArN8Xykx1AtZUKVkfk+iOKfflD2DdkjExK02lovSSm8SZuCm2jLKCdeYkLFbWYFvPEnEx0NQVv+ebrXPpA2aeQZcX9i3XEaOTIPvI2o5n2r11CSczQG4gHT55w+Q6lA4K74dvUYKhWNL8y/5w18faA/h3Hkv4fjjfYsLusUOrx1d0V7C9oM0scPZmy9caYm9DeJuM9PIhJb7Bqdx5oxUZylm0vjd1gypuu9/+vHf9or7xvA+hgPBPCTFw88+70lBMCO8pr0MxD0Gqt+W3P6I+Whhh3gY+IfwUgO8EpEnT9PBqzh50u2J4Csj89FBuBnBgIAMCGG+L3EC2vxOYMBcaZJxcGBlb4xn461/l2TcK97ryvxpqveiVM7m+ODDSqOAOBH9xMOyr7yAwtN5i3m6M3JYUrGZUrGCSmkicXJ9vWzxvBWE8VPLrGpwSeKiFfZ+o1EhJbzE4vxBR976XsYgJNHkpWifJ6SCgGuRxYC3fuW26p0+63r+JYZEb/km58/xPpAJvctZ/NWw3KxoxRisvvtq9R3WMTfx8ugh8dX2QsAMOBoh0eEEY3uFwsIMJq7DgUw+8mWSgfwc/J8dYAG14MC9w/XIaoWQ94jSn5tcjO+d7pveVFgJ6NXfmd4eDm8tzett28tpHczhF9NNrx3fXk0DQ4V9VzXMwUNECAODASs1E5Z/j11CxYAX9CMPwz+72wu3MfCa1jej8Ms2mnPqvez//c+LMCtLeQt7Hvs9wnh40h3N4h3iv/MTM8R377cBkEAmDzw6wQtyKhvKyA4rF7oG8HTP0A9XpBpcLgT391EX8w+vsUf5rDYuldf9AUOjA4Ob3H93Z4X0Hu0mx8Dwdjpvrm+W0fe0R3PnygC9Efffm+3A+jswLrkK/DbxAuyE75mvW8s2dueOeJvaKLvkex/AFhvcQDcvH546Y+qhq0gAK8K0Hd8282UCKCUAADICJign+By+E5Qq/ACT/FJML0ASb6MyAB/Rh8OoIBAwWDhpP2fAV3ed6FAgA+fyoIBSl4RFuX1dicv8Ba+Wx7ov2uOAb/oVoDfe9JC735Y4eFHH4io8ZWE+Xu3fTnxoG59KXp/VAB8JVPhh0xPaghg2eNorkt8/azueIfAofZ1F/C/c8De6EAPd6Di5M4AQYTv7L36zPz9ywDnOvmc+eHwgi55w7/FfIG/1sBPfbf5nke+eZ8B31d4/b5VP35qfq+/c7z2GVwo8C4FBMhl4N1rzbcrr1TPj0zvG5ZPAAAE6EsKjr6EQQ+LFUczL5YKBv1KF/648lrzB3T6ZLKHuVHe90x+G6Bsltfn2w4E5NVuw3RLUDjysxdI8AuFEjOt57BEMe9f73eLWm9Pnd8PYMVrC+a7Lcss2Vxrz+iC3s+V9WHPiv+3ZzYffnOsmlcQ/DjWOROj78fsXk3G496AHA0NPgoC6Bs4+hXs7QEwqLDAp3nKfk2HXqM4P3IhXgREP/zIxr7vaj6Y8ys5r4sZMh4LQETU+U9Qwas8vwLCV18E0JsXtnncDMo/KL5zPPzkQ13M3bCZP6BjJbZ8/PQ/frxV3gF63368Yj9+ej+Ac1+wAV/A+R/ggyCHIO9jIac1ncAmAOCjPx2o7PK+8pmfDafglqVjcpu5uOt4pDFGuYV8nUBP6g0C2It8c0E//Z9Y0W+hiONYq2I6ARx/vcywKX7S38bW+j4cSbd8c8OfQ09+TEgvdU/CA84d0ezxGAq/owg2cwfeTt7BRD84oo+Zks35BEZh+HNnVmIp3zBW5GBAb3OZbv/o0DtptstNhgq8y0EGf8e/4VH5HgI0EQ2c5OM1lJaNlxL4kaPzhUAA8DOH8U/jSVplKOrhaxbD40xN60b0z0yUvOz9HHmT/cyw138VAX6TcUL8XPH299z4DgMh7+rCK4fey+G9/SBBh/m+QQz9jp7qpeF6+oEH8Of7GWdiR3j2WwJptGcB5Eoug/87kfQLriTXheAHEnGxZ+CjbFDMzuhrhHv99y76Zo393nkO/77x5gRQuPXKkcFXotTTfJ4xncmtoxnBI/Majjqf0YQHIDzfaTG75YX683NiiIydDAf4afs5ssG1qEpugX8ba4BwAgDxmtsJ8EXXjKyVCzL3Qzr6xSYQ5QuR8CmDcMAHAvRGBFfo6/jqaVwK/3aUCLgKDqyHD5UXy4vOntZOM5Nr5eT3rZVzmHuk//1wj+5LR3frfmz0kw8Iclj6rc55xOeMl0T/AynxuMMC8CAnnv9jCNv7botf+QPX/22Lf/m7exsBtsvF6H1OPd4pi/jYEQz7yL0++GoRuf2eIMQz3R+IJc3VNeH9Es97HolGdsit+3DzDQ0oGvZrPPo45Q/k8g2BBgsAwwa6VAQGM//YcyRfj2ZBFj9ZhQ8cxQ/Dm9ERRtiIReCvAggEVBD3+lfpR57EG1zQexKO9mkpwx80Y0rACAD5kbvywjeD1Mp3c4eHncVrAYGAnFY1q6tmBAYBUBXrGef7SuG16sD/E0YUfGtKAZSP8BaVe5oLgvJxGeG7TBTOZzjGp1omF/yYiwOgMOr1t+6rVdD/p+2BIe4L28uI7HaE89m35x8Hgq+J5CNfOtDHzfrL70S+lgqU/5T7kMc4/GTVzVjZ/fvakSZtfaX/8qW/TaeAQ/zRRX+dJAQfkAO2+1EK9oX593lz4k267MuT+zP58OYLAAks9tOgvk85BMb03+9oG7U8sxaXnH94TG5sczomJ68nqfGFg55GJi/v1YJAYSvxI6DWVRq5/nEL89vdgTNRQwzIW1tJf/38/ASIAwAE/gr6Ffwr5Ffor7Bf4b8ifkX+ivoV/SvmV+yvuF/xvxJ+Jf5K+pX8K+VX6q+0X+m/Mn5l/sr6lf0r51fur3+/8n7l/yr4Vfir6Ffxr5Jfpb/KfpX/qvhV+avqV/Wvml+1v+p+1f9q+NX4q+lX86+WX62/2n61/+r41fmr61f3r55fvb/6fvX/Gvg1+Gvo1/CvkV+jv8Z+jf+a+DX5a+rX9K+ZX7O/5n7N/1r4tfhr6dfyr5Vfq7/Wfq3/2vi1+Wvr1/avnV+7v/Z+7f86+HX46+jX8a+TX6e/zn6d/7r4dfnr6tf1r5tft7/uft3/evj1+Ovp1/Ovl1+vv95+vf/6+PX56+vX9y8Aid/4d+6RhDKGxdqjZyQf6EnNK8sYRGUW0lQi3ZnvUEiWma2ZGWRkWBhYLWdeNj88Jw3tN+Q+Rqa7XjYdZ3heNkc4XjYfNDV+5u42DOaSxb5TCQciJl/Qi8PbhhR0adqHMUx1jkCFNTtYgd+JlLhAw71JYPQ9kXwkSrTAxi0FHgzMyWpGQrzbus8RlYzrBsc0ABlMIdpxxLG4CxHT1NArT1jQ53GJ1sTUxeyXTLSRSkaX7iONdYrr4SqseSC0oaBHa9kChfR1aRNpxMvRBW54107XrQNRDBgw4bGUsYLCk0vzW5xqD60K8zWbxmrmwVa4MhVERBesFhXA5+K5JOZba4RpTqBwScq5j7Oq/u6ENLKVSXdwrJ1BGaBED48tyHF3MhIn14m+Cw6QhF8CWO+CvSvA6N6jM2HTXFZYGVLN3DRL4MeqNBtuBKaTNlrSxROdrPdb1YTTTV5tyoRyGck8WyrJBa8da0Eq2B5E4/zjbDWeHdnZS0hNqM3Kvk4nbMRy7l4hwSJBQKEG1HZPvx6JjoUyovk7ID/cFjE29lmbqqrk8iaYxsF+yDCfVaYFu4zdPJrOf/0TaRenFudZE3yu37IzEKDC07j7+pNFb/Xpg+iyP/hQD7DN9x4IT20LwmpEXbThWfs2XtnxFcG+9oqidGn8DcwSnoRhZsBJlFQoVBbXFctYvppi0fAyEIdxjESmYUGaiEox137RmFzfasuy2y3Q0paPKxt8Zfk5TVgW5s3v3OzPZZmPLiOi+ffQuWrhqawr+HNxenlpR24RTzsPrj5HWFcoAXz00G/mT6E9rGPjfuKi0pXHtqMDHaeybeIKDjCspvqVsO8LZl+3lH8yL/HIZuNkBtpMeIuY3dR6aGuFzDd9l7uyiPQeL8e0GAuLrHMzc8yCx8qBbHPtpv17dmrngDd5rUCIG1hmbADS5WPKBhW9gcw5zSoMjho8bsuzCik8TePrhzPXnxNLQsZuwoiomjDCuZQI8Vp6zDSy7BJ8OpoGS/Zh+IMTePybYXuPfmvB6MiBlXslrROc29AfBMo5d7wQ30iFbEgeriXyFT06Hfjua1BdJ5mYkPrpD/+mwdFlk3oB+8CENeSEdKKvdCNbHwC2UWtRZ1Rxa3wjo9EwP2/711hvKQOQjcl/uZUPAtu4RxtObpi8QQxjAck4GSiJxS/RIDy4KCIEhXWXz7RX+yTrk7AaSoq88K9Oip250HYJp+4GQG33DPnpFdj6yeSXsa3tXyiNRF5MlPVFySl/j2+HDZRmD9jmdrQfXzjIn+n0SYKf56EYLHgqbT0OWbyppPNjDVi+KOAV/dk8Wl5iQfs2ALshdzP7xM3oiGVuqbQGxtuK4LqrcGWxdzXkB3IE8vwCcKgnVYIJodxpxTl6swdVWbIUjLRgxUOeCwI17fF9tTiVLvkGgGrtY9+j9GMNdA5EnRmoavhOnlX3+qFzERkxTlTpCU6kAqbJ+A+d1ZOPKNl+UlYqHLFGo8Ip27txim9CYStbuFYjOkVY0+Y3X2exLbiXSXZz/XwJCnlubO7ivMk+ybqs3jhdBXRcgWdHpFhHAeTbP8I9p2XkHuXin+DWPAjZ3HhKMbLlFfLt5AnXfAEJnDDTx3m4k/GhugihSML/8YuRaOBY0c0ed+R7TGAlfKVKU/q9SUz2lfS+bSjJfVwvVMOaWBATawEkRiytsJSV8QXCpYL4yYu/7Ndj5MFYQHsUr1YhfCNNh7rZWRQu5gP6DwnfIZMUfoeRcFxIQUnF0FjJwxExMv5dxECtnbggSmhWGOLm6HkctlA6AboNAU+jXpkUVM+glLLYnuIf0Mu0CQ92Z2vKvu58SNiNf86xKLX/xp6AYlIWKoIuOtBePJb8oac8gikfe62kesb3Zcx1/AimI5PydtmbXOUC0LXhz0pb+4RRRZQSmvZGQI/edazuOs6Vu3maJjscn4hKOVlQfdx9W6yeJtvs3FMYhuyEoGN/FHsRiE6KE80ya2xp0gVOvTVZ2MF8x0IPkXOnm5Zedx5wBkeKiQBlpzwuczxgRj4Gh/7q6w/Q22NWVgvr79fTj6ekFvSXw3zpXDty/nHfBoTyagL/FkR6rQH4NkC4BPDi6/XFAbl57oUvzTOe+zEYgjmubA5KVyfEivrXlzq7a6sEDM1ewjR9hmgaG/qgh3ACM8whtJ+EZXc4ebxWnXZ9ka6VK0v2cXBvtBPKqiuaGcqtu+fgni1tUmBCmAiHAhVvZMZsEt2rrx2ldikfi2ZwNGI+ptQtOAUXcTtsxpiEE6BI4WA08lkC4tny4H3EsMsNk2V+ryydTfJHA0b91tFoJIljn54b1f2jQs3bxMQpqLlp29IESp8SW4TAxERM7J3bzAW5243H5lhUzA7hZVhREHdMQmCpba5glGzyWq/AZo0ch5EsNibunJHY7f5UAXneeqy5MblRDfxg71bwiU2iSCEZdVmt6yTYc+aP+1gT50HEAqEXmzy47irXqzDjoiUEfFUgY6w8KcXMeidKirmlQl2lWXrvSQ7zlRjBP1ZZg1C8gp372rIrl+5h3PB7MnK6rJ7kYM9SvTJBH4ejC4F2KZmcgck02pKyOq2Vnuq54sX2tp8eQ8Oxb7BhdonVWCJY6I9Mr3Gl75zUgC/4pNq9w+YS5xKZ5ze0Z6RedpUVpGVt+EuO3bsGWcmG3CBKm0QS7ZQgFhNxUqxhpxZsoRtiitSZdoexiXshnba8bNKZRZLzKkoka6rmlrrAFPRXset6tiKzTI6MWayWAle0BIpTDkhzGTZVOi5jnFQwEQmof3lL7lM8MtXY0AbUdbkBiyLBlfhzA6bv
*/