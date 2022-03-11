
#ifndef BOOST_MPL_AUX_FILTER_ITER_HPP_INCLUDED
#define BOOST_MPL_AUX_FILTER_ITER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    > 
struct filter_iter;

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    >
struct next_filter_iter
{
    typedef typename find_if<
          iterator_range<Iterator,LastIterator>
        , Predicate
        >::type base_iter_;
 
    typedef filter_iter<base_iter_,LastIterator,Predicate> type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    >
struct filter_iter
{
    typedef Iterator base;
    typedef forward_iterator_tag category;
    typedef typename aux::next_filter_iter<
          typename mpl::next<base>::type
        , LastIterator
        , Predicate
        >::type next;
    
    typedef typename deref<base>::type type;
};

template<
      typename LastIterator
    , typename Predicate
    >
struct filter_iter< LastIterator,LastIterator,Predicate >
{
    typedef LastIterator base;
    typedef forward_iterator_tag category;
};

#else

template< bool >
struct filter_iter_impl
{
    template<
          typename Iterator
        , typename LastIterator
        , typename Predicate
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
        typedef typename next_filter_iter<
              typename mpl::next<Iterator>::type
            , LastIterator
            , Predicate
            >::type next;
        
        typedef typename deref<base>::type type;
    };
};

template<>
struct filter_iter_impl< true >
{
    template<
          typename Iterator
        , typename LastIterator
        , typename Predicate
        >
    struct result_
    {
        typedef Iterator base;
        typedef forward_iterator_tag category;
    };
};

template<
      typename Iterator
    , typename LastIterator
    , typename Predicate
    >
struct filter_iter
    : filter_iter_impl<
          ::boost::is_same<Iterator,LastIterator>::value
        >::template result_< Iterator,LastIterator,Predicate >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3, aux::filter_iter)

}}

#endif // BOOST_MPL_AUX_FILTER_ITER_HPP_INCLUDED

