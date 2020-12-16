/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline bool
is_aligned(const volatile void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

inline bool
is_aligned(std::size_t alignment, const volatile void* ptr) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
CZ96Ey/e7mrxzjyTYeilxsTjE0eENe7Ly0qlW+RJVBQgdkMHeOtC2Jt0k0tgtmmQlMI2DcaFC/SefXnC2DOcfoUPs5Yiv0dgw8ZMtxcncMBfWgYxn1VyB6NCWqQYQujrrxVJ9JIupHBzr35yEd30ju+25rKqN9H5qW+ZZOiIr31C6YiLowTShxNBPvBUPQD8bG8QLV6bLIKt5GLVsy5FrqIDiE/l9FThZy791DYzbhJ4PxFSf5582VSeoZgC7aBb2+8s2qxVBd77Nu/Gvs6iKpTkqhie5WvJemZ/wlCFka8GwYMKtE+I3c3Fd/PQDe89Z+gQvigpseq+AuGCmeLabueTcc77q5wBD6Lz0SZfF0zJ0AT3s5Q7iACv1hwMOkeB88m+aYiJR6JcviBggH+awmmAFrav79SCzgZN1x/BRFFHvC7nk9tdC/f5ehAuVrEfOXi+9FF9zGn16kumo+FOjpCA63BwMq168XYFel7gHYZNs+bSMOeTYxO88O/qoVaFu9AnoKgd4gFPFEGq9O787dOnOZ/c4AaBuhC8SO6JQ9t4vpb0OZpK7omL0fpschnVn7xAl6LZdFcjKgHpaBZRGLYiBBTrjqm8bi7XkIMlDLHNFOUPxYlBCoX6hKcTaOMuRPQgd+T52sXAeRicGRIraJ9tbQ+Zz2YIZC4sZJW+8NVuckIyUsPYByoPA/F0O++qwWtGs8DcvnFz+iPCgwFfhGyEqsLpB83CcDA7J2XoZ/LBjfVFAxwcnqlXXEFGre5BEuQZy3leZLt0bpKHBJAoHZd7lafZddewVvhjVg+z/1XK4RZ+QOIl5rWKDJGcOZW3hpqhpKrFhoHwZAhZv8nn26MTrZcXLnqWAzhzpr5jCvNhvKIKhiUygxB6vDJwbWYYWv5NhEHf34nuNv5mnrwZfWenshZwOtBokWtbxreFLXoxqMaQzz5HiSmu/iQSUUYbCMmoGzYg3t+KIq7/kCJ8n3iYJCPoefiiWSepb0BcA7HCNhRdoAod+wnnfUTSxjIZnriWz2HJ5+ZWKdKOkHN+3EPz6PieDZbffoLiNX8+SiN5JtgbhhfwiD7jVNH1v9/A3GhS2eblDsghK/+0r7JFxAPuyHgvETcKSYoI2osjlYhMoNoRdpCIzPTzct6kFXZVgcmn38V6mLM6UvCg0WZwJQfPbY1qQOv8vDfTOoMKYdto4myNkGZEhj/e9oP+0MsY0GVXKH8v4QEiTGAPfIrztodnGtiQ9NsLhI3FpPS/XUWjgqVBG7ZH04TmVF9Emyl706dkWSxDTp/TPNhpXbSjFlNEJkFWYSIjs5cKoEWWydVC9Fhpd/WyFWgpTE5RlMhFcInIw8VzeXJuHBIJgbsGCTNlNKhEUpC4zfRQ5czq1JA/GNgpv1zBgLQehRUGYSCtmeDEwPkMB0IZcB4EQYKbs+BA6McBXaZ/EJ6QBjzDArGTL1K4chbwiULtc8InSgu0oFxbCJLdWsQNCKTbmdu45fk7I6jUN1SuKWVR0AHtATEuX6a28dDOChaE8Z9kl8qbx3Ks/mf4lISchF5wkozmNJJB+egKE4gzp/GhmCZippn+NGw/u4k5QO2n1h4axvo9fiyO/Q4KKIRNKkOyrAhetcLNeNl4aXUMHK9unbv0+y5l1H3uQAp/YIrQpE6hj19MMRPNuVTMwc9KcdfdwiJevuaBHS7WeaAJJXgp9QryX78feysmFE7dnAvHRyLSHU7B8lav669/zptdBw1BPEJV0ABFwpa1zvXh5u5g356CbxfHDtiPAhPH81dEPpdo9WUwEHnx6Yiq5K+dRrDUcZw6l9atFcV6cua1k0nQbxdpD/R8j38eBMuUPR4RIurW9nk=
*/