// Copyright Peter Dimov and David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef GET_POINTER_DWA20021219_HPP
#define GET_POINTER_DWA20021219_HPP

#include <boost/config.hpp>

// In order to avoid circular dependencies with Boost.TR1
// we make sure that our include of <memory> doesn't try to
// pull in the TR1 headers: that's why we use this header 
// rather than including <memory> directly:
#include <boost/config/no_tr1/memory.hpp>  // std::auto_ptr

namespace boost { 

// get_pointer(p) extracts a ->* capable pointer from p

template<class T> T * get_pointer(T * p)
{
    return p;
}

// get_pointer(shared_ptr<T> const & p) has been moved to shared_ptr.hpp

#if !defined( BOOST_NO_AUTO_PTR )

#if defined( __GNUC__ ) && (defined( __GXX_EXPERIMENTAL_CXX0X__ ) || (__cplusplus >= 201103L))
#if defined( BOOST_GCC )
#if BOOST_GCC >= 40600
#define BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS
#endif // BOOST_GCC >= 40600
#elif defined( __clang__ ) && defined( __has_warning )
#if __has_warning("-Wdeprecated-declarations")
#define BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS
#endif // __has_warning("-Wdeprecated-declarations")
#endif
#endif // defined( __GNUC__ ) && (defined( __GXX_EXPERIMENTAL_CXX0X__ ) || (__cplusplus >= 201103L))

#if defined( BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS )
// Disable libstdc++ warnings about std::auto_ptr being deprecated in C++11 mode
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define BOOST_CORE_DETAIL_DISABLED_DEPRECATED_WARNINGS
#endif

template<class T> T * get_pointer(std::auto_ptr<T> const& p)
{
    return p.get();
}

#if defined( BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS )
#pragma GCC diagnostic pop
#undef BOOST_CORE_DETAIL_DISABLE_LIBSTDCXX_DEPRECATED_WARNINGS
#endif

#endif // !defined( BOOST_NO_AUTO_PTR )

#if !defined( BOOST_NO_CXX11_SMART_PTR )

template<class T> T * get_pointer( std::unique_ptr<T> const& p )
{
    return p.get();
}

template<class T> T * get_pointer( std::shared_ptr<T> const& p )
{
    return p.get();
}

#endif

} // namespace boost

#endif // GET_POINTER_DWA20021219_HPP

/* get_pointer.hpp
Rm+63RjsAMOXyot89M2LBYbn6yj7gbYC5vxjNSARFAyKTNxIsNgiFX6q4TGDEJf+AUdnSGP35yKnUEmpMCE3sXjJoxQccHaQw8HnLGPVtYJzWBeiVJGsgOMd50tT6V/02UHRfrfNrwjQjHuBvy4t++EfNkSea8gXeFSM6bebnaH7Du6G8EksOf8vfRXwJVWOdaCpzLdKEcY4r/dH7KPl5b4xX3DCYx+JCSkE9CDPUyG41SJRKYF4gaoe0gTaJgc/xVs6PcSYb6liIGn+k/4Y6YQbLzwxiHL8QXs92hMI4PZ0/QTUVrG8Zgxzs4QHSx8YZN+L3l0TGPfzLU/rwIlnCY8Ia/fr2NREX4+hWSi/5Hp6NM42AKa2mjYMU7p+RP722rtla/SFUWx+uYClsvUmf4n/pdKxXAy61S+th/2KfLOg93/gRyTpuv71t+nIetWa0OkO8PKggtZW8T7EVMUFsJjE0Y+0GkIPv9f2w+LCUNMYQqnczXaE1pCRqz+eArjmBBMF/HXj1NshuYbPc7S3wMT+35IYYQ2ZIHrfzdG7i2fkTlBW9jur+fnNIw==
*/