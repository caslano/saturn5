//
//  boost/assert.hpp - BOOST_ASSERT(expr)
//                     BOOST_ASSERT_MSG(expr, msg)
//                     BOOST_VERIFY(expr)
//                     BOOST_VERIFY_MSG(expr, msg)
//                     BOOST_ASSERT_IS_VOID
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2007, 2014 Peter Dimov
//  Copyright (c) Beman Dawes 2011
//  Copyright (c) 2015 Ion Gaztanaga
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  Note: There are no include guards. This is intentional.
//
//  See http://www.boost.org/libs/assert/assert.html for documentation.
//

//
// Stop inspect complaining about use of 'assert':
//
// boostinspect:naassert_macro
//

//
// BOOST_ASSERT, BOOST_ASSERT_MSG, BOOST_ASSERT_IS_VOID
//

#undef BOOST_ASSERT
#undef BOOST_ASSERT_MSG
#undef BOOST_ASSERT_IS_VOID

#if defined(BOOST_DISABLE_ASSERTS) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && defined(NDEBUG) )

# define BOOST_ASSERT(expr) ((void)0)
# define BOOST_ASSERT_MSG(expr, msg) ((void)0)
# define BOOST_ASSERT_IS_VOID

#elif defined(BOOST_ENABLE_ASSERT_HANDLER) || ( defined(BOOST_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <boost/config.hpp> // for BOOST_LIKELY
#include <boost/current_function.hpp>

namespace boost
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
} // namespace boost

#define BOOST_ASSERT(expr) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define BOOST_ASSERT_MSG(expr, msg) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

# include <assert.h> // .h to support old libraries w/o <cassert> - effect is the same

# define BOOST_ASSERT(expr) assert(expr)
# define BOOST_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
#if defined(NDEBUG)
# define BOOST_ASSERT_IS_VOID
#endif

#endif

//
// BOOST_VERIFY, BOOST_VERIFY_MSG
//

#undef BOOST_VERIFY
#undef BOOST_VERIFY_MSG

#if defined(BOOST_DISABLE_ASSERTS) || ( !defined(BOOST_ENABLE_ASSERT_HANDLER) && defined(NDEBUG) )

# define BOOST_VERIFY(expr) ((void)(expr))
# define BOOST_VERIFY_MSG(expr, msg) ((void)(expr))

#else

# define BOOST_VERIFY(expr) BOOST_ASSERT(expr)
# define BOOST_VERIFY_MSG(expr, msg) BOOST_ASSERT_MSG(expr,msg)

#endif

/* assert.hpp
uLV1kHUNE79KpMZX0/m3hC74d3KCnxj46C3EuVWAh89lf/RAgqTSEGfrQH5zl9S0DYhWWIGvXvmosckCLh2aSV9zp8kxHpDk3Cz/eHu4DHWQPV0MmevpXl0qu8IjRPGtTOhqFafGYFPqnl7EQGQ8lv6yh2rXzam2IoGy7y2om1hH54ENdD4vQTTW6F7R7nHQ859nmpTV0jy85Ezylb/zg4v27ya9jxhJjRyzSPnJ1A/Qo5qnRWg3rY/s1dmwyvXBDvl0rzqI87MbsHqkbi0LJ3U+xITx6wdo3Ub714IuWDSV/ypY+oGeLVhu0fksH3z3X/HzD1TbJZV4pEg2vIP9nOpkg3R5NQ2DpLBOi2NfkKraRjp9Jh91jZfrfY4F4/LpE4i0b+bIp/ntJ7M51F76iwXV9ifBpb40gG3yTm/0U/yjE/KNk3rUNY4aH6+D8JtLaoYCaWc1iCfK0G6+mZRlvoeVazfG1NMBEO2t/WGh868FEjxXsG5NXxBxYvDCmrK1OizrJDN+h8yk/ykk2acWTIfKQF1f0JH5MJN/rTgkz3aQdfsk/eUd4Kuj9LVIW/EDm9xU86sax7Ok7zYA3BhNa2nNSUV00HuuZTSZtUDvfYRt0kn2glyY9+cp3u1Bqn+cKetPd0XXFRDvbQlJ2eOAvIfouWUyYMImyacI9FTpEfU+UjZTC33Daejc5DNvpavS94rem8mkrZ2TZTF9t+43RVaOW2u9fKHGFPXoQbbs6Y9ki90GUV7+oaUd9D7CSfEUIZaJ2OYLiAb7aWN7Lvn/JkmfFJ3fDsn3Aax/U0vGT7e4j9TGKhqIvnLWvJaJHH1J6+8W2VTpyk2dGNjCPtRwagOD6acAFulg83eEacowuvVUxCvXQ3f4pSvyLafJKyL5uULnqT81zJRdJjvlQKSlzgNkNuoN8YtCis+00nkqkgCBdfKNrFwkf6KwN8W+r8DFk2Sr5gd7SqGFnu3h/PwmiP55reGnuuFHKHuSYav3PjC4o53yVNNdTkb1BRHvWw6DVbFgPcU0WrdGP2v6sU3Z8wLuKnPyASzaoH1kD9N3eVzg50fZ2fY6/35Q1r0QnOvL2i5/jlFzWKL3eu0gOeWg9ZdX7/X8GIN8creNW6P74wFlRa4BeqeQzZui9xHbFT+qzBr/kQ9EMXnos1zkj4jXfhsMwu0MJMsqgTjwlJ5PkjYyLp0uHHziIv8VwNibGne8AE+j6MzOr9S9oLDs594wWKXQR0sJ3iRb/uw4QKsg6AbbwO9aK8UXgiCutlv+F7mpymriA3bT5DqZmy4her/RDLoqM0mF9gIRWJjuewwju/qo3l+pyaYTSD0OAJRRVCZZx9zHUTRkHAEIaAji6SDFZyLJ3n3hJPvDWPYMYKYlkj6L1P4oaoN8r6GbNlTr76L8f0ZmrBdd9CO9pY/rTn6ZKv/aPmrMWsxo1Ogh+7Kr7rc3iu/Lm7xhIZwrbHSUP5Yaz0fSZIMyLNHlfoBmIl6rV6yX5+p80SZpdNla7w9obah6/lniXtH1+fq07NV88m8UgjhSB1mX3aROVwf00tuyg2U1H+0Y53dbaHJGf+lDUt4nfKAsRqrfVJktff3I1tThsUChhWxNXqQpdXOvkH46Q+8Fekh/uUNdCyGC4+yQT1rpPC3gkJI28NPW/TwSLqt0wHtqhyaN/6X/URYk9iXaUKPBJMq85UW0NSaV3lv+IXXrTkm9j3CkLG0pYtwtr/ltRVl5VSv1zlj3B2Vuo+VPNKP7oxvCdK4Mz7ho6RtyDXWIVjwqmrLNugP8Xxk4rxKtdJ4CigVLn/TTe0dF8cKa6j2S2Pc013mlUSssm6SMPRKUzNJ5+lT3m0j+IOfKp48=
*/