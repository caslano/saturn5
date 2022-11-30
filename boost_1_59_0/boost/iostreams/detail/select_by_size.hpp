// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

//
// Intended as an alternative to type_traits::yes_type and type_traits::no_type.
// Provides an arbitrary number of types (case_<0>, case_<1>, ...) for
// determining the results of overload resultion using 'sizeof', plus a uniform
// means of using the result. yes_type and no_type are typedefs for case_<1>
// and case_<0>. A single case with negative argument, case_<-1>, is also 
// provided, for convenience.
//
// This header may be included any number of times, with
// BOOST_SELECT_BY_SIZE_MAX_CASE defined to be the largest N such that case_<N>
// is needed for a particular application. It defaults to 20.
//
// This header depends only on Boost.Config and Boost.Preprocessor. Dependence
// on Type Traits or MPL was intentionally avoided, to leave open the 
// possibility that select_by_size could be used by these libraries.
//
// Example usage:
//
//    #define BOOST_SELECT_BY_SIZE_MAX_CASE 7   // (Needed when default was 2)
//    #include <boost/utility/select_by_size.hpp>
//
//    using namespace boost::utility;
//
//    case_<0> helper(bool);
//    case_<1> helper(int);
//    case_<2> helper(unsigned);
//    case_<3> helper(long);
//    case_<4> helper(unsigned long);
//    case_<5> helper(float);
//    case_<6> helper(double);
//    case_<7> helper(const char*);
//
//    struct test {
//        static const int value =
//            select_by_size< sizeof(helper(9876UL)) >::value;
//        BOOST_STATIC_ASSERT(value == 4);
//    };
//
// For compilers with integral constant expression problems, e.g. Borland 5.x,
// one can also write
//
//    struct test {
//        BOOST_SELECT_BY_SIZE(int, value, helper(9876UL));
//    };
//
// to define a static integral constant 'value' equal to
//
//    select_by_size< sizeof(helper(9876UL)) >::value.
//

// Include guards surround all contents of this header except for explicit
// specializations of select_by_size for case_<N> with N > 2.

#ifndef BOOST_IOSTREAMS_DETAIL_SELECT_BY_SIZE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_SELECT_BY_SIZE_HPP_INCLUDED

// The lowest N for which select_by_size< sizeof(case_<N>) > has not been
// specialized.
#define SELECT_BY_SIZE_MAX_SPECIALIZED 20

#include <boost/config.hpp>    // BOOST_STATIC_CONSTANT.
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>

/* Alternative implementation using max_align. 

#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/type_with_alignment.hpp>

namespace boost { namespace utility {

template<int N>
struct case_ { char c[(N + 1) * alignment_of<detail::max_align>::value]; };

template<unsigned Size>
struct select_by_size {
    BOOST_STATIC_CONSTANT(int, value = 
        (Size / alignment_of<detail::max_align>::value - 1));
};

} } // End namespaces utility, boost.

*/              // End alternate implementation.

namespace boost { namespace iostreams { namespace detail {

//--------------Definition of case_-------------------------------------------//

template<int N> struct case_ { char c1; case_<N - 1> c2; };
template<> struct case_<-1> { char c; };
typedef case_<true> yes_type;
typedef case_<false> no_type;

//--------------Declaration of select_by_size---------------------------------//

template<unsigned Size> struct select_by_size;

} } } // End namespaces detail, iostreams, boost.

//--------------Definition of SELECT_BY_SIZE_SPEC-----------------------------//

// Sepecializes select_by_size for sizeof(case<n-1>). The decrement is used
// here because the preprocessor library doesn't handle negative integers.
#define SELECT_BY_SIZE_SPEC(n) \
    namespace boost { namespace iostreams { namespace detail { \
      static const int BOOST_PP_CAT(sizeof_case_, n) = sizeof(case_<n - 1>); \
      template<> \
      struct select_by_size< BOOST_PP_CAT(sizeof_case_, n) > { \
          struct type { BOOST_STATIC_CONSTANT(int, value = n - 1); }; \
          BOOST_STATIC_CONSTANT(int, value = type::value); \
      }; \
    } } } \
    /**/

