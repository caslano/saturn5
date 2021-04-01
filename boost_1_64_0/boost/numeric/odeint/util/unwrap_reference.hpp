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
wDfENxKlV2qm/u4+K2WybVHWejvqEMWihIQ9Fub9kLp34mn89WMheZTzuviMbMU1EvZWX+ebRJxZamovDrRvHKFRpKdI0kEkVIm3d7wxo0Ga/uRAbSTxSIlZQ7GSrDhf7KIgAOiWeDJOaUlLWFv+lkWzI15Ji9QeyfMT9S7Vklp3hSvg1rl/3X8VT5BnGJg1UGaI0XILm3EkCsdL1h01rP0W0H45GzWWigxJjTOmHzGj15bIqVeq/gRS/5BaB4XDYzwACofJXj7xVvZ3kS5FV7k6jdK3vR9OBZl3S61MdpG4NGFoh8SDnXvmCPkN0qbiuHloiJkfMF65KyEXQ7rd/H/NGRnx4I3ZSTQ8Sjybh/KCzDdeN9mjrXxQwDpxy0hoZCsh9Udfp6Cf27JzijHrFKxafkFuWjQsQGNK3YhpZJXX7EAMUUwTA8cwzgIt/8jCNjPMyC06Y6fdIC5QLalM4SUvxAaLwSFUgQ1W99aivEB6EEjJA1xEiwT4UJvHcJL3NsxaYplrnNDd4NCcqXFlPdp86eqV8wE045u/C0e17ds/36XccFZnmw+c2w==
*/