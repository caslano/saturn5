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