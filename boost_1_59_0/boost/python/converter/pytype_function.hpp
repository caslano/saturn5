// Copyright David Abrahams 2002,  Nikolay Mladenov 2007.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef WRAP_PYTYPE_NM20070606_HPP
# define WRAP_PYTYPE_NM20070606_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/converter/registered.hpp>
#  include <boost/python/detail/unwind_type.hpp>
#  include <boost/python/detail/type_traits.hpp>


namespace boost { namespace python {

namespace converter
{
template <PyTypeObject const* python_type>
struct wrap_pytype
{
    static PyTypeObject const* get_pytype()
    {
        return python_type;
    }
};

typedef PyTypeObject const* (*pytype_function)();

#ifndef BOOST_PYTHON_NO_PY_SIGNATURES



namespace detail
{
struct unwind_type_id_helper{
    typedef python::type_info result_type;
    template <class U>
    static result_type execute(U* ){
        return python::type_id<U>();
    }
};

template <class T>
inline python::type_info unwind_type_id_(boost::type<T>* = 0, mpl::false_ * =0)
{
    return boost::python::detail::unwind_type<unwind_type_id_helper, T> ();
}

inline python::type_info unwind_type_id_(boost::type<void>* = 0, mpl::true_* =0)
{
    return type_id<void>();
}

template <class T>
inline python::type_info unwind_type_id(boost::type<T>* p= 0)
{
    return unwind_type_id_(p, (mpl::bool_<boost::python::detail::is_void<T>::value >*)0 );
}
}


template <class T>
struct expected_pytype_for_arg
{
    static PyTypeObject const *get_pytype()
    {
        const converter::registration *r=converter::registry::query(
            detail::unwind_type_id_((boost::type<T>*)0, (mpl::bool_<boost::python::detail::is_void<T>::value >*)0 )
            );
        return r ? r->expected_from_python_type(): 0;
    }
};


template <class T>
struct registered_pytype
{
    static PyTypeObject const *get_pytype()
    {
        const converter::registration *r=converter::registry::query(
            detail::unwind_type_id_((boost::type<T>*) 0, (mpl::bool_<boost::python::detail::is_void<T>::value >*)0 )
            );
        return r ? r->m_class_object: 0;
    }
};


template <class T>
struct registered_pytype_direct
{
    static PyTypeObject const* get_pytype()
    {
        return registered<T>::converters.m_class_object;
    }
};

template <class T>
struct expected_from_python_type : expected_pytype_for_arg<T>{};

template <class T>
struct expected_from_python_type_direct
{
    static PyTypeObject const* get_pytype()
    {
        return registered<T>::converters.expected_from_python_type();
    }
};

template <class T>
struct to_python_target_type
{
    static PyTypeObject const *get_pytype()
    {
        const converter::registration *r=converter::registry::query(
            detail::unwind_type_id_((boost::type<T>*)0, (mpl::bool_<boost::python::detail::is_void<T>::value >*)0 )
            );
        return r ? r->to_python_target_type(): 0;
    }
};

template <class T>
struct to_python_target_type_direct
{
    static PyTypeObject const *get_pytype()
    {
        return registered<T>::converters.to_python_target_type();
    }
};
#endif

}}} // namespace boost::python

#endif // WRAP_PYTYPE_NM20070606_HPP

