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
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
*/