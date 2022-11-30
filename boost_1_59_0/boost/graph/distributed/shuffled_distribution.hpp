// Copyright Daniel Wallin 2007. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SHUFFLED_DISTRIBUTION_070923_HPP
#define BOOST_SHUFFLED_DISTRIBUTION_070923_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

# include <boost/assert.hpp>
# include <boost/iterator/counting_iterator.hpp>
# include <vector>

namespace boost { namespace graph { namespace distributed {

template <class BaseDistribution>
struct shuffled_distribution : BaseDistribution
{
    typedef std::size_t size_type;

    template <class ProcessGroup>
    shuffled_distribution(ProcessGroup const& pg, BaseDistribution const& base)
      : BaseDistribution(base)
      , n(num_processes(pg))
      , mapping_(make_counting_iterator(size_type(0)), make_counting_iterator(n))
      , reverse_mapping(mapping_)
    {}

    std::vector<size_type> const& mapping() const
    {
        return mapping_;
    }

    template <class InputIterator>
    void assign_mapping(InputIterator first, InputIterator last)
    {
        mapping_.assign(first, last);
        BOOST_ASSERT(mapping_.size() == n);
        reverse_mapping.resize(mapping_.size());

        for (std::vector<size_t>::iterator i(mapping_.begin());
            i != mapping_.end(); ++i)
        {
            reverse_mapping[*i] = i - mapping_.begin();
        }
    }

    BaseDistribution& base()
    {
        return *this;
    }

    BaseDistribution const& base() const
    {
        return *this;
    }

    template <class ProcessID>
    size_type block_size(ProcessID id, size_type n) const
    {
        return base().block_size(reverse_mapping[id], n);
    }

    template <class T>
    size_type operator()(T const& value) const
    {
        return mapping_[base()(value)];
    }

    template <class ProcessID>
    size_type start(ProcessID id) const
    {
        return base().start(reverse_mapping[id]);
    }

    size_type local(size_type i) const
    {
        return base().local(i);
    }

    size_type global(size_type i) const
    {
        return base().global(i);
    }

    template <class ProcessID>
    size_type global(ProcessID id, size_type n) const
    {
        return base().global(reverse_mapping[id], n);
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned long /*version*/)
    {
        ar & serialization::make_nvp("base", base());
    }

    void clear() 
    {
        base().clear();
    }

private:
    size_type n;
    std::vector<size_type> mapping_;
    std::vector<size_type> reverse_mapping;
};

}}} // namespace boost::graph::distributed

#endif // BOOST_SHUFFLED_DISTRIBUTION_070923_HPP


/* shuffled_distribution.hpp
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
*/