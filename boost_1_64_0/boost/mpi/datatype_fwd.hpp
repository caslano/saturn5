// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file datatype_fwd.hpp
 *
 *  This header provides forward declarations for the contents of the
 *  header @c datatype.hpp. It is expected to be used primarily by
 *  user-defined C++ classes that need to specialize @c
 *  is_mpi_datatype.
 */
#ifndef BOOST_MPI_DATATYPE_FWD_HPP
#define BOOST_MPI_DATATYPE_FWD_HPP

#include <boost/mpi/config.hpp>

namespace boost { namespace mpi {

template<typename T> struct is_mpi_builtin_datatype;
template<typename T> struct is_mpi_integer_datatype;
template<typename T> struct is_mpi_floating_point_datatype;
template<typename T> struct is_mpi_logical_datatype;
template<typename T> struct is_mpi_complex_datatype;
template<typename T> struct is_mpi_byte_datatype;
template<typename T> struct is_mpi_datatype;
template<typename T> MPI_Datatype get_mpi_datatype(const T& x);
template<typename T> MPI_Datatype get_mpi_datatype() 
                                  { return get_mpi_datatype(T());}

/// a dummy data type giving MPI_PACKED as its MPI_Datatype
struct packed {};
} } // end namespace boost::mpi

#endif // BOOST_MPI_MPI_DATATYPE_FWD_HPP

/* datatype_fwd.hpp
ZNaUIrMmt33czkx8qgewkTPYRs4F5yBGfm6rJKA9NP+G2MiJWdNgRn4GG/nJwOpmTbvSkX+yd+zxbVbVJE3brM1IuhbWua4bbMCwQ+cyYGNDB65zjAW7uvBQUEDEEkBRWp7rWJcVm7WRTjscWnTK1KkFp1YsWLCdE8qc2o2qVauWUfXrUv1FjS5IpZ7Hd7775UvSPVHU5o82uc9zzz33vO7jfPjoB7L8qAYix5pSBiTHmhITx5qO/YP8evVift9Ofg9Zficsv90XJv+eZfldRfx/MGGKly6XGrbpj/y1wROS2C2ZJQ/E5DLzqVULoS1yft76VXmoY0aK32nRr9gV/3En3bEkOaIt4Qrh8h2h2h22mjcEbeyj2m26KXEtVIheivnr386XI/AeUysp5G80mn/pt3rXeMFxu2wbb2eWtT3sb20sbx2eQqLJhZHXzgvmUL03fNN8Z/HPWcYL/x1YoA3G0AE+tXPpqiq+PdOm52wLaTmQ2YbPE0QC+yq1qW/CMl4KL9gZwVOjXUqudYJA8HXBzUO49ylCjY6DeH0Hsvx7CgOg2MHxzR7le++iGlmBPYXlPVyv0b9HrflOetlpD+yxf2OW9p7f4L0dU33q0VpfMYAuYLK+57PK9xT6e7CeEcI+O2O/Ig+gX6/R70u/ln4NydmZqWlbmqalWkaIwHZOhyUAQHWIbEwAqjQAUhKlM1PTaSdA6h0vkkBaWSbnmQGBSU1u58nGBDg7Lah4x4AFFdnjTE5WuiFJPJxM/Uq2H/otMPr9ya+w3/ZQbbtt/VmwUALtIJFu2V2cHQNFklZTY6CjUttN79V4oSQu03Zcr8GcjmIWbXXdWJgKRvBo2FYuDOoYdL/Ld6As0D47sCsc2AW54fKdjf5deCd4J5SHZLwTvBNX6E5euzPfSGuXA77lyJXJV/j2CnEYjr+/9jeJ188O1X/3h95fpfOvvzDLkytEoDTpAmUHCJQhESjnHVICZaUIlOk7MguUP/SxQNmcbRIohx7VBUprqLZVCZRgp0mgXJ3NAqU1SaC0WATKJ35hEijbRKBsY4GyLexvaSxvGT4l2yRQcqne818zC5Q/Og2BsgsL7KgAal2jbT7bECg79JymkJYLmTtC3SUgUPZUas+erQuUXbBKIn5Yrh2Kl7brAgWi3HYpgdLhe76xprNsoRf4yPT94ZpOOJKouE6H7wDl2mFFT98NuVAXVq8SKu3EtzqhMizknH5cyKYWjF6zAp2F5dK3IVQ6fF3Ueh7wkuk90LoSgNkZ+1asGPr2Gn1v/rn0bfDFdp13dRb6uyBLGt9/MMOomenlpIcLWKGh4rajcisdFxgdC2e0DNqKcJ0zdhbCfX+/Bd2Z6mWlBxmAkALQKfJUgeq+nwlUSha0Z+rZNk7P2VaIj55AuFPzJP3upwKVtJ4OKsFzZqBy0gElQivj/EkBBKrIZQBVYQUqJz1QIuU7UshKws4dab3kWNbLz4AdkY7cfPX1NrCZ22zrz8Z13QaW0C09JXXdVeeTTNtVCSu6Quv+gy4A26JXYOHaS6Gwv+3wL8Agu2V/Sd1uLI5FmWG8YhQH8YdK6M4O7GY2Sr+dh/fXvbgbfuV3h8ubkUu1kTzNfaqEV3Y2tkXtRAKD8BJZsyFMd1JrswM7ocEIHj7fDs2hMN0OgEIyCtPtOIrtDMaBM0zCNFeE6eMvJNRTEyxNc34+IU1fNx+Ux+so/ueBtPJ403PlO0musVhuBbGcELH82YNKLF8jYnlTa2axXPEjFsv5eSax/C6uEC5vCdW2KLH8QrtJLP9yEovlliSx3GQRy6/sN4nlZhHLzSyWm1G3KG8afnCSSSy7qN6CHWax/KFJhljegQU=
*/