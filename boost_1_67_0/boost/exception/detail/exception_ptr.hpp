//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.
//Copyright (c) 2019 Dario Menendez, Banco Santander

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_618474C2DE1511DEB74A388C56D89593
#define BOOST_EXCEPTION_618474C2DE1511DEB74A388C56D89593

#include <boost/config.hpp>
#ifdef BOOST_NO_EXCEPTIONS
#error This header requires exception handling to be enabled.
#endif
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/detail/clone_current_exception.hpp>
#include <boost/exception/detail/type_info.hpp>
#ifndef BOOST_NO_RTTI
#include <boost/core/demangle.hpp>
#endif
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <new>
#include <ios>
#include <stdlib.h>

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
    class exception_ptr;
    BOOST_NORETURN void rethrow_exception( exception_ptr const & );
    exception_ptr current_exception();

    class
    exception_ptr
        {
        typedef boost::shared_ptr<exception_detail::clone_base const> impl;
        impl ptr_;
        friend void rethrow_exception( exception_ptr const & );
        typedef exception_detail::clone_base const * (impl::*unspecified_bool_type)() const;
        public:
        exception_ptr()
            {
            }
        explicit
        exception_ptr( impl const & ptr ):
            ptr_(ptr)
            {
            }
        bool
        operator==( exception_ptr const & other ) const
            {
            return ptr_==other.ptr_;
            }
        bool
        operator!=( exception_ptr const & other ) const
            {
            return ptr_!=other.ptr_;
            }
        operator unspecified_bool_type() const
            {
            return ptr_?&impl::get:0;
            }
        };

    template <class T>
    inline
    exception_ptr
    copy_exception( T const & e )
        {
        try
            {
            throw enable_current_exception(e);
            }
        catch(
        ... )
            {
            return current_exception();
            }
        }

#ifndef BOOST_NO_RTTI
    typedef error_info<struct tag_original_exception_type,std::type_info const *> original_exception_type;

    inline
    std::string
    to_string( original_exception_type const & x )
        {
        return core::demangle(x.value()->name());
        }
#endif

    namespace
    exception_detail
        {
        struct
        bad_alloc_:
            boost::exception,
            std::bad_alloc
                {
                ~bad_alloc_() BOOST_NOEXCEPT_OR_NOTHROW { }
                };

        struct
        bad_exception_:
            boost::exception,
            std::bad_exception
                {
                ~bad_exception_() BOOST_NOEXCEPT_OR_NOTHROW { }
                };

        template <class Exception>
        exception_ptr
        get_static_exception_object()
            {
            Exception ba;
            exception_detail::clone_impl<Exception> c(ba);
#ifndef BOOST_EXCEPTION_DISABLE
            c <<
                throw_function(BOOST_CURRENT_FUNCTION) <<
                throw_file(__FILE__) <<
                throw_line(__LINE__);
#endif
            static exception_ptr ep(shared_ptr<exception_detail::clone_base const>(new exception_detail::clone_impl<Exception>(c)));
            return ep;
            }

        template <class Exception>
        struct
        exception_ptr_static_exception_object
            {
            static exception_ptr const e;
            };

        template <class Exception>
        exception_ptr const
        exception_ptr_static_exception_object<Exception>::
        e = get_static_exception_object<Exception>();
        }

#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
    class
    unknown_exception:
        public boost::exception,
        public std::exception
        {
        public:

        unknown_exception()
            {
            }

        explicit
        unknown_exception( std::exception const & e )
            {
            add_original_type(e);
            }

        explicit
        unknown_exception( boost::exception const & e ):
            boost::exception(e)
            {
            add_original_type(e);
            }

        ~unknown_exception() BOOST_NOEXCEPT_OR_NOTHROW
            {
            }

        private:

        template <class E>
        void
        add_original_type( E const & e )
            {
#ifndef BOOST_NO_RTTI
            (*this) << original_exception_type(&typeid(e));
#endif
            }
        };
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

    namespace
    exception_detail
        {
        template <class T>
        class
        current_exception_std_exception_wrapper:
            public T,
            public boost::exception
            {
            public:

            explicit
            current_exception_std_exception_wrapper( T const & e1 ):
                T(e1)
                {
                add_original_type(e1);
                }

            current_exception_std_exception_wrapper( T const & e1, boost::exception const & e2 ):
                T(e1),
                boost::exception(e2)
                {
                add_original_type(e1);
                }

            ~current_exception_std_exception_wrapper() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }

            private:

            template <class E>
            void
            add_original_type( E const & e )
                {
#ifndef BOOST_NO_RTTI
                (*this) << original_exception_type(&typeid(e));
#endif
                }
            };

#ifdef BOOST_NO_RTTI
        template <class T>
        boost::exception const *
        get_boost_exception( T const * )
            {
            try
                {
                throw;
                }
            catch(
            boost::exception & x )
                {
                return &x;
                }
            catch(...)
                {
                return 0;
                }
            }
#else
        template <class T>
        boost::exception const *
        get_boost_exception( T const * x )
            {
            return dynamic_cast<boost::exception const *>(x);
            }
#endif

        template <class T>
        inline
        exception_ptr
        current_exception_std_exception( T const & e1 )
            {
            if( boost::exception const * e2 = get_boost_exception(&e1) )
                return boost::copy_exception(current_exception_std_exception_wrapper<T>(e1,*e2));
            else
                return boost::copy_exception(current_exception_std_exception_wrapper<T>(e1));
            }

        inline
        exception_ptr
        current_exception_unknown_exception()
            {
            return boost::copy_exception(unknown_exception());
            }

        inline
        exception_ptr
        current_exception_unknown_boost_exception( boost::exception const & e )
            {
            return boost::copy_exception(unknown_exception(e));
            }

        inline
        exception_ptr
        current_exception_unknown_std_exception( std::exception const & e )
            {
            if( boost::exception const * be = get_boost_exception(&e) )
                return current_exception_unknown_boost_exception(*be);
            else
                return boost::copy_exception(unknown_exception(e));
            }

