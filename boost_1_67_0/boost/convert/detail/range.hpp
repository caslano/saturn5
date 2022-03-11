// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_DETAIL_RANGE_HPP
#define BOOST_CONVERT_DETAIL_RANGE_HPP

#include <boost/convert/detail/has_member.hpp>
#include <boost/convert/detail/char.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/range/iterator.hpp>

namespace boost { namespace cnv
{
    namespace detail
    {
        template<typename T, bool is_class> struct is_range : std::false_type {};

        template<typename T> struct is_range<T, /*is_class=*/true>
        {
            BOOST_DECLARE_HAS_MEMBER(has_begin, begin);
            BOOST_DECLARE_HAS_MEMBER(  has_end, end);

            static bool const value = has_begin<T>::value && has_end<T>::value;
        };
    }
    template<typename T> struct is_range : detail::is_range<typename boost::remove_const<T>::type, boost::is_class<T>::value> {};
    template<typename T, typename enable =void> struct range;
    template<typename T, typename enable =void> struct iterator;

    template<typename T>
    struct iterator<T, typename enable_if<is_range<T> >::type>
    {
        typedef typename boost::range_iterator<T>::type             type;
        typedef typename boost::range_iterator<T const>::type const_type;
        typedef typename boost::iterator_value<type>::type    value_type;
    };
    template<typename T>
    struct iterator<T*, void>
    {
        typedef typename boost::remove_const<T>::type value_type;
        typedef T*                                        type;
        typedef value_type const*                   const_type;
    };
    template<typename T>
    struct range_base
    {
        typedef typename cnv::iterator<T>::value_type     value_type;
        typedef typename cnv::iterator<T>::type             iterator;
        typedef typename cnv::iterator<T>::const_type const_iterator;
        typedef const_iterator                           sentry_type;

        iterator       begin () { return begin_; }
        const_iterator begin () const { return begin_; }
        void      operator++ () { ++begin_; }
//      void      operator-- () { --end_; }

        protected:

        range_base (iterator b, iterator e) : begin_(b), end_(e) {}

        iterator       begin_;
        iterator mutable end_;
    };

    template<typename T>
    struct range<T, typename enable_if<is_range<T> >::type> : public range_base<T>
    {
        typedef range                                   this_type;
        typedef range_base<T>                           base_type;
        typedef typename base_type::iterator             iterator;
        typedef typename base_type::const_iterator const_iterator;
        typedef const_iterator                        sentry_type;

        range (T& r) : base_type(r.begin(), r.end()) {}

        iterator       end ()       { return base_type::end_; }
        const_iterator end () const { return base_type::end_; }
        sentry_type sentry () const { return base_type::end_; }
        std::size_t   size () const { return base_type::end_ - base_type::begin_; }
        bool         empty () const { return base_type::begin_ == base_type::end_; }
    };

    template<typename T>
    struct range<T*, typename enable_if<cnv::is_char<T> >::type> : public range_base<T*>
    {
        using      this_type = range;
        using      base_type = range_base<T*>;
        using     value_type = typename boost::remove_const<T>::type;
        using       iterator = T*;
        using const_iterator = value_type const*;

        struct sentry_type
        {
            friend bool operator!=(iterator it, sentry_type) { return !!*it; }
        };

        range (iterator b, iterator e =0) : base_type(b, e) {}

        iterator       end ()       { return base_type::end_ ? base_type::end_ : (base_type::end_ = base_type::begin_ + size()); }
        const_iterator end () const { return base_type::end_ ? base_type::end_ : (base_type::end_ = base_type::begin_ + size()); }
        sentry_type sentry () const { return sentry_type(); }
        std::size_t   size () const { return std::char_traits<value_type>::length(base_type::begin_); }
        bool         empty () const { return !*base_type::begin_; }
    };
    template<typename T>
    struct range<T* const, void> : public range<T*>
    {
        range (T* b, T* e =0) : range<T*>(b, e) {}
    };
    template <typename T, std::size_t N>
    struct range<T [N], void> : public range<T*>
    {
        range (T* b, T* e =0) : range<T*>(b, e) {}
    };
}}

#endif // BOOST_CONVERT_DETAIL_RANGE_HPP

/* range.hpp
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
*/