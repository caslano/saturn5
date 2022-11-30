#ifndef  BOOST_SERIALIZATION_COLLECTIONS_LOAD_IMP_HPP
#define BOOST_SERIALIZATION_COLLECTIONS_LOAD_IMP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#if defined(_MSC_VER) && (_MSC_VER <= 1020)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// collections_load_imp.hpp: serialization for loading stl collections

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// helper function templates for serialization of collections

#include <boost/assert.hpp>
#include <cstddef> // size_t
#include <boost/config.hpp> // msvc 6.0 needs this for warning suppression
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif
#include <boost/detail/workaround.hpp>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/detail/stack_constructor.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/serialization/detail/is_default_constructible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/move/utility_core.hpp>

namespace boost{
namespace serialization {
namespace stl {

//////////////////////////////////////////////////////////////////////
// implementation of serialization for STL containers
//

template<
    class Archive,
    class T
>
typename boost::enable_if<
    typename detail::is_default_constructible<
        typename T::value_type
    >,
    void
>::type
collection_load_impl(
    Archive & ar,
    T & t,
    collection_size_type count,
    item_version_type /*item_version*/
){
    t.resize(count);
    typename T::iterator hint;
    hint = t.begin();
    while(count-- > 0){
        ar >> boost::serialization::make_nvp("item", *hint++);
    }
}

template<
    class Archive,
    class T
>
typename boost::disable_if<
    typename detail::is_default_constructible<
        typename T::value_type
    >,
    void
>::type
collection_load_impl(
    Archive & ar,
    T & t,
    collection_size_type count,
    item_version_type item_version
){
    t.clear();
    while(count-- > 0){
        detail::stack_construct<Archive, typename T::value_type> u(ar, item_version);
        ar >> boost::serialization::make_nvp("item", u.reference());
        t.push_back(boost::move(u.reference()));
        ar.reset_object_address(& t.back() , u.address());
     }
}

} // namespace stl
} // namespace serialization
} // namespace boost

#endif //BOOST_SERIALIZATION_COLLECTIONS_LOAD_IMP_HPP

