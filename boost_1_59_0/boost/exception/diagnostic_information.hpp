//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_0552D49838DD11DD90146B8956D89593
#define BOOST_EXCEPTION_0552D49838DD11DD90146B8956D89593

#include <boost/config.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/exception/info.hpp>
#include <boost/utility/enable_if.hpp>
#ifndef BOOST_NO_RTTI
#include <boost/core/demangle.hpp>
#endif
#include <exception>
#include <sstream>
#include <string>
#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception/current_exception_cast.hpp>
#endif

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

#ifndef BOOST_NO_EXCEPTIONS
namespace
boost
    {
    namespace
    exception_detail
        {
        std::string diagnostic_information_impl( boost::exception const *, std::exception const *, bool, bool );
        }

    inline
    std::string
    current_exception_diagnostic_information( bool verbose=true)
        {
        boost::exception const * be=current_exception_cast<boost::exception const>();
        std::exception const * se=current_exception_cast<std::exception const>();
        if( be || se )
            return exception_detail::diagnostic_information_impl(be,se,true,verbose);
#if defined(__GLIBCXX__) && __cplusplus >= 201103L && !defined(BOOST_NO_RTTI)
        else if (auto* p=std::current_exception().__cxa_exception_type())
            return "Dynamic exception type: "+boost::core::demangle(p->name());
#endif
        else
            return "No diagnostic information available.";
        }
    }
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        inline
        exception const *
        get_boost_exception( exception const * e )
            {
            return e;
            }

        inline
        exception const *
        get_boost_exception( ... )
            {
            return 0;
            }

        inline
        std::exception const *
        get_std_exception( std::exception const * e )
            {
            return e;
            }

        inline
        std::exception const *
        get_std_exception( ... )
            {
            return 0;
            }

        inline
        char const *
        get_diagnostic_information( exception const & x, char const * header )
            {
#ifndef BOOST_NO_EXCEPTIONS
            try
                {
#endif
                error_info_container * c=x.data_.get();
                if( !c )
                    x.data_.adopt(c=new exception_detail::error_info_container_impl);
                char const * di=c->diagnostic_information(header);
                BOOST_ASSERT(di!=0);
                return di;
#ifndef BOOST_NO_EXCEPTIONS
                }
            catch(...)
                {
                return 0;
                }
#endif
            }

        inline
        std::string
        diagnostic_information_impl( boost::exception const * be, std::exception const * se, bool with_what, bool verbose )
            {
            if( !be && !se )
                return "Unknown exception.";
#ifndef BOOST_NO_RTTI
            if( !be )
                be=dynamic_cast<boost::exception const *>(se);
            if( !se )
                se=dynamic_cast<std::exception const *>(be);
#endif
            char const * wh=0;
            if( with_what && se )
                {
                wh=se->what();
                if( be && exception_detail::get_diagnostic_information(*be,0)==wh )
                    return wh;
                }
            std::ostringstream tmp;
            if( be && verbose )
                {
                char const * const * f=get_error_info<throw_file>(*be);
                int const * l=get_error_info<throw_line>(*be);
                char const * const * fn=get_error_info<throw_function>(*be);
                if( !f && !l && !fn )
                    tmp << "Throw location unknown (consider using BOOST_THROW_EXCEPTION)\n";
                else
                    {
                    if( f )
                        {
                        tmp << *f;
                        if( int const * l=get_error_info<throw_line>(*be) )
                            tmp << '(' << *l << "): ";
                        }
                    tmp << "Throw in function ";
                    if( char const * const * fn=get_error_info<throw_function>(*be) )
                        tmp << *fn;
                    else
                        tmp << "(unknown)";
                    tmp << '\n';
                    }
                }
#ifndef BOOST_NO_RTTI
            if ( verbose )
                tmp << std::string("Dynamic exception type: ") <<
                    core::demangle((be?(BOOST_EXCEPTION_DYNAMIC_TYPEID(*be)):(BOOST_EXCEPTION_DYNAMIC_TYPEID(*se))).type_->name()) << '\n';
#endif
            if( with_what && se && verbose )
                tmp << "std::exception::what: " << (wh ? wh : "(null)") << '\n';
            if( be )
                if( char const * s=exception_detail::get_diagnostic_information(*be,tmp.str().c_str()) )
                    if( *s )
                        return std::string(s);
            return tmp.str();
            }
        }

    template <class T>
    std::string
    diagnostic_information( T const & e, bool verbose=true )
        {
        return exception_detail::diagnostic_information_impl(exception_detail::get_boost_exception(&e),exception_detail::get_std_exception(&e),true,verbose);
        }

    inline
    char const *
    diagnostic_information_what( exception const & e, bool verbose=true ) BOOST_NOEXCEPT_OR_NOTHROW
        {
        char const * w=0;
#ifndef BOOST_NO_EXCEPTIONS
        try
            {
#endif
            (void) exception_detail::diagnostic_information_impl(&e,0,false,verbose);
            if( char const * di=exception_detail::get_diagnostic_information(e,0) )
                return di;
            else
                return "Failed to produce boost::diagnostic_information_what()";
#ifndef BOOST_NO_EXCEPTIONS
            }
        catch(
        ... )
            {
            }
#endif
        return w;
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* diagnostic_information.hpp
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
*/