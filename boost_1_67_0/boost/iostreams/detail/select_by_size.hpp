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
GTbPR+XQwjbawzxKvGOEImjdOtWj1kQAACz/074Lg/kOfmS2+H7xqWLm9Ni75PxaX4xA1aGadXONwuUUYmJWuokivoV6IcUFn1OSFnPQmLJhZsVOCddb7iLrUbZMufZEAyD9jvkIYc21EtpoaQwWF5kEkyFFEYU9QGlCyJ/sO3x016cxiQwTs7UUyKovh/3/eNXq9O7L9sCLyZb8Rvn5mdVm0AKXH64oulwhigBoRIsNX0lTfGjs8Z85186nCBo27ZzWlMH9AfyFpQEB/H/9wNj5kLm3mMGnkCDZ0UX/2xK0/Xgg44IFvdvqXSGxhWZStnGAK4y91oRCknWKNi41WeT6HQCzdzp1dbUEw+F3fdeIOug9fUFvk+9YlsDyK/2wcdovjHTnA9ZVkaib7u2nm2hDIJT1mVUOprgQMUYFo69FrtpAWeHAOyM9g3vvC5/qhcbNS4ldyFCRW4T6qOgEaH+KjxkN6b5PYUyChWRdNIXl5CQXxVBVEVt1ZSh0pCmrRMa1dCDGieejAoqLv7a/dggAStSd15WFspB99ySMzm4ExguVVmUxsz2UkBaRz0kj3tHGv4zUGjM68ufMFMEyOMOJK6kycrGlNYQc7aOHaxaOzRJlD1TtTEuQnk/2MnnbH8kJRf7PPsbjnv62DRr26aO+cjbvbCX5eNyOD/KuOqtqPrTbbuXtCDnOSgOMrAsqzxcQ2Ig2x6ShDdAOaZ6nJfRzwSwSJ7HtWNKt7UG0QZkbc3bf1wvmMh3BbPmlnTLfa+7qps7AuiMlbPuy2GldK0MgNUyra2eJQe9NpsLHRSnPen3XEiHrCMiNtue/nf60G2puU4br+IEIgJFpPtSxleHzeCPoBsR9vEG1PdFhhsC+mnKEnpNXoTzDkoBcjZVwik0x695tOOs4zj0yQys4L2Bzpiir30vh0/Hg25pUpy41b6S01a7GsKLYcpWKik/X3l+dQHaWlxLatSetAmBLsM6ioo31nPTvzfD9wbpOF/n80bINqfV5AgBZ4v0U+rtBvBWFwDTBrQMyE4k9/aorY7TCQOWlrr0aUMaCY2IVajt91e2NyvLJs2AiZ0pb0ya2F629vU6m8H0F9YEEayfhHMbBAjA8K6rG1IE818TpPn1xsPIlG0OffENx1R71cb7/MmdsFaWXx/V7S7p0mXWhtfLicIebKl5bmzEqc/I/b21wDws7E0OhT4nsiD57ZnMzNCkeePgS/Y30e2l0q9pCKLPDV1GHQ5pod+nKsxdrBdkxYp0QOutewuyGVKapqK3iLMobd+92JIW8pRZIO7fuyhuMVpcrLb+VMmpEWUklL+QRhq04IYCGKbUJ9bwQ3iQ8QbIVaGWyX8NSL1XONu4JmG8K1l7980ledL3MrafVBrSCC0ONoGQV/0s7BnfhtI0XY+5PrarNQqa70ixjqm+5uBTgK8o7ZWnRnciBXTN92vGIXcx+ACyoLNtB3CMkf72SBvVx1QQEeSK5Ly6SIu8fQESS2dZTR5HdsvzqPQL5gihrJxbCxZrJ1AKVoVjnkgnhXpwIwSlr7fOpp27FN+RmCSScDMFPKXBOmt176jOm37+mP1LfbM0L1adFosINUlWof269vws4K+dox9l8Ys+Qi5ZOaebAfHseouUSMCpsPbUNCZAFOOnQt4bZvd2HbHZFwPffF9ZqeHhHWO/YNweKLqQBP7hEBgdJLCP9WETc82I24Hh7GmriiXg98oHKYS4/LP4WEfDaus4Pxed+VykTMfRV5ZgjVwQg0PgUsLjaCd/Yhjvt+kZtPOJJj5XKiBRvmxBbyPT3x5zQMXgEXvGSMbFsU8+HJ0yobZAivrb6wD+3lUmAzYYTO6HPoE2FOJexnWWE/EknEomsb1edu4Y4Gn0amYFEAJIYinxUlUjz7vxeneODP6JqWkkzpLltmo3Ifddg4GVnBiU+Ta7Y2l8j9ZzBbsoC7lMPh3pwXWdAmv/xAqjPAzLZT7h48FC694uDjX8F2PrZLiK9f5LVPYTPBv25RBfreKdxLPAvNJPkYdHYGDkPsoBs8BWpTob/z5HpVl+xvNYA2x18Ik2w5XxoJWPRGLQ0Qrw9iF1DIjcp8yrdS++rWjntDujcPSpY6p/02lvT+cfyUHKdpTD1LAabh2Ub1NsSB4tqe8mmT0LnT3RZ9tsIUpweK7rmNrIZVn6aQV/ErFYeMLiDMAIngR82TjDcDXITF2/XMsgV5DfxMYZNCfogbH5GUye9CxkLc7M97QGFGh32yiDXfdL35Um0jozogmtkeCYvWBGQnRHrrN9Bq+0rljBiu18aYiNFUnecuTSWQXUTZ2QwI6AqCvCb9y8iEJjDf+NEyQl+bOUt73GcSds++aE2jbG8xPJGh9zSIpFiCTI1MXAMZRVvKqo1bKJP7tGxWjvzXS8hNJyB0qJmDkFHhqm9eDUuZpuhMzNww3FpvIcGG2ZDDxdfge8BLfkJstYqhwr2ZZwQo8WyzRfYt+MVgiyBMqDQPZyqp5XDIZpth0vedp7MGcd6ia4VmxVGT2/Y+I+IiXfNexKiHOEd5sJdfKn8Om+aX/jTLDmR+cTCELTy5tFQCU5nGMx2yf8mKORHGsgdb+PvfXTeRffTMt5hloFrti7+G/axd9pD1Aq2f5eKpf1i5sLC0SF03DjgvnRqzu1GXnRwZzcuB4yNxjyXTb2GTwtDmxK8GRWJh4MxmYdRMBsrPRpANVa3PbctE188DbLKrrM5OnK2GQvnN3/5Cl++YDaSWNQbRzyoG9md7S7OmeKbvejHlT4WkGwr1vG/tcO53F3jOPRpxWCLRO9814IpHjXrKaGisow3mGm5cYy9T2ZHrV9NNxrjs8hs5IzskBKUsQZ8G0hKVVSIxi4MQBOpGo66SQz8lgpbFQEOBp6YmrkdYoTBVuO/bhGS6rxZgJqZwIT6yJTxG5IbV6x7pFT9hzrzPUJtUnD20unUp/Pfyh6fV1c8GRw3WMh/6nC++mrj9A2VoDqlWRrbx/loQzeqHz/cH+A4hUZRKhWCVbXDicSukWGCIH2hwTwq5vaUWfExjtRCnnujd1GiQh48rTPHqICJez7pLW+wvCga+Pb6j6EszQyvd4K50OuOhN2vbubkNYgtrxUJcR23krBVwKFkXgeE5Vt57o+XEhzUh/i02izkRjtb1HbiergUOZN7Ra4+baldkpb9JVEpKteytniSLg11Ccm4A6eCcptV90b/Fp8UasSDVec1H2b1kzOYZenBLmilI3bHZ4Ab9FozuTdL1gHJe84nr9cMJWkT9ogs16nPzLDrbKiuOyTnqaTk73sbn+wbXYxwD2npdb0Qc6BtWZJREwsld1uUsmhQeYV8cLezXWNXSUOmOR4ujz49qaqPo8kOQQxiW1JVPsyQu7f89FiZ8sWH9PwzHf6hTm9RAfI6TkUHaakgh3bjtL4p+TNmZJ87CIwV2LlGSkiXFFG5etYNgAXPM523ca8+bn3lHxh61iMqhttZ8cEpUVMdFxyMP2wK3tnI6rT1lnHRE1Z6pkjfAZyFfx+laE297hJvEB2ikWfkw06D3MdtuKNDBrAmn2UepbI9/5aSB/ffHbe4/mSWPftyAq46H1n3GkQnoHPzrjqu101XhYL6yPqxWrJjzwCzKDVOtPv1PVPpQmv0nXI90bouNYUj0itxd23ZYoazojv9AxdWkxK187NNNfjw55kzrN3OPJuHwmnh5Tj+d6o0k27MFT6BvQq+YOOiYDUZi2pbJkKh18EvbIyKlO1CinWrLTdtVWh8g/pty4Wn6e+qTbqj11S4PzdqCxKe3zjGp8Ek/lKFjdGe1d42LLKx2dIrwzM88tWpxMJlfFPXbbHFKfoVi6WQ+Kl4FOqCbytvzYa598w5A2WMz5CCNGRzv9T7maIjS9GvYsmampQrg7jrmnHVJG4KOJgcplCnp7JSMacd5e0My82u8YLdKxmhGf2+6ujhhQ87zw+TR+19ypmS3vkFmRPm9w6SpgsV7Xv1n9QtkLkeoMQHCTS6Nz3QFEQqEg+/nXrqt0QCMtG+tcTcrWJufmSeHFeebGopAqGLBOyF4lyN+fpyphQ6UglV2ZAg4Gk97iQl/9uDijIFdEkNZfp6+macWtMtingVkXsRoJolrGQKxo3SCWrMUY+C85QyoeS+yrAmdI/1eJ6uKKyuL5qbZpU1yTWJoJVA6yalQs0TcaktXi/Opuw3+naZ9EybGexsmedO3kmUVgB7jphkDMzFxcl6ldje6y5Bmat5oWThG2TRPrD+hLUWmr1M6jHTA0s4hkuzQKazQg9nX8iazKJL8ptAQLejGztvj94qXS1n7QOlnFgZGj66HDkePnXmUpqkjIXKgKHMMRauO6Cu9phT+/cSnxXb/BzP6RS4SCT7t90UIN6BtihA4Tv722UHwZvrE/VbIN/yJ+XOUg7/YXLmQxTz/Mdb6ZRKzkCDLPx/B0BdhCZZOGDAnMnquuRozwU9b8gVOm7Cd+dxkVN5ToOanhvXIjvnsc8M08sgEYqoD6i97kkiHW7vWVoqvQdzRCzm5z/GmYisP+yItgCP8ctDH4EW01PUcfGcNYSqpltGQuxMsWQDZfJxCYpz/FAKlNSqL2jed0OH8AN8PXwwqVwzmDzTUIZw0WbrNoqGbUaazsVlSkgABFLPxmYgmKSLoXDOy2g1rD3oFsU1vHRnqejnkak3PlvLTDPsp23l5FcwcqbXUFAfZ2E00D34ZanW5EGmRCm4PcLCimuV8ea3UQC4m3wUq72iGDzMRTxfj733/pKNDKPwVsa1boh7+qgGO+dDt8/jg0K7+f0qEasI3tux/cY9AbI3g+DPynCvM/RvS3ebxvQZpkh5agWH+7ZkQKbB9jU4zBb7wWej74xkkwvL9/eVlIEcZyHzrbGBSYtHOtopESHL454BrjWMyadUIoNh/+XWyf338mB1YOoczdzt/uvtDPeSkq3oMsVq5wWhCUyDW4FaXa3mWzH63QVYQAa9VbM656FNVcRwTol+K3gjDdrpI6WgEFAYI1ZTrovlmZ8hSznJCLDiOcl8ViBtl6jtoOu6CK+sO1j+xnrC2Xpkhr/toOUe/axU4rpHpkKBREEyfx9KUIq4drTmCRrWcNSAOhJMjAi2sZOjVfvxYUM2MX3+6BGPwLQ8tV0NmubTpe8lh+oqr62GqUHSxOqB6mHLafhG4EKuC/Hp/NusqhbflzSYbH1RLKAYaYu6WyzCHrrHf2IGUoPkvfpAX2cX8XYJ1m5ALxuAaFwwJit0hbD2rjhCuV+49PKhGyvo9xoLHnI/G+S+Cll2eXmfGjRZ1I4MoqBmn0Np9ZDjM9ZCqqkPcA+WoM+qhOrT2Pemy1OSn/J8qR7UUhTUY3otJNu3usSEJ3gQF71CsSuV7TVnhzgiwVIxw9EnfLD/24qAUQyBhuxG02bNpBd25YQRRu69X5J7u6wuNJdTFSlP0rCi8qVeE1Nds3hFa4xLhM7v98YYsrsMv/P8j7gowpiPcb5+hiexjddKqCukdt5ksgJaqHlRpQiLC7dLCMgLXbE7hnTbNUH/EbQrLqfeKfdqVOOwJOKfSdVwhDvp0tmOuxd8wvs5m9EM82ZYo6Ay5TmXyaszBcOFzQsl2/cZ5H7bcW0xhjSqdUd+EQKnHGFn8Ojq5Agn8e1CZFiMPglklAmRJoFftcYrpQPPTM9RWLgMgyt3Ky4uLDsieuz6QeI94h14v3HbXWNCHeF0chq4i57paUsiy0TzhBXYt4ecFFXn80nPRluU9r50ydVQ87vX06qucYypBZC3PYcMI/zRelqycnD63pkO4TG1Xm1ItPxiaAN2YgOZPRGFdpNnqloTb61pQFfiTsfRILzIQe7DbXKu4oZIaomUNNO7CjfYiVRMwr+nm4w3cecM2VavVakZmMqyBfodR/ME5Xk53qLIL9+xl9qZErXjsFP04OYhBtxBa13yNij++EVavGgbcxqTiDOFcK+sTfWhYj4hnuW9f7NcODtG8BA5mqMHAUGdCkerLUs2HYNsSSvm4ns3GLrSYBKwGy3tIo1g4mG7PhMRL79lNHm5MhuxEUqaD3WaBiyZir9Lja1S1GuSPlGiD5i8xf4r6p2nnHTOyG2QnDesUVMdLjO3TwgFB7bkyR5WzcWOyg2dtbRatlVbiFu2IhDfRq2Ux6i/gn5C0uZ9UuuEe0wN3973NTQmuaptuw5xYzvwUpVmk5GVO+gPJdud1IyCkZNDYmLXmwp3xs0VCwxBDv9gRhOME5sVLYxIKSpUJSwy39r8AylmkTddTny2Yzy6R3uf3L0K61wISB+yWEY7gbnuQ5495lglsRn+IT98aivQnb2t3aiOcYVJE2bR0lQyXRBKrZt1QQ2TtOw45ArzrKYouCL/rAUVOC8ufNg6bCzWTFPdNLUXKLQtuj0z3L3085v6PoYuSgaWbZTCIuKnNogTw4vbWskJMHj8x0oGODAVdF+eg+0eVtXC3tIWUpuWsulpvboet6KL6BuyhiuRTSLB5oS0oeHimCXnVeWT+bxlkZRqAh5reCMb1/qjxQQrZQjdSgvMvjFj+l6a4qe5ol1IuhlfBxPbxCmKQBNefaTwBJ/XU/30MjgSTQgIzm45jywTFw0labjtgeN7qeVdYt9KReJcaDDdIqtgjrKQRD3ke6qoJxyAiI+VVxMJFiRO92S91zbutkMFt8EXFPtRRaSgEFNOnBoeuXmJsDRkOx1lS9LKqYesjNZ1hldcUHi8BvjzD7iXaulYtmCmxBM2lXsSzAm2Vgv6eQH897JAPIpUHWN36ntSxKgl8x0scBxQOTJ5S9mmtaHdXvDk0wG15XR9zpNd81KdVwNOsZLZW3MTq2rFtfTk660Hsdmt+DKwU85nEcDu2drpfUM1I4WCBsvXmjOF7LZC2csv4YdLU1hShhSLNeK93eXERUskHkG/VAQem5s98TMlAXDnphgVYKvvN2+u2GO/A12PdxxHSpnjP9goHT15S36MNf4JtXKt1aMVlZVO5edsZ3i/bVsmoEwAAj4nw6Bgo7nMVPNsZs6ITBTrRuS6zW48BLjMZvERx8v3PHj7OUlSgn0qfWfieDGNRuifdrLACHTtdTVc0jIVCiUlou3RLT6jjwdIBK/56Wlh2FYzA1V12hHjmDl2MdoT8kbfJycxZOsxYuEuV0ob2MDJ3WEoyqXtaTGeZgl4ZirQSq8DErVWbXzVfy3OJBuRIXLHkMbc3+aptt+98LbIe2GbLma0k3sI731lTvNUwuwCwZ4nsuU0iGzHOajAL8py5nTPh+BYBkpPPwnBeNHI5AtwXWlvN7fxwEx6tSYMbMGoS+alqvQCFhoGmt2qAeKBRI1zbuOHQ+2Q5Zoi0DtW4ih4nR8s2rDSTJL8NjBjP6mZf1merwWQaeOchLnvwRxrTnxEntHDjjt6wRZ6ZO0WjmhPgB9sTvU/IibctDgtLupuQwY/MeBanCPuDi5sS+2vOLpQ9ciQodjnh3Zjx4WzhS1z6L0diYNHk9pH5L0eod+92b8yGtTnulAApvwNwQAc77dvcZkv1oJ/z86vvMF/rvABJe1Is0giJILCyL7cg27hHinJd542+6wJLn53lsXbJwhA5FRABGFd+7zIZb4WBH626lH+E0VGtUDiOsGJORssmT3jUyOQ+TjE0ZTUCq9m+3e9O2LzeXm1UxKw+cPOrd5/Ks0yBy+s6s9KxgIwQvlJbCGU9T2HoPzrM+hUcvjNvM5miSChf5PffvWrQHAw/etEU+dSv7P7gO1hMs4h1vcpfusN8IlEkrYrJ0tE+e8iMRpTKQNDG4GpFEFZOfKb2DC/P0hmjTBDkKjvZyNu9b8VfsO2uTE/ErTpr/Xb5Pc6l1f/OL/Vu8cx05+drnb/6dkLCBBSoH3oWOgP/s5Jn5oFfTnSEdAPTUW1yy85/Zzwl9vRa522xrDcXz+iFyYVwHgCLUvn8IwfeXKCD3YObLsLS30p5RpK5J/z30TY73aZ4l25Kj66B/o8hHo/Lm2IqknbBmVT2oIfP+SYlpffr7Uqwy82UZMCcLpYVBrpULwsraJpFRRQj5Y0isfJ+nB2j9ls46/gAmfz5JKvHDl4Vz5+Iu/pOptLqgZ87TO0x2B3oSsjbZa7CK/VHssrBj5yNjzbvX/4VXhfbjf9yuHlVdeZZhVph2HRESGPR48ddQGHQh4vYbiQW2XxZhGkPWZsTJUcUpZM5jobvlFoGL7bYWzWWg9yjsGyacYaUgSSvZWPy5GENhFO7vlb5neFQzUPthoXPOaHlCtY1w/bkLMQ6mAWSq1tDJIQ2vsHtJ5PMKdirqz8ZrgpenGGLsE0SW8s90ngLfuN6H3xus7t2k30Fww2lBbCbDvISq2HjqItrgMrZUrG+b9pbSETbTNw+08IUzS/+yYpy/+ShSDl6zCJzOSJ29SWo0dT3qWVLpTt0ns1QrU9r8UU5DqLkHqBQE5V1y2sZOtrfJdRtJr0Kx75T9+/7vHr/8Ohcfn+WiY7+ogXsN6/2Ka5vAQ9BxmPyA4s2p5L1XcfbhZ9WireohF+C+ABzPtUunYVhGk51599IVRoRy5nwEesvAuX3yfBX/TyziY0PhBQeE2mZ50h06PHW3ykD5wWknKsz1D7yOY9mOnAL1o1UqsSHAsYJcCJ2jsDiqlwMd2mP8fzRtJzakHA9McTNJAybVpo0zIMyhDn42mJlpoTgdTeFJ4TXzk3dZIIu7IiPYjYMtkm2aZRP4wjI63FXtxSyVJZoOHsJx2fWJzavjgsE058TIZNF0wl5fo3uuRQGswVqtx67Pc6/A+w8r7LJgrrvwO/OkDQ49/VXFnyL0y++NkiOxmEWPoEgU2B+STJXIlNtO3iA842hn8NLzqRUejG8UKCQkIL6zfFq01viVddiZ7pZfWy6RFimBZSmiicpcw35uBo+C0gkBcrZ0G1XBLtp2KTN64c4pHPom/s56rTttjuJmqy9InzXBVyTcOvP+worg0OGlKwKgdZrWrq5/onlu/mFzE8vRItOYYbRc8sbrHzFtu3O6PXHhekU4qKDjt6u3otkjJxrXu1mOhrP//8+8ROsNrmI1tEPaXVDg7+Kyppfkq3dwCH50mKd2g0wHGhKLqOdoJOcDPsHl1w12oyNzvzvlxw6A1jhPwPf2HAMNhF2omEXkp5YuB5J+d1xyIuQnx60PMfGBnG58vXhTPPY4+LGAs=
*/