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