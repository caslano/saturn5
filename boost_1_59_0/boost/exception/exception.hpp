//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_274DA366004E11DCB1DDFE2E56D89593
#define BOOST_EXCEPTION_274DA366004E11DCB1DDFE2E56D89593

#include <boost/assert/source_location.hpp>
#include <boost/config.hpp>
#include <exception>

#ifdef BOOST_EXCEPTION_MINI_BOOST
#include  <memory>
namespace boost { namespace exception_detail { using std::shared_ptr; } }
#else
namespace boost { template <class T> class shared_ptr; }
namespace boost { namespace exception_detail { using boost::shared_ptr; } }
#endif

#if !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#pragma warning(disable: 4265)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        class
        refcount_ptr
            {
            public:

            refcount_ptr():
                px_(0)
                {
                }

            ~refcount_ptr()
                {
                release();
                }

            refcount_ptr( refcount_ptr const & x ):
                px_(x.px_)
                {
                add_ref();
                }

            refcount_ptr &
            operator=( refcount_ptr const & x )
                {
                adopt(x.px_);
                return *this;
                }

            void
            adopt( T * px )
                {
                release();
                px_=px;
                add_ref();
                }

            T *
            get() const
                {
                return px_;
                }

            private:

            T * px_;

            void
            add_ref()
                {
                if( px_ )
                    px_->add_ref();
                }

            void
            release()
                {
                if( px_ && px_->release() )
                    px_=0;
                }
            };
        }

    ////////////////////////////////////////////////////////////////////////

    template <class Tag,class T>
    class error_info;

    typedef error_info<struct throw_function_,char const *> throw_function;
    typedef error_info<struct throw_file_,char const *> throw_file;
    typedef error_info<struct throw_line_,int> throw_line;
    typedef error_info<struct throw_column_,int> throw_column;

    template <>
    class
    error_info<throw_function_,char const *>
        {
        public:
        typedef char const * value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };

    template <>
    class
    error_info<throw_file_,char const *>
        {
        public:
        typedef char const * value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };

    template <>
    class
    error_info<throw_line_,int>
        {
        public:
        typedef int value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };

    template <>
    class
    error_info<throw_column_,int>
        {
        public:
        typedef int value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };

    class
    BOOST_SYMBOL_VISIBLE
    exception;

    namespace
    exception_detail
        {
        class error_info_base;
        struct type_info_;

        struct
        error_info_container
            {
            virtual char const * diagnostic_information( char const * ) const = 0;
            virtual shared_ptr<error_info_base> get( type_info_ const & ) const = 0;
            virtual void set( shared_ptr<error_info_base> const &, type_info_ const & ) = 0;
            virtual void add_ref() const = 0;
            virtual bool release() const = 0;
            virtual refcount_ptr<exception_detail::error_info_container> clone() const = 0;

            protected:

            ~error_info_container() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }
            };

        template <class>
        struct get_info;

        template <>
        struct get_info<throw_function>;

        template <>
        struct get_info<throw_file>;

        template <>
        struct get_info<throw_line>;

        template <>
        struct get_info<throw_column>;

        template <class>
        struct set_info_rv;

        template <>
        struct set_info_rv<throw_function>;

        template <>
        struct set_info_rv<throw_file>;

        template <>
        struct set_info_rv<throw_line>;

        template <>
        struct set_info_rv<throw_column>;

        char const * get_diagnostic_information( exception const &, char const * );

        void copy_boost_exception( exception *, exception const * );

        template <class E,class Tag,class T>
        E const & set_info( E const &, error_info<Tag,T> const & );

        template <class E>
        E const & set_info( E const &, throw_function const & );

        template <class E>
        E const & set_info( E const &, throw_file const & );

        template <class E>
        E const & set_info( E const &, throw_line const & );

        template <class E>
        E const & set_info( E const &, throw_column const & );

        boost::source_location get_exception_throw_location( exception const & );
        }

    class
    BOOST_SYMBOL_VISIBLE
    exception
        {
        //<N3757>
        public:
        template <class Tag> void set( typename Tag::type const & );
        template <class Tag> typename Tag::type const * get() const;
        //</N3757>

        protected:

        exception():
            throw_function_(0),
            throw_file_(0),
            throw_line_(-1),
            throw_column_(-1)
            {
            }

#ifdef __HP_aCC
        //On HP aCC, this protected copy constructor prevents throwing boost::exception.
        //On all other platforms, the same effect is achieved by the pure virtual destructor.
        exception( exception const & x ) BOOST_NOEXCEPT_OR_NOTHROW:
            data_(x.data_),
            throw_function_(x.throw_function_),
            throw_file_(x.throw_file_),
            throw_line_(x.throw_line_),
            throw_column_(x.throw_column_)
            {
            }
#endif

        virtual ~exception() BOOST_NOEXCEPT_OR_NOTHROW
#ifndef __HP_aCC
            = 0 //Workaround for HP aCC, =0 incorrectly leads to link errors.
#endif
            ;

#if (defined(__MWERKS__) && __MWERKS__<=0x3207) || (defined(_MSC_VER) && _MSC_VER<=1310)
        public:
#else
        private:

        template <class E>
        friend E const & exception_detail::set_info( E const &, throw_function const & );

        template <class E>
        friend E const & exception_detail::set_info( E const &, throw_file const & );

        template <class E>
        friend E const & exception_detail::set_info( E const &, throw_line const & );

        template <class E>
        friend E const & exception_detail::set_info( E const &, throw_column const & );

        template <class E,class Tag,class T>
        friend E const & exception_detail::set_info( E const &, error_info<Tag,T> const & );

        friend char const * exception_detail::get_diagnostic_information( exception const &, char const * );

        friend boost::source_location exception_detail::get_exception_throw_location( exception const & );

        template <class>
        friend struct exception_detail::get_info;
        friend struct exception_detail::get_info<throw_function>;
        friend struct exception_detail::get_info<throw_file>;
        friend struct exception_detail::get_info<throw_line>;
        friend struct exception_detail::get_info<throw_column>;
        template <class>
        friend struct exception_detail::set_info_rv;
        friend struct exception_detail::set_info_rv<throw_function>;
        friend struct exception_detail::set_info_rv<throw_file>;
        friend struct exception_detail::set_info_rv<throw_line>;
        friend struct exception_detail::set_info_rv<throw_column>;
        friend void exception_detail::copy_boost_exception( exception *, exception const * );
#endif
        mutable exception_detail::refcount_ptr<exception_detail::error_info_container> data_;
        mutable char const * throw_function_;
        mutable char const * throw_file_;
        mutable int throw_line_;
        mutable int throw_column_;
        };

    inline
    exception::
    ~exception() BOOST_NOEXCEPT_OR_NOTHROW
        {
        }

    namespace
    exception_detail
        {
        template <class E>
        E const &
        set_info( E const & x, throw_function const & y )
            {
            x.throw_function_=y.v_;
            return x;
            }

        template <class E>
        E const &
        set_info( E const & x, throw_file const & y )
            {
            x.throw_file_=y.v_;
            return x;
            }

        template <class E>
        E const &
        set_info( E const & x, throw_line const & y )
            {
            x.throw_line_=y.v_;
            return x;
            }

        template <class E>
        E const &
        set_info( E const & x, throw_column const & y )
            {
            x.throw_column_=y.v_;
            return x;
            }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

        template <>
        struct
        set_info_rv<throw_column>
            {
            template <class E>
            static
            E const &
            set( E const & x, throw_column && y )
                {
                x.throw_column_=y.v_;
                return x;
                }
            };

#endif

        inline boost::source_location get_exception_throw_location( exception const & x )
            {
            return boost::source_location(
                x.throw_file_? x.throw_file_: "",
                x.throw_line_ >= 0? x.throw_line_: 0,
                x.throw_function_? x.throw_function_: "",
                x.throw_column_ >= 0? x.throw_column_: 0
                );
            }
        }

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
        template <class T>
        struct
        BOOST_SYMBOL_VISIBLE
        error_info_injector:
            public T,
            public exception
            {
            explicit
            error_info_injector( T const & x ):
                T(x)
                {
                }

            ~error_info_injector() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }
            };

        struct large_size { char c[256]; };
        large_size dispatch_boost_exception( exception const * );

        struct small_size { };
        small_size dispatch_boost_exception( void const * );

        template <class,int>
        struct enable_error_info_helper;

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(large_size)>
            {
            typedef T type;
            };

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(small_size)>
            {
            typedef error_info_injector<T> type;
            };

        template <class T>
        struct
        enable_error_info_return_type
            {
            typedef typename enable_error_info_helper<T,sizeof(exception_detail::dispatch_boost_exception(static_cast<T *>(0)))>::type type;
            };
        }

    template <class T>
    inline
    typename
    exception_detail::enable_error_info_return_type<T>::type
    enable_error_info( T const & x )
        {
        typedef typename exception_detail::enable_error_info_return_type<T>::type rt;
        return rt(x);
        }

    ////////////////////////////////////////////////////////////////////////
