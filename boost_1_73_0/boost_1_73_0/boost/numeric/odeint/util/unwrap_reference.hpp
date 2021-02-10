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
PcY+gNl3IcFJ7gFI3oG4p4KHB782KEmzTIVyKx3rN5Pnhp0QXCuC/Agk72Dkb0HyACEH1qon/HhsPx/ryV3uIdTcTg0BXRdhQ4h1HSB3wh7adQstyG30IDRq7qPKEBq1i1FzCzXMLRQxt1DFVsr4GFbHcoN1YY0m9zeKAamIDOMtigHpib1spyMYAW4bjmEMseUxCN6ChUNGIjc/OhLMVIQ9fCS2ppZbG1tMEkIhoBYXk4SLQnBbq8+t7f5TWH6fYPmPIevvOn7od72Oj7oA8kfvBqxwUF9A/uj9gRUO5hRkeU8Yx+kS7BwneUeIg4L0xRMbsZy40fgaIE7Xc8tpF+2A7DwmnoHY+T3gSJxu2JP7HnNhQgzHCX2f4wMKYZjQ8znuCWYoWhA/6IYBYXIsfcIcw8YvzCBsfENu6x/Cs+r5rhOGqKsXIDhdr9vtcILDCKIEru92CZ4jCJJ6YSgGt3Wdcwwb9zmDsHChuaUbzS1daWt3+hhzqVc2CverU6NJA8Md7NRy0sBQTzsznziYNKG4j8jJYQjm/xN6lRtTghePgmUWlTS+FkKT3K62EFvgzuTSwBKCDBwst7KEaAPFykwtIepAkVJ7S5m6NmKxHMg6HstwrGOyFMY6LsMnfmmICQEaYa+l1pgQqKFQ
*/