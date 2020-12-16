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
01xeKsM27VeGuJQH1/Qe5tIkqv1RlGukUKQays4nyhjdhvVuTSd2buTSa02hnfuOjuVqqxZH3qHF5V/51szec4vRNWcRrwvGBv0RGnRS0bS/H2u02jusY/3tuV8mc6KiVSbcWuAAnpL3ZJzz/5NNu+akNEz9+9EyD+61ABLF5x8rsMMVrLOxSGp7ypG+PPboWP1hYDHluWM7tgyLYuaenfhobsfODWaLl66cNl/YFNDY9gnXuxRrc8Fc93PHYn2X5YLDYB+BPUNgHyRYWWBXKlhH9sCf+Fq4EORim6L22LqY6sVIH9Lncw+6eHDUeLnJBhL7VpXX3pwF0L0uuv6FG1n0/sJiB9fAQmLiwKzBVWdmSgUnV6gCJ2B7987XF0pCHfN5H+t0FmjMtxTeufJpGQ5tC+hnxvfsDI5u1mZQQTG2svN8NKOBQ6BP1XJBZfNKTeTyZNNnER10KM2gOtKo2zX/HF+WNqqR85wMn8wtZ9QfGwRtrvU/z9iqioBs7wifa2yA+/9JPrVdaztUqrh07PjEBYttbZ7v82b4lwZ4nMXS+Lxssf8turXNhWFbnFvpuPJK4J6J9fpMxJD1Hc8ZdDaYM8+IzpmCb1ckmeyDhcxGgLs+aGkujvkT6Hn8XsPjUC8lGN4S41/Pc1Ofz4GFvTMwYn0Z8IIZnzex/2Drre7PMN+3ejb270q/zcd7e93L3PEDEuND370US+mVlw7WK/yp5kAwPrPRvOYPC8OY5e8Hn0O+r37yjXHjZHf/nvkVft9Tgg7eJEz7gokY9CWJ+tqVYfx19qfjjNcntV0t44jgV3htjYMKAfvCVQEPSGf9fB6aIG5LdW5L4/Qe35bmyo6ez1fLGvg9rIGP7ng+1+rh9x7PjuY378/m8w5sabxYew3jdGAv1Rt6srGdfLqMZEVLfGVWSO5sTYMbOvPySRr+2fwHmcarlX7IwSVhf+J0fn98fNCfOA36My+fsD8f4Xjrvd/wUe1fjEPxwp5bf1zwgppMkHhzHP6k79/EI6O53vdxIWJ74VyJ5eC/0lSJ1vTPgke5P2l5rvU5V0982aF/U4DeNmQ8DGl5bz3OxcnrpOke5wbwvRpr4pGge0zHcygphHPotdE59PVsjMbMHDI2/obFic/iayXvTdNvEg3PH3PX08P734l+y8ebAbU2/I6hMfPC1j8cXEI6dhrbUeYL3zl3bLbIf+tkYCQ98uD6ib/HAzp8h2HDth30+AS39/Fozu88+HiO2dx++/atQwMjvm7+vX6giXeIB/Ow/SZiftCtSUTfnaf7if57/WyDVnzIDv7ZuE8DdSO2Hh5YO6etgZ/T1sC3sjXHBD5ruCXzyZGdW7cGdXLCeXXy73G78Kyf35nl8zzgYncF1M1o125xujLXJWE3//1Osp7LK04Hdis9G/o0fLc5LtMfKx/vj5WPTyW4uvr3iWxtM05jx8bHj2fNA/3H1/XN6WvAz+lrwLOvhe157vGY+W+mzjlmPp0/ZnEaaBS1B957aTnP1auOpIpvb5/Gj0c+HiqEMp4yPDaMEY/HEp8mHkuYhu3PsjYOj2LabR89o3V/fBq/Pz5e4ivLGNuxdeCM8aHTx6PnYIznc7B9XlvwjX0PxutSDE/rCmJLiA9iu43/cbqMly/Ljau2Hz9cTHgVAzFOflt3nsf19OMNjRPfL+TvgeNyMB/nsoc/R2J8eI7E8J6Pd/n2dH0zbk/Pr4L3w8g3vN86K/p+4eMDv/DwwX2tlS5+Xr+J0c0pC37TCs/rMc+dHy9O8exXvvzY95Y+/9D3XPy8vkd0vm8xfl7fIjrft3y871s+3vctn0foWx6efUvtW34pe/+fo5b3OKmJ3y6w3ys=
*/