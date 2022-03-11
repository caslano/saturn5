/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/element_type_of.hpp> 
#include <boost/icl/type_traits/segment_type_of.hpp> 
#include <boost/icl/type_traits/size_type_of.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif



/* is_container.hpp
CMdqU1yVmfmod1Ehi02F5e7tNv/CmCdd5EBj16FQ4gAgU8T6EtRWmXY2iXtSghzBnZUou1KC5JWZUPx7xzX+1PlF6Hf66EYSu28sj6dSbwdDdouXwptC0bxowLPwjupUcl+KH1GIByqPbhCg8gcyKquaqgRt6PfweyC7TAKaHx6FNTOnfS4fYUoMY4c8FORwCtATtNl3BBbhdD42smlQ35f/4nNvh2Wwh5Os9e8hsBnrzZAtFX81nbjlM5hW73qiTM3tleFePJG0Kof3yONQkgzUlNbQisslssi3E3j+OYuCFHv5PQHQ6koMgKUWKgRM5ZhTLSQGUi8yRApoEwbj4HcsqUVkRHcruwmUvMoWyZXO5HAWMeGxrfBlUK10VTtpbaJXwN8+ohPH1LxqRNDAQF1ML+L58WmN2FypbAzc7bxhSAauqelwKYo2IwdI8iK7PzpGVIps5dZd16UkXrYh0atWveDG2/MHtKfZaemjthSg5sySlUPjVPYSGxzeqzC3j/Al50xtRpVDW0bvmdU0lS7gNBewh+eopc8o/PiyHpq0JQN3vQJ2xUmhCTE4ABWyByUlY6YipqhXNhEQzJMaIoofBtpl3kLveUuPAtLi6a+zvBbrxCOYHjD2QBLHJ/+nI4VKlzeMSptAr7B+lHm86LS4DwfiyXX1bMS7q4VbvEtPl8FuOpkrdNKdZsKUTvPJwM0aUSKvnIv90p8rEgHxG+fS4RORHxg/WdqJhhMwTQQ9ANpVLVgjaOgUCQGR0CXie4AWZwfD1QNuNcACBlH/NuMdR1QZc9A0PmZJkh4b45rroDqrH59EPIjaqhGWskm+A95KwP0+Cseb+t5cQvbt9d5wzWvyWxkXeaNOz9NnJptD6b4PO7lu+1yzXkbGp4nPWrN6ZY0atgF26VmSnXuY3870AFs1KGTjhW2UO/QEl0ghySlrGODSfmwc3fHvk+O971XVIXMKSq2C2ntYvOxF0MIz55YjH7QmQzsMJiHWRNRU5m/awKkjCy8pBNUCzlW/bDZhyIfeoNHK2EV/KE/iiDfn28uGiv1PwCY4VBNLbZTAGFAQmcQ18k1+f/ikodBH2WcCMPE56bsSJPS2fuPm1xixAMlegxUIfovR5VP33bIlNodWDwCgH3yABgMWWMjuV74HmaFBCICcMZyIXVfgDC+5mUhSkDx7ha+NQsC7nxMC1h4ku23A0GeoWUHpRPyFyOP8P4LSdhXB77ArOGyTOEcrvMVPl+UzO1xSLTyqctF5aI6XACJVBt1+h0VjO9LV03dq1cEDq+DCzGEOl+h/EWYcgL+s5/bKqzfCpliaqIi1iXDnb8/mq24m9RtCkB2t62wK19TBZYj3QO+mTNzCPabkW0aHr0oxQcIcOIXVGN0Nus5GYvLV4454abQH/k+lM7Ku6gpCbD5xzfJyxjcKQd++lzflPchhClcJtVHNBsuI9jFxQDFyDfp4fieqWvs+6Gnghwr9xUG1d19ocQtlpJfihz3mc7ObPfW1YDX8z8A72JrYB/0EdvsT4XEEjXawE0hnLlz+Idu9sWkDyO4Re9Tx5YvA37HWVpr4VlbY1v9tS57TpFNxzQXzA4gSYYtPzFbg69wDTaI7jfj1ln/eU61QaPaTEwVtfLfAIjNsYbkUM53o8YJjdd+qnGVLTsvhQ/M5NSEX7+dMNzdsgcmv/dvFz3FRIvZOcCx0WYEDdFA7tlafIH83Z/4OFvTzZTgnHrr96kYDHTjSq4X9AEHh6JTGJVN4Wj/XZ8m6moUeJ9M8C029pixf0fOmOC+v5AfdVt2zcVip3QNYAfx9dh7V2WZgGkMLCC5JaSYbQNKRmCTZYEgAQAoTIYNQ0/1SZXlbHcJ74EJTFWRKbQa+GKSOU43QHF+t9kzs6nqD6dmcRXQ11YrexIxrON68vJkqP1RuUJfp0XD/fVeil+o2S3YjrbOE0ZWPW8NU4ONu1NDPGq/ZdD1GoYdiTS+tRe2g1saW6Cjfi2JJQJ2+K8KVfGpKWsSZyEpOohTWTA/57jR5/48Wuhg9dkuJkDkBBicHoQmsVh49VN53Me90SbphnBHBEjuiUIKEgoozMiqEKRYD47mDCt1V0KyByL+yzDmapu1zGP3ZIiluFxsawsTPkTdbCcrEDDtIf3QqnSvVmiWdpg6ipxEKBuFjewMZfNt0bwmGY+6QDgmmVk2g6QQWAlCIgNufBW57PsdgLSCEuH+bIegsr/mtW16LNWV81q8lzDYiPzQdEJMaOkJzUrEqGNhlN8cWPBk/lUTM5rFU97hMd4/SExgd44mjVUEAxWQVNbB08AK//RrpVsXAHXa7ROqnM0+jZb5wQ5xGrxObz/C+S1erbw38yV8roQ5KqRX6ofvYZWJDzc5uoOgYO9R4BvecuQRpg0SxYdfLV9t7XcU37N2bn2oTAqab9FYJeezXCJv5WwX6RMw5WlUsgLVGK0ghADXp6HCPhn99dgtsSYIhmIP9KD0FB/n4pNBV0n8TBDUWBgHAJEVmjNBFbahKLZlG83ASmBuHzZI/PCbIAyNvDWe7XA+suxfzHHPLrYMQ/dQY8w0z5HP9Xz19CgkURPtBNUMqkIr7h8sxant2cRQ+YXDQkybIlw8SAJsZx0HXMM5OIxi+i1NyvwQKaU+yMeT27+OHMcB0kDIt8g7Y5tM/xsaHQ/ts/a4FQYR6EyBmAgw4pB+iXNi06Ul6NiE7WZcR8jlnxzf6gqnEmEBKlGAUl23XZgtcsxaEHJbVdQifL2UJXYRHEzoPB52XiO8XYvuTyiA0XDuQlmEsm3o0Ws6r2M60VeDS/Dstn+3osGKTb/fwilLjY/DQXoUbLMqNsRvHJSe60oKymUCWfd4Sgb1HA0E1vZ3rJppswJABhWiZFcW9NcWvkUlEMyIHX0vLH9RoUc31kxYpyBGdEtDCnos8E5X73xPGTOG+HfgEXfHHZk/bhaP/yELSUZGmCvMlkFEYCUAVHvPJQJsQIBViDwlcaC9QKHSMoQ18IWNXOhb0gtzA2XY9T9eMtX4XlEe7KwFkG+5HPyHiT6nDVO81rgj9M9+hDmUteHCvsO0zR5ZUzAel+EmwH3YjwDUqwLgDrlReAObUv6rwn5jody9DrxTxW5LXHJN0IslwlMZN2M1gM8D6v+NmhD+VQlGJgPMJvXYXkOatBWnTz2EVj7YpOK+zMEUqV9Ccj93+nXifV5TZhxIFDlptzeXuh9mu5aqZWnAt8Jci38mQtpcnyRyap74mOigFV72mBHs6mMtEThOQaBtmWlKgre2E8Ga5p2yrZRdjcZMsZBxlmow7R10/hrsWS3+o/32aFOQlUqh4/VgaIkJAypyvD51tuYuAEM9/H1NcjBKiTOvX3CLP3mT5fFMLK1BrxWWGO6ubchmRtvZRGnY7jdoT1lj+JgIxUhlo0Trt9pfW1TU6auHBdlA6dU0OX5ie8o57M+diktS4LVLiympmUghyAFQmS3cfYEKOORRADXOAIBD16HhSgK/nj6XXTZ9n7pthfels/uUHatAUxrAAXVcqyg7AF4AcGsprsEbMBwz8bTy9XBohyKZoSjcldLby2DRNacgVikTVddsQUKqPgAA8FTLEQACMAPltfvADckzjMvBfcJCPLii0zRbbK0df6Ycn1ieS05hAZ4DsO9rRKtfrrb/RxvL/EREzwBwvwRTCJRRphsLSa9IuHuFhdgiq4WJ+xcCPweE3a973F1BqaLc0NE5PyglhP7J8PkEX0gWI5cPlFUeh0T8SEsezIBWt6PHgM5Ob7rwRs8iQBjekp/PACBpLbJUG/MJC2pLdAL7DX4atnj/ysWFFrbpvLndW9zyEinFRYGzKcA9JjwtsLOY6cvMXSnUswNGHYM/6v3zMYIsXDvoDtgvYRyq3EE7cEXiOFrvKgg9tLbfHjFUtn9Ahwn8TLJ+WO8rPdKEDBlEooRCBJoLvPL9r2yGwLNIcjwoPF87KV5sRc61C7EdV2njoY5Cvxy2Diac8G8JnCnnTih2BVJn8qkJZVNzeN3SqyM11izaUwoA7bHHVp9BEtu/XACJWqmMaNN1otCT4MxLmqljdI6bO3LmCiu1PJ4Dfk6sEwQN2tgcccQVUtyPGUSEcge/wABzN24Qjs+eyKvhisSnzHKXa4cG2h/TkjN9kwhANqTXndaugjsB+SDjM70BUWVwOc+K3QJGuyHtddbuoSXO0FSeI18CW1eBn6MSiKkltd/7w4Vi5fEsJzRAacdnL9RAWL2Kn8FjeSrMsGBNsAH0PovIcZAZbycLJqsib+3okuxW75TRYf1MQ6DyGzmqmB5BfGD+s6z25xzeNcI0JYXss5FrMtNPZRCPGKSTpl7EeLZXlc3AEgUpjut53TzQaOPBWo3VI5kAhsExhfFw/4Na+U6XAEH6qS/z3rE9foENkXnDo74NBYbzfaSkGFBXwyYI+13UV5fk4Mq11m2o45KEd8lQ6DkARi8TqfePGVKLdUX0FgyTEqfcjLA8/KRBmxGe2vOiOSkW4ipx+OLPLSCLWX4FBBOofEKE2LphKgH6VcFXk5+YVRh8r+xhO6+GzdGNR5VttmpJNk6Xbkrj78M41GWkpYotH0wWrjNIL+bjHkJ9ITBKdDkBhgr2+1g0l4xf2QZU6txEMQsvQNqXCSveeUmiOZJ0MWZ0tREZgpYYKj4nqWe4lc1QOkW0c/N+S72U/9XmE9KqzZk3byoz+iIX5+fiH0wnaxOn6Kp1U3PMJB09RH/JRkzt2SSeAqpRkgsSOK2iMmcRWJDwgmbTpHEo71H8/PBn63ichpce0bm52OuW0zNXeaNSBwC2V3c/Z8AEfEXOh2oZ6l+aS+pEyPQpfn14Zgul5GAKUXguNy2FRMzifBiqQ0CyKLuZZFIhKc2VLFIMam0eyEUpN2jhyeOb+9KQC3MN0Pp/NP42XGXRJEptoq3G/neXpMaZOzkfcV21Zw+J46CGB4v07l6ZveIbhjUZ0VAEkk0UJsPWI20aEsfUUa++ReETqkxYmVWFEEb8o6h8eNT4xEYtJLMvqEZeRDgFVEDiD9v2CiwDpFZ+SZqy3WRRRsj7Mdnh7w6TKB4WrcTqdVVnqnqABx0rFzGmIyEbUsNH85CUUZFJA9LBFHKzpOZNPS/TueOuNaKfXZ7aY09WuGASsSJ651LyWl1yjBee1WuPYpMvaua6vPVPsxOjrL3hA6tuRBqQoa4PffgAUsqgCK34A/sLSPmnKTRRQ/dpttlut/79c/zY2z633j8Ww2WN0EzWyCWkCL26TF3yt5U8iLSJn+8mpo3fB2Qzb4TFwBcbcigdqxpuJWglNLjKESJaLZhPQiAicDF7oTQhnc27CQfhBNqhnt5G4GjItKOzpfwTnTJJRABazYCKa8CGlwsyPcyK/Ujwh5GRSRNrBpPbpre2FNJ0a0yS/SEyxu6NsRUXhiLYWIBEjIZxjyhRfNdhjQaw/2rmZlWr8I1Zt6fK4e998mRptdkNoduL/9qPM2drvH4HRBcOHsfeA56OFCp2EfVg9KZUEnkMjHJsJv4xYhIPKjzL8zIb1VcQDsJaNF3CKoGk3+j2pR8CKtgwFSQ9SyV21oSKI4p31g8HNusJ87kVHXfdu1E1/ClMwwaKRnH1e4fm1RK2dftA0BzDi2gv1WtNKfWyX9rRgnlUTnR3JuxQafL+2kwFHFG5s54T28V3SgCkFzpuL/MkI4d6f9u15eKP6RmJgLbTRaT8iDwZCdgiMYyMxSn8uq8xXY9ZtsD2mfSveZqjy/O0RigPYF2FgZjVlVoYMTB5M6qY9AjVeGAdEHEZyVJ0IBaeKjMgojR0FUyUC2koX9m9/HN1keBeFGAP39tTNP52LD/O2n8UW4Xg84Op/1M1EFX9QOu2LaDpMYq8Ag7ub9z4fOmEcVxqRxee3yG5Kqpam7C4EDaMz1S+p6vwIT3V6HwqcIP5dduT8i5zXTrICuulomQbYlL5apR5sTb39UaHzw4BYzy3MgVx+vF8+B7PPxugjzGWLIFIH0OwkZ5yDo2309Jh3p1A6pej4t36oTgGbSGbv2twa28pxZYFf/6ZR7GOVbPyauXOeW0nL/k9Vc7ELPRw8HPRVkBqKoVXqiHGSz+oSwa3NulvBtOQpfrtovV4cXHPkpKtSImRENBv6VY1WbAxTDoMj7aWUpJbG/vhuD/1XsnTPxsv/p627f+NzXaRUC0BjKg7DKOlkkGRB31WP8UpmJl0ZvHE270ep7cAD6XtPudp+zGuYpE179IGT9Xs0Ty+GD3db9DYAw0yqWmghFSafQsDzAB7C2LWcB2hGGg89+eTUX9zVq3s2MK0BW4+raQviESml3n6mrg0tGEf3lRe59BZZHEz299vQJehursA1GaewlQ0Elm4W+z2tlLOKrts/PfBocXQFedlICA4v8KCQxXZSJ0oVwjpsETP3DhnSiYcAY+q8TVlQEDiYOGxuxo4mWIn5B62Tr0g6STAG1D2rHyFQoB9qQhg+/aO91pZP8m5aJnPrRXuzNEVUsF3fs2VSFRz4bJRXRClV2iu3MUl+pzf9YGqT555c110VpdweQE8T9yyi2apOyeOx3+sruMa8RB96yJwBqPm8Oy2YGew02RKsUc9qYJ4KtbFsQMPj4zzb1sRaR/FZWuaN8iOfKN3i4eEogQZo8NieHJk9SrFfytpTjFn7dYRbWqXoous452pSE1ZMSFzueMZg+eXbdR2Rn7FwJOVm6IDWYB2ebil+v729x0iBIpLhkrrcdXAU2pBc5l2j2NvuiPVTi5nilq28FxMp8Ve1bBORkYi2CmL4aY4spyHgY861jhT8YiQ9s15tdHDLmXkBMQz7ZuRm4ECW20P8vu/ys6uvDF+oNJB+vVqmtkSHDAXgAQS/wNoioeLY2vgpnJHytfMD7dJnGRSRelMFMzKSAyY25Z7pGgFgROCT2ANMnX/+oVNRZfUFBjB8dl+ujtBElhPsCfreovlCdpifPzp2ugUiMETHe93lhYTw4ZAyGi7MtKpL8wHnbPz8/Ufs0UZtSyO+PsFri4KUQ3LZ3XTNme9Mo9X2mgEHGwjt8lF6ki+oNtjwP1cggweMDMWDzcR2zv3FBjxNagxk56Hi0Ut3sFjre9IgxBgHRitW51fKyPWekSqmJzamX8d6L+tMwNZ/hwOjwgLjoE0/EeJFTrxodSRoyBZJAP8c81EedMrVqU5YCYxmjseAT32rmhlfdv+DZccfZopSzQm+TtO9K/+UBlPlANL0upM1uMVpyCT6PeKfLe81ljRZqc7+eSZgwhZtUAApn2eQLaZKZ7ZwGJdQKDklt4/aFPeJLmENay+cWW1wd6PS3JipySo4L43ZFfHJRKedrC2y40HIHkw2yQZB3zA/sBruBJ6f/i4Vt1ju+E8NBnPqcnUufeICFz5cYK/uo+/n0g9c6RR8Po4z2hbnQt65fFoNPSyiYir5I1XoXnJG/11W2n3HtOHuJmZqpGvxUIK4yH5Btvmr8cvVgjSa7W79Zf9fNY2r172/Z82HTKV8Bsdl8uEwtWthkJh3Q1DK/uSj4/pEy+9wnjwKZEy9y7PjS3/VFTHSmIOpHNlzwPwlAPnMx+/PpZksVRRclHOiRJe0sohptpjtLbNU0CFJe0tMzrDONts1d1FyLIg7N237M+pXgeCycnXFpLmUR6CxJLgD7OKSIWcZ7Pb10ucP4pxUNZ9j7juWbbFSljJxAEQWJULXYRDejxiUjKT0SC/tprAygUBK2FPn5zdlXXODhGq7V+qF/2hIHnpJDnhBi0BISM4/T99D+fU35P8BG4DkfzoBccZ/HDlPTIgmcThWZ307t9wxzoJp/KrwxEKUuTEAW+pmrJLmZPOt2N2byBmLWiam3I254HN+B5zeHjYmeiF6IyutUzlZ/xZInMCMqepDwEfSoR1kBW5FpFX2A6pO83fr0O3jo+Jesi3NR6KXtjgzzoID5dyWPX+ad3cV89kY+n3HJuuoExmCxrVDmNx7uHYhQ5iFFbymRKH2l79lOd07Y7vtDE0PFRYdtpvf281VjYaM7zCW5qBM9AnnVJ23FJ7uoEXB93xbIy6UMv4O46GXur+xqVdY5fh1ejelMhgxl48gjqWgrPMSFrnyHxepyLgAUOxVTQSpecwkD2p+NcsZWmshDBBgK3m32LlHbi4L5Cm0ib/3eYbhbO38lvtUjFLpdZVVng8qGUWBylnypC5CejD1HSwiUUBBXoEknuKIgfUROSoK5XOJWh7awt03Tf9dnQkXPZo7IqSU0yozZdLukKk/nXtM8p/bjSCsh2y2S6DowGuST7r2eIa2r0WKqlOvvfab/p6ixtjOHv/AZSHYbD8gYcUWfqqGaTWnadByekRZ9rt5jIKxYnsFzolR7/eDMT2RQmZ1V9ffvUFpf0D0zsOiIrRqMIlRheILllt8vHz9xIGDTV8gcIezkUrib78dXEu/+nA+B9gqrSVAq3hbU+jL/Tvx7ee/1OB1n/J4fmxrv7cyMhN0/W4/crzG4dpDuvBI3WJWVcdnAww+BycaISdznm/8C8qvlv9CzkCYqS/kYnK5bsYekc8kUzKCA/PuShOoSjsWspDUO05j+uz/+fWI8d0htLcFDEvuTkKAIJ1m8D/QANMzKlPoOmaVQj16SGXp9sjKZUMYOAY7lRYMYq4xZQeE5AXVeDIP6CroWxT47iE3qe6C1XQqdQnLosJtCYO/XTM3mltAqbuisHs5Fw6UjQDHQd4fsbThjMKJOwt7BEsrNy4Hyjc7wBgHudYUz1J+m1dGmCsh7Y1x8PvIusBAnqq8k/UOxVgOEqTi0sX/g8eYG4BK8ghxF3ejaBtxrIMBPOYIm3neIC4bepPi123u7LqTt7ZrAJP3FuinH2sHA78jWomKLial+XdB5/R0nKU0DlTL8kSAmYJflbDMXhzjpcI5wUH8+yQVG3gqtm3XqTuePQxhTmmXa/eS+Hy0BAlGX9XXAABXm8A+dxuPIJzBlfxYJ/v1EmrndhVjQXm+2hDOB0eUwU6eiJT3ZyCQOmFniVHdiMp6lj4q2e85MYf/Lz411aSOiVBaTII9Y7NlgoqdqN59HjenNOJmM7EWQCV9kALwj/g2ij4arvRQDWesTtHp13MjnmCwQb+fUy2yduiwk6ZGXend6iCOejUWxVieip/eZcMqUpkrZM7o7QlpNLmZzNFwlBkOIp+7UIs=
*/