#if defined(BOOST_NO_EXCEPTIONS)
    BOOST_NORETURN void throw_exception(std::exception const & e); // user defined
#endif

    namespace
    exception_detail
        {
        class
        BOOST_SYMBOL_VISIBLE
        clone_base
            {
            public:

            virtual clone_base const * clone() const = 0;
            virtual void rethrow() const = 0;

            virtual
            ~clone_base() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }
            };

        inline
        void
        copy_boost_exception( exception * a, exception const * b )
            {
            refcount_ptr<error_info_container> data;
            if( error_info_container * d=b->data_.get() )
                data = d->clone();
            a->throw_file_ = b->throw_file_;
            a->throw_line_ = b->throw_line_;
            a->throw_function_ = b->throw_function_;
            a->throw_column_ = b->throw_column_;
            a->data_ = data;
            }

        inline
        void
        copy_boost_exception( void *, void const * )
            {
            }

        template <class T>
        class
        BOOST_SYMBOL_VISIBLE
        clone_impl:
            public T,
            public virtual clone_base
            {
            struct clone_tag { };
            clone_impl( clone_impl const & x, clone_tag ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            public:

            explicit
            clone_impl( T const & x ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            ~clone_impl() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }

            private:

            clone_base const *
            clone() const
                {
                return new clone_impl(*this,clone_tag());
                }

            void
            rethrow() const
                {
#if defined(BOOST_NO_EXCEPTIONS)
                boost::throw_exception(*this);
#else
                throw*this;
#endif
                }
            };
        }

    template <class T>
    inline
    exception_detail::clone_impl<T>
    enable_current_exception( T const & x )
        {
        return exception_detail::clone_impl<T>(x);
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif

#endif // #ifndef BOOST_EXCEPTION_274DA366004E11DCB1DDFE2E56D89593

/* exception.hpp
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
*/