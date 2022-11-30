/*=============================================================================
    Copyright (c) 2006 Joao Abecasis
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_STATIC_HPP)
#define BOOST_SPIRIT_STATIC_HPP

#include <boost/noncopyable.hpp>
#include <boost/call_traits.hpp>
#include <boost/aligned_storage.hpp>

#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/alignment_of.hpp>

#include <boost/thread/once.hpp>

#include <memory>   // for placement new

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    //
    //  Provides thread-safe initialization of a single static instance of T.
    //
    //  This instance is guaranteed to be constructed on static storage in a
    //  thread-safe manner, on the first call to the constructor of static_.
    //
    //  Requirements:
    //      T is default constructible
    //          (There's an alternate implementation that relaxes this
    //              requirement -- Joao Abecasis)
    //      T::T() MUST not throw!
    //          this is a requirement of boost::call_once.
    //
    template <class T, class Tag>
    struct static_
        : boost::noncopyable
    {
    private:

        struct destructor
        {
            ~destructor()
            {
                static_::get_address()->~value_type();
            }
        };

        struct default_ctor
        {
            static void construct()
            {
                ::new (static_::get_address()) value_type();
                static destructor d;
            }
        };

    public:

        typedef T value_type;
        typedef typename boost::call_traits<T>::reference reference;
        typedef typename boost::call_traits<T>::const_reference const_reference;

        static_(Tag = Tag())
        {
            boost::call_once(&default_ctor::construct, constructed_);
        }

        operator reference()
        {
            return this->get();
        }

        operator const_reference() const
        {
            return this->get();
        }

        reference get()
        {
            return *this->get_address();
        }

        const_reference get() const
        {
            return *this->get_address();
        }

    private:
        typedef typename boost::add_pointer<value_type>::type pointer;

        static pointer get_address()
        {
            return static_cast<pointer>(data_.address());
        }

        typedef boost::aligned_storage<sizeof(value_type),
            boost::alignment_of<value_type>::value> storage_type;

        static storage_type data_;
        static once_flag constructed_;
    };

    template <class T, class Tag>
    typename static_<T, Tag>::storage_type static_<T, Tag>::data_;

    template <class T, class Tag>
#ifndef BOOST_THREAD_PROVIDES_ONCE_CXX11
    once_flag static_<T, Tag>::constructed_ = BOOST_ONCE_INIT;
#else
    once_flag static_<T, Tag>::constructed_;
#endif

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // include guard

/* static.hpp
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
*/