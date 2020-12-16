/*!
@file
Defines `boost::hana::Iterable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ITERABLE_HPP
#define BOOST_HANA_CONCEPT_ITERABLE_HPP

#include <boost/hana/fwd/concept/iterable.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/is_empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename It>
    struct Iterable
        : hana::integral_constant<bool,
            !is_default<at_impl<typename tag_of<It>::type>>::value &&
            !is_default<drop_front_impl<typename tag_of<It>::type>>::value &&
            !is_default<is_empty_impl<typename tag_of<It>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ITERABLE_HPP

/* iterable.hpp
Y6f1XLmnY1lX3N29Hs84lnd93/V7r/7IsaLLVkUmVRwri/Ux1mdBcrxjVdf3nX720u8cWynWY6MF/x83eMzjjjVcz5zz4F0vO9Zyre/w+9f1cKx9TOf3/PaSx15yzOeybd497D7HAmI9jZ2ff3+FYyGXHTxywXDHIi676omPz3Is5rIuHSf/3bGEWLuxC5/I/VFr63rPx25+4KeOzRHbyuRsyDEP3+RYRszmZdHi9zscy7me2bGgx3mOFVzvudsT/qccK4nZ+p1571nanxVX3GEHz5rm2JtitrbnfzLyCMfqYtuauOcnHfW5Y02x7Y199uKHO2pt9/B4+ht74faD3tbZFOtjbNmgyVqjoJh9l5kfbt1Faytm6zBw/R536dyKdTdxT374SFLr7rLvj97tKp1plz19+v3nak+IdTM27Y/Ld9F5F7P5zK49cY72hNg2xub8fZlH5921hheO6/hKe8JlR4SPfUX3AjHbEz1/eucs3QvEbN0/ffJXur8UxXYytt0b8T85VnOtYd2+v35HZ9pl7/i+6OXYN2JdTV7mNtZ8r/MutrPt63+/eZPWPdi559dMP3KV1l3M9tl+L100VWsr5rU9/6clQa2f/KcBxsYHvxulcytmc3bnwpd1/5wtZus+4diPF+jcim1l7PZFP/yoNRIbbp75n0+7HOXYo65nnn/GK1HHnhTramz24J5DdG7F7KwEv52y1LFlrmcuWlP7tdZPbJCJO3n7o/prHcT8xhbvdsUi3Vv37NwTx+x92mjNtcvmVPZ6QfMptpuxx84fO073LDFb9199+0RWzxwxW/ehr3l+pWeOmH3PXObH23R/EdvRWPSu+x50zDvW4xlmzF/54nDHxop12Wjejbbxn00WcsUNOHBJUmdabD9jLz/41YU6Y2LbG5u16uZttH5idp/48ZmD9Wx8Xsz20oj5wwbonixm8/L0kB8n6p7sema3bY57VusuZuu+Xc/JHq27mK3D2pknfK3zt5fH02HstGdHbK672ChjH5ZeGuZYUsz25yE7XPahzoPYAGO9R7/4vOZMzOZsjwtHztGcud7li+cX36LrE9vV2LTluy7Uc0U6rp+xVe8911fXJ7aNsVte3GOEY0ExW4ednnupTXtCLGDvDMm+j2lPuOKe+NnVesYlXDYy/N4OmjMxu5fff+vpep9Iie1i7Jp3OvprzsTs+ef9snWxnv1ibcbunXDcSt3nxex+vbp384/ag65n/nrebf/QHnTFrTyl9xitg9hAY/vcEL1HzwAxuy8N/fN95zi23pWXwVeN66L129vj2cHeaW9b867WT8z2xPp3dz1P+1Os3dilq8+8VM93l53eulvzEhWz7/JWdt/n9Hx32TN/HHOY1l1sqHnmXN9l8/QMF7N9fcrvX9Vn5sRsfz7y+1BMa+Ra+zWfLThb6yDW1/buyK+e0TuY2I7GDt15f+0zz3iPZ7Sx3ucm39aeF+tvrP+cn3V3bLKYrd/vUjN/49iRYl2N7bnm8rjmU8zO5qSFo7Q/02KDjb3183/pnfZuMduD0SX/OET7WqzdriE55WTNmStut7GPvq97iJi9M/zykqOO13yKjTUWyiR0X/Ls03kNU+7uvpPmTGxrY7+4M/Sa9qCYrftRy7ILtZfE7H7dWLbvdMemi7UZO/CW0XntM9czZ76/i85tSsyu4a6rxh2ueREbaazj8BP207kV28XYFTPGzNO1hzrvkQftM1DPd69YL2PD9zk36FiHmJ2Vg8dtr/UbLtbd2Mqn5x+o+RQbYp45ZvGcC7WXXN930YvzXtGcme/baD8/W/eJhJit0dH/rr+u9zpX3ENTB++o/Sk2wsSd9Y9eF2gPiu1s7Lw=
*/