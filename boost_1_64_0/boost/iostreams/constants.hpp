// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains constants used by library.

#ifndef BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#ifndef BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE 4096
#endif

#ifndef BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE 128
#endif

#ifndef BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE
# define BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE 4
#endif

#include <boost/iostreams/detail/ios.hpp>  // streamsize.

namespace boost { namespace iostreams {

const std::streamsize default_device_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_DEVICE_BUFFER_SIZE; 
const std::streamsize default_filter_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_FILTER_BUFFER_SIZE;
const std::streamsize default_pback_buffer_size = 
    BOOST_IOSTREAMS_DEFAULT_PBACK_BUFFER_SIZE;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONSTANTS_HPP_INCLUDED

/* constants.hpp
yjrO2yasS2kM+3f465tp5C1rUgTnTz79NfmrZ5WvCONf6lLyzEX/aKFLmaMU1KVchb+NpvgZmpS8cbSKE+4rui6F/Rq6lMBi6FJ+vIkuxZz/c20FdSm/aHXblD7WpHDa8upRTmXeVI+CcIquR2G/hepRDmfeVI/C91vrUa5lFtSjNMgqqEcZllW4HuX7zJvrUT7PvLkepW2WtR7FnZVfj8Jtrhh6lB//gB4lVstc3je5JFgR/Bnh5WbpepS4AlqUAu2R03ie7ikVhvkExEsPo7S5TrAb5RHXiQyr+gB/ljoRq7Jnv+ayv1e04HIbPU67tibELnrJA+QqygpbU+l7zIz5O2Klts5A0d/ZSFrvihLnXKOkKZ506Qw6/Ej/Z+RtgYfldvpcG4URgT3ZI+T+ckflTVs7yYlZkyaOSlI/p1vMdd4l7XO1kZp5Sos0z/3SAb8y4me/VGk4XiSPBfSQbEHXRTVuM34U1t8hjm+RP8Bcdy31pFTT8aF0xvWruj/wQ+V8CZtRpx4kv8+E/Cj1DKrA9fYypdUVNkIk2Dbb4pSVrnOOB0JC5Q2hmBfntnJhouantb8H9exncVJ9xr5DVHXuEJmuJjSXvxFzE8en0F4FcgjvayrG0neaYWXUnwM1P+fglpRN86winM9HmDeB2ntglHTFHeL/Jymcz1VY/jDVYVeW2IX35bt2LjOYlBTIOcac3icUr+keVSxRnle+doRz/sZMgjtyM0I8oExS3qI45iDcXPJfxU/7vQe/m1AcH7Brcb5givNw9ZIflz1J4Mn8vHS6Xj0UuxTICXJDeaKaLMn2RlJ7R6BIc9SRXsT89y5nJynGPUxa4sG6bw++M/WLknr5txQv+0dJlwKSxeTAx0TloLrS0ODn5Q4c33oU7tfBtbHb3UDZjpnmU9JqdanU2t5cmu1wizcd1aXvMAsa5aoktXH7i/HuztIeT6rUxL+c6OufLn0ZECYuB2yXK3M5Dx6vhZccVFnqJGbLs8V3ikc+bLcLj+OgY0Nga1GWy34YPXdB6AlpmGuop4Xjp5Bk6clQmzHvdfUh0te5zonr0vvKYdHBdlwct++S9DLvOl27XlvS8u+IKf/elq4Hh/D5Ga88qLmN8m8uJzj0ct84keqB/2b5tAhQWzkDuNxffsS7B625vOua1n5spXId43GjVehlfZ7cHkbY2coy5UtFe+5eU1yui0M2fY/ZB6j+X89Tn7CBihH+dKp3px2qOOzQ+9P15PYytEfLFX0c9css0q0ZZz20eIR1MJwv+rOzFdVf3+d3AYXT2x3AdW041f3LNq5n9BVcZ47H+3R/95AAMUR6WGoq71TGSx1t3aW37P5iv72KFIR+poazljTcFS5eRD9hgxYyxjNUesdvsNQ4YIT4JuBJ8XRggvR10BCpJ6fjJ2rnoWGh4q/ScamBaIV61kOuJc9WP5J6oA4vcPiLDxyVpfMojUqoZ53c06TD6HsaoY718e8j7QsoLS4FPCU9FtREOhPskGwl/i6Fc34kUhlM8vubcMhvKC6n3t/cQ31CmrxD7DHmn89SnVro2oevZAYp8eJV5biqr0H67kEqn+AWUm9xXW4bMC4Yc87c9/9K8fcLOymFlIiE22ZTPp+VfnS94LdfNAp4g+bYd+NaItUxp6Tnd38qo+ZSANfBtvSs9rLe52yiNIT6j5dOi8/krk4uF/oKsR2Xi4vqz84Ql2gn95DvkZ9To6RPbY2l0qgtTdD/P4iUL3TWlL7CrPhV1zRpjWeE1NR/lfxLYHWpJd4uDwXHSU25PJRxlA8BdtEJYdmhbY2Rl6tz5Tp4DwzEe+BJlEMOyvhnl1tEuptIIzzjJMV/qqSvtQqh+1c=
*/