///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_COMPLEX128_HPP
#define BOOST_MP_COMPLEX128_HPP

#include <boost/multiprecision/float128.hpp>
#include <boost/multiprecision/complex_adaptor.hpp>

namespace boost {
namespace multiprecision {

typedef number<complex_adaptor<float128_backend>, et_off> complex128;

template <>
struct component_type<number<complex_adaptor<float128_backend> > >
{
   typedef float128 type;
};

}
} // namespace boost::multiprecision

#endif

/* complex128.hpp
iT1A7ZhB2Lwu96e3z90ojUV3U3UbTbGv57ixvL5XMvDxRR3pcyqo6Zkav9q/JM0uu8a29aNleVpAgiw83IWdRI+PWNLkAHMRZ6Dpqs3fa1ti+NtngRLLoLyK7O4kwwFWQFL8XgTRuIGyMO0QMgaIZNR2NANlHEm5du1N2MEK4OXk8BqBp9TRQhpr83JX0aeCEpuUneoiul9r69Gog2LSNRbt23UAh/PkiWxRrWLgFhVgf/1MLeb9DgFgv1b2qch+a97Tjxyn4Y2bjKngZ6EpOgX6woh03unmmXC7WmVYmZqpV0yl/pm3zT3SfcBnK1RodSt/kHHCOOmnpQ3WfmBT2enLZuDwU0k0gZ/XihXik6z2oNHGTu8MXS0WIHj5KafMRwIKTuBsYYmUx8TpKVXCZcu++Y8WFXx7OtP7frcCLkw6Qnh+ONDoHqir19C9WLK3N/86/A1X7Vc6MrQFhtT4h0av7wHOUOCG4P9Lo9ePejrpBZ7miwizlsqIjwbi6w0MMiqkvCB18RsCf0DifmiBTvDTX1N3+zg6f6oz1T02oP81sT9UxmjTzkT0uWwIp2wJIztwYnayI734YmyUw/+DEOJHkR+OOmEc6jO9ZoCf//nZknv5thf+vr/Ww/jiOpwZg6zSe7/zIWQDb+KVrRh1kKnlGo07gcHe3qvdNX8z/PWJcsONMPMlDssni8/p+SlC1i2FkcZrtAQg1GN8
*/