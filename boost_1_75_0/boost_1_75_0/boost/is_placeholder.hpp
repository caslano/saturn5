#ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_IS_PLACEHOLDER_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined( _MSC_VER ) && ( _MSC_VER >= 1020 )
# pragma once
#endif


//  is_placeholder.hpp - TR1 is_placeholder metafunction
//
//  Copyright (c) 2006 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt


namespace boost
{

template< class T > struct is_placeholder
{
    enum _vt { value = 0 };
};

} // namespace boost

#endif // #ifndef BOOST_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
KagDmFzJbuJ7WrgVPRCTnbcWwRDgLxAUOjjnUyY9kXZnlZJMZXgEZJZ8gsI534FUqaFoemFBXeurq3v9kx6NNktToo3CHs756Ug94TZOijZxm2/bCwXruGU1t0N5AFJ1oRIQrZiTJ3XxF4zcsmN3EtJ5gD9q4AQZvFKjp8Vk8KBjAWcH/4PB49Vzzi2Qdv4DKFv4N0JB0UV1cW5vdCgh2OBTFmitfBt0RT42wvmJkWzHVha0HgUUDiMK5fpWCdKEvRFGUsydcWdnSQf4HznhkO3WzkN8nSXm60ekr6E6TiiHGjytetvAYm6JzjXZ+LC94zHpIP/DUk9rmC22mFuqgy/Jgj9R+INRSYn4k4k/M/CnzCViOx+2Nwl7bGOlg55WI5a3FMqzQHn8D5wtEmJPBmp5CGJ/NNhCq3VJD9svTJuuDZLQYbtPyjFDMbFSukXYzjlPTzSSPKknpour0RWLRs41WV8suG2Gh+yn49xF2P8nAAKGSH43hhDvdgisDK0OW5miq07VrUzRV6fqoQPNhUV1tzb3SoCehjS+3sA3GPguE7dMZ4Ref0+JfoV8TywMmK/XARjfoKMALYYggPPveo9AuLMBpwUn/B0yd9Yz/4fgcJtP6BcMlkJ5r9G10CiGuZYaIcqwYOh5bskQ3mtyLTQVc/s411JTZ30YEvOT3ObjBo7/GPzF3PyMdtfCdnALLbwXenx+CvT9/Hmx
*/