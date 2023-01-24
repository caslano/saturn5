/*
 [auto_generated]
 boost/numeric/odeint/util/unwrap_reference.hpp

 [begin_description]
 unwrap_reference
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_UNWRAP_REFERENCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_UNWRAP_REFERENCE_HPP_INCLUDED


#include <boost/numeric/odeint/config.hpp>


#if BOOST_NUMERIC_ODEINT_CXX11
#include <functional>
#else
#include <boost/ref.hpp>
#endif

namespace boost {

#if BOOST_NUMERIC_ODEINT_CXX11
template<typename T> class reference_wrapper;

template<typename T> struct unwrap_reference;
#endif

namespace numeric {
namespace odeint {


#if BOOST_NUMERIC_ODEINT_CXX11

template<typename T>
struct unwrap_reference
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< std::reference_wrapper<T> >
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< boost::reference_wrapper<T> >
{
    typedef typename boost::unwrap_reference<T>::type type;
};

#else

using ::boost::unwrap_reference;

#endif

namespace detail
{

#if BOOST_NUMERIC_ODEINT_CXX11

using ::std::ref;

#else

using ::boost::ref;

#endif
}

}
}
}



/*
 * 
 * the following is the suggested way, but unfortunately it does not work with all compilers.
 */

/*

#include <boost/config.hpp>


#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <boost/ref.hpp>
#else
#include <functional>
#endif



namespace boost {
namespace numeric {
namespace odeint {


#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL

template<typename T>
struct unwrap_reference
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< std::reference_wrapper<T> >
{
    typedef typename std::remove_reference<T>::type type;
};

template<typename T>
struct unwrap_reference< boost::reference_wrapper<T> >
{
    typedef typename boost::unwrap_reference<T>::type type;
};

#else

using ::boost::unwrap_reference;

#endif

}
}
}

namespace boost {
namespace numeric {
namespace odeint {  
namespace detail {


#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL

using ::std::ref;

#else

using ::boost::ref;

#endif


}
}
}
}

*/

#endif // BOOST_NUMERIC_ODEINT_UTIL_UNWRAP_REFERENCE_HPP_INCLUDED

/* unwrap_reference.hpp
OMNEzHTZjU5PLww8oQgXcqSt92G3NFnbD5kjTaL9UZVcKb2CBlLpV8ehGDharDjoGbm78AMs81y6XxP1bkqz5d2ekBnYzMvr02wv7wWpgSEw+ru1HDW5WdCxGQDMhbSymdGxyk5Y0LFnmu107A2n0geTBjQLOiM7ZqyAPTrO9wE4BukixzkupOM8E4XzCvG8SveQCnEFyoNB1GLSR98XUX70XeAH5jLfuo/yre8Og0zFF7yPRn5h76Mt0hGjj6LGdf4XUf4py2l5J/mYRJ//+YKe/6G4x6JEQc/o7wfhp/SP4HH6C6pnvwzLOjOrG0a1xI9WE/3sEkz1MnqeBuBSrYr/psJvbvgN/m26xs+MVlC7gkz9i6nfTYOug1A6ORrpZ9f9rc6MF/9N2K/HAFAF6Zm/UX3X4j5eIs5y123CkiTP+ptpKj8HFV4Qp15ykrnSZpKOq+Q5/AxetjiDlyoj7zGLH1AWZvaACK1PwIXin9ZryfX/HMO2YPfbzTFki9byq3pezKdkALpByj/PaXyfWp3Gv8hl/ezz9nn1GRdbuzvvKeNPPW+RXWZD5s/nueyy8DyTXZafNzhHd5vscoLKLuO57MLmqwfma4Lp/2nFexQy3wq8TRzvJRNvgQ3vJad0kszjsnbUPPN9Kc6hdfqSzjXclu05/0vRZ2z+Q+bRL8X8/9JO397A5HHMXLhjxrhZ+GXUWdhV8AN5hRn2
*/