
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_COROUTINE_H
#define BOOST_COROUTINES2_COROUTINE_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

template< typename T >
struct coroutine {
    using pull_type = detail::pull_coroutine< T >;
    using push_type = detail::push_coroutine< T >;
};

template< typename T >
using asymmetric_coroutine = coroutine< T >;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_COROUTINE_H

/* coroutine.hpp
JCHxHPo7Lgj9KMuwCj59O15fbv8l2y78i7qR7RaRZ6Id8RvnrAcaljyKQ2B1/Xr16VXDrXkruvYO/sU79XCnfEMd1MNjwKDzq/GlxCJscoO6xp/6b3kVdYy6DQ0HN0AVXHetnV8sTGk5FPHVFTgIuVMo/IWPq28MEhUDfuK7MEqhfj1jgx2ZY9vRRngsfIG6EqAup65oZ6yD1DH8Iwo8/OV71hbGLrE9oknX8jvtaOwWvnKulKiXs8RjUA6fguAlQwKrgpYd3m1eEkmd77x9nFbBwjsEDzTEzbaf8qILVOuhKVwwDucnow8cvRKdkX4iKkkcydCzGaYl7xXPCmc60z1qg9cxfItkHZGaeLfo6IEVLyD1liaRwMvqyJJ14RXSmK8ti3B/ddYzTxn3/PHHvqahuACQXTlCTzhjNFEcdFFz02kXFpezNiNcz/syoPjevB9y0a3yoLv9FJKDg0y4EOgj3LYMNN62BClsH4EKeiEIFTQpNgmiZ78L+214D/azxCV1L+RVD86zft3ACGRztSdA9emp54Ht4pCe3FS07FjXdDFhUDRYETJmRQ2koFmq7ExIVPeQrBC9PMjN1R6V8I7xo6vyiulU2Xxz/jPTCtLTh/Oi5Xgr3nGH+QTwyPjoe0X3iGPyid+d1XJihpktAkXGUPRO46Sx/3bmWlHtM4Sd9ZVS8rJz1PjQIzT9iITblCrFuS8l/4eo6cU1
*/