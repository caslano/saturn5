/*
 *          Copyright Andrey Semashev 2007 - 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */

/*!
 * \file   explicit_operator_bool.hpp
 * \author Andrey Semashev
 * \date   08.03.2009
 *
 * This header defines a compatibility macro that implements an unspecified
 * \c bool operator idiom, which is superseded with explicit conversion operators in
 * C++11.
 */

#ifndef BOOST_CORE_EXPLICIT_OPERATOR_BOOL_HPP
#define BOOST_CORE_EXPLICIT_OPERATOR_BOOL_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

/*!
 * \brief The macro defines an explicit operator of conversion to \c bool
 *
 * The macro should be used inside the definition of a class that has to
 * support the conversion. The class should also implement <tt>operator!</tt>,
 * in terms of which the conversion operator will be implemented.
 */
#define BOOST_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE explicit operator bool () const\
    {\
        return !this->operator! ();\
    }

/*!
 * \brief The macro defines a noexcept explicit operator of conversion to \c bool
 *
 * The macro should be used inside the definition of a class that has to
 * support the conversion. The class should also implement <tt>operator!</tt>,
 * in terms of which the conversion operator will be implemented.
 */
#define BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()\
    BOOST_FORCEINLINE explicit operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#if !BOOST_WORKAROUND(BOOST_GCC, < 40700)

/*!
 * \brief The macro defines a constexpr explicit operator of conversion to \c bool
 *
 * The macro should be used inside the definition of a class that has to
 * support the conversion. The class should also implement <tt>operator!</tt>,
 * in terms of which the conversion operator will be implemented.
 */
#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE BOOST_CONSTEXPR explicit operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#else

#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL() BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

#endif

#else // !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

#if (defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)) && !defined(BOOST_NO_COMPILER_CONFIG)
// Sun C++ 5.3 can't handle the safe_bool idiom, so don't use it
#define BOOST_NO_UNSPECIFIED_BOOL
#endif // (defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)) && !defined(BOOST_NO_COMPILER_CONFIG)

#if !defined(BOOST_NO_UNSPECIFIED_BOOL)

namespace boost {

namespace detail {

#if !defined(_MSC_VER) && !defined(__IBMCPP__)

    struct unspecified_bool
    {
        // NOTE TO THE USER: If you see this in error messages then you tried
        // to apply an unsupported operator on the object that supports
        // explicit conversion to bool.
        struct OPERATORS_NOT_ALLOWED;
        static void true_value(OPERATORS_NOT_ALLOWED*) {}
    };
    typedef void (*unspecified_bool_type)(unspecified_bool::OPERATORS_NOT_ALLOWED*);

#else

    // MSVC and VACPP are too eager to convert pointer to function to void* even though they shouldn't
    struct unspecified_bool
    {
        // NOTE TO THE USER: If you see this in error messages then you tried
        // to apply an unsupported operator on the object that supports
        // explicit conversion to bool.
        struct OPERATORS_NOT_ALLOWED;
        void true_value(OPERATORS_NOT_ALLOWED*) {}
    };
    typedef void (unspecified_bool::*unspecified_bool_type)(unspecified_bool::OPERATORS_NOT_ALLOWED*);

#endif

} // namespace detail

} // namespace boost

#define BOOST_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE operator boost::detail::unspecified_bool_type () const\
    {\
        return (!this->operator! () ? &boost::detail::unspecified_bool::true_value : (boost::detail::unspecified_bool_type)0);\
    }

#define BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()\
    BOOST_FORCEINLINE operator boost::detail::unspecified_bool_type () const BOOST_NOEXCEPT\
    {\
        return (!this->operator! () ? &boost::detail::unspecified_bool::true_value : (boost::detail::unspecified_bool_type)0);\
    }

#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE BOOST_CONSTEXPR operator boost::detail::unspecified_bool_type () const BOOST_NOEXCEPT\
    {\
        return (!this->operator! () ? &boost::detail::unspecified_bool::true_value : (boost::detail::unspecified_bool_type)0);\
    }

#else // !defined(BOOST_NO_UNSPECIFIED_BOOL)

#define BOOST_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE operator bool () const\
    {\
        return !this->operator! ();\
    }

#define BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()\
    BOOST_FORCEINLINE operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#define BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()\
    BOOST_FORCEINLINE BOOST_CONSTEXPR operator bool () const BOOST_NOEXCEPT\
    {\
        return !this->operator! ();\
    }

