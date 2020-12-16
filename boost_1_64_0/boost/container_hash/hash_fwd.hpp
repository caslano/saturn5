
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(BOOST_FUNCTIONAL_HASH_FWD_HPP)
#define BOOST_FUNCTIONAL_HASH_FWD_HPP

#include <boost/config/workaround.hpp>
#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif


namespace boost
{
    template <class T> struct hash;

    template <class T> void hash_combine(std::size_t& seed, T const& v);

    template <class It> std::size_t hash_range(It, It);
    template <class It> void hash_range(std::size_t&, It, It);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    template <class T> inline std::size_t hash_range(T*, T*);
    template <class T> inline void hash_range(std::size_t&, T*, T*);
#endif
}

#endif

/* hash_fwd.hpp
rRS1OWPCAWGtXM/iPg9JiyPQirxiKznXNK8mkvKQ8WB+lMQ8FBCJhc3NQy9RDBhPsAQUgr6TKPJuVUri1KqmGcAoyaBpbxhQSDrpURJJpRSqbinfWyvlBf1Ag0gyGKk53XhJ1u2IxC2bhvSa04kX9E9rdMtIHDmJTJUREkEvGFAI+rNarpwf+RCMRUdpBLndKI2kLRONpG0iDTgZfJt20bA2dEhH1+o99A/ThbaRPQX+p7l8RLRm1isVjKcaG1RWROYmb9DkKwXTVtoggmkZuSEE4con6oNtaUDYbtgL8z0gHZ2GHa9fGL46OmWVi0QdnYLdE4zI68uZ5oiMqrqWxCNGiYybR4OoXM2ZpnGMqmRli2kF45SRUZkHV0ZUKItcPaDKu46FXzg1CyhB1tCgkjZGovJMQzonyht7kwtbDg+e1l8yVggI4MoO54ZM558CEsmcb0AiGQ0RSVXgc6MkawkpKsbZWUAhifk+hWRfSkAi6JcDCsFyIS5F4oYA+DYdx2BR/DCaEJqBxqsdLKYxGKUqNJJ5pAbNoGlzGSURrBKN0gjqs0HjiCoUPwQxBlbUXKfu4Xd2uObGbqzUkhkvYzEySS01qCQGbFAJNhBwqnzOuIKJamR/g2m3WsnWzZPNStYz7m0qkh63ku2vVI0H81C6YLyHsliF1TTBGKZUycMu3OE69Hqm8dsnmV7LVaU0MBwVkzhikgGnJCVx5Po79ZqYRK6+Y6FLnyMgwfzANR1YY+l8n2k6j6WdomkDKrmme0dKeZgRwA/BpMsojWB6p5TvwcuC4j/izmXXdRoKwyAhMeAlmCIEgnIVM24DxFUIwaRSlDppG7VpQpx2H5jxOvBwvAGw1rKdpC3Q/w+tONpp9znHXxw7vi6vC/Vgb+tFZWIEk4kZDtknuuJKRKa2GejYsyvWy37v35QVBDo7CaIXMccosd0VaAbEqFwVZb6sGGFWJBgpW0AI8VcEGLFcQAiB2bbOnX6Q6amjhshQUtnyGaMuKgqVSy+/w/tKBawIxMJoZOBN1YisKYTTNFCE0heIQJmja90AEAsXBZitgaUnhNwhfQFPX5JeL+asyrJ4x4QV6Ll3QBj5hhLMIlbT19kTuoMMyaVlnEp0kI3INkeFmAGwAxFUamIIczwXAJnEmTehwDt8SeoClZin9OjgHBshI2IZkBW6RggE2/fkIoSNgWD214Fge7gSDlbpUULujxtBGJA9k8kyY1pumREKEwHQEzydBcnGpSDVuLKO6iFl1sAmS5ae7bNlJgsSZhIvZUz3qLZ2BKjBs5QD6Fx+Fm9k5PlYpHN46Z2AutzvYUvDAK2oNp/lpdclX2hilNbUNc8OmEJTL6CoNiVVhW7GMs2JYJZq2QYwQ5Me2jWoJkMCqAlSAHK4VALfKsjgrRch840EIvS+0mVCjZ00D2JaMVPyZb/KOg/3sMDIF2GDNWTEnMSPULtjtj4DVjpiTh6ogq0KYbheOWJ8mVzVbvHFaMJUxl6zNaivuM9XsCLIBOsK/j3LF7W0GylLAGvETcB9xb40+WLG0gFiZNwTag0L9UeIWVaOUPETPIyNkOthI5cJFf6lKNHztRFlVrMDhIy3CXLy84xRSTRCZAF1S+UhwgAHv9kAHIi2Goi6ge0LjNgxc5kCMlJmJ1hgGRBOxzgwnMZrYLZzEFw4agRlwmEEJfczgm0ool8DW/QbwAxnlp6ai5VgdsaanhnALL07cSV2x+4ET2qB2JawFYoRjBqbAZx0V4kFPeos2Ma0IFuTVezinXfeRBVtCm+Xnrq+he68I0O020gQ7UqGnCU3uilBDm6GYLYNU4I0VFCGHEEN4VTzDaFU8yNBDA5GUMr8RlA=
*/