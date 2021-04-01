// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXCEPTION_HPP_
#define BOOST_PROCESS_EXCEPTION_HPP_

#include <system_error>

namespace boost
{
namespace process
{
///The exception usually thrown by boost.process.
/** It merely inherits [std::system_error](http://en.cppreference.com/w/cpp/error/system_error)
 * but can then be distinguished in the catch-block from other system errors.
 *
 */
struct process_error : std::system_error
{
    using std::system_error::system_error;
};

}
}



#endif /* BOOST_PROCESS_EXCEPTION_HPP_ */

/* exception.hpp
2vrJSKW3kxgFOclmje2DwFEtwAAhrjM6RBnxQ/joDP7+6458XSDxKmQRNOpR+x1cMiU+J+1U4QdIJy5kw3qgj4oNBXExi9HOWv53ts+8qu6aOwlkzNf9POLwOPDVqVECujQ8CAO2u7dzdmpvggQY0YnOwxvoX261f5Y581YA4Jk5lAtbpbGKdCiX8RuMv2U36KmCQCHscmk6IZ6+FJ+wKfaqVUj8kDrAofkqNSffz6iQYcLFo3rfaRPJMlqht3zXAisTJUDfcbydPSlXommDRP4Nyl7ohXwJwJzzuADrsdcdcy4zwdCMo8MqsfSDdPiIll3BDeZ3YcFsb+gzVEPQVIv92HaWjpgm97/Ic2s6bkd/+EQCD4W7llc6mhal91OuNUKhfCMT9BPEBIThpK0Er/YJqmAS/x2yh6ds8TOoiRqrYjZcEmqUb7PEXny6vubTCYKyMOo2guzAOZp670xFsloaPWG+pHjD5aasGKVjgEEaBrRN6A5jhjTEXI1/Y8IzCJds44io8iswHS5uFayjOXrqfGZxz1I2NHF5J5bCppi65cxBk34h8YIlrA==
*/