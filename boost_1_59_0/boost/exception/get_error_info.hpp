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
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
*/