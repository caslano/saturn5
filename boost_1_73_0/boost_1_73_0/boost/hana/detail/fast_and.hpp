/*!
@file
Defines `boost::hana::detail::fast_and`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_FAST_AND_HPP
#define BOOST_HANA_DETAIL_FAST_AND_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <bool ...b>
    struct fast_and
        : std::is_same<fast_and<b...>, fast_and<(b, true)...>>
    { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_FAST_AND_HPP

/* fast_and.hpp
0K+uEhEEv5j3ePBqhItefzwRnqZLmJIjLJlJvL8M53MGFCuJmI+DUmIG4Uv23XS7wWgEg0G390D33ySkwQESEAKdCv2gjde0PMntKuMflxNDoSwfl0CjeXNo49WcBSBnResAfU04jvAU9SOiVLpXjXGNgTjouwAuYQeDNXoSuEHkEkA8ILL0MODpm1HYRnfSGUVO5roApkEU1kapjyaD0vxgXUZ2NakDKq/ZeRgu2R26eMhGvM/eBPQs5t64fiDuTi691cKPuZMsGUIsTUqf2B3mjvHAz/RSFvc2x9wdlYLzkfQjpZkp390UEEG0XvGkEa52B5PHlOZkXavj4D0kbvgqbnfeufeRbOMWjXcuIycENptG5LdLHr2wGITXrZiG4s37qNrmzeN2aKvatOKKzwP3b+3zuK08t6FKu3o9R0JBEYWH41l6bizmF7Qpn67c6oTNz1endC8XsJ8VQktOptP+izkuDN9A3ErBxblUBdBModzcoXQBXrmtBDwOp6Zc6OPCV3pR9CLPKYqvkgMZ3cbR7p71e5hz83Wni+59Q8l23t16uDH0KfEQpWHxA1yUYz9wk0N8GXBeLi0ZYwz5gQpGL80ZKGMBVcae8VpWHfvcCR5KUeR4LNPpDHm6nqlI+CK4Bu20kVyqrCmF
*/