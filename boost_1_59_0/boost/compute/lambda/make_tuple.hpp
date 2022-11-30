//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_HPP
#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_HPP

#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/types/tuple.hpp>

namespace boost {
namespace compute {
namespace lambda {
namespace detail {

// function wrapper for make_tuple() in lambda expressions
struct make_tuple_func
{
    template<class Expr, class Args, int N>
    struct make_tuple_result_type;

    #define BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG(z, n, unused) \
        typedef typename proto::result_of::child_c<Expr, BOOST_PP_INC(n)>::type BOOST_PP_CAT(Arg, n);

    #define BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG_TYPE(z, n, unused) \
        typedef typename lambda::result_of<BOOST_PP_CAT(Arg, n), Args>::type BOOST_PP_CAT(T, n);

    #define BOOST_COMPUTE_MAKE_TUPLE_RESULT_TYPE(z, n, unused) \
        template<class Expr, class Args> \
        struct make_tuple_result_type<Expr, Args, n> \
        { \
            BOOST_PP_REPEAT(n, BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG, ~) \
            BOOST_PP_REPEAT(n, BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG_TYPE, ~) \
            typedef boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> type; \
        };

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_MAKE_TUPLE_RESULT_TYPE, ~)

    #undef BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG
    #undef BOOST_COMPUTE_MAKE_TUPLE_RESULT_GET_ARG_TYPE
    #undef BOOST_COMPUTE_MAKE_TUPLE_RESULT_TYPE

    template<class Expr, class Args>
    struct lambda_result
    {
        typedef typename make_tuple_result_type<
            Expr, Args, proto::arity_of<Expr>::value - 1
        >::type type;
    };

    #define BOOST_COMPUTE_MAKE_TUPLE_GET_ARG_TYPE(z, n, unused) \
        typedef typename lambda::result_of< \
            BOOST_PP_CAT(Arg, n), typename Context::args_tuple \
        >::type BOOST_PP_CAT(T, n);

    #define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_ARG(z, n, unused) \
        BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) BOOST_PP_CAT(&arg, n)

    #define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_EVAL_ARG(z, n, unused) \
        BOOST_PP_EXPR_IF(n, ctx.stream << ", ";) proto::eval(BOOST_PP_CAT(arg, n), ctx);

    #define BOOST_COMPUTE_MAKE_TUPLE_APPLY(z, n, unused) \
    template<class Context, BOOST_PP_ENUM_PARAMS(n, class Arg)> \
    static void apply(Context &ctx, BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_ARG, ~)) \
    { \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_MAKE_TUPLE_GET_ARG_TYPE, ~) \
        typedef typename boost::tuple<BOOST_PP_ENUM_PARAMS(n, T)> tuple_type; \
        ctx.stream.template inject_type<tuple_type>(); \
        ctx.stream << "((" << type_name<tuple_type>() << "){"; \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_EVAL_ARG, ~) \
        ctx.stream << "})"; \
    }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_MAKE_TUPLE_APPLY, ~)

    #undef BOOST_COMPUTE_MAKE_TUPLE_GET_ARG_TYPE
    #undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_ARG
    #undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY_EVAL_ARG
    #undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_APPLY
};

} // end detail namespace

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG(z, n, unused) \
    BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) BOOST_PP_CAT(&arg, n)

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG_TYPE(z, n, unused) \
    BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(const Arg, n) &

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_REF_ARG(z, n, unused) \
    BOOST_PP_COMMA_IF(n) ::boost::ref(BOOST_PP_CAT(arg, n))

#define BOOST_COMPUTE_LAMBDA_MAKE_TUPLE(z, n, unused) \
template<BOOST_PP_ENUM_PARAMS(n, class Arg)> \
inline typename proto::result_of::make_expr< \
    proto::tag::function, \
    detail::make_tuple_func, \
    BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG_TYPE, ~) \
>::type \
make_tuple(BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG, ~)) \
{ \
    return proto::make_expr<proto::tag::function>( \
        detail::make_tuple_func(), \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_REF_ARG, ~) \
    ); \
}

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_LAMBDA_MAKE_TUPLE, ~)

#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG
#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_ARG_TYPE
#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_REF_ARG
#undef BOOST_COMPUTE_LAMBDA_MAKE_TUPLE

} // end lambda namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_LAMBDA_MAKE_TUPLE_HPP

