//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct capture_traits
{
    static std::string type_name()
    {
        return ::boost::compute::type_name<T>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

/* capture_traits.hpp
UCaW7Sp3fzvuvj5B7m9fzDp8d/x76WbFYoz/6e7/8wwD9SB98KzZ9o3q3JB+OaTgCzJpj4B26qrGjKpqrHrvBNp5NYH4+1kE+yaq/B2VZxaX7Y4kdE3k3VVdaSmfyoa/Glavun+cgr/TPyz2uO8U/e3MmqYbqvX11iNEDxeFL4x+Ucc263F1oV5utUVdn2TIjotmlB2THVF1qsvjLKTKHir/o8PwOD5ivAD/UQth1zfEfC+s+4bUvxOOrAixRfCYnpz23fz0gU96N9do8xLEyiHb/He/bcVaWvfTR4nPOUT/6aqd/+OrZV+1vL5/b1h90LzqYst5JPxCKPJo+KBe70xGJ2KPRA/q+xIT9W8ntiUnGt9ObmuaaH67KefcSF1r0Ve0XN/6SMtBfaHjGhBI5krE6tPJWGO6KdacbqW94vq6XeX5urnrpOUjUbW4gy5pKsctNnZYByxC5gGayvt99CO+/b6BbrZ/BGvloo8E9/tj9i+JNkGuqPBruvUjFbanO+mBc1gPs9PLh8WETX3EhydeoJvf8rdf9r69c87XSHQNOVdq/RWV0mvN98s+UdGAT1RLJ+MKF14X3Qx2Al5vp2fidmPMekPOL/Wzrgj/oTF2W+gVE2P3Rap8g8qxzvI638ec3VII7yw7+OSFw6zQqwq5a/1vvK9PbaTefMtpfVs/GV4XaY+uiR0wKoWcc6GJdxrWq42xqJNtvEmV
*/