/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGNED_DELETE_HPP
#define BOOST_ALIGN_ALIGNED_DELETE_HPP

#include <boost/align/aligned_alloc.hpp>
#include <boost/align/aligned_delete_forward.hpp>

namespace boost {
namespace alignment {

struct aligned_delete {
    template<class T>
    void operator()(T* ptr) const
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(ptr->~T())) {
        if (ptr) {
            ptr->~T();
            boost::alignment::aligned_free(ptr);
        }
    }
};

} /* alignment */
} /* boost */

#endif

/* aligned_delete.hpp
kE2VZK+tzGopxMBWEQ1qyqaK2E8Y8KDjZk+yF1JO6vPgY2OKsGdWVtrz29NT/ccCbTbRCPhrY/6r8gduFbNcutkM8h3affTyJ+6tUZnirLgpF+XQQS/ixJWYQ2Gu6REv8nLDJiOsTMcBL7ryM/cuYbZ70gX+7PoBMEuTEWr5JJdxLAifTTf+8A03HG/hQdCEKnNy2OtjOWDHL0fvUqycl6sgESSgx/F2ssxCmHRBQZAq5hCfG/5mgdO96zUbcRLoOBuBtaDWtGnJRhwFkssOid4X6/O45womXuAW3HZmI04A5WX3JIIc9TjeTBr331grmw6BOczaIdniUSBewW17Nt83C0xclF9A5L+LTEbh7+ggZNhJA3B8un2WI9N+2GR2Uoo7ZpTp0C4JKXGjEf1R0WhQfLxndihRlKVVfv9uRdPmv+5EgjEPTFyAf12Gkvb/WgpS0NFRQAa5AO9eBEkuAMmLl2J4V65x0/zFizEA+zSF0xcUrxxKcRk1yM2TnX0V9xDFRU23/x77vv8lCL1xM2QKGPVAQrqd3UsMud9xi1fmpLiMOeTiEeUCUkJ8LcVlI8mxgd9eio2aNlWnfPtfmqLM7qV8CXIa3DVs2iR6CXIbgU1n92K+9CCw58ZEkZjShASh5AYivQjLlgjhF8E8aXDFop3/ZUbzqIdf2b1kL5+c3X7zY4+ONQ7AtLN78V8EnR03pX8VU0yyD8LK
*/