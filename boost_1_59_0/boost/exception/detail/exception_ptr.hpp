//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.
//Copyright (c) 2019 Dario Menendez, Banco Santander

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_618474C2DE1511DEB74A388C56D89593
#define BOOST_EXCEPTION_618474C2DE1511DEB74A388C56D89593

#include <boost/config.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/diagnostic_information.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#   include <boost/exception/detail/clone_current_exception.hpp>
#endif
#include <boost/exception/detail/type_info.hpp>
#ifndef BOOST_NO_RTTI
#include <boost/core/demangle.hpp>
#endif
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
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
    namespace
    exception_detail
        {
#ifndef BOOST_NO_CXX11_HDR_EXCEPTION
        struct
        std_exception_ptr_wrapper:
            std::exception
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
        shared_ptr<exception_detail::clone_base const>
        inline
        wrap_exception_ptr( std::exception_ptr const & e )
            {
            exception_detail::clone_base const & base =
                boost::enable_current_exception(std_exception_ptr_wrapper(std::current_exception()));
            return shared_ptr<exception_detail::clone_base const>(base.clone());
            }
#endif
        }

    class exception_ptr;
    namespace exception_detail { void rethrow_exception_( exception_ptr const & ); }

    class
    exception_ptr
        {
        typedef boost::shared_ptr<exception_detail::clone_base const> impl;
        impl ptr_;
        friend void exception_detail::rethrow_exception_( exception_ptr const & );
        typedef exception_detail::clone_base const * (impl::*unspecified_bool_type)() const;
        public:
        exception_ptr()
            {
            }
#ifndef BOOST_NO_CXX11_HDR_EXCEPTION
        exception_ptr( std::exception_ptr const & e ):
            ptr_(exception_detail::wrap_exception_ptr(e))
            {
            }
#endif
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

    template <class E>
    inline
    exception_ptr
    copy_exception( E const & e )
        {
        E cp = e;
        exception_detail::copy_boost_exception(&cp, &e);
        return exception_ptr(boost::make_shared<wrapexcept<E> >(cp));
        }

    template <class T>
    inline
    exception_ptr
    make_exception_ptr( T const & e )
        {
        return boost::copy_exception(e);
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

#ifndef BOOST_NO_EXCEPTIONS
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
                            return exception_ptr(std::current_exception());
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
#endif // ifndef BOOST_NO_EXCEPTIONS

    namespace
    exception_detail
        {
        inline
        void
        rethrow_exception_( exception_ptr const & p )
            {
            BOOST_ASSERT(p);
#if defined( BOOST_NO_CXX11_HDR_EXCEPTION ) || defined( BOOST_NO_EXCEPTIONS )
            p.ptr_->rethrow();
#else
            try
                {
                p.ptr_->rethrow();
                }
            catch(
            std_exception_ptr_wrapper const & wrp)
                {
                // if an std::exception_ptr was wrapped above then rethrow it
                std::rethrow_exception(wrp.p);
                }
#endif
            }
        }

    BOOST_NORETURN
    inline
    void
    rethrow_exception( exception_ptr const & p )
        {
        exception_detail::rethrow_exception_(p);
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
#ifdef BOOST_NO_EXCEPTIONS
            return "<unavailable> due to BOOST_NO_EXCEPTIONS";
#else
            try
                {
                rethrow_exception(p);
                }
            catch(
            ... )
                {
                return current_exception_diagnostic_information(verbose);
                }
#endif
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