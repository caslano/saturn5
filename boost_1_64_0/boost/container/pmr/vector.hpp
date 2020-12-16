//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_VECTOR_HPP
#define BOOST_CONTAINER_PMR_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using vector = boost::container::vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a vector
//! that uses a polymorphic allocator
template<class T>
struct vector_of
{
   typedef boost::container::vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* vector.hpp
Xp5XUAZD2+r2IKt+yflcPsI7fj2mbarZvCrTFfjyvTjR7bO4QbL3zprGgXU3iG+TNvUZhTklJcxZI95Rp2K+tX58zJHiqBjXrB8VT83mE6Ow1LaANqLxSxmwfwzZ44ptS9WzqaXxb3UPmfo85vrrIz6fX5M9nzzn+vK1TYmPoS5qXXywnn19m8bCG9dTzu1KwadNzu6avp752V1bQNlWuD5bN5O5E64j1tXVHY05w+twl3XVmIj68rr0bXFesM/krJD4GLZPVp3L5r6+zLr6cSvfW0ptjOpNHQ//tE5642HVTo+uk8zXotbbTlkHMc3qWpV7z3VoXorbmPNXafyyLy3pl2lbh8oRZvgz2z+vzfdHYNlo3kj32NpmvM8Yw1s+R6+2n73Xjq8r3fPuy65N8Uv77D/8Fr1v5q+1VLlpn0z8HhnEeHktwuf66s81wnuEy3W9ci3C1LWn8GcFyYZ83yPtpTxIo5fuOf/NGG/dfOQGa3G66LnL2QRl313TvOz1grI1QdkNI8s2ys2+Znwdc77vrRHP17Sfvn4NeT89xh6RspC/hJ/z8dYUxPblVd9/swnw/qnJx1lnii/zcVNk+s1noZ+E/1c9cv6sDNCEn3vyYA8/94T2TyCWKhO1z+j3+1BZjnFmT+M86RUDHOJF8VGNT3Tmb66H66w+/6/G0/DnAR7rzmRW7qE924iljfdQzuwcbDq37rdu83dh6+bTT+lOL38gWpQN6XftNssf8Dc19qpt7MuuTGbRblUmvhea+LL2pbxHfrv59Gc93dVF6+j8ndUstzA4R5znykd2IT095xT/7DrIpa69cJvCfbNzP7fp4ueApVefZLP5fb1AHsJNNibA8usxHcjX+Z4G5PF5J9mG+zmN16iuKI6hfCh76DPn4AvheqMsdPagqv+dnZFzi4Cr6k11R+8qC3+uDvlym6r+f1gnPbOD8pJNfTyuH8XoPYTP6ETpvaWF3p8xHB4/EYPaEW8ziNnayecAkG967wf+pAN5xfutMk8LMsjPLtDNDd3RIVvPWCqkvR/eEdXG05F1a6GsUWdX8b2fal/2qNLOF+igNafwd2GSDij3Cqsk1/XL1WW6JsW728cD2c0xH22WrYc2tYTjH22Bb4obhrn9BNt44QnG+2o1GZ507v6+1cZv7j4ubh6zGvkLyphsz4Ap5naryc++WmEVeexTceefBF0/aZ94zFsnAXNoEjA3nATMqZOA+eaq6WC2TZXhXrFqNCbIpLZVnq8AFs2HIKbPh3JjygMGV6VYR7kgYiK/ZDbrSslmEsx/Vpl4zOcmAfNcS8wVVok+53r/VaJzX6LDe/xdmb+uTGNKtqdUMNcOMmn1fGxl6qfC9/Co/RSWx7+/CeRAPDV/P3VlmjdQ5yPi+zi2Fs/GOuF1tfvK6a7Hf9AaPn+w1Mq+fE0t5rmS7TvivluJ71dR58cIS5kjE/iE9uytlezfdwR/a+fnjlkpfH4O8beG+2ouyMuQ3PysD27D89g8POqMNOcpOer8K5GuJD/N04WfZfTZimFyU14XP6eGNrljRV/mH0Pm0R5tNjsHkuTlmCAH8EL+xE+dL6M5Gx+b+A/SfKXhOu+NEXsLlorI+w9dUT7vrsN4a0o4xhYWGPOuCN8rwHwYXIfDtfUKZnTqu5OpzS2wQph8MrnC+H+xfDz/qDXdO5Y3Xy8+ZPl013Q3X576GPX8N92emLDzm2Tni/NxrnrmyjzLoxwok1lcU+2Fv32yHM1j8phg/k4RLHf7ckhjt+78jcG5s4cuh7zsz9vVxcStlguJiQbvW0V+8y+X7Cxcf+9qvH3pnS1fLMv3c4XaGGQLf1cLfvM+9q5lzc/5ksbLI5c=
*/