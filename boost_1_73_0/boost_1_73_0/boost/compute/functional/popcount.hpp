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
ZMOztMLsjb08eTsxj5b5OGofI/mVPicuJ1A6TwJyJelEXq7C7rzOYNYuC7UMm23VrTTJHelAu6Z3dV7tfLEfW6uP10m9hzwe6AGyQvtALDVpwqouukJWIf/0rOlYsoQqkAblq4R0b5OUe3uXlxnrQZ37O29dmVa7kpTDZYZMjkyi2vJZiH5sYbcV7dbkSVHsaQEyYBAGAu9JKaER0KcpVihdM7bTBkQmZls9uHq5KwLpQ7um39A7atlkiEX1QE9uSQ9S5h0fDYuCZiLeNnWSuVG1XHqzcM2Do+O4xDsQj0dBIg5OWlX5HU5cddTy8fbhMMQTIm0JW80MCBY395AQXXAuaQKZdWKhlWjz0i9JabOkScDcBnJJlo6EYsxbsDKiXViO5eHN0qLCT8SQh6q+Y52QT+lwoDhwj7Y1z4l4ny+K/Qu7wJF3nixtaMngRF4VLCdaHtKuF3nD+hAWwqL0hFny/lt6d1mTn4hlR0KWtYUOUqzzCiIAFyExGHq6I1KwwaLaNcZXG6daoh6a+MU/qwTj46fVZlOV2CdiI5FlOomoHvLj7IeISbJ+UJvF3pYke5fIgsR0MiZPnp75YSgEkMakReK9OMykaZKUyGvW5MfrakHn61OlQSOYqISEUybVfHDJXQlvNCl3G9WS
*/