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
CUi6RAvF4kvbXHTxqXTLwr5Kq7jnC/bTfH2a5MFQMdwSFMksOcbAth+xLOYWsH77dVprPFKtmjZLAvShMcO8oAEYapSIEyuBXYgldIMk82bnwG7tzqO2s7LhILuH6LxBgJieLm3BdgbmQL37yKp/BotCdMnux1zOC5lM8dCiiB06+6IjiRSXz4wgm9vDuxoiqe9m1fbt4NnhPCS/nC7R2/kdZa6uQ6GcdagQ8z96bsuQpR0udr/ksKUyLKo8vLVDKyl/YgD43C/dwiJXjaKuMIbTY6jqDX/32nFhD1TqEFRuZwLpb7SdqAKIrSi54tBH3g/vMn7LUpFBLlzUwQrFpZbl1rW5llvX5l5uXeu83MpRvNwaTNWoO4GKVWHgWijvwaHPpa3UyWulq8ZJJaKT10J/97r49SFSogXd4PN+7dAlPraaPgX7qxh557KOGewXVKcId7n4oGjMRK/odiMOruZMLFEYDgoVakV2QEzIrHZpUpucDs2LtQB/oHyNVn4q9OAxKgWWtqKrlSTLM+h+sUxW3gcYXdvnIt26CT9zQW1YB7F8KDSWccvJ0ksSSHiRy3q+fIs+MWnWYAYIpnXjb8aNQ7FVKwZZV2WZWD6K01dl7XFeK4c5rMry2VZBXJV14iyIAp/UvHOOokVTtGGLSiId7oPxORsC2mHvLTQa4WHvCaYTUoP4hNiPw+idLTxCeidvhKGS2WQSNobilOQkPQrHC8YQmuY7rtyNOhsR19t0w1TuGegVvMDWrB16s7a+w5u1dfBm7dinZlUNZQa4BbugBTWJ9HGo0sFMXVlFNiTYpZtuXLsCBR0CuDtzsMB7lNx8zyByE4IhcZZQ5nQ95KZIslQI0GYQoI5y8RGXchjb9jokycEg+nAb9ndeyYPKdQ8ZB3mbScPJ3TbDyfFI4+MdaMzdo0czS6iGO36QhnMc3WhgC+Yb2CbDoJO85E3nNtwPVwcfeg49Q35y25f71qj5QX3W/GCpmh+w3r/UOheIqS0V9ut2rXOBqGUusFqFqrnAp0scywXbKs8FltrnAku13rdU630/PJEtY7a5QD3OBd5G10ubIFvKcwGqEM8F2P+UJwBTtQnAausEoIsnAHX0ybo8xUC48r9bap0ArOIJwCqViV7RI08Yg1UmlocMhycAq9UQSa+O/q1qAjAVJgD5WqpsMk0AKAWWxgPdHDdNAFbzBOB0iHAGpuv9XVJHvP14B/NorCHRi9/Op8Xg2OLBeGwgxS6tb6/npRPHQBSpK4S0R2nVq5ghtFD6onZiDZy+kvfLEWm10sB5aQjY6wI2aUZ09+CmXCRHekZ0ik98jxPFyeKTk+BNyr34AKU5UCP3yUCR3OcJRfIfGgT0RnfsXGdNxYCeKi69qsOlPIEPUCJlrqFqdpAQwnhHGvRUIhhr0NOU4Jk2iOCBYEicLdUoiJjL4lmcnA8SyEmwvIMWnP7PH0d9BucF5p5VSp8JZ+kzPVn2zh4He2ePg72zf4j2zn67vfOMMkdcdHtnj1XH4bl6s0zOI+fjIGwp3q7jhLN0nJ5cOk6Ps47DUc46Tk9ee2eP1d7Z42Tv7MzYO0td/Lpeysd+ko/3qSk5qTs8V7aqNL2s0vQ6pxMGfg7U9JjejArUy0VxEL5SI7Is689p7jxFM3fmabMjQkrb6bFP60OlpO30s7bzjG7utBswe3XjVoKtmbptB8vOO68P55rX9+Sc19vjvFaWcRpDepzm9RzH83qnBR1eTiJLF9aPTNRcsZDd0tVKd06xpatXUsPWyByWyG3A7GX1SWvGZiyd3jdgp63tUIonncAkbI/95jFBZh5WwegrORrAc5Rl0Qya9wWXXBSjoRT7Alk427k=
*/