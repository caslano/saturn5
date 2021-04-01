///////////////////////////////////////////////////////////////////////////////
// expr1.hpp
// Contains definition of expr\<\>::operator() overloads.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define N BOOST_PP_ITERATION()

        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        typename result_of::BOOST_PP_CAT(funop, N)<
            expr const
          , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
        {
            return result_of::BOOST_PP_CAT(funop, N)<
                expr const
              , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(*this BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }

        #ifdef BOOST_PROTO_DEFINE_TERMINAL
        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        BOOST_FORCEINLINE
        typename result_of::BOOST_PP_CAT(funop, N)<
            expr
          , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a))
        {
            return result_of::BOOST_PP_CAT(funop, N)<
                expr
              , default_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(*this BOOST_PP_ENUM_TRAILING_PARAMS(N, a));
        }
        #endif

#undef N

/* expr_funop.hpp
yO5bqorCSUJWDyi8un9Mlp0ZO4VVe/TbOOoPLDjBRAZg+qhvx04Pr0H8GLh4GStovkx29nba5VRqVMjqZGiPHvv+ECPlBaGZTxamrJLf0Rq4QF4LUhuks8BrWe39/yrQCY9dB6reqhA22SyNC+KKmq0cuKxkXVbAhAoHYJo1J2nh2biOT2H8kpq8psXeRMzP3tP7gs4JewIrV352G9wXgwTtT4/4q+ThtYK6/YcAD/jf13iqPu9r2ZX8OEWjLmXScBgbWYJfRl/2XQEWWBOlzMHA3V07IXH44WIA0hFdQGZZscBYNQyeY6A5zYUNrLFyMto7R0vaoWV6QSomLtjBX1/4Rfjch3f4Me6LzARakxraGp1q6+hmiIdBv8rPxBxLRJg1iAsIYgM631avlPWeem9r+Um5f3fPt3lRqGGtSMbGxDJQA2WBrTNmGEOsi1adv5tACpIsjxhonkfas8hzNU4gLtZU/wxpfczO5ywRTyrQM4w8Znap4suJNepGJBwO4a/RX3KMYWk4JRizeykkb3gsE+5ri1XITFIElQuYJnYLLMi5klminhm37g==
*/