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
    error_info_name( error_info<Tag,T> const & )
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
        error_info_container_impl BOOST_FINAL:
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