/* pytype_function.hpp
330cUDvdT2NInoFH6f7JrIcbNcoRGNlcfl3lLbXIryax3U5v3Y7OxBo5PQ7KXxkt/2GMWviYfGlGB+67yf8IbMa/jcSFlyrQ3lWccmkCwwlXceZrOOc0nBzEqR6pqZqzgxngpDGGjV95n+l3bvFV9saffgKjBdGlGa1IovkgkHjyJ627PEsk4uRLiQYS1o9CSGxHEthHDlRyhXLtboS0r2m8k6PeehIw/f/FqM1Qqb1opPbuwRBqv9GpBapbC+W7VHKTiFyr3ASo3oWtRLomEbepLGyDbnF+kiaZ396Cedhkh5bHAIxD5V1g5Vq4xThh0qXq7QloDWV2oO9jwGTKRkqAUU45OA46A4AIHuBn3QT0mbU6MW4QuvhN8oXlOCtrWZmoHtdbndmBE4yryzFC9RH5HPyrzNX5KUJ+XGmo7/85Wjtj4FowiC5A2/e7oJhTbqMot63I0sNAh2Us2+hnG/6Mpp/Ec6ya4TD4FzL6fhAW3CrnaLncIs1onp16cPWMLdiwn3yAFlo0bnKLxp1boCa3peCMJJq2W30MTD83UZOcF1Ra10cxWvbGQhBYFJNKZHs10FKyb9eK6EZolwM78UejjDGpXjZ24pwUvBQJ1Vwhpnf5H4XOPKMDO+Oxz0DfpkJ/+scodRBbh+PBjA7lxf5aJvZgJouMmXS8ZMzky/GkM8UjRfQBf3bJc0fhnVUBu3TfPRiQSzyifDbIYK/Yff0gt/pd6OgBQ4dLvdm8OBYFfXjSIpCN7fBLNFMtCfwB+YlYrKh4+eNbDRL99e4QiX7mKsayOzC70lRpYTfbZLYBAYHfAoSAyotyqkpljZHKc6FUZhOVLbNxZ7aSGaTiW4DKFAn5yjEIyrcDGS2HkVZ+KK1wpCUhIpIzK52mILk0ndwUiiKrkruYYCBnCSX39hUkl6aS45SXDOQcOjncyyLfr5J7wUhu264Qco8QOYdKzqQUGsgV6+TQNJJ/GsDI5RvJVYSSiyNyxSq5KCUySI7fylrgLfkNlVAfI6HhoYSO/ogtsBWphCt7uCCVJkZljfzfKpV9Iw1UTu4MoSIQlSakEuGv00isYyTWy0kqiQYjifWhJLKJxDokEenP0KWxWfbHMOQsI3JRKHIUITejNFpx82vz02Gc8vtONiBTl2C2SOsnZIGvSUiEgh6V1yFpF56XlL8ZoVIfJP4JHaWVHF5xOGQv6pcq1C9svPIsVCaMYV2JkQ1Dsk+oZA+OJrLpQbJP6WRBFRBhJPvBB73I2hvPJOI8Qa4bge6rlQiofD0e1UVbakDIyxIoOK9QWy5/+2u6yGot3oAlzmhFW8YUcCaxi5gaf6Qz8OViXpYsxPQEYGQVeE5+JRqrMEE2jTBcLPtduH6xLO+wN75HoXG6qSsi0QPyumzaNX61pgrIFUm8w0lhP2vkabHqh3z44OXLw+Q5v8bb18rtayrRsZPZkZ7mHgDfyCixDlOhx0i8yynxkDrptb0YHaFGvv1jthE6Gj5HwAwXKgXKlHFU3zm8vFXMc8C7tgO21oE7YA3v3RlXlXFJHMf2vH/ANP0OOxsuY4aHcXjEGo/+QYF8ld1U7TO9i1wwIHVgwMpYqGFi89dDqV7XPD8Gxw9gFIamIKN1x8hxhAD1YyjOspJ5FwbTrUqvRfknd1RVESLJfR/qgTzta4oQMK8qv1AOH4opShhAuV5Do6y6FVqVtedJdSLnScZcoZrLna4NAsvV28qqJzbjqn3NjUsUMRMLkMAWq6pbmQU4fZFq1HbIt9/OLMDqVmX4MDSzqKBSdavY3yk39sPgUC5nYWDSW1AuZTSzWFOviEcFD8UQXtGfVdypYeqVnygos8CAJ0HZL/Dj7I1zx2LILWZYJcyHgu23r6lKxEobJ8HIBPnEh+ZTpOzswfsWBU+Kq55MUsFTLn8+VhuF8WSMy8Vs+IN6Knq7XU6W+i811ZOL1SPxKWAyY/3IR6lVkIMLo7XBT8wrd211UgW2ZNMZaDn75A31hqSHb0MryJ/rcjDKJWO1y3NVm3o31ehgmN8VKX/vRJejMcPfHsUJFWbZY1+zK4kCXEODKKs7MZ6vSxWcDhCcrVjBuD3TlSawGd73SVrRsvGsQIqafFJPxq1YriQ1uVlPxk3SrgQ1+e96MsaoVYWpTf6DnowBdl3RavJybTJY4epuYkkuLSnfJatJBVqSw3VcTbpPS7ozpFRsbrrkiN4X3KOoL2AVfDBWtz4QZXnH/pVke9BBgD5ySlkPLg/WjuhthczActyHVgjuqSjCDJ44QvtZS+xrlo1gnbFIzfrqYTXrWkEpHUF6WGOwklNZLJJnElQsMvifW0NsIif6rLdjFbFWaZaLtVnuYrVFmmVeSypTW6NZvltLekBtiWZ5pJZ0j9oKzbJNS0pMvcLEqbq5Vw/tkn2j2bHhyt6MN2MBf3+ICVgsCmvZbQbmPRN6OSIGuSYvMnghbhsWxoIdJWKKcsdtWsukXgHayulRmhn8lz6sj3cO1mSmLoFDA7hiEZjL7gQadDAy9MqEmyd/fcdorXWRunyVM7V5tbky4FRwG83qGa311yJrPqq/Zq3LrL9mc8fVX+tf9179tegVb4uZHb7muv+d6oCZnH8yvHm7bqub2Jv+q0DV9QDS/z0O0YhjX4sXtEzdYkdXIwbulwqq5jhn+zPrl2+1sRsWYczwXrttxZsAn7GnbkRvooVIdAYSnYJMF1TtabPOMe+BSsAqX8FkSnm4HXV4jbw8ig2Wx2+BweMKaUE7KAaooMZbegLKKahImNWke6qUyaPZ3PV+wkiUXwhinDtnLpwNGvJcfKJ8CNGeH8VghxNskrw0CPtGIQZg/XAEQC1Xoa5aEWqi7LzFMCmwJfSEzqv+Nopufa22Kk+O0mYUO62Ml1tuMVhLowb1BK0ldx5OdwKpRfIYGpm9yy2cfe030NjK6QSNzFKVzNFBOpt4Mu50bA+NoGbIH4a2jCOeiWwREkffYOTqGPI40mrnU3Fsmz1z/yxOFD0uv5RebVkRVWkqLJJfGIpGSlWhgg2LJb8RyWq/cJCh5NmxISWnKz9Vn+rlQdpVtPUReB8ylmXjrWRL3Q0klKduZTX6UiSzIntiNal/4odAoLIHqDvioeYH2FHcOl2Lh+oeEdcezSMix6oekdrBLAcxhnJojUXvVV2MVmuOSFZrz8YamK+MC2HeEw2lt6/tPwopKEMHM6bFI/bNzU5sFFecejpNPwTEsswlBLmMsszQ2/twBJvU3qZniYfgF1gMLoG/3spc0EXytkehh1/AoPEz2vKx9r5+tJvC2NmlaWPVfu+OrDTJB6sgvS8uxK3CJT2ytZSaC6yJ/guzdMXipHXrQDXXgZBBfsccNG5nv2kwbqH+lKZhrAlGBfGWaXix2LEACL0gcaGIrfLjAIUN8ZuBWOZslcyZcJ3MhIG6dMaIAwsp+4/fCOgiChV8eKja/kGs6wOMTLcR1sY3QvJuU/7D8KTqNjFif/0o8pH8mmjgdm15+wD93ncoQKH8rxD8VGU9Q0ejxyWPJTwM0SKvGMAMK3vjjutgG+yD8bZQynPNzlcNqmeBjuIZwXi+aNHxcgZoYvtBu4oHXEozOvI1H9dDiDnTxnHPr0/MJeGYdBx+VGIo99U5MMo08TswvucOHN8LE3Rvc6F8v/oC3dE9U3U72xtxCYfwEPM4Yh5HzPgEg5/aJffTXj2uInlyEPuPnG6OZU9MznZUQqeC+cPSFIpjmOrqXKT6DyHPeJC1zDZCxKXI5TG4TmlGKvWD8ZhSJSYo7sEk/xthFhiYdAqL2CE/NZJOmx2V3BEWea8ZakvKmoz7/2K02x3K7Y0vQm0yDP80IDCPCGxgBGYZCTwZJHAq2kBgIRFADKc8nhBczVj/YMSuT0AvNv5aDb+k5W1iJJknWI5/RdMm0HIhEmiahMzzyqZIg5ulSx5gZqruv6MNqvrbnm7jxDblG5zYduHENhwntnMcoKtmW4LT9Ho2x26U94UxasON1J4Npfbl10itnvwj/q3EisACuwK1I4LPje6H5Sqh43YDIWcooWeREMWnRVoWit+gGgOZzVANUvVWZz7e71sjP/Q+zNSHaR9bwTCUqpu1j9ZdFFibXbsgdeLwM9l3Bc8/ikfohOO0kBAXoJHcuaLJ7zDk1YF5MWord6t2H1F72UBNPU2pUhOPEm224JDnEnITlevxmkKtMWHx0+QT/Q06/B+vB0KH3gfjmQM1H6f/777OLmCtjdFVNmgBZTPA1C9vM9l9w5AVmNqylm+X40ysih/vb6ji77pDqnjyeWyrdsXUo7mtv+QYZxlGrLdfD3GEcIgFCoF8zTDzfP45GANvDdNsv+dUEl39DCSeDyWx86tQEg1I4jOTRqKUY6bJNiOJ1n+GkPgdkMhHcT2+CXBfMGl1m8DpbuOl/TSF9ogCCk11HQvlOB4phQrOF9NT3aPTq7d4brLnVoJydcXDFE2pGqqR/jBwXSM9rJ86ee2vkb27nA1z1HSomqXMLeggPl6Ofudm/FlXrjumnyzXHdMry3XH9OpyckiXYT4w3r5tCzqkt5JDeh1qYf41HAcScRxI5Ly1iZy9MRHz4xORxoL3mXM7D2gpESN0A5pm6E6S4R93qTNMdO1+NZxtHbE3zsGCsmE4Z2jQc7hM9xzWYNdt7rlOcjXEZmib8M4QufrsC+y6y1jXRfMGRq+XJ/aoZsDjw8lnocV6ACle+aUmfw8TdZv8Xl8D9QklQeou0Nhf4NUAaM+Gz2L+lNmxtAtpTA+rt7q+WruftqPDyQWqDQ3Lv8PodZBssLYAbr0h8+SwFbTdR20aA1/cYAzc21d36yALrxd3644sYOEGwBepa0f1ecwVc2ggMbGFCFjka310P1hfwYp385iF2vL0WlD2u9vouN9SNaujGuRAKa98ts6u5x8BNUvlFjtZVzNaaRYHTEfCNAoLXox5ZrYqw+Jx07Ba+wuAvAuP3FQG4H+OGQ+LElhV3TaQbMLlQ7W+1tGNQk1XmGf3MVT6wZE9xibtayRKTRpILZTtKtXWATRwJvYhY0rxDfi/TIR9ONDvQ6MrNU4b6DsK5dvidBNhdpa2Mm1jo+p+fqHJn6ObCueRwnmkcHGwTgFNhS8HG0yFvhoVuw+3erHhtYlfKL+PULRs8ib+ktwpFvJOyeevX9dG53ujtFgF9sb9t+DphIXc88iKJ/x5GqYL5VWATKN0odwRh2N0oSzH4QjdgSN0HBuhY6JohHZJWZxJuEfI7ESrQ7yqbj6xN5ZDQziV9rj/25TZtFA3Zf4+EE2ZDiUF4zsYUMRZKYgzG+WE/BibOnvIvha7yNx+BkUG+vu70PuU3QPJSnBY0AI6O0R3AdQlmOyNh+D9lQR7474hN6/nzOkPjCh4tjGtvxHLfZPPJQkhv0XI/v2ZqbnyJ9Y9P4/sPY3Qtw9M7k+CflS+/TL0yoR4WvB3rVNXkFPl9LdwX4fYJb8biVEAa0iH1Q4L0dx/wCUnGTPe/QX1s/5qvo9o+Uap+RrEe9w56ND+FNYlzl1jCJP/D4TrZ0EJOaCfVF8CTjdj+5lxmuBJxqL+BSmwvSoXIzRr/I6OQKAQR6xvLgJKJ/SRwkJnYWGh6yQwS1tsSTsfiGF7Bh4/p+mkvCC1v0ZoK6HYraFZ/3yxp5eb3zccjxHPO6th29XSuCKMpcm1GHv3nWepXg/IV5C1s9fJZwvdrYk/pO4pObTrLZL0+li1l2Lvq47Ve1+RvNGh7agZHoFT2STfFaiMo/JTXSx/OVzTygtBl7Ad9cgGOvYKUCMapecwmLGu04Y9T8pPnxtWWsSjLdkUyVqegNRdy7BuVoUb1Nfe/2jWgr3xq7648xw3j4szLNC1FOgkeLdL4GWoqJxovesxkLyaFocTvYryiavXtblRcrjBUhvxsnHLy5N9mcxi2yXsxHoEVScPAQRvrYsrsUv8YObMt/fBzTUwWrsGa8q3GnOonCIfsmjTxdSDtP9mz3QcWtpf1gohzuiw++4YzPa6rvgUZM8k792KmxY+1dr5dpVWvUarP4UVxK1bLwfrIhPgvQsmcoo8SGPi+yu6eGVpuNmA9pdptNo8tTJM30JytFD+E6SS7rzHYti0ZV9jRg9FE9ZgkbwTNK+yehCe1vUFPLuVI6c1Jp8M5nXKbKjS8SwvtUo3n8YC+psYzqwrehO/aDY0cduxYLGqTlOUS7UDxwcxlhgxXjdg3Et5iBL5jBpU4SDRKFTacBeTulUvHjf6xt7spUzGcxN7K0DNFENHXY3znFTQNjC+CLUJ8p9/1EWnI0wd3tG59dVfNc+Buqrzr1N4iG5hjKe8MqaFP2tFubtsg8qILpHyEsASkPLOzi7E63WdaGQ8AsKWXpvgmRzCy3PAfWWM/B7gYUxG164Kw86ZnSiJ+2KV39Et9glgeaE7tYgNurveJf+TMocuHBZqrTB9mhLRxE/xDEdHZ4t97Wk6zDPJ/lQr/YhbYdnPTwnHq9lmIptQK8ipFTkFeyjI6c4+yKnVMySE0x8xQoFniuKko2BydadeTQdNhnXD918I6OYWVNLak3jbklU8UIQ341U3F8oR7wbY+lcf3LbQrLwaw/iPBWtIIBc8sC/45tI2wNWZW53y5r5BbmPBLJUkhDIwbCOGY+2NS01kyJ28rPN2p5G3hFDeLn1CN0Ghdb61CCY0W9DaeuQdrNYt0EtiTOhYeAAOLPHT7yutAzRcZtrwU06b/QON14HG6r5NVhxjlDkDOLq7Xm2JNM8g5tbOh1ZYMUttgTRogTT5oz7BMtlCWgCNsowo3L1q4zz3hDTBEjpKmaYcvsF4CvFiY+CW93Hs9H5KDfTxJcZuspHdwAlgNy+tCW93UlbSakw8RxXv0iq+KljxYwxMxlPFu4IVj3z+0Yp8xnOeoSG8fIQRe4CAkniDWMlRWdkSMAVZcSMrM7YiK/FCrkUZFMPmw+7w+gyTp9D1CjmxOuQT2kwyc9dGHMcwbY+WNtHVpIK9riXd2rtmptC18x3KSPiXSGAunslEaJmK5bm9txGEwYYKDd0RxjE/bXxqm2Ly9E8zu0fd2+yJKKQboJHhoUQvSZu3+pbiVRRuyM1f7ipXeeyj5RbpKsUvD7hy1S8dNv1LCn5JcSWoXz7RJmtxrjg1aa+WFA5v/nCXFdIlX5wZvWH/tKEHCqHm9Jj01M9g/jQlUFLSBBXve83eWyV64lXAUPXzKxP5tZk6bXHQAQilA9SY2Fd2bKHrtGf0IhQHObtiyw1ErnGMCI3TtHwq1CWSqwZN23f/zpSYclzbHTmsA/tuGPbdx2+YNEPe9wSO9RpWI8OSHwMAZfMJ8juL1W3y5z/ouJPgUwmFfQyk2n0lgC1PxyTl5Sjd+KXDapy7H1inY+gbXmeNNuAzP7DxuKObyau7XyUG7op7zrCPGrF+6EasKQxLoANt8rwgD2+o6GRWuI855ei+tKt1B6Tj4ltOHIaq4Ttx7n/pFRhdcqLxXFZOrBLVvxeTnhRx1sTkWQ4w6Y4p02fD9IKq0omOVppi0MpobiTacW3KHyNZOY5+z8qRFFoO5+ZgOdy3BVnf8r3O+pXrJt3D6XPZaVujYtN3FC9VCR9Vwdx3pR5M62tfz2yfjk2gZkcwyJkq5EsapKXS4T9D47gv
*/