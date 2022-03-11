/* Boost interval/utility.hpp template interface file
 *
 * Copyright 2013 Cromwell D. Enage
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_UTILITY_FWD_HPP
#define BOOST_NUMERIC_INTERVAL_UTILITY_FWD_HPP

#include <boost/config.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <utility>

/*
 * Interface of simple functions
 */

namespace boost { namespace numeric {

    /*
     * Utility Functions
     */

    template<class T, class Policies>
    const T& lower(const interval<T,Policies>& x);

    template<class T, class Policies>
    const T& upper(const interval<T,Policies>& x);

    template<class T, class Policies>
    T checked_lower(const interval<T,Policies>& x);

    template<class T, class Policies>
    T width(const interval<T,Policies>& x);

    template<class T, class Policies>
    T median(const interval<T,Policies>& x);

    template<class T, class Policies>
    interval<T,Policies> widen(const interval<T,Policies>& x, const T& v);

    /*
     * Set-like operations
     */

    template <class T, class Policies>
    bool empty(const interval<T,Policies>& x);

    template <class T, class Policies>
    bool zero_in(const interval<T,Policies>& x);

    template <class T, class Policies>
    bool in_zero(const interval<T,Policies>& x);  // DEPRECATED

    template <class T, class Policies>
    bool in(const T& x, const interval<T,Policies>& y);