/* filter_iter.hpp
i9iBD8Yg+ivSaPrwUgmDNs/IUaKVTaSSuzKgqnuG5+9u+ugC8ficEncnU4SIDSEdVg6xD9cYZCi1k6FrMEWGafS6u85ckYIIK4cMGgABVnq0HEGDaXhYk84B3rm8rt7Jfn8lyB12+6sSaC11Mnuv7ZwuQMiWw7r0hdnBNjTw/LggtcFXL0Ob8+F153kq55AvbboYTH4l5k01yHm3Z7nZOhcnpmBM8kSajoGMADkZz1Peu3f7N6bnY3ePQM8Hvvi/0BPmFEyoeik1oxA4Mf01Z6aOdmVRO3j/fnxsq5nvPZOijeedaFVa+S+ylgW95LGJMylaURH9i4roVelrOE3p4UQGWR2Z038pgg3BcsjTymYjACMekurtL8KbsxCTIOTB7vKctclhvOFQhnJNvKAnL3b+owYlcw3KiAz94C4asNJD0cnzYkWxCbVKn7TfHLXXPycurSWvP9l6Nlap7LbrBG4DJxOBTNjXpyWhsRhDkqe1+Qm0nXrlxd+oQmEUxrEXHEgQuDLDIa5glGk9jH/3ox1QDcaLsjfPSUi+Qe2RGQ4Oa673tpy0qT8ZgpjME7mcPp8+szPr+eBM09kgz5NrDPLUInnCtUrLpzCpd/+MyLPjsyrCkBrUfhTFrrxGAcdFvDd10dZj0SIYV/Y5yCTKQ0wP9MeMbyV6/z1KiyMjSaFGmHFL74M3kxZyTkuRk1PPb1LPTl5cQu+xO+4XNcucWscyHGHzpduj34Ze9Xcb9FqG9FpSq9z2ZYpe931qp5ffSi9Kf8q+M03X+Yj7zRHvvz87lba4dAuVxmuPmFTCY0iwtjb5eXbp4VSCBfk2eylXvzgqaUvcy2tLTpIbeHriFlT+rypNNl2OODeuPTKbfFboHlHHIngWnb+nVmlddxg4n5y+R5b9Qxb9V2TA5ixBi7nhGeYPBVFbuVA+7BH4efb6eEWyUW3MDfUdr/s29V221+LPWOw0NldQZVtu09kwihyT0jR5eEqYt9WX9pzXdXX7a+fRGBYJyrWbE60H4YJc192KN7At6vaD9GAP/T1Kf3vp73H6ewL+sv9WyiUtgQ9qW/DBROuLeDOBf+VEohM+wuqWffjolauwwz4xq0gTNtwF9NwIdhWpaD3/VSWl8r1A/8+9b8qX8PDNtkASw6rLz4+TLHDFNe56R1iOsKW+ZdCOicNkvf14pSnPePwBTLcpZlIWOnJbYSQWopDTrus7uyz4oLNT+Xhr38g1oxhQRbeWMikR6g1rPd2B3lk83ys9owVOxJxIh6GSt1axtwaqbPnszZLGWEqK5UD9jz20TJHS4YZTzxdZa87XHpLx4ZLOrozzK/KLlP1Wl+3EKtvwZ2M9fteIf7C4ZhwigqXBRTG2//7GV3q2jddh0bGI1wvagjjSKWt0pHPVHdZDnT/97BZrp3n7vzPwVNb1SFGoYfZ3YTI/jFlSTPHSBqo12mjpsySbJfYN6vfy+om9a8UYOR+xxOBHCyn+XLZciuVaz5xk9kZkssd/V3Ah/B/ehgU4WmqMIYC5Sy/eR/gNAxgxTKkxp7wIFxDD3IU+QCDUu9AEzWI2o6q1FqNUkiQKlH3GPjT3GEWLbXZuvGlAiu3pnw1iAWZO2Trc7o6AchLo42nFyLzzbj9AiOGZ7GNjCgXYiFHWvP9PbDf7X5t1OoemO1D8eV/Orh+uSvP3ZB/vOtNbalaVlNkfvjusKtE/0AOvqWN/OLKU6/mxKXXsqvNimcV86c1IdzJmGv9jL2/P0j6brmFKJK5tTL7dsDYW1kspcwMZbE5/yt7wp5fhsBkOhs0xvJHftn2Nt43Yvrv+dPHtm5i9fRe5nm8O2fgJaD6jwoa/9CLZicBnL7jI/Yq+tP2KVByXQ2mzuv9bzzaXWT1cTuUXUy0hv2QXB5K1FHtq7lJwF5Wx0zBW2TTVEhlmetn332puIfTZ4lDyuAfZuoVgeLSgFuuT+Rj6a99CGLBtIaT2YdzWXhQof5/Wi1FhWFz4xunUDsNoikzjjfVEFknaoH2TwrrNM1bZYt1DwVAvjEumElNyzWdtxCXK5rRGjDMaYdnmKKToYd6In4cXceeg12yFrc+ZtiwOxUYjkCvtTvSPKe2OLQOm2e0UpyccouTzty4SvkSWxiv7sm1JdFmKeOVCRWTYdkjnN9vcVryRYTO3nnS0XLDudpVbtGDbdpvy80r7ODg1EQ/HTiwtF17Z1OYDxnKy5yeLTejYlfUO9DrSIAykxo2rIet/QLUSVmVSToPbyKgPDuvfy1nkifYJqCXVj1cYsSS4MXs2dz6d5JweH0NfRI/ZtW+c0xXfkacldvqP6AcwkHkQN0pqoZdi3y+gT5NpafJ8xYcHp0DCyvvn4LGqG69bIikSFvOEvRi8m85ibOOX4bxseLm2EhF6P8E96S1kjvpade9GPDVQr5eucjeOTbhKZXbdn77Uz+wnyA13wlOKpzKmwqVWvfmKRBFBMak1PrVpSKt05RgutnjA59JDQ7F+RLwMumZ+kChaD0/lnEwUzQOzNefk8nDC1bYcoQAnIAvyxQflHxV5X26b/U9BSfdvmYYfxZNhwMRpwJUI2J5wETSSnHMS/r2JjvuZfVUUxKs3T1SbfNiCN6N5fHLFu6AFPmjBSjc+jyiONZ6cNyN4naZCVazf9N61/fOuoPQC/L9f/C/lpP5zmN+clqvW7xf+L92+i59xnel5JYWfx/FuhBrN3VtlHuihd28IgVMRxm0DZZojxZA9lwvWzeC0xlHsrp/CJB90NzlLzqLvNOCpd1Bo3L0YBYu5CI8VzpDqUHmbDKwGIYNuX2nmawzX0aE5tsosrsgsThdw4JVusCaDLjZp/3RE8qlDwJ1mKPOH6esFyos3+VBKIpT0QpcadoMy/8d906UMFi7PrwANXDBAgeFK72PPAK/U3yeLcfAaUiPnIgP5DCwY7RlJ3Fl3Kd2ZqoUGQX750aFZM6jNhqU/A75j97BZP9S60iY8X8+rsq5nsJ/fZnf9azlwPrDouvPmQLX7Kbq9cr4aLFODy9RghRpcjGxLrZTVYLUavFMNrlCDtxHfQjBynxpsVCsbRoKEMsnA2zMhqz5E6DeCHSQqZcZOfUnbqYnK+ewUfLdAakUzwlylVz4sv1CBBe8qw7mFpAnliuWPxCot5XW/lJ2+ls5caumMd3hnsjTdmr/CKn/kzPtZ2iclwO7b1ebVavNatXmdXrweygd+1R1o3+bcxSUljnegfTcMOFhFYAoZLnGwV4Jz8cAQTns1AJKxARuXUuVB6fFdPdyrTO6Mc6dSO068vR9ELy7fBhV5oXwbUN7T0Yscv+EFZhy/e/6fy7v+jgvsf3wSb14neVur6ey727t3Ll/rxcgU1pQOelufRWHkUsqnUexLocjP+0AdX/t0WOAE03OWCWHIoWFNUAB3ah/Sogcq89/DQ/Bw8/i1yE0a8rXaqFrYn9eNBw4Q6H9OYSbrUwSSqA2uEQM+4s2rpditcd3rbaWAh8qG1sPRy1llVzl+Z4f2l0tmKnXMhAHXnK+US1nKa5Si86C82Jx481optjTerEixQKIZHbwndg/pWmUjZmRz1SVq50fIR3Q5n9DBtWpwXebIke7gWofZuBYsMfq/tF0PcBRVmp/J9CStdJhBJxKLANHLuSDuLjpRww7RWZIMwZCkZ5JMUkISdkUqNeUptZnRWJcMupPR9D0a4x3elVWsgn+22DtrjythCbWigSgDioIBJYqrrJu12k08xz+bDX9M3/e9193pSSZ/9FyoyUx3v37ve6/7fe/7vvd9vy9L+a/DqyxDl8lBMaBYXmbU5qahtvbANNROxuPImpHflhxcNY6mt5M+/HaYYrGeDTS3LCzmGzAgBU73RA/oYUJeb8K7xDxpjsyOX/RkzcxvKREaRebmWGLcF4AIg1UpR15aNUu2+/dp3/fSqilMAqw9Mo5n/vDwC9Yp7cfkAj4MWL8anaAaPlEO+kFAip8cQxvvaVQWDo6qqi69xzvhDIaO8K+sskgHX0IvATUjYqeiRMgScshyOdVnHqLZsU0zWky5YjXNaljSF4AuT6WACWU7F2CsDf5GyXNw3yr0yt93HI4TcQyF1ty4MhBBO47EBsQaVh4FxNO/Qx3AVc/OKK+dpw4mv8JyIPbGcULLTwzgXWrOWhc8wIMKHGQ44mdxWOI74QAEq1GU72nS9YUIjjOU1c0uYcj1k7h5MuqQH6c37EAXR65HVE/FRtXIXXr0Ukakgd0hV1s9R7e0eE60b4ydt7Y3LztE5B0U9fMAMcxC4XztJEfhF0S59gAXEGXugKiE/3BRBXGZSoFL92GN1Y74fTBOcFdugvafLly0h0MFmvRMj0j8OEVPDM8Vh+xQPCvIhCYi44MGVuBgXvdx9PsQa2gSQDRqyzKeUEKn6YLNyTI+f2XdaWPN1p8UXbf70hn2P3+HrYTOCfi70izmg3nJmb2Io+GV/p3rv7Nhx0z5mjDXufusKDXC091K88uvaCoP34qGVWX1N9T0JzVeoui4UIbkFN2JadYD+iKG37hKdTXOifc+CHrtHH36j/RZw47Yn8Yo1k5Sjy2cYwlflY7rcxbiK8XtgVgbrChzSXk7ZmMU6C7BiXQbv2nljZXh1P6m6S5uRdFsBZW8iBO2de8qtC0XW6wcLPRjGMtK+1/HB5TVlyb1P5v13z+5/w7Wf8fk/vOm/jss4dweK7Q1CTKfnzwCViIK1APxTXbpLkZGw0ZqI/7NRZ06k0QhjEdfGZKBIVEIjFYSLHUfA47x5CHpjhZDjBCMGP00pOn5PkijEARWLLsW1ZPzUt2l+EjbvfGzbSGymvec3HKX5932Zs+p9nXLDktlo/Gz0etsI7YRln+pmrONx8dVRD5Hp5Y6uicIJXvDeVig19Yryq7HkZX8j6gsfe+iCqWAmyxt5o01PGV/ddr9t3EsoYaUiDc0tmAyxaUUg1KYncWFtfejT0z4WZvTzSelZLGAwOmjibLTrq0grjcOSI2DUuM5qfEDSbOtjTv3mfCpcG+wjAI7SGWKhhVV5wwY3n5yhVWOnFbQK4tEBkiZQt2fqzgpU7uOzs9VvB5pe1qsR7gExSXSWD6uvgYOlVsCgvZqdCn/6Re0wMc0pj99UDpOK/1cOkMd5gOi/ZsiHxCMF7whyhOcjrc6np6KJJqnkn+OZk4vj0F/Uw3N2OElJtjeGfhhflbK/lNagOh+z4UODSwoct+KIBeucZ9dEeSjt0h16PHST6KcrSOJaSfqLsnVfOp4VXO6fSkplKCJ6gTL6ajFgSZ8nIXh0gcFKZjip0VHlTRxnvcdcZlmiHR6RqNZ5COpcXjIjkDjA3LeOrQUaYheNSCPoN3j6NtoYnLG1ejt2s4+0NYNNdkak/DqhfPlivFBo+kwK1IHDWlVK5XIcQLvXhWCeU+mq0rwnHc8Ro1sPt6T6PgZObHsqCyssR2zHfMHZJdX5v5NVIqBFLhQxcO0cp+NH3NsQyEZ7rD1QREYCZnrhrmeKSrZuN5jyRLPe+0fpmvSsQ09OZYlpDrEbd82HwWhvC3Yf8ZPgpztVEB5hypmCqnivctOxPoEmDueQ+0fp+0DDOjhSAFQ82Ts4yzb4UOjttgo15GFkYaWIaHYAt9Rew9+yXlWz8UOO7BtGPmOJPnI857+SqQ+A2hXdq1Bs16/rT/grxHhOSmPf3YBsXpJYtkh6DW9InNrEBje9TCG184/CaOUWOaDUcrH8JvoP9L8MDypG4ZxEmAo/4UNknIJgaihYIlnoP1DaEWP3qkbJmVJZP1BTvKlfWAULzE1udkioGk8uVkVmj3rlX3exZbmJnMmM3JUOYntagW2GwW+y3w1T1PzNKni0obuTsp/8P+ufwZ+0LbvV9PLC+6ziSxkcwgaX76iGbkACAEPcLYIJqaZqXnGBZr59jfJahMXSOc0nrC+unUqfG+8Mjt876N/fnr68aJ1aWS3DJT9HnTaF7aiSpOkaoA17Nz1QRkNnPI+cIBu9CvXZs5GjWXtF+2bhf74wgQSQJ+imVYiV+ltt7SBEmnHA5MOjcORbizSk/QdxkOPmU5k9uBJxqrVHAtGkA0CLcBsjXGK/LhluAwFwWDLhtd8Wqh1w9VIUu6zShmFhhNgAoVU6E65a+YF6luMX49p/AZN47clN1aMTcPQDWpDF7YrL9ppclmqVoFwgIYj1jMDFByHIB1eKM3Xq84+Xy/mu3DsnweyNQhGbl0d3xTvDy8jqmP/8tjY9eFqx/5+uelc7C/5nvfD9tjY7ZGbHPv9GbFDGTT6sj9yZlOs6PrI5d14CL/Cf3Mf27SCb3ZsPwRT5RATAWmCAfbTsf/GTaAqvt7t2O+MXbg+Mo/dZwkXYo62BzOGrnXsH5HvPBf733zPhyCOX7g9fDnmZTsRS2QMZUJhaJnVETk41NncRE1H6QKYML7Bx8PQaU6w8/C5ztcWdV7ffVdzNsx/hiaSyWTOAFfG2got4WziLWRuT1xQPUkHz6gv4/usr54UYyVQLceqzRbVM6YqfYL5nKA1Q4qxFTiL+XigMfUMrCrYIt88ZZNp4rtYf2zfW38kn5NVaZ+yykreP/sqJ/HLsZb8E/sm5GtyTpGvSbpbgRe72NJpsURCpNLl7vUcDVdIZYOYZfZqz0C4SLlaoJMKTQ3pEjc5qWrFE6tUdg7uo29aH7lbmf4WTJVU6fSLNHFTzqu4xZammLG/NbzE3StKpQUIWyHAxwkfF3xy4ZMHn3z4FMBnCXw4LecVlIJnE8IfS9Sc0isQVrPAj4UTUNHmw7jT2QUNu/s3aXCw6fXv2HDhuL9hrPgc8qBg/YE5QOnLS4DHyB3Hv3p+0/ORuXLZcVGpgD4/e47yUEYHiLMhi/l/SwPeVHncjyXuacOeX9IQaZufxcXB/WYTOay4X031TDTooatJbDgP3ol/Mha08M/p6aAGbGhtwSdK/1CUEwpteFsNWRiG9mA2bYYvKm+iT4l6BvHb1FMkG6sw3+unlxHy8EzzOt1/BmcWLSmGtFJqThs0asxXvD484Xqbdn3XMFtEVtKxuEJkl3YhfzfWFJKNh36Nq9sVfb20D2u/9lj7Ut93y6T3/Yap33f3SBD+MZqBVgTxwoTlas4APK1X8J2Fy3Llq0BAe9sB6jEKU4JNkdulyCA68lWe9LwVngMT5ENYikZ51E0uDR1FATaDWCZMBFolXHePDP06NnpFZBf+2ZFuXnC6/v+HnJ3T5X9EhRHW+O0yXc6ZgRoVH5Z+pMqlZRmxjEfpUMOQK5G5FVXbpkLJVyRVeaWm0oSv/CQ9VSs1NUhNotS0Vmpan/BtuFwP0q3aqPQ8dp5aIKWnKKzLUxTV5amt9C8GpBY1OsOLQpzJud2JCrinL3ydqHhGVHUoP8RPuJoJV3lR+eHf4GqGu5dW7ytMK01MjIf4DvlObi18Ol2w2QQZRGHjow9ZVZH7rOcNeMpW4sS8I1JTEakqTD1TSF7GMfFcDN9BHsERQRnKVj/0QxCnPX3Rxd0kS+PuoNl4MfImgXGYHlq2/WPyCI3HNfg/G2Hychers5o80j1e5w2szkVTVdnNqtzWxaARjCq7jAcVK97+XI/FGvnJioVJmErhm1q+NstZ/0By8HRAWshO70UuSksm7Due77H0vuKzyL6NIStDWCvVLDzuY+5eTELfVBu9E5OtJT1vRGzEtxae8B2kDXNx1yWhMzejLa0PV2mDtGZQ44SJ54R6PU36MBz/FGr2VNW272YVYmbfPszsu978ymqZqprWsw1HoM2rm6KiGzEfUtbGezUArNW4WO+8QnOnBd3QxRzioHptLszciiFh0gkI7zIDfYm66s3jkgVSCdSVFRSVM/MNKDmDNDu1gCRsGmW8XIFrvkaZHfEWXSa3qaqpYLQm+kePC0uzkpLMs6e5z5gv2zNn8mcmX6SEfScp64Hu5pCqUmm51MBLDYLUQNOj03B0rSMwTL6NInV1KzU5ilaJsSPlfqV5Ge7yYupvmGV66m8Qgcwect7pUZ+1/U/7DPHJX+iEKAYhbIjWYly8XI4ZiXLc/StWOLYfJq/Hj0XmEtTkPhlayMwlVB47Uq4sXIL4v+Es8jfll2OqakYQ8KaF8AL6aHwvVOBAH615wQBJKvd/rapNOv9X2iZd/3XK9YZJ14N/NV8vYtdz0PQ6D7O7Bsg8LLWH1TJxvzioZKHVioX5wzrBo71Wqfnr5MIYL0AGSImXHI398ZqHzl/j6Hyb5nTnYhfsjs7XcBN/tzO8YHd+ZD6JCqSiiFjrSRR9l8Rctb+zN/wA3OxWd/PhhfCihtaj+yZVLjHSdN4yHy+3ZbytDmXt5sI2EnWNlHitkTVoZ1NtCVHZjD572O8q3nbCr3wBhyutkaWxKMdFFpGgYDsTUNbqZXwC3vImK2Nvvql3XR9UtxwK+ihh80ggV0RUA2rIBNqaHU9AmeY91nV9+DHJ/7FOKqhHMvdYqUWJUEZ/3hpZQrKRL8K74hSpGvA2SnG9WKiH6VPaEeqNMMDHosvZHSSTbvvV8WJAfZudGrLTW2JH0L1y3mrP7+kK8S4QTh8s0EW/KT1dGj039TJ6ujV6Fhj0zDHoCb/PqDZIuJUV0vHHZkFJd1pKzPMt05y/Ozctu0Co57UYLPfPRRZHJ4Xg6VN++42qdvY6Oq+n5lSuHOMRHsWcJ2pBfPNJRELQ8MzNOx3s4dGMinSvVNvl+PQjZsVlOAENJu7CbuDRW9p0w/Cnv2VMkbGjBlNAbhXuVygGQr1Nq0GgMMdlisjgb9M48A41MQLOGfVx4wQ4aVLccQLODS1npT8wStvHS7sQipT4nOY7dJT3MfKGcuXFCRkkqS1Yve2Ez3IffJLw2QmfRTCKqesDhzaMTLrSJehKl8CVziVFBSnqlKK8FOW0lS7qau4bzwdoGFyvN6dhZekTfyDDsqPkH8u2kFviI5Ev9MyCNYb1dSB+NiKs08/T+OSySxXKZ0ezKdxEFBhApIgEc0NCQPa5RCM7ouxas0Yu7R5tc2l4bEGn5KTpEYU1D34Jt8IbfjPhMe9hG5eg2oHqwx04zHlAE8uZ1hGgIW7QMBFp0ixffotRQikURsosiDabJFGmn+T+7MUJ+okwjT7+ZexB3hJxpdEQWDBKInMujoSfh5c6dniudBW5kazhPV+Ef6RNkYA/qCQOUA9desPQHEMZQRdLPUXy5Oo=
*/