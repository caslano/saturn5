//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP

#include <boost/utility/result_of.hpp>

namespace boost {
namespace compute {

/// Returns the result of \c Function when called with \c Args.
///
/// For example,
/// \code
/// // int + int = int
/// result_of<plus(int, int)>::type == int
/// \endcode
template<class Signature>
struct result_of
{
    // the default implementation uses the TR1-style result_of protocol. note
    // that we explicitly do *not* use the C++11 decltype operator as we want
    // the result type as it would be on an OpenCL device, not the actual C++
    // type resulting from "invoking" the function on the host.
    typedef typename ::boost::tr1_result_of<Signature>::type type;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP

/* result_of.hpp
KgdStY+D9tXlQCtBU9nGNZdIV77Iy0HZGoGiFEbTRr1S4wFJKdBg0r8uAeIkjco+pGTHwdxVAsVJ9sq0g1Smc0FTjtUtFar7JJm65SJ1nyhRr98pQ0KScqRJpz/oTEqwYqJytP6lWqYqTlKOdNlrl0nFSZ6wwnLzTZ5mv/FEK0PiJOVIo+HoeQkSJylH6l2XapyTlCNp16V64iQijNu6On6r44m3LovICj/BqZp+1emPdG0yhvN0fbp7eroYjTvd3m/Ax/G8u20Rh2yAJMAtFMocQXUEb3ghs6SGhZXLdiTeT2eNmOtUl3Ubcruo4V+oZoDP7oA9pw6j9WntZKYoU6jfgAKeG2JVsGY8h5BqbWdWlfxwQaquVyXnKK1biVfaRuW91dUP7+I3ySy5CftGwOhFlYIopAZ05PArg4NXWP9UG3QVVflUbX2qNs7JbxenP758hv+r0+nJbPav+PEUHuHr+Wx2Dvu/DdXHb+ffDqtZdmGwgWf37gIWFI/JpTSt/GriVciDfVEJJxUoFV1NqBMsx5o7xoIBdT+hhrEtJepHnVxxJdW3dhBlDug9VfTAr5mSTNxtO1QTdCixqtyR4YNm/G5O0xqSS6i5ndHZfS0Dwe1/n1McsG2rUDKJsqk+ld6cP7/vLm6aoH9B
*/