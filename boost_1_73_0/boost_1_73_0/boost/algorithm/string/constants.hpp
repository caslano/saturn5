//  Boost string_algo library constants.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONSTANTS_HPP
#define BOOST_STRING_CONSTANTS_HPP

namespace boost {
    namespace algorithm {

    //! Token compression mode 
    /*!
        Specifies token compression mode for the token_finder.
    */
    enum token_compress_mode_type
    {
        token_compress_on,    //!< Compress adjacent tokens
        token_compress_off  //!< Do not compress adjacent tokens
    };
    
    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::token_compress_on;
    using algorithm::token_compress_off;

} // namespace boost

#endif  // BOOST_STRING_CONSTANTS_HPP


/* constants.hpp
kGHPUSEKCMSV/UdtMPyqPyVAPzkDT7ijXpjnng98aEfwHAhmGYMZpWJQtJmnxKg8Mr0KGSrWObYtWUeDcOfBjxpmCaqGT0JIoyBBVQs0RGUIQ1CzXtqqmJo101bVtFW3lxkcRphme2ZwtBloBaw7WWpSACbnDLpoizLaos3zkzRp+MWAQqMO1p1jQIN3FVxNJrZx8JXJuFiUpnh8TTPktIaRclpgWuaCAdvkNaWHiaJVfjWfYdVWHYQlF3dGcj0cj9mGITofLdXNl2B/wpkmVl4qVKzJmSbFuwSnDGjkt4JmwVCDwCtkfBu01FEsWfkGqY9TEyuvhCq2ZSor2OwETuU0yW61jLu88+H/8LJ7SOM33NgbqV5LKWm9krZlAE/R/YKsU8eeJ/PYmv0/rYPcuw9RYVm2dHqKkoJmCTt1hHQbJXBm9HPre3Lc0wwv/CmsKGpRMXre94J03xe15z6WKmMavtCAoqx+nr96QONF3odR3z9Eef8l/+H5RZFFz8eCenBe856PWD7FwuNFxwIoKYuke/+Q87pikbKy6zaN4/QV0zKAA20XT0ZJHrHSbV0WZeVG7dJMzstT1CcSRjmeA0KsAoOX/jEuLtjZalifqkQLjlLdGs57JQ5C0YX1RO2NeLe96ImLpmBhTbGb
*/