#ifndef BOOST_NO_CXX11_HDR_EXCEPTION
        struct
        std_exception_ptr_wrapper
            {
            std::exception_ptr p;
            explicit std_exception_ptr_wrapper( std::exception_ptr const & ptr ) BOOST_NOEXCEPT:
                p(ptr)
                {
                }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            explicit std_exception_ptr_wrapper( std::exception_ptr && ptr ) BOOST_NOEXCEPT:
                p(static_cast<std::exception_ptr &&>(ptr))
                {
                }
#endif
            };
#endif

        inline
        exception_ptr
        current_exception_impl()
            {
            exception_detail::clone_base const * e=0;
            switch(
            exception_detail::clone_current_exception(e) )
                {
                case exception_detail::clone_current_exception_result::
                success:
                    {
                    BOOST_ASSERT(e!=0);
                    return exception_ptr(shared_ptr<exception_detail::clone_base const>(e));
                    }
                case exception_detail::clone_current_exception_result::
                bad_alloc:
                    {
                    BOOST_ASSERT(!e);
                    return exception_detail::exception_ptr_static_exception_object<bad_alloc_>::e;
                    }
                case exception_detail::clone_current_exception_result::
                bad_exception:
                    {
                    BOOST_ASSERT(!e);
                    return exception_detail::exception_ptr_static_exception_object<bad_exception_>::e;
                    }
                default:
                    BOOST_ASSERT(0);
                case exception_detail::clone_current_exception_result::
                not_supported:
                    {
                    BOOST_ASSERT(!e);
                    try
                        {
                        throw;
                        }
                    catch(
                    exception_detail::clone_base & e )
                        {
                        return exception_ptr(shared_ptr<exception_detail::clone_base const>(e.clone()));
                        }
                    catch(
                    std::domain_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::invalid_argument & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::length_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::out_of_range & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::logic_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::range_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::overflow_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::underflow_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::ios_base::failure & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::runtime_error & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::bad_alloc & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
        #ifndef BOOST_NO_TYPEID
                    catch(
                    std::bad_cast & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
                    catch(
                    std::bad_typeid & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
        #endif
                    catch(
                    std::bad_exception & e )
                        {
                        return exception_detail::current_exception_std_exception(e);
                        }
#ifdef BOOST_NO_CXX11_HDR_EXCEPTION
                    // this case can be handled losslesly with std::current_exception() (see below)
                    catch(
                    std::exception & e )
                        {
                        return exception_detail::current_exception_unknown_std_exception(e);
                        }
#endif
                    catch(
                    boost::exception & e )
                        {
                        return exception_detail::current_exception_unknown_boost_exception(e);
                        }
                    catch(
                    ... )
                        {
#ifndef BOOST_NO_CXX11_HDR_EXCEPTION
                        try
                            {
                            // wrap the std::exception_ptr in a clone-enabled Boost.Exception object
                            exception_detail::clone_base const & base =
                                boost::enable_current_exception(std_exception_ptr_wrapper(std::current_exception()));
                            return exception_ptr(shared_ptr<exception_detail::clone_base const>(base.clone()));
                            }
                        catch(
                        ...)
                            {
                            return exception_detail::current_exception_unknown_exception();
                            }
#else
                        return exception_detail::current_exception_unknown_exception();
#endif
                        }
                    }
                }
            }
        }

    inline
    exception_ptr
    current_exception()
        {
        exception_ptr ret;
        try
            {
            ret=exception_detail::current_exception_impl();
            }
        catch(
        std::bad_alloc & )
            {
            ret=exception_detail::exception_ptr_static_exception_object<exception_detail::bad_alloc_>::e;
            }
        catch(
        ... )
            {
            ret=exception_detail::exception_ptr_static_exception_object<exception_detail::bad_exception_>::e;
            }
        BOOST_ASSERT(ret);
        return ret;
        }

    BOOST_NORETURN
    inline
    void
    rethrow_exception( exception_ptr const & p )
        {
        BOOST_ASSERT(p);
#ifndef BOOST_NO_CXX11_HDR_EXCEPTION
        try
            {
            p.ptr_->rethrow();
            }
        catch(
        exception_detail::std_exception_ptr_wrapper const & wrp)
            {
            // if an std::exception_ptr was wrapped above then rethrow it
            std::rethrow_exception(wrp.p);
            }
#else
        p.ptr_->rethrow();
#endif
        BOOST_ASSERT(0);
        #if defined(UNDER_CE)
            // some CE platforms don't define ::abort()
            exit(-1);
        #else
            abort();
        #endif
        }

    inline
    std::string
    diagnostic_information( exception_ptr const & p, bool verbose=true )
        {
        if( p )
            try
                {
                rethrow_exception(p);
                }
            catch(
            ... )
                {
                return current_exception_diagnostic_information(verbose);
                }
        return "<empty>";
        }

    inline
    std::string
    to_string( exception_ptr const & p )
        {
        std::string s='\n'+diagnostic_information(p);
        std::string padding("  ");
        std::string r;
        bool f=false;
        for( std::string::const_iterator i=s.begin(),e=s.end(); i!=e; ++i )
            {
            if( f )
                r+=padding;
            char c=*i;
            r+=c;
            f=(c=='\n');
            }
        return r;
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* exception_ptr.hpp
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
*/