/* make_tuple.hpp
JG2zbNfKvQb1LTIeeJ/wI9rXM17Jxz55iIoDMIkHAiYyaJWmJZFFWwnHkyR6zYTDO1ql2nHxANcpeqd8dSxnKydgAsDl5/DBzRnP+24e0ToevqQbaAvpWIXita4ai0GTtCtrS6SRWAHVKQavcY6xdAwNsO4OxTIyyurkOTpwNV6NLt6hQX9X0bYWOdigIx36xVdlMHKty4gjFidR+gflq7goZ3dXyBm1V8LiUE7DxtDtrRHKx9lb6bWM+Torb2muhhzela/FpMtuYA5nHDzJSzQh3rseypcp+NEMngnaATJywgf4qsPrqYTAvXL9Pk9gTd7iOHnwx//5n9BlOvvpUzpfEJlTIYwJNNxDkHC9FgXQtm3btm3btm3btm3btm3btr/+X0/eYFVleCvJPbX3JFg3Ot1fRfMVS6Hctm3zj2vtbUDm8Xb3/31sTrO7z2Mgf8ZQYVCYci8OOJmcpJ871px6rE4pHEeBh9TpZGoqn4Qvh7ef53er76nvP7FKGVzK4MnKB6uWStZX469EUR/0uo8TO3c5wlAGnMidPo2HE8Ll8/o9AMp5/ltVn4er1/twwEoEnl6oZ3h0wF0SB8KEYyiBiyl9TcASn3Oi/M3V1ylsSGZc7cNorUbi8/Rw/i/4e73drzPEl7pCxAdziS6GGHNxKMP8lwkKh3x8aZCi/mTW/KMPWcuRlCZmPoXRDXeCkZQhcq0zO299AgsYts4gMjy6VjvWEwaDq0iyPusx5TNYHtAEaLktRflQhHoOE1NJQvNyzbGk0AAHfalomEDevjPv543tB9kfcqlOWHO6TuFTMjdDMANHO1BwK8m7gSXDALPfOOUb7KObR/jjwAt+5TvZ/2v/P3z4+jv+j8V5D9nry+ZPjAEX8PHCGyg70A3QnLWYrJihdXX2rFfePt9n0KF+AyjsxBgg1yqMyjX/+BVq0zvreznQCmBiF4hn7jGnZ78xzfwiAjYVz2Wge0SosliibOWCN/U3OQQDWQi1YnAU8/zlj0NgpWqNTU0cfb/Zulp7Of4e/9eE3HR7/7Gp6PQaXiUqrI+VlDmaORNbhyqVHBgH1JGJ4bb5wV65MzVrxuN4HwOaJQDElA7uz5/jbXAbjFF1wv4+77Fzrcj1hhkFUYYxAB8odZtJOzzihPgeN2CWtZZ2GCqcgY3WvlEfi94r8Oe+duWpkq+bTWvGQg9qeCgKecumacsdJvs734VCv6Tjhd5coeF0AskUczruHBKgMJ9Mup0cGB81rzhhyDIPqbhWuQIEeTmDpJ7NWWg4SxkDjNuNZSdTRPJTq9QIxZ83PKpsFttLhJiXVC5S/33lxyVHnjr/H/L/dMb8v14+tdkvXZbn2nt4a4gvheg/GDoCeQG2rRWE3b6wpo1gD6uBr+3t8fb0/h1cSnPJu9zD+DR077qpTn9O+pBDqwJla3KRDL2rpWMm7nErckHsCoZUSNXT0Xn0v70szmcOOLRbBsuZ8Nqt38+UKvNEkCEFfg8477G8vYb+W8m3O3TR3aHGsmXg42rI3XgNnmY+4BveyMV84Uyj5vaw0GUtpMsxzKELoxUwi2/Z6xhtDnk47pNz5UZQjApL6SLYU2wGTmsNxOc56G1p1u84QM+aNZfmtm3aHBjWF5OjFlUCoxR5ZfQTKWkY5GylBwPDWWbJ0LSFxxax2+IYd68WiinxanSnAsmdPDVT5sxgOy2RFTYBqrzDf5aQ1Yh0B88w2mHrYuiTRIvNh2GBANHWq1MP7CpbzRGBYX5CkDAtPZ58nkAUFwCDTTP2wOndA5zpZKwWzOBk1qguAQFYGdNWo9vBPt6jSLLSs7VSm5BgdgB96YaBOks/8PT/CP7vcN/XxdP1X/B/2ar3XLHW4K40qdYWOqeenGn0wltVmFaDFYX8PwfB/Ce4VcDHkST+Y+7huUNsFhIyDjGApTzErs2IUZf1DhBty8F444gV77vYbn69vzPx3v7/bizpVej+q8qJa3X3X/pwpSlspaZ9wJg24HefafzoNMmzOWXh0Tb2GBPLjd9VutkulzOgGQ5Qw6U2RezGlf6CPSNGIh9JLlhKkxV+0G1mGxEMXK5SfLvFduvh4/73WI7PM+I533dyndBKsWC5LloIbY8DUhzgYMj5TPGre6wtaDKwnUxxXqqtZ823xJF9PbMh9Xu9Jlho/stM1ZS07n2NmM18n8kra9fysgRsnxwm6MX7Jj/FkTcnj3eG4nJUOM3Ei4eQ/png3QnYoU3FO95yQlX0kBxvbTlD/CgVbZZXo2I5FOajJcw20Sp3P1Jbj37Nw2VGdYp1cVhrum6omGpbvziU8oZLQz7zzsh96u4O5sx0+/MBzv+FzFbZ4z2YoYaynclAWDYyHnmDdiVxy3xBAv4tNcNMyz/l+/3x+7p6XJ/fZ3bITptVi6DLZR3bl1KIFPHeOeJjPHUnrRvMwTQnCdaXUK70N3d7O8aRYshteH2+ou3zj0hfFp+fHcVBg1vV1MBYrLQU1cI/0o650QVJttdbmEaWtxrgiehZlkY5PZ8uzojNLuDkNyueY9Y35WtABu4LRcQG28ANFLGuGTYLnrXuZW2h7qbkqQWiJYe4Lzo4Po8eg8Pl83s5/sJ0jUm4x7jB4JoCC5WQNWA3nnHl6oRDNQ4TEUSw2xKleYP1lteoAMD0IzBY8qMkNiazCW7Ij1ORp/aONzlwzUxZNL9YZXKGVWdO+I2IDKD8gkitfFgk3gfXggrYEd756mbAaX+LQHqHGdIgFGWrQNSLC60w7p625gUEJ0rJpYgnBPmA4MpAMlS8FvfUezlMxYD6VEsFilPYYlQJlLTOoIj9yU8uqAkd7z784of8f+X+75D/quV/v6bLaZ2dWkNr10LedwXRploDy7FnByjX68YegKHNa7I4vhfZ5/M6eVu0rMwelIrbWo/q6QjWLvFusMY/MXdFzQDpNWxCuJx4UE7cfDEni7Ovw33izgbX6wrUFSFyz+8hFcWLtifbz+mQGnSJnhMAu8U6BuzZIk1FmTj0RQpZjGn5CH4/Vt3t5TS3RkTwrR9qvmZKngICNd1uYdWLFbxHKUrUTZyE8tMLW3h2cp11Je9zTTOl+Lu5TT9Xgu3zefkLjQoKsTKwBAAmjaFdd3qhHsJ6MdR7EIcl+c6CD48/ji5WcZa0mMFvYMyhAo1ykBLJqQU5oSuIOQ1N2GS9uJMviXtQ5eF4JRytws/WGQcZx4Rz0NWyqMTamG80iJOAtmesYmclsgTPi5e9WYSLd0kg9Klg57GVinKNkBqmZjmVC0jNhKKEvjx7IU+lGd5lfGBWWyswwyyBQptXkZudCM7ekYqEtXjk8Pwfx49MTIGUWuJ7caOzwEp7+FHC8DUKpDOMewtJObh5vF4OJk9PP1/Zeyo6KlcR2o0pGa1pcqcU3EHJO9wUK/wxbJjlSzrvEgYvLoern8n3mbg/XpvNJ65DagFtUz+0dJRk7xeY9GUyMd0VrQMOMrKodlusjI40BHz+BdytrNJ7pJ2irYdZKHGitOPv0ei+cKFb7kBIsnKB6t6Kf1HsbbG3G21bHBhKyGjl+P4eEncF1TvQlL1VjzIKRawUENpyjroc23ReZQkGt0CoZy8VMik9ccslgF5CAqhnxeOjJOAp29y2+8vjM28RTNK9caSNnha/1IUY8bkmVwYCjQdJUGNOU9kJ4HcHCWV4VGauORkQUUPAx8h4STRvhqQXG+iInNRMKPVm6pcvL5mrJUj0iOFw2Zpri1+SbcjWMSWyLYGTnx/VgqREeo4yn1H8p3dtExiIZ27vbz6Hqp7o/pN4Owz/39V/Px+Hw+H5P/36fqPHNZdPlwbfHQOeGpKD3h4cuLpswc0e3pHL2+308x85D/g8x9O4NVn4kAnjl4bmANm+x3uPKVLPs3pkdC0hwGOAeGdQ1T06+RauL3cnb0cPIaZc5vs8ranYpn2Dh7vX9Zi1YVNQeC4DLpAJTiVIN3urOG12bby3yPNO1dvXzdPh7Ofw/mN8fhlXa6gMN2IKHKdJQ5pMJfyyIksqcGfMtNKOq2xftdikMDaD9wK+b4W0adSXu+tGJ6AFmCXegFdldcv9YSI4PCqDACbYYzL21UQSo5S3VquRRP0sYmEHM0WseP7jBUxaU5YxbX5YrWAcrNxm0pCx7QAyTwcqGGQtNsVwZLRpYpadxlyhrF6XaX6hl6XrgqjwBddcWMKai5cGnOk9L3xYpwuFzN5u9KptDWD4HAX+FoD9CBL1TU9115HoYrqKDquyuEIHvlx+3LRbKDEjme37+7fxCfHjxfN+T+P0ej2d7ymxvIVlmEOxdbPmDhzBtGnGtCRj7uNq02NlcPF2dnzl736/s85o70zT4lnK6hPJW3Hn+gxo3KOEmvvJTW6OVGuAPWAVgczHI2Fk9nA2jY7O3p6fg8vn9NjlFAawliisQo6bK6Ok1/CIS3p3JLHL9fLD0wH3H2jLmfpsnL4zV3H2mQMNrnZtiGo1nO0HwTR4KPWAEi4Mjk0okYyfaU60NC/FnlEB0sOjePSfNUTRkfaZPReoqLnNanIaOKsNRINQrE9TZjnHMAPTnmZu0BmIJLTLVRLB10C81jJY2kxi+FNmVqe3OMB5XGVq9S4nFpym9g1GUndMUyShjo+0Rv9Fkrs3bD+m0ZXSGY09eA8mDtd5UDPjdtalWy5gES9y+JxdPAXkuF+7vEyfoshpSUQLmj9TaQIZfeQ3De03MZzDCZdWLX4eBZ8kYqKAqYrrUu2N+nUzh8CV3kd7+3886v/ex9Pb1fH/g+dJZoL0vh5IfiFjs9Sk50eqd/40d0DlaYYMd26L6uvr+oiJjxF8TPC6w54AeR92cDICxx2pXeJh4YnHyx+gmfbVQJjuALU2UDuZlN6T/UxTV/HqCkrKxgRKAGKba3X2+9nGZB5HpqmcwDSJ2hTExXI/BxPtJv8Zrm4e9ympVX9RrdItSAGdxUokLF+SIOj3hT20QDHHDwWBKWFMTAXjCFlMYeQyxj2dJIe/5z/YPJic32QZc1944xqhAsWVEiYu8bhj9sgVVTT6AIu1zcEt2Ij6oEwIhMXRXDqMIJ7WEe5nFx3yfwix56Qmoy4wbo/3xmBhLFZt40CboEHHUTbzQY1Xqk2Us/d5mFnhXkcCnx1SylNDWDKUPhURlt5y0lkq7NZUWiotf6z+kSxFVq72YSj55+1FpPwppqos5vWCTL3qCa7x/7cA9AvSjXNkTSehH6ltW7M3I9anCPKoXru/FdXGj5/if5v5vSSrX53bIJy1dtEq0axm4aLcxjuxhs217D3hVKZDFyK+gxoXLtvrP0o4koG54sAI92+9D0GRFhJZcHJnm4UMubS5GOxhd9f//Qtb+zS2OTyivLfoVJPPvKzaKvU12V91DJujS5Yzo62Q/y6N18EqdigSFH3mgh4yRd/Kptb77upw4eIHBjADCmDLH22U0WfKOpoF2FsHd1NeRh4bZ1Vm2vm0Szu1Vuw0hzw6TBZvb/e5yVJ/zA8cunR5/2cApgTGcNKVlILYD7WeUGyYax57tGDqF0xGPBQTxxGVaoL4iYVX0xluQMxic2rdGSuM5GVKBjCEAT7heC0Xl2zj5dKGA6Jxloo1r+aQhujnRCKq57auk+XtQD19IizYZrXAdSq7T7tUU6b4NmJJtMD94nDm9iwwabxe53hcJHgpCq205dN2G3gZXWdFIJjs3pU+MBoZ6uuzJvrFT0VS2Q9LyPn7oP97/a2u/t7/8OqR/D7l7u3HlUEYrhVn1rXIhTF25JQ3Hf5On//zg12Wqblv+i4ziNHDhwX2joX1poulCmaOO4cpThuGTuYbGwzZkh2dHK/3wHNAunzORZIr5pVc7JNrtVxK6Brf4ELV14d987jeKIR7GEX2ePi6WVyfoVFQal1oJP8xWE1s+ZKXyHGKCi1W3eaV9tym+iGzLJzP4KqmR33pijHdDvAhoP4AKN2T4esT1Reupp3yNoKA4j82zzGNZpTDtYNlDt7JAvNk+gPVNIx/WQR0CBlM2w2Jxa/AfIf0j1COR/i3BDTbJy2SSXqa+8eRU5dvuhB5+kpjCNO8CZSg/+voaONJTcllSdgNl/jniaG2yhHg3N/Epin1oEzX8/7JRPB3gdfV1ljElWSJyvSFbmex1yfE9tGQ02ViP9vGbcllhMv3iey/J5A4oBbVTcmvkR85v9TVx46P4f4PSNoFyH0ubHmiRtGundu16XR831qR8GCurFjPttGX70Pjv4IoHU7uczx5VW1bpjtSdTxhE4u2sl01MRrT+GFCFu2aKZQWF0IevObHnm6OT2yQZzkbPuq7ZEevMsq+KsfHZ5JucIPEoYAuSY8LNaMGHc6Kt6si6efw39Gw5vEEdGpRiFzs6F0uW9FBK3zM5L4W1QMjLC9tsEFuYsovhJj8nnTzBf8ZqLiJ6xcqbRoDs4BVpJUUFMvbhOHYhdkk3ONFp5oyEdQxg6rEnjEA94sM7lWAZWmZr5nNKcBCAAC5mIRQR/l2NTdiFU/Fz0SG4RYToi7ohKZWlkMDGlyfGEbS0zUIWOyyEycCZfaLLqHGCINu86dMjZcSWt7+sGBEk6APXJjeifbXCDZPU8S4nuxuP0H2jbDXzSTTSXsE3MTqAHF0tRguFUi+N4N4O0cQKIypZbs3x/bAf4Hmp6/Soj38Pj/j/62O3oLj/ztkp9fr955KKtvEXG8NursoqZ8tVJ5lpr+/JGI6XABjadFi8c5vst3qtsoULQXW75ed6fP/OJSRHZYSs3W2CTWhJtO+SqxkuzC0Zukz/bdYnC0+v9FNy++2FZ8lIa640deeusCYUik4CujzBAEuu4Db4mRghQ/u/vpvdrTyXiqXM5Iwto2Pi7EVy1rsto4jzWgRXCncDg+4Gbm+Vb8rnAZgvUvAXUpnV/C0IPcx4BssNe85kLuNHmM8SfwyJI/J1H6n+uLiHQaoez7MSvnRcADLrxb9HbMpSwnGGubyFcNENFKdHGu1RW1oQSOYFHaCNHisgkUsFmegxzM2xmBAasgANJjw2lMFzDps5Snk4pDrmFV4TRhzXFlcr1aiNNjjCKNeDdLCazlJehwFRS49SjwU1PthRRhQzqNQcvd6XZyHRONwyt5YNjKy5FB2A+xzMZJKPsdnWsfrkIZ2KWGH6jH+P8Tnx46vZ/9X46zF5/5DZ3bsluWb5jCHcYvuYxMf+u+F9vnMEYPo5uHbf9P4C6hchvEuNThuFZQeIKLVJzRFrHFhMcZnNhxYni+BfhaYV0hc0Ronvd7wdHMe3++s+hHmo98TFe1e4xuBoQE/ViWy/2GsLlioCwmrd5af+8GewibDvmuwe7g5ejt7/mfdVeM6L9Y/8Xo3ogrGk6zUM/dTuXnhvsZ0Kry80sfcJj0Ys59zUVEUYJc3qNs0vHKqzkPgNyn8iAJNuJaEJZMMprO2JGDlsFgB9arVZ6LMg8k3tGUM/og5IY0Wg1czNammwDnRP0aIY+sI4+6imp7wk4b4joHm4bjQFNUdBbCDRS/gIGAb36OC4FqeQGq+bO0oo5YJtQV0wmpbSFkvx7Hb1fX37aRCiA6ebkEUX64UlJqhtTQuKOnxmNuGXA8uB0QT3E2E8r1q2gQvc/o9yb5zI4pymO8awFhl2TE4Eer0qk4qJGeK
*/