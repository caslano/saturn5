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