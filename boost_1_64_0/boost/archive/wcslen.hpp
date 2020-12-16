#ifndef BOOST_ARCHIVE_WCSLEN_HPP
#define BOOST_ARCHIVE_WCSLEN_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// wcslen.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#ifndef BOOST_NO_CWCHAR

// a couple of libraries which include wchar_t don't include
// wcslen

#if defined(BOOST_DINKUMWARE_STDLIB) && BOOST_DINKUMWARE_STDLIB < 306 \
|| defined(__LIBCOMO__)

namespace std {
inline std::size_t wcslen(const wchar_t * ws)
{
    const wchar_t * eows = ws;
    while(* eows != 0)
        ++eows;
    return eows - ws;
}
} // namespace std

#else

#ifndef BOOST_NO_CWCHAR
#include <cwchar>
#endif
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::wcslen; }
#endif

#endif // wcslen

#endif //BOOST_NO_CWCHAR

#endif //BOOST_ARCHIVE_WCSLEN_HPP

/* wcslen.hpp
c9OvRul3RfpIG1m4isW5e0nZemaOeJdbcCCCOyww/vXJoFb5+Yv8Qvugh31RQjVJXFJp38mcsD6peBdl9ViXHg5BzyFJsx2NZpAJrOfVRecJjw21i25lx1am70DCRBFSJdz0IRLnvv4YO+GK/bNEY669PtzLe/vfW8WPPfV+fKRV/OhF78e3t4rPt+T9+FpW8Stnvx+vtYov/P378U8TcuPPn7SOD1LmmqeJM1iwOUSTNay3aYYNeuKmE3WoB/Y3TPzMHp+uLnaRT6CmDoaJKQoPALn4Syo/1kNj7pFQVK90gtjQRxaN/eZgpYFYu4kaiJU4jB+hNBAtRAPxIsvJbC0gfD2P958TEivPHtTFtXYU639xmtx7hnmObSTsBbQzJx7OiYdYJ95WJP6tOfFUOXMdzwQdy4U330U13AXuVExXF+W/qeYvVbgurqPI+bMs0a1efoa//43N3/+N/P1vbJVpJ5GpX+4dTRCZOvAqOTGzyWJNC8/2b9kB8+9z+1Sqv2zvVXwRtu4R1aNPFsRdF9wjZpjwzGI2keOMNp33p8HEnsBmNGexM1ZTabzUVRABc7ZYk4ofzWKLNtZ4eVTET01ehyxEV+Wfzb2yNHkb+8Y09tPsUPshqH9M40/Qv5zXyF3FA8o08OXoKDbXq4HLvHAOFgB/jngTHNL0zE0zv3Waxh38ZVM3oaQkj4b0x/DcJEypIYvaShaT8FrTs50wWLzaQeRTW1LnRUpIEOGUm0lnyU3O5twol5jGvih0RjYXukxGc1MqGkG6vhSuvC6uPJB75dXcKzNKoFzbEZXhjJJtwI961adgRZU77ZgOTcJz/uaFxtTPFt89fC5a/ZP2tP5LzsrUJAQBIW2s2a10DzJp6HOs0IfI2esRSuyE8a6O71ib1BsOQfKb7OKpwkgkGl89Nb0Bf70vpbR/Ike8pa+C3GnXlHlPQP9rg9G0U4zxt7fzVP3F78dvu8xrF/AtiNAaXthHquWJx95aCiHPnYvj8M7QzdVxiLyr79O2flT9wq0wTBt5QV+va+FqnJmkjvZ2V2lCEmPUU/DjI74hprLLUatMZXPYT2f/MvvH2U9gfwv7q9lfxL6vI/nj+fdQ9ruzP9zq/K3sb2c/jv149nezv8cq/X3s72f/7msP+J3ekH+Tf99mX4TL7Kezf5/9h+z78vn52HdkP9vq/IvsH2X/R45dzP5g9oeyP4z94eyPZL+vHZWnA/t6y0u0Wh9nuA9zfN5lwqhdCve/FBbbDvWxUmq4plFavzCpaFkvnIR9KLJGFeyvi7qpygyP/YMKA+G6ZAcOjnwUJuFqCVfjPXll/aX3hLz8wiUdemWHyQh62DfG96wGoj6FSD6o8TrDrRw0frpslSM2MonIr5OCXML7tHJ8dj7M4aS+z8Gw0idD+yQ1k7y9aKNkWj3p0NwlW+eggV2h7ToH2MfAphFh/sjoUBejL4aK/0K53noe9TxKerirsqB7TEz06v8MoldWpH1Wkj7xkJfxzjzrdJTy4q58Ue2pEX2Gl8OTM/g9azP58GB8HkeV6AXqRT14N3cedEAyATsL8sYT8Gl3fxZhj1UAjecakN0FNiIEeRXt2p6GRCn9NiS44LgFHUvqNfiDIx+cTmcG4XdRBKWos7B2gUqRor6PX3jmCMtWfsWx1b0hCYT9Q4TpUxzt7K3D0Xx6ulPCYY6+5kA7BD52UwJx4aTHaC+WYyrz77Wv8m792OnCAhKE3NxaoTweP/F47Avw43EhI0vSQX4+O1Bs+SHL3SwBq5c3EM/HT3k+VfiJqGfiD45y6tMzuVrf/EzO1zc/k5v1338mFxEmtSPp2tsOhwsycadbNxg/1mCjdTtPI0w=
*/