#ifndef BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP
#define BOOST_ARCHIVE_DETAIL_INTERFACE_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// interface_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <cstddef> // NULL
#include <boost/cstdint.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#include <boost/serialization/singleton.hpp>

namespace boost {
namespace archive {
namespace detail {

class basic_pointer_oserializer;

template<class Archive>
class interface_oarchive
{
protected:
    interface_oarchive(){};
public:
    /////////////////////////////////////////////////////////
    // archive public interface
    typedef mpl::bool_<false> is_loading;
    typedef mpl::bool_<true> is_saving;

    // return a pointer to the most derived class
    Archive * This(){
        return static_cast<Archive *>(this);
    }

    template<class T>
    const basic_pointer_oserializer *
    register_type(const T * = NULL){
        const basic_pointer_oserializer & bpos =
            boost::serialization::singleton<
                pointer_oserializer<Archive, T>
            >::get_const_instance();
        this->This()->register_basic_serializer(bpos.get_basic_serializer());
        return & bpos;
    }

    template<class Helper>
    Helper &
    get_helper(void * const id = 0){
        helper_collection & hc = this->This()->get_helper_collection();
        return hc.template find_helper<Helper>(id);
    }

    template<class T>
    Archive & operator<<(const T & t){
        this->This()->save_override(t);
        return * this->This();
    }

    // the & operator
    template<class T>
    Archive & operator&(const T & t){
        return * this ->This() << t;
    }
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_DETAIL_INTERFACE_IARCHIVE_HPP

/* interface_oarchive.hpp
Q+jEiRNIJBKhkZERdPz4ceTn54f+8Ic/oD179iC4VhQtXboUdXd3oylTpqCoqCh06tQpdOPGDaSrq4sKCwuRs7Mz+uKLL9CBAwfQ9u3b0evXr9HKlSsRXCeKKioqkK+vL3r16hV6+vQp+uabbxCVSkWWlpZo2rRpyMDAAC1ZsgTZ2dkha2tr1N/fjw4ePIgcHR2Rvr4+un79OlqzZg2qrKxE9fX1yMXFBdXU1CAWi4U6OztRUVERevHiBYqPj0fnz59HGzZsQPv27VsBBwBDSP5SSPyzkPT3IeHnQrI/hkT/FpKcBwkeDsntBol9CJK6FxLaC5KZDYn8JSTxJkjgYkjetZC4HEhae0jYnyBZ50Oi0iBJD0OC2kByNkNiBkBS3oKEnAfJ6A2JuAyScCsk4F5IvmFIvGOQdDGQcEJItmeQaJ9DkrVDgjVAcplDYsVBUkVAQhVAMjVBIuEhiRQhgWwhee5A4shD0phCwnwNyeIDifIckuQtJEgjJEctJMZqSAodSIiHkAwLIBHCIAmOQgLsh86fCx1/IXT62dDhNaGz34WOvuiP7J13PJV/G8ePTcmojDI6FJGEJKSyiwbKLIrDOUZmxyZ7h5CUllWKNIiQrIioZJaiUPYoymzIc3U79dydTv165uv54/m+Xqe7+7vHdb0/1zk4Nxg5GwbsG9IFMGxXMOqjYNB9YMxMYMgvwYjDwICDwHjrwHBjwWidwWCnwFjPg6GWgZHuBQN9BsZZA4ZZDUYZAAbpCMa4BAzRAoxwEAzwMhhfMhheMRidKBjcBzA2CTC0PDAyDzAwejCufjCsw2BULWBQWWBM4WBI0WBERDCg22A8M2A4V8FoNoLBrAFj2QyG8g6MRAkMpBmM4w4YhioYBQcYxDUwBncwBH8wgkCA/wiAfzVAvxeAHwKwlwHQMwPklQHwowD3eAD7MoC6AACdBWCuBSAnAMRLAOCFAO8YAPcwQPsxAFsSYG0KoK4CSC8HQL8COD8AMG8HKG8BIFMBjJ8CiA0AwrsBwIsAvpYA3kcAXXEA7mKALRZAmwOQPQ2A3QVwrQCw+gJU6QCoBQBTKQApF0C0FQBqBPDEATh5AJq8AExWgCUngJIbICkIgFQDON4EMN4CKMYBEBkBhhkAws8AQR0AYAPAzwfAFwHQOwXAMwbYJQDo5gByTQC4ewA3DQDbNECtHYBGAzBrA5ApAsROAMBMAF7UAK4dAC1pAJYVwGocQOUHkHoNgDoLcBIGMMkClBQASCcBRjsBRKUAoXUAIE+ATxSAxwGgcwyAMwmwyQfQzAJk9gFgEgEuhwAs2wAqRQAUIYCJCoAkDSDyEQDCAPDQB3C8BWgsAGBoAiysARRyAImLAAgRgIM3gKEWoHAXgNANMJgAENwHCCQBAADniEyBBCFSCahFZBqwiUgaoASRWpB7BG8gr4j8gLwiYQOgDpFAkFYkbADcI5IFqEVwBxKAyBigBpEwkDlEpgGJCK5AehFUgrQjkg/4Q2QRZB9BPYQDiGQBHhFsA5YRyQYpRKQWJByRPMAoIk+AWQTbgF5EAiGcQWQFcI0gENCLoBXkApF8kGIkjIDQBpF9kC5E1kGKkZABZBORUAgZENRCqIFIB8gYIk8gQwj+QSrBc0IQRIO8IqEU4BuRPJAeRLZBUhF5BNlBJBlCHgTdEGogYQaED+BRJQjyQdoRzIPMItIL4Q0SokG4Ax4mCZ7ai8g+SBEiKSBb4JEERE4hFENQv3LlSkSSQaKRsANCHySsAylDpBskH5EckHwklAM5QmQDJBKRdJA6JGQA2UNkR0xMDJEUkH9EZiHEA0/FIuECJESyIfRCwkEIE8FTCxD5AWlEZB3CEvA=
*/