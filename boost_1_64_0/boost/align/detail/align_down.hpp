/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_down(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        reinterpret_cast<std::size_t>(ptr));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
Q8i/P9Xy8prZLByIByUw83tOZG+BcH5QeEpQODkoHEL+fq20r5lFBsGBPeQE8iiXlMAam0ryr3tI/jVd+Z6rM5/D+Ks8h3FZJHKX/w3xxYJfV1bbmG0tA5roJ6eg1LztBQ4lUWiIt6RIsOUDwZbdci2yhzp/GeUqYiDpnmR1Ea0O4Y0qRRLGNjSLQZRZOvTwq/wRr+57lXDrecGtYfcIKk/+hpZ2s+SMJ5H/fMKjYdpiF9SZ81d8ocYfM5wXFE4LCk8ICmcGhUPgz1Mfm+2r3LITKQu1/gf5rfg2560g/Q/Srf35aJelP54geFKDwvlB4SlN4f1uW+P6c54K0n8FpZe9a2k/Oaj+EPj84LYm+LwNOHR8+bfk90p+K+Utyduior8g9JsVsGRylRP9DXc+Ue45qTo2oP+U+hmQKPCPTdb/1ob0v7wawv+dJX3nuqbpT1nS/1bWNH2eJf0ubKlN+m9JPy1E+9mW9FefaZre05J+Zoj2Iy3paneI/m+x9O+lEP23pFeFSH/Kkn7x0yH6b0k/ECL9Wkv6nLUh+m9JH7k4RP8t6Y4Q/Yu0pC8JNf+bG9LDQ7S/1JK+ojRE/zdr/MXbu63dhgNmhRG+fiRv6gh5U0FAn3MRhAkeET+/Cwa2UcTtOH40A58zIYqeHoEm+2uQjMhuZzUYkCKlGGZo8AIAGTUdZTuQMJz0fTVspES3Xbz02mhtPD2IxxIalMvHX7FfQ1oKeVycQm1sxKZgKNhKziIJ2u1kh/qnCBYxl4wLr44OZ/74KTZGH2OxZ16j5ioUdGTgHO4bQqOQSFK302B3isrRYd6Pals1hGfwFQhfvD9aLFHXPMls56seQ1okOQnDJJaoEWKJehh0AZaoNBw/21Vflq9ZXZGV8/xvDAz262eag/0KW7/4yfQ2k1xWeHBrjZ9pOEwnpP4qenmd6VHuPNjMvLVMrMFw0vgM53mO74P4HPBqWfO71TrmbXPOvcrGglvfsFyMePtc49eOrJIRA+k8VRTDfurSMFTeiZXkl4RjVvkTp3dPCCsZjts0y86tsncLq3mex8npX8m8Z7Zrj2sb64Wm/7VOHPghvUGe4gQ8HwIetqV1qAPgDImNh91TIU4N+kFEQBLlIYlwWR4bxbGcdbJ26r/UDSdradlhBW0n3TfHHzC1K/dXZ6WF+fbSq3POskNdjdQ5x/AkKvjm0WgfopqOXky9r9Co6mlDkRnR0Gwt+95fjtby3RDcGOswpuPg+g3jezG5JJx3cGa/HAMOQqpgwkds8pKiHbbqrLl5vNn6l8C6j98f3mmgnIFCBgq1WAKu/HLK0aICYiAELma3fFRhbXIgDX+5FkrWf8fRX8CBVl05xjq0yu85SqtFhXPzwnAcdS4K91eclTzkylttRRU2wJCjYdicM/GTEnu6u2hpRJZNuef8ID0fhUppYrvAg2c4exRcpzZ+oXGBLrzn2MY7altlZeCc41y4KYwiPq6y9aW7hv5K3Btlt2P9bWH4sm2usg1FLI2vF0cKAHqda4O3pGeHOTGQ66yZ1ATedMDrKHHvKKq/clr0/BYoW3v6pGrb5dM9sAupqLcX7XQW7XCeC082yfOHR9DfbvOH2/ASsJ17Vp6Dpex7CcJKbf1cBTiAV/5KIBEjWPs/1/Erbs/gVULqZgfCX2DqE7NJWPW89rR4a+AE5Yt0V9l7IO59WtWvaF+b3cEo0LpPwnBon5tWn1N07H614enCJAoX0peDvs7nFDKcLyuQGwndZ9Nx/yGV8J6oCAaIUqhk1f9/P8Y+Vts/rbfwK0+EuP9pSZ8OKhKkD2sqZLpGCmgx8mF1GBuAxYPF0zNFZtSJOcI7AhKjoe+wxGiVyIU=
*/