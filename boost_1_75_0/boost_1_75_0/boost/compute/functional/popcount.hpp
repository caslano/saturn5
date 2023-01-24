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
3cTmdJ5++yf54NGltWr1Wxn3wYkb7YqdeXQjr6jLaBolAhTQeRtyCk66PWPt77rVxdYzu5SAemDvqd76vrOO+Vb86qqhjmVA1O0D8esyBeSENcUD8WhDF9G2L9lbx6nIHq7SjuBhB/okFWh6+NRQtH/z5+pKdJoTYBO0v+SABUK6lHpyg3jy1JKG3sM0fUH1J0GrA1RYOpQcJmSnm8Ki20pUbrDWcpgzrOFqf725+6CYMzp2MImpPC3PGnfzrZ9eNBY4Z32bmIZdvLG56iDJvfQOmRNg7ckX39SF7cXYJLeKC3DPV63z3DOztusrhJnIqrv+6U4a2iWkxsSRCTu/wQzcar2ptbTYoCLCMXWmbxUVor3SFjY2bqUtDW1Thp7GW5nZqjunOQHJYTfssr3dU6aHIpZa1JQQ8bjGw3ZbyRztxkl8xs9Nl2Hf6B5ybl9BOLA62Les84dJ6vos4wGN5JofDF+17/MLkoyOragSw59BcqvsL40w5910LlWwZ5WypyJy6codk/4vV6W4jGshJEmtJshHQnsgTrz3U6LFPoyPhs+5sK/hvPW5i/0CxbjNiBVW1C59EHWgoJ/6XKHZqk5W56fB8Ez+pcvNfTJq3kW09mtTSeQTGrrcFyO6I/5/Z8QrtWa4tWtuOu3wXOXhv4lab9cx1Rir6axWuYTczPG8o0EoJ0iTmx94bXQKmPjtZWY+LUBOF+TOLuCq
*/