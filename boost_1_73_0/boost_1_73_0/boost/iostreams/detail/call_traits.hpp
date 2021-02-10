// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace iostreams { namespace detail {

template<typename T>
struct param_type {
    typedef typename mpl::if_<is_std_io<T>, T&, const T&>::type type;
};

template<typename T>
struct value_type {
    typedef typename mpl::if_<is_std_io<T>, T&, T>::type type;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_VALUE_TYPE_HPP_INCLUDED //-----------//

/* call_traits.hpp
oZN25yTHv4zvc5208ewSDgLfIpT6gU56zEhi069VzvT60dXxl452fmact+pJbiMM2FxzwVoeTzlhECU2U2I2FY5sKjuJumd23ewkWuSeuC3H+/ms8Hcz8Niu+HCtsvvy5TI9Zq92m1A/CizyW2fOKjezQF4PJJm0yA2jgI+vrZ2dP7wAL7aPtYL3zHwjieccP4VRU3QyIJ7NoBA34oFWOzvVDXaxyw+ubQ7SbfbPp+KNzAiSaYtb8Pgss7qWzvqJvZPH9HLxX2enHJA+a6vpTrHI1AxmdsjcM2HJiLrGEw1JP/uVZAiemtYdGx7DvbM66pC3NX8KMD2nR2h+v//QWd6fJDffEbXmytd41PxBbq7DwYAx0uk5c5j5hU/DWVPyweZEL89LtxSkc7Jtfxdsk5Vt8cipe/dO4Ht87NYqO6AeqAfqvTP18ubIOaj3CdhbAPZazSOIOgXBB7xNx9sX7ard6hiXh5dNjdk+aAfaQeMVEXbQeKqgDhoPEAQEpYMgJJ/EFNRJN7qF4FOIguJZt/U+LOs8Y1mcPLpqtvSpWIvNx3TbJLbicTQdmdSxUrhpd8T6SbOVw3Pk7cyGWSkeSk2Px9rjjmjEG8MyErCuozjr7NfBzhYj+dKBTZ6by7hFsmbeBmafTyBdplGG
*/