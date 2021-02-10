/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_AT_IMPL_01062013_1700

#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<std_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
+I5oxWvLIKUSzx9bPaIncFIgBUpkwkOLDpSy+tQbOn5pTJ370WQRzONgNrWI9UYCO4NtONYdVnnQia/yOVLP0HaMjChLZeiAaWhYs6NjLFBNlc+xRmjeQurh7Ybq3kF0bYWIg1cL3zs/92Lv6OkxwZPSvafB9CII/Sj43e+fywa++DgJvcXbvVCXdepYy3SsqDAOrrTAuMi1zhflQtARum6klqksibGXcTx3egmS33CGUK3Ce4tk50jWhv/ZIhz2R0mEpAFD6YCBEJL4uhUKu8NakqbR2iKNDTyM3XFP4S6DOASotxjY/m2Ne+IFjM/OTlNZocctt6HgDBvRtWh2pJhL7CrDGTO1uocd+r3ckKFLTK6/GFJLUbQ0ZC0Mm3wms+QYFg5B954p3tzwxjEi6b5yHUHJimw1XFdyS3Gh95YSf3FYc0wsB6VxoPYPQDeYuhx9E3f20qKtrnEY8Aq5i4KuGYh9D1A81noHLDOpZ0NspbjmYMc93Knf674Y0Gzjl/U/0bvw8V72z4hHQyiDR4O3JnBr02J9FRYDR7IJhqJ0+3a58JZhbOFiy3jO2lKbSSe31b5554tZPJvMwsh6L5U2R/5v3vt56FtulVtdgxqq/HyvfUUl9BH2pMiP6PAY/rZw05/AlsOWVcO6
*/