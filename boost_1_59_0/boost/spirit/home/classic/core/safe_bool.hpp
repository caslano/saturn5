/*=============================================================================
    Copyright (c) 2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SAFE_BOOL_HPP)
#define BOOST_SPIRIT_SAFE_BOOL_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    namespace impl
    {
        template <typename T>
        struct no_base {};

        template <typename T>
        struct safe_bool_impl
        {
#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
            void stub(T*) {};
            typedef void (safe_bool_impl::*type)(T*);
#else
            typedef T* TP; // workaround to make parsing easier
            TP stub;
            typedef TP safe_bool_impl::*type;
#endif
        };
    }

    template <typename DerivedT, typename BaseT = impl::no_base<DerivedT> >
    struct safe_bool : BaseT
    {
    private:
        typedef impl::safe_bool_impl<DerivedT> impl_t;
        typedef typename impl_t::type bool_type;

    public:
        operator bool_type() const
        {
            return static_cast<const DerivedT*>(this)->operator_bool() ?
                &impl_t::stub : 0;
        }

        operator bool_type()
        {
            return static_cast<DerivedT*>(this)->operator_bool() ?
                &impl_t::stub : 0;
        }
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}

#endif


/* safe_bool.hpp
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
*/