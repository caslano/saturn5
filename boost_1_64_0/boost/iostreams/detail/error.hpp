// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/ios.hpp>  // failure.

namespace boost { namespace iostreams { namespace detail {

inline BOOST_IOSTREAMS_FAILURE cant_read() 
{ return BOOST_IOSTREAMS_FAILURE("no read access"); }

inline BOOST_IOSTREAMS_FAILURE cant_write() 
{ return BOOST_IOSTREAMS_FAILURE("no write access"); }

inline BOOST_IOSTREAMS_FAILURE cant_seek() 
{ return BOOST_IOSTREAMS_FAILURE("no random access"); }

inline BOOST_IOSTREAMS_FAILURE bad_read() 
{ return BOOST_IOSTREAMS_FAILURE("bad read"); }

inline BOOST_IOSTREAMS_FAILURE bad_putback() 
{ return BOOST_IOSTREAMS_FAILURE("putback buffer full"); }

inline BOOST_IOSTREAMS_FAILURE bad_write() 
{ return BOOST_IOSTREAMS_FAILURE("bad write"); }

inline BOOST_IOSTREAMS_FAILURE write_area_exhausted() 
{ return BOOST_IOSTREAMS_FAILURE("write area exhausted"); }

inline BOOST_IOSTREAMS_FAILURE bad_seek() 
{ return BOOST_IOSTREAMS_FAILURE("bad seek"); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

/* error.hpp
cAv8CN4DK5GmrbAGvBfWhvfBnvB+OBRug1nwD/ASuAteAf8Ib4CPw3vhbvggfAq+DJ+BH8Hn4BG4B34Fn4e1qfcXYT34EsyAr8JR8C2YA9+GF8J34aXwPbgMfgBXw8NwC3wcvgq/gq/Dv8HD8HvYjPK3KddM6INDoR+OhAE4GVaCOTAe5sGqUOwM+fX9gr5TKYbnItP8eo+BXgPYELaDrWFv2BcOhv3gSFiFpWtT4ACb6OBAmAeHwkI4Fd4Jz4bbYA7cAWfBJ+Bs+AycA9+EefB9OBd+CufBL+B8+C3Mh5VJdCFsDYvgKXApzITL4FC4HJ4BL4eT4M9gNlwLr4E3w2vhBvgL+CuIWBvhbfA38F64CT4Nb4cfwDvgF/B38Ci8FwZ8tCtYBd4Pm8CHYEu4A46Cj8Ez4ONwPtwNL4dPwevgc/B2+Dz8A9wLd8OX4DPwZfgJ3AcD1NFrsA3cD/vDv8AsWAKnwbdhjrovUvcL1X25ut+o7uvV/VZ136buO9R9l7q/ou771f0tdT+i7n9T9+/UvVog6J4GHfeG0HFPV/eu6p6p7qPUPUvdJ6n7AnUvVPcl8AF4DfwA7oMfwrfgJ/AA/BQm0q6PwDrwC9gEfgk7wK9gOvwb7AGddjwcHuP8dPgNnAmPw0JYGf/FqrcSfob7TdDm/NfQD2+DcXAHrAQfU/3QGlJ59tRn0uKINaRzdPzOgzXhPNgRngdzYAE8DxZC/R3hGTH678jPua7DNTAOXq/paGOeyywReV50/XbdpOHWQrlO6DkH1va4ToLqV4dJsIYrXP5JwtXRcCkarq4Jp/fd8BSPcNXtYLgasA2sqePZQWS1Xu+QhktD3tRw9fV6TWAj2BQ2gafDFrA5PAW2gRnwFNgPtoWjYDs4FXaEM+CpMAemwwUwAxbCHvAS2Auugb3hBtgPboL94V1wANwGB8Nn4FD4PBwOX4Ej4X44Cr4Px8CPNb2hejzsqv8S21WPWq5AynVrDHuLtRmI3SVkGpKPrEA2INuQvchBJDAIm2bIYGQmctGguP+4Pck2D4r7wfuSHXR0BsX9W/Ylw47YT743Waw2wsram6z9soj9yV4KRN2jLAu/iD3KILbxkITBcVYGMhqZg6xANiI7kRLEGhJnpSIZQyrWSFQcFUfFUXFUHBVHxVFxVBwVR8VRcfy/HQGk4J83/z9/4bzFnbqkdzV//BQ2AJx56OmpltnH5ZBtbM+b93/f8E07K0u+cWbppacPzVswY55+1/66lZkfYuaoniH6872+f2pctvnuj96MHM9v+W5dndsVMUd6qvi3spJ03tp1cp5G/quaOeOdnHn2yL2JZe/VFPrmSp50jop+EzdzA0hrxN43M/U7xP1IHHIf8i3hSyLKbITMr49eZh+K/p3ec1lc5fCx7H81N3exa+7VAfHf6FWGJmwKc9QOU6nbec3ShfJI8C+9OiGuisxTC/ntM365jleY32Hj1z/SD7eQX33jF5qLkOExFyFQjnInv7iR34hy5zWMHA9rPncg/tZ8FxsbXu5n5M9kutoJ5W7mLe4R/buYyRjAbSDp0DiIuak1xV0PuEfWQ96CfI0rGX4o/quZU9rGqy4IHzknaV7uAtechqfEfyvv0v1e82wJ790fZH49fFn8FzJz2ufSKcgN6dSCfxadYZRpazMffcA4x627yf/borOO3AdCe0nRjxCPukwsd11SZuqWYOZNUQ4Re6LxjeKEeWoB6nfruPD65QrTC1kvZFllz3lxrwdZqRE3VYUmOt9sVzD+M7p0nnB6Jm5VzTiVb+biPCs6db36KuF1Lo6p40Wmnz4hfinebQO/WObR1Qibq0SawuafLTJ5dO9D2NzY/+Q=
*/