#ifndef BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_EXCEPTION_HPP
#define BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_unescape_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#include <exception>

#include <boost/assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by xml_unescapes
//
class xml_unescape_exception : public std::exception
{
public:
    xml_unescape_exception()
    {}

    virtual const char *what( ) const throw( )
    {
        return "xml contained un-recognized escape code";
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif //BOOST_NO_EXCEPTIONS
#endif //BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_EXCEPTION_HPP

/* xml_unescape_exception.hpp
BGwKhV/zeZqyJh/CvxdQ3uefTPTxV/pZthN79pch9vt6TBp5i+JYJ0rO6+Hgn0pSrQkSzCMjmLTySJjoCxyfoEftc0iZ1gSPpUqrdB4+2RAf6//xg3tvU6i2Cv+cJUFxpMtiwrvxL3ALNNc2QeVJLc3IVKO4Sk8ql64l0b/ZbMioHXTx8V+69GIH7eZFtH7xUNxK38FswwZIf1QchpxMokNDW9D9nkFMWpIU49dDJ6KXDRjcRMksIdrgcoaexE9gXxcZkPf8UB4wNBHLMtIx5d8BbLHbwvqrN8F2awnN8dGBmL474jV+0o/0YXTzIRHT9+N1D5qx418LhUk7o1/SmKlCDN6WsUzcbCZ9equPfdZHoWudRiOO5mDCPRH+72SvwE+qcKMO0F+rleRQfxq5I4kNTyzHS/9ituXdM/i924aaiFpMlr3Oi1zeQvFgMH+f5Q5bDQPmdukHRJbmkPISQQ7Y9oAaXmaRovAZSneool/54ZBUv0BfD0lwqR2vIdYbSYEtwvAJ/MKM9e3R7jeLhF0WY8VeQebaL47Qiab8cXwL+d/RxceKLGo6X8WF/HPhlpXPpovMoJs7N0BtUxT5zFhAky4eJ7Hs06z+21TMdrtGKYPXaXXIK+7bL41V69tZddNEki+7QQ5GHVQsXk97i5+QTIgta7+kQ47bt8DlyxA0ttUixtqD1rgm0rKtQ2hS6Cza+U6Q+5t38au9ybD+c4in1E+n6iFa7PqrTfD+OoGmeXrAY3Q4uz2/gXaX5PGkIQdgvK4KSjFZJPHUi2+8mAPL8Q/YmPAibOuMptHfDWEW5kHpge+g6/8U8Q2+mOHnybeVqGNPSyVpjzxPiqk1dOTHGRS/UePKv3ch8e8mRK8sp9tuWVi5Pg89a2YiIu41ip7Gs9+anRhn3ctPd6nSU3MZSpD1xrGSiyzDaBfdSJvNP7DrdEB9Ak58fQyXyEXcsfcyxHLXU6RxF8VuSAA000gyygzLbcbDargLt3eLoD7jZvo3KhjvjlhxaffvsFDRYuKaycg9p0fZ9Bjv/upxHZdeeE0y4clCX+G4dCqt+BZI3dWaXLl6M/ZH/CG77F304Kig41yRg20avuzauVd0uOQFpW4Pg+65CL5SVw6HNbKo980OyvgxQuD9PSE24wb+64yjs/ef4+kxc2o9/oWkfG5Q6V41eG/XIX5ViNWcv0PvTmjx2tsn6bX5Apo+a4CWvdNgleXbYXLNBqFymqjf18Klp/+iL8+e8I4Jzfj4MZGnXazBJ+UE9uz1Vdp7MIGJ2OaTu64Rci9Ho6LFkCsk3qN7F9R5zfUcSjhzA9/nF2L46fFsW+JSGl+TjM9F4xEgOY+2r3Aj3e/mXM7kBgwf6FG++UUBA5mMH26JaEito5gDh+hqdDeTmHkNPvb7eaqYESZcrOaxGsIQ2xdPhpaDdMOlC6OKvegfdQlmqkrUPH7Pva5OoIbhDnigmoODI4+zb1NP0dvlAZjncZiy7dURYekIQ7VmGnXBnbJWTkHSlpdYeKoNHVJ22B/7GvYXjmK202fudiCdjG4T79bKpprZ6XxRgiqZChHtr7lPBVO+8vHmFmQ4vZiLT4igHi9OTmUONPKVCKuefwFOJ+cyO9XHFKFexO9pjyYnxW+sZJgI3Tmuz2u+XifvxS2ssS2bZt+v4r/y+/Bg7AbmZ8FQd/wGRtYWk8HRNUj5YE2xqcXMIBRYvlOZpVvG4MOxtXRFTh2XJkxjR7pU0V52k6KOPCLZwgfYlqOHq+FHiJLUabrcBP7edh3MQj/xGTJlZDZSGPvkS+jHXjtoLZ4Ht9xxTOnnIUSzarqYVID+cf5Md54P6VcP0Fq1XGhaHqOWDY/phO8=
*/