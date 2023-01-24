/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_HAS_KEY_IMPL_31122005_1647)
#define BOOST_FUSION_HAS_KEY_IMPL_31122005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/has_key.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl;

        template <>
        struct has_key_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : mpl::has_key<Sequence, Key> {};
        };
    }
}}

#endif

/* has_key_impl.hpp
EIg0UbP1epkND6vsi+uey3ZFtsEvW8lFYXYLcMtrBXSGvMhCZ8hgk0Ot37CeOqR4Mz0L+bNgM7V/Br+1OWbya63efApOk54i2+64L16n00GAAcU7NVnpgYc8depvbRq073z2JVg1uQYla7ZbX4IZFW5V6NBjynrdztD/rihZNzEcyT5Zi+cY/50t4XGZb17Bup/R5lDSbJWvUGW9a2CIUcKHKOG6H0Wix/REHM5PPQudeigdDcvL2QcwGvu5bqoyZv51PUV8X8iQ1fHgWMYq/EgNsfmLuN3TJr1O9qkc+5KvAUb017EvQVo7pYoWmewZc6nC419kZW/V8r3PISgZ3lI8Sdbt4OTvsKWV9O/YeAhDC8fHOajetXDmuklWpuTgMlgDRrs+0nxUQpB5snpnDzorESEZala/U3AoMn9Qqik4VT37wjYKTjYFJ6sje7Pv8zPTPsaSpRI5QpwpgmCAkwFAqjFBe632Oz7ZjslpOZFGkeClEb4HRbkGnuwdPVfKZKXfOcuTLFZ5EspPoyhzFipPVAwLgKctlA85NV3dEXXiQMPVEXUZmLWwUTo/QuRqpk5scW3BqaMshHORVtxdPTRInObFm+jCTQLrjqb38B1uQECgvONHfbSgHoWLOHJYGR5YgV5CYc/KEz0YrmewUmQgDibc4e2J1z8X/lauOx3p0wclN/XlpoDJuPyKDTPBQAoAiBXI1+TbV7Pd
*/