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
V9JS2heQ34gC29uomzQWS4y3ZZth/niy0Ra4mhwP2rKO/j2S8kRmAFogmKhC/RxQ5zPoPOa3KlcLPnvLWxt1RmXpUU5nnpLUg7KWsFHlH8u6oRVbnSU2bAzGxzG7cUUpHCMzCOvfUh6MOFxSwNC4n1lhz2WlZm/QA4tTRUBf56xEfov2YNTryB86wIyfh4HaQR416B+v1MjcXjabZSYmbCQCXP6ehrxILT9PIq3dhzy+tYl//EeoXA5Uo1HKk10m5/FjvNKL4sWMUo1yk57DCtZy5o/zWc70Qxn9s3fOmfihCvlOCJ7Vd35ivUaz6Klo+JjwMtsGWduSVGEc86znXA5A97efX3SycS1q/IF+l2v8CexjqvwIpGjYKAW57/P6ynG7w+EVCM16w/tJsuDxVxxd1G4/H/RfL5kzOVSwNuxXH3jUrx6Wf5z7Mf8a45qHnTc5lWGeQVGnC5WCr2vmcQfHaCgxWztDCH/ZlGrGzQNXBxZhY8fL4BQ0vJtGASUMgnbE8q/4M0FwJPDHZG9uSZqJcxn+rBCVnMNEw1hcCZ5HsHTl7wtlx94RNpxQYDj9kZIeBSQz8xF/zVuWXxFDh6pSC+07cGwVWZAid1GWbXkZ3fFb+ZPbSUE1qBouGpOGyIu84zRnQaEtzWvm
*/