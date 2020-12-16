//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_BOUNDARY_BOUNDARY_POINT_HPP_INCLUDED
#define BOOST_LOCALE_BOUNDARY_BOUNDARY_POINT_HPP_INCLUDED

#include <boost/locale/boundary/types.hpp>

namespace boost {
namespace locale {
namespace boundary {

    ///
    /// \addtogroup boundary
    /// @{

    ///
    /// \brief This class represents a boundary point in the text. 
    ///
    /// It represents a pair - an iterator and a rule that defines this 
    /// point.
    ///
    /// This type of object is dereference by the iterators of boundary_point_index. Using a rule()
    /// member function you can get the reason why this specific boundary point was selected. 
    ///
    /// For example, When you use a sentence boundary analysis, the (rule() & \ref sentence_term) != 0 means
    /// that this boundary point was selected because a sentence terminator (like .?!) was spotted
    /// and the (rule() & \ref sentence_sep)!=0 means that a separator like line feed or carriage
    /// return was observed.
    ///
    /// \note
    ///
    /// -   The beginning of analyzed range is always considered a boundary point and its rule is always 0.
    /// -   when using a word boundary analysis the returned rule relates to a chunk of text preceding
    ///     this point.
    ///
    /// \see
    ///
    /// -   \ref boundary_point_index
    /// -   \ref segment
    /// -   \ref segment_index
    ///
    template<typename IteratorType>
    class boundary_point  {
    public:
        ///
        /// The type of the base iterator that iterates the original text
        ///
        typedef IteratorType iterator_type;

        ///
        /// Empty default constructor
        ///
        boundary_point() : rule_(0) {}
        
        ///
        /// Create a new boundary_point using iterator \p and a rule \a r
        ///
        boundary_point(iterator_type p,rule_type r) :
            iterator_(p),
            rule_(r)
        {
        }
        ///
        /// Set an new iterator value \a i
        ///
        void iterator(iterator_type i)
        {
            iterator_ = i;
        }
        ///
        /// Set an new rule value \a r
        ///
        void rule(rule_type r)
        {
            rule_ = r;
        }
        ///
        /// Fetch an iterator
        ///
        iterator_type iterator() const 
        {
            return iterator_;
        }
        ///
        /// Fetch a rule
        ///
        rule_type rule() const
        {
            return rule_;
        }
        ///
        /// Check if two boundary points are the same
        ///
        bool operator==(boundary_point const &other) const
        {
            return iterator_ == other.iterator_ && rule_ = other.rule_;
        }
        ///
        /// Check if two boundary points are different
        ///
        bool operator!=(boundary_point const &other) const
        {
            return !(*this==other);
        }
        ///
        /// Check if the boundary point points to same location as an iterator \a other
        ///
        bool operator==(iterator_type const &other) const
        {
            return iterator_ == other;
        }
        ///
        /// Check if the boundary point points to different location from an iterator \a other
        ///
        bool operator!=(iterator_type const &other) const
        {
            return iterator_ != other;
        }

        ///
        /// Automatic cast to the iterator it represents
        ///
        operator iterator_type ()const
        {
            return iterator_;
        }

    private:
        iterator_type iterator_;
        rule_type rule_;
       
    };
    ///
    /// Check if the boundary point \a r points to same location as an iterator \a l
    ///
    template<typename BaseIterator>
    bool operator==(BaseIterator const &l,boundary_point<BaseIterator> const &r)
    {
        return r==l;
    }
    ///
    /// Check if the boundary point \a r points to different location from an iterator \a l
    ///
    template<typename BaseIterator>
    bool operator!=(BaseIterator const &l,boundary_point<BaseIterator> const &r)
    {
        return r!=l;
    }

    /// @}
    
    typedef boundary_point<std::string::const_iterator> sboundary_point;      ///< convenience typedef
    typedef boundary_point<std::wstring::const_iterator> wsboundary_point;    ///< convenience typedef
    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    typedef boundary_point<std::u16string::const_iterator> u16sboundary_point;///< convenience typedef
    #endif
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    typedef boundary_point<std::u32string::const_iterator> u32sboundary_point;///< convenience typedef
    #endif
   
    typedef boundary_point<char const *> cboundary_point;                     ///< convenience typedef
    typedef boundary_point<wchar_t const *> wcboundary_point;                 ///< convenience typedef
    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
    typedef boundary_point<char16_t const *> u16cboundary_point;              ///< convenience typedef
    #endif
    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
    typedef boundary_point<char32_t const *> u32cboundary_point;              ///< convenience typedef
    #endif
    

} // boundary
} // locale
} // boost


