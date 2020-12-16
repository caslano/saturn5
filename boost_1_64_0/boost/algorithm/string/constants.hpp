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
h8s/g2pxvCLZbU7mS5mUIObpgixjM8UfM4qz/GmOVcB+5CRGE4OZDM31YNdfb/+KbxbGPmx/kuBM92lxQhcy2Xfo43HlLGlhSwfw/twZQfFc97xnn1+YtBEFKfKOOmnsy4o5Qgpd7UxU7xAAx0IlMtr6VcH1GvN17PeinxZGPKWVbMb/OdyhCLZe11/nJGroZgydMzPTP9iBKaWqJlSvFlWSPLupsTllb5tipND4XIdEb5tgpr9Be08MVjQu6SIY+XQ1I+jMPY/5qSt15+4uOI15vZSZyu9xD9GLin1uv/xrUFYJdTm5pBF/SOzz9jq9lHwrHUn5pnCiZijXyYHiepMOlFfAUO5Vne8njvsNzW+8UYulPPU3aG1VpH2ONHcBhY9XJ9aHPFlv5+S3+PVXJ6fR/ufk9cz/IZl6+fDD4rdpOT6pI9FYe6avQ2MzBBTzov5boqX87//Zz/f2z1T2fB/7bOh831so57ubz/cc83z/btkfd74fyy97vmcVWue7h5fgI3/g+V7u/sDc4nd/0id7ykFo9MFNE18Mj2Ecmdn/Yp2d2b/C7/kBw9RZvQ2GL0DkjCTgMZngieWzETHOTVLPzTmXBUpD/cx8dyMMGcTkdxNCAGOo7pyVUyUlWHK+x9991fPVmILj6CBbEb8QsFiAqwQcFuKLkVvUX7coi1t0mzlxqdQi0r6iiCAkd6QGaHR9EfDaVDIcIFzplADRS3osGj01JCeey2ngLqhb7cmcJOci9AwEDV99TdSEfNr7DYkc1L2F2x/ryW+C+9bhuSwTIOiDBH05jEXVCJxDpI8LMLj/cpGU+748LjUg5SDhePFV8eX22RSLT7+THF3r5DngkuQparC5Ut0Fk+kOd5sQwCsKiAD+RXXDgU0txq2tjnItQGn64cGPLKCimjLwCcw9NOYWzMWW9/6e/B+5vFTij9ev9r84yGbpkPKUtnQofIjIsDJK8cBEmh4DbkMGrS+PMdZZ+LA+CLuFUic52WUh1paxdX4AN31wbXdgsHMDDli5yZecmbnHYlx59zik9E0vY9S+AVNIQcVLVfJkNirryfzAu/yOAPUSUy4CkVI6cyqkscqhMVBQ0XuIPDvvDBapbyfBTuaD2zfxcWds5nukacHAwgqsse6PsB/GGroNC3yW0H8WzXL9dKMqa2sMcaqL5RweTnZqPTziPidZLbqJnzraWZY72BAPzwxZ7jheraVDvoCt/QxsLVZwgtkLkot8egdvxryFmnk59ldaPOGNxdIfz6t+jO70du636nij9Uy5g/q/BbiQiV2hXn4AX6nIJRUga8I5CfwA8ppoARt3WLtpPu8KLvRHGXz8zj9ar4mh9WpeqkQgN+dxXrRMcCV89jH1xa3yArjfQRx7lMg+0rHgeGF7TOkoT/UHKd+oKVNlJVcnlRtWYrEW+VVTbUufEuJvLw22kxXelRa2wgr/Loq/5HTPPYoV3luvrjxc+K1AN6iKTy8OLcF6BqKwkshrOFBXl4m92VqkUTrpkymht8nmSMOCpEfGDME52KkW/Fm/h3E96Bu1t6e2jE5T+0bzku3AFye9ZA9NC3Fnff9qW7IXg6bRleplLZRcopftRfOkjgdMml4ymjbMCCblw0K93M5dU3eNslbqVFpu583TK7WqcuJhgUqVNCMETRgBL82iV2RploL6A5DKXmZIPPRgEc2sqjWBdrjr7rYng0LK7aYpvNjRtWf4zcue81+4osvrTyey+wHhIp57REshPxMppPpwrOVI3MVyMjpd2Jq9CHtDYvrQ9T8lyL5l1BfjmZjO8dJM3biEwxaq9BdlTgxPgrp+OauG+/hR9GVw+yX1oZrtuxzySn0N2ZEX0hg=
*/