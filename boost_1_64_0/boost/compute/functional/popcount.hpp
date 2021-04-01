//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_POPCOUNT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_POPCOUNT_HPP

#include <boost/compute/function.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {

/// Returns the number of non-zero bits in \p x.
///
/// \see_opencl_ref{popcount}
template<class T>
class popcount : public function<T(T)>
{
public:
    popcount()
        : function<T(T)>("boost_popcount")
    {
        std::stringstream s;
        s << "inline " << type_name<T>() << " boost_popcount"
          << "(const " << type_name<T>() << " x)\n"
          << "{\n"
          // use built-in popcount if opencl 1.2 is supported
          << "#if __OPENCL_VERSION__ >= 120\n"
          << "    return popcount(x);\n"
          // fallback to generic popcount() implementation
          << "#else\n"
          << "    " << type_name<T>() << " count = 0;\n"
          << "    for(" << type_name<T>() << " i = 0; i < sizeof(i) * CHAR_BIT; i++){\n"
          << "        if(x & (" << type_name<T>() << ") 1 << i){\n"
          << "            count++;\n"
          << "        }\n"
          << "    }\n"
          << "    return count;\n"
          << "#endif\n"
          << "}\n";
        this->set_source(s.str());
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_POPCOUNT_HPP

/* popcount.hpp
PY2YlEyBknt8aFGkm6l8Coaz6R7Wqx3olmfp+ieE2u679kup41cN0Yt4QRz6L2abFRecCgFOBGCeO+lHkZId2quGsTPDghA3Q+Fixk7QwlxhShiJV0KE2hsUHREHisRZRnPZ0GTBlDusqY+l3yEXO/7c4Zdl3oprbTnrKhu92FiTQ5UBOJPot5SMD6gtJO5HihhSh/AB0z2YHUxFvv879tWvSbpvBg5yzzELSwm0xd9xVbXQGIzdwdwVOXVhsN8ui1tSzB4OX/xOluaxT6Jgdpdv6LRI7gDdUQIfs5zP9QI5gmEVKxclr/bhnlt3/Tlw577jVLxq45UUNKJilhhvastl0A5eWOsoAp0EBL6iBZPuj6A5a5Z0i5WUN+QEA9yhWdHEPQw6HhTwJk7eKh7MqL39r39q0laIX3ihZdCvkvISe5xyqb1hhjHOEYj1ScLnZrCb7Y7aUc1JTrjGKl7ouMvabdodYiDFG4kLlcDOrwWKkMvQdnuA1D5RriBUCHPS93uECsd4xx0M2rX0rn9/dp4tFw1/78JqPxkIQVbDE2CBPlji5v32mTVmRw==
*/