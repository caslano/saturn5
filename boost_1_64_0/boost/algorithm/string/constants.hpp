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
u/oahYNv9umbqldTfBT25AL7Txr0FyIknuj8GQ89wUuazfxnm1hAa8JB+RdYOqGEt491ZMOKPFfkfpAyiCzy82WV8jvF4o+i1DvgKwP9WkVxhJJrbE2Fdv8g3XsZBBi8+rD5iNHBZ8G8UAyFEZ4ZVR4KzyrtwPWll0jj+WmaRQY+Wy+zb0iYwWJtNbtMr3OzKZ/dqZaELG3EJMVBpAi9vkbGPu41nhBs4+pXnrToZMSQwYpFmR7KD4PPSiE5mXQoIk07XildJBhabnLpuKzDrIh13n0Zi//E9iSuD5OCabcdJCJVAt1spCK5OmRaWw8J1eSoWPAITC5yf8HrDkxwQLWkjGYWhwopqzzRJgaTYc3By+xm/HK6ALu4Y/vS6RS87zHFXR7vX6KZGCaOqzM3Zpmb5W0LakVZhscnVduU6z8xEy9IG/CBFnnbUZACOrO4LTnhUkeEocSVzzJ24nh/MDCAhfqEr3Z4OLCFWGBXP0bnzWKmDemEdUEMcMerxhuhhkypaS/yvE1VqoYLZY24M7lk/LqM+gBPf/yCTcXwleO8oo/BClm84yAsyg==
*/