//--------------Default specializations of select_by_size---------------------//

#define BOOST_PP_LOCAL_MACRO(n) SELECT_BY_SIZE_SPEC(n)
#define BOOST_PP_LOCAL_LIMITS (0, 20)
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO

//--------------Definition of SELECT_BY_SIZE----------------------------------//

#define BOOST_SELECT_BY_SIZE(type_, name, expr) \
    BOOST_STATIC_CONSTANT( \
        unsigned, \
        BOOST_PP_CAT(boost_select_by_size_temp_, name) = sizeof(expr) \
    ); \
    BOOST_STATIC_CONSTANT( \
        type_, \
        name = \
            ( ::boost::iostreams::detail::select_by_size< \
                BOOST_PP_CAT(boost_select_by_size_temp_, name) \
              >::value ) \
    ) \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_SELECT_BY_SIZE_HPP_INCLUDED

//----------Specializations of SELECT_BY_SIZE (outside main inclued guards)---//

#if defined(BOOST_SELECT_BY_SIZE_MAX_CASE) && \
    BOOST_SELECT_BY_SIZE_MAX_CASE > SELECT_BY_SIZE_MAX_SPECIALIZED

#define BOOST_PP_LOCAL_MACRO(n) SELECT_BY_SIZE_SPEC(n)
#define BOOST_PP_LOCAL_LIMITS \
    (SELECT_BY_SIZE_MAX_SPECIALIZED, BOOST_SELECT_BY_SIZE_MAX_CASE) \
    /**/
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO
#undef SELECT_BY_SIZE_MAX_SPECIALIZED
#define SELECT_BY_SIZE_MAX_SPECIALIZED BOOST_SELECT_BY_SIZE_MAX_CASE

#endif