    template <class T, class Policies>
    bool
        subset(
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies1, class Policies2>
    bool
        proper_subset(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies1, class Policies2>
    bool
        overlap(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies>
    bool singleton(const interval<T, Policies>& x);

    template <class T, class Policies1, class Policies2>
    bool
        equal(
            const interval<T,Policies1>& x
          , const interval<T,Policies2>& y
        );

    template <class T, class Policies>
    interval<T, Policies>
        intersect(
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T, Policies>
        hull(const interval<T,Policies>& x, const interval<T,Policies>& y);

    template <class T, class Policies>
    interval<T, Policies>
        hull(const interval<T,Policies>& x, const T& y);

    template <class T, class Policies>
    interval<T, Policies>
        hull(const T& x, const interval<T,Policies>& y);

    template <class T>
    interval<T> hull(const T& x, const T& y);

    template <class T, class Policies>
    std::pair<interval<T,Policies>,interval<T,Policies> >
        bisect(const interval<T,Policies>& x);

    /*
     * Elementary functions
     */

    template <class T, class Policies>
    T norm(const interval<T,Policies>& x);

    template <class T, class Policies>
    interval<T,Policies> abs(const interval<T,Policies>& x);

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const T& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        max BOOST_PREVENT_MACRO_SUBSTITUTION (
            const T& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const interval<T,Policies>& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const interval<T,Policies>& x
          , const T& y
        );

    template <class T, class Policies>
    interval<T,Policies>
        min BOOST_PREVENT_MACRO_SUBSTITUTION (
            const T& x
          , const interval<T,Policies>& y
        );
}} // namespace boost::numeric

#endif  // include guard


/* utility_fwd.hpp
ftU3I2OCwLSFSbUtueTexO2yePqJpzsser/8s+JYqcprhhd01WkhFVdxYjFyhv4/Y9fLI/0lKBUq2WsJRfVqyJ7nkRmOB2StdrHL6JsV0f/tpWP5xm4qau7eBYqvTGsMnI4H1Af71AMv6HMcJ+zBcCDsjKreH0ii28ftiXPlKvnVHJzvAFQgRY9iyz8Ztz/qpKhNPm8Q2R+JJ5Oyp9BSHv5e+URmzYJSB1F8Gr+OdqPvBuv1xt7ndXWDsQ/UpokQU7bUczmxynMSSRPWMnCYMWelnXZMFsqUJc1HPAaAH0rVzHG61SlsL9fG7qhVJDzpfJdNrv9wL7BGOJJGBZzx7Xa2im+k/+73DUE9Pw6ozl0jQhtl6bONxlHWAOQxXKOHQBgsAij/R3m9gwEq6wBUWzOjdCJ3qtKq5p5MTHJBLhp6+gMccHA1eMCdGNDBQsNV7N+UWxhOUTIKsEdEnrLOT6d+FRvO8+twmHjyv3mQPb9mBrPSMYPNI4o5nOi/SlUQfjwrBAQIZz2A8G0YNYa6w+i9MQ6QZqAIGKXiGEln5YlvB0Q8oh7JX1vC7VGXCR+IaBb0L1vOE8VYFxo2vyFguv9sSDidLfLeCt30D+AlkmkFpazU5YkBCf8RzP/YiOIfG3HuACYUv78nBF20LHt1dnYGDfZkiIu8vCRUVFXhQVuX64xCVtt7DgafY3wB0Mf+Vr2orYGWPDMVMTEw21kA3FlAEj24Sv7Mfv9LAcCUPmawgjCctIDFnhHz8C/N32HTf+0lY5GExZzIK+F5jqwhQ7L3n+/g9z1M98Lg9qT9KhWxQo65Tc9xdcyyvO/6d2mFrQZkiH2pr2DMU0l+daVGP+09guWpGSnPP+KBr7teL5QDP9CIZNjPXoX+KW6/I084kQ3VD8h45BW6xWKlZvnjP7oqqAaBvEUSKd8+dg6b10ecXvDfmIhOYm1J+IKyVIQyH/qxLZK3wM9f7/P2tHBoft96XtPNJA01MMHkWvLNA+khASg3SrIYY2hzXxz3kHnL47+Yx+CcpsapKvr/TqBI+Hr04bqC3oIZdVz6QA2ScVGaGCf2R961dG2niE6Q2K78x3+nYmK/kSzr2i2NxPsXLfG2RiptT5lj3IY3Ic4tEJor9MKysqP/sVuDY8RVDqS4/vI28J52z+2Ljs4KSJTT0vE8rrUztzlK7B/pB92SMxS2SWqEFbM8RItO7m8l8GbZB7hin71xadSPFq8sMiTIwA830RtgWc5+wXdXJ2fnklbsl2rG55CSPupkTiAOpXuR27XI404AkxYzANkSLBIk3Z+ZecsSpAwbcTBxIyvliSZOPBUHI2LyUyHOwQ7OAXM5mC0hftNXSnrI9GImCX841AbTnibqA1VwJpl64hnwfiURHEett9W2gLBrjbo/XXJbBATq7mTKr6PvCm3I2XauZ24Uy2FxOjtD1jeQJp9zlJSU9p78/a7R08igIZvfZG+27PY4Ij3Twb4nlwu9vmdqNQJJQ3nPfz5NLGc97trIUyp0iKKW4vhVRFHFmssquhRZICin1Q6hDMz681Q+LWDRo8tKPyM3HyQMn+x5z+g9YiofJQ5yP4OLV81dotpnZP6oqohWKvBK8S2mxNhI/0xmxE+tY0P+uRDxTcWwUFrhO2X4qi3tjB78VpG1ahjeyZLfDbto1UEezewgqrFhJ7NPn7fOcp0xkfuU9SEcVN5R5BxmRVUKMbaJuPrj0dMyvrb2TL7M9yAsqniBXJvo33Z71R+wkokZNtUZ0GBfWDmzLP8SQrv8uaQBvGZALvrNxsOzmubkATn5Nm5OPkCDIYGIW9zQMszdU9+10JYIYLcRfXsHAy05DDR8d+c9/CuldCq4FwZ3HzY4k2Qabu5r7prS7kK7ndFu8o1UMitJ8p7Gk/c0hT5LlWSwpV91AREF6y5JQe/ntCi1I64Y/CLCJclKXbsbxKbyQzZJTFHQoUiVKri0PfBJBgjxuT1ScoVtPGWKYpxn+hjdkJ8X18tp7hstray0BwPJH/gbAXiQ4+to6Daqop8yx4LzixqIQBKUciYGunXzpxztybELaNGAZMs3kaXIFcSZGacKk5RjVhcKiuzcqBlrgB2lteII9Oxer4c78P2XSEMmRx/25ky9DWw2lINAlKPydKQP2QXCvvgT+9FY4xE2f3ml0BYjzcO9lEwoVR0rdtckuhFehlNmRv2SZP36eJCPPoFoB6PbQpaypLDanT0/X0RilNiyMvUq9WjBBWYf7X21VxLB8om8f7ze/0dkD8j+sI3WxEa3w4mm3sbEG2tQylqQcepWam9+/jbWX93p22mTyyZKI2FvcsXRh1C8e80t1kXZRCpIUTz6BPs0T0KAwhjX7uJq03LqqL3yvp/YB4Zkv4rinp6WjVC3QDSAEE74c4rYSn0JJ38266DpD9ocdiTqEWfARJOhy64OeW2uSj+4nO563DXI398C62QIM0eoHUcuhrCY3xzVNcTs27Nqro38M1fKXR9xZFNJS4iPKpn49zvSv/BqRO1BFmLYnpIT8KcUvhHYY/9ehV/zNRFRxLEve+iXOqXYXFYaXh0ZbSqB9MIo/4li2lO1RYg9PDShi2fwhTktLY3I8rw4Lnnph/Z7yWMbrOfoaCpbfPfN8cgeDJ0OzAAevoi/B9fHR+i8ODn7sKkXG+lL/72f81YUBYivz6kqnGPFrJCh9Gpli5IjFArb/M36Mf/rzKUnkBUgRvK1AVrQztrvGCb82pZE6cxQd1mCwCkyIWtP4KAvDXNKpUyRTiu8DhbgaGNUeMIOYS3BomoC8AoWtwygTnXcKpCNFAt+JSqd9auIo/oqnu4R2T4qWkETpErCfkISIwup4Gz+FAZW+J5PfEF/QrR2OuD0HOcf2WDbistWsXSdmzZ5Myuom7sFUPwDhHL8S71MebNNV8F8Ife/rO26Es3s7YGlgwDUs36H31iwYmskldcext781typaZvO9d8KnhIDWhiCf7Wx+cS9JiV2G9Z5e9kfXqvJ5MuzeUZ2qA8tTVdMeMF/ByM1lx4rTMkAIgQREZ85BWu0IhLf/guHEIdnbP5z0PM4UW8SSGq1a8jrAOQQ5ayrlYoEQ623es8W2q42dDmnAT/yGsw+sPWcy4UBbbcRM0fb4w6tb5R7S0KR1oJlVgGbF/21E1fMoKcaJd9P0b2r0W7zDJoYKAZD4teA4rba9sQdEO0JWel7X9Z9QW/7qItuxYfIjgkduW46EPa50r1ru2BtQNoQT3gsEWdMR1S1NTOa//YQkNeAjBnWMzM7y/Lzkl4pbTrxXX4zaA/K9z+3KZYn6Cr117sux1HmldDT4mI2JPEHqhSznG/tKKiWq176fJ9qNI+vI+m5fXABFKTTkmfXEVtxgWGZ93N94sqdONgmxj1l1KTkCV0yoq4WHx8NQiP/UOLTrviI3aFIVsgRJs/Eu9MjiSHC9mI6+Uk2vF1JUm3NirwKZYgIPC9PVuR66PMfB6XbYIcfUw5bm5T6g78GY0/Yq6rhwUc7Os4oQZxqpiNVywOc2A/3yRA5URNnCUpGy/SEDPZbCnjIp4+rNn2J1jFzuinFxxQvZgj3CWfWtoWM5lSX253zAOl2t0NUUlLSvEwkUXPTC0vKjOzs/J/TOJowzfVfcrIBlie9VnNiYA9r4TVU2kbnCY5GYknzbxu4jkq8reFRtMREH2VVVfGTcS23tVkkHsyMY5TSPnxEwMHBdx3svjB/bubZj3Nn3Czv7YBKEnxUYPKahOR4b/yuhAZAtiCdUEDO0VbCaQ8jCMS6/zo0/J4OFIG9PPe6Xu58OMjnws1T9vv7cTzybmw70Qz01OO61wFiOuchKooR3bK8uQtTAspuHYnWJil+fEiOvEsOnJPZMcA3jZizcf85HFeH++zpWtLxyMNAlcH0fQ8e1vlzfySKCRCOExkKtaXpC+D4INqc7OZFYYeKVQwz+0CJZfXdALk8Y4f1zgrLNmJ6737oh2VF0a0xvpOM8TpyIxfezy8ZRSkAfZJDbpJlPBbCg4/TRE+OGkyktAk3hh+HxaIb0+6GDXZJdFj/1M1Jeq6hdAXeg6kWsFdElLeWqfRFEwdaDjl7Xz8HVXsJUmypehq7//PcF+TQ1Sbl+8D2tkGVgEqy76J8Mm9GlM6xE4L6JY9nMXqx38/40M4vPj7Ek/w0VwDfBiaa58e0rvF8On/6xlMWx71vSOIc8klvESVtT87oFUjQQOh8RQM7F6QSNHa5lMfk/bKBQ5cjVKDYETpdcUb+2HFCx//Ic8dKf0DjLxMQcqa4eZjt8tsD3tWU4inqsETxQpVc9ppRB6ujP2IMjbtMUEA4teQADlTh+hYMRJ9YczvGpNilSEzS2lDJMx1F5WsPqIxOWbnWS2mMcHm6OcwfhluKkpWVDSI9o+myf91urxuvG236nEoE0rpxr+vFWZRrOX4Fycqim+ZOWwNZphFOY9YSKk64H6TOhAp2cwjsvtewIAWJJbxJkNZ6WhXXCn68HmULDA7wPWeejhOpyxqaLX1tScEKRXMl3IOwPlHHlnRRODG6ySkz27ZzA+rzohjZSfZ+I9XVgSWMdmLX06XkmS6lnFt41mIBdK+92GIRyqvgA7rlArEgBj33tFg/C904BDcp9GScCnjbAkDjBwWwqvLO8D37bNBD4UZ9UHWajN51ybGI3UBsyx7TqcubPEWHNXRXxbyFPtCH0rKyO69d0Oju/v4tnne3y1bwpfIlS1JSktMnMFtI4EnMJT7xdgXW5ReNuxeQK0P1NOp5vKFfnFmvfVAdHDdtKmTad2+w9HTedooCFLI9N3rCaoCc/ZXSbsLXFml0KWXBlVXzCiJ6+b300594P3RHesGn1mSzj5smbU9yh2PPaYFwVwAxu1umpuHzJiIDCj5k3kEt/yTKatbZiP0IHb9jclYKUCRkj3I6f4EARpWKd7nMwPyeeEz9FkX5ZCi9SyQocHXulpLebwNbDdBgddtOFgsjGw5jj7Wm3R/y6iLeh4NcbA/CxlOZNrTfsn//PqkrKyznvLT/095+5+Istzqa3dXzcilS+HTgqq96WhcfIW+uEUFWHPNQ9GNaHvhejs9zYQsiQg4C8aU/8youlHHSnht+acnrA2iabNeMSQZpU0bUHpi3C2CFUTRUKLyrEkCCUF/aDuFvg/fh7CfljW8IcaaLankXjlSETZCy3MQjRFP9JWrFXPtIZUuQbk94JjISFVoPKNILhNaj9zYi25NMVbjjfaRyfivTxxObht6W3yWfl/+wmBtkCSwxHe8seyKheQrG2XsgjepINyFyJN+qiHbWxkUit/oumhFGBKJCVeJbzLvdI0WDiLy9ToskvDlvLFtgCS8CdwDM4gLCikktKni/JBFtYvhk0Ww7vq4xIeT/Gli0mXoLf1jVWbixV2dX855OuDkTGNh3nUq4DYDIstTQontNcvm3EHvXjTPn4+8FBsFFcDLN5gm/Sa/A8IkEa7mQGhVA2pYdxfRn2BF+Je3SQjt+dE9wN0UEtlrHbO5Scg10erpNFqtFvFspN7gn3XjhLIdtDnNw5OUH4/w/oQ5R+0sVdFTjVfzDMWbwIGZS9bwZ6VAs3yL4NXlq8apzbvlW20HnQYP2VBUX3c94q6ZIQfjAo+Eq7bqrm0PFWiJO/1EjlY1lf0g3VFmBPiVddL3Mfyo6lg8VpAZbDuqS+GR74k8114yL18yYWRw7rejbjLMLQ+EgrMFZ+03v13O8uzhPclLqD2rJ1T+4Jn45mkgVvDCX5RbH835mdQkqIKcLs/Th0gmNDPv83IDcBvx+7CD0Nv+ocvTBvYBtBLdmGDhjFBD6uovjwT9iUiJAKsCMdLfoJM1y3VG8kNy+81F2N9KG9kKPs6W0vTmpKwrBjaGE9Y2lFmhL59CGSAu1pb6v57ihH7kjJfxEyZwumtkl/fdDIRluQAt2jxxeeav93lhZx9WrBgalonUhNcNxvJh2LRIWZVSTCvfTKe+dlwaUr6Nt0Mj55qzJ2PKywWgKy0D6ESSd3EtzsFtmo9Qgs/wkm8SUFa1rkDe1GyhmX4p4Yjawpbvwz2+1zueHlt3sH4zy4lzYB3dFDROfTg8NZi/68Gr8kBOYtP21O4ux148Rg9J9ckCU1qOOuUCvV1w1h9dNRH/8E6lY0gu9ZZjp2oc61y2Yqns5N0mRYubv28F3pmYCtS5Qi/ausfIGC31dKh6v8Yaa/J1Vd11YkjOvyyu0CafeF5G+1k5esOLHhvrIB+BR8GfAWKqP8jg6CRxiUrvNwEUxlotNN9whNI2lAUyKJu7vPTI2dvzmTQ7V/L/h8gFG/G72shDExe5Jolaq4X6Xc3yVl15MHlGfAZ9ONMi6Cwd8ibmtzvwRlFIz+Ou05qe6d0wWx7IXqWLi73pr9um1LtotuLaONHG20dRdO9EezehR6UMfNp8+8rE+hJMb79Bu0XFSMTdn9OYfhXVC+Olk9DY1gtFzDuKiZBxDF7XU6Ko5duwGP9bYyJLh11BghHN1GJmtSeXfc+iM1fGtIgxuWL4HmU+cIUZtFsfWX+glCdrvDTFiPNZlY+QvUvUBD3sHgYsvJTBrujQz2cvfTyV41eNk2cVc4e/d+RxmYkcFXVwBEwHWYo/P9/auD/7+/lrfpFWMPY1T7f1FscR9Wez9g94vWULFlyVyzkQtqD5LZA7h3+MrEpygnbyuF/FEmkmkkPyJWY4VoniYC2gRcWlaxMKqZShUJvwvaAAw4UwOLJ1OZ1qP9oHdKVPkbdXiiPp8HgmTE1B0hVT+FLy6Fo8PcN6U3Ogijiaj2D14GZyZ9yGl4KMZU7yRgA1bbECEFIX68NJZ+VOx6qW0h783T+rAY7/rFj9qD+nG76nkS5L25W2r7lD1mOPDCqbcXR26hTHrtMJATE27LedtK/uC8JSKgWEUsUHxFwmQ/XW+IaxnEZrsRWyCeveJAPCwX7697OHh4T1E5/Zt55+hYm7ozXh9/iu+REEOxfPilB5DxKC/mJPluO7ZiyM5Zcn/V/cz+tygzGl5T1qo61JMZu6W3dzz1BZxB2li1gdxctd5/HvdByheg/apv+8NLbo3095qrp9eyyfKf7jT+LjA9Pg5LGofIxt69cBh+ulm3AsE0uRRAybAj7X8kYUKXv/R5D0nEVESdofS/MCqFTiXka1EEH58TUXUqEekp9LPtpI2GkBtdHF3TeP59QhZlA7P5lcOqvlRUMeL8yiCQa5bhUk1cbFVAnlgf2LfuLDaIzsjWbF4hlsi7sUCTgX1L2mW0Y6o/BCDYj2REBM/BqLX2XbUjUO9fPLCGvK62r+wvL9M7xGTG5VGNOm3JH155oO1o3wamFKVy2r/9VBCF3tdTp5pp0x5Rcdd7l4znbtnizzRCN3f4ceYndztmRpam7ZIZCp/FV4giRbfcCQG93PdFny9Mjnwo8xq1O4Re/hn2JQ2SHtygncVXYdCdG4yZ48rH6TLhgwWovdVavDfitYPVHSqlqxFiqKnA+RQdo3riYmIg+aefqFoHdz+Tfae0Phbf4MOfDUKkPlzRv3z9W2cXU9QeWsaxoPxWJsFD0lcbFhWwxC5sB5ctWPk/5sPxzRlPKAA0baxq85z2+Y0/ENvx3beYmhoWFO+33NUrds0FKCUt599KnaFLjr6RgS6NBUPiJC4+ZQs4kEtZhEVSq3OXTX1KFDOIUNmW8wxJz/13Z43aQtS+xrz4MKZW4ft3+nLHwo9pabpQ9Y1EGCADANeR1/F9j2LxfCD2r1N45By8A7+Id+ep/IOXAQNBdLUGl6N5rLatks/HXp5p0Rxt3EMF7ftMscU18gaJgERNpz9/apU7+I7AIuM+qyn/53D4/9LuTltRI/aau8c0c3Yt4e6IQfw/kpJ9dvYapTPgk1KRP29y/3RnM3Y9cp4gfZHe32oGOeu3yOrckl7GnN+qNwHYei3BMkqv46zQHOJQHjc709PT3MnXXXj3RRLJAbaOe0rZw2Xj2fGsNC+Gv4ro5oEdf3xwRTnKVEHNivfCRbECXM5yNFVl5N1LcWfGx267OJyMzTfAJW4O4b+ZSWqwq3nIkRQi0Dt8FvOn637NGrR3m16n6tzp+6Yf2OnxMQveno9zQ95UyukuHzIGzQ86iPGes5OVK9txPE0q0Vw7Y0CRmyyzx7A07k0DaOJaeqrJVtFx5aew43DHwgmpbfIaqZg+Eqw4ue1Sjy4qpe8sFOrgG5pIkrg7nH2qiMLlIRL4Jp3Oq0ou7T+DnMwYbSvTPX7zWfW599SYgoGvY7ksRJtC+2Ud3a+iI+eus27GacCFUSduRaBPu+vHT5Yvw4UvNmyfwz+hEobeiYd2wazBeGFiEMHHgO14HOX09z52zPMIy8/IA1s4+cewB5fEw3iw3j90HKDHGeLD1dAwNohWPm0s3GxeF5i886T2JHk/kfKBeSglayXp0QTZwaunu0go+MIYEDmJ0r0ZkS0Gm49JC6iN9pLErf8+tcuAUpDFdrePUXSPukF2FrMOPxEO+Yrja+EyLN/K3NxuxqxXfSt5NEB3FTSuWNoxuYIsjcPvYp1cGr2vcu5958rw6r4N9bmnaOK6KnYI5PfD72mv1bZmln0yja8a68btvbzkpqamvo9Npfj4uPf0KB4T1v7B8O3n15FO8SjpjB56oG//hzbu78JjwPxg/J+sdG8aRNYhvjFRPqrlIfxmYSIkc4p4B3UUFNdhHRuFg7cIlxmMU0T57e09ecvE3QQvT9KSDYU+OYgma/tXKuukpGbnCPpqez1S4SMEdC9dfwbcGvuF8cJWk32KD5kaFS7M7mrPBWOHMW1AzPSYO4oc2BALNo/t53RmcFbgOfbx2Dz14DtOeTQNZZaxFyJciZFNBjhOyYbNZaEsXk5t3KQefhOHbqLQxglZkBZZDerR73juGg1/xMG+dH7h18/xtUvRcD+eVQH7ay/vjLMexjfMm8vH5BYTPOkGsMmfrHuAa38YW+w/oAL//aZVahRHc2l/Y3hpoWz9OzyDmS87xbb3zrSmv5fAoGceiQjOkwZyZD2hXRte3G3iWykcli5+wDCgI3Vb+3ON/wtm5eVm7SYr64lmlcmBmQLqSrV1D012raRcLLIviOzz7OD/bQEWE5e4b/rtfdAEOkvEPCrrTo9ZW4iXQkc5RZzX7cTCuI4Uqs6edV4vbTc9efmA05Z8yXcm2DM8F4=
*/