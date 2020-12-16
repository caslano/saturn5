//
// detail/reactor_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_FWD_HPP
#define BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class null_reactor reactor;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class select_reactor reactor;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor reactor;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor reactor;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor reactor;
#else
typedef class select_reactor reactor;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_REACTOR_FWD_HPP

/* reactor_fwd.hpp
9sy+kNvsmf2A2eyZ/SVm1YcHSNyqDw8EbrNnDpKYppsODshlezskgEkdbSgw1Z6ZBplpzxwGuWnPHA65zZ45QmIKIrCRwGz2zFEmZuj9o4Hb7JlHADPtmemQ2+yZYwKYLI+xwGz2zCOBmfbMcVJutWceJXGrPXM88ET2zAnAbfbMiRasCNgkYDZ75mRgNnvmFIlZ7ZlTgdvsmdOAJbJnTgfemD1zBjg2e+ZMYDZ7ZgYw0545C3KbPTMTmGnPzILcZs/MBmbaM2dDbtoz50Bus2fOBWazZ+YAs9kz5wGz2TPnmxjSlAu5zZ65QGJWe2YecJs9Mx+YzZ5ZAMxmz1wIzLRnFkJu2jOLpFyIIS+G3LRnlkCu2jMXQWbaM4+G3GbPLAVms2cuBmbaM5doctkGL4VctWcug8xmzzwGmM2eeazErPbMMuA2e+ZyidnsmZyGco1DLdNs8dwVUm61c1YAt9k5wxKz2jkjErfaOStVXOlnV6pyVetAHVml4lwcIh+ikBt2Tlf/8e2UxyXm+PbQ4yXHak+tsuPkX8Sj2o67k/X9eNQk5vjxqJUcq122LjHuP2d1gBO0y9aDY9plY5Cbdtm4L7fbZRuAm3bZNZDb7LInCOygdtm14NnssuuAqXbZEzWZfKdPgty0+a2H3LTLnhyQSz3tlAAmw9sAzLTLboTcZpfdJDGrHnqqxK166GnAbXbZ003M0M/OAG6zy54JzGaXPQuYzS67WWKa7nt2QC7z9GcBTObpz4GZdtktkKt22XMgU+2y50Jm2mXPg9xmlz1fYla77AVWXPYVvwCu2mUv1GSybm7V5DKMi1Q5+t2LITPtspdAbtplL4XcZpe9DJhpl70ccptd9ooAJtuVK4GZdtmrIFftsldDZtplrwnIRX27FnKbXfY6YKZd9nrIbXbZG4CZdtkbITftstsgt9llbwJms8vebGJ4t7ZDbrPL3mLFisTYGTDTLnsr5Da77A5gpl32NshNu+zthlxN6x0GpqZ1p4khrXdCbrPL3gXMtMveDblpl70HctMu+ytVjuf+GrL6iMz++IoYY/eqGKJLGD/jPh3z5fezvJa+PWUz257kD0BeBPvrg7iX7RXGwFges9ohH7ZjZTDhibEwcGx2xkckJu2M6AN2AQvaDXHGLePxwHzeR1m+xmpvfQyY7bv2cQtWhGf9jrDasdFAHj4BuZeHT+LezMPdJI+R3JYHTwGz5cHTErPaTp8hfA1wM617gNnS+nsLVgTsWQvmLoP5gvBu5K4d4TgdQ88/PbH+uEvOqrvi2ORXOw16doLT9Gv6Nf2afv/zv+bkKp1Qivt31uRl7oHxYp2N+DNWNWpFQ7QqPGrM6DGj0ytHrYmNTR8zwcfWjh83KkZnHEfCo+ojVZHyWMRjVNSvq4vXLgtXVVWXR2tG166gRYWTnakpznLHed7p5LR2Hix3/OuCaEV9bay2Mt4vrXBYv/w6WnAYPZGGYPtl0vn00Spa1Zns5KbMpz2yRjsdOa7fhUT8o+Q6kKsg9+dp9N+mrk7I2ZhVVbWAnuvqFdNTvu7vkGxVtCYWz8rNdWUZKTnkP5W5i5zu9H97ks0Lef5T2d8Ax/VXGT6hkFJWW8OcTo7H6eJ0JU5SssupqltTGIlF6tfQgkYRfoEf1hinv9OG/LqykNOfZW0oPVkpM3ld+pKUZnSdMJDS1sPt51I79rMX1awU7n9TUtw9yt005Ye8NAn5RLapuHIZ5x4kd59D8SS5Hs9mFAu3H5vZjPKT+7Ftl1QW3tP8oz8/fMOQHy/fuvkGxykY6cpvuWZb1mnNk36YVTHhlzVvTaASu5zls/Mqerxd+sXIVnW99m046sAjjvNXljc=
*/