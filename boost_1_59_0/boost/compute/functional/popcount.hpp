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
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
*/