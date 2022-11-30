//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_AS_STRING_DEC_18_0644PM)
#define BOOST_SPIRIT_KARMA_AS_STRING_DEC_18_0644PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/attributes_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    //  This file contains the attribute to string conversion utility. The 
    //  utility provided also accept spirit's unused_type; all no-ops. Compiler 
    //  optimization will easily strip these away.
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Attribute>
    inline typename spirit::result_of::attribute_as<T, Attribute>::type
    as(Attribute const& attr)
    {
        return attribute_as<T, Attribute>::call(attr);
    }

    template <typename T>
    inline unused_type as(unused_type)
    {
        return unused;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Attribute>
    inline bool valid_as(Attribute const& attr)
    {
        return attribute_as<T, Attribute>::is_valid(attr);
    }

    template <typename T>
    inline bool valid_as(unused_type)
    {
        return true;
    }
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace result_of
{
    template <typename T, typename Attribute>
    struct attribute_as
      : traits::attribute_as<T, Attribute>
    {};

    template <typename T>
    struct attribute_as<T, unused_type>
    {
        typedef unused_type type;
    };

    template <typename T>
    struct attribute_as<T, unused_type const>
    {
        typedef unused_type type;
    };
}}}

#endif

/* as.hpp
z9exG8QT7J1k7HqV33gZj2VnFZeJ66VHzeADcuZT1n5JSyY+Ifd3RNbx7i40d5jYGa3bU/04OjFxFOGl69jI+sqMs+eC6i4VO72DVsQuwrmgHRxCGyl/K2ktQv+W1lTKPfNmEWOOrY+yj+sQHSG5uC8EGsEeGMjlMA7eB49I0FwmBNTdTAhoojP55fgRwxcbCZfKI5XNyhgw8VS8mNYhhlAd5SXsiqxStMcNI+oy41+PEfu5rwWpExjYZsD6BfbFoH3DaXNy2AzDX71LPvxnw2iFx6FSWfWGwSZ9GTzKt6D4q/U17ey0+xQZPJG6HiOCHPb7X730vMm9ms42XDi6f+xxS27OgMGeFgZf7JEEBxGAeM/TdUma2OglVGDxetMu+aD0r2e75JV1NPSPOKk7t6NEHHQW1U2cq4g1a7Ma+ldzs5Kn9rMjS96z/v8QGdO0/p+lxv9nmTG7Fc6S1/yNz+VMpyDT2EaaEJqJIQK5JnoI5JlrdL90UE/35Noqcwl4auvR98db0HfBC5RYonnxzW2fMYBWlQre4O/xrMI8WAwt285xs+CjDJPWV3jh9sWY5YQ1C69OearfeaKnUZLgXz+Xv/S38RfwFxKIIPtU8VRfzWokcvUzKZv8nzayEmZNy2cqhx05Lush5BnJNrZBg4CoAdVK0d2KQZG/XdNpxF/Ho76exCw7LG+2LkeBTR9SgXc3muoi7khW2HiHProSo8GGF8pBT/Qj9bVNm6bsLr9aDWvSmlMgV5RBaX92bTOM2BLLCDRihMTh+uUYEDu++fRTw6jnfuKWgTVR004lhGjhRAli5eq1UARJSHomAzmdhvlaDdHEUKIGbyonjh3iDVlmfK9u7DSUSLM+DoOsXNUoTD816lJWszOMHfhQNFTC/YG89jPVRn3JlHTrxMxREUOfNirEoGOXxdRYNRrcHIPbbVpQiG4ZJnSj5g+ukuEdWLyO+Yi/oaiwheZoR/vG3xjNT+apVl4ZV4LXBFpJnYCwiJjTS8UTOPtXzQ0Zr6AUGetJD+YXtlRu/MRqmqz4gOi3yIxa+000kG+ddMJox8HoxFNzNXzzOSxxeFEXUVuw1nHDXmthgafagfcH5ft/om50+z/3VH8Cv3GP0JvWLH7z9m56c0TO+BNh42sgQi9H/AxXDYLKbPGxPMCzpskOtyXY1Bh51VLrK21XUNO+9LgpbN6paz3+w9Gh5Yk4VkEoLGtXfE5V6rFtyWxd2yY+R1dLqaYHW84a9U+MvNzssgqMY8c5c3KMXzDJPRphfwGM6t6TgCWWkkmI3B/4/oiuajR6k/z7tUP6E6OoLN+iMdFCMX0M+D4To+Zn3DLEz4LyR47+CvITpZNYlBl0UQZGwIMjyAb2r+sSwUZfrDbqEMEmPbhdBJupk77XsMlHL/PXRy9BeJFcoW2rX1k7UPUl6ZJXCJhzbcMY/YmPhHNFAMXQlgf/XdsF9Gp3gqTNdK5rnpHzUKC1VPxMKLu2QNl1VgEVcwfaC8ucn19KrSRauayFSuOC9bLtCO6Eo3mij3eHqJmzEmvYz0Tu/Z8b+i7ubk44TKT/TojmtxNNaKx1wR2Ncq/HxFNgG+AGqNsamlScPnnDpXBDjBInLGdT851FxlQ9BtN22PXNvvYc8QAEzl2YYz5wHAh5E8Yy2gdhibJEPWJe8UjJBz44a4gJcN1SY0SLxNQCHYFYtmYQDcnHeC9ziIkFvsDOqMd0BfKItf0d8AmUTXMUqPMFMUeBBjGspMSgkacOHgLVazyFHsJt24LXCOdccsLigZhyYdHHWfnwfp6kSiWGMzfvsLrbRjWkrHTG6cV56ceET29ZMTOfsk8sVaFOZubKD/vQ1LPsDrv2oPhMK8YJvdtL7+ZykJO0opGyhp1UqV3hW8EaW8NFSa7vzg6YZ5g2oYfos6QL5Mar9bzdcTyoaO1MIIJ9x53sITTgJnQwfTT8hK4lmPAf0dz6V/Qqp9jf+gunDaazviUd0TbYOCwPyUs+/pzIpOWIIFwdfQ+BgyY7Q+zF+/fvEGQxCKpx0IaoO1MdIxsrmViKDSH51qJu9ve9jeB0ihiQlnD7j5gnlfK4bDqqBNrZ378Mj08Sy3Hy+PvBbc0szZZ/PQpx9TbzXDLm9VT/kOox7fZ2yrdpixACFEFcKP25WA/1LFsE1yWHEJUS2Kgivm3xH1lWJIIbxe5rKO/yR7OnxRs+nxi13yUC62GkttNRZ9qoLXd0Gq0S2DywpYiD88Fgxx9HHZ6EB6hFgCZhr+TUz1o2LX7tg04eFGwcqaG4gRZSIljLFoWyoa2DrQlrZcWbZyxrQryWv6M3HJmJigo0hORMuIsZlyiGhftWLr3PuVTpWReUvlWVHjFL3yqNA5mlb5Uhq3QqKrAqJNuPwvjHQZPSXUXLzR/YGOurBzbqL3WoJQ2tyaVZsCCptYyYv023RmALDYg5DKtx0iu0ta0v4sS1dCVyV4vJ+YkprhwsUmpqL7RlHY8544GdWQJBxkyMuhkRsig3zdOVmD0rYx88cAHnoFXQK2en7pOd1BMxKKE1llsMZyYgDs4ERGWJKsoIZazn+sDAJ6ZkZW2G0vXkAsfkPOiwtGNQjn4ur3wYsKqUY9pn6lpLK3wJh6z5PdEMRmujCNTCFkvbLoYlgo0lIURuOWxu4WhNYNv1gSZAU3C9ajoiDW3Rg8e4kIndqpDYFjG1wyzBDH9xYVcGZnaFsDqMLrazyQi6Ea/L2iy0pkKtkfpCFaiZHdbIrpxFg9hfaKfdyNL0CbbA7HyLTc2paQH6rK2zV2Aq5RZWlbOwG5ySg4rWWiAsCbQQuBCe1wMScxaxF3UpmYESX9x6gWCCFvUHxyGTyP5+dmTAfIgQgDgiDnxDm8t2XVuna+vlbqoHHkyJS1m0RNc2EZeia+hLC+eSz9N7bBbwWD5GX+iUsb84YQwWGV27EogteYwQWwWc/hQ7aVb0imOY9ctBruRY54GemoGsmlYSSvC5qax+j7eMS1RUhcQallx9lx96aj5Po5ZG+QgWQbEz5Ypm+PkO05a42aCJCDanLYXbpFp9zXLF/tTqQxb5Nr2Js4qu6clWFOeC1fNUdzJRUxldPNwL9nKUHoCuWrbMjmNimtnYljalSYdpUgm1N+ncfqhVqAgpzLqOShTnhqieohPSdY7WObNjouFbB/pRcf7dS8eLveq82H+QFvtxdRqcyO2rP8cPG2NwDvhMHT6qOJZwlzgalJgv+X0BOD4mLok/0GKLP3DKBrlboNm0MyB6I3isPtDmvY4+DHXMChmllapsUSELK1oQ8bJqpao5HmjqR+3xBZuW/qb1u1AISXduwVvo3IU9y4F0LNhganLFGrThvtghbXBRXdGBTO3k5BUReykXdFh6wdVRQdutgpCBSDFA+u8/AwJsxOUmukzmq4K+WOVZXvKOk8PORGmual8GmFW/bQkoOUhuYnJeSK/ZAsWQ1NL5Wj+2pWHneiqElW9Rpafm37h4SWkC/h0Dn2gAvnw7q8fg3ZQjLMNydEZ3B8znaWuu4Z3HAZccr8O5vyLXVSRiEV/O13BvnnbF0W9Foo2+AWWZiUGIfuWo0GLyQzqry6S9dQwXDusb6hlEGyqHbwd+tb6+RQtZI4Z2h3A4VE400A50V7Xe2IFBkM6rLKUb7lJ3z3mjdW5fUBFL1OCIeDU3dt3nZhvW80NWaK/ZwNd5fL3Waps6nq+BqSLhg+gNvXqT73sJwjltEHsZiGZjS8jWFy1JOvRFD/legiY89fgl1Amd8EULox6dalX1cU0ctJIQpnZMp8WkNWfS0mYlj4ofQakhvTvBym5PITcJVoWNPnbqqvX3Ta/UcuIyix5dX9bsE3xS7sd3r0HWwZ/GIelIvHZMFbh5s1XQ5mlXCjDom/U4y0XikHwIR4SgY9XncEAP0Tbd2xOJ5Rn3KUpbeXqyg/sgfJHre6xS89TXQA0NSMb32ALMPG7x5kG6177me+w+7T7f6yhec/leX01/o7N8r6EV2t2+11ib8M7ES2hOOlKmV3Bzr88Rt+kvcRv5njeVcMrWERtA0qyQ8DiXlUjU0p1nXZ1es4khBr+W0P641F9nYKPW9aXWeao3otmv8yc16/h6J1+zrc2tF6pF1CCjnkAW/5kvUoJLPbxIKeKZemi51ZpfppXgUNYHu+Uj/Bo3itis50WBQSWKtEmIOrQnzioAJjnBRp+becMyrZMUOJlbT3XdBT2o6frP2hzT6KWpzXEye9uL0DQ9wW394E1q+on9VtORzVLp+MBsvNy5P6PpUOsIyMJASyF/wBNmD7SoQ5FCzmU+OyVLiJY3tgFSxSrI50oyzFSDp4qM5DI45GcAme177F6tlGkBSe+YdhLpGo5+Xtgu4uhxYobdjsB+wVM+BgvtK3BWyqaqDSJVvVKYDp5KFojAKUeg7T+8FlqLYwcqcXBPYXcfbDNbVIoWzey1gif6XuO1OE4tRKXZGWgjwi+9EIl6ctDiY3FkvIV+6+NYCZjoIgLTeAJgbqTnURumcJ6q6FAKSdH+1fMis4V3pLHxWAXJWGZob3Sk/BfobcuYDMRbqVkczpLGgzgxfLwioqPlHsprLHpIeI1FUQQFXbREKDfu6hNWAeTzp+S85wFWtEswkMpFqiGXq5HRhonp44iZ6itnf4yQB1qOzodHcBrHhWFBonyrVHX+JbisXyJnnGeO9rIHs0xwZ0vlt+MHDP1p5NqsJxjHPA1cT8jkR4yd+wM774lO9u+O3uErrYwOke2gSZXs8ymEgksWKzTi36155Dv8Eq8wWSLBw8KmoclLfDwNtFfxU2MHj7id9yrGNcTaMxBc75t+rzayRHUlUbPxcwgLD0qjHYQGMBSwfGsNKC8EfKpDrPPdVUOEwEL+1gGHo8ExPU8P1iWH+hhtwWUV5hm6P/ZAXfw1pt12FSwHjhSTmXiL+sy22pl8A/HGQ8f0W+BRuMIZWTg5v5Aj7GacQO5LZu8auZyxvRWdETa5xBpsNjvAyB0hmeMMEjbRHh1kjQBv4jQCo7AkWRAwkdoDnn2cWnjWADr2U1XE4RQysqr0LgcD3EB5E8E6NhDlfOCe/CqoZsRcUF/vtZbuFfGM3ZDA9cxxxwET4TVaCC/+7aYsc9TlB99gvoHIrsIG8xlxPrJePWZL8WYFWEa6V9vMXo3phTpr4M0iM9KupwZ+GYgXOKjzQMgV7C41ehPN9bUvsJ53rm9hQdQjGuSvN+OoecVHEFLipDP+kSO+f6D6jlmobeBhNiMo2Tb0A9jObC94lG0hNdZFXWpO9B0b+ReLRg5YQDxLzVbkVWzLDlyDc+GeqF2RPzcJpWbqfSb+aAQkMoWEcFNMHulMKgmmkIhoEUweKdJFMHmkCBhZ1cCkKdW7ojYLUi3fijr6WwUjgr217e0pv+0/fAjynID7+pBb6Li2K9/ulk7vBWbRYZy9Sxl4C750TbB0Z4ZWxV3KBnbW2Phr26CoEC2mF8pSt4f+mZY3vAuK1VRpoViHqoMdMnkoAwX2sqfFOVDKnrb+ediImJ51SlTTIjgOggMBdwjhHdl19gYqznipEn30Gi/B6SU1JCNuaw8XDXzPB3Zmgaa9nhvsIVHza5bS9/U2lg6xaa5pmwIVvhUSwnC7kn0W1fHQ8bMvHMP0KecEwGqpHpTGezjBK+c/iyGFXR4F34SxCmH5pEeKtXLL2vy7l+X49yzN0gmDuuiiDz1w6KUu4aAbt2+6i+7wYtlgul46gN2EZtP7JH3BNzm+/rE+yX6+UteybCpCd5ijWlQ3V353Y4btTQkGVpS5xWBmbB/oximtt1yMCYslLnHE8U7hYf8nsb661zxdQdZZrsJ3/OdoMKv66SGXaede9LavLDd6qa+sB6dbjqP0Jun2lXVH+4iQq/Co7oUpuGVwhnP/A741DK4FvjUA32i2vDRKqPIZHEHwjHjpQvcmZ6v3Wh/WpkzeFcllj1byVy854aWGzZ9eRg5auZsQ6fxYKJJHs24MXfI8+O4ecWstLt41tG444mJTQBfk8jTPKcuXxMrtVERIPnoA+i/zWtfuSNmk52bMbViclR8u6DLiB5XLu72tMG4sryTOyRZOvIIyyuUfUEZOETG90a/5phVE76tcnoW4M3mUqZeJm3UuKwZCytoWKg3Le//4mUG3WeZtQN06zNvb1K3TvL2Obivdp4fANdytz8Ob9DzMMxbPD57LdK4OE/TTypxVPtp8zjwrBuxH7BEbO9Bue4FdQLttldglak+D1X12L86MShMJDiH4XHaXUZrgcIJFXaFEcBNY1YUfd+JkjZq/3adtxXHFFr0GcSmZclxUkArprGttZtwRRXWY0fbEDmQuByoscKA5xL2HznUS54sgbCIO7/dg7rxyRwOwBruNYAKV1aZnjVER/0Qc65GWV5/aBYvhgSIkz8D/j8o0ynjpfiw4MZp+Ta++XG/ipYlO5s/MYIIO3nDH8NlYQrQ5rNyJl/JUvs3idXwHDYC1o+h14qVGRyaXdEWKpkI2iz0bjQJfVxUCFabye2pYCPV+PaFamgiijGzGS9XAZA3GS8vpbxqNqQKNp3A8Pr5u8TBTKahusRtKQXWLsyOO2TgZTCRgWVMSMmuKZKsviwz9dbxQse5kWUW3Ib/B1YbDZpVeVaVJYvaqlPk97oCxgweKzytGGTsmpm7GGDt4xo7IH3Z3IlIQi4o3f9RpygUYhH7v6DLk/t3qWPLKMQRit+1WIBbcIn+f1UVQU0ewxXDTo2t1urZP1xp07ZACHd5N8S6TbXfihSUJZfWjg5vldw04yjomgo3iVuznxKASd8ZCynfxi/rOdiPPKRFssd4SxL4rEAp0J7ij+ENqAiAfTumH0YclPKcjGU3tFAK5HA2ciRY35aeMPHy9siKq0xYZ/NwcDrrOpe7KP9VZx0vih8Bh8TZ3uMjwvxcdQ1jKX5+yRBLBvMKgN+IIh0tEMLcw6C6ZBRsozW3ZIUV9rzI2fai03PdqA1UYHSgCuULLKwy4CzVvMk+saEKL/9BMv4UrALWFfzhGv+HyUOLZndg0Ax2glNd+2bS5CvN/wBwHTczxjXup5SrXb67uMebNnZ/aTZVefyaa0bf3GPFd45yAHDZ3j86K78IqtEXvonyJ57DyKG+p8Z5v5b10Hb0Fjix0dd23BhHHVEyOiL2UMJS+EgbuCk8pj/90kXgOQF6aWn6T1aBwmdUZZVb/pzKXX1xmfNd9aKU2WhQXcOTPQDdUhupX4jF2uvpAu5f/dIDskY0vfGbMMd1ss9MIlGYqMXNRvl1oOZFnu7hrVxOuX4nOh9ACfqfzG+OdVBt8u5abn1SnPlmd+mQ5f1Ld+xPa3evmKt13cbqmK3pjvKrAFh1VLu880Qn3qtHBrGPltrgvCDSxDcwzNmIfsDx8KQ/TTnF6QhY9fWToBPirWHTtl9Dz6BVx6YxemvRNcNLD790yIZv+LO6XfRZaDt32R64UvIlCpMh1DSJyrbIPmmltdFDLe+vkucxABb3211reR8XZmoArGi0PpXbU+XtwPszbaCjt9CbQLXJ4U71oI40YYdnvN+mdFPfnXkxvpbj/p7p3Wvfv0z22TxBJ8+XdP8b+mTLO6AXay56j/X0CpllchqGHWhUAPVrmWwkIjwZNiA5M
*/