//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_1A590226753311DD9E4CCF6156D89593
#define BOOST_EXCEPTION_1A590226753311DD9E4CCF6156D89593

#include <boost/config.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/detail/error_info_impl.hpp>
#include <boost/exception/detail/type_info.hpp>
#include <boost/exception/detail/shared_ptr.hpp>
#include <boost/assert.hpp>

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
    namespace
    exception_detail
        {
        template <class ErrorInfo>
        struct
        get_info
            {
            static
            typename ErrorInfo::value_type *
            get( exception const & x )
                {
                if( exception_detail::error_info_container * c=x.data_.get() )
                    if( shared_ptr<exception_detail::error_info_base> eib = c->get(BOOST_EXCEPTION_STATIC_TYPEID(ErrorInfo)) )
                        {
#ifndef BOOST_NO_RTTI
                        BOOST_ASSERT( 0!=dynamic_cast<ErrorInfo *>(eib.get()) );
#endif
                        ErrorInfo * w = static_cast<ErrorInfo *>(eib.get());
                        return &w->value();
                        }
                return 0;
                }
            };

        template <>
        struct
        get_info<throw_function>
            {
            static
            char const * *
            get( exception const & x )
                {
                return x.throw_function_ ? &x.throw_function_ : 0;
                }
            };

        template <>
        struct
        get_info<throw_file>
            {
            static
            char const * *
            get( exception const & x )
                {
                return x.throw_file_ ? &x.throw_file_ : 0;
                }
            };

        template <>
        struct
        get_info<throw_line>
            {
            static
            int *
            get( exception const & x )
                {
                return x.throw_line_!=-1 ? &x.throw_line_ : 0;
                }
            };

        template <class T,class R>
        struct
        get_error_info_return_type
            {
            typedef R * type;
            };

        template <class T,class R>
        struct
        get_error_info_return_type<T const,R>
            {
            typedef R const * type;
            };
        }

#ifdef BOOST_NO_RTTI
    template <class ErrorInfo>
    inline
    typename ErrorInfo::value_type const *
    get_error_info( boost::exception const & x )
        {
        return exception_detail::get_info<ErrorInfo>::get(x);
        }
    template <class ErrorInfo>
    inline
    typename ErrorInfo::value_type *
    get_error_info( boost::exception & x )
        {
        return exception_detail::get_info<ErrorInfo>::get(x);
        }
#else
    template <class ErrorInfo,class E>
    inline
    typename exception_detail::get_error_info_return_type<E,typename ErrorInfo::value_type>::type
    get_error_info( E & some_exception )
        {
        if( exception const * x = dynamic_cast<exception const *>(&some_exception) )
            return exception_detail::get_info<ErrorInfo>::get(*x);
        else
            return 0;
        }
#endif
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* get_error_info.hpp
hRyEaZ+jKRTmz6Aa6+f7SUFL6npoPYGiP1c80ZBTWlH153CjTs1qM53oySGvauYQE1HABKnpyAvUFPfQRFLYnH9WXB+7f1b9zhMVvsgUxUnFKl0YK18f8Yrqx+NjOg9Fs99+mHhU7EOKt/SOdEbxQVwminNUM5niLV03QmoGK8MaWc1+08sHKgg9UaWYS2nG96hzpMudKO4pB8groqOl5k/HOgLtJG+UtEwMcQvhlSFEjqP5eQP248uUPh70842/L5Dq4yGvHJSyDbGeiazTyH8nBW//ZVqSBhj3TWR/3nsJr/givX+z0GpP/mstOzC+/09QxtV14v9NCP7VhfW5rzU0BH7I5Hq/N/bdAkJijulvWamPv1O0MK4ZfiO9Us7JgHmb4hM+EOcIFi0Hs37xMZdYX4ymlR/ntQiiGcjgP5fq4Is0cK9I3udoBn3CvtX7ZVvrf5Ka51uNydtKMUDORGJu5GWgmmzEqbgDsyZR1umQRbW++Y4qW/s10/lfUt3nneT/Op84pVkjDu4onPlCc5pXYP+I/6Ml/+xJyA4fveaImm5cLWaF22/vncfv0/kp3F22YcAenF5voZdy/ziRePEJXnxBXlLFZl9mZcvl3l8vMfPq2+dwextyEV5bqicRlzIgVHeHV0w888R3Jj7TSnxke+gHWjReL9FWpQtTtnuQPOcOFEIUyKPH19zoqFFdAf+QzFZ0SUbZdVU1QyGrALvU76CgFkYNQ8qiiAtHqV/xS56RUdQgNueNbvrpil/ZzsWx1W5vQj+j4pe4oQBCOgQkPpNWPVQmNfVSrE/6ihZfVznpyyO+YmRJ1AeInOuCT+6LM1bEOYIifHst9cVWImkfzk0o9eEoKQy1E4z14HezHbjTQH+H+2sRMiEjRZZFzrLwqndo6elQWntRPgUnePEwf7noYORrCT+x7RDfwWC7jAEe+Qb/wgGWVltwsd5q7RXjLEq0SsGFBBDus9vEdHFRimOWu3orXk0nuOigwE6TCE+AgUBmxJpYWLtcY3CBV+JB4OpfA14Lw6+M1xnOa2Jl+OIm4p/RTSLWZfflmhovOEW85gwz+PYYLEXHk0sciQ48Zuyugnajj8w8Syt/7gIOd0LEozB9hokNGav3mdNJGM51kDDu6kKFhrGvBOw69UIL9RtUPvprpCmUHmObBzsya6TYSX8Da8aABf50yAlcafYOCMjw9TXlQWeB+K2IrrP6XXyseUF88COmAF9g2s8lUZalP7MsTRwRW+F3twQrxjXfXT0TIqMpNJDe18QJFOqbau1l00BFFISMSx2/5EtpNGgKKJM0lBDMOmhLisZ/ohZY8HWS+JgqZftSZPztFHaySqkpl25VSenw7/yzVbfc/YGHu4ckLL5LRqZgrD3O06kEnhDQslzfdH/KLAtj6Ould/zSTKdLoQq0ZgnLOVGCRzkijD3dbjaPJqhfUF9HjnPDedT0Emgm/vlnB3L8/1+D/rLC2v8L2PPCZ/QcEux2ThnsahJ20RRWE16WnCgm41wWzSvwSzwNDdut/mg3oC21kzZO6FwWL0CV2gbc9V+fWDifN1Oax4bT5PveWIhPlIo5288OjU/0hNppEwf009fXscrpMA6PoKubx9XuWDlnJymrQ6LYDC5ooYU18gbiJBIvI4S4WfBo9a+In1HAD2JtnxbE6hHFyEWKwKVjOG3Kpw0W3mNuf92HKw34C9n/zKCdVmtYA4hlMN987bZcrsjrfj/tu+lsJEp1mMIh52qOmV9MqAqJTnM+5qdQ9JpXfxNUvJrC1mIiJMgfR4l97+tkq7hwUFWNHKXFyNaokSfE/4lEMbqdw/drUmmH/u0tXB/W87qwnerDfPPNBVU=
*/