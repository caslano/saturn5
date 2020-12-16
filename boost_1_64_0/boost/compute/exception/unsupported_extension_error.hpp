//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_UNSUPPORTED_EXTENSION_ERROR_HPP
#define BOOST_COMPUTE_EXCEPTION_UNSUPPORTED_EXTENSION_ERROR_HPP

#include <exception>
#include <sstream>
#include <string>

namespace boost {
namespace compute {

/// \class unsupported_extension_error
/// \brief Exception thrown when attempting to use an unsupported
///        OpenCL extension.
///
/// This exception is thrown when the user attempts to use an OpenCL
/// extension which is not supported on the platform and/or device.
///
/// An example of this is attempting to use CL-GL sharing on a non-GPU
/// device.
///
/// \see opencl_error
class unsupported_extension_error : public std::exception
{
public:
    /// Creates a new unsupported extension error exception object indicating
    /// that \p extension is not supported by the OpenCL platform or device.
    explicit unsupported_extension_error(const char *extension) throw()
        : m_extension(extension)
    {
        std::stringstream msg;
        msg << "OpenCL extension " << extension << " not supported";
        m_error_string = msg.str();
    }

    /// Destroys the unsupported extension error object.
    ~unsupported_extension_error() throw()
    {
    }

    /// Returns the name of the unsupported extension.
    std::string extension_name() const throw()
    {
        return m_extension;
    }

    /// Returns a string containing a human-readable error message containing
    /// the name of the unsupported exception.
    const char* what() const throw()
    {
        return m_error_string.c_str();
    }

private:
    std::string m_extension;
    std::string m_error_string;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_UNSUPPORTED_EXTENSION_ERROR_HPP

/* unsupported_extension_error.hpp
5VPt/OKx8A16OmrHpd2Ubyhv0MqjsowU/s/s+PhR60+OXUSK/t5i5wMb7f1fs/39Iav/drw78DM7Ht3DjoNfW0FK+S+w+mzH/dOH7Dj/ETvOdNjxbdiQ8n2z9XPWj7ypZuOGB/LdYDf3tvr4bNtvT4Vv8EO3Uk/S5dN2HncK30nfs9+O9+dxn+H7O61//Zid59l5yc2rrV4utXp2mdWD461/OtLK99crSOHdxHfSz77Rjr8/teMV/7Xk9AbrB+y4c4/X2nj541YuH11Ein6dzHeDXd3T+t8jSA39fouNe/DPpMw/7Xz0bjaeONLO/55o5z2vXWbnv9ZfdVp7uBaeQV5/Jj+D3A+38cGDqK8hPxsPvPP+Ni55FOUZ5Hgh9xnacz5yIy0faseBtYtJsecLbVx4GuWSnmjt4Drnn49ZSYrdWbu9kjjS0KwHm8OxKLZ9fgae2bBj6+rSjk1955f2lKulank8GRuo4sk4Ms7yuiLeRPkS4/KYi7AKeQwkSWl4oDpg+Nzf8uZvUF7343Z2b93UXdqwdVdptGoG7ms5jRwOeMnhCz7e5243JSnjmYcI3re9Z+uZpb4NG8/pLg0MD0t9a8/K5wyNlQcmphOpb6MNDxm5vFDYmNPMZaq0e6rckp+rd2+WN54YbVc9i08mBxQv3hLjTekq3pXFp/38O74a480aqtxmMzitLKaFnOA4z87hlIbLuwemx6ql8YHKXjPh8qtn8hsrT+ypjgCNid604aBAdKnqxHyGh/bxxFjaNhLjydToRFX60VRz8VJ5v6mKHbTllHYnXl26bo15VNaT88xtOXjRlFw59Wfn4KXBA6WtPZsN5ThZ15+T4WVkfZKT43/llgYqQ2qH/Zm2VidLO/vOWE/fiB3eluEcSMrmDJfHQi7e6pgxkfsXxFb71q321U7L6cjjjGrfFfNwSjFeHr0eZ+O2bed0b9hKFuYS57sMsbjDe7Y0fcETjfiTCBsaKQ/t5Um+2N3VIT48upsIWvGZWoDb5mnZ9QinXmWHzUUYzdJ6hZjVaM2395oAp8dVZjNZrFSpksEeM3aCu/8FAQcNwJgnylMDY6OXloero+NlM+DKKrxYubt6kRGey9WzH9krJu2fcvfWonvxGOJPao9aFGOlps1NDlXLVVthsZvTY27Ik/LC+gTjVD2qSzIwtBfhXDxdnhii0pLH7EtCHvIzog8vzWCruXyxa9PMoxeF+EHaZB4Tc/N5xZeFZU5PhDUXf6pt37m159zu7Ts2nKNWp7xGex7qaYS30J6HWNnS6HSJmLYND7WyjeEjNiPtwetsEpPskbHoFSGuZqn+ej7LQS1LTcUtVeG5sgpfXBTzmrLQ/sziyEDr2pXFabv6UvOqsB5qqjom9L4mw6GrtS0zubgIrip+26sL3trrWh13Z3I5NMkop5bLoVlwxFaUc27Pjh7CHr84rdN8Gx5Fqr6141Ck8fLqXSU8wrXS5OhwaXxyeHqM8i6xeWGkPgcZDQyOlR2NvJwNz+8W3uBE2iXa56OKTe+W/pp0ZSRfc/2R6h0GvHt0YrRaLpUnhilD4iGPNzlRqeaxXX06jhPucOdoaXB00hsHQox4Q7HCQxUb3VOuVMGOddgJihHsVUQnr3fXrU+nLhPUcDf962Qwm8PZt0bx+a95OG5p8InloSr3i49cK/ho53CrPUMi+3UBRnsUmx0T2SOi8WaDjdSJuU+EtTIWO3pAFidztdXjA1wEJrJ8WIgjNM17PKwXcR/Za94Lr4/x0I/MXpPBabveX7g2g6P9Hv6GECfzYP7V8ZIQJ3Mt+9RDYiyQW319Bkdu6sO6orwnCB1bBXj9XYzqT+W9fgmxhNGJy8PSL+8=
*/