#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* boundary_point.hpp
/77UfDxB8Lmzu1rO4x0HubB/w+B9yo96dPXVl69LbT+ncPMru76PrbV8aTsr5xHfTVqfWBeDcysDo/nbkqsKUa46RDl3iHLi3Rx4u0bORbnbJLki+10Q9co5X5JcMuUu5u9L+PsKn/rrqaeimfpP9JLjc4jPa5VcD8o1SHKF9n0M92fKRUn36hy2UzfKdwf2AfYAuiNQJ8b+KkDzQTUgjE+3yNh0S4xLBzsmHcx4dEuORT/cITac/+VgDHo12mk9KAorF2eDBoMmgapBtaD6xPA4dHgLb+EtvIW38Bbewlt4C2/h7f+9RYGm//v+/1PKKytPmtICMQBWfv+294Xfnoon9x9UYHoRDZvf9wMVv7/NL1HyC23+NQr+rJlN+ld78wsG7s15/cnf4cfnnPTk53/ox58hH3+ZH9/7/BYr+PL5rVHw5fMzPvLny+e3lze/f0Gh9/lV+PG9z6/Gj+99fg0K/TI/6mMFXzq/QgVfPr9KBV8+v1ry5f6Vz2+tH9/7/GI/8eWL8xPxI9eBvy9jJR7WrCtQ+5sdK+HbyM2O/8vzTGREqfXXqfSzEZ3GZFh1zNPUUa+vAxBcHY2aOhr0dRQ6PQ+rL4qiNXN9KOqgwQSlv1ajf5NCPy+YoPTjT6V+Y7tSPwwyOP0lGv2JCv0w+KBtdZVGf7Zaf0i2mhujWcdDXUdItrpIU0eRuo6QbHWjpo6x6jqCttXiWE1cm1p/0La6QqO/Sq0/aFtNiNPEtyn04+EWtK1WafS71fpDstW1mjpq1XWEZKuF8Zrng7qOkGx1saaOenUdQdvqNo3+BrX+oG11QlvNc0GtPwhb5bobnFf/XnO/yMnhPE1bhH5bN2xUu1ZCGmNLegiZpcZB0HSubi2gLc7jnlBWFQejng9piyrnXh3fIJedJs0dbq250l/wbzIG4//ZUixjLyt+TcKu6R7MSTdCykEOLWYF58Z1faaIY0WOU1/vfl3FOf0PcnnaZ4SLsaq/evWrvLiPdn2nIiGT55pmRKr6FDqd92n+r877lGW18yg8JPhPqPoYsso+RhnO/yP4PVzHGxGq2CUxP0aJKDPGP/6J/GcF/xHEP43S6sjZZpYZZxwCG0qiDWX5rK1yPaggiH07LzYK7c195rnYcVBB7JNtsjaJ6/uyf0/mvab2Fz+bLGwuhrpOyExU2SP0ObfH2l+c22PtL87vMSzrbRcsa7aRl11KMYWPC7nD7ZjZXj42sFi2gZ14r2mub+elqPs20b9vm11zJztA3yYG0beJQfRtYhB9mxhi3/Zqpm+7pP83+7YMJ25ud/qspdSwzadvZ83U9y3b4FMhc52qb6HPed82bHPetw3bnPetV1mHfZsB/FnInW/0Rt/GMc7V7N8b2Lc3Sn/f1MrX8GxNP89HB4kz5jrnlexnY6t3P+Mdttl+ThIyvVT9DH3O+5lltbHv+wp+nKrfKat+f0gD5gj+cJUdQFYR+86+HiJ4PZXvFsnAXME/EPnRUfZ7QF+xb5gyXj4VmCn4R9jzDu3WCfbTCs96851yjDgWbN297aMax2Ru9/Bb4W7GOxdt9rYPfcxz0/qZBwmZa41D1N8J0Ok8Drpos/M46KLNzuOgvcpyjiugPRdVheDnY87VWKUtpAMPF2VuMIq89Jwyo6y8aX7Cu0SZYfJzQcRc1wCrE0XuBK7Df/Z9EWrstdX3E3AMwmrZjiW8N7h97g0zHDzfa4XMYcp+dwdxb3Bvdf4McG91/gxwbw3t+X6XkDvYyEQ/RkvP996gjP/Ys30LsNqljz1Xx27rY9ITDnZh/5Evd/z+kGO3vvLMHT2OveeSCXcGH6uujvUOPmZcHcsffGx4sDkH6pwAfaz6z2I=
*/