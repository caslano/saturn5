// Boost.Range library
//
//  Copyright Neil Groves 2009.
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_SUB_RANGE_HPP
#define BOOST_RANGE_SUB_RANGE_HPP

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500)) 
    #pragma warning( push )
    #pragma warning( disable : 4996 )
#endif

#include <boost/range/config.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost
{
    namespace range_detail
    {

template<class ForwardRange, class TraversalTag>
class sub_range_base
        : public iterator_range<
            BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
        >
{
    typedef iterator_range<
        BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
    > base;

protected:
    typedef BOOST_DEDUCED_TYPENAME base::iterator_range_ iterator_range_;

public:
    typedef BOOST_DEDUCED_TYPENAME range_value<ForwardRange>::type value_type;
    typedef BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type iterator;
    typedef BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type const_iterator;
    typedef BOOST_DEDUCED_TYPENAME range_difference<ForwardRange>::type difference_type;
    typedef BOOST_DEDUCED_TYPENAME range_size<ForwardRange>::type size_type;
    typedef BOOST_DEDUCED_TYPENAME range_reference<ForwardRange>::type reference;
    typedef BOOST_DEDUCED_TYPENAME range_reference<const ForwardRange>::type const_reference;

    sub_range_base()
    {
    }

    template<class Iterator>
    sub_range_base(Iterator first, Iterator last)
        : base(first, last)
    {
    }

    reference front()
    {
        return base::front();
    }

    const_reference front() const
    {
        return base::front();
    }
};

template<class ForwardRange>
class sub_range_base<ForwardRange, bidirectional_traversal_tag>
        : public sub_range_base<ForwardRange, forward_traversal_tag>
{
    typedef sub_range_base<ForwardRange, forward_traversal_tag> base;
public:
    sub_range_base()
    {
    }

    template<class Iterator>
    sub_range_base(Iterator first, Iterator last)
        : base(first, last)
    {
    }

    BOOST_DEDUCED_TYPENAME base::reference back()
    {
        return base::back();
    }

    BOOST_DEDUCED_TYPENAME base::const_reference back() const
    {
        return base::back();
    }
};

template<class ForwardRange>
class sub_range_base<ForwardRange, random_access_traversal_tag>
        : public sub_range_base<ForwardRange, bidirectional_traversal_tag>
{
    typedef sub_range_base<ForwardRange, bidirectional_traversal_tag> base;

public:
    sub_range_base()
    {
    }

    template<class Iterator>
    sub_range_base(Iterator first, Iterator last)
        : base(first, last)
    {
    }

    BOOST_DEDUCED_TYPENAME base::reference
    operator[](BOOST_DEDUCED_TYPENAME base::difference_type n)
    {
        return this->begin()[n];
    }

    BOOST_DEDUCED_TYPENAME base::const_reference
    operator[](BOOST_DEDUCED_TYPENAME base::difference_type n) const
    {
        return this->begin()[n];
    }
};

    } // namespace range_detail

    template<class ForwardRange>
    class sub_range
        : public range_detail::sub_range_base<
                ForwardRange,
                BOOST_DEDUCED_TYPENAME iterator_traversal<
                    BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
                >::type
            >
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<
            ForwardRange
        >::type iterator_t;

        typedef range_detail::sub_range_base<
            ForwardRange,
            BOOST_DEDUCED_TYPENAME iterator_traversal<
                BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
            >::type
        > base;

        typedef BOOST_DEDUCED_TYPENAME base::impl impl;

    protected:
        typedef BOOST_DEDUCED_TYPENAME base::iterator_range_ iterator_range_;

    private:
        template<class Source>
        struct is_compatible_range
            : is_convertible<
                BOOST_DEDUCED_TYPENAME mpl::eval_if<
                    has_range_iterator<Source>,
                    range_iterator<Source>,
                    mpl::identity<void>
                >::type,
                BOOST_DEDUCED_TYPENAME base::iterator
            >
        {
        };

    public:
        sub_range()
        { }

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500) ) 
        sub_range(const sub_range& r)
            : base(impl::adl_begin(const_cast<base&>(static_cast<const base&>(r))),
                   impl::adl_end(const_cast<base&>(static_cast<const base&>(r))))
        { }  
#endif

        template< class ForwardRange2 >
        sub_range(
            ForwardRange2& r,
            BOOST_DEDUCED_TYPENAME ::boost::enable_if<
                is_compatible_range<ForwardRange2>
            >::type* = 0
        )
        : base(impl::adl_begin(r), impl::adl_end(r))
        {
        }

        template< class ForwardRange2 >
        sub_range(
            const ForwardRange2& r,
            BOOST_DEDUCED_TYPENAME ::boost::enable_if<
                is_compatible_range<const ForwardRange2>
            >::type* = 0
        )
        : base(impl::adl_begin(r), impl::adl_end(r))
        {
        }

        BOOST_DEDUCED_TYPENAME base::const_iterator begin() const
        {
            return base::begin();
        }

        BOOST_DEDUCED_TYPENAME base::iterator begin()
        {
            return base::begin();
        }

        BOOST_DEDUCED_TYPENAME base::const_iterator end() const
        {
            return base::end();
        }

        BOOST_DEDUCED_TYPENAME base::iterator end()
        {
            return base::end();
        }

        template< class Iter >
        sub_range( Iter first, Iter last ) :
            base( first, last )
        { }

        template<class ForwardRange2>
        BOOST_DEDUCED_TYPENAME ::boost::enable_if<
            is_compatible_range<ForwardRange2>,
            sub_range&
        >::type
        operator=(ForwardRange2& r)
        {
            iterator_range_::operator=( r );
            return *this;
        }

        template<class ForwardRange2>
        BOOST_DEDUCED_TYPENAME ::boost::enable_if<
            is_compatible_range<const ForwardRange2>,
            sub_range&
        >::type
        operator=( const ForwardRange2& r )
        {
            iterator_range_::operator=( r );
            return *this;
        }   

        sub_range& operator=( const sub_range& r )
        {
            iterator_range_::operator=( static_cast<const iterator_range_&>(r) );
            return *this;            
        }
        
        sub_range& advance_begin(
            BOOST_DEDUCED_TYPENAME base::difference_type n)
        {
            std::advance(this->m_Begin, n);
            return *this;
        }
        
        sub_range& advance_end(
            BOOST_DEDUCED_TYPENAME base::difference_type n)
        {
            std::advance(this->m_End, n);
            return *this;
        }
    };

} // namespace 'boost'

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500)) 
    #pragma warning( pop )
#endif

#endif


/* sub_range.hpp
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
*/