/* collections_load_imp.hpp
n/tGO8xs19TumL2meyDByjYOHaUeaOuw+LP9KTmA0+w70jv69Da3dkpqSTzF0S+uVb/uWuyFxQO9l5T6hQCcL3CCNeoOnMc9AVYUiTdnSBveWQn2hKCDeLLU15xs9imN1NmS8zJHSSLhSKG1BdrBq2ZwZwtMcrIUB/ZKWEQb3C6hGTBKboIrf90v7l6p/JB2UKffbjlXKO5oPpvsSp0HbPhZPJyal42WN1qcA7fYW2MMbaZ97t8+p/RXLXto4I2+1xY63gf4aQA+sxlUdOkch/sca3Zvqk1uas1LIx4LyjmFs4MDD13xpbBV373xGfCwLFgzgajs36nUlOt0UBX3Ya06ugexFfdkq3ttGS/+NzuhJMJhO6a8qAJdl6QNv0i6fiDOnqaI8wFfPyPyADIJzj4Lp3Qd3t0bKZuf5WGDnXyON3wDRQoPNHwsQr5ycHw5bxS9uwf9puRbNj/RF8ro6VPVlw7VLQfacvYGVNgyZcPqwermyIH27V3eMrNSHP/mzpgHpFuggl1bUivkgt79Z+8lRW+Ib5huHtz/wGPz4MCPNOwF/wruPKU4mW/CmjNJeaIFmTaSEaYbPjRl6+7JJn4fFY0sah1zKQbnOGwMtrLa3RW6NgNMArPTParaduW8xVq+OE3S2aEGKXrjpxG70ck/hD5pjfXpaykjgUhXgwxHkrFns5aU7B+05Km+t/+UnB0EfByVHqe8ZC5O+DcmAaDVwOldNRyWMRCA03hD88MscCL+BbafccoiIcRiIEfBpxCESjpEu+MoX7k6Qv2gZke84Jh+fNXfr79oodYtlmnCyV0HQY3QPmyTfZ7F8EYOYn8l59zgzUDa5QxCvPjehhosFTUg/bxO5jl2U5kTNhqZGV4oqbPjU/RE9EtYQ++Ots1vcKaOKXHSwlbqC+bSDPBIe+rb6BET+9kREel6JUVpBtgRhjK34K7qbaLHsQi7qHzgPcSJ6+kiUkbTvfQTTmPK+dIisC0lbcGTWIzPz0FQrN8938E/SXOOjoi+sq/yH0squiCXcFnGOvPbD/VEXfqtwvwHYtsZLou7/agOfu5zH09Pesd8dQ8W9asmxHzmwjT5I/k3re0Sdil7dNe3LTwXYIPEuaERd3CCGqF9/ZR8sAq5NcyChWZdQ8gcKGnYGqZ/CC5nX1Oy4jqjVBjSyNtK46PAqIgFhioq4ch7hDlwbjf/rqnpBaGF6QX+DaV9JIaqNGAGtPS+XgNCjUAIoBEIpn7svmR5wuBVJdUW1ccp08Cyhd0SaKH9qfL3wEoxUr6FCVzvVp0ASnN3ZYu7GUYKoAYmDCV/AAVc93/I1v0vHLXiwuRJcfqmPADMn8YWbzD472g0FMEWB+igFqqhj9vKr/5emAPzMHbceykNY1CtAw+zXf3WjotleSxBb4/jY++Q22Phv80TUbd61PjytFP8nCTWXnXZyhYZK6N+zWbutXmGBXeLnZmSJE9TsDvntv+RCEKkxZUEMkDZB7kwYizgDv8QHSQ0kmlIZm5mLUUyzOjNCGCXX5/DxDp8ep9q3ev0C9IS8GAo1vHJiRYo6Z/AUTr9bI7ZnSM1ruEphKUd5RGQJWxTJWde9LJ0DO+gWVbnxrs7bXdUjK28XEUv28s9aGtITNM6gwIlBPhD+6HnF+KbAxXMVr2tQTg1QpsirT8Ooj1rtOrdLOfYPAd2bE4CN01orXTWoRePmspm2hQHEIH4L1c4KodUrTfGAHg9SCU9nYkt2RhoKBN/A7oSxN8nD23UDFQO0/w0oApGfF5VLjCFCRM+A/5Ui/mBnvc3DIlqh7ZqLzEk4L/0mYqvOq3BdZvR5ZQiENojSK/O3sBB9zTxeM3feiWmr0DJQYjwKmf7zeufZTjFBuYKo2I9ztLXr1phfn0ypdxJHhQneqdDScPjZf7AiJ35RandR6IrcILHYZoyeVgN2fEoHWPKiF7AS0S4goROlWvOcnWxlRvVvCHjc+4C48ErKeoXzz35iBwv2jeQ6rn9oIQeQYImYLbAnLnOvHIG/jvgLe3twue4hmKHnNfijd/jd6DcXz+NbuhnfzRcqCj0F1sq3GlpG0/LH2ZrEUnfBo7lvY6+WUtmYr+OpGcfbr5M4JXM346HUKehM+9ek1UgV9Klwo56eaYZOCDyYeRctbXB61jTrAEJEdMq0wz+e+p9CXcCvGtIn2iWRBY4Jr+SK/8QXWOsafMPLTMckTU6GlsDn9hMIv1tGZ9fi15KHZGwD/6URBos31aAVhJyzFPwPXEqEnYGAm3Kp0dZdjXXpRuIeDwCc6Q2zf1W8mwogm3XP/CR5nSWj3caVjGSTw5N1vmeqNE6/ohhd7xUf6ENG172zi19jQaKeLg/6dzocQBmNZWgcAtNs+tLq9axMtN1Qo5+QOby1d0zDMye9nPUrVIRhsc1Y1KG7O1gThEWFzDhq+GOz85gAVpKkxcfbr1y7Rn/y30CWM9U3KDZrDrV3+CZsgKTTPM9/2suypWnvGIdXgDCCzta/MRsA47YbBn214mPjI+ePw+uOaP1EOye25+te8lCtH+8bm5d3jXy0hFCBN4caJ7an4g4hAIDtjj2vblyrghHL01QbpN5zlC/WifdoJT5jEY/TY1oTg3lHE3agCu+tfaT9oJfBUoIAz3qTC8KaA8058T9D+3gh9JXXKsZwzY9/I+rGUWw988+l5N30l/VbBukKtXVHfy+DL1T/wvPt9LgZdYBOTXsLaa95Y3RFrGsdD07GS+FWI6si6bvirIRmNGJKWA/42kHK8KpO09snUp2Mr1AkjX+OH3ptJgkWhVUaBCy8MEcaLzlsJkyhLmOILhHBqEd1QhuuBFQISdcYvIU7ix4BE0LS9Xkal/gUlgkmNBVU8Jo0Vx4rgYbzyIquU+Rzt/yzM9ItiFRG+otw/w5SMlOJRnIt6ZXCNbFcQToscgeA1h2OUOcOUi3xlQRpCkmi2km8tRywMMQaIGKR5QTf9PW+aC4BxNaGcU4HzXgYAsN3KfQJWyo8y9Dyo39lpcwEpQBrxricRpnhdq20o0daYRVS56nl5C3rtCw/sxEeFxuKP9X6EydAlrp8iXLfuoey47D52/KH+tBFPOmowZjAiRcqbjnBp2tHa+tSGLRvFTfQtkOBQF7b7zPeynCy1SPjQz7IzU7HiNpTzEl+wsRlKaE5T23LavNVT+5rls4P/1roNqUO6b8vCSQ+UyZ4BzO/mj35aWUL0lPNvahJM0DAubiJfk3A0sV+FmlfgLPAPdRy3o0+CgLeH6GKCOmbjDpu+hIyNKyOEwSdU0anTEZGehdur0BWpOQF+sNmXets9N5yXbocBu1g9yHAouc3G/aaXcciD55oBYbkmy/q+hwDhLInz9TY2iWup6vVCwf9otxvoQdBlhMMfbJPhNIomJPwA71F6c+0146NOrY8jcZgXIlmnz7Qu8nSthpDpcwFa/uOLWZrMt//fYNfluTYUVV1AkdWzo9XsPm8Ze6XoGV+tI3aVY0z2YD1NXnnQn5CfeAOsL8ejF/QzpjLQDa2+10GDLR4WUog+2NjwnX17GdC3sdLKbF0b5f9+Zm+RT5ves1B4Bqd1v0Y7jFPRn0qLZ7r3pNoW72KgUf1sW8B0DCG14wLh1pVW2vgHnIV5C1uPI/pqsEx7kWstxtNMAGwojARTgbWFa07DZCybZ8QqtLvShNHqfCgdUa+2bz9hK52jodVeXLbmy8p3L6uP74VQrn/IXTY211H2JrUljig9I8+QwHFd/xDYe9xafTDUzwjozTO4U19ZVopaKUneBqlcK0GPFD28Aaqb+mC7YhmyMaM9CZw68XzahfcymLZn45e2Jr09bwTDeV2JuKUj7l9Mi4XjBNPsFjIGxmYOyiR2RvFvLvVVL40AuOokimrppUs4v3aXxZFIZxzl2zUao+JyuqVXZc2znma+CshGHAgaToPz/1JEvMZKTdwEoNG3knMWHej5jjOWL3z/E6mBEF70A1mAz91Ogk+4Scl+qRJFKbAf6Q6KQ1Mguf1waq/npUgVQY7gojl01y1RKitaEeNt02EhNX1V5wdp6v07mI9UTKSV/dd6th8E8ekaCQf4i958wqcvmRjktd092pnUq5ET/Vbhw5PiGa+2cqWLXp1B9m3EiEOTqc5jlHnwoJgHlPy3oa030G87kjA/+4NhYWYlKpub+xVy9CyyAKjbriBZAHS2CnL2rh5bdPmM8GPL0MrDeULK1csN5y5zgqkL0TdZ7Z1KygMzTvkN4f/Mgm3sAs7MHOpt9jVxxTwxM8FrhVFyTDtOjxKgq+gcnbGkit5sPiqj+o3vfG6jCpXsRzsspEz9dkEFfqw0daYGykxQyNplAtCc5jnwamO8ydMGd5y0iEHD4+5dhvBTiE80sykFrKldI3qeED7Bxch2MdKYLYyOQM7kacp+Ho2za/gxIqTicwcErwQtVrHrd4Rj/EJYiUESfrizKZsEzFDtsvg4+7FY/moHyftrl9Be0tAbci7QnABccF6zYzzURGPjxCReHgaZ6tWaEsVsMHWmrSBK4Yk9/81sV5fZxAvHq3vD3UqGLSrIW9VDRC0h5HBngbVt4WL1/TOBSKj2q/U1Fc1L1U0BmMP4I/UyHbRurSMA/tYnpRZNDxyENVwpxpoHiJq5N8sOq4WSb1G53izic6p5v2YkGVt4+R8jVD2vZBACawyipEsqLOea7kOUdFmpQSIUFxqS/tnUD9/Wq13UrqbeSmcdKwXOto8hv7yOoOF1JmyJbaVGTxduPeFzbfXeN9y43gg6WkLJeLenv8ZwPz6as6FjKMuOnzEjPtLxEsjziEDD7sBzu/d7m0JjXyPboGCJPA+9fxEd62VuP2xRk3Z0o/GwXNiVcqduFe39B1JXohZm5lij+1T8WDMqXCXLn62/mi+4+AkzaR5zYjSLs/6579mPCq9Oj7R/MIJOPYUCY7sN15IQbj5BhKE+sdX63kjxf72ZOimooDh4mLD7RVHZF19Q8H7xk8MxD7bixRC79i3va2XJLFh0jwn3I2G1WmyVaLfMDLatinjoQblYXYpavkvP3gmQY3eKpamXOJq+1bnMHFriPRFgtPGCdp8LArPAb0U+O54Dd3ZJ3LkR6WqDMGIxvtMhJIesUiTTNWxdUM0nYqHeizL61O3/rVX+Nqv6Samrpfoay7otovaV4ccUONU5Fpmd0PVAz/xDOaYTHTWENfI1VBGu/X0fmS683DDWe9Mh9mqecXK+Wbly83hpQP3/zNDZohxiovvt6DoBbxr5W392NjVP8dSkqla8csAVNXKIcw7yIgxjQwclxR/LOsIWMg7kO51QwO5Sf2BgNhoCQwnF7OhRKxaLmiEtZo9emfKv7R8C4YyIL1vv6U1+vvy1SoyfN+eL3d+RdvbgeSLKX+DiJbz6Q74qEz+0hwNVYkTlKqDnujw1JF9WgGdeInJ66T/1hSYJkcp3H1BSlQUymlz96gHmqeMJzVyTqi6VdqXx6pCXr+7qgUCN3IyAHtME5Lj1kweuo+FYjjmr2iUujTfijDs4hiS2ohhUQfCSvw2jKIb/18eLyUh5T/PMeTc6x1XSj4fnNKsvOeG9lT58S1MckI1h6hYLmn4SvUkmWrcNNub1JXtC7LT3v2jVlyIZTbkkZxWk/TpcD+6oWVXCM0sOdF3LlL/b8e3205rpg5pt+yKpxOf2IHTjOX1IDZvtV9+Esfce1IM3Cl4x65l1IrnksH7zYy16I1VQ3VR2GUQkSWl5LMKE1YmdGJwM5XFjqfC69o7PgL25ytJBdDDxUd9xJpxC/a/ktakVpfTXJ3E4R5LlUz5ndp1BMuxfLW/hL+BN1Jx2FS094UemvL+5oxWIZ3OWkXT4s1tuYRZjV1hJw3jJm0b8rlrfp0uXLdYrtf3/hAln9ytooYsnpah8BVlaDO/4yGdB+xKxBbo2PehWIJiq67+qYnC/o9ZCNBtWJLq8Ad5mK3BnGCduLdGVslS9YzA+LxfSxpZJQ5L2Ln8GmPiRkRZZZ4Uygiq1XmOj279JkpM5dNLszWhjZJ8D2u2T7mLT60hSBk1PrNFBgc2JhTKrU6OLldOUQ0fKEFcwH1++VyIwR45XrpYi5jpyDnlMm3WxqLIeTYXQ9qZc8mgXZVy34hdGo8eCKbbyJlPysvHMlU0iZd/5W0aGO9JwFDiz4ItLWt+0NB8OnbFERNLMJwlSJLlMD0ds8lyPjz3JBAVXDBfzvRt1/EovQU3ixWR5DHTq4tfNDFk4TidN2u7kI5j2dDoBS7MCCgReMZy/OUnEM0YXcMbRG9u9j1IafEnHAREGf9UyipJClUdYN3wO3RzNxSfURYJdxf1oKl/xJPSC/W+DyaGBj/g/GBENQv9cHh07c32HBN1L8TOars1DNNqfGr7/xohk+UuxrUG8Wky1JeNAyDD8mBmcgpUVYp97vc32swWfXRDs3OhJxvqhS1Eyrj2TjBj7DRYVS8ZibhYSpsUR8A3HKI9l638DmPmeeOpu3BAZShVNvm6wkv+b5C72YXXk54elkrFHrEh1snYqfuiBDTmHbpq186ZTqpYerxWYCCI5OtyzPEPjox7ue/pRsaRI1rpz6aNJjNa0OPGHFPjT92eP/B/kr1hMeM0jz3q494QxWpDU00Yi2qUUkVAJP+NeOLdrkuUl+MLB9b5N9lhiEDHt5OLw9kxoWQr0wsWIheaHHZH77mF+lvUHe1yrHayLYTlrQ6yjEGYQqXNWQRRO+W1apQQx1P2JaY/yidgFtx5guov45rfvpkVBWrQQNgqZSCz1zKmtoPoB7Otd+3OlcOIj8GbzmJtO+ClDWvzD7ck65FyIzos3ONW3Sc8VCcOqCi8m1qgS7yrmQfUVa5a7MjpCE8fXMEMRD44m9eZYw8WBjScIdq13/JYy62DFmvbCbxQHofq0cp6Ed3IiRZFcisnl4gK1bVrEn5ghzmyb/Qz1eBbvuq1oDl0/1gfqEDLCPi5uE36nJWhXai3L4XIXZzL29KnxLlH+LZrCJv7CJvxmLSOmcvr35cDf9ejHdwlEXBpss9N5JxDX8Pu9vhfT3c5dfVVNNSOfEyBTrX1zBT9tUv4ereTYHL6ZbB1y7S9pWUEqQGFWhmhbRekvtZvFSmSaiESa1RPMtIbCMaVH3GM/QOe3XZQgE8eKmMFreb7vre9L8SOs3YuCJ5/wyu6Gz8wgf1QwyyxtwnRBMRSj5KCDIoKVCbOGaQS97lk7sA0ZUoMkj5CS7SeVCr2tD5Cpqj/gHH1Tzo8ujRQ0uFGBmZaIkSskn0mks/of+Nydi+idvR11QW/Z+q0NseHjVDtO/GXE4PIf3B+rkoeRysQ+2h5TDvyTqFpEelpP7XvIzQJOU5zlq3jU+xI/54b6AyUR3GUCYrS88gol+ZNN/vQoBiB5M6M6g+g5iODEpsA/ZvzPAa27anEOeZVnrecXey+E/EmTeEoWbrvNXdYYoFhcR61OidNqyP3wlKKhz+iz0V6LBjcZBJWJV3+iGleRSXCzmiNbt1ti5BcLk6kBJsuJyleq7wRpp0t+TN6dXIYnlZubB1XQNfRAUtU2BXpr0Bjzer6dV9ox6hegRTkfiFcxDwFZLLLzJ9d1MM7P35V8js7/Y6N6tUu+Q9L5NeP4gMtf/Nzq9mv08OGpHf
*/