#endif // !defined(BOOST_NO_UNSPECIFIED_BOOL)

#endif // !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)

#endif // BOOST_CORE_EXPLICIT_OPERATOR_BOOL_HPP

/* explicit_operator_bool.hpp
IRlzMGWH0waG6EOTgmQZYzJlwkKDFpUBxg4c/DtNej5mBjXIXmZNUDnFMahaA3VC9CUuyMHtAA3TmgBpFzS5cRq2vJNCkHSHG4sJVAJxshJjGjh1IJcv+SKYlHGmPCNKH5UihrMVh15GOmxBS6S7/97y97WCKKyROQzPGRCqGrUUsEgqjp91gsujh1TxiIjzJrNsOXG/ZDSGFuSdDL/g7x1G5ZSFrCTr8odIS6ofVShp4pgvxxpYTgmOqfSkpK1htkHKJZvgvGp7lDsp3MHkKSHp/jun6Bx5Fu3sUWXKLL9et2Shx95QCo0J4pGmiT4Jwg5ti+58rkAN2eaJfEnhbk0Ze5SoJR+xHt/3ZPRhjPbIm0RQPzlxudyuvG2087WOMHx4KXS0XimqQVKKILabqNOX9kapU9UqL6tJyDBYWHYZyynSda2xF214RTmvbLkadRCmgb7atlrO/+HeFLXifNh24vB0ul7VhByivB9v8mH3S1qzmG87/K9GgK3gy/W63rgxh6v3w3qflMeT/4qm9748Ea918c6yjH1Wln7WOuppVXhXoIZkbUFzzvGjqHxhwf3C8tgfcK2qQSzvUadbVBNlJUc5GveRP0zXb/FjNTHL6Gz9cq4LV67YgNc+NvfquZ14EtYS6j4nNJTN+eHeL2bej2sNuVmcM/WVI9gatttYYIfyOV/O+74c5fQlzfZfnF49fpKs6y5e0xsH1oEz3LPLaGvtChbXyzhPoV9XHn9SwybBimbMUhm9v6fQt4tufcxva4IDCxlXyx6PYU/dgavBM571WGSwmqdM5Jyc4ywjx7/joSjkl40hzSsWOKgGmM36wdGsuH+YGPtItA6W1umgrziH8BANfSPh3nT3By/h3bX+AYbR/xE5gA99X34BYIO4c+psOp8Ol9puqp+Broc6PO4vQpnPwQPbQGx/n4HN/2BsAbVD3oB1zDigD9mGWw99x60KOkx57DG88cg+0qfawuF/5ioaQmGHKgedfFVXK70FRUiu2h2azrX8SxiWHyMbsivpTJMeve5ci5Ltuuxgxb7zb9Jl/0GJ2sFjDLmie7XMHpjaxvXeabbZMobuXtpg2qN9uw3hH36pR/pyh/xZCfKP3denfluD/KG9yPOv3i+35jLX+ljfGFi2MKoqpDg22uAWjyPr9M/ap494yGU1zvaP/ff4GFoDcgaSkjApUc3HNfSSObMmtErZmUP2aZKTP/XeyRY+aGe6TduwQ8THpGktieV6ngE4tVp+Z7Z5RRiuDMhuV8+Jowd4GynJx77AmBvvLFuXPyZE/Y9Dv1bME69yJmTe3xA/BPx9c8pafOk9auRI49314fx46r/4ZHByW3Jd6lwy9r+JXJYcd5H4UXN+37gkNbySpx1PlpooSQKih2r3k7WPyqkjNQHpgomvzdORymNXROvUtHHRedHRhfsDh1fOZ0xKimzECBmpxzHE0UTalIPkgeXAwNS088DBDlm+BGdFDwCFkpAUTcXjZHb+Svd3OkES/2Gkj8aOazrIxJYpMEZWXqwz7kIyVt1EcFvBE3dSLGItH4klqcnwvwmsVyLcRXkvSfILIt4S4PssCfDR8g6UcNUJs0WIKZ1xFeGTvkmJRYn1HirSGko2xcwWH9OuMUxUya1U2Sjpe4m8Y4mwoc7cpcXu3IVe8bkYZuY5rm71W/wnzvLbzm8/j933b3AYHJY3cXQdCtjO83HhcFj8RNf7CcWNYmenx7GY3uNFxyP6qX6fIVRkctk+JgUFjtIKj8uWpOoyfV0tNmOzd9ZmKirzucos7389V6f6/sNBVpwYUNSsrYjPY10WMktH7JiQzJp78+vLAAIs/dM+j0Padt+Q2SE8Ms6vvapVaKvYVDIbKonid+bkKMZmd2KkJnqlK+diMeAqmo5SJyGaCEwrXqU68eRHOeYLaVhqYLFOtUoV7GqNGxaELclyO8Lm93iiza+jaLWkxYoe3vP4/SmbteBXibtnMYeHhzcuMVPDHYJBSn7v23mY1009PVUPeRnLJHzLpiriVY4GTdHshxMBIFf/MTHtm+xfZ95/k/J9ZtleZp7kKaHPIi1P/zdLmpvjFyk6lLk6qhzTr8Gx1O3B5Vh6iy1A7or1nm8HaLm7sTK8BrTYw9wbXb4G9LP6qHJS3owvl4g03KVj0r3t11V98jyZOyl5xF6khUbbZ/vfoql/+9cLt1pNj/OKbvVajW77T7n7XvOB+etu+/0P+I+f8lUwPO/Xozjeztf6kTzPO7w87/d089y30dSq/o/VVn2+v+GnvVtPx2Opbr/vu3u3/sbjpXW//3esv89jbfvrzxL35+738A8/nsftPn+///ld/9fFnO3vx2A/7vsd/e/Pwni+j9fTunm+//3J/e/b5VW/39JP/p7fK7t8AHnefhcL4I99+u9v77d8KwCn49sv5OerhaXmalNF6A0unbVmW0ep/uuNhiWNbhcKdkdPT9pD2okGq0nsBH291SAXUHTsw8MJi4dZK419YTaRhp0IUWJMTF7svYcwz422ucxgnAEYA3a16dnPS0Et4MtzGsCVOqoB9hhqUzodvYkgJ81/LRtNabo2vENq8fQm4Ad83INJmbUrll7BZJSxhDVhnRjQpEbhSyGIuS8eSq+uwNuIflF40eKoyok1pDkqUpLnYxB4YvDw0qRVRvNRnZJUSkiEwrFbgzJUKchRtCoGGE5LEPxzyOkmykMxihso6kopKsqJRUi9BDKwkmYjCgrzWjSjw8QarjJl+KPhpV4mMFJCXj2Qv+egP5KzCrJe2qzqKrZTy+CU38mSXk3kK+h2i8cYTSTZUsVWUoajqUNY6k1PHExVZVlVOKrZqOwtWpESujNJBN6LMeWbwhPJ/T64125AvvcVMbqpRYr3FbA67r0oUZeRJYUaXkrDofNWvGWVSFV0WQrWlbu4sMt0LKWBPG47q2sZTgxVb00HVA9TAXmqmp6opbo6Q1XJhspMKDYNLKrCRCu4NcTH5cW93PXq8nXKj++XhyH/xFmnSZxw1ZDzIo2cepLd1i1986t+5FTtITNk2GiSh5mCiLp1qVidmKzyBlSEPsgj7E13x2vL8lcUSF3Om93MSfsif2rX1rkqbBU0g91mkOrHnvcCZE+EDDgYHA9J2DwfSNhgfnQMWBigMCSZoAmZceia8fI7U9tc1z9Nh0VR/J5tiS4CuGEmQMXk8f5DCI0l4gf8FYttwvvEiIXw2m4iPUnevEAYyQeZfx6PVGDxbNrK89Qm6wSFTsL6HpMa/vEZBBr+WMmR/OqwjOlHqSMCVy0SVgyOmj1aNvi0RoRGy0BkPXhDNltPjZwaaVscYCJBCZV+gTfnNHZ5zgDIhk4BAtxXIoDGgHkCngXDuBPVC/DVxDPAH7QFjoODbBh2gAf6DHQPaA9YC8wdcDPAbgD1APvraWF4YGyA2ICwA54HrAxIG3A0gFoAoAPFBkAOBVAiAAwLsDLgp0GpAp0KUCgAowJ8CLAxoJ7A/3ane4C+BmEDpBVgRQAAA4bhyAj2Ab7663qBQgLfBSgTQCUE+Pdh9ifOAbaAbYCwAp0MKBIAW0yJaQ14EQClmmk/T4ZxYUwAxMUG9Yp7ygvdmD6RsOOi8yY/hsO2uaH2FPi+77OKpuwme4uui9n7NzpdP73b6T/evbX5p/e0Ht5du091+PZrb/p53GYbrW+zOfcvwtH1O9t+i9YDfdlh/IoYereEsfFuO/3D8ejlum/a+qjzrbMbjS8yCv03H3b69nadXmy+X7L5mev3DHm8Xz3VfT6vP2mPPvqYrhfwwG+1+XV8l3jc9qS9y/G990mf+9r44bMz+2024+Tbb7Q7jV6/6b8FNt5Mhq9qzeFly+K71OZ+HJ5sbeMt4ukZy/sfZQft4fhepr9qUc+23Qze157lcareTVZZk9mfMLtNXWxeM2bU4d7NhvMQd/Isr74v4tT9nP5Fd99s8lw8NsPd4r1YnHZZWuPtlNPfuL1lzVvzHmrdTm9G09+s5XW7Xy5O68di/Fzevb8Lg5348DyceP5rvG4S7n+7+D57maz34H96ipoUKWt67wyLpDfZ1fgdVMaXn/J0XSuiHqO9aWfZ0sC+catpeZ6Ihi87QbXr7zLbP2V99XlW8xld6X5wU3nxOM86p/429/24CSC23rt5zGDytojP7+VW6qq0uujY1bfx/uyP6H65q4ii0bfMImEKBJEVMxvJ5E6CoUBKIEkAt3BPCgMQzHLBGyFhkXQn35Fdwv1IDF+0sjnEyK7Yq7nq4vbxI2o4mojZg+GCqbODieBB0aeJjqkfXLnvlmGSwykW40/r7ld+fekG7vocfxk/2FV2na0c53S93O5SZZ+jv/HZznP9mlEG7/e3mIOH+Wy5WsKV9n+aI4b/quzqtrpJVu1/u3ul/2qbd9mKTM//L0P34fJ7M16N3/VFbU687Ma1/tpm09fhN3NO930V+vN39eGCF96Lnbana8h0c+tol72Nuvvs7WUB6RF+SXXcbfoz0XKWfXFe+Oz3Ow9eDOeDl7NX/NW/9fOq8B3sVdz/dsPLxfxK/vfhY8ZZX5Kb5yvZGPzW90qc+EyP+8j/jJ7XnpO/1zr3N9rfWfefX5UxzbM+Pu/PyJTfUkt5uT9vid9TWuZaTY6v6sJrm17zTn3eo+hr9+MP4WvGaZxvPY2f4bnIbEvheJqq/NymZ8nRZhTwCXs/l8vHySX2TYvOuue3bmzxXg7lzpnXisdzWGq1+1fBomCbuJs4m/iLWJuYmxib2Itom6ibKJvoi0ibiJsIm8iLcJuwmzCb8ItQm5CbEJvQi2CboJsgm+CLQJuAmwCbwAf5TvKu5FmJ/SLrRaaLzAfpTpKeZHmJ/CLpRaKLxAfxTuKuhHkJ/SLqRaSLyAfhToKeBHkJ/CLoRaCLwHf9VWEzMso5lF66dXOCOVrbeg5f/ShxC9eMwGPiYaMBGstj66nIh0ZQyYOFea1QY9HKqYDKiasoqI9QdXdwH/JBaMB8HNgH6+Mrhti0JN6X/ak94HEv/kMfYvxD3ubE3phrg4/DK8UtIdEJBWK/qEMHV9ESY3BhnFr0/OmlYcSnp0+oy88JWFE5T7tp9dwpWDD4c0zq1eBxmEY+H1MMR8GS7YWN65SMmcN8yt4UsKZ0h7jRe+pTB0s0pC99C3Hgx+KYcLRd9lpUlsexw4gNJSra8/GzyKOrRg+Q7YM7tFMEYUu3rvYxSiiHEDSvgjtHZaT2capxZ4gF4Huja+wEvONdmuix8wfPia4qTf5/4uXmPYl6kRfC9fuhL7QLG45fy8UeIg0QdW5+/aOmL5wddDHTAZImwHWoMlOTjiuASwdV4HpTVYdPJ6gxYajYMaibTsV2wbMVa6tqumJioNrBv+pA5unJqo1i3UrunVwrd+4OXMuxq+ew6cmaxbrV1SsrGCmeSxOli3gsnb5iarHWxOmpJX5jUa7WC2LGrW2K45BEbHDGTpxdJtb/bEJvUvtCv+8ZZdQkzEycbDeE7AYMnYcuT08xT8dSgU/+w7pUYTsTPevkUlQon5oRvd+58PnU+8IYeUv+l2qlRHWMqUEEG7O6JZV/NxH/35F81wHPoFXhXPixPNNPu0bbfIZI0spJhGHxrb0Wz39vCA/aWrl9ck8B49Qt75tbtDchL+TWJhPwixogreDLPZZPReFu59k0JESH2A+Pj8XHbprbbS96u8yJVrOB9bJP+CrypRDpc9JR37+/v0FGAADBf0L+hP4J+xP+J+JP5J+oP9F/Yv7E/on7E/8n4U/in6Q/yX9S/qT+SfuT/ifjT+afrD/Zf3L+5P7J+5P/p+BP4Z+iP8V/Sv6U/in7U/6n4k/ln6o/1X9q/tT+qftT/6fhT+Ofpj/Nf1r+tP5p+9P+p+NP55+uP91/ev70/un70/9n4M/gn6E/w39G/oz+Gfsz/mfiz39/Jv9M/Zn+M/Nn9s/cn/k/C38W/yz9Wf6z8mf1z9qf9T8bfzb/bP3Z/rPzZ/fP3p/9Pwd/Dv8c/Tn+c/Ln9M/Zn/M/F38u/1z9uf7z78/Nn9s/d3/u/zz8efzz9Of5z8uf1z9vf97/fPz5/PP15/vPzx8A47/4L/cyQ6irvdkfMbO4S8psGW8cp7Y6+1cx1v0bNMkTwXOVLWtXxclgaW7a8PbyLfqDwaSZQhmRo1dWi3ixZcyB89aQ7qYqt2HmMH1+xBpd+2oaTHpVojtUpqQiL9IPeSCe5WFCe7alUV2+cl5McJiNOmWYox1cD8g+mhkFtan8Wl47dOJ+OLGL4pPJuhkUC/RisbU+q2NS5NntEvksLAztslLITGEU9JMM1JNPLeghu5T2sjbwsd93PcJoSfT5zBI5Z0bkbRSfj11kK4MkTypiphzRPVBhBB/LQYF06WCSJhnbSWTZ/MLPTTaBvi1C8yVLdkDyQykpHIrktvy+ckaB5UtGTa1bCe+0p+8i2NLzKUoAmi4j10nTgYhh/9lSUerywFoRcNDMwlXkde8cy6Q/FS7vltgIoe+tDCWlev431CetGWkqM3ZUWs9AckEsbp09yqj5i4C/op6JzElbTcAODSXFqLKQ7QOTi2qxUDVpxdEEVpgLHZkk6h+hsNBR49BeO5XEIacFyt4D4CX2kvHfUYtTR0CqazVVJ3bY4GMgdrn/x2elnSlXe2I4k+0LhxYvxh4au5BXRGEkgeS7nDQ7Oh45/Ikx1sPkidMePhRM8cfOyLBx4dDOFmUzxXiG0cfyf794RiWlhN8n974evMnvLJ74IO9B8x62V6nJJ/M6aGTq1kl+R0uKGjDm6i4YUzNvduLs/rsFvfbZnrnHvmaJKRJfKHXEkUycb+7/TECXkMj4mxHyK0Lk09s0uTQlpoJyppI5+pAfqXXk4H2/sukFlap04EKRa5LSZ76rY08Vu681t2jIuCCo13uceUtQRoL42iPH12oLx0RaWa/VO1i08o69J+hotTG5+U5sobJOgz03j0WvLST3yuJcshpRlUOyderMmSWFTaZviz/GabY48cxq0FL+gUXrIBTRcsFszPR3nKqcVk+lSds490LGOB51r2xgW8ldx2CQ8jvaCQdda24/XTBIXBZuhHyGk7CtYvlVQM8x+TTtP+2V4rDD1FIXAbZBUVnat2eeB/t/AaZvQ7dWtELXxiB4vTV7MB+Wm7lFIymLbIUz9Rl/YYzqFJ4N/mdJzMfLqBfjZVc+kQVE8GUxZ4u+l2ir/MIRKvcr8sil81Q1t72yaUmtkWPvxmEhj/VegVpgISGEnUsrr8LEfhbbxJhJ8y6SV3PDwNthbW8f4yzRBSZEJCwnXK2feowZ8Yk1ihwWZqmEFT4urkQjt4d2acuExpQ7L/BKEo+dw3IWmhs4g3m0JaEWUw9pGoJRtC3nk4N9C3nyA8sYNk40dyBP3JhkegTH6yt3eKab7Hk44hYWgTDlbuR3hUpVdQWD2royhpVrqKsrGzrboaSOLWiFfSHhtJ4fbi16I12ZgtcsTq8fy0TpXUY97DxWBVdObRm+sB/zYOdlXR/e/SL1YPXb7YVttbZioT75XK9jqmGs43oV5UoydUKsTjrvzmGzjXNH3wlE/JyaDiYEowOuOLtw3eQxwctlETtnuCWjFxWX+WiYY4KTwPJe7Cs5Ll0RC0myHc7yuKTbMq6B9/rfuI+MJg+Uk3gNEUvK0bivzC5XDIHo3Hz7lDEkIeI3cmRcPCjmmQkPodDwAoUmK6F0fJomMqM/WroKIlTU0Tcm0fydl0n33H/5mDyJDVxltGD5kavGm75w4LXECYAUwSFSS2ETRnlzF/JvlNFCPmwRiTjG3YbYMg9ffJo0fp6Eycsni9NSDJyRuCEX70RiQjUYR5+HUwZL5Yxjv27YRPBje4F0BRA1wWHhwK3OKVCeeIaAvVimnn2hX3uxQnn1Kb/GNZRzS0Jzi1x9TlJTJSMCt5Lp0CtROH1BJoxLWlEBLqb/Yk+l85ZH19ZO/B19nswtiX1QpNEfdH+dVHB9yUNupZK3Rf0e0Eifl1ne2WP9WnxpRWdVZAfp/dyLtXKzJjW0srRkX2m+ZoLyBX50/JLOwdjydybQDJbpjsnj0Ix36UxEbSC1J6M0Ia2UwiqEhtWlqfc5XW1Atf+rWqdqy6o1XLGh3dsqNr96j7KkrTZ+rgm0NYi9Zlsd0VoXMzs2T5f5ghXk5kc3MXbz0Acvcifnx25Lvd0u5/3RrcGWx+m9dnMD3xr7+tLliFekeyWOSukqye5IcP7PV8c1VFT6kq45+er3U5yrDjhl2uy6Hrs+YK4XEKtb0BOeeNy//a57wheXRVnwzDfFXlZBL4La7hvZbfMfZC/xhPFD1IuZX9jIf/Kg4+NOXOS9F/PdNnIbgMQC0YP5hd+6+Bbrcdmt10Q36njzDfr4ESW+od5L+ERvSx3kHBUlspwUR/UHHy+C75eeesi7twZTPV6zhDPfzu9u9SkcOqjh8pHDS0Z3KlxPqMHQjm9lGDqyxhRg+Vjh+ujhZ2MHno5vso5vhxw9CbPLzHj1850ZSnBfjJH5wk13Ol32UPm3Rfj/lL3ueGG9ERXe4sJsfwvTTGnnm+QDfjHfnl4XXm+J4NdIJbo/O7Zf6w8/vttZr6c1YT9XJLfzFxu8BKfi9v2O4lttsAt+YWG9YRRiFeXMb955/ht3Ot+WYY8Hgyq+QX/0fueVBuV/VQbe1Tr5UoTl/26BcpfmQM+NXnTmeuCuHl4blfnpmfz3RQVn5ZnLGkAcuskgx5baqDB1CvgD5jMzdOx5xl/Ai5Z8xusU2WNOn+h+ieRp7OhJT7/WxJ5GXjYz4Hqaz1ID7IC+7y6q1fbbz2LDvm84UEbayCMOo+X2hpUCzFuuU28aP73UpCp6wjgPnvcs3ToNRkG50iQ6qlUmpAkOAByQSarVhrA2l265UdyxC+ZDWwe0nx7At98NmO3oz7xvPJ8L4Md9kx2Jf2epWaInW5HuLK7DextTu3b6jPF7ZYJlZX1Jq/XyMddis+lG612hP+Uy4A+XRdabxhtebeVb88Uv9t9c5UrT2RWRh3hw2j9biWvwoCpYC/3itE5AdRbLjdjsFhkmqw3pgJhYLTfqAkTLNSA+kSz0t94OfVgM4L4WzJ4A3oFuQGaAeCB/NM/fiE+mgE7RKTnAPegGoFv2SVfJTnKl8ZOOLnDiN1d4C01ggea+nFhWi3XZK6JP4+LX3sU=
*/