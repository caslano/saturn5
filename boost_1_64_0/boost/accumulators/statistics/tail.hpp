///////////////////////////////////////////////////////////////////////////////
// tail.hpp
//
//  Copyright 2005 Eric Niebler, Michael Gauckler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_TAIL_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_STATISTICS_TAIL_HPP_EAN_28_10_2005

#include <vector>
#include <functional>
#include <boost/assert.hpp>
#include <boost/range.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/numeric/functional.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/statistics_fwd.hpp>

namespace boost { namespace accumulators
{
///////////////////////////////////////////////////////////////////////////////
// cache_size named parameters
BOOST_PARAMETER_NESTED_KEYWORD(tag, right_tail_cache_size, cache_size)
BOOST_PARAMETER_NESTED_KEYWORD(tag, left_tail_cache_size, cache_size)

BOOST_ACCUMULATORS_IGNORE_GLOBAL(right_tail_cache_size)
BOOST_ACCUMULATORS_IGNORE_GLOBAL(left_tail_cache_size)

namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_range
    /// INTERNAL ONLY
    ///
    template<typename ElementIterator, typename IndexIterator>
    struct tail_range
    {
        typedef boost::iterator_range<
            boost::reverse_iterator<boost::permutation_iterator<ElementIterator, IndexIterator> >
        > type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // make_tail_range
    /// INTERNAL ONLY
    ///
    template<typename ElementIterator, typename IndexIterator>
    typename tail_range<ElementIterator, IndexIterator>::type
    make_tail_range(ElementIterator elem_begin, IndexIterator index_begin, IndexIterator index_end)
    {
        return boost::make_iterator_range(
            boost::make_reverse_iterator(
                boost::make_permutation_iterator(elem_begin, index_end)
            )
          , boost::make_reverse_iterator(
                boost::make_permutation_iterator(elem_begin, index_begin)
            )
        );
    }

    ///////////////////////////////////////////////////////////////////////////////
    // stat_assign_visitor
    /// INTERNAL ONLY
    ///
    template<typename Args>
    struct stat_assign_visitor
    {
        stat_assign_visitor(Args const &a, std::size_t i)
          : args(a)
          , index(i)
        {
        }

        template<typename Stat>
        void operator ()(Stat &stat) const
        {
            stat.assign(this->args, this->index);
        }