/* select_by_size.hpp
htbfMqJyvzs2mcFs4H5fNVZqvdD1Y8vkmsKKrkw25IPYtvI1SfiNcrcm0hYqd5MmeimTaFhruBkOHvjimBWZrftLzz8+tJIWYF7Ec/jxRk8vaJQ2d56LC3IuCkxUuUKJCIANaI7+JHkfSbY+AoHyb3XUDW8ppoEPqs7c8Ysx2tGuF39Eo6EZwxG+zFKDspgYbS62asgDmJ18UxuZ0GLnWA9yp0ghQKu0MAxdz6qMfHTgJwH2VBdG+ax/0GIw5XDLduy+15w1td8lNT4Cwu0WA6ImlYIu62sWQeA2bg1Oke03lz4kHfdw9nyQ81aErZ3dIXc1zN6v7xmelu1oaYhx26C3jzOQglDA2zRF47qQXbZN1TKpEgxW0D9zKiOg0ibrkEjEpU2aeKqPRSGzzQoXqQrIfghpAm7VlZNJ9zjSwojDBmkyp8DJ+fuclFVDYeac3EjeGqGGE3a1xV2zk7DjoxAu6a5S0b9Yz5Ne82lLws/rf5g6+hA1iX2MMJCBLtkYIhk5DI30zTbTeeSIlj+EZXnWbkJThw8RhUMaa1ct4GSOGzGqrYavlYj9+xaflyEI6dxB/SKgLQ2a6fvjEZp854Iq2EagEyD34BmRQt+wghENIBdliJ1ID7SCTHXiHyHnayyCzyGOXaoKRwYjW6zN7KfXk1ld8h8X8MOkJFTgmpTcg5hXVcOFw1QPld7whpuEFC5xu5H25euEtCwcVhZ5c+CUyvIAV8ysJWfxQaMf50u82+2IE8Fsr055M+itP1UBEkqRvIgu4D/5DKe1drJmLilcbke3MD0LHCMFA5L/3FiIDwDs0/dyh9zoGm8F7wAamUNDRN2pGsthwbi9PFGiIlsZEIlACR7WuZymJLtjbkEw9k3uzTKg1EemjWFzeUT+SLBHXIynFd3kostyGAoZB44Z/7yQQVCk3gxeg6bvLvW92mYxVBd6auf+2SrNZ3I65lfV+clVsL5Vs86ZCTpLIVomxUGwq/UHBvbpqa91bAAALP/TzcC06//SjvgCgO9n6zYmNyxiAeTAzn38Z45JY8m6z1+YwwjodJmrz8uM5FcEnJI50zRbTHRkZ/VUJqmdIHyRbmng3FedosG5pFx+fy/7imGOi4Zh1GsegrrRJTs0y7TtWZL4YPSm/drZYKmUG3iG4ZISULBTn4g9vW2V6WFB3TW/opAPCMt979SBGBeVni5SGDKzic7/5H4pYH0CTB65vPYzOzLxOHKn3TkO9sL5JxvA1EYS7T7WrAo/vGNbIuhLZo14aisZyQP3K5YmTCid8KYpkGbxr9w1fIf9a2SbxNjp1oeE6QGmd9DVZW7POgww8cZYNZJRXB8Bimpqjs4TyipxNMiidmCbUGpcrSaLTChaKoiTWplhIVA9PRuIKKYYn0EVmHcPWxC2Mbw+ZHjYLDWWUbXNx5DE8Oao/TUo0O1rfeiOu8+mjFW8zp255EZP6VTLH/VaSaiYWbHPIHU0S8t7Vef20yPgF/Nrpo+V1vcINgVB3fI20+xLFynEO9wPTCpM6EVpTls2ecjWttad84+tmOgaib5rasQix+0fA/gc/TpC6EN4n8+RSF8IWp9P/Qs6Zz53Oe2+OrOlMpf+PXJTZ8y7QOK0PtRcC9vjLEdl/Y1ohrwVI+qvy0lYVHOKs3EUYDfeDx1GDC4p8+ZMqKrlFmtB8C0qeNz1PD6By3gsyPgP6QtSBluu+HbfXIXsV31Oz0Q6HrepFIP6WutSA5cAU2w5uoO4itA40i0nJbCzlA4G+P739X93G6ZB4yzpV71rytsPu6xWRg9pQulThD3L3xFkqEtFq26QYKaPPs+mGtuA4nLLIG6mzsFLPyN0G0U7db7BQ+VrKhJkjJeekkNf5dYKrC1D1nyAT6SW0YMZ1mb+82jvGMSQIJrHWt9vMW+If96L/pIyWS9gP1fNHraeDCe7fae8Jqgs++whCgAI6L3P+AUn4PULeHa7ioSjSe7aCd0a62xZPEKpf/bJk2Z7dNfnZEjmUWESn+ZWB1nYKSApY9Amaurr4wGYtS4Hnpg+cnJojZ6MD8Zla83igFKREd2MMW40LakTe36G2zyWwItdjP22iPvH+JyJNbIr9f7kCI42eE0x3aSUGKqR0YS7KmashVI64BtiI+fR4SkT6QfU8o/7feRNr8HBTCO79uDb4H26Z/VfMdjH4dEWCQlOXiOrr7b2DvYgz6Y5DhWI5FYiRgqGfCZ6ZwWAp++3XA3iZI/gpT1ehcH9ulNV6Uyn/uap5t3tKsV69ihe/BeRL7l3jeGkjKQU0WtZuxdrJ9IQwigyAjbxe1wbPymGJh+p48vX1hSFDa7uscLeO625ECo6obgEq3/O3i8rpHCjMQ7Ndq1rdPCx0XrJYqA+6uKLP50v4zXypFxTTYvxJwN3uLhbJQTkLYK/Dk+gRdVLCvN5dy1xX5QrGd7cpKlHNAhs20+XoAKc7X9YiGAAOwg8iCgsFMVy7lYp5rqrOyf6KODb+WNv1K4/OoSEmXHzTtINkkiNWo7GvugogsqqdTyFp7Zw4YaaZ5t7F8GA3wo7KdntPUYod0JpBa+Tbt2M9irNtRdyYYS3NrjHsiSHE9ddlDaRNOxDNsAg2+HsfI6VgaVeptQiMnCWnHJ4x1aGCUIfjzWpeQoAeqJODDJ1/pHJcBMdlgmUDnPXJcOfpsoOnKbodNbkxq1bmrwnyaiidJYhVBAk7JD8eHJA9az/ePVzVXvmg9i+Y9iPaBtvvbrfzx5fa8c6i36140IcukVUMC6XIHAFjWDraCYa39ZIJC+6paKPmb44RuXpyGWzMUnfDIxPQPLCs5WXVoEx4D0jL4erVUTmZCUmcLJOsj1u/PAjgJPC8AZcNVhXhxNp87E08WKUHsV+/6xJbRY5cRkzJEB6zEvHy/lMGgTNWTLmha0/vPUL+AHfVQTGv725PGWEAWcKGbbj+lfC1wAczR2i2oAxVlwJfDKhQGs3abXh+v4rr8XghHwqMXO24XM5dTAOSwRL0ZvoPK73ZDAApIuEoBEkWE079D4wH1ArJKwBK6iVeck0ijScMC4o7uQnm/cllu4dLfRHc6fgrzswzBqKsCjiy4yM3gO/zTiucJL5WI0+EyIG5mLb+bfpPmifK6LUvgP3AnEV+u/NyIsoVx/xz9lTC2Il+YorApsTQUcLLL37p4lh6L+yv+XcqScIooTxAEwYHduC6T9y57BXol89gVKzBTaDMkbtnwaOz3VgIcm4vJZDSNwFpN5VUFlvJSPe0XzL6WVwPJmwM6g2NNWbVvHL3m4RAc8wbEAHL8u1hTwKrehZ4idV4CUESNE25jnfFsjXhvQm0Z0AnlJ/xqtvHbz5XYyQ6zPaoFylONU+QodJDGCJCDvDhD1ox6LpysIzlk3kpVO9vwTE9Wh4oWlbMOa1mVMVUITx+w9dmfxa16H0JnQ4XopR4d7M+4Sgalc4ErpkgD9/nEdJwLw2aJsXnERB2fB+nujArz39vzhB0PExJaY2g1PfaeJlI1X/QkxJ2pWt49mllWo6Tt+eEzL9VXVyesLMv3llSDHm/bRTHh2Ko0R6tRuRFpJnw8/UAW5korffEzCz4aV7BYMAYZPhG3q5SGkTY6PS1MKsbfkKoy71g+LAU2fAxB6RZDQqvGZyaxM+SFRmUGFvSuKON6vSy2i40MSJ/1k8cpJ1tX5TNJHepumN6EOmniaVOSC5TYk++jdVVikwIqSSK4rQtgv8J4eOYSd88p9hqoNBPzPbUBtNu+1Br/wjzqt7A31mqUDBydt5vJlZakdJ1a2xKFcoN1vIWJjlx/bJkl5boE6lIOZoSlpFRnUQkQa6LzKSxVNiSLwN46PFXU9aqM1fmnBFtPVzhPl/Sr0AmyPdUiqcDn/uQ5n9Ve/ngRrOpm7T7lyWEnqFFklkDdGLCdRbaZwjRS0YXkquISIMSlcnyUNa8sfc2gHzCXcDmtMc1mcOm+ZDjmzVCJnueuVGmIRgTqfDgrtv8xQoejbYqm5vD7YDfMJInqHlwaZkykIM3PP0s+123eLKREd1rRmRuGzyeK/IkGT7Rv4M7QISn5zcife7BAOPF38aNyH+/fHwrZraGe73h1uNchQYEgv0wu/QPA2nitQVvKkaalFsRdvgXJW/gLtdoWtHZVKGUBFTSlmadSrr3gHXkrNI9zWvHJO+UbSpkER+C5uyLmJQutW+2LozdsTox4ZBJewiP1dyHX9WsMnepb/HItaQTbQ6/tlrzXyNVNiGwfNnET6gVjerDn+kgK9SQ3LjHVsE4gjeesHIHZ7uaBuAQJEsyk6jdX/InyIH0IEkHhzrTbou3O3nggHPpg2FSK1WDILJv/LN1DHh+NLKlACIZzldaDGmpOgIX4nAV2projxC6d9DBGz2oXbvPctWCyGrgjC135jgisshvVkitlMzow/0RT+cF0BRJ2FV/M7YJrQgsTSYd8y4Xza4DrXtUsCSPC4M5GtxTzbFvtbvEGfCUwq3LVviCksBdEcqg+kn0q2xZGw6AlihUBw/jMhvX4ysN8fI73G6dz85vPECGvNKRkeUcMiPX3VhkIGgW832v4YUzDSf1hh72r8hdYcaROYSzUAnG/Sm0Z3zOxNk27YhWjGWTtTjweveyaePGw/2FMwBXFPq2PuSX8Y2c/CJYzpZxeSPMkA/5Cim/Yd5Y4zsnQUxe9Py2nTKJxKPAPHIJ20Mji1ANHR+jCbGZuu2PlWAvb63g3oCKNZJetP/rqCYlJIruDhO6/rYRwfzmH28NZD14A1U+H6PrIIXbzZlYfqOBY7h9XVnCKRLR4Lo/nyzvDqcXQpv8yAqoDZx+pZw9pefxv01H22mir3Vtm3ZxMprSCb0as7yg9macBXa6TgHJvxJ8SCvf2MgOg1J94OIlHPk4qhhf2PKlpC/zyxbTMESraq/RNdnvkGH5Sp+SI0p9913SzTgj/vC+ETDoCd/H3TO359746EFIC+UMUdMymVlWaPoR+1Jj5Dt2Bulk4pj0sxwIYC9lZ9KImBsRRXscV9+YGPVCSsH0plFa2OJLiOvL95Sf+N8l4s748kWL/6fIB1FF8dXgnfl1LOM5SxlUUpkdhn4y0WVRMdV3smuTKl4TQQgfQC48FTtbtjCWlUCuk737aUD1Darngm5QpOLFa7UF1zb4Rw5JLlOcodRWsB8ozYbCHxI1LPZy4f7vUFb27u8kM1Y6NmYqxyya562jEPr4j4mtavCJrMxMyHebsav9gh6p92e+bvmL2LqUjZOh7hUT0L0MKJX/Gn/DCkoT66lOHetTFsNj+3rZtf1OoBodmfs3bWZ3Z6jlZyh0bz6D4oElKBnBStVEYgLmi+Yrq5Vx/Kl+U9rEzpllfQMP4aW/kZvSxXMSScaNjfPI4Ba1tklV/ecJnN4yzK3ldaWMAlWq80wKxNcq4aOij7/aGpC7lUJNA2lXjz4ioRP3hQnPNt0OF1ECoHPZmC6uacFkAyMZLrpRNrCzt6Jc7eFz7A4TMnSmgSymDyjGdq6F9IQylF2cozT58XK+W5BFRewZa5WFLY2hY8BKJjMRfSqMiAIeeB6/iFQfPugA0VzALQwPvx+W1O3+Nzn8CarHwVTkJq+Wdoeb8souGYQnVksPDMI2RRMLPkmDBk2SPq/oAFA+a1JaU13c2UiwXKvovjonfsLIxklIcxKBCx0sgrfAs10LEOsYoqcARXpZ6xwmJITEs2ga4R6yu1aN6Sk9kU5HKrTh2oeZ5HLAqbMyXLMa35TF8aBAXo5i4/Z3QBIFpdW/Z+QkWgJsSxNGocID2uFBFKMg1z9SdPP5ad2qRXpOAHFpDhPjaPRjLlO6O1Gh6dgSBlwGvhidH1BASkIEmnb/5Kb7vFQEaKSfSrLd29whph2um8K4Vn9pyS4dN9zWk1EeKAwLEXMS0uuy/XHD5OTXQ3lcm5dpGvnipChwFf+YbNjP9ndWUOXJwA9G4qTkyIwprQ3lGkTtgxlEB9qXUQAgIPO0zqx2aiU9GMC3VQnRSDkCWJCX6tpcmJrCMCLHS3O3BQOe4aqZV4vY7VECxAwYGp7HhJFayNXMlRf9e7h6f+sbJBpyQnN7Cp18L2pCH2YCttZhH6UzLMpt/HAHorIlkYCF9ERXusgZxoV4V72658HtK+0UqfM9GadZ6r6n+clWGxADSf8I55UPbEiFkRumsTcaS79Y6i6oDtZh2XlGFQ4TUuaTFjLuAp1k9bLiZ3w42j3wPAo+p0GudG1Qsa5zrASRRpwPO1x0wjG2eh1z372wIwkmVTtBCe/4Mpzkx0EGZ7sr2ED7yHSI4bViB78cv9+ZQq47xEN23iAScFqqU01lnBtFiDvoR1k0xvJacFSPHou8w1bSd+u4o4jYbj0kRJyPSPyabD7z4bYwPNCIn0BPSVCflnw2O886aKSH0yyTMNtMWOiJzANQPLfPfUFOGljQGie/aG60p/CPsVYc0XMnxejqxIy6eYPlNo7e7ZS/NWoTLwOYPLFnN3Ag0/wSJXUdD7WL5jpZ/jvYwm/jC14ufhL/5SS1KV2OFxbUcLk1ri0GZn6Env5hmiFyTs6LN6jfXpdcyNYW1RNu55CnQhRTRjupzktEZcE16TxJ1cUElnRxRuVfce4QXsa+VQcYglKcO2Xj2jcs+N1+gUHwotlsJ2LLG6U3g/X6PlgZ35Y2n+aDfto6Rca7bCnRv1aqTk9monqY6b/ykthcq60fcZeNl8XGP0N1MdhxQ73/OQnNUXK2olkFa2Jomxe9K2+bx/JAfkJQfJsWqOKCBD6rP6utESqPFlk0W2xctPWFquwlqga29OTUucjvEmlNCNgJ4QSA32pywcr+4KS2JFXoaN6dSnNK8EwKbNVTloC+khYa0ULW5oCD/09q50EMqcI7Du1wlUAzuzMSeuE8mKoz6nEUERisXDmGJ1Mx7hRlUfd9+UTaCfXW757EdT3EfMTvUhpkRXhSqLgo1sGsdP/+24eiWSonBYyyBIi6vNztM5VNOawLok1TVGQQSDqBKFChnAdAnmHYqPq8UdNFuSgjE1oqEnubeuljpmyu/F3aay8kbdASomkEXbhgt+idOcWykOdjL7/QAizY5cY0St8brWpCNYfVWZgOb71WQHITCvS2Qh+SlaZW3vAddopwnIzXM/+7AqVG+hL4kMv52Gj5ruZL9VKJ29cXhh2va/se8Ypzt8xFpBNjU5afCOpOnmuD8PM5u7NHEdhIp9YbI8W+Fgf/mxBJie9J6fJI2Zf7PuFj+DZ1g9yQplt1LODPCZAfyQ6KPwRP4XTCctWe+YEgGzeflhZIULu+SJgpsCKAvtZvv5Add6gxgPDZDTe2X0TKOL+gFCH5uheWwjd1A5aSr/CHOosIiClWzf2K4cFVAuh86pSfeVbSaLtLIPXcbOaF9w5fZv/JO6GN62EsQ9/FbNvr9K2gmLgLMlor1TyYCjHAkbOKwE7QrRuziigaz4h7gHMFtm+kmHHXRWFRLIGYkUYD8CgfxJGypxXuGmfIqE2PMSfLUaLfsoJSjhqMUajAlI9QnI18K3/cyJjGFXkAqUKbuS1Yx1D97NzM8MAKuTOWc96QhHY0HiOLGur9nGuKB5/XYFMQfMwZe46LGZ7LzfKb2N/4ET2cxJ325I2965TV680o/x+afVh
*/