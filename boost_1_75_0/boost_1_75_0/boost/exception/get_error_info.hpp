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
AJtigUTFrxU4nCS3ACP86pWI8Elr068dxbbNBJlMO4D7sDgL0BzzdW41d+P2+x3RfJhE83wLzYclmEv/Umi+zbxlpUJzgc8o3Y9Zu8VbFnAGPD8Hg6APwd//D23fAhdVtT18hoeOCg4Ig/ioMKkoK1G0QKwYZXRGZxRLjHxiJlFaoTKJ+UgDlPE0Spplb29P6vawx018pJglmAakppjdolu3DtED66ao6Xx7rbX3OWeYGaTv3n+/8MzZe5/9XHuttddej6+btd+71N9RTb/rfm/X/X5K/R3fVKf7/bju90Lxm43ZE/nZChCWz4rvCZSq0sDIl49MCO/Rs23yT5w16L2eI0kQuB6zuZ2NnL5YbOwvh/0xImIpSjnpngcJjNBYGGWxFLDVLbK53yYR4tskVny7nB7k++LtTfQgDxhb0Veu+3qWQJG13sbwVqX7bB5LgiuE4Xf3ikbKoIhhb6PTlRW7IbSYkjwIDJfd737EXtzvVqFm6bsNWLFT8ZpvuIjCahnwxjh8UhTQLWu9zZOtsAL1iiHCLFm2JoL+q8fyT5bcgMlrWHI53tiY16+A2weWti0aWvI4G5SG1lhKqjMAes+ut80a0WrzRIywyR/a0j8rdOQVp15TiAdKW/pu1wn2T2EqfnAV+5IRj3vFRw5PGHwEwque8JHLuHUGDsEIH9vTq1xNgFlfsMRK1SPjI0NgjF/Q4OqVCa1oD8ao
*/