    private:
        stat_assign_visitor &operator =(stat_assign_visitor const &);
        Args const &args;
        std::size_t index;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // stat_assign
    /// INTERNAL ONLY
    ///
    template<typename Args>
    inline stat_assign_visitor<Args> const stat_assign(Args const &args, std::size_t index)
    {
        return stat_assign_visitor<Args>(args, index);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // is_tail_variate_feature
    /// INTERNAL ONLY
    ///
    template<typename Stat, typename LeftRight>
    struct is_tail_variate_feature
      : mpl::false_
    {
    };

    /// INTERNAL ONLY
    ///
    template<typename VariateType, typename VariateTag, typename LeftRight>
    struct is_tail_variate_feature<tag::tail_variate<VariateType, VariateTag, LeftRight>, LeftRight>
      : mpl::true_
    {
    };

    /// INTERNAL ONLY
    ///
    template<typename LeftRight>
    struct is_tail_variate_feature<tag::tail_weights<LeftRight>, LeftRight>
      : mpl::true_
    {
    };

} // namespace detail

namespace impl
{
    ///////////////////////////////////////////////////////////////////////////////
    // tail_impl
    template<typename Sample, typename LeftRight>
    struct tail_impl
      : accumulator_base
    {
        // LeftRight must be either right or left
        BOOST_MPL_ASSERT((
            mpl::or_<is_same<LeftRight, right>, is_same<LeftRight, left> >
        ));

        typedef
            typename mpl::if_<
                is_same<LeftRight, right>
              , numeric::functional::greater<Sample const, Sample const>
              , numeric::functional::less<Sample const, Sample const>
            >::type
        predicate_type;

        // for boost::result_of
        typedef typename detail::tail_range<
            typename std::vector<Sample>::const_iterator
          , std::vector<std::size_t>::iterator
        >::type result_type;

        template<typename Args>
        tail_impl(Args const &args)
          : is_sorted(false)
          , indices()
          , samples(args[tag::tail<LeftRight>::cache_size], args[sample | Sample()])
        {
            this->indices.reserve(this->samples.size());
        }

        tail_impl(tail_impl const &that)
          : is_sorted(that.is_sorted)
          , indices(that.indices)
          , samples(that.samples)
        {
            this->indices.reserve(this->samples.size());
        }

        // This just stores the heap and the samples.
        // In operator()() below, if we are adding a new sample
        // to the sample cache, we force all the
        // tail_variates to update also. (It's not
        // good enough to wait for the accumulator_set to do it
        // for us because then information about whether a sample
        // was stored and where is lost, and would need to be
        // queried at runtime, which would be slow.) This is
        // implemented as a filtered visitation over the stats,
        // which we can access because args[accumulator] gives us
        // all the stats.

        template<typename Args>
        void operator ()(Args const &args)
        {
            if(this->indices.size() < this->samples.size())
            {
                this->indices.push_back(this->indices.size());
                this->assign(args, this->indices.back());
            }
            else if(predicate_type()(args[sample], this->samples[this->indices[0]]))
            {
                std::pop_heap(this->indices.begin(), this->indices.end(), indirect_cmp(this->samples));
                this->assign(args, this->indices.back());
            }
        }

        result_type result(dont_care) const
        {
            if(!this->is_sorted)
            {
                // Must use the same predicate here as in push_heap/pop_heap above.
                std::sort_heap(this->indices.begin(), this->indices.end(), indirect_cmp(this->samples));
                // sort_heap puts elements in reverse order. Calling std::reverse
                // turns the sorted sequence back into a valid heap.
                std::reverse(this->indices.begin(), this->indices.end());
                this->is_sorted = true;
            }

            return detail::make_tail_range(
                this->samples.begin()
              , this->indices.begin()
              , this->indices.end()
            );
        }

    private:

        struct is_tail_variate
        {
            template<typename T>
            struct apply
              : detail::is_tail_variate_feature<
                    typename detail::feature_tag<T>::type
                  , LeftRight
                >
            {};
        };

        template<typename Args>
        void assign(Args const &args, std::size_t index)
        {
            BOOST_ASSERT(index < this->samples.size());
            this->samples[index] = args[sample];
            std::push_heap(this->indices.begin(), this->indices.end(), indirect_cmp(this->samples));
            this->is_sorted = false;
            // Tell the tail variates to store their values also
            args[accumulator].template visit_if<is_tail_variate>(detail::stat_assign(args, index));
        }

        ///////////////////////////////////////////////////////////////////////////////
        //
        struct indirect_cmp
        {
            typedef std::size_t first_argument_type;
            typedef std::size_t second_argument_type;
            typedef bool result_type;

            indirect_cmp(std::vector<Sample> const &s)
              : samples(s)
            {
            }

            bool operator ()(std::size_t left, std::size_t right) const
            {
                return predicate_type()(this->samples[left], this->samples[right]);
            }

        private:
            indirect_cmp &operator =(indirect_cmp const &);
            std::vector<Sample> const &samples;
        };

    public:
        // make this accumulator serializeable
        template<class Archive>
        void serialize(Archive & ar, const unsigned int file_version)
        { 
            ar & is_sorted;
            ar & indices;
            ar & samples;
        }

    private:
        mutable bool is_sorted;
        mutable std::vector<std::size_t> indices;
        std::vector<Sample> samples;
    };

} // namespace impl

// TODO The templatized tag::tail below should inherit from the correct named parameter.
// The following lines provide a workaround, but there must be a better way of doing this.
template<typename T>
struct tail_cache_size_named_arg
{
};
template<>
struct tail_cache_size_named_arg<left>
  : tag::left_tail_cache_size
{
};
template<>
struct tail_cache_size_named_arg<right>
  : tag::right_tail_cache_size
{
};

///////////////////////////////////////////////////////////////////////////////
// tag::tail<>
//
namespace tag
{
    template<typename LeftRight>
    struct tail
      : depends_on<>
      , tail_cache_size_named_arg<LeftRight>
    {
        /// INTERNAL ONLY
        ///
        typedef accumulators::impl::tail_impl<mpl::_1, LeftRight> impl;

        #ifdef BOOST_ACCUMULATORS_DOXYGEN_INVOKED
        /// tag::tail<LeftRight>::cache_size named parameter
        static boost::parameter::keyword<tail_cache_size_named_arg<LeftRight> > const cache_size;
        #endif
    };

    struct abstract_tail
      : depends_on<>
    {
    };
}

///////////////////////////////////////////////////////////////////////////////
// extract::tail
//
namespace extract
{
    extractor<tag::abstract_tail> const tail = {};

