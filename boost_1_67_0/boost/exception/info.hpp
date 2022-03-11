//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_8D22C4CA9CC811DCAA9133D256D89593
#define BOOST_EXCEPTION_8D22C4CA9CC811DCAA9133D256D89593

#include <boost/config.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/to_string_stub.hpp>
#include <boost/exception/detail/error_info_impl.hpp>
#include <boost/exception/detail/shared_ptr.hpp>
#include <map>

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
    template <class Tag,class T>
    inline
    std::string
    error_info_name( error_info<Tag,T> const & x )
        {
        return tag_type_name<Tag>();
        }

    template <class Tag,class T>
    inline
    std::string
    to_string( error_info<Tag,T> const & x )
        {
        return '[' + error_info_name(x) + "] = " + to_string_stub(x.value()) + '\n';
        }

    template <class Tag,class T>
    inline
    std::string
    error_info<Tag,T>::
    name_value_string() const
        {
        return to_string_stub(*this);
        }

    namespace
    exception_detail
        {
        class
        error_info_container_impl:
            public error_info_container
            {
            public:

            error_info_container_impl():
                count_(0)
                {
                }

            ~error_info_container_impl() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }

            void
            set( shared_ptr<error_info_base> const & x, type_info_ const & typeid_ )
                {
                BOOST_ASSERT(x);
                info_[typeid_] = x;
                diagnostic_info_str_.clear();
                }

            shared_ptr<error_info_base>
            get( type_info_ const & ti ) const
                {
                error_info_map::const_iterator i=info_.find(ti);
                if( info_.end()!=i )
                    {
                    shared_ptr<error_info_base> const & p = i->second;
#ifndef BOOST_NO_RTTI
                    BOOST_ASSERT( *BOOST_EXCEPTION_DYNAMIC_TYPEID(*p).type_==*ti.type_ );
#endif
                    return p;
                    }
                return shared_ptr<error_info_base>();
                }

            char const *
            diagnostic_information( char const * header ) const
                {
                if( header )
                    {
                    std::ostringstream tmp;
                    tmp << header;
                    for( error_info_map::const_iterator i=info_.begin(),end=info_.end(); i!=end; ++i )
                        {
                        error_info_base const & x = *i->second;
                        tmp << x.name_value_string();
                        }
                    tmp.str().swap(diagnostic_info_str_);
                    }
                return diagnostic_info_str_.c_str();
                }

            private:

            friend class boost::exception;

            typedef std::map< type_info_, shared_ptr<error_info_base> > error_info_map;
            error_info_map info_;
            mutable std::string diagnostic_info_str_;
            mutable int count_;

            error_info_container_impl( error_info_container_impl const & );
            error_info_container_impl & operator=( error_info_container const & );

            void
            add_ref() const
                {
                ++count_;
                }

            bool
            release() const
                {
                if( --count_ )
                    return false;
                else
                    {
                    delete this;
                    return true;
                    }
                }

            refcount_ptr<error_info_container>
            clone() const
                {
                refcount_ptr<error_info_container> p;
                error_info_container_impl * c=new error_info_container_impl;
                p.adopt(c);
                for( error_info_map::const_iterator i=info_.begin(),e=info_.end(); i!=e; ++i )
                    {
                    shared_ptr<error_info_base> cp(i->second->clone());
                    c->info_.insert(std::make_pair(i->first,cp));
                    }
                return p;
                }
            };

        template <class E,class Tag,class T>
        inline
        E const &
        set_info( E const & x, error_info<Tag,T> const & v )
            {
            typedef error_info<Tag,T> error_info_tag_t;
            shared_ptr<error_info_tag_t> p( new error_info_tag_t(v) );
            exception_detail::error_info_container * c=x.data_.get();
            if( !c )
                x.data_.adopt(c=new exception_detail::error_info_container_impl);
            c->set(p,BOOST_EXCEPTION_STATIC_TYPEID(error_info_tag_t));
            return x;
            }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        template <class E,class Tag,class T>
        E const & set_info( E const &, error_info<Tag,T> && );
        template <class T>
        struct set_info_rv;
        template <class Tag,class T>
        struct
        set_info_rv<error_info<Tag,T> >
            {
            template <class E,class Tag1,class T1>
            friend E const & set_info( E const &, error_info<Tag1,T1> && );
            template <class E>
            static
            E const &
            set( E const & x, error_info<Tag,T> && v )
                {
                typedef error_info<Tag,T> error_info_tag_t;
                shared_ptr<error_info_tag_t> p( new error_info_tag_t(std::move(v)) );
                exception_detail::error_info_container * c=x.data_.get();
                if( !c )
                    x.data_.adopt(c=new exception_detail::error_info_container_impl);
                c->set(p,BOOST_EXCEPTION_STATIC_TYPEID(error_info_tag_t));
                return x;
                }
            };
        template <>
        struct
        set_info_rv<throw_function>
            {
            template <class E,class Tag1,class T1>
            friend E const & set_info( E const &, error_info<Tag1,T1> && );
            template <class E>
            static
            E const &
            set( E const & x, throw_function && y )
                {
                x.throw_function_=y.v_;
                return x;
                }
            };
        template <>
        struct
        set_info_rv<throw_file>
            {
            template <class E,class Tag1,class T1>
            friend E const & set_info( E const &, error_info<Tag1,T1> && );
            template <class E>
            static
            E const &
            set( E const & x, throw_file && y )
                {
                x.throw_file_=y.v_;
                return x;
                }
            };
        template <>
        struct
        set_info_rv<throw_line>
            {
            template <class E,class Tag1,class T1>
            friend E const & set_info( E const &, error_info<Tag1,T1> && );
            template <class E>
            static
            E const &
            set( E const & x, throw_line && y )
                {
                x.throw_line_=y.v_;
                return x;
                }
            };
        template <class E,class Tag,class T>
        inline
        E const &
        set_info( E const & x, error_info<Tag,T> && v )
            {
            return set_info_rv<error_info<Tag,T> >::template set<E>(x,std::move(v));
            }
#endif

        template <class T>
        struct
        derives_boost_exception
            {
            enum e { value = (sizeof(dispatch_boost_exception((T*)0))==sizeof(large_size)) };
            };
        }

    template <class E,class Tag,class T>
    inline
    typename enable_if<exception_detail::derives_boost_exception<E>,E const &>::type
    operator<<( E const & x, error_info<Tag,T> const & v )
        {
        return exception_detail::set_info(x,v);
        }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    template <class E,class Tag,class T>
    inline
    typename enable_if<exception_detail::derives_boost_exception<E>,E const &>::type
    operator<<( E const & x, error_info<Tag,T> && v )
        {
        return exception_detail::set_info(x,std::move(v));
        }
#endif
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* info.hpp
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
*/