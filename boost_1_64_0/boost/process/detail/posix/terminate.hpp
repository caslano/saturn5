// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_TERMINATE_HPP
#define BOOST_PROCESS_DETAIL_POSIX_TERMINATE_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <signal.h>
#include <sys/wait.h>


namespace boost { namespace process { namespace detail { namespace posix {

inline void terminate(const child_handle &p, std::error_code &ec) noexcept
{
    if (::kill(p.pid, SIGKILL) == -1)
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();

    int status;
    ::waitpid(p.pid, &status, WNOHANG); //just to clean it up
}

inline void terminate(const child_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "kill(2) failed");
}

}}}}

#endif

/* terminate.hpp
e2B3uBf2he/DbPgBnAA/hNPhR3AunA0Xqf1unl9fi2c4N8AphMWEVYSthL2ErwnG1MLr9FSZ+v9jg3n9VNef2w7zT2aD2W2qK2iH+St2mLn0UaAt5pSprqA95v+4PeYyzuFWwn7CT4Ry9wTtMoNbcAtuwS24Bbf/p+0Ptv9P/r2+/f++jf0/skD7f2RW+39T5hRZ29adeKYpoWQuX16dxi37rdsblrI8+rsBpixEfzcAnY6ShRb+ZoA+RpjIb9L74b68ej9C9rvosqNkv1OzthxQyUgrZbS48faWOl+MyJrpNBVkvx2vgc06VbT5NgFyW1+HBZa1EGY67ddC6HPUOH8tBD4/npGrF0O44LUQThW9FoL2ec8q48vptSepoXgyBrnUYxyjq+hv/HuzzpR0KY4rHHHqewgqLyW1j3Zq3bOS29v+Kx3uYolv46iuygoroiwlL/J7CDGwwgniaaXHKKl1y7xYQ7YxMhfdbDPX8DC/bc5b33nlX0V6jLYhdULvcvt1sGOkjGnoYIc7qik99CZJmxdVit5qZuQ6v3HOM9a5whytPBtCpDydb17IFKO96wPXCmc8bemM/Yo/bxwX6blIp9R9u1QspX9Ors+2YLSyISooq78LLPJxyE399YC0oRZbla4/estdjr1XM61zzpQ6xEo/5pP3Pemv3tGHopxFrhHRVOp3v3ElRxxrxOnzckjk70VucpUOU+Wrfiil7K3Y121b7m7hyQ8xj8FaGpZv9x85RTqGYGm0Cr3p2aGOVsbLjqu07UL5k974KK0HHyttm0x8jrL79vfvfsc9lHqCuLWO2tLOXrTzkLSzXfR7hduZlKNswRerfvxE5rXBGBMpG3HkEcjfD/gGxtfSried4WiiElSdkn5Axlu5KEZ1ZWabJlxlacbttmtqlIWHjpMeewaP5Rsi46UNk6TeWRz7UjlOePQcVe8SYlvGZ5z932ogTeHvOxS2U2sl5ZXV/VZD+vGgUc7Il2MsI/8/pW9aR7/DMWx8QiTdAtKdk3RXRW8indmmlNS+ef0lzSTSuKS+9aNfLFSWTFRU2ldWLunKSrrK0U9a03Gtqs/W67H3ovTpVEcKvbTWWEpa6zhe7YjlGvSen1jJn6Hb3eJ7b3yY9NESjmfWt68YhfrTVZd01fS8lSfHe9zxI8cqoexAPGeRcfR4v++K5HmD+8AIvrN6hRp/qk7Y7ixg/Lkdk43NMv4oQ8dd5ZqPN5u3D1Ko0xnpz2ujt1j7kz5I518ZDzBWjp2u2m2WE2uUd5lzXF/mYzPPS2dIQ60SAuYdt9HFM8pT39jmaWxUDLlZzsVM6rFF6jEk+gz1MMvM5rvipu1Qb7k+e3lKFGrrAiNWfz/EZ9HLH/pb5A9JuVWid3mWGj+FRRj9o+hDa39gseDtj6tcldwRZjlyzrZTr6K+G7OKuINS9q3RH1Jniw+Svj7vkXGeyUzks7cpjewbmeerGjVVP82W83hZRDds6UahBbjRcXHo/LAKxteEtuEfqvPtr+tCR6Th4roezJxPfj0OaoeXR3NxH95o853LPN3DGhvPhN0s/VjFrexA+/nqPZx6Xy3j/ueoKYXmoQFcG+a8MFHmtqdZN6GT7bw9l3LekfYnRf+TcqzfzVHdpPuhlORLoI+iJO/j5N0neW+P3qfyquuCX5BXN7TaGSbJOQ/nbql8U6Tuq90haICyHJnGRc5RhgMPoGtdtY1cl8d4jdDKnaLnmoOSv66bI7vVWLTcJys6b3IOMTY4Pc7N7r+FeuvWjbpVlPjy0Y9RtwCfLj0W60u5tbXtWXfZD5P2DaCM1dK+idHR0YwNc27U7fpExkEda//nJKXnqvPNuJD8BWHLjW8=
*/