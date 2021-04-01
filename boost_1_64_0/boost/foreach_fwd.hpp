///////////////////////////////////////////////////////////////////////////////
// foreach.hpp header file
//
// Copyright 2010 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//
// Credits:
// Kazutoshi Satoda: for suggesting the need for a _fwd header for foreach's
//                      customization points.

#ifndef BOOST_FOREACH_FWD_HPP
#define BOOST_FOREACH_FWD_HPP

// This must be at global scope, hence the uglified name
enum boost_foreach_argument_dependent_lookup_hack
{
    boost_foreach_argument_dependent_lookup_hack_value
};

namespace boost
{

namespace foreach
{
    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::tag
    //
    typedef boost_foreach_argument_dependent_lookup_hack tag;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_lightweight_proxy
    //   Specialize this for user-defined collection types if they are inexpensive to copy.
    //   This tells BOOST_FOREACH it can avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_lightweight_proxy;

    ///////////////////////////////////////////////////////////////////////////////
    // boost::foreach::is_noncopyable
    //   Specialize this for user-defined collection types if they cannot be copied.
    //   This also tells BOOST_FOREACH to avoid the rvalue/lvalue detection stuff.
    template<typename T>
    struct is_noncopyable;

} // namespace foreach

} // namespace boost

#endif

/* foreach_fwd.hpp
+gJ8Zc1LTN+n6xeQvrSCUg+NeggWlGaxqypuDRlK+N2Fgup4yH/YGfiE6M3AqqesDbAL8R9ongHT70JdrBuyX0AKeXx9cYVZadbMHRENihmsSfyxG0ytIIwCzAyQXCRHsrXu3+U1ecFeXJolA2yS54oIrHUTWMQpMElMfqO9A/LOk3YaAPUbzBZ8+/GG05DbhpDUqPKRy+vRCa67aD2d22u8fpBeyttRLZ7+iw2L+PRDc67yMi4z0Fcrc85BYZFz5ZvrBdKp/9GcoNSbTNPQN4W/UfcOPYx7YUKX+uZp7Buh7KXAcs9vLhx2p5r4j56BTlchm2yPL9E9qeFI0hyCD9NoroZBBKczNBFVBIAhdn97YpyfWfcW8QfF7CxRJMjPtFrK/hZM2Vym23kDufwiTFjS7wQXkiKiU7rrLrupJomWvjDha96teh5wFO3gpObfEG78I8gH3fo/XUHA46JPBL859jllTnG9w+WteZLVHAFFTUgHN94m/rfYTW9A09YvVPsuBJ1k8hQpiTICc03O27Kzl+l9REXUf7u+1aXAjddnTvHNiV+lpQ7kEw==
*/