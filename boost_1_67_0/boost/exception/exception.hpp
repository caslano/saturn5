//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_274DA366004E11DCB1DDFE2E56D89593
#define BOOST_EXCEPTION_274DA366004E11DCB1DDFE2E56D89593

#include <boost/config.hpp>

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

        template <class>
        struct set_info_rv;

        template <>
        struct set_info_rv<throw_function>;

        template <>
        struct set_info_rv<throw_file>;

        template <>
        struct set_info_rv<throw_line>;

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
            throw_line_(-1)
            {
            }

#ifdef __HP_aCC
        //On HP aCC, this protected copy constructor prevents throwing boost::exception.
        //On all other platforms, the same effect is achieved by the pure virtual destructor.
        exception( exception const & x ) BOOST_NOEXCEPT_OR_NOTHROW:
            data_(x.data_),
            throw_function_(x.throw_function_),
            throw_file_(x.throw_file_),
            throw_line_(x.throw_line_)
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

        template <class E,class Tag,class T>
        friend E const & exception_detail::set_info( E const &, error_info<Tag,T> const & );

        friend char const * exception_detail::get_diagnostic_information( exception const &, char const * );

        template <class>
        friend struct exception_detail::get_info;
        friend struct exception_detail::get_info<throw_function>;
        friend struct exception_detail::get_info<throw_file>;
        friend struct exception_detail::get_info<throw_line>;
        template <class>
        friend struct exception_detail::set_info_rv;
        friend struct exception_detail::set_info_rv<throw_function>;
        friend struct exception_detail::set_info_rv<throw_file>;
        friend struct exception_detail::set_info_rv<throw_line>;
        friend void exception_detail::copy_boost_exception( exception *, exception const * );
#endif
        mutable exception_detail::refcount_ptr<exception_detail::error_info_container> data_;
        mutable char const * throw_function_;
        mutable char const * throw_file_;
        mutable int throw_line_;
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
                throw*this;
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