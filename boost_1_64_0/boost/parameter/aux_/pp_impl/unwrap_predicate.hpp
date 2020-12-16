// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_UNWRAP_PREDICATE_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_UNWRAP_PREDICATE_HPP

namespace boost { namespace parameter { namespace aux {

    // Given Match, which is "void x" where x is an argument matching
    // criterion, extract a corresponding MPL predicate.
    template <typename Match>
    struct unwrap_predicate;
}}} // namespace boost::parameter::aux

#include <boost/parameter/aux_/always_true_predicate.hpp>

namespace boost { namespace parameter { namespace aux {

    // Match anything
    template <>
    struct unwrap_predicate<void*>
    {
        typedef ::boost::parameter::aux::always_true_predicate type;
    };
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A matching predicate is explicitly specified.
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))
    template <typename Predicate>
    struct unwrap_predicate< ::boost::parameter::aux::voidstar(Predicate)>
    {
        typedef Predicate type;
    };
#else
    template <typename Predicate>
    struct unwrap_predicate<void *(Predicate)>
    {
        typedef Predicate type;
    };
#endif   // SunProCC workarounds needed.
}}} // namespace boost::parameter::aux

#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    // A type to which the argument is supposed to be convertible is
    // specified.
    template <typename Target>
    struct unwrap_predicate<void (Target)>
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        struct type
        {
            template <typename Argument, typename ArgumentPack>
            struct apply
              : ::boost::mpl::if_<
                    ::std::is_convertible<Argument,Target>
                  , ::boost::mpl::true_
                  , ::boost::mpl::false_
                >
            {
            };

            template <typename Argument, typename ArgumentPack>
            using fn = ::std::is_convertible<Argument,Target>;
        };
#else
        typedef ::boost::mpl::if_<
            ::boost::is_convertible< ::boost::mpl::_,Target>
          , ::boost::mpl::true_
          , ::boost::mpl::false_
        > type;
#endif  // BOOST_PARAMETER_CAN_USE_MP11
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unwrap_predicate.hpp
65lP855i/d18XTXPYuqcWMaeIE3v3+3NVOPq8g7Sz9hG8h2eUce+g5pmImkX0frwrxDKwc7wvwZnxOVIylYbHXyDudb4JvO+ZbNMZv5I6sN9SNfGdU7yLBuPvdNcNsZ3veukLr6U1a8qjX7W23mtRdsl49T+anxL81c1zTFtreZrfX6SNIz41h5l+aMaf5Iv9QrwDkO3Old55oO/wWOSk135cNdZ7KLWK4lj2t9yuyar8dW1koxVw+gboIY1pL9ktrZhkMU2pDy9bkPPdleMsstSl5nyMNUXvGL776kv6K1eYMOpruGJM1/+9v1hEfrvnF89MTPg9Mh/XH1B63pvOa9H+P9WX/A/rV6gep+s7jXd9aEOyrknsw5wuLwfKYp5sRiGYHHMnP+gzB9hMX+k1McriWFYCotjaVN76+kyf2OZ3/zePr8sPxD9MAgjMBhLYghWwgJYWYbXleEPy3Cphyj3LdwPyXLM9RDXSj6fRQeul3xuwPK4EaviJklvmHEvwX4v6eWh6yvpzZf0nkQnLsYg6Y/EpVgbl2EDXI7RuBI74irshquNeo9y3ccKanlS79GiXl4QzsVgnKXyT7+ks8q4/vJvScc1/QJTfUwbVpZ8V5XtXReLYgMp34bYCB+WfDfBR7ENpmBbHIftcDw2w6n4CM7EFrgYW+JKme4mHjGuN1xvJX9hdPskfx2lXHtgOPbEUjgAK+BgbINx2AmHSL6G4gAcgUmYiGNwFM7CJJyHqbgCx+AqHItrZL7ncSJuw8dxO47GV3AKvo9T8UMZH5DN57a5z2tzn9fmPq/9739e24uKlePp1tIdpLtCF0SFptp0fSfmPmvN/cv9y/3L/cv9y/3L/cv9y/3L/cv9+//7+xe8/4fYhIET4pNjU2q5KgD85vf/+03v/yfL+/9N8s3wRroDhfjtOlG9D5Jm2ts36+2uAKDev7xeSMUMSaDXeP9TT82zxvL9D+lJrI0+jGMZ5OEg3Rt0b+Yg9rxruQVlueb3rmXkJ2lemSkP3ezC/G/SveuhYmVTqhJq0XN9rPJPOtmrw+Aln0Z5V3AVsnom6bY1DyODLPI5PHF4qualvEOwsJonwiq/kp5u+d4uVI0LsG6fmnHm9+FvZONdrMU6y7t963fkJ6UM6DHehQ1jW8VYlUGKq3W8sTUlsGq2tlXMb9xWbSWfZ2UnLO9+nqy1ZFslWeRTmteMj8t4p8zx7W4nJrrovdsudZL3+jJJkn+LGOhGXJsJsu2zvsd0TeSOTzU2Y5pslwP5tDy20uS9fz6ZKUDKYb1FOWRd+3vW37p+UA63F+lZHlvR8t6/Pp1OV0/OZTss8imnW6/nst1qnppW+ZX03O/q35Jz2aHfcB5rKeuQ7sz6fjhQ1kGbbLUOvKnPKHECxYwhGFx8to4PbfIDy7ttdo6P9b7WeY30mldVp8DILJNnK7+RvzG/mXUf7krdh27yvqwrXTtXe3j35teokGWRR6NuSAs1X0feD+rWdYsk3/mNulgqRpjledc8bapRt8FdJ6GtGt+ac5DNOhbW5Hvr0RwOfXDdEasyCzHXy5I8h2Spm0XePM4Ru/yN+nnqr7icI3ZYlK3aC4yThPdz5C41b7j1MZjDfYL0Lffh5/K49121bLoOZP7i5Mw6erHNu/XK2B3ihwwck5BqrjQUS0Fk5D8g2DU98bis92HSs6y7Yt3W0YPXLcu2cy27oCxbtp1nfRDjHNkorxFbRv3VpIsqwv+mGOubnKIaLiQWmto8WeJ1W60b82Yvv56xfM3H5lkv+WrqJV+xCaMSh2Yjb01/Q94yz8n7Au7dR9q4KhEYebvf/vHgOnBpU7K/b6TlcH3k/svbfmG0MRM=
*/