    BOOST_ACCUMULATORS_IGNORE_GLOBAL(tail)
}

using extract::tail;

template<typename LeftRight>
struct feature_of<tag::tail<LeftRight> >
  : feature_of<tag::abstract_tail>
{
};

}} // namespace boost::accumulators

#endif

/* tail.hpp
Bk4MY7PEQIqqmzY1lYSqNjTztkLTNpiFqg3PmoWq2nh0G5OmilRFCLmWEoRPxjVEgqs3xhEuCE8XCDpKz9NwLaBiaowZFeErV35tqUroK3e10FfXNXI+Npt7u12ezUxgZ0JO5ejp0tVmejpAUHYBZ1xgq0xMHsMjlJNCGEj2GrOFcjBZXQBsDXmGKcdtrAjUK0c2DSNUg3dnTTanoJe7V1WmlzarmV40ctztJnIjbDiDNxqkMTEViCtHHSvN1PHa02dJHXXX/1uoI+L/d6VQRIdVLO0YQhB+arJj0jrEkNszaDmC29NHOiL243MP2/wWR/7jeA508Huz/TG89eZP9WYb9Hh4kiEC8OVYa2+cIMrHfvNICP4Jr5WCqlSnwkV/qziCzmSpn1KaXqZGweJJfkJmiD5cjsHBuIPR4Vkb8Jtqn38rouj7HlB7Sa9fRs+s+JP8J097OOUcPhXPn0aXMftXMMYz6eL/fcZP8Fi0oiiC+8oMyTCowtIyV1Fuw1BRhcVwABGoP/J2hRyktwsVfRsfdyLvO4KKdsV70DtxJ839I4/QR2m8Cho9SQMCkwzC7c914JNPUgfej3DVAhqCcF7lOzB6htej+1KkRb1OOdMhe1Yf4DtytcGM5SIff0w+Wmwsr1guaAht/vqD4jJ2B+TjY43M8rE3Ih//iHDqslTjx7yvaYIQTMZ9xjKn8bna+TKLaPMblROXpy/hPsSLt/FC3QMGSwcwOyLgGQQgIZ+0e1wSjyifuHskcS4lbimJSdYebZcVNnvsPefLESp9Kp+/Bfyz9Cu0e80yxqw42qq5nGvtEbrFbeaFDtId4tr4jOyyw5PeFeq5DNRzTFNP/8eJemhtpEpIm1o8CW/kAyUqnrUOOPAOJ45qic+G05ezf35PuFu/ZT8z3/nj8yynFT3LyX/vReU/8kcSyyT2VEN03VdrI0dKHmsYITCzaFj7IYr37LMi5zcUOriCJOPmmB5qGMVFXyTWtJKu+uKHy0nNtd2IXEp3rWRRDlYw7DMXL3/x/dx6/b804t+hATnXfAbn4Dt6ljRgl4O4Z72B3vQaiFmFt7KwklhCgQH0KtwELyyJk8HlDV7z2CVyU0pjuRESrQyMLstt7AaO+S5piNC1JvKZUPhLTqb3uXhwkkZ3bWPGS2j8uHWEFxRQXO3dxagFp0SWetCgUEYR1+nDooO/wOGubv+7ByP3AYSwA6TefkF7Ml9a/0zuEzi0JJp+OaW/P5x+TCR9oPaA+qe/T0DrPyQ/UF9bpFFzJzNVtabnUUQ9xdUa1z+97w2zPNBDclSt3o1qP+ge5Nrbzkem5+FtxP9Ku69D+ojpqe3fwu0le8PzNXG8Ov9g6FTrn8XR+HdRgeMRN1Cth066qlL7JT4G4RNyEr4RJeq7KqI/qA8Y4ysZWLmAXl0xjzF0uB6e60zj51iEA1GfIwgfqeKLYG1c4JnJv4u1PoYl4Np/pcyLnuKlc7BedOkc0HaXlKQgj5fOQ+V1zpU0xlvy+N9S9GVizTi9cK7/SPmFcyfEL6V5IrNeufPEh5edLW1X9qfgMVa4i1S8J5n/3Hlf0LQHqHDjkJZvuo984cZ7Y51z5QfKurJI2YasqOdcN6Soths3RVeNH7NrA0HU4UUmDa7xiQerhdWFrGZKR9uvx5TngkQcei+OddpWCM9QzeIpNnAJGfkMIFYpztM9SYOAN7xILPTQVfLVwUNkL0FmI9c6XuHt1Yd/UsnxAc3HdXFZVsUFH0yNPMbdc8CTBidQPWqaNMCQ8KkCLaAB3hEW8+ugjmtms5gfuERr1eeIhB+uZW5byuhe6IHnVNQD3z47ogf+dlM5PXBKWA+ciAJ+WhoXY24=
*/