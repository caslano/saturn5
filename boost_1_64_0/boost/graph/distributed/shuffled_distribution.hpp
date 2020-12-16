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
U7gEngUfhf3h43AgfBIOhU/BErgU3l7KLvsp+Bx8Hg6C78KRcAscBbfB0fBj+CI8AF9Se+0V8Gf4MqzC8/QKzIGvwYbwdXi22nHnwzfhBWqvPUTttS+F78JZcD28GW6A98ON8Am1234LboFr4efwQ3i9zdp9cBa0fNwvmAl/B4+Hs9Ue+0aYC2+CZ8Kb4QVwDuwLb4GD4G1wGtyuvvl2wLlqV30/3AMXw0/hargXboCfqd3159DjZ04cDKj9dKraTZ8Bv4Id4NewN/wBDlB76elqL/076IHzoRc+Cn3waT1+Vo9f1nTvwlT4IaygdtZpal9dEf4E/bAyz3IA1oSJsBbMgHVhJdgEVoZnwCzYFsqafvA4OBAeD0fD2vAmWAcugHXhE7AefB42gLtgI/gJPAnuh43hIXgKPAJPhX+GTWF6gL9tYDY8DdbS47p6fDJsCs+CXWAh7AqHwG5wLLxA7bEL4A2wOZwPW8KHYSv4B5gP18J2cDNsDw/CDvAoPA9+D8VenPdoT1gJ9oJ1YW/YFPaBLWFf2AVeBHvCIjgaDoDj4CB4LRwMb4FD4V1wGFwGh8OkJJ4zWBWOgSfAElgPXgIbwXGwA5wIO8NJsAhOhkPhZXAqvALeBafAh+CVcBG8Ci6GU+E3cAZMSw7ny4anwePhH0nSBN6m83SWmr/b5O9XeQ80ZX8hDG136Xyg+2FL+AA8S4/PhQthnh531fgCOB+OgQvg5fBBOBM+AufAJXABfBQ+Ax+Dz8PH4Zvw93AN3A33wCfgp/BJeBS+An+AT0MPdX0G+uDzMBW+AHPgS/AsuAJ2hS/DC+ErsBiugqPga3AafB1eC1fD2fBt+AB8Bz4M34VL4R/hOrgG7oVr4RdwHfwLXA99HsY7mAHfgzXhFtgCboV58AN4PtwG+8Lt8DL4IZwKd8Fr4fvwVrgJVvbLvAKZR/DqZmxuCfsJFhNaahKaEToQdI5B3LkJRwn9t5TPP/hfm39QPvfg2OYelM87+OfPO+i22/7N5x5E5h1MYQy7fUv5vIPyrXwr38o32f4d9v+Dxo3KLWkRmgHwD9v/t3XZ/yNz2/8jc/v+Q+b2/adyt+8/5C7ff8jcvv+QGR9/+d0L23XslC9288jLtpt/Icg8CPXNd0BfTyk2c8Lh54T25EvfJD8NDBg8uGhQ8bgJ44uGjBs7ukjtrNFzeIOiY5owYNBIR28oeRrLcU+Oz5bj7RFbJfZDRUkZzrprkuZyR48oxw3NGnfPyvH5WKw0KG23btYVu1DSvCTxdTPFVmikFWX/UyDxL1tlrUOXCbtJ/HNR8YPGThwzwdindZb4VyT+99Jqk4dH+xNcKfENyqwz9iqi97W8/OZC3VMTp85LTWxWpm1LUNPWIe1LQdKmTF0YsUdZEYxN04E0LyOjvI9ddi2aZpQXYYaked6xDVLbG44TLMeuIyEjzFco87Zf5a/Qn/H5JqOzN/okb1D0NNIvMpF1MDp3c+9Fp9JcddU7ksOFXkRdc5TziKm5WfqfPLkjB41voZM34q7DiPMNZM14XrLVf2GkjP5GNzhD0jxgZVnT467FqHncfU11eT0l3vY6Nr5yXaPGT3Bs38ZJmk89CbbXtaZjmvqOvFbSvOcpy0fhaJvUEr/P40dHjn5Ux5ixjn9Cif+WuH1l+hoMahu8Lddch3QBM4fiPMlbwRvtR46GtjK1v18h8Svs5VYHdO85lIUcSVMp6wt8o1wv5/QHLTZyFjnjgPwmvjWUjnxqP9dc8o3E493FdplrMFKvmvBiOe/3nih9sLnemqITqE3fOd7YkV8m6Xd6DjGGP8KP2qsJZfjwM3r3SyV9Y88KruuG8HUhd66rvXWd228=
*/