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
ET7jihWhvvFZYjMAGjM6W4W/enyQ3O0nyzOQBOQmmzI/zaNMy6WFM86s56UFZhpIeGWQU4/sE6Tc6AkC0dr6vlhXfOYjN/5T4jOzFfomoscPX/poceKT+H3igzhIpN/0bFmv4+3ETYjAocBrwTIUPu8tcuu881fo1jkT3TpnsVtnl4lYt9VdxbKKUXfTUb96rB2mxZv4CByyUvmAqKSGo7LtUkFlh1NSEQYnkixNYkwTH5pkaZL86GNmydI0mtVEc+eoMDTPI5rnq5du99K/TC+jLEYMZyrOWE3CM9+3c6gFkJ84wQHWrTDIutGZe+p7qhsTZqwbLu6njrYRlvRi1wLFYCFDljiqAb+/pkJ8ig+JeAIhjhFpwHrgDdiapVbg0xszUfIougn1QhZKPsMs+YUwJmk1lShOkqEXHoLC21zilA4cgQM9gw8PAqZyyFQFH8GCUeKiAhTkOe0Xt/v/Un96/IdpMv4NBpWhcbDCWKXiKNXHX78M0R26TkVNK7+RH/jZoB8pGI6JFkM6d4PUYI/GA6HnhtOtlnKEOhe0F3KHAcwwB12lGULK3vNCbPIiEb+RmzwHTCXVeDsOFGyY0fNy7RDAF3IIgDcbjdHna4cAvtBDgLaqr5I93y23NGlZpWICXCPYRHYrxIw7TR5m7YAvdUTj5Qj8ucJldJypzJLkg8JWrR26SOHF3R2d2EEujVu92+bIWWIWn92aCb1xkSwwHm8qvU3PK6myPuQd08S6KEOW7CMjZmI9j6d6fn4kPVJqqucjsHOllcT289QTzRvkOyO3zRbvjJT9+70zEnZ90/Yak+u8kZ6nFIKc3pPoDNlTJBc49LlbfiYFEun6adxsmc9rAkq/YCqlg2UPWxOrl89rs4138+t7Z6DW+L95QhQtZuQUsBZbg9t2oMEWVIAWv8W74cdBY/LUOo+OQ+4/TuVJGuh5uQf/bWIo1fMUVa+i6kWqc0fWwmCKKpqCRUePrJNBO+MV3X8Ocp6nPZWbr/0ukr85BOHWEeql9Ov7m5/scFfjE7XbcWCSU+iML9s5zINdgUsOCHstZgbAvEpi9hmD7o51oH+7usEk2Sl1F0IRmisHAcB1DOAOAXASQDYDwLEopPFjaqLbxu+KchYfO6OwnUp26slgxdnDYzMaFtgcJOb17WcETWXLvzAL2i2j7EGqrlvOa4mu+4882hx8XvrRcFEEG8ZAz4yyP1CRq85TJwQdtQKylvi4F2vPq9YegpZJljRiemJhpmnxsf0ydfxWk/DJ59bWqHREaA1oRJbtcTNYQUI4CH9G2S6S5s5MdUo3KpWkyZfS5AspXIFRGWUvUNlrZdk0o6ssmyfL5smyXTPK9lHZszNVY18zV95uqH6DbFJJL9MY3TGTYxnP4DE6KxsWN8lY6iCV+vZcLDXHXKpHNh7ZvE6kXj9Xkfp5Dib/mZJ3QjK1BsZchhxz/3hTyi9L5Yv7S1SKexQ/7p8vS+VhqXVUivvgvy708r/FX9jz8FlX8FYzW7lk+HmQ4i1DEV33FCferamqL5PdK9/IGitOkNzVP3A/gtq/8nJ6yEg8oV2OvqYDM0vKAXAYA/7hLAm4WwGSaWNARlkCEUnlslVjZNm1QSLZHsoLgBc8g5zCIFsIhFxEOJJCTPAFaEKDvjneOHFVNXX+9JJxenoKpPMaD/7nkK8beeQhbTZRGhNDHQaTM/lmNUBkwbIOeNqYqXgq88nl2avY0aaDrUPsMyxwaQCXCHCrGe4mCUfHw/SG45JitqjRUWQGTnpUvuUZVTVhReYo8z/FSpHBkVNPTwCRGc0K6L/m7O8ALEhlJgwCD7AR95fxGzhZf1b9Xyb0f7LyBxmn1L/I5Fg=
*/