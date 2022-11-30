// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_DETAIL_RANGE_HPP
#define BOOST_CONVERT_DETAIL_RANGE_HPP

#include <boost/convert/detail/has_member.hpp>
#include <boost/convert/detail/char.hpp>
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

            static bool BOOST_CONSTEXPR_OR_CONST value = has_begin<T>::value && has_end<T>::value;
        };
    }
    template<typename T> struct is_range : detail::is_range<typename boost::remove_const<T>::type, boost::is_class<T>::value> {};
    template<typename T, typename enable =void> struct range;
    template<typename T, typename enable =void> struct iterator;

    template<typename T>
    struct iterator<T, typename std::enable_if<is_range<T>::value>::type>
    {
        using       type = typename boost::range_iterator<T>::type;
        using const_type = typename boost::range_iterator<T const>::type;
        using value_type = typename boost::iterator_value<type>::type;
    };
    template<typename T>
    struct iterator<T*, void>
    {
        using value_type = typename boost::remove_const<T>::type;
        using       type = T*;
        using const_type = value_type const*;
    };
    template<typename T>
    struct range_base
    {
        using     value_type = typename cnv::iterator<T>::value_type;
        using       iterator = typename cnv::iterator<T>::type;
        using const_iterator = typename cnv::iterator<T>::const_type;
        using    sentry_type = const_iterator;

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
    struct range<T, typename std::enable_if<is_range<T>::value>::type> : public range_base<T>
    {
        using      this_type = range;
        using      base_type = range_base<T>;
        using       iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using    sentry_type = const_iterator;

        range (T& r) : base_type(r.begin(), r.end()) {}

        iterator       end ()       { return base_type::end_; }
        const_iterator end () const { return base_type::end_; }
        sentry_type sentry () const { return base_type::end_; }
        std::size_t   size () const { return base_type::end_ - base_type::begin_; }
        bool         empty () const { return base_type::begin_ == base_type::end_; }
    };

    template<typename T>
    struct range<T*, typename std::enable_if<cnv::is_char<T>::value>::type> : public range_base<T*>
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