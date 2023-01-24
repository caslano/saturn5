// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_


#include <boost/process/detail/config.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {


inline bool compare_handles(int lhs, int rhs)
{

    if ((lhs == -1) || (rhs == -1))
        return false;

    if (lhs == rhs)
        return true;

    struct stat stat1, stat2;
    if(fstat(lhs, &stat1) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    if(fstat(rhs, &stat2) < 0) ::boost::process::detail::throw_last_error("fstat() failed");
    
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);   
}





}}}}



#endif /* BOOST_PROCESS_DETAIL_POSIX_COMPARE_HANDLES_HPP_ */

/* compare_handles.hpp
k8STOL/8ihqJEsc0bwoOb7SUXjCRHqz+YW9iPjG6j2S95+1WyW3LU+14/4rWtImYbc9tQiwXILTzXp7g0K1ZxBn4BEC4Bnkh3HBefAC+vrOqI199x8eqBucby3QOIcmzwFCz02IT/hkjaKFVVXdD4qRvr1HaFu00udlm4iX80RsuT5gx3p3wrPaBSp6YqU3JKFO8C+2k0dgYMtzPslek8Ixvs2dsS2tpaK7HRhSblpVMZWO72CsSPwQm6jHRUlf7jdPMmWCCL8Ew/JcBYlCEcPbEw1ytIiJX28nrlw0K0xHCh0gSWuQRjJWjm70xLZj+2PPpImJaMw9lMSMgT7X7SZNxMR/BUgq7cVCrygekqXaLrnbRHNb80Y+nyK1YhknxkYLDPNF2BQdZBxcjZZKvjyL5aOzFaNd4Io9wHKSZGS5r6ZooLKFZofDLSEM2Y8Sp9EvCIJAzTrlEecMxGG5+FV68N7nJ7s75Suljek770p4GDLdgXY9ZjSuf5r0b/GJZhy93RXAejL6CqVZHDH+nLEH5QSWI+jyIYwVNeYBfYdiDuAMci6HW0aNLt1o9d4JxRzulDIRNr1IxYHv4PWZgeTLfrgIZ+fhKfthaIvLfrMU4/nhxhXqLFCLeqPsCUN3yn5EWcmtoSi/cslVP7aF6ydgOpQsUl8WpHUfft1QoX9nGivOThXWSNLwWsvJA2WzAR5vTHim46I7WxW+w
*/