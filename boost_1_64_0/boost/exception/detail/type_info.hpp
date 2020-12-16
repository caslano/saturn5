//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_C3E1741C754311DDB2834CCA55D89593
#define BOOST_EXCEPTION_C3E1741C754311DDB2834CCA55D89593

#include <boost/config.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/core/demangle.hpp>
#include <boost/current_function.hpp>
#include <string>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class T>
    inline
    std::string
    tag_type_name()
        {
#ifdef BOOST_NO_TYPEID
        return BOOST_CURRENT_FUNCTION;
#else
        return core::demangle(typeid(T*).name());
#endif
        }

    template <class T>
    inline
    std::string
    type_name()
        {
#ifdef BOOST_NO_TYPEID
        return BOOST_CURRENT_FUNCTION;
#else
        return core::demangle(typeid(T).name());
#endif
        }

    namespace
    exception_detail
        {
        struct
        type_info_
            {
            core::typeinfo const * type_;

            explicit
            type_info_( core::typeinfo const & type ):
                type_(&type)
                {
                }

            friend
            bool
            operator<( type_info_ const & a, type_info_ const & b )
                {
                return 0!=(a.type_->before(*b.type_));
                }
            };
        }
    }

#define BOOST_EXCEPTION_STATIC_TYPEID(T) ::boost::exception_detail::type_info_(BOOST_CORE_TYPEID(T))

#ifndef BOOST_NO_RTTI
#define BOOST_EXCEPTION_DYNAMIC_TYPEID(x) ::boost::exception_detail::type_info_(typeid(x))
#endif

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* type_info.hpp
+nj+PZ5RIyPueevIsPb5J4+a+vzm5dTn3+jnOEM7xx3U1A7v67L1XpbebLseHJgAtfGPLebe9206Tb1f1XrQbp1oDzFaeZuJuhMM8Epc3hV8iXxiFQUL6TvBbB+ZgIM6ntaL91axF0dOQP8NGxkZv+YHguPQ2jNlZTnFEE1KL9Bzso3m0EnsTI4qcQ6DAwSSiaNbVinL9Ou3kQXgqS0hVcazPLFWtBJdtKhj3TUFMqRl9fYsAskmQoKrXXqBjui7mYSoNvfBN64N7z64eKm4kYmZhe/fjy+v9f3zkTXh0RtE9B6Hqhlfbi2v4f1zwZpTu3/6672Cevp6oH5gcvX3T0H3X6dIP4Po73gG7782VU+/ivf/nw6vvTc+KCh+tRAo3nZrea37t3GY9C4herOQXsPi8hr277NPnVr77lhG79k9BNSP5lTfvlb6SadIP53oT0b6iS9VT9/a1EJiXfuk2ooeXMuh1HKYJz7wpQlDXWURRGcQ30Y0kW5BYSEOk3navQ/h+jsD1985vP767hHXL33o+oX61GuOxZaCJxwiIXw2wWpdHgAdTrJ1V7bV7IqWVvQFGby2foj2hXPGmvcFwddXxNePy2lfMPFVVCj4eszklBYwMOeKjn1B2piLneY7wrhmuU1NxwBGfzf2a6MRqyJAQn1xvaUantuI8n1Uly0/kbn4EMDKbop3rVC2UngCxe249I9iO158GrbjU/6z7CzXr1bbU2BTuaVpFW87abBxq/lAgGDzYhksNL0vHhcwpJcOkDzahGFD09tAsMUISmAxwSQtod4Wk8LPpElXFqGkDuE5bI24nxlCF6qCk/Isk8rR+SV1S40IHOhGk0KpxTVWzaVf2dIw203Re1FX5nSQphQfyiAr7tXx8u2WcTIvq7gpIKbM+SrzSpnpDQCOVXk9IQ8vesWZu53Q0QRKpalSGPwPzE4JTb5G4xxV4nNstuRnTEGmIPkdTD463qqowVOfORoExLwGzGyb6TN2ApDAvJTdbV6C+ckbg+67NHumDH04lhudr3yzlPaYSbApxF2TJVgyC0jZxmhcYsk0Yiq74mqhFKFn/FNxfUiiADkL7+cVZzavDwOWKCQPT1W+iceWKt3MV/KX1zgMv6i6H8pf+cZe+EWsHLwDf2HNizfgCvZbWRFq9meZX+uwfZqv4vm1ITC/Uqq8WaCOYK0kzz7LFKNToJ3OMlVOvSJ96nk5IabUiBRz8Wu1vxieWdqNcaqci5k4gB904n3PWn24s+6vEPt9UTugVaICSUT9UQ7mkWqe4kCnkh/HySmURlOxxCFMKw7L2ZaN05FKblQlm0ssOYG85SrvhJqlgbzbVd4/RB61UCB7hMoukdmLTdn9VPYTIpu6IcD+2Sp7Hmaz/kXubGB1wAHY9etvaWY0jbKXSlAf5mVR3lY4F9L2THfjMAMo40NoSzlwOHCpECErHpAxFkfRzPTfwzNzLs/M5xaqGZddqObjDYVqxg0rVDNuUKGaj6nwi30Ce8EHqwET4IOFh5aFisHz/6im/Dn5ctqu+8+bttXP54Bfl3eFOm3GyYkVGY8fPKkiYYIkOnLPloFlx0XGR8wv6erv4q8Hjl2F6Y5U/zl+mRkNKfNLIv2N/A3GAWBUQQMo4I0Mx/NLk38tliB/eEgwaNq2U+1N7HkNQnHVS4EIMXQwDYtHRpVX8m2lj9JiIE3GLAIFBEeeOVgXpkU7GhILIaM/7rF5Hlr4cx8gUXOWy++jeLLtaVSOCGT0VSqtXY70oUN7+NvRoDpf4YIiTU1FeiJdf4IWBM4owCkwC6fAvED8k3ln1N0ww0ae6rRcCo17RIOS9eRSwczjatrceD8eM+IgosfNwDw=
*/