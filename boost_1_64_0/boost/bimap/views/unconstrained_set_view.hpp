// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file views/unconstrained_set_view.hpp
/// \brief Unconstrained view of a bimap.

#ifndef BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP
#define BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace views {

/// \brief Unconstrained view of a bimap.

template< class CoreIndex >
class unconstrained_set_view
{
    public:
    template< class T >
    unconstrained_set_view(const T &) {}

    typedef void iterator;
    typedef void const_iterator;
};

} // namespace views
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_VIEWS_UNCONSTRAINED_SET_VIEW_HPP

/* unconstrained_set_view.hpp
6M33SO0j+8FUDjZ2MOVbU3EqaxZm3G1b7Xpmyldle5r71Y9ib+8c2zM7COXV93L+HFPe+A9bg3yjo23vHd0na3nvEvl2OtYP+u/iWp8m63lnfdop9lyfV3/bQa5/v3NNhjBCazLV2B19qxnznyH+TlG7SYdnvxon5zN8TUw/vsD04RfJuUQZJ7/ejjrbPtjn1t1Id5vk7+C9XpKqfja3N/3umqh+F3sTK/Csqw8y35FvGXAMphFGx2jU2Yb3VT90DO+rSH9YX5UetgZp6pHWZTOGpq5oXXbp18pd6nx1Pc8V+nbS/cZ9lKsyLcfeICesfhdxBy2rqK6Vsvo2K1DPHeNslS8w6yLrxD7J14b66tU2Jhp/h5nn+I/YdmJ6k7VY3VgZ62y7DaGGJlpubabQhDPYrK88KPajfbXWg+pmwqElxUW2HaPv+U7xd5xvqPWDto9g2L2jx//aHm7hPG6+HF9LZ5vAX3ibSNW8o/+cUVuk+afx7SVx+3V0XCPXh7RPflLCnuBL9/klXgVSmnNrLEf7KZYwjnDLR9NXJ0hcpCs0c6QakZvPHCkZt1HMpfX7DLnm89RT3Djip2EWWe2R9ZrrbBd/u61Nui5VI3Gtnutcl7q5s1N3usaV2A2mHTa1iJOzDWq7eyqDsBlbPA3ttrgeVkl7bNh6kN0muU7UfYQykvYXbJPTPNpksUubLA9vk3ttf0s6Rz6f1nlXrml/8+eYJ9T1zLlyw55Re8+1csOeT3vPsXLDnk97jRVULk3kpu3nc+x/xdxmqhb8mLhAW+wLW9lrCCZfdSLrnacq29+0i++72Pbz0B2cbNrYRyJzkdp91pbutr2p5Af757v2MxNN2Nex19UQLRvujBJ+gvhdpX5b5gT0Pc+dV2bGh5fk2XJ9JaxCl7AKI8Ja41EfJhu/vczY5B9ibxYXWS9a67VvkHCzYuPQYHAH/XuCP8PZ5xFeqM9b5/ZMUdftWkg4L8fGsKYoa3km7+JDzx0jwns2+FwqVfuYIslTs/72gcimxrmNU6sIr5+EH2elip0wu9n2rb7RVjvHGmDNjLnzySDHGuAXEu71vrvxO5kVyixdAxwu5XCPPwEtIysZX033NfOdF/NT2NgnS9ci35P0nutvbP0eXTtJfFe3xTfW38LKlfOMruX8Of5D6APHU8OuZj2pja/AWu7rZj3ju0PGYp0D6Z5XWWNJmgdi+0zi1iQueI+15B4rcxfTF4TG5bVV1VKclKfep3eJ/y/8D8TEWO/ENLI+iXkOec6Z/PmU/PmD69i+tfbvX0kYj8fm+7tav4ptbl0V20HPscoiYbziS2e3w5MYyZ3jS5OwdmQF4jpnpt6z9D4wq0ugDrTW9lUt9pGxd8Z0tX72N7cyNOwjTNgbyZsCCXu+r21gfKJhSxw13IclnOP9rdCo8zX38m6+TjHB9vRRXmB8nCV2Z7leSi3vacq1mTMfWWrroP3CTkn/T7GPUmon+n60zovxWz/6h1ljY/OsdJGJLN+e/lTKby0hTegq6/YxPXVsk5kSWFOqKA3lyZFdQusP1fGcVr2Rzj481UXvez8JO0mexyztLBv/yBqUfxJLCE3i+MtOC46P1+s90+v+7JM49FV7qH+RdWcNP4/wHwusVT/IwkeU/r5gPKYF5RLqvk3y9/dcz05V+YVG/twZGmaUzIqQzGAvmfXIrJN18XNjop4tqcxuk4Zzn5bFmwESvXrj17aHCfddr3D55lHDPa+VhNvHM1yTnwtMuOfluq3j56pcck/mVna5nvdBYs/4GJaEcoXplLCfwGV9WRV+zqaMT0oVyrw7VKfn0aodei6l7qSYfmKN2L/jup1oEX72Yhzt2k840zw=
*/