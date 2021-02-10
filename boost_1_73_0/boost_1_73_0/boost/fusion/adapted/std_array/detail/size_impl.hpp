/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_
                    <
                        std_array_size
                        <
                            typename remove_const<Sequence>::type
                        >::value
                    >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
XztKNWFNnfHFnyu617lNwUgI/bao9CcGIMdJasa9Lq3UgrqobB5ypdSFzyAauWW9r4FT6t+bgmwWahHXOkpK/e8ts68NAd2IDTz7KHrPT9nTDxb57sE/ByoqJCqf5VD2F6NfcQB6D4Jpd5YFccih2xrS2buagq+oQHToxNfwNWpfi2sX/Ndig1pZvDdVcqrAqqDGFSwdJeujYa/WnIHI3ZDPLJLd36Eo39UcXDwhXy/PUrfWtlAiFh6HEp4uBr1Zmy5n4zYNbrr4vr7g7/Fo/Jz1mN7MxiTiqxXHqHSVS1xUYmkUHJ+2yXFBeLAIwtVsNm5eclTg6ylyxCAvf/xL52lQmJ2QoPbgCAoShwvQ3Cr4uAr+SU2m63wvri2oiE7mfLnoX3bn17PFeDKajXqj6xgYIAm0FfqBRwymAfTshz2jWLzEGr8xic2sSA+ACnERLmmdhBfR7yorY7FmD0vs2lQ4yRBfbxjwR+fFa2oHjPlwOh+PR5NZ/2KndYMlZhGABA4iZqelUUcwRO/gbInmQs/m7Rrusl+8zuoikZKHfEYAgXWV6FwUW3do7s2O+h4tCQcXtsjcI1dK1occjUkbunnjUy+t+MgF7KVlbeF8nG78wbnGJ2uOP8JzEM7GIdMoPIKD8cN1KrfcNx8O
*/