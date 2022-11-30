/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_MATCH_HPP)
#define BOOST_SPIRIT_MATCH_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/config.hpp>
#include <boost/spirit/home/classic/core/nil.hpp>
#include <boost/call_traits.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/home/classic/core/assert.hpp>
#include <boost/spirit/home/classic/core/safe_bool.hpp>
#include <boost/spirit/home/classic/core/impl/match_attr_traits.ipp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/is_reference.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  match class
    //
    //      The match holds the result of a parser. A match object evaluates
    //      to true when a successful match is found, otherwise false. The
    //      length of the match is the number of characters (or tokens) that
    //      is successfully matched. This can be queried through its length()
    //      member function. A negative value means that the match is
    //      unsuccessful.
    //
    //      Each parser may have an associated attribute. This attribute is
    //      also returned back to the client on a successful parse through
    //      the match object. The match's value() member function returns the
    //      match's attribute.
    //
    //      A match attribute is valid:
    //
    //          * on a successful match
    //          * when its value is set through the value(val) member function
    //          * if it is assigned or copied from a compatible match object
    //            (e.g. match<double> from match<int>) with a valid attribute.
    //
    //      The match attribute is undefined:
    //
    //          * on an unsuccessful match
    //          * when an attempt to copy or assign from another match object
    //            with an incompatible attribute type (e.g. match<std::string>
    //            from match<int>).
    //
    //      The member function has_valid_attribute() can be queried to know if
    //      it is safe to get the match's attribute. The attribute may be set
    //      through the member function value(v) where v is the new attribute
    //      value.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T = nil_t>
    class match : public safe_bool<match<T> >
    {
        typedef typename
            conditional<
                is_reference<T>::value
              , T
              , typename add_reference<
                    typename add_const<T>::type
                >::type
            >::type attr_ref_t;

    public:

        typedef typename boost::optional<T> optional_type;
        typedef attr_ref_t ctor_param_t;
        typedef attr_ref_t return_t;
        typedef T attr_t;

                                match();
        explicit                match(std::size_t length);
                                match(std::size_t length, ctor_param_t val);

        bool                    operator!() const;
        std::ptrdiff_t          length() const;
        bool                    has_valid_attribute() const;
        return_t                value() const;
        void                    swap(match& other);

        template <typename T2>
        match(match<T2> const& other)
        : len(other.length()), val()
        {
            impl::match_attr_traits<T>::copy(val, other);
        }

        template <typename T2>
        match&
        operator=(match<T2> const& other)
        {
            impl::match_attr_traits<T>::assign(val, other);
            len = other.length();
            return *this;
        }

        template <typename MatchT>
        void
        concat(MatchT const& other)
        {
            BOOST_SPIRIT_ASSERT(*this && other);
            len += other.length();
        }

        template <typename ValueT>
        void
        value(ValueT const& val_)
        {
            impl::match_attr_traits<T>::set_value(val, val_, is_reference<T>());
        }

        bool operator_bool() const
        {
            return len >= 0;
        }

    private:

        std::ptrdiff_t len;
        optional_type val;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  match class specialization for nil_t values
    //
    ///////////////////////////////////////////////////////////////////////////
    template <>
    class match<nil_t> : public safe_bool<match<nil_t> >
    {
    public:

        typedef nil_t attr_t;
        typedef nil_t return_t;

                                match();
        explicit                match(std::size_t length);
                                match(std::size_t length, nil_t);

        bool                    operator!() const;
        bool                    has_valid_attribute() const;
        std::ptrdiff_t          length() const;
        nil_t                   value() const;
        void                    value(nil_t);
        void                    swap(match& other);

        template <typename T>
        match(match<T> const& other)
        : len(other.length()) {}

        template <typename T>
        match<>&
        operator=(match<T> const& other)
        {
            len = other.length();
            return *this;
        }

        template <typename T>
        void
        concat(match<T> const& other)
        {
            BOOST_SPIRIT_ASSERT(*this && other);
            len += other.length();
        }

        bool operator_bool() const
        {
            return len >= 0;
        }

    private:

        std::ptrdiff_t len;
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif
#include <boost/spirit/home/classic/core/impl/match.ipp>


/* match.hpp
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
*/