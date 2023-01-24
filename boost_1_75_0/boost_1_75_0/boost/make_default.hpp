/// @file
// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_MAKE_DEFAULT_HPP
#define BOOST_MAKE_DEFAULT_HPP

namespace boost
{
    /// @details A considerable number of libraries require an instance of a class
    /// provided (storage created and initialized). For example,
    /// @code
    ///    Type result;
    ///    ...
    ///    istream >> result;
    /// @endcode
    /// In generic code that results in the Default Constructibility requirement imposed
    /// on every type 'Type' to be used with the respective code. Inevitably, that requirement
    /// a) either excludes all the classes that for various reasons do not meet that requirement or
    /// b) imposes certain (not necessarily desirable) design/implementation onto respective classes.
    ///
    /// Deployment of boost::make_default() eliminates the Default Constructibility requirement with
    /// @code
    ///    Type result = boost::make_default<Type>();
    ///    ...
    ///    istream >> result;
    /// @endcode
    /// Classes with no default constructor can now be included via a boost::make_default() specialization:
    /// @code
    /// namespace boost
    /// {
    ///     template<> inline Type make_default<Type>() { return Type(parameters); }
    /// }
    /// @endcode

    template<typename T> T make_default() { return T(); }
}

#endif // BOOST_MAKE_DEFAULT_HPP

/* make_default.hpp
476+eET78Wjtv4xvfLSWUwBxqn+IfzOInwHi5/4hXqQQGYwqAY9tr/fB41+va3ic6b+MdFZLG0C09Q8RwyDOAsTZ/iEGMDwYYQMe2X3xSPTjcb7/MrZ10lraUcjoH+IdBvELQPzSP0QVhcjoAIgOxOPoa33w2P0anYNdANLVfyETWSEXAOICFjJ+Zp/Zc9tMjX/+0H8Zvg6K6o9Xng77On5tOnxCITLYdAA8xnzaB4/rP+1vFnfHwnxcyHIzIobctrv75J55t9aKK/DFsQzH1isTsaXj14j49C8UD0bEgEdLbB88dsVqeFyBtf6dlrHkzJWJuPqXXyPiYoYHI2LAI6YvHhEUjyXnr0yjN//yazSqtNNqGI1CNQfv6lNNw120Gmyvr/9CNrNCGI1CIbP6FpJ1l9ZnR/svYyEtY8kPV6bRR9t/jUbHMjwYjQIeH77cZzq9+bI2ra/Ask+f/7UlfCeDOHFllv13CpHBWDbg8eYf++Cx4o8aHldg2cWslqtIAZPO/xq138LwYNQOeHz9Uh883C9peFyBZR85R2u5iiDx2blfo/Y3KUQGo3bAY2ZfPDJe+jVRI4dVcxVqj2PVMGqHalof7VPN/ke15l6BI585S2thHLlfiF0Mgskz/UJ8QCEy2IQBPJ7ri8dTFI+MbgDpRpCiiX1mzJSJ/fBKYSqU7f37YEL+Abruc/frLI1DdJbZ4G6H8OmlOsu/
*/