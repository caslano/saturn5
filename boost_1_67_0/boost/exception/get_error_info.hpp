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