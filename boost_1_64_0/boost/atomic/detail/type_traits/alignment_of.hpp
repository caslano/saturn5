/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/alignment_of.hpp
 *
 * This header defines \c alignment_of type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) ||\
    (defined(BOOST_GCC) && (BOOST_GCC+0) < 80100) ||\
    (defined(BOOST_CLANG) && !defined(__apple_build_version__) && (__clang_major__+0) < 8) ||\
    (defined(BOOST_CLANG) && defined(__apple_build_version__) && (__clang_major__+0) < 9)
// For some compilers std::alignment_of gives the wrong result for 64-bit types on 32-bit targets
#define BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF)
#include <type_traits>
#else
#include <boost/type_traits/alignment_of.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_STD_ALIGNMENT_OF)
using std::alignment_of;
#else
using boost::alignment_of;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_ALIGNMENT_OF_HPP_INCLUDED_

/* alignment_of.hpp
247YRx4zhxJ8fUgXPIeyoonlIX+PPNU+8kgD/CJIHuYeguUhXeC8A2FNKw/5e/rNlUP95ckLlMfMpQQ/50SRKW8fyqTfi2EvQ0t+F+Da4Gbifmev09TKVIKF9tSZBWVTeVvF2Po5bdGRQeO2t1L1+1Fviz/Pas3/x+Pc7/Gkqj3iWxJvgnUQ5TkOJ3Kb/FLxy7Mfv3xMC5FNv1/1vYT3J/9Es3/qNdhe3WV/76dj7DaGyKI26D7v5ri+zbLrFK+efm8/3/6tvp4Kpkt+Qboifn1dnS9+oyv3vglGV/P+5q8r8jO66uujq1v+5tXVtaqrtEP2TleOvRDqf4PoVK+uHs2wb9Tr62pucJ0ibn09tcfv1pOxcTV1Ctb464n8jJ56iJ7m1tPTcTVePV2nenqoEXarRk9+dqv7v9XyX/Wtlspc2WM4tVWrq2777MAv2iwpe2ny0Lv3f6slsgfzThnjdG8p2Fu/qxKGuqQg3wNJgRfC9nAB7AIvgt3EX/cdgArN5xjNx/kdgHmOeNVR4i3UeJl23Hfqx4uH3TTebboX860wU/0qD/vGBMtzl8pzt8pzj8pzL+ymfvPdhXeCy3mHKSe/d4PL2VPL2UPLid/kn/1ucP7dHPFWRIn3iJFb9kMIlPs0lXuEyj1S5R4lcuM38uA2BcszUeWZoPLgN+kqoqSbZKfT+JnqN/VhU7B8XU083HvB8dKd1/+9YD0Uqx5KVA/nqh7mwm7qN9f/vdjqs7U5tvqcvXnP6vOKzcHy3KDyLFd5blJ5blZ58JtybtkcW33OfH/P6nPF+7HV5+r3Y6vP6VuC5T5J5R6scg9RuYeq3PiNPHlb9qw+V27Zs/ps/TW2+pz914brs7R/jTfUJ95DzvN+EBzvYac+NN5kH7nKVa4yOF795rqZ/KO3h8wPTbyo7WGpiRe9PWSZ9mBsBwPLf7umW6Hlx2/KlfeROV/U+l9l4kWv/1nqN/3TVpMuav2vMPEC67/a/wTLOU7LMRaOV7/pZz42+Uet71nu+m7SRa/vWa76nvyJSRe1vpeYeNHre3WUeIc669m22NrF0m2xtYuabXvWLvI+ja1dVH0aW7tI375n7aJi+561i5rtsbWL7M/2rF1UfhZbu0jeEVu7KNmxZ+1iy449axdZn+9Zu1jxeWztwvoitnaR90XD7aICV6XxLtB4Wm/ld4aOl1NhZ5gH0+HZOo5Ng8fAs1Se6dA+Xz4cofEmwgI4Bc6A+XAmxBFuysHcRXA5LtFyXKrlWKLluFbLcZmW43ItxxVajiu1HNdqOa7ScvxKy3G1loNwUw6rJrgcmVqOI7UcR2k5jtdyHK3lwEk5fqbl6KflOF7LcayWo7+WYwCcqeHZCfu/f/a/+P2zgY+E98k30JJ37f8O2t58B20K12Ux7m7cetxXuLRHw9ZA3CzclbhVuA24XbhOjxGGm4JbgqvEbcQlrAlbfXE5uCW4Vbhq3G5ct8f5bhOuBLcMtwa3CZfwRNjqhRuBK8PdiqvC1eCSnwxbmbhcXAVuJW4dbgeu7VOUAZePW4pbg9uCS3o6bB2Ly8Mtw63BbcK1+EPYOho3BbcYtwq3EfcVru0z+78htP/3n/nt4/3/50wvLZky76ipNu0PAOz1/v953S2zxpOu+//fhzsEdwPu3FTuC9+UdYv8I4vkvFOL5xRPL6hnNzBN1y0icXuIfyT+Zm/Z/sW1tguyzlFi1v+Gm/hdxT8Cf7zEX2SlED/FsuOz3D+zrDCSZhRxLIlTIf5Ck0e6nCNLJJlTapl9P6DEn22lsq6RYN8rk3Ez4i3CTUmuXdvItALXNsgn3HqQ5GF148OLsp6YZewMplkp+l478uGvlS9V320=
*/