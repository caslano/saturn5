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